SRC_DIR:=src 
OBJ_DIR:=build

SRC_FILES:=$(shell find $(SRC_DIR) -name "*.cpp")
OBJ_FILES:=$(patsubst src/%.cpp,build/%.o,$(SRC_FILES))
CXXFLAGS=-std=c++17

vpath %.cpp src
vpath %.hh  src


test: $(OBJ_FILES)
	g++  $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o:%.cpp
	g++ -MMD $(ĆXXFLAGS) -c -o $@ $<

-include $(OBJ_FILES:.o=.d)

