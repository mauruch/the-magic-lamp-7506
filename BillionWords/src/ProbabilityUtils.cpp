#include "../headers/ProbabilityUtils.h"
#include "../headers/NgramDataRetriever.h"
#include "../headers/StringUtils.h"
#include "../headers/CONSTANTES.h"


double ProbabilityUtils::getUnigramProbability(string unigram) {
	string result;
	result = NgramDataRetriever::getExactNgram(unigram);
	double unigramWeight = NgramDataRetriever::getWeight(result); //check empty string

	result = NgramDataRetriever::getAllUnigrams();
	double sumOfAllUnigrams = NgramDataRetriever::getWeight(result);

	return unigramWeight/sumOfAllUnigrams; //Probabilidad del 1gram

}

double ProbabilityUtils::getBigramProbability(string bigram) {
	string result;
	result = NgramDataRetriever::getExactNgram(bigram);
	double bigramWeight = NgramDataRetriever::getWeight(result); //check empty string

	vector<string> bigramSplit = StringUtils::split(bigram, ' ');
	string unigram = bigramSplit.at(0);

	result = NgramDataRetriever::getAllBigramsGivenAUnigram(unigram);
	double sumOfAllBigrams = NgramDataRetriever::getWeight(result);

	return bigramWeight/sumOfAllBigrams; //Probabilidad del 2gram

}


double ProbabilityUtils::getTrigramProbability(string trigram) { //the cat is
	string result;
	result = NgramDataRetriever::getExactNgram(trigram);
	double trigramWeight = NgramDataRetriever::getWeight(result); //check empty string

	vector<string> trigramSplit = StringUtils::split(trigram, ' ');
	string bigram = trigramSplit.at(0).append(trigramSplit.at(1));

	result = NgramDataRetriever::getAllTrigramsGivenABigram(bigram);
	double sumOfAllTrigrams = NgramDataRetriever::getWeight(result);

	return trigramWeight/sumOfAllTrigrams; //Probabilidad del 3gram

}

double interpolate(double unigramProbability, double bigramProbability, double trigramProbability){
	double unigramWeigth = 0.33;
	double bigramWeigth = 0.33;
	double trigramWeigth = 0.33;
	return	unigramWeigth*unigramProbability + bigramWeigth*bigramProbability + unigramWeigth*unigramProbability;
}

string getNgramExp(vector<string> line, int wordPosition, int gramLevel){
	string gram = "";
	gram.append(line.at(wordPosition -2)).append(" ");
	gram.append(line.at(wordPosition -1)).append(" ");
	gram.append(line.at(wordPosition));
	return gram;
}


double ProbabilityUtils::getWordProbability(vector<string> line, int wordPosition) {

	double trigramProbability = (double)0;
	double bigramProbability = (double)0;
	double unigramProbability = (double)0;
	double wordProbability = (double)0;
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

