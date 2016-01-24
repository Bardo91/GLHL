//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramon Soria									//
//			Date:	2014-12-24											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	BufferObject class


#ifndef _GLHL_CORE_BASE_BUFFER_OBJECT_H_
#define _GLHL_CORE_BASE_BUFFER_OBJECT_H_

#include "DriverGPU.h"
#include <cstdint>

class BufferObject{
public:
	BufferObject(unsigned _size);
	BufferObject(unsigned _size, std::uint8_t *_bytes);
	~BufferObject();

	operator GLuint() const{ return mBufferId; };

	void write(const unsigned _pos, std::uint8_t _byte);
	void write(const unsigned _pos, const unsigned _size, std::uint8_t *_bytes);

	std::uint8_t read(const unsigned _pos);
	void read(const unsigned _pos, const unsigned _size, std::uint8_t *_bytes);

private:
	GLuint mBufferId;


};

#endif	//	_GLHL_CORE_BASE_BUFFER_OBJECT_H_