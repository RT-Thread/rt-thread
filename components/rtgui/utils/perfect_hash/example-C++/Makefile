
CXX = g++ -Wall


lookup: main.o states-code.o
	$(CXX) -o $@ $^


main.o: main.cc states-code.hh
	$(CXX) -c $<


states-code.o: states-code.cc states-code.hh states.dat.h
	$(CXX) -c $<


states-code.cc: states.dat states-tmpl.cc states-code.hh
	../perfect_hash.py --splitby '|' --keycol 2 states.dat states-tmpl.cc


states.dat.h: states.dat
	./mk_header.py >$@


clean:
	rm lookup *.o states.dat.h states-code.cc


test:
	./lookup 'NY'
	./lookup 'QW'
