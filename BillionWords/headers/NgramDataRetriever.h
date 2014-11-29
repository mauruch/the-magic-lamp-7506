#ifndef NGRAMDATARETRIEVER_H_
#define NGRAMDATARETRIEVER_H_

#include <vector>
#include <iostream>
#include <string>
using namespace std;

class NgramDataRetriever {

public:

	NgramDataRetriever();

	static string getExactNgram(string ngram, int ngramIdentifier);
	static long getUnigramTotalWeight();
	static string getAllTrigramsGivenABigram(string bigram);
	static string getAllBigramsGivenAUnigram(string unigram);
	static long getWeight(string ngramResult);
	//va a servir para cambiar el . que es un wildcard en regular expressions
	void convertNgramForGrepUsage(string *ngram);


};

#endif /* NGRAMDATARETRIEVER */
