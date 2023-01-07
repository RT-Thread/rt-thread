/**
  ******************************************************************************
  * @file    bl808_iso11898.c
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
#include "bl808_iso11898.h"
#include "bflb_platform.h"

#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type * iso11898IntCbfArra[ISO11898_INT_ALL] = { NULL };
static void ISO11898_IntHandler(void);
static void ISO11898_IRQHandler(void);
#endif

void ISO11898_Init(void)
{
    uint32_t tmpVal;

    /* Enable ISO11898 clock witch share with UART2 */
    GLB_PER_Clock_UnGate(GLB_AHB_CLOCK_UART2);

    /* Enable UART clock*/
    tmpVal=BL_RD_REG(GLB_BASE,GLB_UART_CFG0);
    tmpVal=BL_SET_REG_BIT(tmpVal,GLB_UART_CLK_EN);
    BL_WR_REG(GLB_BASE,GLB_UART_CFG0,tmpVal);

    /* UART2 and ISO11898 can not work together */
    GLB_Set_UART2_IO_Sel(GLB_UART2_IO_SEL_ISO11898);

    /* Need to enter reset mode before operating */
    ISO11898_Mode_Set(ISO11898_MODE_TYPE_RESET, ISO11898_MODE_VALUE_RESET);

    /* Force using Peli not Basic ISO11898 */
    tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_CLOCK_DIVIDER);
    tmpVal = BL_SET_REG_BIT(tmpVal, ISO11898_MODE);
    BL_WR_REG(ISO11898_BASE, ISO11898_CLOCK_DIVIDER, tmpVal);

    /* Disable all interrupts */
    BL_WR_REG(ISO11898_BASE, ISO11898_INTERRUPT_ENABLE, 0);

    /* Set clock and sample point  */
    ISO11898_Clock_Div_Set(0);
    ISO11898_Synchronization_Jump_Width_Set(3);
    ISO11898_Sample_Parameter_Set(1, 8, 5);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(UART2_IRQn, ISO11898_IRQHandler);
#endif
}

void ISO11898_Mode_Set(ISO11898_MODE_Type type, ISO11898_MODE_VALUE_Type value)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_ISO11898_MODE_TYPE(type));
    CHECK_PARAM(IS_ISO11898_MODE_VALUE_TYPE(value));

    /* Set mode value */
    tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_MODE);
    tmpVal &= ~(1 << type);
    tmpVal |= (value << type);    

    /* Write back */
    BL_WR_REG(ISO11898_BASE, ISO11898_MODE, tmpVal);
}

ISO11898_MODE_VALUE_Type ISO11898_Mode_Get(ISO11898_MODE_Type type)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_ISO11898_MODE_TYPE(type));

    tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_MODE);
    tmpVal &= (1 << type);
    tmpVal >>= type;
    return (ISO11898_MODE_VALUE_Type)tmpVal;
}

void ISO11898_Int_Enable(ISO11898_INT_Type intType, BL_Fun_Type enable)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_ISO11898_INT_TYPE(intType));

    tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_INTERRUPT_ENABLE);
    /* Enable or Disable certain or all interrupt */
    if(ISO11898_INT_ALL == intType){
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
    BL_WR_REG(ISO11898_BASE, ISO11898_INTERRUPT_ENABLE, tmpVal);
}

