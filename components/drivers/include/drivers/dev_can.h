/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2015-05-14     aubrcool@qq.com   first version
 * 2015-07-06     Bernard           remove RT_CAN_USING_LED.
 * 2022-05-08     hpmicro           add CANFD support, fixed typos
 * 2025-09-20     wdfk_prog         Added non-blocking send mechanism APIs and data structures.
 */

#ifndef __DEV_CAN_H_
#define __DEV_CAN_H_

#include <rtthread.h>
#include <rtdevice.h>

#ifndef RT_CANMSG_BOX_SZ
#define RT_CANMSG_BOX_SZ    16
#endif
#ifndef RT_CANSND_BOX_NUM
#define RT_CANSND_BOX_NUM   1
#endif
#ifndef RT_CANSND_MSG_TIMEOUT
#define RT_CANSND_MSG_TIMEOUT 100
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

#define RT_CAN_MODE_MASK                0x00
#define RT_CAN_MODE_LIST                0x01

/**
 * @defgroup    group_drivers_can CAN Driver
 * @brief       CAN driver api
 * @ingroup     group_device_driver
 *
 * <b>Example: Demonstrating CAN RX, Filters, and Blocking/Non-Blocking TX</b>
 * @code {.c}
 * #include <rtthread.h>
 * #include <rtdevice.h>
 *
 * #define CAN_DEV_NAME       "can1"      // The name of the CAN device
 *
 * static rt_device_t can_dev;            // CAN device handle
 * static struct rt_semaphore rx_sem;     // Semaphore for message reception
 *
 * // Callback function for CAN reception
 * static rt_err_t can_rx_callback(rt_device_t dev, rt_size_t size)
 * {
 *     // The CAN interrupt calls this callback when data is received.
 *     // Release the semaphore to notify the receiving thread.
 *     rt_sem_release(&rx_sem);
 *     return RT_EOK;
 * }
 *
 * static void can_rx_thread(void *parameter)
 * {
 *     rt_err_t res;
 *     struct rt_can_msg rx_msg = {0};
 *
 *     // Set the receive callback function
 *     rt_device_set_rx_indicate(can_dev, can_rx_callback);
 *
 * #ifdef RT_CAN_USING_HDR
 *     // Example of configuring multiple hardware filters
 *     struct rt_can_filter_item items[] =
 *     {
 *         // Filter 1: Match standard frames with IDs from 0x100 to 0x1FF. hdr_index will be -1.
 *         RT_CAN_FILTER_ITEM_INIT(0x100, 0, 0, 0, 0x700, RT_NULL, RT_NULL),
 *         // Filter 2: Match standard frames with IDs from 0x300 to 0x3FF. hdr_index will be -1.
 *         RT_CAN_FILTER_ITEM_INIT(0x300, 0, 0, 0, 0x700, RT_NULL, RT_NULL),
 *         // Filter 3: Exactly match standard frame with ID 0x211. hdr_index will be -1.
 *         RT_CAN_FILTER_ITEM_INIT(0x211, 0, 0, 0, 0x7FF, RT_NULL, RT_NULL),
 *         // Filter 4: Exactly match standard frame with ID 0x486 using a helper macro. hdr_index will be -1.
 *         RT_CAN_FILTER_STD_INIT(0x486, RT_NULL, RT_NULL),
 *         // Filter 5: Exactly match standard frame with ID 0x555 and explicitly assign it to filter bank #7.
 *         // This uses direct struct initialization: {id, ide, rtr, mode, mask, hdr_bank}.
 *         {0x555, 0, 0, 0, 0x7FF, 7}
 *     };
 *     // Create the filter configuration structure with 5 active filters.
 *     struct rt_can_filter_config cfg = {sizeof(items)/sizeof(items[0]), 1, items};
 *     // Set the hardware filters for the CAN device.
 *     res = rt_device_control(can_dev, RT_CAN_CMD_SET_FILTER, &cfg);
 *     RT_ASSERT(res == RT_EOK);
 * #endif
 *
 *     // Some drivers might require an explicit start command.
 *     // This is driver-specific.
 *     rt_uint32_t cmd_arg = 1; // Argument to enable the controller
 *     res = rt_device_control(can_dev, RT_CAN_CMD_START, &cmd_arg);
 *     RT_ASSERT(res == RT_EOK);
 *
 *     while (1)
 *     {
 *         // Block and wait for the semaphore, which is released by the receive callback.
 *         rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
 *
 *         // Read one frame of data from the CAN device's general message queue.
 *         rx_msg.hdr_index = -1;
 *         rt_device_read(can_dev, 0, &rx_msg, sizeof(rx_msg));
 *
 *         // Print the received message's ID and data.
 *         rt_kprintf("Received a message. ID: 0x%x, Data: ", rx_msg.id);
 *         for (int i = 0; i < rx_msg.len; i++)
 *         {
 *             rt_kprintf("%02x ", rx_msg.data[i]);
 *         }
 *         rt_kprintf("\n");
 *     }
 * }
 *
 * int can_sample(int argc, char *argv[])
 * {
 *     rt_err_t res;
 *     rt_thread_t thread;
 *     char can_name[RT_NAME_MAX];
 *
 *     // Allow specifying the CAN device name from the command line, e.g., "can_sample can2"
 *     if (argc == 2)
 *     {
 *         rt_strncpy(can_name, argv[1], RT_NAME_MAX);
 *     }
 *     else
 *     {
 *         rt_strncpy(can_name, CAN_DEV_NAME, RT_NAME_MAX);
 *     }
 *
 *     // Find the CAN device by name
 *     can_dev = rt_device_find(can_name);
 *     if (!can_dev)
 *     {
 *         rt_kprintf("find device %s failed!\n", can_name);
 *         return -RT_ERROR;
 *     }
 *
 *     // Initialize the receive semaphore
 *     rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
 *
 *     // Open the CAN device in interrupt-driven TX/RX mode
 *     res = rt_device_open(can_dev, RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX);
 *     RT_ASSERT(res == RT_EOK);
 *
 *     // Create and start the data receiving thread
 *     thread = rt_thread_create("can_rx", can_rx_thread, RT_NULL, 1024, 25, 10);
 *     if (thread != RT_NULL)
 *     {
 *         rt_thread_startup(thread);
 *     }
 *     else
 *     {
 *         rt_kprintf("create can_rx thread failed!\n");
 *         return -RT_ERROR;
 *     }
 *
 *     rt_kprintf("CAN device %s opened successfully.\n", can_name);
 *
 *     // --- Demonstrate Blocking Send ---
 *     struct rt_can_msg blocking_msg = {0};
 *     blocking_msg.id = 0x78;
 *     blocking_msg.ide = RT_CAN_STDID;
 *     blocking_msg.rtr = RT_CAN_DTR;
 *     blocking_msg.len = 8;
 *     // The `nonblocking` flag is 0 by default for blocking mode.
 *     for(int i = 0; i < 8; i++) blocking_msg.data[i] = i;
 *
 *     rt_kprintf("Attempting to send a message in BLOCKING mode...\n");
 *     if (rt_device_write(can_dev, 0, &blocking_msg, sizeof(blocking_msg)) == sizeof(blocking_msg))
 *     {
 *         rt_kprintf("Blocking message sent successfully.\n");
 *     }
 *     else
 *     {
 *         rt_kprintf("Blocking message send failed.\n");
 *     }
 *
 *     rt_thread_mdelay(100); // Wait a moment for clarity in the log
 *
 *     // --- Demonstrate Non-Blocking Send ---
 *     struct rt_can_msg nonblocking_msg = {0};
 *     nonblocking_msg.id = 0x79;
 *     nonblocking_msg.ide = RT_CAN_STDID;
 *     nonblocking_msg.rtr = RT_CAN_DTR;
 *     nonblocking_msg.len = 4;
 *     nonblocking_msg.data[0] = 0xDE;
 *     nonblocking_msg.data[1] = 0xAD;
 *     nonblocking_msg.data[2] = 0xBE;
 *     nonblocking_msg.data[3] = 0xEF;
 *     nonblocking_msg.nonblocking = 1; // <-- Key: Set the non-blocking flag
 *
 *     rt_kprintf("Attempting to send a message in NON-BLOCKING mode...\n");
 *     if (rt_device_write(can_dev, 0, &nonblocking_msg, sizeof(nonblocking_msg)) == sizeof(nonblocking_msg))
 *     {
 *         rt_kprintf("Non-blocking message was accepted (sent or enqueued).\n");
 *     }
 *     else
 *     {
 *         rt_kprintf("Non-blocking send failed (buffer was full).\n");
 *     }
 *
 *     return res;
 * }
 * // Export the function to the MSH command line
 * MSH_CMD_EXPORT(can_sample, can device usage example);
 * @endcode
 */

