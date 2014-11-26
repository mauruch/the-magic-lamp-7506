// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "../headers/CONSTANTES.h"
#include "../headers/StringUtils.h"
#include "../headers/NGram.h"
using namespace std;

int main(int argc, char *argv[]) {

	/* ngram file */
	string ngrams = argv[1];

	/* file to predict */
	string test_v2 = argv[2];

	NGram *ngram = new NGram(ngrams);

	ngram->getWeight("nueve diez");

	ifstream fileNgrams(ngrams.c_str());
	ifstream fileTest_v2(test_v2.c_str());

	if (fileNgrams.is_open() && fileTest_v2.is_open()) {
		//Una vez que tengo los files cargados
		//si llego aca es que checkee que ya se han abierto bien los archivos
		string lineaTexto;

//			while (getline(fileTest_v2, lineaTexto)) {
//							StringUtils::removeSpaces(lineaTexto);
////								std::vector<string> array = StringUtils::split(lineaTexto, '_');
////								cout << "tamaño: " << array.size() << endl;
////								cout << lineaTexto << endl;
////								cout << "weight: " << StringUtils::getWeight(array) << endl;
//
//				//			else cout << line << endl;
//
//			}

	} else {
		cout << "Problemas al abrir los archivos" << endl;
		cout << "Probar viendo si las direcciones pasadas son correctas" << endl;

		return ERROR_AL_ABRIR_ARCHIVO;
	}

	return 0;
}


