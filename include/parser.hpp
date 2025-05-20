#pragma once

#include "standard.hpp"
#include "structs.h"
#include <cfloat>
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
		float minY;
		float maxY;
		float minZ;
		float maxZ;
		void sort_and_genUv();
		void calcBound();
		void pushUV(int);
		void pushNextThreeVertex(int, std::vector<GLfloat>& sorted_vertices);
		std::vector<GLfloat> vertices;
		std::vector<t_face> faces;
		std::vector<t_uv> uv;
};
