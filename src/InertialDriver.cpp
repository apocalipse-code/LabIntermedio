#include <iostream>
#include "Misura.h"
#include "MyVector.h"

//costruttore di default
InertialDriver::InertialDriver():v_(BUFFER_DIM_), head_(-1), tail_(-1){}


//costruttore con lista
InertialDriver::InertialDriver(std::initializer_list<Misura> values){
	if(values.size() <= BUFFER_DIM_){
		v_(values);
		head_ = 0; 
		tail_ = values.size()-1; 
	} else{
		//se la lista è troppo grande, prendo solo i primi BUFFER_DIM_ elementi
		v_(BUFFER_DIM_); 
		for(int i=0; i<BUFFER_DIM_; ++i){
			v_[i] = *(values.begin() + i);
		}
		
		head_ = 0; 
		tail_ = BUFFER_DIM_-1;
	}
}


//costruttore con array di Misure
InertialDriver::InertialDriver(const Misura* m, int dim=0){
	v_(BUFFER_DIM_); 
	
	if(dim > 0){
		dim = (dim > BUFFER_DIM_) ? BUFFER_DIM_ : dim; 
		
		for(int i=0; i<dim; ++i){
			v_[i] = m[i];
		}
		
		head_ = 0;
		tail_ = dim-1;
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
	return BUFFER_DIM_; 
}

const Misura& InertialDriver::getFirst() const{
	return (head >= 0) ? v_[head] : throw EmptyBufferException;
}

const Misura& InertialDriver::getLast() const{
	return (tail >= 0) ? v_[tail] : throw EmptyBufferException;
}

const Misura& InertialDriver::get(int n) const {
	return (n >= 0 && n < BUFFER_DIM_) ? return v_[n] : throw InvalidIndexException;
}


void InertialDriver::push_back(const Lettura* arr){
	
}

Lettura* InertialDriver::pop_front(){
	
}