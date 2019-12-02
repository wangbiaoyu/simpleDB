/***
 *
 *2019-9-27 wby
 *
 ***/
#include <string>
#include "version_set.h"
#include "log_reader.h"

namespace kvDB
{

	VersionSet::VersionSet(const std::string& dbname,Env* env,
		TableCache* table,InternalKeyCompartor* cmp)
	:	dbname_(dbname)
	,	env_(env)
	,	table_(table)
	,	internal_cmp_(cmp)
	,	next_file_number_(2)
	,	manifest_file_number_(0)
	,	last_sequence(0)
	,	log_number(0)
	,	pre_log_number(0)
	,	current_(NULL)
	{
		AppendVersion(new Version(this));
	}

	Status VersionSet::Recover(){
		Status s;
		std::string manifest;
		s = env_->GetManifestFileName(dbname_,manifest);
		if(!s.ok()) { }
		File* file;
		Slice* save;
		uint64_t log_number = 0;
		bool have_log_number = false;
		uint64_t prev_log_number = 0;
		bool have_prev_log_number = false;
		uint64_t next_file = 0;
		bool have_next_file = false;
		uint64_t last_sequence = 0;
		bool have_last_sequence = false;
		VersionSetBuilder build(this,current_);
		s = env_->NewSequenceFile(file,manifest);
		LogReader reader(file,true,0);
		while(reader.NextBlock(save)){
			VersionEdit edit;
			s = edit.Decode(save);	
			if(!s.ok()) { }
			else{
				build.apply(edit);
			}
			if(edit.has_log_number_){
				log_number = edit.log_number_;
				have_log_number = true;
			}			
			if(edit.has_prev_log_number_){
				prev_log_number = edit.prev_log_number_;
				have_prev_log_number = true;
			}					
			if(edit.has_next_file_){
				next_file = edit.next_file_;
				have_next_file = true;
			}
			if(edit.has_last_sequence_){
				last_sequence = edit.last_sequence_;
				have_last_sequence = true;
			}
		}
		delete file;
		file = NULL;
		if(s.ok()){
			if(!have_next_file){
				s = Status::Corruption("no meta-nextfile entry in descriptor");
			}else if(!have_log_number){
				s = Status::Corruption("no meta-lognumber entry in descriptor");
			}else if(!have_last_sequence){
				s = Status::Corruption("no last-sequence-number entry in descriptor");
			}
			if(!have_prev_log_number){
				prev_log_number = 0;
			}
		}
		MarkFileNumberUsed(prev_log_number);
		MarkFileNumberUsed(log_number);
	
		if(s.ok()){
			Version* v = new Version(this);
			builder.SaveTo(v);
			Finalize(v);
			AppendVersion(v);	
			manifest_file_number_ = next_file_;
			next_file_number_ = next_file_ + 1;
			last_sequence_ = last_sequence;
			log_number_ = log_number;
			prev_log_number_ = prev_log_number;
		}
		return s;
	}

	void VersionSet::MarkFileNumberUsed(uint64_t number){
		if(next_file_number_ <= number){
			next_file_number_ = number + 1;
		}
	}

	void VersionSet::Finalize(Version* v){
		//Precompute best level for next compaction
		int best level = -1;
		double best_score = -1;
		for(int level = 0; level < config::kNumLevels-1; level++){
			double score;
			if(level == 0){
				score = v->files_[level].size() / 
					static_cast<double>(config::kL0_CompactionTrigger);
			}else{
				const uint64_t level_bytes = TotalFileSize(v->files_[level]);
				score = static_cast<double>(level_bytes) / MaxBytesForLevel(level);
			}
			if(score > best_score){
				best_level = level;
				best_score = score;
			}
		}
	}

	void VersionSet::AppendVersion(Version* v){
		assert(v != current);
		assert(v->refs == 0);
		if(current_ != NULL){
			current_->refs = 0;
		}
		current_ = v;
		v->Ref();
		
		v->prev_ = dummy_versions_.prev_;
		v->next_ = &dummy_versions_;
		v->prev_->next_ = v;
		v->next_->prev_ = v;
	}

class VersionSetBuilder{
	//字典升序
	private:
			
		struct AscInternalKey{
			InternalKeyCompator* cmp_;
			bool operator()(FileMetaData* f1,FileMetaData* f2){
				return cmp_->Compare(f1->smallest,f2->smallest);
			}
		};

		typedef std::set<FileMetaData*,AscInternalKey> FileSet;
		struct LevelState{
			std::set<uint64_t> deleted_files;
			FileSet* added_files;
		};

	public:

		VersionSetBuilder(VersionSet* v_set,Version* current)
		:	v_set_(v_set)
		,	current_(current)
		{
			AscInternalKey cmp;
			cmp.cmp_ = v_set_.internal_cmp_;
			for(int level = 0; level < config::kLevelNum; level++){
				levels_[level].added_files = new FileSet(cmp);
			}
		}


		void Apply(VersionEdit edit){
			//Update compaction poiniters
			for(int i = 0;i < edit->compact_pointers_.size(); i++){
				const int level = edit->compact_pointers_[i].first;
				v_set_->compact_pointer_[level] = 
					edit->compact_pointers_[i].second.Encode().ToString();	
			}							

			//Deleted Files
			const VersionEdit::DeletedFileSet& del = edit->deleted_files_;
			for(VersionEdit::DeletedFileSet::const_iterator iter = del.begin();
				iter != del.end();++iter){
				const int level = iter->first;
				const uint64_t number = iter->second;
				levels_[level].deleted_files_.insert(number);
			}
			
			//Add new files
			for(size_t i = 0;i < new_files_.size();i++){
				const int level = new_files_[i].first;
				FileMetaData* f = new FileMetaData(edit->new_files_[i].second);
				f->refs = 1;
	
				f->allowed_seeks = (f->file_size / 16384);
				if(f->allowed_seeks < 100) f->allowed_seeks = 100;
				levels_[level].deleted_files.erase(f->number);
				levels_[level].added_files->insert(f);
			}			
		}

		void SaveTo(Version* v){
			AscInteralKey cmp;
			cmp.cmp_ = &v_set_->cmp_;
			for(int level = 0; level < config::kNumLevels; level++){
				const std::vector<FileMetaData*>& base_files = base_->files_[level];
				std::vector<FileMetaData*>::const_iterator base_iter = base_files.begin();
				std::vector<FileMetaData*>::const_iterator base_end = base_files.end();
				const FileSet* added = levels_[level].added_iter = added->begin();
				v->files_[level].reserve(base_files.size() + added->size());
				for(FileSet::const_iterator added_iter = added->begin();
					added_iter !=added->end();
					++added_iter){
					for(std::vector<FileMetaData*>::const_iterator bpos = 
						std::upper_bound(base_iter,base_end,*added_iter,cmp)
						base_iter != bpos;
						++base_iter){
						MaybeAddFile(v,level,*base_iter);
					}
					MaybeAddFile(v,level,*added_iter);
				}
			
			}
		}

		void MaybeAddFile(Version* v,int level,FileMetaData* f){
			if(levels_[level].deleted_files.count(f->number) > 0){
				//File is deleted: do nothing
			}else{
				std::vector<FileMetaData*>* files = &v->files_[level];
				if(level > 0 && !files->empty()){
					assert(v_set_->cmp_.Compare((*files)[files->size()-1]->largest,f->smallest) < 0);
				}
				f->refs++;
				files->push_back(f);
			}
		}
	private:
	
		VersionSet* v_set_；
		Version* current_;
		LevelState levels_[config::kNumLevels];
};

}
