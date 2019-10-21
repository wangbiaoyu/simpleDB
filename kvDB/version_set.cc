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
			
		}
	}

	void VersionSet::MarkFileNumberUsed(uint64_t number){
		if(next_file_number_ <= number){
			next_file_number_ = number + 1;
		}
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
		}
	private:
	
		VersionSet* v_set_；
		Version* current_;
		LevelState levels_[config::kNumLevels];
}

}
