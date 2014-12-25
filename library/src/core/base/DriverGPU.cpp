//////////////////////////////////////////////////////////////////////////arrat
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-17											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	DriverGPU. Abstraction of GPU

#include "DriverGPU.h"

#include "../types/Types.h"

#include <cassert>
#include <iostream>

using namespace std;
namespace GLHL{
	//---------------------------------------------------------------------------
	//------------------------- Singleton Interface -----------------------------
	//---------------------------------------------------------------------------

	// Static initialization of DriverGPU's intance
	DriverGPU* DriverGPU::mInstance = nullptr;
	std::vector<std::thread::id> DriverGPU::mInitializedThreads;
	//---------------------------------------------------------------------------
	void DriverGPU::init(){
		GLenum res = glewInit();
		assert(res == GLEW_OK);
		cout << "init glew" << endl;
	}

	//---------------------------------------------------------------------------
	DriverGPU* DriverGPU::get(){
		if (mInstance == nullptr)
			mInstance = new DriverGPU(); 
		
		bool isInit = false;
		for (auto i : mInitializedThreads){
			if (i == this_thread::get_id())
				isInit = true;
		}
		
		if (!isInit){
			init();
			mInitializedThreads.push_back(this_thread::get_id());
		}

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
	GLuint DriverGPU::createShader(GLenum _shaderType){
		return glCreateShader(_shaderType);
	}

	void DriverGPU::shaderSource(GLuint _shader, GLsizei _count, const char **_string, const GLint *_length){
		glShaderSource(_shader, _count, _string, _length);
	}

	void DriverGPU::compileShader(GLuint _shader){
		glCompileShader(_shader);
	}

	void DriverGPU::getShaderiv(GLuint _shader, GLenum _pname, GLint *_params){
		glGetShaderiv(_shader, _pname, _params);
	}

	void DriverGPU::getShaderInfoLog(GLuint _shader, GLsizei _maxLength, GLsizei *_length, char *_infoLog){
		glGetShaderInfoLog(_shader, _maxLength, _length, _infoLog);
	}

	void DriverGPU::deleteShader(GLuint _shader){
		glDeleteShader(_shader);
	}

	GLuint DriverGPU::getUniformLocation(GLuint _program, const char *_name){
		GLint loc = glGetUniformLocation(_program, _name);
		assert(loc != -1);	// Could not find uniform name.
		return loc;
	}

	void DriverGPU::setProgramUniform(GLint _location, GLint _program, GLuint _value){
		glProgramUniform1ui(_location, _program, _value);
	}

	void DriverGPU::setProgramUniform(GLint _location, GLint _program, vec2ui _vec){
		glProgramUniform2uiv(_location, _program, _vec.size(), _vec);
	}

	void DriverGPU::setProgramUniform(GLint _location, GLint _program, vec3ui _vec){
		glProgramUniform3uiv(_location, _program, _vec.size(), _vec);
	}

	void DriverGPU::setProgramUniform(GLint _location, GLint _program, vec4ui _vec){
		glProgramUniform4uiv(_location, _program, _vec.size(), _vec);
	}

	void DriverGPU::setProgramUniform(GLint _location, GLint _program, GLint _value){
		glProgramUniform1i(_location, _program, _value);
	}

	void DriverGPU::setProgramUniform(GLint _location, GLint _program, vec2i _vec){
		glProgramUniform2iv(_location, _program, _vec.size(), _vec);
	}

	void DriverGPU::setProgramUniform(GLint _location, GLint _program, vec3i _vec){
		glProgramUniform3iv(_location, _program, _vec.size(), _vec);
	}

	void DriverGPU::setProgramUniform(GLint _location, GLint _program, vec4i _vec){
		glProgramUniform4iv(_location, _program, _vec.size(), _vec);
	}

	void DriverGPU::setProgramUniform(GLint _location, GLint _program, GLfloat _value){
		glProgramUniform1f(_location, _program, _value);
	}

	void DriverGPU::setProgramUniform(GLint _location, GLint _program, vec2f _vec){
		glProgramUniform2fv(_location, _program, _vec.size(), _vec);
	}

	void DriverGPU::setProgramUniform(GLint _location, GLint _program, vec3f _vec){
		glProgramUniform3fv(_location, _program, _vec.size(), _vec);
	}

	void DriverGPU::setProgramUniform(GLint _location, GLint _program, vec4f _vec){
		glProgramUniform4fv(_location, _program, _vec.size(), _vec);
	}

	void DriverGPU::setProgramUniform(GLint _location, GLint _program, mat2f _mat){
		glProgramUniformMatrix2fv(_location, _program, _mat.size(), false, _mat);
	}

	void DriverGPU::setProgramUniform(GLint _location, GLint _program, mat3f _mat){
		glProgramUniformMatrix3fv(_location, _program, _mat.size(), false, _mat);
	}

	void DriverGPU::setProgramUniform(GLint _location, GLint _program, mat4f _mat){
		glProgramUniformMatrix4fv(_location, _program, _mat.size(), false, _mat);
	}

	void DriverGPU::setUniform(GLint _location, GLuint _value){
		glUniform1ui(_location, _value);
	}

	void DriverGPU::setUniform(GLint _location, vec2ui _vec){
		glUniform2uiv(_location, _vec.size(), _vec);
	}

	void DriverGPU::setUniform(GLint _location, vec3ui _vec){
		glUniform3uiv(_location, _vec.size(), _vec);
	}

	void DriverGPU::setUniform(GLint _location, vec4ui _vec){
		glUniform4uiv(_location, _vec.size(), _vec);
	}

	void DriverGPU::setUniform(GLint _location, GLint _value){
		glUniform1i(_location, _value);
	}

	void DriverGPU::setUniform(GLint _location, vec2i _vec){
		glUniform2iv(_location, _vec.size(), _vec);
	}

	void DriverGPU::setUniform(GLint _location, vec3i _vec){
		glUniform3iv(_location, _vec.size(), _vec);
	}

	void DriverGPU::setUniform(GLint _location, vec4i _vec){
		glUniform4iv(_location, _vec.size(), _vec);
	}

	void DriverGPU::setUniform(GLint _location, GLfloat _value){
		glUniform1f(_location, _value);
	}

	void DriverGPU::setUniform(GLint _location, vec2f _vec){
		glUniform2fv(_location, _vec.size(), _vec);
	}

	void DriverGPU::setUniform(GLint _location, vec3f _vec){
		glUniform3fv(_location, _vec.size(), _vec);
	}

	void DriverGPU::setUniform(GLint _location, vec4f _vec){
		glUniform4fv(_location, _vec.size(), _vec);
	}

	void DriverGPU::setUniform(GLint _location, mat2f _mat){
		glUniformMatrix2fv(_location, _mat.size(), false, _mat);
	}

	void DriverGPU::setUniform(GLint _location, mat3f _mat){
		glUniformMatrix3fv(_location, _mat.size(), false, _mat);
	}

	void DriverGPU::setUniform(GLint _location, mat4f _mat){
		glUniformMatrix4fv(_location, _mat.size(), false, _mat);
	}



	// --> Fragment Shader
	void DriverGPU::bindFragDataLocation(GLuint _program, GLuint _colorNumber, const char * _name){
		glBindFragDataLocation(_program, _colorNumber, _name);
	}


	// --> Vertex Shader

	// --> Buffer Objects
	void  DriverGPU::genBuffers(const GLsizei _size, GLuint *_buffers){
		glGenBuffers(_size, _buffers);
	}

	GLuint DriverGPU::genBuffer(){
		GLuint buffer;
		glGenBuffers(1, &buffer);

		assert(buffer != 0);	// Could not create buffer.

		return buffer;
	}

	void  DriverGPU::bindBuffer(GLenum _target, GLuint _buffer){
		glBindBuffer(_target, _buffer);
	}

	void  DriverGPU::deleteBuffers(const GLsizei _size, GLuint *_buffers){
		glDeleteBuffers(_size, _buffers);
	}

	void  DriverGPU::deleteBuffer(GLuint &_buffer){
		glDeleteBuffers(1, &_buffer);
	}

	void DriverGPU::bufferData(GLenum _target, GLsizeiptr _size, const void *_data, GLenum _usage){
		glBufferData(_target, _size, _data, _usage);
	}

	void DriverGPU::genFramebuffers(GLsizei _n, GLuint *_ids){
		glGenFramebuffers(_n, _ids);
	}
	
	GLuint DriverGPU::genFramebuffer(){
		GLuint fb;
		glGenFramebuffers(1, &fb);

		assert(fb != 0);	// Could not create frame buffer.

		return fb;
	}
	
	void DriverGPU::bindFramebuffer(GLenum _target, GLuint _framebuffer){
		glBindFramebuffer(_target, _framebuffer);
	}
	
	void DriverGPU::deleteFramebuffers(GLsizei _n, GLuint *_framebuffers){
		glDeleteFramebuffers(_n, _framebuffers);
	}
	
	void DriverGPU::deleteFramebuffer(GLuint _framebuffer){
		glDeleteFramebuffers(1, &_framebuffer);
	}

	void DriverGPU::blitFramebuffer(	GLint _srcX0, GLint _srcY0, GLint _srcX1, GLint _srcY1,
										GLint _dstX0, GLint _dstY0, GLint _dstX1, GLint _dstY1,
										GLbitfield _mask, GLenum _filter){
		glBlitFramebuffer(	_srcX0, _srcY0, _srcX1, _srcY1,
							_dstX0, _dstY0, _dstX1, _dstY1,
							_mask, _filter);
	}

	void DriverGPU::framebufferTexture(GLenum _target, GLenum _attachment, GLuint _texture, GLint _level){
		glFramebufferTexture(_target, _attachment, _texture, _level);
	}

	void DriverGPU::framebufferTexture2D(GLenum _target, GLenum _attachment, GLenum _textarget, GLuint _texture, GLint _level){
		glFramebufferTexture2D(_target, _attachment, _textarget, _texture, _level);
	}

	void DriverGPU::drawBuffers(GLsizei _n, const GLenum * _bufs){
		glDrawBuffers(_n, _bufs);
	}

	GLenum DriverGPU::checkFramebufferStatus(GLenum _target){
		return glCheckFramebufferStatus(_target);
	}


	// --> Textures
	void DriverGPU::activeTexture(GLenum _texture){
		glActiveTexture(_texture);
	}

	void DriverGPU::bindTexture(GLenum _target, GLuint _texture){
		glBindTexture(_target, _texture);
	}

	void DriverGPU::bindSampler(GLuint _unit, GLuint _sampler){
		glBindSampler(_unit, _sampler);
	}

	void DriverGPU::genTextures(GLsizei _n, GLuint * _textures){
		glGenTextures(_n, _textures);
	}

	void DriverGPU::deleteTextures(GLsizei _n, const GLuint * _textures){
		glDeleteTextures(_n, _textures);
	}

	void DriverGPU::texImage2D(GLenum _target, GLint _level, GLint _internalformat, GLsizei _width, GLsizei _height, GLint _border, GLenum _format, GLenum _type, const GLvoid * _data){
		glTexImage2D(_target, _level, _internalformat, _width, _height, _border, _format, _type, _data);

	}

	void DriverGPU::getTexLevelParameteriv(GLenum _target, GLint _level, GLenum _pname, GLint * _params){
		glGetTexLevelParameteriv(_target, _level, _pname, _params);
	}

	void DriverGPU::texParameteri(GLenum _target, GLenum _pname, GLint _param){
		glTexParameteri(_target, _pname, _param);
	}

	// --> Programs
	GLuint DriverGPU::createProgram(){
		return glCreateProgram();
	}

	void DriverGPU::attachShader(GLuint _program, GLuint _shader){
		glAttachShader(_program, _shader);
	}

	void DriverGPU::bindAttribLocation(GLuint _program, GLuint _index, const GLchar * _name){
		glBindAttribLocation(_program, _index, _name);
	}

	void DriverGPU::linkProgram(GLuint _program){
		glLinkProgram(_program);
	}

	void DriverGPU::getProgramiv(GLuint _program, GLenum _pname, GLint *_params){
		glGetProgramiv(_program, _pname, _params);
	}

	void DriverGPU::getProgramInfoLog(GLuint _program, GLsizei _maxLength, GLsizei *_length, GLchar *_infoLog){
		glGetProgramInfoLog(_program, _maxLength, _length, _infoLog);
	}

	void DriverGPU::deleteProgram(GLuint _program){
		glDeleteProgram(_program);
	}

	void DriverGPU::useProgram(GLuint _program){
		glUseProgram(_program);
	}

	GLint DriverGPU::getAttribLocation(GLuint _program, const GLchar * _name){
		return glGetAttribLocation(_program, _name);
	}

	// --> Vertex
	void DriverGPU::vertexAttribPointer(GLuint _index, GLint _size, GLenum _type, GLboolean _normalized, GLsizei _stride, const GLvoid * _pointer){
		glVertexAttribPointer(_index, _size, _type, _normalized, _stride, _pointer);
	}

	void DriverGPU::enableVertexAttribArray(GLuint _index){
		glEnableVertexAttribArray(_index);
	}

	// --> Draw methods
	void DriverGPU::drawLine2f(std::array<vec2f, 2> _points) {
		glBegin(GL_LINE);
		glVertex2f(_points[0][0], _points[0][1]);
		glVertex2f(_points[1][0], _points[1][1]);
		glEnd();
	}

	void DriverGPU::drawTriangle2f(std::array<vec2f, 3> _points) {
		glBegin(GL_TRIANGLES);
		glVertex2f(_points[0][0],_points[0][1]);
		glVertex2f(_points[1][0],_points[1][1]);
		glVertex2f(_points[2][0],_points[2][1]);
		glEnd();
	}

	void DriverGPU::drawQuad2f(std::array<vec2f, 4> _points) {
		glBegin(GL_TRIANGLES);
		// First Triangle
		glVertex2f(_points[0][0],_points[0][1]);
		glVertex2f(_points[1][0],_points[1][1]);
		glVertex2f(_points[2][0],_points[2][1]);

		// Second Triangle
		glVertex2f(_points[0][0],_points[0][1]);
		glVertex2f(_points[2][0],_points[2][1]);
		glVertex2f(_points[3][0],_points[3][1]);
		glEnd();
	}

	void DriverGPU::drawTriangleTextured2f(std::array<vec2f, 3> _points, std::array<vec2f, 3> _texPoints){
		glBegin(GL_TRIANGLES);
		glTexCoord2f(_texPoints[0][0], _texPoints[0][1]);
		glVertex2f(_points[0][0], _points[0][1]);

		glTexCoord2f(_texPoints[1][0], _texPoints[1][1]);
		glVertex2f(_points[1][0], _points[1][1]);

		glTexCoord2f(_texPoints[2][0], _texPoints[2][1]);
		glVertex2f(_points[2][0], _points[2][1]);
		glEnd();
	}

	void DriverGPU::drawQuadTextured2f(std::array<vec2f, 4> _points, std::array<vec2f, 4> _texPoints) {
		glBegin(GL_TRIANGLES);
		// First Triangle
		glTexCoord2f(_texPoints[0][0], _texPoints[0][1]);
		glVertex2f(_points[0][0], _points[0][1]);
		glTexCoord2f(_texPoints[1][0], _texPoints[1][1]);
		glVertex2f(_points[1][0], _points[1][1]);
		glTexCoord2f(_texPoints[2][0], _texPoints[2][1]);
		glVertex2f(_points[2][0], _points[2][1]);

		// Second Triangle
		glTexCoord2f(_texPoints[0][0], _texPoints[0][1]);
		glVertex2f(_points[0][0], _points[0][1]);
		glTexCoord2f(_texPoints[2][0], _texPoints[2][1]);
		glVertex2f(_points[2][0], _points[2][1]);
		glTexCoord2f(_texPoints[3][0], _texPoints[3][1]);
		glVertex2f(_points[3][0], _points[3][1]);
		glEnd();
	}


	void DriverGPU::drawLine3f(std::array<vec3f, 2> _points) {
		glBegin(GL_LINE);
		glVertex3f(_points[0][0], _points[0][1], _points[0][2]);
		glVertex3f(_points[1][0], _points[1][1], _points[1][2]);
		glEnd();
	}

	void DriverGPU::drawTriangle3f(std::array<vec3f, 3> _points) {
		glBegin(GL_TRIANGLES);
		glVertex3f(_points[0][0], _points[0][1], _points[0][2]);
		glVertex3f(_points[1][0], _points[1][1], _points[1][2]);
		glVertex3f(_points[2][0], _points[2][1], _points[2][2]);
		glEnd();
	}

	void DriverGPU::drawQuad3f(std::array<vec3f, 4> _points) {
		glBegin(GL_TRIANGLES);
		glVertex3f(_points[0][0], _points[0][1], _points[0][2]);
		glVertex3f(_points[1][0], _points[1][1], _points[1][2]);
		glVertex3f(_points[2][0], _points[2][1], _points[2][2]);

		// Second Triangle
		glVertex3f(_points[0][0], _points[0][1], _points[0][2]);
		glVertex3f(_points[2][0], _points[2][1], _points[2][2]);
		glVertex3f(_points[3][0], _points[3][1], _points[3][2]);
		glEnd();
	}

	void DriverGPU::drawTriangleTextured3f(std::array<vec3f, 3> _points, std::array<vec2f, 3> _texPoints) {
		glBegin(GL_TRIANGLES);
		glTexCoord2f(_texPoints[0][0], _texPoints[0][1]);
		glVertex3f(_points[0][0], _points[0][1], _points[0][2]);
		glTexCoord2f(_texPoints[1][0], _texPoints[1][1]);
		glVertex3f(_points[1][0], _points[1][1], _points[1][2]);
		glTexCoord2f(_texPoints[2][0], _texPoints[2][1]);
		glVertex3f(_points[2][0], _points[2][1], _points[2][2]);
		glEnd();
	}

	void DriverGPU::drawQuadTextured3f(std::array<vec3f, 4> _points, std::array<vec2f, 4> _texPoints) {
		glBegin(GL_TRIANGLES);
		// First Triangle;
		glTexCoord2f(_texPoints[0][0], _texPoints[0][1]);
		glVertex3f(_points[0][0], _points[0][1], _points[0][2]);
		glTexCoord2f(_texPoints[1][0], _texPoints[1][1]);
		glVertex3f(_points[1][0], _points[1][1], _points[1][2]);
		glTexCoord2f(_texPoints[2][0], _texPoints[2][1]);
		glVertex3f(_points[2][0], _points[2][1], _points[2][2]);

		// Second Triangle
		glTexCoord2f(_texPoints[0][0], _texPoints[0][1]);
		glVertex3f(_points[0][0], _points[0][1], _points[0][2]);
		glTexCoord2f(_texPoints[2][0], _texPoints[2][1]);
		glVertex3f(_points[2][0], _points[2][1], _points[2][2]);
		glTexCoord2f(_texPoints[3][0], _texPoints[3][1]);
		glVertex3f(_points[3][0], _points[3][1], _points[3][2]);
		glEnd();
	}

	// --> Generic OpenGL
	void DriverGPU::readPixels(GLint _x, GLint _y, GLsizei _width, GLsizei _height, GLenum _format, GLenum _type, GLvoid * _data){
		glReadPixels(_x, _y, _width, _height, _format, _type, _data);
	}

	void DriverGPU::checkErrors(){
		GLenum err = glGetError();
		bool noError = true;
		switch(err) {
		case GL_INVALID_OPERATION:      
			std::cerr << "INVALID_OPERATION" << std::endl;
			noError = false;
			break;
		case GL_INVALID_ENUM:           
			std::cerr << "INVALID_ENUM" << std::endl;
			noError = false;
			break;
		case GL_INVALID_VALUE:          
			std::cerr <<"INVALID_VALUE" << std::endl;
			noError = false;
			break;
		case GL_OUT_OF_MEMORY:          
			std::cerr << "OUT_OF_MEMORY" << std::endl;
			noError = false;
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:  
			std::cerr << "INVALID_FRAMEBUFFER_OPERATION" << std::endl;
			noError = false;
			break;
		}

		assert(noError);
	}

} //namespace GLHL