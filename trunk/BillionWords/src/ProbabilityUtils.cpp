#include "../headers/ProbabilityUtils.h"

ProbabilityUtils::ProbabilityUtils( NGram *nGram){
	this->nGram = nGram;

	cout << "Comenzando a poner el archivo " << NGRAMS_CLEANED << endl;

	ifstream ngram_file("ngrams_cleaned_up65");

	if (ngram_file.is_open()) {
		cout << "Masticando el conocimiento..." << endl;
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
		cout << "Conocimiento incorporado!!!" << endl;
	}

	else {
		cout << "Problemas al abrir los archivos" << endl;
	}

}

float ProbabilityUtils::getUnigramProbability(string unigram) {
	string weightAsString = this->unigrams[unigram];
	int weight = atoi(weightAsString.c_str());

	float sumOfAllUnigrams = UNIGRAMTOTALWEIGHT;
	return (weight / sumOfAllUnigrams); //Probabilidad del 1gram

}

float ProbabilityUtils::getBigramProbability(vector<string> bigram) {

	long uni_hashed = StringUtils::hashCode(bigram[0]);

	map<string, string> uni_map = this->bigrams[uni_hashed];
	typedef map<string, string>::iterator it_type;

	float sumOfAllBigrams = 0;
	for (it_type iterator = uni_map.begin(); iterator != uni_map.end();
			iterator++) {
		sumOfAllBigrams += atoi(iterator->second.c_str());
	}

	float weightBigram = atoi(
			this->bigrams[uni_hashed][bigram[1]].c_str());

	return (weightBigram / sumOfAllBigrams);

}

float ProbabilityUtils::getTrigramProbability(vector<string> trigram) {

	long uni_hashed = StringUtils::hashCode(trigram[0]);
	long bi_hashed = StringUtils::hashCode(
			StringUtils::ltos(uni_hashed) + trigram[1]);

	map<string, string> bi_map = this->trigrams[bi_hashed];
	typedef map<string, string>::iterator it_type;
	float sumOfAllTrigrams = 0;
	for (it_type iterator = bi_map.begin(); iterator != bi_map.end();
			iterator++) {
		sumOfAllTrigrams += atoi(iterator->second.c_str());
	}

	float weightTrigram = atoi(
			this->trigrams[bi_hashed][trigram[2]].c_str());

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

