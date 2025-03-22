#pragma once

#include "standard.hpp"
#include "structs.h"
#include "glFunction.hpp"

class Parser {
	public:
		Parser(std::string filename);
		~Parser();
		const std::vector<GLfloat>& getVertices() const;
		const std::vector<t_face>& getFaces() const;
		const std::vector<t_uv>& getUv() const;
		bool failed;
	private:
		void sort_and_genUv();
		std::vector<GLfloat> vertices;
		std::vector<t_face> faces;
		std::vector<t_uv> uv;
};
