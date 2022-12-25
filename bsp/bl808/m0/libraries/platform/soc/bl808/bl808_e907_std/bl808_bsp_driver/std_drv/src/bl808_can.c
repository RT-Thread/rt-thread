/**
  ******************************************************************************
  * @file    bl808_can.c
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

#include "bl808_glb.h"
#include "bl808_can.h"
#include "bflb_platform.h"

#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type * canIntCbfArra[CAN_INT_ALL] = { NULL };
static void CAN_IntHandler(void);
static void CAN_IRQHandler(void);
#endif

void CAN_Init(void)
{
    uint32_t tmpVal;

    /* Enable CAN clock witch share with UART2 */
    GLB_PER_Clock_UnGate(GLB_AHB_CLOCK_UART2);

    /* Enable UART clock*/
    tmpVal=BL_RD_REG(GLB_BASE,GLB_UART_CFG0);
    tmpVal=BL_SET_REG_BIT(tmpVal,GLB_UART_CLK_EN);
    BL_WR_REG(GLB_BASE,GLB_UART_CFG0,tmpVal);

    /* UART2 and CAN can not work together */
    GLB_Set_UART2_IO_Sel(GLB_UART2_IO_SEL_CAN_FD);

    /* Need to enter reset mode before operating */
    CAN_Mode_Set(CAN_MODE_TYPE_RESET, CAN_MODE_VALUE_RESET);

    /* Force using PeliCAN not BasicCAN */
    tmpVal = BL_RD_REG(CAN_BASE, CAN_CLOCK_DIVIDER);
    tmpVal = BL_SET_REG_BIT(tmpVal, CAN_MODE);
    BL_WR_REG(CAN_BASE, CAN_CLOCK_DIVIDER, tmpVal);

    /* Disable all interrupts */
    BL_WR_REG(CAN_BASE, CAN_INTERRUPT_ENABLE, 0);

    /* Set clock and sample point  */
    CAN_Clock_Div_Set(0);
    CAN_Synchronization_Jump_Width_Set(3);
    CAN_Sample_Parameter_Set(1, 8, 5);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(UART2_IRQn, CAN_IRQHandler);
#endif
}

void CAN_Mode_Set(CAN_MODE_Type type, CAN_MODE_VALUE_Type value)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_CAN_MODE_TYPE(type));
    CHECK_PARAM(IS_CAN_MODE_VALUE_TYPE(value));

    /* Set mode value */
    tmpVal = BL_RD_REG(CAN_BASE, CAN_MODE);
    tmpVal &= ~(1 << type);
    tmpVal |= (value << type);    

    /* Write back */
    BL_WR_REG(CAN_BASE, CAN_MODE, tmpVal);
}

CAN_MODE_VALUE_Type CAN_Mode_Get(CAN_MODE_Type type)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_CAN_MODE_TYPE(type));

    tmpVal = BL_RD_REG(CAN_BASE, CAN_MODE);
    tmpVal &= (1 << type);
    tmpVal >>= type;
    return (CAN_MODE_VALUE_Type)tmpVal;
}

void CAN_Int_Enable(CAN_INT_Type intType, BL_Fun_Type enable)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_CAN_INT_TYPE(intType));

    tmpVal = BL_RD_REG(CAN_BASE, CAN_INTERRUPT_ENABLE);
    /* Enable or Disable certain or all interrupt */
    if(CAN_INT_ALL == intType){
        if(ENABLE == enable){
            tmpVal |= 0xFF;
        }else{
            tmpVal &= 0;
        }
    }else{
        if(ENABLE == enable){
            tmpVal |= 1<<intType;
        }else{
            tmpVal &= ~(1<<intType);
        }
    }

    /* Write back */
    BL_WR_REG(CAN_BASE, CAN_INTERRUPT_ENABLE, tmpVal);
}

