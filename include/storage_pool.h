/*!
 *  @file storage_pool.h
 *  @brief Classe StoragePool
 *  @copyright Copyright &copy; 2016. Todos os direitos reservados.
 *
 *  Arquivo com a classe do StoragePool
 */

#ifndef STORAGEPOOL_H
#define STORAGEPOOL_H

class StoragePool {
public:

    /**
     * @brief Destrutor do StoragePool
     */
	virtual ~StoragePool (){};
	
	/**
     * @brief Aloca a memória usando o algoritmo First Fit
     * @param size_t Numero de bytes a ser alocado
     * @return Um ponteiro para o início da área alocada
     */
	virtual void * Allocate ( size_t ) = 0;
	
    /**
     * @brief Aloca a memoria usando o algoritmo do Best Fit
     * @param _bytes Numero de bytes a ser alocado
     * @return Um ponteiro para o início da área alocada
     */	
	virtual void * AllocateBest ( size_t ) = 0;

	/**
     * @brief Libera um espaço alocado
     * @param Ponteiro pro início da área a ser desalocada
     */
	virtual void Free ( void * ) = 0;
	
	/**
     * @brief Imprime uma representação da memória
     */		
	virtual void print ( void ) = 0;

};

#endif