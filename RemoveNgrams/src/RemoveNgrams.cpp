//============================================================================
// Name        : RemoveNgrams.cpp
// Author      : mcapolupo
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

vector<string> split(const string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;

}

vector<string> split(const string &s, char delim) {
	vector<std::string> elems;
	split(s, delim, elems);
	return elems;

}

int main(int argc, char *argv[]) {
	std::ofstream outputFile;
	outputFile.open("ngrams_cleaned_up5", std::ios_base::app);

	ifstream ngramas("ngram.merged");
	string lineaDelNgrama = "";
	vector<string> vectorOfTheLine;
	int i = 0;
	if (ngramas.is_open()) {
		string lineOfText;
		while (getline(ngramas, lineaDelNgrama)) {
			vectorOfTheLine = split(lineaDelNgrama, '\t');
			string numero = vectorOfTheLine.back();
			//aca filtro todas las que son menores o iguales a cinco
			if (atoi(numero.c_str()) > 5) {
				outputFile << vectorOfTheLine[0];
				outputFile << '\t';     //le pone el tab
				outputFile << numero;   //le pone el numero
				outputFile << std::endl;
				i++;
			}
		}
	}

	outputFile.close();

	return 0;
}
