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
	/**
	 * va a ser para remover las wildcards de las regular expressions
	 */
	void convertNgramForGrepUsage(string *ngram);
	/*
	 * todo definir comportamiento
	 */
	double getProbability(vector<string> line, int counter);
	/*
	 * todo definir comportamiento
	 */
	double get3GramProbability(string threeGram);
	/*
	 * todo definir comportamiento
	 */
	double get2GramProbability(string biGram);
	/*
	 * todo definir comportamiento
	 */
	double get1GramProbability(string uniGram);
	/*
	 * Nos dice en que posicion falta la palabra, ejemplo, si tengo I running, y la frase deberia ser
	 * I am running, devuelve 1, que es la posicion donde deberia haber una palabra
	 */
	unsigned int whereIsMissingTheWord(vector<string> vectorOfTheLine);
	/*
	 * Sabiendo donde uno tiene que insertar, puede saber cual es el ngrama y cual le sigue
	 */
	string whichWordToAdd(vector<string> vectorOfTheLine,unsigned int whereToAdd);
};

#endif /* HEADERS_NGRAM_H_ */
