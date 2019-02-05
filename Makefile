#
# @file     Makefile
# @author   Konstantin Rebrov
# @version  07/16/2018
#
# Tower of Hanoi Project
#
# @section DESCRIPTION
#
# This is the Makefile for the Tower of Hanoi Project.
# To create the executable:
# make --makefile=Makefile
#

# Command-line options for the compiler
CXX=g++
CXXFLAGS=-g -std=c++11 -Wall -Wextra
SDL_INCLUDE=`sdl2-config --cflags`
SDL_LIBS=`sdl2-config --libs`

# Files to be processed
INCLUDE=drawer.h hanoi.h tower.h
SOURCE_FILES=main.cpp drawer.cpp hanoi.cpp tower.cpp
OBJECT_FILES=main.o drawer.o hanoi.o tower.o
EXECUTABLE=Tower_Of_Hanoi.out
MAKEFILE=Makefile

# Automatically install the SDL2 libraries.
#install_SDL2:
#	sudo apt-get install libsdl2-2.0
#	sudo apt-get install libsdl2-dev

# Builds and runs the executable all in one command!
run: $(EXECUTABLE)
	./$<

$(EXECUTABLE): $(OBJECT_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SDL_LIBS)

main.o: main.cpp $(INCLUDE)
	$(CXX) $(CXXFLAGS) -c $< $(SDL_INCLUDE)

drawer.o: drawer.cpp $(INCLUDE)
	$(CXX) $(CXXFLAGS) -c $< $(SDL_INCLUDE)

hanoi.o: hanoi.cpp hanoi.h tower.h
	$(CXX) $(CXXFLAGS) -c $< $(SDL_INCLUDE)

tower.o: tower.cpp tower.h
	$(CXX) $(CXXFLAGS) -c $< $(SDL_INCLUDE)

# Creates a tarball with the code files.
tower_of_hanoi.tar: $(SOURCE_FILES) $(INCLUDE) $(MAKEFILE)
	tar -cvf tower_of_hanoi.tar $(SOURCE_FILES) $(INCLUDE) $(MAKEFILE)

clean:
	rm -f $(OBJECT_FILES) $(EXECUTABLE)
