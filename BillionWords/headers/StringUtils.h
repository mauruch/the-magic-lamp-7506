#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <boost/functional/hash.hpp>
using namespace std;

class StringUtils {

public:

	virtual ~StringUtils();

	StringUtils();

	vector<string> &split(const string &s, char delim,
			vector<string> &elems);

	vector<string> split(const string &s, char delim);

	/**
	 * Obtain the weight of n-gram
	 */
	int getWeight(vector<string> &elems);

	/**
	 * replace all occurrences of fromString in this string with toString.
	 */
	bool replace(std::string& str, const std::string& from, const std::string& to);

	long hashCode(string stringToHash);

	/*
	 * return string given a long
	 */
	string ltos(long longToCast);



};

#endif /* STRINGUTILS_H_ */
