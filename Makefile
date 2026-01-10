all: banco

banco: banco.o escalonador.o fila.o logtree.o
	gcc banco.o escalonador.o fila.o logtree.o -o banco

banco.o: banco.c escalonador.h
	gcc -c banco.c

escalonador.o: escalonador.c escalonador.h fila.h logtree.h
	gcc -c escalonador.c

fila.o: fila.c fila.h
	gcc -c fila.c

logtree.o: logtree.c logtree.h
	gcc -c logtree.c

clean:
	rm -f *.o banco
