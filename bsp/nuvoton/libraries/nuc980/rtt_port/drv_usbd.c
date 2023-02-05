/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-12-25      Wayne            First version
*
******************************************************************************/


#include <rtconfig.h>

#if defined(BSP_USING_USBD)

#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>
#include "NuMicro.h"
#include <nu_bitutil.h>
#include "drv_sys.h"

#define LOG_TAG         "drv.usbd"
//#define DBG_ENABLE
#define DBG_SECTION_NAME "drv.usbd"
//#define DBG_LEVEL   DBG_ERROR
#define DBG_COLOR
#include <rtdbg.h>

/* Private define ---------------------------------------------------------------*/
#define ENABLE_FULL_SPEED_MODE_ONLY 0 /* 0: default hi-speed mode; 1: full-speed mode only */

/* Define EP maximum packet size */

#define CEP_MAX_PKT_SIZE        64
#define CEP_OTHER_MAX_PKT_SIZE  64

#define EPA_MAX_PKT_SIZE        512
#define EPA_OTHER_MAX_PKT_SIZE  64

#define EPB_MAX_PKT_SIZE        512
#define EPB_OTHER_MAX_PKT_SIZE  64

#define EPC_MAX_PKT_SIZE        64
#define EPC_OTHER_MAX_PKT_SIZE  64

#define EPD_MAX_PKT_SIZE        64
#define EPD_OTHER_MAX_PKT_SIZE  64

#define EPE_MAX_PKT_SIZE        512
#define EPE_OTHER_MAX_PKT_SIZE  64

#define EPF_MAX_PKT_SIZE        512
#define EPF_OTHER_MAX_PKT_SIZE  64

#define EPG_MAX_PKT_SIZE        64
#define EPG_OTHER_MAX_PKT_SIZE  64

#define EPH_MAX_PKT_SIZE        64
#define EPH_OTHER_MAX_PKT_SIZE  64

#define EPI_MAX_PKT_SIZE        512
#define EPI_OTHER_MAX_PKT_SIZE  64

#define EPJ_MAX_PKT_SIZE        512
#define EPJ_OTHER_MAX_PKT_SIZE  64

#define EPK_MAX_PKT_SIZE        64
#define EPK_OTHER_MAX_PKT_SIZE  64

#define EPL_MAX_PKT_SIZE        64
#define EPL_OTHER_MAX_PKT_SIZE  64

#define CEP_BUF_BASE    0
#define CEP_BUF_LEN     CEP_MAX_PKT_SIZE

#define EPA_BUF_BASE    (CEP_BUF_BASE + CEP_BUF_LEN)
#define EPA_BUF_LEN     EPA_MAX_PKT_SIZE

#define EPB_BUF_BASE    (EPA_BUF_BASE + EPA_BUF_LEN)
#define EPB_BUF_LEN     EPB_MAX_PKT_SIZE

#define EPC_BUF_BASE    (EPB_BUF_BASE + EPB_BUF_LEN)
#define EPC_BUF_LEN     EPC_MAX_PKT_SIZE

#define EPD_BUF_BASE    (EPC_BUF_BASE + EPC_BUF_LEN)
#define EPD_BUF_LEN     EPD_MAX_PKT_SIZE

#define EPE_BUF_BASE    (EPD_BUF_BASE + EPD_BUF_LEN)
#define EPE_BUF_LEN     EPE_MAX_PKT_SIZE

#define EPF_BUF_BASE    (EPE_BUF_BASE + EPE_BUF_LEN)
#define EPF_BUF_LEN     EPF_MAX_PKT_SIZE

#define EPG_BUF_BASE    (EPF_BUF_BASE + EPF_BUF_LEN)
#define EPG_BUF_LEN     EPG_MAX_PKT_SIZE

#define EPH_BUF_BASE    (EPG_BUF_BASE + EPG_BUF_LEN)
#define EPH_BUF_LEN     EPH_MAX_PKT_SIZE

#define EPI_BUF_BASE    (EPH_BUF_BASE + EPH_BUF_LEN)
#define EPI_BUF_LEN     EPI_MAX_PKT_SIZE

#define EPJ_BUF_BASE    (EPI_BUF_BASE + EPI_BUF_LEN)
#define EPJ_BUF_LEN     EPJ_MAX_PKT_SIZE

#define EPK_BUF_BASE    (EPJ_BUF_BASE + EPJ_BUF_LEN)
#define EPK_BUF_LEN     EPK_MAX_PKT_SIZE

#define EPL_BUF_BASE    (EPK_BUF_BASE + EPK_BUF_LEN)
#define EPL_BUF_LEN     EPL_MAX_PKT_SIZE


#define EPADR_SW2HW(address) ((address & USB_EPNO_MASK) - 1) /* for non-control endpoint */
#define EPADR_HW2SW(address) ((address & USB_EPNO_MASK) + 1) /* for non-control endpoint */

