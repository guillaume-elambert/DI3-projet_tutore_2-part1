build:
	gcc -Wall -o main main.c paramcmd1.c paramcmd1.h;

run: build
	./main -a zutyr -t 788 -s 127.0.0.1:9000
