CXX:=clang++
CXXFLAGS:=-std=c++11
Concurrency: concurrency3.cpp sharedResource.o generalHelpers.o listHandler.o
	$(CXX) $(CXXFLAGS) -lpthread -o Concurrency concurrency3.cpp sharedResource.o generalHelpers.o listHandler.o

sharedResource: sharedResource.cpp sharedResource.
	$(CXX) $(CXXFLAGS) -c sharedResource.cpp

generalHelpers: generalHelpers.cpp generalHelpers.h
	$(CXX) $(CXXFLAGS) -c generalHelpers.cpp -std=c++11

listHandler: listHandler.cpp listHandler.h
	$(CXX) $(CXXFLAGS) -c -stdlib=libc++ listHandler.cpp -std=c++11

clean: 
	rm Concurrency generalHelpers.o sharedResource.o listHandler.o


