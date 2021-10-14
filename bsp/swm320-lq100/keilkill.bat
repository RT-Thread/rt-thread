del *.bak /s
del *.ddk /s
del *.edk /s
del *.lst /s
::del *.lnp /s
del *.mpf /s
del *.mpj /s
del *.obj /s
del *.omf /s
::del *.opt /s  ::不允许删除JLINK的设置
del *.plg /s
del *.rpt /s
del *.tmp /s
::del *.__i /s
::del *._ia /s
del *.crf /s
del *.o /s
del *.d /s
del *.axf /s
del *.tra /s
del *.dep /s           
::del JLinkLog.txt /s

del *.iex /s
del *.htm /s
::del *.sct /s
del *.map /s

del *.whsj2 /s
del *.SYNWIT_Lik /s
del *.whsj2 /s
del *.scvd /s

rmdir /s/q .git
rmdir /s/q .vscode

exit
