/*
 * generadorArchivoGrep.h
 *
 *  Created on: 25/11/2014
 *      Author: santiago
 */

#ifndef TRUNK_BILLIONWORDS_HEADERS_GENERADORARCHIVOGREP_H_
#define TRUNK_BILLIONWORDS_HEADERS_GENERADORARCHIVOGREP_H_

#include <stdlib.h>
#include <fstream>
using namespace std;

class generadorArchivoGrep{
private:
string miPalabra;

public:

generadorArchivoGrep();
virtual ~generadorArchivoGrep();

static void generarArchivo(string miPalabra);

};
#endif /* TRUNK_BILLIONWORDS_HEADERS_GENERADORARCHIVOGREP_H_ */
