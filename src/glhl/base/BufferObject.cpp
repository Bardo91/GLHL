//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for Image Processing  (GLHL)			//
//			Author: Pablo Ramon Soria									//
//			Date:	2014-01-17											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	BufferObject class

#include "BufferObject.h"
#include "DriverGPU.h"

using namespace GLHL;

//---------------------------------------------------------------------------------------------------------------------
BufferObject::BufferObject(unsigned _size) {
	DriverGPU *driver = DriverGPU::get();
	mBufferId = driver->genBuffer();
	driver->bindBuffer(GL_ARRAY_BUFFER, mBufferId);
	driver->bufferData(GL_ARRAY_BUFFER, _size, nullptr, GL_DYNAMIC_DRAW);

}

//---------------------------------------------------------------------------------------------------------------------
BufferObject::BufferObject(unsigned _size, std::uint8_t * _bytes) {
	DriverGPU *driver = DriverGPU::get();
	mBufferId = driver->genBuffer();
	driver->bindBuffer(GL_ARRAY_BUFFER, mBufferId);
	driver->bufferData(GL_ARRAY_BUFFER, _size, _bytes, GL_DYNAMIC_DRAW);
}

//---------------------------------------------------------------------------------------------------------------------
BufferObject::~BufferObject() {
	DriverGPU::get()->deleteBuffer(mBufferId);
}

//---------------------------------------------------------------------------------------------------------------------
void BufferObject::write(const unsigned _pos, std::uint8_t _byte) {

}

//---------------------------------------------------------------------------------------------------------------------
void BufferObject::write(const unsigned _pos, const unsigned _size, std::uint8_t * _bytes) {

}

//---------------------------------------------------------------------------------------------------------------------
std::uint8_t BufferObject::read(const unsigned _pos) {
	return std::uint8_t();
}

//---------------------------------------------------------------------------------------------------------------------
void BufferObject::read(const unsigned _pos, const unsigned _size, std::uint8_t * _bytes) {

}
