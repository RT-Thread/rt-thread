/*
 * File      : drv_lpccan.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       		Notes
 * 2015-06-30     aubrcool@qq.com 	first version
 */
#include <rthw.h>
#include <rtdevice.h>
#include <board.h>
#include <drv_lpccan.h>

#ifdef RT_USING_CAN

#include "lpc_types.h"
#include "lpc_can.h"
#include "lpc_pinsel.h"
#include "lpc_exti.h"
#include "lpc_clkpwr.h"

struct lpccandata
{
    en_CAN_unitId id;
};

static LPC_CAN_TypeDef*  lcpcan_get_reg_base(rt_uint32_t id)
{
    LPC_CAN_TypeDef* pCan;

    switch (id)
    {
    case CAN_ID_1:
        pCan = LPC_CAN1;
        break;

    case CAN_ID_2:
        pCan = LPC_CAN2;
        break;
    default:
        pCan = NULL;
    }
    return pCan;
}

static void lpccan_irqstate_init(rt_uint32_t id)
{
    LPC_CAN_TypeDef* pCan = lcpcan_get_reg_base(id);
    volatile rt_int32_t i;

    pCan->MOD = 1; // Enter Reset Mode
    pCan->IER = 0; // Disable All CAN Interrupts
    pCan->GSR = 0;

    /* Request command to release Rx, Tx buffer and clear data overrun */
    //pCan->CMR = CAN_CMR_AT | CAN_CMR_RRB | CAN_CMR_CDO;
    pCan->CMR = (1 << 1) | (1 << 2) | (1 << 3);

    /* Read to clear interrupt pending in interrupt capture register */
    i = pCan->ICR;
    i = i;

    pCan->MOD = 0;// Return Normal operating
}

static rt_err_t lpccan_baud_set(rt_uint32_t id, rt_uint32_t baud)
{
    uint32_t result = 0;
    uint8_t NT, TSEG1, TSEG2;
    uint32_t CANPclk = 0;
    uint32_t BRP;
    LPC_CAN_TypeDef* pCan = lcpcan_get_reg_base(id);

    CANPclk = CLKPWR_GetCLK(CLKPWR_CLKTYPE_PER);
    result = CANPclk / baud;

    /* Calculate suitable nominal time value
     * NT (nominal time) = (TSEG1 + TSEG2 + 3)
     * NT <= 24
     * TSEG1 >= 2*TSEG2
     */
    for(NT = 24; NT > 0; NT = NT-2)
    {
        if ((result % NT) == 0)
        {
            BRP = result / NT - 1;
            NT--;
            TSEG2 = (NT/3) - 1;
            TSEG1 = NT -(NT/3) - 1;
            break;
        }
    }

    /* Enter reset mode */
    pCan->MOD = 0x01;
    /* Set bit timing
     * Default: SAM = 0x00;
     *          SJW = 0x03;
     */
    pCan->BTR = (TSEG2 << 20) | (TSEG1 << 16) | (3 << 14) | BRP;
    /* Return to normal operating */
    pCan->MOD = 0;

    return RT_EOK;
}

static void lpccan_init_alut_ram(void)
{
    //Reset CANAF value
    LPC_CANAF->AFMR = 0x01;
    //clear ALUT RAM
    rt_memset((void *)LPC_CANAF_RAM->mask, 0, 2048);
    LPC_CANAF->SFF_sa = 0;
    LPC_CANAF->SFF_GRP_sa = 0;
    LPC_CANAF->EFF_sa = 0;
    LPC_CANAF->EFF_GRP_sa = 0;
    LPC_CANAF->ENDofTable = 0;
    LPC_CANAF->AFMR = 0x00;
    // Set AF Mode
    CAN_SetAFMode(CAN_NORMAL);
}

#ifdef RT_USING_LPCCAN1
static void lpccan1_turnon_clk(void)
{
    CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCAN1, ENABLE);
}

static void lpccan1_filter_init(struct rt_can_device *can)
{
}

static void lpccan1_hw_init(uint32_t baud, CAN_MODE_Type mode)
{
    if(mode != CAN_SELFTEST_MODE)
    {
#ifndef LPCCAN1_USEING_GPIO_SECOND
        PINSEL_ConfigPin (0, 0, 1);
        PINSEL_ConfigPin (0, 1, 1);
#else
        PINSEL_ConfigPin (0, 21, 4);
        PINSEL_ConfigPin (0, 22, 4);
#endif
    }
    lpccan1_turnon_clk();
    lpccan_irqstate_init(CAN_1);
    lpccan_init_alut_ram();
    lpccan1_turnon_clk();
    lpccan_baud_set(CAN_1, baud);
    CAN_ModeConfig(CAN_1, mode, ENABLE);
    if(mode == CAN_SELFTEST_MODE)
    {
        //CAN_ModeConfig(CAN_1, CAN_TEST_MODE, ENABLE);
        CAN_SetAFMode(CAN_ACC_BP);
    }
}
#endif /*RT_USING_LPCCAN1*/

