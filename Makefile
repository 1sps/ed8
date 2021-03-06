# 06/01/2015 -St
# 06/01/2015 
# SPS
# Makefile for this program

CC = gcc

OBJECTS = ed8.o modeNormal.o subFile.o modeInsert.o modeCommand.o navigate.o

ed8: $(OBJECTS)
	$(CC) $(OBJECTS) -o ed8 -lncurses

ed8.o: header8.h

modeNormal.o: header8.h

subFile.o: header8.h

modeInsert.o: header8.h

modeCommand.o: header8.h

navigate.o: header8.h

.PHONY: clean
clean:
	-rm $(OBJECTS)
	rm ed8

# End of Makefile
