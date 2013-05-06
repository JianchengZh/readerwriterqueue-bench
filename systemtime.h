#pragma once

#if defined(_MSC_VER)
#define ST_WINDOWS
#elif defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__) || defined(BSD)
#define ST_NIX
#endif

void sleep(int milliseconds);

#if defined(ST_WINDOWS)
typedef unsigned __int64 SystemTime;
#elif defined(ST_NIX)
#include <time.h>
typedef timespec SystemTime;
#endif

SystemTime getSystemTime();

// Returns the delta time, in milliseconds
double getTimeDelta(SystemTime start);
