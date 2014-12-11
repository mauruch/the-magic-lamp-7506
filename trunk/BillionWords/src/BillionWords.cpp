#include "../headers/CONSTANTES.h"
#include "../headers/StringUtils.h"
#include "../headers/NGram.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {

	//Phase 1: Init Model

	NGram *nGram = new NGram();
	StringUtils *stringUtils = new StringUtils();

//	Phase 2: Predict word
	ifstream fileTest_v2("test_v2.txt");

	std::ofstream outputFile; //abro un archivo de salida
	outputFile.open("LuisTeAmo.txt", std::ios_base::app); //le indico el nombre del archivo de salida

	if (fileTest_v2.is_open()) {
		//inicializo EVERYTHING afuera
		string lineOfText;
		vector<string> vectorLine;
		string missingWord = "";
		int startOfSentence;
		int longOfSentence;
		int counter;
		unsigned int wordMissingPos;
		int iterator;

		//Hago esto una sola vez para ponerle el "id", "sentence"
		getline(fileTest_v2, lineOfText);
		outputFile << lineOfText;
		outputFile << std::endl;

		while (getline(fileTest_v2, lineOfText)) {
			try {
				//aca se procesaria el metodo
				startOfSentence = 0;
				longOfSentence = lineOfText.length();
				startOfSentence = lineOfText.find("\"");
				for (counter = 0; counter < startOfSentence; counter++) {
					outputFile << lineOfText[counter];
				}
//				outputFile << "\""; //la parte inicial de las comillas
				lineOfText.erase(0, lineOfText.find_first_of("\"") + 1);
				lineOfText.erase(lineOfText.find_last_of("\""), lineOfText.size() - 1);
//				lineOfText.clear();

			} catch (...) {
				cout << "error con la oracion: " << lineOfText << endl;
			}

				vectorLine = stringUtils->split(lineOfText, ' ');
				if (vectorLine.size()< 6){
					std::locale loc;
					wordMissingPos = nGram->whereIsMissingTheWord(&vectorLine);
		//			cout << wordMissingPos << endl;
					missingWord = nGram->findMissingWord(&vectorLine, wordMissingPos);
//					cout << missingWord << endl;
					  for (std::string::size_type i=0; i<missingWord.length(); ++i){
					    missingWord[i] = tolower(missingWord[i],loc);
					  }
					  if(missingWord != "")
						cout << endl << "la palabra que pongo es " << missingWord << endl;

				}
				else missingWord="";


			//le agrego la primer comilla al output
			outputFile << "\"";

			if(lineOfText == "\"")
				lineOfText = "";

			if (missingWord != "" && lineOfText != "") {
				if (wordMissingPos < vectorLine.size()) {
					vectorLine.insert(vectorLine.begin() + wordMissingPos,
							missingWord);
				} else
					vectorLine.insert(vectorLine.end(), missingWord);

				//			nGram->fillTheMissingWord(&lineOfText); //aca le agrego la palabra que le falta
				for (iterator = 0; iterator < vectorLine.size();
						iterator++) {
					outputFile << vectorLine[iterator];
					if (iterator != (vectorLine.size() - 1)) {
						outputFile << " ";
					}
				}
			} else
				outputFile << lineOfText;

			outputFile << "\""; //la parte final de las comillas
			outputFile << std::endl;
			vectorLine.clear();
			lineOfText.clear();
		}

	} else {
		cout << "Problemas al abrir los archivos" << endl;
		cout << "Probar viendo si las direcciones pasadas son correctas"
				<< endl;

		return ERROR_AL_ABRIR_ARCHIVO;
	}
	cout << "Fin del procesamiento del archivo" << endl;
	return 0;
}

