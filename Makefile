#  MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW
LIBS=-lfreeglut -lglew32 -lglu32 -lopengl32
INCLUDES=-I./glm   # Relative path to the glm directory
CLEAN=rm *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations -DRES=2
LIBS=-framework GLUT -framework OpenGL -lglm
#INCLUDES=-I/path/to/glm   # Add the correct path to the GLM headers
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm -lglm
#INCLUDES=-I/path/to/glm   # Add the correct path to the GLM headers
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f gears *.o *.a
endif

#  Compile and link
main: main.cpp
	gcc $(CFLG) -o $@ $^ $(INCLUDES) $(LIBS)

#  Clean
clean:
	$(CLEAN)
