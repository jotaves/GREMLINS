#ifndef STORAGEPOOL_H
#define STORAGEPOOL_H

class StoragePool {
public:

	virtual ~StoragePool (){};

	virtual void * Allocate ( size_t ) = 0;
	
	virtual void * AllocateBest ( size_t ) = 0;

	virtual void Free ( void * ) = 0;
	
	virtual void print ( void ) = 0;

};

#endif