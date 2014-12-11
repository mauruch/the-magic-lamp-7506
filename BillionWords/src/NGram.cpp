#include "../headers/NGram.h"
#include "../headers/StringUtils.h"
#include "../headers/CONSTANTES.h"
#include "../headers/ProbabilityUtils.h"
#include <limits>
#include <cstdlib>

string NGram::findMissingWord(vector<string> *vectorOfTheLine, int wordPosition) {
	return this->probabilityUtils->getMostProbableWordInTheGivenContext(vectorOfTheLine, wordPosition);

}

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
	StringUtils *stringUtils = new StringUtils();
	this->probabilityUtils = new ProbabilityUtils(this, stringUtils);
}

unsigned int NGram::whereIsMissingTheWord(vector<string> *vectorOfTheLine){

	unsigned int whereToAdd = 1;
	double minorProbability = ((double)1);
	double secondLowestProbability = ((double)1);
	int numberOfWords = (*vectorOfTheLine).size();
	double wordProbability;

	for (unsigned int counter = 1; counter < (numberOfWords); counter++) {
		wordProbability = this->probabilityUtils->getWordProbability(vectorOfTheLine, counter);
		//obtengo el peso
		if (wordProbability < minorProbability) {
			secondLowestProbability = minorProbability;
			minorProbability = wordProbability;
			whereToAdd = counter;
		}else{
			if(wordProbability < secondLowestProbability){
				secondLowestProbability = wordProbability;
			}
		}
	}
	if(minorProbability!=0){
			if(secondLowestProbability/minorProbability < 1.5){
					whereToAdd = OUT_OF_LINE;
			}
	}else{

				whereToAdd = OUT_OF_LINE;
	}

	return whereToAdd;
}

string NGram::getNgramExp(vector<string> *line, int wordPosition, int gramLevel) {
	string gram = "";
	switch (gramLevel) {
	case 1:
		gram.append((*line).at(wordPosition));
		break;
	case 2:
		gram.append((*line).at(wordPosition - 1)).append(" ");
		gram.append((*line).at(wordPosition));
		break;
	case 3:
		gram.append((*line).at(wordPosition - 2)).append(" ");
		gram.append((*line).at(wordPosition - 1)).append(" ");
		gram.append((*line).at(wordPosition));
		break;
	}
	return gram;
}

string NGram::whichWordToAdd(vector<string> vectorOfTheLine,unsigned int whereToAdd){
	string wordToAdd;
	return wordToAdd;
}
