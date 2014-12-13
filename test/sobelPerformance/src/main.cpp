 //// MAIN FILE TO TEST

#include <src/core/utils/time/time.h>
#include "SobelCPU.h"
#include "SobelGPU.h"

#include <fstream>
#include <string>
#include <iostream>

#include <SOIL.h>

using namespace GLHL;
using namespace std;

const int REPETITIONS = 1;

int main(void){
	STime::init();
	STime *time = STime::get();

	std::cout << "Image characteristics: " << std::endl;
	std::cout << "\t Width = 1024" << std::endl;
	std::cout << "\t Height = 768" << std::endl;
	std::cout << "\t Channels = 1" << std::endl;

	int width, height, channels;
	double loadTime = 0, computeTime = 0, transferTime = 0;

	// Performance test using CPU (Simple SOBEL)
	SobelCPU sobelCPU;
	for (int i = 0; i < REPETITIONS; i++){
		double t1 = time->getTime();
		unsigned char *image = SOIL_load_image("./Tulips.jpg", &width, &height, &channels, SOIL_LOAD_AUTO);
		unsigned char *res = new unsigned char[1024 * 768 * 3];
		double t2 = time->getTime();
		sobelCPU.processImage(width, height, image, res);
		double t3 = time->getTime();
		loadTime += t2 - t1;
		computeTime += t3 - t2;
		SOIL_save_image("ResultCPU.bmp", SOIL_SAVE_TYPE_BMP, width, height, channels, res);
	}
	
	loadTime /= REPETITIONS;
	computeTime /= REPETITIONS;

	std::cout << "SOIL's image load spent: " << loadTime << std::endl;
	std::cout << "CPU spent: " << computeTime << std::endl;


	// Performance test using GPU (Simple SOBEL)
	loadTime = 0; 
	computeTime = 0;
	SobelGPU sobelGPU(1024, 768);
	//sobelGPU.showWnd();
	for (int i = 0; i < REPETITIONS; i++){
		double t1 = time->getTime();
		unsigned char *image = SOIL_load_image("./Tulips.jpg", &width, &height, &channels, SOIL_LOAD_AUTO);
		double t2 = time->getTime(); 
		GpuTime gpuTime = sobelGPU.process(width, height, image);
		loadTime += t2 - t1;
		transferTime += gpuTime.mTransferTime;
		computeTime += gpuTime.mComputeTime;
	}

	loadTime /= REPETITIONS;
	computeTime /= REPETITIONS;
	transferTime /= REPETITIONS;

	std::cout << "SOIL's image load: " << loadTime << std::endl;
	std::cout << "Image transfer to GPU spent: " << transferTime << std::endl;
	std::cout << "GPU spent: " << computeTime << std::endl;

	#ifdef _WIN32
	system("PAUSE");
	#endif

	return 0;
}


