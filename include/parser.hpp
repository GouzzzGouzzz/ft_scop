#include "../include/scop.hpp"

class Parser {
	public:
		Parser(std::string filename);
		~Parser();
		std::vector<GLfloat> getVertices();
		std::vector<t_face> getFaces();
	private:
		void sort_vertices_by_faces();
		std::vector<GLfloat> vertices;
		std::vector<t_face> faces;

};
