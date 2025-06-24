CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2

all: porsoc.e por.e por2.e

porsoc.e: porsoc.cpp
	$(CXX) $(CXXFLAGS) -o porsoc.e porsoc.cpp

por.e: por.cpp
	$(CXX) $(CXXFLAGS) -o por.e por.cpp

por2.e: por2.cpp
	$(CXX) $(CXXFLAGS) -o por2.e por2.cpp

clean:
	rm -f porsoc.e por.e por2.e

