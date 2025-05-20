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
		float minY = FLT_MAX;
		float maxY = -FLT_MAX;
		float minZ = FLT_MAX;
		float maxZ = -FLT_MAX;
		void sort_and_genUv();
		void caclBound();
		void pushUV(int);
		void pushNextThreeVertex(int, std::vector<GLfloat>& sorted_vertices);
		std::vector<GLfloat> vertices;
		std::vector<t_face> faces;
		std::vector<t_uv> uv;
};
