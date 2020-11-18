/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-3-25       Egbert           First version
*
******************************************************************************/

#include <rtconfig.h>

#ifdef BSP_USING_USBD
#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>
#include "NuMicro.h"

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
#define EP4_MAX_PKT_SIZE    64
#define EP5_MAX_PKT_SIZE    64
#define EP6_MAX_PKT_SIZE    64
#define EP7_MAX_PKT_SIZE    64
#define EP8_MAX_PKT_SIZE    64
#define EP9_MAX_PKT_SIZE    64

#define SETUP_BUF_BASE  0
#define SETUP_BUF_LEN   8
#define EP0_BUF_BASE    (SETUP_BUF_BASE + SETUP_BUF_LEN)
#define EP0_BUF_LEN     EP0_MAX_PKT_SIZE

#define EP1_BUF_BASE    (SETUP_BUF_BASE + SETUP_BUF_LEN)
#define EP1_BUF_LEN     EP1_MAX_PKT_SIZE
#define EP2_BUF_BASE    (EP1_BUF_BASE + EP1_BUF_LEN)
#define EP2_BUF_LEN     EP2_MAX_PKT_SIZE
#define EP3_BUF_BASE    (EP2_BUF_BASE + EP2_BUF_LEN)
#define EP3_BUF_LEN     EP3_MAX_PKT_SIZE
#define EP4_BUF_BASE    (EP3_BUF_BASE + EP3_BUF_LEN)
#define EP4_BUF_LEN     EP4_MAX_PKT_SIZE
#define EP5_BUF_BASE    (EP4_BUF_BASE + EP4_BUF_LEN)
#define EP5_BUF_LEN     EP5_MAX_PKT_SIZE
#define EP6_BUF_BASE    (EP5_BUF_BASE + EP5_BUF_LEN)
#define EP6_BUF_LEN     EP6_MAX_PKT_SIZE
#define EP7_BUF_BASE    (EP6_BUF_BASE + EP6_BUF_LEN)
#define EP7_BUF_LEN     EP7_MAX_PKT_SIZE
#define EP8_BUF_BASE    (EP7_BUF_BASE + EP7_BUF_LEN)
#define EP8_BUF_LEN     EP8_MAX_PKT_SIZE
#define EP9_BUF_BASE    (EP8_BUF_BASE + EP8_BUF_LEN)
#define EP9_BUF_LEN     EP9_MAX_PKT_SIZE

#define EPADR_SW2HW(address) ((((address & USB_EPNO_MASK) * 2) +  (!(address & USB_DIR_IN))))
#define EPADR_HW2SW(address) ((address & USB_EPNO_MASK) / 2)
/* Private typedef --------------------------------------------------------------*/
typedef struct _nu_usbd_t
{
    USBD_T *Instance;       /* REG base */
    uint8_t address_tmp;    /* Keep assigned address for flow control */
} nu_usbd_t;


/* Private variables ------------------------------------------------------------*/
static nu_usbd_t nu_usbd =
{
    .Instance       = USBD,
    .address_tmp    = 0,
};

static struct udcd _rt_obj_udc;

static struct ep_id _ep_pool[] =
{
    {EPADR_HW2SW(EP0),  USB_EP_ATTR_CONTROL,     USB_DIR_INOUT,  EP0_MAX_PKT_SIZE, ID_ASSIGNED  },
    {EPADR_HW2SW(EP2),  USB_EP_ATTR_BULK,        USB_DIR_IN,     EP2_MAX_PKT_SIZE, ID_UNASSIGNED},
    {EPADR_HW2SW(EP3),  USB_EP_ATTR_BULK,        USB_DIR_OUT,    EP3_MAX_PKT_SIZE, ID_UNASSIGNED},
    {EPADR_HW2SW(EP4),  USB_EP_ATTR_INT,         USB_DIR_IN,     EP4_MAX_PKT_SIZE, ID_UNASSIGNED},
    {EPADR_HW2SW(EP5),  USB_EP_ATTR_INT,         USB_DIR_OUT,    EP5_MAX_PKT_SIZE, ID_UNASSIGNED},
    {EPADR_HW2SW(EP6),  USB_EP_ATTR_BULK,        USB_DIR_IN,     EP6_MAX_PKT_SIZE, ID_UNASSIGNED},
    {EPADR_HW2SW(EP7),  USB_EP_ATTR_BULK,        USB_DIR_OUT,    EP7_MAX_PKT_SIZE, ID_UNASSIGNED},
    {EPADR_HW2SW(EP8),  USB_EP_ATTR_INT,         USB_DIR_IN,     EP8_MAX_PKT_SIZE, ID_UNASSIGNED},
    {EPADR_HW2SW(EP9),  USB_EP_ATTR_INT,         USB_DIR_OUT,    EP9_MAX_PKT_SIZE, ID_UNASSIGNED},
    {0xFF,              USB_EP_ATTR_TYPE_MASK,   USB_DIR_MASK,   0,                ID_ASSIGNED  },
};

