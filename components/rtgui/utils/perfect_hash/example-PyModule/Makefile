

CC = gcc -Wall


stations.so: stationsmodule.c stations.dat.h stations-code.h
	$(CC) -shared -fPIC -I/usr/local/include/python2.5 \
            -o stations.so stationsmodule.c


stations.dat.h: stations.dat
	sed <$< >$@ -e 's:\([^,]*\),\([^,]*\):  { "\1", "\2" },:'


stations-code.h: stations.dat stations-tmpl.h
	../perfect_hash.py --trails 2 $^


clean:
	rm stations-code.h stations.dat.h stations.so


test:
	python -c "import stations; print stations.locator('DL5BAC')"


