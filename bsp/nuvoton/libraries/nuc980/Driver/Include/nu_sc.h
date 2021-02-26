/**************************************************************************//**
 * @file     sc.h
 * @brief    NUC980 Smartcard (SC) driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_SC_H__
#define __NU_SC_H__
#include "nuc980.h"
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
#define SC_INTERFACE_NUM        2                /*!< Smartcard interface numbers */ /* NUC980 series has two SC interface */
#define SC_PIN_STATE_HIGH       1                /*!< Smartcard pin status high   */
#define SC_PIN_STATE_LOW        0                /*!< Smartcard pin status low    */
#define SC_PIN_STATE_IGNORE     0xFFFFFFFF       /*!< Ignore pin status           */
#define SC_CLK_ON               1                /*!< Smartcard clock on          */
#define SC_CLK_OFF              0                /*!< Smartcard clock off         */

#define SC_TMR_MODE_0                   (0ul << 24)     /*!<Timer Operation Mode 0, down count                                                      */
#define SC_TMR_MODE_1                   (1ul << 24)     /*!<Timer Operation Mode 1, down count, start after detect start bit                        */
#define SC_TMR_MODE_2                   (2ul << 24)     /*!<Timer Operation Mode 2, down count, start after receive start bit                       */
#define SC_TMR_MODE_3                   (3ul << 24)     /*!<Timer Operation Mode 3, down count, use for activation, only timer 0 support this mode  */
#define SC_TMR_MODE_4                   (4ul << 24)     /*!<Timer Operation Mode 4, down count with reload after timeout                            */
#define SC_TMR_MODE_5                   (5ul << 24)     /*!<Timer Operation Mode 5, down count, start after detect start bit, reload after timeout  */
#define SC_TMR_MODE_6                   (6ul << 24)     /*!<Timer Operation Mode 6, down count, start after receive start bit, reload after timeout */
#define SC_TMR_MODE_7                   (7ul << 24)     /*!<Timer Operation Mode 7, down count, start and reload after detect start bit             */
#define SC_TMR_MODE_8                   (8ul << 24)     /*!<Timer Operation Mode 8, up count                                                        */
#define SC_TMR_MODE_F                   (0xF << 24)     /*!<Timer Operation Mode 15, down count, reload after detect start bit                      */

#define SC_INTEN_ACERRIEN_Msk   0x00000400
#define SC_INTEN_RXTOIF_Msk     0x00000200
#define SC_INTEN_INITIEN_Msk    0x00000100
#define SC_INTEN_CDIEN_Msk      0x00000080
#define SC_INTEN_BGTIEN_Msk     0x00000040
#define SC_INTEN_TMR2IEN_Msk    0x00000020
#define SC_INTEN_TMR1IEN_Msk    0x00000010
#define SC_INTEN_TMR0IEN_Msk    0x00000008
#define SC_INTEN_TERRIEN_Msk    0x00000004
#define SC_INTEN_TBEIEN_Msk     0x00000002
#define SC_INTEN_RDAIEN_Msk     0x00000001

#define SC_INTSTS_ACERRIF_Msk   0x00000400
#define SC_INTSTS_RBTOIF_Msk    0x00000200
#define SC_INTSTS_CDIF_Msk      0x00000080
#define SC_INTSTS_TMR2IF_Msk    0x00000020
#define SC_INTSTS_TMR1IF_Msk    0x00000010
#define SC_INTSTS_TMR0IF_Msk    0x00000008
#define SC_INTSTS_TERRIF_Msk    0x00000004
#define SC_INTSTS_TBEIF_Msk     0x00000002
#define SC_INTSTS_RDAIF_Msk     0x00000001

#define SC_CTL_SYNC_Msk         0x40000000
#define SC_CTL_CDLV_Msk         0x04000000
#define SC_CTL_CDDBSEL_Msk      0x03000000
#define SC_CTL_TXRTYEN_Msk      0x00800000
#define SC_CTL_TXRTY_Msk        0x00700000
#define SC_CTL_RXRTYEN_Msk      0x00080000
#define SC_CTL_RXRTY_Msk        0x00070000
#define SC_CTL_NSB_Msk          0x00008000
#define SC_CTL_TMRSEL_Msk       0x00006000
#define SC_CTL_RXTRGLV_Msk      0x000000C0
#define SC_CTL_AUTOCEN_Msk      0x00000008
#define SC_CTL_RXOFF_Msk        0x00000002
#define SC_CTL_SCEN_Msk         0x00000001

