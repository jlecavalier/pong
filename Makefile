# We are compiling pong
EXE=pong

# Main target
all: $(EXE)

#  MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall
LIBS=-lglut32cu -lglu32 -lopengl32
CLEAN=del *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall `sdl-config --cflags --libs` -lSDL_mixer
LIBS=-lglut -lGLU -lGL -lm -lSDL
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) src/*.o src/*.a $(AUX)*.o $(OBJ)*.o
endif

src/pong.o: src/pong.c src/pong.h

# Compile rules
src/%.c.o:
	gcc -c $(CFLG) $<
src/%.cpp.o:
	g++ -c $(CFLG) $<

# Link
pong:src/pong.o
	gcc -O3 -o $@ $^ $(LIBS)

# Clean
clean:
	$(CLEAN)	