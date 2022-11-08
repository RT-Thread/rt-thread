/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-4-27       Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_CANFD)

#include <rtdevice.h>
#include <rthw.h>

#include "drv_sys.h"
#include "drv_common.h"
#include "nu_bitutil.h"

#define LOG_TAG    "drv.canfd"
#undef  DBG_ENABLE
#define DBG_SECTION_NAME   LOG_TAG
#define DBG_LEVEL       LOG_LVL_ERROR
#define DBG_COLOR
#include <rtdbg.h>

/* Private Define ---------------------------------------------------------------*/
#define IS_CAN_STDID(STDID)   ((STDID) <= 0x7FFU)
#define IS_CAN_EXTID(EXTID)   ((EXTID) <= 0x1FFFFFFFU)
#define IS_CAN_DLC(DLC)       ((DLC) <= 8U)

/* Default config for serial_configure structure */
#define NU_CANFD_CONFIG_DEFAULT                  \
{                                              \
    CAN1MBaud,           /* 1M bits/s       */ \
    RT_CANMSG_BOX_SZ,    /* message box max size */ \
    RT_CANSND_BOX_NUM,   /* message box number   */ \
    RT_CAN_MODE_NORMAL,  /* Normal mode     */ \
    0,                   /* privmode        */ \
    0,                   /* reserved        */ \
    100,                 /* Timeout Tick    */ \
}

enum
{
    CANFD_START = -1,
#if defined(BSP_USING_CANFD0)
    CANFD0_IDX,
#endif
#if defined(BSP_USING_CANFD1)
    CANFD1_IDX,
#endif
#if defined(BSP_USING_CANFD2)
    CANFD2_IDX,
#endif
#if defined(BSP_USING_CANFD3)
    CANFD3_IDX,
#endif
    CANFD_CNT
};

/* Private Typedef --------------------------------------------------------------*/
struct nu_canfd
{
    struct rt_can_device dev;
    char *name;
    CANFD_T *base;
    uint32_t rstidx;
    IRQn_Type irqn0;
    IRQn_Type irqn1;
    uint32_t int_flag;
    CANFD_FD_T sCANFD_Config;
};
typedef struct nu_canfd *nu_canfd_t;

/* Private functions ------------------------------------------------------------*/
static rt_err_t nu_canfd_configure(struct rt_can_device *can, struct can_configure *cfg);
static rt_err_t nu_canfd_control(struct rt_can_device *can, int cmd, void *arg);
static int nu_canfd_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno);
static int nu_canfd_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t boxno);

static struct nu_canfd nu_canfd_arr[] =
{
#if defined(BSP_USING_CANFD0)
    {
        .name = "canfd0",
        .base = CANFD0,
        .rstidx = CANFD0_RST,
        .irqn0 = CANFD00_IRQn,
        .irqn1 = CANFD01_IRQn,
    },
#endif
#if defined(BSP_USING_CANFD1)
    {
        .name = "canfd1",
        .base = CANFD1,
        .rstidx = CANFD1_RST,
        .irqn0 = CANFD10_IRQn,
        .irqn1 = CANFD11_IRQn,
    },
#endif
#if defined(BSP_USING_CANFD2)
    {
        .name = "canfd2",
        .base = CANFD2,
        .rstidx = CANFD2_RST,
        .irqn0 = CANFD20_IRQn,
        .irqn1 = CANFD21_IRQn,
    },
#endif
#if defined(BSP_USING_CANFD3)
    {
        .name = "canfd3",
        .base = CANFD3,
        .rstidx = CANFD3_RST,
        .irqn0 = CANFD30_IRQn,
        .irqn1 = CANFD31_IRQn,
    },
#endif
}; /* struct nu_can */

/* Public functions ------------------------------------------------------------*/

/* Private variables ------------------------------------------------------------*/
static const struct rt_can_ops nu_canfd_ops =
{
    .configure = nu_canfd_configure,
    .control = nu_canfd_control,
    .sendmsg = nu_canfd_sendmsg,
    .recvmsg = nu_canfd_recvmsg,
};

