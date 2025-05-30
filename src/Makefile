# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Output executable
TARGET = icsh

# Source files
SRCS = icsh.cpp parser.cpp builtins.cpp cmd_exec.cpp signal_handler.cpp io_redirect.cpp jobs.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Header files
DEPS = parser.h builtins.h cmd_exec.h icsh.h signal_handler.h io_redirect.h jobs.h

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
