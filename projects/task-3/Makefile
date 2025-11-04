CXX := g++
CXXFLAGS := -std=c++14 -Wall -Wextra -O2

SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)
TARGET := main

all: $(TARGET) run clean

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run:
	@./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
