GPP = g++ -O3 -std=c++11

match: main.o graphics.o triangle.o ppm.o
	$(GPP) 

main.o: main.h main.cc
	$(GPP) -c main.cc

