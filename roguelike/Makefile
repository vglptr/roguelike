LIBS=-lglfw3 -DGLEW_STATIC -lGLEW -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread
#DEBUG_OPTIONS=-ggdb
OPTIMISATION=-O3

all:
	g++ -std=c++11 $(OPTIMISATION) start.cpp $(LIBS) $(DEBUG_OPTIONS) -o roguelike.exe

