#ifndef InertialDriver_h
#define InertialDriver_h

#include "./MyVector.h"
#include "./Misura.h"
#include <ostream>

class InertialDriver{
	public:
		InertialDriver(); //costruttore di default
		InertialDriver(std::initializer_list<Misura> values); //costruttore con lista
		InertialDriver(const Misura* m); //costruttore con array di Misure
		InertialDriver(const InertialDriver& inDriver); //costruttore di copia
		InertialDriver(InertialDriver&& inDriver); //costruttore di spostamento
		
		
		InertialDriver& operator=(const InertialDriver& inDriver); //assegnamento di copia
		InertialDriver& operator=(InertialDriver&& inDriver); //assegnamento di spostamento

		int capacity() const; //ritorna la dimensione massima del buffer
		int size() const; //ritorna il numero di Misure che il buffer contiene
		bool isFull() const; //ritorna true se il buffer è pieno
		bool isEmpty() const; //ritorna true se il buffer è vuoto
		
		const Misura& getFirst() const; //ritorna la prima misura inserita, o la più vecchia in generale se sovrascritta
		const Misura& getLast() const; //ritorna l'ultima misura inserita
		const Misura& get(int n) const;//ritorna l'n-esima misura nel buffer, se l'indice è invalido lancia eccezione
		
		void push_back(const Lettura* arr); //aggiunge una Misura al buffer, se è pieno sovrascrive la più vecchia
		const Lettura* pop_front(); //toglie la misura più vecchia dal buffer, se è vuoto lancia eccezione
		
		void clear_buffer(); //svuota il buffer
		const Lettura& get_reading(int index) const;  //ritorna la Lettura richiesta della Misura più recente
		//se l'indice passato è invalido allora get_reading(int) lancia eccezione
		
		class EmptyBufferException{}; 
		class InvalidIndexException{};
		
	private: 
		static constexpr int BUFFER_DIM_ = 10; //dimensione fisica del buffer
		MyVector<Misura> v_; //struttura dato per il buffer
		int head_; //indice logico della misura più vecchia
		int tail_; //indice logico della misura più recente
};

//overloading dell'operatore di output
std::ostream& operator<<(std::ostream& os, InertialDriver obj);

#endif