#ifndef PROBABILITYUTILS_H_
#define PROBABILITYUTILS_H_
#include <iostream>
#include <string>
#include "StringUtils.h"
#include "CONSTANTES.h"
#include "../headers/NGram.h"

using namespace std;
class NGram;


class ProbabilityUtils {
private:
	map<string, string> unigrams;
	map< long, std::map<string, string> > bigrams;
	map< long, std::map<string, string> > trigrams;
	map< long, long> totalWeightGivenUni;
	map< long, long> totalWeightGivenBigram;
	NGram *nGram;

public:

	ProbabilityUtils(NGram *nGram);

	double getWordProbability(vector<string> line, int wordPosition);

	double getTrigramProbability(vector<string> trigram);

	double getBigramProbability(vector<string> bigram, int gramLevel);

	double getUnigramProbability(string unigram);

	string getMostProbableWordInTheGivenContext(vector<string> line, int wordPosition);

	double getWordProbability(string ngram, int gramLevel);

};

#endif /* PROBABILITYUTILS_H_ */
