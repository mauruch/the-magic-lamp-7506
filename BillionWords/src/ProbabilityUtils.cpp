#include "../headers/ProbabilityUtils.h"

float ProbabilityUtils::getUnigramProbability(string unigram, HashModel& model) {

	string weightAsString = model.getUnigrams()[unigram];
	float weight = atol(weightAsString.c_str());

	float sumOfAllUnigrams = UNIGRAMTOTALWEIGHT;
	return (weight / sumOfAllUnigrams); //Probabilidad del 1gram

}

float ProbabilityUtils::getBigramProbability(vector<string> bigram,  HashModel& model) {

	long uni_hashed = StringUtils::hashCode(bigram[0]);

	map<string, string> uni_map = model.getBigrams()[uni_hashed];
	typedef map<string, string>::iterator it_type;

	float sumOfAllBigrams = 0;
	for (it_type iterator = uni_map.begin(); iterator != uni_map.end();
			iterator++) {
		sumOfAllBigrams += atoi(iterator->second.c_str());
	}

	float weightBigram = atoi(
			model.getBigrams()[uni_hashed][bigram[1]].c_str());

	return (weightBigram / sumOfAllBigrams);

}

float ProbabilityUtils::getTrigramProbability(vector<string> trigram, HashModel& model) { //the cat is

	long uni_hashed = StringUtils::hashCode(trigram[0]);
	long bi_hashed = StringUtils::hashCode(
			StringUtils::ltos(uni_hashed) + trigram[1]);

	map<string, string> bi_map = model.getTrigrams()[bi_hashed];
	typedef map<string, string>::iterator it_type;

	float sumOfAllTrigrams = 0;
	for (it_type iterator = bi_map.begin(); iterator != bi_map.end();
			iterator++) {
		sumOfAllTrigrams += atoi(iterator->second.c_str());
	}

	float weightTrigram = atoi(
			model.getTrigrams()[bi_hashed][trigram[2]].c_str());

	return (weightTrigram / sumOfAllTrigrams);

}

float interpolate(double unigramProbability, double bigramProbability,
		double trigramProbability) {
	float unigramWeigth = 0.33;
	float bigramWeigth = 0.33;
	float trigramWeigth = 0.33;
	return unigramWeigth * unigramProbability + bigramWeigth * bigramProbability
			+ trigramWeigth * unigramProbability;
}

float ProbabilityUtils::getWordProbability(vector<string> line,
		int wordPosition, HashModel& model) {

	float trigramProbability = (float) 0;
	float bigramProbability = (float) 0;
	float unigramProbability = (float) 0;

	string ngramExpression;

	if (wordPosition > 1) {
		ngramExpression = NGram::getNgramExp(line, wordPosition,
				TRIGRAM_EXPRESSION);
	} else {
		ngramExpression = NGram::getNgramExp(line, wordPosition,
				BIGRAM_EXPRESSION);
	}

	vector<string> ngram_splitted = StringUtils::split(ngramExpression, ' ');

	if (wordPosition > 1)
		trigramProbability = getTrigramProbability(ngram_splitted, model);

	unigramProbability = getUnigramProbability(ngram_splitted[0], model);

	bigramProbability = getBigramProbability(ngram_splitted, model);

	return interpolate(unigramProbability, bigramProbability,
			trigramProbability);
}

