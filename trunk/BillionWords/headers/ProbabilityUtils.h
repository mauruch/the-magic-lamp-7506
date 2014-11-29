#ifndef PROBABILITYUTILS_H_
#define PROBABILITYUTILS_H_
#include <vector>
#include <iostream>
#include <string>
using namespace std;


class ProbabilityUtils {

public:

	ProbabilityUtils();

	static double getWordProbability(vector<string> line, int wordPosition);

	static double getTrigramProbability(string trigram);

	static double getBigramProbability(string bigram);

	static double getUnigramProbability(string unigram);



};

#endif /* PROBABILITYUTILS_H_ */
