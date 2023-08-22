target:
	gcc -Wall -g -o impl impl.c -lm

clean:
	rm -rf impl
	rm -rf *~
	rm -rf #*
	rm -rf *.bak
