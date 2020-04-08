#This is the Makefile to use for Homework Assignment #6
# To use, at the prompt, type:
#
#       make Calc               # This will make executable Calc
# or
#       make Driver             # This will make executable Driver
# or
#       make clean              # This will safely remove old stuff
Driver:	Driver.o Hash.o
	g++ -o Driver -g Driver.o Hash.o
Driver.o:	Base.h Driver.c Hash.h SymTab.h
	g++ -g -c Driver.c
Hash.o:	Base.h Hash.c Hash.h SymTab.h
	g++ -g -c Hash.c
List.o:	Base.h List.c List.h
	g++ -g -c List.c
Stack.o: Base.h List.h Stack.c Stack.h
	g++ -g -c Stack.c
valgrind_Driver: Driver
	valgrind --leak-check=full --read-var-info=yes \
	    --show-reachable=yes ./Driver $(DEBUG)
clean:
	rm -f *.o Driver 
new:
	make clean
	make