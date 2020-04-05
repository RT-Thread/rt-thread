/**************************************************************************//**
 * @file     I2C.h
 * @version  V3.0
 * $Revision: 6 $
 * $Date: 15/05/22 11:22a $
 * @brief    I2C Driver Header File
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef __I2C_H__
#define __I2C_H__


#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup I2C_Driver I2C Driver
  @{
*/

/** @addtogroup I2C_EXPORTED_CONSTANTS I2C Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/*  I2CON constant definitions.                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define I2C_I2CON_STA_SI            0x28UL /*!< I2CON setting for I2C control bits. It would set STA and SI bits          */
#define I2C_I2CON_STA_SI_AA         0x2CUL /*!< I2CON setting for I2C control bits. It would set STA, SI and AA bits      */
#define I2C_I2CON_STO_SI            0x18UL /*!< I2CON setting for I2C control bits. It would set STO and SI bits          */
#define I2C_I2CON_STO_SI_AA         0x1CUL /*!< I2CON setting for I2C control bits. It would set STO, SI and AA bits      */
#define I2C_I2CON_SI                0x08UL /*!< I2CON setting for I2C control bits. It would set SI bit                   */
#define I2C_I2CON_SI_AA             0x0CUL /*!< I2CON setting for I2C control bits. It would set SI and AA bits           */
#define I2C_I2CON_STA               0x20UL /*!< I2CON setting for I2C control bits. It would set STA bit                  */
#define I2C_I2CON_STO               0x10UL /*!< I2CON setting for I2C control bits. It would set STO bit                  */
#define I2C_I2CON_AA                0x04UL /*!< I2CON setting for I2C control bits. It would set AA bit                   */

#define I2C_GCMODE_ENABLE           1      /*!< Enable  I2C GC Mode                                                       */
#define I2C_GCMODE_DISABLE          0      /*!< Disable I2C GC Mode                                                       */

/*@}*/ /* end of group I2C_EXPORTED_CONSTANTS */

/** @addtogroup I2C_EXPORTED_FUNCTIONS I2C Exported Functions
  @{
*/
/**
 *    @brief        The macro is used to set I2C bus condition at One Time
 *
 *    @param[in]    i2c        Specify I2C port
 *    @param[in]    u8Ctrl     A byte writes to I2C control register
 *
 *    @return       None
 *
 *    @details      Set I2CON register to control I2C bus conditions of START, STOP, SI, ACK.
 */
#define I2C_SET_CONTROL_REG(i2c, u8Ctrl) ((i2c)->I2CON = ((i2c)->I2CON & ~0x3c) | (u8Ctrl))

/**
 *    @brief        The macro is used to set START condition of I2C Bus
 *
 *    @param[in]    i2c        Specify I2C port
 *
 *    @return       None
 *
 *    @details      Set the I2C bus START condition in I2CON register.
 */
#define I2C_START(i2c)  ((i2c)->I2CON = ((i2c)->I2CON & ~I2C_I2CON_SI_Msk) | I2C_I2CON_STA_Msk)

/**
 *    @brief        The macro is used to wait I2C bus status get ready
 *
 *    @param[in]    i2c        Specify I2C port
 *
 *    @return       None
 *
 *    @details      When a new status is presented of I2C bus, the SI flag will be set in I2CON register.
 */
#define I2C_WAIT_READY(i2c)     while(!((i2c)->I2CON & I2C_I2CON_SI_Msk))

/**
 *    @brief        The macro is used to Read I2C Bus Data Register
 *
 *    @param[in]    i2c        Specify I2C port
 *
 *    @return       A byte of I2C data register
 *
 *    @details      I2C controller read data from bus and save it in I2CDAT register.
 */
#define I2C_GET_DATA(i2c)   ((i2c)->I2CDAT)

/**
 *    @brief        Write a Data to I2C Data Register
 *
 *    @param[in]    i2c         Specify I2C port
 *    @param[in]    u8Data      A byte that writes to data register
 *
 *    @return       None
 *
 *    @details      When write a data to I2CDAT register, the I2C controller will shift it to I2C bus.
 */
#define I2C_SET_DATA(i2c, u8Data) ((i2c)->I2CDAT = (u8Data))

