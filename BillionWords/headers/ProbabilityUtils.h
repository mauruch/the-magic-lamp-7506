#ifndef PROBABILITYUTILS_H_
#define PROBABILITYUTILS_H_
#include <iostream>
#include <string>
#include "StringUtils.h"
#include "CONSTANTES.h"
#include "../headers/NGram.h"

using namespace std;
class NGram;
class StringUtils;

class ProbabilityUtils {
private:
	map<string, string> unigrams;
	map< long, std::map<string, string> > bigrams;
	map< long, std::map<string, string> > trigrams;
	map< long, long> totalWeightGivenUni;
	map< long, long> totalWeightGivenBigram;
	NGram *nGram;
	StringUtils *stringUtils;

public:

	ProbabilityUtils(NGram *nGram, StringUtils *stringUtils);

	double getWordProbability(vector<string> *line, int wordPosition);

	double getWordProbability(string ngram, int gramLevel);

	double getTrigramProbability(vector<string> *trigram);

	double getBigramProbability(vector<string> *bigram, int gramLevel);

	double getUnigramProbability(string unigram);

	string getMostProbableWordInTheGivenContext(vector<string> *line, int wordPosition);

	string getFirstUnigram(ifstream& ngram_file, string& lineOfText);
	vector<string> getFirstBigram(ifstream& ngram_file, string& lineOfText);

};

#endif /* PROBABILITYUTILS_H_ */
