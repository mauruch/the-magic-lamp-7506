#include "../headers/ProbabilityUtils.h"

string getFirstUnigram(ifstream& ngram_file, string& lineOfText);

vector<string> getFirstBigram(ifstream& ngram_file, string& lineOfText);

ProbabilityUtils::ProbabilityUtils(NGram *nGram) {
	this->nGram = nGram;

	cout << "Masticando el conocimiento..." << endl;

	ifstream ngram_file("ngrams_cleaned_up5");

	if (ngram_file.is_open()) {
		string lineOfText;
		int sumWeightGivenUni = 0;
		int sumWeightGivenBigram = 0;

		//get first unigram and back to top
		string aux_uni = getFirstUnigram(ngram_file, lineOfText);

		//get first bigram and back to top
		vector<string> aux_bigram = getFirstBigram(ngram_file, lineOfText);

		while (getline(ngram_file, lineOfText)) {
			StringUtils::replace(lineOfText, "\t", " ");
			vector<string> vector = StringUtils::split(lineOfText, ' ');
			string unigram = vector.at(0);
			if (unigram != aux_uni) {
				totalWeightGivenUni[StringUtils::hashCode(aux_uni)] =
						sumWeightGivenUni;
				aux_uni = unigram;
				sumWeightGivenUni = 0;
			}
			//the 99
			if (vector.size() == 2) {
				unigrams[unigram] = vector.at(1);
				//the cat 99
			} else if (vector.size() == 3) {

				long unigram_hashed = StringUtils::hashCode(unigram);

				if (vector.at(1) != aux_bigram[1]) {
					long previous_unigram_hashed = StringUtils::hashCode(
							aux_bigram[0]);
					totalWeightGivenBigram[StringUtils::hashCode(
							StringUtils::ltos(previous_unigram_hashed)
									+ aux_bigram[1])] = sumWeightGivenBigram;
					aux_bigram = vector;
					sumWeightGivenBigram = 0;
				}

				bigrams[unigram_hashed][vector.at(1)] = vector.at(2);
				sumWeightGivenUni += atol(vector.at(2).c_str());
				//the cat is 99
			} else {
				long unigram_hashed = StringUtils::hashCode(unigram);
				string numberAsString = StringUtils::ltos(unigram_hashed);
				long bigram_hashed = StringUtils::hashCode(
						numberAsString + vector.at(1));
				trigrams[bigram_hashed][vector.at(2)] = vector.at(3);
				sumWeightGivenBigram += atol(vector.at(3).c_str());
			}
		}

	}

	else {
		cout << "Problemas al abrir los archivos" << endl;
	}

	cout << "Conocimiento incorporado!!!" << endl;

}

string getFirstUnigram(ifstream& ngram_file, string& lineOfText) {
	streampos firstPos = ngram_file.tellg();
	getline(ngram_file, lineOfText);
	StringUtils::replace(lineOfText, "\t", " ");
	string aux_uni = StringUtils::split(lineOfText, ' ').at(0);
	ngram_file.seekg(firstPos);
	return aux_uni;
}

vector<string> getFirstBigram(ifstream& ngram_file, string& lineOfText) {
	streampos firstPos = ngram_file.tellg();
	vector<string> aux_bigram;
	bool read = true;
	while (read && getline(ngram_file, lineOfText)) {
		StringUtils::replace(lineOfText, "\t", " ");
		vector<string> vector = StringUtils::split(lineOfText, ' ');
		if (vector.size() == 3) {
			aux_bigram = vector;
			read = false;
		}
	}
	ngram_file.seekg(firstPos);
	return aux_bigram;
}

float ProbabilityUtils::getUnigramProbability(string unigram) {
	string weightAsString = this->unigrams[unigram];
	int weight = atoi(weightAsString.c_str());

	float sumOfAllUnigrams = UNIGRAMTOTALWEIGHT;
	return (weight / sumOfAllUnigrams); //Probabilidad del 1gram

}

