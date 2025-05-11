all: exec

main.o: main.c espece.h affichage.h gestions.h utilitaires.h
	gcc -c main.c -o main.o

gestions.o: gestions.c gestions.h espece.h affichage.h utilitaires.h
	gcc -c gestions.c -o gestions.o

espece.o: espece.c espece.h
	gcc -c espece.c -o espece.o

affichage.o: affichage.c affichage.h espece.h gestions.h utilitaires.h
	gcc -c affichage.c -o affichage.o

utilitaires.o: utilitaires.c utilitaires.h affichage.h espece.h gestions.h
	gcc -c utilitaires.c -o utilitaires.o

exec: main.o gestions.o espece.o affichage.o utilitaires.o
	gcc main.o gestions.o espece.o affichage.o utilitaires.o -o exec

clean:
	rm -f *.o exec