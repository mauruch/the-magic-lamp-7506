#include "../headers/ProbabilityUtils.h"

ProbabilityUtils::ProbabilityUtils(NGram *nGram, StringUtils *stringUtils) {
	this->nGram = nGram;
	this->stringUtils = stringUtils;

	cout << "Masticando el conocimiento..." << endl;

	ifstream ngram_file("ngrams_cleaned_up6");

	if (ngram_file.is_open()) {
		string lineOfText;
		int sumWeightGivenUni = 0;
		int sumWeightGivenBigram = 0;


		//get first unigram and back to top
		string aux_uni = getFirstUnigram(ngram_file, lineOfText);

		//get first bigram and back to top
		vector<string> aux_bigram = getFirstBigram(ngram_file, lineOfText);

		//defino everything aca
		vector<string> vector;
		string unigram;
		long unigram_hashed;
		string numberAsString;
		long bigram_hashed;

		while (getline(ngram_file, lineOfText)) {
			stringUtils->replace(lineOfText, "\t", " ");
			vector = stringUtils->split(lineOfText, ' ');
			unigram = vector.at(0);
			if (unigram != aux_uni) {
				totalWeightGivenUni[stringUtils->hashCode(aux_uni)] =
						sumWeightGivenUni;
				aux_uni = unigram;
				sumWeightGivenUni = 0;
			}
			//the 99
			if (vector.size() == 2) {
				unigrams[unigram] = vector.at(1);
				//the cat 99
			} else if (vector.size() == 3) {

				long unigram_hashed = stringUtils->hashCode(unigram);

				if (vector.at(1) != aux_bigram[1]) {
					long previous_unigram_hashed = stringUtils->hashCode(
							aux_bigram[0]);
					totalWeightGivenBigram[stringUtils->hashCode(
							stringUtils->ltos(previous_unigram_hashed)
									+ aux_bigram[1])] = sumWeightGivenBigram;
					aux_bigram = vector;
					sumWeightGivenBigram = 0;
				}

				bigrams[unigram_hashed][vector.at(1)] = vector.at(2);
				sumWeightGivenUni += atol(vector.at(2).c_str());
				//the cat is 99
			} else {
				unigram_hashed = stringUtils->hashCode(unigram);
				numberAsString = stringUtils->ltos(unigram_hashed);
				bigram_hashed = stringUtils->hashCode(
						numberAsString + vector.at(1));
				trigrams[bigram_hashed][vector.at(2)] = vector.at(3);
				sumWeightGivenBigram += atol(vector.at(3).c_str());
			}
			vector.clear();
		}
		aux_bigram.clear();

	}

	else {
		cout << "Problemas al abrir los archivos" << endl;
	}
	ngram_file.close();
	cout << "Conocimiento incorporado!!!" << endl;

}

string ProbabilityUtils::getFirstUnigram(ifstream& ngram_file, string& lineOfText) {
	streampos firstPos = ngram_file.tellg();
	getline(ngram_file, lineOfText);
	this->stringUtils->replace(lineOfText, "\t", " ");
	ngram_file.seekg(firstPos);
	return this->stringUtils->split(lineOfText, ' ').at(0);
}

vector<string> ProbabilityUtils::getFirstBigram(ifstream& ngram_file, string& lineOfText) {
	streampos firstPos = ngram_file.tellg();
	vector<string> aux_bigram;
	bool read = true;
	vector<string> vector;
	while (read && getline(ngram_file, lineOfText)) {
		this->stringUtils->replace(lineOfText, "\t", " ");
		vector = this->stringUtils->split(lineOfText, ' ');
		if (vector.size() == 3) {
			aux_bigram.clear();
			aux_bigram = vector;
			read = false;
		}
	}
	ngram_file.seekg(firstPos);
	return aux_bigram;
}

double ProbabilityUtils::getUnigramProbability(string unigram) {
	string weightAsString = this->unigrams[unigram];
	int weight = atoi(weightAsString.c_str());

	return (weight / UNIGRAMTOTALWEIGHT); //Probabilidad del 1gram

}

double ProbabilityUtils::getBigramProbability(vector<string> *vectorBigram, int gramLevel) {

	int bigramPos1 = 0;
	int bigramPos2 = 1;
	if (gramLevel > 2) {
		bigramPos1 = 1;
		bigramPos2 = 2;
	}

	long uni_hashed = this->stringUtils->hashCode((*vectorBigram)[bigramPos1]);

	float sumOfAllBigrams = this->totalWeightGivenUni[uni_hashed];
	string bigram = (*vectorBigram)[bigramPos2];
	float weightBigram = atoi(this->bigrams[uni_hashed][bigram].c_str());

	return ( weightBigram / sumOfAllBigrams );
}

double ProbabilityUtils::getTrigramProbability(vector<string> *trigram) {
	long uni_hashed = this->stringUtils->hashCode((*trigram)[0]);
	long bi_hashed = this->stringUtils->hashCode(
			this->stringUtils->ltos(uni_hashed) + (*trigram)[1]);
	float sumOfAllTrigrams = this->totalWeightGivenBigram[bi_hashed];
	float weightTrigram = atoi(this->trigrams[bi_hashed][(*trigram)[2]].c_str());
	return (weightTrigram / sumOfAllTrigrams);
}

double interpolate(double unigramProbability, double bigramProbability, double trigramProbability) {
	return (UNIGRAM_WEIGHT * unigramProbability + BIGRAM_WEIGHT * bigramProbability + TRIGRAM_WEIGHT * unigramProbability);
}

