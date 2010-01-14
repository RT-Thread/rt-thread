CLEAN_FILES:= *.axf rtconfig.pyc rtthread.bin *.map .sconsign.dblite

clean:
	find . \( -name '*.o' \) -type f -print | xargs rm -f
	rm -fr ./build
	rm -f $(CLEAN_FILES)
