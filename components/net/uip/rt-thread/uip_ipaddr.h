
#include "rtdef.h"






/* ethernetif APIs */
#define IP_ADDR_ANY_VALUE 0x00000000UL
#define IP_ADDR_BROADCAST_VALUE 0xffffffffUL

//extern const struct ip_addr ip_addr_any;
//extern const struct ip_addr ip_addr_broadcast;

/** IP_ADDR_ can be used as a fixed IP address
 *  for the wildcard and the broadcast address
 */
#define IP_ADDR_ANY         ((struct ip_addr *)0)
#define IP_ADDR_BROADCAST   ((struct ip_addr *)0)