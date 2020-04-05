/**************************************************************************//**
 * @file     PS2.h
 * @version  V3.00
 * $Revision: 5 $
 * $Date: 15/05/20 3:47p $
 * @brief     PS/2 Driver Header File
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __PS2_H__
#define __PS2_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup PS2_Driver PS2 Driver
  @{
*/


/** @addtogroup PS2_EXPORTED_FUNCTIONS PS2 Exported Functions
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/*  Define Macros and functions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/

/**
 *  @brief     To Set PS/2 Tx FIFO length
 *
 *  @param[in] u32Count    Tx FIFO length
 *
 *  @return    None
 *
 *  @details   Before PS/2 data transmit, program needs to set the FIFO depth.
 * \hideinitializer
 */
#define PS2_SET_TX_BYTE_CNT(u32Count) (PS2->PS2CON = (PS2->PS2CON & ~PS2_PS2CON_TXFIFO_DEPTH_Msk) \
                                      | (((u32Count)-1) << PS2_PS2CON_TXFIFO_DEPTH_Pos))

/**
 *  @brief     This function use to Get PS/2 Status
 *
 *  @param     None
 *
 *  @return    PS/2 bus status
 *
 *  @details   To get PS/2 bus status which are about Byte index, Tx/Rx status, Error status and PS/2 line status.
 */
#define PS2_GET_STATUS() (PS2->PS2STATUS)

/**
 *  @brief     This function is used to Clear PS/2 Status
 *
 *  @param[in] u32Mask    Clear the specified status of PS/2 module:
 *                        1. PS2D_PS2STATUS_FRAMERR_Msk 2. PS2D_PS2STATUS_RXOVF_Msk
 *
 *  @return    None
 *
 *  @details   To clear PS/2 bus status which are about Byte index, TX/RX status, Error status, PS/2 line status.
 */
#define PS2_CLR_STATUS(u32Mask) (PS2->PS2STATUS = (u32Mask))

/**
 *  @brief     This function is used to Clear PS/2 Tx FIFO
 *
 *  @param     None
 *
 *  @return    None
 *
 *  @details   Write 1 to terminate PS/2 device to host transmission.
 *
 *  @note      Write 1 is always clear Tx FIFO, and need write 0 to STOP the clear action.
 */
__STATIC_INLINE void PS2_CLEAR_TX_FIFO(void)
{
    PS2->PS2CON |= PS2_PS2CON_CLRFIFO_Msk;
    PS2->PS2CON &= ~PS2_PS2CON_CLRFIFO_Msk;
}

/**
 *  @brief    This function is used to Clear PS2 Rx interrupt
 *
 *  @param    None
 *
 *  @return   None
 *
 *  @details  To disable PS/2 receive interrupt occurs.
 */
#define PS2_CLR_RX_INT_FLAG() (PS2->PS2INTID = PS2_PS2INTID_RXINT_Msk)

/**
 *  @brief    This function is used to Clear PS/2 Tx Interrupt
 *
 *  @param    None
 *
 *  @return   None
 *
 *  @details  To disable PS/2 transmit interrupt occurs.
 */
#define PS2_CLR_TX_INT_FLAG() (PS2->PS2INTID = PS2_PS2INTID_TXINT_Msk)

/**
 *  @brief     This function is used to Get PS/2 Interrupt
 *
 *  @param[in] u32IntFlag  Interrupt flag of PS2_PS2INTID_TXINT_Msk, PS2_PS2INTID_RXINT_Msk
 *
 *  @retval    1 Interrupt occurs
 *  @retval    0 Interrupt not occurs
 *
 *  @details   To check PS/2 bus interrupt occur from TX or RX
 */
#define PS2_GET_INT_FLAG(u32IntFlag) ((PS2->PS2INTID & (u32IntFlag))?1:0)

/**
 *  @brief    Disable PS2CLK and PS2DATA pins override.
 *
 *  @param    None
 *
 *  @return   None
 *
 *  @details  To disable the override control of PS2CLK and PS2DATA pins.
 */
#define PS2_DISABLE_OVERRIDE() (PS2->PS2CON &= ~PS2_PS2CON_OVERRIDE_Msk)

/**
 *  @brief    Enable PS2CLK and PS2DATA pins Override.
 *
 *  @param    None
 *
 *  @return   None
 *
 *  @details  TO enable the override control of PS2CLK and PS2DATA pins.
 */
#define PS2_ENABLE_OVERRIDE() (PS2->PS2CON |= PS2_PS2CON_OVERRIDE_Msk)

/**
 *  @brief    This function is used to Get Indicates which data byte in transmit data shift register
 *
 *  @param    None
 *
 *  @return   The indicates which data byte in transmit data shift register.
 *
 *  @details  To get a indication which a data byte in the data shift register.
 */
#define PS2_GET_TX_BYTE_INDEX() ((PS2->PS2STATUS & PS2_PS2STATUS_BYTEIDX_Msk) >> PS2_PS2STATUS_BYTEIDX_Pos)

/**
 *  @brief    This function is used to set PS2DATA Pin low.
 *
 *  @param    None
 *
 *  @return   None
 *
 *  @details  To control the PS2DATA pin state to low.
 */
#define PS2_SET_DATA_LOW() (PS2->PS2CON &= ~PS2_PS2CON_FPS2DAT_Msk)

/**
 *  @brief    This function is used to set PS2DATA Pin high
 *
 *  @param    None
 *
 *  @return   None
 *
 *  @details  To control the PS2DATA pin state to high.
 */
#define PS2_SET_DATA_HIGH() (PS2->PS2CON |= PS2_PS2CON_FPS2DAT_Msk)

/**
 *  @brief    This function is used to set PS2CLK Pin low.
 *
 *  @param    None
 *
 *  @return   None
 *
 *  @details  To control the PS2CLK pin state to low.
 */
#define PS2_SET_CLK_LOW() (PS2->PS2CON &= ~PS2_PS2CON_FPS2CLK_Msk)

/**
 *  @brief    This function is used to set PS2CLK Pin high.
 *
 *  @param    None
 *
 *  @return   None
 *
 *  @details  To control the PS2CLK pin state to high.
 */
#define PS2_SET_CLK_HIGH() (PS2->PS2CON |= PS2_PS2CON_FPS2CLK_Msk)

/**
 *  @brief    Disable always sends acknowledge
 *
 *  @param    None
 *
 *  @return   None
 *
 *  @details  If parity error or Stop bit is not received correctly, acknowledge will not be sent to host at 12th clock.
 */
#define PS2_DISABLE_ACK_ALWAYS() (PS2->PS2CON |= PS2_PS2CON_ACK_Msk)

/**
 *  @brief    Always sends acknowledge
 *
 *  @param    None
 *
 *  @return   None
 *
 *  @details  Always send acknowledge to host at 12th clock for host to device communication.
 */
#define PS2_ENABLE_ACK_ALWAYS() (PS2->PS2CON &= ~PS2_PS2CON_ACK_Msk)


/*---------------------------------------------------------------------------------------------------------*/
/* Define Function Prototypes                                                                              */
/*---------------------------------------------------------------------------------------------------------*/

void PS2_Open(void);
void PS2_Close(void);
uint8_t PS2_Read(void);
int32_t PS2_Write(uint32_t *pu32Buf, uint32_t u32ByteCount);
void PS2_EnableInt(uint32_t u32Mask);
void PS2_DisableInt(uint32_t u32Mask);


/*@}*/ /* end of group PS2_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group PS2_Driver */

/*@}*/ /* end of group Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__PS2_H__

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/

