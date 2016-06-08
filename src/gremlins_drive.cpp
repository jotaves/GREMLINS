// g++ -Wall -std=c++11 src/gremlins_drive.cpp -o bin/drive -I include/

/*!
 *  @mainpage GREMLINS
 *  @author João Victor Bezerra Barboza
 *	@author Carlos Vinicius Fernandes Rodrigues
 *  @date Maio, 2016
 *  @copyright Copyright &copy; 2016. Todos os direitos reservados.
 *  @version 1.0
 *
 *  @file gremlins_drive.cpp
 *  @brief Arquivo do drive
 *
 *	Arquivo com os testes das funções implementadas
 */

#include <iostream>

#include "sl_pool.h"


int main (void){

/*

for ( std::time_t t( 0 ) ; t < _timeLimit ; ++t ){
	while( !pq.empty() ){
		Event ev = pq.top();
		if ( event.getTimeStamp() > t ) break;
		pq.pop()
		_pool.Free( ev.getMemoryPtr() );
		delete ev;
	}
	 auto memSize = getRandomForSize();
	 void* const add = _p.Allocate( memSize );
	 auto elapsedTime = getRandomTimeInterval();
	 std::time_t releaseTime = t + elapsedTime;
	 pq.push( new Event( add, releaseTime ) );
}

*/
	//std::cout << "Freeing " << ptBlockReserved->mui_Length  << " block(s).\n";
	
	SLPool p (64);
	
	std::cout << "Allocating array.\n";
	int *array = new (p) int[3];
	p.print();
	
	std::cout << "Deleting array.\n";
	delete array;
	
	p.print();
	
	std::cout << "Trying do allocate " << sizeof(long double) + sizeof ( Tag ) << " bytes in a.\n";
	long double *a = new (p) long double;
	p.print();
	
	std::cout << "Trying do allocate " << sizeof(int) + sizeof ( Tag ) << " bytes in b.\n";
	int *b = new (p) (int);
	p.print();
	
	std::cout << "Trying do allocate " << sizeof(long int) + sizeof ( Tag ) << " bytes in c.\n";
	long int *c = new (p) (long int);
	p.print();
	
	std::cout << std::endl;
	
	std::cout << "Freeing a.\n";
	delete a;
	p.print();
	
	std::cout << "Freeing b.\n";
	delete b;
	p.print();
	
	std::cout << "Freeing c.\n";
	delete c;
	p.print();
	
	std::cout << std::endl;
	
	std::cout << "Allocating again.\n";
	a = new (p) long double;
	b = new (p) (int);
	c = new (p) (long int);
	
	p.print();
	
	std::cout << std::endl;
	
	std::cout << "Freeing a.\n";
	delete a;
	p.print();
	
	std::cout << "Freeing c.\n";
	delete c;
	p.print();
	
	std::cout << "Freeing b.\n";
	delete b;
	p.print();
	
	std::cout << std::endl;
	
	std::cout << "Allocating again.\n";
	a = new (p) long double;
	b = new (p) (int);
	c = new (p) (long int);
	
	p.print();
	
	std::cout << std::endl;
	
	std::cout << "Freeing b.\n";
	delete b;
	p.print();
	
	std::cout << "Freeing a.\n";
	delete a;
	p.print();
	
	std::cout << "Freeing c.\n";
	delete c;
	p.print();
	
	std::cout << std::endl;
	
	std::cout << "Allocating again.\n";
	a = new (p) long double;
	b = new (p) (int);
	c = new (p) (long int);
	
	p.print();
	
	std::cout << std::endl;
	
	std::cout << "Freeing b.\n";
	delete b;
	p.print();
	
	std::cout << "Freeing c.\n";
	delete c;
	p.print();
	
	std::cout << "Freeing a.\n";
	delete a;
	p.print();
	
	std::cout << std::endl;		
	
	std::cout << "Allocating again.\n";
	a = new (p) long double;
	b = new (p) (int);
	c = new (p) (long int);
	
	p.print();
	
	std::cout << std::endl;
	
	std::cout << "Freeing c.\n";
	delete c;
	p.print();
	
	std::cout << "Freeing a.\n";
	delete a;
	p.print();
	
	std::cout << "Freeing b.\n";
	delete b;
	p.print();
	
	std::cout << std::endl;

	std::cout << "Allocating again.\n";
	a = new (p) long double;
	b = new (p) (int);
	c = new (p) (long int);	
	
	p.print();
	std::cout << std::endl;
	
	std::cout << "Freeing c.\n";
	delete c;
	p.print();
	
	std::cout << "Freeing b.\n";
	delete b;
	p.print();
	
	std::cout << "Freeing a.\n";
	delete a;
	p.print();
	
	std::cout << std::endl;
	
	std::cout << ">>> Here we can see the difference between best fit and first fit (and if best fit is working normally).\n";
	
	std::cout << "Allocating again.\n";
	a = new (p) long double;
	b = new (p) (int);
	c = new (p) (long int);	
	
	p.print();
	std::cout << std::endl;	
	
	std::cout << "Freeing a.\n";
	delete a;
	p.print();
	
	std::cout << std::endl;	
	
	std::cout << "Trying do allocate " << sizeof(int) + sizeof ( Tag ) << " bytes in d.\n";
	int *d = new (p) (int);
	p.print();
	
	std::cout << std::endl;
	
	std::cout << "Deleting c.\n";
	delete c;
	p.print();
	
	std::cout << std::endl;
	
	std::cout << "Trying do allocate " << sizeof(int) + sizeof ( Tag ) << " bytes in e.\n";
	int *e = new (p) (int);
	p.print();
	
	std::cout << std::endl;
	
	std::cout << "Deleting d and e.\n";
	delete e;
	p.print();
	delete d;
	p.print();
	
	std::cout << std::endl;
	
	std::cout << "Trying to allocate " << sizeof(long double) + sizeof ( Tag ) << " bytes in a.\n";
	a = new (p) (long double);
	p.print();
	return 0;
}