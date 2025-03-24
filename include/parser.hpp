#pragma once

#include "standard.hpp"
#include "structs.h"
#include "glFunction.hpp"

class Parser {
	public:
		Parser(std::string filename);
		~Parser();
		std::vector<GLfloat>& getVertices();
		std::vector<t_face>& getFaces();
		std::vector<t_uv>& getUv() ;
		bool failed;
	private:
		void sort_and_genUv();
		std::vector<GLfloat> vertices;
		std::vector<t_face> faces;
		std::vector<t_uv> uv;
};
