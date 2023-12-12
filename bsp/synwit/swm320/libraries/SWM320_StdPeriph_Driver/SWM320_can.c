/******************************************************************************************************************************************
* 文件名称: SWM320_can.c
* 功能说明: SWM320单片机的CAN模块驱动库
* 技术支持: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
* 版本日期: V1.1.0      2017年10月25日
* 升级记录:
*
*
*******************************************************************************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION
* REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE
* FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
* OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
* -ECTION WITH THEIR PRODUCTS.
*
* COPYRIGHT 2012 Synwit Technology
*******************************************************************************************************************************************/
#include "SWM320.h"
#include "SWM320_can.h"


/******************************************************************************************************************************************
* 函数名称: CAN_Init()
* 功能说明: CAN接口初始化
* 输    入: CAN_TypeDef * CANx    指定要被设置的CAN接口，有效值包括CAN
*           CAN_InitStructure * initStruct    包含CAN接口相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CAN_Init(CAN_TypeDef * CANx, CAN_InitStructure * initStruct)
{
    switch((uint32_t)CANx)
    {
    case ((uint32_t)CAN):
        SYS->CLKEN |= (0x01 << SYS_CLKEN_CAN_Pos);
        break;
    }

    CAN_Close(CANx);    //一些关键寄存器只能在CAN关闭时设置

    CANx->CR &= ~(CAN_CR_LOM_Msk | CAN_CR_STM_Msk | CAN_CR_AFM_Msk);
    CANx->CR |= (initStruct->Mode << CAN_CR_LOM_Pos) |
                (initStruct->FilterMode << CAN_CR_AFM_Pos);

    CANx->FILTER.AMR[3] = initStruct->FilterMask32b & 0xFF;
    CANx->FILTER.AMR[2] = (initStruct->FilterMask32b >>  8) & 0xFF;
    CANx->FILTER.AMR[1] = (initStruct->FilterMask32b >> 16) & 0xFF;
    CANx->FILTER.AMR[0] = (initStruct->FilterMask32b >> 24) & 0xFF;

    CANx->FILTER.ACR[3] = initStruct->FilterCheck32b & 0xFF;
    CANx->FILTER.ACR[2] = (initStruct->FilterCheck32b >>  8) & 0xFF;
    CANx->FILTER.ACR[1] = (initStruct->FilterCheck32b >> 16) & 0xFF;
    CANx->FILTER.ACR[0] = (initStruct->FilterCheck32b >> 24) & 0xFF;

    CANx->BT1 = (0 << CAN_BT1_SAM_Pos) |
                (initStruct->CAN_BS1 << CAN_BT1_TSEG1_Pos) |
                (initStruct->CAN_BS2 << CAN_BT1_TSEG2_Pos);

    CANx->BT0 = (initStruct->CAN_SJW << CAN_BT0_SJW_Pos) |
                ((SystemCoreClock/2/initStruct->Baudrate/(1 + (initStruct->CAN_BS1 + 1) + (initStruct->CAN_BS2 + 1)) - 1) << CAN_BT0_BRP_Pos);

    CANx->RXERR = 0;    //只能在复位模式下清除
    CANx->TXERR = 0;

    CANx->IE = (initStruct->RXNotEmptyIEn << CAN_IE_RXDA_Pos)    |
               (initStruct->RXOverflowIEn << CAN_IE_RXOV_Pos)    |
               (initStruct->ArbitrLostIEn << CAN_IE_ARBLOST_Pos) |
               (initStruct->ErrPassiveIEn << CAN_IE_ERRPASS_Pos);

    switch((uint32_t)CANx)
    {
    case ((uint32_t)CAN):
        if(initStruct->RXNotEmptyIEn | initStruct->RXOverflowIEn | initStruct->ArbitrLostIEn | initStruct->ErrPassiveIEn)
        {
            NVIC_EnableIRQ(CAN_IRQn);
        }
        else
        {
            NVIC_DisableIRQ(CAN_IRQn);
        }
        break;
    }
}

/******************************************************************************************************************************************
* 函数名称: CAN_Open()
* 功能说明: CAN接口打开
* 输    入: CAN_TypeDef * CANx    指定要被设置的CAN接口，有效值包括CAN
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CAN_Open(CAN_TypeDef * CANx)
{
    CANx->CR &= ~(0x01 << CAN_CR_RST_Pos);  //退出复位模式，进入工作模式
}

/******************************************************************************************************************************************
* 函数名称: CAN_Close()
* 功能说明: CAN接口关闭
* 输    入: CAN_TypeDef * CANx    指定要被设置的CAN接口，有效值包括CAN
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CAN_Close(CAN_TypeDef * CANx)
{
    CANx->CR |= (0x01 << CAN_CR_RST_Pos);   //进入复位模式，不能发送和接收数据
}

/******************************************************************************************************************************************
* 函数名称: CAN_Transmit()
* 功能说明: CAN发送数据
* 输    入: CAN_TypeDef * CANx    指定要被设置的CAN接口，有效值包括CAN
*           uint32_t format     CAN_FRAME_STD 标准帧    CAN_FRAME_EXT 扩展帧
*           uint32_t id         消息ID
*           uint8_t data[]      要发送的数据
*           uint32_t size       要发送的数据的个数
*           uint32_t once       只发送一次，即使发送失败（仲裁丢失、发送出错、NAK）也不尝试重发
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CAN_Transmit(CAN_TypeDef * CANx, uint32_t format, uint32_t id, uint8_t data[], uint32_t size, uint32_t once)
{
    uint32_t i;

    if(format == CAN_FRAME_STD)
    {
        CANx->FRAME.INFO = (0 << CAN_INFO_FF_Pos)  |
                           (0 << CAN_INFO_RTR_Pos) |
                           (size << CAN_INFO_DLC_Pos);

        CANx->FRAME.DATA[0] = id >> 3;
        CANx->FRAME.DATA[1] = id << 5;

        for(i = 0; i < size; i++)
        {
            CANx->FRAME.DATA[i+2] = data[i];
        }
    }
    else //if(format == CAN_FRAME_EXT)
    {
        CANx->FRAME.INFO = (1 << CAN_INFO_FF_Pos)  |
                           (0 << CAN_INFO_RTR_Pos) |
                           (size << CAN_INFO_DLC_Pos);

        CANx->FRAME.DATA[0] = id >> 21;
        CANx->FRAME.DATA[1] = id >> 13;
        CANx->FRAME.DATA[2] = id >>  5;
        CANx->FRAME.DATA[3] = id <<  3;

        for(i = 0; i < size; i++)
        {
            CANx->FRAME.DATA[i+4] = data[i];
        }
    }

    if(CANx->CR & CAN_CR_STM_Msk)
    {
        CANx->CMD = (1 << CAN_CMD_SRR_Pos);
    }
    else
    {
        if(once == 0)
        {
            CANx->CMD = (1 << CAN_CMD_TXREQ_Pos);
        }
        else
        {
            CANx->CMD = (1 << CAN_CMD_TXREQ_Pos) | (1 << CAN_CMD_ABTTX_Pos);
        }
    }
}

/******************************************************************************************************************************************
* 函数名称: CAN_TransmitRequest()
* 功能说明: CAN发送远程请求，请求远程节点发送数据
* 输    入: CAN_TypeDef * CANx    指定要被设置的CAN接口，有效值包括CAN
*           uint32_t format     CAN_FRAME_STD 标准帧    CAN_FRAME_EXT 扩展帧
*           uint32_t id         消息ID
*           uint32_t once       只发送一次，即使发送失败（仲裁丢失、发送出错、NAK）也不尝试重发
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CAN_TransmitRequest(CAN_TypeDef * CANx, uint32_t format, uint32_t id, uint32_t once)
{
    if(format == CAN_FRAME_STD)
    {
        CANx->FRAME.INFO = (0 << CAN_INFO_FF_Pos)  |
                           (1 << CAN_INFO_RTR_Pos) |
                           (0 << CAN_INFO_DLC_Pos);

        CANx->FRAME.DATA[0] = id >> 3;
        CANx->FRAME.DATA[1] = id << 5;
    }
    else //if(format == CAN_FRAME_EXT)
    {
        CANx->FRAME.INFO = (1 << CAN_INFO_FF_Pos)  |
                           (1 << CAN_INFO_RTR_Pos) |
                           (0 << CAN_INFO_DLC_Pos);

        CANx->FRAME.DATA[0] = id >> 21;
        CANx->FRAME.DATA[1] = id >> 13;
        CANx->FRAME.DATA[2] = id >>  5;
        CANx->FRAME.DATA[3] = id <<  3;
    }

    if(once == 0)
    {
        CANx->CMD = (1 << CAN_CMD_TXREQ_Pos);
    }
    else
    {
        CANx->CMD = (1 << CAN_CMD_TXREQ_Pos) | (1 << CAN_CMD_ABTTX_Pos);
    }
}

/******************************************************************************************************************************************
* 函数名称: CAN_Receive()
* 功能说明: CAN接收数据
* 输    入: CAN_TypeDef * CANx    指定要被设置的CAN接口，有效值包括CAN
*           CAN_RXMessage *msg  接收到的消息存储在此结构体变量中
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CAN_Receive(CAN_TypeDef * CANx, CAN_RXMessage *msg)
{
    uint32_t i;
    msg->format = (CANx->FRAME.INFO & CAN_INFO_FF_Msk) >> CAN_INFO_FF_Pos;

    msg->remote = (CANx->FRAME.INFO & CAN_INFO_RTR_Msk) >> CAN_INFO_RTR_Pos;
    msg->size = (CANx->FRAME.INFO & CAN_INFO_DLC_Msk) >> CAN_INFO_DLC_Pos;

    if(msg->format == CAN_FRAME_STD)
    {
        msg->id = (CANx->FRAME.DATA[0] << 3) | (CANx->FRAME.DATA[1] >> 5);

        for(i = 0; i < msg->size; i++)
        {
            msg->data[i] = CANx->FRAME.DATA[i+2];
        }
    }
    else //if(msg->format == CAN_FRAME_EXT)
    {
        msg->id = (CANx->FRAME.DATA[0] << 21) | (CANx->FRAME.DATA[1] << 13) | (CANx->FRAME.DATA[2] << 5) | (CANx->FRAME.DATA[3] >> 3);

        for(i = 0; i < msg->size; i++)
        {
            msg->data[i] = CANx->FRAME.DATA[i+4];
        }
    }

    CANx->CMD = (1 << CAN_CMD_RRB_Pos);
}

/******************************************************************************************************************************************
* 函数名称: CAN_TXComplete()
* 功能说明: 发送是否完成
* 输    入: CAN_TypeDef * CANx    指定要被设置的CAN接口，有效值包括CAN
* 输    出: uint32_t          1 已经完成    0 还未完成
* 注意事项: 发送被Abort也会触发发送完成，但不会触发发送成功
******************************************************************************************************************************************/
uint32_t CAN_TXComplete(CAN_TypeDef * CANx)
{
    return (CANx->SR & CAN_SR_TXBR_Msk) ? 1 : 0;
}

