all: out

out: main.o minishell.o
	gcc minishell.c main.c -o out
	
main.o: main.c
	gcc -c main.c

minishell.o: minishell.c
	gcc -c minishell.c

compile:
	./out

clean:
	rm -rf *o out