#ifdef RT_USING_LPCCAN2
static void lpccan2_turnon_clk(void)
{
    CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCAN2, ENABLE);
}

static void lpccan2_filter_init(struct rt_can_device *can)
{
}

static void lpccan2_hw_init(uint32_t baud,  CAN_MODE_Type mode)
{
    if(mode != CAN_SELFTEST_MODE)
    {
#ifndef LPCCAN2_USEING_GPIO_SECOND
        PINSEL_ConfigPin (0, 4, 2);
        PINSEL_ConfigPin (0, 5, 2);
#else
        PINSEL_ConfigPin (2, 7, 1);
        PINSEL_ConfigPin (2, 8, 1);
#endif
    }
    lpccan2_turnon_clk();
    lpccan_irqstate_init(CAN_2);
#ifndef RT_USING_LPCCAN1
    lpccan_init_alut_ram();
#endif /*RT_USING_LPCCAN1*/
    lpccan_baud_set(CAN_2, baud);
    CAN_ModeConfig(CAN_2, mode, ENABLE);
    if(mode == CAN_SELFTEST_MODE)
    {
        CAN_SetAFMode(CAN_ACC_BP);
    }
}
#endif /*RT_USING_LPCCAN2*/

static rt_err_t configure(struct rt_can_device *can, struct can_configure *cfg)
{
    CAN_MODE_Type mode;
    rt_uint32_t canid;

    switch(cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
        mode = CAN_OPERATING_MODE;
        break;
    case RT_CAN_MODE_LISEN:
        mode = CAN_LISTENONLY_MODE;
        break;
    case RT_CAN_MODE_LOOPBACKANLISEN:
        mode = CAN_SELFTEST_MODE;
        break;
    default:
        return RT_EIO;
    }

    canid = ((struct lpccandata  *) can->parent.user_data)->id;
#ifdef RT_USING_LPCCAN1
    if(canid == CAN_1)
    {
        lpccan1_hw_init(cfg->baud_rate, mode);
        lpccan1_filter_init(can);
    }
#endif /*RT_USING_LPCCAN1*/
#ifdef RT_USING_LPCCAN2
#ifdef RT_USING_LPCCAN1
    else
#endif /*RT_USING_LPCCAN1*/
    {
        lpccan2_hw_init(cfg->baud_rate, mode);
        lpccan2_filter_init(can);
    }
#endif /*RT_USING_LPCCAN2*/
    return RT_EOK;
}

