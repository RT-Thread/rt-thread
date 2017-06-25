/*********************************************************************!     
 *     技术讨论：QQ群  123763203
 *     官网    ：www.navota.com
 *
 * @file       i2c.c
 * @brief      i2c通讯接口函数库
 * @author     Navota
 * @date       2017-1-1
 ************************************************************************/
#include "nv32f100.h"


/*!
 * @brief 存放回调入口
 *
 */
static I2C_CallbackType I2C_Callback[2] = {(I2C_CallbackType)NULL};

void I2C0_Isr( void );

/******************************************************************************
* 定义I2C的接口函数
*******************************************************************************/
/*****************************************************************************//*!
*
* @brief 初始化I2C模块.
*        
* @param[in] pI2Cx        I2C的基址.
* @param[in] pI2CConfig   配置I2C的结构体.
*
* @return none
*
*****************************************************************************/

void I2C_Init(I2C_Type *pI2Cx,I2C_ConfigPtr pI2CConfig)
{
    uint8_t u8Temp;

#if defined(CPU_NV32)
    SIM->SCGC |= SIM_SCGC_IIC_MASK;
#endif

	I2C_SetBaudRate(pI2Cx,pI2CConfig->u16F);
    I2C_SetSlaveAddress(pI2Cx,pI2CConfig->u16OwnA1);
    pI2Cx->FLT = (uint8_t)pI2CConfig->u16Filt;
    pI2Cx->RA = (uint8_t)pI2CConfig->u16RangeA & 0xfe;
    I2C_SetSCLLowETMeout(pI2Cx,pI2CConfig->u16Slt);

    /* 配置控制寄存器C2 */
    u8Temp = 0;
    if( pI2CConfig->sSetting.bGCAEn )
    {
        u8Temp |= I2C_C2_GCAEN_MASK;
    }
    if( pI2CConfig->sSetting.bAddressExt )
    {
        u8Temp |= I2C_C2_ADEXT_MASK;
    }
    if( pI2CConfig->sSetting.bRangeAddEn )
    {
        u8Temp |= I2C_C2_RMEN_MASK;
    }
    pI2Cx->C2 |= u8Temp;

    /* 配置寄存器SMB */
    u8Temp = 0;
    if( pI2CConfig->sSetting.bFackEn )
    {
        u8Temp |= I2C_SMB_FACK_MASK;
    }
    if( pI2CConfig->sSetting.bSMB_AlertEn )
    {
        u8Temp |= I2C_SMB_ALERTEN_MASK;
    }
    if( pI2CConfig->sSetting.bSecondAddressEn )
    {
        u8Temp |= I2C_SMB_SIICAEN_MASK;
    }
    if( pI2CConfig->sSetting.bSHTF2IntEn )
    {
        u8Temp |= I2C_SMB_SHTF2IE_MASK;
    }
    pI2Cx->SMB = u8Temp;
    
    /* 配置寄存器C1 */
    u8Temp = 0;
    if( pI2CConfig->sSetting.bIntEn )
    {
        u8Temp |= I2C_C1_IICIE_MASK;
        if(pI2Cx == I2C0)
        {
            NVIC_EnableIRQ(I2C0_IRQn);
        }   
        else
        {
            //
        }
    }
    if( pI2CConfig->sSetting.bWakeUpEn )
    {
        u8Temp |= I2C_C1_WUEN_MASK;
    }
    if( pI2CConfig->sSetting.bI2CEn )
    {
        u8Temp |= I2C_C1_IICEN_MASK;
    }
    pI2Cx->C1 = u8Temp;


}
/*****************************************************************************//*!
*
* @brief 发送I2C起始信号（启动传输）.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return 错误状态
*
*****************************************************************************/
uint8_t I2C_Start(I2C_Type *pI2Cx)
{
    uint32_t u32ETMeout;
    uint8_t u8ErrorStatus;
    
    u32ETMeout = 0; 
    u8ErrorStatus = 0x00;

    I2C_TxEnable(pI2Cx);//将 I2C 配置成 TX 发送模式
    pI2Cx->C1 |= I2C_C1_MST_MASK;//将 I2C 配置成主机模式
      
    //持续监测起始位有没有发送成功
    while( (!I2C_IsBusy(pI2Cx)) && ( u32ETMeout < I2C_WAIT_STATUS_ETMEOUT))
     {
        u32ETMeout ++;
     }

     if( u32ETMeout == I2C_WAIT_STATUS_ETMEOUT )
     {
        u8ErrorStatus |= I2C_ERROR_START_NO_BUSY_FLAG;
     }

     return u8ErrorStatus;//返回错误标志，为0x10即起始信号没有发送成功
}

