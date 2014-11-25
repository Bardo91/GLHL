//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-11-25											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	

#ifndef _GLHL_CORE_BASE_CONTEXT_BASE_WIN32_H_
#define _GLHL_CORE_BASE_CONTEXT_BASE_WIN32_H_

#if defined (_WIN32)

#include <Windows.h>

namespace GLHL{
	//-----------------------------------------------------------------------------------------------------------------
	namespace GLHL_WIN32{
		class ContextBaseWin32{
		public:
			ContextBaseWin32();

		private:
			bool initContext();

			bool selfDestroy();

		private:
			HGLRC		mHRC = NULL;
			HDC			mHDC = NULL;
			HINSTANCE	mHInstance = NULL;
			HWND		mHWnd = NULL;


		};	//	class ContextBaseWin32

	}
	typedef GLHL_WIN32::ContextBaseWin32 ContextBase;
#endif
}	//	namespace GLHL
#endif	//	_GLHL_CORE_BASE_CONTEXT_BASE_WIN32_H_