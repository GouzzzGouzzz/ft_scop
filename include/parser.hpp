#pragma once


#include "../include/scop.hpp"

class Parser {
	public:
		Parser(std::string filename);
		~Parser();
		const std::vector<GLfloat>& getVertices() const;
		const std::vector<t_face>& getFaces() const;
		bool failed;
	private:
		void sort_vertices_by_faces();
		std::vector<GLfloat> vertices;
		std::vector<t_face> faces;

};
