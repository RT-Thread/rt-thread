/**
    *****************************************************************************
    * @file     cmem7_uart.c
    *
    * @brief    CMEM7 uart file
    *
    *
    * @version  V1.0
    * @date     3. September 2013
    *
    * @note
    *
    *****************************************************************************
    * @attention
    *
    * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
    * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
    * TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
    * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
    * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
    * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
    *
    * <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
    *****************************************************************************
    */

#include "cmem7_uart.h"

#define UART_Mode_8b                        1
#define UART_Mode_8b_Parity                 7

#define UART_BaudMode_0                     0
#define UART_BaudMode_1                     1
#define UART_BaudMode_Division                          19200

#define UART_WR_MAX_FIFO_SIZE               16

static uint32_t UART_GetClock(UART0_Type* UARTx) {
    uint32_t dividor;
    assert_param(IS_UART_ALL_PERIPH(UARTx));

    if ((uint32_t)UARTx == (uint32_t)UART0) {
        dividor = GLOBAL_CTRL->CLK_SEL_0_b.UART0_CLK;
    } else if ((uint32_t)UARTx == (uint32_t)UART1) {
        dividor = GLOBAL_CTRL->CLK_SEL_0_b.UART1_CLK;
    } else if ((uint32_t)UARTx == (uint32_t)UART2) {
        dividor = GLOBAL_CTRL->CLK_SEL_1_b.UART2_CLK;
    }

    return SYSTEM_CLOCK_FREQ / (1 << (dividor + 1));
}

static uint16_t UART_CalcBaudrateReload(uint32_t FreqHz, uint32_t Baudrate) {
  if (Baudrate <= UART_BaudMode_Division) {
        /** reload in mode 0
          *    reload = FreqHz / 16 * Baudrate
          * round up
          *    reload = FreqHz / 16 * Baudrate + 1/ 2
          *    reload = (2 * FreqHz + 16 * Baudrate) / 2 * 16 * Baudrate
          */
        return ((FreqHz << 1) + (Baudrate << 4)) / (Baudrate << 5);
    }

    /** reload in mode 1
        *    reload = Baudrate * 16 * 65536 / FreqHz
        * round up
        *    reload = Baudrate * 16 * 65536 / FreqHz + 1/ 2
        *    reload = (2 * Baudrate * 16 * 65536 + FreqHz) / 2 * FreqHz
        */
    return ((((uint64_t)(Baudrate)) << 21) + FreqHz) / (FreqHz << 1);
}

void UART_Init(UART0_Type* UARTx, UART_InitTypeDef *init) {
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(init);
    assert_param(IS_UART_STOPBITS(init->UART_StopBits));
    assert_param(IS_UART_PARITY(init->UART_Parity));

    /* TODO : assume clock is 50MHz */
    UARTx->BAUDRATE = UART_CalcBaudrateReload(
      UART_GetClock(UARTx), init->UART_BaudRate);
    UARTx->CTRL_b.MODE =
      (init->UART_Parity == UART_Parity_None) ?
      UART_Mode_8b : UART_Mode_8b_Parity;
    UARTx->CTRL_b.STOP = init->UART_StopBits;
    UARTx->CTRL_b.PARITY =
      (init->UART_Parity == UART_Parity_None) ?
      UART_Parity_Even : init->UART_Parity;
    UARTx->CTRL_b.LOOPBACK = init->UART_LoopBack;
    UARTx->CTRL_b.RX_EN = init->UART_RxEn;
    UARTx->CTRL_b.CTS = init->UART_CtsEn;
    UARTx->CTRL_b.BAUD_MODE =
      (init->UART_BaudRate > UART_BaudMode_Division) ?
      UART_BaudMode_1 : UART_BaudMode_0;
    UARTx->CTRL_b.FIFO_EN = TRUE;
    UARTx->CTRL_b.RX_THRESHOLD = UART_WR_MAX_FIFO_SIZE;
    UARTx->CTRL_b.RX_HALF_FULL = (UART_WR_MAX_FIFO_SIZE >> 1);
    UARTx->TIMEOUT = 0xFF;

    UARTx->INT_MASK |= UART_Int_All;
    UARTx->INT_SEEN &= UART_Int_All;
}

void UART_EnableInt(UART0_Type* UARTx, uint32_t Int, BOOL enable) {
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_INT(Int));

  if (enable) {
      UARTx->INT_MASK &= ~Int;
    } else {
        UARTx->INT_MASK |= Int;
    }

    UARTx->INT_MASK &= UART_Int_All;
}

void UART_Enable(UART0_Type* UARTx, BOOL enable) {
    assert_param(IS_UART_ALL_PERIPH(UARTx));

    UARTx->RUN_b.EN = enable;
}

BOOL UART_GetIntStatus(UART0_Type* UARTx, uint32_t Int) {
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_INT(Int));

    if (0 != (UARTx->INT_SEEN & Int)) {
        return TRUE;
    }

    return FALSE;
}

void UART_ClearInt(UART0_Type* UARTx, uint32_t Int) {
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_INT(Int));

    UARTx->INT_SEEN = Int;
}

uint8_t UART_Write(UART0_Type* UARTx, uint8_t Size, uint8_t* Data) {
    uint8_t count;

    /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(Data);

    if (!UARTx->RUN_b.EN) {
        return 0;
    }

    count = 0;
    while (!UARTx->STATUS_b.TF && count < Size) {
        UARTx->TX_BUF = *(Data + count++);
    }

    return count;
}

/* return value is actual read data size */
uint8_t UART_Read(UART0_Type* UARTx, uint8_t Size, uint8_t* Data) {
    uint8_t count;

    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(Data);

    if (!UARTx->RUN_b.EN) {
        return 0;
    }

    count = 0;
    while (UARTx->STATUS_b.RNE && count < Size) {
        *(Data + count++) = (UARTx->RX_BUF & 0x00FF);
    }

    return count;
}

