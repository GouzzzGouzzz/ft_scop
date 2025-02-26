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
			face.v1 = 0;
			face.v2 = 0;
			face.v3 = 0;
			face.v4 = 0;
			sscanf(line.c_str(), "f %d %d %d %d", &face.v1, &face.v2, &face.v3, &face.v4);
			this->faces.push_back(face);
		}
	}
	file.close();
	sort_vertices_by_faces();
}

void Parser::sort_vertices_by_faces() {
	std::vector<GLfloat> sorted_vertices;
	int index;
	int test=0;
	for (std::vector<t_face>::iterator it = this->faces.begin(); it != this->faces.end(); it++) {
		index = (it->v1- 1) * 3;
		sorted_vertices.push_back(this->vertices[index]);
		sorted_vertices.push_back(this->vertices[index + 1]);
		sorted_vertices.push_back(this->vertices[index + 2]);
		index = (it->v2- 1) * 3;
		sorted_vertices.push_back(this->vertices[index]);
		sorted_vertices.push_back(this->vertices[index + 1]);
		sorted_vertices.push_back(this->vertices[index + 2]);
		index = (it->v3- 1) * 3;
		sorted_vertices.push_back(this->vertices[index]);
		sorted_vertices.push_back(this->vertices[index + 1]);
		sorted_vertices.push_back(this->vertices[index + 2]);
		if (it->v4 != 0) {
			test++;
			index = (it->v1- 1) * 3;
			sorted_vertices.push_back(this->vertices[index]);
			sorted_vertices.push_back(this->vertices[index + 1]);
			sorted_vertices.push_back(this->vertices[index + 2]);

			index = (it->v3- 1) * 3;
			sorted_vertices.push_back(this->vertices[index]);
			sorted_vertices.push_back(this->vertices[index + 1]);
			sorted_vertices.push_back(this->vertices[index + 2]);

			index = (it->v4- 1) * 3;
			sorted_vertices.push_back(this->vertices[index]);
			sorted_vertices.push_back(this->vertices[index + 1]);
			sorted_vertices.push_back(this->vertices[index + 2]);
		}
	}
	this->vertices = sorted_vertices;
}

Parser::~Parser() {}

std::vector<GLfloat> Parser::getVertices() {
	return this->vertices;
}

std::vector<t_face> Parser::getFaces() {
	return this->faces;
}
