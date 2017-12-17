/**************************************************************************//**
 * @file     PS2.h
 * @version  V0.10
 * $Revision: 6 $
 * $Date: 14/10/06 1:58p $
 * @brief    NUC472/NUC442 PS2 Driver Header File
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __PS2_H__
#define __PS2_H__

/*---------------------------------------------------------------------------------------------------------*/
/* Include related headers                                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
#include "NUC472_442.h"

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_PS2_Driver PS2 Driver
  @{
*/


/** @addtogroup NUC472_442_PS2_EXPORTED_FUNCTIONS PS2 Exported Functions
  @{
*/


/**
 *  @brief    This function use to set TX FIFO length.
 *
 *  @param[in]    u32Count    TX FIFO length
 *
 *  @return   None
 * \hideinitializer 
 */
#define PS2_SET_TX_BYTE_CNT(u32Count) (PS2->CTL = (PS2->CTL & ~PS2_CTL_TXFDEPTH_Msk) \
                                      | ((u32Count-1) << PS2_CTL_TXFDEPTH_Pos))

/**
 *  @brief    This function use to get PS2 status.
 *
 *  @param    None
 *
 *  @return   PS2 status
 * \hideinitializer 
 */
#define PS2_GET_STATUS() (PS2->STATUS)

/**
 *  @brief    This function use to clear PS2 status.
 *
 *  @param[in]    u32Mask    Clear the specified status of Ps2 module:
 *                         \ref PS2_STATUS_FRAMEERR_Msk , \ref PS2_STATUS_RXOV_Msk
 *
 *  @return   None
 */
#define PS2_CLR_STATUS(u32Mask) (PS2D->PS2STATUS = u32Mask)

/**
 *  @brief    This function use to clear PS2 Tx FIFO.
 *
 *  @param    None
 *
 *  @return   None
 *  \hideinitializer 
 */
__STATIC_INLINE void PS2_CLEAR_TX_FIFO(void) 
{
    PS2->CTL |= PS2_CTL_CLRFIFO_Msk; 
    PS2->CTL &= ~PS2_CTL_CLRFIFO_Msk;
}

/**
 *  @brief    This function use to clear PS2 Rx interrupt.
 *
 *  @param    None
 *
 *  @return   None
 *  \hideinitializer 
 */
#define PS2_CLR_RX_INT_FLAG() (PS2->INTSTS = PS2_INTSTS_RXIF_Msk)

/**
 *  @brief    This function use to clear PS2 Tx interrupt.
 *
 *  @param    None
 *
 *  @return   None
 *  \hideinitializer 
 */
#define PS2_CLR_TX_INT_FLAG() (PS2->INTSTS = PS2_INTSTS_TXIF_Msk)

/**
 *  @brief    This function use to get PS2 interrupt.
 *
 *  @param[in]    u32IntFlag interrupt flag: \ref PS2_INTSTS_TXIF_Msk , \ref PS2_INTSTS_RXIF_Msk
 *
 *  @return   1: interrupt occurs
 *            0: interrupt not occurs
 *  \hideinitializer 
 */
#define PS2_GET_INT_FLAG(u32IntFlag) ((PS2->INTSTS & u32IntFlag)?1:0)

/**
 *  @brief    This function use to set PS2CLK and PS2DATA pins are controlled by hardware.
 *
 *  @param    None
 *
 *  @return   None
 *  \hideinitializer 
 */
#define PS2_DISABLE_OVERRIDE() (PS2->CTL &= ~PS2_CTL_PS2EN_Msk)

/**
 *  @brief    This function use to set PS2CLK and PS2DATA pins are controlled by software.
 *
 *  @param    None
 *
 *  @return   None
 *  \hideinitializer 
 */
#define PS2_ENABLE_OVERRIDE() (PS2->CTL |= PS2_CTL_PS2EN_Msk)

/**
 *  @brief    This function use to get indicates which data byte in transmit data shift register.
 *
 *  @param    None
 *
 *  @return   The indicates which data byte in transmit data shift register.
 *  \hideinitializer 
 */
#define PS2_GET_TX_BYTE_INDEX() ((PS2->STATUS & PS2_STATUS_BYTEIDX_Msk) >> PS2_STATUS_BYTEIDX_Pos)

/**
 *  @brief    This function use to set PS2DATA Pin low.
 *
 *  @param    None
 *
 *  @return   None.
 *  \hideinitializer 
 */
#define PS2_SET_DATA_LOW() (PS2->CTL &= ~PS2_CTL_FPS2DAT_Msk)

/**
 *  @brief    This function use to set PS2DATA Pin high.
 *
 *  @param    None
 *
 *  @return   None.
 *  \hideinitializer 
 */
#define PS2_SET_DATA_HIGH() (PS2->CTL |= PS2_CTL_FPS2DAT_Msk)

/**
 *  @brief    This function use to set PS2CLK Pin low.
 *
 *  @param    None
 *
 *  @return   None.
 *  \hideinitializer 
 */
#define PS2_SET_CLK_LOW() (PS2->CTL &= ~PS2_CTL_FPS2CLK_Msk)

/**
 *  @brief    This function use to set PS2CLK Pin high.
 *
 *  @param    None
 *
 *  @return   None.
 *  \hideinitializer 
 */
#define PS2_SET_CLK_HIGH() (PS2->CTL |= PS2_CTL_FPS2CLK_Msk)

/**
 *  @brief    If Parity error or Stop bit is Not Received Correctly, Acknowledge will Not be Sent to host at 12th clock.
 *
 *  @param    None
 *
 *  @return   None.
 *  \hideinitializer 
 */
#define PS2_DISABLE_ACK_ALWAYS() (PS2->CTL |= PS2_CTL_ACK_Msk)

/**
 *  @brief    Always sends acknowledge to host at 12th clock for host to device communication.
 *
 *  @param    None
 *
 *  @return   None.
 *  \hideinitializer 
 */
#define PS2_ENABLE_ACK_ALWAYS() (PS2->CTL &= ~PS2_CTL_ACK_Msk)


/*---------------------------------------------------------------------------------------------------------*/
/* Define Function Prototypes                                                                              */
/*---------------------------------------------------------------------------------------------------------*/

void PS2_Open(void);
void PS2_Close(void);
uint8_t PS2_Read(void);
int32_t PS2_Write(uint32_t *pu32Buf, uint32_t u32ByteCount);
void PS2_EnableInt(uint32_t u32Mask);
void PS2_DisableInt(uint32_t u32Mask);


/*@}*/ /* end of group NUC472_442_PS2_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_PS2_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__PS2_H__

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/

