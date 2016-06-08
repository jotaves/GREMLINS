#include <stdexcept>
#include <new>

SLPool::SLPool ( size_t bytes = 224 ) : mui_NumberOfBlocks (ceil(((float)bytes + sizeof (Header)) / Block::BlockSize)), mp_Pool(new Block[mui_NumberOfBlocks+1]), mr_Sentinel(mp_Pool[mui_NumberOfBlocks]) {

	mp_Pool->mui_Length = mui_NumberOfBlocks; // alternative form: mp_Pool[0].mui_Length = mui_NumberOfBlocks
	mp_Pool->mp_Next = nullptr; // alternative form: mp_Pool[0].mp_Next = nullptr
	
	mr_Sentinel.mp_Next = mp_Pool; // NEXT label at sentinel receives &mp_Pool[0]

	assert(mp_Pool[mui_NumberOfBlocks].mp_Next == mr_Sentinel.mp_Next);
	if (sizeof(Block::mc_RawArea) == 16) assert(mui_NumberOfBlocks == bytes/16);
	
	/* COUT AREA (to comment later) */
	/*
	std::cout << "Number of bytes: " << bytes << "\n";
	std::cout << "Number of Blocks: " << mui_NumberOfBlocks << "\n";
	std::cout << "Size of Block::mc_RawArea: " << sizeof(Block::mc_RawArea);
	std::cout << "\nSize of Header: " << sizeof(Header) << "\n";
	std::cout << "Size of Block: " << sizeof(Block::mc_RawArea) + sizeof(Header) << "\n";
	*/
}

SLPool::~SLPool() {
	delete [] mp_Pool;
}

void * SLPool::Allocate ( size_t _bytes){
	/* first fit */
	size_t blocks = ceil((float)_bytes/16);
	
	//std::cout << "Trying do allocate "<< blocks << " block(s).\n";
	
	Block *aux = mr_Sentinel.mp_Next;
	Block *beforeAux = mr_Sentinel.mp_Next;
	
	while (aux != nullptr){
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
			// Esse if é só pra não fazer o processo novamente no caso em que aux == beforeAux, já que já foi feito "aux->mp_Next = part2"
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
		
		// Bloco não encontrado ainda
		beforeAux = aux;
		aux = aux->mp_Next;
	}
	
	throw std::bad_alloc();
	return nullptr;
}

