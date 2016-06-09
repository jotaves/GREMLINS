# GREMLINS
GeREnciador de Memória com LIsta eNcadeada Simples

## Sobre
**G**e**RE**nciador de **M**emória com **LI**sta e**N**cadeada **S**imples ou GREMLINS é um gerenciador
de memória que apartir de um bloco de memória faz as devidas partições, o gerenciando, para entregar blocos
menores de acordo com o solicitado.

## Visualização
A visualização dos espaços da memória são feitas através dos seguintes símbolos:

**<>**: Espaço vazio (cada <> é um bloco);

**<!>**: Espaço alocado (a quantidade de ! indica a quantidade de blocos alocados nesse espaço);

**[]**: O que estiver dentro de [] faz parte de um elemento da lista encadeada de espaços livres.

Alguns exemplos:
```
[<><><><>] -> A lista encadeada possui 1 elemento, nesse único elemento, há 4 blocos livres
<!>[<><><>] -> A lista encadeada possui 1 elemento. Nesse único elemento, há 3 blocos livres. Um bloco foi alocado (o primeiro).
<!>[<>]<!>[<>] -> A lista encadeada possui 2 elementos. Cada elemento possui 1 bloco livre. Dois blocos foram alocados (o primeiro e o terceiro)
```
A necessidade da representação [] se dá para confirmar que, ao liberar todos os blocos alocados, a lista encadeada volte à situação inicial, em que possui 1 elemento:

```
[<><><><>] -> Situação inicial

[<>]<!>[<><>] -> Possível situação durante o uso

[<>][<>][<><>] -> Situação final incorreta (em que a memória está fragmentada em três partes)

[<><><><>] -> Situação final correta (em que os blocos foram mesclados)
```

## Testes
A partir dos testes realizados, não foi encontrado erro no GREMLINS.

## Compilando
Através do terminal, entre no diretório do projeto e digite:

`make best` ou
`g++ -Wall -std=c++11 src/gremlins_drive.cpp -o bin/drive -I include/ -D BEST` para compilar utliziando o Allocate Best-fit;

`make first` ou `g++ -Wall -std=c++11 src/gremlins_drive.cpp -o bin/drive -I include/` para compilar o utilizando o Allocate First-fit;

`make mlfull` ou `valgrind --leak-check=full --show-leak-kinds=all ./bin/drive` para realizar teste de vazamento de memória.

## Executando
Através do terminal, entre no diretório do projeto e digite:

`make run` ou `./bin/drive` para executar os testes com o que foi compilado.

## Autores
- Carlos Vinicius Fernandes Rodrigues
- João Victor Bezerra Barboza

## (Emotional) Support/Mana Provider
```cpp
#ifndef MAIN_CPP // Just kidding (inside joke)
#define MAIN_CPP // #SomosTodosNalbert

#include <iostream>
#include <random>

int main(int argc, const char *argv[]) {
    std::string surname[2] = {"Viana", "Vieira"};
    std::random_device r;
    
    std::cout << "Elton " << surname[r()%2] << std::endl;
}

#endif
```
