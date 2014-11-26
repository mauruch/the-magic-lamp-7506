#include <stdlib.h>
#include <fstream>
using namespace std;


generadorArchivoGrep::generadorArchivoGrep(){}

generadorArchivoGrep::~generadorArchivoGrep() {
	// TODO Auto-generated destructor stub
}


//hay que darle permiso al .sh para que ande
//chmod a+x /where/i/saved/it/(elnombredelscript).sh
void generadorArchivoGrep::generarArchivo(string miPalabra){

	ofstream myfile ("grepscriptprueba2.sh");

		  if (myfile.is_open())
		  {
		    myfile << "#!/bin/bash \n";
		    string miVariableScript= "var="+miPalabra+"\n";
		    myfile << miVariableScript;
		    myfile << "grep $var docprueba > grepscriptprueba2.txt";
		    myfile.close();
		  }
		  else cout << "Unable to open file";
		system("./grepscriptprueba2.sh");


}

