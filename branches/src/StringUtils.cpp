#include "../headers/StringUtils.h"

StringUtils::~StringUtils() {
	// TODO Auto-generated destructor stub
}

StringUtils::StringUtils() {
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

bool StringUtils::replace(std::string& str, const std::string& from,
		const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

