/*
 * NGram.cpp
 *
 *  Created on: 25/11/2014
 *      Author: mauro
 */

#include "../headers/NGram.h"
#include "../headers/StringUtils.h"

NGram::NGram(string ngramAddress) {
	this->ngramAddress;
}

NGram::~NGram() {
	// TODO Auto-generated destructor stub
}

int NGram::getWeight(string ngram) {
	vector<string> vectorDeStrings;
	string aux = "";
	string regularExpr = "grep '";
	regularExpr.append(ngram);
	regularExpr.append(" [^a-z^A-Z]*$' ");
	regularExpr.append(this->ngramAddress);
	FILE *filePointer = popen(regularExpr.c_str(), "r");

	char palabra[1024];
	fgets(palabra, 1024, filePointer);	//tengo el contenido de lo buscado
	fclose(filePointer);

	aux = palabra;	//lo paso a un string para que sea usado con el split
	vectorDeStrings = StringUtils::split(aux, ' ');//realizo el split
	int numero = 0;

	if (!(vectorDeStrings.empty())) {
		std::stringstream out;
		out << vectorDeStrings.back();
		out >> numero;
		//		std::cout << numero << std::endl;
	}
	return numero;
}

