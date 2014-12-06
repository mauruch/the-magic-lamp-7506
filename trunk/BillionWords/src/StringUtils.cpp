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


bool StringUtils::replace(std::string& str, const std::string& from,
		const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

long StringUtils::hashCode(string stringToHash){
	boost::hash<std::string> string_hash;
	return string_hash(stringToHash);
}


