export RTT_EXEC_PATH=G:\emStudio\tools\arm-2014.05\bin
#export RTT_EXEC_PATH=E:\embTools\arm-2015.q3\bin
#export RTT_EXEC_PATH=E:\embTools\arm-2016.q3\bin
#export RTT_EXEC_PATH=E:\embTools\arm-2017.q2\bin
#export RTT_ROOT=E:\rt-thread-env\workspace\rt-thread_fork

scons:=python ${SCONS}\scons.py

all:
	@$(scons) -j4
	
keil:	
	@$(scons) --target=mdk4 -s
	
copy:	
	@$(scons) --copy
	
clean:
	@$(scons) -j4 -c
	
buildlib:
	@$(scons) --buildlib=littlefs
cleanlib:
	@$(scons) --cleanlib
	