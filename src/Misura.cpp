#include "../include/Misura.h"

//costruttore di default
Misura::Misura():letture{} {}

//costruttore con parametro array di Letture
//occorre che l'array passato sia esattamente di 17 elementi, altrimenti Undefined Behaviour
Misura::Misura(const Lettura* arr){
	letture_(DIM_);
	
	if(arr){
		for(int i=0; i < DIM_; ++i){
			letture_[i] = arr[i];
		}
	}
}

Misura::Misura(const Misura& m){
	std::copy(m.letture_, m.letture_+DIM_, letture_);
}


Misura& Misura::operator=(const Misura& m){
	if(this != &m){
		std::copy(m.letture_, m.letture_+DIM_, letture_);
	}
	
	return *this;
}

//funzione getter per gli elementi dell'array
const Lettura& Misura::get(int index) const{
	if(index < 0 || index >= DIM_){
		throw InvalidIndexException;
	}
	return letture_[index];
}

const Lettura* Misura::get_letture() const{
	return letture_[0];
}

int Misura::size() const{
	return DIM_;
}


std::ostream& operator<<(std::ostream& os, const Misura& m){
	os << "(";
	for(int i=0; i< m.DIM_; ++i){
		os << m.get(i); 
		
		if(i < m.DIM_-1){
			os << ", ";
		}
	}
	
	os << ")";
	return os; 
}