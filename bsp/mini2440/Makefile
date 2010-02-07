CLEAN_FILES= *.bin *.map *.axf rtconfig.pyc .sconsign.dblite

clean:
	find . \( -name "*.o" -o -name "*.bak" \) -type f -print | xargs rm -f
	rm -fr ./build
	rm -fr $(CLEAN_FILES)
