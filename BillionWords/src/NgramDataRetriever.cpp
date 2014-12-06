#include "../headers/NgramDataRetriever.h"
#include "../headers/NGram.h"
#include "../headers/StringUtils.h"
#include "../headers/CONSTANTES.h"

NgramDataRetriever::NgramDataRetriever() {
}

long NgramDataRetriever::getUnigramTotalWeight() {
	return 768648884;
}

string NgramDataRetriever::getExactNgram(string ngram, int ngramIdentifier) {
	//TODO
	string result;
	vector<string> vector = StringUtils::split(ngram, ' ');
	switch (ngramIdentifier) {
	case 1:
		result = HashModel::getUnigrams()[ngram];
		break;
	}
}

string NgramDataRetriever::getAllTrigramsGivenABigram(string bigram) {
	//todo
	return "the cat is	8989";
}

string NgramDataRetriever::getAllBigramsGivenAUnigram(string unigram) {
	//todo
	return "the cat	89";
}

long NgramDataRetriever::getWeight(string ngramResult) {
	long sumOfWeights = 0;
	vector<string> lines = StringUtils::split(ngramResult, '\n');
	for (int i = 0; i < lines.size(); i++) {
		long weigth = 0;
		string weightString = StringUtils::split(lines[i], '\t')[1];
		weigth = atoll(weightString.c_str());
		sumOfWeights += weigth;
	}
	return sumOfWeights;
}

