:forever_develop
py -3 nuwriter.py -a ddrimg\enc_ddr2_winbond_128mb.bin
IF %ERRORLEVEL% EQU 0 (
   py -3 nuwriter.py -o execute -w ddr 0x80400000 ..\rtthread.bin
)
pause

goto :forever_develop