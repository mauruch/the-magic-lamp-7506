// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "StringUtils.h"
using namespace std;

int main() {
	string line;
	string sentence = "And_finally	18";
	ifstream myfile("output.txt");
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			StringUtils::removeSpaces(line);
			StringUtils::removeSpaces(sentence);
			if (sentence.compare(line) == 0) {
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