#define SC_PINCTL_SYNC_Msk      0x40000000
#define SC_PINCTL_PWRINV_Msk    0x00000800
#define SC_PINCTL_SCDOUT_Msk    0x00000200
#define SC_PINCTL_CLKKEEP_Msk   0x00000040
#define SC_PINCTL_SCRST_Msk     0x00000002
#define SC_PINCTL_PWREN_Msk     0x00000001

#define SC_ALTCTL_ADACEN_Msk    0x00000800
#define SC_ALTCTL_CNTEN2_Msk    0x00000080
#define SC_ALTCTL_CNTEN1_Msk    0x00000040
#define SC_ALTCTL_CNTEN0_Msk    0x00000020
#define SC_ALTCTL_RXRST_Msk     0x00000002
#define SC_ALTCTL_TXRST_Msk     0x00000001

#define SC_ETUCTL_CMPEN_Msk     0x00008000
#define SC_ETUCTL_ETURDIV_Msk   0x00000FFF

#define SC_EGT_EGT_Msk          0x000000FF

#define SC_STATUS_TXACT_Msk     0x80000000
#define SC_STATUS_TXOVERR_Msk   0x40000000
#define SC_STATUS_TXRERR_Msk    0x20000000
#define SC_STATUS_RXACT_Msk     0x00800000
#define SC_STATUS_RXOVERR_Msk   0x00400000
#define SC_STATUS_RXRERR_Msk    0x00200000
#define SC_STATUS_CDPINSTS_Msk  0x00002000
#define SC_STATUS_CINSERT_Msk   0x00001000
#define SC_STATUS_CREMOVE_Msk   0x00000800
#define SC_STATUS_TXEMPTY_Msk   0x00000200
#define SC_STATUS_TXOV_Msk      0x00000100
#define SC_STATUS_BEF_Msk       0x00000040
#define SC_STATUS_FEF_Msk       0x00000020
#define SC_STATUS_PEF_Msk       0x00000010
#define SC_STATUS_RXEMPTY_Msk   0x00000002
#define SC_STATUS_RXOV_Msk      0x00000001

/*@}*/ /* end of group NUC980_SC_EXPORTED_CONSTANTS */


/** @addtogroup NUC980_SC_EXPORTED_FUNCTIONS SC Exported Functions
  @{
*/

/**
  * @brief Enable smartcard interrupt.
  * @param[in] sc Smartcard module number
  * @param[in] u32Mask Interrupt mask to be enabled. A combination of
  *             - \ref SC_INTEN_ACERRIEN_Msk
  *             - \ref SC_INTEN_RXTOIF_Msk
  *             - \ref SC_INTEN_INITIEN_Msk
  *             - \ref SC_INTEN_CDIEN_Msk
  *             - \ref SC_INTEN_BGTIEN_Msk
  *             - \ref SC_INTEN_TMR2IEN_Msk
  *             - \ref SC_INTEN_TMR1IEN_Msk
  *             - \ref SC_INTEN_TMR0IEN_Msk
  *             - \ref SC_INTEN_TERRIEN_Msk
  *             - \ref SC_INTEN_TBEIEN_Msk
  *             - \ref SC_INTEN_RDAIEN_Msk
  * @return None
  * @details The macro is used to enable Auto-convention error interrupt, Receiver buffer time-out interrupt, Initial end interrupt,
  *          Card detect interrupt, Block guard time interrupt, Timer2 interrupt, Timer1 interrupt, Timer0 interrupt,
  *          Transfer error interrupt, Transmit buffer empty interrupt or Receive data reach trigger level interrupt.
  * \hideinitializer
  */
#define SC_ENABLE_INT(sc, u32Mask) \
    do {\
        if(sc == 0)\
            outpw(REG_SC0_INTEN, inpw(REG_SC0_INTEN) | (u32Mask));\
        else\
            outpw(REG_SC1_INTEN, inpw(REG_SC1_INTEN) | (u32Mask));\
    }while(0)


