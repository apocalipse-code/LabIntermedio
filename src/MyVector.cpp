#include "../include/MyVector.h"

//costruttore di default
template<class T>
MyVector<T>::MyVector(){
	sz = 0; 
	fullsz = 0; 
	elem = nullptr; 
}


//costruttore con parametro intero per la dimensione del vettore
template<class T>
MyVector<T>::MyVector(int dim){
	if(dim > 0){
		sz = dim; 
		fullsz = dim * 2; 
		elem = new T[fullsz]; 
	} else{
		//se la dimensione passata è invalida creo un vettore vuoto
		sz = 0;
		fullsz = 0; 
		elem = nullptr; 
	}
}


//costruttore che accetta una lista di oggetti di tipo T
template<class T>
MyVector<T>::MyVector(std::initializer_list<T> values){
	if(values.size() > 0){
		sz = values.size(); 
		fullsz = sz * 2; 
		elem = new T[fullsz]; 
		
		//copio i valori della lista nel mio vettore
		std::copy(values.begin(), values.end(), elem);  
		
	} else{
		//se la lista è vuota creo un vettore vuoto
		sz = 0; 
		fullsz = 0;
		elem = nullptr; 
	}
}


//costruttore di copia
template<class T>
MyVector<T>::MyVector(const MyVector<T>& mv)
	:sz{mv.sz}, fullsz{mv.fullsz}, elem{ new T[fullsz]}{
	
	//copio tutti gli elementi di mv in elem
	std::copy(mv.elem, mv.elem + mv.size(), elem); 
	
}


//costruttore di spostamento
template<class T>
MyVector<T>::MyVector(MyVector<T>&& mv)
	:sz{mv.sz}, fullsz{mv.fullsz}, elem{mv.elem}{
		//elimino il vettore che ho spostato
		mv.sz = 0;
		mv.fullsz = 0;
		mv.elem = nullptr;
}


//distruttore
template<class T>
MyVector<T>::~MyVector(){
	sz = 0; 
	fullsz = 0; 
	delete[] elem; 
}


//assegnamento di copia
template<class T>
MyVector<T>& MyVector<T>::operator=(const MyVector& mv){
	//controllo per gli auto assegnamenti 
	if(this != &mv){
		T* ptr = new T[mv.fullsz]; //puntatore ausiliario 
	
	    std::copy(mv.elem, mv.elem + mv.size(), ptr); //copio il vettore mv nell'area del freestore di ptr
		
		delete[] elem; //elimino il mio vettore vecchio
		elem = ptr; //assegno al mio vettore il contenuto di mv
		
		sz = mv.sz; 
		fullsz = mv.fullsz; 
		
		ptr = nullptr; //rendo nullo il puntatore ausiliario per sicurezza
	}
	
	return *this; //ritorno il mio vettore copiato
}


//assegnamento di spostamento
template<class T>
MyVector<T>& MyVector<T>::operator=(MyVector&& mv){
	delete[] elem; //elimino il mio vettore
	elem = mv.elem; //sovrascrivo con il nuovo vettore mv
	mv.elem = nullptr; 
	
	sz = mv.sz;
	fullsz = mv.fullsz;
	mv.sz = 0;
	mv.fullsz = 0;
	
	return *this;
}


//getter per sz
template<class T>
int MyVector<T>::size() const{
	return sz;
}


//getter per fullsz
template<class T>
int MyVector<T>::capacity() const{
	return fullsz; 
}


//overloading operatore []
template<class T>
T& MyVector<T>::operator[](int pos){
	return elem[pos]; 
}


//overloading operatore [] per istanze costanti
template<class T>
const T& MyVector<T>::operator[](int pos) const{
	return elem[pos];
}


//funzione che ritorna l'elemento all'indice passato, effettua controllo se l'indice è valido
//potrebbe lanciare l'eccezione IndexOutOfBoundException se l'indice non fosse valido
template<class T>
T& MyVector<T>::at(int index){
	if(index >= 0 && index < sz){
		return elem[index]; 
	}
	
	throw IndexOutOfBoundException(); 	
}


//funzione che ritorna l'elemento all'indice passato, effettua controllo se l'indice è valido
//overloading per le istanze costanti
//può lanciare l'eccezione IndexOutOfBoundException
template<class T>
const T& MyVector<T>::at(int index) const{
	if(index >= 0 && index < sz){
		return elem[index]; 
	}
	
	throw IndexOutOfBoundException();
}


//aggiunge un elemento alla fine del vettore. Se è pieno ne aumenta la dimensione
template<class T>
void MyVector<T>::push_back(const T& obj){
	if(sz == fullsz){
		//caso in cui il vettore è pieno
		if(elem){
			fullsz = fullsz*2; //definisco la nuova capacità del vettore

			T* elem2 = new T[fullsz]; //creo la nuova memoria

			std::copy(elem, elem+sz, elem2); //copio tutto nella nuova memoria 
			
			delete[] elem; //elimino la memoria vecchia

			elem = elem2; //punto alla memoria nuova  
			elem2 = nullptr; 
		
			elem[sz] = obj; 	
			sz++;
		} else{
			//caso in cui il vettore è vuoto 
			sz++;
			fullsz++; 
			elem = new T[fullsz]; 
			elem[0] = obj; 
		}
	} else{
		//caso in cui il vettore non è pieno e non è neanche vuoto
		elem[sz] = obj;	
		sz++; 
	}	
}


//toglie un elemento dalla fine del vettore
//potrebbe lanciare EmptyVectorException se il vettore è vuoto
template<class T>
T& MyVector<T>::pop_back(){
	if(sz > 0){
		sz--; 
		return elem[sz]; 
	}
	
	throw EmptyVectorException(); 
}

//riserva tanti posti quanti ne richiede l'utente. Se quei posti sono già disponibili, non fa niente
template<class T>
void MyVector<T>::reserve(int newsz){
	if(newsz > fullsz){
		if(elem){
			T* elem2 = new T[newsz]; //creo una nuova memoria grande quanto richiesto
			
			std::copy(elem, elem+sz, elem2); //copio tutto lì
			
			delete[] elem; //elimino la memoria vecchia
			elem = elem2; //sposto il puntatore alla memoria vecchia
			elem2 = nullptr;  
			fullsz = newsz; //aggiorno la nuova capacità del vettore
		} else{
			fullsz = newsz;
			elem = new T[fullsz];
		}
	}
}


//overloading dell'operatore <<
template<class T>
std::ostream& operator<<(std::ostream& os, const MyVector<T>& mv){
	os << "[";
	for(int i=0; i< mv.size(); ++i){
		os << mv[i]; 
		
		if(i < mv.size()-1){
			os << ", ";
		}
	}
	
	os << "]";
	return os; 
}