static void _nu_ep_partition(void)
{
    /* Init setup packet buffer */
    /* Buffer range for setup packet -> [0 ~ 0x7] */
    USBD->STBUFSEG = SETUP_BUF_BASE;

    /*****************************************************/
    /* EP0 ==> control IN endpoint, address 0 */
    USBD_CONFIG_EP(EP0, USBD_CFG_CSTALL | USBD_CFG_EPMODE_IN | EPADR_HW2SW(EP0));
    /* Buffer range for EP0 */
    USBD_SET_EP_BUF_ADDR(EP0, EP0_BUF_BASE);

    /* EP1 ==> control OUT endpoint, address 0 */
    USBD_CONFIG_EP(EP1, USBD_CFG_CSTALL | USBD_CFG_EPMODE_OUT | EPADR_HW2SW(EP1));
    /* Buffer range for EP1 */
    USBD_SET_EP_BUF_ADDR(EP1, EP1_BUF_BASE);

    /*****************************************************/
    /* EP2 ==> Bulk IN endpoint, address 1 */
    USBD_CONFIG_EP(EP2, USBD_CFG_EPMODE_IN | EPADR_HW2SW(EP2));
    /* Buffer range for EP2 */
    USBD_SET_EP_BUF_ADDR(EP2, EP2_BUF_BASE);

    /* EP3 ==> Bulk OUT endpoint, address 1 */
    USBD_CONFIG_EP(EP3, USBD_CFG_EPMODE_OUT | EPADR_HW2SW(EP3));
    /* Buffer range for EP3 */
    USBD_SET_EP_BUF_ADDR(EP3, EP3_BUF_BASE);

    /*****************************************************/
    /* EP4 ==> Interrupt IN endpoint, address 2 */
    USBD_CONFIG_EP(EP4, USBD_CFG_EPMODE_IN | EPADR_HW2SW(EP4));
    /* Buffer range for EP4 */
    USBD_SET_EP_BUF_ADDR(EP4, EP4_BUF_BASE);

    /* EP5 ==> Interrupt Out endpoint, address 2 */
    USBD_CONFIG_EP(EP5, USBD_CFG_EPMODE_OUT | EPADR_HW2SW(EP5));
    /* Buffer range for EP5 */
    USBD_SET_EP_BUF_ADDR(EP5, EP5_BUF_BASE);

    /*****************************************************/
    /* EP6 ==> Bulk IN endpoint, address 3 */
    USBD_CONFIG_EP(EP6, USBD_CFG_EPMODE_IN | EPADR_HW2SW(EP6));
    /* Buffer range for EP4 */
    USBD_SET_EP_BUF_ADDR(EP6, EP6_BUF_BASE);

    /* EP7 ==> Bulk Out endpoint, address 3 */
    USBD_CONFIG_EP(EP7, USBD_CFG_EPMODE_OUT | EPADR_HW2SW(EP7));
    /* Buffer range for EP5 */
    USBD_SET_EP_BUF_ADDR(EP7, EP7_BUF_BASE);

    /*****************************************************/
    /* EP8 ==> Interrupt IN endpoint, address 4 */
    USBD_CONFIG_EP(EP8, USBD_CFG_EPMODE_IN | EPADR_HW2SW(EP8));
    /* Buffer range for EP4 */
    USBD_SET_EP_BUF_ADDR(EP8, EP8_BUF_BASE);

    /* EP9 ==> Interrupt Out endpoint, address 4 */
    USBD_CONFIG_EP(EP9, USBD_CFG_EPMODE_OUT | EPADR_HW2SW(EP9));
    /* Buffer range for EP9 */
    USBD_SET_EP_BUF_ADDR(EP9, EP9_BUF_BASE);

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
        nu_usbd.address_tmp = address;
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

static rt_size_t _ep_read(rt_uint8_t address, void *buffer)
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

static rt_size_t _ep_read_prepare(rt_uint8_t address, void *buffer, rt_size_t size)
{
    RT_ASSERT(!(address & USB_DIR_IN));

    USBD_SET_PAYLOAD_LEN(EPADR_SW2HW(address), size);

    return size;
}

static rt_size_t _ep_write(rt_uint8_t address, void *buffer, rt_size_t size)
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
            /* USB Un-plug */
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
                nu_usbd.Instance->EP[i].CFG &= ~USBD_CFG_DSQSYNC_Msk;
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

        // EP events
        if (u32IntSts & USBD_INTSTS_EP0)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP0);

            if (       (USBD_GET_ADDR() == 0)
                    && (nu_usbd.address_tmp)
               )
            {
                USBD_SET_ADDR(nu_usbd.address_tmp);
                LOG_I("SET ADDR: 0x%02x", nu_usbd.address_tmp);
                nu_usbd.address_tmp = 0;
            }

            rt_usbd_ep0_in_handler(&_rt_obj_udc);
        }

        if (u32IntSts & USBD_INTSTS_EP1)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP1);
            rt_usbd_ep0_out_handler(&_rt_obj_udc, 0);
        }

        if (u32IntSts & USBD_INTSTS_EP2)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP2);
            rt_usbd_ep_in_handler(&_rt_obj_udc, USB_DIR_IN | EPADR_HW2SW(EP2), 0);
        }

        if (u32IntSts & USBD_INTSTS_EP3)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP3);
            rt_usbd_ep_out_handler(&_rt_obj_udc, USB_DIR_OUT | EPADR_HW2SW(EP3), 0);
        }

        if (u32IntSts & USBD_INTSTS_EP4)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP4);
            rt_usbd_ep_in_handler(&_rt_obj_udc, USB_DIR_IN | EPADR_HW2SW(EP4), 0);
        }

        if (u32IntSts & USBD_INTSTS_EP5)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP5);
            rt_usbd_ep_out_handler(&_rt_obj_udc, USB_DIR_OUT | EPADR_HW2SW(EP5), 0);
        }

        if (u32IntSts & USBD_INTSTS_EP6)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP6);
            rt_usbd_ep_in_handler(&_rt_obj_udc, USB_DIR_IN | EPADR_HW2SW(EP6), 0);
        }

        if (u32IntSts & USBD_INTSTS_EP7)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP7);
            rt_usbd_ep_out_handler(&_rt_obj_udc, USB_DIR_OUT | EPADR_HW2SW(EP7), 0);
        }

        if (u32IntSts & USBD_INTSTS_EP8)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP8);
            rt_usbd_ep_in_handler(&_rt_obj_udc, USB_DIR_IN | EPADR_HW2SW(EP8), 0);
        }

        if (u32IntSts & USBD_INTSTS_EP9)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP9);
            rt_usbd_ep_out_handler(&_rt_obj_udc, USB_DIR_OUT | EPADR_HW2SW(EP9), 0);
        }
    }
}

