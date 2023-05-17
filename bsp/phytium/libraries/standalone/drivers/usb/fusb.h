/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fusb.h
 * Date: 2022-02-11 13:33:11
 * LastEditTime: 2022-02-18 09:22:25
 * Description:  This files is for definition of FUSB user interface
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/7    init commit
 */

#ifndef  FUSB_H
#define  FUSB_H

/***************************** Include Files *********************************/
#include "ftypes.h"
#include "ferror_code.h"
#include "fassert.h"
#include "fusb_def.h"

#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions *****************************/
#define FUSB_SUCCESS            FT_SUCCESS
#define FUSB_ERR_WAIT_TIMEOUT   FT_MAKE_ERRCODE(ErrModBsp, ErrUsb, 0x0)
#define FUSB_ERR_INVALID_PARA   FT_MAKE_ERRCODE(ErrModBsp, ErrUsb, 0x1)
#define FUSB_ERR_NOT_SUPPORT    FT_MAKE_ERRCODE(ErrModBsp, ErrUsb, 0x2)
#define FUSB_ERR_NON_INSTANCE   FT_MAKE_ERRCODE(ErrModBsp, ErrUsb, 0x3)
#define FUSB_ERR_INVALID_DATA   FT_MAKE_ERRCODE(ErrModBsp, ErrUsb, 0x4)
#define FUSB_ERR_DESC_PARSE_ERR FT_MAKE_ERRCODE(ErrModBsp, ErrUsb, 0x5)
#define FUSB_ERR_ALLOCATE_FAIL  FT_MAKE_ERRCODE(ErrModBsp, ErrUsb, 0x6)
#define FUSB_ERR_TRANS_FAIL     FT_MAKE_ERRCODE(ErrModBsp, ErrUsb, 0x7)

/* SetAddress() recovery interval (USB 2.0 specification 9.2.6.3 */
#define FUSB_SET_ADDRESS_MDELAY 2

/*
 * USB sets an upper limit of 5 seconds for any transfer to be completed.
 *
 * Data originally from FUSB_HC_EHCI driver:
 *  Tested with some USB2.0 flash sticks:
 *  TUR turn around took  about 2.2s for the slowest (13fe:3800), maximum
 *  of 250ms for the others.
 *
 * SET ADDRESS on xHCI controllers.
 *  The USB specification indicates that devices must complete processing
 *  of a SET ADDRESS request within 50 ms.  However, some hubs were found
 *  to take more than 100 ms to complete a SET ADDRESS request on a
 *  downstream port.
 */
#define FUSB_USB_MAX_PROCESSING_TIME_US         (5 * 1000 * 1000)
#define FUSB_FULL_LOW_SPEED_FRAME_US            1000
#define FUSB_MAX_CTRL_NUM                       1
#define FUSB_MAX_DEV_TYPE_NUM                   8
#define FUSB_MAX_DEV_NUM                        128
#define FUSB_MAX_EP_NUM                         32
#define FUSB_MAX_SLOT_NUM                       FUSB_MAX_DEV_NUM

#define FUSB_SLOT_ID_VALID(slot)                ((0 <= (slot)) && (FUSB_MAX_SLOT_NUM > (slot)))


#define FUSB_DEFAULT_ALIGN                       1
#define FUSB_NO_DEV_ADDR                        -1
#define FUSB_NO_HUB                             -1
#define FUSB_NO_PORT                            -1

/**************************** Type Definitions *******************************/

typedef struct _FUsbDev FUsbDev;
typedef struct _FUsbHc FUsbHc;
typedef struct _FUsb FUsb;

/* Transfer complete code for USB */
enum
{
    FUSB_CC_ZERO_BYTES = 0,
    FUSB_CC_SUCCESS = 1

                      /* for XHCI transfer complete code, please refer to e.g. FXHCI_CC_SUCCESS */
                      /* be careful not define conflict CC code */
};

/* less than 0 means error (implemented by usb Hc, e.g. FXhciTransCode),
   greater or equal than 0 means bytes transfered */
typedef int FUsbTransCode;

