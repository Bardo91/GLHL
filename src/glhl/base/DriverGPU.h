//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ram�n Soria									//
//			Date:	2014-01-17											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	DriverGPU. Abstraction of GPU

#ifndef _GLHL_CORE_BASE_DRIVERGPU_H_
#define _GLHL_CORE_BASE_DRIVERGPU_H_

#if defined(_WIN32)
#include <Windows.h>
#include "glew.h"
#include <gl/GL.h>
#endif
#if defined(__linux__)
#include <GL/glew.h>
#endif

#include "../types/Types.h"
#include "Context.h"

#include <array>
#include <string>
#include <thread>
#include <vector>


namespace GLHL{
	/** DriverGPU class is and abstraction GPU methods using OpenGL. Basically, ensures that the drivers are properly loaded once per thread,
	*	and gather all method in one class to more class-oriented likely interface. Every method is called as the original method but without
	*	the initial gl, so for more information visit https://www.opengl.org docs.
	*
	*/

	class DriverGPU{	// Only one GPU driver is created
	public:		// Singleton interface
		/** \brief static initialization of Drivers.
		*/
		static void  init();
		/** \brief Getting the proper instance of driver in the thread.
		*/
		static DriverGPU* get();
		/** \brief End up with drivers properly.
		*/
		static void end();

	protected:			
		DriverGPU(){};				// Class constructor.	

	private:	// Private members
		static DriverGPU *mInstance;
		static std::vector<std::thread::id> mInitializedThreads;

	public: // Public interface to OpenGL library
		// --> Shaders
		GLuint createShader(GLenum _shaderType);
		void shaderSource(GLuint _shader, GLsizei _count, const char **_string, const GLint *_length);
		void compileShader(GLuint _shader);
		void getShaderiv(GLuint _shader, GLenum _pname, GLint *_params);
		void getShaderInfoLog(GLuint _shader, GLsizei _maxLength, GLsizei *_length, char *_infoLog);
		void deleteShader(GLuint _shader);

		GLuint getUniformLocation(GLuint _program, const char *_name);


		void setProgramUniform(GLint _location, GLint _program, GLuint _value);
		void setProgramUniform(GLint _location, GLint _program, vec2ui _vec);
		void setProgramUniform(GLint _location, GLint _program, vec3ui _vec);
		void setProgramUniform(GLint _location, GLint _program, vec4ui _vec);
				
		void setProgramUniform(GLint _location, GLint _program, GLint _value);
		void setProgramUniform(GLint _location, GLint _program, vec2i _vec);
		void setProgramUniform(GLint _location, GLint _program, vec3i _vec);
		void setProgramUniform(GLint _location, GLint _program, vec4i _vec);

		void setProgramUniform(GLint _location, GLint _program, GLfloat _value);
		void setProgramUniform(GLint _location, GLint _program, vec2f _vec);
		void setProgramUniform(GLint _location, GLint _program, vec3f _vec);
		void setProgramUniform(GLint _location, GLint _program, vec4f _vec);
		void setProgramUniform(GLint _location, GLint _program, mat2f _mat);
		void setProgramUniform(GLint _location, GLint _program, mat3f _mat);
		void setProgramUniform(GLint _location, GLint _program, mat4f _mat);

		
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
		void genBuffers(const GLsizei _size, GLuint *_buffers);
		GLuint genBuffer();
		void bindBuffer(GLenum _target, GLuint _buffer);
		void deleteBuffers(const GLsizei _size, GLuint *_buffers);
		void deleteBuffer(GLuint &_buffer);
		void bufferData(GLenum _target, GLsizeiptr _size, const void *_data, GLenum _usage);

		// --> Frame Buffer Objects
		void genFramebuffers(GLsizei _n, GLuint *_ids);
		GLuint genFramebuffer();
		void bindFramebuffer(GLenum _target, GLuint _framebuffer);
		void deleteFramebuffers(GLsizei _n, GLuint *_framebuffers);
		void deleteFramebuffer(GLuint _framebuffer);
		void blitFramebuffer(	GLint _srcX0, GLint _srcY0, GLint _srcX1, GLint _srcY1,
								GLint _dstX0, GLint _dstY0, GLint _dstX1, GLint _dstY1,
								GLbitfield _mask, GLenum _filter);
		void framebufferTexture(GLenum _target, GLenum _attachment, GLuint _texture, GLint _level);
		void framebufferTexture2D(GLenum _target, GLenum _attachment, GLenum _textarget, GLuint _texture, GLint _level);
		void drawBuffers(GLsizei n, const GLenum * bufs);
		GLenum checkFramebufferStatus(GLenum _target);



		// --> Textures
		void activeTexture(GLenum _texture);
		void bindTexture(GLenum _target, GLuint _texture);
		void bindSampler(GLuint _unit, GLuint _sampler);
		void genTextures(GLsizei _n, GLuint * _textures);
		void deleteTextures(GLsizei _n, const GLuint * _textures);
		void texImage2D(GLenum _target, GLint _level, GLint _internalformat, GLsizei _width, GLsizei _height, GLint _border, GLenum _format, GLenum _type, const GLvoid * _data);
		void getTexLevelParameteriv(GLenum _target, GLint _level, GLenum _pname, GLint * _params);
		void texParameteri(GLenum _target, GLenum _pname, GLint _param);

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
		
		// --> Draw methods
		void drawLine2f(std::array<vec2f, 2> _points);
		void drawTriangle2f(std::array<vec2f, 3> _points);
		void drawQuad2f(std::array<vec2f, 4> _points);

		void drawTriangleTextured2f(std::array<vec2f, 3> _points, std::array<vec2f, 3> _texPoints);
		void drawQuadTextured2f(std::array<vec2f, 4> _points, std::array<vec2f, 4> _texPoints);

		void drawLine3f(std::array<vec3f, 2> _points);
		void drawTriangle3f(std::array<vec3f, 3> _points);
		void drawQuad3f(std::array<vec3f, 4> _points);

		void drawTriangleTextured3f(std::array<vec3f, 3> _points, std::array<vec2f, 3> _texPoints);
		void drawQuadTextured3f(std::array<vec3f, 4> _points, std::array<vec2f, 4> _texPoints);


		// --> Generic OpenGL
		void readPixels(GLint _x, GLint _y, GLsizei _width, GLsizei _height, GLenum _format, GLenum _type, GLvoid * _data);

		void checkErrors();


	};

} // namespace GLHL



#endif //_GLHL_CORE_BASE_DRIVERGPU_H_
