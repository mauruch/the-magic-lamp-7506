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

map<string, string> HashModel::unigrams;
map<long, map<string, string> > HashModel::bigrams;
map<long, map<string, string> > HashModel::trigrams;

void HashModel::initModel() {
	cout << "inicializando HashModel::initModel()" << endl;

	ifstream fileTest_v2("ngrams_cleaned_up5");

	if (fileTest_v2.is_open()) {
		cout << "Masticando el conocimiento..." << endl;
		string lineOfText;
		while (getline(fileTest_v2, lineOfText)) {
			StringUtils::replace(lineOfText, "\t", " ");
			vector<string> vector = StringUtils::split(lineOfText, ' ');
			string unigram = vector.at(0);
			if (vector.size() == 2) {
				getUnigrams()[unigram] = vector.at(1);
			} else if (vector.size() == 3) {
				long unigram_hashed = StringUtils::hashCode(unigram);
				getBigrams()[unigram_hashed][vector.at(1)] = vector.at(2);
			} else {
				long unigram_hashed = StringUtils::hashCode(unigram);
				std::string number;
				std::stringstream strstream;
				strstream << unigram_hashed;
				strstream >> number;
				long bigram_hashed = StringUtils::hashCode(
						number + vector.at(1));
				getTrigrams()[bigram_hashed][vector.at(2)] = vector.at(3);
			}
		}
		cout << "Conocimiento incorporado!!!" << endl;
	}

	else {
		cout << "Problemas al abrir los archivos" << endl;
	}

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

