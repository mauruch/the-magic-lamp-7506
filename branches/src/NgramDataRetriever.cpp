#include "../headers/NgramDataRetriever.h"

NgramDataRetriever::NgramDataRetriever() {
	this->objectStringUtils = new StringUtils();

	string NgramLine = "";
	vector<string> vectorOfTheLine;
	ifstream ngrams ("/home/fdc/workspace/OrgaDatos/trunk/BillionWords/nGramSUPERFiltered.txt");

	while (getline(ngrams, NgramLine)) {
		vectorOfTheLine = this->objectStringUtils->split(NgramLine,'\t');
		string key = vectorOfTheLine[0];
		string value = vectorOfTheLine.back();
		int numValue = atoi(value.c_str());
		this->keyValueNGrams[key] = numValue;	//asi es recomendado por stack overflow
	}


}

std::string exec(string cmd) {
	FILE* pipe = popen(cmd.c_str(), "r");
	if (!pipe)
		return "ERROR";
	char buffer[128];
	std::string result = "";
	while (!feof(pipe)) {
		if (fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	pclose(pipe);
	return result;
}

long NgramDataRetriever::getUnigramTotalWeight() {
	//magic number
	return 768648884;
}

int NgramDataRetriever::getExactNgram(string ngram) {
	auto search = this->keyValueNGrams.find(ngram);

	if(search != this->keyValueNGrams.end()) {
		std::cout << "Encontre\n";
		return this->keyValueNGrams.at(ngram);
	}
	    else {
	    	std::cout << "No encontre\n";
	        return 0;
	    }

}

string NgramDataRetriever::getAllTrigramsGivenABigram(string bigram) {
	return exec("sgrep '" + bigram + " ' /home/fdc/workspace/OrgaDatos/trunk/BillionWords/nGramSUPERFiltered.txt");
}

string NgramDataRetriever::getAllBigramsGivenAUnigram(string unigram) {
	return exec("sgrep '" + unigram + " ' /home/fdc/workspace/OrgaDatos/trunk/BillionWords/nGramSUPERFiltered.txt");
}

long NgramDataRetriever::getWeight(string ngramResult) {
	long sumOfWeights = 0;
	vector<string> lines = this->objectStringUtils->split(ngramResult, '\n');
	for (unsigned int i = 0; i < lines.size(); i++) {
		long weigth = 0;
		string weightString = this->objectStringUtils->split(lines[i], '\t')[1];
		weigth = atoll(weightString.c_str());
		sumOfWeights += weigth;
	}
	return sumOfWeights;
}

/*void NGram::convertNgramForGrepUsage(string *ngram) {
	for (size_t pos = 0;; pos += LARGO_BARRA_PUNTO)	//el dos es porque \. tiene 2 caracteres
			{
		pos = (*ngram).find('.', pos);
		if (pos == string::npos)
			break;
		(*ngram).erase(pos, LARGO_PUNTO);	//el 1 es porque . tiene 1 caracter
		(*ngram).insert(pos, "/.");
	}
}*/