float ProbabilityUtils::getBigramProbability(vector<string> bigram) {

	long uni_hashed = StringUtils::hashCode(bigram[0]);

	float sumOfAllBigrams = this->totalWeightGivenUni[uni_hashed];

	float weightBigram = atoi(this->bigrams[uni_hashed][bigram[1]].c_str());

	return (weightBigram / sumOfAllBigrams);

}

float ProbabilityUtils::getTrigramProbability(vector<string> trigram) {

	long uni_hashed = StringUtils::hashCode(trigram[0]);
	long bi_hashed = StringUtils::hashCode(
			StringUtils::ltos(uni_hashed) + trigram[1]);

	float sumOfAllTrigrams = this->totalWeightGivenBigram[bi_hashed];

	float weightTrigram = atoi(this->trigrams[bi_hashed][trigram[2]].c_str());

	return (weightTrigram / sumOfAllTrigrams);

}

float interpolate(double unigramProbability, double bigramProbability,
		double trigramProbability) {
	float unigramWeigth = 0.33;
	float bigramWeigth = 0.33;
	float trigramWeigth = 0.33;
	return unigramWeigth * unigramProbability + bigramWeigth * bigramProbability
			+ trigramWeigth * unigramProbability;
}

float ProbabilityUtils::getWordProbability(vector<string> line,
		int wordPosition) {

	float trigramProbability = (float) 0;
	float bigramProbability = (float) 0;
	float unigramProbability = (float) 0;

	string ngramExpression;

	if (wordPosition > 1) {
		ngramExpression = this->nGram->getNgramExp(line, wordPosition,
		TRIGRAM_EXPRESSION);
	} else {
		ngramExpression = this->nGram->getNgramExp(line, wordPosition,
		BIGRAM_EXPRESSION);
	}

	vector<string> ngram_splitted = StringUtils::split(ngramExpression, ' ');

	if (wordPosition > 1)
		trigramProbability = getTrigramProbability(ngram_splitted);

	unigramProbability = getUnigramProbability(ngram_splitted[0]);

	bigramProbability = getBigramProbability(ngram_splitted);

	return interpolate(unigramProbability, bigramProbability,
			trigramProbability);
}

string ProbabilityUtils::getMostProbableWordInTheGivenContext(
		vector<string> line, int wordPosition) {

	string mostProbableString = "ERROR NO DEBERIA LANZAR ESTO";
	long weightOfMostProbableString = 0;
	long uni_hashed = 0;
	long bi_hashed = 0;

	if (wordPosition >= 2) {

		uni_hashed = StringUtils::hashCode(line[wordPosition - 2]);
		bi_hashed = StringUtils::hashCode(
				StringUtils::ltos(uni_hashed) + line[wordPosition - 1]);

		map<string, string> bi_map = this->trigrams[bi_hashed];
		typedef map<string, string>::iterator it_type;

		for (it_type iterator = bi_map.begin(); iterator != bi_map.end();
				iterator++) {

			if (weightOfMostProbableString < atoi(iterator->second.c_str())) {
				weightOfMostProbableString = atoi(iterator->second.c_str());
				mostProbableString = iterator->first.c_str();
			}
		}
		cout << "mostProbableString: " << mostProbableString << " con peso "
				<< weightOfMostProbableString << endl;

	} else {
		uni_hashed = StringUtils::hashCode(line[wordPosition - 1]);

		map<string, string> uni_map = this->bigrams[uni_hashed];
		typedef map<string, string>::iterator it_type;

		for (it_type iterator = uni_map.begin(); iterator != uni_map.end();
				iterator++) {
			if (weightOfMostProbableString < atoi(iterator->second.c_str())) {
				weightOfMostProbableString = atoi(iterator->second.c_str());
				mostProbableString = iterator->first.c_str();
			}
		}
		cout << "mostProbableString: " << mostProbableString << " con peso "
				<< weightOfMostProbableString << endl;

	}

	return mostProbableString;
}
