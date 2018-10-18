#include <rtthread.h>
#ifndef __NRF_DATA_H__

typedef char    BYTE;
typedef uint8_t BOOL;  

#define u8	uint8_t
#define u16 uint16_t
#define u32 uint32_t

#define TRUE	1
#define FALSE	0
#define NULL	0

#define ACK				1
#define NO_ACK			0

#define MAC_LEN				(5)
#define PAYLOAD_LEN			(32)
#define PALYOAD_HEADER_LEN	(sizeof(PayloadHeader))
#define PAYLOAD_DATA_LEN	(PAYLOAD_LEN-PALYOAD_HEADER_LEN)

#define DATA_BUF_COUNT		(50)
#define MAX_NODE_NUM		(32) 	//节点数
#define MAX_HOP_NUM			(MAX_NODE_NUM)

#define DEFAULT_CHANNEL		(124)
#define GATEWAY_ADDR		(1)
#define ASSIGN_ADDR_START	(31)
#define ASSIGN_ADDR_END		(ASSIGN_ADDR_START+MAX_NODE_NUM)

#define MAX_FAILED_COUNT	(3)		//发送失败次数
#define MAX_RETRY_COUNT		(5)
#define MAX_ACK_TIME		(100)
#define HEART_PACK_TIME 	(100)	//心跳包扫描间隔(10ms*100)

#define MULTI_PACK_INTERVAL	(10000)	//处理重复包间隔,单位(10秒)
#ifdef USING_NRF24L01_GATEWAY
	#define HEART_LINK_INTERVAL (20000)	//发送心跳包间隔,单位(20秒)
#else
	#define HEART_LINK_INTERVAL (25000)	//心跳包接收超时时间,单位(25秒)
#endif
#define WAIT_CONNECT_INTERVAL (20000)  //等待连接间隔,单位(20秒)

enum LINKSTATUS{DISCONNECT,WAIT_CONNECT,CONNECTED,WAIT_CHANGE};
enum PAYLOADSTATUS
{
IDLE,
WAIT_USE,
WAIT_SEND,
WAIT_RETRY,
WAIT_SEND_RETRY,
SEND_FAILED,
SEND_SUCCESS,
SEND_BROADCAST,
WAIT_ACK,
WAIT_RECV,
RECV_FAILED,
WAIT_HANDLER
};
enum PACKAGETYPE
{
DEL_NODE,		//0
ASSIGN_ADDR,	//1
START_LINK,		//2
BUILD_LINK,		//3
BUILD_LINK_ACK,	//4
CHECK_LINK,		//5
CHECK_LINK_ACK,	//6
APP_DATA,		//7
APP_DATA_ACK	//8
};

#define PACKAGE_BROADCAST	0x02
#define PACKAGE_SUCCESS   	0x01
#define PACKAGE_FAILED    	0x00

typedef void (*send_callback_t)(u8 src_addr,u8 dst_addr,u8 pack_type,u16 num,u8 *buf,u8 status);
typedef void (*recv_callback_t)(u8 src_addr,u8 dst_addr,u8 pack_type,u8 *buf);

#pragma pack(1)
typedef struct 
{
	u32 PID;     //网络ID
	u32 SID;     //发送payload ID
	u8 the_addr; //本次发送地址
	u8 src_addr; //源发送地址
	u8 dst_addr; //目的地址
	u8 ass_addr; //待分配地址
	u8 hop_addr; //上一跳地址
	u8 hop_count;//跳跃次数
	u8 pack_type;//数据包类型
}PayloadHeader,*LPayloadHeader;//payload头结构,长度为15

typedef struct
{
	PayloadHeader header;    //payload头
	u8 buf[PAYLOAD_DATA_LEN];//数据缓冲区
}Payload,*LPayload;//payload结构 

typedef struct
{
	u16 time_count;		 //超时计数
	u8 status;         	 //数据包发送状态
	u8 isBroadcast;		 //是否广播
	u8 send_failed_count;//发送失败次数
	u8 retry_count;		 //当前数据包重发数
	u8 pipe_num;
	send_callback_t SendCallBack;//回调
	Payload payload;     //数据包
}DATA_BUF,*LPDATA_BUF;//同步数据包

typedef struct 
{
	u8 addr;	//节点地址
	u8 path[MAX_HOP_NUM];//路径表
}RoutrTable,*LRoutrTable;//路由表

typedef struct
{
	u8 set_tag;
	u32 time;  
	u16 RID;
	u8 the_addr;
	u8 src_addr;
	u8 dst_addr;
	u8 pack_type;
}HANDLEMULTIPACK;//处理重复的包

typedef struct 
{
	u8 idx;
	u8 addr;
}PathTable;//查找节点最短路径

#ifdef USING_NRF24L01_GATEWAY
typedef struct
{
	u32 shift_failed_count; //切换失败计数
	u32 shift_count;        //切换成功计数器
	u32 recv_count;         //接收数据包数
	u32 pwd;
	u8 addr;           		//当前地址
	u8 assign_addr;			//分配地址
	u8 channel;             //当前信道
	u8 heart_status;  		//心跳包状态
	u8 node_mac[MAC_LEN];
}NODESTATUS;//节点状态结构

typedef struct
{
	u8 addr;
	u8 count;	//计数器
}LOST_CONNECTION;//统计掉线次数

typedef struct 
{
	u32 link_time;
	u8 addr;	//节点地址
}HeartTable;//心跳表

typedef struct
{
	u32 tag;
	u8 assign_addr;		   		//分配地址
}NRFSTOREDATA,*LPNRFSTOREDATA;
#endif

#ifdef USING_NRF24L01_NODE
typedef struct
{
	u32 shift_failed_count; //切换失败计数
	u32 shift_count;        //切换成功计数器
	u32 recv_count;         //接收数据包数
	u32 pwd;
	u8 addr;           		//当前地址
	u8 route_addr;
	u8 channel;             //当前信道
	u8 link_status;  		//心跳包状态
	u8 send_failed_count;
	u8 node_mac[MAC_LEN];
}NODESTATUS;//节点状态结构

typedef struct
{
	u32 tag;
	u32 pwd;
	u8 addr;		   		//节点地址
}NRFSTOREDATA,*LPNRFSTOREDATA;

#endif

#pragma pack()

typedef void (*on_connect_callback_t)(void* args);
typedef void (*on_disconnect_callback_t)(void* args);

#endif
