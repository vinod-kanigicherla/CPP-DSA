CXX = g++
CXXFLAGS = -Wall -g
TARGET = censor
SRC = censor.cpp
OBJ = $(SRC:.cpp=.o)
all: $(TARGET)
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)
clean:
	rm -f $(TARGET) $(OBJ)
.PHONY: all clean

