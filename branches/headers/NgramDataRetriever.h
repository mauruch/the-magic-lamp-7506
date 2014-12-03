#ifndef NGRAMDATARETRIEVER_H_
#define NGRAMDATARETRIEVER_H_

#include <vector>
#include <iostream>
#include <string>
#include <map>
#include "NGram.h"
#include "StringUtils.h"
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class NgramDataRetriever {
private:
	std::map<string,int> keyValueNGrams;

public:

	StringUtils *objectStringUtils;
	/*
	 * Constructor, tiene adentro el new de StringUtils que va a usar
	 */
	NgramDataRetriever();

	int getExactNgram(string ngram);
	long getUnigramTotalWeight();
	string getAllTrigramsGivenABigram(string bigram);
	string getAllBigramsGivenAUnigram(string unigram);
	long getWeight(string ngramResult);
	//va a servir para cambiar el . que es un wildcard en regular expressions
	//void convertNgramForGrepUsage(string *ngram);


};

#endif /* NGRAMDATARETRIEVER */
