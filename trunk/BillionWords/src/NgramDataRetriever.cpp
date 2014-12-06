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
	return "unString";
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
	//	TODO FIJARSE POR QUE ACA LE PONGO EL -1 FUNCIONA HASTA QUE TIRA UN ERROR, SERA ALGO DE OUT OF BOUNDS?
	for (int i = 0; i < lines.size()-1; i++) {
		long weigth = 0;
		string weightString = StringUtils::split(lines[i], '\t')[1];
		weigth = atol(weightString.c_str());
		sumOfWeights += weigth;
	}
	return sumOfWeights;
}

