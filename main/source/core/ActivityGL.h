//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-17											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	ActivityGL

#ifndef _GLHL_ACTIVITYGL_H_
#define _GLHL_ACTIVITYGL_H_

#include "DriverGPU.h"
#include "WindowGL.h"

namespace GLHL{
	class ActivityGL{
	public:

	protected:
		ActivityGL();				// Basic constructor.

	protected:
		DriverGPU* driverGPU;
		WindowGL* window;

	}; // class ActivityGL.
} // namespace GLHL.

#endif // _GLHL_ACTIVITY_H_