void CAN_Cmd_Request_Transmit(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(CAN_BASE, CAN_COMMAND);
    tmpVal = BL_SET_REG_BIT(tmpVal, CAN_TRANSMIT_REQUEST);
    BL_WR_REG(CAN_BASE, CAN_COMMAND, tmpVal);
}
void CAN_Cmd_Abort_Transmit(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(CAN_BASE, CAN_COMMAND);
    tmpVal = BL_SET_REG_BIT(tmpVal, CAN_ABORT_TRANSMISSION);
    BL_WR_REG(CAN_BASE, CAN_COMMAND, tmpVal);
}
void CAN_Cmd_Release_Recv_Buff(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(CAN_BASE, CAN_COMMAND);
    tmpVal = BL_SET_REG_BIT(tmpVal, CAN_RELEASE_RECEIVE_BUFFER);
    BL_WR_REG(CAN_BASE, CAN_COMMAND, tmpVal);
}
void CAN_Cmd_Clear_Data_Overrun(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(CAN_BASE, CAN_COMMAND);
    tmpVal = BL_SET_REG_BIT(tmpVal, CAN_CLEAR_DATA_OVERRUN);
    BL_WR_REG(CAN_BASE, CAN_COMMAND, tmpVal);
}
void CAN_Cmd_Request_Self_Reception(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(CAN_BASE, CAN_COMMAND);
    tmpVal = BL_SET_REG_BIT(tmpVal, CAN_SELF_REQUEST);
    BL_WR_REG(CAN_BASE, CAN_COMMAND, tmpVal);
}

CAN_STATUS_VALUE_Type CAN_Status_Get(CAN_STATUS_Type type)
{
    volatile uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_CAN_STATUS_TYPE(type));

    tmpVal = BL_RD_REG(CAN_BASE, CAN_STATUS);
    tmpVal &= (1 << type);
    tmpVal >>= type;
    return (CAN_STATUS_VALUE_Type)tmpVal;
}

uint8_t CAN_Arbitration_Lost_Position_Get(void)
{
    uint8_t tmpVal;

    tmpVal = BL_RD_REG(CAN_BASE, CAN_ARB_LOST_CAPTURE);
    tmpVal = BL_GET_REG_BITS_VAL(tmpVal, CAN_ALC4_0);
    return tmpVal;
}

void CAN_Error_Get(CAN_ERROR_Type *const type)
{
    uint8_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_CAN_FRAME_FORMAT_TYPE(type));

    tmpVal = BL_RD_REG(CAN_BASE, CAN_ERROR_CODE_CAPTURE);
    type->code = BL_GET_REG_BITS_VAL(tmpVal, CAN_ERR_CODE);
    type->dir = BL_GET_REG_BITS_VAL(tmpVal, CAN_DIR);
    type->location = BL_GET_REG_BITS_VAL(tmpVal, CAN_SEGMENT4_0);
}

BL_Err_Type CAN_Error_Warning_Limit_Set(uint8_t limit)
{
    if(CAN_MODE_VALUE_NORMAL == CAN_Mode_Get(CAN_MODE_TYPE_RESET))
    {
        return ERROR;
    }
    BL_WR_REG(CAN_BASE, CAN_ERROR_WARNING_LIMIT, limit);
    return SUCCESS;
}

uint8_t CAN_Error_Warning_Limit_Get(void)
{
    return BL_RD_REG(CAN_BASE, CAN_ERROR_WARNING_LIMIT);
}

uint8_t CAN_Error_Rx_Counter_Get(void)
{
    return BL_RD_REG(CAN_BASE, CAN_RX_ERR_COUNT);
}

uint8_t CAN_Error_Tx_Counter_Get(void)
{
    return BL_RD_REG(CAN_BASE, CAN_TX_ERR_COUNT);
}

