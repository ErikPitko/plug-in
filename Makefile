CFLAGS=-std=c99 -Wall -g -fPIC

all: program plugin.so

program: program.o
	cc program.o -o program -ldl
plugin.so: plugin.o
	cc plugin.o -shared -fPIC -o plugin.so
clean:
	rm *.o *.so
dep:
	cc -MM *.c >>Makefile
plugin.o: plugin.c pluginapi.h
program.o: program.c pluginapi.h
