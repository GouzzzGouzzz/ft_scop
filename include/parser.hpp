#include "../include/scop.hpp"

class Parser {
	public:
		Parser(std::string filename);
		~Parser();
		std::vector<t_vertex> getVertices();
		std::vector<t_face> getFaces();
	private:
		std::vector<t_vertex> vertices;
		std::vector<t_face> faces;

};
