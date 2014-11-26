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
	for (unsigned int counter = 0; counter < (vectorOfTheLine.size() - 1); counter++) {
		//agarro de a bigramas y me fijare el peso
		searchNgram = "";
		searchNgram.append(vectorOfTheLine[counter]);
		searchNgram.append(" ");
		searchNgram.append(vectorOfTheLine[counter+1]);

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

unsigned int NGram::getWeight(string ngram) {
	vector<string> vectorDeStrings;
	string aux = "";
	string regularExpr = "grep '";
	regularExpr.append(ngram);
	regularExpr.append(" [^a-z^A-Z]*$' ");
	regularExpr.append(this->ngramAddress);
	FILE *filePointer = popen(regularExpr.c_str(), "r");

	char buffering[1024];
	fgets(buffering, 1024, filePointer);	//tengo el contenido de lo buscado
	fclose(filePointer);

	aux = buffering;	//lo paso a un string para que sea usado con el split
	vectorDeStrings = StringUtils::split(aux, ' ');//realizo el split
	unsigned int weight = 0;

	if (!(vectorDeStrings.empty())) {
		std::stringstream out;
		out << vectorDeStrings.back();
		out >> weight;
	}
	//std::cout << weight << std::endl;
	return weight;
}

