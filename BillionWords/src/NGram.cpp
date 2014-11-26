#include "../headers/NGram.h"
#include "../headers/StringUtils.h"
#include <limits>
NGram::NGram(string ngramAddress) {
	//a modo de inicializador
	this->ngramAddress = ngramAddress;
}

NGram::~NGram() {
	// TODO Auto-generated destructor stub
}

void NGram::fillTheMissingWord(string *lineOfText){
	string searchNgram;
	unsigned int minorWeight = std::numeric_limits<unsigned int>::max();
	unsigned int whereToAdd;	//aca vamos a saber donde vamos a tener que meter una palabra porque es la que falta
	vector<string> vectorOfTheLine = StringUtils::split(*lineOfText,' ');
	for (unsigned int counter = 1; counter < (vectorOfTheLine.size() - 1); counter++) {
		//agarro de a bigramas y me fijare el peso
		searchNgram = "";
		searchNgram.append(vectorOfTheLine[counter]);
		searchNgram.append(" ");
		searchNgram.append(vectorOfTheLine[counter+1]);

		getProbability(vectorOfTheLine, counter);

		//obtengo el peso
		if (this->getWeight(searchNgram) < minorWeight){
			whereToAdd = counter;
		}
	}
	//ahora que se donde debo insertar la palabra
	searchNgram = "";
	for (unsigned int counter = 0; counter < (vectorOfTheLine.size()); counter++) {
		if (counter == whereToAdd){
			searchNgram.append(" ");
			searchNgram.append("the");	//aca deberia ir la palabra que realmente falta, no "the"
			searchNgram.append(" ");
		}
		searchNgram.append(vectorOfTheLine[counter]);
		searchNgram.append(" ");
		searchNgram.append(vectorOfTheLine[counter+1]);
	}
	lineOfText = &searchNgram;
return;
}

int NGram::getWeight(string ngram) {

	vector<string> vectorDeStrings;

	StringUtils::removeSpaces(ngram);

	vectorDeStrings = StringUtils::split(ngram, ' ');

	return vectorDeStrings.at(vectorDeStrings.size() -1);

}


unsigned double getProbability(vector<string> line, int counter) {

	unsigned double 3GramProbability = (double)0;
	if (counter > 1){
		string gram = "";
		gram.append(line.at(counter -2)).append(" ");
		gram.append(line.at(counter -1)).append(" ");
		gram.append(line.at(counter));
		3GramProbability = get3GramProbability(gram);
	}

	//TODO refactor

	double 2GramProbability = get2GramProbability();
	double 1GramProbability = get1GramProbability();
}



unsigned double get3GramProbability(string 3gram) { //the cat is

	std::string result = system( "./grep exact regular expression" ) ;
	getWeight(result); //check empty string

	std::string result = system( "./grep hallar todos los bigramas ) ;

}


//std::string exec(char* cmd) {
//    FILE* pipe = popen(cmd, "r");
//    if (!pipe) return "ERROR";
//    char buffer[128];
//    std::string result = "";
//    while(!feof(pipe)) {
//    	if(fgets(buffer, 128, pipe) != NULL)
//    		result += buffer;
//    }
//    pclose(pipe);
//    return result;
//}

