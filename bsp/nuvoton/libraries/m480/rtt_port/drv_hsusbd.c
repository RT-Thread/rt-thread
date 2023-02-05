/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-5-26       Egbert           First version
*
******************************************************************************/


#include <rtconfig.h>

#ifdef BSP_USING_HSUSBD
#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>
#include "NuMicro.h"


#define LOG_TAG         "drv.hsusbd"
#define DBG_ENABLE
#define DBG_SECTION_NAME "drv.hsusbd"
#define DBG_LEVEL DBG_ERROR
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

#define EPADR_SW2HW(address) ((address & USB_EPNO_MASK) - 1) /* for non-control endpoint */
#define EPADR_HW2SW(address) ((address & USB_EPNO_MASK) + 1) /* for non-control endpoint */

/* Private typedef --------------------------------------------------------------*/
typedef struct _nu_usbd_t
{
    HSUSBD_T *Instance;     /* REG base */
    uint8_t address_tmp;    /* Keep assigned address for flow control */
} nu_usbd_t;


/* Private variables ------------------------------------------------------------*/
static nu_usbd_t nu_usbd =
{
    .Instance       = HSUSBD,
    .address_tmp    = 0,
};

static struct udcd _rt_obj_udc;

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
    {0xFF,              USB_EP_ATTR_TYPE_MASK,   USB_DIR_MASK,  0,                   ID_ASSIGNED  },
};


static void _nu_ep_partition_fs(void)
{
    /*****************************************************/
    /* EPA ==> Bulk IN endpoint, address 1 */
    HSUSBD_SetEpBufAddr(EPA, EPA_BUF_BASE, EPA_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPA, EPA_OTHER_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPA, EPADR_HW2SW(EPA), HSUSBD_EP_CFG_TYPE_BULK, HSUSBD_EP_CFG_DIR_IN);


    /* EPB ==> Bulk OUT endpoint, address 2 */
    HSUSBD_SetEpBufAddr(EPB, EPB_BUF_BASE, EPB_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPB, EPB_OTHER_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPB, EPADR_HW2SW(EPB), HSUSBD_EP_CFG_TYPE_BULK, HSUSBD_EP_CFG_DIR_OUT);
    HSUSBD_ENABLE_EP_INT(EPB, HSUSBD_EPINTEN_RXPKIEN_Msk);

    /*****************************************************/
    /* EPC ==> Interrupt IN endpoint, address 3 */
    HSUSBD_SetEpBufAddr(EPC, EPC_BUF_BASE, EPC_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPC, EPC_OTHER_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPC, EPADR_HW2SW(EPC), HSUSBD_EP_CFG_TYPE_INT, HSUSBD_EP_CFG_DIR_IN);

    /* EPD ==> Interrupt OUT endpoint, address 4 */
    HSUSBD_SetEpBufAddr(EPD, EPD_BUF_BASE, EPD_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPD, EPD_OTHER_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPD, EPADR_HW2SW(EPD), HSUSBD_EP_CFG_TYPE_INT, HSUSBD_EP_CFG_DIR_OUT);
    HSUSBD_ENABLE_EP_INT(EPD, HSUSBD_EPINTEN_RXPKIEN_Msk);

    /*****************************************************/
    /* EPE ==> Bulk IN endpoint, address 5 */
    HSUSBD_SetEpBufAddr(EPE, EPE_BUF_BASE, EPE_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPE, EPE_OTHER_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPE, EPADR_HW2SW(EPE), HSUSBD_EP_CFG_TYPE_BULK, HSUSBD_EP_CFG_DIR_IN);


    /* EPF ==> Bulk OUT endpoint, address 6 */
    HSUSBD_SetEpBufAddr(EPF, EPF_BUF_BASE, EPF_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPF, EPF_OTHER_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPF, EPADR_HW2SW(EPF), HSUSBD_EP_CFG_TYPE_BULK, HSUSBD_EP_CFG_DIR_OUT);
    HSUSBD_ENABLE_EP_INT(EPF, HSUSBD_EPINTEN_RXPKIEN_Msk);

    /*****************************************************/
    /* EPG ==> Interrupt IN endpoint, address 7 */
    HSUSBD_SetEpBufAddr(EPG, EPG_BUF_BASE, EPG_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPG, EPG_OTHER_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPG, EPADR_HW2SW(EPG), HSUSBD_EP_CFG_TYPE_INT, HSUSBD_EP_CFG_DIR_IN);

    /* EPH ==> Interrupt OUT endpoint, address 8 */
    HSUSBD_SetEpBufAddr(EPH, EPH_BUF_BASE, EPH_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPH, EPH_OTHER_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPH, EPADR_HW2SW(EPH), HSUSBD_EP_CFG_TYPE_INT, HSUSBD_EP_CFG_DIR_OUT);
    HSUSBD_ENABLE_EP_INT(EPH, HSUSBD_EPINTEN_RXPKIEN_Msk);
}

