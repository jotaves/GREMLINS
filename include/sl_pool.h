#ifndef SLPOOL_H
#define SLPOOL_H

#include <cmath>
#include <cassert>

#include "storage_pool.h"
#include "mempool_common.h"

class SLPool : public StoragePool {
public:
	struct Header {
		unsigned int mui_Length;
		Header () : mui_Length ( 0u ) { /* Empty */ };
	};

	struct Block : public Header {
		enum { BlockSize = 16 }; // Each block has 16 bytes .
		union {
			Block * mp_Next;
			char mc_RawArea [ BlockSize - sizeof ( Header ) ];
		};
		Block () : Header () , mp_Next ( nullptr ) { /* Empty */ };
	};

private:
	unsigned int mui_NumberOfBlocks; // ! < Number of blocks in my SLPool
	Block * mp_Pool; // ! < Head of list .
	Block & mr_Sentinel; // ! < End of the list .

public:
	explicit SLPool ( size_t );
	
	~SLPool ();

	void * Allocate ( size_t );

	void Free ( void * );
	
	void print ();
	
	void view();
	
	void * AllocateBest(size_t _bytes);	
};

#include "sl_pool.inl"

#endif