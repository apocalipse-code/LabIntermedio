#include "Misura.h"

//costruttore di default
Misura::Misura(){}


//costruttore con parametro intero
Misura::Misura(int dim){}


//costruttore con parametro array di Letture
//occorre documentare che l'array passato deve essere esattamente di 17 elementi, altrimenti Undef Behav
Misura::Misura(const Lettura* arr){
	if(arr){
		for(int i=0; i < DIM_; ++i){
			l_[i] = arr[i];
		}
	} 
}


//funzione getter per gli elementi dell'array
const Lettura& Misura::get(int index) const{
	return l_[index];
}


std::ostream& operator<<(std::ostream os, Misura& m){
	os << "(";
	for(int i=0; i< DIM_; ++i){
		os << m.get(i); 
		
		if(i < DIM_-1){
			os << ", ";
		}
	}
	
	os << ")";
	return os; 
}