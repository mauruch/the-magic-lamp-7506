/*
 * NGram.h
 *
 *  Created on: 25/11/2014
 *      Author: mauro
 */

#ifndef HEADERS_NGRAM_H_
#define HEADERS_NGRAM_H_

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

class NGram {

private:
	string ngramAddress;

public:

	NGram(string ngramAddress);
	virtual ~NGram();

	/**
	 * return the weight
	 * ngram: 'word1 word2.. wordN weight
	 */
	unsigned int getWeight(string ngram);
	/**
	 * will return the modified lineOfText with the missing word, ready to be put in the file
	 */
	void fillTheMissingWord(string *lineOfText);
};

#endif /* HEADERS_NGRAM_H_ */
