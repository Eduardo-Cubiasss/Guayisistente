# Makefile automático (compila todos los .cpp que encuentre)
# make        # compila todo
# ./encriptador   # ejecuta
# make clean  # limpia

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = main

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