/*****************************************************************************//*!
*
* @brief 发送停止信号.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return 错误状态
*
*****************************************************************************/
uint8_t I2C_Stop(I2C_Type *pI2Cx)
{
    uint32_t u32ETMeout;
    uint8_t u8ErrorStatus;
    
    u32ETMeout = 0; 
    u8ErrorStatus = 0x00;
    
    pI2Cx->C1 &= ~I2C_C1_MST_MASK;
   //持续监测 I2C 停止位是否发送成功
    while( (I2C_IsBusy(pI2Cx) ) && ( u32ETMeout < I2C_WAIT_STATUS_ETMEOUT))
     {
        u32ETMeout ++;
     }

     if( u32ETMeout == I2C_WAIT_STATUS_ETMEOUT )
     {
        u8ErrorStatus |= I2C_ERROR_STOP_BUSY_FLAG;
     }

     return u8ErrorStatus;
}


/*****************************************************************************//*!
*
* @brief 发送重复起始位.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return 错误状态.
*
*****************************************************************************/
uint8_t I2C_RepeatStart(I2C_Type *pI2Cx)
{
    uint32_t u32ETMeout;
    uint8_t u8ErrorStatus;
    
    u32ETMeout = 0; 
    u8ErrorStatus = 0x00;
    
    pI2Cx->C1 |= I2C_C1_RSTA_MASK;
    //持续监测起始位是否发送成功
    while( (!I2C_IsBusy(I2C0) ) && ( u32ETMeout < I2C_WAIT_STATUS_ETMEOUT))
     {
        u32ETMeout ++;
     }
       
     if( u32ETMeout == I2C_WAIT_STATUS_ETMEOUT )
     {
        u8ErrorStatus |= I2C_ERROR_START_NO_BUSY_FLAG;
     }

     return u8ErrorStatus;
}

/*****************************************************************************//*!
*
* @brief 设置从机地址.
*        
* @param[in] pI2Cx      I2C的基址.
* @param[in] u16SlaveAddress      从机地址.
*
* @return none
*
*****************************************************************************/
void I2C_SetSlaveAddress(I2C_Type *pI2Cx,uint16_t u16SlaveAddress)
{
    /* 写入8位地址 */
    pI2Cx->A1 = (uint8_t)u16SlaveAddress;

    /* 如果支持十位从机地址， 写入高三位地址 */
    pI2Cx->C2 &= ~I2C_C2_AD_MASK;
    pI2Cx->C2 |= (uint8_t)(u16SlaveAddress>>8)&0x03;
}

/*****************************************************************************//*!
*
* @brief 禁用I2C中断.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return none.
*
*****************************************************************************/
void I2C_IntDisable(I2C_Type *pI2Cx)
{
    pI2Cx->C1 &= ~I2C_C1_IICIE_MASK;
    if(pI2Cx == I2C0)
    {
        NVIC_DisableIRQ(I2C0_IRQn);
    }
    else
    {
        
    }
}
/*****************************************************************************//*!
*
* @brief 使能I2C中断.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return none.
*
*****************************************************************************/
void I2C_IntEnable(I2C_Type *pI2Cx)
{
    pI2Cx->C1 |= I2C_C1_IICIE_MASK;
    if(pI2Cx == I2C0)
    {
        NVIC_EnableIRQ(I2C0_IRQn);
    }
    else
    {
        
    }
}

/*****************************************************************************//*!
*
* @brief 设置SCL低超时周期.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return none.
*
*****************************************************************************/
void I2C_SetSCLLowETMeout(I2C_Type *pI2Cx, uint16_t u16ETMeout)
{
    pI2Cx->SLTL = (uint8_t)u16ETMeout;
    pI2Cx->SLTH = (uint8_t)(u16ETMeout>>8);
}

/*****************************************************************************//*!
*
* @brief 复位I2C模块.
*        
* @param[in] pI2Cx    I2C的基址.
*
* @return none
*
*****************************************************************************/
void I2C_Deinit(I2C_Type *pI2Cx)
{
     pI2Cx->C1 &= ~I2C_C1_IICEN_MASK;
#if defined(CPU_NV32)
    SIM->SCGC &= ~SIM_SCGC_IIC_MASK;
#endif
}

