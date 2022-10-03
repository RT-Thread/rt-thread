:forever_develop
py -3 nuwriter.py -a ddrimg\enc_ddr3_winbond_256mb.bin
IF %ERRORLEVEL% EQU 0 (
   py -3 nuwriter.py -o execute -w ddr 0x28000000 ..\preload\leave_ibr.bin
)
pause

goto :forever_develop