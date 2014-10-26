//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-10-26											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	

#include "Shader.h"
#include "DriverGPU.h"

#include <fstream>

using namespace std;

namespace GLHL{
	Shader::Shader(string _shaderPath){
		ifstream shaderFile(_shaderPath);

		if (shaderFile.is_open){
			string shaderSrc(istreambuf_iterator<char>(shaderFile), (istreambuf_iterator<char>()));


		}
	}

}	//	namespace GLHL