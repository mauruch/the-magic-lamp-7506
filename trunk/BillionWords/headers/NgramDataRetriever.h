#ifndef NGRAMDATARETRIEVER_H_
#define NGRAMDATARETRIEVER_H_

#include <vector>
#include <iostream>
#include <string>
using namespace std;

class NgramDataRetriever {

public:

	NgramDataRetriever();

	static string getExactNgram(string ngram);
	static string getAllUnigrams();
	static string getAllTrigramsGivenABigram(string bigram);
	static string getAllBigramsGivenAUnigram(string unigram);
	static long getWeight(string ngramResult);


};

#endif /* NGRAMDATARETRIEVER */
