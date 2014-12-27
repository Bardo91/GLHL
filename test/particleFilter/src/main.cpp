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
	
#include <src/core/base/Context.h>

#include "ParticleFilterGPU.h"
#include "ParticleFilterCPU.h"
#include "Robot.h"

class ParticleRobot : public Particle {
public:
	ParticleRobot() :mRobot() { mRobot.setNoise(0.05, 0.05, 5.0); };
	void simulate() { mRobot.move(0.1, 5.0); };
	void calcWeigh(Particle &_realParticle) { mWeigh = mRobot.measurementProb(static_cast<ParticleRobot &>(_realParticle).sense()); };

	std::array<double, 3> position() { return mRobot.position(); };
private:
	std::array<double, 4> sense() { return mRobot.sense(); };
	
private:
	Robot mRobot;
};
//---------------------------------------------------------------------------------------------------------------------
using namespace std;
using namespace GLHL;

//---------------------------------------------------------------------------------------------------------------------
std::array<double, 3> mediumState(std::vector<ParticleRobot> _particles);
void particleFilterCPU();
void particleFilterGPU();

//---------------------------------------------------------------------------------------------------------------------
int main(void){
	
	//particleFilterCPU();
	
	particleFilterGPU();

	std::cout << "Finished" << std::endl;
	
	system("PAUSE");

}

//---------------------------------------------------------------------------------------------------------------------

std::array<double, 3> mediumState(std::vector<ParticleRobot> _particles){
	std::array<double, 3> position = {0.0, 0.0, 0.0};
	for (unsigned i = 0; i < 1000; i++){
		std::array<double, 3> pos = _particles[i].position();
		position[0] += pos[0];
		position[1] += pos[1];
		position[2] += pos[2];
	}
	position[0] /= 1000;
	position[1] /= 1000;
	position[2] /= 1000;

	return position;
}

void particleFilterCPU() {
	srand(unsigned(time(NULL)));

	ParticleFilterCPU<ParticleRobot> filter(1000);
	filter.init();

	ParticleRobot robot;

	for (unsigned i = 0; i < 10; i++) {
		robot.simulate();
		filter.step(robot);

		std::array<double, 3> medState = mediumState(filter.particles());
		std::array<double, 3> realState = robot.position();
		std::cout << "-------------------------------------------------------------------" << std::endl;
		std::cout << "Real state. X:" << realState[0] << " ; Y: " << realState[1] << " ; Ori: " << realState[2] << std::endl;
		std::cout << "Promediate state. X:" << medState[0] << " ; Y: " << medState[1] << " ; Ori: " << medState[2] << std::endl;
	}
}

void particleFilterGPU() {
	srand(unsigned(time(NULL)));
	Context context;

	// 666 TODO Relative path to vertex shader?
	ParticleFilterGPU pfGPU(1000, "../../src/shaders/particleFilterShaderTemplate.fragment");

	//for (unsigned i = 0; i < 10; i++) {
	//	pfGPU.step();
	//}
}