::clean output files
del *.log /s
del *.dblite /s
del project.* /s
del *.scvd /s

rd /s /q .\build
rd /s /q .\settings
rd /s /q .\DebugConfig

::start cmd window and do the command
::start cmd.exe /c "scons --target=mdk5 -s"
start cmd.exe /c "scons --target=iar -s&&scons --target=mdk5 -s"

::start 用来启动一个应用
::cmd /k 表示cmd后面的命令执行完后不关闭窗口。
::如果要在执行完成后关闭窗口可以用/c 。
::详细请使用cmd/?查看

::"命令1&&命令2&&.." 
::将要执行的多条命令使用引号全部包起来，并且在命令间用&&分隔。
::如果只有一条命令则不用引号也可以。

::如：
::@echo off  
::start cmd /k "cd/d E:\&&echo hello&&pause&&ping www.163.com"