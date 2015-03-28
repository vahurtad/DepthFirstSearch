#
# Vanessa Hurtado
#

BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -c  -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f

FindComponents : FindComponents.o $(BASE_OBJECTS)
	$(LINK) FindComponents FindComponents.o $(BASE_OBJECTS)

GraphTest : GraphTest.o $(BASE_OBJECTS)
	$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

FindPath.o : FindComponents.c $(HEADERS)
	$(COMPILE) FindComponents.c -g

GraphTest.o : GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c -g

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) FindComponents GraphTest FindComponents.o GraphTest.o $(BASE_OBJECTS)

submit : List.c List.h FindComponents.c Graph.c Graph.h Makefile README
	submit cmps101-pt.w15 pa5 $(HEADERS) $(BASE_SOURCES) GraphTest.c FindComponents.c Makefile README