/******************************************************************************************************************************************
* 函数名称: CAN_TXSuccess()
* 功能说明: 发送是否成功
* 输    入: CAN_TypeDef * CANx    指定要被设置的CAN接口，有效值包括CAN
* 输    出: uint32_t          1 发送成功    0 发送失败
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t CAN_TXSuccess(CAN_TypeDef * CANx)
{
    return (CANx->SR & CAN_SR_TXOK_Msk) ? 1 : 0;
}

/******************************************************************************************************************************************
* 函数名称: CAN_AbortTransmit()
* 功能说明: 终止发送
* 输    入: CAN_TypeDef * CANx    指定要被设置的CAN接口，有效值包括CAN
* 输    出: 无
* 注意事项: 正在进行的发送无法终止，但执行此命令后若发送失败不会再重发
******************************************************************************************************************************************/
void CAN_AbortTransmit(CAN_TypeDef * CANx)
{
    CANx->CMD = (1 << CAN_CMD_ABTTX_Pos);
}

/******************************************************************************************************************************************
* 函数名称: CAN_TXBufferReady()
* 功能说明: TX Buffer是否准备好可以写入消息
* 输    入: CAN_TypeDef * CANx    指定要被设置的CAN接口，有效值包括CAN
* 输    出: uint32_t          1 已准备好    0 未准备好
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t CAN_TXBufferReady(CAN_TypeDef * CANx)
{
    return (CANx->SR & CAN_SR_TXBR_Msk) ? 1 : 0;
}

/******************************************************************************************************************************************
* 函数名称: CAN_RXDataAvailable()
* 功能说明: RX FIFO中是否有数据可读出
* 输    入: CAN_TypeDef * CANx    指定要被设置的CAN接口，有效值包括CAN
* 输    出: uint32_t          1 有数据可读出    0 没有数据
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t CAN_RXDataAvailable(CAN_TypeDef * CANx)
{
    return (CANx->SR & CAN_SR_RXDA_Msk) ? 1 : 0;
}

/******************************************************************************************************************************************
* 函数名称: CAN_SetBaudrate()
* 功能说明: 设置波特率
* 输    入: CAN_TypeDef * CANx    指定要被设置的CAN接口，有效值包括CAN
*           uint32_t baudrate   波特率，即位传输速率
*           uint32_t CAN_BS1    CAN_BS1_1tq、CAN_BS1_2tq、... ... 、CAN_BS1_16tq
*           uint32_t CAN_BS2    CAN_BS2_1tq、CAN_BS2_2tq、... ... 、CAN_BS2_8tq
*           uint32_t CAN_SJW    CAN_SJW_1tq、CAN_SJW_2tq、CAN_SJW_3tq、CAN_SJW_4tq
* 输    出: 无
* 注意事项: 设置前需要先调用CAN_Close()关闭CAN模块
******************************************************************************************************************************************/
void CAN_SetBaudrate(CAN_TypeDef * CANx, uint32_t baudrate, uint32_t CAN_BS1, uint32_t CAN_BS2, uint32_t CAN_SJW)
{
    CANx->BT1 = (0 << CAN_BT1_SAM_Pos) |
                (CAN_BS1 << CAN_BT1_TSEG1_Pos) |
                (CAN_BS2 << CAN_BT1_TSEG2_Pos);

    CANx->BT0 = (CAN_SJW << CAN_BT0_SJW_Pos) |
                ((SystemCoreClock/2/baudrate/(1 + (CAN_BS1 + 1) + (CAN_BS2 + 1)) - 1) << CAN_BT0_BRP_Pos);
}

