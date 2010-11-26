#include "uip_pbuf.h"
#include "uip-conf.h"
#include "rtdef.h"


struct eth_hdr {
  u8_t ip_addrdest[6];
  u8_t ip_addrsrc[6];
  u16_t type;
} ;
#define ETHTYPE_ARP       UIP_ETHTYPE_ARP
#define ETHTYPE_IP        UIP_ETHTYPE_IP
#define ETHTYPE_VLAN      0x8100
#define ETHTYPE_PPPOEDISC 0x8863  /* PPP Over Ethernet Discovery Stage */
#define ETHTYPE_PPPOE     0x8864  /* PPP Over Ethernet Session Stage */
