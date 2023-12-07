CC = gcc
FLAGS = -pg -O3

aship: aship.o
	$(CC) $(FLAGS) aship.o -o aship

aship.o: aship.c
	$(CC) -c $(FLAGS) aship.c -o aship.o

noprof:
	$(CC) -c aship.c -o aship.o
	$(CC) aship.o -o aship

run:
	-../aship/aship ../data/datain.txt ../data/dataout.txt

prof: run
	gprof aship > aship.out

image:
	octave --persist ../Matlab/text2im.m

clean:
	rm -f *.o aship gmon.out aship.out
