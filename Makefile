CC=g++
CFLAGE= -Werror -Wall -O1 -march=native

all:
	 $(CC)  main.cpp $(CFLAGE) -o scrabble