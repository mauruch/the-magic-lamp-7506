#include "../headers/NGram.h"
#include "../headers/StringUtils.h"
#include "../headers/CONSTANTES.h"
#include <limits>
#include <cstdlib>
NGram::NGram(string ngramAddress) {
	//a modo de inicializador
	this->ngramAddress = ngramAddress;
}

NGram::~NGram() {
	// TODO Auto-generated destructor stub
}

string NGram::findMissingWord(string context){
	return ProbabilityUtils::getWordFromContext(context);
}

void NGram::fillTheMissingWord(string *lineOfText){
	string finalNGram = "";
	string wordToAdd = "";
	vector<string> vectorOfTheLine = StringUtils::split(*lineOfText,' ');
	unsigned int whereToAdd = this->whereIsMissingTheWord(vectorOfTheLine);	//aca vamos a saber donde vamos a tener que meter una palabra porque es la que falta
	wordToAdd = this->whichWordToAdd(vectorOfTheLine,whereToAdd);

	//ahora que se donde debo insertar la palabra
	for (unsigned int counter = 0; counter < (vectorOfTheLine.size()); counter++) {
		if (counter == whereToAdd){
			finalNGram.append(" ");
			finalNGram.append(wordToAdd);
			finalNGram.append(" ");
		}
		finalNGram.append(vectorOfTheLine[counter]);
		finalNGram.append(" ");
		finalNGram.append(vectorOfTheLine[counter+1]);
	}
	lineOfText = &finalNGram;
return;
}

unsigned int NGram::whereIsMissingTheWord(vector<string> vectorOfTheLine){
	string searchNgram;
	unsigned int whereToAdd;
	long minorProbability = std::numeric_limits<long>::max();	//le asigno el valor maximo de un int

	for (unsigned int counter = 1; counter < (vectorOfTheLine.size() -1); counter++) {
		//obtengo el peso
		if (ProbabilityUtils::getWordProbability(vectorOfTheLine, counter) < minorProbability){
			whereToAdd = counter;
		}
	}

	return whereToAdd;
}

string NGram::whichWordToAdd(vector<string> vectorOfTheLine,unsigned int whereToAdd){
	string wordToAdd;
	return wordToAdd;
}
