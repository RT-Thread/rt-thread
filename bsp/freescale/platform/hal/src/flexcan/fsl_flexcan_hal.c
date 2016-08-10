/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "fsl_flexcan_hal.h"
#if FSL_FEATURE_SOC_FLEXCAN_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATAB_RTR_SHIFT  (31U)          /*!< FlexCAN RX FIFO ID filter*/
                                                                     /*! format A&B RTR mask.*/
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATAB_IDE_SHIFT  (30U)          /*!< FlexCAN RX FIFO ID filter*/
                                                                     /*! format A&B IDE mask.*/
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_RTR_SHIFT  (15U)           /*!< FlexCAN RX FIFO ID filter*/
                                                                     /*! format B RTR-2 mask.*/
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_IDE_SHIFT  (14U)           /*!< FlexCAN RX FIFO ID filter*/
                                                                     /*! format B IDE-2 mask.*/
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATA_EXT_MASK    (0x3FFFFFFFU)  /*!< FlexCAN RX FIFO ID filter*/
                                                                     /*! format A extended mask.*/
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATA_EXT_SHIFT   (1U)           /*!< FlexCAN RX FIFO ID filter*/
                                                                     /*! format A extended shift.*/
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATA_STD_MASK    (0x3FF80000U)  /*!< FlexCAN RX FIFO ID filter*/
                                                                     /*! format A standard mask.*/
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATA_STD_SHIFT   (19U)          /*!< FlexCAN RX FIFO ID filter*/
                                                                     /*! format A standard shift.*/
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_EXT_MASK    (0x3FFFU)      /*!< FlexCAN RX FIFO ID filter*/
                                                                     /*! format B extended mask.*/
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_EXT_SHIFT1  (16U)          /*!< FlexCAN RX FIFO ID filter*/
                                                                     /*! format B extended mask.*/
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_EXT_SHIFT2  (0U)           /*!< FlexCAN RX FIFO ID filter*/
                                                                     /*! format B extended mask.*/
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_STD_MASK    (0x7FFU)      /*!< FlexCAN RX FIFO ID filter*/
                                                                     /*! format B standard mask.*/
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_STD_SHIFT1  (19U)          /*!< FlexCAN RX FIFO ID filter*/
                                                                     /*! format B standard shift1.*/
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_STD_SHIFT2  (3U)           /*!< FlexCAN RX FIFO ID filter*/
                                                                     /*! format B standard shift2.*/
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATC_MASK        (0xFFU)        /*!< FlexCAN RX FIFO ID filter*/
                                                                     /*! format C mask.*/
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATC_SHIFT1      (24U)          /*!< FlexCAN RX FIFO ID filter*/
                                                                     /*! format C shift1.*/
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATC_SHIFT2      (16U)          /*!< FlexCAN RX FIFO ID filter*/
                                                                     /*! format C shift2.*/
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATC_SHIFT3      (8U)           /*!< FlexCAN RX FIFO ID filter*/
                                                                     /*! format C shift3.*/
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATC_SHIFT4      (0U)           /*!< FlexCAN RX FIFO ID filter*/
                                                                     /*! format C shift4.*/
#define FLEXCAN_ALL_INT                               (0x0007U)      /*!< Masks for wakeup, error, bus off*/
                                                                     /*! interrupts*/
