author: Jone.Chen <yuhua8688@tom.com>
License:LGPL
Date:2013-12-26
version:v1.2

apply RT-thread system and lwip
code can be cut
In the current directory, deposit HTTPD core code
Interface directory to store three interface file


the web server support list
--support cgi
--support post
--support auth
--support upload
--support File System




*.cgi file specification

# --Comments, don't deal with
i --include file,will output file content 
c --command process_cgi method processing
t --don't deal with,direct output
. --end of file

*.inc file
by *.cgi include("i *.inc") files, output directly