BL_Err_Type CAN_Transmit(const CAN_CFG_Type *cfg)
{
    uint32_t timeOut;
    uint32_t tmpVal;
    uint32_t i;
    volatile uint32_t *pData;
    
    /* Check the parameters */
    CHECK_PARAM(IS_CAN_FRAME_FORMAT_TYPE(cfg->dataAddr));
    CHECK_PARAM(IS_CAN_FRAME_TYPE(cfg->frameType));
    CHECK_PARAM(IS_CAN_FRAME_FORMAT_TYPE(cfg->frameFormat));

    timeOut = cfg->timeout;

    /* Chcek Timeout type */
    while(CAN_STATUS_TRANSMIT_BUFFER_LOCKED == CAN_Status_Get(CAN_STATUS_TRANSMIT_BUFFER))
    {
        /* Wait no time */
        if (cfg->timeout == 0)
        {
            return TIMEOUT;
        }
        /* Wait until transmit buffer accessible */
        if (cfg->timeout >= CAN_TIMEOUT_MAX)
        {

        }
        /* Wait time = cfg->timeOut */
        else
        {
            if(timeOut == 0)
            {
                return TIMEOUT;
            }
            timeOut--;
        }
    }

    /* Config information register */
    tmpVal = cfg->dataLen;
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAN_INF_FF, cfg->frameFormat);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAN_INF_RTR, cfg->frameType);
    BL_WR_REG(CAN_BASE, CAN_INFORMATION, tmpVal);

    tmpVal = cfg->id;
    /* Transmit format with 11 bits ID, SFF */
    if(CAN_FRAME_FORMAT_STANDARD == cfg->frameFormat)
    {
        /* Config identifier registers */
        BL_WR_REG(CAN_BASE, CAN_IDENTIFIER_1, (tmpVal >> 3) & 0xFF);
        tmpVal <<= 5;
        tmpVal |= (cfg->frameType << 4);
        BL_WR_REG(CAN_BASE, CAN_IDENTIFIER_2, tmpVal & 0xFF);
        /* Config SFF data registers start address */
        pData = (uint32_t *)(CAN_BASE + CAN_SFF_DATA_1_OFFSET);
    }
    /* Transmit format with 29 bits ID, EFF */
    else
    {
        /* Config identifier registers */
        BL_WR_REG(CAN_BASE, CAN_IDENTIFIER_1, (tmpVal >> 21) & 0xFF);
        BL_WR_REG(CAN_BASE, CAN_IDENTIFIER_2, (tmpVal >> 13) & 0xFF);
        BL_WR_REG(CAN_BASE, CAN_IDENTIFIER_3, (tmpVal >> 5) & 0xFF);
        tmpVal <<= 3;
        tmpVal |= (cfg->frameType << 2);
        BL_WR_REG(CAN_BASE, CAN_IDENTIFIER_4, tmpVal & 0xFF);
        /* Config EFF data registers start address */
        pData = (uint32_t *)(CAN_BASE + CAN_EFF_DATA_1_OFFSET);
    }
    /* Move data from user buff to registers */
    for (i = 0; i < cfg->dataLen; i++)
    {
        *(pData + i) = (uint32_t)(*(cfg->dataAddr + i));
    }

    /* Trig a request for transmit */
    if(CAN_MODE_VALUE_RESET == CAN_Mode_Get(CAN_MODE_TYPE_RESET))
    {
        return ERROR;
    }
    else if(CAN_MODE_VALUE_LISTEN_ONLY == CAN_Mode_Get(CAN_MODE_TYPE_LISTEN_ONLY))
    {
        return ERROR;
    }
    else if(CAN_MODE_VALUE_SELF_TSET == CAN_Mode_Get(CAN_MODE_TYPE_SELF_TSET))
    {
        CAN_Cmd_Request_Self_Reception();
    }
    else
    {
        CAN_Cmd_Request_Transmit();
    }

    return SUCCESS;
}

