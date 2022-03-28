@echo off
set n=%USERNAME%
del *.%n% /s

del *.hex /s
del *.bak /s
del *.ddk /s
del *.edk /s
del *.lst /s
del *.lnp /s
del *.mpf /s
del *.mpj /s
del *.obj /s
del *.omf /s
del *.plg /s
del *.rpt /s
del *.tmp /s
del *.__i /s
del *.crf /s
del *.o /s
del *.d /s
del *.axf /s
del *.tra /s
del *.dep /s           
del JLinkLog.txt /s
del *.iex /s
del *.htm /s
rem del *.sct /s
del *.map /s
del *.ini /s
del *.scvd /s

for /r %%d in (.) do rd /s /q "%%d\Listings" 2>nul
for /r %%d in (.) do rd /s /q "%%d\RTE" 2>nul
for /r %%d in (.) do rd /s /q "%%d\Objects" 2>nul

exit   
