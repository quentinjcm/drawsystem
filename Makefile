#
#turtle make file
#
OBJECTS = main.o structs.o lsys.o turtle.o ui.o
COMPILER = clang
PROGNAME = drawsystem
OUTPUT = -o
OPTIONS = -std=c99 -Wall -g -c

$(PROGNAME): $(OBJECTS)
	$(COMPILER) $(OBJECTS) -l SDL2 -l SDL2_ttf $(OUTPUT) $(PROGNAME)

structs.o: src/structs.c src/structs.h
	$(COMPILER) $(OPTIONS)  src/structs.c

lsys.o: src/lsys.c src/lsys.h
	$(COMPILER) $(OPTIONS)  src/lsys.c

turtle.o: src/turtle.c src/turtle.h
	$(COMPILER) $(OPTIONS)  src/turtle.c

ui.o: src/ui.c src/ui.h
	$(COMPILER) $(OPTIONS)  src/ui.c

main.o: src/main.c 
	$(COMPILER) $(OPTIONS)  src/main.c
	
clean:
	rm *.o

