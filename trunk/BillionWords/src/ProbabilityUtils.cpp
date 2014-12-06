#include "../headers/ProbabilityUtils.h"
#include "../headers/NgramDataRetriever.h"
#include "../headers/StringUtils.h"
#include "../headers/CONSTANTES.h"


float ProbabilityUtils::getUnigramProbability(string unigram) {
	string result;
	result = NgramDataRetriever::getExactNgram(unigram, UNIGRAM_EXPRESSION);
	float unigramWeight = NgramDataRetriever::getWeight(result); //check empty string

	float sumOfAllUnigrams = NgramDataRetriever::getUnigramTotalWeight();
	return 1; //Probabilidad del 1gram

}

float ProbabilityUtils::getBigramProbability(string bigram) {

	string result = NgramDataRetriever::getExactNgram(bigram, BIGRAM_EXPRESSION);
	float bigramWeight = NgramDataRetriever::getWeight(result); //check empty string
	vector<string> bigramSplit = StringUtils::split(bigram, ' ');
	string unigram = bigramSplit.at(0);

	result = NgramDataRetriever::getAllBigramsGivenAUnigram(unigram);
	float sumOfAllBigrams = NgramDataRetriever::getWeight(result);

	return 1; //Probabilidad del 2gram

}


float ProbabilityUtils::getTrigramProbability(string trigram) { //the cat is
	string result;
	result = NgramDataRetriever::getExactNgram(trigram, TRIGRAM_EXPRESSION);
	float trigramWeight = NgramDataRetriever::getWeight(result); //check empty string

	vector<string> trigramSplit = StringUtils::split(trigram, ' ');
	string bigram = trigramSplit.at(0).append(trigramSplit.at(1));

	result = NgramDataRetriever::getAllTrigramsGivenABigram(bigram);
	float sumOfAllTrigrams = NgramDataRetriever::getWeight(result);

	return 1; //Probabilidad del 3gram

}

float interpolate(double unigramProbability, double bigramProbability, double trigramProbability){
	float unigramWeigth = 0.33;
	float bigramWeigth = 0.33;
	float trigramWeigth = 0.33;
	return	unigramWeigth*unigramProbability + bigramWeigth*bigramProbability + trigramWeigth*unigramProbability;
}

string ProbabilityUtils::getNgramExp(vector<string> line, int wordPosition, int gramLevel){
	string gram = "";
	switch (gramLevel) {
	case 1:
		gram.append(line.at(wordPosition));
		break;
	case 2:
		gram.append(line.at(wordPosition -1)).append(" ");
		gram.append(line.at(wordPosition));
		break;
	case 3:
		gram.append(line.at(wordPosition -2)).append(" ");
		gram.append(line.at(wordPosition -1)).append(" ");
		gram.append(line.at(wordPosition));
		break;
	}
	return gram;
}


float ProbabilityUtils::getWordProbability(vector<string> line, int wordPosition) {

	float trigramProbability = (float)0;
	float bigramProbability = (float)0;
	float unigramProbability = (float)0;
	if (wordPosition > 1){
		string trigramExp = getNgramExp(line, wordPosition, TRIGRAM_EXPRESSION);
		trigramProbability = getTrigramProbability(trigramExp);
	}
	string bigramExp = getNgramExp(line, wordPosition, BIGRAM_EXPRESSION);
	bigramProbability = getBigramProbability(bigramExp);

	string unigramExp = getNgramExp(line, wordPosition, UNIGRAM_EXPRESSION);
	unigramProbability = getUnigramProbability(unigramExp);

	return interpolate(unigramProbability, bigramProbability, trigramProbability);
}