/*!
 * @addtogroup group_drivers_can
 * @{
 */
#define CAN_RX_FIFO0                (0x00000000U)  /*!< CAN receive FIFO 0 */
#define CAN_RX_FIFO1                (0x00000001U)  /*!< CAN receive FIFO 1 */

/**
 * @brief CAN filter item structure
 */
struct rt_can_filter_item
{
    rt_uint32_t id  : 29;   /**< The CAN ID to be filtered. */
    rt_uint32_t ide : 1;    /**< Identifier type. 0 for Standard ID, 1 for Extended ID. */
    rt_uint32_t rtr : 1;    /**< Frame type. 0 for Data Frame, 1 for Remote Frame. */
    rt_uint32_t mode : 1;   /**< Filter mode. 0 for Mask Mode, 1 for List Mode. */
    rt_uint32_t mask;       /**< The filter mask. In Mask Mode, a '1' bit means the corresponding ID bit must match. */
    rt_int32_t  hdr_bank;   /**< The specific hardware filter bank index to use. A value of -1 allows the driver to auto-assign. */
    rt_uint32_t rxfifo;     /**< The target RX FIFO for matched messages (CAN_RX_FIFO0 or CAN_RX_FIFO1). */
#ifdef RT_CAN_USING_HDR
    /**
     * @brief Callback function for a specific filter.
     * @param[in] dev   The CAN device that triggered the callback.
     * @param[in] args  User-provided arguments.
     * @param[in] hdr   The hardware filter index that matched the message.
     * @param[in] size  The size of the received data in bytes.
     * @return The operation status.
     */
    rt_err_t (*ind)(rt_device_t dev, void *args , rt_int32_t hdr, rt_size_t size);
    void *args;             /**< User arguments for the indication callback. */
#endif /*RT_CAN_USING_HDR*/
};

