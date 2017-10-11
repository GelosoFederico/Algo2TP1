// Template de arreglo dinamico

#ifndef ARRAYDIN_H
#define ARRAYDIN_H

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <stdio.h>

#define ARRAY_DEFAULT_SIZE 1
#define ARRAY_SIZE_CHOP 5


template <class T> class Array
{
public:
	Array();
	Array(size_t n); 
	Array( const Array<T> & ); 
	~Array( ); 
	size_t 		getSize( ) const; 
	Array<T>&	operator=( const Array<T> & ); 
	bool 		operator==( const Array<T> & ) const; 
	bool 		operator!=( const Array<T> & ) const; 
	T &		operator[ ]( int );
	void		append(T&);

private:
	size_t alloc_size; 
	size_t used_size;
	T *ptr; 

	void 		resize(int );
};

template <class T> Array<T>::Array()
{
	alloc_size = ARRAY_DEFAULT_SIZE;
	used_size = 0;
	ptr = new T[alloc_size];
}

template <class T> Array<T>::Array(size_t n)
{
	alloc_size = n;
	used_size = n;
	ptr = new T[alloc_size];
}


template <class T> Array<T>::Array( const Array<T> &init )
{
	used_size = init.used_size;
	alloc_size = init.alloc_size;
	ptr = new T[ alloc_size ];
	for ( int i = 0; i < used_size; i++ )
		ptr[ i ] = init.ptr[ i ]; //debe existir el = para la clase T !
}


template <class T> Array<T>::~Array()
{
	if (ptr)
		delete[] ptr; 
}

template <class T> size_t Array<T>::getSize() const { return used_size; }

template <class T> Array<T>& Array<T>::operator=( const Array<T> &right )
{
	T* aux;

	if ( &right == this ) {
		return *this;
	}
	if ( alloc_size != right.alloc_size ){
		aux = new T[ right.alloc_size ]; 
		delete [] ptr; 
		ptr = aux;
		alloc_size = right.alloc_size; 
		used_size = right.used_size;
		for ( int i = 0; i < used_size; i++ ){
			ptr[ i ] = (right.ptr)[ i ]; 
		}
		return *this; 
		}
	else {
		used_size = right.used_size;
		for ( int i = 0; i < used_size; i++ )
			ptr[ i ] = right.ptr[ i ]; 
		return *this; 
	}
	return *this;
}

template <class T> bool Array<T>::operator==( const Array<T> &right ) const
{
	if ( used_size != right.used_size )
		return false; 
	else{
		for ( int i = 0; i < used_size; i++ ){
			if ( ptr[ i ] != right.ptr[ i ] )
       				return false; 
		}
       	return true; 
       }
}

template <class T> bool Array<T>::operator!=( const Array<T> &right ) const
{
	if ( right == *this )
		return false;
	else
		return true;
}

template <class T> T & Array<T>::operator [ ]( int subscript )
{
	assert( (0 < subscript)|| (subscript < used_size) ) ; 
	return ptr[ subscript ]; 
}

template <class T> void Array<T>::resize(int new_size)
{
	T *aux;

	aux = new T[new_size];
	if(new_size>used_size){
		//copio todo
		for(int i=0;i<used_size;++i){
			aux[i] = (*this)[i];
		}
	}
	else{
		//copio hasta donde llega
		used_size = new_size;
		for(int i=0;i<used_size;++i){
			aux[i] = (*this)[i];
		}
	}
	delete [] ptr;
	ptr = aux;
	alloc_size = new_size;
}

template <class T> void Array<T>::append(T &new_thing)
{
	if(alloc_size == used_size){
		this->resize(alloc_size+ARRAY_SIZE_CHOP);
	}	
	ptr[used_size] = new_thing;
	used_size++;
}

template <class T> 
std::ostream & operator<< (std::ostream& os,Array<T> & arr)
{
	for(int i=0; i<arr.getSize(); ++i){
		os<<arr[i]<<" ";
	}
	os << std::endl;
	return os;
}
#endif
