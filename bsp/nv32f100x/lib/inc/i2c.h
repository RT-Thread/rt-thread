/******************************************************************************
* @brief header file for I2C module utilities (I2C). 
*
*******************************************************************************
*
* provide APIs for accessing I2C module (I2C)
******************************************************************************/
#ifndef _I2C_H__
#define _I2C_H__
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
* Global variables
******************************************************************************/

/******************************************************************************
* Constants and macros
******************************************************************************/
/******************************************************************************
* define I2C work read or write 
*
*//*! @addtogroup i2c_read_write_list
* @{
*******************************************************************************/
#define I2C_READ                        0x01				/*!< I2C read */
#define I2C_WRITE                       0x0  				/*!< I2C write */
/*! @} End of i2c_read_write_list                                             */

#define I2C_SEND_ACK                    0						/*!< I2C send ACK */
#define I2C_SEND_NACK                   1						/*!< I2C send NACK */

#define I2C_WAIT_STATUS_ETMEOUT         200000

/******************************************************************************
* define I2C error state
*
*//*! @addtogroup i2c_error_state_list
* @{
*******************************************************************************/
#define I2C_ERROR_NULL                  0x00			/*!< I2C sucess*/
#define I2C_ERROR_NO_WAIT_TCF_FLAG      0x01			/*!< I2C wait TCF overETMe*/
#define I2C_ERROR_NO_WAIT_IICIF_FLAG    0x02			/*!< I2C wait IICIF overETMe */
#define I2C_ERROR_NO_GET_ACK            0x04			/*!< I2C no get ACK */
#define I2C_ERROR_START_NO_BUSY_FLAG    0x10			/*!< I2C fail to send start signals */
#define I2C_ERROR_STOP_BUSY_FLAG        0x20			/*!< I2C fail to send stop signal */
#define I2C_ERROR_BUS_BUSY              0x80			/*!< I2C bus busy error */
/*! @} End of i2c_error_state_list                                            */

/******************************************************************************
* define I2C bus state
*
*//*! @addtogroup i2c_bus_state_list
* @{
*******************************************************************************/
#define I2C_BUS_NORMAL				0x00								/*!< I2C bus normal */
#define I2C_BUS_SLTF					0x01								/*!< I2C bus SLTF flag */
#define I2C_BUS_SHTF2					0x02								/*!< I2C bus SHTF2 flag */
/*! @} End of i2c_bus_state_list                                             */


/******************************************************************************
* Local types
******************************************************************************/

/******************************************************************************
* Local function prototypes
******************************************************************************/

/******************************************************************************
* Local variables
******************************************************************************/
#define I2C_MODE_MASTER             1
#define I2C_MODE_SLAVE              0
#define I2C_ADDRESS_7BIT            0
#define I2C_ADDRESS_10BIT           1
#define I2C_ETMEOUT_BUS_CLOCK_DIV64 0
#define I2C_ETMEOUT_BUS_CLOCK       1

/******************************************************************************
*
*//*! @addtogroup i2c_setting_type
* @{
*******************************************************************************/
/*!
 * @brief I2C setting type.
 *
 */
typedef struct
{
	uint16_t bI2CEn         :1;     			/*!< enable I2C module */
	uint16_t bIntEn         :1;    			 	/*!< enable I2C enable */
	uint16_t bWakeUpEn      :1;     			/*!< I2C wake up enable */
	uint16_t bGCAEn         :1;     			/*!< I2C General call address enable */
	uint16_t bAddressExt    :1;     			/*!< I2C extertion address selection */
	uint16_t bRangeAddEn    :1;     			/*!< enable range address */
	uint16_t bFackEn        :1;     			/*!< enable fast ack */
	uint16_t bSMB_AlertEn   :1;     			/*!< SMB Alert enable */
	uint16_t bSecondAddressEn:1;    			/*!< enable the second address */
	uint16_t bETMeoutCountClockSelect:1;  /*!< ETMeoutCountClockSelect */
    uint16_t bSHTF2IntEn    :1;					/*!< SHTF2 interrupt enable */
    uint16_t Reserve        :5;
}I2C_SettingType;
/*! @} End of i2c_setting_type                                       						*/

/******************************************************************************
*
*//*! @addtogroup i2c_config_type
* @{
*******************************************************************************/
/*!
 * @brief I2C configure type.
 *
 */
