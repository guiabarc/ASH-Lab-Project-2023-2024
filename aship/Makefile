CC = gcc
FLAGS = -O3 -pg -fprofile-arcs

INPUT = ../data/datain.txt
OUTPUT = ../data/dataout.txt

aship: aship.o
	$(CC) $(FLAGS) aship.o -o aship

aship.o: aship.c
	$(CC) -c $(FLAGS) aship.c -o aship.o

noprof:
	$(CC) -c aship.c -o aship.o
	$(CC) aship.o -o aship

run:
	-../aship/aship  $(INPUT) $(OUTPUT)

prof: run
	gprof aship gmon.out > profile.txt

image:
	octave --persist ../Matlab/text2im.m

clean:
	rm -f *.o aship gmon.out aship.out profile.txt aship.gcda