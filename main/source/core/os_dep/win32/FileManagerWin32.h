//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-30											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	

#ifndef _GLHL_CORE_OSDEP_WIN32_FILEMANAGERWIN32_H_
#define _GLHL_CORE_OSDEP_WIN32_FILEMANAGERWIN32_H_

#include "../../FileManager.h"

namespace GLHL {
	class FileManagerWin32: public FileManager {
	public:
		FileManagerWin32();

		std::string loadTextFile(std::string& _FilePath);

	private:

	};	// class FileManagerWin32

}	// namespace GLHL


#endif