/* Private typedef --------------------------------------------------------------*/
typedef struct _nu_usbd_t
{
    USBD_T *base;     /* REG base */
    char *name;
    IRQn_Type irqn;
    E_SYS_IPRST rstidx;
    E_SYS_IPCLK clkidx;
    uint8_t address_tmp;      /* Keep assigned address for flow control */
    uint8_t plugging_status;  /* For debounce, 0: Unplug, 1: plug-in */
} nu_usbd_t;


typedef struct
{

    uint32_t u32BufferBase;
    uint32_t u32BufferLength;

    uint32_t u32OtherMaxPktSize;

} S_EP_CXT;


/* Private variables ------------------------------------------------------------*/

static nu_usbd_t nu_usbd =
{
    .base        = USBD,
    .name        = "usbd",
    .irqn        = IRQ_UDC,
    .rstidx      = USBDRST,
    .clkidx      = USBDCKEN,
    .address_tmp = 0,
    .plugging_status = 0,
};

static struct udcd _rt_obj_udc;

static S_EP_CXT _ep_cxt_pool[] =
{
    { EPA_BUF_BASE, EPA_BUF_LEN, EPA_OTHER_MAX_PKT_SIZE}, //EPA
    { EPB_BUF_BASE, EPB_BUF_LEN, EPB_OTHER_MAX_PKT_SIZE}, //EPB
    { EPC_BUF_BASE, EPC_BUF_LEN, EPC_OTHER_MAX_PKT_SIZE}, //EPC
    { EPD_BUF_BASE, EPD_BUF_LEN, EPD_OTHER_MAX_PKT_SIZE}, //EPD
    { EPE_BUF_BASE, EPE_BUF_LEN, EPE_OTHER_MAX_PKT_SIZE}, //EPE
    { EPF_BUF_BASE, EPF_BUF_LEN, EPF_OTHER_MAX_PKT_SIZE}, //EPF
    { EPG_BUF_BASE, EPG_BUF_LEN, EPG_OTHER_MAX_PKT_SIZE}, //EPG
    { EPH_BUF_BASE, EPH_BUF_LEN, EPH_OTHER_MAX_PKT_SIZE}, //EPH
    { EPI_BUF_BASE, EPI_BUF_LEN, EPI_OTHER_MAX_PKT_SIZE}, //EPI
    { EPJ_BUF_BASE, EPJ_BUF_LEN, EPJ_OTHER_MAX_PKT_SIZE}, //EPJ
    { EPK_BUF_BASE, EPK_BUF_LEN, EPK_OTHER_MAX_PKT_SIZE}, //EPK
    { EPL_BUF_BASE, EPL_BUF_LEN, EPL_OTHER_MAX_PKT_SIZE}  //EPL
};

static struct ep_id _ep_pool[] =
{
    {0x0,               USB_EP_ATTR_CONTROL,     USB_DIR_INOUT, CEP_MAX_PKT_SIZE,    ID_ASSIGNED  },

    {EPADR_HW2SW(EPA),  USB_EP_ATTR_BULK,        USB_DIR_IN,    EPA_MAX_PKT_SIZE,    ID_UNASSIGNED},
    {EPADR_HW2SW(EPB),  USB_EP_ATTR_BULK,        USB_DIR_OUT,   EPB_MAX_PKT_SIZE,    ID_UNASSIGNED},
    {EPADR_HW2SW(EPC),  USB_EP_ATTR_INT,         USB_DIR_IN,    EPC_MAX_PKT_SIZE,    ID_UNASSIGNED},
    {EPADR_HW2SW(EPD),  USB_EP_ATTR_INT,         USB_DIR_OUT,   EPD_MAX_PKT_SIZE,    ID_UNASSIGNED},
    {EPADR_HW2SW(EPE),  USB_EP_ATTR_BULK,        USB_DIR_IN,    EPE_MAX_PKT_SIZE,    ID_UNASSIGNED},
    {EPADR_HW2SW(EPF),  USB_EP_ATTR_BULK,        USB_DIR_OUT,   EPF_MAX_PKT_SIZE,    ID_UNASSIGNED},
    {EPADR_HW2SW(EPG),  USB_EP_ATTR_INT,         USB_DIR_IN,    EPG_MAX_PKT_SIZE,    ID_UNASSIGNED},
    {EPADR_HW2SW(EPH),  USB_EP_ATTR_INT,         USB_DIR_OUT,   EPH_MAX_PKT_SIZE,    ID_UNASSIGNED},
    {EPADR_HW2SW(EPI),  USB_EP_ATTR_BULK,        USB_DIR_IN,    EPE_MAX_PKT_SIZE,    ID_UNASSIGNED},
    {EPADR_HW2SW(EPJ),  USB_EP_ATTR_BULK,        USB_DIR_OUT,   EPF_MAX_PKT_SIZE,    ID_UNASSIGNED},
    {EPADR_HW2SW(EPK),  USB_EP_ATTR_INT,         USB_DIR_IN,    EPG_MAX_PKT_SIZE,    ID_UNASSIGNED},
    {EPADR_HW2SW(EPL),  USB_EP_ATTR_INT,         USB_DIR_OUT,   EPH_MAX_PKT_SIZE,    ID_UNASSIGNED},

