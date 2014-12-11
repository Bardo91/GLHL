///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Test Performance - Sobel
//
//		Author: Pablo Ramon Soria
//		Date:	2014-12-11
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sobel GPU



#include <src/core/base/WindowGL.h>
#include <src/core/base/DriverGPU.h>
#include <src/core/base/Texture.h>
#include <src/core/glsl/ShaderProgram.h>
#include <src/core/glsl/Shader.h>
#include <src/core/utils/time/time.h>

struct GpuTime{
	GpuTime(double _transferTime, double _computeTime) : mTransferTime(_transferTime), mComputeTime(_computeTime){};
	double mTransferTime = 0;
	double mComputeTime = 0;
};

class SobelGPU{
public:
	SobelGPU(unsigned _width, unsigned _height);

	GpuTime process(unsigned _width, unsigned _height, unsigned char *_image);

	void showWnd(){ mWindow.show(); };
	void hideWnd(){ mWindow.hide(); };

private:
	GLHL::WindowGL mWindow;	//	666 TODO sustitute it with a context without window
	GLHL::ShaderProgram mProgram;



};