static CAN_ERROR findfilter(struct lpccandata* plpccan, struct rt_can_filter_item* pitem, rt_int32_t* pos)
{
    extern uint16_t CANAF_FullCAN_cnt;
    extern uint16_t CANAF_std_cnt;
    extern uint16_t CANAF_gstd_cnt;
    extern uint16_t CANAF_ext_cnt;
    extern uint16_t CANAF_gext_cnt;

    rt_uint32_t buf0 = 0, buf1 = 0;
    rt_int16_t cnt1 = 0, cnt2 = 0, bound1 = 0;
    CAN_ID_FORMAT_Type format;
    *pos = -1;
    if(pitem->ide)
    {
        format = EXT_ID_FORMAT;
    }
    else
    {
        format = STD_ID_FORMAT;
    }
    if(pitem->mode)
    {
        rt_uint32_t id = pitem->id;
        if(format == STD_ID_FORMAT)
        {
            id &= 0x07FF;

            id |= plpccan->id << 13;/* Add controller number */

            if (CANAF_std_cnt == 0)
            {
                return CAN_ENTRY_NOT_EXIT_ERROR;
            }
            else if (CANAF_std_cnt == 1)
            {
                cnt2 = (CANAF_FullCAN_cnt + 1) >> 1;
                if(id != LPC_CANAF_RAM->mask[cnt2] >> 16)
                {
                    return CAN_ENTRY_NOT_EXIT_ERROR;
                }
            }
            else
            {
                cnt1 = (CANAF_FullCAN_cnt+1)>>1;

                bound1 = ((CANAF_FullCAN_cnt+1)>>1)+((CANAF_std_cnt+1)>>1);

                while (cnt1 < bound1)
                {
                    /* Loop through standard existing IDs */
                    if (((LPC_CANAF_RAM->mask[cnt1] >> 16) & 0xE7FF) == id)
                    {
                        *pos = cnt1 * 2;
                        return CAN_OK;
                    }

                    if ((LPC_CANAF_RAM->mask[cnt1] & 0x0000E7FF) == id)
                    {
                        *pos = cnt1 * 2 + 1;
                        return CAN_OK;
                    }
                    if (((LPC_CANAF_RAM->mask[cnt1] >> 16) & 0xE7FF) > id)
                    {
                        return CAN_ENTRY_NOT_EXIT_ERROR;
                    }

                    if ((LPC_CANAF_RAM->mask[cnt1] & 0x0000E7FF) > id)
                    {
                        return CAN_ENTRY_NOT_EXIT_ERROR;
                    }
                    cnt1++;
                }
                return CAN_ENTRY_NOT_EXIT_ERROR;
            }
        }
        /*********** Add Explicit Extended Identifier Frame Format entry *********/
        else
        {
            /* Add controller number */
            id |= plpccan->id << 29;

            cnt1 = ((CANAF_FullCAN_cnt+1) >> 1) + (((CANAF_std_cnt + 1) >> 1) + CANAF_gstd_cnt);

            cnt2 = 0;

            while (cnt2 < CANAF_ext_cnt)
            {
                /* Loop through extended existing masks*/
                if (LPC_CANAF_RAM->mask[cnt1] == id)
                {
                    *pos = cnt2;
                    return CAN_OK;
                }
                if (LPC_CANAF_RAM->mask[cnt1] > id)
                {
                    return CAN_ENTRY_NOT_EXIT_ERROR;
                }
                cnt1++;
                cnt2++;
            }
        }
    }
    else
    {
        rt_uint32_t lowerID =  pitem->id;
        rt_uint32_t upperID =  pitem->mask;
        rt_uint32_t  LID,UID;
        if(lowerID > upperID)
            return CAN_CONFLICT_ID_ERROR;
        if(format == STD_ID_FORMAT)
        {
            lowerID &=0x7FF; //mask ID
            upperID &=0x7FF;
            cnt1 = ((CANAF_FullCAN_cnt+1)>>1) + ((CANAF_std_cnt + 1) >> 1);
            if(CANAF_gstd_cnt == 0)
            {
                return CAN_ENTRY_NOT_EXIT_ERROR;
            }
            else
            {
                bound1 = ((CANAF_FullCAN_cnt+1)>>1) + ((CANAF_std_cnt + 1) >> 1) + CANAF_gstd_cnt;
                while(cnt1 < bound1)
                {
                    //compare controller first
                    while((LPC_CANAF_RAM->mask[cnt1] >> 29) < (plpccan->id))//increase until meet greater or equal controller
                        cnt1++;
                    buf0 = LPC_CANAF_RAM->mask[cnt1];
                    if((LPC_CANAF_RAM->mask[cnt1] >> 29) > (plpccan->id)) //meet greater controller
                    {
                        return CAN_ENTRY_NOT_EXIT_ERROR;
                    }
                    else //meet equal controller
                    {
                        LID  = (buf0 >> 16)&0x7FF;
                        UID  = buf0 & 0x7FF;
                        if (upperID == LID && lowerID == UID)
                        {
                            *pos = cnt1;
                            return CAN_OK;
                        }
                        if (upperID < LID)
                        {
                            return CAN_ENTRY_NOT_EXIT_ERROR;
                        }
                        else if (lowerID >= UID)
                        {
                            cnt1 ++;
                        }
                        else
                            return CAN_CONFLICT_ID_ERROR;
                    }
                }
                if(cnt1 >= bound1)
                {
                    return CAN_ENTRY_NOT_EXIT_ERROR;
                }
            }
        }
        /*********Add Group of Extended Identifier Frame Format************/
        else
        {
            lowerID  &= 0x1FFFFFFF; //mask ID
            upperID &= 0x1FFFFFFF;
            cnt1 = ((CANAF_FullCAN_cnt+1)>>1) + ((CANAF_std_cnt + 1) >> 1) + CANAF_gstd_cnt + CANAF_ext_cnt;
            //if this is the first Group standard ID entry
            if(CANAF_gext_cnt == 0)
            {
                return CAN_ENTRY_NOT_EXIT_ERROR;
            }
            else
            {
                bound1 = ((CANAF_FullCAN_cnt+1)>>1) + ((CANAF_std_cnt + 1) >> 1) + CANAF_gstd_cnt \
                         + CANAF_ext_cnt + (CANAF_gext_cnt<<1);
                while(cnt1 < bound1)
                {
                    while((LPC_CANAF_RAM->mask[cnt1] >>29)< plpccan->id ) //increase until meet greater or equal controller
                        cnt1++;
                    buf0 = LPC_CANAF_RAM->mask[cnt1];
                    buf1 = LPC_CANAF_RAM->mask[cnt1+1];
                    if((LPC_CANAF_RAM->mask[cnt1] >> 29) > plpccan->id ) //meet greater controller
                    {
                        return CAN_ENTRY_NOT_EXIT_ERROR;
                    }
                    else //meet equal controller
                    {
                        LID  = buf0 & 0x1FFFFFFF; //mask ID
                        UID  = buf1 & 0x1FFFFFFF;
                        if (upperID == LID && lowerID == UID)
                        {
                            *pos = cnt1;
                            return CAN_OK;
                        }
                        if (upperID < LID)
                        {
                            return CAN_ENTRY_NOT_EXIT_ERROR;
                        }
                        else if (lowerID >= UID)
                        {
                            //load next entry to compare
                            cnt1 +=2;
                        }
                        else
                            return CAN_CONFLICT_ID_ERROR;
                    }
                }
                if(cnt1 >= bound1)
                {
                    return CAN_ENTRY_NOT_EXIT_ERROR;
                }
            }
        }
    }
    return CAN_ENTRY_NOT_EXIT_ERROR;
}

