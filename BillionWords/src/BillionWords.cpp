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

//El primer argumento es donde esta el archivo de ngramas
//El segundo argumento es donde esta el archivo a predecir el que se llama test_v2
//Modificar estos parametros desde las propiedades de run
int main(int argc, char *argv[]) {
	string ngrams = argv[1];	//direccion de donde se encuentra el archivo
	string test_v2 = argv[2];	//direccion de donde se encuentra el archivo

	std::ofstream outputFile;									//abro un archivo de salida
	outputFile.open("resultadoFinal.txt", std::ios_base::app);	//le indico el nombre del archivo de salida

	ifstream fileNgrams(ngrams.c_str());
	ifstream fileTest_v2(test_v2.c_str());
//el c_str() es porque:the standard streams doesn't accept a standard string, only c-string! So pass the string using c_str():
	NGram *NGramFunctions = new NGram(ngrams);	//Inicializo el NGram con la direccion donde se encuentra el archivo de los Ngramas

	if (fileNgrams.is_open() && fileTest_v2.is_open()){
		//Una vez que tengo los files cargados
		//si llego aca es que checkee que ya se han abierto bien los archivos
			string lineOfText;
			//Hago esto una sola vez para ponerle el "id", "sentence"
			getline(fileTest_v2, lineOfText);
			outputFile << lineOfText;
			outputFile << std::endl;

			while (getline(fileTest_v2, lineOfText)) {
				//aca se procesaria el metodo
				int startOfSentence;
				int longOfSentence = lineOfText.length();
				startOfSentence = lineOfText.find("\"");

				for (int counter=0 ; counter<startOfSentence ; counter++ ){
					outputFile << lineOfText[counter];
				}
				outputFile << "\"";	//la parte inicial de las comillas
				lineOfText = lineOfText.substr (startOfSentence+1,(longOfSentence -startOfSentence-2));	//aca tengo la frase sin la primera ni la ultima comilla

				NGramFunctions->fillTheMissingWord(&lineOfText);	//aca le agrego la palabra que le falta

				outputFile << lineOfText;
				outputFile << "\"";	//la parte final de las comillas

				outputFile << std::endl;
			}

	}
	else{
		cout << "Problemas al abrir los archivos" << endl;
		cout << "Probar viendo si las direcciones pasadas son correctas" << endl;

		return ERROR_AL_ABRIR_ARCHIVO;
	}


	outputFile.close();
	return 0;
}

