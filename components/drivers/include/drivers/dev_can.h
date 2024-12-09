/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2015-05-14     aubrcool@qq.com   first version
 * 2015-07-06     Bernard           remove RT_CAN_USING_LED.
 * 2022-05-08     hpmicro           add CANFD support, fixed typos
 */

#ifndef __DEV_CAN_H_
#define __DEV_CAN_H_

#include <rtthread.h>

#ifndef RT_CANMSG_BOX_SZ
#define RT_CANMSG_BOX_SZ    16
#endif
#ifndef RT_CANSND_BOX_NUM
#define RT_CANSND_BOX_NUM   1
#endif

enum CAN_DLC
{
    CAN_MSG_0BYTE = 0,
    CAN_MSG_1BYTE,
    CAN_MSG_2BYTES,
    CAN_MSG_3BYTES,
    CAN_MSG_4BYTES,
    CAN_MSG_5BYTES,
    CAN_MSG_6BYTES,
    CAN_MSG_7BYTES,
    CAN_MSG_8BYTES,
    CAN_MSG_12BYTES,
    CAN_MSG_16BYTES,
    CAN_MSG_20BYTES,
    CAN_MSG_24BYTES,
    CAN_MSG_32BYTES,
    CAN_MSG_48BYTES,
    CAN_MSG_64BYTES,
};

enum CANBAUD
{
    CAN1MBaud   = 1000UL * 1000,/* 1 MBit/sec   */
    CAN800kBaud = 1000UL * 800, /* 800 kBit/sec */
    CAN500kBaud = 1000UL * 500, /* 500 kBit/sec */
    CAN250kBaud = 1000UL * 250, /* 250 kBit/sec */
    CAN125kBaud = 1000UL * 125, /* 125 kBit/sec */
    CAN100kBaud = 1000UL * 100, /* 100 kBit/sec */
    CAN50kBaud  = 1000UL * 50,  /* 50 kBit/sec  */
    CAN20kBaud  = 1000UL * 20,  /* 20 kBit/sec  */
    CAN10kBaud  = 1000UL * 10   /* 10 kBit/sec  */
};

#define RT_CAN_MODE_NORMAL              0
#define RT_CAN_MODE_LISTEN              1
#define RT_CAN_MODE_LOOPBACK            2
#define RT_CAN_MODE_LOOPBACKANLISTEN    3

#define RT_CAN_MODE_PRIV                0x01
#define RT_CAN_MODE_NOPRIV              0x00

