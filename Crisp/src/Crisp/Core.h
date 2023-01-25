#pragma once

#ifdef CRISP_PLATFORM_WINDOWS
	#ifdef CRISP_BUILD_DLL
		#define CRISP_API __declspec(dllexport)
	#else
		#define CRISP_API __declspec(dllimport)
	#endif
#else
	#error Crisp only support windows
#endif