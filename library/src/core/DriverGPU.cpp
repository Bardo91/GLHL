//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-17											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	DriverGPU. Abstraction of GPU

#include "DriverGPU.h"

#include <cassert>
#include <iostream>

namespace GLHL{
	//---------------------------------------------------------------------------
	//------------------------- Singleton Interface -----------------------------
	//---------------------------------------------------------------------------

	// Static initialization of DriverGPU's intance
	DriverGPU* DriverGPU::mInstance = nullptr;

	//---------------------------------------------------------------------------
	void DriverGPU::init(){
		if (mInstance == nullptr)
			mInstance = new DriverGPU();

	}

	//---------------------------------------------------------------------------
	DriverGPU* DriverGPU::get(){
		if (mInstance == nullptr)
			init();

		return mInstance;

	}

	//---------------------------------------------------------------------------
	void DriverGPU::end(){
		if (nullptr != mInstance)
			delete mInstance;
	}

	//---------------------------------------------------------------------------
	// OpenGL interface
	//---------------------------------------------------------------------------
	// --> Shaders
	GLuint createShader(GLenum _shaderType){
		return glCreateShader(_shaderType);
	}

	void shaderSource(GLuint _shader, GLsizei _count, const char **_string, const GLint *_length){
		glShaderSource(_shader, _count, _string, _length);
	}

	void compileShader(GLuint _shader){
		glCompileShader(_shader);
	}

	void getShaderiv(GLuint _shader, GLenum _pname, GLint *_params){
		glGetShaderiv(_shader, _pname, _params);
	}

	void getShaderInfoLog(GLuint _shader, GLsizei _maxLength, GLsizei *_length, char *_infoLog){
		glGetShaderInfoLog(_shader, _maxLength, _length, _infoLog);
	}

	void deleteShader(GLuint _shader){
		glDeleteShader(_shader);
	}

	GLint getUniformLocation(GLuint _program, const char *_name){
		return glGetUniformLocation(_program, _name);
	}

	void setUniform(GLint _location, GLuint _value){
		glUniform1ui(_location, _value);
	}

	void setUniform(GLint _location, vec2ui _vec){
		glUniform2uiv(_location, _vec.mSize, _vec);
	}

	void setUniform(GLint _location, vec3ui _vec){
		glUniform3uiv(_location, _vec.mSize, _vec);
	}

	void setUniform(GLint _location, vec4ui _vec){
		glUniform4uiv(_location, _vec.mSize, _vec);
	}

	void setUniform(GLint _location, GLint _value){
		glUniform1i(_location, _value);
	}

	void setUniform(GLint _location, vec2i _vec){
		glUniform2iv(_location, _vec.mSize, _vec);
	}

	void setUniform(GLint _location, vec3i _vec){
		glUniform3iv(_location, _vec.mSize, _vec);
	}

	void setUniform(GLint _location, vec4i _vec){
		glUniform4iv(_location, _vec.mSize, _vec);
	}

	void setUniform(GLint _location, GLfloat _value){
		glUniform1f(_location, _value);
	}

	void setUniform(GLint _location, vec2f _vec){
		glUniform2fv(_location, _vec.mSize, _vec);
	}

	void setUniform(GLint _location, vec3f _vec){
		glUniform3fv(_location, _vec.mSize, _vec);
	}

	void setUniform(GLint _location, vec4f _vec){
		glUniform4fv(_location, _vec.mSize, _vec);
	}

	void setUniform(GLint _location, mat2f _mat){
		glUniformMatrix2fv(_location, _mat.mSize, false, _mat);
	}

	void setUniform(GLint _location, mat3f _mat){
		glUniformMatrix3fv(_location, _mat.mSize, false, _mat);
	}

	void setUniform(GLint _location, mat4f _mat){
		glUniformMatrix4fv(_location, _mat.mSize, false, _mat);
	}



	// --> Fragment Shader
	void bindFragDataLocation(GLuint _program, GLuint _colorNumber, const char * _name);

	// --> Vertex Shader


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
	void getProgramInfoLog(GLuint _program, GLsizei _maxLength, GLsizei *_length, GLchar *_infoLog);
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

} //namespace GLHL