#pragma once

// Make sure code is only run in debug

#ifdef _DEBUG
#define DEBUG_ONLY(CODE) {CODE}
#else
#define DEBUG_ONLY(CODE) {}
#endif