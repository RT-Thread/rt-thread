lwIP NAT componenent

If you want to use lwIP NAT componenent, please define LWIP_USING_NAT in rtconfig.h. 

In this case the network 213.129.231.168/29 is nat'ed when packets are sent to the 
destination network 10.0.0.0/24 (untypical example - most users will have the other 
way around).

Use following code to add a NAT entry: 

  ip_nat_entry_t nat_entry;
 
  nat_entry.out_if = (struct netif *)&emac_if1;
  nat_entry.in_if = (struct netif *)&emac_if2;
  IP4_ADDR(&nat_entry.source_net, 213, 129, 231, 168);
  IP4_ADDR(&nat_entry.source_netmask, 255, 255, 255, 248);
  IP4_ADDR(&nat_entry.dest_net, 10, 0, 0, 0);
  IP4_ADDR(&nat_entry.source_netmask, 255, 0, 0, 0);
  ip_nat_add(&_nat_entry);
