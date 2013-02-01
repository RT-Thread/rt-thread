
CC = gcc -Wall


lookup: main.o states-code.o
	$(CC) -o $@ $^


main.o: main.c states-code.h states.dat.h
	$(CC) -c $<


states-code.o: states-code.c states-code.h
	$(CC) -c $<


states-code.c: states.dat states-tmpl.c
	../perfect_hash.py -vvvv --splitby '|' --keycol 2 $^


states.dat.h: states.dat
	./mk_header.py >$@


clean:
	rm lookup *.o states.dat.h states-code.c


test:
	./lookup 'NY'
	./lookup 'QW'
