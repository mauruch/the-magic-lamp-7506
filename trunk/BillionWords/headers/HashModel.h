/*
 * HashModel.h
 *
 *  Created on: 5/12/2014
 *      Author: mauro
 */

#ifndef HASHMODEL_H_
#define HASHMODEL_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>


using namespace std;

class HashModel {
private:
	map<string, string> unigrams;
	map<long, map<string, string> > bigrams;
	map<long, map<string, string> > trigrams;
public:
	HashModel();
	void initModel();
	map<string, string> getUnigrams();
	map<long, std::map<string, string> > getBigrams();
	map<long, std::map<string, string> > getTrigrams();
	virtual ~HashModel();
};

#endif /* HASHMODEL_H_ */
