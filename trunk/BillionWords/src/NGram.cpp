#include "../headers/NGram.h"
#include "../headers/StringUtils.h"
#include "../headers/CONSTANTES.h"
#include "../headers/ProbabilityUtils.h"
#include <limits>
#include <cstdlib>

/*string NGram::findMissingWord(vector<string> vectorOfTheLine, int wordPosition) {
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
}*/

/*void NGram::fillTheMissingWord(string *lineOfText){
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
}*/

NGram::NGram(){
	this->probabilityUtils = new ProbabilityUtils(this);
}

unsigned int NGram::whereIsMissingTheWord(vector<string> vectorOfTheLine){
	string searchNgram;
	unsigned int whereToAdd = 1;
	float minorProbability = ((float)90);
	int numberOfWords = vectorOfTheLine.size();

	for (unsigned int counter = 1; counter < (numberOfWords -1); counter++) {
		float wordProbability = this->probabilityUtils->getWordProbability(vectorOfTheLine, counter);
		//obtengo el peso
		if (wordProbability < minorProbability) {
			minorProbability = wordProbability;
			whereToAdd = counter;
		}
	}
	return whereToAdd;
}

string NGram::getNgramExp(vector<string> line, int wordPosition,
		int gramLevel) {
	string gram = "";
	switch (gramLevel) {
	case 1:
		gram.append(line.at(wordPosition));
		break;
	case 2:
		gram.append(line.at(wordPosition - 1)).append(" ");
		gram.append(line.at(wordPosition));
		break;
	case 3:
		gram.append(line.at(wordPosition - 2)).append(" ");
		gram.append(line.at(wordPosition - 1)).append(" ");
		gram.append(line.at(wordPosition));
		break;
	}
	return gram;
}

string NGram::whichWordToAdd(vector<string> vectorOfTheLine,unsigned int whereToAdd){
	string wordToAdd;
	return wordToAdd;
}
