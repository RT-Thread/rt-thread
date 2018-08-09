dox:
	doxygen Doxyfile


pdf:	dox
	(cd latex; $(MAKE) refman.pdf)
	mv latex/refman.pdf pt-refman.pdf