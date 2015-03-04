SHELL = /bin/sh
prefix = /usr/lib/i386-linux-gnu
# This prefix works on Kali
prefix = /usr/lib/x86_64-linux-gnu
CC = gcc
C++ = g++
GLUT_LIBS = $(prefix)/libglut.so.3
X_LIBADD =  -lXmu -lXext -lXi -lX11
INCLUDES = -Iinclude -I/usr/include  
LDADD = $(GLUT_LIBS) $(prefix)/libGLU.so.1 $(prefix)/libGL.so.1  -lm -lstdc++
CFLAGS = -g -O2 -Wall -fomit-frame-pointer -ffast-math -fexpensive-optimizations -D_REENTRANT
CPPFLAGS = -std=c++11
COMPILE = $(CC) $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
LINK = $(CC) $(CFLAGS) $(LDFLAGS) -o $@

.SUFFIXES:
.SUFFIXES: .cpp .c .o 

.c.o:
	$(COMPILE) -c $<

.cpp.o:
	$(C++) $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS) -c $<

all: main

CLI_OBJECTS=main.o cli_module.o dispatcher_module.o move_module.o draw_module.o color_module.o read_module.o tiffstat_module.o tiffread_module.o tiffwrite_module.o tiff_utils.o cli_global.o signal_utils.o resize_module.o zoom_module.o

main: $(CLI_OBJECTS)
	$(LINK) $(CLI_OBJECTS) $(LDADD) $(LIBS)

clean:
	-rm -f *.o $(PROGRAMS)

