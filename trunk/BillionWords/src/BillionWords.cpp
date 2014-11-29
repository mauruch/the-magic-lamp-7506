#include "../headers/CONSTANTES.h"
#include "../headers/StringUtils.h"
#include "../headers/NGram.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;


int main(int argc, char *argv[]) {
	ifstream fileTest_v2 ("test_v2.txt");


	if (fileTest_v2.is_open()){
			string lineOfText;
			getline(fileTest_v2, lineOfText);
			while (getline(fileTest_v2, lineOfText)) {
				vector<string> vectorLine = StringUtils::split(lineOfText, ' ');
				unsigned int wordMissingPos = NGram::whereIsMissingTheWord(vectorLine);
				string salida = vectorLine.at(wordMissingPos).append(" POSICION ");
				cout << salida << endl;
				cout << wordMissingPos << endl;
			}

	}
	else{
		cout << "Problemas al abrir los archivos" << endl;
		cout << "Probar viendo si las direcciones pasadas son correctas" << endl;

		return ERROR_AL_ABRIR_ARCHIVO;
	}

	return 0;
}

