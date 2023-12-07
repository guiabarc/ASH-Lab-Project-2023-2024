CC = gcc
FLAGS = -pg -O3

aship: aship.o
	$(CC) $(FLAGS) aship.o -o aship

aship.o: aship.c
	$(CC) -c $(FLAGS) aship.c -o aship.o

noprof: aship.c
	$(CC) -c aship.c -o aship.o
	$(CC) aship.o -o aship

run:
	aship ../data/datain.txt ../data/dataout.txt

prof: gmon.out
	gprof aship > aship.out

image: text2im.m
	octave --persist ../Matlab/text2im.m

clean:
	rm -f *.o aship gmon.out aship.out
