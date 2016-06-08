#ifndef MEMPOOL_COMMON_H
#define MEMPOOL_COMMON_H

#include "tag.h"

void * operator new ( size_t bytes , StoragePool & p );

void * operator new[] (size_t bytes , StoragePool & p);

void * operator new ( size_t bytes );

void operator delete ( void * arg ) noexcept;

#include "mempool_common.inl"

#endif