void ISO11898_Cmd_Request_Transmit(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_COMMAND);
    tmpVal = BL_SET_REG_BIT(tmpVal, ISO11898_TRANSMIT_REQUEST);
    BL_WR_REG(ISO11898_BASE, ISO11898_COMMAND, tmpVal);
}
void ISO11898_Cmd_Abort_Transmit(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_COMMAND);
    tmpVal = BL_SET_REG_BIT(tmpVal, ISO11898_ABORT_TRANSMISSION);
    BL_WR_REG(ISO11898_BASE, ISO11898_COMMAND, tmpVal);
}
void ISO11898_Cmd_Release_Recv_Buff(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_COMMAND);
    tmpVal = BL_SET_REG_BIT(tmpVal, ISO11898_RELEASE_RECEIVE_BUFFER);
    BL_WR_REG(ISO11898_BASE, ISO11898_COMMAND, tmpVal);
}
void ISO11898_Cmd_Clear_Data_Overrun(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_COMMAND);
    tmpVal = BL_SET_REG_BIT(tmpVal, ISO11898_CLEAR_DATA_OVERRUN);
    BL_WR_REG(ISO11898_BASE, ISO11898_COMMAND, tmpVal);
}
void ISO11898_Cmd_Request_Self_Reception(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_COMMAND);
    tmpVal = BL_SET_REG_BIT(tmpVal, ISO11898_SELF_REQUEST);
    BL_WR_REG(ISO11898_BASE, ISO11898_COMMAND, tmpVal);
}

ISO11898_STATUS_VALUE_Type ISO11898_Status_Get(ISO11898_STATUS_Type type)
{
    volatile uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_ISO11898_STATUS_TYPE(type));

    tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_STATUS);
    tmpVal &= (1 << type);
    tmpVal >>= type;
    return (ISO11898_STATUS_VALUE_Type)tmpVal;
}

uint8_t ISO11898_Arbitration_Lost_Position_Get(void)
{
    uint8_t tmpVal;

    tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_ARB_LOST_CAPTURE);
    tmpVal = BL_GET_REG_BITS_VAL(tmpVal, ISO11898_ALC4_0);
    return tmpVal;
}

void ISO11898_Error_Get(ISO11898_ERROR_Type *const type)
{
    uint8_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_ISO11898_FRAME_FORMAT_TYPE(type));

    tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_ERROR_CODE_CAPTURE);
    type->code = BL_GET_REG_BITS_VAL(tmpVal, ISO11898_ERR_CODE);
    type->dir = BL_GET_REG_BITS_VAL(tmpVal, ISO11898_DIR);
    type->location = BL_GET_REG_BITS_VAL(tmpVal, ISO11898_SEGMENT4_0);
}

BL_Err_Type ISO11898_Error_Warning_Limit_Set(uint8_t limit)
{
    if(ISO11898_MODE_VALUE_NORMAL == ISO11898_Mode_Get(ISO11898_MODE_TYPE_RESET))
    {
        return ERROR;
    }
    BL_WR_REG(ISO11898_BASE, ISO11898_ERROR_WARNING_LIMIT, limit);
    return SUCCESS;
}

uint8_t ISO11898_Error_Warning_Limit_Get(void)
{
    return BL_RD_REG(ISO11898_BASE, ISO11898_ERROR_WARNING_LIMIT);
}

uint8_t ISO11898_Error_Rx_Counter_Get(void)
{
    return BL_RD_REG(ISO11898_BASE, ISO11898_RX_ERR_COUNT);
}

uint8_t ISO11898_Error_Tx_Counter_Get(void)
{
    return BL_RD_REG(ISO11898_BASE, ISO11898_TX_ERR_COUNT);
}

