#include "../headers/ProbabilityUtils.h"
#include "../headers/NgramDataRetriever.h"
#include "../headers/StringUtils.h"
#include "../headers/CONSTANTES.h"

ProbabilityUtils::ProbabilityUtils(){
	this->objectNgramDataRetriever = new NgramDataRetriever();
	this->objectStringUtils = new StringUtils();
}


double ProbabilityUtils::getUnigramProbability(string unigram) {
	string result;
	int unigramWeight = this->objectNgramDataRetriever->getExactNgram(unigram); //check empty string

	double sumOfAllUnigrams = this->objectNgramDataRetriever->getUnigramTotalWeight();

	return unigramWeight/sumOfAllUnigrams; //Probabilidad del 1gram

}

double ProbabilityUtils::getBigramProbability(string bigram) {
	string result;
	int bigramWeight = this->objectNgramDataRetriever->getExactNgram(bigram); //check empty string

	vector<string> bigramSplit = this->objectStringUtils->split(bigram, ' ');
	string unigram = bigramSplit.at(0);

	result = this->objectNgramDataRetriever->getAllBigramsGivenAUnigram(unigram);
	double sumOfAllBigrams = this->objectNgramDataRetriever->getWeight(result);

	return bigramWeight/sumOfAllBigrams; //Probabilidad del 2gram

}


double ProbabilityUtils::getTrigramProbability(string trigram) { //the cat is
	string result;
	int trigramWeight = this->objectNgramDataRetriever->getExactNgram(trigram);

	vector<string> trigramSplit = this->objectStringUtils->split(trigram, ' ');
	string bigram = trigramSplit.at(0).append(trigramSplit.at(1));

	result = this->objectNgramDataRetriever->getAllTrigramsGivenABigram(bigram);
	double sumOfAllTrigrams = this->objectNgramDataRetriever->getWeight(result);

	return trigramWeight/sumOfAllTrigrams; //Probabilidad del 3gram

}

double interpolate(double unigramProbability, double bigramProbability, double trigramProbability){
	double unigramWeigth = 0.33;
	double bigramWeigth = 0.33;
	double trigramWeigth = 0.33;
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


double ProbabilityUtils::getWordProbability(vector<string> line, int wordPosition) {

	double trigramProbability = (double)0;
	double bigramProbability = (double)0;
	double unigramProbability = (double)0;
	if (wordPosition > 1){
		string trigramExp = getNgramExp(line, wordPosition, TRIGRAM_EXPRESSION);
		getTrigramProbability(trigramExp);
	}
	string bigramExp = getNgramExp(line, wordPosition, BIGRAM_EXPRESSION);
	bigramProbability = getBigramProbability(bigramExp);

	string unigramExp = getNgramExp(line, wordPosition, UNIGRAM_EXPRESSION);
	unigramProbability = getUnigramProbability(unigramExp);

	return interpolate(unigramProbability, bigramProbability, trigramProbability);
}