/******************************************************************************************************************************************
* 函数名称: CAN_SetFilter32b()
* 功能说明: 设置接收滤波器，1个32位滤波器
* 输    入: CAN_TypeDef * CANx    指定要被设置的CAN接口，有效值包括CAN
*           uint32_t check      与mask一起决定了接收到的Message是否是自己需要的：check & (~mask) == ID & (~mask)的Message通过过滤
*           uint32_t mask
* 输    出: 无
* 注意事项: 设置前需要先调用CAN_Close()关闭CAN模块
******************************************************************************************************************************************/
void CAN_SetFilter32b(CAN_TypeDef * CANx, uint32_t check, uint32_t mask)
{
    CANx->CR &= ~CAN_CR_AFM_Msk;
    CANx->CR |= (CAN_FILTER_32b << CAN_CR_AFM_Pos);

    CANx->FILTER.AMR[3] =  mask & 0xFF;
    CANx->FILTER.AMR[2] = (mask >>  8) & 0xFF;
    CANx->FILTER.AMR[1] = (mask >> 16) & 0xFF;
    CANx->FILTER.AMR[0] = (mask >> 24) & 0xFF;

    CANx->FILTER.ACR[3] =  check & 0xFF;
    CANx->FILTER.ACR[2] = (check >>  8) & 0xFF;
    CANx->FILTER.ACR[1] = (check >> 16) & 0xFF;
    CANx->FILTER.ACR[0] = (check >> 24) & 0xFF;
}