void * SLPool::AllocateBest(size_t _bytes){
	size_t blocks = ceil((float)_bytes/16);
	
	Block *aux = mr_Sentinel.mp_Next;
	Block *beforeAux = mr_Sentinel.mp_Next;
	Block *best = nullptr;
	
	while (best == nullptr and aux != nullptr){
		// Se encontrar um bloco com tamanho igual, já encontrou o best fit
		if (blocks == aux->mui_Length){
			//std::cout << "aehooo." << std::endl;
			if (beforeAux != aux) beforeAux->mp_Next = aux->mp_Next;
			if (mr_Sentinel.mp_Next == aux) mr_Sentinel.mp_Next = aux->mp_Next;
			return reinterpret_cast < void * > (reinterpret_cast < Header * >( aux )  + 1U);			
		} // Se não, procura o primeiro com tamanho maior que o de blocos necessários
		else if (blocks < aux->mui_Length){
			//std::cout << "só pode aparecer 1 vez." << std::endl;
			best = aux;
		}
		
		beforeAux = aux;
		aux = aux->mp_Next;		
	}
	//std::cout << "saiu da pesquisa" << std::endl;
	// Significa que encontrou algum maior ou igual ou que procurou por todo o vetor e não encontrou.
	if (best == nullptr) throw std::bad_alloc();
	//std::cout << "encontrou o primeiro menor" << std::endl;

	// Se foi encontrado pelo menos um "best", continua a procura por algum que possa ser menor
	while(aux != nullptr){
		//std::cout << "???" << std::endl;
		// Se encontrar um com tamanho igual, já encontrou o best fit
		if (blocks == aux->mui_Length){
			if (beforeAux != aux) beforeAux->mp_Next = aux->mp_Next;
			if (mr_Sentinel.mp_Next == aux) mr_Sentinel.mp_Next = aux->mp_Next;
			return reinterpret_cast < void * > (reinterpret_cast < Header * >( aux )  + 1U);			
		} // Se não, procura um com tamanho maior e menor que a do atual best (que foi o primeiro maior que blocks encontrado)
		else if (blocks < aux->mui_Length and aux->mui_Length < best->mui_Length)
			best = aux;
	}
	
	//std::cout << "Quebrando!!!!!" << std::endl;
	// Significa que encontrou o menor numero de blocos maior que blocks, já que todos os iguais e "não foi encontrado nenhum" foram processados)
	// "Quebrando" o bloco
	Block * part2 = reinterpret_cast < Block * >( best )  + blocks;
	
	part2->mp_Next = best->mp_Next;
	best->mp_Next = part2;

	// Definindo tamanhos
	part2->mui_Length = best->mui_Length-blocks; // Atualizando tamanho da parte que sobrou
	best->mui_Length = blocks; // Atualizando tamanho da parte que será enviada
	
	// Associando com o anterior
	// Esse if é só pra não fazer o processo novamente no caso em que aux == beforeAux, já que já foi feito "aux->mp_Next = part2"
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
	bool a = false;
	Block * ptBlockReserved = reinterpret_cast < Block * > (reinterpret_cast < Header * > (ptReserved) - 1U);
	Block * ptPrevReserved = &mr_Sentinel;
	Block * ptPostReserved = mr_Sentinel.mp_Next;
	
	//std::cout << "Freeing " << ptBlockReserved->mui_Length  << " block(s).\n";
	
	while (ptPostReserved != nullptr and ptPostReserved <= ptBlockReserved){
		ptPrevReserved = ptPostReserved;
		ptPostReserved = ptPostReserved->mp_Next;
	}
	
	/*
	std::cout << ptPrevReserved << std::endl;
	std::cout << ptBlockReserved << std::endl;
	std::cout << ptPostReserved << std::endl;
	
	std::cout << ptBlockReserved+ptBlockReserved->mui_Length << std::endl;
	std::cout << ptBlockReserved-ptPrevReserved->mui_Length << std::endl;
	*/
	
	// Precede uma área livre
	if (ptBlockReserved+ptBlockReserved->mui_Length == ptPostReserved){
		if (ptBlockReserved-ptPrevReserved->mui_Length == ptPrevReserved) a = true;
		//std::cout << "Precede uma área livre.\n";
		ptBlockReserved->mp_Next = ptPostReserved->mp_Next;
		
		ptBlockReserved->mui_Length += ptPostReserved->mui_Length;
		ptPostReserved->mui_Length = 0;
	}
	else{
		//std::cout << "Não precede uma área livre.\n";
		ptBlockReserved->mp_Next = ptPostReserved;
	}	
	
	// Segue uma área livre
	if (ptBlockReserved-ptPrevReserved->mui_Length == ptPrevReserved){
		//std::cout << "Segue uma área livre.\n";
		ptPrevReserved->mui_Length += ptBlockReserved->mui_Length;
		ptBlockReserved->mui_Length = 0;
		
		if (a) ptPrevReserved->mp_Next = ptPostReserved->mp_Next; // caso especial
	}
	else{
		//std::cout << "Não segue uma área livre.\n";
		ptPrevReserved->mp_Next = ptBlockReserved;
	}
}

void SLPool::print (){
	Block *aux = mr_Sentinel.mp_Next;
	auto c(0u);
	
	// Se a lista não for vazia.
	if (aux != nullptr){
		while (aux != nullptr){
			// Se houver algo antes de aux, primeiro imprime o que está antes.
			if (aux > mp_Pool+c){
				while(aux > mp_Pool+c){
					std::cout << "<";
					for(auto i(0u); i < ((mp_Pool+c)->mui_Length); i++)
						std::cout << "!";
					std::cout << ">";
					c += (mp_Pool+c)->mui_Length;
				}
			}
			
			// Agora imprime o que está no aux (lista de espaços não-alocados)
			std::cout << "[";
			for(auto i(0u); i < aux->mui_Length; i++){
				std::cout << "<>";
				c++;
			}
			std::cout << "]";
			
			aux = aux->mp_Next;
		}
	}
	
	// Se o aux for menor que o mp_Pool, ou seja, não tiver impresso a lista completa ou a lista de espaços não-alocados for vazia.
	if (aux < mp_Pool+mui_NumberOfBlocks){
		// Imprime o restante da lista.
		while (c < mui_NumberOfBlocks){
			std::cout << "<";
			for(auto i(0u); i < ((mp_Pool+c)->mui_Length); i++)
				std::cout << "!";
			std::cout << ">";
			c += (mp_Pool+c)->mui_Length;
		}
	}
		
	std::cout << std::endl;
}