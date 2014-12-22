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

class ParticleRobot : public Particle {
public:
	ParticleRobot() :mRobot() { mRobot.setNoise(0.05, 0.05, 5.0); };
	void simulate() { mRobot.move(0.1, 5.0); };
	void calcWeigh() { mWeigh = mRobot.measurementProb(lastMeasurement); };

	static void setMeasurement(std::array<double, 4> _measure){ lastMeasurement = _measure; };

private:
	static std::array<double, 4> lastMeasurement;
	Robot mRobot;
};

std::array<double, 4> ParticleRobot::lastMeasurement = { 0, 0, 0, 0 };

using namespace std;

int main(void){
	srand(unsigned(time(NULL)));

	ParticleFilterCPU<ParticleRobot> filter(1000);
	filter.init();

	Robot robot;
	robot.setNoise(0.05, 0.05, 5.0);

	for (unsigned i = 0; i < 10; i++){
		robot.move(0.1, 5.0);
		ParticleRobot::setMeasurement(robot.sense());
		filter.step();
	}

	std::cout << "Finished" << std::endl;


}

//---------------------------------------------------------------------------

