# -*- coding: utf-8 -*-

import socket

s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)

s.connect(('192.168.10.110',6001))

print s.recv(1024)

for data in ['rtt_nano','rtt_thread','rtt_bsp']:
    s.send(data)
    print s.recv(1024)

s.send('exit')
s.close()