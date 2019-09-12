/***
 *
 *2019-9-12 wby
 *
 ***/

#pragma once


namespace kvDB{

	struct Option{
		
		bool create_if_missing;
		
		size_t write_buffer_size;

		size_t block_size;	
	
		Option()
		:	create_if_missing(false)
		,	write_buffer_size(4<<20)
		,  	block_size(4<<10)
		{ }

	};

	struct ReadOption{
		
		const SnapShot* snapshot;

		ReadOption(): snapshot(NULL){ }

	};

	struct WriteOption{
		
		bool sync;
		
		WriteOption():sync(false) { }

	};
}
