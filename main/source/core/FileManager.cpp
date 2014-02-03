//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-30											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	


#include "FileManager.h"

#ifdef _WIN32
	#include "os_dep\win32\FileManagerWin32.h"
#elif defined(__linux__)
	#include "os_dep/linux/FileManagerLinux.h"
#endif

#include <cassert>

namespace GLHL {
	//---------------------------------------------------------------------------------
	FileManager* FileManager::createFileManager(){
		#ifdef _WIN32
				return new GLHL_WIN32::FileManagerWin32();
		#elif defined(__linux__)
				return new FileManagerLinux();
		#endif
		assert(false);

	}

	//---------------------------------------------------------------------------------
	
	//---------------------------------------------------------------------------------
	FileManager::FileManager(){

	}
	//---------------------------------------------------------------------------------

}	// namespace GLHL