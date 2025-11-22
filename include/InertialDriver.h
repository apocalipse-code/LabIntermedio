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

		int size() const; 
		bool isFull() const;
		bool isEmpty() const;
		
		const Misura& getFirst() const; //ritorna la prima misura inserita, o la più vecchia in generale se sovrascritta
		const Misura& getLast() const; //ritorna l'ultima misura inserita
		const Misura& get(int n) const;//ritorna l'n-esima misura nel buffer, se l'indice è invalido lancia eccezione
		
		void push_back(const Lettura* arr); 
		Lettura* pop_front(); 
		
		void clear_buffer(); 
		const Lettura& get_reading(int index) const;  //lancia EmptyBufferException se tail < 0
		
		
		class EmptyBufferException{}; 
		class InvalidIndexException{}; 
		
	private: 
		static constexpr int BUFFER_DIM_ = 10; 
		MyVector<Misura> v_; 
		int head_; //indice della misura più vecchia
		int tail_; //indice della misura più recente
};

std::ostream& operator<<(std::ostream& os, InertialDriver obj);

#endif