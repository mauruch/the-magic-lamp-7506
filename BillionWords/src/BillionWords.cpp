// reading a text file
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "StringUtils.h"
using namespace std;

//El primer argumento es donde esta el archivo de unigramas
//El segundo argumento es donde esta el archivo de bigramas
//El tercer argunemento es donde esta el archivo de trigramas
//El cuarto argumento va a ser el archivo de salida
//Modificar estos parametros desde las propiedades de run
int main(int argc, char *argv[]) {
	string line;
	string unigrams = argv[0];
	string bigrams = argv[1];
	string trigrams = argv[2];
	string output = argv[3];
	ifstream myfile(output.c_str());	//el c_str() es porque:the standard streams doesn't accept a standard string, only c-string! So pass the string using c_str():
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			StringUtils::removeSpaces(line);
			StringUtils::removeSpaces(unigrams);
			if (unigrams.compare(line) == 0) {
				std::vector<string> array = StringUtils::split(line, '_');
				cout << "tamaño: " << array.size() << endl;
				cout << line << endl;
				cout << "weight: " << StringUtils::getWeight(array) << endl;
			}
//			else cout << line << endl;
		}
		myfile.close();
	}

	else
		cout << "Unable to open file";

	return 0;
}
