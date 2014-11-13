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

#if defined(_WIN32)
#include <Windows.h>
#include "os_dep/win32/glew/glew.h"
#include <gl/GL.h>
#endif
#if defined(__linux__)
#include <GL/glew.h>
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
		DriverGPU(){};				// Class constructor.	

	private:	// Private members about shaders
		GLboolean initDriver();

		static DriverGPU *mInstance;

	public: // Public interface to OpenGL Extended libraries
		// --> Shaders
		GLuint createShader(GLenum _shaderType);
		void shaderSource(GLuint _shader, GLsizei _count, const char **_string, const GLint *_length);
		void compileShader(GLuint _shader);
		void getShaderiv(GLuint _shader, GLenum _pname, GLint *_params);
		void getShaderInfoLog(GLuint _shader, GLsizei _maxLength, GLsizei *_length, char *_infoLog);
		void deleteShader(GLuint _shader);

		GLint getUniformLocation(GLuint _program, const char *_name);
		void setUniform(GLint _location, GLuint _value);
		void setUniform(GLint _location, vec2ui _vec);
		void setUniform(GLint _location, vec3ui _vec);
		void setUniform(GLint _location, vec4ui _vec);
		
		void setUniform(GLint _location, GLint _value);
		void setUniform(GLint _location, vec2i _vec);
		void setUniform(GLint _location, vec3i _vec);
		void setUniform(GLint _location, vec4i _vec);
		
		void setUniform(GLint _location, GLfloat _value);
		void setUniform(GLint _location, vec2f _vec);
		void setUniform(GLint _location, vec3f _vec);
		void setUniform(GLint _location, vec4f _vec);
		void setUniform(GLint _location, mat2f _mat);
		void setUniform(GLint _location, mat3f _mat);
		void setUniform(GLint _location, mat4f _mat);

		

		// --> Fragment Shader
		void bindFragDataLocation(GLuint _program, GLuint _colorNumber, const char * _name);

		// --> Vertex Shader

		// --> Buffer Objects
		void genFramebuffers(GLsizei _n, GLuint *_ids);
		GLuint genFramebuffer();
		void bindFramebuffer(GLenum _target, GLuint _framebuffer);
		void deleteFramebuffers(GLsizei _n, GLuint *_framebuffers);
		void deleteFramebuffer(GLuint _framebuffer);

		void framebufferTexture(GLenum _target, GLenum _attachment, GLuint _texture, GLint _level);

		void drawBuffers(GLsizei n, const GLenum * bufs);

		// --> Textures
		void activeTexture(GLenum _texture);
		void bindTexture(GLenum _target, GLuint _texture);
		void bindSampler(GLuint _unit, GLuint _sampler);

		// --> Programs
		GLuint createProgram();
		void attachShader(GLuint _program, GLuint _shader);
		void bindAttribLocation(GLuint _program, GLuint _index, const GLchar * _name);
		void linkProgram(GLuint _program);
		void getProgramiv(GLuint _program, GLenum _pname, GLint *_params);
		void getProgramInfoLog (GLuint _program, GLsizei _maxLength, GLsizei *_length, GLchar *_infoLog);
		void deleteProgram(GLuint _program);
		void useProgram(GLuint _program);
		GLint getAttribLocation(GLuint _program, const GLchar * _name);
		
		// --> Vertex
		void vertexAttribPointer(GLuint _index, GLint _size, GLenum _type, GLboolean _normalized, GLsizei _stride, const GLvoid * _pointer);
		void enableVertexAttribArray(GLuint _index);
		
		// --> Memory
		void genBuffers(GLsizei _n, GLuint * _buffers);//	Create a buffer object
		void bindBuffer(GLenum _target, GLuint _buffer);	//	Make buffer active
		void bufferData(GLenum _target, GLsizeiptr _size, const GLvoid * _data, GLenum _usage); //	Send data to buffer

	};

} // namespace GLHL



#endif //_GLHL_CORE_DRIVERGPU_H_