typedef struct
{
    I2C_SettingType sSetting;
    uint16_t u16F;              /*!< setting the band rate for I2C */
    uint16_t u16OwnA1;          /*!< slave address */
    uint16_t u16OwnA2;          /*!< the second slave address */
    uint16_t u16RangeA;         /*!< range address */
    uint16_t u16Filt;           /*!< Filter for I2C   */
    uint16_t u16Slt;            /*!< SCL Low ETMeout register low */
    
}I2C_ConfigType, *I2C_ConfigPtr;
/*! @} End of i2c_config_type                                             				*/

/******************************************************************************
*
*//*! @addtogroup i2c_callback
* @{
*******************************************************************************/
typedef void (*I2C_CallbackType)(void);		/*!< I2C call back function */
/*! @} End of i2c_callback                                             						*/

/******************************************************************************
* inline functions
******************************************************************************/
/******************************************************************************
*
*//*! @addtogroup i2c_api_list
* @{
*******************************************************************************/
/*****************************************************************************//*!
   *
   * @brief enable I2C to transmit data.
   *        
   * @param[in] pI2Cx      point to I2C module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void I2C_TxEnable(I2C_Type *pI2Cx)
{
    pI2Cx->C1 |= I2C_C1_TX_MASK;
}
/*****************************************************************************//*!
   *
   * @brief enable I2C to receive data.
   *        
   * @param[in] pI2Cx      point to I2C module type.
   *
   * @return none.
   *
   * @ Pass/ Fail criteria: none.
*****************************************************************************/
__STATIC_INLINE void I2C_RxEnable(I2C_Type *pI2Cx)
{
    pI2Cx->C1 &= ~I2C_C1_TX_MASK;
}

