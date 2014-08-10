#include "Memory.h"

#include <cstring> // memcpy


void Memory::copy(const void* src, void* dst, int size)
{
	memcpy(dst, src, size);
}
