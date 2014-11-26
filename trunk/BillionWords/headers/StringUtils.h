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



};

#endif /* STRINGUTILS_H_ */