static void _nu_ep_partition_hs(void)
{
    /*****************************************************/
    /* EPA ==> Bulk IN endpoint, address 1 */
    HSUSBD_SetEpBufAddr(EPA, EPA_BUF_BASE, EPA_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPA, EPA_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPA, EPADR_HW2SW(EPA), HSUSBD_EP_CFG_TYPE_BULK, HSUSBD_EP_CFG_DIR_IN);


    /* EPB ==> Bulk OUT endpoint, address 2 */
    HSUSBD_SetEpBufAddr(EPB, EPB_BUF_BASE, EPB_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPB, EPB_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPB, EPADR_HW2SW(EPB), HSUSBD_EP_CFG_TYPE_BULK, HSUSBD_EP_CFG_DIR_OUT);
    HSUSBD_ENABLE_EP_INT(EPB, HSUSBD_EPINTEN_RXPKIEN_Msk);

    /*****************************************************/
    /* EPC ==> Interrupt IN endpoint, address 3 */
    HSUSBD_SetEpBufAddr(EPC, EPC_BUF_BASE, EPC_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPC, EPC_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPC, EPADR_HW2SW(EPC), HSUSBD_EP_CFG_TYPE_INT, HSUSBD_EP_CFG_DIR_IN);

    /* EPD ==> Interrupt OUT endpoint, address 4 */
    HSUSBD_SetEpBufAddr(EPD, EPD_BUF_BASE, EPD_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPD, EPD_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPD, EPADR_HW2SW(EPD), HSUSBD_EP_CFG_TYPE_INT, HSUSBD_EP_CFG_DIR_OUT);
    HSUSBD_ENABLE_EP_INT(EPD, HSUSBD_EPINTEN_RXPKIEN_Msk);

    /*****************************************************/
    /* EPE ==> Bulk IN endpoint, address 5 */
    HSUSBD_SetEpBufAddr(EPE, EPE_BUF_BASE, EPE_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPE, EPE_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPE, EPADR_HW2SW(EPE), HSUSBD_EP_CFG_TYPE_BULK, HSUSBD_EP_CFG_DIR_IN);


    /* EPF ==> Bulk OUT endpoint, address 6 */
    HSUSBD_SetEpBufAddr(EPF, EPF_BUF_BASE, EPF_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPF, EPF_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPF, EPADR_HW2SW(EPF), HSUSBD_EP_CFG_TYPE_BULK, HSUSBD_EP_CFG_DIR_OUT);
    HSUSBD_ENABLE_EP_INT(EPF, HSUSBD_EPINTEN_RXPKIEN_Msk);

    /*****************************************************/
    /* EPG ==> Interrupt IN endpoint, address 7 */
    HSUSBD_SetEpBufAddr(EPG, EPG_BUF_BASE, EPG_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPG, EPG_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPG, EPADR_HW2SW(EPG), HSUSBD_EP_CFG_TYPE_INT, HSUSBD_EP_CFG_DIR_IN);

    /* EPH ==> Interrupt OUT endpoint, address 8 */
    HSUSBD_SetEpBufAddr(EPH, EPH_BUF_BASE, EPH_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPH, EPH_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPH, EPADR_HW2SW(EPH), HSUSBD_EP_CFG_TYPE_INT, HSUSBD_EP_CFG_DIR_OUT);
    HSUSBD_ENABLE_EP_INT(EPH, HSUSBD_EPINTEN_RXPKIEN_Msk);
}