#ifdef RT_CAN_USING_HDR
/**
 * @def RT_CAN_FILTER_ITEM_INIT
 * @brief A helper macro to initialize a `rt_can_filter_item` structure for Mask Mode.
 *
 * @param[in] id   The CAN ID for the filter.
 * @param[in] ide  Identifier type (0 for Standard, 1 for Extended).
 * @param[in] rtr  Frame type (0 for Data, 1 for Remote).
 * @param[in] mode Filter mode (0 for Mask, 1 for List).
 * @param[in] mask The mask to be applied.
 * @param[in] ind  Optional callback function (can be RT_NULL).
 * @param[in] args Optional arguments for the callback (can be RT_NULL).
 */
#define RT_CAN_FILTER_ITEM_INIT(id,ide,rtr,mode,mask,ind,args) \
      {(id), (ide), (rtr), (mode),(mask), -1, CAN_RX_FIFO0,(ind), (args)}
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
/**
 * @def RT_CAN_FILTER_ITEM_INIT
 * @brief A helper macro to initialize a `rt_can_filter_item` structure for Mask Mode.
 *
 * @param[in] id   The CAN ID for the filter.
 * @param[in] ide  Identifier type (0 for Standard, 1 for Extended).
 * @param[in] rtr  Frame type (0 for Data, 1 for Remote).
 * @param[in] mode Filter mode (0 for Mask, 1 for List).
 * @param[in] mask The mask to be applied.
 */
#define RT_CAN_FILTER_ITEM_INIT(id,ide,rtr,mode,mask) \
      {(id), (ide), (rtr), (mode), (mask), -1, CAN_RX_FIFO0 }
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
 * @brief CAN hardware filter configuration structure.
 * This structure is passed to the driver via `rt_device_control` with the `RT_CAN_CMD_SET_FILTER` command.
 */
