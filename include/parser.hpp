#include "../include/scop.hpp"

class Parser {
	public:
		Parser(std::string filename);
		~Parser();
		std::vector<t_vertex> getVertices();
	private:
		std::vector<t_vertex> vertices;

};
