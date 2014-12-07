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

	//Phase 1: Init Model

	NGram *nGram = new NGram();

//	Phase 2: Predict word
	ifstream fileTest_v2("test_v2.txt");

	if (fileTest_v2.is_open()) {
		string lineOfText;
		int lineCounter = 1;
		//Skip first line
		getline(fileTest_v2, lineOfText);
		while (getline(fileTest_v2, lineOfText)) {
			try {
				lineOfText.erase(0, lineOfText.find_first_of("\"") + 1);
				lineOfText.erase(lineOfText.find_last_of("\"") - 1, lineOfText.size() - 1);
			} catch(...){
				cout << "error con la oracion: " << lineOfText << endl;
			}
			vector<string> vectorLine = StringUtils::split(lineOfText, ' ');
			unsigned int wordMissingPos = nGram->whereIsMissingTheWord(vectorLine);

			cout << "Linea procesada: "<< lineCounter << endl;
			cout << "Posicion: " << wordMissingPos << endl;
			lineCounter++;
		}

	} else {
		cout << "Problemas al abrir los archivos" << endl;
		cout << "Probar viendo si las direcciones pasadas son correctas"<< endl;

		return ERROR_AL_ABRIR_ARCHIVO;
	}
	cout << "Fin del procesamiento del archivo" << endl;
	return 0;
}

