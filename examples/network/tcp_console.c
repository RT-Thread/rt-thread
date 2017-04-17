#include <rtthread.h>
#include <lwip/sockets.h> /* ??BSD socket,????sockets.h??? */
#include <rtdevice.h>
#include <finsh.h>
#include <shell.h>
#define TCP_BUFSZ				       1256
#define TCP_CONSOLE_PORT 	     23

#define DEV_BUFSZ	             1256

struct rt_tcp_console
{
	struct rt_device parent;
	rt_sem_t 	lock;
	struct rt_ringbuffer rb;
	rt_uint16_t port;
	rt_int32_t  connect;
	rt_uint8_t rx_bp[DEV_BUFSZ];	   //device buff  for reciever		
};
struct rt_tcp_console tcp_console;

static 	rt_uint8_t tcp_tx_buf[TCP_BUFSZ];

static rt_err_t rt_tconsole_init (rt_device_t dev)
{
	
	return RT_EOK;
}

static rt_err_t rt_tconsole_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t rt_tconsole_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_size_t rt_tconsole_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	int cnt = 0;
	struct rt_tcp_console *tp = (struct rt_tcp_console*)dev;


	if(tp == RT_NULL) return 0;
	if(buffer == RT_NULL) return 0;
	if(tp->lock != RT_NULL) rt_sem_take(tp->lock, RT_WAITING_FOREVER);
	
	cnt =  rt_ringbuffer_get(&tp->rb,buffer,size);
	
	if(tp->lock != RT_NULL) rt_sem_release(tp->lock);
	return cnt;
}

static rt_size_t rt_tconsole_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	rt_uint8_t tmp;
	rt_uint8_t *dp;
	int cnt,i;
	int scnt = 0;
	struct rt_tcp_console *tp = (struct rt_tcp_console*)dev;
	
	if(tp == RT_NULL) return 0;
	if(buffer == RT_NULL) return 0;
	if(tp->lock != RT_NULL) rt_sem_take(tp->lock, RT_WAITING_FOREVER);

	if(tp->connect){
		if (dev->flag & RT_DEVICE_FLAG_STREAM)
		{
			dp = (rt_uint8_t*)buffer;
			cnt = 0;
			for(i = 0; i< size; i++)
			{
				tmp = *dp++;
				if(tmp == '\n')
				{
					tcp_tx_buf[cnt++] = '\r';
				}
				tcp_tx_buf[cnt++] = tmp;
				if(cnt >= TCP_BUFSZ-2)
				{
					scnt += send(tp->connect,tcp_tx_buf,cnt,0);
					cnt = 0;
				}
				
			}
			scnt += send(tp->connect,tcp_tx_buf,cnt,0);	
		}
		else{
			scnt = send(tp->connect,buffer,size,0);
		}
	}
	if(tp->lock != RT_NULL) rt_sem_release(tp->lock);	
	return scnt;
}

static rt_err_t rt_tconsole_control(rt_device_t dev, rt_uint8_t cmd, void* arg)
{	

	return RT_EOK;
}


void tcp_console_service(void* parameter)
{
   char *recv_data;  //dat from tcp
   rt_uint32_t sin_size;
   int sock, bytes_received;
   struct sockaddr_in server_addr, client_addr;
   
   recv_data = rt_malloc(TCP_BUFSZ); /* get tcp data buffer */
   if (recv_data == RT_NULL)
   {
       rt_kprintf("No memory\n");
       return;
   }
   //socket
   if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
   {
       rt_kprintf("Socket error\n");
       rt_free(recv_data);
       return;
   }

   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(tcp_console.port);
   server_addr.sin_addr.s_addr = INADDR_ANY;
   rt_memset(&(server_addr.sin_zero),8, sizeof(server_addr.sin_zero));
   //bind
   if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
   {
       rt_kprintf("Unable to bind\n");
       rt_free(recv_data);
       return;
   }
	// listen
   if (listen(sock, 5) == -1)
   {
       rt_kprintf("Listen error\n");

       /* release recv buffer */
       rt_free(recv_data);
       return;
   }

   rt_kprintf("\nTCP Console Server Waiting for client on port %d...\n",tcp_console.port);
   
   while(RT_TRUE)
   {
       sin_size = sizeof(struct sockaddr_in);
       tcp_console.connect = accept(sock, (struct sockaddr *)&client_addr, &sin_size);
   
	   /* send finsh prompt */
		send(tcp_console.connect, FINSH_PROMPT, strlen(FINSH_PROMPT), 0);
       /*wait data*/
       while (1)
       {
           
           bytes_received = recv(tcp_console.connect,recv_data, TCP_BUFSZ, 0);
           if (bytes_received <= 0) 
           {
			   lwip_close(tcp_console.connect);
			   tcp_console.connect = -1;
               break;
           }
		   rt_ringbuffer_put(&tcp_console.rb,(const unsigned char*)recv_data,bytes_received);
		   if (tcp_console.parent.rx_indicate != RT_NULL) //tcp  invoke callback
           {
                tcp_console.parent.rx_indicate(&tcp_console.parent, bytes_received);
		   }
       }
   }
}

void tcp_console_ervice_start(void)
{
	
	rt_thread_t tid;
	struct rt_tcp_console* tp;

	/* get uart device */
	tp = &tcp_console;	
	/* device initialization */
	tp->parent.type = RT_Device_Class_Char;
	tp->port = TCP_CONSOLE_PORT;
	tp->lock = rt_sem_create("tc_send",1,RT_IPC_FLAG_FIFO);
	rt_ringbuffer_init(&tp->rb,tp->rx_bp,DEV_BUFSZ);
	
	 
	/* device interface */
	tp->parent.init 	    = rt_tconsole_init;
	tp->parent.open 	    = rt_tconsole_open;
	tp->parent.close      = rt_tconsole_close;
	tp->parent.read 	    = rt_tconsole_read;
	tp->parent.write      = rt_tconsole_write;
	tp->parent.control    = rt_tconsole_control;
	tp->parent.user_data    = RT_NULL;

	rt_device_register(&tp->parent,
		"tcp_c", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STREAM);
		
	
	
    tid = rt_thread_create("tcp_c",
        tcp_console_service, RT_NULL,
        1024, 19, 20);

    if (tid != RT_NULL)
        rt_thread_startup(tid);
	
	
}


