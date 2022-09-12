/**************************************************************************//**
 * @file     scuart.c
 * @version  V3.00
 * @brief    Smartcard UART mode (SCUART) driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NuMicro.h"


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SCUART_Driver SCUART Driver
  @{
*/

int32_t g_SCUART_i32ErrCode = 0;       /*!< SCUART global error code */

/** @addtogroup SCUART_EXPORTED_FUNCTIONS SCUART Exported Functions
  @{
*/

/**
  * @brief      Disable smartcard interface
  *
  * @param      sc      The pointer of smartcard module.
  *
  * @return     None
  *
  * @details    The function is used to disable smartcard interface UART mode.
  */
void SCUART_Close(SC_T *sc)
{
    sc->INTEN = 0UL;
    sc->UARTCTL = 0UL;
    sc->CTL = 0UL;
}

/** @cond HIDDEN_SYMBOLS */
/**
  * @brief      Returns module clock of specified SC interface
  *
  * @param[in]  sc      The pointer of smartcard module.
  *
  * @return     Module clock of specified SC interface.
  */
static uint32_t SCUART_GetClock(SC_T *sc)
{
    uint32_t u32ClkSrc = 0, u32Num = 0, u32ClkFreq = __HIRC, u32Div = 0;

    /* Get smartcard module clock source and divider */
    if (sc == SC0)
    {
        u32Num = 0UL;
        u32ClkSrc = CLK_GetModuleClockSource(SC0_MODULE);
        u32Div = CLK_GetModuleClockDivider(SC0_MODULE);
    }
    else if (sc == SC1)
    {
        u32Num = 1UL;
        u32ClkSrc = CLK_GetModuleClockSource(SC1_MODULE);
        u32Div = CLK_GetModuleClockDivider(SC1_MODULE);
    }
    else if (sc == SC2)
    {
        u32Num = 2UL;
        u32ClkSrc = CLK_GetModuleClockSource(SC2_MODULE);
        u32Div = CLK_GetModuleClockDivider(SC2_MODULE);
    }
    else
    {
        u32ClkFreq = 0UL;
    }

    if (u32ClkFreq != 0UL)
    {
        /* Get smartcard module clock */
        if (u32ClkSrc == 0UL)
        {
            u32ClkFreq = __HXT;
        }
        else if (u32ClkSrc == 1UL)
        {
            u32ClkFreq = CLK_GetPLLClockFreq();
        }
        else if (u32ClkSrc == 2UL)
        {
            if (u32Num == 1UL)
            {
                u32ClkFreq = CLK_GetPCLK1Freq();
            }
            else
            {
                u32ClkFreq = CLK_GetPCLK0Freq();
            }
        }
        else
        {
            u32ClkFreq = __HIRC;
        }

        u32ClkFreq /= (u32Div + 1UL);
    }

    return u32ClkFreq;
}
/** @endcond HIDDEN_SYMBOLS */

/**
  * @brief      Enable smartcard module UART mode and set baudrate
  *
  * @param[in]  sc          The pointer of smartcard module.
  * @param[in]  u32Baudrate Target baudrate of smartcard UART module.
  *
  * @return     Actual baudrate of smartcard UART mode
  *
  * @details    This function use to enable smartcard module UART mode and set baudrate.
  *
  * @note       This function configures character width to 8 bits, 1 stop bit, and no parity.
  *             And can use \ref SCUART_SetLineConfig function to update these settings.
  *             The baudrate clock source comes from SC_CLK/SC_DIV, where SC_CLK is controlled
  *             by SCxSEL in CLKSEL3 register, SC_DIV is controlled by SCxDIV in CLKDIV1
  *             register. Since the baudrate divider is 12-bit wide and must be larger than 4,
  *             (clock source / baudrate) must be larger or equal to 5 and smaller or equal to
  *             4096. Otherwise this function cannot configure SCUART to work with target baudrate.
  */
uint32_t SCUART_Open(SC_T *sc, uint32_t u32Baudrate)
{
    uint32_t u32ClkFreq = SCUART_GetClock(sc), u32Div;

    /* Calculate divider for target baudrate */
    u32Div = (u32ClkFreq + (u32Baudrate >> 1) - 1UL) / u32Baudrate - 1UL;

    sc->CTL = SC_CTL_SCEN_Msk | SC_CTL_NSB_Msk;  /* Enable smartcard interface and stop bit = 1 */
    sc->UARTCTL = SCUART_CHAR_LEN_8 | SCUART_PARITY_NONE | SC_UARTCTL_UARTEN_Msk; /* Enable UART mode, disable parity and 8 bit per character */
    sc->ETUCTL = u32Div;

    return (u32ClkFreq / (u32Div + 1UL));
}

/**
  * @brief      Read Rx data from Rx FIFO
  *
  * @param[in]  sc              The pointer of smartcard module.
  * @param[in]  pu8RxBuf        The buffer to store receive the data.
  * @param[in] u32ReadBytes     Target number of characters to receive
  *
  * @return     Actual character number reads to buffer
  *
  * @details    The function is used to read data from Rx FIFO.
  *
  * @note       This function does not block and return immediately if there's no data available.
  */
