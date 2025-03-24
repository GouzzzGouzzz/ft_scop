#include "../include/parser.hpp"

Parser::Parser(std::string filename) {
	std::string line;
	std::ifstream file(filename);
	this->failed = false;
	if (!file.is_open()) {
		std::cerr << "Failed to open file" << std::endl;
		this->failed = true;
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
	sort_and_genUv();
}

void Parser::sort_and_genUv() {
	std::vector<GLfloat> sorted_vertices;
	int index;
	const float basic_uv[2] = {0.0f, 1.0f};
	sorted_vertices.reserve(this->vertices.size());

	for (std::vector<t_face>::iterator it = this->faces.begin(); it != this->faces.end(); it++) {

		index = (it->v1 - 1) * 3;
		uv.push_back({(this->vertices[index] + 1.0f * 0.5f),(this->vertices[index+2] + 1.0f * 0.5f)});
		sorted_vertices.push_back(this->vertices[index]);
		sorted_vertices.push_back(this->vertices[index + 1]);
		sorted_vertices.push_back(this->vertices[index + 2]);
		index = (it->v2 - 1) * 3;
		uv.push_back({(this->vertices[index] + 1.0f * 0.5f),(this->vertices[index+2] + 1.0f * 0.5f)});
		sorted_vertices.push_back(this->vertices[index]);
		sorted_vertices.push_back(this->vertices[index + 1]);
		sorted_vertices.push_back(this->vertices[index + 2]);
		index = (it->v3 - 1) * 3;
		uv.push_back({(this->vertices[index] + 1.0f * 0.5f),(this->vertices[index+2] + 1.0f * 0.5f)});
		sorted_vertices.push_back(this->vertices[index]);
		sorted_vertices.push_back(this->vertices[index + 1]);
		sorted_vertices.push_back(this->vertices[index + 2]);
		if (it->v4  != 0){
			index = (it->v1 - 1) * 3;
			uv.push_back({(this->vertices[index] + 1.0f * 0.5f),(this->vertices[index+2] + 1.0f * 0.5f)});
			sorted_vertices.push_back(this->vertices[index]);
			sorted_vertices.push_back(this->vertices[index + 1]);
			sorted_vertices.push_back(this->vertices[index + 2]);

			index = (it->v3 - 1) * 3;
			uv.push_back({(this->vertices[index] + 1.0f * 0.5f),(this->vertices[index+2] + 1.0f * 0.5f)});
			sorted_vertices.push_back(this->vertices[index]);
			sorted_vertices.push_back(this->vertices[index + 1]);
			sorted_vertices.push_back(this->vertices[index + 2]);

			index = (it->v4 - 1) * 3;
			uv.push_back({(this->vertices[index] + 1.0f * 0.5f),(this->vertices[index+2] + 1.0f * 0.5f)});
			sorted_vertices.push_back(this->vertices[index]);
			sorted_vertices.push_back(this->vertices[index + 1]);
			sorted_vertices.push_back(this->vertices[index + 2]);
		}
	}
	this->vertices = sorted_vertices;
}

Parser::~Parser() {}

std::vector<GLfloat>& Parser::getVertices() {
	return this->vertices;
}

std::vector<t_face>& Parser::getFaces(){
	return this->faces;
}

std::vector<t_uv>& Parser::getUv(){
	return this->uv;
}
