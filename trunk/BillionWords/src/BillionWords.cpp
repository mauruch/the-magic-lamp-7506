#include "../headers/CONSTANTES.h"
#include "../headers/StringUtils.h"
#include "../headers/NGram.h"
#include "../headers/HashModel.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {

	//Phase 1: Init Model

	HashModel *ourModel = new HashModel();
	ourModel->initModel();

	//Phase 2: Predict word

	ifstream fileTest_v2("test_v2.txt");

	if (fileTest_v2.is_open()) {
		string lineOfText;
		//Skip first line
		getline(fileTest_v2, lineOfText);
		while (getline(fileTest_v2, lineOfText)) {
			lineOfText.erase(0, lineOfText.find_first_of("\"") + 1);
			vector<string> vectorLine = StringUtils::split(lineOfText, ' ');
			lineOfText.erase(lineOfText.find_last_of(".") - 1, lineOfText.size() - 1);
			unsigned int wordMissingPos = NGram::whereIsMissingTheWord(vectorLine);
			string salida = vectorLine.at(wordMissingPos).append(" POSICION ");
			cout << salida << endl;
			cout << wordMissingPos << endl;
		}

	} else {
		cout << "Problemas al abrir los archivos" << endl;
		cout << "Probar viendo si las direcciones pasadas son correctas"
				<< endl;

		return ERROR_AL_ABRIR_ARCHIVO;
	}

	return 0;
}

