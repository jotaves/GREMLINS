#include <cmath>

SLPool::SLPool ( size_t bytes = 224 ) {
	// I have no idea what I'm doing, please ignore. I'll try another day.
	mui_NumberOfBlocks = ceil((bytes + sizeof (Header)) / Block::BlockSize);

	Block block;

	block.mui_Length = mui_NumberOfBlocks-1;

	mp_Pool = &block;

	mr_Sentinel.mp_Next = mp_Pool;

	//flist.push_back(mr_Sentinel);

	//flist.push_front(mp_Pool);

	//flist.push_back(mp_Pool);

	std::cout << "Number of bytes: " << bytes << "\n";
	std::cout << "Number of Blocks: " << mui_NumberOfBlocks << "\n";
	std::cout << "Size of Block::mc_RawArea: " << sizeof(Block::mc_RawArea);
	std::cout << "\nSize of Header: " << sizeof(Header) << "\n";
	std::cout << "Size of Block: " << sizeof(Block::mc_RawArea) + sizeof(Header) << "\n";	
}

SLPool::~SLPool() {
}

void * SLPool::Allocate ( size_t ){
	return 0;
}

void SLPool::Free ( void * ){

}