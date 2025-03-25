#include "../include/color.hpp"

Color::Color() {};

Color::~Color() {};

std::vector<GLfloat> Color::cycleColor(uint size){
	static int cycleIndex = 0;
	int reset;
	int offset = 0;
	std::vector<GLfloat> color;
	std::vector<std::vector<float>> grayScale = {
		{ 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f },
		{ 0.1f, 0.1f, 0.2f, 0.2f, 0.3f, 0.3f, 0.4f, 0.4f,
		  0.5f, 0.5f, 0.6f, 0.6f, 0.7f, 0.7f, 0.8f, 0.8f },
		{ 0.1f, 0.1f, 0.1f, 0.1f, 0.2f, 0.2f, 0.2f, 0.2f, 0.3f, 0.3f, 0.3f, 0.3f,
		  0.4f, 0.4f, 0.4f, 0.4f, 0.5f, 0.5f, 0.5f, 0.5f, 0.6f, 0.6f, 0.6f, 0.6f,
		  0.7f, 0.7f, 0.7f, 0.7f, 0.8f, 0.8f, 0.8f, 0.8f },
		{ 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.2f, 0.2f, 0.2f, 0.2f,
		  0.2f, 0.2f, 0.2f, 0.2f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f,
		  0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.5f, 0.5f, 0.5f, 0.5f,
		  0.5f, 0.5f, 0.5f, 0.5f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f,
		  0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.7f, 0.8f, 0.8f, 0.8f, 0.8f,
		  0.8f, 0.8f, 0.8f, 0.8f }
	};

	if (cycleIndex == 0)
		reset = 8;
	else if (cycleIndex == 1)
		reset = 16;
	else if (cycleIndex == 2)
		reset = 32;
	else if (cycleIndex == 3)
		reset = 64;

	cycleIndex = (cycleIndex + 1) % 4;

	std::cout << "using :" << reset << " grayscale" << std::endl;
	color.reserve(size);
	for (size_t i = 0; i < size; i += 3) {
		color.push_back(grayScale[cycleIndex][offset]);
		color.push_back(grayScale[cycleIndex][offset]);
		color.push_back(grayScale[cycleIndex][offset]);
		offset++;
		if (offset == reset)
			offset = 0;
	}

	return color;
}
