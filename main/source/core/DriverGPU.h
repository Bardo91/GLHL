//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-17											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	DriverGPU. Abstraction of GPU

#ifndef _GLHL_CORE_DRIVERGPU_H_
#define _GLHL_CORE_DRIVERGPU_H_

#ifdef _WIN32
#include <Windows.h>
#endif

#include <gl/GL.h>
#include <gl/GLU.h>
#include <string>

#include "OpenGLExtensions/glext.h"
#include "OpenGLExtensions/wglext.h"

// La carga de funciones de expansión de OpenGl se hacen de forma diferente
// en windows y en linux, para que sea comodo el traslado del código entre 
// una plataforma y otra se ha escrito la siguiente macro.
#ifdef _WIN32
inline PROC loadGlFunction(const char* _strFun){
	return wglGetProcAddress(_strFun);
}
#elif defined(__linux__)
inline void* () loadGlFunction(const char* _strFun){
	return glXGetProcAddress(reinterpret_cast<GLubyte *>(_strFun));
}
#endif
//-------------------------------------------------------------------//

namespace GLHL{
	enum eShaders {eVertexShader = GL_VERTEX_SHADER, eFragmentShader = GL_FRAGMENT_SHADER};

	class DriverGPU{	// Only one GPU driver is created
	public:			
		DriverGPU();				// Class constructor.	

	private:	// Private members about shaders
		GLboolean initDriver();

	public:		// Public interface about shaders
		GLboolean initShaders(std::string _vSource, std::string _fSource);	

		//-------------------------------------------------------------
		//	New public interface.
		GLuint createProgram();
		GLuint uploadShader(eShaders _shaderType, std::string _shaderSource, GLuint _program);
		void bindAttribute(GLuint _program, GLuint _index, const GLchar* _name);
		bool linkProgram(GLuint _program);


	private:
		GLuint loadShader(GLenum _type, const char* _shaderSrc);

	private:	// Shaders declaration.
		GLuint mVertexShader, mGeometryShader, mFragmentShader; // 666 TODO: maybe arent necessary
		GLuint mProgram;

	public: // Draw
		GLvoid drawOnBuffer(GLint _widt, GLint _height);


	private: // Public interface to OpenGL Extended libraries
		// --> Shaders
		PFNGLCREATESHADERPROC glCreateShader;
		PFNGLSHADERSOURCEPROC glShaderSource;
		PFNGLCOMPILESHADERPROC glCompileShader;
		PFNGLGETSHADERIVPROC glGetShaderiv;
		PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
		PFNGLDELETESHADERPROC glDeleteShader;
		
		PFNGLCREATEPROGRAMPROC glCreateProgram;
		PFNGLATTACHSHADERPROC glAttachShader;
		PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
		PFNGLLINKPROGRAMPROC glLinkProgram;
		PFNGLGETPROGRAMIVPROC glGetProgramiv;
		PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
		PFNGLDELETEPROGRAMPROC glDeleteProgram;
		PFNGLUSEPROGRAMPROC glUseProgram;
		
		PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
		PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
	};

} // namespace GLHL



#endif //_GLHL_CORE_DRIVERGPU_H_