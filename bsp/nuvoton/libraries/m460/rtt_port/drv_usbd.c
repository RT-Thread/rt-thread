/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2022-3-15       Wayne            First version
* 2023-10-11     ChuShicheng       change rt_size_t to rt_ssize_t
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_USBD)
#include <rtthread.h>
#include <rtdevice.h>
#include "NuMicro.h"
#include <nu_bitutil.h>

#define LOG_TAG         "drv.usbd"
#define DBG_ENABLE
#define DBG_SECTION_NAME "drv.usbd"
#define DBG_LEVEL DBG_ERROR
#define DBG_COLOR
#include <rtdbg.h>

/* Private define ---------------------------------------------------------------*/
/* Define EP maximum packet size */
#define EP0_MAX_PKT_SIZE    64
#define EP1_MAX_PKT_SIZE    EP0_MAX_PKT_SIZE /* EP0 and EP1 are assigned the same size for control endpoint */
#define EP2_MAX_PKT_SIZE    64
#define EP3_MAX_PKT_SIZE    64
#define EP4_MAX_PKT_SIZE    32
#define EP5_MAX_PKT_SIZE    32
#define EP6_MAX_PKT_SIZE    64
#define EP7_MAX_PKT_SIZE    64
#define EP8_MAX_PKT_SIZE    32
#define EP9_MAX_PKT_SIZE    32
#define EP10_MAX_PKT_SIZE   64
#define EP11_MAX_PKT_SIZE   64
#define EP12_MAX_PKT_SIZE   32
#define EP13_MAX_PKT_SIZE   32
#define EP14_MAX_PKT_SIZE   64
#define EP15_MAX_PKT_SIZE   64
#define EP16_MAX_PKT_SIZE   32
#define EP17_MAX_PKT_SIZE   32
#define EP18_MAX_PKT_SIZE   64
#define EP19_MAX_PKT_SIZE   64
#define EP20_MAX_PKT_SIZE   32
#define EP21_MAX_PKT_SIZE   32
#define EP22_MAX_PKT_SIZE   64
#define EP23_MAX_PKT_SIZE   64
#define EP24_MAX_PKT_SIZE   32

#define SETUP_BUF_BASE  0
#define SETUP_BUF_LEN   8

#define EPADR_SW2HW(address) ((((address & USB_EPNO_MASK) * 2) +  (!(address & USB_DIR_IN))))
#define EPADR_HW2SW(address) ((address & USB_EPNO_MASK) / 2)

/* Private typedef --------------------------------------------------------------*/
struct nu_usbd
{
    USBD_T *Instance;       /* REG base */
    uint8_t address_tmp;    /* Keep assigned address for flow control */
};
typedef struct nu_usbd *nu_usbd_t;

typedef struct
{

    uint32_t u32BufferBase;
    uint32_t u32BufferLength;

    uint32_t u32;

} S_EP_CXT;

/* Private variables ------------------------------------------------------------*/
static struct nu_usbd nu_usbd_obj =
{
    .Instance       = USBD,
    .address_tmp    = 0,
};

static struct udcd _rt_obj_udc;

static const uint32_t s_au32MaxPktSize[USBD_MAX_EP] =
{
    EP0_MAX_PKT_SIZE,  //EP0
    EP1_MAX_PKT_SIZE,  //EP1
    EP2_MAX_PKT_SIZE,  //EP2
    EP3_MAX_PKT_SIZE,  //EP3
    EP4_MAX_PKT_SIZE,  //EP4
    EP5_MAX_PKT_SIZE,  //EP5
    EP6_MAX_PKT_SIZE,  //EP6
    EP7_MAX_PKT_SIZE,  //EP7
    EP8_MAX_PKT_SIZE,  //EP8
    EP9_MAX_PKT_SIZE,  //EP9
    EP10_MAX_PKT_SIZE, //EP10
    EP11_MAX_PKT_SIZE, //EP11
    EP12_MAX_PKT_SIZE, //EP12
    EP13_MAX_PKT_SIZE, //EP13
    EP14_MAX_PKT_SIZE, //EP14
    EP15_MAX_PKT_SIZE, //EP15
    EP16_MAX_PKT_SIZE, //EP16
    EP17_MAX_PKT_SIZE, //EP17
    EP18_MAX_PKT_SIZE, //EP18
    EP19_MAX_PKT_SIZE, //EP19
    EP20_MAX_PKT_SIZE, //EP20
    EP21_MAX_PKT_SIZE, //EP21
    EP22_MAX_PKT_SIZE, //EP22
    EP23_MAX_PKT_SIZE, //EP23
    EP24_MAX_PKT_SIZE  //EP24
};