static void _nu_ep_partition(void)
{
    /* Configure USB controller */
    /* Enable USB BUS, CEP and EPA ~ EPH global interrupt */
    HSUSBD_ENABLE_USB_INT(HSUSBD_GINTEN_USBIEN_Msk
                          | HSUSBD_GINTEN_CEPIEN_Msk
                          | HSUSBD_GINTEN_EPAIEN_Msk
                          | HSUSBD_GINTEN_EPBIEN_Msk
                          | HSUSBD_GINTEN_EPCIEN_Msk
                          | HSUSBD_GINTEN_EPDIEN_Msk
                          | HSUSBD_GINTEN_EPEIEN_Msk
                          | HSUSBD_GINTEN_EPFIEN_Msk
                          | HSUSBD_GINTEN_EPGIEN_Msk
                          | HSUSBD_GINTEN_EPHIEN_Msk
                         );

    /* Enable BUS interrupt */
    HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_DMADONEIEN_Msk
                          | HSUSBD_BUSINTEN_RESUMEIEN_Msk
                          | HSUSBD_BUSINTEN_RSTIEN_Msk
                          | HSUSBD_BUSINTEN_VBUSDETIEN_Msk);
    /* Reset Address to 0 */
    HSUSBD_SET_ADDR(0);

    /*****************************************************/
    /* Control endpoint */
    HSUSBD_SetEpBufAddr(CEP, CEP_BUF_BASE, CEP_BUF_LEN);
    HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk
                          | HSUSBD_CEPINTEN_STSDONEIEN_Msk
                         );

    _nu_ep_partition_hs();
}

static void NU_SetupStageCallback(nu_usbd_t *nu_udc)
{
    struct urequest setup_packet;

    /* Setup packet process */
    setup_packet.request_type   = (uint8_t)(nu_udc->Instance->SETUP1_0 & 0xfful);
    setup_packet.bRequest       = (uint8_t)((nu_udc->Instance->SETUP1_0 >> 8) & 0xfful);
    setup_packet.wValue         = (uint16_t)  nu_udc->Instance->SETUP3_2;
    setup_packet.wIndex         = (uint16_t)  nu_udc->Instance->SETUP5_4;
    setup_packet.wLength        = (uint16_t)  nu_udc->Instance->SETUP7_6;

    rt_usbd_ep0_setup_handler(&_rt_obj_udc, (struct urequest *)&setup_packet);
}

static rt_err_t _ep_set_stall(rt_uint8_t address)
{

    if (address  & USB_EPNO_MASK)
    {
        HSUSBD_SetEpStall(EPADR_SW2HW(address));
    }
    else
    {
        /* Not support. Reply STALL. */
        HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALLEN_Msk);
        HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_SETUPPKIF_Msk);
        HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk);
    }
    return RT_EOK;
}