static const struct can_configure nu_canfd_default_config = NU_CANFD_CONFIG_DEFAULT;

/* Interrupt Handle Function  ----------------------------------------------------*/

/* Private Variables ------------------------------------------------------------*/
const char *szIR[] =
{
    "CANFD_IR_RF0N - Rx FIFO 0 New Message",
    "CANFD_IR_RF0W - Rx FIFO 0 Watermark Reached",
    "CANFD_IR_RF0F - Rx FIFO 0 Full",
    "CANFD_IR_RF0L - Rx FIFO 0 Message Lost",
    "CANFD_IR_RF1N - Rx FIFO 1 New Message",
    "CANFD_IR_RF1W - Rx FIFO 1 Watermark Reached",
    "CANFD_IR_RF1F - Rx FIFO 1 Full",
    "CANFD_IR_RF1L - Rx FIFO 1 Message Lost",
    "CANFD_IR_HPM - High Priority Message",
    "CANFD_IR_TC - Transmission Completed",
    "CANFD_IR_TCF - Transmission Cancellation Finished",
    "CANFD_IR_TFE - Tx FIFO Empty",
    "CANFD_IR_TEFN - Tx Event FIFO New Entry",
    "CANFD_IR_TEFW - Tx Event FIFO Watermark Reached",
    "CANFD_IR_TEFF - Tx Event FIFO Full",
    "CANFD_IR_TEFL - Tx Event FIFO Event Lost",
    "CANFD_IR_TSW - Timestamp Wraparound",
    "CANFD_IR_MRAF - Message RAM Access Failure",
    "CANFD_IR_TOO - Timeout Occurred",
    "CANFD_IR_DRX - Message stored to Dedicated Rx Buffer",
    "BIT20",
    "BIT21",
    "CANFD_IR_ELO - Error Logging Overflow",
    "CANFD_IR_EP - Error Passive",
    "CANFD_IR_EW - Warning Status",
    "CANFD_IR_BO - Bus_Off Status",
    "CANFD_IR_WDI - Watchdog",
    "CANFD_IR_PEA - Protocol Error in Arbitration Phase",
    "CANFD_IR_PED - Protocol Error in Data Phase",
    "CANFD_IR_ARA - Access to Reserved Address",
    "BIT30",
    "BIT31"
};

static void dump_interrupt_event(uint32_t u32Status)
{
    uint32_t idx;
    while ((idx = nu_ctz(u32Status)) < 32) // Count Trailing Zeros ==> Find First One
    {
        LOG_D("[%s]", szIR[idx]);
        u32Status &= ~(1 << idx);
    }
}

