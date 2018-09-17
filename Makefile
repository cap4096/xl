SRC_DIR:=src
OBJ_DIR:=build

SRC_FILES:=$(shell find $(SRC_DIR) -name "*.cpp")
OBJ_FILES:=$(patsubst src/%.cpp,build/%.o,$(SRC_FILES))

vpath %.cpp src
vpath %.hh  src


$(OBJ_DIR)/test: $(OBJ_FILES)
	g++  $(LDFLAGS) -o $@ $^

clean:
	@rm -rf build
	@mkdir -p build
	@touch build/.empty


$(OBJ_DIR)/%.o:%.cpp
	g++ -MMD -std=c++17 -g -O0 -c -o $@ $<

-include $(OBJ_FILES:.o=.d)
