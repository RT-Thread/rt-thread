Porting network interface device for RT-Thread in lwIP.
The major jobs following RT-Thread Team. The RT-Thread network interface device need to synchronize some network status and address information in lwIP, so it need to make some changes in the lwIP netwrok status and address operations function.
The specific changes are as follows:

 - netif.c: add RT-Thread netdev header file , status synchronize(UP, LINK_UP), address synchronize(IP, netmask, gateway);
 
 - dns.c: add RT-Thread header file, dns servers synchronize;
 
 - sockets.c: custom 'select' function implementation in RT-Thread by the wait queue mode.
 
by ChenYong 2019/3/26 10:00 AM
chenyong@rt-thread.com
