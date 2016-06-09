/*!
 *  @file sl_pool.h
 *  @brief Clase SLPool
 *  @copyright Copyright &copy; 2016. Todos os direitos reservados.
 *
 *  Arquivo com a classe do SLPool
 */

#ifndef SLPOOL_H
#define SLPOOL_H

#include <cmath> //< ceil

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
    /**
     * @brief Construtor do SLPool
     */
	explicit SLPool ( size_t );
	
	/**
     * @brief Destrutor do SLPool
     */
	~SLPool ();
	
	/**
     * @brief Aloca a memória usando o algoritmo First Fit
     * @param size_t Numero de bytes a ser alocado
     * @return Um ponteiro para o início da área alocada
     */
	void * Allocate ( size_t );
	
    /**
     * @brief Aloca a memoria usando o algoritmo do Best Fit
     * @param _bytes Numero de bytes a ser alocado
     * @return Um ponteiro para o inico da área alocada
     */
	void * AllocateBest ( size_t _bytes );

	/**
     * @brief Libera um espaço alocado
     * @param Ponteiro pro início da área a ser desalocada
     */
	void Free ( void * );
	
	/**
     * @brief Imprime uma representação da memória
     */	
	void print ( void );
};

#include "sl_pool.inl"

#endif