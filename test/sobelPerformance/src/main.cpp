 //// MAIN FILE TO TEST

#include <src/core/utils/time/time.h>
#include "SobelCPU.h"
#include "SobelGPU.h"

#include <fstream>
#include <string>
#include <iostream>
#include <map>

#include <SOIL.h>

using namespace GLHL;
using namespace std;

const int REPETITIONS = 1;

map<string, string> parseArgs(int _argc, char** _argv);

int main(int _argc, char **_argv){
	map<string, string> hashMap = parseArgs(_argc, _argv);

	string imgPath = hashMap["IMG_PATH"];
	if (imgPath.compare("") == 0){
		imgPath = "./Tulips.jpg";
	}

	STime::init();
	STime *time = STime::get();

	cout << "Image characteristics: " << endl;
	cout << "\t Width = 1024" << endl;
	cout << "\t Height = 768" << endl;
	cout << "\t Channels = 1" << endl;

	int width, height, channels;
	double loadTime = 0, computeTime = 0, transferTime = 0;

	// Performance test using CPU (Simple SOBEL)
	SobelCPU sobelCPU;
	for (int i = 0; i < REPETITIONS; i++){
		double t1 = time->getTime();
		unsigned char *image = SOIL_load_image(imgPath.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);
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

	cout << "SOIL's image load spent: " << loadTime << endl;
	cout << "CPU spent: " << computeTime << endl;


	// Performance test using GPU (Simple SOBEL)
	loadTime = 0; 
	computeTime = 0;
	SobelGPU sobelGPU(1024, 768);
	sobelGPU.showWnd();
	for (int i = 0; i < REPETITIONS; i++){
		double t1 = time->getTime();
		unsigned char *image = SOIL_load_image(imgPath.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);
		double t2 = time->getTime(); 
		GpuTime gpuTime = sobelGPU.process(width, height, image);
		loadTime += t2 - t1;
		transferTime += gpuTime.mTransferTime;
		computeTime += gpuTime.mComputeTime;
	}

	loadTime /= REPETITIONS;
	computeTime /= REPETITIONS;
	transferTime /= REPETITIONS;

	cout << "SOIL's image load: " << loadTime << endl;
	cout << "Image transfer to GPU spent: " << transferTime <<endl;
	cout << "GPU spent: " << computeTime << endl;

	#ifdef _WIN32
	system("PAUSE");
	#endif

	return 0;
}



std::map<std::string, std::string> parseArgs(int _argc, char** _argv){
	std::map<std::string, std::string> hashMap;
	for (int i = 1; i < _argc; i++){
		std::string arg(_argv[i]);
		size_t next = arg.find_first_of('=');
		std::string type = arg.substr(0, next);
		arg = arg.substr(next + 1, arg.size());
		hashMap[type] = arg;
		std::cout << "Detected argument: " << type << " - With value: " << arg << std::endl;
	}
	return hashMap;
}
