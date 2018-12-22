# -*- coding: utf-8 -*-
#引入模块
import socket
import threading
import time
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 监听端口:
s.bind(('192.168.10.110', 6001))
 
s.listen(5)
print 'Waiting for connection...'

def tcp_link(sock,addr):
    print 'Accept new connection from %s:%s...' % addr
    sock.send('Welcome to RT-Thread!')
    while True:
        data=sock.recv(1024)
        time.sleep(1)
        if data=='exit' or not data:
            break
        print data
        sock.send('Hello,%s!'%data)
    sock.close()
    print 'Connection from %s:%s closed.'%addr

while True:
    
    #接受一个新连接
    sock,addr=s.accept()
    
    #创建新线程来处理TCP连接
    t=threading.Thread(target=tcp_link(sock,addr))

