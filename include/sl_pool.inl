#include <stdexcept>
#include <new>

SLPool::SLPool ( size_t bytes = 224 ) : mui_NumberOfBlocks (ceil(((float)bytes + sizeof (Header)) / Block::BlockSize)), mp_Pool(new Block[mui_NumberOfBlocks+1]), mr_Sentinel(mp_Pool[mui_NumberOfBlocks]) {

	mp_Pool->mui_Length = mui_NumberOfBlocks; // alternative form: mp_Pool[0].mui_Length = mui_NumberOfBlocks
	mp_Pool->mp_Next = NULL; // alternative form: mp_Pool[0].mp_Next = NULL
	
	mr_Sentinel.mp_Next = mp_Pool; // NEXT label at sentinel receives &mp_Pool[0]

	assert(mp_Pool[mui_NumberOfBlocks].mp_Next == mr_Sentinel.mp_Next);
	if (sizeof(Block::mc_RawArea) == 16) assert(mui_NumberOfBlocks == bytes/16);
	
	/* COUT AREA (to delete later) */
	
	std::cout << "Number of bytes: " << bytes << "\n";
	std::cout << "Number of Blocks: " << mui_NumberOfBlocks << "\n";
	std::cout << "Size of Block::mc_RawArea: " << sizeof(Block::mc_RawArea);
	std::cout << "\nSize of Header: " << sizeof(Header) << "\n";
	std::cout << "Size of Block: " << sizeof(Block::mc_RawArea) + sizeof(Header) << "\n";	
	
}

SLPool::~SLPool() {
	delete [] mp_Pool;
}

void * SLPool::Allocate ( size_t _bytes){
	/* first fit */
	std::cout << "Trying do allocate "<< _bytes << " bytes.\n";
	size_t blocks = ceil((float)_bytes/16);
	
	Block *aux = mr_Sentinel.mp_Next;
	Block *beforeAux = mr_Sentinel.mp_Next;
	
	while (aux != NULL){
		// Quantidade de blocos necessários igual ao tamanho do bloco encontrado
		if (blocks == aux->mui_Length){
			if (beforeAux != aux) beforeAux->mp_Next = aux->mp_Next;
			if (mr_Sentinel.mp_Next == aux) mr_Sentinel.mp_Next = aux->mp_Next;
			return reinterpret_cast < void * > (reinterpret_cast < Header * >( aux )  + 1U);
		}

		// Quantidade de blocos necessários menor do que o tamanho do bloco encontrado
		if (blocks < aux->mui_Length){
			// "Quebrando" o bloco
			Block * part2 = reinterpret_cast < Block * >( aux )  + blocks;
			
			part2->mp_Next = aux->mp_Next;
			aux->mp_Next = part2;

			// Definindo tamanhos
			part2->mui_Length = aux->mui_Length-blocks; // Atualizando tamanho da parte que sobrou
			aux->mui_Length = blocks; // Atualizando tamanho da parte que será enviada
			
			// Associando com o anterior
			// AVISO: Se der algum erro, pode ser por aqui
			if (beforeAux != aux) beforeAux->mp_Next = part2; // Atualizando mp_Next do bloco livre que aponta para o que será enviado
		
			// Atualizando o sentinela, caso o enviado seja o primeiro bloco
			if (mr_Sentinel.mp_Next == aux) mr_Sentinel.mp_Next = part2;
			
			/*
			std::cout << "Size of Header: " << sizeof(Header) << std::endl;
			std::cout << "Before aux: " << beforeAux << "\n";
			std::cout << "Sending "<< aux << "\n";
			std::cout << "After aux: " << beforeAux->mp_Next << "\n";
			std::cout << "Sentinel position: " << mr_Sentinel.mp_Next << "\n";
			*/

			return reinterpret_cast < void * > (reinterpret_cast < Header * >( aux )  + 1U);
		}
		
		// Bloco não encontrado ainda: bola pra frente, tem outros blocos
		beforeAux = aux;
		aux = aux->mp_Next;
	}
	
	throw std::bad_alloc();
	return NULL;
}

