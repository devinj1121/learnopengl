INCFLAGS  = -I /usr/include/GLFW
INCFLAGS  += -I /usr/include/glad

LINKFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

all:
	g++ src/main.cpp src/glad.c -o ./bin/main $(INCFLAGS) $(LINKFLAGS)
	./bin/main

clean:
	rm main.cpp main.o main

