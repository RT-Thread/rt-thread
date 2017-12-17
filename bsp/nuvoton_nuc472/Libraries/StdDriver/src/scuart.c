/**************************************************************************//**
 * @file     scuart.c
 * @version  V1.00
 * $Revision: 7 $
 * $Date: 15/11/09 7:18p $
 * @brief    NUC472/NUC442 Smartcard UART mode (SCUART) driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NUC472_442.h"

/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_SCUART_Driver SCUART Driver
  @{
*/


/** @addtogroup NUC472_442_SCUART_EXPORTED_FUNCTIONS SCUART Exported Functions
  @{
*/

/**
  * @brief The function is used to disable smartcard interface UART mode.
  * @param sc The base address of smartcard module.
  * @return None
  */
void SCUART_Close(SC_T* sc)
{
    sc->INTEN = 0;
    sc->UARTCTL = 0;
    sc->CTL = 0;

}
/// @cond HIDDEN_SYMBOLS
/**
  * @brief This function returns module clock of specified SC interface
  * @param[in] sc The base address of smartcard module.
  * @return Module clock of specified SC interface
  */
static uint32_t SCUART_GetClock(SC_T *sc)
{
    uint32_t u32ClkSrc, u32Num, u32Clk;

    if(sc == SC0)
        u32Num = 0;
    else if(sc == SC1)
        u32Num = 1;
    else if(sc == SC2)
        u32Num = 2;
    else if(sc == SC3)
        u32Num = 3;
    else if(sc == SC4)
        u32Num = 4;
    else
        u32Num = 5;

    u32ClkSrc = (CLK->CLKSEL3 >> (2 * u32Num)) & CLK_CLKSEL3_SC0SEL_Msk;

    // Get smartcard module clock
    if(u32ClkSrc == 0)
        u32Clk = __HXT;
    else if(u32ClkSrc == 1)
        u32Clk = CLK_GetPLLClockFreq();
    else if(u32ClkSrc == 2)
        u32Clk = CLK_GetPCLKFreq();
    else
        u32Clk = __HIRC;

    if(u32Num < 4) {
        u32Clk /= (((CLK->CLKDIV1 >> (8 * u32Num)) & CLK_CLKDIV1_SC0DIV_Msk) + 1);
    } else {
        u32Clk /= (((CLK->CLKDIV2 >> (8 * (u32Num - 4))) & CLK_CLKDIV2_SC4DIV_Msk) + 1);
    }

    return u32Clk;
}

/// @endcond HIDDEN_SYMBOLS

/**
  * @brief This function use to enable smartcard module UART mode and set baudrate.
  * @param[in] sc The base address of smartcard module.
  * @param[in] u32baudrate Target baudrate of smartcard module.
  * @return Actual baudrate of smartcard mode
  * @details This function configures character width to 8 bits, 1 stop bit, and no parity.
  *          And can use \ref SCUART_SetLineConfig function to update these settings
  *          The baudrate clock source comes from SC_CLK/SC_DIV, where SC_CLK is controlled
  *          by SCxSEL in CLKSEL3 register, SC_DIV is controlled by SCxDIV in 
  *          CLKDIV1 and CLKDIV2 register. Since the baudrate divider is
  *          12-bit wide and must be larger than 4, (clock source / baudrate) must be
  *          larger or equal to 5 and smaller or equal to 4096. Otherwise this function
  *          cannot configure SCUART to work with target baudrate.
  */
uint32_t SCUART_Open(SC_T* sc, uint32_t u32baudrate)
{
    uint32_t u32Clk = SCUART_GetClock(sc), u32Div;

    // Calculate divider for target baudrate
    u32Div = (u32Clk + (u32baudrate >> 1) - 1) / u32baudrate - 1;

    sc->CTL = SC_CTL_SCEN_Msk | SC_CTL_NSB_Msk;  // Enable smartcard interface and stop bit = 1
    sc->UARTCTL = SCUART_CHAR_LEN_8 | SCUART_PARITY_NONE | SC_UARTCTL_UARTEN_Msk; // Enable UART mode, disable parity and 8 bit per character
    sc->ETUCTL = u32Div;

    return(u32Clk / u32Div);
}

/**
  * @brief The function is used to read Rx data from RX FIFO.
  * @param[in] sc The base address of smartcard module.
  * @param[in] pu8RxBuf The buffer to store receive the data
  * @param[in] u32ReadBytes Target number of characters to receive
  * @return Actual character number reads to buffer
  * @note This function does not block and return immediately if there's no data available
  */
