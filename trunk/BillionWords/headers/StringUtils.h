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

	static vector<string> &split(const string &s, char delim,
			vector<string> &elems);

	static vector<string> split(const string &s, char delim);

	/**
	 * Obtain the weight of n-gram
	 */
	static int getWeight(vector<string> &elems);

	/**
	 * replace all occurrences of fromString in this string with toString.
	 */
	static bool replace(std::string& str, const std::string& from, const std::string& to);

	static long hashCode(string stringToHash);

	/*
	 * return string given a long
	 */
	static string ltos(long longToCast);



};

#endif /* STRINGUTILS_H_ */
