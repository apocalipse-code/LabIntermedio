#include <iostream>
#include "../include/Misura.h"
#include "../include/MyVector.h"
#include "../include/InertialDriver.h"

//costruttore di default
InertialDriver::InertialDriver():v_(capacity()), head_(-1), tail_(-1){}


//costruttore con lista
InertialDriver::InertialDriver(std::initializer_list<Misura> values):v_(values.size()){
	if(values.size() <= capacity()){
		//se la lista ha un numero adeguato di elementi lo inserisco tutti
		head_ = 0; 
		tail_ = values.size()-1; 
	} else{
		//se la lista è troppo grande, prendo solo gli elementi che ci stanno 
		for(int i=0; i<capacity(); ++i){
			v_[i] = *(values.begin() + i);
		}
		
		head_ = 0; 
		tail_ = capacity()-1;
	}
}


//costruttore con array di Misure
//la dimensione dell'array passato deve essere tassativamente uguale a capacity()
//in caso la dimensione fosse differente, ci sarebbe Undefined Behaviour
InertialDriver::InertialDriver(const Misura* m):v_(capacity()){
	
	if(m){
		for(int i=0; i<capacity(); ++i){
			v_[i] = m[i];
		}
			
		head_ = 0;
		tail_ = capacity()-1;
	} else{
		head_ = -1; //il valore -1 è usato come indice logico per il buffer vuoto 
		tail_ = -1;
	}
}


//costruttore di copia
InertialDriver::InertialDriver(const InertialDriver& obj)
    :v_{obj.v_}, head_{obj.head_}, tail_{obj.tail_}{}


//costruttore di spostamento
InertialDriver::InertialDriver(InertialDriver&& obj)
    :v_{std::move(obj.v_)}, head_{obj.head_}, tail_{obj.tail_}
{
    obj.head_ = -1; //il valore -1 è usato come indice logico per il buffer vuoto
    obj.tail_ = -1;
}



//assegnamento di copia
InertialDriver& InertialDriver::operator=(const InertialDriver& obj) {
    if (this != &obj) { //evito auto assegnamenti
        v_ = obj.v_;    
        head_ = obj.head_;
        tail_ = obj.tail_;
    }
    return *this;
}


//assegnamento di spostamento
InertialDriver& InertialDriver::operator=(InertialDriver&& obj){
    if (this != &obj) { //evito auto assegnamenti
        v_ = std::move(obj.v_);
        head_ = obj.head_;
        tail_ = obj.tail_;
        
        obj.head_ = -1; //il valore -1 è usato come indice logico per il buffer vuoto
        obj.tail_ = -1;
    }
    return *this;
}


int InertialDriver::capacity() const {
	return BUFFER_DIM_; 
}

//ritorna il numero di Misure contenute nel buffer
int InertialDriver::size() const {
	if(isEmpty()){
		return 0; //se è vuoto ritorno 0
	}
	
	if(isFull()){
		return capacity(); //se è pieno ritorno la grandezza fisica del buffer
	}
	
	int N = capacity(); //variabile ausiliaria 
	return ((tail_ - head_ + N) % N) + 1; 
}

//ritorna true se il buffer è pieno, come logica controllo se tail è subito dietro head
bool InertialDriver::isFull() const{
	return head_ == (tail_+1)%capacity();
}

//ritorna true se il buffer è vuoto
bool InertialDriver::isEmpty() const{
	return (head_ == -1 && tail_ == -1);
}

//ritorna la misura più vecchia, cioè la prima del buffer
const Misura& InertialDriver::getFirst() const{
	return (head_ >= 0) ? v_[head_] : throw EmptyBufferException{};
}

//ritorna la misura più nuova, cioè l'ultima inserita nel buffer
const Misura& InertialDriver::getLast() const{
	return (tail_ >= 0) ? v_[tail_] : throw EmptyBufferException{};
}

//ritorna l'n-esima misura del buffer
const Misura& InertialDriver::get(int n) const {
	return (n >= 0 && n < size()) ? v_[(head_ + n)%capacity()] : throw InvalidIndexException{};
}


//l'array passato deve essere tassativamente di 17 elementi, rischio di undefined behaviour 
void InertialDriver::push_back(const Lettura* arr){	
	if(isFull() || isEmpty()){
		//se il buffer è pieno devo shiftare head e sovrascrivere, se invece è vuoto passo da -1 a 0
		head_ = (head_+1)%capacity();
	} 
	
	tail_ = (tail_+1)%capacity();
	
	v_[tail_] = Misura(arr);
	
}

//toglie dal buffer la misura più vecchia e ne ritorna il contenuto, cioè l'array di Letture
const Lettura* InertialDriver::pop_front(){
	if(isEmpty()){
		throw EmptyBufferException{};
	}
	
	int aux = head_;
	
	if(head_ == tail_){
		head_ = -1;
		tail_ = -1;
		return v_[aux].get_letture();
	}
	
	head_ = (head_+1)%capacity();
	return v_[aux].get_letture();
}

void InertialDriver::clear_buffer() {
    // Reset dell'indice head_ (inizio buffer) e indice tail_ (fine buffer)
    // Impostare head_ e tail_ a -1 implicando che non esiste un elemento valido all'inizio e alla fine
    head_ = -1;
    tail_ = -1;
 	// v_ potrebbe essere riusato successivamente e quindi non lo dealloco
    // risparmio tempo e risorse gestendo solo gli indici logici, tuttavia gli elementi sono ancora lì
}

const Lettura& InertialDriver::get_reading(int index) const {
    // Verifico se il buffer è vuoto: 
	// Quando le condizioni di head_ e tail_ assumuno il valore di -1 contemporaneamente
    if (isEmpty()) {
        throw EmptyBufferException{}; // Se vuoto, lancio l'eccezione adeguata
    }    
    // Verificare che l'indice dato sia valido (compreso tra 0 e il numero di misure)

    if (index < 0 || index >= getLast().size() ) {
        throw InvalidIndexException{}; 					// L'indice è fuori dal range valido
    }

    // Accedo al vettore usando l'operatore [] di MyVector
    return getLast().get(index);
}

std::ostream& operator<<(std::ostream& os, InertialDriver obj){
	os << "[";
	
	for(int i=0; i< obj.size(); ++i){
		os << i+1 << "- ";
		os << obj.get(i);
	}
	
	os << "]\n";
	return os;
}