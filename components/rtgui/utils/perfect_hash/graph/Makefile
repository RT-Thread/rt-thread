


animals.ps: animals.dot
	neato -Tps $< -Gstart=100 -o $@


animals.dot: animals.py
	./py2dot -l $< -o $@


animals.py: ../animals.txt
	../perfect_hash.py $< >$@


clean:
	rm animals.py animals.dot animals.ps


test:
	true


