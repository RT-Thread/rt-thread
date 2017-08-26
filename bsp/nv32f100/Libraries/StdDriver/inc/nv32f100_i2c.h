/******************************************************************************
*
* @brief  I2C 驱动头文件.  
*
******************************************************************************/
#ifndef _I2C_H__
#define _I2C_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
/******************************************************************************
* 定义I2C的读和写
*
*//*! 
* @{
*******************************************************************************/
#define I2C_READ                        0x01				/*!< I2C 读 */
#define I2C_WRITE                       0x0  				/*!< I2C 写 */
/*! @}                                            */

#define I2C_SEND_ACK                    0				/*!< I2C 发送 ACK */
#define I2C_SEND_NACK                   1				/*!< I2C 发送 NACK */

#define I2C_WAIT_STATUS_ETMEOUT         200000

/******************************************************************************
* 定义I2C错误状态
*
*//*!
* @{
*******************************************************************************/
#define I2C_ERROR_NULL                  0x00			/*!< I2C 工作成功*/
#define I2C_ERROR_NO_WAIT_TCF_FLAG      0x01			/*!< I2C 等待传输完成超时*/
#define I2C_ERROR_NO_WAIT_IICIF_FLAG    0x02			/*!< I2C 等待中断超时 */
#define I2C_ERROR_NO_GET_ACK            0x04			/*!< I2C 没有得到 ACK */
#define I2C_ERROR_START_NO_BUSY_FLAG    0x10			/*!< I2C 没有成功发送起始信号 */
#define I2C_ERROR_STOP_BUSY_FLAG        0x20			/*!< I2C 没有成功发送停止信号 */
#define I2C_ERROR_BUS_BUSY              0x80			/*!< I2C 总线繁忙错误 */
/*! @} End of i2c_error_state_list                                            */

/******************************************************************************
* 定义I2C总线状态
*
*//*! 
* @{
*******************************************************************************/
#define I2C_BUS_NORMAL				        0x00								/*!< I2C 总线正常 */
#define I2C_BUS_SLTF					0x01								/*!< I2C 总线偏移一个FLAG */
#define I2C_BUS_SHTF2					0x02								/*!< I2C 总线偏移两个FLAG */
/*! @}                                                                        */


#define I2C_MODE_MASTER             1
#define I2C_MODE_SLAVE              0
#define I2C_ADDRESS_7BIT            0
#define I2C_ADDRESS_10BIT           1
#define I2C_ETMEOUT_BUS_CLOCK_DIV64 0
#define I2C_ETMEOUT_BUS_CLOCK       1

/******************************************************************************
*
*//*! @I2C控制参数结构体
* @{
*******************************************************************************/
/*!
 * @I2C控制参数结构体.
 *
 */
typedef struct
{
	uint16_t bI2CEn         :1;     			/*!< 使能I2C模块 */
	uint16_t bIntEn         :1;    			 	/*!< 使能I2C中断 */
	uint16_t bWakeUpEn      :1;     			/*!< I2C唤醒使能 */
	uint16_t bGCAEn         :1;     			/*!< I2C通用启动地址使能 */
	uint16_t bAddressExt    :1;     			/*!< I2C地址扩展选择 */
	uint16_t bRangeAddEn    :1;     			/*!< 使能范围地址匹配 */
	uint16_t bFackEn        :1;     			/*!< 使能快速ack */
	uint16_t bSMB_AlertEn   :1;     			/*!< SMB 报警响应地址使能 */
	uint16_t bSecondAddressEn:1;    			/*!< 启用第二I2C地址 */
	uint16_t bETMeoutCountClockSelect:1;                    /*!< 超时计数器时钟选择 */
    uint16_t bSHTF2IntEn    :1;					/*!< SHTF2 中断使能 */
    uint16_t Reserve        :5;
}I2C_SettingType;
/*! @}                                      						*/

/******************************************************************************
*
*//*! @I2C配置结构体
* @{
*******************************************************************************/
/*!
 * @I2C配置结构体.
 *
 */
typedef struct
{
    I2C_SettingType sSetting;
    uint16_t u16F;              /*!< 设置I2C模块的波特率 */
    uint16_t u16OwnA1;          /*!< 从机地址 */
    uint16_t u16OwnA2;          /*!< SMBus使用的从机地址 */
    uint16_t u16RangeA;         /*!< 范围地址 */
    uint16_t u16Filt;           /*!< I2C输入干扰滤波器   */
    uint16_t u16Slt;            /*!< SCL低超时周期 */
    
}I2C_ConfigType, *I2C_ConfigPtr;
/*! @}                                           				*/

/*!
 * @brief I2C 回调类型.
 *
 */

typedef void (*I2C_CallbackType)(void);		
/*! @}                            						*/

/******************************************************************************
******************************************************************************/

/*!
 * 内联函数
 */