struct rt_can_filter_config
{
    rt_uint32_t count;                /**< The number of filter items in the `items` array. */
    rt_uint32_t actived;              /**< A flag to activate (1) or deactivate (0) the filters. */
    struct rt_can_filter_item *items; /**< A pointer to an array of filter items. */
};

/**
 * @brief CAN bit-timing parameters structure.
 */
struct rt_can_bit_timing
{
    rt_uint16_t prescaler;  /**< Baud rate prescaler. */
    rt_uint16_t num_seg1;   /**< Bit Timing Segment 1, in terms of Time Quanta (Tq). */
    rt_uint16_t num_seg2;   /**< Bit Timing Segment 2, in terms of Time Quanta (Tq). */
    rt_uint8_t num_sjw;     /**< Synchronization Jump Width, in terms of Time Quanta (Tq). */
    rt_uint8_t num_sspoff;  /**< Secondary Sample Point Offset, in terms of Time Quanta (Tq) for CAN-FD. */
};

/**
 * @brief CAN bit timing configuration list structure.
 * @note items[0] is for CAN 2.0 / CAN-FD Arbitration Phase.
 *       items[1] is for CAN-FD Data Phase (if applicable).
 */
struct rt_can_bit_timing_config
{
    rt_uint32_t count;                  /**< The number of bit-timing configurations (typically 1 for CAN, 2 for CAN-FD). */
    struct rt_can_bit_timing *items;    /**< A pointer to an array of bit-timing structures. */
};


/**
 * @brief CAN device configuration structure.
 */
struct can_configure
{
    rt_uint32_t baud_rate;      /**< The baud rate for the arbitration phase (e.g., CAN500kBaud). */
    rt_uint32_t msgboxsz;       /**< The size of the software receive buffer (in number of messages). */
    rt_uint32_t sndboxnumber;   /**< The number of hardware mailboxes used for blocking send operations. */
    rt_uint32_t mode      : 8;  /**< The CAN operation mode (e.g., RT_CAN_MODE_NORMAL, RT_CAN_MODE_LOOPBACK). */
    rt_uint32_t privmode  : 8;  /**< Private mode flag. If set, the `priv` field of `rt_can_msg` specifies the hardware mailbox. */
    rt_uint32_t reserved  : 16; /**< Reserved for future use. */
    rt_uint32_t ticks;          /**< The period in OS ticks for the status-checking timer. */
#ifdef RT_CAN_USING_HDR
    rt_uint32_t maxhdr;         /**< The maximum number of hardware filters supported by the controller. */
#endif

#ifdef RT_CAN_USING_CANFD
    rt_uint32_t baud_rate_fd;       /**< The baud rate for the CAN-FD data phase. */
    rt_uint32_t use_bit_timing: 8;  /**< A flag to indicate that `can_timing` and `canfd_timing` should be used instead of `baud_rate`. */
    rt_uint32_t enable_canfd : 8;   /**< A flag to enable CAN-FD functionality. */
    rt_uint32_t reserved1 : 16;     /**< Reserved for future use. */

