/**************************************************************************//**
 * @file     nu_sc.h
 * @version  V3.00
 * @brief    Smartcard(SC) driver header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_SC_H__
#define __NU_SC_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SC_Driver SC Driver
  @{
*/

/** @addtogroup SC_EXPORTED_CONSTANTS SC Exported Constants
  @{
*/
#define SC_INTERFACE_NUM                (3UL)               /*!< Smartcard interface numbers \hideinitializer */
#define SC_PIN_STATE_HIGH               (1UL)               /*!< Smartcard pin status high   \hideinitializer */
#define SC_PIN_STATE_LOW                (0UL)               /*!< Smartcard pin status low    \hideinitializer */
#define SC_PIN_STATE_IGNORE             (0xFFFFFFFFUL)      /*!< Ignore pin status           \hideinitializer */
#define SC_CLK_ON                       (1UL)               /*!< Smartcard clock on          \hideinitializer */
#define SC_CLK_OFF                      (0UL)               /*!< Smartcard clock off         \hideinitializer */

#define SC_TMR_MODE_0                   (0UL << SC_TMRCTL0_OPMODE_Pos)      /*!<Timer Operation Mode 0, down count                                                      \hideinitializer */
#define SC_TMR_MODE_1                   (1UL << SC_TMRCTL0_OPMODE_Pos)      /*!<Timer Operation Mode 1, down count, start after detect start bit                        \hideinitializer */
#define SC_TMR_MODE_2                   (2UL << SC_TMRCTL0_OPMODE_Pos)      /*!<Timer Operation Mode 2, down count, start after receive start bit                       \hideinitializer */
#define SC_TMR_MODE_3                   (3UL << SC_TMRCTL0_OPMODE_Pos)      /*!<Timer Operation Mode 3, down count, use for activation, only timer 0 support this mode  \hideinitializer */
#define SC_TMR_MODE_4                   (4UL << SC_TMRCTL0_OPMODE_Pos)      /*!<Timer Operation Mode 4, down count with reload after timeout                            \hideinitializer */
#define SC_TMR_MODE_5                   (5UL << SC_TMRCTL0_OPMODE_Pos)      /*!<Timer Operation Mode 5, down count, start after detect start bit, reload after timeout  \hideinitializer */
#define SC_TMR_MODE_6                   (6UL << SC_TMRCTL0_OPMODE_Pos)      /*!<Timer Operation Mode 6, down count, start after receive start bit, reload after timeout \hideinitializer */
#define SC_TMR_MODE_7                   (7UL << SC_TMRCTL0_OPMODE_Pos)      /*!<Timer Operation Mode 7, down count, start and reload after detect start bit             \hideinitializer */
#define SC_TMR_MODE_8                   (8UL << SC_TMRCTL0_OPMODE_Pos)      /*!<Timer Operation Mode 8, up count                                                        \hideinitializer */
#define SC_TMR_MODE_F                   (0xFUL << SC_TMRCTL0_OPMODE_Pos)    /*!<Timer Operation Mode 15, down count, reload after detect start bit                      \hideinitializer */

/**@}*/ /* end of group SC_EXPORTED_CONSTANTS */


/** @addtogroup SC_EXPORTED_FUNCTIONS SC Exported Functions
  @{
*/

/**
  * @brief      This macro enable smartcard interrupt
  *
  * @param[in]  sc      The pointer of smartcard module.
  * @param[in]  u32Mask Interrupt mask to be enabled. A combination of
  *                         - \ref SC_INTEN_ACERRIEN_Msk
  *                         - \ref SC_INTEN_RXTOIEN_Msk
  *                         - \ref SC_INTEN_INITIEN_Msk
  *                         - \ref SC_INTEN_CDIEN_Msk
  *                         - \ref SC_INTEN_BGTIEN_Msk
  *                         - \ref SC_INTEN_TMR2IEN_Msk
  *                         - \ref SC_INTEN_TMR1IEN_Msk
  *                         - \ref SC_INTEN_TMR0IEN_Msk
  *                         - \ref SC_INTEN_TERRIEN_Msk
  *                         - \ref SC_INTEN_TBEIEN_Msk
  *                         - \ref SC_INTEN_RDAIEN_Msk
  *
  * @return     None
  *
  * @details    The macro is used to enable Auto-convention error interrupt, Receiver buffer time-out interrupt, Initial end interrupt,
  *             Card detect interrupt, Block guard time interrupt, Timer2 interrupt, Timer1 interrupt, Timer0 interrupt,
  *             Transfer error interrupt, Transmit buffer empty interrupt or Receive data reach trigger level interrupt.
  * \hideinitializer
  */
#define SC_ENABLE_INT(sc, u32Mask)      ((sc)->INTEN |= (u32Mask))

