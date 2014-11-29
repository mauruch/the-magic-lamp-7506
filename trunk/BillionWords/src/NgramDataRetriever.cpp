#include "../headers/NgramDataRetriever.h"
#include "../headers/NGram.h"
#include "../headers/StringUtils.h"

NgramDataRetriever::NgramDataRetriever() {
}

std::string exec(char* cmd) {
    FILE* pipe = popen(cmd, "r");
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
	char* command = 'grep ^[^[:space:]][  ]';
	return exec(command);
}

string NgramDataRetriever::getExactNgram(string ngram) {
	char* command = 'grep ^' + ngram + '    ';
	return exec(command);
}

string NgramDataRetriever::getAllTrigramsGivenABigram(string bigram) {
	char* command = 'grep ^' + bigram + ' ';
	return exec(command);

}

string NgramDataRetriever::getAllBigramsGivenAUnigram(string unigram) {
	char* command = 'grep ^' + unigram + '\s[^[:space:]]\+[     ]';
	return exec(command);

}

string NgramDataRetriever::getWeight(string ngram) {

	vector<string> stringsVector;
	StringUtils::removeSpaces(ngram);
	stringsVector = StringUtils::split(ngram, ' ');
	return stringsVector.at(stringsVector.size() -1);

}
