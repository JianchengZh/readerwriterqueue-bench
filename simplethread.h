#pragma once

#include <utility>
#include <type_traits>


struct ThreadRef;

class SimpleThread
{
private:
	template<typename TCallback>
	struct CallbackWrapper
	{
		CallbackWrapper(TCallback&& callback)
			: callback(std::forward<TCallback>(callback))
		{
		}

		static void callAndDelete(void* wrapper)
		{
			auto typedWrapper = static_cast<CallbackWrapper*>(wrapper);
			typedWrapper->callback();
			delete typedWrapper;
		}

		typename std::decay<TCallback>::type callback;
	};
	
	typedef void (*CallbackFunc)(void*);

	void startThread();


public:
	static const int StackSize = 4 * 1024;	// bytes


	template<typename TCallback>
	SimpleThread(TCallback&& callback)
	{
		auto wrapper = new CallbackWrapper<TCallback>(std::forward<TCallback>(callback));
		callbackObj = wrapper;
		callbackFunc = &CallbackWrapper<TCallback>::callAndDelete;
		startThread();
	}

	~SimpleThread();

	void join();

	// Disable copying and assignment (undefined on purpose)
	SimpleThread(SimpleThread const&);
	SimpleThread& operator=(SimpleThread const&);

private:
	ThreadRef* thread;
	friend struct ThreadRef;

	void* callbackObj;
	CallbackFunc callbackFunc;
};
