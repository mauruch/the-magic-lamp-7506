#include "../headers/NGram.h"
#include "../headers/StringUtils.h"
#include "../headers/CONSTANTES.h"
#include "../headers/ProbabilityUtils.h"
#include <limits>
#include <cstdlib>
NGram::NGram(string ngramAddress) {
	//a modo de inicializador
	this->ngramAddress = ngramAddress;
}

NGram::~NGram() {
	// TODO Auto-generated destructor stub
}

string NGram::findMissingWord(vector<string> vectorOfTheLine, int wordPosition) {
	string ngramExp = "";
	if (wordPosition < 2){
        //ARMAR BIGRAMA Y BUSCAR TODOS LOS TRI DADO EL BI
		//LUEGO HACERLE BACKOFF A CADA UNO DE LOS TRI
		//(QUEDARME CON LA PROB MAS ALTA DE LA ULTIMA PALABRA DEL TRI)
		ngramExp = ProbabilityUtils::getNgramExp(vectorOfTheLine, wordPosition - 1, UNIGRAM_EXPRESSION);
		string result =  NgramDataRetriever::getAllBigramsGivenAUnigram(ngramExp);
	} else {
		ngramExp = ProbabilityUtils::getNgramExp(vectorOfTheLine, wordPosition - 1, BIGRAM_EXPRESSION);
		NgramDataRetriever::getAllTrigramsGivenABigram(ngramExp);
	}







}

void NGram::fillTheMissingWord(string *lineOfText){
	string finalNGram = "";
	string wordToAdd = "";
	vector<string> vectorOfTheLine = StringUtils::split(*lineOfText,' ');
	unsigned int whereToAdd = this->whereIsMissingTheWord(vectorOfTheLine);	//aca vamos a saber donde vamos a tener que meter una palabra porque es la que falta
	wordToAdd = this->whichWordToAdd(vectorOfTheLine,whereToAdd);

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
