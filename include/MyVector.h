#ifndef MyVector_h
#define MyVector_h

#include <ostream>

/*
  * la classe MyVector<T> non accetta oggetti non assegnabili 
*/

template<typename T>
class MyVector{
	public:
		MyVector(); //costruttore di default
		explicit MyVector(int dim);  //costruttore che prende una dimensione per il vettore
		MyVector(std::initializer_list<T> values); //costruttore che prende una lista di oggetti T 
		MyVector(const MyVector<T>& mv); //costruttore di copia 
		MyVector(MyVector<T>&& mv); //costruttore di spostamento
		~MyVector(); //distruttore 
		
		MyVector<T>& operator=(const MyVector<T>& mv); // assegnamento di copia
		MyVector<T>& operator=(MyVector<T>&& mv); // assegnamento di spostamento
		
		int size() const; //getter per il numero di elementi inseriti (sz)
		int capacity() const;  //getter per la capacità totale del vettore (fullsz)
		
		T& operator[](int pos);  //overloading di [] non const (lettura e scrittura abilitate)
		const T& operator[](int pos) const; //overloading di [] per oggetti costanti e per sola lettura
		
		T& at(int index);  //è uguale a [] ma in più fa un controllo; scrittura e lettura abilitate
		const T& at(int index) const; //versione const, per oggetti costanti e per sola lettura
		/*la funzione at(int) può lanciare l'eccezione IndexOutOfBoundException se l'indice passato non è valido*/
		
		
		void push_back(const T& obj);  //aggiunge un elemento alla fine
		T& pop_back();  //toglie un elemento dalla fine
		/*la funzione pop_back() può lanciare EmptyVectorException in caso il vettore sia vuoto*/
		
		void reserve(int newsz); //alloca uno spazio extra al vettore passato dall'utente
		
		class IndexOutOfBoundException{}; //lanciata da at(int) 
		class EmptyVectorException{}; //lanciata da pop_back()

	private:
		int sz;  //numero di elementi effettivamente inseriti nell'array
		int fullsz;  //numero totale di celle allocate 
		T* elem;  //puntatore al primo elemento dell'array 
};

//overloading dell'operatore <<
//è stato posto fuori dalla classe volutamente come scelta di design 
template <typename T>
std::ostream& operator<<(std::ostream& os, const MyVector<T>& mv);
 

// Includo l'implementazione dei template
#include "MyVector.cpp"

#endif