static rt_err_t setfilter(struct lpccandata* plpccan,struct rt_can_filter_config *pconfig)
{
    struct rt_can_filter_item* pitem = pconfig->items;
    rt_uint32_t count = pconfig->count;
    rt_int32_t pos;
    CAN_ID_FORMAT_Type format;
    CAN_ERROR lpccanres;
    while(count)
    {
        if(pitem->ide)
        {
            format = EXT_ID_FORMAT;
        }
        else
        {
            format = STD_ID_FORMAT;
        }
        lpccanres = findfilter(plpccan, pitem, &pos);
        if(pconfig->actived && lpccanres != CAN_OK)
        {
            if(pitem->mode)
            {
                lpccanres = CAN_LoadGroupEntry(plpccan->id, pitem->id, pitem->mask, format);
            }
            else
            {
                lpccanres = CAN_LoadExplicitEntry(plpccan->id, pitem->id, format);
            }
        }
        else if(!pconfig->actived && lpccanres == CAN_OK)
        {
            AFLUT_ENTRY_Type type;
            if(pitem->mode)
            {
                if(format == EXT_ID_FORMAT)
                {
                    type = GROUP_EXTEND_ENTRY;
                }
                else
                {
                    type = GROUP_STANDARD_ENTRY;
                }
            }
            else
            {
                if(format == EXT_ID_FORMAT)
                {
                    type = EXPLICIT_EXTEND_ENTRY;
                }
                else
                {
                    type = EXPLICIT_STANDARD_ENTRY;
                }
            }
            lpccanres = CAN_RemoveEntry(type, (rt_uint16_t)(pos));
        }
        else if(!pconfig->actived && lpccanres != CAN_OK)
        {
            lpccanres = CAN_OK;
        }
        if(lpccanres != CAN_OK)
        {
            return RT_EIO;
        }
        pitem++;
        count--;
    }
    return RT_EOK;
}

