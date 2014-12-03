#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>     /* atoi */
#include "StringUtils.h"

#define LINEAS_TOTALES_DE_NGRAMAS 233172601
using namespace std;

struct nGramas {
  unsigned long int  valor;
  string linea;
  nGramas* siguiente;
} vectorDenGramas [2331726] ;


//int main(int argc, char *argv[]) {
//	ifstream ngramas ("/home/fdc/workspace/OrgaDatos/trunk/BillionWords/nGramFiltered.txt");
//	unsigned long int lineasTotales = 0;
//	if (ngramas.is_open()){
//			string lineOfText;
//			std::cout << "empiezo" << std::endl;
//
//			while (getline(ngramas,lineOfText)){
//				lineasTotales++;
//			}
//	}
//
////	for (int i=0 ; i<2331725 ; i++){
////
////		std::cout << "linea: " << vectorDenGramas[i].linea << std::endl;
////		std::cout << "valor: " << vectorDenGramas[i].valor << std::endl;
////
////
////	}
//	std::cout << lineasTotales << std::endl;
//	return 0;
//}


int main(int argc, char *argv[]) {
	std::ofstream outputFile;
    outputFile.open("nGramSUPERFiltered.txt", std::ios_base::app);      //le indico el nombre del archivo de salida

	ifstream ngramas ("/home/fdc/workspace/OrgaDatos/trunk/BillionWords/ngram.txt");
	string lineaDelNgrama = "";
	vector<string> vectorOfTheLine;
	int i = 0;
	if (ngramas.is_open()){
			string lineOfText;
			while (getline(ngramas, lineaDelNgrama)) {
				vectorOfTheLine = StringUtils::split(lineaDelNgrama,'\t');
				string numero = vectorOfTheLine.back();
				//aca filtro todas las que son menores o iguales a cinco
				if (atoi(numero.c_str()) >= 65){
					outputFile << vectorOfTheLine[0];
					outputFile << '\t';	//le pone el tab
					outputFile << numero;	//le pone el numero
					outputFile << std::endl;
					i++;
				}
			}
	}

	outputFile.close();

	return 0;
}
