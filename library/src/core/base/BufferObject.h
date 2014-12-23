//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramon Soria									//
//			Date:	2014-01-17											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	BufferObject class


#ifndef _GLHL_CORE_BASE_BUFFER_OBJECT_H_
#define _GLHL_CORE_BASE_BUFFER_OBJECT_H_

#include "DriverGPU.h"

class BufferObject{
public:
	BufferObject();
	~BufferObject();

	operator GLuint() const{ return mBufferId; };

	void write(/*unit*/);
	void write(/*mani units*/);

	unit read(/*position*/);
	unit* read(/*size, offset...*/);

private:
	GLuint mBufferId;


};

#endif	//	_GLHL_CORE_BASE_BUFFER_OBJECT_H_