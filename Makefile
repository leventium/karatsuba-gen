TARGET := app

SRCS := $(wildcard src/*.cpp)

OBJS := $(SRCS:.cpp=.o)

INCLUDE_DIR := src/include

CXX := g++

CXXFLAGS := -std=c++17 -I$(INCLUDE_DIR)

LDFLAGS :=

all: build

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $(TARGET)
	@echo "\n\nRun: ./$(TARGET) N"

clean:
	rm -rf src/*.o $(TARGET)

.PHONY: clean, build
