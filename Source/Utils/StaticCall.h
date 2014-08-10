#pragma once

// Allows code to be called automatically during the start
// of the program. Only to be used in .cpp

#define STATIC_CALL(CODE) \
namespace \
{ \
	class StaticCall \
	{ \
	public: \
		StaticCall() \
		{ \
			CODE \
		} \
	}; \
	StaticCall _staticCall; \
}