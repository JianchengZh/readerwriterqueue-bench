#pragma once

#if defined(_WIN32)
#define ST_WINDOWS
#elif defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__) || defined(BSD)
#define ST_NIX
#else
#error "Unknown platform"
#endif

#if defined(ST_WINDOWS)
typedef unsigned long long SystemTime;
#elif defined(ST_NIX)
#include <time.h>
typedef timespec SystemTime;
#endif

namespace moodycamel
{
void sleep(int milliseconds);

SystemTime getSystemTime();

// Returns the delta time, in milliseconds
double getTimeDelta(SystemTime start);
}
