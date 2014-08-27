#include <rtthread.h>
#include <finsh.h>
#include <lwip/api.h>

#define TCP_ECHO_PORT 10001
void tcpecho6(void)
{
	struct netconn *conn, *newconn;
	err_t err;
	
	conn = netconn_new(NETCONN_TCP_IPV6);
	netconn_bind_ip6(conn, IP6_ADDR_ANY, TCP_ECHO_PORT);
	netconn_listen(conn);
	
	while(1)
	{
		err = netconn_accept(conn, &newconn);
		if(err == ERR_OK)
		{
			struct netbuf *buf;
			void *data;
			u16_t len;
			
			while(netconn_recv(newconn, &buf) == ERR_OK)
			{
				do
				{
					netbuf_data(buf, &data, &len);
					err = netconn_write(newconn, data, len, NETCONN_COPY);
					if(err != ERR_OK)
						rt_kprintf("netconn_write() error\n");
				}while(netbuf_next(buf) >= 0);
				netbuf_delete(buf);
			}
			netconn_delete(newconn);
		}
	}
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(tcpecho6, startup tcp echo server via ipv6);
#endif
