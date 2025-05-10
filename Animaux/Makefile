all: exec

main.o: main.c fonction.h espece.h
	gcc -c main.c -o main.o

menu.o: menu.c fonction.h espece.h
	gcc -c menu.c -o menu.o

espece.o: espece.c espece.h
	gcc -c espece.c -o espece.o

exec: main.o menu.o espece.o
	gcc main.o menu.o espece.o -o exec