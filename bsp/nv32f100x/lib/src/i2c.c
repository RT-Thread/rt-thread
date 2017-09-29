/******************************************************************************
*
* @brief providing APIs for configuring I2C module (I2C). 
*
*******************************************************************************
*
* provide APIs for configuring I2C module (I2C).
******************************************************************************/
#include "common.h"
#include "i2c.h"

/******************************************************************************
* Global variables
******************************************************************************/

/******************************************************************************
* Constants and macros
******************************************************************************/

/******************************************************************************
* Local types
******************************************************************************/

/******************************************************************************
* Local function prototypes
******************************************************************************/

/******************************************************************************
* Local variables
******************************************************************************/
static I2C_CallbackType I2C_Callback[2] = {(I2C_CallbackType)NULL};
/******************************************************************************
* Local functions
******************************************************************************/
void I2C0_Isr( void );

/******************************************************************************
* Global functions
******************************************************************************/


/******************************************************************************
* define I2C APIs
*
*//*! @addtogroup i2c_api_list
* @{
*******************************************************************************/
/*****************************************************************************//*!
   *
   * @brief Initialize I2C module.
   *        
   * @param[in] pI2Cx      point to I2C module type.
 	 * @param[in] pI2CConfig point to I2C configure structure.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/

void I2C_Init(I2C_Type *pI2Cx,I2C_ConfigPtr pI2CConfig)
{
    uint8_t u8Temp;

#if defined(CPU_NV32)
    SIM->SCGC |= SIM_SCGC_IIC_MASK;
#elif defined(CPU_NV32M3)
    SIM->SCGC |= SIM_SCGC_IIC_MASK;
#elif defined(CPU_NV32M4)
    if(pI2Cx == I2C0)
    {
        SIM->SCGC |= SIM_SCGC_I2C0_MASK;
    }
    else
    {
        SIM->SCGC |= SIM_SCGC_I2C1_MASK;
    }
#endif

	I2C_SetBaudRate(pI2Cx,pI2CConfig->u16F);
    I2C_SetSlaveAddress(pI2Cx,pI2CConfig->u16OwnA1);
    pI2Cx->FLT = (uint8_t)pI2CConfig->u16Filt;
    pI2Cx->RA = (uint8_t)pI2CConfig->u16RangeA & 0xfe;
    I2C_SetSCLLowETMeout(pI2Cx,pI2CConfig->u16Slt);

    /* configure C2 control register */
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

    /* configure SMB rehister */
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
    
    /* configure C1 rehister */
    u8Temp = 0;
    if( pI2CConfig->sSetting.bIntEn )
    {
        u8Temp |= I2C_C1_IICIE_MASK;
        if(pI2Cx == I2C0)
        {
            NVIC_EnableIRQ(I2C0_IRQn);
        }
    #if defined(CPU_NV32M4)     
        else if(pI2Cx == I2C1)
        {
            NVIC_EnableIRQ(I2C1_IRQn);
        }
    #endif    
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
   * @brief send out start signals.
   *        
   * @param[in] pI2Cx      point to I2C module type.
   *
   * @return error status
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
uint8_t I2C_Start(I2C_Type *pI2Cx)
{
    uint32_t u32ETMeout;
    uint8_t u8ErrorStatus;
    
    u32ETMeout = 0; 
    u8ErrorStatus = 0x00;

    I2C_TxEnable(pI2Cx);
    pI2Cx->C1 |= I2C_C1_MST_MASK;

    while( (!I2C_IsBusy(pI2Cx)) && ( u32ETMeout < I2C_WAIT_STATUS_ETMEOUT))
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
   * @brief send out stop signals.
   *        
   * @param[in] pI2Cx      point to I2C module type.
   *
   * @return error status
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
uint8_t I2C_Stop(I2C_Type *pI2Cx)
{
    uint32_t u32ETMeout;
    uint8_t u8ErrorStatus;
    
    u32ETMeout = 0; 
    u8ErrorStatus = 0x00;
    
    pI2Cx->C1 &= ~I2C_C1_MST_MASK;

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
   * @brief send out repeat start signals.
   *        
   * @param[in] pI2Cx      point to I2C module type.
   *
   * @return error status.
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
uint8_t I2C_RepeatStart(I2C_Type *pI2Cx)
{
    uint32_t u32ETMeout;
    uint8_t u8ErrorStatus;
    
    u32ETMeout = 0; 
    u8ErrorStatus = 0x00;
    
    pI2Cx->C1 |= I2C_C1_RSTA_MASK;

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
   * @brief set slave address.
   *        
   * @param[in] pI2Cx      point to I2C module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
void I2C_SetSlaveAddress(I2C_Type *pI2Cx,uint16_t u16SlaveAddress)
{
    /* write low 8bit address */
    pI2Cx->A1 = (uint8_t)u16SlaveAddress;

    /* write high 3bit address if it support 10bit slave address */
    pI2Cx->C2 &= ~I2C_C2_AD_MASK;
    pI2Cx->C2 |= (uint8_t)(u16SlaveAddress>>8)&0x03;
}

/*****************************************************************************//*!
   *
   * @brief disable IICIF interrupt.
   *        
   * @param[in] pI2Cx      point to I2C module type.
   *
   * @return none.
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
void I2C_IntDisable(I2C_Type *pI2Cx)
{
    pI2Cx->C1 &= ~I2C_C1_IICIE_MASK;
    if(pI2Cx == I2C0)
    {
        NVIC_DisableIRQ(I2C0_IRQn);
    }
    #if defined(CPU_NV32M4)
    else if(pI2Cx == I2C1)
    {
        NVIC_DisableIRQ(I2C1_IRQn);
    }
    #endif
    else
    {
        
    }
}
/*****************************************************************************//*!
   *
   * @brief enable IICIF interrupt.
   *        
   * @param[in] pI2Cx      point to I2C module type.
   *
   * @return none.
   *
   * @ Pass/ Fail criteria: none.
*****************************************************************************/
void I2C_IntEnable(I2C_Type *pI2Cx)
{
    pI2Cx->C1 |= I2C_C1_IICIE_MASK;
    if(pI2Cx == I2C0)
    {
        NVIC_EnableIRQ(I2C0_IRQn);
    }
    #if defined(CPU_NV32M4)
    else if(pI2Cx == I2C1)
    {
        NVIC_EnableIRQ(I2C1_IRQn);
    }
    #endif
    else
    {
        
    }
}

/*****************************************************************************//*!
   *
   * @brief SCL low ETMeout value that determines the ETMeout period of SCL low.
   *        
   * @param[in] pI2Cx      point to I2C module type.
   *
   * @return none.
   *
   * @ Pass/ Fail criteria: none.
*****************************************************************************/
void I2C_SetSCLLowETMeout(I2C_Type *pI2Cx, uint16_t u16ETMeout)
{
    pI2Cx->SLTL = (uint8_t)u16ETMeout;
    pI2Cx->SLTH = (uint8_t)(u16ETMeout>>8);
}
/*****************************************************************************//*!
   *
   * @brief deinit I2C module.
   *        
   * @param[in] pI2Cx    point to I2C module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
void I2C_Deinit(I2C_Type *pI2Cx)
{
     pI2Cx->C1 &= ~I2C_C1_IICEN_MASK;
#if defined(CPU_NV32)
    SIM->SCGC &= ~SIM_SCGC_IIC_MASK;
#elif defined(CPU_NV32M3)
    SIM->SCGC &= ~SIM_SCGC_IIC_MASK;
#elif defined(CPU_NV32M4)
    if(pI2Cx == I2C0)
    {
        SIM->SCGC &= ~SIM_SCGC_I2C0_MASK;
    }
    else
    {
        SIM->SCGC &= ~SIM_SCGC_I2C1_MASK;
    }
#endif
}

/*****************************************************************************//*!
   *
   * @brief write a byte to I2C module.
   *        
   * @param[in] pI2Cx    point to I2C module type.
   * @param[in] u8WrBuff  data buffer for writing. 
   *
   * @return error status
   *
   * @ Pass/ Fail criteria: none
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
    
    I2C_TxEnable(pI2Cx);
    I2C_WriteDataReg(pI2Cx,u8WrBuff);

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

    /* clear IICIF flag */
    I2C_ClearStatus(pI2Cx,I2C_S_IICIF_MASK);
    if (I2C_GetStatus(pI2Cx) & I2C_S_RXAK_MASK) 
    {
        u8ErrorStatus |= I2C_ERROR_NO_GET_ACK;
    }
    return u8ErrorStatus;
}
/*****************************************************************************//*!
   *
   * @brief read a byte from slave I2C.
   *        
   * @param[in] pI2Cx    point to I2C module type.
   * @param[out] pRdBuff point to the data read from slave I2C.
   * @param[out] u8Ack   send out ack or nack.
   *
   * @return error status
   *
   * @ Pass/ Fail criteria:  none
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
    
    I2C_RxEnable(pI2Cx);

    if( u8Ack )
    {
        /* send out nack */
        I2C_SendNack(pI2Cx);
       
    }
    else
    {
         /* send out ack */
        I2C_SendAck(pI2Cx);
    }
    *pRdBuff = I2C_ReadDataReg(pI2Cx);

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

    /* clear IICIF flag */
    I2C_ClearStatus(pI2Cx,I2C_S_IICIF_MASK);

    return u8ErrorStatus;
}
/*****************************************************************************//*!
   *
   * @brief send data to I2C, and wait to complete transfering.
   *   
   * @param[in]  pI2Cx    point to I2C module type.
   * @param[in]  u16SlaveAddress slave address. 
   * @param[in]  pWrBuff point the first address of transfering data buffer. 
   * @param[in]  the length of transfering data.
   *
   * @return error status
   *
   * @ Pass/ Fail criteria:  none
*****************************************************************************/

uint8_t I2C_MasterSendWait(I2C_Type *pI2Cx,uint16_t u16SlaveAddress,uint8_t *pWrBuff,uint32_t u32Length)
{
    uint32_t i;
    uint8_t u8ErrorStatus;

    /* send start signals to bus */
    u8ErrorStatus = I2C_Start(pI2Cx);

    /* send device address to slave */
    u8ErrorStatus = I2C_WriteOneByte(pI2Cx,((uint8_t)u16SlaveAddress<<1) | I2C_WRITE);

    /* if no error occur, received the correct ack from slave
            continue to send data to slave
        */
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

     /* send stop signals to bus */
     u8ErrorStatus = I2C_Stop(pI2Cx);

     return u8ErrorStatus;
            
}
/*****************************************************************************//*!
   *
   * @brief read data from I2C,and wait to complete transferring.
   *        
   * @param[in] pI2Cx    point to I2C module type.
   * @param[in]  u16SlaveAddress slave address. 
   * @param[in]  pRdBuff point the first address of reading data buffer. 
   * @param[in]  the length of transfering data.
   *
   * @return error status
   *
   * @ Pass/ Fail criteria:  none
*****************************************************************************/

uint8_t I2C_MasterReadWait(I2C_Type *pI2Cx,uint16_t u16SlaveAddress,uint8_t *pRdBuff,uint32_t u32Length)
{
    uint32_t i;
    uint8_t u8ErrorStatus;

    /* send start signals to bus */
    u8ErrorStatus = I2C_Start(pI2Cx);

    /* send device address to slave */
    u8ErrorStatus = I2C_WriteOneByte(pI2Cx,((uint8_t)u16SlaveAddress<<1) | I2C_READ);

    /* if no error occur, received the correct ack from slave
            continue to send data to slave
        */
    /* dummy read one byte to switch to Rx mode */
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
     /* send stop signals to bus */
     u8ErrorStatus = I2C_Stop(pI2Cx);
     
     return u8ErrorStatus;
            
}
/*****************************************************************************//*!
   *
   * @brief set call back function for I2C1 module.
   *        
   * @param[in] pCallBack point to address of I2C1 call back function.
   *
   * @return none.
   *
   * @ Pass/ Fail criteria:  none.
*****************************************************************************/

void I2C1_SetCallBack( I2C_CallbackType pCallBack )
{
    I2C_Callback[1] = pCallBack;
}

/*****************************************************************************//*!
   *
   * @brief set call back function for I2C0 module.
   *        
   * @param[in] pCallBack point to address of I2C0 call back function.
   *
   * @return none.
   *
   * @ Pass/ Fail criteria:  none.
*****************************************************************************/

void I2C0_SetCallBack( I2C_CallbackType pCallBack )
{
    I2C_Callback[0] = pCallBack;
}
/*! @} End of i2c_api_list                                               						*/


/*****************************************************************************//*!
   *
   * @brief I2C0 interrupt service routine.
   *        
   * @param  
   *
   * @return none
   *
   * @ Pass/ Fail criteria:  none
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
   * @brief I2C1 interrupt service routine.
   *        
   * @param  
   *
   * @return none
   *
   * @ Pass/ Fail criteria:  none
*****************************************************************************/
void I2C1_Isr( void )
{
    if( I2C_Callback[1] )
    {
        I2C_Callback[1]();
    }
}



