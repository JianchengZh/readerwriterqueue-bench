#include "simplethread.h"

#if defined(_MSC_VER) || defined(__INTEL_COMPILER)
#include <windows.h>

struct ThreadRef
{
	HANDLE handle;

	static DWORD WINAPI ThreadProc(LPVOID param)
	{
		auto simpleThread = static_cast<SimpleThread*>(param);
		simpleThread->callbackFunc(simpleThread->callbackObj);
		return 0;
	}
};

void SimpleThread::startThread()
{
	thread = new ThreadRef;
	thread->handle = CreateThread(NULL, StackSize, &ThreadRef::ThreadProc, this, 0, NULL);
}

void SimpleThread::join()
{
	if (thread->handle != NULL) {
		WaitForSingleObject(thread->handle, INFINITE);
		CloseHandle(thread->handle);
		thread->handle = NULL;
	}
}
#else
#include <thread>

struct ThreadRef
{
	std::thread thread;

	static void threadProc(SimpleThread* simpleThread)
	{
		simpleThread->callbackFunc(simpleThread->callbackObj);
	}
};

void SimpleThread::startThread()
{
	thread = new ThreadRef;
	thread->thread = std::thread(&ThreadRef::threadProc, this);
}

void SimpleThread::join()
{
	if (thread->thread.joinable()) {
		thread->thread.join();
	}
}
#endif

SimpleThread::~SimpleThread()
{
	join();
	delete thread;
}
