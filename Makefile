NAME=scop
CXX=g++
CXXFLAGS=-g -Wall -Werror -Wextra
CXXLINKFLAGS=-lGL -lglfw
OBJ_DIR=obj
SRC_DIR=src
FILES=main.cpp\
	parser.cpp\
	loadShader.cpp\
	glFunctions.cpp\
	matrix4.cpp\
	moreMath.cpp\
	renderData.cpp\
	quaternion.cpp\
	draw.cpp\
	color.cpp\
	init.cpp\
	controller.cpp\
	textureLoader.cpp\

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

re: fclean all

.PHONY: all re clean fclean