/*****************************************************************************//*!
*
* @brief 配置I2C发送模式.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void I2C_TxEnable(I2C_Type *pI2Cx)
{
    pI2Cx->C1 |= I2C_C1_TX_MASK;
}

/*****************************************************************************//*!
*
* @brief 配置I2C接收模式.
*      
* @param[in] pI2Cx      I2C的基址.
*
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void I2C_RxEnable(I2C_Type *pI2Cx)
{
    pI2Cx->C1 &= ~I2C_C1_TX_MASK;
}

/*****************************************************************************//*!
*
* @brief 设置I2C波特率. 
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void I2C_SetBaudRate(I2C_Type *pI2Cx,uint32_t u32Bps)
{
    pI2Cx->F = (uint8_t)u32Bps;
}

/*****************************************************************************//*!
*
* @brief 使能通用地址启动.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void I2C_GeneralCallEnable(I2C_Type *pI2Cx)
{
     pI2Cx->C2 |= I2C_C2_GCAEN_MASK;
}

/*****************************************************************************//*!
*
* @brief SMBus 报警响应地址使能. 
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void I2C_SMBusAlertEnable(I2C_Type *pI2Cx)
{
     pI2Cx->SMB|= I2C_SMB_ALERTEN_MASK;
}

/*****************************************************************************//*!
*
* @brief 范围地址匹配使能.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void I2C_RangeAddressEnable(I2C_Type *pI2Cx)
{
     pI2Cx->C2 |= I2C_C2_RMEN_MASK;
}

/*****************************************************************************//*!
*
* @brief SHTF2 中断使能.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void I2C_SHTF2IntEnable(I2C_Type *pI2Cx)
{
     pI2Cx->SMB |= I2C_SMB_SHTF2IE_MASK;
}

/*****************************************************************************//*!
*
* @brief 超时计数器时钟选择.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void I2C_ETMeoutCounterClockSelect(I2C_Type *pI2Cx, uint8_t u8Clock)
{
    if( u8Clock )
    {
        pI2Cx->SMB |= I2C_SMB_TCKSEL_MASK;
    }
    else
    {
        pI2Cx->SMB &= ~I2C_SMB_TCKSEL_MASK;
    }
}

/*****************************************************************************//*!
*
* @brief 获取I2C的状态.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return I2C的状态
*
*****************************************************************************/
__STATIC_INLINE uint8_t I2C_GetStatus(I2C_Type *pI2Cx)
{
    return pI2Cx->S;
}

/*****************************************************************************//*!
*
* @brief 清除特定的状态.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void I2C_ClearStatus(I2C_Type *pI2Cx, uint8_t u8ClearFlag)
{
    pI2Cx->S |= u8ClearFlag;
}

/*****************************************************************************//*!
*
* @brief 写数据到数据寄存器.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void I2C_WriteDataReg(I2C_Type *pI2Cx, uint8_t u8DataBuff)
{
    pI2Cx->D = u8DataBuff;
}

/*****************************************************************************//*!
*
* @brief 从数据寄存器读取数据.
*        
* @param[in] pI2Cx       I2C的基址.
*
* @return I2C数据寄存器值
*
*****************************************************************************/
__STATIC_INLINE uint8_t I2C_ReadDataReg(I2C_Type *pI2Cx )
{
    return pI2Cx->D;
}

/*****************************************************************************//*!
*
* @brief 检查I2C模式是否为发送.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return 是/否
*
*****************************************************************************/
__STATIC_INLINE uint8_t I2C_IsTxMode(I2C_Type *pI2Cx )
{
    return(pI2Cx->C1 & I2C_C1_TX_MASK);
}

/*****************************************************************************//*!
*
* @brief 检查总线是否繁忙.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return 是/否
*
*****************************************************************************/
__STATIC_INLINE uint8_t I2C_IsBusy(I2C_Type *pI2Cx )
{
    return (pI2Cx->S & I2C_S_BUSY_MASK);
}

/*****************************************************************************//*!
*
* @brief 确认信号是否被接收.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return 是/否
*
*****************************************************************************/
__STATIC_INLINE uint8_t I2C_IsReceivedAck(I2C_Type *pI2Cx )
{
    return (pI2Cx->S & I2C_S_RXAK_MASK);
}

/*****************************************************************************//*!
*
* @brief 检查I2C是否为主机模式.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return 是/否.
*
*****************************************************************************/
__STATIC_INLINE uint8_t I2C_IsMasterMode(I2C_Type *pI2Cx )
{
    return(pI2Cx->C1 & I2C_C1_MST_MASK);
}

/*****************************************************************************//*!
*
* @brief 检查有无低超时发生.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return 是/否.
*
*****************************************************************************/
__STATIC_INLINE uint8_t I2C_IsSMB_SLTF(I2C_Type *pI2Cx )
{
    return (pI2Cx->SMB & I2C_SMB_SLTF_MASK);
}

/*****************************************************************************//*!
*
* @brief 检查有无高超时发生.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return 是/否.
*
*****************************************************************************/
__STATIC_INLINE uint8_t I2C_IsSMB_SHTF2(I2C_Type *pI2Cx )
{
    return(pI2Cx->SMB & I2C_SMB_SHTF2_MASK);
}

