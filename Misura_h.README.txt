#ifndef Misura_h
#define Misura_h

#include <ostream>

class Misura{
	public:
		Misura();  //costruttore di default
		explicit Misura(int dim);  //costruttore con parametro
		
		explicit Misura(const Lettura* arr); //costruttore con array come parametro 		
	
		const Lettura& get(int index) const; //ritorna un elemento all'indice passato
	private:
		const static int DIM_ = 17; //dimensione del vettore stile C di Letture
		const Lettura l_[DIM]; //vettore stile C di Letture
}

//overloading operatore di stampa
void operator<<(std:ostream os, Misura& m);

#include "Misura.cpp"
#include "Lettura.cpp"
#endif 