typedef struct
{
    FUsbDev *dev; /* device instance of this endpoint */
    int endpoint; /* endpoint address ep0 = 0, epn = n */
    FUsbDirection direction; /* type or direction of ep */
    int toggle; /* ep state for some device to toggle */
    int maxpacketsize; /* max packet size for ep transfer */
    FUsbEpType type; /* transfer type of ep, control, bulk or so on */
    int interval; /* expressed as binary logarithm of the number
                    of microframes (i.e. t = 125us * 2^interval) */
} FUsbEndpoint; /* encapsulates a single endpoint of an USB device */
typedef struct
{
    const FUsbDescriptor *buf;
    u32 buf_len;
    boolean is_valid;
    const FUsbDescriptor *end_pos;
    const FUsbDescriptor *next_pos;
    const FUsbDescriptor *cur_desc;
    const FUsbDescriptor *err_pos;
} FUsbConfigParser; /* parser for configure descriptor */

typedef struct
{
#define FUSB_USBSTR_MIN_LEN         4
    FUsbStringDescriptor         *usb_str;
#define FUSB_STRDESC_BUF_MAX        64
    char                          str_buf[FUSB_STRDESC_BUF_MAX];
} FUsbStringParser; /* parser for string descriptor */

typedef int FUsbDevAddr;

typedef struct _FUsbDev
{
    FUsbHc *controller; /* Hc instance where device attached */
    FUsbEndpoint endpoints[FUSB_MAX_EP_NUM]; /* all Ep instance of device */
    int num_endp; /* num of Ep in use */
    FUsbDevAddr address; /* USB address */
    FUsbDevClass class; /* USB device class, e.g hid */
    int hub; /* hub where device is attached to */
    int port; /* port where device is attached */
    FUsbSpeed speed; /* speed type of device */
    void *data; /* private data for specific type of device */
    FUsbDeviceDescriptor *descriptor; /* device descriptor ever get from device hw */
    FUsbConfigurationDescriptor *configuration; /* configure descriptor followed with interface descriptor ever get from device hw */
    FUsbConfigParser  config_parser; /* parser for configure descriptor */
    FUsbStringParser  string_parser; /* parser for string descriptor */
    void (*init)(FUsbDev *dev); /* device init function of specific device type for register */
    void (*destroy)(FUsbDev *dev);  /* device deinit function of specific device type for register */
    void (*poll)(FUsbDev *dev);  /* device poll function of specific device type for register */
} FUsbDev; /* encapsulates a single USB device */

typedef enum
{
    FUSB_HC_OHCI = 0,
    FUSB_HC_UHCI = 1,
    FUSB_HC_EHCI = 2,
    FUSB_HC_XHCI = 3,
    FUSB_HC_DWC2 = 4
} FUsbHcType;

typedef struct _FUsbHc
{
    uintptr reg_base; /* base address of Hc register */
    FUsb *usb; /* instance of USB system */
    FUsbHcType type; /* type of Hc, e.g XHCI */
    FUsbDev *devices[FUSB_MAX_DEV_NUM]; /* dev 0 is root hub, 127 is last addressable */

    /* start():     Resume operation. */
    void (*start)(FUsbHc *controller);
    /* stop():      Stop operation but keep controller initialized. */
    void (*stop)(FUsbHc *controller);
    /* reset():     Perform a controller reset. The controller needs to
                    be (re)initialized afterwards to work (again). */
    FUsbTransCode(*reset)(FUsbHc *controller);
    /* init():      Initialize a (previously reset) controller
                    to a working state. */
    void (*init)(FUsbHc *controller);
    /* shutdown():  Stop operation, detach host controller and shutdown
                    this driver instance. After calling shutdown() any
                    other usage of this hci_t* is invalid. */
    void (*shutdown)(FUsbHc *controller);

    FUsbTransCode(*bulk)(FUsbEndpoint *ep, int size, u8 *data, int finalize);
    FUsbTransCode(*control)(FUsbDev *dev, FUsbDirection pid, int dr_length,
                            void *devreq, int data_length, u8 *data);
    void *(*create_intr_queue)(FUsbEndpoint *ep, int reqsize, int reqcount, int reqtiming);
    void (*destroy_intr_queue)(FUsbEndpoint *ep, void *queue);
    u8 *(*poll_intr_queue)(void *queue);
    void *instance; /* instance to specific Hc implementation, e.g XHCI */

    /* set_address():       Tell the USB device its address (xHCI
                    controllers want to do this by
                    themselves). Also, allocate the FUsbDev
                    structure, initialize enpoint 0
                    (including MPS) and return it. */
    FUsbDev *(*set_address)(FUsbHc *controller, FUsbSpeed speed,
                            int hubport, int hubaddr);
    /* finish_device_config():  Another hook for xHCI, returns 0 on success. */
    int (*finish_device_config)(FUsbDev *dev);
    /* destroy_device(): Finally, destroy all structures that
                         were allocated during set_address()
                         and finish_device_config(). */
    void (*destroy_device)(FUsbHc *controller, int devaddr);
} FUsbHc; /* encapsulates a single USB host */

