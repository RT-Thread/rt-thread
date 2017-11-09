export RTT_EXEC_PATH=E:\embTools\arm-2014.05\bin
#export RTT_ROOT=E:\embTools\rt-thread-v2.1.x
#export RTT_ROOT=E:\embTools\rt-thread-fork

scons:=python ${SCONS}\scons.py

all:
	@$(scons) -j4
	
copy:	
	@$(scons) --copy -s
	
clean:
	@$(scons) -j4 -c
	
buildlib:
	@$(scons) --buildlib=SPIFFS
cleanlib:
	@$(scons) --cleanlib
	