BL_Err_Type ISO11898_Transmit(const ISO11898_CFG_Type *cfg)
{
    uint32_t timeOut;
    uint32_t tmpVal;
    uint32_t i;
    volatile uint32_t *pData;
    
    /* Check the parameters */
    CHECK_PARAM(IS_ISO11898_FRAME_FORMAT_TYPE(cfg->dataAddr));
    CHECK_PARAM(IS_ISO11898_FRAME_TYPE(cfg->frameType));
    CHECK_PARAM(IS_ISO11898_FRAME_FORMAT_TYPE(cfg->frameFormat));

    timeOut = cfg->timeout;

    /* Chcek Timeout type */
    while(ISO11898_STATUS_TRANSMIT_BUFFER_LOCKED == ISO11898_Status_Get(ISO11898_STATUS_TRANSMIT_BUFFER))
    {
        /* Wait no time */
        if (cfg->timeout == 0)
        {
            return TIMEOUT;
        }
        /* Wait until transmit buffer accessible */
        if (cfg->timeout >= ISO11898_TIMEOUT_MAX)
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
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, ISO11898_INF_FF, cfg->frameFormat);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, ISO11898_INF_RTR, cfg->frameType);
    BL_WR_REG(ISO11898_BASE, ISO11898_INFORMATION, tmpVal);

    tmpVal = cfg->id;
    /* Transmit format with 11 bits ID, SFF */
    if(ISO11898_FRAME_FORMAT_STANDARD == cfg->frameFormat)
    {
        /* Config identifier registers */
        BL_WR_REG(ISO11898_BASE, ISO11898_IDENTIFIER_1, (tmpVal >> 3) & 0xFF);
        tmpVal <<= 5;
        tmpVal |= (cfg->frameType << 4);
        BL_WR_REG(ISO11898_BASE, ISO11898_IDENTIFIER_2, tmpVal & 0xFF);
        /* Config SFF data registers start address */
        pData = (uint32_t *)(ISO11898_BASE + ISO11898_SFF_DATA_1_OFFSET);
    }
    /* Transmit format with 29 bits ID, EFF */
    else
    {
        /* Config identifier registers */
        BL_WR_REG(ISO11898_BASE, ISO11898_IDENTIFIER_1, (tmpVal >> 21) & 0xFF);
        BL_WR_REG(ISO11898_BASE, ISO11898_IDENTIFIER_2, (tmpVal >> 13) & 0xFF);
        BL_WR_REG(ISO11898_BASE, ISO11898_IDENTIFIER_3, (tmpVal >> 5) & 0xFF);
        tmpVal <<= 3;
        tmpVal |= (cfg->frameType << 2);
        BL_WR_REG(ISO11898_BASE, ISO11898_IDENTIFIER_4, tmpVal & 0xFF);
        /* Config EFF data registers start address */
        pData = (uint32_t *)(ISO11898_BASE + ISO11898_EFF_DATA_1_OFFSET);
    }
    /* Move data from user buff to registers */
    for (i = 0; i < cfg->dataLen; i++)
    {
        *(pData + i) = (uint32_t)(*(cfg->dataAddr + i));
    }

    /* Trig a request for transmit */
    if(ISO11898_MODE_VALUE_RESET == ISO11898_Mode_Get(ISO11898_MODE_TYPE_RESET))
    {
        return ERROR;
    }
    else if(ISO11898_MODE_VALUE_LISTEN_ONLY == ISO11898_Mode_Get(ISO11898_MODE_TYPE_LISTEN_ONLY))
    {
        return ERROR;
    }
    else if(ISO11898_MODE_VALUE_SELF_TSET == ISO11898_Mode_Get(ISO11898_MODE_TYPE_SELF_TSET))
    {
        ISO11898_Cmd_Request_Self_Reception();
    }
    else
    {
        ISO11898_Cmd_Request_Transmit();
    }

    return SUCCESS;
}

