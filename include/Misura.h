#ifndef Misura_h
#define Misura_h

#include <ostream>
#include "./Lettura.h"

class Misura{
	public:
		Misura();  //costruttore di default	
		explicit Misura(const Lettura* arr); //costruttore con array come parametro 

		//NOTA: DA FARE COSTRUTTORI E ASSEGNAZIONI DI COPIA E SPOSTAMENTO
		Misura(const Misura& m);
		Misura(Misura&& m);
		
		Misura& operator=(const Misura& m);
		Misura& operator=(Misura&& m);
	
		const Lettura& get(int index) const; //ritorna un elemento all'indice passato
		
		const Lettura* get_letture() const; //ritorna un puntatore const all'inizio del vettore
		int size() const; //ritorna la dimensione del vettore di letture
		
		class InvalidIndexException{}; //lanciata da get
	private:
		static constexpr int DIM_ = 17; //dimensione del vettore stile C di Letture
		Lettura letture_[DIM_]; //vettore stile C di Letture
};

//overloading operatore di stampa
std::ostream& operator<<(std::ostream& os, const Misura& m);

#endif 