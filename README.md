# Introduction


# Done

- list( void );
- ~list( void );
- list( const list & );
- int size( void ) const; 
- bool empty( void ) const; 
- void clear( void ); 
- T & front( void );
- const T & front( void ) const; 
- T & back( void ); 
- const T & back( void ) const;
- void push_front( const T & value ); 
- void push_back( const T & value ); 
- void pop_front( void ); 
- void pop_back( void ); 
- void assign(const T& value ); 
- void assign( std::initializer_list<T> ilist ); 
- iterator begin( void ); 
- const_iterator cbegin( void ) const; 
- iterator end( void ); 
- const_iterator cend( void ) const; 
- template <class InItr >
- void assign( InItr first, InItr last ); 

# To do

- list( list<T> && );
- list & operator= ( const list<T> & );
- list & operator= ( list<T> && );
- iterator insert( const_iterator itr, const T & value );
- iterator insert( const_iterator pos, std::initializer_list<T> ilist );
- iterator erase( const_iterator itr );
- iterator erase( const_iterator first, const_iterator last );
- const_iterator find( const T & value ) const;

		
# How to build

	`$ g++ -Wall -std=c++11 src/drive_list.cpp -I include -o bin/drive`

	`$ ./bin/drive`


# Git repository

[**projetos.imd.ufrn.br/edivaniap/ls_list**](http://projetos.imd.ufrn.br/edivaniap/ls_list)


# Authorship

Program developed by _Edivânia Pontes de Oliveira_ (< *edivaniap@ufrn.edu.br* >), 2017.1

&copy; IMD/UFRN 2017.
