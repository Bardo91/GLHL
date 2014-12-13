///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Test Performance - Sobel
//
//		Author: Pablo Ramon Soria
//		Date:	2014-12-11
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sobel CPU

#include <array>
#include <cstdint>
#include <math.h>

std::array<int8_t, 9> sobelH = {	1, 2, 1, 
									0, 0, 0, 
									-1, -2, -1 };
std::array<int8_t, 9> sobelV = {	-1, 0, 1, 
									-2, 0, 2, 
									-1, 0, 1 };

class SobelCPU{
public:
	void processImage(const unsigned &_width, const unsigned &_height, const std::uint8_t *_image, std::uint8_t *_res);

private:
	

};

inline void SobelCPU::processImage(const unsigned &_width, const unsigned &_height, const std::uint8_t *_image, std::uint8_t *_res){
	// 666 TODO: only 1 channel
	for (unsigned i = 1; i < _height - 1; i++){
		for (unsigned j = 1; j < _width - 1; j++){
			unsigned char c1 = _image[((i - 1)*_width)*3	+ (j - 1)*3 + 0];
			unsigned char c2 = _image[((i - 1)*_width)*3	+ (j	)*3 + 0];
			unsigned char c3 = _image[((i - 1)*_width)*3	+ (j + 1)*3 + 0];
			unsigned char c4 = _image[((i	)*_width)*3		+ (j - 1)*3 + 0];
			unsigned char c5 = _image[((i	)*_width)*3		+ (j	)*3 + 0];
			unsigned char c6 = _image[((i	)*_width)*3		+ (j + 1)*3 + 0];
			unsigned char c7 = _image[((i + 1)*_width)*3	+ (j - 1)*3 + 0];
			unsigned char c8 = _image[((i + 1)*_width)*3	+ (j	)*3 + 0];
			unsigned char c9 = _image[((i + 1)*_width)*3	+ (j + 1)*3 + 0];

			int Gx = sobelH[0] * c1 +
				sobelH[1] * c2 +
				sobelH[2] * c3 +
				sobelH[3] * c4 +
				sobelH[4] * c5 +
				sobelH[5] * c6 +
				sobelH[6] * c7 +
				sobelH[7] * c8 +
				sobelH[8] * c9;

			int Gy = sobelV[0] * c1 +
				sobelV[1] * c2 +
				sobelV[2] * c3 +
				sobelV[3] * c4 +
				sobelV[4] * c5 +
				sobelV[5] * c6 +
				sobelV[6] * c7 +
				sobelV[7] * c8 +
				sobelV[8] * c9;



			double val = sqrt( double(Gx*Gx + Gy*Gy));

			if (val > 0.3 * 255){
				_res[((i)*_width) * 3 + j*3 + 0] = 255;
				_res[((i)*_width) * 3 + j*3 + 1] = 255;
				_res[((i)*_width) * 3 + j*3 + 2] = 255;
			}
			else{
				_res[((i)*_width) * 3 + j*3 + 0] = 0;
				_res[((i)*_width) * 3 + j*3 + 1] = 0;
				_res[((i)*_width) * 3 + j*3 + 2] = 0;
			}

		}
	}

}