BL_Err_Type CAN_Receive(CAN_CFG_Type *cfg)
{
    uint32_t timeOut;
    uint32_t tmpVal;
    uint32_t i;
    uint32_t id;
    volatile uint32_t *pData;

    /* Check the parameters */
    CHECK_PARAM(IS_CAN_FRAME_FORMAT_TYPE(cfg->dataAddr));

    timeOut = cfg->timeout;

    /* Chcek Timeout type */
    while(CAN_STATUS_RECEIVE_BUFFER_EMPTY == CAN_Status_Get(CAN_STATUS_RECEIVE_BUFFER))
    {
        /* Wait no time */
        if (cfg->timeout == 0)
        {
            return TIMEOUT;
        }
        /* Wait until transmit buffer accessible */
        if (cfg->timeout >= CAN_TIMEOUT_MAX)
        {

        }
        /* Wait time = cfg->timeOut */
        else
        {
            if(timeOut == 0)
            {
                return TIMEOUT;
            }
            timeOut--;
        }
    }

    /* Read information register */
    tmpVal = BL_RD_REG(CAN_BASE, CAN_INFORMATION);
    cfg->frameFormat = BL_GET_REG_BITS_VAL(tmpVal, CAN_INF_FF);
    cfg->frameType = BL_GET_REG_BITS_VAL(tmpVal, CAN_INF_RTR);
    cfg->dataLen = BL_GET_REG_BITS_VAL(tmpVal, CAN_INF_DLC);

    /* Receive with 11 bits ID */
    if(CAN_FRAME_FORMAT_STANDARD == cfg->frameFormat)
    {
        /* Read identifier registers */
        tmpVal = BL_RD_REG(CAN_BASE, CAN_IDENTIFIER_1);
        id = ((tmpVal & 0xFF) << 3);
        tmpVal = BL_RD_REG(CAN_BASE, CAN_IDENTIFIER_2);
        id |= (tmpVal & 0xFF) >> 5;
        /* Config SFF data registers start address */
        pData = (uint32_t *)(CAN_BASE + CAN_SFF_DATA_1_OFFSET);
    }
    /* Receive with 29 bits ID */
    else
    {
        /* Read identifier registers */
        tmpVal = BL_RD_REG(CAN_BASE, CAN_IDENTIFIER_1);
        id = ((tmpVal & 0xFF) << 21);
        tmpVal = BL_RD_REG(CAN_BASE, CAN_IDENTIFIER_2);
        id |= (tmpVal & 0xFF) << 13;
        tmpVal = BL_RD_REG(CAN_BASE, CAN_IDENTIFIER_3);
        id |= (tmpVal & 0xFF) << 5;
        tmpVal = BL_RD_REG(CAN_BASE, CAN_IDENTIFIER_4);
        id |= (tmpVal & 0xFF) >> 3;
        /* Config EFF data registers start address */
        pData = (uint32_t *)(CAN_BASE + CAN_EFF_DATA_1_OFFSET);
    }
    cfg->id = id;

    /* Move data from registers to user buff */
    for (i = 0; i < cfg->dataLen; i++)
    {
        *(cfg->dataAddr + i) = (uint8_t)(*(pData + i) & 0xFF);
    }

    CAN_Cmd_Release_Recv_Buff();

    return SUCCESS;
}

uint8_t CAN_Receive_Buff_Frame_Count_Get(void)
{
    volatile uint32_t tmpVal;

    tmpVal = BL_RD_REG(CAN_BASE, CAN_RX_MESSAGE_COUNT);
    return (uint8_t)(tmpVal & 0xFF);
}

BL_Err_Type CAN_Clock_Div_Set(uint8_t div)
{
    uint32_t tmpVal;

    /* Must be operated in reset mode */
    if (CAN_MODE_VALUE_NORMAL == CAN_Mode_Get(CAN_MODE_TYPE_RESET))
    {
        return ERROR;
    }

    tmpVal = BL_RD_REG(CAN_BASE, CAN_BUS_TIMING_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAN_BAUD_RATE_PRESCALER, div);
    BL_WR_REG(CAN_BASE, CAN_BUS_TIMING_0, tmpVal);

    return SUCCESS;
}

uint8_t CAN_Clock_Div_Get(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(CAN_BASE, CAN_BUS_TIMING_0);
    return (uint8_t)BL_GET_REG_BITS_VAL(tmpVal, CAN_BAUD_RATE_PRESCALER);
}

