Concurrency: concurrency3.cpp sharedResource.o generalHelpers.o
	g++ -std=c++11 -lpthread -o Concurrency concurrency3.cpp sharedResource.o generalHelpers.o

sharedResource: sharedResource.cpp
	g++ -c sharedResource.cpp -std=c++11

generalHelpers: generalHelpers.cpp
	g++ -c generalHelpers.cpp -std=c++11

clean: 
	rm Concurrency generalHelpers.o sharedResource.o