static void nu_canfd_isr(int vector, void *param)
{
    /* Get base address of canfd register */
    nu_canfd_t psNuCANFD = (nu_canfd_t)param;

    /* Get base address of CAN register */
    CANFD_T *base = psNuCANFD->base;

    /* Get interrupt status */
    uint32_t u32Status = base->IR;
    CANFD_ClearStatusFlag(base, u32Status);

    /* Dump IR event */
    dump_interrupt_event(u32Status);

    /* Check Status Interrupt Flag (Error status Int and Status change Int) */
    /**************************/
    /* Status Change interrupt*/
    /**************************/

    if (u32Status & CANFD_IR_TC_Msk)
    {
        if (psNuCANFD->int_flag & RT_DEVICE_FLAG_INT_TX)
        {
            rt_hw_can_isr(&psNuCANFD->dev, RT_CAN_EVENT_TX_DONE);
        }
    }

    if (u32Status & (CANFD_IR_RF0N_Msk | CANFD_IR_RF1N_Msk))
    {
        if (psNuCANFD->int_flag & RT_DEVICE_FLAG_INT_RX)
        {
            rt_hw_can_isr(&psNuCANFD->dev, RT_CAN_EVENT_RX_IND);
        }
    }

    if (u32Status & (CANFD_IR_RF0L_Msk | CANFD_IR_RF1L_Msk))
    {
        rt_hw_can_isr(&psNuCANFD->dev, RT_CAN_EVENT_RXOF_IND);
    }

    if (u32Status & (CANFD_IR_TEFF_Msk | CANFD_IR_TOO_Msk))
    {
        rt_hw_can_isr(&psNuCANFD->dev, RT_CAN_EVENT_TX_FAIL);
    }

    /**************************/
    /* Error Status interrupt */
    /**************************/
    if (u32Status & CANFD_IR_EW_Msk)
    {
        LOG_E("[%s]EWARN", psNuCANFD->name) ;
    }

    if (u32Status & CANFD_IR_BO_Msk)
    {
        LOG_E("[%s]BUSOFF", psNuCANFD->name) ;

        /* To release busoff pin */
    }

    if (u32Status & CANFD_IR_PED_Msk)
    {
        LOG_E("[%s] LEC: %03x\n", psNuCANFD->name, base->PSR & CANFD_PSR_LEC_Msk) ;
    }
}

static void nu_canfd_ie(nu_canfd_t psNuCANFD)
{
    uint32_t u32CanFDIE = CANFD_IE_BOE_Msk;

    if (psNuCANFD->int_flag & (RT_DEVICE_FLAG_INT_RX))
    {
        /* Rx FIFO 0 New Message Interrupt */
        u32CanFDIE |= (CANFD_IE_RF0NE_Msk | CANFD_IE_RF1NE_Msk);
    }

    if (psNuCANFD->int_flag & (RT_DEVICE_FLAG_INT_TX))
    {
        /* Transmission Completed Interrupt */
        /* Timeout Occurred Interrupt */
        u32CanFDIE |= (CANFD_IE_TCE_Msk | CANFD_IE_TEFNE_Msk);
    }

    if (psNuCANFD->int_flag & RT_DEVICE_CAN_INT_ERR)
    {
        /* Bus_Off Status Interrupt */
        /* Warning Status Interrupt */
        /* Error Passive Interrupt */
        /* Error Logging Overflow Interrupt */
        /* Protocol Error in Data Phase interrupt Indicator */
        u32CanFDIE |= (CANFD_IE_EPE_Msk | CANFD_IE_EWE_Msk | CANFD_IE_ELOE_Msk | CANFD_IE_TOOE_Msk | CANFD_IR_PED_Msk);
    }

    //u32CanFDIE = 0xffffffff;

    CANFD_EnableInt(psNuCANFD->base, u32CanFDIE, 0,
                    (psNuCANFD->int_flag & (RT_DEVICE_FLAG_INT_TX)) ? CANFD_TXBTIE_TIEn_Msk : 0,
                    (psNuCANFD->int_flag & (RT_DEVICE_FLAG_INT_TX)) ? CANFD_TXBCIE_CFIEn_Msk : 0);
}

