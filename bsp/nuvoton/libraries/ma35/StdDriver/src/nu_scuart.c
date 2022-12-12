/**************************************************************************//**
 * @file     scuart.c
 * @brief    Smartcard UART mode (SCUART) driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NuMicro.h"

static uint32_t SCUART_GetClock(SC_T *sc);

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SCUART_Driver SCUART Driver
  @{
*/


/** @addtogroup SCUART_EXPORTED_FUNCTIONS SCUART Exported Functions
  @{
*/

/**
  * @brief The function is used to disable smartcard interface UART mode.
  * @param sc The base address of smartcard module.
  * @return None
  */
void SCUART_Close(SC_T *sc)
{
    sc->INTEN = 0UL;
    sc->UARTCTL = 0UL;
    sc->CTL = 0UL;

}
/** @cond HIDDEN_SYMBOLS */
/**
  * @brief This function returns module clock of specified SC interface
  * @param[in] sc The base address of smartcard module.
  * @return Module clock of specified SC interface
  */
static uint32_t SCUART_GetClock(SC_T *sc)
{
    uint32_t u32ClkSrc, u32Num, u32Clk;

    if (sc == SC0)
    {
        u32Num = 0UL;
    }
    else
    {
        u32Num = 1UL;
    }

    u32ClkSrc = CLK->CLKSEL4 >> (u32Num + CLK_CLKSEL4_SC0SEL_Msk);

    /* Get smartcard module clock */
    if (u32ClkSrc == 0UL)
    {
        u32Clk = __HXT;
    }
    else
    {
        u32Clk = CLK_GetPCLK3Freq();
    }


    u32Clk /= (((CLK->CLKDIV1 >> (4UL * u32Num)) & CLK_CLKDIV1_SC0DIV_Msk) + 1UL);


    return u32Clk;
}

/** @endcond HIDDEN_SYMBOLS */

/**
  * @brief This function use to enable smartcard module UART mode and set baudrate.
  * @param[in] sc The base address of smartcard module.
  * @param[in] u32baudrate Target baudrate of smartcard module.
  * @return Actual baudrate of smartcard mode
  * @details This function configures character width to 8 bits, 1 stop bit, and no parity.
  *          And can use \ref SCUART_SetLineConfig function to update these settings
  *          The baudrate clock source comes from SC_CLK/SC_DIV, where SC_CLK is controlled
  *          by SCxSEL in CLKSEL3 register, SC_DIV is controlled by SCxDIV in CLKDIV1
  *          register. Since the baudrate divider is 12-bit wide and must be larger than 4,
  *          (clock source / baudrate) must be larger or equal to 5 and smaller or equal to
  *          4096. Otherwise this function cannot configure SCUART to work with target baudrate.
  */
uint32_t SCUART_Open(SC_T *sc, uint32_t u32baudrate)
{
    uint32_t u32Clk = SCUART_GetClock(sc), u32Div;

    /* Calculate divider for target baudrate */
    u32Div = (u32Clk + (u32baudrate >> 1) - 1UL) / u32baudrate - 1UL;

    /* Enable smartcard interface and stop bit = 1 */
    sc->CTL = SC_CTL_SCEN_Msk | SC_CTL_NSB_Msk;
    /* Enable UART mode, disable parity and 8 bit per character */
    sc->UARTCTL = SCUART_CHAR_LEN_8 | SCUART_PARITY_NONE | SC_UARTCTL_UARTEN_Msk;
    sc->ETUCTL = u32Div;

    return (u32Clk / (u32Div + 1UL));
}

/**
  * @brief The function is used to read Rx data from RX FIFO.
  * @param[in] sc The base address of smartcard module.
  * @param[in] pu8RxBuf The buffer to store receive the data
  * @param[in] u32ReadBytes Target number of characters to receive
  * @return Actual character number reads to buffer
  * @note This function does not block and return immediately if there's no data available
  */
uint32_t SCUART_Read(SC_T *sc, uint8_t pu8RxBuf[], uint32_t u32ReadBytes)
{
    uint32_t u32Count;

    for (u32Count = 0UL; u32Count < u32ReadBytes; u32Count++)
    {
        if (SCUART_GET_RX_EMPTY(sc))  /* no data available */
        {
            break;
        }
        pu8RxBuf[u32Count] = (uint8_t)SCUART_READ(sc);    /* get data from FIFO */
    }

    return u32Count;
}

/**
  * @brief This function use to configure smartcard UART mode line setting.
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
  *          by SCxSEL in CLKSEL3 register, SC_DIV is controlled by SCxDIV in CLKDIV1
  *          register. Since the baudrate divider is 12-bit wide and must be larger than 4,
  *          (clock source / baudrate) must be larger or equal to 5 and smaller or equal to
  *          4096. Otherwise this function cannot configure SCUART to work with target baudrate.
  */
uint32_t SCUART_SetLineConfig(SC_T *sc, uint32_t u32Baudrate, uint32_t u32DataWidth, uint32_t u32Parity, uint32_t  u32StopBits)
{

    uint32_t u32Clk = SCUART_GetClock(sc), u32Div;

    if (u32Baudrate == 0UL)   /* keep original baudrate setting */
    {
        u32Div = sc->ETUCTL & SC_ETUCTL_ETURDIV_Msk;
    }
    else
    {
        /* Calculate divider for target baudrate */
        u32Div = (u32Clk + (u32Baudrate >> 1) - 1UL) / u32Baudrate - 1UL;
        sc->ETUCTL = u32Div;
    }
    /* Set stop bit */
    sc->CTL = u32StopBits | SC_CTL_SCEN_Msk;
    /* Set character width and parity */
    sc->UARTCTL = u32Parity | u32DataWidth | SC_UARTCTL_UARTEN_Msk;

    return (u32Clk / (u32Div + 1UL));
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
void SCUART_SetTimeoutCnt(SC_T *sc, uint32_t u32TOC)
{
    sc->RXTOUT = u32TOC;
}


/**
  * @brief This function is to write data into transmit FIFO to send data out.
  * @param[in] sc The base address of smartcard module.
  * @param[in] pu8TxBuf The buffer containing data to send to transmit FIFO.
  * @param[in] u32WriteBytes Number of data to send.
  * @return None
  * @note This function blocks until all data write into FIFO
  */
void SCUART_Write(SC_T *sc, uint8_t pu8TxBuf[], uint32_t u32WriteBytes)
{
    uint32_t u32Count;

    for (u32Count = 0UL; u32Count != u32WriteBytes; u32Count++)
    {
        /* Wait 'til FIFO not full */
        while (SCUART_GET_TX_FULL(sc))
        {
            ;
        }
        /* Write 1 byte to FIFO */
        sc->DAT = pu8TxBuf[u32Count];
    }
}


/*@}*/ /* end of group SCUART_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SCUART_Driver */

/*@}*/ /* end of group Standard_Driver */

