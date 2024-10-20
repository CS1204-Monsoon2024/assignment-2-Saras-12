# Makefile

# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Target executable
TARGET = main.out

# Source files
SRCS = HashTable.cpp main.cpp

# Build target
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Clean up build files
clean:
	rm -f $(TARGET)
