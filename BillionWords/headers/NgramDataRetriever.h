#ifndef NGRAMDATARETRIEVER_H_
#define NGRAMDATARETRIEVER_H_

#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

class NgramDataRetriever {

public:

	NgramDataRetriever();
	static string getExactNgram(string ngram, int ngramIdentifier);
	static long getUnigramTotalWeight();
	static string getAllTrigramsGivenABigram(string bigram);
	static string getAllBigramsGivenAUnigram(string unigram);
	static long getWeight(string ngramResult);


};

#endif /* NGRAMDATARETRIEVER */
