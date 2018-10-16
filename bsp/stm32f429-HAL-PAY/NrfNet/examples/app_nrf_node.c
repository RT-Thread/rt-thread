#include <rtthread.h>
#include <nrf_node.h>
#include <stdlib.h>
#include <rtdevice.h> 

#define USING_LOG
#ifdef USING_LOG
	#define LOG		rt_kprintf("[NRF_APP]:");rt_kprintf
	#define LOGS	rt_kprintf
#else
	#define LOG(...)
	#define LOGS(...)
#endif

#define LED_0_PIN		(57)
#define LED_1_PIN		(56)

static rt_uint8_t IsLink = 0;

static void on_conn_cb(void* args)
{
	u8 data[2];
	IsLink = 1;
	LOG("NRF Connected!\r\n");
	data[0] = rt_pin_read(LED_0_PIN);data[1] = rt_pin_read(LED_1_PIN);
	nrf_send_data(GATEWAY_ADDR,data);
}
static void on_disconn_cb(void* args)
{
	//NODESTATUS *nodestatus = args;
	IsLink = 0;
	LOG("NRF DisConnected!\r\n");
}
static void on_send_cb(u8 src_addr,u8 dst_addr,u8 pack_type,u16 ID,u8 *buf,u8 status)
{
	LOG("on_send_cb:id=%d src=%d dst=%d type=%d data[0]=%d data[1]=%d ",ID,src_addr,dst_addr,pack_type,buf[0],buf[1]);
	if(status==PACKAGE_BROADCAST)
	{
		LOGS("broadcast!\r\n");
	}
	else if(status==PACKAGE_SUCCESS)
	{
		LOGS("ok!\r\n");
	}
	else
	{
		LOGS("fail!\r\n");
	}	
}
static void on_recv_cb(u8 src_addr,u8 dst_addr,u8 pack_type,u8 *buf)
{
	LOG("on_recv_cb:src=%d,dst=%d,type=%d,data[0]=%d,data[1]=%d\r\n",src_addr,dst_addr,pack_type,buf[0],buf[1]);
	rt_pin_write(LED_0_PIN,buf[0]);
	rt_pin_write(LED_1_PIN,buf[1]);
}
static void nrfstatus(void)
{
	int i;
	NODESTATUS node;
	nrf_get_nodestatus(&node);
	LOGS("======NodeStatus======\r\n");
	switch(node.link_status)
	{
		case DISCONNECT:
			LOGS("link_status=DISCONNECT\r\n");
			break;
		case WAIT_CONNECT:
			LOGS("link_status=WAIT_CONNECT\r\n");
			break;
		case CONNECTED:
			LOGS("link_status=CONNECTED\r\n");
			break;
		case WAIT_CHANGE:
			LOGS("link_status=WAIT_CHANGE\r\n");
			break;
	}
	LOGS("channel=%d\r\n",node.channel);
	LOGS("addr=%d\r\n",node.addr);
	LOGS("mac:");
	for(i=0;i<MAC_LEN;i++)
	{
		LOGS("%02x",node.node_mac[i]);
	}
	LOGS("\r\n");	
	LOGS("sys_pwd=%08X\r\n",node.pwd);
	LOGS("shift_failed_count=%d\r\n",node.shift_failed_count);
	LOGS("shift_count=%d\r\n",node.shift_count);
	LOGS("recv_count=%d\r\n",node.recv_count);
	LOGS("======================\r\n");
}
MSH_CMD_EXPORT(nrfstatus, show nrf status);

static void nrfreset(void)
{
	nrf_reset();
}
MSH_CMD_EXPORT(nrfreset, nrf wait connect);

static void nrfsend(int argc, char** argv)
{
	if(IsLink && argc==3)
	{
		rt_uint8_t addr = atol(argv[1]);
		char* data = argv[2];
		data[PAYLOAD_DATA_LEN-1] = '\0';
		nrf_send_data(addr, data);
	}
	else
	{
		LOG("Wait Connect...\r\n");
	}
}
MSH_CMD_EXPORT(nrfsend, nrf send data);

static int nrf_node_startup(void)
{
	nrf_reg_callback(on_conn_cb, on_disconn_cb,
					on_send_cb, on_recv_cb);
	return RT_EOK;
}
INIT_APP_EXPORT(nrf_node_startup);
