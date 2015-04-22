SHELL = /bin/sh
INCLUDES = -Iinclude -I/usr/include
 
prefix = /usr/lib/i386-linux-gnu
# This prefix works on Kali
prefix = /usr/lib/x86_64-linux-gnu

GLUT_LIBS = $(prefix)/libglut.so.3
LDADD = $(GLUT_LIBS) $(prefix)/libGLU.so.1 $(prefix)/libGL.so.1  -lm -lstdc++ -larmadillo

CFLAGS = -g -O2 -Wall -fomit-frame-pointer -ffast-math -fexpensive-optimizations -D_REENTRANT
CPPFLAGS = -std=c++11
LINK = $(CC) $(CFLAGS) $(LDFLAGS) -o $@

SRC_DIR = /src
OBJ_DIR = /obj
CPP_FILES = $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o))) 

obj/%.o: src/%.cpp
	g++ $(INCLUDES) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

all: armadillo main

armadillo: 
	./install_armadillo.sh
.PHONY: armadillo

main: $(OBJ_FILES)
	$(LINK) $(OBJ_FILES) $(LDADD) $(LIBS)

clean:
	-rm -f $(OBJ_FILES) main

