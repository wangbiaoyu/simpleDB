#pragma once

#include <map>
#include <vector>
#include <string>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp>

using namespace std;

typedef vector<string> VS;
           //<key,value> 
typedef map<string,VS > MVS;
class HashIndex{
  
public:

    HashIndex();
    HashIndex(string table);
    static MVS getRecords(HashIndex* node);
    void setMVS(string key,VS value,HashIndex* node);
    void printNodeData(HashIndex* node);

private:

    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar,const unsigned int version){
	ar & table_;
	ar & records_;
	ar & next;
    }

    /*void save(HashIndex& hs){
	std::ofstream ofs("data");
	boost::archive::text_iarchive oa(ofs);
	oa << hs;
    }

    void load(const HashIndex& hs){
	std::ifstream ifs("data");
	boost::archive::text_iarchive ia(ifs);
	ifs >> hs;
    }*/
public:
    string table_;
    MVS records_;
    HashIndex* next;
};
