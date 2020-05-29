generator:
	gcc -Wall -g -o dag_generator dag_generator.c -lm

clean:
	rm -rf dag_gen_stq
	rm -rf *~
	rm -rf *.gra
	rm -rf *.stat
