/***
 *
 *2019-9-27 wby
 *
 ***/

#pragma once

#include <status.h>

namespace kvDB
{
	class VersionSet
	{
	
	public:
		VersionSet(const std::string& dbname, Env* env,TableCache* table);
		Status Recover();
		Status AppendVersion(Version* version);
		void MarkFileNumberUsed(uint64_t number);
		Finalize(Version* v);
		
			
	private:
		const std::string& dbname_;
		Env* env_;
		TableCache* table_;
	
	};

	class Version{
	
	public:
		Version(VersionSet* ver_set);

	private:
		uint64_t next_file_number_;
		uint64_t manifest_file_number_;
		uint64_t log_number_;
		uint64_t pre_log_number_;
		SequenceNumber last_sequence_;
		
		std::vector<FileMetaData*> files_[config::kNumLevels];
		std::vector<uint64_t> deleted_files_;

		Version* current_;
		Version* pre_;
		Version* next_;
		InternalCompator* internal_cmp_;
	};
}	
