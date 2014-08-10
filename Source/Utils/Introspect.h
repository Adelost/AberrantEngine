#pragma once

#include "ClassInfo.h"

#define INTROSPECT(NAME, MEMBERS) \
ClassInfo& introspect() \
{ \
	static ClassInfo info; \
	info._setTarget(this); \
	if (!info._hasInit()) \
	{ \
		info._init(NAME); \
		MEMBERS \
	} \
	return info; \
}

#define MEMBER(TYPE, VAR) \
	info._add(TYPE, &VAR, #VAR);

/// Allows introspection of subclasses.

class Introspect
{
public:
	virtual INTROSPECT("Unkown",)
};