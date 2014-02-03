//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ram�n Soria									//
//			Date:	2014-01-30											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	


#include "FileManagerWin32.h"

#include <fstream>
#include <iostream>

using namespace std;

namespace GLHL {
	namespace GLHL_WIN32{
		//---------------------------------------------------------------------------------
		FileManagerWin32::FileManagerWin32(){


		}
		//---------------------------------------------------------------------------------
		string FileManagerWin32::loadTextFile(string &_filePath){

			ifstream file;
			string source, line;

			file.open(_filePath.c_str(), ifstream::in);

			if(!file.is_open())
				return NULL;
		
			while( getline(file, line) ){
				source += line += "\n ";
			}

			file.close();
			return source;
		}

		//---------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------
	}	// namespace GLHL_WIN32
}	// namespace GLHL