#include "Misura.h"

//costruttore di default
Misura::Misura(){}

//costruttore con parametro array di Letture
//occorre documentare che l'array passato deve essere esattamente di 17 elementi, altrimenti Undef Behav
Misura::Misura(const Lettura* arr){
	if(arr){
		for(int i=0; i < DIM_; ++i){
			letture_[i] = arr[i];
		}
	} 
}


//funzione getter per gli elementi dell'array
const Lettura& Misura::get(int index) const{
	if(index < 0 || index >= DIM_){
		throw InvalidIndexException;
	}
	return letture_[index];
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