#include "../headers/NGram.h"
#include "../headers/StringUtils.h"
#include "../headers/CONSTANTES.h"
#include <limits>
#include <cstdlib>
NGram::NGram(string ngramAddress) {
	//a modo de inicializador
	this->ngramAddress = ngramAddress;
}

NGram::~NGram() {
	// TODO Auto-generated destructor stub
}

void NGram::fillTheMissingWord(string *lineOfText){
	string finalNGram = "";
	string wordToAdd = "";
	vector<string> vectorOfTheLine = StringUtils::split(*lineOfText,' ');
	unsigned int whereToAdd = this->whereIsMissingTheWord(vectorOfTheLine);	//aca vamos a saber donde vamos a tener que meter una palabra porque es la que falta
	wordToAdd = this->whichWordToAdd(vectorOfTheLine,whereToAdd);

	//ahora que se donde debo insertar la palabra
	for (unsigned int counter = 0; counter < (vectorOfTheLine.size()); counter++) {
		if (counter == whereToAdd){
			finalNGram.append(" ");
			finalNGram.append(wordToAdd);
			finalNGram.append(" ");
		}
		finalNGram.append(vectorOfTheLine[counter]);
		finalNGram.append(" ");
		finalNGram.append(vectorOfTheLine[counter+1]);
	}
	lineOfText = &finalNGram;
return;
}

unsigned int NGram::getWeight(string ngram) {
	vector<string> vectorDeStrings;
	string aux = "";
	string regularExpr = "grep '^";
	//cambiamos los caracteres de . por \. ya que es un wildcard en regular expressions
	this->convertNgramForGrepUsage(&ngram);
	std::cout << ngram << std::endl;
	regularExpr.append(ngram);
	regularExpr.append("\t' ");
	regularExpr.append(this->ngramAddress);

	//se utiliza el file porque system() no devuelve bien el string
	FILE *filePointer = popen(regularExpr.c_str(),"r");
	char lineOfText[1024];
	fgets(lineOfText, 1024, filePointer); //tengo el contenido de lo buscado
	fclose(filePointer);	//cierro el file

	aux = lineOfText;

	vectorDeStrings = StringUtils::split(aux, '\t');//realizo el split
	unsigned int weight = 0;

	if (!(vectorDeStrings.empty())) {
		std::stringstream out;
		out << vectorDeStrings.back();
		out >> weight;
	}
	return weight;
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

double NGram::getProbability(vector<string> line, int counter) {
	double result;
	double threeGramProbability = 0;
	if (counter > 1){
		string gram = "";
		gram.append(line.at(counter -2)).append(" ");
		gram.append(line.at(counter -1)).append(" ");
		gram.append(line.at(counter));
		threeGramProbability = this->get3GramProbability(gram);
	}
	//TODO refactor
	double biGramProbability = get2GramProbability("algun string");
	double uniGramProbability = get1GramProbability("algun string");
	return result;
}

double NGram::get3GramProbability(string threeGram) { //the cat is
	double result;
//	string lineOfText1 = system("./grep exact regular expression");
//	getWeight(lineOfText1); //check empty string
//	string lineOfText2 = system("./grep hallar todos los bigramas");
	return result;
}

double NGram::get2GramProbability(string biGram) {
	double result;
	return result;
}

double NGram::get1GramProbability(string uniGram) {
	double result;
	return result;
}

unsigned int NGram::whereIsMissingTheWord(vector<string> vectorOfTheLine){
	string searchNgram;
	unsigned int whereToAdd;
	unsigned int minorWeight = std::numeric_limits<unsigned int>::max();	//le asigno el valor maximo de un int

	for (unsigned int counter = 0; counter < (vectorOfTheLine.size() - 1); counter++) {
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

	return whereToAdd;
}

string NGram::whichWordToAdd(vector<string> vectorOfTheLine,unsigned int whereToAdd){
	string wordToAdd;
	return wordToAdd;
}

//std::string exec(char* cmd) {
// FILE* pipe = popen(cmd, "r");
// if (!pipe) return "ERROR";
// char buffer[128];
// std::string result = "";
// while(!feof(pipe)) {
// if(fgets(buffer, 128, pipe) != NULL)
// result += buffer;
// }
// pclose(pipe);
// return result;
//}
