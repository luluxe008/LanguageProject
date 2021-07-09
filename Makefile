#to compile EVERTHING
CPP=g++
TARGET=bin/prog
DIR=src

all: $(DIR)/main.cpp
	$(CPP) $(DIR)/*.cpp -o $(TARGET)

clean:
	rm $(TARGET)
