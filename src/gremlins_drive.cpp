// g++ -Wall -std=c++11 src/gremlins_drive.cpp -o bin/drive -I include/

#include <iostream>

#include "sl_pool.h"


int main (void){
	SLPool p(64);
	p.view();
	long double *a = new (p) long double;
	p.view();
	int *b = new (p) (int);
	p.view();	
	int *c = new (p) (int);
	p.view();
	long int *d = new (p) (long int);
	p.view();
	
	delete c;

	p.view();
	
	delete d;
	
	p.view();
	
	delete a;
	
	p.view();
	
	delete b;
	
	p.view();
	
	return 0;
}