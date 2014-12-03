#ifndef PROBABILITYUTILS_H_
#define PROBABILITYUTILS_H_
#include <vector>
#include <iostream>
#include <string>

#include "NgramDataRetriever.h"
using namespace std;
class NgramDataRetriever;

class ProbabilityUtils {

public:
	StringUtils *objectStringUtils;
	NgramDataRetriever *objectNgramDataRetriever;

	/*
	 * Constructor, tiene adentro el new de NgramDataRetriever que va a usar
	 */
	ProbabilityUtils();

	double getWordProbability(vector<string> line, int wordPosition);

	double getTrigramProbability(string trigram);

	double getBigramProbability(string bigram);

	double getUnigramProbability(string unigram);

	string getNgramExp(vector<string> line, int wordPosition, int gramLevel);



};

#endif /* PROBABILITYUTILS_H_ */
