#include "../include/Misura.h"

//costruttore di default
Misura::Misura():letture_{} {}

//costruttore con parametro array di Letture
//occorre che l'array passato sia esattamente di 17 elementi, altrimenti Undefined Behaviour
Misura::Misura(const Lettura* arr):letture_{}{
	if(arr){
		for(int i=0; i < DIM_; ++i){
			letture_[i] = arr[i];
		}
	}
}

//costruttore di copia
Misura::Misura(const Misura& m){
	std::copy(m.letture_, m.letture_+DIM_, letture_);
}


//assegnamento di copia
Misura& Misura::operator=(const Misura& m){
	if(this != &m){
		std::copy(m.letture_, m.letture_+DIM_, letture_);
	}
	
	return *this;
}


//funzione getter per gli elementi dell'array
const Lettura& Misura::get(int index) const{
	if(index < 0 || index >= DIM_){
		throw InvalidIndexException{};
	}
	return letture_[index];
}


//ritorna un puntatore al primo elemento dell'array di letture
const Lettura* Misura::get_letture() const{
	return letture_;
}

//ritorna la dimensione dell'array di letture
int Misura::size() const{
	return DIM_;
}


//overloading operatore di stampa
std::ostream& operator<<(std::ostream& os, const Misura& m){
	os << "(";
	for(int i=0; i< m.size(); ++i){
		os << m.get(i); 
		
		if(i < m.size()-1){
			os << ", ";
		}
	}
	
	os << ");\n";
	return os; 
}