    {0xFF,              USB_EP_ATTR_TYPE_MASK,   USB_DIR_MASK,  0,                   ID_ASSIGNED  },
};


static void _nu_ep_partition_set(int isHighSpeed)
{
    int i;

    for (i = 0; i < USBD_MAX_EP; i++)
    {
        uint32_t u32NuEPTypeDef = 0x0;
        uint32_t u32NuEPDirDef = 0x0;

        if (_ep_pool[i + 1].type == USB_EP_ATTR_BULK)
            u32NuEPTypeDef =  USB_EP_CFG_TYPE_BULK;
        else if (_ep_pool[i + 1].type == USB_EP_ATTR_INT)
            u32NuEPTypeDef =  USB_EP_CFG_TYPE_INT;
        else
            continue;

        if (_ep_pool[i + 1].dir == USB_DIR_IN)
            u32NuEPDirDef =  USB_EP_CFG_DIR_IN;
        else if (_ep_pool[i + 1].dir == USB_DIR_OUT)
            u32NuEPDirDef =  USB_EP_CFG_DIR_OUT;
        else
            continue;

        USBD_SetEpBufAddr(i, _ep_cxt_pool[i].u32BufferBase, _ep_cxt_pool[i].u32BufferLength);
        if (isHighSpeed)
            USBD_SET_MAX_PAYLOAD(i, _ep_cxt_pool[i].u32BufferLength);
        else
            USBD_SET_MAX_PAYLOAD(i, _ep_cxt_pool[i].u32OtherMaxPktSize);

        USBD_ConfigEp(i, EPADR_HW2SW(i), u32NuEPTypeDef, u32NuEPDirDef);

        if (u32NuEPDirDef ==  USB_EP_CFG_DIR_OUT)
            USBD_ENABLE_EP_INT(i, USBD_EPINTEN_RXPKIEN_Msk);

    } //for

}

static void _nu_ep_partition(void)
{
    /* Configure USB controller */
    /* Enable USB BUS, CEP and EPA ~ EPH global interrupt */
    USBD_ENABLE_USB_INT(USBD_GINTEN_USBIE_Msk
                        | USBD_GINTEN_CEPIE_Msk
                        | USBD_GINTEN_EPAIE_Msk
                        | USBD_GINTEN_EPBIE_Msk
                        | USBD_GINTEN_EPCIE_Msk
                        | USBD_GINTEN_EPDIE_Msk
                        | USBD_GINTEN_EPEIE_Msk
                        | USBD_GINTEN_EPFIE_Msk
                        | USBD_GINTEN_EPGIE_Msk
                        | USBD_GINTEN_EPHIE_Msk
                        | USBD_GINTEN_EPIIE_Msk
                        | USBD_GINTEN_EPJIE_Msk
                        | USBD_GINTEN_EPKIE_Msk
                        | USBD_GINTEN_EPLIE_Msk);

    /* Enable BUS interrupt */
    USBD_ENABLE_BUS_INT(USBD_BUSINTEN_DMADONEIEN_Msk
                        | USBD_BUSINTEN_RESUMEIEN_Msk
                        | USBD_BUSINTEN_RSTIEN_Msk
                        | USBD_BUSINTEN_VBUSDETIEN_Msk);
    /* Reset Address to 0 */
    USBD_SET_ADDR(0);

    /*****************************************************/
    /* Control endpoint */
    USBD_SetEpBufAddr(CEP, CEP_BUF_BASE, CEP_BUF_LEN);
    USBD_ENABLE_CEP_INT(USBD_CEPINTEN_SETUPPKIEN_Msk
                        | USBD_CEPINTEN_STSDONEIEN_Msk);

    _nu_ep_partition_set(1);
}

static void NU_SetupStageCallback(nu_usbd_t *nu_udc)
{
    struct urequest setup_packet;

    /* Setup packet process */
    setup_packet.request_type   = (uint8_t)(nu_udc->base->SETUP1_0 & 0xfful);
    setup_packet.bRequest       = (uint8_t)((nu_udc->base->SETUP1_0 >> 8) & 0xfful);
    setup_packet.wValue         = (uint16_t)  nu_udc->base->SETUP3_2;
    setup_packet.wIndex         = (uint16_t)  nu_udc->base->SETUP5_4;
    setup_packet.wLength        = (uint16_t)  nu_udc->base->SETUP7_6;

    rt_usbd_ep0_setup_handler(&_rt_obj_udc, (struct urequest *)&setup_packet);
}

