all: supermarket firefighter client manager semaphores
supermarket: supermarket.o semaphores.o
	gcc -o mainprog mainprog.o semaphores.o
supermarket.o: supermarket.c semaphores.h 
	gcc -c mainprog.c
semaphores.o: semaphores.c
	gcc -c semaphores.c
firefighter: firefighter.o semaphores.o
	gcc -o firefighter firefighter.o semaphores.o
firefighter.o: firefighter.c
	gcc -c firefighter.c 
client: client.o semaphores.o
	gcc -o client client.o semaphores.o
client.o:	client.c
	gcc -c client.c
manager: manager.o semaphores.o
	gcc -o manager manager.o semaphores.o
manager.o: manager.c
	gcc -c manager.c
