/**
 *  @file mempool_common.h
 *  @brief Implementação dos operadores new e delete
 *  @copyright Copyright &copy; 2016. Todos os direitos reservados.
 *  @author Selan Rodrigues dos Santos
 *  @author Carlos Vinicius Fernandes Rodrigues
 *  @author João Victor Bezerra Barboza
 *  Arquivo com a classe SLPool
 */

#ifndef MEMPOOL_COMMON_H
#define MEMPOOL_COMMON_H

#include "tag.h"

/**
 * @brief Sobrecarrega o operador new
 * @param bytes Numero de bytes a ser alocado
 * @param p Referência para a Pool utilizada
 * @return Ponteiro para o início da área alocada
 */
void * operator new ( size_t bytes , StoragePool & p );

/**
 * @brief Sobrecarrega o operador new[]
 * @param bytes Numero de bytes a ser alocado
 * @param p Referência para a Pool utilizada
 * @return Ponteiro para o início da área alocada
 */
void * operator new[] (size_t bytes , StoragePool & p);

/**
 * @brief Sobrecarrega o operador new
 * @param bytes Numero de bytes a ser alocado
 * @return Ponteiro para o início da área alocada
 */
void * operator new ( size_t bytes );

/**
 * @brief Sobrecarrega o operador delete
 * @param bytes Ponteiro para o início da área alocada
 */
void operator delete ( void * arg ) noexcept;

#include "mempool_common.inl"

#endif