/**
  * @brief      This macro disable smartcard interrupt
  *
  * @param[in]  sc      The pointer of smartcard module.
  * @param[in]  u32Mask Interrupt mask to be disabled. A combination of
  *                         - \ref SC_INTEN_ACERRIEN_Msk
  *                         - \ref SC_INTEN_RXTOIEN_Msk
  *                         - \ref SC_INTEN_INITIEN_Msk
  *                         - \ref SC_INTEN_CDIEN_Msk
  *                         - \ref SC_INTEN_BGTIEN_Msk
  *                         - \ref SC_INTEN_TMR2IEN_Msk
  *                         - \ref SC_INTEN_TMR1IEN_Msk
  *                         - \ref SC_INTEN_TMR0IEN_Msk
  *                         - \ref SC_INTEN_TERRIEN_Msk
  *                         - \ref SC_INTEN_TBEIEN_Msk
  *                         - \ref SC_INTEN_RDAIEN_Msk
  *
  * @return     None
  *
  * @details    The macro is used to disable Auto-convention error interrupt, Receiver buffer time-out interrupt, Initial end interrupt,
  *             Card detect interrupt, Block guard time interrupt, Timer2 interrupt, Timer1 interrupt, Timer0 interrupt,
  *             Transfer error interrupt, Transmit buffer empty interrupt or Receive data reach trigger level interrupt.
  * \hideinitializer
  */
#define SC_DISABLE_INT(sc, u32Mask)     ((sc)->INTEN &= ~(u32Mask))

/**
  * @brief      This macro set VCC pin state of smartcard interface
  *
  * @param[in]  sc          The pointer of smartcard module.
  * @param[in]  u32State    Pin state of VCC pin, valid parameters are \ref SC_PIN_STATE_HIGH and \ref SC_PIN_STATE_LOW.
  *
  * @return     None
  *
  * @details    User can set PWREN (SC_PINCTL[0]) and PWRINV (SC_PINCTL[11]) to decide SC_PWR pin is in high or low level.
  * \hideinitializer
  */
#define SC_SET_VCC_PIN(sc, u32State) \
    do {\
            while(((sc)->PINCTL & SC_PINCTL_SYNC_Msk) == SC_PINCTL_SYNC_Msk);\
            if(u32State)\
                (sc)->PINCTL |= SC_PINCTL_PWREN_Msk;\
            else\
                (sc)->PINCTL &= ~SC_PINCTL_PWREN_Msk;\
    }while(0)


/**
  * @brief      This macro turns CLK output on or off
  *
  * @param[in]  sc          The pointer of smartcard module.
  * @param[in] u32OnOff     Clock on or off for selected smartcard module, valid values are \ref SC_CLK_ON and \ref SC_CLK_OFF.
  *
  * @return     None
  *
  * @details    User can set CLKKEEP (SC_PINCTL[6]) to decide SC_CLK pin always keeps free running or not.
  * \hideinitializer
  */
#define SC_SET_CLK_PIN(sc, u32OnOff)\
    do {\
            while(((sc)->PINCTL & SC_PINCTL_SYNC_Msk) == SC_PINCTL_SYNC_Msk);\
            if(u32OnOff)\
                (sc)->PINCTL |= SC_PINCTL_CLKKEEP_Msk;\
            else\
                (sc)->PINCTL &= ~(SC_PINCTL_CLKKEEP_Msk);\
    }while(0)

/**
  * @brief      This macro set I/O pin state of smartcard interface
  *
  * @param[in]  sc          The pointer of smartcard module.
  * @param[in] u32State     Pin state of I/O pin, valid parameters are \ref SC_PIN_STATE_HIGH and \ref SC_PIN_STATE_LOW.
  *
  * @return     None
  *
  * @details    User can set SCDATA (SC_PINCTL[9]) to decide SC_DATA pin to high or low.
  * \hideinitializer
  */
#define SC_SET_IO_PIN(sc, u32State)\
    do {\
            while(((sc)->PINCTL & SC_PINCTL_SYNC_Msk) == SC_PINCTL_SYNC_Msk);\
            if(u32State)\
                (sc)->PINCTL |= SC_PINCTL_SCDATA_Msk;\
            else\
                (sc)->PINCTL &= ~SC_PINCTL_SCDATA_Msk;\
    }while(0)

/**
  * @brief      This macro set RST pin state of smartcard interface
  *
  * @param[in]  sc          The pointer of smartcard module.
  * @param[in] u32State     Pin state of RST pin, valid parameters are \ref SC_PIN_STATE_HIGH and \ref SC_PIN_STATE_LOW.
  *
  * @return     None
  *
  * @details    User can set SCRST (SC_PINCTL[1]) to decide SC_RST pin to high or low.
  * \hideinitializer
  */
#define SC_SET_RST_PIN(sc, u32State)\
    do {\
            while(((sc)->PINCTL & SC_PINCTL_SYNC_Msk) == SC_PINCTL_SYNC_Msk);\
            if(u32State)\
                (sc)->PINCTL |= SC_PINCTL_RSTEN_Msk;\
            else\
                (sc)->PINCTL &= ~SC_PINCTL_RSTEN_Msk;\
    }while(0)