/**
 * @addtogroup  Drivers          RTTHREAD Driver
 * @defgroup    CAN_Device          CAN Driver
 *
 * @brief       CAN driver api
 *
 * <b>Example</b>
 * @code {.c}
 * #include <rtthread.h>
 * #include "rtdevice.h"
 *
 * #define CAN_DEV_NAME       "can1"      // CAN 设备名称
 *
 * static struct rt_semaphore rx_sem;     // 用于接收消息的信号量
 * static rt_device_t can_dev;            // CAN 设备句柄
 *
 * // 接收数据回调函数
 * static rt_err_t can_rx_call(rt_device_t dev, rt_size_t size)
 * {
 *     // CAN 接收到数据后产生中断，调用此回调函数，然后发送接收信号量
 *     rt_sem_release(&rx_sem);
 *
 *     return RT_EOK;
 * }
 *
 * static void can_rx_thread(void *parameter)
 * {
 *     int i;
 *     rt_err_t res;
 *     struct rt_can_msg rxmsg = {0};
 *
 *     // 设置接收回调函数
 *     rt_device_set_rx_indicate(can_dev, can_rx_call);
 *
 * #ifdef RT_CAN_USING_HDR
 *     struct rt_can_filter_item items[5] =
 *     {
 *         RT_CAN_FILTER_ITEM_INIT(0x100, 0, 0, 0, 0x700, RT_NULL, RT_NULL), // std,match ID:0x100~0x1ff，hdr 为 - 1，设置默认过滤表
 *         RT_CAN_FILTER_ITEM_INIT(0x300, 0, 0, 0, 0x700, RT_NULL, RT_NULL), // std,match ID:0x300~0x3ff，hdr 为 - 1
 *         RT_CAN_FILTER_ITEM_INIT(0x211, 0, 0, 0, 0x7ff, RT_NULL, RT_NULL), // std,match ID:0x211，hdr 为 - 1
 *         RT_CAN_FILTER_STD_INIT(0x486, RT_NULL, RT_NULL),                  // std,match ID:0x486，hdr 为 - 1
 *         {0x555, 0, 0, 0, 0x7ff, 7,}                                       // std,match ID:0x555，hdr 为 7，指定设置 7 号过滤表
 *     };
 *     struct rt_can_filter_config cfg = {5, 1, items}; // 一共有 5 个过滤表
 *     // 设置硬件过滤表
 *     res = rt_device_control(can_dev, RT_CAN_CMD_SET_FILTER, &cfg);
 *     RT_ASSERT(res == RT_EOK);
 * #endif
 *     res = RT_TRUE;
 *     res = rt_device_control(can_dev, RT_CAN_CMD_START, &res);
 *     while (1)
 *     {
 *         // hdr 值为 - 1，表示直接从 uselist 链表读取数据
 *         rxmsg.hdr = -1;
 *         // 阻塞等待接收信号量
 *         rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
 *         // 从 CAN 读取一帧数据
 *         rt_device_read(can_dev, 0, &rxmsg, sizeof(rxmsg));
 *         // 打印数据 ID 及内容
 *         rt_kprintf("ID:%x", rxmsg.id);
 *         for (i = 0; i < 8; i++)
 *         {
 *             rt_kprintf("%2x", rxmsg.data[i]);
 *         }
 *
 *         rt_kprintf("\n");
 *     }
 * }
 *
 * int can_sample(int argc, char *argv[])
 * {
 *     struct rt_can_msg msg = {0};
 *     rt_err_t res;
 *     rt_size_t  size;
 *     rt_thread_t thread;
 *     char can_name[RT_NAME_MAX];
 *
 *     if (argc == 2)
 *     {
 *         rt_strncpy(can_name, argv[1], RT_NAME_MAX);
 *     }
 *     else
 *     {
 *         rt_strncpy(can_name, CAN_DEV_NAME, RT_NAME_MAX);
 *     }
 *     // 查找 CAN 设备
 *     can_dev = rt_device_find(can_name);
 *     if (!can_dev)
 *     {
 *         rt_kprintf("find %s failed!\n", can_name);
 *         return -RT_ERROR;
 *     }
 *
 *     // 初始化 CAN 接收信号量
 *     rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
 *
 *     // 以中断接收及发送方式打开 CAN 设备
 *     res = rt_device_open(can_dev, RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX);
 *     RT_ASSERT(res == RT_EOK);
 *     // 创建数据接收线程
 *     thread = rt_thread_create("can_rx", can_rx_thread, RT_NULL, 1024, 25, 10);
 *     if (thread != RT_NULL)
 *     {
 *         rt_thread_startup(thread);
 *     }
 *     else
 *     {
 *         rt_kprintf("create can_rx thread failed!\n");
 *     }
 *
 *     msg.id = 0x78;              // ID 为 0x78
 *     msg.ide = RT_CAN_STDID;     // 标准格式
 *     msg.rtr = RT_CAN_DTR;       // 数据帧
 *     msg.len = 8;                // 数据长度为 8
 *     // 待发送的 8 字节数据
 *     msg.data[0] = 0x00;
 *     msg.data[1] = 0x11;
 *     msg.data[2] = 0x22;
 *     msg.data[3] = 0x33;
 *     msg.data[4] = 0x44;
 *     msg.data[5] = 0x55;
 *     msg.data[6] = 0x66;
 *     msg.data[7] = 0x77;
 *     // 发送一帧 CAN 数据
 *     size = rt_device_write(can_dev, 0, &msg, sizeof(msg));
 *     if (size == 0)
 *     {
 *         rt_kprintf("can dev write data failed!\n");
 *     }
 *
 *     return res;
 * }
 * // 导出到 msh 命令列表中
 * MSH_CMD_EXPORT(can_sample, can device sample);
 * @endcode
 *
 * @ingroup     Drivers
 *
 */


/*!
 * @addtogroup CAN_Device
 * @{
 */
#define CAN_RX_FIFO0                (0x00000000U)  /*!< CAN receive FIFO 0 */
#define CAN_RX_FIFO1                (0x00000001U)  /*!< CAN receive FIFO 1 */

/**
 * @brief CAN filter item
 */
