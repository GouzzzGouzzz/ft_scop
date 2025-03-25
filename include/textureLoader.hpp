#pragma once

#include "glFunction.hpp"
#include "standard.hpp"

class TextureLoader {
	public:
		static GLuint cycleTextureDir();
	private:
		static GLuint loadTexture(const char* path);
};
