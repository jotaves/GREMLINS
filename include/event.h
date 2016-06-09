/*!
 *  @file event.h
 *  @brief Classe Event
 *  @copyright Copyright &copy; 2016. Todos os direitos reservados.
 *
 *  Arquivo com a classe Event
 */

#ifndef EVENT_H
#define EVENT_H

class Event{
public:

    /**
     * @brief Construtor de Event
     * @param _add Um ponteiro
     * @param _releaseTime Marcador de tempo
     */
    Event( void * _add, std::time_t _releaseTime ){
        add = _add;
        releaseTime = _releaseTime;
    }
    
    /**
     * @brief Pega o marcador de tempo de Event
     * @return O marcador de tempo
     */
    std::time_t getTimeStamp(){
        return releaseTime;
    }
    
    /**
     * @brief Pega o ponteiro
     * @return O ponteiro
     */
    void * getMemoryPtr(){
        return &add;
    }
    
    /**
     * @brief Sobrepõe o operador <
     * @param Um Event
     * @return True, se o tempo do Event por parâmetro for maior que o do da classe. False se não.
     */
    bool operator < (const Event add) const{
        return releaseTime < add.releaseTime;
    }
    
private:
    std::time_t releaseTime; //< Tempo
    void * add; //< Ponteiro para o local alocado
};

#endif