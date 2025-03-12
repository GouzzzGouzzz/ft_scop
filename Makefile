NAME=scop
TESTNAME=test
CXX=g++
CXXFLAGS=-g #-Wall -Werror -Wextra
CXXLINKFLAGS=-lglfw -lGL
OBJ_DIR=obj
SRC_DIR=src
FILES=main.cpp\
	parser.cpp\
	loadShader.cpp\
	glFunctions.cpp\
	matrix4.cpp\
	moreMath.cpp\
	renderData.cpp\

SRC=$(FILES:%=$(SRC_DIR)/%.cpp)
OBJ=$(FILES:%.cpp=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) -c $(CXXFLAGS) -o $@ $<


$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(CXXLINKFLAGS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(TESTNAME)

re: fclean all

test:
	g++ -o $(TESTNAME) test.cpp -lstdc++ -lm

.PHONY: all re clean fclean test
