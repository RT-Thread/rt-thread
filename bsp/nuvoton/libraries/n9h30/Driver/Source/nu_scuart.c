/**************************************************************************//**
 * @file     scuart.c
 * @brief    N9H30 series Smartcard UART mode (SCUART) driver source file
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "N9H30.h"
#include "nu_scuart.h"

/** @addtogroup N9H30_Device_Driver N9H30 Device Driver
  @{
*/

/** @addtogroup N9H30_SCUART_Driver SCUART Driver
  @{
*/


/** @addtogroup N9H30_SCUART_EXPORTED_FUNCTIONS SCUART Exported Functions
  @{
*/

/**
  * @brief Disable smartcard uart interface.
  * @param sc Smartcard module number
  * @return None
  * @details The function is used to disable smartcard interface UART mode.
  */
void SCUART_Close(UINT sc)
{
    if (sc == 0)
    {
        outpw(REG_SC0_INTEN, 0);
        outpw(REG_SC0_UARTCTL, 0);
        outpw(REG_SC0_CTL, 0);
    }
    else
    {
        outpw(REG_SC1_INTEN, 0);
        outpw(REG_SC1_UARTCTL, 0);
        outpw(REG_SC1_CTL, 0);
    }
}

/// @cond HIDDEN_SYMBOLS
/**
  * @brief This function returns module clock of specified SC interface
  * @param[in] sc Smartcard module number
  * @return Module clock of specified SC interface
  */
static uint32_t SCUART_GetClock(UINT sc)
{
    uint32_t u32Div;

    if (sc == 0)
        u32Div = ((inpw(REG_CLK_DIVCTL6) >> 24) & 0xF) + 1;
    else
        u32Div = ((inpw(REG_CLK_DIVCTL6) >> 28) & 0xF) + 1;

    return 12000000 / u32Div;
}
/// @endcond HIDDEN_SYMBOLS

/**
  * @brief Enable smartcard uart interface.
  * @param[in] sc Smartcard module number
  * @param[in] u32baudrate Target baudrate of smartcard module.
  * @return Actual baudrate of smartcard mode.
  * @details This function use to enable smartcard module UART mode and set baudrate.
  * @note This function configures character width to 8 bits, 1 stop bit, and no parity.
  *       And can use \ref SCUART_SetLineConfig function to update these settings.
  */
UINT SCUART_Open(UINT sc, UINT u32baudrate)
{
    uint32_t u32Clk = SCUART_GetClock(sc), u32Div;

    // Calculate divider for target baudrate
    u32Div = (u32Clk + (u32baudrate >> 1) - 1) / u32baudrate - 1;

    if (sc == 0)
    {
        outpw(REG_SC0_CTL, SC_CTL_SCEN_Msk | SC_CTL_NSB_Msk);   // Enable smartcard interface and stop bit = 1
        outpw(REG_SC0_UARTCTL, SCUART_CHAR_LEN_8 | SCUART_PARITY_NONE | SC_UARTCTL_UARTEN_Msk); // Enable UART mode, disable parity and 8 bit per character
        outpw(REG_SC0_ETUCTL, u32Div);
    }
    else
    {
        outpw(REG_SC1_CTL, SC_CTL_SCEN_Msk | SC_CTL_NSB_Msk);   // Enable smartcard interface and stop bit = 1
        outpw(REG_SC1_UARTCTL, SCUART_CHAR_LEN_8 | SCUART_PARITY_NONE | SC_UARTCTL_UARTEN_Msk); // Enable UART mode, disable parity and 8 bit per character
        outpw(REG_SC1_ETUCTL, u32Div);
    }

    return (u32Clk / (u32Div + 1));
}

/**
  * @brief Read data from smartcard UART interface.
  * @param[in] sc Smartcard module number
  * @param[in] pu8RxBuf The buffer to store receive the data.
  * @param[in] u32ReadBytes Target number of characters to receive.
  * @return Actual character number reads to buffer.
  * @details The function is used to read Rx data from RX FIFO.
  * @note This function does not block and return immediately if there's no data available.
  */
UINT SCUART_Read(UINT sc, char *pu8RxBuf, UINT u32ReadBytes)
{
    uint32_t u32Count;

    if (sc == 0)
    {
        for (u32Count = 0; u32Count < u32ReadBytes; u32Count++)
        {
            if (inpw(REG_SC0_STATUS) & SC_STATUS_RXEMPTY_Msk)  // no data available
            {
                break;
            }
            pu8RxBuf[u32Count] = inpw(REG_SC0_DAT);    // get data from FIFO
        }
    }
    else
    {
        for (u32Count = 0; u32Count < u32ReadBytes; u32Count++)
        {
            if (inpw(REG_SC1_STATUS) & SC_STATUS_RXEMPTY_Msk)  // no data available
            {
                break;
            }
            pu8RxBuf[u32Count] = inpw(REG_SC1_DAT);    // get data from FIFO
        }

    }

    return u32Count;
}

