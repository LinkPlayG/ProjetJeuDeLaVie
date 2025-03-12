# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -g -Werror

# SFML Libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

# Directories
SRC_DIR = src
INC_DIR = hea
TEST_DIR = tests

# Source and header files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(wildcard $(INC_DIR)/*.h)

# Executables
BINARIES = main test TBS

# Default target
all: $(BINARIES)

# Build main executable
main: $(SRCS) $(HEADERS) ./main.cpp
	$(CXX) $(CXXFLAGS) $(SRCS) main.cpp -o main $(SFML_LIBS)

# Build test executable
test: $(SRCS) $(HEADERS) $(TEST_DIR)/test.cpp
	$(CXX) $(CXXFLAGS) $(SRCS) $(TEST_DIR)/test.cpp -o test $(SFML_LIBS)

# Build TBS executable
TBS: $(SRCS) $(HEADERS) $(TEST_DIR)/troubleshooting.cpp
	$(CXX) $(CXXFLAGS) $(SRCS) $(TEST_DIR)/troubleshooting.cpp -o TBS $(SFML_LIBS)

# Clean build files
clean:
	rm -f $(BINARIES)

.PHONY: all clean
