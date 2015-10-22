all: client server
	rm -f *.p
clean: cleans cleanc
	rm -f *o
cleanc:
	rm -f client

cleans:
	rm -f server

client: client.o
	g++ -o client client.o

server: server.o 
	g++ -o server server.o

client.o: client.cpp
	g++ -c client.cpp

server.o: server.cpp
	g++ -c server.cpp