BL_Err_Type ISO11898_Receive(ISO11898_CFG_Type *cfg)
{
    uint32_t timeOut;
    uint32_t tmpVal;
    uint32_t i;
    uint32_t id;
    volatile uint32_t *pData;

    /* Check the parameters */
    CHECK_PARAM(IS_ISO11898_FRAME_FORMAT_TYPE(cfg->dataAddr));

    timeOut = cfg->timeout;

    /* Chcek Timeout type */
    while(ISO11898_STATUS_RECEIVE_BUFFER_EMPTY == ISO11898_Status_Get(ISO11898_STATUS_RECEIVE_BUFFER))
    {
        /* Wait no time */
        if (cfg->timeout == 0)
        {
            return TIMEOUT;
        }
        /* Wait until transmit buffer accessible */
        if (cfg->timeout >= ISO11898_TIMEOUT_MAX)
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
    tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_INFORMATION);
    cfg->frameFormat = BL_GET_REG_BITS_VAL(tmpVal, ISO11898_INF_FF);
    cfg->frameType = BL_GET_REG_BITS_VAL(tmpVal, ISO11898_INF_RTR);
    cfg->dataLen = BL_GET_REG_BITS_VAL(tmpVal, ISO11898_INF_DLC);

    /* Receive with 11 bits ID */
    if(ISO11898_FRAME_FORMAT_STANDARD == cfg->frameFormat)
    {
        /* Read identifier registers */
        tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_IDENTIFIER_1);
        id = ((tmpVal & 0xFF) << 3);
        tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_IDENTIFIER_2);
        id |= (tmpVal & 0xFF) >> 5;
        /* Config SFF data registers start address */
        pData = (uint32_t *)(ISO11898_BASE + ISO11898_SFF_DATA_1_OFFSET);
    }
    /* Receive with 29 bits ID */
    else
    {
        /* Read identifier registers */
        tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_IDENTIFIER_1);
        id = ((tmpVal & 0xFF) << 21);
        tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_IDENTIFIER_2);
        id |= (tmpVal & 0xFF) << 13;
        tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_IDENTIFIER_3);
        id |= (tmpVal & 0xFF) << 5;
        tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_IDENTIFIER_4);
        id |= (tmpVal & 0xFF) >> 3;
        /* Config EFF data registers start address */
        pData = (uint32_t *)(ISO11898_BASE + ISO11898_EFF_DATA_1_OFFSET);
    }
    cfg->id = id;

    /* Move data from registers to user buff */
    for (i = 0; i < cfg->dataLen; i++)
    {
        *(cfg->dataAddr + i) = (uint8_t)(*(pData + i) & 0xFF);
    }

    ISO11898_Cmd_Release_Recv_Buff();

    return SUCCESS;
}

uint8_t ISO11898_Receive_Buff_Frame_Count_Get(void)
{
    volatile uint32_t tmpVal;

    tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_RX_MESSAGE_COUNT);
    return (uint8_t)(tmpVal & 0xFF);
}

BL_Err_Type ISO11898_Clock_Div_Set(uint8_t div)
{
    uint32_t tmpVal;

    /* Must be operated in reset mode */
    if (ISO11898_MODE_VALUE_NORMAL == ISO11898_Mode_Get(ISO11898_MODE_TYPE_RESET))
    {
        return ERROR;
    }

    tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_BUS_TIMING_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, ISO11898_BAUD_RATE_PRESCALER, div);
    BL_WR_REG(ISO11898_BASE, ISO11898_BUS_TIMING_0, tmpVal);

    return SUCCESS;
}

uint8_t ISO11898_Clock_Div_Get(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_BUS_TIMING_0);
    return (uint8_t)BL_GET_REG_BITS_VAL(tmpVal, ISO11898_BAUD_RATE_PRESCALER);
}

BL_Err_Type ISO11898_Synchronization_Jump_Width_Set(uint8_t width)
{
    uint32_t tmpVal;

    /* Must be operated in reset mode */
    if (ISO11898_MODE_VALUE_NORMAL == ISO11898_Mode_Get(ISO11898_MODE_TYPE_RESET))
    {
        return ERROR;
    }

    tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_BUS_TIMING_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, ISO11898_SYNC_JUMP_WIDTH, width);
    BL_WR_REG(ISO11898_BASE, ISO11898_BUS_TIMING_0, tmpVal);

    return SUCCESS;
}

uint8_t ISO11898_Synchronization_Jump_Width_Get(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_BUS_TIMING_0);
    return (uint8_t)BL_GET_REG_BITS_VAL(tmpVal, ISO11898_SYNC_JUMP_WIDTH);
}

