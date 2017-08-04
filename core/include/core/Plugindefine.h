#pragma once

#ifdef __cplusplus
	#   define HADES_EXTERN     extern "C"
#else
	#   define HADES_EXTERN		extern
#endif // __cplusplus

#ifdef __linux
	#	define HADES_PLUGIN 
	#	define HADES_CORE_API
#else
	#ifdef _FRAMEWORK_EXPORT //��ܵ���ĳЩ�ؼ������ĺ�
	#	define HADES_CORE_API  __declspec(dllexport)
	#else
	#	define HADES_CORE_API  __declspec(dllimport)
	#endif // LIBRARY_IMPORT

	#ifdef _DYNAMIC_PLUGIN //��������������ַ�ĺ�
	#	define HADES_PLUGIN __declspec(dllexport)
	#else
	#	define HADES_PLUGIN 
	#endif
#endif