double ProbabilityUtils::getWordProbability(vector<string> *line, int wordPosition) {

	double trigramProbability = (double) 0;
	double bigramProbability = (double) 0;
	double unigramProbability = (double) 0;
	int gramLevel = BIGRAM_EXPRESSION;

	string ngramExpression = "";

	if (wordPosition > 1) {
		ngramExpression = this->nGram->getNgramExp(line, wordPosition,
		TRIGRAM_EXPRESSION);
		gramLevel = TRIGRAM_EXPRESSION;
	} else {
		ngramExpression = this->nGram->getNgramExp(line, wordPosition,
		BIGRAM_EXPRESSION);
	}

	vector<string> ngram_splitted = this->stringUtils->split(ngramExpression, ' ');

	if (wordPosition > 1)
		trigramProbability = getTrigramProbability(&ngram_splitted);

	unigramProbability = getUnigramProbability(ngram_splitted[ngram_splitted.size() - 1]);

	bigramProbability = getBigramProbability(&ngram_splitted, gramLevel);

	ngram_splitted.clear();

	return interpolate(unigramProbability, bigramProbability,trigramProbability);
}

double ProbabilityUtils::getWordProbability(string ngramExpression,	int gramLevel) {

    double trigramProbability = (double) 0;
    double bigramProbability = (double) 0;
    double unigramProbability = (double) 0;

	//TODO vector<string> ngram_splitted = {"a", "b", "c"};
	vector<string> ngram_splitted = this->stringUtils->split(ngramExpression, ' ');

    if (gramLevel == TRIGRAM_EXPRESSION)
            trigramProbability = getTrigramProbability(&ngram_splitted);

    unigramProbability = getUnigramProbability(
                    ngram_splitted[ngram_splitted.size() - 1]);

    bigramProbability = getBigramProbability(&ngram_splitted, gramLevel);
	ngram_splitted.clear();
    return interpolate(unigramProbability, bigramProbability,
                    trigramProbability);


}

string ProbabilityUtils::getMostProbableWordInTheGivenContext(vector<string> *line, int wordPosition) {
        long uni_hashed = 0;
        long bi_hashed = 0;

        double wordProba = (double) 0;
        string mostProbableWord;
        if (wordPosition >= 2) {
                string uni = (*line)[wordPosition - 2];
                string bi = (*line)[wordPosition - 1];
                uni_hashed = this->stringUtils->hashCode(uni);
                bi_hashed = this->stringUtils->hashCode(this->stringUtils->ltos(uni_hashed) + bi);

                typedef map<string, string>::iterator it_type;

                //defino variables afuera de los ciclos
                string currentWord;
                string ngramExpression = "";
                double currentProba;

                for (it_type iterator = (this->trigrams[bi_hashed]).begin(); iterator != (this->trigrams[bi_hashed]).end(); iterator++) {
                        currentWord = iterator->first;
                        ngramExpression = "";
                        ngramExpression.append(uni).append(WHITE_SPACE_STRING).append(bi).append(WHITE_SPACE_STRING)
                                        .append(currentWord);
                        currentProba = getWordProbability(ngramExpression,
                                        TRIGRAM_EXPRESSION);
                        if (currentProba > wordProba && (currentWord != "\""  && currentWord != ";" && currentWord != "." && currentWord != "," && currentWord != "!"  && currentWord != "?" && currentWord != "'m" && currentWord != "--"
                        		&& currentWord != "'" && currentWord != "N.J."&& currentWord != ":"&& currentWord != ")" && currentWord != "(" && currentWord != "/" && currentWord != "$" )) {
                                wordProba = currentProba;
                                mostProbableWord = currentWord;
                        }

                }

//                uni_hashed = this->stringUtils->hashCode(bi);
//                typedef map<string, string>::iterator it_type;
//
//                 for (it_type iterator = (this->bigrams[uni_hashed]).begin(); iterator != (this->bigrams[uni_hashed]).end();
//                                iterator++) {
//                        currentWord = iterator->first;
//                        ngramExpression = "";
//                        ngramExpression.append(uni).append(WHITE_SPACE_STRING).append(currentWord);
//                        currentProba = getWordProbability(ngramExpression, BIGRAM_EXPRESSION);
//                        if (currentProba > wordProba) {
//                                wordProba = currentProba;
//                                mostProbableWord = currentWord;
//                        }
//                }

//                cout << "mostProbable: " << mostProbableWord << " con peso: " << wordProba << endl;

		if (wordProba<0.3){
			return "";
		}
        } else { return "";

                string uni = (*line)[wordPosition - 1];
                uni_hashed = this->stringUtils->hashCode(uni);

                typedef map<string, string>::iterator it_type;

                //defino variables afuera de los ciclos
                string currentWord;
                string ngramExpression = "";
                double currentProba;

                for (it_type iterator = (this->bigrams[uni_hashed]).begin(); iterator != (this->bigrams[uni_hashed]).end();
                                iterator++) {
                        currentWord = iterator->first;
                         ngramExpression = "";
                        ngramExpression.append(uni).append(WHITE_SPACE_STRING).append(currentWord);
                        currentProba = getWordProbability(ngramExpression,BIGRAM_EXPRESSION);


                        if (currentProba > wordProba && (currentWord != "\"" && currentWord != "." && currentWord != "," && currentWord != "!"  && currentWord != "?" && currentWord != "'m" && currentWord != "--"
                        		&& currentWord != "'" && currentWord != ")" && currentWord != ";" && currentWord != ":"&& currentWord != "(" && currentWord != "/" && currentWord != "$" )) {
                                wordProba = currentProba;
                                mostProbableWord = currentWord;
                        }
                        //destruyo al terminar
                        ngramExpression.clear();
                        currentWord.clear();
                }
//                cout << "mostProbableString: " << mostProbableWord << " con peso: " << wordProba << endl;

        }


        return mostProbableWord;

}
