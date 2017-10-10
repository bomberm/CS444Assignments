concurrency: concurrency.o mt19937ar.o
	gcc -pthread -o concurrency concurrency.o mt19937ar.o

mt19937ar.o: mt19937ar.c
	gcc -c mt19937ar.c

concurrency.o: concurrency.c
	gcc -c concurrency.c

clean:
	rm concurrency.o concurrency mt19937ar.o