void * SLPool::AllocateBest(size_t _bytes){
	std::cout << "Trying do allocate "<< _bytes << " bytes.\n";	
	size_t blocks = ceil((float)_bytes/16);
	
	Block *aux = mr_Sentinel.mp_Next;
	Block *beforeAux = mr_Sentinel.mp_Next;
	Block *best = NULL;
	
	while (best == NULL and aux != NULL){
		// Se encontrar um bloco com tamanho igual, já encontrou o best fit
		if (blocks == aux->mui_Length){
			std::cout << "aehooo." << std::endl;
			if (beforeAux != aux) beforeAux->mp_Next = aux->mp_Next;
			if (mr_Sentinel.mp_Next == aux) mr_Sentinel.mp_Next = aux->mp_Next;
			return reinterpret_cast < void * > (reinterpret_cast < Header * >( aux )  + 1U);			
		} // Se não, procura o primeiro com tamanho maior que o de blocos necessários
		else if (blocks < aux->mui_Length){
			std::cout << "só pode aparecer 1 vez caraio." << std::endl;
			best = aux;
		}
		
		beforeAux = aux;
		aux = aux->mp_Next;		
	}
	std::cout << "saiu da pesquisa" << std::endl;
	// Significa que encontrou algum maior ou igual ou que procurou por todo o vetor e não encontrou.
	if (best == NULL) throw std::bad_alloc();
	std::cout << "encontrou o primeiro menor" << std::endl;

	// Se foi encontrado pelo menos um "best", continua a procura por algum que possa ser menor
	while(aux != NULL){
		std::cout << "???" << std::endl;
		// Se encontrar um com tamanho igual, já encontrou o best fit
		if (blocks == aux->mui_Length){
			if (beforeAux != aux) beforeAux->mp_Next = aux->mp_Next;
			if (mr_Sentinel.mp_Next == aux) mr_Sentinel.mp_Next = aux->mp_Next;
			return reinterpret_cast < void * > (reinterpret_cast < Header * >( aux )  + 1U);			
		} // Se não, procura um com tamanho maior e menor que a do atual best (que foi o primeiro maior que blocks encontrado)
		else if (blocks < aux->mui_Length and aux->mui_Length < best->mui_Length)
			best = aux;
	}
	
	std::cout << "Quebrando!!!!!" << std::endl;
	// Significa que encontrou o menor numero de blocos maior que blocks, já que todos os iguais e "não foi encontrado nenhum" foram processados)
	// "Quebrando" o bloco
	Block * part2 = reinterpret_cast < Block * >( best )  + blocks;
	
	part2->mp_Next = best->mp_Next;
	best->mp_Next = part2;

	// Definindo tamanhos
	part2->mui_Length = best->mui_Length-blocks; // Atualizando tamanho da parte que sobrou
	best->mui_Length = blocks; // Atualizando tamanho da parte que será enviada
	
	// Associando com o anterior
	// AVISO: Se der algum erro, pode ser por aqui
	if (beforeAux != best) beforeAux->mp_Next = part2; // Atualizando mp_Next do bloco livre que aponta para o que será enviado

	// Atualizando o sentinela, caso o enviado seja o primeiro bloco
	if (mr_Sentinel.mp_Next == best) mr_Sentinel.mp_Next = part2;
	
	/*
	std::cout << "Size of Header: " << sizeof(Header) << std::endl;
	std::cout << "Before aux: " << beforeAux << "\n";
	std::cout << "Sending "<< aux << "\n";
	std::cout << "After aux: " << beforeAux->mp_Next << "\n";
	std::cout << "Sentinel position: " << mr_Sentinel.mp_Next << "\n";
	*/

	return reinterpret_cast < void * > (reinterpret_cast < Header * >( best )  + 1U);
}