__STATIC_INLINE void nu_udc_enable(void)
{
    USBD_ENABLE_USB();
}

__STATIC_INLINE void nu_udc_disable(void)
{
    int i;

    USBD_ENABLE_CEP_INT(0);
    USBD_CLR_CEP_INT_FLAG(0xffff);

    USBD_SET_CEP_STATE(inpw(REG_USBD_CEPCTL)  | USB_CEPCTL_FLUSH);

    for (i = 0; i < USBD_MAX_EP; i++)
        USBD->EP[i].EPRSPCTL = USB_EP_RSPCTL_FLUSH | USB_EP_RSPCTL_TOGGLE;

    USBD_DISABLE_USB();
}


static rt_err_t _ep_set_stall(rt_uint8_t address)
{

    if (address  & USB_EPNO_MASK)
    {
        USBD_SetEpStall(EPADR_SW2HW(address));
    }
    else
    {
        /* Not support. Reply STALL. */
        USBD_SET_CEP_STATE(USBD_CEPCTL_STALLEN_Msk);
        USBD_CLR_CEP_INT_FLAG(USBD_CEPINTSTS_SETUPPKIF_Msk);
        USBD_ENABLE_CEP_INT(USBD_CEPINTEN_SETUPPKIEN_Msk);
    }
    return RT_EOK;
}

static rt_err_t _ep_clear_stall(rt_uint8_t address)
{
    if (address  & USB_EPNO_MASK)
    {
        USBD_ClearEpStall(EPADR_SW2HW(address));
    }

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

    USBD->EP[EPADR_SW2HW(ep->ep_desc->bEndpointAddress)].EPRSPCTL = USB_EP_RSPCTL_TOGGLE;
    USBD->EP[EPADR_SW2HW(ep->ep_desc->bEndpointAddress)].EPCFG |= USB_EP_CFG_VALID;

    return RT_EOK;
}

static rt_err_t _ep_disable(uep_t ep)
{
    RT_ASSERT(ep != RT_NULL);
    RT_ASSERT(ep->ep_desc != RT_NULL);
    USBD->EP[EPADR_SW2HW(ep->ep_desc->bEndpointAddress)].EPCFG &= ~USB_EP_CFG_VALID;

    return RT_EOK;
}

static rt_err_t _ep0_send_status(void)
{
    /* Status Stage */
    USBD_CLR_CEP_INT_FLAG(USBD_CEPINTSTS_STSDONEIF_Msk
                          | USBD_CEPINTSTS_SETUPPKIF_Msk);

    USBD_ENABLE_CEP_INT(USBD_CEPINTEN_STSDONEIEN_Msk);

    USBD_SET_CEP_STATE(USB_CEPCTL_NAKCLR);

    return RT_EOK;
}

__STATIC_INLINE void nu_buffer_cpy(rt_uint8_t address, void *buffer, rt_size_t size)
{
    rt_uint32_t i, cnt;
    rt_uint32_t *_buf_word;
    rt_uint8_t  *_buf_byte;

    _buf_word = (rt_uint32_t *)buffer;
    cnt = size >> 2;
    _buf_byte = (rt_uint8_t *)((rt_uint8_t *)buffer + (cnt * 4));

    if ((address & USB_EPNO_MASK)) //EPs
    {
        if (address &  USB_DIR_IN) //IN
        {
            /* Non-control endpoint IN*/
            for (i = 0; i < cnt; i++)
            {
                USBD->EP[EPADR_SW2HW(address)].ep.EPDAT = _buf_word[i];
            }

            for (i = 0ul; i < (size % 4ul); i++)
                USBD->EP[EPADR_SW2HW(address)].ep.EPDAT_BYTE = _buf_byte[i];
        }
        else //OUT
        {
            for (i = 0; i < cnt; i++)
            {
                _buf_word[i] = USBD->EP[EPADR_SW2HW(address)].ep.EPDAT;
            }

            for (i = 0ul; i < (size % 4ul); i++)
                _buf_byte[i] = USBD->EP[EPADR_SW2HW(address)].ep.EPDAT_BYTE;
        }
    }
    else //Control
    {
        if (address &  USB_DIR_IN) //IN
        {
            for (i = 0; i < cnt; i++)
            {
                USBD->cep.CEPDAT = _buf_word[i];
            }

            for (i = 0ul; i < (size % 4ul); i++)
                USBD->cep.CEPDAT_BYTE = _buf_byte[i];

        }
        else //OUT
        {
            for (i = 0; i < cnt; i++)
            {
                _buf_word[i] = USBD->cep.CEPDAT;
            }

            for (i = 0ul; i < (size % 4ul); i++)
                _buf_byte[i] = USBD->cep.CEPDAT_BYTE;
        }
    }
}

