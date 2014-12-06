/*
 * HashModel.cpp
 *
 *  Created on: 5/12/2014
 *      Author: mauro
 */

#include "../headers/HashModel.h"
#include "../headers/StringUtils.h"

HashModel::HashModel() {
	// TODO Auto-generated constructor stub

}

HashModel::~HashModel() {
	// TODO Auto-generated destructor stub
}


void HashModel::initModel() {

	cout << "Masticando el conocimiento..." << endl;

	ifstream ngram_file("ngram_test_aa");

	if (ngram_file.is_open()) {
		string lineOfText;
		while (getline(ngram_file, lineOfText)) {
			StringUtils::replace(lineOfText, "\t", " ");
			vector<string> vector = StringUtils::split(lineOfText, ' ');
			string unigram = vector.at(0);
			if (vector.size() == 2) {
				unigrams[unigram] = vector.at(1);
			} else if (vector.size() == 3) {
				long unigram_hashed = StringUtils::hashCode(unigram);
				bigrams[unigram_hashed][vector.at(1)] = vector.at(2);
			} else {
				long unigram_hashed = StringUtils::hashCode(unigram);
				string numberAsString = StringUtils::ltos(unigram_hashed);
				long bigram_hashed = StringUtils::hashCode(
						numberAsString + vector.at(1));
				trigrams[bigram_hashed][vector.at(2)] = vector.at(3);
			}
		}

	}

	else {
		cout << "Problemas al abrir los archivos" << endl;
	}

	cout << "Conocimiento incorporado!!!" << endl;
}

map<string, string> HashModel::getUnigrams() {
	return unigrams;
}
map<long, std::map<string, string> > HashModel::getBigrams() {
	return bigrams;
}
map<long, std::map<string, string> > HashModel::getTrigrams() {
	return trigrams;
}

