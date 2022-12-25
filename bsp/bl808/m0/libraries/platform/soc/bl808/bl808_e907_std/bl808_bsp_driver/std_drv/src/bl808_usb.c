/**
  ******************************************************************************
  * @file    bl808_usb.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#include "bl808_usb.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  USB
 *  @{
 */

/** @defgroup  USB_Private_Macros
 *  @{
 */

/*@} end of group USB_Private_Macros */

/** @defgroup  USB_Private_Types
 *  @{
 */

/*@} end of group USB_Private_Types */

/** @defgroup  USB_Private_Variables
 *  @{
 */

/*@} end of group USB_Private_Variables */

/** @defgroup  USB_Global_Variables
 *  @{
 */

/*@} end of group USB_Global_Variables */

/** @defgroup  USB_Private_Fun_Declaration
 *  @{
 */

/*@} end of group USB_Private_Fun_Declaration */

/** @defgroup  USB_Private_Functions
 *  @{
 */

/*@} end of group USB_Private_Functions */

/** @defgroup  USB_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  USB global interrupt enable or disable
 *
 * @param  enable: ENABLE or DISABLE
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Global_IntEnable(uint8_t enable)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(USB_BASE, USB_DEV_CTL);

    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, USB_GLINT_EN_HOV);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, USB_GLINT_EN_HOV);
    }

    BL_WR_REG(USB_BASE, USB_DEV_CTL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  USB global interrupt mask or unmask
 *
 * @param  intType: interrupt type
 * @param  intMask: MASK or UNMASK
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Global_IntMask(USB_GLOBAL_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_USB_GLOBAL_INT_TYPE(intType));

    tmpVal = BL_RD_REG(USB_BASE, USB_GLB_INT);

    if (intMask == MASK) {
        tmpVal = tmpVal | (1 << intType);
    } else {
        tmpVal = tmpVal & ~(1 << intType);
    }

    BL_WR_REG(USB_BASE, USB_GLB_INT, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get USB global interrupt status
 *
 * @param  intType: interrupt type
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type USB_Global_IntStatus(USB_GLOBAL_INT_Type intType)
{
    CHECK_PARAM(IS_USB_GLOBAL_INT_TYPE(intType));

    return (BL_RD_REG(USB_BASE, USB_GLB_ISR) & (1 << intType)) ? SET : RESET;
}

/****************************************************************************/ /**
 * @brief  set USB normal configuration
 *
 * @param  cfg: configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Set_Normal_Config(USB_NORMAL_Cfg_Type *cfg)
{
    uint32_t tmpVal = 0;
    uint32_t to = 0;

    if (cfg->swRst) {
        tmpVal = BL_RD_REG(USB_BASE, USB_DEV_CTL);
        tmpVal = BL_SET_REG_BIT(tmpVal, USB_SFRST_HOV);
        BL_WR_REG(USB_BASE, USB_DEV_CTL, tmpVal);

        while (BL_GET_REG_BITS_VAL(BL_RD_REG(USB_BASE, USB_DEV_CTL), USB_SFRST_HOV)) {
            if (to >= cfg->rstTimeOut) {
                return ERROR;
            }

            to++;
        }
    }

    tmpVal = BL_RD_REG(USB_BASE, USB_DEV_CTL);

    if (cfg->forceFullSpeed) {
        tmpVal = BL_SET_REG_BIT(tmpVal, USB_FORCE_FS);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, USB_FORCE_FS);
    }

    if (cfg->remoteWakeupEn) {
        tmpVal = BL_SET_REG_BIT(tmpVal, USB_CAP_RMWAKUP);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, USB_CAP_RMWAKUP);
    }

    BL_WR_REG(USB_BASE, USB_DEV_CTL, tmpVal);

    tmpVal = BL_RD_REG(USB_BASE, USB_DEV_CTL);

    if (cfg->chipEn) {
        tmpVal = BL_SET_REG_BIT(tmpVal, USB_CHIP_EN_HOV);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, USB_CHIP_EN_HOV);
    }

    BL_WR_REG(USB_BASE, USB_DEV_CTL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get USB device speed
 *
 * @param  None
 *
 * @return high speed or full speed
 *
*******************************************************************************/
USB_DEVICE_SPEED_Type USB_Get_Device_Speed_Status(void)
{
    return (USB_DEVICE_SPEED_Type)BL_GET_REG_BITS_VAL(BL_RD_REG(USB_BASE, USB_DEV_CTL), USB_HS_EN_HOV);
}

/****************************************************************************/ /**
 * @brief  USB go suspend
 *
 * @param  enable: ENABLE or DISABLE
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Go_Suspend(uint8_t enable)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(USB_BASE, USB_DEV_CTL);

    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, USB_GOSUSP);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, USB_GOSUSP);
    }

    BL_WR_REG(USB_BASE, USB_DEV_CTL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set USB device address
 *
 * @param  addr: address
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Set_Device_Address(uint8_t addr)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM((addr <= 127));

    tmpVal = BL_RD_REG(USB_BASE, USB_DEV_ADR);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_DEVADR, addr);
    BL_WR_REG(USB_BASE, USB_DEV_ADR, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get USB device address
 *
 * @param  None
 *
 * @return address
 *
*******************************************************************************/
uint8_t USB_Get_Device_Address(void)
{
    return BL_GET_REG_BITS_VAL(BL_RD_REG(USB_BASE, USB_DEV_ADR), USB_DEVADR);
}