typedef struct
{
    void *(*malloc_align)(size_t size, size_t align);
    void (*free)(void *mem);
} FUsbMemAllocator; /* memory allocator used in USB system */

typedef struct
{
    u32 instance_id; /* id for this USB system */
    uintptr base_addr; /* base addr of Hc register, set as 0 for pci-usb */
    u32 irq_num;
    u32 irq_priority;
    FUsbMemAllocator allocator; /* memory allocator to support dynamic memory */
} FUsbConfig; /* configure data of the USB system */

typedef enum
{
    FUSB_STANDARD_INTERFACE,
    FUSB_VENDOR_SPECIFIED
} FUsbDevCategory;

typedef struct
{
    FUsbDevCategory category;
    FUsbDevClass class;
    u32 sub_class;
    u32 protocol;
} FUsbDevIndex;

typedef void (* FUsbDevInitHandler)(FUsbDev *dev);

typedef struct
{
    FUsbDevIndex index;
    FUsbDevInitHandler handler;
} FUsbDevInitFunc;

typedef struct _FUsb
{
    FUsbConfig config; /* configuration of USB system */
    void *pcie_instance; /* NULL if unused */
    void *pcie_info[FUSB_MAX_CTRL_NUM]; /* NULL if unused */
    FUsbHc *hc; /* first hc, there might have multiple hc in pcie-mode */
    /* hook to set init function for specific device type */
    FUsbDevInitFunc dev_init[FUSB_MAX_DEV_TYPE_NUM];
    u32 dev_init_num; /* number of init function in used */
    u32 is_ready; /* indicator of system okay */
} FUsb; /* instance of the USB system */

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
static FUsbDev *FUsbGetDevEntry(FUsbHc *controller, int dev_address)
{
    FASSERT(controller && controller->devices);
    FUsbDev *result = NULL;
    u32 loop;

    for (loop = 0; loop < FUSB_MAX_DEV_NUM; loop++)
    {
        if ((NULL != controller->devices[loop]) && (dev_address == controller->devices[loop]->address))
        {
            result = controller->devices[loop];
            break;
        }
    }

    return result;
}

/*
 * returns the speed is above FUSB_SUPER_SPEED or not
 */
static inline boolean FUsbIsSuperSpeed(FUsbSpeed speed)
{
    return (speed == FUSB_SUPER_SPEED || speed == FUSB_SUPER_SPEED_PLUS);
}

static inline unsigned char FUsbGenerateReqType(FUsbReqDirection dir, FUsbReqType type, FUsbReqRecpient recp)
{
    return (dir << 7) | (type << 5) | recp;
}

/************************** Function Prototypes ******************************/
/* 获取USB的默认配置 */
const FUsbConfig *FUsbLookupConfig(u32 instance_id);

/* 初始化USB实例 */
FError FUsbCfgInitialize(FUsb *instance, const FUsbConfig *config);

/* 去初始化USB实例 */
void FUsbDeInitialize(FUsb *instance);

/* 轮询所有的USB控制器连接的所有设备, 更新设备拓扑 */
void FUsbPoll(FUsb *instance);

/* 关闭所有的USB控制器，移除所有连接的设备 */
void FUsbExit(FUsb *instance);

