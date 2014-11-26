#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
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
	 * Trim string, remove all whitespace
	 */
	static void removeSpaces(string& str);


	/**
	 * replace all occurrences of fromString in this string with toString.
	 */
	static bool replace(std::string& str, const std::string& from, const std::string& to);



};

#endif /* STRINGUTILS_H_ */
