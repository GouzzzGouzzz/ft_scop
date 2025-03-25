#include "../include/textureLoader.hpp"

GLuint TextureLoader::cycleTextureDir(){
	static int index = -1;
	static std::string path = "textures/";
	static std::vector<std::string> files;
	if (index == -1){
		for (const std::filesystem::__cxx11::directory_entry& entry : std::filesystem::directory_iterator(path)) {
			if (!entry.is_directory()) {
				if (entry.path().filename().string().find(".bmp") != std::string::npos) {
					files.push_back(entry.path().filename().string());
				}
			}
		}
		index = 0;
	}
	if (files.size() == 0){
		std::cerr << "No texture found in textures directory" << std::endl;
		return 0;
	}
	GLuint texture = 0;
	int failed = -1;
	do{
		failed++;
		if (failed == files.size()){
			std::cerr << "Failed to load any texture" << std::endl;
			return 0;
		}
		texture = loadTexture((path + files[index]).c_str());
		if (texture != 0)
			std::cout << "loaded texute : " << files[index] << std::endl;
		index++;
		if (index == files.size())
			index = 0;
	} while (texture == 0);
	return texture;
}

//return a texture ID to use with opegGL
//load a BMP file using our custom loader
GLuint TextureLoader::loadTexture(const char* imagepath){
	char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char * data;
	std::ifstream file(imagepath);
	if (!file.is_open()) {
		std::cerr << "Failed to open texutre file" << std::endl;
		return 0;
	}
	file.read(header, 54);
	if (file.gcount() != 54){
		std::cerr << "Failed to read file header" << std::endl;
		return 0;
	}
	if ( header[0] != 'B' || header[1] != 'M' ){
		std::cerr << "Invalid BMP file" << std::endl;
		return 0;
	}
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	if (imageSize == 0)
		imageSize = width * height * 3;
	if (dataPos == 0)
		dataPos = 54;
	data = new unsigned char[imageSize];
	file.read((char*)data, imageSize);
	file.close();

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	//filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	delete[] data;
	return textureID;
}
