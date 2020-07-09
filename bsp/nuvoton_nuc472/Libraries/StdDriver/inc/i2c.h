/****************************************************************************//**
 * @file     i2c.h
 * @version  V1.00
 * $Revision: 13 $
 * $Date: 15/11/20 7:27p $
 * @brief    NUC472/NUC442 I2C driver header file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_I2C_Driver I2C Driver
  @{
*/

/** @addtogroup NUC472_442_I2C_EXPORTED_CONSTANTS I2C Exported Constants
  @{
*/

#define I2C_STA 0x20    /*!< I2C START bit value  \hideinitializer */
#define I2C_STO 0x10    /*!< I2C STOP bit value  \hideinitializer */
#define I2C_SI  0x08    /*!< I2C SI bit value  \hideinitializer */
#define I2C_AA  0x04    /*!< I2C ACK bit value  \hideinitializer */

#define I2C_GCMODE_ENABLE   1    /*!< Enable I2C GC Mode  \hideinitializer */
#define I2C_GCMODE_DISABLE  0    /*!< Disable I2C GC Mode  \hideinitializer */

/*@}*/ /* end of group NUC472_442_I2C_EXPORTED_CONSTANTS */


/** @addtogroup NUC472_442_I2C_EXPORTED_FUNCTIONS I2C Exported Functions
  @{
*/

/**
  * @brief This macro sets the I2C control register at one time.
  * @param[in] i2c is the base address of I2C module.
  * @param[in] u8Ctrl is the register value of I2C control register.
  * @return none
  * \hideinitializer
  */
#define I2C_SET_CONTROL_REG(i2c, u8Ctrl) ( (i2c)->CTL = ((i2c)->CTL & ~0x3c) | u8Ctrl )

/**
  * @brief This macro only set START bit to the control register of I2C module.
  * @param[in] i2c is the base address of I2C module.
  * @return none
  * \hideinitializer
  */
#define I2C_START(i2c) ( (i2c)->CTL = ((i2c)->CTL & ~I2C_CTL_SI_Msk) | I2C_CTL_STA_Msk )

/**
  * @brief This macro only set STOP bit to the control register of I2C module.
  * @param[in] i2c is the base address of I2C module.
  * @return none
  * \hideinitializer
  */
#define I2C_STOP(i2c) ( (i2c)->CTL = ((i2c)->CTL & ~0x3c) | I2C_CTL_SI_Msk | I2C_CTL_STO_Msk )

/**
  * @brief This macro will return when I2C module is ready.
  * @param[in] i2c is the base address of I2C module.
  * @return none
  * \hideinitializer
  */
#define I2C_WAIT_READY(i2c) while(!((i2c)->CTL & I2C_CTL_SI_Msk))

/**
  * @brief This macro returns the data stored in data register of I2C module.
  * @param[in] i2c is the base address of I2C module.
  * @return Data.
  * \hideinitializer
  */
#define I2C_GET_DATA(i2c) ( (i2c)->DAT )

/**
  * @brief This macro writes the data to data register of I2C module.
  * @param[in] i2c is the base address of I2C module.
  * @param[in] u8Data is the data which will be write to data register of I2C module.
  * @return none
  * \hideinitializer
  */
#define I2C_SET_DATA(i2c, u8Data) ( (i2c)->DAT = u8Data )

/**
  * @brief This macro returns the status of I2C module.
  * @param[in] i2c is the base address of I2C module.
  * @return Status.
  * \hideinitializer
  */
#define I2C_GET_STATUS(i2c) ( (i2c)->STATUS )

/**
  * @brief This macro returns time-out flag.
  * @param[in] i2c is the base address of I2C module.
  * @return Status.
  * @retval 0 Flag is not set.
  * @retval 1 Flag is set.
  * \hideinitializer
  */
#define I2C_GET_TIMEOUT_FLAG(i2c) ( ((i2c)->TOCTL & I2C_TOCTL_TOIF_Msk) == I2C_TOCTL_TOIF_Msk ? 1:0  )

/**
  * @brief This macro returns wakeup flag.
  * @param[in] i2c is the base address of I2C module.
  * @return Status.
  * @retval 0 Flag is not set.
  * @retval 1 Flag is set.
  * \hideinitializer
  */
#define I2C_GET_WAKEUP_FLAG(i2c) ( ((i2c)->WKSTS & I2C_WKSTS_WKIF_Msk) == I2C_WKSTS_WKIF_Msk ? 1:0  )

/**
  * @brief This macro clears wakeup flag.
  * @param[in] i2c is the base address of I2C module.
  * @return none
  */
#define I2C_CLEAR_WAKEUP_FLAG(i2c)  ((i2c)->WKSTS |= I2C_WKSTS_WKIF_Msk )


uint32_t I2C_Open(I2C_T *i2c, uint32_t u32BusClock);
void I2C_Close(I2C_T *i2c);
void I2C_ClearTimeoutFlag(I2C_T *i2c);
void I2C_Trigger(I2C_T *i2c, uint8_t u8Start, uint8_t u8Stop, uint8_t u8Si, uint8_t u8Ack);
void I2C_DisableInt(I2C_T *i2c);
void I2C_EnableInt(I2C_T *i2c);
uint32_t I2C_GetBusClockFreq(I2C_T *i2c);
uint32_t I2C_SetBusClockFreq(I2C_T *i2c, uint32_t u32BusClock);
uint32_t I2C_GetIntFlag(I2C_T *i2c);
uint32_t I2C_GetStatus(I2C_T *i2c);
uint32_t I2C_GetData(I2C_T *i2c);
void I2C_SetData(I2C_T *i2c, uint8_t u8Data);
void I2C_SetSlaveAddr(I2C_T *i2c, uint8_t u8SlaveNo, uint8_t u8SlaveAddr, uint8_t u8GCMode);
void I2C_SetSlaveAddrMask(I2C_T *i2c, uint8_t u8SlaveNo, uint8_t u8SlaveAddrMask);
void I2C_EnableTimeout(I2C_T *i2c, uint8_t u8LongTimeout);
void I2C_DisableTimeout(I2C_T *i2c);
void I2C_EnableWakeup(I2C_T *i2c);
void I2C_DisableWakeup(I2C_T *i2c);

/*@}*/ /* end of group NUC472_442_I2C_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_I2C_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__I2C_H__

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
