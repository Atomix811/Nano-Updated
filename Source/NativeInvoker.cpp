//NativeInvoker.cpp
#include "stdafx.h"

extern "C" void		_call_asm(void* context, void* function, void* ret);
static NativeManagerContext g_context;

static UINT64 g_hash;

void(*scrNativeCallContext::SetVectorResults)(scrNativeCallContext*) = nullptr;

void nativeInit(UINT64 hash) {

	g_context.Reset();
	g_hash = hash;
}

void nativePush64(UINT64 value) {

	g_context.Push(value);
}

uint64_t * nativeCall() {

	auto fn = Hooking::GetNativeHandler(g_hash);

	if (fn != 0) {

		static void* exceptionAddress;

		__try
		{
			//fn(&g_context); // Old One
			_call_asm(&g_context, fn, Hooking::m_native_return);
			scrNativeCallContext::SetVectorResults(&g_context);
		}
		__except (exceptionAddress = (GetExceptionInformation())->ExceptionRecord->ExceptionAddress, EXCEPTION_EXECUTE_HANDLER)
		{
			Log::Error("executing native 0x%016llx at address %p.", g_hash, exceptionAddress);
		}
	}

	return reinterpret_cast<uint64_t*>(g_context.GetResultPointer());
}