/*****************************************************************************//*!
*
* @brief 发送单字节数据.
*        
* @param[in] pI2Cx         I2C模块的基址.
* @param[in] u8WrBuff      要写的数据缓冲区. 
*
* @return 错误状态
*
*****************************************************************************/

uint8_t I2C_WriteOneByte(I2C_Type *pI2Cx, uint8_t u8WrBuff)
{
    uint32_t u32ETMeout;
    uint8_t u8ErrorStatus;
    
    u32ETMeout = 0; 
    u8ErrorStatus = 0x00;
    while (((I2C_GetStatus(pI2Cx)&I2C_S_TCF_MASK) !=  I2C_S_TCF_MASK)
            && (u32ETMeout<I2C_WAIT_STATUS_ETMEOUT))
    {
        u32ETMeout ++;
    }
    if (u32ETMeout >= I2C_WAIT_STATUS_ETMEOUT)
    {
        u8ErrorStatus |= I2C_ERROR_NO_WAIT_TCF_FLAG; 
        return u8ErrorStatus;
    }
    
    I2C_TxEnable(pI2Cx);  //将 I2C 配置成 TX 输出模式
    I2C_WriteDataReg(pI2Cx,u8WrBuff); //写数据寄存器发送数据

    u32ETMeout = 0;
    while (((I2C_GetStatus(pI2Cx)&I2C_S_IICIF_MASK) !=  I2C_S_IICIF_MASK)
            && (u32ETMeout<I2C_WAIT_STATUS_ETMEOUT))
    {
        u32ETMeout ++;
    }
    if (u32ETMeout >= I2C_WAIT_STATUS_ETMEOUT)
    {
        u8ErrorStatus |= I2C_ERROR_NO_WAIT_IICIF_FLAG; 
        return u8ErrorStatus;
    }

    /* 清除中断标志位 */
    I2C_ClearStatus(pI2Cx,I2C_S_IICIF_MASK);
    if (I2C_GetStatus(pI2Cx) & I2C_S_RXAK_MASK) 
    {
        u8ErrorStatus |= I2C_ERROR_NO_GET_ACK;
    }
    return u8ErrorStatus;
}
/*****************************************************************************//*!
*
* @brief 读取单字节数据.
*        
* @param[in] pI2Cx        I2C的基址.
* @param[out] pRdBuff     所要从从机读的地址.
* @param[out] u8Ack       发送 ack or nack.
*
* @return 错误状态
*
*****************************************************************************/

uint8_t I2C_ReadOneByte(I2C_Type *pI2Cx, uint8_t *pRdBuff, uint8_t u8Ack)
{
    uint32_t u32ETMeout;
    uint8_t u8ErrorStatus;
    
    u32ETMeout = 0; 
    u8ErrorStatus = 0x00;
    while (((I2C_GetStatus(pI2Cx)&I2C_S_TCF_MASK) !=  I2C_S_TCF_MASK)
            && (u32ETMeout<I2C_WAIT_STATUS_ETMEOUT))
    {
        u32ETMeout ++;
    }
    if (u32ETMeout >= I2C_WAIT_STATUS_ETMEOUT)
    {
        u8ErrorStatus |= I2C_ERROR_NO_WAIT_TCF_FLAG; 
        return u8ErrorStatus;
    }
    
    I2C_RxEnable(pI2Cx); //将 I2C 配置为输入模式

    if( u8Ack )
    {
        /*  发送 nack  */
        I2C_SendNack(pI2Cx);
       
    }
    else
    {
         /*  发送 ack  */
        I2C_SendAck(pI2Cx);
    }
    *pRdBuff = I2C_ReadDataReg(pI2Cx);   //将读到的数据存放到参数里头

    u32ETMeout = 0;
     //持续监测中断标志
    while (((I2C_GetStatus(pI2Cx)&I2C_S_IICIF_MASK) !=  I2C_S_IICIF_MASK)
            && (u32ETMeout<I2C_WAIT_STATUS_ETMEOUT))
    {
        u32ETMeout ++;
    }
    if (u32ETMeout >= I2C_WAIT_STATUS_ETMEOUT)
    {
        u8ErrorStatus |= I2C_ERROR_NO_WAIT_IICIF_FLAG; 
        return u8ErrorStatus;
    }

    /*清除 IIC 中断标志位 */
    I2C_ClearStatus(pI2Cx,I2C_S_IICIF_MASK);

    return u8ErrorStatus;
}
/*****************************************************************************//*!
*
* @brief 发送数据到I2C,然后等待数据传送完成.
*   
* @param[in]  pI2Cx                   I2C的基址.
* @param[in]  u16SlaveAddress         16位从机地址. 
* @param[in]  pWrBuff                 需要发送数据的缓冲数组. 
* @param[in]  u32Length               发送字节的数目.
*
* @return 错误状态
*
*****************************************************************************/