/**
  * @brief      This macro read one byte from smartcard module receive FIFO
  *
  * @param[in]  sc      The pointer of smartcard module.
  *
  * @return     One byte read from receive FIFO
  *
  * @details    By reading DAT register, the SC will return an 8-bit received data.
  * \hideinitializer
  */
#define SC_READ(sc)             ((char)((sc)->DAT))

/**
  * @brief      This macro write one byte to smartcard module transmit FIFO
  *
  * @param[in]  sc      The pointer of smartcard module.
  * @param[in]  u8Data  Data to write to transmit FIFO.
  *
  * @return     None
  *
  * @details    By writing data to DAT register, the SC will send out an 8-bit data.
  * \hideinitializer
  */
#define SC_WRITE(sc, u8Data)    ((sc)->DAT = (u8Data))

/**
  * @brief      This macro set smartcard stop bit length
  *
  * @param[in]  sc      The pointer of smartcard module.
  * @param[in]  u32Len  Stop bit length, ether 1 or 2.
  *
  * @return     None
  *
  * @details    Stop bit length must be 1 for T = 1 protocol and 2 for T = 0 protocol.
  * \hideinitializer
  */
#define SC_SET_STOP_BIT_LEN(sc, u32Len) ((sc)->CTL = ((sc)->CTL & ~SC_CTL_NSB_Msk) | (((u32Len) == 1)? SC_CTL_NSB_Msk : 0))


/*---------------------------------------------------------------------------------------------------------*/
/* static inline functions                                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
/* Declare these inline functions here to avoid MISRA C 2004 rule 8.1 error */
__STATIC_INLINE void SC_SetTxRetry(SC_T *sc, uint32_t u32Count);
__STATIC_INLINE void SC_SetRxRetry(SC_T *sc, uint32_t u32Count);


/**
  * @brief      Enable/Disable Tx error retry, and set Tx error retry count
  *
  * @param[in]  sc          The pointer of smartcard module.
  * @param[in]  u32Count    The number of times of Tx error retry count, between 0~8. 0 means disable Tx error retry.
  *
  * @return     None
  *
  * @details    This function is used to enable/disable transmitter retry function when parity error has occurred, and set error retry count.
  */
__STATIC_INLINE void SC_SetTxRetry(SC_T *sc, uint32_t u32Count)
{
    while(((sc)->CTL & SC_CTL_SYNC_Msk) == SC_CTL_SYNC_Msk) {}

    /* Retry count must set while enable bit disabled, so disable it first */
    (sc)->CTL &= ~(SC_CTL_TXRTY_Msk | SC_CTL_TXRTYEN_Msk);

    if((u32Count) != 0UL)
    {
        while(((sc)->CTL & SC_CTL_SYNC_Msk) == SC_CTL_SYNC_Msk) {}
        (sc)->CTL |= (((u32Count) - 1UL) << SC_CTL_TXRTY_Pos) | SC_CTL_TXRTYEN_Msk;
    }
}

/**
  * @brief      Enable/Disable Rx error retry, and set Rx error retry count
  *
  * @param[in]  sc          The pointer of smartcard module.
  * @param[in]  u32Count    The number of times of Rx error retry count, between 0~8. 0 means disable Rx error retry.
  *
  * @return     None
  *
  * @details    This function is used to enable/disable receiver retry function when parity error has occurred, and set error retry count.
  */
__STATIC_INLINE void SC_SetRxRetry(SC_T *sc, uint32_t u32Count)
{
    while(((sc)->CTL & SC_CTL_SYNC_Msk) == SC_CTL_SYNC_Msk) {}

    /* Retry count must set while enable bit disabled, so disable it first */
    (sc)->CTL &= ~(SC_CTL_RXRTY_Msk | SC_CTL_RXRTYEN_Msk);

    if((u32Count) != 0UL)
    {
        while(((sc)->CTL & SC_CTL_SYNC_Msk) == SC_CTL_SYNC_Msk) {}
        (sc)->CTL |= (((u32Count) - 1UL) << SC_CTL_RXRTY_Pos) | SC_CTL_RXRTYEN_Msk;
    }
}


uint32_t SC_IsCardInserted(SC_T *sc);
void SC_ClearFIFO(SC_T *sc);
void SC_Close(SC_T *sc);
void SC_Open(SC_T *sc, uint32_t u32CardDet, uint32_t u32PWR);
void SC_ResetReader(SC_T *sc);
void SC_SetBlockGuardTime(SC_T *sc, uint32_t u32BGT);
void SC_SetCharGuardTime(SC_T *sc, uint32_t u32CGT);
void SC_StopAllTimer(SC_T *sc);
void SC_StartTimer(SC_T *sc, uint32_t u32TimerNum, uint32_t u32Mode, uint32_t u32ETUCount);
void SC_StopTimer(SC_T *sc, uint32_t u32TimerNum);
uint32_t SC_GetInterfaceClock(SC_T *sc);

/**@}*/ /* end of group SC_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group SC_Driver */

/**@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_SC_H__ */