BL_Err_Type CAN_Synchronization_Jump_Width_Set(uint8_t width)
{
    uint32_t tmpVal;

    /* Must be operated in reset mode */
    if (CAN_MODE_VALUE_NORMAL == CAN_Mode_Get(CAN_MODE_TYPE_RESET))
    {
        return ERROR;
    }

    tmpVal = BL_RD_REG(CAN_BASE, CAN_BUS_TIMING_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAN_SYNC_JUMP_WIDTH, width);
    BL_WR_REG(CAN_BASE, CAN_BUS_TIMING_0, tmpVal);

    return SUCCESS;
}

uint8_t CAN_Synchronization_Jump_Width_Get(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(CAN_BASE, CAN_BUS_TIMING_0);
    return (uint8_t)BL_GET_REG_BITS_VAL(tmpVal, CAN_SYNC_JUMP_WIDTH);
}

BL_Err_Type CAN_Sample_Parameter_Set(uint8_t num, uint8_t head, uint8_t tail)
{
    uint32_t tmpVal = 0;

    /* Must be operated in reset mode */
    if (CAN_MODE_VALUE_NORMAL == CAN_Mode_Get(CAN_MODE_TYPE_RESET))
    {
        return ERROR;
    }

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAN_TIME_SEGMENT_1, head);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAN_TIME_SEGMENT_2, tail);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CAN_SAMPLING, num);
    BL_WR_REG(CAN_BASE, CAN_BUS_TIMING_1, tmpVal & 0xFF);

    return SUCCESS;
}

void CAN_Sample_Parameter_Get(uint8_t *num, uint8_t *head, uint8_t *tail)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(CAN_BASE, CAN_BUS_TIMING_1);
    *head = (uint8_t)BL_GET_REG_BITS_VAL(tmpVal, CAN_TIME_SEGMENT_1);
    *tail = (uint8_t)BL_GET_REG_BITS_VAL(tmpVal, CAN_TIME_SEGMENT_2);
    *num = (uint8_t)BL_GET_REG_BITS_VAL(tmpVal, CAN_SAMPLING);
}

