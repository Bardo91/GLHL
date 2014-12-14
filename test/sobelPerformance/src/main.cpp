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

	int width, height, channels;
	double computeTime = 0, transferTime = 0;

	STime::init();
	STime *time = STime::get();

	double t1 = time->getTime();
	unsigned char *image = SOIL_load_image(imgPath.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);
	unsigned char *res = new unsigned char[width * height * channels];
	double t2 = time->getTime();

	cout << "Image characteristics: " << endl;
	cout << "\t Width = " << width << endl;
	cout << "\t Height = " << height << endl;
	cout << "\t Channels = " << channels << endl;

	cout << "SOIL's image load spent: " << t2 - t1 << endl;

	// Performance test using CPU (Simple SOBEL)
	SobelCPU sobelCPU;
	for (int i = 0; i < REPETITIONS; i++){
		double t1 = time->getTime();
		sobelCPU.processImage(width, height, image, res);
		double t2 = time->getTime();
		computeTime += t2 - t1;
		SOIL_save_image("ResultCPU.bmp", SOIL_SAVE_TYPE_BMP, width, height, channels, res);
	}
	
	computeTime /= REPETITIONS;
	
	cout << "CPU spent: " << computeTime << endl;


	// Performance test using GPU (Simple SOBEL)
	computeTime = 0;
	SobelGPU sobelGPU(width, height);
	sobelGPU.showWnd();
	for (int i = 0; i < REPETITIONS; i++){
		GpuTime gpuTime = sobelGPU.process(width, height, image);
		transferTime += gpuTime.mTransferTime;
		computeTime += gpuTime.mComputeTime;
	}

	computeTime /= REPETITIONS;
	transferTime /= REPETITIONS;

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