static rt_err_t control(struct rt_can_device *can, int cmd, void *arg)
{
    struct lpccandata* plpccan;
    rt_uint32_t argval;
    CAN_MODE_Type mode;

    plpccan = (struct lpccandata* )  can->parent.user_data;
    RT_ASSERT(plpccan != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t) arg;
        if(argval == RT_DEVICE_FLAG_INT_RX)
        {
            CAN_IRQCmd(plpccan->id, CANINT_RIE, DISABLE);
            CAN_IRQCmd(plpccan->id, CANINT_DOIE, DISABLE);
        }
        else if(argval == RT_DEVICE_FLAG_INT_TX)
        {
            CAN_IRQCmd(plpccan->id, CANINT_TIE1, DISABLE);
            CAN_IRQCmd(plpccan->id, CANINT_TIE2, DISABLE);
            CAN_IRQCmd(plpccan->id, CANINT_TIE3, DISABLE);
        }
        else if(argval == RT_DEVICE_CAN_INT_ERR)
        {
            CAN_IRQCmd(plpccan->id, CANINT_EIE, DISABLE);
        }
        break;

    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t) arg;
        if(argval == RT_DEVICE_FLAG_INT_RX)
        {
            CAN_IRQCmd(plpccan->id, CANINT_RIE, ENABLE);
            CAN_IRQCmd(plpccan->id, CANINT_DOIE, ENABLE);
        }
        else if(argval == RT_DEVICE_FLAG_INT_TX)
        {
            CAN_IRQCmd(plpccan->id, CANINT_TIE1, ENABLE);
            CAN_IRQCmd(plpccan->id, CANINT_TIE2, ENABLE);
            CAN_IRQCmd(plpccan->id, CANINT_TIE3, ENABLE);
        }
        else if(argval == RT_DEVICE_CAN_INT_ERR)
        {
            CAN_IRQCmd(plpccan->id, CANINT_EIE, ENABLE);
        }
        break;

    case RT_CAN_CMD_SET_FILTER:
        return setfilter(plpccan, (struct rt_can_filter_config*) arg);

    case RT_CAN_CMD_SET_MODE:
        argval = (rt_uint32_t) arg;
        if(argval != RT_CAN_MODE_NORMAL ||
                argval != RT_CAN_MODE_LISEN)
        {
            return RT_ERROR;
        }
        if(argval != can->config.mode)
        {
            can->config.mode = argval;
            switch(argval)
            {
            case RT_CAN_MODE_NORMAL:
                mode = CAN_OPERATING_MODE;
                break;
            case RT_CAN_MODE_LISEN:
                mode = CAN_LISTENONLY_MODE;
                break;
            case RT_CAN_MODE_LOOPBACKANLISEN:
                mode = CAN_SELFTEST_MODE;
                break;
            default:
                return RT_EIO;
            }
            CAN_ModeConfig(plpccan->id, mode, ENABLE);
            if(mode == CAN_SELFTEST_MODE)
            {
                //CAN_ModeConfig(CAN_1, CAN_TEST_MODE, ENABLE);
                CAN_SetAFMode(CAN_ACC_BP);
            }
        }
        break;

    case RT_CAN_CMD_SET_BAUD:
        argval = (rt_uint32_t) arg;
        if(argval != can->config.baud_rate)
        {
            can->config.baud_rate = argval;
            return lpccan_baud_set(plpccan->id, (rt_uint32_t) arg);
        }
        break;

    case RT_CAN_CMD_SET_PRIV:
        argval = (rt_uint32_t) arg;
        if(argval != RT_CAN_MODE_PRIV ||
                argval != RT_CAN_MODE_NOPRIV)
        {
            return RT_ERROR;
        }
        if(argval != can->config.privmode)
        {
            can->config.privmode = argval;
            CAN_ModeConfig(plpccan->id, CAN_TXPRIORITY_MODE, ENABLE);
        }
        break;

    case RT_CAN_CMD_GET_STATUS:
    {
        can->status.rcverrcnt = 0;
        can->status.snderrcnt = 0;
        can->status.errcode = 0;
        if(arg != &can->status)
        {
            rt_memcpy(arg,&can->status,sizeof(can->status));
        }
    }
    break;

    }
    return RT_EOK;
}

static int sendmsg(struct rt_can_device *can, const void* buf, rt_uint32_t boxno)
{
    struct lpccandata* plpccan;
    LPC_CAN_TypeDef* pCan;
    struct rt_can_msg* pmsg;
    rt_uint32_t SR_Mask;
    rt_uint32_t CMRMsk;

    plpccan = (struct lpccandata* )  can->parent.user_data;
    RT_ASSERT(plpccan != RT_NULL);

    pCan = lcpcan_get_reg_base(plpccan->id);
    RT_ASSERT(pCan != RT_NULL);

    pmsg = (struct rt_can_msg*) buf;

    if(boxno > 2)
    {
        return RT_ERROR;
    }

    CMRMsk = 0x01 | (0x01 << (boxno + 5));
    SR_Mask = 0x01 <<(boxno * 8 + 2);

    if(pCan->SR & SR_Mask)
    {
    	volatile unsigned int  *pTFI = (&pCan->TFI1 + 0 + 4 * boxno);
    	volatile unsigned int  *pTID = (&pCan->TFI1 + 1 + 4 * boxno);
    	volatile unsigned int  *pTDA = (&pCan->TFI1 + 2 + 4 * boxno);
    	volatile unsigned int  *pTDB = (&pCan->TFI1 + 3 + 4 * boxno);
	    rt_uint32_t data;

        /* Transmit Channel 1 is available */
        /* Write frame informations and frame data into its CANxTFI1,
         * CANxTID1, CANxTDA1, CANxTDB1 register */
        *pTFI &= ~ 0x000F0000;
        *pTFI |= (pmsg->len) << 16;
        if(pmsg->rtr == REMOTE_FRAME)
        {
            *pTFI |= (1 << 30); //set bit RTR
        }
        else
        {
            *pTFI &= ~(1 << 30);
        }

        if(pmsg->ide == EXT_ID_FORMAT)
        {
            *pTFI |= (((uint32_t)1) << 31); //set bit FF
        }
        else
        {
            *pTFI &= ~(((uint32_t)1) << 31);
        }
        if(can->config.privmode)
        {
            *pTFI &= ~0x000000FF;
            *pTFI |= pmsg->priv;
        }
        /* Write CAN ID*/
        *pTID = pmsg->id;
        /*Write first 4 data bytes*/
        data = (pmsg->data[0]) | (((pmsg->data[1]))<< 8) | ((pmsg->data[2]) << 16) | ((pmsg->data[3]) << 24);
        *pTDA = data;
        /*Write second 4 data bytes*/
        data = (pmsg->data[4]) | (((pmsg->data[5])) << 8) | ((pmsg->data[6]) << 16) | ((pmsg->data[7]) << 24);
        *pTDB = data;
        /*Write transmission request*/
        pCan->CMR = CMRMsk;
        return RT_EOK;
    }
    else
    {
        return RT_ERROR;
    }
}

