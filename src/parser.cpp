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
			t_vertex vertex;
			sscanf(line.c_str(), "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			this->vertices.push_back(vertex);
		}
	}
	file.close();
}

Parser::~Parser() {}

std::vector<t_vertex> Parser::getVertices() {
	return this->vertices;
}
