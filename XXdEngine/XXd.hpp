#ifndef XXD_HPP
#define XXD_HPP

#ifdef XXD_PLATFORM_APPLE
	#ifdef XXD_BUILD_DLL
		#define XXD_API __attribute__ ((visibility("default")))
	#else
		#define XXD_API __attribute__ ((visibility("default")))
	#endif
#elifdef XXD_PLATFORM_WINDOWS
	#ifdef XXD_BUILD_DLL 
		#define XXD_API __declspec(dllexport) 
	#else
		#define XXD_API __declspec(dllimport) 
	#endif
#else
	#error XXdEngine don't support the platform
#endif

#endif
