#include "../headers/StringUtils.h"

StringUtils::~StringUtils() {
	// TODO Auto-generated destructor stub
}

StringUtils::StringUtils(string direccionDeLosNgramas) {
	this->direccionNgramas = direccionDeLosNgramas;
}

vector<string> & StringUtils::split(const string &s, char delim,
		vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;

}

vector<string> StringUtils::split(const string &s, char delim) {
	vector<std::string> elems;
	split(s, delim, elems);
	return elems;

}

int StringUtils::getWeight(vector<string> &elems) {
	string lastElement = elems.at(elems.size() - 1);
	char ch = *lastElement.rbegin();
	return (int) ch - '0';
}

void StringUtils::removeSpaces(string& str) {
	/* remove multiple spaces */
	int k = 0;
	for (int j = 0; j < str.size(); ++j) {
		if ((str[j] != ' ') || (str[j] == ' ' && str[j + 1] != ' ')) {
			str[k] = str[j];
			++k;
		}

	}
	str.resize(k);

	/* remove space at the end */
	if (str[k - 1] == ' ')
		str.erase(str.end() - 1);
	/* remove space at the begin */
	if (str[0] == ' ')
		str.erase(str.begin());
}

int StringUtils::devolverPesoNgrama(string stringABuscar){
	string auxiliar = "";
	string buscarEsto = "grep '";
	buscarEsto.append(stringABuscar);
	buscarEsto.append(" [^a-z^A-Z]*$' ");
	buscarEsto.append(this->direccionNgramas);
	FILE *filePointer = popen(buscarEsto.c_str(),"r");

	char buf[1024];

	while (fgets(buf, 1024, filePointer)) {
		auxiliar.append(buf);
	}
	std::cout << buf << std::endl;
	fclose(filePointer);
	return 0;
}