/**
 *    @brief        Get I2C Bus status code
 *
 *    @param[in]    i2c        Specify I2C port
 *
 *    @return       I2C status code
 *
 *    @details      To get this status code to monitor I2C bus event.
 */
#define I2C_GET_STATUS(i2c) ((i2c)->I2CSTATUS)

/**
 *    @brief        Get Time-out flag from I2C Bus
 *
 *    @param[in]    i2c     Specify I2C port
 *
 *    @retval       0       I2C Bus time-out is not happened
 *    @retval       1       I2C Bus time-out is happened
 *
 *    @details      When I2C bus occurs time-out event, the time-out flag will be set.
 */
#define I2C_GET_TIMEOUT_FLAG(i2c)   ( ((i2c)->I2CTOC & I2C_I2CTOC_TIF_Msk) == I2C_I2CTOC_TIF_Msk ? 1:0 )

/**
 *    @brief        To get wake-up flag from I2C Bus
 *
 *    @param[in]    i2c     Specify I2C port
 *
 *    @retval       0       Chip is not woken-up from power-down mode
 *    @retval       1       Chip is woken-up from power-down mode
 *
 *    @details      I2C bus occurs wake-up event, wake-up flag will be set.
 */
#define I2C_GET_WAKEUP_FLAG(i2c) ( ((i2c)->I2CWKUPSTS & I2C_I2CWKUPSTS_WKUPIF_Msk) == I2C_I2CWKUPSTS_WKUPIF_Msk ? 1:0  )

/**
 *    @brief        To clear wake-up flag
 *
 *    @param[in]    i2c     Specify I2C port
 *
 *    @return       None
 *
 *    @details      If wake-up flag is set, use this macro to clear it.
 */
#define I2C_CLEAR_WAKEUP_FLAG(i2c)  ((i2c)->I2CWKUPSTS |= I2C_I2CWKUPSTS_WKUPIF_Msk)

/*---------------------------------------------------------------------------------------------------------*/
/* inline functions                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/

/**
 *    @brief        The macro is used to set STOP condition of I2C Bus
 *
 *    @param[in]    i2c        Specify I2C port
 *
 *    @return       None
 *
 *    @details      Set the I2C bus STOP condition in I2CON register and wait STOP condition finish.
 */
static __INLINE void I2C_STOP(I2C_T *i2c)
{
    (i2c)->I2CON |= (I2C_I2CON_SI_Msk | I2C_I2CON_STO_Msk);
    while((i2c)->I2CON & I2C_I2CON_STO_Msk);
}

void I2C_ClearTimeoutFlag(I2C_T *i2c);
void I2C_Close(I2C_T *i2c);
void I2C_Trigger(I2C_T *i2c, uint8_t u8Start, uint8_t u8Stop, uint8_t u8Si, uint8_t u8Ack);
void I2C_DisableInt(I2C_T *i2c);
void I2C_EnableInt(I2C_T *i2c);
uint32_t I2C_GetBusClockFreq(I2C_T *i2c);
uint32_t I2C_SetBusClockFreq(I2C_T *i2c, uint32_t u32BusClock);
uint32_t I2C_GetIntFlag(I2C_T *i2c);
uint32_t I2C_GetStatus(I2C_T *i2c);
uint32_t I2C_Open(I2C_T *i2c, uint32_t u32BusClock);
uint8_t I2C_GetData(I2C_T *i2c);
void I2C_SetSlaveAddr(I2C_T *i2c, uint8_t u8SlaveNo, uint8_t u8SlaveAddr, uint8_t u8GCMode);
void I2C_SetSlaveAddrMask(I2C_T *i2c, uint8_t u8SlaveNo, uint8_t u8SlaveAddrMask);
void I2C_EnableTimeout(I2C_T *i2c, uint8_t u8LongTimeout);
void I2C_DisableTimeout(I2C_T *i2c);
void I2C_EnableWakeup(I2C_T *i2c);
void I2C_DisableWakeup(I2C_T *i2c);
void I2C_SetData(I2C_T *i2c, uint8_t u8Data);

/*@}*/ /* end of group I2C_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group I2C_Driver */

/*@}*/ /* end of group Device_Driver */

#ifdef __cplusplus
}
#endif
#endif //__I2C_H__