static rt_err_t _ep_clear_stall(rt_uint8_t address)
{
    if (address  & USB_EPNO_MASK)
    {
        HSUSBD_ClearEpStall(EPADR_SW2HW(address));
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

    HSUSBD->EP[EPADR_SW2HW(ep->ep_desc->bEndpointAddress)].EPRSPCTL = HSUSBD_EP_RSPCTL_TOGGLE;
    HSUSBD->EP[EPADR_SW2HW(ep->ep_desc->bEndpointAddress)].EPCFG |= HSUSBD_EP_CFG_VALID;

    return RT_EOK;
}

static rt_err_t _ep_disable(uep_t ep)
{
    RT_ASSERT(ep != RT_NULL);
    RT_ASSERT(ep->ep_desc != RT_NULL);
    HSUSBD->EP[EPADR_SW2HW(ep->ep_desc->bEndpointAddress)].EPCFG &= ~HSUSBD_EP_CFG_VALID;

    return RT_EOK;
}

static rt_err_t _ep0_send_status(void)
{
    /* Status Stage */
    HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk
                            | HSUSBD_CEPINTSTS_SETUPPKIF_Msk
                           );

    HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_STSDONEIEN_Msk);

    HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);

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
                HSUSBD->EP[EPADR_SW2HW(address)].EPDAT = _buf_word[i];
            }

            for (i = 0ul; i < (size % 4ul); i++)
                HSUSBD->EP[EPADR_SW2HW(address)].EPDAT_BYTE = _buf_byte[i];
        }
        else //OUT
        {
            for (i = 0; i < cnt; i++)
            {
                _buf_word[i] = HSUSBD->EP[EPADR_SW2HW(address)].EPDAT;
            }

            for (i = 0ul; i < (size % 4ul); i++)
                _buf_byte[i] = HSUSBD->EP[EPADR_SW2HW(address)].EPDAT_BYTE;
        }
    }
    else //Control
    {
        if (address &  USB_DIR_IN) //IN
        {
            for (i = 0; i < cnt; i++)
            {
                HSUSBD->CEPDAT = _buf_word[i];
            }

            for (i = 0ul; i < (size % 4ul); i++)
                HSUSBD->CEPDAT_BYTE = _buf_byte[i];

        }
        else //OUT
        {
            for (i = 0; i < cnt; i++)
            {
                _buf_word[i] = HSUSBD->CEPDAT;
            }

            for (i = 0ul; i < (size % 4ul); i++)
                _buf_byte[i] = HSUSBD->CEPDAT_BYTE;
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
        size = HSUSBD->EP[EPADR_SW2HW(address)].EPDATCNT & 0xffff;
        nu_buffer_cpy(address, buffer, size);
    }
    else     //control transfer
    {

        size =  HSUSBD->CEPRXCNT & 0xffff;
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
        HSUSBD_ENABLE_EP_INT(EPADR_SW2HW(address),
                             HSUSBD_EPINTEN_RXPKIEN_Msk
                            );
    }
    else //control transfer
    {
        if (size)
        {
            RT_ASSERT(_rt_obj_udc.stage == STAGE_DOUT);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_OUTTKIEN_Msk);
        }
        else
        {

            RT_ASSERT(_rt_obj_udc.stage == STAGE_STATUS_OUT);
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_SETUPPKIF_Msk
                                    | HSUSBD_CEPINTSTS_STSDONEIF_Msk
                                   );
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk
                                  | HSUSBD_CEPINTEN_STSDONEIEN_Msk
                                 );
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
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
            HSUSBD_START_CEP_IN(size);
        }
        else//zero length
        {
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_ZEROLEN);
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk
                                    | HSUSBD_CEPINTSTS_SETUPPKIF_Msk);

            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk
                                  | HSUSBD_CEPINTEN_STSDONEIEN_Msk
                                 );
        }

        if (_rt_obj_udc.stage == STAGE_DIN)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_TXPKIF_Msk);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_TXPKIEN_Msk);
        }
        else if (_rt_obj_udc.stage == STAGE_DOUT)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_RXPKIF_Msk);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_RXPKIEN_Msk);
        }
    }
    else
    {
        /* Non-control endpoint IN*/
        nu_buffer_cpy(address, buffer, size);
        HSUSBD->EP[EPADR_SW2HW(address)].EPRSPCTL = HSUSBD_EP_RSPCTL_SHORTTXEN; // packet end
        HSUSBD->EP[EPADR_SW2HW(address)].EPTXCNT = size;

        if ((HSUSBD->EP[EPADR_SW2HW(address)].EPCFG & HSUSBD_EPCFG_EPTYPE_Msk) == HSUSBD_EP_CFG_TYPE_INT)
        {
            HSUSBD_ENABLE_EP_INT(EPADR_SW2HW(address), HSUSBD_EPINTEN_INTKIEN_Msk);  //for interrupt transfer timing
        }
        else
        {
            HSUSBD_ENABLE_EP_INT(EPADR_SW2HW(address), HSUSBD_EPINTEN_TXPKIEN_Msk);  //for bulk transfer  timing
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

void _USBD20_IRQHandler(void)
{
    __IO rt_uint32_t IrqStL, IrqSt;

    IrqStL = HSUSBD->GINTSTS & HSUSBD->GINTEN;    /* get interrupt status */

    if (!IrqStL)    return;

    /* USB interrupt */
    if (IrqStL & HSUSBD_GINTSTS_USBIF_Msk)
    {
        IrqSt = HSUSBD->BUSINTSTS & HSUSBD->BUSINTEN;

        if (IrqSt & HSUSBD_BUSINTSTS_SOFIF_Msk)
        {
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_SOFIF_Msk);
            rt_usbd_sof_handler(&_rt_obj_udc);
        }
        if (IrqSt & HSUSBD_BUSINTSTS_RSTIF_Msk)
        {
            /* Reset USB device address */
            HSUSBD_SET_ADDR(0ul);

            HSUSBD_ResetDMA();
            HSUSBD->EP[EPA].EPRSPCTL = HSUSBD_EPRSPCTL_FLUSH_Msk;
            HSUSBD->EP[EPB].EPRSPCTL = HSUSBD_EPRSPCTL_FLUSH_Msk;
            HSUSBD->EP[EPC].EPRSPCTL = HSUSBD_EPRSPCTL_FLUSH_Msk;
            HSUSBD->EP[EPD].EPRSPCTL = HSUSBD_EPRSPCTL_FLUSH_Msk;
            HSUSBD->EP[EPE].EPRSPCTL = HSUSBD_EPRSPCTL_FLUSH_Msk;
            HSUSBD->EP[EPF].EPRSPCTL = HSUSBD_EPRSPCTL_FLUSH_Msk;
            HSUSBD->EP[EPG].EPRSPCTL = HSUSBD_EPRSPCTL_FLUSH_Msk;
            HSUSBD->EP[EPH].EPRSPCTL = HSUSBD_EPRSPCTL_FLUSH_Msk;

            if (HSUSBD->OPER & 0x04)    /* high speed */
            {
                LOG_I("-High Speed-");
                _nu_ep_partition_hs();
            }
            else                        /* full speed */
            {
                LOG_I("-Full Speed-");
                _nu_ep_partition_fs();
            }

            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk);
            HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_RSTIEN_Msk
                                  | HSUSBD_BUSINTEN_RESUMEIEN_Msk
                                  | HSUSBD_BUSINTEN_SUSPENDIEN_Msk
                                  | HSUSBD_BUSINTEN_VBUSDETIEN_Msk
                                 );
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_RSTIF_Msk);
            HSUSBD_CLR_CEP_INT_FLAG(0x1ffc);

            for (rt_uint32_t i = 0ul; i < HSUSBD_MAX_EP; i++)
            {
                if ((HSUSBD->EP[i].EPCFG & 0x1ul) == 0x1ul)
                {
                    HSUSBD->EP[i].EPRSPCTL = HSUSBD_EP_RSPCTL_TOGGLE;
                }
            }
            rt_usbd_reset_handler(&_rt_obj_udc);
            HSUSBD_ENABLE_USB();
        }

        if (IrqSt & HSUSBD_BUSINTSTS_RESUMEIF_Msk)
        {
            LOG_I("-Resume-");
            HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_RSTIEN_Msk | HSUSBD_BUSINTEN_SUSPENDIEN_Msk);
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_RESUMEIF_Msk);
        }

        if (IrqSt & HSUSBD_BUSINTSTS_SUSPENDIF_Msk)
        {
            LOG_I("-Suspend-");
            HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_RSTIEN_Msk | HSUSBD_BUSINTEN_RESUMEIEN_Msk | HSUSBD_BUSINTEN_VBUSDETIEN_Msk);
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_SUSPENDIF_Msk);
        }

        if (IrqSt & HSUSBD_BUSINTSTS_HISPDIF_Msk)
        {
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk);
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_HISPDIF_Msk);
        }

        if (IrqSt & HSUSBD_BUSINTSTS_DMADONEIF_Msk)
        {
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_DMADONEIF_Msk);

            if (!(HSUSBD->DMACTL & HSUSBD_DMACTL_DMARD_Msk))
            {
                HSUSBD_ENABLE_EP_INT(EPD, HSUSBD_EPINTEN_RXPKIEN_Msk);
            }
        }

        if (IrqSt & HSUSBD_BUSINTSTS_PHYCLKVLDIF_Msk)
        {
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_PHYCLKVLDIF_Msk);
        }

        if (IrqSt & HSUSBD_BUSINTSTS_VBUSDETIF_Msk)
        {
            if (HSUSBD_IS_ATTACHED())
            {
                LOG_I("PLUG IN");
                /* USB Plug In */
                HSUSBD_ENABLE_USB();
                rt_usbd_connect_handler(&_rt_obj_udc);

            }
            else
            {
                LOG_I("Un-Plug");
                /* USB Un-plug */
                HSUSBD_DISABLE_USB();
                rt_usbd_disconnect_handler(&_rt_obj_udc);
            }
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_VBUSDETIF_Msk);
        }
    }

    /* Control Transfer */
    if (IrqStL & HSUSBD_GINTSTS_CEPIF_Msk)
    {
        IrqSt = HSUSBD->CEPINTSTS & HSUSBD->CEPINTEN;

        if (IrqSt & HSUSBD_CEPINTSTS_SETUPTKIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_SETUPTKIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_SETUPPKIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_SETUPPKIF_Msk);
            NU_SetupStageCallback(&nu_usbd);
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk
                                    | HSUSBD_CEPINTSTS_RXPKIF_Msk
                                    | HSUSBD_CEPINTSTS_STSDONEIF_Msk
                                   );
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_OUTTKIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_OUTTKIF_Msk);
            rt_usbd_ep0_out_handler(&_rt_obj_udc, 0);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_RXPKIEN_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_INTKIF_Msk)
        {
            HSUSBD_ENABLE_CEP_INT(0);
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
            rt_usbd_ep0_in_handler(&_rt_obj_udc);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_PINGIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_PINGIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_TXPKIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_TXPKIF_Msk
                                    | HSUSBD_CEPINTSTS_SETUPPKIF_Msk
                                    | HSUSBD_CEPINTSTS_STSDONEIF_Msk
                                   );

            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_INTKIEN_Msk
                                  | HSUSBD_CEPINTEN_SETUPPKIEN_Msk
                                  | HSUSBD_CEPINTEN_STSDONEIEN_Msk
                                 );

            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_RXPKIF_Msk)
        {

            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_SETUPPKIF_Msk
                                    | HSUSBD_CEPINTSTS_STSDONEIF_Msk
                                    | HSUSBD_CEPINTSTS_RXPKIF_Msk
                                   );
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk
                                  | HSUSBD_CEPINTEN_STSDONEIEN_Msk
                                  | HSUSBD_CEPINTEN_RXPKIEN_Msk
                                 );
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_NAKIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_NAKIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_STALLIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STALLIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_ERRIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_ERRIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_STSDONEIF_Msk)
        {

            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk | HSUSBD_CEPINTSTS_SETUPPKIF_Msk);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk);

            if ((HSUSBD_GET_ADDR() == 0)
                    && ((uint8_t)((nu_usbd.Instance->SETUP1_0 >> 8) & 0xfful) == SET_ADDRESS)
               )
            {
                HSUSBD_SET_ADDR(nu_usbd.address_tmp);
                LOG_I("SET ADDR: 0x%02x", nu_usbd.address_tmp);
                nu_usbd.address_tmp = 0;

            }
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_BUFFULLIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_BUFFULLIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_BUFEMPTYIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_BUFEMPTYIF_Msk);
            return;
        }
    }

    /* bulk in */
    if (IrqStL & HSUSBD_GINTSTS_EPAIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPA].EPINTSTS & HSUSBD->EP[EPA].EPINTEN;
        HSUSBD_ENABLE_EP_INT(EPA, 0);
        HSUSBD_CLR_EP_INT_FLAG(EPA, IrqSt);
        rt_usbd_ep_in_handler(&_rt_obj_udc, USB_DIR_IN | EPADR_HW2SW(EPA), 0);
    }

    /* bulk out */
    if (IrqStL & HSUSBD_GINTSTS_EPBIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPB].EPINTSTS & HSUSBD->EP[EPB].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPB, IrqSt);
        rt_usbd_ep_out_handler(&_rt_obj_udc, USB_DIR_OUT | EPADR_HW2SW(EPB), 0);
    }

    /* interrupt in */
    if (IrqStL & HSUSBD_GINTSTS_EPCIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPC].EPINTSTS & HSUSBD->EP[EPC].EPINTEN;
        HSUSBD_ENABLE_EP_INT(EPC, 0);
        HSUSBD_CLR_EP_INT_FLAG(EPC, IrqSt);
        rt_usbd_ep_in_handler(&_rt_obj_udc, USB_DIR_IN | EPADR_HW2SW(EPC), 0);
    }

    /* interrupt out */
    if (IrqStL & HSUSBD_GINTSTS_EPDIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPD].EPINTSTS & HSUSBD->EP[EPD].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPD, IrqSt);
        rt_usbd_ep_out_handler(&_rt_obj_udc, USB_DIR_OUT | EPADR_HW2SW(EPD), 0);
    }

    /* bulk in */
    if (IrqStL & HSUSBD_GINTSTS_EPEIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPE].EPINTSTS & HSUSBD->EP[EPE].EPINTEN;
        HSUSBD_ENABLE_EP_INT(EPE, 0);
        HSUSBD_CLR_EP_INT_FLAG(EPE, IrqSt);

        rt_usbd_ep_in_handler(&_rt_obj_udc, USB_DIR_IN | EPADR_HW2SW(EPE), 0);
    }

    /* bulk out */
    if (IrqStL & HSUSBD_GINTSTS_EPFIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPF].EPINTSTS & HSUSBD->EP[EPF].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPF, IrqSt);
        rt_usbd_ep_out_handler(&_rt_obj_udc, USB_DIR_OUT | EPADR_HW2SW(EPF), 0);
    }

    /* interrupt in */
    if (IrqStL & HSUSBD_GINTSTS_EPGIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPG].EPINTSTS & HSUSBD->EP[EPG].EPINTEN;
        HSUSBD_ENABLE_EP_INT(EPG, 0);
        HSUSBD_CLR_EP_INT_FLAG(EPG, IrqSt);
        rt_usbd_ep_in_handler(&_rt_obj_udc, USB_DIR_IN | EPADR_HW2SW(EPG), 0);
    }

    /* interrupt out */
    if (IrqStL & HSUSBD_GINTSTS_EPHIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPH].EPINTSTS & HSUSBD->EP[EPH].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPH, IrqSt);
        rt_usbd_ep_out_handler(&_rt_obj_udc, USB_DIR_OUT | EPADR_HW2SW(EPH), 0);
    }

}