void USBD_IRQHandler(void)
{
    rt_interrupt_enter();

    _USBD_IRQHandler();

    /* leave interrupt */
    rt_interrupt_leave();
}

static rt_err_t _init(rt_device_t device)
{
    nu_usbd_t *nu_usbd = (nu_usbd_t *)device->user_data;

    /* Initialize USB PHY */
    SYS_UnlockReg();
    /* Select USBD */
    SYS->USBPHY = (SYS->USBPHY & ~SYS_USBPHY_USBROLE_Msk) | SYS_USBPHY_USBEN_Msk | SYS_USBPHY_SBO_Msk;
    SYS_ResetModule(USBD_RST);
    SYS_LockReg();

    _nu_ep_partition();

    /* Initial USB engine */
    nu_usbd->Instance->ATTR = 0x6D0ul;

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

    _rt_obj_udc.parent.user_data = &nu_usbd;
    _rt_obj_udc.ops = &_udc_ops;
    /* Register endpoint infomation */
    _rt_obj_udc.ep_pool = _ep_pool;
    _rt_obj_udc.ep0.id = &_ep_pool[0];

    _rt_obj_udc.device_is_hs = RT_FALSE; /* Support Full-Speed only */

    rt_device_register((rt_device_t)&_rt_obj_udc, "usbd", 0);
    rt_usb_device_init();
    return RT_EOK;
}
INIT_DEVICE_EXPORT(nu_usbd_register);
#endif
