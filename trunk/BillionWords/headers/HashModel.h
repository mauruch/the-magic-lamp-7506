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
	static map<string, string> unigrams;
	static map<long, map<string, string> > bigrams;
	static map<long, map<string, string> > trigrams;
public:
	HashModel();
	void initModel();
	static map<string, string> getUnigrams();
	static map<long, std::map<string, string> > getBigrams();
	static map<long, std::map<string, string> > getTrigrams();
	virtual ~HashModel();
};

#endif /* HASHMODEL_H_ */