uint32_t SCUART_Read(SC_T* sc, uint8_t *pu8RxBuf, uint32_t u32ReadBytes)
{
    uint32_t u32Count;

    for(u32Count = 0; u32Count < u32ReadBytes; u32Count++) {
        if(SCUART_GET_RX_EMPTY(sc)) { // no data available
            break;
        }
        pu8RxBuf[u32Count] = SCUART_READ(sc);    // get data from FIFO
    }

    return u32Count;
}

/**
  * @brief This function use to config smartcard UART mode line setting.
  * @param[in] sc The base address of smartcard module.
  * @param[in] u32Baudrate Target baudrate of smartcard module. If this value is 0, UART baudrate will not change.
  * @param[in] u32DataWidth The data length, could be
  *                 - \ref SCUART_CHAR_LEN_5
  *                 - \ref SCUART_CHAR_LEN_6
  *                 - \ref SCUART_CHAR_LEN_7
  *                 - \ref SCUART_CHAR_LEN_8
  * @param[in] u32Parity The parity setting, could be
  *                 - \ref SCUART_PARITY_NONE
  *                 - \ref SCUART_PARITY_ODD
  *                 - \ref SCUART_PARITY_EVEN
  * @param[in] u32StopBits The stop bit length, could be
  *                 - \ref SCUART_STOP_BIT_1
  *                 - \ref SCUART_STOP_BIT_2
  * @return Actual baudrate of smartcard
  * @details The baudrate clock source comes from SC_CLK/SC_DIV, where SC_CLK is controlled
  *          by SCxSEL in CLKSEL3 register, SC_DIV is controlled by SCxDIV in 
  *          CLKDIV1 and CLKDIV2 register. Since the baudrate divider is
  *          12-bit wide and must be larger than 4, (clock source / baudrate) must be
  *          larger or equal to 5 and smaller or equal to 4096. Otherwise this function
  *          cannot configure SCUART to work with target baudrate.
  */
uint32_t SCUART_SetLineConfig(SC_T* sc, uint32_t u32Baudrate, uint32_t u32DataWidth, uint32_t u32Parity, uint32_t  u32StopBits)
{

    uint32_t u32Clk = SCUART_GetClock(sc), u32Div;

    if(u32Baudrate == 0) {  // keep original baudrate setting
        u32Div = sc->ETUCTL & SC_ETUCTL_ETURDIV_Msk;
    } else {
        // Calculate divider for target baudrate
        u32Div = (u32Clk + (u32Baudrate >> 1) - 1)/ u32Baudrate - 1;
        sc->ETUCTL = u32Div;
    }

    sc->CTL = u32StopBits | SC_CTL_SCEN_Msk;  // Set stop bit
    sc->UARTCTL = u32Parity | u32DataWidth | SC_UARTCTL_UARTEN_Msk;  // Set character width and parity

    return(u32Clk / u32Div);
}

/**
  * @brief This function use to set receive timeout count.
  * @param[in] sc The base address of smartcard module.
  * @param[in] u32TOC Rx timeout counter, using baudrate as counter unit. Valid range are 0~0x1FF,
  *                   set this value to 0 will disable timeout counter
  * @return None
  * @details The time-out counter resets and starts counting whenever the RX buffer received a
  *          new data word. Once the counter decrease to 1 and no new data is received or CPU
  *          does not read any data from FIFO, a receiver time-out interrupt will be generated.
  */
void SCUART_SetTimeoutCnt(SC_T* sc, uint32_t u32TOC)
{
    sc->RXTOUT= u32TOC;
}


/**
  * @brief This function is to write data into transmit FIFO to send data out.
  * @param[in] sc The base address of smartcard module.
  * @param[in] pu8TxBuf The buffer containing data to send to transmit FIFO.
  * @param[in] u32WriteBytes Number of data to send.
  * @return None
  * @note This function blocks until all data write into FIFO
  */
void SCUART_Write(SC_T* sc,uint8_t *pu8TxBuf, uint32_t u32WriteBytes)
{
    uint32_t u32Count;

    for(u32Count = 0; u32Count != u32WriteBytes; u32Count++) {
        while(SCUART_GET_TX_FULL(sc));  // Wait 'til FIFO not full
        sc->DAT = pu8TxBuf[u32Count];    // Write 1 byte to FIFO
    }
}


/*@}*/ /* end of group NUC472_442_SCUART_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_SCUART_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