struct rt_can_filter_item
{
    rt_uint32_t id  : 29;
    rt_uint32_t ide : 1;
    rt_uint32_t rtr : 1;
    rt_uint32_t mode : 1;
    rt_uint32_t mask;
    rt_int32_t  hdr_bank;/*Should be defined as:rx.FilterBank,which should be changed to rt_int32_t hdr_bank*/
    rt_uint32_t rxfifo;/*Add a configuration item that CAN_RX_FIFO0/CAN_RX_FIFO1*/
#ifdef RT_CAN_USING_HDR
    rt_err_t (*ind)(rt_device_t dev, void *args , rt_int32_t hdr, rt_size_t size);
    void *args;
#endif /*RT_CAN_USING_HDR*/
};


#ifdef RT_CAN_USING_HDR
#define RT_CAN_FILTER_ITEM_INIT(id,ide,rtr,mode,mask,ind,args) \
      {(id), (ide), (rtr), (mode),(mask), -1, CAN_RX_FIFO0,(ind), (args)}/*0:CAN_RX_FIFO0*/
#define RT_CAN_FILTER_STD_INIT(id,ind,args) \
     RT_CAN_FILTER_ITEM_INIT(id,0,0,0,0xFFFFFFFF,ind,args)
#define RT_CAN_FILTER_EXT_INIT(id,ind,args) \
     RT_CAN_FILTER_ITEM_INIT(id,1,0,0,0xFFFFFFFF,ind,args)
#define RT_CAN_STD_RMT_FILTER_INIT(id,ind,args) \
     RT_CAN_FILTER_ITEM_INIT(id,0,1,0,0xFFFFFFFF,ind,args)
#define RT_CAN_EXT_RMT_FILTER_INIT(id,ind,args) \
     RT_CAN_FILTER_ITEM_INIT(id,1,1,0,0xFFFFFFFF,ind,args)
#define RT_CAN_STD_RMT_DATA_FILTER_INIT(id,ind,args) \
     RT_CAN_FILTER_ITEM_INIT(id,0,0,1,0xFFFFFFFF,ind,args)
#define RT_CAN_EXT_RMT_DATA_FILTER_INIT(id,ind,args) \
     RT_CAN_FILTER_ITEM_INIT(id,1,0,1,0xFFFFFFFF,ind,args)
#else

#define RT_CAN_FILTER_ITEM_INIT(id,ide,rtr,mode,mask) \
      {(id), (ide), (rtr), (mode), (mask), -1, CAN_RX_FIFO0 }/*0:CAN_RX_FIFO0*/
#define RT_CAN_FILTER_STD_INIT(id) \
     RT_CAN_FILTER_ITEM_INIT(id,0,0,0,0xFFFFFFFF)
#define RT_CAN_FILTER_EXT_INIT(id) \
     RT_CAN_FILTER_ITEM_INIT(id,1,0,0,0xFFFFFFFF)
#define RT_CAN_STD_RMT_FILTER_INIT(id) \
     RT_CAN_FILTER_ITEM_INIT(id,0,1,0,0xFFFFFFFF)
#define RT_CAN_EXT_RMT_FILTER_INIT(id) \
     RT_CAN_FILTER_ITEM_INIT(id,1,1,0,0xFFFFFFFF)
#define RT_CAN_STD_RMT_DATA_FILTER_INIT(id) \
     RT_CAN_FILTER_ITEM_INIT(id,0,0,1,0xFFFFFFFF)
#define RT_CAN_EXT_RMT_DATA_FILTER_INIT(id) \
     RT_CAN_FILTER_ITEM_INIT(id,1,0,1,0xFFFFFFFF)
#endif


/**
 * @brief CAN filter configuration
 */
struct rt_can_filter_config
{
    rt_uint32_t count;
    rt_uint32_t actived;
    struct rt_can_filter_item *items;
};

/**
 * @brief CAN timing configuration
 */
struct rt_can_bit_timing
{
    rt_uint16_t prescaler;  /* Pre-scaler */
    rt_uint16_t num_seg1;   /* Bit Timing Segment 1, in terms of Tq */
    rt_uint16_t num_seg2;   /* Bit Timing Segment 2, in terms of Tq */
    rt_uint8_t num_sjw;     /* Synchronization Jump Width, in terms of Tq */
    rt_uint8_t num_sspoff;  /* Secondary Sample Point Offset, in terms of Tq */
};

/**
 * @brief CAN bit timing configuration list
 * @note
 *  items[0] always for CAN2.0/CANFD Arbitration Phase
 *  items[1] always for CANFD (if it exists)
 */
struct rt_can_bit_timing_config
{
    rt_uint32_t count;
    struct rt_can_bit_timing *items;
};