    /* The below fields take effect only if use_bit_timing is non-zero */
    struct rt_can_bit_timing can_timing;    /**< Custom bit-timing for the arbitration phase. */
    struct rt_can_bit_timing canfd_timing;  /**< Custom bit-timing for the data phase. */
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
 * @brief CAN device status and error statistics structure.
 */
struct rt_can_status
{
    rt_uint32_t rcverrcnt;      /**< Receive Error Counter (REC). */
    rt_uint32_t snderrcnt;      /**< Transmit Error Counter (TEC). */
    rt_uint32_t errcode;        /**< The current bus error code (see `enum RT_CAN_BUS_ERR`). */
    rt_uint32_t rcvpkg;         /**< Total number of successfully received packages. */
    rt_uint32_t dropedrcvpkg;   /**< Number of received packages dropped due to full buffers. */
    rt_uint32_t sndpkg;         /**< Total number of successfully sent packages. */
    rt_uint32_t dropedsndpkg;   /**< Number of sent packages dropped due to full buffers or errors. */
    rt_uint32_t bitpaderrcnt;   /**< Bit stuffing error count. */
    rt_uint32_t formaterrcnt;   /**< Format error count. */
    rt_uint32_t ackerrcnt;      /**< Acknowledgment error count. */
    rt_uint32_t biterrcnt;      /**< Bit error (recessive/dominant) count. */
    rt_uint32_t crcerrcnt;      /**< CRC error count. */
    rt_uint32_t rcvchange;      /**< A flag indicating that the RX buffer status has changed. */
    rt_uint32_t sndchange;      /**< A bitmask indicating which TX mailboxes have changed status. */
    rt_uint32_t lasterrtype;    /**< The type of the last error that occurred. */
};

#ifdef RT_CAN_USING_HDR
/**
 * @brief CAN hardware filter list entry.
 * @internal
 */
struct rt_can_hdr
{
    rt_uint32_t connected;            /**< Flag indicating if the filter is connected to a specific list. */
    rt_uint32_t msgs;                 /**< The number of messages currently buffered for this filter. */
    struct rt_can_filter_item filter; /**< A copy of the filter configuration item. */
    struct rt_list_node list;         /**< The list head for messages matched by this filter. */
};
#endif
struct rt_can_device;
/**
 * @brief Typedef for the CAN status indication callback function.
 * @param[in] can  A pointer to the CAN device.
 * @param[in] args User-provided arguments.
 * @return The operation status.
 */
typedef rt_err_t (*rt_canstatus_ind)(struct rt_can_device *can, void *args);

/**
 * @brief Structure to hold the status indication callback and its arguments.
 */
typedef struct rt_can_status_ind_type
{
    rt_canstatus_ind ind;   /**< Pointer to the status indication callback function. */
    void *args;             /**< Pointer to user arguments for the callback. */
} *rt_can_status_ind_type_t;

/**
 * @brief Typedef for the periodic bus hook function.
 * @param[in] can A pointer to the CAN device.
 * @return void
 */
typedef void (*rt_can_bus_hook)(struct rt_can_device *can);

/**
 * @brief The CAN message structure.
 */
struct rt_can_msg
{
    rt_uint32_t id  : 29;           /**< CAN ID (Standard or Extended). */
    rt_uint32_t ide : 1;            /**< Identifier type: 0=Standard ID, 1=Extended ID. */
    rt_uint32_t rtr : 1;            /**< Frame type: 0=Data Frame, 1=Remote Frame. */
    rt_uint32_t rsv : 1;            /**< Reserved bit. */
    rt_uint32_t len : 8;            /**< Data Length Code (DLC) from 0 to 8. */
    rt_uint32_t priv : 8;           /**< Private data, used to specify the hardware mailbox in private mode. */
    rt_int32_t hdr_index : 8;       /**< For received messages, the index of the hardware filter that matched the message. */
#ifdef RT_CAN_USING_CANFD
    rt_uint32_t fd_frame : 1;       /**< CAN-FD frame indicator. */
    rt_uint32_t brs : 1;            /**< Bit-rate switching indicator for CAN-FD. */
    rt_uint32_t rxfifo : 2;         /**< The RX FIFO where the message was received. */
    rt_uint32_t reserved : 3;
#else
    rt_uint32_t rxfifo : 2;         /**< The RX FIFO where the message was received. */
    rt_uint32_t reserved : 5;
#endif
    rt_uint32_t nonblocking : 1;    /**< Send mode: 0=Blocking (default), 1=Non-blocking. */
#ifdef RT_CAN_USING_CANFD
    rt_uint8_t data[64];            /**< CAN-FD message payload (up to 64 bytes). */
#else
    rt_uint8_t data[8];             /**< CAN message payload (up to 8 bytes). */
#endif
};
typedef struct rt_can_msg *rt_can_msg_t;

#ifndef RT_CAN_NB_TX_FIFO_SIZE
#define RT_CAN_NB_TX_FIFO_SIZE   (RT_CANMSG_BOX_SZ * sizeof(struct rt_can_msg))
#endif

/**
 * @brief The core CAN device structure.
 */
struct rt_can_device
{
    struct rt_device parent;            /**< Inherits from the base RT-Thread device structure. */

