INCFLAGS  = -I ./include

LINKFLAGS = -L ./lib
LINKFLAGS += -lglfw -lassimp -lX11 -lpthread -lXrandr -lXi -ldl

all:
	g++ -Wall ./src/*.cpp ./src/*.c -o ./bin/main $(INCFLAGS) $(LINKFLAGS)
	./bin/main

clean:
	rm main.cpp main.o main