void CAN_Filter_Set(const CAN_FILTER_CFG_Type *cfg)
{
    uint8_t tmpVal[8] = {0}; //tmpVal[0~3] for match, tmpVal[4~7] for mask

    /* Config filter must be in reset mode */
    CAN_MODE_VALUE_Type modeReset = CAN_Mode_Get(CAN_MODE_TYPE_RESET);
    CAN_Mode_Set(CAN_MODE_TYPE_RESET, CAN_MODE_VALUE_RESET);


    /* Single filter mode */
    if (CAN_MODE_VALUE_ACCEPTANCE_FILTER_SINGLE == cfg->filterMode)
    {
        CAN_Mode_Set(CAN_MODE_TYPE_ACCEPTANCE_FILTER, CAN_MODE_VALUE_ACCEPTANCE_FILTER_SINGLE);
        /* Filter: ID10~0 + RTR + Data1 + Data2 */
        if (CAN_FRAME_FORMAT_STANDARD == cfg->formatType)
        {
            tmpVal[0] = (uint8_t)(cfg->matchId1 >> 3);
            tmpVal[1] = (uint8_t)(cfg->matchId1 << 5);
            tmpVal[1] |= (uint8_t)(cfg->matchRtr1 << 4);
            tmpVal[2] = cfg->matchData1;
            tmpVal[3] = cfg->matchData2;
            tmpVal[4] = (uint8_t)(cfg->maskId1 >> 3);
            tmpVal[5] = (uint8_t)(cfg->maskId1 << 5);
            tmpVal[5] |= (uint8_t)(cfg->maskRtr1 << 4);
            tmpVal[5] |= (uint8_t)0x0F;//0b1111 for unused bit 3:0
            tmpVal[6] = cfg->maskData1;
            tmpVal[7] = cfg->maskData2;
        }
        /* Filter: ID28~0 + RTR */
        else if(CAN_FRAME_FORMAT_EXTENDED == cfg->formatType)
        {
            tmpVal[0] = (uint8_t)(cfg->matchId1 >> 21);
            tmpVal[1] = (uint8_t)(cfg->matchId1 >> 13);
            tmpVal[2] = (uint8_t)(cfg->matchId1 >> 5);
            tmpVal[3] = (uint8_t)(cfg->matchId1 << 3);
            tmpVal[3] |= (uint8_t)(cfg->matchRtr1 << 2);
            tmpVal[4] = (uint8_t)(cfg->maskId1 >> 21);
            tmpVal[5] = (uint8_t)(cfg->maskId1 >> 13);
            tmpVal[6] = (uint8_t)(cfg->maskId1 >> 5);
            tmpVal[7] = (uint8_t)(cfg->maskId1 << 3);
            tmpVal[7] |= (uint8_t)(cfg->maskRtr1 << 2);
            tmpVal[7] |= (uint8_t)0x03;//0b11 for unused bit 1:0
        }
    }
    /* Dual filter mode */
    else if (CAN_MODE_VALUE_ACCEPTANCE_FILTER_DUAL == cfg->filterMode)
    {
        CAN_Mode_Set(CAN_MODE_TYPE_ACCEPTANCE_FILTER, CAN_MODE_VALUE_ACCEPTANCE_FILTER_DUAL);
        /* Filter1: ID10~0 + RTR + Data1 */
        /* Filter2: ID10~0 + RTR */
        if (CAN_FRAME_FORMAT_STANDARD == cfg->formatType)
        {
            tmpVal[0] = (uint8_t)(cfg->matchId1 >> 3);
            tmpVal[1] = (uint8_t)(cfg->matchId1 << 5);
            tmpVal[1] |= (uint8_t)(cfg->matchRtr1 << 4);
            tmpVal[1] |= (cfg->matchData1 >> 4);
            tmpVal[2] = (uint8_t)(cfg->matchId2 >> 3);
            tmpVal[3] = (uint8_t)(cfg->matchId2 << 5);
            tmpVal[3] |= (uint8_t)(cfg->matchRtr2 << 4);
            tmpVal[3] |= (cfg->matchData1 & 0xF);
            tmpVal[4] = (uint8_t)(cfg->maskId1 >> 3);
            tmpVal[5] = (uint8_t)(cfg->maskId1 << 5);
            tmpVal[5] |= (uint8_t)(cfg->maskRtr1 << 4);
            tmpVal[5] |= (cfg->maskData1 >> 4);
            tmpVal[6] = (uint8_t)(cfg->maskId2 >> 3);
            tmpVal[7] = (uint8_t)(cfg->maskId2 << 5);
            tmpVal[7] |= (uint8_t)(cfg->maskRtr2 << 4);
            tmpVal[7] |= (cfg->maskData1 & 0xF);
        }
        /* Filter1: ID28~13 */
        /* Filter2: ID28~13 */
        else if (CAN_FRAME_FORMAT_EXTENDED == cfg->formatType)
        {
            tmpVal[0] = (uint8_t)(cfg->matchId1 >> 21);
            tmpVal[1] = (uint8_t)(cfg->matchId1 >> 13);
            tmpVal[2] = (uint8_t)(cfg->matchId2 >> 21);
            tmpVal[3] = (uint8_t)(cfg->matchId2 >> 13);
            tmpVal[4] = (uint8_t)(cfg->maskId1 >> 21);
            tmpVal[5] = (uint8_t)(cfg->maskId1 >> 13);
            tmpVal[6] = (uint8_t)(cfg->maskId2 >> 21);
            tmpVal[7] = (uint8_t)(cfg->maskId2 >> 13);
        }
    }
    /* Write configuration to Registers*/
    BL_WR_REG(CAN_BASE, CAN_FILTER_ACCEPTANCE_0, (uint32_t)tmpVal[0]);
    BL_WR_REG(CAN_BASE, CAN_FILTER_ACCEPTANCE_1, (uint32_t)tmpVal[1]);
    BL_WR_REG(CAN_BASE, CAN_FILTER_ACCEPTANCE_2, (uint32_t)tmpVal[2]);
    BL_WR_REG(CAN_BASE, CAN_FILTER_ACCEPTANCE_3, (uint32_t)tmpVal[3]);
    BL_WR_REG(CAN_BASE, CAN_FILTER_Mask_0, (uint32_t)tmpVal[4]);
    BL_WR_REG(CAN_BASE, CAN_FILTER_Mask_1, (uint32_t)tmpVal[5]);
    BL_WR_REG(CAN_BASE, CAN_FILTER_Mask_2, (uint32_t)tmpVal[6]);
    BL_WR_REG(CAN_BASE, CAN_FILTER_Mask_3, (uint32_t)tmpVal[7]);

    /* Recovery reset mode value */
    CAN_Mode_Set(CAN_MODE_TYPE_RESET, modeReset);
}