#define FLEXCAN_BYTE_DATA_FIELD_MASK                  (0xFFU)        /*!< Masks for byte data field.*/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_Enable
 * Description   : Enable FlexCAN module.
 * This function will enable FlexCAN module.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_HAL_Enable(CAN_Type * base)
{
    /* Check for low power mode*/
    if(CAN_BRD_MCR_LPMACK(base))
    {
        /* Enable clock*/
        CAN_CLR_MCR(base, CAN_MCR_MDIS_MASK);
        /* Wait until enabled*/
        while (CAN_BRD_MCR_LPMACK(base)){}
    }

    return kStatus_FLEXCAN_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_Disable
 * Description   : Disable FlexCAN module.
 * This function will disable FlexCAN module.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_HAL_Disable(CAN_Type * base)
{
    /* To access the memory mapped registers*/
    /* Entre disable mode (hard reset).*/
    if(CAN_BRD_MCR_MDIS(base) == 0x0)
    {
        /* Clock disable (module)*/
        CAN_BWR_MCR_MDIS(base, 0x1);

        /* Wait until disable mode acknowledged*/
        while (!(CAN_BRD_MCR_LPMACK(base))){}
    }

    return kStatus_FLEXCAN_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_SelectClock
 * Description   : Select FlexCAN clock source.
 * This function will select either internal bus clock or external clock as
 * FlexCAN clock source.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_HAL_SelectClock(
    CAN_Type * base,
    flexcan_clk_source_t clk)
{
    CAN_BWR_CTRL1_CLKSRC(base, clk);
    return kStatus_FLEXCAN_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_Init
 * Description   : Initialize FlexCAN module.
 * This function will reset FlexCAN module, set maximum number of message
 * buffers, initialize all message buffers as inactive, enable RX FIFO
 * if needed, mask all mask bits, and disable all MB interrupts.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_HAL_Init(CAN_Type * base)
{
    /* Reset the FLEXCAN*/
    CAN_BWR_MCR_SOFTRST(base, 0x1);

    /* Wait for reset cycle to complete*/
    while (CAN_BRD_MCR_SOFTRST(base)){}

    /* Set Freeze, Halt*/
    FLEXCAN_HAL_EnterFreezeMode(base);

    /* Rx global mask*/
    CAN_WR_RXMGMASK(base, CAN_ID_EXT(CAN_RXMGMASK_MG_MASK));

    /* Rx reg 14 mask*/
    CAN_WR_RX14MASK(base, CAN_ID_EXT(CAN_RX14MASK_RX14M_MASK));

    /* Rx reg 15 mask*/
    CAN_WR_RX15MASK(base, CAN_ID_EXT(CAN_RX15MASK_RX15M_MASK));

    /* De-assert Freeze Mode*/
    FLEXCAN_HAL_ExitFreezeMode(base);

    /* Disable all MB interrupts*/
    CAN_WR_IMASK1(base, 0x0);

    return kStatus_FLEXCAN_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_SetTimeSegments
 * Description   : Set FlexCAN time segments.
 * This function will set all FlexCAN time segments which define the length of
 * Propagation Segment in the bit time, the length of Phase Buffer Segment 2 in
 * the bit time, the length of Phase Buffer Segment 1 in the bit time, the ratio
 * between the PE clock frequency and the Serial Clock (Sclock) frequency, and
 * the maximum number of time quanta that a bit time can be changed by one
 * resynchronization. (One time quantum is equal to the Sclock period.)
 *
 *END**************************************************************************/
void FLEXCAN_HAL_SetTimeSegments(
    CAN_Type * base,
    flexcan_time_segment_t *timeSeg)
{
    /* Set Freeze mode*/
    FLEXCAN_HAL_EnterFreezeMode(base);
    /* Set FlexCAN time segments*/
    CAN_CLR_CTRL1(base, (CAN_CTRL1_PROPSEG_MASK | CAN_CTRL1_PSEG2_MASK |
                                CAN_CTRL1_PSEG1_MASK | CAN_CTRL1_PRESDIV_MASK) |
                                CAN_CTRL1_RJW_MASK);
    CAN_SET_CTRL1(base, (CAN_CTRL1_PROPSEG(timeSeg->propSeg) |
                                CAN_CTRL1_PSEG2(timeSeg->phaseSeg2) |
                                CAN_CTRL1_PSEG1(timeSeg->phaseSeg1) |
                                CAN_CTRL1_PRESDIV(timeSeg->preDivider) |
                                CAN_CTRL1_RJW(timeSeg->rJumpwidth)));

    /* De-assert Freeze mode*/
     FLEXCAN_HAL_ExitFreezeMode(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_GetTimeSegments
 * Description   : Get FlexCAN time segments.
 * This function will get all FlexCAN time segments defined.
 *
 *END**************************************************************************/
void FLEXCAN_HAL_GetTimeSegments(
    CAN_Type * base,
    flexcan_time_segment_t *timeSeg)
{
    timeSeg->preDivider = CAN_BRD_CTRL1_PRESDIV(base);
    timeSeg->propSeg = CAN_BRD_CTRL1_PROPSEG(base);
    timeSeg->phaseSeg1 = CAN_BRD_CTRL1_PSEG1(base);
    timeSeg->phaseSeg2 = CAN_BRD_CTRL1_PSEG2(base);
    timeSeg->rJumpwidth = CAN_BRD_CTRL1_RJW(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_SetTxMsgBuff
 * Description   : Configure a message buffer for transmission.
 * This function will first check if RX FIFO is enabled. If RX FIFO is enabled,
 * the function will make sure if the MB requested is not occupied by RX FIFO
 * and ID filter table. Then this function will copy user's buffer into the
 * message buffer data area and configure the message buffer as required for
 * transmission.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_HAL_SetTxMsgBuff(
    CAN_Type * base,
    uint32_t msgBuffIdx,
    flexcan_msgbuff_code_status_t *cs,
    uint32_t msgId,
    uint8_t *msgData)
{
    uint32_t i;
    uint32_t val1, val2 = 1, temp, temp1;
    volatile CAN_Type *flexcan_reg_ptr;

    flexcan_reg_ptr = ((CAN_Type *)base);
    if (NULL == flexcan_reg_ptr)
    {
        return kStatus_FLEXCAN_InvalidArgument;
    }

    if (msgBuffIdx >= CAN_BRD_MCR_MAXMB(base))
    {
        return kStatus_FLEXCAN_OutOfRange;
    }

    /* Check if RX FIFO is enabled*/
    if (CAN_BRD_MCR_RFEN(base))
    {
        /* Get the number of RX FIFO Filters*/
        val1 = (CAN_BRD_CTRL2_RFFN(base));
        /* Get the number if MBs occupied by RX FIFO and ID filter table*/
        /* the Rx FIFO occupies the memory space originally reserved for MB0-5*/
        /* Every number of RFFN means 8 number of RX FIFO filters*/
        /* and every 4 number of RX FIFO filters occupied one MB*/
        val2 = RxFifoOcuppiedLastMsgBuff(val1);

        if (msgBuffIdx <= val2)
        {
            return kStatus_FLEXCAN_InvalidArgument;
        }
    }

    /* Copy user's buffer into the message buffer data area*/
    if (msgData != NULL)
    {
        flexcan_reg_ptr->MB[msgBuffIdx].WORD0 = 0x0;
        flexcan_reg_ptr->MB[msgBuffIdx].WORD1 = 0x0;

        for (i = 0; i < cs->dataLen; i++ )
        {
            temp1 = (*(msgData + i));
            if (i < 4)
            {
                temp = temp1 << ((3 - i) * 8);
                flexcan_reg_ptr->MB[msgBuffIdx].WORD0 |= temp;
            }
            else
            {
                temp = temp1 << ((7 - i) * 8);
                flexcan_reg_ptr->MB[msgBuffIdx].WORD1 |= temp;
            }
        }
    }

    /* Set the ID according the format structure*/
    if (cs->msgIdType == kFlexCanMsgIdExt)
    {
        /* ID [28-0]*/
        flexcan_reg_ptr->MB[msgBuffIdx].ID &= ~(CAN_ID_STD_MASK | CAN_ID_EXT_MASK);
        flexcan_reg_ptr->MB[msgBuffIdx].ID |= (msgId & (CAN_ID_STD_MASK | CAN_ID_EXT_MASK));

        /* Set IDE*/
        flexcan_reg_ptr->MB[msgBuffIdx].CS |= CAN_CS_IDE_MASK;

        /* Clear SRR bit*/
        flexcan_reg_ptr->MB[msgBuffIdx].CS &= ~CAN_CS_SRR_MASK;

        /* Set the length of data in bytes*/
        flexcan_reg_ptr->MB[msgBuffIdx].CS &= ~CAN_CS_DLC_MASK;
        flexcan_reg_ptr->MB[msgBuffIdx].CS |= CAN_CS_DLC(cs->dataLen);

        /* Set MB CODE*/
        /* Reset the code*/
        if (cs->code != kFlexCanTXNotUsed)
        {
            if (cs->code == kFlexCanTXRemote)
            {
                /* Set RTR bit*/
                flexcan_reg_ptr->MB[msgBuffIdx].CS |= CAN_CS_RTR_MASK;
                cs->code = kFlexCanTXData;
            }

            /* Reset the code*/
            flexcan_reg_ptr->MB[msgBuffIdx].CS &= ~(CAN_CS_CODE_MASK);

            /* Activating message buffer*/
            flexcan_reg_ptr->MB[msgBuffIdx].CS |= CAN_CS_CODE(cs->code);
        }
    }
    else if(cs->msgIdType == kFlexCanMsgIdStd)
    {
        /* ID[28-18]*/
        flexcan_reg_ptr->MB[msgBuffIdx].ID &= ~CAN_ID_STD_MASK;
        flexcan_reg_ptr->MB[msgBuffIdx].ID |= CAN_ID_STD(msgId);

        /* make sure IDE and SRR are not set*/
        flexcan_reg_ptr->MB[msgBuffIdx].CS &= ~(CAN_CS_IDE_MASK | CAN_CS_SRR_MASK);

        /* Set the length of data in bytes*/
        flexcan_reg_ptr->MB[msgBuffIdx].CS &= ~CAN_CS_DLC_MASK;
        flexcan_reg_ptr->MB[msgBuffIdx].CS |= (cs->dataLen) << CAN_CS_DLC_SHIFT;

        /* Set MB CODE*/
        if (cs->code != kFlexCanTXNotUsed)
        {
            if (cs->code == kFlexCanTXRemote)
            {
                /* Set RTR bit*/
                flexcan_reg_ptr->MB[msgBuffIdx].CS |= CAN_CS_RTR_MASK;
                cs->code = kFlexCanTXData;
            }

            /* Reset the code*/
            flexcan_reg_ptr->MB[msgBuffIdx].CS &= ~CAN_CS_CODE_MASK;

            /* Set the code*/
            flexcan_reg_ptr->MB[msgBuffIdx].CS |= CAN_CS_CODE(cs->code);
        }
    }
    else
    {
        return kStatus_FLEXCAN_InvalidArgument;
    }

    return kStatus_FLEXCAN_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_SetMbRx
 * Description   : Configure a message buffer for receiving.
 * This function will first check if RX FIFO is enabled. If RX FIFO is enabled,
 * the function will make sure if the MB requested is not occupied by RX FIFO
 * and ID filter table. Then this function will configure the message buffer as
 * required for receiving.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_HAL_SetRxMsgBuff(
    CAN_Type * base,
    uint32_t msgBuffIdx,
    flexcan_msgbuff_code_status_t *cs,
    uint32_t msgId)
{
    uint32_t val1, val2 = 1;
    volatile CAN_Type *flexcan_reg_ptr;

    flexcan_reg_ptr = ((CAN_Type *)base);
    if (NULL == flexcan_reg_ptr)
    {
        return kStatus_FLEXCAN_InvalidArgument;
    }

    if (msgBuffIdx >= CAN_BRD_MCR_MAXMB(base))
    {
        return kStatus_FLEXCAN_OutOfRange;
    }

    /* Check if RX FIFO is enabled*/
    if (CAN_BRD_MCR_RFEN(base))
    {
        /* Get the number of RX FIFO Filters*/
        val1 = CAN_BRD_CTRL2_RFFN(base);
        /* Get the number if MBs occupied by RX FIFO and ID filter table*/
        /* the Rx FIFO occupies the memory space originally reserved for MB0-5*/
        /* Every number of RFFN means 8 number of RX FIFO filters*/
        /* and every 4 number of RX FIFO filters occupied one MB*/
        val2 = RxFifoOcuppiedLastMsgBuff(val1);

        if (msgBuffIdx <= val2)
        {
            return kStatus_FLEXCAN_InvalidArgument;
        }
    }

    /* Set the ID according the format structure*/
    if (cs->msgIdType == kFlexCanMsgIdExt)
    {
        /* Set IDE*/
        flexcan_reg_ptr->MB[msgBuffIdx].CS |= CAN_CS_IDE_MASK;

        /* Clear SRR bit*/
        flexcan_reg_ptr->MB[msgBuffIdx].CS &= ~CAN_CS_SRR_MASK;

        /* Set the length of data in bytes*/
        flexcan_reg_ptr->MB[msgBuffIdx].CS &= ~CAN_CS_DLC_MASK;
        flexcan_reg_ptr->MB[msgBuffIdx].CS |= CAN_CS_DLC(cs->dataLen);

        /* ID [28-0]*/
        flexcan_reg_ptr->MB[msgBuffIdx].ID &= ~(CAN_ID_STD_MASK | CAN_ID_EXT_MASK);
        flexcan_reg_ptr->MB[msgBuffIdx].ID |= (msgId & (CAN_ID_STD_MASK | CAN_ID_EXT_MASK));

        /* Set MB CODE*/
        if (cs->code != kFlexCanRXNotUsed)
        {
            flexcan_reg_ptr->MB[msgBuffIdx].CS &= ~CAN_CS_CODE_MASK;
            flexcan_reg_ptr->MB[msgBuffIdx].CS |= CAN_CS_CODE(cs->code);
        }
    }
    else if(cs->msgIdType == kFlexCanMsgIdStd)
    {
        /* Make sure IDE and SRR are not set*/
        flexcan_reg_ptr->MB[msgBuffIdx].CS &= ~(CAN_CS_IDE_MASK | CAN_CS_SRR_MASK);

        /* Set the length of data in bytes*/
        flexcan_reg_ptr->MB[msgBuffIdx].CS &= ~CAN_CS_DLC_MASK;
        flexcan_reg_ptr->MB[msgBuffIdx].CS |= (cs->dataLen) << CAN_CS_DLC_SHIFT;

        /* ID[28-18]*/
        flexcan_reg_ptr->MB[msgBuffIdx].ID &= ~CAN_ID_STD_MASK;
        flexcan_reg_ptr->MB[msgBuffIdx].ID |= CAN_ID_STD(msgId);

        /* Set MB CODE*/
        if (cs->code != kFlexCanRXNotUsed)
        {
            flexcan_reg_ptr->MB[msgBuffIdx].CS &= ~CAN_CS_CODE_MASK;
            flexcan_reg_ptr->MB[msgBuffIdx].CS |= CAN_CS_CODE(cs->code);
        }
    }
    else
    {
        return kStatus_FLEXCAN_InvalidArgument;
    }

    return kStatus_FLEXCAN_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_GetMsgBuff
 * Description   : Get a message buffer field values.
 * This function will first check if RX FIFO is enabled. If RX FIFO is enabled,
 * the function will make sure if the MB requested is not occupied by RX FIFO
 * and ID filter table. Then this function will get the message buffer field
 * values and copy the MB data field into user's buffer.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_HAL_GetMsgBuff(
    CAN_Type * base,
    uint32_t msgBuffIdx,
    flexcan_msgbuff_t *msgBuff)
{
    uint32_t i;
    uint32_t val1, val2 = 1;
    volatile CAN_Type *flexcan_reg_ptr;

    flexcan_reg_ptr = ((CAN_Type *)base);
    if (NULL == flexcan_reg_ptr)
    {
        return kStatus_FLEXCAN_InvalidArgument;
    }

    if (msgBuffIdx >= CAN_BRD_MCR_MAXMB(base))
    {
        return kStatus_FLEXCAN_OutOfRange;
    }

    /* Check if RX FIFO is enabled*/
    if (CAN_BRD_MCR_RFEN(base))
    {
        /* Get the number of RX FIFO Filters*/
        val1 = CAN_BRD_CTRL2_RFFN(base);
        /* Get the number if MBs occupied by RX FIFO and ID filter table*/
        /* the Rx FIFO occupies the memory space originally reserved for MB0-5*/
        /* Every number of RFFN means 8 number of RX FIFO filters*/
        /* and every 4 number of RX FIFO filters occupied one MB*/
        val2 = RxFifoOcuppiedLastMsgBuff(val1);

        if (msgBuffIdx <= val2)
        {
            return kStatus_FLEXCAN_InvalidArgument;
        }
    }

    /* Get a MB field values*/
    msgBuff->cs = flexcan_reg_ptr->MB[msgBuffIdx].CS;
    if ((msgBuff->cs) & CAN_CS_IDE_MASK)
    {
        msgBuff->msgId = flexcan_reg_ptr->MB[msgBuffIdx].ID;
    }
    else
    {
        msgBuff->msgId = (flexcan_reg_ptr->MB[msgBuffIdx].ID) >> CAN_ID_STD_SHIFT;
    }

    /* Copy MB data field into user's buffer*/
    for (i = 0 ; i < kFlexCanMessageSize ; i++)
    {
        if (i < 4)
        {
            msgBuff->data[3 - i] = ((flexcan_reg_ptr->MB[msgBuffIdx].WORD0) >> (i * 8)) &
                              FLEXCAN_BYTE_DATA_FIELD_MASK;
        }
        else
        {
            msgBuff->data[11 - i] = ((flexcan_reg_ptr->MB[msgBuffIdx].WORD1) >> ((i - 4) * 8)) &
                               FLEXCAN_BYTE_DATA_FIELD_MASK;
        }
    }

    return kStatus_FLEXCAN_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_LockRxMsgBuff
 * Description   : Lock the RX message buffer.
 * This function will the RX message buffer.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_HAL_LockRxMsgBuff(
    CAN_Type * base,
    uint32_t msgBuffIdx)
{
    volatile CAN_Type *flexcan_reg_ptr;
    uint32_t tmp = 1;

    flexcan_reg_ptr = ((CAN_Type *)base);
    if (NULL == flexcan_reg_ptr)
    {
        return (kStatus_FLEXCAN_InvalidArgument);
    }

    if (msgBuffIdx >= CAN_BRD_MCR_MAXMB(base))
    {
        return (kStatus_FLEXCAN_OutOfRange);
    }

    /* Lock the mailbox*/
		if(tmp)
		{
        tmp = flexcan_reg_ptr->MB[msgBuffIdx].CS;
		}

    return kStatus_FLEXCAN_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_EnableRxFifo
 * Description   : Enable Rx FIFO feature.
 * This function will enable the Rx FIFO feature.
 *
 *END**************************************************************************/
void FLEXCAN_HAL_EnableRxFifo(CAN_Type * base, uint32_t numOfFilters)
{
    uint32_t i;
    uint32_t maxNumMb;
    /* Set Freeze mode*/
    FLEXCAN_HAL_EnterFreezeMode(base);
    /* Enable RX FIFO*/
    CAN_BWR_MCR_RFEN(base, 0x1);
    /* Set the number of the RX FIFO filters needed*/
    CAN_BWR_CTRL2_RFFN(base, numOfFilters);
    /* RX FIFO global mask*/
    CAN_WR_RXFGMASK(base, CAN_ID_EXT(CAN_RXFGMASK_FGM_MASK));
    maxNumMb = CAN_BRD_MCR_MAXMB(base);
    for (i = 0; i < maxNumMb; i++)
    {
        /* RX individual mask*/
        CAN_WR_RXIMR(base, i, CAN_ID_EXT(CAN_RXIMR_MI_MASK));
    }

    /* De-assert Freeze Mode*/
    FLEXCAN_HAL_ExitFreezeMode(base);

}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_DisableRxFifo
 * Description   : Disable Rx FIFO feature.
 * This function will disable the Rx FIFO feature.
 *
 *END**************************************************************************/
void FLEXCAN_HAL_DisableRxFifo(CAN_Type * base)
{
    /* Set Freeze mode*/
    FLEXCAN_HAL_EnterFreezeMode(base);
    /* Disable RX FIFO*/
    CAN_BWR_MCR_RFEN(base, 0x0);

    /* De-assert Freeze Mode*/
    FLEXCAN_HAL_ExitFreezeMode(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_SetRxFifoFilterNum
 * Description   : Set the number of Rx FIFO filters.
 * This function will define the number of Rx FIFO filters.
 *
 *END**************************************************************************/
void FLEXCAN_HAL_SetRxFifoFilterNum(
    CAN_Type * base,
    uint32_t number)
{
    /* Set Freeze mode*/
    FLEXCAN_HAL_EnterFreezeMode(base);

    /* Set the number of RX FIFO ID filters*/
    CAN_BWR_CTRL2_RFFN(base, number);

    /* De-assert Freeze Mode*/
    FLEXCAN_HAL_ExitFreezeMode(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_SetMaxMsgBuffNum
 * Description   : Set the number of the last Message Buffers.
 * This function will define the number of the last Message Buffers
 *
*END**************************************************************************/
void FLEXCAN_HAL_SetMaxMsgBuffNum(
    CAN_Type * base,
    uint32_t maxMsgBuffNum)
{
    uint32_t i;
    volatile CAN_Type *flexcan_reg_ptr;

    flexcan_reg_ptr = ((CAN_Type *)base);

    /* Set Freeze mode*/
    FLEXCAN_HAL_EnterFreezeMode(base);
    /* Set the maximum number of MBs*/
    CAN_BWR_MCR_MAXMB(base, maxMsgBuffNum);

    /* Initialize all message buffers as inactive*/
    for (i = 0; i < maxMsgBuffNum; i++)
    {
        flexcan_reg_ptr->MB[i].CS = 0x0;
        flexcan_reg_ptr->MB[i].ID = 0x0;
        flexcan_reg_ptr->MB[i].WORD0 = 0x0;
        flexcan_reg_ptr->MB[i].WORD1 = 0x0;
    }

    /* De-assert Freeze Mode*/
    FLEXCAN_HAL_ExitFreezeMode(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_SetRxFifoFilter
 * Description   : Confgure RX FIFO ID filter table elements.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_HAL_SetRxFifoFilter(
    CAN_Type * base,
    flexcan_rx_fifo_id_element_format_t idFormat,
    flexcan_id_table_t *idFilterTable)
{
    /* Set RX FIFO ID filter table elements*/
uint32_t i, j, numOfFilters;
    uint32_t val1 = 0, val2 = 0, val = 0;
    volatile CAN_Type  *flexcan_reg_ptr;
    volatile uint32_t *filterTable;
    flexcan_reg_ptr = ((CAN_Type *)base);
    if (NULL == flexcan_reg_ptr)
    {
        return kStatus_FLEXCAN_InvalidArgument;
    }

    numOfFilters = CAN_BRD_CTRL2_RFFN(base);
    filterTable = (volatile uint32_t *)&(flexcan_reg_ptr->MB[RxFifoOcuppiedFirstMsgBuff]);
    switch(idFormat)
    {
        case (kFlexCanRxFifoIdElementFormatA):
            /* One full ID (standard and extended) per ID Filter Table element.*/
            CAN_BWR_MCR_IDAM(base, kFlexCanRxFifoIdElementFormatA);
            if (idFilterTable->isRemoteFrame)
            {
                val = FlexCanRxFifoAcceptRemoteFrame << FLEXCAN_RX_FIFO_ID_FILTER_FORMATAB_RTR_SHIFT;
            }
            if (idFilterTable->isExtendedFrame)
            {
                val |= FlexCanRxFifoAcceptExtFrame << FLEXCAN_RX_FIFO_ID_FILTER_FORMATAB_IDE_SHIFT;
            }
            for (i = 0; i < RxFifoFilterElementNum(numOfFilters); i++)
            {
                if(idFilterTable->isExtendedFrame)
                {
                    filterTable[i] = val + ((*(idFilterTable->idFilter + i)) <<
                                             FLEXCAN_RX_FIFO_ID_FILTER_FORMATA_EXT_SHIFT &
                                             FLEXCAN_RX_FIFO_ID_FILTER_FORMATA_EXT_MASK);
                }else
                {
                    filterTable[i] = val + ((*(idFilterTable->idFilter + i)) <<
                                             FLEXCAN_RX_FIFO_ID_FILTER_FORMATA_STD_SHIFT &
                                             FLEXCAN_RX_FIFO_ID_FILTER_FORMATA_STD_MASK);
                }
            }
            break;
        case (kFlexCanRxFifoIdElementFormatB):
            /* Two full standard IDs or two partial 14-bit (standard and extended) IDs*/
            /* per ID Filter Table element.*/
            CAN_BWR_MCR_IDAM(base, kFlexCanRxFifoIdElementFormatB);
            if (idFilterTable->isRemoteFrame)
            {
                val1 = FlexCanRxFifoAcceptRemoteFrame << FLEXCAN_RX_FIFO_ID_FILTER_FORMATAB_RTR_SHIFT;
                val2 = FlexCanRxFifoAcceptRemoteFrame << FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_RTR_SHIFT;
            }
            if (idFilterTable->isExtendedFrame)
            {
                val1 |= FlexCanRxFifoAcceptExtFrame << FLEXCAN_RX_FIFO_ID_FILTER_FORMATAB_IDE_SHIFT;
                val2 |= FlexCanRxFifoAcceptExtFrame << FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_IDE_SHIFT;
            }
            j = 0;
            for (i = 0; i < RxFifoFilterElementNum(numOfFilters); i++)
            {
                if (idFilterTable->isExtendedFrame)
                {
                    filterTable[i] = val1 + (((*(idFilterTable->idFilter + j)) &
                                              FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_EXT_MASK) <<
                                              FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_EXT_SHIFT1);
                    filterTable[i] |= val2 + (((*(idFilterTable->idFilter + j + 1)) &
                                              FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_EXT_MASK) <<
                                              FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_EXT_SHIFT2);
                }else
                {
                    filterTable[i] = val1 + (((*(idFilterTable->idFilter + j)) &
                                              FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_STD_MASK) <<
                                              FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_STD_SHIFT1);
                    filterTable[i] |= val2 + (((*(idFilterTable->idFilter + j + 1)) &
                                              FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_STD_MASK) <<
                                              FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_STD_SHIFT2);
                }
                j = j + 2;
            }
            break;
        case (kFlexCanRxFifoIdElementFormatC):
            /* Four partial 8-bit Standard IDs per ID Filter Table element.*/
            CAN_BWR_MCR_IDAM(base, kFlexCanRxFifoIdElementFormatC);
            j = 0;
            for (i = 0; i < RxFifoFilterElementNum(numOfFilters); i++)
            {
                filterTable[i] = (((*(idFilterTable->idFilter + j)) &
                                  FLEXCAN_RX_FIFO_ID_FILTER_FORMATC_MASK) <<
                                  FLEXCAN_RX_FIFO_ID_FILTER_FORMATC_SHIFT1);
                filterTable[i] = (((*(idFilterTable->idFilter + j + 1)) &
                                  FLEXCAN_RX_FIFO_ID_FILTER_FORMATC_MASK) <<
                                  FLEXCAN_RX_FIFO_ID_FILTER_FORMATC_SHIFT2);
                filterTable[i] = (((*(idFilterTable->idFilter + j + 2)) &
                                  FLEXCAN_RX_FIFO_ID_FILTER_FORMATC_MASK) <<
                                  FLEXCAN_RX_FIFO_ID_FILTER_FORMATC_SHIFT3);
                filterTable[i] = (((*(idFilterTable->idFilter + j + 3)) &
                                  FLEXCAN_RX_FIFO_ID_FILTER_FORMATC_MASK) <<
                                  FLEXCAN_RX_FIFO_ID_FILTER_FORMATC_SHIFT4);
                j = j + 4;
            }
            break;
        case (kFlexCanRxFifoIdElementFormatD):
            /* All frames rejected.*/
            CAN_BWR_MCR_IDAM(base, kFlexCanRxFifoIdElementFormatD);
            break;
        default:
            return kStatus_FLEXCAN_InvalidArgument;
    }

    return kStatus_FLEXCAN_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_SetMsgBuffIntCmd
 * Description   : Enable/Disable the corresponding Message Buffer interrupt.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_HAL_SetMsgBuffIntCmd(
    CAN_Type * base,
    uint32_t msgBuffIdx, bool enable)
{
    uint32_t temp;

    if (msgBuffIdx >= CAN_BRD_MCR_MAXMB(base))
    {
        return kStatus_FLEXCAN_OutOfRange;
    }

    /* Enable the corresponding message buffer Interrupt*/
    temp = 0x1 << msgBuffIdx;
    if(enable)
    {
        CAN_SET_IMASK1(base, temp);
    }
    else
    {
        CAN_CLR_IMASK1(base, temp);
    }

    return kStatus_FLEXCAN_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_SetErrIntCmd
 * Description   : Enable the error interrupts.
 * This function will enable Error interrupt.
 *
 *END**************************************************************************/
void FLEXCAN_HAL_SetErrIntCmd(CAN_Type * base, flexcan_int_type_t errType, bool enable)
{
    uint32_t temp = errType;
    if(enable)
    {
        if((errType == kFlexCanIntRxwarning)||(errType == kFlexCanIntTxwarning))
        {
            CAN_BWR_MCR_WRNEN(base,0x1);
        }
        if(errType == kFlexCanIntWakeup)
        {
            CAN_BWR_MCR_WAKMSK(base,0x1);
        }
        else
        {
            CAN_SET_CTRL1(base,temp);
        }
    }
    else
    {
        if(errType == kFlexCanIntWakeup)
        {
            CAN_BWR_MCR_WAKMSK(base,0x0);
        }
        else
        {
            CAN_CLR_CTRL1(base,temp);
        }
    }
}


/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_ExitFreezeMode
 * Description   : Exit of freeze mode.
 *
 *END**************************************************************************/
void FLEXCAN_HAL_ExitFreezeMode(CAN_Type * base)
{
    CAN_BWR_MCR_HALT(base, 0x0);
    CAN_BWR_MCR_FRZ(base, 0x0);

    /* Wait till exit freeze mode*/
    while (CAN_BRD_MCR_FRZACK(base)){}
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_EnterFreezeMode
 * Description   : Enter the freeze mode.
 *
 *END**************************************************************************/
void FLEXCAN_HAL_EnterFreezeMode(CAN_Type * base)
{
    CAN_BWR_MCR_FRZ(base, 0x1);
    CAN_BWR_MCR_HALT(base, 0x1);


    /* Wait for entering the freeze mode*/
    while (!(CAN_BRD_MCR_FRZACK(base))){}
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_GetMsgBuffIntStatusFlag
 * Description   : Get the corresponding message buffer interrupt flag.
 *
 *END**************************************************************************/
uint8_t FLEXCAN_HAL_GetMsgBuffIntStatusFlag(
    CAN_Type * base,
    uint32_t msgBuffIdx)
{
    uint32_t temp;

    /* Get the corresponding message buffer interrupt flag*/
    temp = 0x1 << msgBuffIdx;
    if (CAN_RD_IFLAG1(base) & temp)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_GetErrCounter
 * Description   : Get transmit error counter and receive error counter.
 *
 *END**************************************************************************/
void FLEXCAN_HAL_GetErrCounter(
    CAN_Type * base,
    flexcan_buserr_counter_t *errCount)
{
    /* Get transmit error counter and receive error counter*/
    errCount->rxerr = CAN_RD_ECR_RXERRCNT(base);
    errCount->txerr = CAN_RD_ECR_TXERRCNT(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_ClearErrIntStatusFlag
 * Description   : Clear all error interrupt status.
 *
 *END**************************************************************************/
void FLEXCAN_HAL_ClearErrIntStatusFlag(CAN_Type * base)
{
    if(CAN_RD_ESR1(base) & FLEXCAN_ALL_INT)
    {
        CAN_WR_ESR1(base, FLEXCAN_ALL_INT);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_ReadRxFifo
 * Description   : Read Rx FIFO data.
 * This function will copy MB[0] data field into user's buffer.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_HAL_ReadRxFifo(
    CAN_Type * base,
    flexcan_msgbuff_t *rxFifo)
{
    uint32_t i;
    volatile CAN_Type  *flexcan_reg_ptr;

    flexcan_reg_ptr = ((CAN_Type *)base);
    if (NULL == flexcan_reg_ptr)
    {
        return kStatus_FLEXCAN_InvalidArgument;
    }

    rxFifo->cs = flexcan_reg_ptr->MB[0].CS;

    if ((rxFifo->cs) & CAN_CS_IDE_MASK)
    {
        rxFifo->msgId = flexcan_reg_ptr->MB[0].ID;
    }
    else
    {
        rxFifo->msgId = (flexcan_reg_ptr->MB[0].ID) >> CAN_ID_STD_SHIFT;
    }

    /* Copy MB[0] data field into user's buffer*/
    for ( i=0 ; i < kFlexCanMessageSize ; i++ )
    {
        if (i < 4)
        {
            rxFifo->data[3 - i] = ((flexcan_reg_ptr->MB[0].WORD0) >> (i * 8)) &
                                   FLEXCAN_BYTE_DATA_FIELD_MASK;
        }
        else
        {
            rxFifo->data[11 - i] = ((flexcan_reg_ptr->MB[0].WORD1) >> ((i - 4) * 8)) &
                                    FLEXCAN_BYTE_DATA_FIELD_MASK;
        }
    }

    return kStatus_FLEXCAN_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_SetMaskType
 * Description   : Set RX masking type.
 * This function will set RX masking type as RX global mask or RX individual
 * mask.
 *
 *END**************************************************************************/
void FLEXCAN_HAL_SetRxMaskType(
    CAN_Type * base,
    flexcan_rx_mask_type_t type)
{
    /* Set Freeze mode*/
    FLEXCAN_HAL_EnterFreezeMode(base);

    /* Set RX masking type (RX global mask or RX individual mask)*/
    if (type == kFlexCanRxMaskGlobal)
    {
        /* Enable Global RX masking*/
        CAN_BWR_MCR_IRMQ(base, 0x0);
    }
    else
    {
        /* Enable Individual Rx Masking and Queue*/
        CAN_BWR_MCR_IRMQ(base, 0x1);
    }

    /* De-assert Freeze Mode*/
    FLEXCAN_HAL_ExitFreezeMode(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_SetRxFifoGlobalStdMask
 * Description   : Set Rx FIFO global mask as the 11-bit standard mask.
 *
 *END**************************************************************************/
void FLEXCAN_HAL_SetRxFifoGlobalStdMask(
    CAN_Type * base,
    uint32_t stdMask)
{
    /* Set Freeze mode*/
    FLEXCAN_HAL_EnterFreezeMode(base);

    /* 11 bit standard mask*/
    CAN_WR_RXFGMASK(base, CAN_ID_STD(stdMask));

    /* De-assert Freeze Mode*/
    FLEXCAN_HAL_ExitFreezeMode(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_SetRxFifoGlobalExtMask
 * Description   : Set Rx FIFO global mask as the 29-bit extended mask.
 *
 *END**************************************************************************/
void FLEXCAN_HAL_SetRxFifoGlobalExtMask(
    CAN_Type * base,
    uint32_t extMask)
{
    /* Set Freeze mode*/
    FLEXCAN_HAL_EnterFreezeMode(base);

    /* 29-bit extended mask*/
    CAN_WR_RXFGMASK(base, CAN_ID_EXT(extMask));

    /* De-assert Freeze Mode*/
    FLEXCAN_HAL_ExitFreezeMode(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_SetRxIndividualStdMask
 * Description   : Set Rx individual mask as the 11-bit standard mask.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_HAL_SetRxIndividualStdMask(
    CAN_Type * base,
    uint32_t msgBuffIdx,
    uint32_t stdMask)
{
    if (msgBuffIdx >= CAN_BRD_MCR_MAXMB(base))
    {
        return kStatus_FLEXCAN_OutOfRange;
    }

    /* Set Freeze mode*/
    FLEXCAN_HAL_EnterFreezeMode(base);

    /* 11 bit standard mask*/
    CAN_WR_RXIMR(base, msgBuffIdx, CAN_ID_STD(stdMask));

    /* De-assert Freeze Mode*/
    FLEXCAN_HAL_ExitFreezeMode(base);

    return kStatus_FLEXCAN_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_SetRxIndividualExtMask
 * Description   : Set Rx individual mask as the 29-bit extended mask.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_HAL_SetRxIndividualExtMask(
    CAN_Type * base,
    uint32_t msgBuffIdx,
    uint32_t extMask)
{
    if (msgBuffIdx >= CAN_BRD_MCR_MAXMB(base))
    {
        return kStatus_FLEXCAN_OutOfRange;
    }

    /* Set Freeze mode*/
    FLEXCAN_HAL_EnterFreezeMode(base);

    /* 29-bit extended mask*/
    CAN_WR_RXIMR(base, msgBuffIdx, CAN_ID_EXT(extMask));

    /* De-assert Freeze Mode*/
    FLEXCAN_HAL_ExitFreezeMode(base);

    return kStatus_FLEXCAN_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_SetRxMbGlobalStdMask
 * Description   : Set Rx Message Buffer global mask as the 11-bit standard mask.
 *
 *END**************************************************************************/
void FLEXCAN_HAL_SetRxMsgBuffGlobalStdMask(
    CAN_Type * base,
    uint32_t stdMask)
{
    /* Set Freeze mode*/
    FLEXCAN_HAL_EnterFreezeMode(base);

    /* 11 bit standard mask*/
    CAN_WR_RXMGMASK(base, CAN_ID_STD(stdMask));

    /* De-assert Freeze Mode*/
    FLEXCAN_HAL_ExitFreezeMode(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_SetRxMbBuf14StdMask
 * Description   : Set Rx Message Buffer 14 mask as the 11-bit standard mask.
 *
 *END**************************************************************************/
void FLEXCAN_HAL_SetRxMsgBuff14StdMask(
    CAN_Type * base,
    uint32_t stdMask)
{
    /* Set Freeze mode*/
    FLEXCAN_HAL_EnterFreezeMode(base);

    /* 11 bit standard mask*/
    CAN_WR_RX14MASK(base, CAN_ID_STD(stdMask));

    /* De-assert Freeze Mode*/
    FLEXCAN_HAL_ExitFreezeMode(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_SetRxMbBuf15StdMask
 * Description   : Set Rx Message Buffer 15 mask as the 11-bit standard mask.
 *
 *END**************************************************************************/
void FLEXCAN_HAL_SetRxMsgBuff15StdMask(
    CAN_Type * base,
    uint32_t stdMask)
{
    /* Set Freeze mode*/
    FLEXCAN_HAL_EnterFreezeMode(base);

    /* 11 bit standard mask*/
    CAN_WR_RX15MASK(base, CAN_ID_STD(stdMask));

    /* De-assert Freeze Mode*/
    FLEXCAN_HAL_ExitFreezeMode(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_SetRxMbGlobalExtMask
 * Description   : Set Rx Message Buffer global mask as the 29-bit extended mask.
 *
 *END**************************************************************************/
void FLEXCAN_HAL_SetRxMsgBuffGlobalExtMask(
    CAN_Type * base,
    uint32_t extMask)
{
    /* Set Freeze mode*/
    FLEXCAN_HAL_EnterFreezeMode(base);

    /* 29-bit extended mask*/
    CAN_WR_RXMGMASK(base, CAN_ID_EXT(extMask));

    /* De-assert Freeze Mode*/
    FLEXCAN_HAL_ExitFreezeMode(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_SetRxMbBuf14ExtMask
 * Description   : Set Rx Message Buffer 14 mask as the 29-bit extended mask.
 *
 *END**************************************************************************/
void FLEXCAN_HAL_SetRxMsgBuff14ExtMask(
    CAN_Type * base,
    uint32_t extMask)
{
    /* Set Freeze mode*/
    FLEXCAN_HAL_EnterFreezeMode(base);

    /* 29-bit extended mask*/
    CAN_WR_RX14MASK(base, CAN_ID_EXT(extMask));

    /* De-assert Freeze Mode*/
    FLEXCAN_HAL_ExitFreezeMode(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_SetRxMbBuf15ExtMask
 * Description   : Set Rx Message Buffer 15 mask as the 29-bit extended mask.
 *
 *END**************************************************************************/
void FLEXCAN_HAL_SetRxMsgBuff15ExtMask(
    CAN_Type * base,
    uint32_t extMask)
{
    /* Set Freeze mode*/
    FLEXCAN_HAL_EnterFreezeMode(base);

    /* 29-bit extended mask*/
    CAN_WR_RX15MASK(base, CAN_ID_EXT(extMask));

    /* De-assert Freeze Mode*/
    FLEXCAN_HAL_ExitFreezeMode(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_EnableOperationMode
 * Description   : Enable a FlexCAN operation mode.
 * This function will enable one of the modes listed in flexcan_operation_modes_t.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_HAL_SetOperationMode(
    CAN_Type * base,
    flexcan_operation_modes_t mode)
{
    if (mode == kFlexCanFreezeMode)
    {
        /* Debug mode, Halt and Freeze*/
        FLEXCAN_HAL_EnterFreezeMode(base);

        return kStatus_FLEXCAN_Success;
    }
    else if (mode == kFlexCanDisableMode)
    {
        /* Debug mode, Halt and Freeze*/
        CAN_BWR_MCR_MDIS(base, 0x1);
        return kStatus_FLEXCAN_Success;
    }

    /* Set Freeze mode*/
    FLEXCAN_HAL_EnterFreezeMode(base);

    if (mode == kFlexCanNormalMode)
    {
        CAN_BWR_MCR_SUPV(base, 0x0);
    }
    else if (mode == kFlexCanListenOnlyMode)
    {
        CAN_BWR_CTRL1_LOM(base, 0x1);
    }
    else if (mode == kFlexCanLoopBackMode)
    {
        CAN_BWR_CTRL1_LPB(base, 0x1);
    }
    else
    {
        return kStatus_FLEXCAN_InvalidArgument;
    }

    /* De-assert Freeze Mode*/
    FLEXCAN_HAL_ExitFreezeMode(base);

    return kStatus_FLEXCAN_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_HAL_ExitOperationMode
 * Description   : Disable a FlexCAN operation mode.
 * This function will disable one of the modes listed in flexcan_operation_modes_t.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_HAL_ExitOperationMode(
    CAN_Type * base,
    flexcan_operation_modes_t mode)
{
    if (mode == kFlexCanFreezeMode)
    {
        /* De-assert Freeze Mode*/
        FLEXCAN_HAL_ExitFreezeMode(base);

        return kStatus_FLEXCAN_Success;
    }
    else if (mode == kFlexCanDisableMode)
    {
        /* Disable module mode*/
        CAN_BWR_MCR_MDIS(base, 0x0);
        return kStatus_FLEXCAN_Success;
    }

    /* Set Freeze mode*/
    FLEXCAN_HAL_EnterFreezeMode(base);

    if (mode == kFlexCanNormalMode)
    {
        CAN_BWR_MCR_SUPV(base, 0x1);
    }
    else if (mode == kFlexCanListenOnlyMode)
    {
        CAN_BWR_CTRL1_LOM(base, 0x0);
    }
    else if (mode == kFlexCanLoopBackMode)
    {
        CAN_BWR_CTRL1_LPB(base, 0x0);
    }
    else
    {
        return kStatus_FLEXCAN_InvalidArgument;
    }

    /* De-assert Freeze Mode*/
    FLEXCAN_HAL_ExitFreezeMode(base);

    return kStatus_FLEXCAN_Success;
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

