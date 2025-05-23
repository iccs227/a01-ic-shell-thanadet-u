# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Output executable
TARGET = icsh

# Source files
SRCS = icsh.cpp parser.cpp builtins.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Header files
DEPS = parser.h builtins.h

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp files to .o
%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)
