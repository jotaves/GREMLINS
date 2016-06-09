/*!
 *  @mainpage GREMLINS
 *  @author João Victor Bezerra Barboza
 *	@author Carlos Vinicius Fernandes Rodrigues
 *  @date Junho, 2016
 *  @copyright Copyright &copy; 2016. Todos os direitos reservados.
 *  @version 1.0
 *
 *  @file gremlins_drive.cpp
 *  @brief Arquivo do drive
 *
 *	Arquivo com os testes das funções implementadas
 */

#include <iostream> //< io
#include <chrono> //< std::chrono
#include <random> //< std::random_device
#include <queue> //< std::priority_queue

#include "sl_pool.h"
#include "event.h"

/**
 * @brief Função para gerar um valor aleatório de tempo
 * @return Valor aleatório de tempo
 */
std::time_t getRandomTimeInterval(){
	std::random_device generator;
	std::uniform_int_distribution<std::time_t> distribution(100, 2000);
	
	return distribution(generator);
}

/**
 * @brief Função para gerar um valor aleatório de tamanho
 * @return Valor aleatório de tamanho
 */
std::size_t getRandomForSize(){
	std::random_device generator;
	std::uniform_int_distribution<int> distribution(1, 100);
	
	return distribution(generator);
}

/**
 * @brief Função que testa a Pool
 * @param _pool A pool que deverá ser testada
 * @param _timeLimit O tempo limite
 */
void StoragePoolTest(StoragePool& _pool, std::time_t _timeLimit ){
	std::random_device rd;
	// [1] Setup random numbers generator for memory size , say [100 ,2000] bytes .
	// [2] Setup random numbers generator for time intervals , say [1 ,100] units .
	// [3] Create the pirority queue std :: priority_queue ‘pq ’ and
	// insert some events comprising the simulation .
	// Assuming there is a class Event that creates a pair address /time - stamp .
	std::priority_queue <Event> pq;
	
	// Run simulation fot the time set by the client .	
		for ( std::time_t t( 0 ) ; t < _timeLimit ; ++t ){
			while( !pq.empty() ){ // Run while we have events pending or time to run.
				Event ev = pq.top(); // Access the event with the smallest time - stamp .
				if ( ev.getTimeStamp() > t ) break; // Still some time left ....
				// When we got here , the top event has run out of time .
				pq.pop(); // Remove event from priority queue .
				_pool.Free( ev.getMemoryPtr() ); // Calling free operator .
				
			}
			 auto memSize = getRandomForSize();
			 void* const add = _pool.Allocate( memSize );
			 auto elapsedTime = getRandomTimeInterval();
			 std::time_t releaseTime = t + elapsedTime; // Set time stamp some time from now.
			 pq.push( Event( add, releaseTime ) ); // Creating a new simulation event .
			_pool.print();
			
		}
	// Here you might want to show the memory map on the screen ,
	// or write it to a log file , for debugging purpose .
}

int main (void){
	SLPool q (1024);

	std::cout << "Testing Allocate.\n";
	//auto start = std::chrono::steady_clock::now();
	StoragePoolTest(q, 12);
	//auto end = std::chrono::steady_clock::now();
	//auto diff = end - start;
	//std::cout <<  std::chrono::duration <double, std::milli> (diff).count() << "\n";

	std::cout << "\nTesting SLPool for every 'delete permutation' of a, b and c.\n";
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
	
	delete a;
	delete b;
	std::cout << "\nDeleting a and b.\n";
	p.print();
	return 0;
}