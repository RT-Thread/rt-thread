
CC = gcc -Wall

a.out: main.c keys.code.h
	$(CC) $<


keys.code.h: keys.dat keys.tmpl.h
	../perfect_hash.py $^


keys.dat:
	./mk_rnd_keys.py 100 >keys.dat


clean:
	rm keys.dat keys.code.h a.out


test:
	./a.out