static rt_err_t nu_canfd_configure(struct rt_can_device *can, struct can_configure *cfg)
{
    nu_canfd_t psNuCANFD  = (nu_canfd_t)can;
    CANFD_FD_T *psCANFDConf;

    RT_ASSERT(can);
    RT_ASSERT(cfg);

    psCANFDConf = &psNuCANFD->sCANFD_Config;

    /* Get base address of CAN register */
    CANFD_T *base = psNuCANFD->base;

    CANFD_GetDefaultConfig(psCANFDConf, CANFD_OP_CAN_MODE);

    LOG_I("Message Ram Size: %d @%08x ~ %08x",    psCANFDConf->u32MRamSize, CANFD_SRAM_BASE_ADDR(base), psCANFDConf->u32MRamSize + CANFD_SRAM_BASE_ADDR(base));
    LOG_I("SIDFC: %d @%08x Size:%d",       psCANFDConf->sElemSize.u32SIDFC, CANFD_SRAM_BASE_ADDR(base) + psCANFDConf->sMRamStartAddr.u32SIDFC_FLSSA, psCANFDConf->sElemSize.u32SIDFC * sizeof(CANFD_STD_FILTER_T));
    LOG_I("XIDFC: %d @%08x Size:%d",       psCANFDConf->sElemSize.u32XIDFC, CANFD_SRAM_BASE_ADDR(base) + psCANFDConf->sMRamStartAddr.u32XIDFC_FLESA, psCANFDConf->sElemSize.u32XIDFC * sizeof(CANFD_EXT_FILTER_T));
    LOG_I("RxFifo0: %d @%08x Size:%d",     psCANFDConf->sElemSize.u32RxFifo0, CANFD_SRAM_BASE_ADDR(base) + psCANFDConf->sMRamStartAddr.u32RXF0C_F0SA, psCANFDConf->sElemSize.u32RxFifo0 * sizeof(CANFD_BUF_T));
    LOG_I("RxFifo1: %d @%08x Size:%d",     psCANFDConf->sElemSize.u32RxFifo1, CANFD_SRAM_BASE_ADDR(base) + psCANFDConf->sMRamStartAddr.u32RXF1C_F1SA, psCANFDConf->sElemSize.u32RxFifo1 * sizeof(CANFD_BUF_T));
    LOG_I("RxBuf: %d @%08x Size:%d",       psCANFDConf->sElemSize.u32RxBuf, CANFD_SRAM_BASE_ADDR(base) + psCANFDConf->sMRamStartAddr.u32RXBC_RBSA, psCANFDConf->sElemSize.u32RxBuf * sizeof(CANFD_BUF_T));
    LOG_I("TxEventFifo: %d @%08x Size:%d", psCANFDConf->sElemSize.u32TxEventFifo, CANFD_SRAM_BASE_ADDR(base) + psCANFDConf->sMRamStartAddr.u32TXEFC_EFSA, psCANFDConf->sElemSize.u32TxEventFifo * sizeof(CANFD_EXT_FILTER_T));
    LOG_I("TxBuf: %d @%08x Size:%d",       psCANFDConf->sElemSize.u32TxBuf, CANFD_SRAM_BASE_ADDR(base) + psCANFDConf->sMRamStartAddr.u32TXBC_TBSA, psCANFDConf->sElemSize.u32TxBuf * sizeof(CANFD_BUF_T));

    psCANFDConf->sBtConfig.sNormBitRate.u32BitRate = cfg->baud_rate;
    psCANFDConf->sBtConfig.sDataBitRate.u32BitRate = 0;

    LOG_I("CAN Baud rate: %d bps",  cfg->baud_rate);

    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:    // Normal
        psCANFDConf->sBtConfig.evTestMode = eCANFD_NORMAL;
        break;

    case RT_CAN_MODE_LISTEN:     // Bus monitor Mode, can't start a transmission
        psCANFDConf->sBtConfig.evTestMode = eCANFD_BUS_MONITOR;
        break;

    case RT_CAN_MODE_LOOPBACK:  // Test - Internal loopback
        psCANFDConf->sBtConfig.evTestMode = eCANFD_LOOPBACK_INTERNAL;
        break;

    case RT_CAN_MODE_LOOPBACKANLISTEN:
    default:
        rt_kprintf("Unsupported Operating mode\n");
        goto exit_nu_canfd_configure;
    }

    /*Set the CAN Bit Rate and Operating mode*/
    CANFD_Open(base, psCANFDConf);

    /* Set FIFO policy */
#if defined(RT_CAN_USING_HDR)
    /* Whitelist filtering */
    CANFD_SetGFC(base, eCANFD_REJ_NON_MATCH_FRM, eCANFD_REJ_NON_MATCH_FRM, 0, 0);
