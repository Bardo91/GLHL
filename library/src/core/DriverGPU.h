//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
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
	class DriverGPU{	// Only one GPU driver is created
	public:		// Singleton interface
		static void  init();
		static DriverGPU* get();
		static void end();

	protected:			
		DriverGPU();				// Class constructor.	

	private:	// Private members about shaders
		GLboolean initDriver();

		static DriverGPU *mInstance;

	public: // Public interface to OpenGL Extended libraries
		// --> Shaders
		PFNGLCREATESHADERPROC glCreateShader;
		PFNGLSHADERSOURCEPROC glShaderSource;
		PFNGLCOMPILESHADERPROC glCompileShader;
		PFNGLGETSHADERIVPROC glGetShaderiv;
		PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
		PFNGLDELETESHADERPROC glDeleteShader;
		
		PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
		PFNGLUNIFORM1FPROC glUniform1f;
		PFNGLUNIFORM2FPROC glUniform2f;
		PFNGLUNIFORM3FPROC glUniform3f;
		PFNGLUNIFORM4FPROC glUniform4f;
		PFNGLUNIFORM1IPROC glUniform1i;
		PFNGLUNIFORM2IPROC glUniform2i;
		PFNGLUNIFORM3IPROC glUniform3i;
		PFNGLUNIFORM4IPROC glUniform4i;
		PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;
		PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
		PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;

		// --> Fragment Shader
		PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation;

		// --> Vertex Shader


		// --> Textures
		PFNGLACTIVETEXTUREPROC glActiveTexture;
		PFNGLBINDTEXTUREEXTPROC glBindTexture;
		PFNGLBINDSAMPLERPROC glBindSampler;

		// --> Programs
		PFNGLCREATEPROGRAMPROC glCreateProgram;
		PFNGLATTACHSHADERPROC glAttachShader;
		PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
		PFNGLLINKPROGRAMPROC glLinkProgram;
		PFNGLGETPROGRAMIVPROC glGetProgramiv;
		PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
		PFNGLDELETEPROGRAMPROC glDeleteProgram;
		PFNGLUSEPROGRAMPROC glUseProgram;
		PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
		
		// --> Vertex
		PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
		PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
		
		// --> Memory
		PFNGLGENBUFFERSPROC glGenBuffers;	//	Create a buffer object
		PFNGLBINDBUFFERPROC glBindBuffer;	//	Make buffer active
		PFNGLBUFFERDATAPROC glBufferData;	//	Send data to buffer

	};

} // namespace GLHL



#endif //_GLHL_CORE_DRIVERGPU_H_