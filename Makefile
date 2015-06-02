# 06/01/2015 -St
# 06/01/2015 
# SPS
# Makefile for this program

CC = gcc

OBJECTS = ed8.o modeNormal.o subNodes.o subFile.o

ed8: $(OBJECTS)
	$(CC) $(OBJECTS) -o ed8 -lncurses

ed8.o: header8.h

modeNormal.o: header8.h

subNodes.o: header8.h

subFile.o: header8.h

.PHONY: clean
clean:
	rm ed8 $(OBJECTS)

# End of Makefile