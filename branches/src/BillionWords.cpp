#include "../headers/CONSTANTES.h"
#include "../headers/StringUtils.h"
#include "../headers/NGram.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;


int main(int argc, char *argv[]) {
	ifstream fileTest_v2 ("/home/fdc/workspace/OrgaDatos/trunk/BillionWords/test_v2.txt");
	StringUtils *stringUtils = new StringUtils();
	NGram *nGram = new NGram();

	if (fileTest_v2.is_open()){
			string lineOfText;
			getline(fileTest_v2, lineOfText);
			while (getline(fileTest_v2, lineOfText)) {
				cout << "ping1" <<endl;
				vector<string> vectorLine = stringUtils->split(lineOfText, ' ');
				cout << "ping2" <<endl;
				unsigned int wordMissingPos = nGram->whereIsMissingTheWord(vectorLine);
				cout << "ping3" <<endl;
				string salida = vectorLine.at(wordMissingPos).append(" POSICION ");
				cout << "ping4" <<endl;
				cout << salida << endl;
				cout << "ping5" <<endl;
				cout << wordMissingPos << endl;
				cout << "ping6" <<endl;
			}

	}
	else{
		cout << "Problemas al abrir los archivos" << endl;
		cout << "Probar viendo si las direcciones pasadas son correctas" << endl;

		return ERROR_AL_ABRIR_ARCHIVO;
	}

	return 0;
}