/******************************************************************************************************************************************
* 函数名称: CAN_SetFilter16b()
* 功能说明: 设置接收滤波器，2个16位滤波器
* 输    入: CAN_TypeDef * CANx    指定要被设置的CAN接口，有效值包括CAN
*           uint16_t check1     与mask一起决定了接收到的Message是否是自己需要的：check & (~mask) == ID & (~mask)的Message通过过滤
*           uint16_t mask1
*           uint16_t check2
*           uint16_t mask2
* 输    出: 无
* 注意事项: 设置前需要先调用CAN_Close()关闭CAN模块
******************************************************************************************************************************************/
void CAN_SetFilter16b(CAN_TypeDef * CANx, uint16_t check1, uint16_t mask1, uint16_t check2, uint16_t mask2)
{
    CANx->CR &= ~CAN_CR_AFM_Msk;
    CANx->CR |= (CAN_FILTER_16b << CAN_CR_AFM_Pos);

    CANx->FILTER.AMR[3] =  mask1 & 0xFF;
    CANx->FILTER.AMR[2] = (mask1 >>  8) & 0xFF;
    CANx->FILTER.AMR[1] =  mask2 & 0xFF;
    CANx->FILTER.AMR[0] = (mask2 >>  8) & 0xFF;

    CANx->FILTER.ACR[3] =  check1 & 0xFF;
    CANx->FILTER.ACR[2] = (check1 >>  8) & 0xFF;
    CANx->FILTER.ACR[1] =  check2 & 0xFF;
    CANx->FILTER.ACR[0] = (check2 >>  8) & 0xFF;
}

