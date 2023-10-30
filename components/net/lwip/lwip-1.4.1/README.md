Porting network interface device for RT-Thread in lwIP.

Fix a bug in src/core/netif.c. The netif->name variable is a 2-byte char array, which may not end with '\0' and may cause a bug when it's directly passed to the function `netdev_get_by_name`. Use the newly added function `netif_get_netdev` to get a netdev object by netif's name.

by windsgo 2023/10/30 11:03 AM
18221102427@163.com

The major jobs following RT-Thread Team. The RT-Thread network interface device need to synchronize some network status and address information in lwIP, so it need to make some changes in the lwIP netwrok status and address operations function.
The specific changes are as follows:

 - netif.c: add RT-Thread netdev header file , status synchronize(UP, LINK_UP), address synchronize(IP, netmask, gateway);

 - dns.c: add RT-Thread header file, dns servers synchronize;

 - sockets.c: custom 'select' function implementation in RT-Thread by the wait queue mode.

by ChenYong 2019/3/26 10:00 AM
chenyong@rt-thread.com