BL_Err_Type ISO11898_Sample_Parameter_Set(uint8_t num, uint8_t head, uint8_t tail)
{
    uint32_t tmpVal = 0;

    /* Must be operated in reset mode */
    if (ISO11898_MODE_VALUE_NORMAL == ISO11898_Mode_Get(ISO11898_MODE_TYPE_RESET))
    {
        return ERROR;
    }

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, ISO11898_TIME_SEGMENT_1, head);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, ISO11898_TIME_SEGMENT_2, tail);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, ISO11898_SAMPLING, num);
    BL_WR_REG(ISO11898_BASE, ISO11898_BUS_TIMING_1, tmpVal & 0xFF);

    return SUCCESS;
}

void ISO11898_Sample_Parameter_Get(uint8_t *num, uint8_t *head, uint8_t *tail)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_BUS_TIMING_1);
    *head = (uint8_t)BL_GET_REG_BITS_VAL(tmpVal, ISO11898_TIME_SEGMENT_1);
    *tail = (uint8_t)BL_GET_REG_BITS_VAL(tmpVal, ISO11898_TIME_SEGMENT_2);
    *num = (uint8_t)BL_GET_REG_BITS_VAL(tmpVal, ISO11898_SAMPLING);
}

void ISO11898_Filter_Set(const ISO11898_FILTER_CFG_Type *cfg)
{
    uint8_t tmpVal[8] = {0}; //tmpVal[0~3] for match, tmpVal[4~7] for mask

    /* Config filter must be in reset mode */
    ISO11898_MODE_VALUE_Type modeReset = ISO11898_Mode_Get(ISO11898_MODE_TYPE_RESET);
    ISO11898_Mode_Set(ISO11898_MODE_TYPE_RESET, ISO11898_MODE_VALUE_RESET);


    /* Single filter mode */
    if (ISO11898_MODE_VALUE_ACCEPTANCE_FILTER_SINGLE == cfg->filterMode)
    {
        ISO11898_Mode_Set(ISO11898_MODE_TYPE_ACCEPTANCE_FILTER, ISO11898_MODE_VALUE_ACCEPTANCE_FILTER_SINGLE);
        /* Filter: ID10~0 + RTR + Data1 + Data2 */
        if (ISO11898_FRAME_FORMAT_STANDARD == cfg->formatType)
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
        else if(ISO11898_FRAME_FORMAT_EXTENDED == cfg->formatType)
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
    else if (ISO11898_MODE_VALUE_ACCEPTANCE_FILTER_DUAL == cfg->filterMode)
    {
        ISO11898_Mode_Set(ISO11898_MODE_TYPE_ACCEPTANCE_FILTER, ISO11898_MODE_VALUE_ACCEPTANCE_FILTER_DUAL);
        /* Filter1: ID10~0 + RTR + Data1 */
        /* Filter2: ID10~0 + RTR */
        if (ISO11898_FRAME_FORMAT_STANDARD == cfg->formatType)
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
        else if (ISO11898_FRAME_FORMAT_EXTENDED == cfg->formatType)
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
    BL_WR_REG(ISO11898_BASE, ISO11898_FILTER_ACCEPTANCE_0, (uint32_t)tmpVal[0]);
    BL_WR_REG(ISO11898_BASE, ISO11898_FILTER_ACCEPTANCE_1, (uint32_t)tmpVal[1]);
    BL_WR_REG(ISO11898_BASE, ISO11898_FILTER_ACCEPTANCE_2, (uint32_t)tmpVal[2]);
    BL_WR_REG(ISO11898_BASE, ISO11898_FILTER_ACCEPTANCE_3, (uint32_t)tmpVal[3]);
    BL_WR_REG(ISO11898_BASE, ISO11898_FILTER_Mask_0, (uint32_t)tmpVal[4]);
    BL_WR_REG(ISO11898_BASE, ISO11898_FILTER_Mask_1, (uint32_t)tmpVal[5]);
    BL_WR_REG(ISO11898_BASE, ISO11898_FILTER_Mask_2, (uint32_t)tmpVal[6]);
    BL_WR_REG(ISO11898_BASE, ISO11898_FILTER_Mask_3, (uint32_t)tmpVal[7]);

    /* Recovery reset mode value */
    ISO11898_Mode_Set(ISO11898_MODE_TYPE_RESET, modeReset);
}

void ISO11898_Filter_Register_Set(ISO11898_FILTER_REGISTER_Type reg, uint8_t value)
{
    /* Config filter must be in reset mode */
    ISO11898_MODE_VALUE_Type modeReset = ISO11898_Mode_Get(ISO11898_MODE_TYPE_RESET);
    ISO11898_Mode_Set(ISO11898_MODE_TYPE_RESET, ISO11898_MODE_VALUE_RESET);

    /* Write configuration to Register*/
    BL_WR_WORD(ISO11898_BASE + ISO11898_FILTER_ACCEPTANCE_0_OFFSET + 4 * reg, value);

    /* Recovery reset mode value */
    ISO11898_Mode_Set(ISO11898_MODE_TYPE_RESET, modeReset);
}

void ISO11898_Filter_Registers_Set(uint8_t *valueArr)
{
    /* Config filter must be in reset mode */
    ISO11898_MODE_VALUE_Type modeReset = ISO11898_Mode_Get(ISO11898_MODE_TYPE_RESET);
    ISO11898_Mode_Set(ISO11898_MODE_TYPE_RESET, ISO11898_MODE_VALUE_RESET);

    /* Write configuration to Registers*/
    BL_WR_REG(ISO11898_BASE, ISO11898_FILTER_ACCEPTANCE_0, (uint32_t)valueArr[0]);
    BL_WR_REG(ISO11898_BASE, ISO11898_FILTER_ACCEPTANCE_1, (uint32_t)valueArr[1]);
    BL_WR_REG(ISO11898_BASE, ISO11898_FILTER_ACCEPTANCE_2, (uint32_t)valueArr[2]);
    BL_WR_REG(ISO11898_BASE, ISO11898_FILTER_ACCEPTANCE_3, (uint32_t)valueArr[3]);
    BL_WR_REG(ISO11898_BASE, ISO11898_FILTER_Mask_0, (uint32_t)valueArr[4]);
    BL_WR_REG(ISO11898_BASE, ISO11898_FILTER_Mask_1, (uint32_t)valueArr[5]);
    BL_WR_REG(ISO11898_BASE, ISO11898_FILTER_Mask_2, (uint32_t)valueArr[6]);
    BL_WR_REG(ISO11898_BASE, ISO11898_FILTER_Mask_3, (uint32_t)valueArr[7]);

    /* Recovery reset mode value */
    ISO11898_Mode_Set(ISO11898_MODE_TYPE_RESET, modeReset);
}

#ifndef BFLB_USE_HAL_DRIVER
BL_Err_Type ISO11898_Int_Callback_Install(ISO11898_INT_Type intType,intCallback_Type* cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_ISO11898_FRAME_FORMAT_TYPE(cbFun));
    CHECK_PARAM(IS_ISO11898_INT_TYPE(intType));

    iso11898IntCbfArra[intType] = cbFun;

    return SUCCESS;
}

static void ISO11898_IntHandler(void)
{
    uint32_t tmpVal = 0;
    uint32_t i = 0;

    tmpVal = BL_RD_REG(ISO11898_BASE, ISO11898_INTERRUPT);

    for(i=0; i<ISO11898_INT_ALL; i++)
    {
        if(tmpVal & (1 << i))
        {
            if (iso11898IntCbfArra[i])
            {
                iso11898IntCbfArra[i]();
            }
        }
    }
}

void ISO11898_IRQHandler(void)
{
    ISO11898_IntHandler();
}

#endif
