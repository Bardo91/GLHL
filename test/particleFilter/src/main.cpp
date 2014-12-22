///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		GLHL Tests - Particle Filter
//			Author:	Pablo R.S.
//			Date:	2014-Dec-21
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main


#include <iostream>
#include <string>
#include <ctime>
	
#include "ParticleFilterCPU.h"
#include "Robot.h"

class ParticleRobot : private Particle {
public:
	ParticleRobot() :mRobot() { mRobot.setNoise(0.05, 0.05, 5.0); };
	void simulate() { mRobot.move(0.1, 5.0); };
	void calcWeigh() { mWeigh = mRobot.measurementProb(lastMasurement); };

private:
	std::array<double, 4> lastMasurement;
	Robot mRobot;
};

using namespace std;

int main(void){
	srand(unsigned(time(NULL)));

	ParticleFilterCPU<ParticleRobot> filter(1000);
	filter.init();



}

//---------------------------------------------------------------------------

