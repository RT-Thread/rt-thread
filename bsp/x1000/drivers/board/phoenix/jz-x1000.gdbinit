#connect to the JDI gdb server
target remote 169.28.23.51:2823

#set remote write size
set remotewritesize fixed
set remotewritesize 8192

#load the debug image
load

#debug begin
