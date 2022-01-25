/**
 * @file    spi17y.h
 * @brief   Serial Peripheral Interface (SPI17Y) function prototypes and data types.
 */

/* ****************************************************************************
 * Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
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
 * $Date: 2018-12-18 15:37:22 -0600 (Tue, 18 Dec 2018) $
 * $Revision: 40072 $
 *
 *************************************************************************** */

/* Define to prevent redundant inclusion */
#ifndef _SPI17Y_H_
#define _SPI17Y_H_

/* **** Includes **** */
#include "mxc_config.h"
#include "spi17y_regs.h"
#include "mxc_sys.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup spi17y SPI17Y
 * @ingroup spi
 * @{
 */

/* **** Definitions **** */

/** 
 * Enumeration type for setting the number data lines to use for communication. 
 */
typedef enum {
    SPI17Y_WIDTH_1 = 0,  /**< 1 Data Line.                        */
    SPI17Y_WIDTH_2 = 1,  /**< 2 Data Lines (x2).                  */
    SPI17Y_WIDTH_4 = 2   /**< 4 Data Lines (x4).                  */
} spi17y_width_t;

/** 
 * Enumeration type for setting the polarity of ss lines. 
 */
typedef enum {
    SPI17Y_POL_LOW  = 0, /**< Polarity Low.                        */
    SPI17Y_POL_HIGH = 1  /**< Polarity High.                  */
} spi17y_sspol_t;

/** 
 * Structure type representing a SPI17Y Master Transaction request.
 */
typedef struct spi17y_req spi17y_req_t;


/**
 * @brief Callback function type used in asynchronous SPI Master communication requests.
 * @details The function declaration for the SPI Master callback is:
 * @code 
 * void callback(spi17y_req_t * req, int error_code);
 * @endcode
 * |        |                                            |
 * | -----: | :----------------------------------------- |
 * | \p req |  Pointer to a #spi_req object representing the active SPI Master active transaction. |
 * | \p error_code | An error code if the active transaction had a failure or #E_NO_ERROR if successful. |
 * @note Callback will execute in interrupt context
 * @addtogroup spi_async
 */
typedef void (*spi17y_callback_fn)(spi17y_req_t * req, int error_code);

/**
 * @brief      Structure definition for an SPI Master Transaction request.
 * @note       When using this structure for an asynchronous operation, the
 *             structure must remain allocated until the callback is completed.
 * @addtogroup spi_async
 */
struct spi17y_req {
    uint8_t            ssel;       /**< Slave select line to use. (Master only, ignored in slave mode) */
    uint8_t            deass;      /**< Non-zero to de-assert slave select after transaction. (Master only, ignored in slave mode)*/
    spi17y_sspol_t     ssel_pol;   /**< Slave select line polarity. */
    const void         *tx_data;   /**< Pointer to a buffer to transmit data from. NULL if undesired. */
    void               *rx_data;   /**< Pointer to a buffer to store data received. NULL if undesired.*/
    spi17y_width_t     width;      /**< Number of data lines to use, see #spi17y_width_t. */
    unsigned           len;        /**< Number of transfer units to send from the \p tx_data buffer. */
    unsigned           bits;       /**< Number of bits in transfer unit (e.g. 8 for byte, 16 for short) */
    unsigned           rx_num;     /**< Number of bytes actually read into the \p rx_data buffer. */
    unsigned           tx_num;     /**< Number of bytes actually sent from the \p tx_data buffer */
    spi17y_callback_fn    callback;   /**< Callback function if desired, NULL otherwise */
};


/* **** Function Prototypes **** */

/**
 * @brief     Initialize the spi.
 * @param     spi     Pointer to spi module to initialize.
 * @param     mode    SPI mode for clock phase and polarity.
 * @param     freq    Desired clock frequency.
 * @param     sys_cfg System configuration object
 *
 * @return     #E_NO_ERROR if successful, @ref
 *             MXC_Error_Codes "error" if unsuccessful.
 */
int SPI17Y_Init(mxc_spi17y_regs_t *spi, unsigned int mode, unsigned int freq, const sys_cfg_spi17y_t* sys_cfg);

/**
 * @brief      Shutdown SPI module.
 * @param      spi  Pointer to SPI regs.
 * 
 * @return     #E_NO_ERROR if successful, @ref
 *             MXC_Error_Codes "error" if unsuccessful.
 */
int SPI17Y_Shutdown(mxc_spi17y_regs_t *spi);

/**
 * @brief     Processing function for asynchronous SPI operations.  
 *            This function must be called either from the SPI interrupt 
 *            handler or periodically.
 *
 * @param     spi   Pointer to spi module.
 */
void SPI17Y_Handler(mxc_spi17y_regs_t *spi);

/**
 * @brief     Execute a master transaction.
 *            This function will block until the transaction is complete.
 * @param     spi   Pointer to spi module.
 * @param     req   Pointer to spi request
 * 
 * @return     #E_NO_ERROR if successful, @ref
 *             MXC_Error_Codes "error" if unsuccessful.
 */
int SPI17Y_MasterTrans(mxc_spi17y_regs_t *spi, spi17y_req_t *req);

/**
 * @brief     Execute a slave transaction.
 *            This function will block until the transaction is complete.
 * @param     spi   Pointer to spi module.
 * @param     req   Pointer to spi request
 * 
 * @return     #E_NO_ERROR if successful, @ref
 *             MXC_Error_Codes "error" if unsuccessful.
 */
int SPI17Y_SlaveTrans(mxc_spi17y_regs_t *spi, spi17y_req_t *req);

/**
 * @brief      Asynchronously read/write SPI Master data
 *
 * @param      spi   Pointer to spi module
 * @param      req   Pointer to spi request
 *
 * @return     #E_NO_ERROR if successful, @ref
 *             MXC_Error_Codes "error" if unsuccessful.
 */
int SPI17Y_MasterTransAsync(mxc_spi17y_regs_t *spi, spi17y_req_t *req);

/**
 * @brief      Asynchronously read/write SPI Slave data
 *
 * @param      spi   Pointer to spi module
 * @param      req   Pointer to spi request
 *
 * @return     #E_NO_ERROR if successful, @ref
 *             MXC_Error_Codes "error" if unsuccessful.
 */
int SPI17Y_SlaveTransAsync(mxc_spi17y_regs_t *spi, spi17y_req_t *req);

/**
 * @brief      Aborts an Asynchronous request
 *
 * @param      req   Pointer to spi request
 * @return     #E_NO_ERROR if successful, @ref
 *             MXC_Error_Codes "error" if unsuccessful.
 */
int SPI17Y_AbortAsync(spi17y_req_t *req);

/**
 * @brief     Enable SPI
 * @param     spi  Pointer to spi module.
 *
 * @return     #E_NO_ERROR if successful, @ref
 *             MXC_Error_Codes "error" if unsuccessful.
 */
void SPI17Y_Enable(mxc_spi17y_regs_t* spi);

/**
 * @brief     Disable SPI.  Any pending asynchronous transactions will not
 *            complete and their callbacks will not be executed.
 * @param     spi  Pointer to spi module.
 *
 * @return     #E_NO_ERROR if successful, @ref
 *             MXC_Error_Codes "error" if unsuccessful.
 */
void SPI17Y_Disable(mxc_spi17y_regs_t* spi);

/**
 * @brief     Clear the TX and RX FIFO
 * @param     spi  Pointer to spi module.
 *
 * @return     #E_NO_ERROR if successful, @ref
 *             MXC_Error_Codes "error" if unsuccessful.
 */
void SPI17Y_Clear_fifo(mxc_spi17y_regs_t* spi);


/**@} end of group spi17y */

#ifdef __cplusplus
}
#endif

#endif /* _SPI17Y_H_ */