/**
  * @brief Disable smartcard interrupt.
  * @param[in] sc Smartcard module number
  * @param[in] u32Mask Interrupt mask to be disabled. A combination of
  *             - \ref SC_INTEN_ACERRIEN_Msk
  *             - \ref SC_INTEN_RXTOIF_Msk
  *             - \ref SC_INTEN_INITIEN_Msk
  *             - \ref SC_INTEN_CDIEN_Msk
  *             - \ref SC_INTEN_BGTIEN_Msk
  *             - \ref SC_INTEN_TMR2IEN_Msk
  *             - \ref SC_INTEN_TMR1IEN_Msk
  *             - \ref SC_INTEN_TMR0IEN_Msk
  *             - \ref SC_INTEN_TERRIEN_Msk
  *             - \ref SC_INTEN_TBEIEN_Msk
  *             - \ref SC_INTEN_RDAIEN_Msk
  * @return None
  * @details The macro is used to disable Auto-convention error interrupt, Receiver buffer time-out interrupt, Initial end interrupt,
  *          Card detect interrupt, Block guard time interrupt, Timer2 interrupt, Timer1 interrupt, Timer0 interrupt,
  *          Transfer error interrupt, Transmit buffer empty interrupt or Receive data reach trigger level interrupt.
  * \hideinitializer
  */
#define SC_DISABLE_INT(sc, u32Mask) \
    do {\
        if(sc == 0)\
            outpw(REG_SC0_INTEN, inpw(REG_SC0_INTEN) & ~(u32Mask));\
        else\
            outpw(REG_SC1_INTEN, inpw(REG_SC1_INTEN) & ~(u32Mask));\
    }while(0)

/**
  * @brief This macro set VCC pin state of smartcard interface.
  * @param[in] sc Smartcard module number
  * @param[in] u32State Pin state of VCC pin, valid parameters are:
  *                 \ref SC_PIN_STATE_HIGH    :Smartcard pin status high.
  *                 \ref SC_PIN_STATE_LOW     :Smartcard pin status low.
  * @return None
  * @details User can set PWREN (SC_PINCTL[0]) and PWRINV (SC_PINCTL[11])to decide SC_PWR pin is in high or low level.
  * \hideinitializer
  */
#define SC_SET_VCC_PIN(sc, u32State) \
    do {\
        if(sc == 0) {\
            while(inpw(REG_SC0_PINCTL) & SC_PINCTL_SYNC_Msk);\
            if(u32State)\
                outpw(REG_SC0_PINCTL, inpw(REG_SC0_PINCTL) | SC_PINCTL_PWREN_Msk);\
            else\
                outpw(REG_SC0_PINCTL, inpw(REG_SC0_PINCTL) & ~SC_PINCTL_PWREN_Msk);\
        } else {\
            while(inpw(REG_SC1_PINCTL) & SC_PINCTL_SYNC_Msk);\
            if(u32State)\
                outpw(REG_SC1_PINCTL, inpw(REG_SC1_PINCTL) | SC_PINCTL_PWREN_Msk);\
            else\
                outpw(REG_SC1_PINCTL, inpw(REG_SC1_PINCTL) & ~SC_PINCTL_PWREN_Msk);\
        }\
    }while(0)


/**
  * @brief Set CLK output status.
  * @param[in] sc Smartcard module number
  * @param[in] u32OnOff Clock on or off for selected smartcard module, valid values are:
  *                 \ref SC_CLK_ON    :Smartcard clock on.
  *                 \ref SC_CLK_OFF   :Smartcard clock off.
  * @return None
  * @details User can set CLKKEEP (SC_PINCTL[6]) to decide SC_CLK pin always keeps free running or not.
  * \hideinitializer
  */
#define SC_SET_CLK_PIN(sc, u32OnOff)\
    do {\
        if(sc == 0) {\
            while(inpw(REG_SC0_PINCTL) & SC_PINCTL_SYNC_Msk);\
            if(u32OnOff)\
                outpw(REG_SC0_PINCTL, inpw(REG_SC0_PINCTL) | SC_PINCTL_CLKKEEP_Msk);\
            else\
                outpw(REG_SC0_PINCTL, inpw(REG_SC0_PINCTL) & ~SC_PINCTL_CLKKEEP_Msk);\
        } else {\
            while(inpw(REG_SC1_PINCTL) & SC_PINCTL_SYNC_Msk);\
            if(u32OnOff)\
                outpw(REG_SC1_PINCTL, inpw(REG_SC1_PINCTL) | SC_PINCTL_CLKKEEP_Msk);\
            else\
                outpw(REG_SC1_PINCTL, inpw(REG_SC1_PINCTL) & ~SC_PINCTL_CLKKEEP_Msk);\
        }\
    }while(0)


