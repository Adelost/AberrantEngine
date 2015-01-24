#pragma once

#include "PoolArrayBase.h"
#include "StableArray.h"

namespace ae
{
/** A pool array in which allocated elements can be safely referenced.
	Similarly to a StaableArray, elements do not change memory address
	when growing. */
template <class T>
using StablePoolArray = PoolArrayBase<T, StableArray<T>>;
}