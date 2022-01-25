/**
 * @file
 * @brief   Direct Memory Access (DMA) driver function prototypes and data types.
 */

/* ****************************************************************************
 * Copyright (C) 2017 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2019-07-01 11:06:19 -0500 (Mon, 01 Jul 2019) $
 * $Revision: 44383 $
 *
 *************************************************************************** */

#ifndef _DMA_H_
#define _DMA_H_

/* **** Includes **** */
#include "mxc_config.h"
#include "dma_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dma Direct Memory Access (DMA)
 * @ingroup periphlibs
 * @{
 */

/* **** Definitions **** */

/**
 * Enumeration for the DMA Channel's priority level.
 */
typedef enum {
    DMA_PRIO_HIGH = MXC_S_DMA_CFG_PRI_HIGH,         /**< High Priority */
    DMA_PRIO_MEDHIGH = MXC_S_DMA_CFG_PRI_MEDHIGH,   /**< Medium High Priority */
    DMA_PRIO_MEDLOW = MXC_S_DMA_CFG_PRI_MEDLOW,     /**< Medium Low Priority */
    DMA_PRIO_LOW = MXC_S_DMA_CFG_PRI_LOW,           /**< Low Priority */
} dma_priority_t;

/** @brief DMA request select */
typedef enum {
    DMA_REQSEL_MEMTOMEM = MXC_S_DMA_CFG_REQSEL_MEMTOMEM,        /**< Memory to Memory DMA Request Selection */
    DMA_REQSEL_SPI0RX = MXC_S_DMA_CFG_REQSEL_SPI0RX,            /**< SPI0 Receive DMA Request Selection */
    DMA_REQSEL_SPI1RX = MXC_S_DMA_CFG_REQSEL_SPI1RX,            /**< SPI1 Receive DMA Request Selection */
    DMA_REQSEL_UART0RX = MXC_S_DMA_CFG_REQSEL_UART0RX,          /**< UART0 Receive DMA Request Selection */
    DMA_REQSEL_UART1RX = MXC_S_DMA_CFG_REQSEL_UART1RX,          /**< UART1 Receive DMA Request Selection */
    DMA_REQSEL_I2C0RX = MXC_S_DMA_CFG_REQSEL_I2C0RX,            /**< I2C0 Receive DMA Request Selection */
    DMA_REQSEL_I2C1RX = MXC_S_DMA_CFG_REQSEL_I2C1RX,            /**< I2C1 Receive DMA Request Selection */
    DMA_REQSEL_SPI0TX = MXC_S_DMA_CFG_REQSEL_SPI0TX,            /**< SPI0 Transmit DMA Request Selection */
    DMA_REQSEL_SPI1TX = MXC_S_DMA_CFG_REQSEL_SPI1TX,            /**< SPI1 Transmit DMA Request Selection */
    DMA_REQSEL_UART0TX = MXC_S_DMA_CFG_REQSEL_UART0TX,          /**< UART0 Transmit DMA Request Selection */
    DMA_REQSEL_UART1TX = MXC_S_DMA_CFG_REQSEL_UART1TX,          /**< UART1 Transmit DMA Request Selection */
    DMA_REQSEL_I2C0TX = MXC_S_DMA_CFG_REQSEL_I2C0TX,            /**< I2C0 Transmit DMA Request Selection */
    DMA_REQSEL_I2C1TX = MXC_S_DMA_CFG_REQSEL_I2C1TX,            /**< I2C1 Transmit DMA Request Selection */
} dma_reqsel_t;

/** @brief Enumeration for the DMA prescaler */
typedef enum {
    DMA_PRESCALE_DISABLE = MXC_S_DMA_CFG_PSSEL_DIS,     /**< Prescaler disabled */
    DMA_PRESCALE_DIV256 = MXC_S_DMA_CFG_PSSEL_DIV256,   /**< Divide by 256 */
    DMA_PRESCALE_DIV64K = MXC_S_DMA_CFG_PSSEL_DIV64K,   /**< Divide by 65,536 */
    DMA_PRESCALE_DIV16M = MXC_S_DMA_CFG_PSSEL_DIV16M,   /**< Divide by 16,777,216 */
} dma_prescale_t;

/** @brief Enumeration for the DMA timeout value */
typedef enum {
    DMA_TIMEOUT_4_CLK = MXC_S_DMA_CFG_TOSEL_TO4,        /**< DMA timeout of 4 clocks */
    DMA_TIMEOUT_8_CLK = MXC_S_DMA_CFG_TOSEL_TO8,        /**< DMA timeout of 8 clocks */
    DMA_TIMEOUT_16_CLK = MXC_S_DMA_CFG_TOSEL_TO16,      /**< DMA timeout of 16 clocks */
    DMA_TIMEOUT_32_CLK = MXC_S_DMA_CFG_TOSEL_TO32,      /**< DMA timeout of 32 clocks */
    DMA_TIMEOUT_64_CLK = MXC_S_DMA_CFG_TOSEL_TO64,      /**< DMA timeout of 64 clocks */
    DMA_TIMEOUT_128_CLK = MXC_S_DMA_CFG_TOSEL_TO128,    /**< DMA timeout of 128 clocks */
    DMA_TIMEOUT_256_CLK = MXC_S_DMA_CFG_TOSEL_TO256,    /**< DMA timeout of 256 clocks */
    DMA_TIMEOUT_512_CLK = MXC_S_DMA_CFG_TOSEL_TO512,    /**< DMA timeout of 512 clocks */
} dma_timeout_t;

/** @brief DMA transfer data width */
typedef enum {
    /* Using the '_V_' define instead of the '_S_' since these same values will be used to 
       specify the DSTWD also.  The API functions will shift the value the correct amount 
       prior to writing the cfg register. */
    DMA_WIDTH_BYTE = MXC_V_DMA_CFG_SRCWD_BYTE,          /**< DMA transfer in bytes */
    DMA_WIDTH_HALFWORD = MXC_V_DMA_CFG_SRCWD_HALFWORD,  /**< DMA transfer in 16-bit half-words */
    DMA_WIDTH_WORD = MXC_V_DMA_CFG_SRCWD_WORD,          /**< DMA transfer in 32-bit words */
} dma_width_t;

/** @brief Convenience defines for options */
#define DMA_FALSE 0 /**< Define for passing 0 to DMA functions */
#define DMA_TRUE  1 /**< Define for passing 1 to DMA functions */

/* **** Function Prototypes **** */

/**
 * @brief      Initialize DMA resources
 * @details    This initialization is required before using the DMA driver functions.
 * @return     #E_NO_ERROR if successful
 */
int DMA_Init(void);


/**
 * @brief      Request DMA channel
 * @details    Returns a handle to the first free DMA channel, which can be used via API calls
 *             or direct access to channel registers using the DMA_GetCHRegs(int ch) function.
 * @return     Non-negative channel handle (inclusive of zero).
 * @return     #E_NONE_AVAIL    All channels in use.
 * @return     #E_BAD_STATE     DMA is not initialized, call DMA_Init() first.
 * @return     #E_BUSY          DMA is currently busy (locked), try again later.
 */
int DMA_AcquireChannel(void);

/**
 * @brief      Release DMA channel
 * @details    Stops any DMA operation on the channel and returns it to the pool of free channels.
 *
 * @param          ch   channel handle to release
 *
 * @return     #E_BAD_PARAM if an unused or invalid channel handle, #E_NO_ERROR otherwise
 */
int DMA_ReleaseChannel(int ch);

/**
 * @brief      Configure the DMA channel
 * @details    Configures the channel, which was previously requested by DMA_Getchannel()
 *
 * @param      ch           The channel to configure
 * @param      prio         The channel's priority
 * @param      reqsel       Select the DMA request line
 * @param      reqwait_en   The enable delay before request
 * @param      tosel        The transfer timer timeout select
 * @param      pssel        The transfer timer prescale select
 * @param      srcwd        The size of the read transactions
 * @param      srcinc_en    Enable auto-increment source pointer
 * @param      dstwd        The size of write transactions
 * @param      dstinc_en    Enable auto-increment destination pointer
 * @param      burst_size   The number of bytes transferred in one transaction
 * @param      chdis_inten  The channel disable interrupt enable
 * @param      ctz_inten    The count-to-zero interrupt enable
 *
 * @return     #E_BAD_PARAM if an unused or invalid channel handle
 * @return     #E_NO_ERROR otherwise
 */
int DMA_ConfigChannel(int ch,
                      dma_priority_t prio,
                      dma_reqsel_t reqsel, unsigned int reqwait_en,
                      dma_timeout_t tosel, dma_prescale_t pssel,
                      dma_width_t srcwd, unsigned int srcinc_en,
                      dma_width_t dstwd, unsigned int dstinc_en,
                      unsigned int burst_size, unsigned int chdis_inten,
                      unsigned int ctz_inten);

/**
 * @brief      Set channel source, destination, and count for transfer
 * @param      ch   channel handle
 * @param      src_addr  source address (*)
 * @param      dst_addr  destination address (*)
 * @param      count  number of bytes to transfer
 * @details    This function is used to set the source and destination addresses and the number
 *             of bytes to transfer using the channel, @p ch.
 * @note       Unless the channel request select is #DMA_REQSEL_MEMTOMEM,
 *             either src_addr or dst_addr will be ignored by the DMA engine.
 *             In these cases, the address is a don't-care. See the User's
 *             Guide for more information.
 * @return     #E_BAD_PARAM if an unused or invalid channel handle
 * @return     #E_NO_ERROR otherwise
 */
int DMA_SetSrcDstCnt(int ch,
                     void *src_addr,
                     void *dst_addr,
                     unsigned int count);

/**
 * @brief      Set channel reload values
 * @param      ch   channel handle
 * @param      src_addr_reload  source address
 * @param      dst_addr_reload  destination address
 * @param      count_reload  number of bytes to transfer
 * @details    This function will set the values which will be loaded after the
 *             channel count register reaches zero. After enabling, call with
 *             count_reload set to zero to disable reload.
 * @return     #E_BAD_PARAM if an unused or invalid channel handle
 * @return     #E_NO_ERROR otherwise
 */
int DMA_SetReload(int ch,
                  void *src_addr_reload,
                  void *dst_addr_reload,
                  unsigned int count_reload);

/**
 * @brief      Set channel interrupt callback
 * @param      ch        channel handle
 * @param      callback  Pointer to a function to call when the channel
 *                       interrupt flag is set and interrupts are enabled or
 *                       when DMA is shutdown by the driver.
 * @details    Configures the channel interrupt callback. The @p callback
 *             function is called for two conditions:
 *               -# When the channel's interrupt flag is set and DMA interrupts
 *                  are enabled.
 *               -# If the driver calls the DMA_Shutdown() function. The
 *                  callback function prototype is:
 * @code
 *             void callback_fn(int ch, int reason);
 * @endcode
 *             @p ch indicates the channel that generated the callback, @p
 *             reason is either #E_NO_ERROR for a DMA interrupt or #E_SHUTDOWN
 *             if the DMA is being shutdown.
 *
 * @return     #E_BAD_PARAM if an unused or invalid channel handle
 * @return     #E_NO_ERROR otherwise
 */
int DMA_SetCallback(int ch, void (*callback)(int, int));

/**
 * @brief      Enable channel interrupt
 * @param      ch   channel handle
 * @return     #E_BAD_PARAM if an unused or invalid channel handle
 * @return     #E_NO_ERROR otherwise
 */
int DMA_EnableInterrupt(int ch);

/**
 * @brief      Disable channel interrupt
 * @param      ch   channel handle
 * @return     #E_BAD_PARAM if an unused or invalid channel handle
 * @return     #E_NO_ERROR otherwise
 */
int DMA_DisableInterrupt(int ch);

/**
 * @brief Read channel interrupt flags
 * @param      ch channel handle
 * @param      fl flags to get
 * @return    #E_BAD_PARAM if an unused or invalid channel handle
 * @return    #E_NO_ERROR otherwise
 */
int DMA_GetFlags(int ch, unsigned int *fl);

/**
 * @brief      Clear channel interrupt flags
 * @param      ch   channel handle
 * @return     #E_BAD_PARAM if an unused or invalid channel handle
 * @return     #E_NO_ERROR otherwise
 */
int DMA_ClearFlags(int ch);

/**
 * @brief      Start transfer
 * @param      ch   channel handle
 * @details    Start the DMA channel transfer, assumes that DMA_SetSrcDstCnt() has been called beforehand.
 * @return     #E_BAD_PARAM if an unused or invalid channel handle
 * @return     #E_NO_ERROR otherwise
 */
int DMA_Start(int ch);

/**
 * @brief      Stop DMA transfer, irrespective of status (complete or in-progress)
 * @param      ch   channel handle
 * @return     #E_BAD_PARAM if an unused or invalid channel handle
 * @return     #E_NO_ERROR otherwise
 */
int DMA_Stop(int ch);

/**
 * @brief      Get a pointer to the DMA channel registers
 * @param      ch   channel handle
 * @details    If direct access to DMA channel registers is required, this
 *             function can be used on a channel handle returned by DMA_AcquireChannel().
 * @return     NULL if an unused or invalid channel handle, or a valid pointer otherwise
 */
mxc_dma_ch_regs_t *DMA_GetCHRegs(int ch);

/**
 * @brief      Interrupt handler function
 * @param      ch   channel handle
 * @details    Call this function as the ISR for each DMA channel under driver control.
 *             Interrupt flags for channel ch will be automatically cleared before return.
 * @return     NULL if an unused or invalid channel handle, or a valid pointer otherwise
 */
void DMA_Handler(int ch);

/**@} end of group dma */
#ifdef __cplusplus
}
#endif

#endif /* _DMA_H_ */