/****************************************************************************/ /**
 * @brief  USB non-control transfer enable
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Non_Ctrl_Transfer_Enable(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(USB_BASE, USB_DEV_ADR);
    tmpVal = BL_SET_REG_BIT(tmpVal, USB_AFT_CONF);
    BL_WR_REG(USB_BASE, USB_DEV_ADR, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  USB non-control transfer disable
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Non_Ctrl_Transfer_Disable(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(USB_BASE, USB_DEV_ADR);
    tmpVal = BL_CLR_REG_BIT(tmpVal, USB_AFT_CONF);
    BL_WR_REG(USB_BASE, USB_DEV_ADR, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  USB FIFO counters and location counters clear
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Clear_FIFO(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(USB_BASE, USB_DEV_TST);
    tmpVal = BL_SET_REG_BIT(tmpVal, USB_TST_CLRFF_HOV);
    BL_WR_REG(USB_BASE, USB_DEV_TST, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  USB SOF mask timer in high speed
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_SOF_Mask_Time_HighSpeed(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(USB_BASE, USB_DEV_SMT);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_SOFMT, USB_SOF_TIMER_MASK_AFTER_RESET_HS);
    BL_WR_REG(USB_BASE, USB_DEV_SMT, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  USB SOF mask timer in full speed
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_SOF_Mask_Time_FullSpeed(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(USB_BASE, USB_DEV_SMT);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_SOFMT, USB_SOF_TIMER_MASK_AFTER_RESET_FS);
    BL_WR_REG(USB_BASE, USB_DEV_SMT, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  USB SOF mask timer in full speed
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_SoftDetach_Enable(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(USB_BASE, USB_PHY_TST);
    tmpVal = BL_SET_REG_BIT(tmpVal, USB_UNPLUG);
    BL_WR_REG(USB_BASE, USB_PHY_TST, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  USB SOF mask timer in full speed
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_SoftDetach_Disable(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(USB_BASE, USB_PHY_TST);
    tmpVal = BL_CLR_REG_BIT(tmpVal, USB_UNPLUG);
    BL_WR_REG(USB_BASE, USB_PHY_TST, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  is USB FIFOn empty
 *
 * @param  fifoNum: FIFO number
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type USB_Is_FIFO_Empty(USB_FIFO_EMPTY_Type fifoNum)
{
    CHECK_PARAM(IS_USB_FIFO_EMPTY_TYPE(fifoNum));

    return (BL_RD_REG(USB_BASE, USB_DEV_CXCFE) & (1 << fifoNum)) ? SET : RESET;
}

/****************************************************************************/ /**
 * @brief  is USB control FIFO empty
 *
 * @param  None
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type USB_Is_CTRL_FIFO_Empty(void)
{
    return BL_GET_REG_BITS_VAL(BL_RD_REG(USB_BASE, USB_DEV_CXCFE), USB_CX_EMP) ? SET : RESET;
}

/****************************************************************************/ /**
 * @brief  is USB control FIFO full
 *
 * @param  None
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type USB_Is_CTRL_FIFO_Full(void)
{
    return BL_GET_REG_BITS_VAL(BL_RD_REG(USB_BASE, USB_DEV_CXCFE), USB_CX_FUL) ? SET : RESET;
}

/****************************************************************************/ /**
 * @brief  is USB control FIFO full
 *
 * @param  None
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Err_Type USB_Clear_CTRL_FIFO(void)
{
    BL_WR_REG(USB_BASE, USB_DEV_CXCFE, BL_SET_REG_BIT(0, USB_CX_CLR));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set USB control endpoint stall once
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Set_CTRL_Endpoint_Stall_Once(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(USB_BASE, USB_DEV_CXCFE);
    tmpVal = BL_SET_REG_BIT(tmpVal, USB_CX_STL);
    BL_WR_REG(USB_BASE, USB_DEV_CXCFE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set USB control endpoint data transfer done
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_CTRL_Endpoint_Data_Transfer_Done(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(USB_BASE, USB_DEV_CXCFE);
    tmpVal = BL_SET_REG_BIT(tmpVal, USB_CX_DONE);
    BL_WR_REG(USB_BASE, USB_DEV_CXCFE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  is USB endpoint receive 0 length data packet
 *
 * @param  epID: endpoint number
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type USB_Is_Endpoint_Receive_Zero_Length_Packet(USB_Endpoint_Type epID)
{
    /* cannot be USB_Endpoint_0 */
    CHECK_PARAM(IS_USB_ENDPOINT_TYPE(epID));

    return (BL_RD_REG(USB_BASE, USB_DEV_RXZ) & (1 << (epID - 1))) ? SET : RESET;
}

