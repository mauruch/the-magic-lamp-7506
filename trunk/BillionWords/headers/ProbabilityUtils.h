#ifndef PROBABILITYUTILS_H_
#define PROBABILITYUTILS_H_
#include <vector>
#include <iostream>
#include <string>
#include "HashModel.h"
#include "ProbabilityUtils.h"
#include "StringUtils.h"
#include "CONSTANTES.h"
#include "NGram.h""
using namespace std;


class ProbabilityUtils {

public:

	ProbabilityUtils();

	static float getWordProbability(vector<string> line, int wordPosition, HashModel& model);

	static float getTrigramProbability(vector<string> trigram, HashModel& model);

	static float getBigramProbability(vector<string> bigram, HashModel& model);

	static float getUnigramProbability(string unigram, HashModel& model);

};

#endif /* PROBABILITYUTILS_H_ */