static rt_ssize_t _ep_read(rt_uint8_t address, void *buffer)
{
    rt_size_t size  = 0;

    RT_ASSERT(!(address & USB_DIR_IN));

    if ((address & USB_EPNO_MASK))
    {
        RT_ASSERT(buffer != RT_NULL);
        size = USBD->EP[EPADR_SW2HW(address)].EPDATCNT & 0xffff;
        nu_buffer_cpy(address, buffer, size);
    }
    else     //control transfer
    {

        size =  USBD->CEPRXCNT & 0xffff;
        if (size)
        {
            RT_ASSERT(_rt_obj_udc.stage == STAGE_DOUT);
            nu_buffer_cpy(address, buffer, size);
        }

        _ep0_send_status();
    }

    return size;
}

static rt_ssize_t _ep_read_prepare(rt_uint8_t address, void *buffer, rt_size_t size)
{
    RT_ASSERT(!(address & USB_DIR_IN));

    if ((address & USB_EPNO_MASK))
    {
        USBD_ENABLE_EP_INT(EPADR_SW2HW(address),
                           USBD_EPINTEN_RXPKIEN_Msk);
    }
    else //control transfer
    {
        if (size)
        {
            RT_ASSERT(_rt_obj_udc.stage == STAGE_DOUT);
            USBD_ENABLE_CEP_INT(USBD_CEPINTEN_OUTTKIEN_Msk);
        }
        else
        {

            RT_ASSERT(_rt_obj_udc.stage == STAGE_STATUS_OUT);
            USBD_CLR_CEP_INT_FLAG(USBD_CEPINTSTS_SETUPPKIF_Msk
                                  | USBD_CEPINTSTS_STSDONEIF_Msk);
            USBD_ENABLE_CEP_INT(USBD_CEPINTEN_SETUPPKIEN_Msk
                                | USBD_CEPINTEN_STSDONEIEN_Msk);
            USBD_SET_CEP_STATE(USB_CEPCTL_NAKCLR);
        }

    }

    return size;
}

static rt_ssize_t _ep_write(rt_uint8_t address, void *buffer, rt_size_t size)
{

    RT_ASSERT((address & USB_DIR_IN));

    if (!(address & USB_EPNO_MASK)) //control transfer
    {
        if (size)
        {
            nu_buffer_cpy(address, buffer, size);
            USBD_START_CEP_IN(size);
        }
        else//zero length
        {
            USBD_SET_CEP_STATE(USB_CEPCTL_ZEROLEN);
            USBD_CLR_CEP_INT_FLAG(USBD_CEPINTSTS_STSDONEIF_Msk
                                  | USBD_CEPINTSTS_SETUPPKIF_Msk);

            USBD_ENABLE_CEP_INT(USBD_CEPINTEN_SETUPPKIEN_Msk
                                | USBD_CEPINTEN_STSDONEIEN_Msk);
        }

        if (_rt_obj_udc.stage == STAGE_DIN)
        {
            USBD_CLR_CEP_INT_FLAG(USBD_CEPINTSTS_TXPKIF_Msk);
            USBD_ENABLE_CEP_INT(USBD_CEPINTEN_TXPKIEN_Msk);
        }
        else if (_rt_obj_udc.stage == STAGE_DOUT)
        {
            USBD_CLR_CEP_INT_FLAG(USBD_CEPINTSTS_RXPKIF_Msk);
            USBD_ENABLE_CEP_INT(USBD_CEPINTEN_RXPKIEN_Msk);
        }
    }
    else
    {
        /* Non-control endpoint IN*/
        nu_buffer_cpy(address, buffer, size);
        USBD->EP[EPADR_SW2HW(address)].EPRSPCTL = USB_EP_RSPCTL_SHORTTXEN; // packet end
        USBD->EP[EPADR_SW2HW(address)].EPTXCNT = size;

        if ((USBD->EP[EPADR_SW2HW(address)].EPCFG & USBD_EPCFG_EPTYPE_Msk) == USB_EP_CFG_TYPE_INT)
        {
            USBD_ENABLE_EP_INT(EPADR_SW2HW(address), USBD_EPINTEN_INTKIEN_Msk);  //for interrupt transfer timing
        }
        else
        {
            USBD_ENABLE_EP_INT(EPADR_SW2HW(address), USBD_EPINTEN_TXPKIEN_Msk);  //for bulk transfer  timing
        }
    }

    return size;
}

static rt_err_t _suspend(void)
{
    return RT_EOK;
}

static rt_err_t _wakeup(void)
{
    return RT_EOK;
}