static struct ep_id _ep_pool[] =
{
    {EPADR_HW2SW(EP0),  USB_EP_ATTR_CONTROL,     USB_DIR_INOUT,  EP0_MAX_PKT_SIZE,  ID_ASSIGNED  },
    {EPADR_HW2SW(EP2),  USB_EP_ATTR_BULK,        USB_DIR_IN,     EP2_MAX_PKT_SIZE,  ID_UNASSIGNED},
    {EPADR_HW2SW(EP3),  USB_EP_ATTR_BULK,        USB_DIR_OUT,    EP3_MAX_PKT_SIZE,  ID_UNASSIGNED},
    {EPADR_HW2SW(EP4),  USB_EP_ATTR_INT,         USB_DIR_IN,     EP4_MAX_PKT_SIZE,  ID_UNASSIGNED},
    {EPADR_HW2SW(EP5),  USB_EP_ATTR_INT,         USB_DIR_OUT,    EP5_MAX_PKT_SIZE,  ID_UNASSIGNED},
    {EPADR_HW2SW(EP6),  USB_EP_ATTR_BULK,        USB_DIR_IN,     EP6_MAX_PKT_SIZE,  ID_UNASSIGNED},
    {EPADR_HW2SW(EP7),  USB_EP_ATTR_BULK,        USB_DIR_OUT,    EP7_MAX_PKT_SIZE,  ID_UNASSIGNED},
    {EPADR_HW2SW(EP8),  USB_EP_ATTR_INT,         USB_DIR_IN,     EP8_MAX_PKT_SIZE,  ID_UNASSIGNED},
    {EPADR_HW2SW(EP9),  USB_EP_ATTR_INT,         USB_DIR_OUT,    EP9_MAX_PKT_SIZE,  ID_UNASSIGNED},
    {EPADR_HW2SW(EP10), USB_EP_ATTR_BULK,        USB_DIR_IN,     EP10_MAX_PKT_SIZE, ID_UNASSIGNED},
    {EPADR_HW2SW(EP11), USB_EP_ATTR_BULK,        USB_DIR_OUT,    EP11_MAX_PKT_SIZE, ID_UNASSIGNED},
    {EPADR_HW2SW(EP12), USB_EP_ATTR_INT,         USB_DIR_IN,     EP12_MAX_PKT_SIZE, ID_UNASSIGNED},
    {EPADR_HW2SW(EP13), USB_EP_ATTR_INT,         USB_DIR_OUT,    EP13_MAX_PKT_SIZE, ID_UNASSIGNED},
    {EPADR_HW2SW(EP14), USB_EP_ATTR_BULK,        USB_DIR_IN,     EP14_MAX_PKT_SIZE, ID_UNASSIGNED},
    {EPADR_HW2SW(EP15), USB_EP_ATTR_BULK,        USB_DIR_OUT,    EP15_MAX_PKT_SIZE, ID_UNASSIGNED},
    {EPADR_HW2SW(EP16), USB_EP_ATTR_INT,         USB_DIR_IN,     EP16_MAX_PKT_SIZE, ID_UNASSIGNED},
    {EPADR_HW2SW(EP17), USB_EP_ATTR_INT,         USB_DIR_OUT,    EP17_MAX_PKT_SIZE, ID_UNASSIGNED},
    {EPADR_HW2SW(EP18), USB_EP_ATTR_BULK,        USB_DIR_IN,     EP18_MAX_PKT_SIZE, ID_UNASSIGNED},
    {EPADR_HW2SW(EP19), USB_EP_ATTR_BULK,        USB_DIR_OUT,    EP19_MAX_PKT_SIZE, ID_UNASSIGNED},
    {EPADR_HW2SW(EP20), USB_EP_ATTR_INT,         USB_DIR_IN,     EP20_MAX_PKT_SIZE, ID_UNASSIGNED},
    {EPADR_HW2SW(EP21), USB_EP_ATTR_INT,         USB_DIR_OUT,    EP21_MAX_PKT_SIZE, ID_UNASSIGNED},
    {EPADR_HW2SW(EP22), USB_EP_ATTR_BULK,        USB_DIR_IN,     EP22_MAX_PKT_SIZE, ID_UNASSIGNED},
    {EPADR_HW2SW(EP23), USB_EP_ATTR_BULK,        USB_DIR_OUT,    EP23_MAX_PKT_SIZE, ID_UNASSIGNED},
    {EPADR_HW2SW(EP24), USB_EP_ATTR_INT,         USB_DIR_IN,     EP24_MAX_PKT_SIZE, ID_UNASSIGNED},
    {0xFF,              USB_EP_ATTR_TYPE_MASK,   USB_DIR_MASK,   0,                 ID_ASSIGNED  },
};

