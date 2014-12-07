#ifndef PROBABILITYUTILS_H_
#define PROBABILITYUTILS_H_
#include <vector>
#include <iostream>
#include <string>
#include "ProbabilityUtils.h"
#include "StringUtils.h"
#include "CONSTANTES.h"

#include "../headers/NGram.h"
#include <vector>
#include <map>
#include "../headers/CONSTANTES.h"


using namespace std;
class NGram;


class ProbabilityUtils {
private:
	map<string, string> unigrams;
	map< long, std::map<string, string> > bigrams;
	map< long, std::map<string, string> > trigrams;
	NGram *nGram;

public:

	ProbabilityUtils(NGram *nGram);

	float getWordProbability(vector<string> line, int wordPosition);

	float getTrigramProbability(vector<string> trigram);

	float getBigramProbability(vector<string> bigram);

	float getUnigramProbability(string unigram);

};

#endif /* PROBABILITYUTILS_H_ */
