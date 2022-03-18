CC	= g++
CFLAGS	= -Wall -g
INCLUDE	= ./include
LIBS	= -lglfw3 -lGL -lGLU -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -ldl -lXi

FILES 	= $(wildcard ./src/*.cpp)
OBJS	= $(patsubst ./src/%.cpp,./%.o,$(FILES))

all:	main clean run

main:	$(OBJS)
	$(CC) $(CFLAGS) -o ./build/$@ $(OBJS) -I $(INCLUDE) $(LIBS)

./%.o: ./src/%.cpp
	$(CC) $(CFLAGS) -c $^ -I $(INCLUDE) $(LIBS)

clean:
	rm -f *.o
	echo "Clean done"

run:
	./build/main