static struct ep_id *get_ep_entry(int ep_addr)
{
    int i;
    for (i = 0; i < sizeof(_ep_pool) / sizeof(_ep_pool[0]); i++)
    {
        if (_ep_pool[i].addr == EPADR_HW2SW(ep_addr))
            return &_ep_pool[i];
    }
    return RT_NULL;
}

#define PRINT_EP_BASE(ep, base)   rt_kprintf("%d: %08x\n", ep, USBD_GET_EP_BUF_ADDR(ep));

static void _nu_ep_partition(void)
{
    int i;
    uint32_t u32EPBufBase, u32EPBufLen;

    /* Init setup packet buffer */
    /* Buffer range for setup packet -> [0 ~ 0x7] */
    USBD->STBUFSEG = SETUP_BUF_BASE;

    /*****************************************************/
    u32EPBufBase = SETUP_BUF_BASE + SETUP_BUF_LEN; //For EP0

    /* EP0 ==> control IN endpoint, address 0 */
    USBD_CONFIG_EP(EP0, USBD_CFG_CSTALL | USBD_CFG_EPMODE_IN | EPADR_HW2SW(EP0));
    /* Buffer range for EP0 */
    USBD_SET_EP_BUF_ADDR(EP0, u32EPBufBase);

    u32EPBufLen = s_au32MaxPktSize[0];   //EP0 max pkt size
    u32EPBufBase += u32EPBufLen;

    /* EP1 ==> control OUT endpoint, address 0 */
    USBD_CONFIG_EP(EP1, USBD_CFG_CSTALL | USBD_CFG_EPMODE_OUT | EPADR_HW2SW(EP1));
    /* Buffer range for EP1 */
    USBD_SET_EP_BUF_ADDR(EP1, u32EPBufBase);

    u32EPBufLen = s_au32MaxPktSize[1];   //EP1 max pkt size
    u32EPBufBase += u32EPBufLen;
    /*****************************************************/

    for (i = EP2; i < USBD_MAX_EP; i++)
    {
        uint32_t u32Config = EPADR_HW2SW(i);
        struct ep_id *psEpId;
        u32EPBufLen  = s_au32MaxPktSize[i];

        RT_ASSERT(u32EPBufBase <= 1536);

        psEpId = get_ep_entry(i);

        if (psEpId == RT_NULL)
            continue;

        switch (psEpId->dir)
        {
        case USB_DIR_IN:
            u32Config |= USBD_CFG_EPMODE_IN;
            break;
        case USB_DIR_OUT:
            u32Config |= USBD_CFG_EPMODE_OUT;
            break;

        default:
            continue;
        }

        /* Endpoint configuration */
        USBD_CONFIG_EP(i, u32Config);

        /* Buffer range for EP */
        USBD_SET_EP_BUF_ADDR(i, u32EPBufBase);

        //PRINT_EP_BASE(i, u32EPBufBase);

        u32EPBufBase += u32EPBufLen;
    }
}

