#ifndef PROBABILITYUTILS_H_
#define PROBABILITYUTILS_H_
#include <vector>
#include <iostream>
#include <string>
using namespace std;


class ProbabilityUtils {

public:

	ProbabilityUtils();

	static float getWordProbability(vector<string> line, int wordPosition);

	static float getTrigramProbability(string trigram);

	static float getBigramProbability(string bigram);

	static float getUnigramProbability(string unigram);

	static string getNgramExp(vector<string> line, int wordPosition, int gramLevel);



};

#endif /* PROBABILITYUTILS_H_ */
