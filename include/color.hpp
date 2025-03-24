#pragma once

#include "standard.hpp"
#include "glFunction.hpp"

class Color {
	public:
		Color();
		~Color();
		static std::vector<GLfloat> cycleColor(uint size);
	private:
		static int cycleIndex;
};
