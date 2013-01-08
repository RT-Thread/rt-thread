#include <rtthread.h>
#include <lwip/sockets.h> /* 使用BSD socket，需要包含sockets.h头文件 */

#define BUFSZ	1024

void udpserv(void* paramemter)
{
   int sock;
   int bytes_read;
   char *recv_data;
   rt_uint32_t addr_len;
   struct sockaddr_in server_addr, client_addr;

   /* 分配接收用的数据缓冲 */
   recv_data = rt_malloc(BUFSZ);
   if (recv_data == RT_NULL)
   {
       /* 分配内存失败，返回 */
       rt_kprintf("No memory\n");
       return;
   }

   /* 创建一个socket，类型是SOCK_DGRAM，UDP类型 */
   if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
   {
       rt_kprintf("Socket error\n");

       /* 释放接收用的数据缓冲 */
       rt_free(recv_data);
       return;
   }

   /* 初始化服务端地址 */
   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(5000);
   server_addr.sin_addr.s_addr = INADDR_ANY;
   rt_memset(&(server_addr.sin_zero),0, sizeof(server_addr.sin_zero));

   /* 绑定socket到服务端地址 */
   if (bind(sock,(struct sockaddr *)&server_addr,
            sizeof(struct sockaddr)) == -1)
   {
       /* 绑定地址失败 */
       rt_kprintf("Bind error\n");

       /* 释放接收用的数据缓冲 */
       rt_free(recv_data);
       return;
   }

   addr_len = sizeof(struct sockaddr);
   rt_kprintf("UDPServer Waiting for client on port 5000...\n");

   while (1)
   {
       /* 从sock中收取最大BUFSZ - 1字节数据 */
       bytes_read = recvfrom(sock, recv_data, BUFSZ - 1, 0,
                             (struct sockaddr *)&client_addr, &addr_len);
       /* UDP不同于TCP，它基本不会出现收取的数据失败的情况，除非设置了超时等待 */

       recv_data[bytes_read] = '\0'; /* 把末端清零 */

       /* 输出接收的数据 */
       rt_kprintf("\n(%s , %d) said : ",inet_ntoa(client_addr.sin_addr),
                  ntohs(client_addr.sin_port));
       rt_kprintf("%s", recv_data);

       /* 如果接收数据是exit，退出 */
       if (strcmp(recv_data, "exit") == 0)
       {
           lwip_close(sock);

           /* 释放接收用的数据缓冲 */
           rt_free(recv_data);
           break;
       }
   }

   return;
}

#ifdef RT_USING_FINSH
#include <finsh.h>
/* 输出udpserv函数到finsh shell中 */
FINSH_FUNCTION_EXPORT(udpserv, startup udp server);
#endif
