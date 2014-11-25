//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-11-25											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	

#ifndef _GLHL_CORE_BASE_CONTEXT_H_
#define _GLHL_CORE_BASE_CONTEXT_H_

#if defined (_WIN32)
	#include "os_dep\win32\ContextBaseWin32.h"
#endif
#if defined (__linux__)
	#include "os_dep\linux\ContextBaseLinux.h"
#endif


namespace GLHL{
	//-----------------------------------------------------------------------------------------------------------------
	class Context: public ContextBase{
	public:
		Context(){}

	private:

	};	//	class Context
}	//	namespace GLHL
#endif	//	_GLHL_CORE_BASE_CONTEXT_H_