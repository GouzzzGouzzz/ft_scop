#include "../include/parser.hpp"

Parser::Parser(std::string filename) {
	std::string line;
	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cerr << "Failed to open file" << std::endl;
		return ;
	}
	while (std::getline(file, line)) {
		if (line[0] == 'v' && line[1] == ' ') {
			GLfloat x,y,z;
			sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
			this->vertices.push_back(x);
			this->vertices.push_back(y);
			this->vertices.push_back(z);
		}
		if (line[0] == 'f' && line[1] == ' ') {
			t_face face;
			sscanf(line.c_str(), "f %d %d %d %d", &face.v1, &face.v2, &face.v3, &face.v4);
			this->faces.push_back(face);
		}
	}
	file.close();
}

Parser::~Parser() {}

std::vector<GLfloat> Parser::getVertices() {
	return this->vertices;
}

std::vector<t_face> Parser::getFaces() {
	return this->faces;
}