/**
  * @brief This function use to config smartcard UART mode line setting.
  * @param[in] sc Smartcard module number
  * @param[in] u32Baudrate Target baudrate of smartcard module. If this value is 0, UART baudrate will not change.
  * @param[in] u32DataWidth The data length, could be:
  *                 - \ref SCUART_CHAR_LEN_5
  *                 - \ref SCUART_CHAR_LEN_6
  *                 - \ref SCUART_CHAR_LEN_7
  *                 - \ref SCUART_CHAR_LEN_8
  * @param[in] u32Parity The parity setting, could be:
  *                 - \ref SCUART_PARITY_NONE
  *                 - \ref SCUART_PARITY_ODD
  *                 - \ref SCUART_PARITY_EVEN
  * @param[in] u32StopBits The stop bit length, could be:
  *                 - \ref SCUART_STOP_BIT_1
  *                 - \ref SCUART_STOP_BIT_2
  * @return Actual baudrate of smartcard.
  * @details Smartcard UART mode is operated in LIN data frame.
  */
UINT SCUART_SetLineConfig(UINT sc, UINT u32Baudrate, UINT u32DataWidth, UINT u32Parity, UINT  u32StopBits)
{

    uint32_t u32Clk = SCUART_GetClock(sc), u32Div;

    if (u32Baudrate == 0)   // keep original baudrate setting
    {
        u32Div = (sc == 0) ? inpw(REG_SC0_ETUCTL) & 0xFFF : inpw(REG_SC1_ETUCTL) & 0xFFF;
    }
    else
    {
        // Calculate divider for target baudrate
        u32Div = (u32Clk + (u32Baudrate >> 1) - 1) / u32Baudrate - 1;
        if (sc == 0)
            outpw(REG_SC0_ETUCTL, u32Div);
        else
            outpw(REG_SC1_ETUCTL, u32Div);
    }

    if (sc == 0)
    {
        outpw(REG_SC0_CTL, u32StopBits | SC_CTL_SCEN_Msk);  // Set stop bit
        outpw(REG_SC0_UARTCTL, u32Parity | u32DataWidth | SC_UARTCTL_UARTEN_Msk);   // Set character width and parity
    }
    else
    {
        outpw(REG_SC1_CTL, u32StopBits | SC_CTL_SCEN_Msk);  // Set stop bit
        outpw(REG_SC1_UARTCTL, u32Parity | u32DataWidth | SC_UARTCTL_UARTEN_Msk);   // Set character width and parity
    }
    return (u32Clk / (u32Div + 1));
}

/**
  * @brief This function use to set receive timeout count.
  * @param[in] sc Smartcard module number
  * @param[in] u32TOC Rx timeout counter, using baudrate as counter unit. Valid range are 0~0x1FF,
  *                   set this value to 0 will disable timeout counter.
  * @return None
  * @details The time-out counter resets and starts counting whenever the RX buffer received a
  *          new data word. Once the counter decrease to 1 and no new data is received or CPU
  *          does not read any data from FIFO, a receiver time-out interrupt will be generated.
  */
void SCUART_SetTimeoutCnt(UINT sc, UINT u32TOC)
{
    if (sc == 0)
        outpw(REG_SC0_RXTOUT, u32TOC);
    else
        outpw(REG_SC1_RXTOUT, u32TOC);
}


/**
  * @brief Write data to smartcard UART interface.
  * @param[in] sc Smartcard module number
  * @param[in] pu8TxBuf The buffer containing data to send to transmit FIFO.
  * @param[in] u32WriteBytes Number of data to send.
  * @return None
  * @details This function is to write data into transmit FIFO to send data out.
  * @note This function blocks until all data write into FIFO.
  */
void SCUART_Write(UINT sc, char *pu8TxBuf, UINT u32WriteBytes)
{
    uint32_t u32Count;

    if (sc == 0)
    {
        for (u32Count = 0; u32Count != u32WriteBytes; u32Count++)
        {
            while (inpw(REG_SC0_STATUS) & SC_STATUS_TXFULL_Msk); // Wait 'til FIFO not full
            outpw(REG_SC0_DAT, pu8TxBuf[u32Count]);    // Write 1 byte to FIFO
        }
    }
    else
    {
        for (u32Count = 0; u32Count != u32WriteBytes; u32Count++)
        {
            while (inpw(REG_SC0_STATUS) & SC_STATUS_TXFULL_Msk); // Wait 'til FIFO not full
            outpw(REG_SC1_DAT, pu8TxBuf[u32Count]);    // Write 1 byte to FIFO
        }
    }
}


/*@}*/ /* end of group N9H30_SCUART_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group N9H30_SCUART_Driver */

/*@}*/ /* end of group N9H30_Device_Driver */

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