/**
 * @brief CAN configuration
 */
struct can_configure
{
    rt_uint32_t baud_rate;
    rt_uint32_t msgboxsz;
    rt_uint32_t sndboxnumber;
    rt_uint32_t mode      : 8;
    rt_uint32_t privmode  : 8;
    rt_uint32_t reserved  : 16;
    rt_uint32_t ticks;
#ifdef RT_CAN_USING_HDR
    rt_uint32_t maxhdr;
#endif

#ifdef RT_CAN_USING_CANFD
    rt_uint32_t baud_rate_fd;       /* CANFD data bit rate*/
    rt_uint32_t use_bit_timing: 8;  /* Use the bit timing for CAN timing configuration */
    rt_uint32_t enable_canfd : 8;   /* Enable CAN-FD mode */
    rt_uint32_t reserved1 : 16;

    /* The below fields take effect only if use_bit_timing is non-zero */
    struct rt_can_bit_timing can_timing;    /* CAN bit-timing /CANFD bit-timing for arbitration phase */
    struct rt_can_bit_timing canfd_timing;  /* CANFD bit-timing for datat phase */
#endif
};

#define CANDEFAULTCONFIG \
{\
        CAN1MBaud,\
        RT_CANMSG_BOX_SZ,\
        RT_CANSND_BOX_NUM,\
        RT_CAN_MODE_NORMAL,\
};

struct rt_can_ops;
#define RT_CAN_CMD_SET_FILTER       0x13
#define RT_CAN_CMD_SET_BAUD         0x14
#define RT_CAN_CMD_SET_MODE         0x15
#define RT_CAN_CMD_SET_PRIV         0x16
#define RT_CAN_CMD_GET_STATUS       0x17
#define RT_CAN_CMD_SET_STATUS_IND   0x18
#define RT_CAN_CMD_SET_BUS_HOOK     0x19
#define RT_CAN_CMD_SET_CANFD        0x1A
#define RT_CAN_CMD_SET_BAUD_FD      0x1B
#define RT_CAN_CMD_SET_BITTIMING    0x1C
#define RT_CAN_CMD_START            0x1D

#define RT_DEVICE_CAN_INT_ERR       0x1000

enum RT_CAN_STATUS_MODE
{
    NORMAL = 0,
    ERRWARNING = 1,
    ERRPASSIVE = 2,
    BUSOFF = 4,
};
enum RT_CAN_BUS_ERR
{
    RT_CAN_BUS_NO_ERR = 0,
    RT_CAN_BUS_BIT_PAD_ERR = 1,
    RT_CAN_BUS_FORMAT_ERR = 2,
    RT_CAN_BUS_ACK_ERR = 3,
    RT_CAN_BUS_IMPLICIT_BIT_ERR = 4,
    RT_CAN_BUS_EXPLICIT_BIT_ERR = 5,
    RT_CAN_BUS_CRC_ERR = 6,
};

/**
 * @brief CAN status
 */
struct rt_can_status
{
    rt_uint32_t rcverrcnt;
    rt_uint32_t snderrcnt;
    rt_uint32_t errcode;
    rt_uint32_t rcvpkg;
    rt_uint32_t dropedrcvpkg;
    rt_uint32_t sndpkg;
    rt_uint32_t dropedsndpkg;
    rt_uint32_t bitpaderrcnt;
    rt_uint32_t formaterrcnt;
    rt_uint32_t ackerrcnt;
    rt_uint32_t biterrcnt;
    rt_uint32_t crcerrcnt;
    rt_uint32_t rcvchange;
    rt_uint32_t sndchange;
    rt_uint32_t lasterrtype;
};

#ifdef RT_CAN_USING_HDR
struct rt_can_hdr
{
    rt_uint32_t connected;
    rt_uint32_t msgs;
    struct rt_can_filter_item filter;
    struct rt_list_node list;
};
#endif
struct rt_can_device;
typedef rt_err_t (*rt_canstatus_ind)(struct rt_can_device *, void *);

typedef struct rt_can_status_ind_type
{
    rt_canstatus_ind ind;
    void *args;
} *rt_can_status_ind_type_t;
typedef void (*rt_can_bus_hook)(struct rt_can_device *);
struct rt_can_device
{
    struct rt_device parent;

    const struct rt_can_ops *ops;
    struct can_configure config;
    struct rt_can_status status;