/*****************************************************************************//*!
   *
   * @brief set IIC band rate. 
   *        
   * @param[in] pI2Cx      point to I2C module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void I2C_SetBaudRate(I2C_Type *pI2Cx,uint32_t u32Bps)
{
    pI2Cx->F = (uint8_t)u32Bps;
}
/*****************************************************************************//*!
   *
   * @brief enable general call.
   *        
   * @param[in] pI2Cx      point to I2C module type.
   *
   * @return none.
   *
   * @ Pass/ Fail criteria: none.
*****************************************************************************/
__STATIC_INLINE void I2C_GeneralCallEnable(I2C_Type *pI2Cx)
{
     pI2Cx->C2 |= I2C_C2_GCAEN_MASK;
}
/*****************************************************************************//*!
   *
   * @brief SMBus Alert Response Address Enable. 
   *        
   * @param[in] pI2Cx      point to I2C module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void I2C_SMBusAlertEnable(I2C_Type *pI2Cx)
{
     pI2Cx->SMB|= I2C_SMB_ALERTEN_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Range Address Matching Enable.
   *        
   * @param[in] pI2Cx      point to I2C module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void I2C_RangeAddressEnable(I2C_Type *pI2Cx)
{
     pI2Cx->C2 |= I2C_C2_RMEN_MASK;
}
/*****************************************************************************//*!
   *
   * @brief SHTF2 Interrupt Enable.
   *        
   * @param[in] pI2Cx      point to I2C module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void I2C_SHTF2IntEnable(I2C_Type *pI2Cx)
{
     pI2Cx->SMB |= I2C_SMB_SHTF2IE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief ETMeout Counter Clock Select.
   *        
   * @param[in] pI2Cx      point to I2C module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
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
   * @brief get I2C status.
   *        
   * @param[in] pI2Cx      point to I2C module type.
   *
   * @return I2C status
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t I2C_GetStatus(I2C_Type *pI2Cx)
{
    return pI2Cx->S;
}
/*****************************************************************************//*!
   *
   * @brief clear specified status.
   *        
   * @param[in] pI2Cx      point to I2C module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void I2C_ClearStatus(I2C_Type *pI2Cx, uint8_t u8ClearFlag)
{
    pI2Cx->S |= u8ClearFlag;
}
/*****************************************************************************//*!
   *
   * @brief write data to data register.
   *        
   * @param[in] pI2Cx      point to I2C module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void I2C_WriteDataReg(I2C_Type *pI2Cx, uint8_t u8DataBuff)
{
    pI2Cx->D = u8DataBuff;
}
/*****************************************************************************//*!
   *
   * @brief read data from data register.
   *        
   * @param[in] pI2Cx      point to I2C module type.
   *
   * @return I2C data register value
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t I2C_ReadDataReg(I2C_Type *pI2Cx )
{
    return pI2Cx->D;
}
/*****************************************************************************//*!
   *
   * @brief check if is Tx mode.
   *        
   * @param[in] pI2Cx      point to I2C module type.
   *
   * @return result  TRUE or FALSE
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t I2C_IsTxMode(I2C_Type *pI2Cx )
{
    return(pI2Cx->C1 & I2C_C1_TX_MASK);
}
/*****************************************************************************//*!
   *
   * @brief check I2C if busy.
   *        
   * @param[in] pI2Cx      point to I2C module type.
   *
   * @return result  TRUE or FALSE
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t I2C_IsBusy(I2C_Type *pI2Cx )
{
    return (pI2Cx->S & I2C_S_BUSY_MASK);
}
/*****************************************************************************//*!
   *
   * @brief check I2C receive ack or nack.
   *        
   * @param[in] pI2Cx      point to I2C module type.
   *
   * @return result    TRUE or FALSE
   *
   * @ Pass/ Fail criteria: none.
*****************************************************************************/
__STATIC_INLINE uint8_t I2C_IsReceivedAck(I2C_Type *pI2Cx )
{
    return (pI2Cx->S & I2C_S_RXAK_MASK);
}
/*****************************************************************************//*!
   *
   * @brief check I2C if is master mode.
   *        
   * @param[in] pI2Cx    point to I2C module type.
   *
   * @return result    TRUE or FALSE.
   *
   * @ Pass/ Fail criteria: none.
*****************************************************************************/
__STATIC_INLINE uint8_t I2C_IsMasterMode(I2C_Type *pI2Cx )
{
    return(pI2Cx->C1 & I2C_C1_MST_MASK);
}
/*****************************************************************************//*!
   *
   * @brief check SCL Low ETMeout Flag.
   *        
   * @param[in] pI2Cx    point to I2C module type.
   *
   * @return result    TRUE or FALSE.
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t I2C_IsSMB_SLTF(I2C_Type *pI2Cx )
{
    return (pI2Cx->SMB & I2C_SMB_SLTF_MASK);
}
/*****************************************************************************//*!
   *
   * @brief check SCL High ETMeout Flag is set or clear.
   *        
   * @param[in] pI2Cx    point to I2C module type.
   *
   * @return result    TRUE or FALSE.
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t I2C_IsSMB_SHTF2(I2C_Type *pI2Cx )
{
    return(pI2Cx->SMB & I2C_SMB_SHTF2_MASK);
}
/*****************************************************************************//*!
   *
   * @brief clear SLTF flag.
   *        
   * @param[in] pI2Cx    point to I2C module type.
   *
   * @return none.
   *
   * @ Pass/ Fail criteria: none.
*****************************************************************************/
__STATIC_INLINE void I2C_ClearSLTF(I2C_Type *pI2Cx )
{
    pI2Cx->SMB |= I2C_SMB_SLTF_MASK;
}
/*****************************************************************************//*!
   *
   * @brief clear SHTF2 flag.
   *        
   * @param[in] pI2Cx    point to I2C module type.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void I2C_ClearSHTF2(I2C_Type *pI2Cx )
{
    pI2Cx->SMB |= I2C_SMB_SHTF2_MASK;
}
/*****************************************************************************//*!
   *
   * @brief send out ACK.
   *        
   * @param[in] pI2Cx    point to I2C module type.
   *
   * @return none.
   *
   * @ Pass/ Fail criteria: none.
*****************************************************************************/
__STATIC_INLINE void I2C_SendAck(I2C_Type *pI2Cx )
{
    pI2Cx->C1 &= ~I2C_C1_TXAK_MASK;
}
/*****************************************************************************//*!
   *
   * @brief send out NACK.
   *        
   * @param[in] pI2Cx    point to I2C module type.
   *
   * @return none.
   *
   * @ Pass/ Fail criteria: none.
*****************************************************************************/
__STATIC_INLINE void I2C_SendNack(I2C_Type *pI2Cx )
{
    pI2Cx->C1 |= I2C_C1_TXAK_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Second I2C Address Enable.
   *        
   * @param[in] pI2Cx    point to I2C module type.
   *
   * @return none.
   *
   * @ Pass/ Fail criteria: none.
*****************************************************************************/
__STATIC_INLINE void I2C_SecondAddressEnable(I2C_Type *pI2Cx)
{
     pI2Cx->SMB |= I2C_SMB_SIICAEN_MASK;
}
/******************************************************************************
* Global functions
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

/*! @} End of i2c_bus_state_list                                             						*/

#ifdef __cplusplus
}
#endif
#endif //


