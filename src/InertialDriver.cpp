#include <iostream>
#include "../include/Misura.h"
#include "../include/MyVector.h"
#include "../include/InertialDriver.h"

//costruttore di default
InertialDriver::InertialDriver():v_(size()), head_(-1), tail_(-1){}


//costruttore con lista
InertialDriver::InertialDriver(std::initializer_list<Misura> values):v_(values.size()){
	if(values.size() <= size()){
		head_ = 0; 
		tail_ = values.size()-1; 
	} else{
		//se la lista è troppo grande, prendo solo i primi size() elementi
		v_(size()); 
		for(int i=0; i<size(); ++i){
			v_[i] = *(values.begin() + i);
		}
		
		head_ = 0; 
		tail_ = size()-1;
	}
}


//costruttore con array di Misure
//la dimensione dell'array passato deve essere tassativamente uguale a size()
InertialDriver::InertialDriver(const Misura* m):v_(size()){
	
	if(m){
		for(int i=0; i<size(); ++i){
			v_[i] = m[i];
		}
			
		head_ = 0;
		tail_ = size()-1;
	} else{
		head_ = -1;
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
    obj.head_ = -1;
    obj.tail_ = -1;
}



//assegnamento di copia
InertialDriver& InertialDriver::operator=(const InertialDriver& obj) {
    if (this != &obj) {
        v_ = obj.v_;    
        head_ = obj.head_;
        tail_ = obj.tail_;
    }
    return *this;
}


//assegnamento di spostamento
InertialDriver& InertialDriver::operator=(InertialDriver&& obj){
    if (this != &obj) {
        v_ = std::move(obj.v_);
        head_ = obj.head_;
        tail_ = obj.tail_;
        
        obj.head_ = -1;
        obj.tail_ = -1;
    }
    return *this;
}


int InertialDriver::size() const {
	return size(); 
}

bool InertialDriver::isFull() const{
	return head_ == (tail_+1)%size();
}

bool InertialDriver::isEmpty() const{
	return (head_ == -1 && tail_ == -1);
}

const Misura& InertialDriver::getFirst() const{
	return (head_ >= 0) ? v_[head_] : throw EmptyBufferException{};
}

const Misura& InertialDriver::getLast() const{
	return (tail_ >= 0) ? v_[tail_] : throw EmptyBufferException{};
}

const Misura& InertialDriver::get(int n) const {
	return (n >= 0 && n < size()) ? v_[n] : throw InvalidIndexException{};
}


//l'array passato deve essere di 17 elementi 
void InertialDriver::push_back(const Lettura* arr){	
	if(isFull() || isEmpty()){
		head_ = (head_+1)%size();
	} 
	
	tail_ = (tail_+1)%size();
	std::copy(arr, arr + v_[tail_].size(), v_[tail_]);
}

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
	
	head_ = (head_+1)%size();
	return v_[aux];
}

void InertialDriver::clear_buffer(){}

const Lettura& get_reading(int index) const{}

std::ostream& operator<<(std::ostream& os, InertialDriver obj){
	os << "[";
	
	for(int i=0; i<size(); ++i){
		os << obj.v_[i];
		
		if(i < size()-1){
			os << "; ";
		}
	}
	
	os << "]\n";
	return os;
}