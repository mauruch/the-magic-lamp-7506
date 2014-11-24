#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

class StringUtils {

private:
	string direccionNgramas;

public:

	virtual ~StringUtils();

	StringUtils(string direccionDeLosNgramas);

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

	/*devuelve el peso del ngrama solicitado */
	int devolverPesoNgrama(string stringABuscar);

};

#endif /* STRINGUTILS_H_ */
