/*
 * Copyright (c) 2022 OpenLuat & AirM2M
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "user.h"

#define IIC_DBG DBG
enum
{
    I2C_STATE_FREE,
    I2C_STATE_INIT_STOP,
    I2C_STATE_ERROR_STOP,
    I2C_STATE_WRITE_ADDRESS,
    I2C_STATE_WRITE_REG,
    I2C_STATE_WRITE_DATA,
    I2C_STATE_WRITE_STOP,
    I2C_STATE_READ_ADDRESS_WR,
    I2C_STATE_READ_REG_WR,
    I2C_STATE_READ_ADDRESS_RD,
    I2C_STATE_READ_DATA_RD,
    I2C_STATE_READ_STOP,
};

typedef struct
{
    const I2C_TypeDef *RegBase;
    const int IrqLine;
    Buffer_Struct DataBuf;
    CBFuncEx_t Callback;
    void *pParam;
    HANDLE Sem;
    I2C_CommonRegDataStruct *RegQueue;
    uint32_t TotalQueueNum;
    uint32_t CurQueuePos;
    int32_t Result;
    uint16_t TimeoutMs;
    uint16_t ChipAddress;
    uint8_t ChipAddressLen;
    uint8_t RegAddress;
    uint8_t State;
    uint8_t IsBusy;
    uint8_t IsBlockMode;
}I2C_CtrlStruct;
static I2C_CtrlStruct prvI2C = {
        I2C0,
        I2C0_IRQn,
};

static void prvI2C_Done(int32_t Result)
{
    prvI2C.State = I2C_STATE_FREE;
    prvI2C.Result = Result;
    prvI2C.IsBusy = 0;
#ifdef __BUILD_OS__
    if (prvI2C.IsBlockMode) OS_MutexRelease(prvI2C.Sem);
#endif
    prvI2C.Callback(I2C_ID0, prvI2C.pParam);
}

static int32_t prvI2C_DummyCB(void *pData, void *pParam)
{
    prvI2C.IsBusy = 0;
}

static void I2C_IrqHandle(int32_t IrqLine, void *pData)
{
    int32_t result = ERROR_NONE;
    I2C_TypeDef *I2C = prvI2C.RegBase;
    uint32_t Source = I2C->IC_TX_ABRT_SOURCE;
    uint32_t State = I2C->IC_RAW_INTR_STAT;
    uint32_t RegValue = I2C->IC_CLR_INTR;

    if (Source & 0x0000ffff)
    {
        result = -ERROR_OPERATION_FAILED;
        goto I2C_DONE;
    }

    switch(prvI2C.State)
    {
    case I2C_STATE_WRITE_ADDRESS:
    case I2C_STATE_WRITE_REG:
    case I2C_STATE_WRITE_DATA:
        if (State & I2C_IT_TXE)
        {
            if (prvI2C.DataBuf.Pos >= prvI2C.DataBuf.MaxLen)
            {
                goto I2C_DONE;
            }
            else if ((prvI2C.DataBuf.MaxLen - prvI2C.DataBuf.Pos) > 1)
            {
                I2C->IC_DATA_CMD = prvI2C.DataBuf.Data[prvI2C.DataBuf.Pos];
            }
            else
            {
                I2C->IC_DATA_CMD = prvI2C.DataBuf.Data[prvI2C.DataBuf.Pos]|I2C_IC_DATA_CMD_STOP;
            }
            prvI2C.DataBuf.Pos++;
        }
        break;
    case I2C_STATE_READ_ADDRESS_WR:
        if (State & I2C_IT_TXE)
        {
            prvI2C.State = I2C_STATE_READ_ADDRESS_RD;
            if ((prvI2C.DataBuf.MaxLen - prvI2C.DataBuf.Pos) > 1)
            {
                I2C->IC_DATA_CMD = I2C_IC_DATA_CMD_CMD;
            }
            else
            {
                I2C->IC_DATA_CMD = I2C_IC_DATA_CMD_CMD|I2C_IC_DATA_CMD_STOP;
            }
            I2C->IC_INTR_MASK = I2C_IC_INTR_MASK_M_RX_FULL|I2C_IC_INTR_MASK_M_STOP_DET;
        }
        break;
    case I2C_STATE_READ_ADDRESS_RD:
        prvI2C.State = I2C_STATE_READ_DATA_RD;
    case I2C_STATE_READ_DATA_RD:
        if (State & I2C_IT_RXF)
        {
            prvI2C.DataBuf.Data[prvI2C.DataBuf.Pos] = I2C->IC_DATA_CMD & 0x00ff;
            prvI2C.DataBuf.Pos++;
            if (prvI2C.DataBuf.Pos >= prvI2C.DataBuf.MaxLen)
            {
                goto I2C_DONE;
            }
            else if ((prvI2C.DataBuf.MaxLen - prvI2C.DataBuf.Pos) > 1)
            {
                I2C->IC_DATA_CMD = I2C_IC_DATA_CMD_CMD;
            }
            else
            {
                I2C->IC_DATA_CMD = I2C_IC_DATA_CMD_CMD|I2C_IC_DATA_CMD_STOP;
            }
        }
        break;
    default:
        break;
    }
    return;
I2C_DONE:
    I2C->IC_INTR_MASK = 0;
    prvI2C_Done(result);
}

static void I2C_IrqHandleRegQueue(int32_t IrqLine, void *pData)
{
    int32_t result = ERROR_NONE;
    I2C_TypeDef *I2C = prvI2C.RegBase;
    uint32_t Source = I2C->IC_TX_ABRT_SOURCE;
    uint32_t State = I2C->IC_RAW_INTR_STAT;
    uint32_t RegValue = I2C->IC_CLR_INTR;

    if (Source & 0x0000ffff)
    {

        result = -ERROR_OPERATION_FAILED;
        goto I2C_DONE;
    }

    if (State & I2C_IT_TXE)
    {
        if (prvI2C.DataBuf.Pos >= prvI2C.DataBuf.MaxLen)
        {
            prvI2C.CurQueuePos++;
            if (prvI2C.CurQueuePos >= prvI2C.TotalQueueNum)
            {
                goto I2C_DONE;
            }
            else
            {
                Buffer_StaticInit(&prvI2C.DataBuf, prvI2C.RegQueue[prvI2C.CurQueuePos].Data, 2);
                I2C->IC_DATA_CMD = prvI2C.DataBuf.Data[0];
                prvI2C.DataBuf.Pos++;
                I2C->IC_INTR_MASK = I2C_IC_INTR_MASK_M_TX_EMPTY|I2C_IC_INTR_MASK_M_STOP_DET;
            }

        }
        else if ((prvI2C.DataBuf.MaxLen - prvI2C.DataBuf.Pos) > 1)
        {
            I2C->IC_DATA_CMD = prvI2C.DataBuf.Data[prvI2C.DataBuf.Pos];
        }
        else
        {
            I2C->IC_DATA_CMD = prvI2C.DataBuf.Data[prvI2C.DataBuf.Pos]|I2C_IC_DATA_CMD_STOP;
        }
        prvI2C.DataBuf.Pos++;
    }
    return;
I2C_DONE:
    I2C->IC_INTR_MASK = 0;
    prvI2C_Done(result);
}

void I2C_GlobalInit(void)
{
    prvI2C.Callback = prvI2C_DummyCB;
    ISR_SetHandler(prvI2C.IrqLine, I2C_IrqHandle, NULL);
#ifdef __BUILD_OS__
    prvI2C.Sem = OS_MutexCreate();
    ISR_SetPriority(prvI2C.IrqLine, configLIBRARY_LOWEST_INTERRUPT_PRIORITY - 1);
#else
    ISR_SetPriority(prvI2C.IrqLine, 7);
#endif
}

void I2C_MasterSetup(uint8_t I2CID, uint32_t Speed)
{
    I2C_TypeDef *I2C = prvI2C.RegBase;
    uint32_t Cnt = ((SystemCoreClock >> 3) / Speed);
    I2C->IC_ENABLE = 0;
    while(I2C->IC_ENABLE_STATUS & I2C_IC_ENABLE_STATUS_IC_EN){;}
    I2C->IC_SDA_HOLD = 5;
    I2C->IC_SDA_SETUP = Cnt/3;
    switch(Speed)
    {
    case 100000:
        I2C->IC_SS_SCL_HCNT = Cnt - I2C->IC_FS_SPKLEN;
        I2C->IC_SS_SCL_LCNT = Cnt;
        I2C->IC_CON = I2C_IC_CON_RESTART_EN|I2C_IC_CON_SPEED_0|I2C_IC_CON_MASTER_MODE|I2C_IC_CON_SLAVE_DISABLE;
        break;
    case 400000:
        I2C->IC_FS_SCL_HCNT = Cnt - I2C->IC_FS_SPKLEN;
        I2C->IC_FS_SCL_LCNT = Cnt;
        I2C->IC_CON = I2C_IC_CON_RESTART_EN|I2C_IC_CON_SPEED_1|I2C_IC_CON_MASTER_MODE|I2C_IC_CON_SLAVE_DISABLE;
        break;
    }
    I2C->IC_ENABLE = 1;
    I2C->IC_RX_TL = 0;
    I2C->IC_TX_TL = 0;
    I2C->IC_INTR_MASK = 0;
    return;
}

void I2C_Prepare(uint8_t I2CID, uint16_t ChipAddress, uint8_t ChipAddressLen, CBFuncEx_t CB, void *pParam)
{
    I2C_TypeDef *I2C = prvI2C.RegBase;
    I2C->IC_ENABLE = 0;
    while(I2C->IC_ENABLE_STATUS & I2C_IC_ENABLE_STATUS_IC_EN){;}

    switch(ChipAddressLen)
    {
    case 1:
        I2C->IC_TAR = ChipAddress & 0x00ff;
        I2C->IC_SAR = ChipAddress & 0x00ff;
        break;
    case 2:
        I2C->IC_TAR = I2C_IC_TAR_10BITADDR_MASTER | (ChipAddress & I2C_IC_TAR_TAR);
        I2C->IC_SAR = ChipAddress;
        break;
    }
    I2C->IC_ENABLE = 1;
    if (CB)
    {
        prvI2C.Callback = CB;
    }
    else
    {
        prvI2C.Callback = prvI2C_DummyCB;
    }
    prvI2C.pParam = pParam;
}

void I2C_MasterXfer(uint8_t I2CID, uint8_t Operate, uint8_t RegAddress, uint8_t *Data, uint32_t Len, uint16_t Toms)
{
    I2C_TypeDef *I2C = prvI2C.RegBase;
    uint32_t RegValue;
    I2C->IC_INTR_MASK = 0;
    ISR_OnOff(prvI2C.IrqLine, 0);
    if (prvI2C.IsBusy)
    {
        I2C->IC_ENABLE |= I2C_IC_ENABLE_ABORT;
        prvI2C.IsBusy = 0;
        prvI2C.Result = -ERROR_OPERATION_FAILED;
        prvI2C.Callback(I2C_ID0, prvI2C.pParam);
        while(I2C->IC_ENABLE & I2C_IC_ENABLE_ABORT){;}
    }
    ISR_SetHandler(prvI2C.IrqLine, I2C_IrqHandle, NULL);
    prvI2C.IsBusy = 1;
    if (Toms)
    {
        prvI2C.TimeoutMs = Toms;
    }
    else
    {
        prvI2C.TimeoutMs = 50;
    }
    Buffer_StaticInit(&prvI2C.DataBuf, Data, Len);
    prvI2C.RegQueue = NULL;
    RegValue = I2C->IC_CLR_INTR;
    switch(Operate)
    {
    case I2C_OP_READ_REG:

        prvI2C.State = I2C_STATE_READ_ADDRESS_WR;
        I2C->IC_DATA_CMD = I2C_IC_DATA_CMD_RESTART|RegAddress;
        I2C->IC_INTR_MASK = I2C_IC_INTR_MASK_M_TX_EMPTY|I2C_IC_INTR_MASK_M_STOP_DET;
        break;
    case I2C_OP_READ:
        prvI2C.State = I2C_STATE_READ_ADDRESS_RD;
        if ((prvI2C.DataBuf.MaxLen - prvI2C.DataBuf.Pos) > 1)
        {
            I2C->IC_DATA_CMD = I2C_IC_DATA_CMD_CMD;
        }
        else
        {
            I2C->IC_DATA_CMD = I2C_IC_DATA_CMD_CMD|I2C_IC_DATA_CMD_STOP;
        }
        I2C->IC_INTR_MASK = I2C_IC_INTR_MASK_M_RX_FULL|I2C_IC_INTR_MASK_M_STOP_DET;
        break;
    case I2C_OP_WRITE:
        prvI2C.State = I2C_STATE_WRITE_ADDRESS;
        if ((prvI2C.DataBuf.MaxLen - prvI2C.DataBuf.Pos) > 1)
        {
            I2C->IC_DATA_CMD = prvI2C.DataBuf.Data[0];
        }
        else
        {
            I2C->IC_DATA_CMD = prvI2C.DataBuf.Data[0]|I2C_IC_DATA_CMD_STOP;
        }
        prvI2C.DataBuf.Pos++;
        I2C->IC_INTR_MASK = I2C_IC_INTR_MASK_M_TX_EMPTY|I2C_IC_INTR_MASK_M_STOP_DET;
        break;
    default:
        prvI2C.IsBusy = 0;
        prvI2C.Result = -ERROR_PARAM_INVALID;
        prvI2C.Callback(I2C_ID0, prvI2C.pParam);
        return;
    }

    ISR_OnOff(prvI2C.IrqLine, 1);
}

int32_t I2C_MasterWriteRegQueue(uint8_t I2CID, I2C_CommonRegDataStruct *RegQueue, uint32_t TotalNum, uint16_t Toms, uint8_t IsBlock)
{
    I2C_TypeDef *I2C = prvI2C.RegBase;
    uint32_t RegValue;
    int32_t Result;
    I2C->IC_INTR_MASK = 0;
    ISR_OnOff(prvI2C.IrqLine, 0);
    if (prvI2C.IsBusy)
    {
        I2C->IC_ENABLE |= I2C_IC_ENABLE_ABORT;
        prvI2C.IsBusy = 0;
        prvI2C.Result = -ERROR_OPERATION_FAILED;
        prvI2C.Callback(I2C_ID0, prvI2C.pParam);
        while(I2C->IC_ENABLE & I2C_IC_ENABLE_ABORT){;}
    }
    ISR_SetHandler(prvI2C.IrqLine, I2C_IrqHandleRegQueue, NULL);
    prvI2C.IsBusy = 1;
    if (Toms)
    {
        prvI2C.TimeoutMs = Toms;
    }
    else
    {
        prvI2C.TimeoutMs = 50;
    }
    prvI2C.RegQueue = RegQueue;
    prvI2C.TotalQueueNum = TotalNum;
    prvI2C.CurQueuePos = 0;
    RegValue = I2C->IC_CLR_INTR;
    Buffer_StaticInit(&prvI2C.DataBuf, prvI2C.RegQueue[prvI2C.CurQueuePos].Data, 2);
    I2C->IC_DATA_CMD = prvI2C.DataBuf.Data[0];
    prvI2C.DataBuf.Pos++;
    I2C->IC_INTR_MASK = I2C_IC_INTR_MASK_M_TX_EMPTY|I2C_IC_INTR_MASK_M_STOP_DET;
    ISR_OnOff(prvI2C.IrqLine, 1);
    if (IsBlock)
    {
        while(!I2C_WaitResult(I2CID, &Result)) {;}
        return Result;
    }
    else
    {
        return 0;
    }
}


int I2C_WaitResult(uint8_t I2CID, int32_t *Result)
{
    if (prvI2C.IsBusy) return 0;
    *Result = prvI2C.Result;
    return 1;
}

int32_t I2C_BlockWrite(uint8_t I2CID, uint8_t ChipAddress, const uint8_t *Data, uint32_t Len, uint16_t Toms, CBFuncEx_t CB, void *pParam)
{
    int32_t Result;
    while(!I2C_WaitResult(I2CID, &Result)) {;}
    prvI2C.IsBlockMode = !OS_CheckInIrq();
    I2C_Prepare(I2CID, ChipAddress, 1, CB, pParam);
    I2C_MasterXfer(I2CID, I2C_OP_WRITE, 0, Data, Len, Toms);
#ifdef __BUILD_OS__
    if (!OS_CheckInIrq())
    {
        OS_MutexLock(prvI2C.Sem);
    }
#endif
    while(!I2C_WaitResult(I2CID, &Result)) {;}
    return Result;
}

int32_t I2C_BlockRead(uint8_t I2CID, uint8_t ChipAddress, uint8_t *Reg, uint8_t *Data, uint32_t Len, uint16_t Toms, CBFuncEx_t CB, void *pParam)
{
    int32_t Result;
    while(!I2C_WaitResult(I2CID, &Result)) {;}
    prvI2C.IsBlockMode = !OS_CheckInIrq();
    I2C_Prepare(I2CID, ChipAddress, 1, CB, pParam);
    if (Reg)
    {
        I2C_MasterXfer(I2CID, I2C_OP_READ_REG, *Reg, Data, Len, Toms);
    }
    else
    {
        I2C_MasterXfer(I2CID, I2C_OP_READ, 0, Data, Len, Toms);
    }
#ifdef __BUILD_OS__
    if (!OS_CheckInIrq())
    {
        OS_MutexLock(prvI2C.Sem);
    }
#endif
    while(!I2C_WaitResult(I2CID, &Result)) {;}
    return Result;
}

void I2C_ForceStop(uint8_t I2CID)
{
    I2C_TypeDef *I2C = prvI2C.RegBase;
    IIC_DBG("%d,%x",prvI2C.State, I2C->IC_RAW_INTR_STAT);
    I2C->IC_ENABLE |= I2C_IC_ENABLE_ABORT;
    I2C->IC_INTR_MASK = 0;
    prvI2C_Done(-ERROR_TIMEOUT);
    while(I2C->IC_ENABLE & I2C_IC_ENABLE_ABORT){;}
}
