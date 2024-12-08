# Compiler and flags
CXX = g++
CXXFLAGS = -g -Wall -std=c++11

# Source files and target
SOURCES = solitaire.cpp mytest.cpp
HEADERS = solitaire.h
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = mytest

# Default rule to build the program
all: $(TARGET)

# Rule to link the object files and create the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Rule to compile .cpp files into .o files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

# Rule to run valgrind for memory checking
valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

# Clean up object files and the executable
clean:
	rm -f $(OBJECTS) $(TARGET)