/******************************************************************************************************************************************
* 函数名称: CAN_INTEn()
* 功能说明: 使能指定中断
* 输    入: CAN_TypeDef * CANx    指定要被设置的CAN接口，有效值包括CAN
*           uint32_t it         interrupt type，有效值包括 CAN_IT_RX_NOTEMPTY、CAN_IT_RX_OVERFLOW、CAN_IT_TX_EMPTY、CAN_IT_ARBLOST、
*                               CAN_IT_ERR、CAN_IT_ERR_WARN、CAN_IT_ERR_PASS、CAN_IT_WAKEUP 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CAN_INTEn(CAN_TypeDef * CANx, uint32_t it)
{
    CANx->IE |= it;
}

/******************************************************************************************************************************************
* 函数名称: CAN_INTDis()
* 功能说明: 关闭指定中断
* 输    入: CAN_TypeDef * CANx    指定要被设置的CAN接口，有效值包括CAN
*           uint32_t it         interrupt type，有效值包括 CAN_IT_RX_NOTEMPTY、CAN_IT_RX_OVERFLOW、CAN_IT_TX_EMPTY、CAN_IT_ARBLOST、
*                               CAN_IT_ERR、CAN_IT_ERR_WARN、CAN_IT_ERR_PASS、CAN_IT_WAKEUP 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CAN_INTDis(CAN_TypeDef * CANx, uint32_t it)
{
    CANx->IE &= ~it;
}

/******************************************************************************************************************************************
* 函数名称: CAN_INTClr()
* 功能说明: 清除中断标志
* 输    入: CAN_TypeDef * CANx    指定要被设置的CAN接口，有效值包括CAN
*           uint32_t it         interrupt type，有效值包括 CAN_IT_RX_OVERFLOW
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CAN_INTClr(CAN_TypeDef * CANx, uint32_t it)
{
    CANx->CMD = (1 << CAN_CMD_CLROV_Pos);
}

/******************************************************************************************************************************************
* 函数名称: CAN_INTStat()
* 功能说明: 查询中断状态
* 输    入: CAN_TypeDef * CANx    指定要被设置的CAN接口，有效值包括CAN
* 输    出: uint32_t          当前中断状态
* 注意事项: CANx->IF读取清零，因此在中断ISR中只能读取一次，不能多次读取
******************************************************************************************************************************************/
uint32_t CAN_INTStat(CAN_TypeDef * CANx)
{
    return CANx->IF;
}
