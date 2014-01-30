//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-30											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	

#ifndef _GLHL_CORE_FILEMANAGER_H_
#define _GLHL_CORE_FILEMANAGER_H_

#include <string>

namespace GLHL {
	class FileManager{
	public:
		static FileManager* createFileManager();

		virtual std::string loadTextFile(std::string& _filePath) = 0;

	protected:
		FileManager();

	protected:


	};	// class FileManager


}	// namespace GLHL


#endif