/****************************************************************************/ /**
 * @brief  clear USB endpoint receive 0 length data packet
 *
 * @param  epID: endpoint number
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Clear_Endpoint_Receive_Zero_Length_Packet_Status(USB_Endpoint_Type epID)
{
    /* cannot be USB_Endpoint_0 */
    CHECK_PARAM(IS_USB_ENDPOINT_TYPE(epID));

    BL_WR_REG(USB_BASE, USB_DEV_RXZ, 1 << (epID - 1));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  reset USB in endpoint data_toggle_sequence
 *
 * @param  epID: endpoint number
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Reset_Endpoint_IN_Data_Toggle_Sequence(USB_Endpoint_Type epID)
{
    uint32_t tmpVal = 0;
    uint32_t regAddr = 0;

    /* cannot be USB_Endpoint_0 */
    CHECK_PARAM(IS_USB_ENDPOINT_TYPE(epID));

    /* calc reg address */
    regAddr = USB_BASE + USB_DEV_INMPS1_OFFSET + (epID - 1) * 4;

    /* clear RSTG_IEPn bit */
    BL_RD_WORD(regAddr);
    tmpVal = BL_CLR_REG_BIT(tmpVal, USB_RSTG_IEP1);
    BL_WR_WORD(regAddr, tmpVal);

    /* set RSTG_IEPn bit */
    BL_RD_WORD(regAddr);
    tmpVal = BL_SET_REG_BIT(tmpVal, USB_RSTG_IEP1);
    BL_WR_WORD(regAddr, tmpVal);

    /* clear RSTG_IEPn bit */
    BL_RD_WORD(regAddr);
    tmpVal = BL_CLR_REG_BIT(tmpVal, USB_RSTG_IEP1);
    BL_WR_WORD(regAddr, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  reset USB out endpoint data_toggle_sequence
 *
 * @param  epID: endpoint number
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Reset_Endpoint_OUT_Data_Toggle_Sequence(USB_Endpoint_Type epID)
{
    uint32_t tmpVal = 0;
    uint32_t regAddr = 0;

    /* cannot be USB_Endpoint_0 */
    CHECK_PARAM(IS_USB_ENDPOINT_TYPE(epID));

    /* calc reg address */
    regAddr = USB_BASE + USB_DEV_OUTMPS1_OFFSET + (epID - 1) * 4;

    /* clear RSTG_IEPn bit */
    BL_RD_WORD(regAddr);
    tmpVal = BL_CLR_REG_BIT(tmpVal, USB_RSTG_OEP1);
    BL_WR_WORD(regAddr, tmpVal);

    /* set RSTG_IEPn bit */
    BL_RD_WORD(regAddr);
    tmpVal = BL_SET_REG_BIT(tmpVal, USB_RSTG_OEP1);
    BL_WR_WORD(regAddr, tmpVal);

    /* clear RSTG_IEPn bit */
    BL_RD_WORD(regAddr);
    tmpVal = BL_CLR_REG_BIT(tmpVal, USB_RSTG_OEP1);
    BL_WR_WORD(regAddr, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  USB endpoint transmit 0 length data packet
 *
 * @param  epID: endpoint number
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Endpoint_Transmit_Zero_Length_Packet(USB_Endpoint_Type epID)
{
    uint32_t tmpVal = 0;
    uint32_t regAddr = 0;

    /* cannot be USB_Endpoint_0 */
    CHECK_PARAM(IS_USB_ENDPOINT_TYPE(epID));

    regAddr = USB_BASE + USB_DEV_INMPS1_OFFSET + 0x04 * (epID - 1);

    tmpVal = BL_RD_WORD(regAddr);
    tmpVal |= (1 << USB_TX0BYTE_IEP1_POS);
    BL_WR_WORD(regAddr, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  is USB endpoint receive 0 length data packet
 *
 * @param  epID: endpoint number
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type USB_Is_Endpoint_Transfer_Zero_Length_Packet(USB_Endpoint_Type epID)
{
    /* cannot be USB_Endpoint_0 */
    CHECK_PARAM(IS_USB_ENDPOINT_TYPE(epID));

    return (BL_RD_REG(USB_BASE, USB_DEV_TXZ) & (1 << (epID - 1))) ? SET : RESET;
}

/****************************************************************************/ /**
 * @brief  clear USB endpoint transfer 0 length data packet status
 *
 * @param  epID: endpoint number
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Clear_Endpoint_Transfer_Zero_Length_Packet_Status(USB_Endpoint_Type epID)
{
    /* cannot be USB_Endpoint_0 */
    CHECK_PARAM(IS_USB_ENDPOINT_TYPE(epID));

    BL_WR_REG(USB_BASE, USB_DEV_TXZ, 1 << (epID - 1));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set USB IN endpoint stall
 *
 * @param  epID: endpoint number
 * @param  enable: ENABLE or DISABLE
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Set_Endpoint_IN_Stall(USB_Endpoint_Type epID, uint8_t enable)
{
    uint32_t tmpVal = 0;
    uint32_t regAddr = 0;

    /* cannot be USB_Endpoint_0 */
    CHECK_PARAM(IS_USB_ENDPOINT_TYPE(epID));

    regAddr = USB_BASE + USB_DEV_INMPS1_OFFSET + 0x04 * (epID - 1);

    tmpVal = BL_RD_WORD(regAddr);

    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, USB_STL_IEP1);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, USB_STL_IEP1);
    }

    BL_WR_WORD(regAddr, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set USB IN endpoint max packet size
 *
 * @param  epID: endpoint number
 * @param  max: max packet size
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Set_Endpoint_IN_MaxPacketSize(USB_Endpoint_Type epID, uint16_t max)
{
    uint32_t tmpVal = 0;
    uint32_t regAddr = 0;

    /* cannot be USB_Endpoint_0 */
    CHECK_PARAM(IS_USB_ENDPOINT_TYPE(epID));
    CHECK_PARAM((max <= 0x7FF));

    regAddr = USB_BASE + USB_DEV_INMPS1_OFFSET + 0x04 * (epID - 1);

    tmpVal = BL_RD_WORD(regAddr);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_MAXPS_IEP1, max);
    BL_WR_WORD(regAddr, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set USB OUT endpoint stall
 *
 * @param  epID: endpoint number
 * @param  enable: ENABLE or DISABLE
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Set_Endpoint_OUT_Stall(USB_Endpoint_Type epID, uint8_t enable)
{
    uint32_t tmpVal = 0;
    uint32_t regAddr = 0;

    /* cannot be USB_Endpoint_0 */
    CHECK_PARAM(IS_USB_ENDPOINT_TYPE(epID));

    regAddr = USB_BASE + USB_DEV_OUTMPS1_OFFSET + 0x04 * (epID - 1);

    tmpVal = BL_RD_WORD(regAddr);

    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, USB_STL_OEP1);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, USB_STL_OEP1);
    }

    BL_WR_WORD(regAddr, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set USB OUT endpoint max packet size
 *
 * @param  epID: endpoint number
 * @param  max: max packet size
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Set_Endpoint_OUT_MaxPacketSize(USB_Endpoint_Type epID, uint16_t max)
{
    uint32_t tmpVal = 0;
    uint32_t regAddr = 0;

    /* cannot be USB_Endpoint_0 */
    CHECK_PARAM(IS_USB_ENDPOINT_TYPE(epID));
    CHECK_PARAM((max <= 0x7FF));

    regAddr = USB_BASE + USB_DEV_OUTMPS1_OFFSET + 0x04 * (epID - 1);

    tmpVal = BL_RD_WORD(regAddr);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_MAXPS_OEP1, max);
    BL_WR_WORD(regAddr, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set USB FIFO ID of IN endpoint
 *
 * @param  epID: endpoint number
 * @param  fifoID: FIFO ID
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Set_FIFO_Of_Endpoint_IN(USB_Endpoint_Type epID, USB_FIFO_Type fifoID)
{
    uint32_t tmpVal = 0;
    uint32_t regAddr = 0;

    /* cannot be USB_Endpoint_0 */
    CHECK_PARAM(IS_USB_ENDPOINT_TYPE(epID));
    CHECK_PARAM(IS_USB_FIFO_TYPE(fifoID));

    if (epID <= USB_Endpoint_4) {
        regAddr = USB_BASE + USB_DEV_EPMAP0_OFFSET;
    } else {
        regAddr = USB_BASE + USB_DEV_EPMAP1_OFFSET;
    }

    tmpVal = BL_RD_WORD(regAddr);

    switch (epID) {
        case USB_Endpoint_1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_FNO_IEP1, fifoID);
            break;

        case USB_Endpoint_2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_FNO_IEP2, fifoID);
            break;

        case USB_Endpoint_3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_FNO_IEP3, fifoID);
            break;

        case USB_Endpoint_4:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_FNO_IEP4, fifoID);
            break;

        case USB_Endpoint_5:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_FNO_IEP5, fifoID);
            break;

        case USB_Endpoint_6:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_FNO_IEP6, fifoID);
            break;

        case USB_Endpoint_7:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_FNO_IEP7, fifoID);
            break;

        case USB_Endpoint_8:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_FNO_IEP8, fifoID);
            break;

        default:
            break;
    }

    BL_WR_WORD(regAddr, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set USB FIFO ID of IN endpoint
 *
 * @param  epID: endpoint number
 * @param  fifoID: FIFO ID
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Set_FIFO_Of_Endpoint_OUT(USB_Endpoint_Type epID, USB_FIFO_Type fifoID)
{
    uint32_t tmpVal = 0;
    uint32_t regAddr = 0;

    /* cannot be USB_Endpoint_0 */
    CHECK_PARAM(IS_USB_ENDPOINT_TYPE(epID));
    CHECK_PARAM(IS_USB_FIFO_TYPE(fifoID));

    if (epID <= USB_Endpoint_4) {
        regAddr = USB_BASE + USB_DEV_EPMAP0_OFFSET;
    } else {
        regAddr = USB_BASE + USB_DEV_EPMAP1_OFFSET;
    }

    tmpVal = BL_RD_WORD(regAddr);

    switch (epID) {
        case USB_Endpoint_1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_FNO_OEP1, fifoID);
            break;

        case USB_Endpoint_2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_FNO_OEP2, fifoID);
            break;

        case USB_Endpoint_3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_FNO_OEP3, fifoID);
            break;

        case USB_Endpoint_4:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_FNO_OEP4, fifoID);
            break;

        case USB_Endpoint_5:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_FNO_OEP5, fifoID);
            break;

        case USB_Endpoint_6:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_FNO_OEP6, fifoID);
            break;

        case USB_Endpoint_7:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_FNO_OEP7, fifoID);
            break;

        case USB_Endpoint_8:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_FNO_OEP8, fifoID);
            break;

        default:
            break;
    }

    BL_WR_WORD(regAddr, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set USB FIFO configuration
 *
 * @param  fifoID: FIFO ID
 * @param  cfg: configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Set_FIFO_Config(USB_FIFO_Type fifoID, USB_FIFO_Cfg_Type *cfg)
{
    uint32_t tmpVal1 = 0;
    uint32_t tmpVal2 = 0;
    uint32_t en = 0;

    CHECK_PARAM(IS_USB_FIFO_TYPE(fifoID));
    CHECK_PARAM(IS_USB_FIFO_DIR_TYPE(cfg->dir));
    CHECK_PARAM(IS_USB_ENDPOINT_TYPE(cfg->epID));
    CHECK_PARAM(IS_USB_FIFO_BLOCK_MAX_SIZE_TYPE(cfg->blockSize));
    CHECK_PARAM(IS_USB_FIFO_BLOCK_CNT_TYPE(cfg->blockType));
    CHECK_PARAM(IS_USB_FIFO_TRANSFER_TYPE(cfg->fifoType));

    tmpVal1 = BL_RD_REG(USB_BASE, USB_DEV_FMAP);
    tmpVal2 = BL_RD_REG(USB_BASE, USB_DEV_FCFG);

    if (cfg->enable) {
        en = 1;
    }

    switch (fifoID) {
        case USB_FIFO_0:
            tmpVal1 = BL_SET_REG_BITS_VAL(tmpVal1, USB_DIR_FIFO0, cfg->dir);
            tmpVal1 = BL_SET_REG_BITS_VAL(tmpVal1, USB_EPNO_FIFO0, cfg->epID);
            tmpVal2 = BL_SET_REG_BITS_VAL(tmpVal2, USB_EN_F0, en);
            tmpVal2 = BL_SET_REG_BITS_VAL(tmpVal2, USB_BLKSZ_F0, cfg->blockSize);
            tmpVal2 = BL_SET_REG_BITS_VAL(tmpVal2, USB_BLKNO_F0, cfg->blockType);
            tmpVal2 = BL_SET_REG_BITS_VAL(tmpVal2, USB_BLK_TYP_F0, cfg->fifoType);
            break;

        case USB_FIFO_1:
            tmpVal1 = BL_SET_REG_BITS_VAL(tmpVal1, USB_DIR_FIFO1, cfg->dir);
            tmpVal1 = BL_SET_REG_BITS_VAL(tmpVal1, USB_EPNO_FIFO1, cfg->epID);
            tmpVal2 = BL_SET_REG_BITS_VAL(tmpVal2, USB_EN_F1, en);
            tmpVal2 = BL_SET_REG_BITS_VAL(tmpVal2, USB_BLKSZ_F1, cfg->blockSize);
            tmpVal2 = BL_SET_REG_BITS_VAL(tmpVal2, USB_BLKNO_F1, cfg->blockType);
            tmpVal2 = BL_SET_REG_BITS_VAL(tmpVal2, USB_BLK_TYP_F1, cfg->fifoType);
            break;

        case USB_FIFO_2:
            tmpVal1 = BL_SET_REG_BITS_VAL(tmpVal1, USB_DIR_FIFO2, cfg->dir);
            tmpVal1 = BL_SET_REG_BITS_VAL(tmpVal1, USB_EPNO_FIFO2, cfg->epID);
            tmpVal2 = BL_SET_REG_BITS_VAL(tmpVal2, USB_EN_F2, en);
            tmpVal2 = BL_SET_REG_BITS_VAL(tmpVal2, USB_BLKSZ_F2, cfg->blockSize);
            tmpVal2 = BL_SET_REG_BITS_VAL(tmpVal2, USB_BLKNO_F2, cfg->blockType);
            tmpVal2 = BL_SET_REG_BITS_VAL(tmpVal2, USB_BLK_TYP_F2, cfg->fifoType);
            break;

        case USB_FIFO_3:
            tmpVal1 = BL_SET_REG_BITS_VAL(tmpVal1, USB_DIR_FIFO3, cfg->dir);
            tmpVal1 = BL_SET_REG_BITS_VAL(tmpVal1, USB_EPNO_FIFO3, cfg->epID);
            tmpVal2 = BL_SET_REG_BITS_VAL(tmpVal2, USB_EN_F3, en);
            tmpVal2 = BL_SET_REG_BITS_VAL(tmpVal2, USB_BLKSZ_F3, cfg->blockSize);
            tmpVal2 = BL_SET_REG_BITS_VAL(tmpVal2, USB_BLKNO_F3, cfg->blockType);
            tmpVal2 = BL_SET_REG_BITS_VAL(tmpVal2, USB_BLK_TYP_F3, cfg->fifoType);
            break;

        default:
            break;
    }

    BL_WR_REG(USB_BASE, USB_DEV_FMAP, tmpVal1);
    BL_WR_REG(USB_BASE, USB_DEV_FCFG, tmpVal2);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  reset USB FIFO
 *
 * @param  fifoID: FIFO ID
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Reset_FIFO(USB_FIFO_Type fifoID)
{
    uint32_t tmpVal = 0;
    uint32_t regAddr = 0;

    CHECK_PARAM(IS_USB_FIFO_TYPE(fifoID));

    regAddr = USB_BASE + USB_DEV_FIBC0_OFFSET + 0x04 * fifoID;

    tmpVal = BL_RD_WORD(regAddr);
    tmpVal = BL_SET_REG_BIT(tmpVal, USB_FFRST0_HOV);
    BL_WR_WORD(regAddr, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get USB out FIFO count
 *
 * @param  fifoID: FIFO ID
 *
 * @return FIFO count
 *
*******************************************************************************/
uint16_t USB_Get_OUT_FIFO_Count(USB_FIFO_Type fifoID)
{
    uint32_t regAddr = 0;

    CHECK_PARAM(IS_USB_FIFO_TYPE(fifoID));

    regAddr = USB_BASE + USB_DEV_FIBC0_OFFSET + 0x04 * fifoID;

    return BL_GET_REG_BITS_VAL(BL_RD_WORD(regAddr), USB_BC_F0);
}

/****************************************************************************/ /**
 * @brief  set USB dma configuration
 *
 * @param  cfg: configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Set_DMA_Config(USB_DMA_TARGET_FIFO_Type fifoN, USB_DMA_Cfg_Type *cfg)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_USB_DMA_TRANS_DIR_TYPE(cfg->dir));
    CHECK_PARAM(IS_USB_DMA_TARGET_FIFO_TYPE(fifoN));
    CHECK_PARAM(((cfg->length) <= 0x1FFFF));

    switch (fifoN) {
        case USB_DMA_TARGET_FIFO_CTRL:
            tmpVal = (1 << 4);
            break;
        case USB_DMA_TARGET_FIFO_0:
            tmpVal = (1 << 0);
            break;
        case USB_DMA_TARGET_FIFO_1:
            tmpVal = (1 << 1);
            break;
        case USB_DMA_TARGET_FIFO_2:
            tmpVal = (1 << 2);
            break;
        case USB_DMA_TARGET_FIFO_3:
            tmpVal = (1 << 3);
            break;
        default:
            break;
    }
    BL_WR_REG(USB_BASE, USB_DMA_TFN, tmpVal);

    tmpVal = BL_RD_REG(USB_BASE, USB_DMA_CPS1);

    switch (cfg->dir) {
        case USB_DMA_TRANS_DIR_FIFO_2_MEM:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_DMA_IO_HOV, 0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_DMA_TYPE_HOV, 0);
            break;

        case USB_DMA_TRANS_DIR_MEM_2_FIFO:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_DMA_IO_HOV, 0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_DMA_TYPE_HOV, 1);
            break;

        case USB_DMA_TRANS_DIR_FIFO_2_FIFO:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_DMA_IO_HOV, 1);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_DMA_TYPE_HOV, 0);

            if ((cfg->length) & 0x3) {
                return ERROR;
            }

            break;

        default:
            break;
    }

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_DMA_LEN_HOV, cfg->length);
    BL_WR_REG(USB_BASE, USB_DMA_CPS1, tmpVal);

    BL_WR_REG(USB_BASE, USB_DMA_CPS2, cfg->memAddr);

    return SUCCESS;
}
/****************************************************************************/ /**
 * @brief  reset usb dma accessing fifo
 *
 * @param  cfg: configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
void USB_Reset_DMA_Accessing_Fifo(void)
{
    BL_WR_REG(USB_BASE, USB_DMA_TFN, 0);
}
/****************************************************************************/ /**
 * @brief  update USB dma transmit configuration
 *
 * @param  memAddr: memory address
 * @param  length: transmit length
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Update_DMA_Trans(uint32_t memAddr, uint32_t length)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(USB_BASE, USB_DMA_CPS1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_DMA_LEN_HOV, length);
    BL_WR_REG(USB_BASE, USB_DMA_CPS1, tmpVal);

    BL_WR_REG(USB_BASE, USB_DMA_CPS2, memAddr);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  USB dma transmit start
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Set_DMA_Start(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(USB_BASE, USB_DMA_CPS1);
    tmpVal = BL_SET_REG_BIT(tmpVal, USB_DMA_START_HOV);
    BL_WR_REG(USB_BASE, USB_DMA_CPS1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get USB setup command
 *
 * @param  setup[2]: buffer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Get_Setup_Command(uint32_t setup[2])
{
    uint32_t tmpVal = 0;

    if (NULL == setup) {
        return ERROR;
    }

    tmpVal = BL_RD_REG(USB_BASE, USB_DMA_TFN);
    tmpVal = BL_SET_REG_BIT(tmpVal, USB_ACC_CXF_HOV);
    BL_WR_REG(USB_BASE, USB_DMA_TFN, tmpVal);

    setup[0] = BL_RD_REG(USB_BASE, USB_DMA_CPS3);
    setup[1] = BL_RD_REG(USB_BASE, USB_DMA_CPS3);

    tmpVal = BL_RD_REG(USB_BASE, USB_DMA_TFN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, USB_ACC_CXF_HOV);
    BL_WR_REG(USB_BASE, USB_DMA_TFN, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set USB vdma configuration
 *
 * @param  fifoN: target FIFO
 * @param  cfg: configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Set_VDMA_Config(USB_VDMA_TARGET_FIFO_Type fifoN, USB_VDMA_Cfg_Type *cfg)
{
    uint32_t tmpVal = 0;
    uint32_t setting1Addr = 0;
    uint32_t setting2Addr = 0;

    CHECK_PARAM(IS_USB_VDMA_TARGET_FIFO_TYPE(fifoN));
    CHECK_PARAM(IS_USB_VDMA_TRANS_DIR_TYPE(cfg->dir));
    CHECK_PARAM(((cfg->length) <= 0x1FFFF));

    setting1Addr = USB_BASE + USB_VDMA_CXFPS1_OFFSET + 0x08 * (fifoN);
    setting2Addr = USB_BASE + USB_VDMA_CXFPS2_OFFSET + 0x08 * (fifoN);
    tmpVal = BL_RD_WORD(setting1Addr);

    switch (cfg->dir) {
        case USB_VDMA_TRANS_DIR_FIFO_2_MEM:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_VDMA_IO_CXF, 0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_VDMA_TYPE_CXF, 0);
            break;

        case USB_VDMA_TRANS_DIR_MEM_2_FIFO:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_VDMA_IO_CXF, 0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_VDMA_TYPE_CXF, 1);
            break;

        case USB_VDMA_TRANS_DIR_FIFO_2_FIFO:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_VDMA_IO_CXF, 1);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_VDMA_TYPE_CXF, 0);

            if ((cfg->length) & 0x3) {
                return ERROR;
            }

            break;

        default:
            break;
    }

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_VDMA_LEN_CXF, cfg->length);
    BL_WR_WORD(setting1Addr, tmpVal);

    BL_WR_WORD(setting2Addr, cfg->memAddr);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  USB vdma transmit start
 *
 * @param  fifoN: target FIFO
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Set_VDMA_Start(USB_VDMA_TARGET_FIFO_Type fifoN)
{
    uint32_t tmpVal = 0;
    uint32_t setting1Addr = 0;

    CHECK_PARAM(IS_USB_VDMA_TARGET_FIFO_TYPE(fifoN));

    setting1Addr = USB_BASE + USB_VDMA_CXFPS1_OFFSET + 0x08 * (fifoN);

    tmpVal = BL_RD_WORD(setting1Addr);
    tmpVal = BL_SET_REG_BIT(tmpVal, USB_VDMA_START_CXF);
    BL_WR_WORD(setting1Addr, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get USB vdma transmit start status
 *
 * @param  fifoN: target FIFO
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type USB_Get_VDMA_Start(USB_VDMA_TARGET_FIFO_Type fifoN)
{
    uint32_t setting1Addr = 0;

    CHECK_PARAM(IS_USB_VDMA_TARGET_FIFO_TYPE(fifoN));

    setting1Addr = USB_BASE + USB_VDMA_CXFPS1_OFFSET + 8 * (fifoN);

    return BL_GET_REG_BITS_VAL(BL_RD_WORD(setting1Addr), USB_VDMA_START_CXF) ? SET : RESET;
}

/****************************************************************************/ /**
 * @brief  USB vdma multi channel function enable
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Set_VDMA_Enable(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(USB_BASE, USB_VDMA_CTRL);
    tmpVal = BL_SET_REG_BIT(tmpVal, USB_VDMA_EN);
    BL_WR_REG(USB_BASE, USB_VDMA_CTRL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set USB LPM configuration
 *
 * @param  cfg: configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Set_LPM_Config(USB_LPM_Cfg_Type *cfg)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_USB_LPM_RESP_TYPE(cfg->resp));

    tmpVal = BL_RD_REG(USB_BASE, USB_LPM_CAP);

    if (cfg->lpmWakeUpEn) {
        tmpVal = BL_SET_REG_BIT(tmpVal, USB_LPM_WAKEUP_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, USB_LPM_WAKEUP_EN);
    }

    BL_WR_REG(USB_BASE, USB_LPM_CAP, tmpVal);

    tmpVal = BL_RD_REG(USB_BASE, USB_DEV_CTL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_LPM_ACCEPT, cfg->resp);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_LPM_BESL_MIN, cfg->minBesl);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_LPM_BESL_MAX, cfg->maxBesl);
    BL_WR_REG(USB_BASE, USB_DEV_CTL, tmpVal);

    tmpVal = BL_RD_REG(USB_BASE, USB_DEV_CTL);

    if (cfg->lpmEn) {
        tmpVal = BL_SET_REG_BIT(tmpVal, USB_LPM_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, USB_LPM_EN);
    }

    BL_WR_REG(USB_BASE, USB_DEV_CTL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set USB LPM configuration
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
uint8_t USB_Get_LPM_BESL(void)
{
    return BL_GET_REG_BITS_VAL(BL_RD_REG(USB_BASE, USB_DEV_CTL), USB_LPM_BESL);
}

/****************************************************************************/ /**
 * @brief  set suspend delay
 *
 * @param  ms: delay ms count
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Set_Suspend_Delay(uint8_t ms)
{
    uint32_t tmpVal;

    CHECK_PARAM((ms <= 7));

    tmpVal = BL_RD_REG(USB_BASE, USB_DEV_ICR);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_IDLE_CNT, ms);
    BL_WR_REG(USB_BASE, USB_DEV_ICR, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  USB group interrupt mask or unmask
 *
 * @param  intType: interrupt type
 * @param  intMask: MASK or UNMASK
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Group_IntMask(USB_GRP_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_USB_GRP_INT_TYPE(intType));

    tmpVal = BL_RD_REG(USB_BASE, USB_DEV_MIGR);

    if (intMask == MASK) {
        tmpVal = tmpVal | (1 << intType);
    } else {
        tmpVal = tmpVal & ~(1 << intType);
    }

    BL_WR_REG(USB_BASE, USB_DEV_MIGR, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get USB group interrupt status
 *
 * @param  intType: interrupt type
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type USB_Group_IntStatus(USB_GRP_INT_Type intType)
{
    CHECK_PARAM(IS_USB_GRP_INT_TYPE(intType));

    return (BL_RD_REG(USB_BASE, USB_DEV_IGR) & (1 << intType)) ? SET : RESET;
}

/****************************************************************************/ /**
 * @brief  USB mask sub group interrupt
 *
 * @param  intType: interrupt type, USB_INT_CX_SETUP | USB_INT_CX_IN | ...
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Sub_Group_IntMask(uint64_t intType)
{
    uint64_t val = intType;
    uint32_t bit = 0;
    uint32_t tmpValG0 = BL_RD_WORD(USB_BASE + USB_DEV_MISG0_OFFSET);
    uint32_t tmpValG1 = BL_RD_WORD(USB_BASE + USB_DEV_MISG1_OFFSET);
    uint32_t tmpValG2 = BL_RD_WORD(USB_BASE + USB_DEV_MISG2_OFFSET);
    uint32_t tmpValG3 = BL_RD_WORD(USB_BASE + USB_DEV_MISG3_OFFSET);
    uint32_t tmpValG4 = BL_RD_WORD(USB_BASE + USB_DEV_MISG4_OFFSET);

    while (0 == arch_ctzll(&val, &bit)) {
        val &= ~(((uint64_t)1) << bit);
        switch (bit) {
            case USB_SUB_GRP0_INT_CX_SETUP:
                tmpValG0 |= (1 << USB_MCX_SETUP_INT_POS);
                break;
            case USB_SUB_GRP0_INT_CX_IN:
                tmpValG0 |= (1 << USB_MCX_IN_INT_POS);
                break;
            case USB_SUB_GRP0_INT_CX_OUT:
                tmpValG0 |= (1 << USB_MCX_OUT_INT_POS);
                break;
            case USB_SUB_GRP0_INT_CX_COMFAIL:
                tmpValG0 |= (1 << USB_MCX_COMFAIL_INT_POS);
                break;
            case USB_SUB_GRP0_INT_CX_COMABORT:
                tmpValG0 |= (1 << USB_MCX_COMABORT_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F0_OUT:
                tmpValG1 |= (1 << USB_MF0_OUT_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F0_SPK:
                tmpValG1 |= (1 << USB_MF0_SPK_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F1_OUT:
                tmpValG1 |= (1 << USB_MF1_OUT_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F1_SPK:
                tmpValG1 |= (1 << USB_MF1_SPK_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F2_OUT:
                tmpValG1 |= (1 << USB_MF2_OUT_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F2_SPK:
                tmpValG1 |= (1 << USB_MF2_SPK_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F3_OUT:
                tmpValG1 |= (1 << USB_MF3_OUT_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F3_SPK:
                tmpValG1 |= (1 << USB_MF3_SPK_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F0_IN:
                tmpValG1 |= (1 << USB_MF0_IN_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F1_IN:
                tmpValG1 |= (1 << USB_MF1_IN_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F2_IN:
                tmpValG1 |= (1 << USB_MF2_IN_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F3_IN:
                tmpValG1 |= (1 << USB_MF3_IN_INT_POS);
                break;
            case USB_SUB_GRP2_INT_RESET:
                tmpValG2 |= (1 << USB_MUSBRST_INT_POS);
                break;
            case USB_SUB_GRP2_INT_SUSPEND:
                tmpValG2 |= (1 << USB_MSUSP_INT_POS);
                break;
            case USB_SUB_GRP2_INT_RESUME:
                tmpValG2 |= (1 << USB_MRESM_INT_POS);
                break;
            case USB_SUB_GRP2_INT_TX0BYTE:
                tmpValG2 |= (1 << USB_MTX0BYTE_INT_POS);
                break;
            case USB_SUB_GRP2_INT_RX0BYTE:
                tmpValG2 |= (1 << USB_MRX0BYTE_INT_POS);
                break;
            case USB_SUB_GRP2_INT_DMA_CMPLT:
                tmpValG2 |= (1 << USB_MDMA_CMPLT_HOV_POS);
                break;
            case USB_SUB_GRP2_INT_DMA_ERROR:
                tmpValG2 |= (1 << USB_MDMA_ERROR_HOV_POS);
                break;
            case USB_SUB_GRP2_INT_IDLE:
                tmpValG2 |= (1 << USB_MDEV_IDLE_HOV_POS);
                break;
            case USB_SUB_GRP2_INT_WAKEUP_BY_VBUS:
                tmpValG2 |= (1 << USB_MDEV_WAKEUP_BYVBUS_POS);
                break;
            case USB_SUB_GRP3_INT_VDMA_CMPLT_CXF:
                tmpValG3 |= (1 << USB_MVDMA_CMPLT_CXF_POS);
                break;
            case USB_SUB_GRP3_INT_VDMA_CMPLT_F0:
                tmpValG3 |= (1 << USB_MVDMA_CMPLT_F0_POS);
                break;
            case USB_SUB_GRP3_INT_VDMA_CMPLT_F1:
                tmpValG3 |= (1 << USB_MVDMA_CMPLT_F1_POS);
                break;
            case USB_SUB_GRP3_INT_VDMA_CMPLT_F2:
                tmpValG3 |= (1 << USB_MVDMA_CMPLT_F2_POS);
                break;
            case USB_SUB_GRP3_INT_VDMA_CMPLT_F3:
                tmpValG3 |= (1 << USB_MVDMA_CMPLT_F3_POS);
                break;
            case USB_SUB_GRP3_INT_VDMA_ERROR_CXF:
                tmpValG3 |= (1 << USB_MVDMA_ERROR_CXF_POS);
                break;
            case USB_SUB_GRP3_INT_VDMA_ERROR_F0:
                tmpValG3 |= (1 << USB_MVDMA_ERROR_F0_POS);
                break;
            case USB_SUB_GRP3_INT_VDMA_ERROR_F1:
                tmpValG3 |= (1 << USB_MVDMA_ERROR_F1_POS);
                break;
            case USB_SUB_GRP3_INT_VDMA_ERROR_F2:
                tmpValG3 |= (1 << USB_MVDMA_ERROR_F2_POS);
                break;
            case USB_SUB_GRP3_INT_VDMA_ERROR_F3:
                tmpValG3 |= (1 << USB_MVDMA_ERROR_F3_POS);
                break;
            case USB_SUB_GRP4_INT_L1:
                tmpValG4 |= (1 << USB_ML1_INT_POS);
                break;
            default:
                break;
        }
    }
    BL_WR_WORD(USB_BASE + USB_DEV_MISG0_OFFSET, tmpValG0);
    BL_WR_WORD(USB_BASE + USB_DEV_MISG1_OFFSET, tmpValG1);
    BL_WR_WORD(USB_BASE + USB_DEV_MISG2_OFFSET, tmpValG2);
    BL_WR_WORD(USB_BASE + USB_DEV_MISG3_OFFSET, tmpValG3);
    BL_WR_WORD(USB_BASE + USB_DEV_MISG4_OFFSET, tmpValG4);
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  USB unmask sub group interrupt
 *
 * @param  intType: interrupt type, USB_INT_CX_SETUP | USB_INT_CX_IN | ...
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Sub_Group_IntUnmask(uint64_t intType)
{
    uint64_t val = intType;
    uint32_t bit = 0;
    uint32_t tmpValG0 = BL_RD_WORD(USB_BASE + USB_DEV_MISG0_OFFSET);
    uint32_t tmpValG1 = BL_RD_WORD(USB_BASE + USB_DEV_MISG1_OFFSET);
    uint32_t tmpValG2 = BL_RD_WORD(USB_BASE + USB_DEV_MISG2_OFFSET);
    uint32_t tmpValG3 = BL_RD_WORD(USB_BASE + USB_DEV_MISG3_OFFSET);
    uint32_t tmpValG4 = BL_RD_WORD(USB_BASE + USB_DEV_MISG4_OFFSET);

    while (0 == arch_ctzll(&val, &bit)) {
        val &= ~(((uint64_t)1) << bit);
        switch (bit) {
            case USB_SUB_GRP0_INT_CX_SETUP:
                tmpValG0 &= ~(1 << USB_MCX_SETUP_INT_POS);
                break;
            case USB_SUB_GRP0_INT_CX_IN:
                tmpValG0 &= ~(1 << USB_MCX_IN_INT_POS);
                break;
            case USB_SUB_GRP0_INT_CX_OUT:
                tmpValG0 &= ~(1 << USB_MCX_OUT_INT_POS);
                break;
            case USB_SUB_GRP0_INT_CX_COMFAIL:
                tmpValG0 &= ~(1 << USB_MCX_COMFAIL_INT_POS);
                break;
            case USB_SUB_GRP0_INT_CX_COMABORT:
                tmpValG0 &= ~(1 << USB_MCX_COMABORT_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F0_OUT:
                tmpValG1 &= ~(1 << USB_MF0_OUT_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F0_SPK:
                tmpValG1 &= ~(1 << USB_MF0_SPK_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F1_OUT:
                tmpValG1 &= ~(1 << USB_MF1_OUT_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F1_SPK:
                tmpValG1 &= ~(1 << USB_MF1_SPK_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F2_OUT:
                tmpValG1 &= ~(1 << USB_MF2_OUT_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F2_SPK:
                tmpValG1 &= ~(1 << USB_MF2_SPK_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F3_OUT:
                tmpValG1 &= ~(1 << USB_MF3_OUT_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F3_SPK:
                tmpValG1 &= ~(1 << USB_MF3_SPK_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F0_IN:
                tmpValG1 &= ~(1 << USB_MF0_IN_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F1_IN:
                tmpValG1 &= ~(1 << USB_MF1_IN_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F2_IN:
                tmpValG1 &= ~(1 << USB_MF2_IN_INT_POS);
                break;
            case USB_SUB_GRP1_INT_F3_IN:
                tmpValG1 &= ~(1 << USB_MF3_IN_INT_POS);
                break;
            case USB_SUB_GRP2_INT_RESET:
                tmpValG2 &= ~(1 << USB_MUSBRST_INT_POS);
                break;
            case USB_SUB_GRP2_INT_SUSPEND:
                tmpValG2 &= ~(1 << USB_MSUSP_INT_POS);
                break;
            case USB_SUB_GRP2_INT_RESUME:
                tmpValG2 &= ~(1 << USB_MRESM_INT_POS);
                break;
            case USB_SUB_GRP2_INT_TX0BYTE:
                tmpValG2 &= ~(1 << USB_MTX0BYTE_INT_POS);
                break;
            case USB_SUB_GRP2_INT_RX0BYTE:
                tmpValG2 &= ~(1 << USB_MRX0BYTE_INT_POS);
                break;
            case USB_SUB_GRP2_INT_DMA_CMPLT:
                tmpValG2 &= ~(1 << USB_MDMA_CMPLT_HOV_POS);
                break;
            case USB_SUB_GRP2_INT_DMA_ERROR:
                tmpValG2 &= ~(1 << USB_MDMA_ERROR_HOV_POS);
                break;
            case USB_SUB_GRP2_INT_IDLE:
                tmpValG2 &= ~(1 << USB_MDEV_IDLE_HOV_POS);
                break;
            case USB_SUB_GRP2_INT_WAKEUP_BY_VBUS:
                tmpValG2 &= ~(1 << USB_MDEV_WAKEUP_BYVBUS_POS);
                break;
            case USB_SUB_GRP3_INT_VDMA_CMPLT_CXF:
                tmpValG3 &= ~(1 << USB_MVDMA_CMPLT_CXF_POS);
                break;
            case USB_SUB_GRP3_INT_VDMA_CMPLT_F0:
                tmpValG3 &= ~(1 << USB_MVDMA_CMPLT_F0_POS);
                break;
            case USB_SUB_GRP3_INT_VDMA_CMPLT_F1:
                tmpValG3 &= ~(1 << USB_MVDMA_CMPLT_F1_POS);
                break;
            case USB_SUB_GRP3_INT_VDMA_CMPLT_F2:
                tmpValG3 &= ~(1 << USB_MVDMA_CMPLT_F2_POS);
                break;
            case USB_SUB_GRP3_INT_VDMA_CMPLT_F3:
                tmpValG3 &= ~(1 << USB_MVDMA_CMPLT_F3_POS);
                break;
            case USB_SUB_GRP3_INT_VDMA_ERROR_CXF:
                tmpValG3 &= ~(1 << USB_MVDMA_ERROR_CXF_POS);
                break;
            case USB_SUB_GRP3_INT_VDMA_ERROR_F0:
                tmpValG3 &= ~(1 << USB_MVDMA_ERROR_F0_POS);
                break;
            case USB_SUB_GRP3_INT_VDMA_ERROR_F1:
                tmpValG3 &= ~(1 << USB_MVDMA_ERROR_F1_POS);
                break;
            case USB_SUB_GRP3_INT_VDMA_ERROR_F2:
                tmpValG3 &= ~(1 << USB_MVDMA_ERROR_F2_POS);
                break;
            case USB_SUB_GRP3_INT_VDMA_ERROR_F3:
                tmpValG3 &= ~(1 << USB_MVDMA_ERROR_F3_POS);
                break;
            case USB_SUB_GRP4_INT_L1:
                tmpValG4 &= ~(1 << USB_ML1_INT_POS);
                break;
            default:
                break;
        }
    }
    BL_WR_WORD(USB_BASE + USB_DEV_MISG0_OFFSET, tmpValG0);
    BL_WR_WORD(USB_BASE + USB_DEV_MISG1_OFFSET, tmpValG1);
    BL_WR_WORD(USB_BASE + USB_DEV_MISG2_OFFSET, tmpValG2);
    BL_WR_WORD(USB_BASE + USB_DEV_MISG3_OFFSET, tmpValG3);
    BL_WR_WORD(USB_BASE + USB_DEV_MISG4_OFFSET, tmpValG4);
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get USB sub group 0 interrupt status
 *
 * @param  None
 *
 * @return interrupt status
 *
*******************************************************************************/
uint32_t USB_Get_Sub_Group_0_IntStatus(void)
{
    return BL_RD_WORD(USB_BASE + USB_DEV_ISG0_OFFSET);
}

/****************************************************************************/ /**
 * @brief  get USB sub group 1 interrupt status
 *
 * @param  None
 *
 * @return interrupt status
 *
*******************************************************************************/
uint32_t USB_Get_Sub_Group_1_IntStatus(void)
{
    return BL_RD_WORD(USB_BASE + USB_DEV_ISG1_OFFSET);
}

/****************************************************************************/ /**
 * @brief  get USB sub group 2 interrupt status
 *
 * @param  None
 *
 * @return interrupt status
 *
*******************************************************************************/
uint32_t USB_Get_Sub_Group_2_IntStatus(void)
{
    return BL_RD_WORD(USB_BASE + USB_DEV_ISG2_OFFSET);
}

/****************************************************************************/ /**
 * @brief  get USB sub group 3 interrupt status
 *
 * @param  None
 *
 * @return interrupt status
 *
*******************************************************************************/
uint32_t USB_Get_Sub_Group_3_IntStatus(void)
{
    return BL_RD_WORD(USB_BASE + USB_DEV_ISG3_OFFSET);
}

/****************************************************************************/ /**
 * @brief  get USB sub group 4 interrupt status
 *
 * @param  None
 *
 * @return interrupt status
 *
*******************************************************************************/
uint32_t USB_Get_Sub_Group_4_IntStatus(void)
{
    return BL_RD_WORD(USB_BASE + USB_DEV_ISG4_OFFSET);
}

/****************************************************************************/ /**
 * @brief  get USB sub group 0 interrupt mask
 *
 * @param  None
 *
 * @return interrupt mask
 *
*******************************************************************************/
uint32_t USB_Get_Sub_Group_0_IntMask(void)
{
    return BL_RD_WORD(USB_BASE + USB_DEV_MISG0_OFFSET);
}

/****************************************************************************/ /**
 * @brief  get USB sub group 1 interrupt mask
 *
 * @param  None
 *
 * @return interrupt mask
 *
*******************************************************************************/
uint32_t USB_Get_Sub_Group_1_IntMask(void)
{
    return BL_RD_WORD(USB_BASE + USB_DEV_MISG1_OFFSET);
}

/****************************************************************************/ /**
 * @brief  get USB sub group 2 interrupt mask
 *
 * @param  None
 *
 * @return interrupt mask
 *
*******************************************************************************/
uint32_t USB_Get_Sub_Group_2_IntMask(void)
{
    return BL_RD_WORD(USB_BASE + USB_DEV_MISG2_OFFSET);
}

/****************************************************************************/ /**
 * @brief  get USB sub group 3 interrupt mask
 *
 * @param  None
 *
 * @return interrupt mask
 *
*******************************************************************************/
uint32_t USB_Get_Sub_Group_3_IntMask(void)
{
    return BL_RD_WORD(USB_BASE + USB_DEV_MISG3_OFFSET);
}

/****************************************************************************/ /**
 * @brief  get USB sub group 4 interrupt mask
 *
 * @param  None
 *
 * @return interrupt mask
 *
*******************************************************************************/
uint32_t USB_Get_Sub_Group_4_IntMask(void)
{
    return BL_RD_WORD(USB_BASE + USB_DEV_MISG4_OFFSET);
}

/****************************************************************************/ /**
 * @brief  clear USB sub group 0 interrupt status
 *
 * @param  clrVal: clear value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Get_Sub_Group_0_IntClear(uint32_t clrVal)
{
    BL_WR_WORD(USB_BASE + USB_DEV_ISG0_OFFSET, clrVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  clear USB sub group 1 interrupt status
 *
 * @param  clrVal: clear value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Get_Sub_Group_1_IntClear(uint32_t clrVal)
{
    BL_WR_WORD(USB_BASE + USB_DEV_ISG1_OFFSET, clrVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  clear USB sub group 2 interrupt status
 *
 * @param  clrVal: clear value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Get_Sub_Group_2_IntClear(uint32_t clrVal)
{
    BL_WR_WORD(USB_BASE + USB_DEV_ISG2_OFFSET, clrVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  clear USB sub group 3 interrupt status
 *
 * @param  clrVal: clear value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Get_Sub_Group_3_IntClear(uint32_t clrVal)
{
    BL_WR_WORD(USB_BASE + USB_DEV_ISG3_OFFSET, clrVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  clear USB sub group 4 interrupt status
 *
 * @param  clrVal: clear value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type USB_Get_Sub_Group_4_IntClear(uint32_t clrVal)
{
    BL_WR_WORD(USB_BASE + USB_DEV_ISG4_OFFSET, clrVal);

    return SUCCESS;
}

/*@} end of group USB_Public_Functions */

/*@} end of group USB */

/*@} end of group BL808_Peripheral_Driver */
