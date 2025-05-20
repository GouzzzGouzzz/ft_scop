#include "../include/parser.hpp"

Parser::Parser(std::string filename) {
	std::string line;
	std::ifstream file(filename);
	this->failed = false;
	this->minY = FLT_MAX;
	this->maxY = -FLT_MAX;
	this->minZ = FLT_MAX;
	this->maxZ = -FLT_MAX;
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

void Parser::calcBound(){
	for (size_t i = 0; i < this->vertices.size(); i += 3) {
		float y = this->vertices[i + 1];
		float z = this->vertices[i + 2];
		if (y < this->minY)
			this->minY = y;
		if (y > this->maxY)
			this->maxY = y;
		if (z < this->minZ)
			this->minZ = z;
		if (z > this->maxZ)
			this->maxZ = z;
	}
}

void Parser::pushUV(int index) {
	float u, v;
	u = (this->vertices[index + 1] - minY) / (maxY - minY);
	v = (this->vertices[index + 2] - minZ) / (maxZ - minZ);
	uv.push_back({u, v});
}

void Parser::pushNextThreeVertex(int index, std::vector<GLfloat>& sorted_vertices) {
	sorted_vertices.push_back(this->vertices[index]);
	sorted_vertices.push_back(this->vertices[index + 1]);
	sorted_vertices.push_back(this->vertices[index + 2]);
}

void Parser::sort_and_genUv() {
	std::vector<GLfloat> sorted_vertices;
	int index;
	sorted_vertices.reserve(this->vertices.size());
	calcBound();
	for (std::vector<t_face>::iterator it = this->faces.begin(); it != this->faces.end(); it++) {
		index = (it->v1 - 1) * 3;
		pushUV(index);
		pushNextThreeVertex(index, sorted_vertices);
		index = (it->v2 - 1) * 3;
		pushUV(index);
		pushNextThreeVertex(index, sorted_vertices);
		index = (it->v3 - 1) * 3;
		pushUV(index);
		pushNextThreeVertex(index, sorted_vertices);

		if (it->v4  != 0){
			index = (it->v1 - 1) * 3;
			pushUV(index);
			pushNextThreeVertex(index, sorted_vertices);

			index = (it->v3 - 1) * 3;
			pushUV(index);
			pushNextThreeVertex(index, sorted_vertices);

			index = (it->v4 - 1) * 3;
			pushUV(index);
			pushNextThreeVertex(index, sorted_vertices);
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