static int recvmsg(struct rt_can_device *can, void* buf, rt_uint32_t boxno)
{
    struct lpccandata* plpccan;
    LPC_CAN_TypeDef* pCan;

    plpccan = (struct lpccandata* )  can->parent.user_data;
    RT_ASSERT(plpccan != RT_NULL);
    pCan = lcpcan_get_reg_base(plpccan->id);
    RT_ASSERT(pCan != RT_NULL);

    //CAN_ReceiveMsg
    //check status of Receive Buffer
    if((pCan->SR &0x00000001))
    {
	    uint32_t data;
    	struct rt_can_msg* pmsg = (struct rt_can_msg*) buf;

        /* Receive message is available */
        /* Read frame informations */
        pmsg->ide = (uint8_t)(((pCan->RFS) & 0x80000000) >> 31);
        pmsg->rtr = (uint8_t)(((pCan->RFS) & 0x40000000) >> 30);
        pmsg->len = (uint8_t)(((pCan->RFS) & 0x000F0000) >> 16);
        /* Read CAN message identifier */
        pmsg->id = pCan->RID;
        /* Read the data if received message was DATA FRAME */
        if (!pmsg->rtr)
        {
            /* Read first 4 data bytes */
            data = pCan->RDA;
            pmsg->data[0] = data & 0x000000FF;
            pmsg->data[1] = (data & 0x0000FF00) >> 8;
            pmsg->data[2] = (data & 0x00FF0000) >> 16;
            pmsg->data[3] = (data & 0xFF000000) >> 24;
            /* Read second 4 data bytes */
            if(pmsg->len > 4)
            {
                data = pCan->RDB;
                pmsg->data[4] = data & 0x000000FF;
                pmsg->data[5] = (data & 0x0000FF00) >> 8;
                pmsg->data[6] = (data & 0x00FF0000) >> 16;
                pmsg->data[7] = (data & 0xFF000000) >> 24;
            }
            pmsg->hdr = 0;
            /*release receive buffer*/
            pCan->CMR = 0x04;
        }
        else
        {
            /* Received Frame is a Remote Frame, not have data, we just receive
             * message information only */
            pCan->CMR = 0x04; /*release receive buffer*/
            return SUCCESS;
        }
    }
    else
    {
        // no receive message available
        return ERROR;
    }
    return RT_EOK;
}

static const struct rt_can_ops canops =
{
    configure,
    control,
    sendmsg,
    recvmsg,
};

#ifdef RT_USING_LPCCAN1
#ifdef RT_CAN_USING_LED
#endif
static struct lpccandata lpccandata1 =
{
    CAN_ID_1,
};
static struct rt_can_device lpccan1;
#endif /*RT_USINGLPCCAN1*/

#ifdef RT_USING_LPCCAN2
#ifdef RT_CAN_USING_LED
#endif
static struct lpccandata lpccandata2 =
{
    CAN_ID_2,
};
static struct rt_can_device lpccan2;
#endif /*RT_USINGLPCCAN2*/

/*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/
/*********************************************************************//**
 * @brief        Event Router IRQ Handler
 * @param[in]    None
 * @return       None
 **********************************************************************/
