CC=clang++

Concurrency: concurrency3.cpp sharedResource.o generalHelpers.o listHelper.o
	$(CC) -std=c++11 -stdlib=libc++ -lpthread -o Concurrency concurrency3.cpp sharedResource.o generalHelpers.o listHelper.o

sharedResource: sharedResource.cpp sharedResource.
	$(CC) -std=c++11 -stdlib=libc++ -c sharedResource.cpp 

generalHelpers: generalHelpers.cpp generalHelpers.h
	$(CC) -std=c++11 -stdlib=libc++ -c generalHelpers.cpp

listHelper: listHelper.cpp listHelper.h
	$(CC) -std=c++11 -c -stdlib=libc++ listHelper.cpp

clean: 
	rm Concurrency generalHelpers.o sharedResource.o


