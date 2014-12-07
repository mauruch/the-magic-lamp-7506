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

	float getWordProbability(vector<string> line, int wordPosition);

	float getTrigramProbability(vector<string> trigram);

	float getBigramProbability(vector<string> bigram);

	float getUnigramProbability(string unigram);

	string getMostProbableWordInTheGivenContext(vector<string> line, int wordPosition);

};

#endif /* PROBABILITYUTILS_H_ */