/*****************************************************************************//*!
*
* @brief 清除SCL低超时标志.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void I2C_ClearSLTF(I2C_Type *pI2Cx )
{
    pI2Cx->SMB |= I2C_SMB_SLTF_MASK;
}

/*****************************************************************************//*!
*
* @brief 清除高超时标志位2.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void I2C_ClearSHTF2(I2C_Type *pI2Cx )
{
    pI2Cx->SMB |= I2C_SMB_SHTF2_MASK;
}

/*****************************************************************************//*!
*
* @brief 发送信号ACK.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void I2C_SendAck(I2C_Type *pI2Cx )
{
    pI2Cx->C1 &= ~I2C_C1_TXAK_MASK;
}

/*****************************************************************************//*!
*
* @brief 发送信号NACK.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void I2C_SendNack(I2C_Type *pI2Cx )
{
    pI2Cx->C1 |= I2C_C1_TXAK_MASK;
}

/*****************************************************************************//*!
*
* @brief 使能第二I2C地址.
*        
* @param[in] pI2Cx      I2C的基址.
*
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void I2C_SecondAddressEnable(I2C_Type *pI2Cx)
{
     pI2Cx->SMB |= I2C_SMB_SIICAEN_MASK;
}

/******************************************************************************
******************************************************************************/
void I2C_Init(I2C_Type *pI2Cx,I2C_ConfigPtr pI2CConfig);
uint8_t I2C_Start(I2C_Type *pI2Cx);
uint8_t I2C_Stop(I2C_Type *pI2Cx);
uint8_t I2C_RepeatStart(I2C_Type *pI2Cx);
uint8_t I2C_IsTxMode(I2C_Type *pI2Cx );
uint8_t I2C_IsBusy(I2C_Type *pI2Cx );
uint8_t I2C_IsReceivedAck(I2C_Type *pI2Cx );
uint8_t I2C_IsMasterMode(I2C_Type *pI2Cx );
void I2C_ClearSHTF2(I2C_Type *pI2Cx );
void I2C_ClearSLTF(I2C_Type *pI2Cx );
uint8_t I2C_IsSMB_SHTF2(I2C_Type *pI2Cx );
uint8_t I2C_IsSMB_SLTF(I2C_Type *pI2Cx );
void I2C_TxEnable(I2C_Type *pI2Cx);
void I2C_RxEnable(I2C_Type *pI2Cx);
void I2C_IntEnable(I2C_Type *pI2Cx);
void I2C_IntDisable(I2C_Type *pI2Cx);
void I2C_SetBaudRate(I2C_Type *pI2Cx,uint32_t u32Bps);
void I2C_SetSlaveAddress(I2C_Type *pI2Cx,uint16_t u16SlaveAddress);
void I2C_GeneralCallEnable(I2C_Type *pI2Cx);
void I2C_SMBusAlertEnable(I2C_Type *pI2Cx);
void I2C_RangeAddressEnable(I2C_Type *pI2Cx);
void I2C_SHTF2IntEnable(I2C_Type *pI2Cx);
void I2C_ETMeoutCounterClockSelect(I2C_Type *pI2Cx, uint8_t u8Clock);
void I2C_SetSCLLowETMeout(I2C_Type *pI2Cx, uint16_t u16ETMeout);
uint8_t I2C_GetStatus(I2C_Type *pI2Cx);
void I2C_ClearStatus(I2C_Type *pI2Cx, uint8_t u8ClearFlag);
void I2C_SendAck(I2C_Type *pI2Cx );
void I2C_SendNack(I2C_Type *pI2Cx );
void I2C_SecondAddressEnable(I2C_Type *pI2Cx);
void I2C_ClearStatus(I2C_Type *pI2Cx, uint8_t u8ClearFlag);
void I2C_WriteDataReg(I2C_Type *pI2Cx, uint8_t u8DataBuff);
uint8_t I2C_ReadDataReg(I2C_Type *pI2Cx );
void I2C_Deinit(I2C_Type *pI2Cx);
uint8_t I2C_WriteOneByte(I2C_Type *pI2Cx, uint8_t u8WrBuff);
uint8_t I2C_ReadOneByte(I2C_Type *pI2Cx, uint8_t *pRdBuff, uint8_t u8Ack);
uint8_t I2C_MasterSendWait(I2C_Type *pI2Cx,uint16_t u16SlaveAddress,uint8_t *pWrBuff,uint32_t u32Length);
uint8_t I2C_MasterReadWait(I2C_Type *pI2Cx,uint16_t u16SlaveAddress,uint8_t *pRdBuff,uint32_t u32Length);
void I2C0_SetCallBack( I2C_CallbackType pCallBack );
void I2C1_SetCallBack( I2C_CallbackType pCallBack );

/*! @}                              						*/

#ifdef __cplusplus
}
#endif
#endif //


