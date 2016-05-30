/*!
 *  @file Forward_list.h
 *  @brief Forward List ADT
 *  @copyright Copyright &copy; 2016. Todos os direitos reservados.
 *
 *  Arquivo que contêm a foward list
 */


#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <stdexcept>

using size_type = int;

template < typename T >
class Forward_list{
	private:
	struct Node {        //!< Struct para um nó de lista encadeada
		T data;        //!< Armazena os interios da lista
		Node *next;  //!< Aponta para o poróximo nó da lista
 	 	Node( const T & d = T(), Node *n = nullptr) : data (d), next (n){/* Empty */}
	};
	
	size_type m_size;
	Node *m_head;
	Node *m_tail;

public:
	/* Iterators */
	class const_iterator{
		public:
			const_iterator();
			/** 
	     	 * @brief Sobrecarrega o operador *
	     	 * @return O elemento na posição 
	     	 */
			const T & operator* () const;
			
			 /**
		      * @brief Sobrecarrega o operador ++
		      * @return O iterador incrementado
		      */
			const_iterator & operator++ ();
			
			 //it++
			 /**
		      * @brief Sobrecarrega o operador ++
		      * @return O iterador antes de ser incrementado
		      */
			const_iterator operator++ (int);
			
			 //--it
			 /**
		      * @brief Sobrecarrega o operador --
		      * @return O iterador decrementado
		      */
			const_iterator & operator-- ();
			
			 //it--
			 /**
		      * @brief Sobrecarrega o operador --
		      * @return O iterador antes de ser decrementado
		      */
			const_iterator operator-- (int);
			
			/**
		     * @brief Sobrecarrega o operador ==
		     * @param rhs Iterador a ser comparado
		     * @return True, se for igual ao iterador, falso se não
		     */
			bool operator == (const const_iterator & rhs) const;
			
			/**
		     * @brief Sobrecarrega o operador !=
		     * @param rhs Iterador a ser comparado
		     * @return True, se for diferente do iterador, falso se não
		     */
			bool operator != (const const_iterator & rhs) const;
			
		private:
			Node *p = nullptr;
			const_iterator (Node *_p) : p(_p){/* Empty */}
			friend class Forward_list<T>;
		};

		class iterator: public const_iterator{
		public:
			iterator() : const_iterator(){/* Empty */}
			
			T & operator * (){
				return const_iterator::p->data;
			}
			
		protected:
			iterator (Node *_p = nullptr) : const_iterator(_p){/* Empty */}
			friend class Forward_list<T>;
		};

	/* Common functions */		
	
	/**
 	 * @brief Construtor Foward List
 	 */
	Forward_list ();
	
	/**
 	 * @brief Destrutor Foward List
 	 */
	~Forward_list();
	
	/**
 	 * @brief Retorna o tamanho atual da lista
 	 * @return Tamanho da lista
 	 */
	size_type size() const;
	
	/**
     * @brief Remove todos os elementos do container
     */
	void clear();
	
	/**
     * @brief Verifica se o container possui elementos
     * @return True se estiver vazio, caso contrário, false
     */
	bool empty();
	
	/**
     * @brief Adiciona um valor ao final da lista
     * @param x é o elemento à ser movido
     */
	void push_back( const T & x );
	
	/**
 	 * @brief Retira um elemento do fim da lista
 	 * @return O elemento retirado
 	 */
	T pop_back();
	
	T & back ();
	
	const T & back() const;
	
	/**
     * @brief Substitui os elementos da lista por um determinado valor
     * @param x, valor para ser usado na substituição
     */
	void assign( const T & x );
	
	// Exclusive
	
	/**
     * @brief Adiciona um valor ao começo da lista
     * @param x é o elemento à ser movido
     */
	void push_front( const T & x );
	
	/**
 	 * @brief Retira um elemento da frente da lista
 	 * @return O elemento retirado
 	 */
	T pop_front();
	
	T & front ();

	/**
 	 * @brief Retorna o elemento na frente da lista
 	 * @return O elemento retirado
 	 */
	const T & front () const;


	/* Return iterators */	
	
	/**
     * @brief Retorna um const_iterator para o primeiro elemento do vector
     * @return Um const_iterator apontando para o primeiro elemento do vector
     */
    const_iterator cbegin() const;
    
    /**
     * @brief Retorna um const_iterator para o ponto final da lista
     * @return Um const_iterator apontando para o ponto final na lista
     */
    const_iterator cend() const;
    
    /**
     * @brief Retorna um iterator para o primeiro elemento do vector
     * @return Um iterator apontando para o primeiro elemento do vector
     */
    iterator begin() const;
    
    /**
     * @brief Retorna um iterator para o ponto final da lista
     * @return Um iterator apontando para o ponto final na lista
     */
    iterator end() const;	
};

#include "forward_list.inl"

#endif