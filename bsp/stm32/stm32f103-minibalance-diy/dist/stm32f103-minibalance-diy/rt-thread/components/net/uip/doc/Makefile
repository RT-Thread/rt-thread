all: htmldoc pdfdoc

htmldoc:
	doxygen Doxyfile

pdfdoc: htmldoc
	cd latex; make refman.pdf && mv refman.pdf ../uip-refman.pdf