/* 从USB内存池分配一块内存，并清零分配的空间 */
void *FUsbMempAllocate(FUsb *instance, size_t size, size_t align);

/* 释放从USB内存池分配的空间 */
void FUsbMempFree(FUsb *instance, void *ptr);

/* 指定特定USB设备的初始化函数，供创建USB设备实例时使用 */
FError FUsbAssignDevInitFunc(FUsb *instance, const FUsbDevIndex *index, FUsbDevInitHandler handler);

/* 获取USB控制器上连接的所有USB设备实例 */
size_t FUsbGetAllDevEntries(FUsbHc *controller, FUsbDev *devs[], size_t max_dev_num);

/* 标准USB主机请求，使能设备/接口/端点的某个特性 */
FUsbTransCode FUsbSetFeature(FUsbDev *dev, int endp, int feature, int rtype);

/* 标准USB主机请求，获取设备/接口/端点的状态 */
FUsbTransCode FUsbGetStatus(FUsbDev *dev, int endp, int rtype, int len, void *data);

/* 标准USB主机请求，获取指定描述符 */
FUsbTransCode FUsbGetDescriptor(FUsbDev *dev, int rtype, FUsbDescriptorType descType, int descIdx,
                                void *data, size_t len);

/* USB主机请求，获取字符串描述符 */
FUsbTransCode FUsbGetStringDescriptor(FUsbDev *dev, int rtype, FUsbDescriptorType desc_type, int desc_idx, int lang_id,
                                      void *data, size_t len);

/* 标准USB主机请求，设置配置值 */
FUsbTransCode FUsbSetConfiguration(FUsbDev *dev);

/* 标准USB主机请求，去使能设备/接口/端点的某个特性 */
FUsbTransCode FUsbClearFeature(FUsbDev *dev, int endp, int feature, int rtype);

/* 打印描述符信息 */
void FUsbDumpAllDescriptors(FUsbDev *dev);

/* 从USB主机移除指定USB设备(USB设备驱动使用) */
void FUsbDetachDev(FUsbHc *controller, int devno);

/* 向USB主机添加USB设备(USB设备驱动使用) */
FUsbDevAddr FUsbAttachDev(FUsbHc *controller, int hubaddress, int port,
                          FUsbSpeed speed);

/**
 * To be implemented by application. It's called by the USB
 * stack just before iterating over known devices to poll them for
 * status change.
 */
void __attribute__((weak)) FUsbPollPrepare(FUsb *instance);

/**
 * To be implemented by application. It's called by the USB
 * stack just before exit known Hc.
 */
void __attribute__((weak)) FUsbExitPrepare(FUsb *instance);

/**
 * To be implemented by application. It's called by the USB stack
 * when a new USB device is found which isn't claimed by a built in driver,
 * so the client has the chance to know about it.
 *
 * @param dev descriptor for the USB device
 */
void __attribute__((weak)) FUsbGenericCreate(FUsbDev *dev);

/**
 * To be implemented by application. It's called by the USB stack
 * when it finds out that a USB device is removed which wasn't claimed by a
 * built in driver.
 *
 * @param dev descriptor for the USB device
 */
void __attribute__((weak)) FUsbGenericRemove(FUsbDev *dev);

/* 支持带TAG的内存分配，用于跟踪动态内存使用 */
#ifdef FMEMP_TAG_DEBUG
void *FUsbMempAllocateTag(FUsb *instance, size_t size, size_t align, const char *file, unsigned long line, const char *msg);
void FUsbMempFreeTag(FUsb *instance, void *ptr);

#define FUSB_ALLOCATE(instance, size, align) FUsbMempAllocateTag((instance), (size), (align), __FILE__, __LINE__, "")
#define FUSB_FREE(instance, ptr)    FUsbMempFreeTag((instance), (ptr))
#else
#define FUSB_ALLOCATE(instance, size, align) FUsbMempAllocate((instance), (size), (align))
#define FUSB_FREE(instance, ptr)    FUsbMempFree((instance), (ptr))
#endif

#ifdef __cplusplus
}
#endif


#endif
