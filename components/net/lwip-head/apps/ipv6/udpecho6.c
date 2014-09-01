#include <rtthread.h>
#include <finsh.h>
#include <lwip/api.h>

#define UDP_ECHO_PORT 10002

void udpecho6(void)
{
	struct netconn *conn, *newconn;
	struct netbuf *buf;
	struct ip6_addr *addr6;
	unsigned short port;
	err_t err;
	
	
	conn = netconn_new(NETCONN_UDP_IPV6);
	netconn_bind_ip6(conn, IP6_ADDR_ANY, UDP_ECHO_PORT);
	
	while(1)
	{
		netconn_recv(conn, &buf);
		addr6 = netbuf_fromaddr_ip6(buf);
		port = netbuf_fromport(buf);
		netconn_connect_ip6(conn, addr6, port);
		netconn_sendto_ip6(conn, buf, addr6, port);
		netbuf_delete(buf);
	}
}
#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(udpecho6, startup udpecho via ipv6);
#endif