#else
    /* Blacklist filtering. */
    CANFD_SetGFC(base, eCANFD_ACC_NON_MATCH_FRM_RX_FIFO0, eCANFD_ACC_NON_MATCH_FRM_RX_FIFO0, 0, 0);
#endif

    /* Enable interrupt */
    nu_canfd_ie(psNuCANFD);

    //LOG_HEX("canfd", 16, (void *)base, sizeof(CANFD_T));

    /* Lock protected registers & Run */
    CANFD_RunToNormal(base, TRUE);

    return RT_EOK;

exit_nu_canfd_configure:

    CANFD_Close(base);

    return -(RT_ERROR);
}

static rt_err_t nu_canfd_control(struct rt_can_device *can, int cmd, void *arg)
{
    rt_uint32_t argval = (rt_uint32_t)arg;
    nu_canfd_t psNuCANFD = (nu_canfd_t)can;

    RT_ASSERT(can);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_SET_INT:
        psNuCANFD->int_flag |= argval;
        return nu_canfd_configure(can, &can->config);

    case RT_DEVICE_CTRL_CLR_INT:
        psNuCANFD->int_flag &= ~argval;
        return nu_canfd_configure(can, &can->config);

#if defined(RT_CAN_USING_HDR)
    case RT_CAN_CMD_SET_FILTER:
    {
        struct rt_can_filter_config *filter_cfg = (struct rt_can_filter_config *)arg;

        RT_ASSERT(filter_cfg);

        for (int i = 0; i < filter_cfg->count; i++)
        {
            uint32_t u32FEC = (filter_cfg->items[i].mode == RT_CAN_MODE_PRIV) ?  eCANFD_FLTR_ELEM_SET_PRI_STO_FIFO0 : eCANFD_FLTR_ELEM_STO_FIFO0;

            /* Set the filter rule */
            if (filter_cfg->items[i].ide == RT_CAN_STDID)
            {
                /* for 11-bit */
                CANFD_STD_FILTER_T sStdFilter;

                if (i >= CANFD_MAX_11_BIT_FTR_ELEMS)  // Check filter entry limitation
                    return -(RT_ERROR);

                sStdFilter.SFID2 = filter_cfg->items[i].mask;    /*!<Standard Filter ID 2. */ //mask
                sStdFilter.SFID1 = filter_cfg->items[i].id;      /*!<Standard Filter ID 1. */ //filter
                sStdFilter.SFEC  = u32FEC;                       /*!<Standard Filter Element Configuration */ //001b: Store in Rx FIFO 0 if filter matches
                sStdFilter.SFT   = eCANFD_SID_FLTR_TYPE_CLASSIC; /*!<Standard Filter Type */ //10b: Classic filter: SFID1 = filter, SFID2 = mask

                CANFD_SetSIDFltr(psNuCANFD->base, i, sStdFilter.VALUE);
            }
            else
            {
                /* for 29-bit */
                CANFD_EXT_FILTER_T sXidFilter;

                if (i >= CANFD_MAX_29_BIT_FTR_ELEMS) // Check filter entry limitation
                    return -(RT_ERROR);

                sXidFilter.EFID1 = filter_cfg->items[i].mask;     /*!<Extended Filter ID 2. */ //mask
                sXidFilter.EFID2 = filter_cfg->items[i].id;       /*!<Extended Filter ID 1. */ //filter
                sXidFilter.EFEC  = u32FEC;                        /*!<Extended Filter Element Configuration */ //001b: Store in Rx FIFO 0 if filter matches
                sXidFilter.EFT   = eCANFD_XID_FLTR_TYPE_CLASSIC;  /*!<Extended Filter Type */ //10b: Classic filter: SFID1 = filter, SFID2 = mask

                CANFD_SetXIDFltr(psNuCANFD->base, i, sXidFilter.LOWVALUE, sXidFilter.HIGHVALUE);
            }

        } //for (int i = 0; i < filter_cfg->count; i++)
    }
    break;
#endif

    case RT_CAN_CMD_SET_MODE:
        if ((argval == RT_CAN_MODE_NORMAL) ||
                (argval == RT_CAN_MODE_LISTEN) ||
                (argval == RT_CAN_MODE_LOOPBACK) ||
                (argval == RT_CAN_MODE_LOOPBACKANLISTEN))
        {
            if (argval != can->config.mode)
            {
                can->config.mode = argval;
                return nu_canfd_configure(can, &can->config);
            }
        }
        else
        {
            return -(RT_ERROR);
        }
        break;

    case RT_CAN_CMD_SET_BAUD:
    {
        if ((argval == CAN1MBaud) ||
                (argval == CAN800kBaud) ||
                (argval == CAN500kBaud) ||
                (argval == CAN250kBaud) ||
                (argval == CAN125kBaud) ||
                (argval == CAN100kBaud) ||
                (argval == CAN50kBaud) ||
                (argval == CAN20kBaud) ||
                (argval == CAN10kBaud))
        {
            if (argval != can->config.baud_rate)
            {
                can->config.baud_rate = argval;
                return nu_canfd_configure(can, &can->config);
            }
        }
        else
        {
            return -(RT_ERROR);
        }
    }
    break;

    case RT_CAN_CMD_SET_PRIV:
        if (argval != RT_CAN_MODE_PRIV &&
                argval != RT_CAN_MODE_NOPRIV)
        {
            return -(RT_ERROR);
        }
        if (argval != can->config.privmode)
        {
            can->config.privmode = argval;
            return nu_canfd_configure(can, &can->config);
        }
        break;

    case RT_CAN_CMD_GET_STATUS:
    {
        rt_uint32_t u32ErrCounter = psNuCANFD->base->ECR;
        rt_uint32_t u32ProtocolStatus = psNuCANFD->base->PSR;

        RT_ASSERT(arg);

        /*Receive Error Counter, return value is with Receive Error Passive.*/
        can->status.rcverrcnt = ((u32ErrCounter & CANFD_ECR_REC_Msk) >> CANFD_ECR_REC_Pos);

        /*Transmit Error Counter*/
        can->status.snderrcnt = ((u32ErrCounter & CANFD_ECR_TEC_Msk) >> CANFD_ECR_TEC_Pos);

        /*Last Error Type*/
        can->status.lasterrtype = ((u32ProtocolStatus & CANFD_PSR_LEC_Msk) >> CANFD_PSR_LEC_Pos);

        /*Status error code*/
        can->status.errcode = (u32ProtocolStatus & CANFD_PSR_EW_Msk) ? 1 :
                              (u32ProtocolStatus & CANFD_PSR_EP_Msk) ? 2 :
                              (u32ProtocolStatus & CANFD_PSR_BO_Msk) ? 3 :
                              0;

        rt_memcpy(arg, &can->status, sizeof(struct rt_can_status));
    }
    break;

    default:
        return -(RT_EINVAL);

    }

    return RT_EOK;
}

