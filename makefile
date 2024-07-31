SRC_DIR := src
OBJ_DIR := .cache
OUT := monitor
# SRCS := $(wildcard $(SRC_DIR)/*.cpp)
SRCS := src/main.cpp src/render/render.cpp src/progress_bar.cpp
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

CXX := g++
CXXFLAGS := -g -I include -export-dynamic

run : build
	./$(OUT)

build: $(OBJS)
	g++ $(CXXFLAGS) -o $(OUT) $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm $(OBJS)

.PHONY: all clean inst source