/**
  * @brief Set I/O pin state.
  * @param[in] sc Smartcard module number
  * @param[in] u32State Pin state of I/O pin, valid parameters are:
  *                 \ref SC_PIN_STATE_HIGH    :Smartcard pin status high.
  *                 \ref SC_PIN_STATE_LOW     :Smartcard pin status low.
  * @return None
  * @details User can set SCDOUT(SC_PINCTL[9]) to decide SCDOUT pin to high or low.
  * \hideinitializer
  */
#define SC_SET_IO_PIN(sc, u32State)\
    do {\
        if(sc == 0) {\
            while(inpw(REG_SC0_PINCTL) & SC_PINCTL_SYNC_Msk);\
            if(u32State)\
                outpw(REG_SC0_PINCTL, inpw(REG_SC0_PINCTL) | SC_PINCTL_SCDOUT_Msk);\
            else\
                outpw(REG_SC0_PINCTL, inpw(REG_SC0_PINCTL) & ~SC_PINCTL_SCDOUT_Msk);\
        } else {\
            while(inpw(REG_SC1_PINCTL) & SC_PINCTL_SYNC_Msk);\
            if(u32State)\
                outpw(REG_SC1_PINCTL, inpw(REG_SC1_PINCTL) | SC_PINCTL_SCDOUT_Msk);\
            else\
                outpw(REG_SC1_PINCTL, inpw(REG_SC1_PINCTL) & ~SC_PINCTL_SCDOUT_Msk);\
        }\
    }while(0)

/**
  * @brief Set RST pin state.
  * @param[in] sc Smartcard module number
  * @param[in] u32State Pin state of RST pin, valid parameters are:
  *                 \ref SC_PIN_STATE_HIGH    :Smartcard pin status high.
  *                 \ref SC_PIN_STATE_LOW     :Smartcard pin status low.
  * @return None
  * @details User can set SCRST(SC_PINCTL[1]) to decide SCRST pin to high or low.
  * \hideinitializer
  */
#define SC_SET_RST_PIN(sc, u32State)\
    do {\
        if(sc == 0) {\
            while(inpw(REG_SC0_PINCTL) & SC_PINCTL_SYNC_Msk);\
            if(u32State)\
                outpw(REG_SC0_PINCTL, inpw(REG_SC0_PINCTL) | SC_PINCTL_SCRST_Msk);\
            else\
                outpw(REG_SC0_PINCTL, inpw(REG_SC0_PINCTL) & ~SC_PINCTL_SCRST_Msk);\
        } else {\
            while(inpw(REG_SC1_PINCTL) & SC_PINCTL_SYNC_Msk);\
            if(u32State)\
                outpw(REG_SC1_PINCTL, inpw(REG_SC1_PINCTL) | SC_PINCTL_SCRST_Msk);\
            else\
                outpw(REG_SC1_PINCTL, inpw(REG_SC1_PINCTL) & ~SC_PINCTL_SCRST_Msk);\
        }\
    }while(0)

/**
  * @brief Read one byte from smartcard module receive FIFO.
  * @param[in] sc Smartcard module number
  * @return One byte read from receive FIFO.
  * @details By reading DAT register, the SC will return an 8-bit received data.
  * \hideinitializer
  */
#define SC_READ(sc) (sc == 0 ? inpw(REG_SC0_DAT) : inpw(REG_SC1_DAT))

/**
  * @brief Write one byte to smartcard module transmit FIFO.
  * @param[in] sc Smartcard module number
  * @param[in] u8Data Data to write to transmit FIFO.
  * @return None
  * @details By writing data to DAT register, the SC will send out an 8-bit data.
  * \hideinitializer
  */
#define SC_WRITE(sc, u8Data) \
    do {\
        if(sc == 0)\
            outpw(REG_SC0_DAT, u8Data);\
        else\
            outpw(REG_SC1_DAT, u8Data);\
    }while(0)

/**
  * @brief This macro set smartcard stop bit length.
  * @param[in] sc Smartcard module number
  * @param[in] u32Len Stop bit length, ether 1 or 2.
  * @return None
  * @details Stop bit length must be 1 for T = 1 protocol and 2 for T = 0 protocol.
  * \hideinitializer
  */
