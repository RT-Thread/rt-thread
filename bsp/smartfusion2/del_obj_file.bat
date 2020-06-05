%删除obj目录下的多余文件%
del *.lnp /s
::del *.opt /s  ::不允许删除JLINK的设置
del *.__i /s
del *.crf /s
del *.o /s
del *.d /s
del *.htm /s

%删除USER目录下的多余文件%
del *.map /s
del *.lst /s
del *.dep /s
del *.build_log.htm /s
del *.bak

echo 编译产生的其他文件已经删除
