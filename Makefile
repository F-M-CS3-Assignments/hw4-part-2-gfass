all: bdc

bdc: biggest-divisible-conglomerate.cpp main.cpp
	g++ -std=c++11 -Wall biggest-divisible-conglomerate.cpp main.cpp -o bdc
run: all
	./bdc