    const struct rt_can_ops *ops;       /**< A pointer to the low-level driver operations. */
    struct can_configure config;        /**< The current configuration of the CAN device. */
    struct rt_can_status status;        /**< The current status and error statistics of the CAN device. */

    rt_uint32_t timerinitflag;          /**< A flag to indicate if the status timer has been initialized. */
    struct rt_timer timer;              /**< A timer for periodically checking the CAN bus status. */

    struct rt_can_status_ind_type status_indicate; /**< The user-registered status indication callback. */
#ifdef RT_CAN_USING_HDR
    struct rt_can_hdr *hdr;             /**< A pointer to an array of hardware filter list entries. */
#endif
#ifdef RT_CAN_USING_BUS_HOOK
    rt_can_bus_hook bus_hook;           /**< The user-registered periodic bus hook function. */
#endif /*RT_CAN_USING_BUS_HOOK*/
    struct rt_mutex lock;               /**< A mutex for thread-safe access to the device. */
    void *can_rx;                       /**< A pointer to the software receive FIFO structure (`rt_can_rx_fifo`). */
    void *can_tx;                       /**< A pointer to the software transmit FIFO structure (`rt_can_tx_fifo`). */

    struct rt_ringbuffer nb_tx_rb;      /**< The ring buffer for non-blocking transmissions. */
#ifdef RT_CAN_MALLOC_NB_TX_BUFFER
    rt_uint8_t *nb_tx_rb_pool;          /**< A pointer to the dynamically allocated pool for the non-blocking TX ring buffer. */
#else
    rt_uint8_t nb_tx_rb_pool[RT_CAN_NB_TX_FIFO_SIZE]; /**< The statically allocated pool for the non-blocking TX ring buffer. */
#endif /* RT_CAN_MALLOC_NB_TX_BUFFER  */
};
typedef struct rt_can_device *rt_can_t;

#define RT_CAN_STDID 0
#define RT_CAN_EXTID 1
#define RT_CAN_DTR   0
#define RT_CAN_RTR   1

typedef struct rt_can_status *rt_can_status_t;

/**
 * @internal
 * @brief List node for a single CAN message in a software FIFO.
 */
struct rt_can_msg_list
{
    struct rt_list_node list;       /**< List node to link into a free/used list. */
#ifdef RT_CAN_USING_HDR
    struct rt_list_node hdrlist;    /**< List node to link into a specific hardware filter's list. */
    struct rt_can_hdr *owner;       /**< Pointer to the hardware filter that owns this message. */
#endif
    struct rt_can_msg data;         /**< The actual CAN message data. */
};

/**
 * @internal
 * @brief Software receive FIFO structure.
 */
struct rt_can_rx_fifo
{
    struct rt_can_msg_list *buffer; /**< A pointer to the buffer pool of message list nodes. */
    rt_uint32_t freenumbers;        /**< The number of free nodes in the buffer pool. */
    struct rt_list_node freelist;   /**< The list of free message nodes. */
    struct rt_list_node uselist;    /**< The list of used message nodes (containing received messages). */
};

#define RT_CAN_SND_RESULT_OK        0
#define RT_CAN_SND_RESULT_ERR       1
#define RT_CAN_SND_RESULT_WAIT      2

#define RT_CAN_EVENT_RX_IND         0x01    /* Rx indication */
#define RT_CAN_EVENT_TX_DONE        0x02    /* Tx complete   */
#define RT_CAN_EVENT_TX_FAIL        0x03    /* Tx fail   */
#define RT_CAN_EVENT_RX_TIMEOUT     0x05    /* Rx timeout    */
#define RT_CAN_EVENT_RXOF_IND       0x06    /* Rx overflow */

/**
 * @internal
 * @brief List node for a blocking send operation, corresponding to one hardware mailbox.
 */
struct rt_can_sndbxinx_list
{
    struct rt_list_node list;       /**< List node to link into the free list. */
    struct rt_completion completion;/**< A completion object to block the sending thread. */
    rt_uint32_t result;             /**< The result of the transmission (OK, ERR, WAIT). */
};

/**
 * @internal
 * @brief Software transmit FIFO structure for blocking sends.
 */
struct rt_can_tx_fifo
{
    struct rt_can_sndbxinx_list *buffer; /**< A pointer to the buffer of sendbox nodes. */
    struct rt_semaphore sem;             /**< A counting semaphore representing available hardware mailboxes. */
    struct rt_list_node freelist;        /**< The list of free sendbox nodes. */
};

/**
 * @brief The CAN device driver operations structure.
 *
 * This structure contains pointers to the low-level functions that implement the CAN functionality.
 * It must be provided when registering a CAN device.
 */
struct rt_can_ops
{
    /**
     * @brief Configures the CAN controller with the specified settings.
     * @param[in] can A pointer to the CAN device structure.
     * @param[in] cfg A pointer to the configuration structure.
     * @return `RT_EOK` on success, or a negative error code on failure.
     */
    rt_err_t (*configure)(struct rt_can_device *can, struct can_configure *cfg);
    /**
     * @brief Sends control commands to the CAN device.
     * @param[in] can A pointer to the CAN device structure.
     * @param[in] cmd The control command (e.g., RT_CAN_CMD_SET_FILTER).
     * @param[in] arg A pointer to the arguments for the command.
     * @return `RT_EOK` on success, or a negative error code on failure.
     */
    rt_err_t (*control)(struct rt_can_device *can, int cmd, void *arg);
    /**
     * @brief Low-level blocking function to send a CAN message.
     * @param[in] can   A pointer to the CAN device structure.
     * @param[in] buf   A pointer to the `rt_can_msg` to be sent.
     * @param[in] boxno The hardware mailbox number to use for transmission.
     * @return The number of bytes sent on success, or a negative error code on failure.
     */
    rt_ssize_t (*sendmsg)(struct rt_can_device *can, const void *buf, rt_uint32_t boxno);
    /**
     * @brief Low-level function to receive a CAN message.
     * @param[in,out] can A pointer to the CAN device structure.
     * @param[out]    buf A pointer to the buffer to store the received `rt_can_msg`.
     * @param[in]     fifo The hardware FIFO number to read from.
     * @return The number of bytes received on success, or a negative error code on failure.
     */
    rt_ssize_t (*recvmsg)(struct rt_can_device *can, void *buf, rt_uint32_t fifo);
    /**
     * @brief Low-level, hardware-specific function to send a CAN message non-blockingly.
     *
     * This function attempts to place a message into a hardware transmission mailbox
     * and returns immediately without waiting for the transmission to complete.
     *
     * @param[in] can A pointer to the CAN device structure.
     * @param[in] buf A pointer to the `rt_can_msg` to be sent.
     *
     * @return
     * - `RT_EOK` if the message was successfully accepted by the hardware.
     * - `-RT_EBUSY` if all hardware mailboxes are currently full.
     * - Other negative error codes for different failures.
     */
    rt_ssize_t (*sendmsg_nonblocking)(struct rt_can_device *can, const void *buf);
};

/**
 * @brief This function registers a CAN device with the device framework.
 *
 * @param[in] can   A pointer to the CAN device object to be registered.
 * @param[in] name  The name that the device will be registered with.
 * @param[in] ops   A pointer to the structure containing the low-level CAN driver operations.
 * @param[in] data  A pointer to a user-defined data structure, which can be accessed
 *                  via `can->parent.user_data`.
 *
 * @return `RT_EOK` on successful registration, or a negative error code on failure.
 */
rt_err_t rt_hw_can_register(struct rt_can_device    *can,
                            const char              *name,
                            const struct rt_can_ops *ops,
                            void                    *data);

/**
 * @brief The framework-level ISR handler for CAN devices.
 *
 * This function is called by the low-level BSP ISR and acts as the central
 * dispatcher for all CAN-related interrupt events. It handles both receive
 * events and transmission-complete events.
 *
 * @param[in] can    A pointer to the CAN device structure.
 * @param[in] event  The interrupt event mask, indicating the cause of the interrupt.
 */
void rt_hw_can_isr(struct rt_can_device *can, int event);

/*! @}*/

#endif /*__DEV_CAN_H*/