uint8_t I2C_MasterSendWait(I2C_Type *pI2Cx,uint16_t u16SlaveAddress,uint8_t *pWrBuff,uint32_t u32Length)
{
    uint32_t i;
    uint8_t u8ErrorStatus;

    /* 发送起始信号 */
    u8ErrorStatus = I2C_Start(pI2Cx);

    /* 给从机发送从机地址 */
    u8ErrorStatus = I2C_WriteOneByte(pI2Cx,((uint8_t)u16SlaveAddress<<1) | I2C_WRITE);

    /* 如果没有错误发生， 则继续发送字节*/
    if( u8ErrorStatus == I2C_ERROR_NULL )
    {
        for(i=0;i<u32Length;i++)
        {
            u8ErrorStatus = I2C_WriteOneByte(pI2Cx,pWrBuff[i]);
            if( u8ErrorStatus != I2C_ERROR_NULL )
            {
                return u8ErrorStatus;
            }
        }
     }

    /*发送 I2C 停止位 */
     u8ErrorStatus = I2C_Stop(pI2Cx);

     return u8ErrorStatus;
            
}
/*****************************************************************************//*!
*
* @brief 读取多个字节并等待完成.
*        
* @param[in] pI2Cx                 I2C的基址.
* @param[in]  u16SlaveAddress      从机地址. 
* @param[in]  pRdBuff              用于接收数据的缓冲区. 
* @param[in]  u32Length            接收数据的字节数.           
*
* @return 错误状态
*
*****************************************************************************/

uint8_t I2C_MasterReadWait(I2C_Type *pI2Cx,uint16_t u16SlaveAddress,uint8_t *pRdBuff,uint32_t u32Length)
{
    uint32_t i;
    uint8_t u8ErrorStatus;

    /* 发送起始信号到总线 */
    u8ErrorStatus = I2C_Start(pI2Cx);

    /* 给从机发送器件地址 */
    u8ErrorStatus = I2C_WriteOneByte(pI2Cx,((uint8_t)u16SlaveAddress<<1) | I2C_READ);

    /* 如果没有错误发生， 则继续接收字节*/
    I2C_ReadOneByte(pI2Cx,&pRdBuff[0],I2C_SEND_ACK);
    
    if( u8ErrorStatus == I2C_ERROR_NULL )
    {
        for(i=0;i<u32Length-1;i++)
        {
            u8ErrorStatus = I2C_ReadOneByte(pI2Cx,&pRdBuff[i],I2C_SEND_ACK);
            if( u8ErrorStatus != I2C_ERROR_NULL )
            {
                return u8ErrorStatus;
            }
        }
        u8ErrorStatus = I2C_ReadOneByte(pI2Cx,&pRdBuff[i],I2C_SEND_NACK);
     }
    /*发送停止信号 */
     u8ErrorStatus = I2C_Stop(pI2Cx);
     
     return u8ErrorStatus;
            
}

/*****************************************************************************//*!
*
* @brief 设置I2C模块的中断回调函数
*        
* @param[in]   pfnCallback   回调函数的地址
*
* @return none 
*
*****************************************************************************/

void I2C1_SetCallBack( I2C_CallbackType pCallBack )
{
    I2C_Callback[1] = pCallBack;
}

/*****************************************************************************//*!
*
* @brief 设置RTC模块的中断回调函数
*        
* @param[in]   pfnCallback   回调函数的地址
*
* @return none 
*
*****************************************************************************/

void I2C0_SetCallBack( I2C_CallbackType pCallBack )
{
    I2C_Callback[0] = pCallBack;
}
/*! @}                          						*/


/*****************************************************************************//*!
*
* @brief I2C0 中断服务函数.
*        
* @param  
*
* @return none
*
*****************************************************************************/
void I2C0_Isr( void )
{
    if( I2C_Callback[0] )
    {
        I2C_Callback[0]();
    }
}
/*****************************************************************************//*!
*
* @brief I2C1 中断服务函数.
*        
* @param  
*
* @return none
*
*****************************************************************************/
void I2C1_Isr( void )
{
    if( I2C_Callback[1] )
    {
        I2C_Callback[1]();
    }
}