void CAN_Filter_Register_Set(CAN_FILTER_REGISTER_Type reg, uint8_t value)
{
    /* Config filter must be in reset mode */
    CAN_MODE_VALUE_Type modeReset = CAN_Mode_Get(CAN_MODE_TYPE_RESET);
    CAN_Mode_Set(CAN_MODE_TYPE_RESET, CAN_MODE_VALUE_RESET);

    /* Write configuration to Register*/
    BL_WR_WORD(CAN_BASE + CAN_FILTER_ACCEPTANCE_0_OFFSET + 4 * reg, value);

    /* Recovery reset mode value */
    CAN_Mode_Set(CAN_MODE_TYPE_RESET, modeReset);
}

void CAN_Filter_Registers_Set(uint8_t *valueArr)
{
    /* Config filter must be in reset mode */
    CAN_MODE_VALUE_Type modeReset = CAN_Mode_Get(CAN_MODE_TYPE_RESET);
    CAN_Mode_Set(CAN_MODE_TYPE_RESET, CAN_MODE_VALUE_RESET);

    /* Write configuration to Registers*/
    BL_WR_REG(CAN_BASE, CAN_FILTER_ACCEPTANCE_0, (uint32_t)valueArr[0]);
    BL_WR_REG(CAN_BASE, CAN_FILTER_ACCEPTANCE_1, (uint32_t)valueArr[1]);
    BL_WR_REG(CAN_BASE, CAN_FILTER_ACCEPTANCE_2, (uint32_t)valueArr[2]);
    BL_WR_REG(CAN_BASE, CAN_FILTER_ACCEPTANCE_3, (uint32_t)valueArr[3]);
    BL_WR_REG(CAN_BASE, CAN_FILTER_Mask_0, (uint32_t)valueArr[4]);
    BL_WR_REG(CAN_BASE, CAN_FILTER_Mask_1, (uint32_t)valueArr[5]);
    BL_WR_REG(CAN_BASE, CAN_FILTER_Mask_2, (uint32_t)valueArr[6]);
    BL_WR_REG(CAN_BASE, CAN_FILTER_Mask_3, (uint32_t)valueArr[7]);

    /* Recovery reset mode value */
    CAN_Mode_Set(CAN_MODE_TYPE_RESET, modeReset);
}

#ifndef BFLB_USE_HAL_DRIVER
BL_Err_Type CAN_Int_Callback_Install(CAN_INT_Type intType,intCallback_Type* cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_CAN_FRAME_FORMAT_TYPE(cbFun));
    CHECK_PARAM(IS_CAN_INT_TYPE(intType));

    canIntCbfArra[intType] = cbFun;

    return SUCCESS;
}

static void CAN_IntHandler(void)
{
    uint32_t tmpVal = 0;
    uint32_t i = 0;

    tmpVal = BL_RD_REG(CAN_BASE, CAN_INTERRUPT);

    for(i=0; i<CAN_INT_ALL; i++)
    {
        if(tmpVal & (1 << i))
        {
            if (canIntCbfArra[i])
            {
                canIntCbfArra[i]();
            }
        }
    }
}

void CAN_IRQHandler(void)
{
    CAN_IntHandler();
}

#endif