void CAN_IRQHandler(void)
{
    rt_uint32_t IntStatus;
    rt_interrupt_enter();
#ifdef RT_USING_LPCCAN1
    IntStatus = CAN_IntGetStatus(CAN_1);
    //check receive interrupt
    if((IntStatus >> 0) & 0x01)
    {
        rt_hw_can_isr(&lpccan1,RT_CAN_EVENT_RX_IND | 0<<8);
    }
    //check Transmit Interrupt  interrupt1
    if((IntStatus >> 1) & 0x01)
    {
        rt_uint32_t state = 0;
        state = CAN_GetCTRLStatus(CAN_1, CANCTRL_STS);
        if(state & (0x01 << 3))
        {
            rt_hw_can_isr(&lpccan1,RT_CAN_EVENT_TX_DONE | 0<<8);
        }
        else
        {
            rt_hw_can_isr(&lpccan1,RT_CAN_EVENT_TX_FAIL | 0<<8);
        }
    }
    //check Error Warning Interrupt
    if((IntStatus >> 2) & 0x01)
    {
        rt_uint32_t errtype;
        rt_uint32_t state;

        errtype = (IntStatus >> 16);
        if(errtype & 0x1F && lpccan1.status.lasterrtype == (errtype & 0x1F))
        {
            switch((errtype & 0x1F))
            {
            case 00011: // Start of Frame
            case 00010: // ID28 ... ID21
            case 00110: //ID20 ... ID18
            case 00100: // SRTR Bit
            case 00101: // IDE bit
            case 00111: // ID17 ... 13
            case 01111: // ID12 ... ID5
            case 01110: // ID4 ... ID0
            case 01100: // RTR Bit
            case 01011: // Data Length Code
            case 01010: // Data Field
                lpccan1.status.formaterrcnt++;
                break;
            case 01101: // Reserved Bit 1
            case 01001: // Reserved Bit 0
                lpccan1.status.bitpaderrcnt++;
                break;
            case 01000: // CRC Sequence
            case 11000: // CRC Delimiter
                lpccan1.status.crcerrcnt++;
                break;
            case 11001: // Acknowledge Slot
            case 11011: // Acknowledge Delimiter
                lpccan1.status.ackerrcnt++;
                break;
            case 11010: // End of Frame
            case 10010: // Intermission
                lpccan1.status.formaterrcnt++;
                break;
            }
            lpccan1.status.lasterrtype = errtype & 0x1F;
        }

        state = CAN_GetCTRLStatus(CAN_1, CANCTRL_GLOBAL_STS);
        lpccan1.status.rcverrcnt = (state >> 16) & 0xFF;
        lpccan1.status.snderrcnt = (state >> 24) & 0xFF;
        lpccan1.status.errcode = (state >> 5) & 0x06;
    }
    //check Data Overrun Interrupt Interrupt
    if((IntStatus >> 3) & 0x01)
    {
        rt_hw_can_isr(&lpccan1,RT_CAN_EVENT_RXOF_IND | 0<<8);
    }
    //check Transmit Interrupt  interrupt2
    if((IntStatus >> 9) & 0x01)
    {
        rt_uint32_t state = 0;
        state = CAN_GetCTRLStatus(CAN_1, CANCTRL_STS);
        if(state & (0x01 << 11))
        {
            rt_hw_can_isr(&lpccan1,RT_CAN_EVENT_TX_DONE | 1<<8);
        }
        else
        {
            rt_hw_can_isr(&lpccan1,RT_CAN_EVENT_TX_FAIL | 1<<8);
        }
    }
    //check Transmit Interrupt  interrupt3
    if((IntStatus >> 10) & 0x01)
    {
        rt_uint32_t state = 0;
        state = CAN_GetCTRLStatus(CAN_1, CANCTRL_STS);
        if(state & (0x01 << 19))
        {
            rt_hw_can_isr(&lpccan1,RT_CAN_EVENT_TX_DONE | 2<<8);
        }
        else
        {
            rt_hw_can_isr(&lpccan1,RT_CAN_EVENT_TX_FAIL | 2<<8);
        }
    }
#endif /*RT_USING_LPCCAN1*/

#ifdef RT_USING_LPCCAN2
    IntStatus = CAN_IntGetStatus(CAN_2);
    //check receive interrupt
    if((IntStatus >> 0) & 0x01)
    {
        rt_hw_can_isr(&lpccan2,RT_CAN_EVENT_RX_IND | 0<<8);
    }
    //check Transmit Interrupt  interrupt1
    if((IntStatus >> 1) & 0x01)
    {
        rt_uint32_t state = 0;
        state = CAN_GetCTRLStatus(CAN_2, CANCTRL_STS);
        if(state & (0x01 << 3))
        {
            rt_hw_can_isr(&lpccan1,RT_CAN_EVENT_TX_DONE | 0<<8);
        }
        else
        {
            rt_hw_can_isr(&lpccan1,RT_CAN_EVENT_TX_FAIL | 0<<8);
        }
    }

    //check Error Warning Interrupt
    if((IntStatus >> 2) & 0x01)
    {
        rt_uint32_t errtype;
        errtype = (IntStatus >> 16);
        if(errtype & 0x1F && lpccan2.status.lasterrtype == (errtype & 0x1F))
        {
            switch((errtype & 0x1F))
            {
            case 00011: // Start of Frame
            case 00010: // ID28 ... ID21
            case 00110: //ID20 ... ID18
            case 00100: // SRTR Bit
            case 00101: // IDE bit
            case 00111: // ID17 ... 13
            case 01111: // ID12 ... ID5
            case 01110: // ID4 ... ID0
            case 01100: // RTR Bit
            case 01011: // Data Length Code
            case 01010: // Data Field
                lpccan2.status.formaterrcnt++;
                break;
            case 01101: // Reserved Bit 1
            case 01001: // Reserved Bit 0
                lpccan2.status.bitpaderrcnt++;
                break;
            case 01000: // CRC Sequence
            case 11000: // CRC Delimiter
                lpccan2.status.crcerrcnt++;
                break;
            case 11001: // Acknowledge Slot
            case 11011: // Acknowledge Delimiter
                lpccan2.status.ackerrcnt++;
                break;
            case 11010: // End of Frame
            case 10010: // Intermission
                lpccan2.status.formaterrcnt++;
                break;
            }
            lpccan2.status.lasterrtype = errtype & 0x1F;
        }
        rt_uint32_t state = 0;
        state = CAN_GetCTRLStatus(CAN_2, CANCTRL_GLOBAL_STS);
        lpccan2.status.rcverrcnt = (state >> 16) & 0xFF;
        lpccan2.status.snderrcnt = (state >> 24) & 0xFF;
        lpccan2.status.errcode = (state >> 5) & 0x06;
    }

    //check Data Overrun Interrupt Interrupt
    if((IntStatus >> 3) & 0x01)
    {
        rt_hw_can_isr(&lpccan1,RT_CAN_EVENT_RXOF_IND | 0<<8);
    }

    //check Transmit Interrupt  interrupt2
    if((IntStatus >> 9) & 0x01)
    {
        rt_uint32_t state = 0;
        state = CAN_GetCTRLStatus(CAN_2, CANCTRL_STS);
        if(state & (0x01 << 11))
        {
            rt_hw_can_isr(&lpccan1,RT_CAN_EVENT_TX_DONE | 1<<8);
        }
        else
        {
            rt_hw_can_isr(&lpccan1,RT_CAN_EVENT_TX_FAIL | 1<<8);
        }
    }

    //check Transmit Interrupt  interrupt3
    if((IntStatus >> 10) & 0x01)
    {
        rt_uint32_t state = 0;
        state = CAN_GetCTRLStatus(CAN_2, CANCTRL_STS);
        if(state & (0x01 << 19))
        {
            rt_hw_can_isr(&lpccan1,RT_CAN_EVENT_TX_DONE | 2<<8);
        }
        else
        {
            rt_hw_can_isr(&lpccan1,RT_CAN_EVENT_TX_FAIL | 2<<8);
        }
    }
#endif /*RT_USING_LPCCAN2*/
    rt_interrupt_leave();
}

