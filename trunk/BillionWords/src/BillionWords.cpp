// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "../headers/CONSTANTES.h"
#include "../headers/StringUtils.h"
using namespace std;

//El primer argumento es donde esta el archivo de ngramas
//El segundo argumento es donde esta el archivo a predecir el que se llama test_v2
//Modificar estos parametros desde las propiedades de run
int main(int argc, char *argv[]) {
	string ngrams = argv[1];
	string test_v2 = argv[2];

	StringUtils *stringUtils = new StringUtils(ngrams);	//para usar sus funciones

	stringUtils->devolverPesoNgrama("nueve diez");

	ifstream fileNgrams(ngrams.c_str());
	ifstream fileTest_v2(test_v2.c_str());
//el c_str() es porque:the standard streams doesn't accept a standard string, only c-string! So pass the string using c_str():

	if (fileNgrams.is_open() && fileTest_v2.is_open()){
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

	}
	else{
		cout << "Problemas al abrir los archivos" << endl;
		cout << "Probar viendo si las direcciones pasadas son correctas" << endl;

		return ERROR_AL_ABRIR_ARCHIVO;
	}



	return 0;
}




//	ifstream myfile(output.c_str());	//el c_str() es porque:the standard streams doesn't accept a standard string, only c-string! So pass the string using c_str():
//	if (myfile.is_open()) {
//		while (getline(myfile, line)) {
//			StringUtils::removeSpaces(line);
//			StringUtils::removeSpaces(ngrams);
//			if (ngrams.compare(line) == 0) {
//				std::vector<string> array = StringUtils::split(line, '_');
//				cout << "tamaño: " << array.size() << endl;
//				cout << line << endl;
//				cout << "weight: " << StringUtils::getWeight(array) << endl;
//			}
////			else cout << line << endl;
//		}
//		myfile.close();
//	}
//
//	else
//		cout << "Unable to open file";
//
//	return 0;
//}