#define SC_SET_STOP_BIT_LEN(sc, u32Len) \
    do {\
        if(sc == 0) {\
            outpw(REG_SC0_CTL, (inpw(REG_SC0_CTL) & ~SC_CTL_NSB_Msk) | ((u32Len) == 1 ? 1 : 0));\
        } else{ \
            outpw(REG_SC1_CTL, (inpw(REG_SC1_CTL) & ~SC_CTL_NSB_Msk) | ((u32Len) == 1 ? 1 : 0));\
        }\
    }while(0)

/**
  * @brief Enable/Disable Tx error retry, and set Tx error retry count.
  * @param[in] sc Smartcard module number
  * @param[in] u32Count The number of times of Tx error retry count, between 0~8. 0 means disable Tx error retry.
  * @return None
  * @details This macro enable/disable transmitter retry function when parity error has occurred, and set error retry count.
  */
static __inline void SC_SetTxRetry(UINT sc, uint32_t u32Count)
{
    if (sc == 0)
    {
        while (inpw(REG_SC0_CTL) & SC_CTL_SYNC_Msk);
        outpw(REG_SC0_CTL, inpw(REG_SC0_CTL) & ~(SC_CTL_TXRTY_Msk | SC_CTL_TXRTYEN_Msk));
        if (u32Count != 0)
        {
            while (inpw(REG_SC0_CTL) & SC_CTL_SYNC_Msk);
            outpw(REG_SC0_CTL, inpw(REG_SC0_CTL) | (((u32Count - 1) << 20) | SC_CTL_TXRTYEN_Msk));
        }
    }
    else
    {
        while (inpw(REG_SC1_CTL) & SC_CTL_SYNC_Msk);
        outpw(REG_SC1_CTL, inpw(REG_SC1_CTL) & ~(SC_CTL_TXRTY_Msk | SC_CTL_TXRTYEN_Msk));
        if (u32Count != 0)
        {
            while (inpw(REG_SC1_CTL) & SC_CTL_SYNC_Msk);
            outpw(REG_SC1_CTL, inpw(REG_SC1_CTL) | (((u32Count - 1) << 20) | SC_CTL_TXRTYEN_Msk));
        }
    }
}

/**
  * @brief Enable/Disable Rx error retry, and set Rx error retry count.
  * @param[in] sc Smartcard module number
  * @param[in] u32Count The number of times of Rx error retry count, between 0~8. 0 means disable Rx error retry.
  * @return None
  * @details This macro enable/disable receiver retry function when parity error has occurred, and set error retry count.
  */
static __inline void  SC_SetRxRetry(UINT sc, uint32_t u32Count)
{
    if (sc == 0)
    {
        while (inpw(REG_SC0_CTL) & SC_CTL_SYNC_Msk);
        outpw(REG_SC0_CTL, inpw(REG_SC0_CTL) & ~(SC_CTL_RXRTY_Msk | SC_CTL_RXRTYEN_Msk));

        if (u32Count != 0)
        {
            while (inpw(REG_SC0_CTL) & SC_CTL_SYNC_Msk);
            outpw(REG_SC0_CTL, inpw(REG_SC0_CTL) | (((u32Count - 1) << 16) | SC_CTL_RXRTYEN_Msk));
        }
    }
    else
    {
        while (inpw(REG_SC1_CTL) & SC_CTL_SYNC_Msk);
        outpw(REG_SC1_CTL, inpw(REG_SC1_CTL) & ~(SC_CTL_RXRTY_Msk | SC_CTL_RXRTYEN_Msk));
        if (u32Count != 0)
        {
            while (inpw(REG_SC1_CTL) & SC_CTL_SYNC_Msk);
            outpw(REG_SC1_CTL, inpw(REG_SC1_CTL) | (((u32Count - 1) << 16) | SC_CTL_RXRTYEN_Msk));
        }
    }
}


UINT SC_IsCardInserted(UINT sc);
void SC_ClearFIFO(UINT sc);
void SC_Close(UINT sc);
void SC_Open(UINT sc, UINT u32CardDet, UINT u32PWR);
void SC_ResetReader(UINT sc);
void SC_SetBlockGuardTime(UINT sc, UINT u32BGT);
void SC_SetCharGuardTime(UINT sc, UINT u32CGT);
void SC_StopAllTimer(UINT sc);
void SC_StartTimer(UINT sc, UINT u32TimerNum, UINT u32Mode, UINT u32ETUCount);
void SC_StopTimer(UINT sc, UINT u32TimerNum);


/*@}*/ /* end of group SC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SC_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif //__NU_SC_H__