static rt_err_t _ep_set_stall(rt_uint8_t address)
{
    USBD_SET_EP_STALL(EPADR_SW2HW(address));
    return RT_EOK;
}

static rt_err_t _ep_clear_stall(rt_uint8_t address)
{
    USBD_ClearStall(EPADR_SW2HW(address));

    return RT_EOK;
}


static rt_err_t _set_address(rt_uint8_t address)
{
    if (0 != address)
    {
        nu_usbd_obj.address_tmp = address;
    }

    return RT_EOK;
}

static rt_err_t _set_config(rt_uint8_t address)
{
    return RT_EOK;
}

static rt_err_t _ep_enable(uep_t ep)
{
    RT_ASSERT(ep != RT_NULL);
    RT_ASSERT(ep->ep_desc != RT_NULL);

    USBD_CONFIG_EP(EPADR_SW2HW(EP_ADDRESS(ep)),
                   USBD_CFG_CSTALL
                   | ((EP_ADDRESS(ep) & USB_DIR_IN) ? USBD_CFG_EPMODE_IN : USBD_CFG_EPMODE_OUT)
                   | (EP_ADDRESS(ep) & USB_EPNO_MASK));

    return RT_EOK;
}

static rt_err_t _ep_disable(uep_t ep)
{
    RT_ASSERT(ep != RT_NULL);
    RT_ASSERT(ep->ep_desc != RT_NULL);

    USBD_CONFIG_EP(EPADR_SW2HW(EP_ADDRESS(ep)),  USBD_CFG_EPMODE_DISABLE);

    return RT_EOK;
}

static rt_ssize_t _ep_read(rt_uint8_t address, void *buffer)
{
    rt_size_t size = 0;
    rt_uint8_t *buf;
    rt_uint32_t hw_ep_num = EPADR_SW2HW(address);

    RT_ASSERT(!(address & USB_DIR_IN));
    RT_ASSERT(buffer != RT_NULL);

    size = USBD_GET_PAYLOAD_LEN(hw_ep_num);
    buf = (uint8_t *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(hw_ep_num));
    USBD_MemCopy(buffer, (uint8_t *)buf, size);

    return size;
}

static rt_ssize_t _ep_read_prepare(rt_uint8_t address, void *buffer, rt_size_t size)
{
    RT_ASSERT(!(address & USB_DIR_IN));

    USBD_SET_PAYLOAD_LEN(EPADR_SW2HW(address), size);

    return size;
}

static rt_ssize_t _ep_write(rt_uint8_t address, void *buffer, rt_size_t size)
{
    RT_ASSERT((address & USB_DIR_IN));

    /* even number is for IN endpoint */
    rt_uint32_t hw_ep_num = EPADR_SW2HW(address);
    uint8_t *buf;
    buf = (uint8_t *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(hw_ep_num));

    USBD_MemCopy(buf, (uint8_t *)buffer, size);

    USBD_SET_PAYLOAD_LEN(hw_ep_num, size);

    return size;
}

static rt_err_t _ep0_send_status(void)
{
    /* Status stage */
    USBD_SET_DATA1(EP0);
    USBD_SET_PAYLOAD_LEN(EP0, 0);
    return RT_EOK;
}

static rt_err_t _suspend(void)
{
    return RT_EOK;
}

static rt_err_t _wakeup(void)
{
    return RT_EOK;
}

