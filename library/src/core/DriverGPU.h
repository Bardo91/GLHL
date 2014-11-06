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
#include "os_dep/win32/glew/glew.h"
#endif

#include "types/Types.h"

#include <string>


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
		GLuint glCreateShader(GLenum _shaderType);
		void glShaderSource(GLuint _shader, GLsizei _count, const char **_string, const GLint *_length);
		void glCompileShader(GLuint _shader);
		void glGetShaderiv(GLuint _shader, GLenum _pname, GLint *_params);
		void glGetShaderInfoLog(GLuint _shader, GLsizei _maxLength, GLsizei *_length, char *_infoLog);
		void glDeleteShader(GLuint _shader);
		
		GLint glGetUniformLocation(GLuint _program, const char *_name);
		void glUniform(GLint _location, GLuint _value);
		void glUniform(GLint _location, vec2ui _vec);
		void glUniform(GLint _location, vec3ui _vec);
		void glUniform(GLint _location, vec4ui _vec);
		void glUniform(GLint _location, mat2ui _mat);
		void glUniform(GLint _location, mat3ui _mat);
		void glUniform(GLint _location, mat4ui _mat);


		void glUniform(GLint _location, GLint _value);
		void glUniform(GLint _location, vec2i _vec);
		void glUniform(GLint _location, vec3i _vec);
		void glUniform(GLint _location, vec4i _vec);
		void glUniform(GLint _location, mat2i _mat);
		void glUniform(GLint _location, mat3i _mat);
		void glUniform(GLint _location, mat4i _mat);


		void glUniform(GLint _location, GLfloat _value);
		void glUniform(GLint _location, vec2f _vec);
		void glUniform(GLint _location, vec3f _vec);
		void glUniform(GLint _location, vec4f _vec);
		void glUniform(GLint _location, mat2f _mat);
		void glUniform(GLint _location, mat3f _mat);
		void glUniform(GLint _location, mat4f _mat);

		

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