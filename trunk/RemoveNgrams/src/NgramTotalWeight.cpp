#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "../../BillionWords/headers/StringUtils.h"

using namespace std;



int main1(int argc, char *argv[]) {
	ifstream ngramas("ngrams_cleaned_up5");
	string lineaDelNgrama = "";
	vector<string> vectorOfTheLine;
	StringUtils *stringUtils = new StringUtils();

	unsigned int totalCounter = 0;
	if (ngramas.is_open()) {
		string lineOfText;
		while (getline(ngramas, lineaDelNgrama)) {
			vectorOfTheLine = stringUtils->split(lineaDelNgrama, ' ');
			if(vectorOfTheLine.size() == 1){
				vectorOfTheLine = stringUtils->split(lineaDelNgrama, '\t');
				string numero = vectorOfTheLine.back();
				totalCounter += atoi(numero.c_str());
			}
		}
	}
	else {
		cout << "no se pudo abrir el archivo" << endl;
		return -1;
	}
	ngramas.close();
	cout << "El PESO total de UNIGramas es: " << totalCounter << endl;
	return 0;
}