__STATIC_INLINE void _USBD_IRQHandler(void)
{
    rt_uint32_t u32IntSts   = USBD_GET_INT_FLAG();
    rt_uint32_t u32State    = USBD_GET_BUS_STATE();

//------------------------------------------------------------------
    if (u32IntSts & USBD_INTSTS_VBDETIF_Msk)
    {
        // Floating detect
        USBD_CLR_INT_FLAG(USBD_INTSTS_VBDETIF_Msk);

        if (USBD_IS_ATTACHED())
        {
            /* USB Plug In */
            USBD_ENABLE_USB();
            rt_usbd_connect_handler(&_rt_obj_udc);
        }
        else
        {
            /* USB Unplug */
            USBD_DISABLE_USB();
            rt_usbd_disconnect_handler(&_rt_obj_udc);
        }
    }

    if (u32IntSts & USBD_INTSTS_SOFIF_Msk)
    {
        USBD_CLR_INT_FLAG(USBD_INTSTS_SOFIF_Msk);
        rt_usbd_sof_handler(&_rt_obj_udc);
    }
//------------------------------------------------------------------
    if (u32IntSts & USBD_INTSTS_BUSIF_Msk)
    {
        /* Clear event flag */
        USBD_CLR_INT_FLAG(USBD_INTSTS_BUSIF_Msk);

        if (u32State & USBD_ATTR_USBRST_Msk)
        {
            USBD_ENABLE_USB();

            /* Reset PID DATA0 */
            for (rt_uint32_t i = 0ul; i < USBD_MAX_EP; i++)
            {
                nu_usbd_obj.Instance->EP[i].CFG &= ~USBD_CFG_DSQSYNC_Msk;
            }

            /* Reset USB device address */
            USBD_SET_ADDR(0ul);

            /* Bus reset */
            rt_usbd_reset_handler(&_rt_obj_udc);
        }
        if (u32State & USBD_ATTR_SUSPEND_Msk)
        {
            /* Enable USB but disable PHY */
            USBD_DISABLE_PHY();
        }
        if (u32State & USBD_ATTR_RESUME_Msk)
        {
            /* Enable USB and enable PHY */
            USBD_ENABLE_USB();
        }
    }

//------------------------------------------------------------------
    if (u32IntSts & USBD_INTSTS_WAKEUP)
    {
        /* Clear event flag */
        USBD_CLR_INT_FLAG(USBD_INTSTS_WAKEUP);
        USBD_ENABLE_USB();
    }

    if (u32IntSts & USBD_INTSTS_USBIF_Msk)
    {
        // USB event
        if (u32IntSts & USBD_INTSTS_SETUP_Msk)
        {
            // Setup packet
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_SETUP_Msk);

            /* Clear the data IN/OUT ready flag of control end-points */
            USBD_STOP_TRANSACTION(EP0);
            USBD_STOP_TRANSACTION(EP1);

            USBD_SET_DATA1(EP0);
            rt_usbd_ep0_setup_handler(&_rt_obj_udc, (struct urequest *)USBD_BUF_BASE);
        }

        /* Service EP events */
        rt_uint32_t u32EpIntSts   = USBD_GET_EP_INT_FLAG();

        // EP events
        if (u32EpIntSts & USBD_EPINTSTS_EPEVT0_Msk)
        {
            /* Clear event flag */
            USBD_CLR_EP_INT_FLAG(USBD_EPINTSTS_EPEVT0_Msk);

            if ((USBD_GET_ADDR() == 0)
                    && (nu_usbd_obj.address_tmp)
               )
            {
                USBD_SET_ADDR(nu_usbd_obj.address_tmp);
                LOG_I("SET ADDR: 0x%02x", nu_usbd.address_tmp);
                nu_usbd_obj.address_tmp = 0;
            }

            rt_usbd_ep0_in_handler(&_rt_obj_udc);
        }

        if (u32EpIntSts & USBD_EPINTSTS_EPEVT1_Msk)
        {
            /* Clear event flag */
            USBD_CLR_EP_INT_FLAG(USBD_EPINTSTS_EPEVT1_Msk);
            rt_usbd_ep0_out_handler(&_rt_obj_udc, 0);
        }

        /* For EP2 ~ EP24 */
        {
            rt_int32_t u32EpIrqIdx;
            rt_int32_t u32EpIrqStatus = u32EpIntSts & (~((1 << EP2) - 1)); // Skip EP0/EP1 traveling.

            // Find index of pin is attached in pool.
            while ((u32EpIrqIdx = nu_ctz(u32EpIrqStatus)) < USBD_MAX_EP) // Count Trailing Zeros ==> Find First One
            {
                /* Clear event flag */
                USBD_CLR_EP_INT_FLAG(1 << u32EpIrqIdx);

                /* Report upper layer. */
                rt_usbd_ep_in_handler(&_rt_obj_udc, _ep_pool[u32EpIrqIdx - 1].dir | EPADR_HW2SW(u32EpIrqIdx), 0);
                u32EpIrqStatus &= ~(1 << u32EpIrqIdx);
            }
        }
    }
}