static int nu_canfd_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno)
{
    CANFD_FD_MSG_T sTxMsg;
    struct rt_can_msg *pmsg;
    nu_canfd_t psNuCANFD = (nu_canfd_t)can;

    RT_ASSERT(can);
    RT_ASSERT(buf);

    pmsg = (struct rt_can_msg *) buf;

    if (pmsg->ide == RT_CAN_STDID && IS_CAN_STDID(pmsg->id))
    {
        /* Standard ID (11 bits)*/
        sTxMsg.u32Id = pmsg->id;
        sTxMsg.eIdType = eCANFD_SID;
    }
    else if (pmsg->ide == RT_CAN_EXTID && IS_CAN_EXTID(pmsg->id))
    {
        /* Extended ID (29 bits)*/
        sTxMsg.u32Id = pmsg->id;
        sTxMsg.eIdType = eCANFD_XID;
    }
    else
    {
        goto exit_nu_canfd_sendmsg;
    }

    sTxMsg.bBitRateSwitch = 0;

    if (pmsg->rtr == RT_CAN_DTR)
    {
        /* Data frame */
        sTxMsg.eFrmType = eCANFD_DATA_FRM;
    }
    else if (pmsg->rtr == RT_CAN_RTR)
    {
        /* Remote frame */
        sTxMsg.eFrmType = eCANFD_REMOTE_FRM;
    }
    else
    {
        goto exit_nu_canfd_sendmsg;
    }

    /* Check the parameters */
    if (IS_CAN_DLC(pmsg->len))
    {
        sTxMsg.u32DLC = pmsg->len;
    }
    else
    {
        goto exit_nu_canfd_sendmsg;
    }

    if (pmsg->len > 0)
    {
        rt_memcpy(&sTxMsg.au8Data[0], pmsg->data, pmsg->len);
    }

    if (!CANFD_TransmitTxMsg(psNuCANFD->base, 0, &sTxMsg))
    {
        goto exit_nu_canfd_sendmsg;
    }

    return RT_EOK;

exit_nu_canfd_sendmsg:

    return -(RT_ERROR);
}