uint32_t SCUART_Read(SC_T *sc, uint8_t pu8RxBuf[], uint32_t u32ReadBytes)
{
    uint32_t u32Count;

    for (u32Count = 0UL; u32Count < u32ReadBytes; u32Count++)
    {
        if (SCUART_GET_RX_EMPTY(sc) == SC_STATUS_RXEMPTY_Msk)
        {
            /* No data available */
            break;
        }
        /* Get data from FIFO */
        pu8RxBuf[u32Count] = (uint8_t)SCUART_READ(sc);
    }

    return u32Count;
}

/**
  * @brief      Configure smartcard UART mode line setting
  *
  * @param[in]  sc              The pointer of smartcard module.
  * @param[in]  u32Baudrate     Target baudrate of smartcard UART mode. If this value is 0, SC UART baudrate will not change.
  * @param[in]  u32DataWidth    The data length, could be:
  *                                 - \ref SCUART_CHAR_LEN_5
  *                                 - \ref SCUART_CHAR_LEN_6
  *                                 - \ref SCUART_CHAR_LEN_7
  *                                 - \ref SCUART_CHAR_LEN_8
  * @param[in]  u32Parity       The parity setting, could be:
  *                                 - \ref SCUART_PARITY_NONE
  *                                 - \ref SCUART_PARITY_ODD
  *                                  - \ref SCUART_PARITY_EVEN
  * @param[in]  u32StopBits     The stop bit length, could be:
  *                                 - \ref SCUART_STOP_BIT_1
  *                                 - \ref SCUART_STOP_BIT_2
  *
  * @return     Actual baudrate of smartcard UART mode
  *
  * @details    The baudrate clock source comes from SC_CLK/SC_DIV, where SC_CLK is controlled
  *             by SCxSEL in CLKSEL3 register, SC_DIV is controlled by SCxDIV in CLKDIV1
  *             register. Since the baudrate divider is 12-bit wide and must be larger than 4,
  *             (clock source / baudrate) must be larger or equal to 5 and smaller or equal to
  *             4096. Otherwise this function cannot configure SCUART to work with target baudrate.
  */
uint32_t SCUART_SetLineConfig(SC_T *sc, uint32_t u32Baudrate, uint32_t u32DataWidth, uint32_t u32Parity, uint32_t u32StopBits)
{
    uint32_t u32ClkFreq = SCUART_GetClock(sc), u32Div;

    if (u32Baudrate == 0UL)
    {
        /* Keep original baudrate setting */
        u32Div = sc->ETUCTL & SC_ETUCTL_ETURDIV_Msk;
    }
    else
    {
        /* Calculate divider for target baudrate */
        u32Div = ((u32ClkFreq + (u32Baudrate >> 1) - 1UL) / u32Baudrate) - 1UL;
        sc->ETUCTL = u32Div;
    }

    sc->CTL = u32StopBits | SC_CTL_SCEN_Msk;  /* Set stop bit */
    sc->UARTCTL = u32Parity | u32DataWidth | SC_UARTCTL_UARTEN_Msk;  /* Set character width and parity */

    return (u32ClkFreq / (u32Div + 1UL));
}

/**
  * @brief      Set receive timeout count
  *
  * @param[in]  sc      The pointer of smartcard module.
  * @param[in]  u32TOC  Rx time-out counter, using baudrate as counter unit. Valid range are 0~0x1FF,
  *                     set this value to 0 will disable time-out counter.
  *
  * @return     None
  *
  * @details    The time-out counter resets and starts counting whenever the Rx buffer received a
  *             new data word. Once the counter decrease to 1 and no new data is received or CPU
  *             does not read any data from FIFO, a receiver time-out interrupt will be generated.
  */
void SCUART_SetTimeoutCnt(SC_T *sc, uint32_t u32TOC)
{
    sc->RXTOUT = u32TOC;
}

/**
  * @brief      Write data into transmit FIFO to send data out
  *
  * @param[in]  sc              The pointer of smartcard module.
  * @param[in]  pu8TxBuf        The buffer containing data to send to transmit FIFO.
  * @param[in]  u32WriteBytes   Number of data to send.
  *
  * @return Actual number of data put into SCUART Tx FIFO
  *
  * @details    This function is used to write data into Tx FIFO to send data out.
  *
  * @note This function sets g_SCUART_i32ErrCode to SCUART_TIMEOUT_ERR if the Tx FIFO
  *       blocks longer than expected.
  */
uint32_t SCUART_Write(SC_T *sc, uint8_t pu8TxBuf[], uint32_t u32WriteBytes)
{
    uint32_t u32Count;
    /* Baudrate * (start bit + 8-bit data + 1-bit parity + 2-bit stop) */
    uint32_t u32Delay = (SystemCoreClock / SCUART_GetClock(sc)) * sc->ETUCTL * 12, i;

    g_SCUART_i32ErrCode = 0;
    for (u32Count = 0UL; u32Count != u32WriteBytes; u32Count++)
    {
        i = 0;
        /* Wait 'til FIFO not full */
        while (SCUART_GET_TX_FULL(sc))
        {
            /* Block longer than expected. Maybe some interrupt disable SCUART clock? */
            if (i++ > u32Delay)
            {
                g_SCUART_i32ErrCode = SCUART_TIMEOUT_ERR;
                return u32Count;
            }
        }
        /* Write 1 byte to FIFO */
        sc->DAT = pu8TxBuf[u32Count];
    }
    return u32Count;
}


/**@}*/ /* end of group SCUART_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group SCUART_Driver */

/**@}*/ /* end of group Standard_Driver */