    rt_uint32_t timerinitflag;
    struct rt_timer timer;

    struct rt_can_status_ind_type status_indicate;
#ifdef RT_CAN_USING_HDR
    struct rt_can_hdr *hdr;
#endif
#ifdef RT_CAN_USING_BUS_HOOK
    rt_can_bus_hook bus_hook;
#endif /*RT_CAN_USING_BUS_HOOK*/
    struct rt_mutex lock;
    void *can_rx;
    void *can_tx;
};
typedef struct rt_can_device *rt_can_t;

#define RT_CAN_STDID 0
#define RT_CAN_EXTID 1
#define RT_CAN_DTR   0
#define RT_CAN_RTR   1

typedef struct rt_can_status *rt_can_status_t;

struct rt_can_msg
{
    rt_uint32_t id  : 29;
    rt_uint32_t ide : 1;
    rt_uint32_t rtr : 1;
    rt_uint32_t rsv : 1;
    rt_uint32_t len : 8;
    rt_uint32_t priv : 8;
    rt_int32_t hdr_index : 8;/*Should be defined as:rx.FilterMatchIndex,which should be changed to rt_int32_t hdr_index : 8*/
#ifdef RT_CAN_USING_CANFD
    rt_uint32_t fd_frame : 1;
    rt_uint32_t brs : 1;
    rt_uint32_t rxfifo : 2;/*Redefined to return :CAN RX FIFO0/CAN RX FIFO1*/
    rt_uint32_t reserved : 4;
#else
    rt_uint32_t rxfifo : 2;/*Redefined to return :CAN RX FIFO0/CAN RX FIFO1*/
    rt_uint32_t reserved : 6;
#endif
#ifdef RT_CAN_USING_CANFD
    rt_uint8_t data[64];
#else
    rt_uint8_t data[8];
#endif
};
typedef struct rt_can_msg *rt_can_msg_t;

struct rt_can_msg_list
{
    struct rt_list_node list;
#ifdef RT_CAN_USING_HDR
    struct rt_list_node hdrlist;
    struct rt_can_hdr *owner;
#endif
    struct rt_can_msg data;
};

struct rt_can_rx_fifo
{
    /* software fifo */
    struct rt_can_msg_list *buffer;
    rt_uint32_t freenumbers;
    struct rt_list_node freelist;
    struct rt_list_node uselist;
};

#define RT_CAN_SND_RESULT_OK        0
#define RT_CAN_SND_RESULT_ERR       1
#define RT_CAN_SND_RESULT_WAIT      2

#define RT_CAN_EVENT_RX_IND         0x01    /* Rx indication */
#define RT_CAN_EVENT_TX_DONE        0x02    /* Tx complete   */
#define RT_CAN_EVENT_TX_FAIL        0x03    /* Tx fail   */
#define RT_CAN_EVENT_RX_TIMEOUT     0x05    /* Rx timeout    */
#define RT_CAN_EVENT_RXOF_IND       0x06    /* Rx overflow */

struct rt_can_sndbxinx_list
{
    struct rt_list_node list;
    struct rt_completion completion;
    rt_uint32_t result;
};

struct rt_can_tx_fifo
{
    struct rt_can_sndbxinx_list *buffer;
    struct rt_semaphore sem;
    struct rt_list_node freelist;
};

/**
 * @brief CAN operators
 */
struct rt_can_ops
{
    rt_err_t (*configure)(struct rt_can_device *can, struct can_configure *cfg);
    rt_err_t (*control)(struct rt_can_device *can, int cmd, void *arg);
    rt_ssize_t (*sendmsg)(struct rt_can_device *can, const void *buf, rt_uint32_t boxno);
    rt_ssize_t (*recvmsg)(struct rt_can_device *can, void *buf, rt_uint32_t boxno);
};

/**
 * @brief Register a CAN device to device list
 *
 * @param can   the CAN device object
 * @param name  the name of CAN device
 * @param ops   the CAN device operators
 * @param data  the private data of CAN device
 *
 * @return the error code, RT_EOK on successfully
 */
rt_err_t rt_hw_can_register(struct rt_can_device    *can,
                            const char              *name,
                            const struct rt_can_ops *ops,
                            void                    *data);

/**
 * @brief CAN interrupt service routine
 *
 * @param can    the CAN device
 * @param event  the event mask
 */
void rt_hw_can_isr(struct rt_can_device *can, int event);

/*! @}*/

#endif /*__DEV_CAN_H*/
