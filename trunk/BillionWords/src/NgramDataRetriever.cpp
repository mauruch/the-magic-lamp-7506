#include "../headers/NgramDataRetriever.h"
#include "../headers/NGram.h"
#include "../headers/StringUtils.h"

NgramDataRetriever::NgramDataRetriever() {
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
	return 768648884;
}

string NgramDataRetriever::getExactNgram(string ngram, int ngramIdentifier) {
	string command = "grep '^";
	command.append(ngram);
	command.append("	' "); //<tab>'
	string unigramFile;
	switch (ngramIdentifier) {
	case 1:
		command.append("ngram_uni.merged");
		break;
	case 2:
		command.append("ngram_bi.merged");
		break;
	case 3:
		command.append("ngram_tri.merged");
		break;
	}
	return exec(command);
}

string NgramDataRetriever::getAllTrigramsGivenABigram(string bigram) {
	return exec("grep '^" + bigram + "'  ngram_tri.merged");
}

string NgramDataRetriever::getAllBigramsGivenAUnigram(string unigram) {
	return exec("grep '^" + unigram + "\s'" + "' ngram_bi.merged");
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

void NGram::convertNgramForGrepUsage(string *ngram){
	   for( size_t pos = 0; ; pos += LARGO_BARRA_PUNTO)	//el dos es porque \. tiene 2 caracteres
	 	{
	         pos = (*ngram).find( '.', pos );
	         if( pos == string::npos ) break;
	         (*ngram).erase( pos, LARGO_PUNTO);	//el 1 es porque . tiene 1 caracter
	         (*ngram).insert( pos, "/.");
	     }
}
