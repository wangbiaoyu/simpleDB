/***
 *
 *2019-10-17 wby
 *
 ***/
#pragma once


namespace kvDB{

class Compator{

public:
	virtual ~Compator();
	
	virtual bool Compare() =  0;
private:
	

};

}
