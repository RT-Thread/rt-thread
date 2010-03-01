#include <rtthread.h>
#include <lwip/netdb.h>
#include <lwip/sockets.h>

static const char send_data[] = "This is TCP Client from RT-Thread.";
void tcpclient(const char* url, int port)
{
	char *recv_data;
	struct hostent *host;
	int sock, bytes_received;
	struct sockaddr_in server_addr;

	host = gethostbyname(url);

    recv_data = rt_malloc(1024);
    if (recv_data == RT_NULL)
    {
        rt_kprintf("No memory\n");
        return;
    }

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		rt_kprintf("Socket error\n");

        /* release recv buffer */
        rt_free(recv_data);
		return;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr = *((struct in_addr *)host->h_addr);
	rt_memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

	if (connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
	{
		rt_kprintf("Connect error\n");

        /* release recv buffer */
        rt_free(recv_data);
		return;
	}

	while(1)
	{
		bytes_received = recv(sock, recv_data, 1024, 0);
		if (bytes_received < 0)
		{
		    lwip_close(sock);

            /* release recv buffer */
            rt_free(recv_data);
			break;
		}

		recv_data[bytes_received] = '\0';

		if (strcmp(recv_data , "q") == 0 || strcmp(recv_data , "Q") == 0)
		{
			lwip_close(sock);

            /* release recv buffer */
            rt_free(recv_data);
			break;
		}
		else
		{
			rt_kprintf("\nRecieved data = %s " , recv_data);
		}

		send(sock,send_data,strlen(send_data), 0);
	}

	return;
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(tcpclient, startup tcp client);
#endif
