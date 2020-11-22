all: server client1 client2

server: server.o
	g++ server.o -o server

client1: client1.o
	g++ client1.o -o client1

client2: client2.o
	g++ client2.o -o client2
clean:
	rm -rf *.o client1 client2 server client1.cpp~ client2.cpp~ server.cpp~ Makefile~


