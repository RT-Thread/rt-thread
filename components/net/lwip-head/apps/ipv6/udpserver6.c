#include <rtthread.h>
#include <lwip/sockets.h>

#define SERV_PORT 10012
#define BUF_SIZE  1024

static const char send_data[] = "This is UDP Server from RT-Thread.";

void udpserver6(void)
{
	int sockfd;
	struct sockaddr_in6 server_addr6;
	struct sockaddr_in6 client_addr6;
	int bytes_read;
	char *recv_data;
	rt_uint32_t addr_len;

	recv_data = rt_malloc(BUF_SIZE);
	if(recv_data == RT_NULL)
	{
		rt_kprintf("No memory\n");
		return ;
	}

	if((sockfd = socket(AF_INET6, SOCK_DGRAM, 0)) == -1)
	{
		rt_kprintf("Socket error\n");
		rt_free(recv_data);
		return ;
	}
	
	server_addr6.sin6_family = AF_INET6;
	server_addr6.sin6_port = htons(SERV_PORT);
	memcpy(server_addr6.sin6_addr.s6_addr, IP6_ADDR_ANY, 16);
	
	if(bind(sockfd, (struct sockaddr *)&server_addr6, sizeof(struct sockaddr)) == -1)
	{
		rt_kprintf("Bind error\n");
		rt_free(recv_data);
		return ;
	}
	rt_sprintf(recv_data, "%4d", SERV_PORT);
	rt_kprintf("UDPServer Waiting for client on port %s...\n", recv_data);
	
	addr_len = sizeof(struct sockaddr);
	while(1)
	{
		bytes_read = recvfrom(sockfd, recv_data, BUF_SIZE - 1, 0, (struct sockaddr *)&client_addr6, &addr_len);
		recv_data[bytes_read] = '\0';
		rt_kprintf("\n(%s, %d) said:", inet6_ntoa(client_addr6.sin6_addr), ntohs(client_addr6.sin6_port));
		rt_kprintf("%s", recv_data);
		
		if(strcmp(recv_data, "exit") == 0)
		{
			closesocket(sockfd);
			rt_free(recv_data);
			break;
		}
	}
	return ;
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(udpserver6, startup udp server via ipv6);
#endif
