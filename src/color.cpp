#include "../include/color.hpp"

Color::Color() {};

Color::~Color() {};

std::vector<GLfloat> Color::cycleColor(uint size){
	std::vector<GLfloat> color;
	std::vector<GLfloat> grayScale;
	int reset;
	int offset = 0;
	if (cycleIndex == 0){
		grayScale = {
			0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f
		};
		reset = 8;
	}
	else if (cycleIndex == 1){
		grayScale = {
			0.1f, 0.1f, 0.2f, 0.2f, 0.3f, 0.3f, 0.4f, 0.4f,
			0.5f, 0.5f, 0.6f, 0.6f, 0.7f, 0.7f, 0.8f, 0.8f
		};
		reset = 16;
	}
	else if (cycleIndex == 2){
		grayScale = {
			0.1f, 0.1f, 0.1f, 0.1f, 0.2f, 0.2f, 0.2f, 0.2f, 0.3f, 0.3f, 0.3f, 0.3f, 0.4f, 0.4f, 0.4f,
			0.4f, 0.5f, 0.5f, 0.5f, 0.5f, 0.6f, 0.6f, 0.6f, 0.6f, 0.7f, 0.7f, 0.7f, 0.7f, 0.8f, 0.8f,
			0.8f, 0.8f
		};
		reset = 32;
	}
	else if (cycleIndex == 3){
		grayScale = {
			0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f,
			0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f,
			0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f,
			0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f
		};
		reset = 64;
	}
	cycleIndex++;
	if (cycleIndex == 4)
		cycleIndex = 0;
	color.reserve(size);
	for (size_t i = 0; i < size; i += 3) {
		color.push_back(grayScale[offset]);
		color.push_back(grayScale[offset]);
		color.push_back(grayScale[offset]);
		offset++;
		if (offset == reset)
			offset = 0;
	}
	return color;
}