void SLPool::Free ( void * ptReserved ){
	Block * ptBlockReserved = reinterpret_cast < Block * > (reinterpret_cast < Header * > (ptReserved) - 1U);
	Block * ptPrevReserved = &mr_Sentinel;
	Block * ptPostReserved = mr_Sentinel.mp_Next;
	
	//std::cout << ptReserved << std::endl;
	//std::cout << ptPostReserved << std::endl;
	
	while (ptPostReserved != NULL and ptPostReserved->mp_Next < ptBlockReserved){
		ptPrevReserved = ptPostReserved;
		ptPostReserved = ptPostReserved->mp_Next;
	}
	
	if (ptPostReserved == NULL){
		std::cout << "Liberando área sem coisas adjacentes.\n";
		ptBlockReserved->mp_Next = ptPostReserved;
		ptPrevReserved->mp_Next = ptBlockReserved;
	} else ptPostReserved = ptPostReserved->mp_Next;
	
	// Não faço ideia do q to fazendo, sao 03:43 da manha ne
	//ptBlockReserved->mp_Next = ptPostReserved;
	//ptPrevReserved->mp_Next = ptBlockReserved;
	
	if (ptPrevReserved == &mr_Sentinel) ptPrevReserved = mr_Sentinel.mp_Next;
	
	
	std::cout << ptPrevReserved << std::endl;
	std::cout << ptReserved << std::endl;
	std::cout << ptPostReserved << std::endl;
	
	std::cout << ptBlockReserved << std::endl;
	std::cout << ptBlockReserved+ptBlockReserved->mui_Length << std::endl;
	std::cout << ptBlockReserved-ptPrevReserved->mui_Length << std::endl;
	
	// SÓ FALTA AJEITAR AS COLAGENS DOS BLOCOS DE ACORDO COM CADA VERSÃO ABAIXO:
	
	if(ptBlockReserved-ptPrevReserved->mui_Length == ptPrevReserved and ptBlockReserved+ptBlockReserved->mui_Length != ptPostReserved){
		std::cout << "fuck ya\n";
		ptBlockReserved->mp_Next = ptPostReserved;
		ptPrevReserved->mp_Next = ptBlockReserved;
	}
	
	if(ptBlockReserved-ptPrevReserved->mui_Length != ptPrevReserved and ptBlockReserved+ptBlockReserved->mui_Length == ptPostReserved){
		std::cout << "will it work?\n";
		ptBlockReserved->mp_Next = ptPostReserved;
		ptPrevReserved->mp_Next = ptBlockReserved;			
	}
	
	if(ptBlockReserved-ptPrevReserved->mui_Length == ptPrevReserved and ptBlockReserved+ptBlockReserved->mui_Length == ptPostReserved){
		std::cout << "or not?\n";
		ptBlockReserved->mp_Next = ptPostReserved;
		ptPrevReserved->mp_Next = ptBlockReserved;
	}
	/*
	if ((ptBlockReserved-ptBlockReserved->mui_Length-ptPrevReserved->mui_Length) == ptPrevReserved and (ptBlockReserved+ptBlockReserved->mui_Length) == ptPostReserved){
		std::cout << "Liberando área com duas áreas adjacentes.\n";
	}
	
	if ((ptBlockReserved-ptPrevReserved->mui_Length-1) == ptPrevReserved and (ptBlockReserved+ptBlockReserved->mui_Length+1) != ptPostReserved){
		std::cout << "Liberando área com área adjacentes à esquerda.\n";
	}
	
	if ((ptBlockReserved-ptPrevReserved->mui_Length-1) != ptPrevReserved and (ptBlockReserved+ptBlockReserved->mui_Length+1) == ptPostReserved){
		std::cout << "Liberando área com área adjacentes à direita.\n";
	}
	*/
	std::cout << "Teste\n";
	
}

void SLPool::print (){
	Block *aux = mp_Pool;
	while(aux != NULL){
		std::cout << "[";
		std::cout << "]";
		aux = aux->mp_Next;
	}
}

void SLPool::view() {
	//	std::cout << mr_Sentinel.mp_Next;
    auto *pt = mr_Sentinel.mp_Next;
    auto pos = 0u;
    while (pos < mui_NumberOfBlocks) {
        auto j = (mp_Pool + pos)->mui_Length;
        pos   += j;
        if (mp_Pool + pos - j == pt) {
            while (j-- > 0) std::cout << "[] ";
            pt = pt->mp_Next;
        } else {
            std::cout << "[" << std::string(j, '#') << "] ";
        }
    }
    std::cout << "\n";
}