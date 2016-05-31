#ifndef SLPOOL_H
#define SLPOOL_H

#include <iostream>

#include "storage_pool.h" // Initialize class storage pool
#include "tag.h"		// Initialize struct tag
#include "mempool_common.h" // Initialize operators new and delete
#include "forward_list.h"

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
	Block mr_Sentinel; // ! < End of the list .
	Forward_list <Block> flist;

public:
	explicit SLPool ( size_t );
	
	~SLPool ();

	void * Allocate ( size_t );

	void Free ( void * );
};

#include "sl_pool.inl"

#endif