void USBD_IRQHandler(void)
{
    rt_interrupt_enter();

    _USBD_IRQHandler();

    rt_interrupt_leave();
}

static rt_err_t _init(rt_device_t device)
{
    nu_usbd_t nu_usbd = (nu_usbd_t)device->user_data;

    uint32_t u32RegLockBackup = SYS_IsRegLocked();

    /* Initialize USB PHY */
    SYS_UnlockReg();
    /* Select USBD */
    SYS->USBPHY = (SYS->USBPHY & ~SYS_USBPHY_USBROLE_Msk) | SYS_USBPHY_USBEN_Msk | SYS_USBPHY_SBO_Msk;
    SYS_ResetModule(USBD_RST);

    if (u32RegLockBackup)
        SYS_LockReg();

    _nu_ep_partition();

    /* Initial USB engine */
    /*
      BYTEM=1:  Byte mode: The size of the transfer from CPU to USB SRAM can be Byte only.
      PWRDN=1:  Turn-on related circuit of PHY transceiver.
    DPPUEN=1: Pull-up resistor in USB_D+ bus Active.
    */
    nu_usbd->Instance->ATTR = 0x7D0ul;

    /* Force SE0 */
    USBD_SET_SE0();

    NVIC_EnableIRQ(USBD_IRQn);

    USBD_Start();

    return RT_EOK;
}

const static struct udcd_ops _udc_ops =
{
    _set_address,
    _set_config,
    _ep_set_stall,
    _ep_clear_stall,
    _ep_enable,
    _ep_disable,
    _ep_read_prepare,
    _ep_read,
    _ep_write,
    _ep0_send_status,
    _suspend,
    _wakeup,
};

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops _ops =
{
    _init,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
};
#endif

int nu_usbd_register(void)
{
    if (RT_NULL != rt_device_find("usbd"))
    {
        LOG_E("\nUSBD Register failed. Another USBD device registered\n");
        return -RT_ERROR;
    }

    rt_memset((void *)&_rt_obj_udc, 0, sizeof(struct udcd));
    _rt_obj_udc.parent.type = RT_Device_Class_USBDevice;

#ifdef RT_USING_DEVICE_OPS
    _rt_obj_udc.parent.ops = &_ops;
#else
    _rt_obj_udc.parent.init = _init;
#endif

    _rt_obj_udc.parent.user_data = &nu_usbd_obj;
    _rt_obj_udc.ops = &_udc_ops;

    /* Register endpoint information */
    _rt_obj_udc.ep_pool = _ep_pool;
    _rt_obj_udc.ep0.id = &_ep_pool[0];

    _rt_obj_udc.device_is_hs = RT_FALSE; /* Support Full-Speed only */

    rt_device_register((rt_device_t)&_rt_obj_udc, "usbd", 0);

    return rt_usb_device_init();
}
INIT_DEVICE_EXPORT(nu_usbd_register);
#endif
