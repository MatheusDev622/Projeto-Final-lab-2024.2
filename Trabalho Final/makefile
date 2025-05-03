all: main.e

main.e: main.c kmeans.o pgm.o utils.o
	gcc -o main.e main.c kmeans.o pgm.o utils.o

histograma.e: histogram.c pgm.o
	gcc -o histograma.e histograma.c pgm.o

kmeans.o: kmeans.c pgm.o utils.o 
	gcc -o kmeans.o -c kmeans.c

pgm.o: pgm.c
	gcc -o pgm.o -c pgm.c

utils.o: utils.c
	gcc -o utils.o -c utils.c

clean:
	rm -f main.e main.o kmeans.o pgm.o utils.o