int lpc_can_init(void)
{
#ifdef RT_USING_LPCCAN1
    lpccan1.config.baud_rate=CAN1MBaud;
    lpccan1.config.msgboxsz=16;
    lpccan1.config.sndboxnumber=3;
    lpccan1.config.mode=RT_CAN_MODE_NORMAL;
    lpccan1.config.privmode=0;

#ifdef RT_CAN_USING_LED
#endif

    lpccan1.config.ticks = 50;

#ifdef RT_CAN_USING_HDR
#endif

    //Enable CAN Interrupt
    NVIC_EnableIRQ(CAN_IRQn);
    rt_hw_can_register(&lpccan1, "lpccan1", &canops, &lpccandata1);
#endif /*RT_USING_LPCCAN1*/

#ifdef RT_USING_LPCCAN2
    lpccan2.config.baud_rate=CAN1MBaud;
    lpccan2.config.msgboxsz=16;
    lpccan2.config.sndboxnumber=3;
    lpccan2.config.mode=RT_CAN_MODE_NORMAL;
    lpccan2.config.privmode=0;

#ifdef RT_CAN_USING_LED
#endif

    lpccan2.config.ticks = 50;

#ifdef RT_CAN_USING_HDR
#endif

    //Enable CAN Interrupt
    NVIC_EnableIRQ(CAN_IRQn);

#ifdef RT_CAN_USING_HDR
#endif

    rt_hw_can_register(&lpccan2, "lpccan2", &canops, &lpccandata2);
#endif /*RT_USING_LPCCAN2*/

    return RT_EOK;
}
INIT_BOARD_EXPORT(lpc_can_init);

#endif /*RT_USING_CAN*/
