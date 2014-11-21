//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-02-01											//
//																		//
//////////////////////////////////////////////////////////////////////////
//

#ifdef _WIN32

#ifndef _GLHL_CORE_OSDEP_WIN32_DIRECTORYCHANGESNOTIFYMANAGER_H_
#define _GLHL_CORE_OSDEP_WIN32_DIRECTORYCHANGESNOTIFYMANAGER_H_

#include <Windows.h>

namespace GLHL{
	namespace GLHL_WIN32{
		class DirectoryChangesNotifyManager{
		public:
			static void watchDirectory(LPTSTR _dir);

		private:

		private:

		};	// class DirectoryChangesNotifyManager.
	}	// namespace GLHL_WIN32
}	// namespace GLHL

#endif	// _GLHL_CORE_OSDEP_WIN32_DIRECTORYCHANGESNOTIFYMANAGER_H_

#endif