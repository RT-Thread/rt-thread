Porting network interface device for RT-Thread in lwIP.

The major jobs following RT-Thread Team. Only update the origin code of lwip 2.0.2 to lwip 2.0.3.
And keep the difference between on the change of RT-Thread Team.

by xiangxistu 2021/06/21 17:00 PM
liuxianliang@rt-thread.com

The major jobs following RT-Thread Team. The RT-Thread network interface device need to synchronize some network status and address information in lwIP, so it need to make some changes in the lwIP netwrok status and address operations function.
The specific changes are as follows:

 - netif.c: add RT-Thread netdev header file , status synchronize(UP, LINK_UP), address synchronize(IP, netmask, gateway);
 
 - dns.c: add RT-Thread header file, dns servers synchronize;
 
 - sockets.c: custom 'select' function implementation in RT-Thread by the wait queue mode.
 
by ChenYong 2019/3/26 10:00 AM
chenyong@rt-thread.com


Porting lwip 2.0.2 running on RT-Thread.
The major jobs following RT-Thread Team. The RT-Thread team already port the lwip 2.0.0, so I only do some move code and test jobs.
I use the memory pools to test lwip 2.0.2, I use the iperf tool to test it about more than 20 hours, It is running normal.
I don't test it working on memory heap.
...
Good Luck.
by Hans.Huang 2017/3/27 10:52 AM
huangxi_hans@163.com
