#include "../headers/NgramDataRetriever.h"
#include "../headers/NGram.h"
#include "../headers/StringUtils.h"

NgramDataRetriever::NgramDataRetriever() {
}

std::string exec(string cmd) {
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
    	if(fgets(buffer, 128, pipe) != NULL)
    		result += buffer;
    }
    pclose(pipe);
    return result;
}

string NgramDataRetriever::getAllUnigrams(){
	string result = exec("grep ^[^[:space:]][  ] ngram.merged");
	return result;
}

string NgramDataRetriever::getExactNgram(string ngram) {
	return exec("grep ^" + ngram + "     ngram.merged");
}

string NgramDataRetriever::getAllTrigramsGivenABigram(string bigram) {
	return exec("grep ^" + bigram + "  ngram.merged");
}

string NgramDataRetriever::getAllBigramsGivenAUnigram(string unigram) {
	return exec("grep ^" + unigram + "\s[^[:space:]]\+[     ] ngram.merged");
}

long NgramDataRetriever::getWeight(string ngramResult) {
	long sumOfWeights = 0;
	vector<string> lines = StringUtils::split(ngramResult, '\n');
	for(int i=0; i < lines.size(); i++){
		long weigth = 0;
		string weightString = StringUtils::split(lines[i], '\t')[1];
		weigth = atoll(weightString.c_str());
		sumOfWeights += weigth;
	}
	return sumOfWeights;
}