static void nu_usbd_isr(int vector, void *param)
{
    __IO rt_uint32_t IrqStL, IrqSt;
    int i;
    int IrqStAllEP;

    /* Igrone event if role is USBH*/
    if (nu_sys_usb0_role() != USB0_ID_DEVICE) return;

    IrqStL = USBD->GINTSTS & USBD->GINTEN;    /* get interrupt status */

    if (!IrqStL)    return;

    /* USB interrupt */
    if (IrqStL & USBD_GINTSTS_USBIF_Msk)
    {
        IrqSt = USBD->BUSINTSTS & USBD->BUSINTEN;

        if (IrqSt & USBD_BUSINTSTS_SOFIF_Msk)
        {
            USBD_CLR_BUS_INT_FLAG(USBD_BUSINTSTS_SOFIF_Msk);
            rt_usbd_sof_handler(&_rt_obj_udc);
        }
        if (IrqSt & USBD_BUSINTSTS_RSTIF_Msk)
        {
            /* Reset USB device address */
            USBD_SET_ADDR(0ul);

            USBD_ResetDMA();
            for (i = 0; i < USBD_MAX_EP; i++)
                USBD->EP[i].EPRSPCTL = USBD_EPRSPCTL_FLUSH_Msk;

            if (USBD->OPER & 0x04)    /* high speed */
            {
                LOG_I("-High Speed-");
                _nu_ep_partition_set(1);
            }
            else                        /* full speed */
            {
                LOG_I("-Full Speed-");
                _nu_ep_partition_set(0);
            }

            USBD_ENABLE_CEP_INT(USBD_CEPINTEN_SETUPPKIEN_Msk);
            USBD_ENABLE_BUS_INT(USBD_BUSINTEN_RSTIEN_Msk
                                | USBD_BUSINTEN_RESUMEIEN_Msk
                                | USBD_BUSINTEN_SUSPENDIEN_Msk
                                | USBD_BUSINTEN_VBUSDETIEN_Msk);
            USBD_CLR_BUS_INT_FLAG(USBD_BUSINTSTS_RSTIF_Msk);
            USBD_CLR_CEP_INT_FLAG(0x1ffc);

            for (i = 0ul; i < USBD_MAX_EP; i++)
            {
                if ((USBD->EP[i].EPCFG & 0x1ul) == 0x1ul)
                {
                    USBD->EP[i].EPRSPCTL = USB_EP_RSPCTL_TOGGLE;
                }
            }
            rt_usbd_reset_handler(&_rt_obj_udc);
            USBD_ENABLE_USB();
        }

        if (IrqSt & USBD_BUSINTSTS_RESUMEIF_Msk)
        {
            LOG_I("-Resume-");
            USBD_ENABLE_BUS_INT(USBD_BUSINTEN_RSTIEN_Msk | USBD_BUSINTEN_SUSPENDIEN_Msk);
            USBD_CLR_BUS_INT_FLAG(USBD_BUSINTSTS_RESUMEIF_Msk);
        }

        if (IrqSt & USBD_BUSINTSTS_SUSPENDIF_Msk)
        {
            LOG_I("-Suspend-");
            USBD_ENABLE_BUS_INT(USBD_BUSINTEN_RSTIEN_Msk | USBD_BUSINTEN_RESUMEIEN_Msk | USBD_BUSINTEN_VBUSDETIEN_Msk);
            USBD_CLR_BUS_INT_FLAG(USBD_BUSINTSTS_SUSPENDIF_Msk);
        }

        if (IrqSt & USBD_BUSINTSTS_HISPDIF_Msk)
        {
            USBD_ENABLE_CEP_INT(USBD_CEPINTEN_SETUPPKIEN_Msk);
            USBD_CLR_BUS_INT_FLAG(USBD_BUSINTSTS_HISPDIF_Msk);
        }

        if (IrqSt & USBD_BUSINTSTS_DMADONEIF_Msk)
        {
            USBD_CLR_BUS_INT_FLAG(USBD_BUSINTSTS_DMADONEIF_Msk);

            if (!(USBD->DMACTL & USBD_DMACTL_DMARD_Msk))
            {
                USBD_ENABLE_EP_INT(EPD, USBD_EPINTEN_RXPKIEN_Msk);
            }
        }

        if (IrqSt & USBD_BUSINTSTS_PHYCLKVLDIF_Msk)
        {
            USBD_CLR_BUS_INT_FLAG(USBD_BUSINTSTS_PHYCLKVLDIF_Msk);
        }

        if (IrqSt & USBD_BUSINTSTS_VBUSDETIF_Msk)
        {
            if (USBD_IS_ATTACHED())
            {
                if (!nu_usbd.plugging_status)
                {
                    LOG_I("PLUG IN");
                    /* USB Plug In */
                    nu_udc_enable();
                    rt_usbd_connect_handler(&_rt_obj_udc);
                    nu_usbd.plugging_status = 1;
                }
            }
            else
            {
                if (nu_usbd.plugging_status)
                {
                    LOG_I("Un-Plug");
                    /* USB Un-plug */
                    nu_udc_disable();
                    rt_usbd_disconnect_handler(&_rt_obj_udc);
                    nu_usbd.plugging_status = 0;
                }
            }
            USBD_CLR_BUS_INT_FLAG(USBD_BUSINTSTS_VBUSDETIF_Msk);
        }
    } //if (IrqStL & USBD_GINTSTS_USBIF_Msk)

    /* Control Transfer */
    if (IrqStL & USBD_GINTSTS_CEPIF_Msk)
    {
        IrqSt = USBD->CEPINTSTS & USBD->CEPINTEN;

        if (IrqSt & USBD_CEPINTSTS_SETUPTKIF_Msk)
        {
            USBD_CLR_CEP_INT_FLAG(USBD_CEPINTSTS_SETUPTKIF_Msk);
            return;
        }

        if (IrqSt & USBD_CEPINTSTS_SETUPPKIF_Msk)
        {
            USBD_CLR_CEP_INT_FLAG(USBD_CEPINTSTS_SETUPPKIF_Msk);
            NU_SetupStageCallback(&nu_usbd);
            USBD_CLR_CEP_INT_FLAG(USBD_CEPINTSTS_INTKIF_Msk
                                  | USBD_CEPINTSTS_RXPKIF_Msk
                                  | USBD_CEPINTSTS_STSDONEIF_Msk);
            return;
        }

        if (IrqSt & USBD_CEPINTSTS_OUTTKIF_Msk)
        {
            USBD_CLR_CEP_INT_FLAG(USBD_CEPINTSTS_OUTTKIF_Msk);
            rt_usbd_ep0_out_handler(&_rt_obj_udc, 0);
            USBD_ENABLE_CEP_INT(USBD_CEPINTEN_RXPKIEN_Msk);
            return;
        }

        if (IrqSt & USBD_CEPINTSTS_INTKIF_Msk)
        {
            USBD_ENABLE_CEP_INT(0);
            USBD_CLR_CEP_INT_FLAG(USBD_CEPINTSTS_INTKIF_Msk);
            rt_usbd_ep0_in_handler(&_rt_obj_udc);
            return;
        }

        if (IrqSt & USBD_CEPINTSTS_PINGIF_Msk)
        {
            USBD_CLR_CEP_INT_FLAG(USBD_CEPINTSTS_PINGIF_Msk);
            return;
        }

        if (IrqSt & USBD_CEPINTSTS_TXPKIF_Msk)
        {
            USBD_CLR_CEP_INT_FLAG(USBD_CEPINTSTS_TXPKIF_Msk
                                  | USBD_CEPINTSTS_SETUPPKIF_Msk
                                  | USBD_CEPINTSTS_STSDONEIF_Msk);

            USBD_ENABLE_CEP_INT(USBD_CEPINTEN_INTKIEN_Msk
                                | USBD_CEPINTEN_SETUPPKIEN_Msk
                                | USBD_CEPINTEN_STSDONEIEN_Msk);

            USBD_SET_CEP_STATE(USB_CEPCTL_NAKCLR);
            return;
        }

        if (IrqSt & USBD_CEPINTSTS_RXPKIF_Msk)
        {

            USBD_CLR_CEP_INT_FLAG(USBD_CEPINTSTS_SETUPPKIF_Msk
                                  | USBD_CEPINTSTS_STSDONEIF_Msk
                                  | USBD_CEPINTSTS_RXPKIF_Msk);
            USBD_SET_CEP_STATE(USB_CEPCTL_NAKCLR);
            USBD_ENABLE_CEP_INT(USBD_CEPINTEN_SETUPPKIEN_Msk
                                | USBD_CEPINTEN_STSDONEIEN_Msk
                                | USBD_CEPINTEN_RXPKIEN_Msk);
            return;
        }

        if (IrqSt & USBD_CEPINTSTS_NAKIF_Msk)
        {
            USBD_CLR_CEP_INT_FLAG(USBD_CEPINTSTS_NAKIF_Msk);
            return;
        }

        if (IrqSt & USBD_CEPINTSTS_STALLIF_Msk)
        {
            USBD_CLR_CEP_INT_FLAG(USBD_CEPINTSTS_STALLIF_Msk);
            return;
        }

        if (IrqSt & USBD_CEPINTSTS_ERRIF_Msk)
        {
            USBD_CLR_CEP_INT_FLAG(USBD_CEPINTSTS_ERRIF_Msk);
            return;
        }

        if (IrqSt & USBD_CEPINTSTS_STSDONEIF_Msk)
        {

            USBD_CLR_CEP_INT_FLAG(USBD_CEPINTSTS_STSDONEIF_Msk | USBD_CEPINTSTS_SETUPPKIF_Msk);
            USBD_ENABLE_CEP_INT(USBD_CEPINTEN_SETUPPKIEN_Msk);

            if ((USBD_GET_ADDR() == 0)
                    && ((uint8_t)((nu_usbd.base->SETUP1_0 >> 8) & 0xfful) == SET_ADDRESS))
            {
                USBD_SET_ADDR(nu_usbd.address_tmp);
                LOG_I("SET ADDR: 0x%02x", nu_usbd.address_tmp);
                nu_usbd.address_tmp = 0;

            }
            return;
        }

        if (IrqSt & USBD_CEPINTSTS_BUFFULLIF_Msk)
        {
            USBD_CLR_CEP_INT_FLAG(USBD_CEPINTSTS_BUFFULLIF_Msk);
            return;
        }

        if (IrqSt & USBD_CEPINTSTS_BUFEMPTYIF_Msk)
        {
            USBD_CLR_CEP_INT_FLAG(USBD_CEPINTSTS_BUFEMPTYIF_Msk);
            return;
        }

    } //if (IrqStL & USBD_GINTSTS_CEPIF_Msk)

    // For End-points
    IrqStAllEP = (IrqStL >> USBD_GINTSTS_EPAIF_Pos) & ((1 << USBD_MAX_EP) - 1);

    // Find the position of first '1' in allch_sts.
    while ((i = nu_ctz(IrqStAllEP)) != 32)
    {
        IrqSt = USBD->EP[i].EPINTSTS & USBD->EP[i].EPINTEN;

        if (_ep_pool[i + 1].dir == USB_DIR_IN)
            USBD_ENABLE_EP_INT(i, 0);

        USBD_CLR_EP_INT_FLAG(i, IrqSt);

        rt_usbd_ep_in_handler(&_rt_obj_udc, _ep_pool[i + 1].dir | EPADR_HW2SW(i), 0);

        IrqStAllEP &= ~(1 << i);
    }
}

