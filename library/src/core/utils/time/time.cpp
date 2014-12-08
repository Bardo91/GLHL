////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL - core
//
//		Author: Pablo Ram�n Soria 
//		Date: 2013/14/08	
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Time and time functions

// Engine headers
#include "time.h"
#include <cassert>

namespace GLHL {
	//------------------------------------------------------------------------------------------------------------------
	// Static data definition
	//------------------------------------------------------------------------------------------------------------------
	STime* STime::sTime = nullptr;	

	//------------------------------------------------------------------------------------------------------------------
	// Method implementations
	//------------------------------------------------------------------------------------------------------------------
	void STime::init() {
		assert(sTime == nullptr);
		sTime = new STime();
	}

	//------------------------------------------------------------------------------------------------------------------
	void STime::end() {
		assert(sTime != nullptr);
		delete sTime;
		sTime = nullptr;
	}

	//------------------------------------------------------------------------------------------------------------------
	STime::STime() {
		#if defined (__linux__)
			// Get current time
			std::cout << "por aqui he pasao" << std::endl;
			gettimeofday(&mInitTime, 0);
		#elif defined (WIN32)
			// Get initial time
			QueryPerformanceCounter(&mInitTime);
		#endif
	}
	
}        // namespace GLHL
