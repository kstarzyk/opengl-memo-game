CXX = g++
CXXFLAGS = -Wall -std=c++11
LDLIBS = -lglfw -lGL -lGLU -lGLEW -lX11 -lXxf86vm -lpthread -lXrandr -lXi

LIB_DIR = -L/usr/lib/
INC_DIR = -I/usr/local/include/ -I/usr/local/include/GLFW/

OBJ_DIR = bin
SOURCE = $(wildcard *.cpp) 
COMMON_SOURCE = common/shader.cpp
OBJECTS = ${SOURCE:%.cpp=$(OBJ_DIR)/%.o} ${COMMON_SOURCE:%.cpp=$(OBJ_DIR)/%.o}
EXECUTABLE = memo

all: init $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE):
	$(CXX) $(LDFLAGS) $(LIB_DIR) -o $@ $(OBJECTS) $(LDLIBS)

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC_DIR) -c $< -o $@

init:
	@mkdir -p "$(OBJ_DIR)"
	@mkdir -p "$(OBJ_DIR)/common"

clean:
	@rm -rf $(OBJ_DIR) $(EXECUTABLE)
