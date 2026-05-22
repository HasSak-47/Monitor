OUT := lytop

SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include

LUI_DIR := lui
LUI_LIB := $(LUI_DIR)/lib/liblui.a
LUI_INCLUDE := $(LUI_DIR)/include

CXX ?= g++
AR := ar
PKG_CONFIG := pkg-config
LUA_CFLAGS := $(shell $(PKG_CONFIG) --cflags lua5.4)
LUA_LIBS := $(shell $(PKG_CONFIG) --libs lua5.4)
CFLAGS := -g -pg -O2 -I"$(INCLUDE_DIR)" -I"$(LUI_INCLUDE)" $(LUA_CFLAGS) -std=c++23 -MMD -MP -c
LDFLAGS := -L"$(LUI_DIR)/lib" -llui $(LUA_LIBS)
LDOUT := -o "$(OUT)"

# Gather all .cpp source files
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

.DEFAULT_GOAL := build

-include $(OBJS:.o=.d)

.PHONY: build all compile clean run valgrind

build: $(LUI_LIB) all

# Default build
all: $(OUT)


compile: all

# Final binary links main + lib
$(OUT): $(OBJS) $(LUI_LIB)
	$(CXX) $(OBJS) $(LDOUT) $(LDFLAGS)

# Static lib from lui subproject
$(LUI_LIB):
	$(MAKE) -C $(LUI_DIR) libonly

# Compile .cpp to .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p "$(dir $@)"
	$(CXX) $(CFLAGS) -o $@ $<

run: $(build) $(OUT)
	./$(OUT)

valgrind: $(OUT)
	valgrind ./$(OUT)

clean:
	@rm -rf "$(BUILD_DIR)" "$(OUT)"
	$(MAKE) -C $(LUI_DIR) clean