static rt_err_t _init(rt_device_t device)
{
    nu_sys_ipclk_enable(nu_usbd.clkidx);

    nu_sys_ip_reset(nu_usbd.rstidx);

    rt_hw_us_delay(1000);

    /* USBD Open */
    USBD_ENABLE_USB();

    while (1)
    {
        USBD->EP[EPA].EPMPS = 0x20ul;
        if (USBD->EP[EPA].EPMPS == 0x20ul)
        {
            break;
        }
    }

    /* Force SE0 */
    USBD_SET_SE0();

    _nu_ep_partition();

#if ENABLE_FULL_SPEED_MODE_ONLY
    USBD->OPER &= ~USBD_OPER_HISPDEN_Msk;
#else
    USBD->OPER |= USBD_OPER_HISPDEN_Msk;
#endif

    /* Install USBD interrupt */
    rt_hw_interrupt_install(nu_usbd.irqn, nu_usbd_isr, &nu_usbd, nu_usbd.name);
    rt_hw_interrupt_set_priority(nu_usbd.irqn, IRQ_LEVEL_1);

    /* Enable USBD interrupt */
    rt_hw_interrupt_umask(nu_usbd.irqn);

    /* Start transaction */
    USBD_CLR_SE0();

    /* Get currect cable status */
    nu_usbd.plugging_status = USBD_IS_ATTACHED() >> USBD_PHYCTL_VBUSDET_Pos;

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
    rt_err_t result = RT_EOK;

    rt_memset((void *)&_rt_obj_udc, 0, sizeof(struct udcd));
    _rt_obj_udc.parent.type = RT_Device_Class_USBDevice;

#ifdef RT_USING_DEVICE_OPS
    _rt_obj_udc.parent.ops = &_ops;
#else
    _rt_obj_udc.parent.init = _init;
#endif

    _rt_obj_udc.parent.user_data = &nu_usbd;
    _rt_obj_udc.ops = &_udc_ops;

    /* Register endpoint information */
    _rt_obj_udc.ep_pool = _ep_pool;
    _rt_obj_udc.ep0.id = &_ep_pool[0];

#if ENABLE_FULL_SPEED_MODE_ONLY
    _rt_obj_udc.device_is_hs = RT_FALSE; /* Enable Full-speed only */
#else
    _rt_obj_udc.device_is_hs = RT_TRUE; /* Support Hi-Speed */
#endif

    result = rt_device_register((rt_device_t)&_rt_obj_udc, nu_usbd.name, 0);
    RT_ASSERT(result == RT_EOK);

    return rt_usb_device_init();
}
INIT_DEVICE_EXPORT(nu_usbd_register);
#endif