void USBD20_IRQHandler(void)
{
    rt_interrupt_enter();

    _USBD20_IRQHandler();

    /* leave interrupt */
    rt_interrupt_leave();
}

static rt_err_t _init(rt_device_t device)
{
#if !defined(BSP_USING_HSOTG)
    uint32_t volatile i;

    /* Initialize USB PHY */
    SYS_UnlockReg();
    SYS->USBPHY &= ~SYS_USBPHY_HSUSBROLE_Msk;    /* select HSUSBD */

    /* Enable USB PHY */
    SYS->USBPHY = (SYS->USBPHY & ~(SYS_USBPHY_HSUSBROLE_Msk | SYS_USBPHY_HSUSBACT_Msk)) | SYS_USBPHY_HSUSBEN_Msk;

    for (i = 0; i < 0x1000; i++)
        __NOP();  // delay > 10 us

    SYS->USBPHY |= SYS_USBPHY_HSUSBACT_Msk;
    SYS_LockReg();
#endif

    /* HSUSBD Open */
    HSUSBD->PHYCTL |= (HSUSBD_PHYCTL_PHYEN_Msk | HSUSBD_PHYCTL_DPPUEN_Msk);
    while (1)
    {
        HSUSBD->EP[EPA].EPMPS = 0x20ul;
        if (HSUSBD->EP[EPA].EPMPS == 0x20ul)
        {
            break;
        }
    }

    /* Force SE0 */
    HSUSBD_SET_SE0();

    _nu_ep_partition();

#if ENABLE_FULL_SPEED_MODE_ONLY
    HSUSBD->OPER &= ~HSUSBD_OPER_HISPDEN_Msk;
#else
    HSUSBD->OPER |= HSUSBD_OPER_HISPDEN_Msk;
#endif

    /* Enable USBD interrupt */
    NVIC_EnableIRQ(USBD20_IRQn);

    /* Start transaction */
    HSUSBD_Start();
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

int nu_hsusbd_register(void)
{
    if (RT_NULL != rt_device_find("usbd"))
    {
        LOG_E("\nHSUSBD Register failed. Another USBD device is registered\n");
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

    /* Register endpoint information */
    _rt_obj_udc.ep_pool = _ep_pool;
    _rt_obj_udc.ep0.id = &_ep_pool[0];

#if ENABLE_FULL_SPEED_MODE_ONLY
    _rt_obj_udc.device_is_hs = RT_FALSE; /* Enable Full-speed only */
#else
    _rt_obj_udc.device_is_hs = RT_TRUE; /* Support Hi-Speed */
#endif

    rt_device_register((rt_device_t)&_rt_obj_udc, "usbd", 0);

    rt_usb_device_init();
    return RT_EOK;
}
INIT_DEVICE_EXPORT(nu_hsusbd_register);
#endif