static int nu_canfd_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t boxno)
{
    CANFD_FD_MSG_T sRxMsg;
    struct rt_can_msg *pmsg;
    nu_canfd_t psNuCANFD = (nu_canfd_t)can;

    RT_ASSERT(can);
    RT_ASSERT(buf);

    pmsg = (struct rt_can_msg *) buf;

    /* get data */
    if (CANFD_ReadRxFifoMsg(psNuCANFD->base, 0, &sRxMsg) == FALSE)
    {
        rt_kprintf("No available RX Msg.\n");
        return -(RT_ERROR);
    }

#ifdef RT_CAN_USING_HDR
    /* Hardware filter messages are valid */
    pmsg->hdr_index = boxno;
    can->hdr[pmsg->hdr_index].connected = 1;
#endif

    pmsg->ide = (sRxMsg.eIdType == eCANFD_SID) ? RT_CAN_STDID : RT_CAN_EXTID;
    pmsg->rtr = (sRxMsg.eFrmType == eCANFD_DATA_FRM) ? RT_CAN_DTR : RT_CAN_RTR;
    pmsg->id  = sRxMsg.u32Id;
    pmsg->len = sRxMsg.u32DLC;

    if (pmsg->len > 0)
        rt_memcpy(&pmsg->data[0], &sRxMsg.au8Data[0], pmsg->len);

    return RT_EOK;
}

/**
 * Hardware CAN Initialization
 */
static int rt_hw_canfd_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;

    for (i = (CANFD_START + 1); i < CANFD_CNT; i++)
    {
        nu_canfd_arr[i].dev.config = nu_canfd_default_config;

#ifdef RT_CAN_USING_HDR
        nu_canfd_arr[i].dev.config.maxhdr = RT_CANMSG_BOX_SZ;
#endif
        /* Register can device */
        ret = rt_hw_can_register(&nu_canfd_arr[i].dev, nu_canfd_arr[i].name, &nu_canfd_ops, NULL);
        RT_ASSERT(ret == RT_EOK);

        /* Register ISR. */
        rt_hw_interrupt_install(nu_canfd_arr[i].irqn0, nu_canfd_isr, &nu_canfd_arr[i], nu_canfd_arr[i].name);
        rt_hw_interrupt_install(nu_canfd_arr[i].irqn1, nu_canfd_isr, &nu_canfd_arr[i], nu_canfd_arr[i].name);

        /* Unmask interrupt. */
        rt_hw_interrupt_umask(nu_canfd_arr[i].irqn0);
        rt_hw_interrupt_umask(nu_canfd_arr[i].irqn1);
    }

    return (int)ret;
}
INIT_DEVICE_EXPORT(rt_hw_canfd_init);
#endif  //#if defined(BSP_USING_CANFD)
