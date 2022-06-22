/**
 * @file    spimss.h
 * @brief   Serial Peripheral Interface (SPIMSS) function prototypes and data types.
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
 * $Date: 2018-12-18 15:37:22 -0600 (Tue, 18 Dec 2018) $
 * $Revision: 40072 $
 *
 *************************************************************************** */
 
/* Define to prevent redundant inclusion */
#ifndef _SPIMSS_H_
#define _SPIMSS_H_

/* **** Includes **** */
#include "mxc_config.h"
#include "mxc_sys.h"
#include "spimss_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup spimss SPIMSS
 * @ingroup spi
 * @{
 */

/* **** Definitions **** */


/** 
 * @brief Enumeration type for setting the number data lines to use for communication.
 */
typedef enum {  // ONLY FOR COMPATIBILITY FOR CONSOLIDATION WITH SPY17, NOT USED OR NEEDED
    DUMMY_1,    /**< NOT USED                */
    DUMMY_2,    /**< NOT USED                */
    DUMMY_3,    /**< NOT USED                */
} spimss_width_t;

/**
 * @brief Structure type representing a SPI Master Transaction request.
 */
typedef struct spimss_req spimss_req_t;

/**
 * @brief Callback function type used in asynchronous SPI Master communication requests.
 * @details The function declaration for the SPI Master callback is:
 * @code 
 * void callback(spi_req_t * req, int error_code);
 * @endcode
 * |        |                                            |
 * | -----: | :----------------------------------------- |
 * | \p req |  Pointer to a #spi_req object representing the active SPI Master active transaction. |
 * | \p error_code | An error code if the active transaction had a failure or #E_NO_ERROR if successful. |
 * @note Callback will execute in interrupt context
 * @addtogroup spi_async
 */
typedef void (*spimss_callback_fn)(spimss_req_t * req, int error_code);

/**
 * @brief      Structure definition for an SPI Master Transaction request.
 * @note       When using this structure for an asynchronous operation, the
 *             structure must remain allocated until the callback is completed.
 * @addtogroup spi_async
 */
struct spimss_req {
    uint8_t            ssel;       /**< Not Used*/
    uint8_t            deass;      /**< Not Used*/
    const void         *tx_data;   /**< Pointer to a buffer to transmit data from. NULL if undesired. */
    void               *rx_data;   /**< Pointer to a buffer to store data received. NULL if undesired.*/
    spimss_width_t     width;      /**< Not Used */
    unsigned           len;        /**< Number of transfer units to send from the \p tx_data buffer. */
    unsigned           bits;       /**< Number of bits in transfer unit (e.g. 8 for byte, 16 for short) */
    unsigned           rx_num;     /**< Number of bytes actually read into the \p rx_data buffer. */
    unsigned           tx_num;     /**< Number of bytes actually sent from the \p tx_data buffer */
    spimss_callback_fn callback;   /**< Callback function if desired, NULL otherwise */
};

/* **** Function Prototypes **** */

/**
 * @brief     Initialize the spi.
 * @param     spi     Pointer to spi module to initialize.
 * @param     mode    SPI mode for clock phase and polarity.
 * @param     freq    Desired clock frequency.
 * @param     sys_cfg System configuration object
 *
 * @return \c #E_NO_ERROR if successful, appropriate error otherwise
 */
int SPIMSS_Init(mxc_spimss_regs_t *spi, unsigned mode, unsigned freq, const sys_cfg_spimss_t* sys_cfg);

/**
 * @brief      Shutdown SPI module.
 * @param      spi  Pointer to SPI regs.
 * 
 * @return  \c #E_NO_ERROR if successful, appropriate error otherwise
 */
int SPIMSS_Shutdown(mxc_spimss_regs_t *spi);

/**
 * @brief     Execute a master transaction.
 * @param     spi   Pointer to spi module.
 * @param     req   Pointer to spi request
 * 
 * @return  \c #E_NO_ERROR if successful, @ref
 *             MXC_Error_Codes "error" if unsuccessful.
 */
int SPIMSS_MasterTrans(mxc_spimss_regs_t *spi, spimss_req_t *req);

/**
 * @brief      Execute SPI transaction based on interrupt handler
 * @param      spi   The spi
 *
 */
void SPIMSS_Handler(mxc_spimss_regs_t *spi);

/**
 * @brief     Execute a slave transaction.
 * @param     spi   Pointer to spi module.
 * @param     req   Pointer to spi request
 * 
 * @return  \c #E_NO_ERROR if successful, @ref
 *             MXC_Error_Codes "error" if unsuccessful.
 */
int SPIMSS_SlaveTrans(mxc_spimss_regs_t *spi, spimss_req_t *req);

/**
 * @brief      Asynchronously read/write SPI Master data
 *
 * @param      spi   Pointer to spi module
 * @param      req   Pointer to spi request
 *
 * @return  \c #E_NO_ERROR if successful, @ref
 *             MXC_Error_Codes "error" if unsuccessful.
 */
int SPIMSS_MasterTransAsync(mxc_spimss_regs_t *spi, spimss_req_t *req);

/**
 * @brief      Asynchronously read/write SPI Slave data
 *
 * @param      spi   Pointer to spi module
 * @param      req   Pointer to spi request
 *
 * @return  \c #E_NO_ERROR if successful, @ref
 *             MXC_Error_Codes "error" if unsuccessful.
 */
int SPIMSS_SlaveTransAsync(mxc_spimss_regs_t *spi, spimss_req_t *req);

/**
 * @brief      Aborts an Asynchronous request
 *
 * @param      req   Pointer to spi request
 * @return  \c #E_NO_ERROR if successful, @ref
 *             MXC_Error_Codes "error" if unsuccessful.
 */
int SPIMSS_AbortAsync(spimss_req_t *req);

/**@} end of group spimss */

#ifdef __cplusplus
}
#endif

#endif /* _SPIMSS_H_ */
