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
	string ngrams = argv[1];
	string test_v2 = argv[2];
	std::ofstream resultadoFinal;
	resultadoFinal.open("resultadoFinal.txt", std::ios_base::app);

	ifstream fileNgrams(ngrams.c_str());
	ifstream fileTest_v2(test_v2.c_str());
//el c_str() es porque:the standard streams doesn't accept a standard string, only c-string! So pass the string using c_str():

	if (fileNgrams.is_open() && fileTest_v2.is_open()){
		//Una vez que tengo los files cargados
		//si llego aca es que checkee que ya se han abierto bien los archivos
			string lineaTexto;
			//Hago esto una sola vez para ponerle el "id", "sentence"
			getline(fileTest_v2, lineaTexto);
			resultadoFinal << lineaTexto;
			resultadoFinal << std::endl;

			while (getline(fileTest_v2, lineaTexto)) {
				int iniciaFrase;
//				int terminaFrase;
				int largoFrase = lineaTexto.length();
				string linea = lineaTexto;
				string parsearFrase = "";
				iniciaFrase = lineaTexto.find("\"");
//				terminaFrase = lineaTexto.rfind("\"");
				for (int contador=0 ; contador<iniciaFrase ; contador++ ){
					resultadoFinal << lineaTexto[contador];
				}
				resultadoFinal << "\"";	//la parte inicial de las comillas

				lineaTexto = lineaTexto.substr (iniciaFrase+1,(largoFrase -iniciaFrase-2));	//aca tengo la frase sin la primera ni la ultima comilla
				resultadoFinal << lineaTexto;
				resultadoFinal << "\"";	//la parte final de las comillas

				resultadoFinal << std::endl;
			}

	}
	else{
		cout << "Problemas al abrir los archivos" << endl;
		cout << "Probar viendo si las direcciones pasadas son correctas" << endl;

		return ERROR_AL_ABRIR_ARCHIVO;
	}


	resultadoFinal.close();
	return 0;
}

