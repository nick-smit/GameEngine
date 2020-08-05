#pragma once
#include "pch.h"

#ifdef GE_DEBUG
	#define GE_ASSERT_ENABLED 1
#endif

#ifdef GE_ASSERT_ENABLED

	#define GE_ASSERT(x, ...) { if(!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } };
	#define GE_CORE_ASSERT(x, ...) { if(!(x)) { LOG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } };

#else

	#define GE_ASSERT(x, ...)
	#define GE_CORE_ASSERT(x, ...)

#endif
