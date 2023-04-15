/***************************************************************************//**
* \file cy_ethif.h
* \version 1.0
*
* Provides an API declaration of the Ethernet Interface driver
*
********************************************************************************
* \copyright
* Copyright 2020 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/**
* \addtogroup group_ethif
* \{
*
* Ethernet is a well-defined industry specification. Ethernet MAC module
* transmits and receives IEEE 802.3 frames by connecting with the PHY device
* using MII/RMII/GMII or RGMII interface. Ethernet MAC also supports 10/100/1000
* Transfer rates and IEEE 1588 time stamp feature. Infineon uses a third-party
* Ethernet MAC IP from Cadence GEM_GXL, which is a Gigabit Ethernet MAC.
*
* Below block diagram shows the hardware and software partition inside the MCU.
* Ethernet MAC IP hardware directly interface with external ethernet PHY via MII
* or RMII or GMII or RGMII interface and MDIO interface is for configuring the
* Ethernet PHY chip/device. The software section consists of three major layers
* Ethernet PDL (Peripheral Driver Library), Connectivity Middleware, and
* Applications. Ethernet PDL implements  low level driver for Ethernet MAC and a
* generic driver for the external Ethernet PHY chips.
*
* \image html ethernet_system.png "Ethernet Block Diagram"
*
* The ETHIF driver is wrapper around Cadence's EMAC core driver. This is a
* network interface driver to Cadence core EMAC driver. It provides APIs to
* communicate with Ethernet IP. The PHY driver also uses this driver to
* communicate with PHY chip (via application). This driver has internal buffer
* management, handling callbacks from Cadence EMAC during transport, etc.
*
* The functions and other declarations used in this driver are in cy_ethif.h.
* You can include cy_pdl.h (ModusToolbox only) to get access to all functions
* and declarations in the PDL.
*
* \section group_ethif_tx_rx_programming Tx/Rx Programming
*
* 1. Make sure all the pins connected between MAC and PHY is configured properly.
* 2. Enable Interrupts for Ethernet queues. This is used to receive events from driver.
* 3. Initialize MAC using \ref Cy_ETHIF_Init() API.
* 4. Optionally set filters.
* 5. PHY chip is outside of silicon. Initialize PHY using EPHY driver. Some PHY chip
*    needs configuration using it's proprietary(extended) registers. Fo this
*    refer to PHY data sheet.
* 6. Wait for link to be up. This can be done using EPHY APIs.
* 7. Once is link is up, then transmit frame using \ref Cy_ETHIF_TransmitFrame() API.
* 8. The receive callback is called when there is any frame received by MAC. The
*    receive callback is registered during \ref Cy_ETHIF_Init() API call.
*
* \section group_ethif_more_information More Information
*
* Refer to the technical reference manual (TRM) and the device datasheet.
*
* \section group_ethif_MISRA MISRA-C Compliance
* The Ethernet driver has no specific deviations
*
* \section group_ethif_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_ethif_macros Macros
* \defgroup group_ethif_functions Functions
* \defgroup group_ethif_data_structures Data Structures
* \defgroup group_ethif_enums Enumerated Types
*/

#if !defined (CY_ETHIF_H)
#define CY_ETHIF_H

#include "cy_device.h"

#if defined (CY_IP_MXETH)

#include <stddef.h>
#include "cy_syslib.h"
#include "cdn_errno.h"
#include "cedi.h"
#include "emac_regs_macro.h"
#include "edd_int.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_ethif_macros
* \{
*/

/** Driver major version */
#define CY_ETHIF_DRV_VERSION_MAJOR        1

/** Driver minor version */
#define CY_ETHIF_DRV_VERSION_MINOR        0

/** Eth driver ID */
#define CY_ETHIF_ID                     CY_PDL_DRV_ID(0x71U)

/** \} group_ethif_macros */

/***************************************
*        Constants
***************************************/

/** \cond INTERNAL */

/*##############################################################################
*                   USER DEFINES
*#############################################################################*/
/** Ethernet configurations constants  */
#define CY_ETH_STANDARD_BD                  (0U)                         /* Standard Buffer Descriptor Mode */
#define CY_ETH_EXTENDED_BD                  (1U)                         /* Extended Buffer Descriptor Mode */

/* DMA operational mode */
#define CY_ETH_TX_FSFM                      (0U)                         /* Full Store and Forward Mode [FSFM] for Tx */
#define CY_ETH_TX_PSFM                      (1U)                         /* Partial Store and Forward Mode [PSFM] for Tx */
#define CY_ETH_RX_FSFM                      (2U)                         /* Full Store and Forward Mode for Rx */
#define CY_ETH_RX_PSFM                      (3U)                         /* Partial Store and Forward Mode for Rx */

/** Ethernet channel  */
#define CY_ETH_DEFINE_NUM_IP                (CY_IP_MXETH_INSTANCES)      /* Number of Ethernet channels intended to use, maximum 2 */
#define CY_ETH_DEFINE_NUM_RXQS              (2U)                         /* Number of queues intended to use, maximum 2 */
#define CY_ETH_DEFINE_NUM_TXQS              (3U)                         /* Number of queues intended to use, maximum 3 */

/** Ethernet Operation Mode */
#define CY_ETH_DEFINE_TX_OP_MODE            CY_ETH_TX_FSFM               /* FSFM OR PSFM */
#define CY_ETH_DEFINE_RX_OP_MODE            CY_ETH_RX_FSFM               /* FSFM OR PSFM */
#define CY_ETH_DEFINE_TX_WATERMARK          (50U)                        /* Watermark level for Tx */
#define CY_ETH_DEFINE_RX_WATERMARK          (50U)                        /* Watermark level for Rx */

/** Buffer Descriptor mode  */
#define CY_ETH_DEFINE_BD                    CY_ETH_EXTENDED_BD           /* standard or extended */

/** Memory Allocation defines */                                         /* Frame Buffers are allocated based on number of buffer descriptors */
#define CY_ETH_DEFINE_TOTAL_BD_PER_TXQUEUE  (2U)                         /* Total number of Buffer Descriptors allocated for each transmit queue */
#define CY_ETH_DEFINE_TOTAL_BD_PER_RXQUEUE  (4U)                         /* Total number of Buffer Descriptors allocated for each receive queue */
/*############################################################################*/


/** Ethernet configurations constants  */
#define CY_ETH_TX_PBUF_SIZE                 (0x1U)                          /* dma_config[bit-10] 1: Use full configured addressable space (4Kb) */
#define CY_ETH_RX_PBUF_SIZE                 (0x3U)                          /* dma_config[bit-8:9]3: Use full configured addressable space (8Kb) */

/** Ethernet channel  */
#define CY_ETHIF_INSTANCE_0                 (0U)                            /* channel ETH0 considered instance 0 for driver reference */
#define CY_ETHIF_INSTANCE_1                 (1U)                            /* channel ETH1 considered instance 1 for driver reference */

#define CY_ETH0_TYPE                        (ETH0)                          /* This includes both GEMGXL and Wrapper */
#define CY_ETH0_ADDR_REG_BASE               (ETH0_BASE)                     /* Register area for ETH0 */
#define CY_ETH0_GEMGXL_ADDR_REGBASE         (ETH0_BASE + 0x00001000UL)        /* Register area for GEMGXL */

#if (CY_IP_MXETH_INSTANCES > 1u)
#define CY_ETH1_TYPE                        (ETH1)                          /* This includes both GEMGXL and Wrapper */
#define CY_ETH1_ADDR_REG_BASE               (ETH1_BASE)                     /* Register area for ETH1 */
#define CY_ETH1_GEMGXL_ADDR_REGBASE         (ETH1_BASE + 0x00001000UL)        /* Register area for GEMGXL */
#endif /* (CY_IP_MXETH_INSTANCES > 1u) */

/** Driver constants    */
#define CY_ETH_SIZE_MIN_FRAME               (64U)                           /* Min Frame size */
#define CY_ETH_SIZE_MAX_FRAME               (1536U)                         /* Max Frame size */
#define CY_ETH_SIZE_BUF_TXQ_RXQ             (1536U)                         /* Tx/Rx buffer size */

#if (CY_ETH_DEFINE_BD == CY_ETH_EXTENDED_BD)
#define CY_ETH_BD_SIZE                      (16U)                           /* 16 Bytes */
#else
#define CY_ETH_BD_SIZE                      (8U)                            /* 8 Bytes */
#endif

#define CY_ETH_DISABLE_0                    (0U)
#define CY_ETH_ENABLE_1                     (1U)
#define CY_ETH_MDIO_BUSY_0                  (0U)
#define CY_ETH_MDIO_IDLE_1                  (1U)
#define CY_ETH_QS0_0                        (0U)
#define CY_ETH_QS1_1                        (1U)
#define CY_ETH_QS2_2                        (2U)
#define CY_ETH_QS3_3                        (3U)
#define CY_ETH_NOT_INITIALIZE_0             (0U)
#define CY_ETH_INITIALIZE_1                 (1U)
#define CY_ETHIF_BUFFER_CLEARED_0           (0U)

#define CY_ETH_TOTAL_TX_BUF                 (CY_ETH_DEFINE_NUM_IP * CY_ETH_DEFINE_NUM_TXQS * CY_ETH_DEFINE_TOTAL_BD_PER_TXQUEUE)
#define CY_ETH_TOTAL_RX_BUF                 (CY_ETH_DEFINE_NUM_IP * CY_ETH_DEFINE_NUM_RXQS * CY_ETH_DEFINE_TOTAL_BD_PER_RXQUEUE * 2U)   // *2 is to replace the already provided buffer to BDs

#define CY_ETHIF_NO_BUFFER_AVAILABLE        (255U)
#define CY_ETHIF_BUFFER_AVAILABLE           (254U)

#define CY_ETHIF_MDIO_READ_FAILED           (2U)
#define CY_ETHIF_PHY_FLAG                   (0U)                         // defines clause 22

#define CY_ETHIF_TX_STATUS_CLEAR            (0x000001FFUL)

#define CY_EHTIF_EMPTYVALUE                 (0xBAADF00DUL)

#define CY_ETHIF_PAUSE_P0                   (0U)
#define CY_ETHIF_PAUSE_P1                   (1U)
#define CY_ETHIF_PAUSE_P2                   (2U)
#define CY_ETHIF_PAUSE_P3                   (3U)
#define CY_ETHIF_PAUSE_P4                   (4U)
#define CY_ETHIF_PAUSE_P5                   (5U)
#define CY_ETHIF_PAUSE_P6                   (6U)
#define CY_ETHIF_PAUSE_P7                   (7U)

#if (CY_IP_MXETH_INSTANCES > 1u)
    #define CY_ETHIF_IS_IP_INSTANCE_VALID(base) (((base) == CY_ETH0_TYPE) || ((base) == CY_ETH1_TYPE))
    #define CY_ETHIF_IP_INSTANCE(base) (((base) == CY_ETH0_TYPE) ? CY_ETHIF_INSTANCE_0 : CY_ETHIF_INSTANCE_1)
    #define CY_ETHIF_IP_ADDR_REGBASE(instance) (((instance) == CY_ETHIF_INSTANCE_0) ? CY_ETH0_TYPE : CY_ETH1_TYPE)
    #define CY_ETHIF_GEMGXL_ADDR_REGBASE(instance) (((instance) == CY_ETHIF_INSTANCE_0) ? CY_ETH0_GEMGXL_ADDR_REGBASE : CY_ETH1_GEMGXL_ADDR_REGBASE)
#else
    #define CY_ETHIF_IS_IP_INSTANCE_VALID(base) ((base) == CY_ETH0_TYPE)
    #define CY_ETHIF_IP_INSTANCE(base) (((base) == CY_ETH0_TYPE) ? CY_ETHIF_INSTANCE_0 : CY_ETHIF_INSTANCE_0)
    #define CY_ETHIF_IP_ADDR_REGBASE(instance) (((instance) == CY_ETHIF_INSTANCE_0) ? CY_ETH0_TYPE : CY_ETH0_TYPE)
    #define CY_ETHIF_GEMGXL_ADDR_REGBASE(instance) (((instance) == CY_ETHIF_INSTANCE_0) ? CY_ETH0_GEMGXL_ADDR_REGBASE : CY_ETH0_GEMGXL_ADDR_REGBASE)
#endif

/** \endcond */

/** \addtogroup group_ethif_macros
* \{
*/

/* Bit-flags to specify DMA config register bits 24-27; see EMAC User Guide for details. */
#define CY_ETHIF_CFG_DMA_DISC_RXP           (0x01U) /**< The DMA will automatically discard receive packets from the receiver packet buffer memory when no AMBA (AXI) resource is available. */
#define CY_ETHIF_CFG_DMA_FRCE_RX_BRST       (0x02U) /**< Force the RX DMA to always issue max length bursts on EOP(end of packet) or EOB(end of buffer) transfers. */
#define CY_ETHIF_CFG_DMA_FRCE_TX_BRST       (0x04U) /**< Force the TX DMA to always issue max length bursts on EOP(end of packet) or EOB(end of buffer) transfers. */

/** \} group_ethif_macros */

/***************************************
*        Enumerations
***************************************/

/**
* \addtogroup group_ethif_enums
* \{
*/

/**
 *****************************************************************************
 ** \brief Ethernet MAC driver error codes.
 **
 *****************************************************************************/
typedef enum
{
    CY_ETHIF_SUCCESS = 0U,               /**< Returned successful */
    CY_ETHIF_BAD_PARAM,                 /**< Bad parameter was passed */
    CY_ETHIF_MEMORY_NOT_ENOUGH,         /**< Assigned memory for BDs not enough */
    CY_ETHIF_LINK_DOWN,                 /**< Link between nodes is not up */
    CY_ETHIF_LINK_UP,                   /**< Link between nodes is up */
    CY_ETHIF_BUFFER_NOT_AVAILABLE,      /**< No local buffer available to send the frame */
} cy_en_ethif_status_t;


/**
 *****************************************************************************
 ** \brief Ethernet MAC driver buffer status.
 **
 *****************************************************************************/
typedef enum
{
    CY_ETHIF_BUFFER_UNINIT = 0U,         /**< Buffer Uninitialized */
    CY_ETHIF_BUFFER_FREE,               /**< Buffer free and cleared with CY_EHTIF_EMPTYVALUE */
    CY_ETHIF_BUFFER_OCCUPIED,           /**< Buffer has been allocated to BD or in case of Tx loaded with the source data */
    CY_ETHIF_BUFFER_RELEASED,           /**< Buffer has been used and can be written with CY_EHTIF_EMPTYVALUE */
} cy_en_ethif_buffer_status_t;


/**
 *****************************************************************************
 ** \brief Ethernet MAC Drive Modes.
 **
 *****************************************************************************/
typedef enum
{
    CY_ETHIF_CTL_MII_10         = 0U,    /**< PHY mode  MII - 10Mbps */
    CY_ETHIF_CTL_MII_100        = 1U,    /**< PHY mode  MII - 100Mbps */
    CY_ETHIF_CTL_GMII_1000      = 2U,    /**< PHY mode  GMII - 1000Mbps */
    CY_ETHIF_CTL_RGMII_10       = 3U,    /**< PHY mode  RGMII - 10Mbps (4bits/Cycle) */
    CY_ETHIF_CTL_RGMII_100      = 4U,    /**< PHY mode  RGMII - 100Mbps (4bits/Cycle) */
    CY_ETHIF_CTL_RGMII_1000     = 5U,    /**< PHY mode  RGMII - 1000Mbps (8bits/Cycle) */
    CY_ETHIF_CTL_RMII_10        = 6U,    /**< PHY mode  RMII - 10Mbps */
    CY_ETHIF_CTL_RMII_100       = 7U,    /**< PHY mode  RMII - 100Mbps */
} cy_en_ethif_speed_sel_t;


/**
 *****************************************************************************
 ** \brief Reference Clock for RMII/RGMII.
 **
 *****************************************************************************/
typedef enum
{
    CY_ETHIF_EXTERNAL_HSIO = 0U,         /**< Clock coming from HSIO */
    CY_ETHIF_INTERNAL_PLL,              /**< Clock referenced from Internal PLL source */
} cy_en_ethif_clock_ref_t;


/**
 *****************************************************************************
 ** \brief MAC filter types
 **
 *****************************************************************************/
typedef enum
{
    CY_ETHIF_FILTER_TYPE_DESTINATION = 0U, /**< filter on destination address */
    CY_ETHIF_FILTER_TYPE_SOURCE      = 1U, /**< filter on source address */
} cy_en_ethif_filter_type_t;


/**
 *****************************************************************************
 ** \brief Total number of filters supported
 **
 *****************************************************************************/
typedef enum
{
    CY_ETHIF_FILTER_NUM_1 = 1U,          /**< filter 1 */
    CY_ETHIF_FILTER_NUM_2 = 2U,          /**< filter 2 */
    CY_ETHIF_FILTER_NUM_3 = 3U,          /**< filter 3 */
    CY_ETHIF_FILTER_NUM_4 = 4U,          /**< filter 4 */
    CY_ETHIF_FILTER_NUM_INV,            /**< Invalid Filter */
} cy_en_ethif_filter_num_t;


/**
 *****************************************************************************
 ** \brief Transmit Time stamp modes
 **
 *****************************************************************************/
typedef enum
{
    CY_ETHIF_TX_TS_DISABLED = 0U,
    CY_ETHIF_TX_TS_PTP_EVENT_ONLY = 1U,
    CY_ETHIF_TX_TS_PTP_ALL = 2U,
    CY_ETHIF_TX_TS_ALL = 3U,
} cy_en_ethif_TxTs_mode_t;


/**
 *****************************************************************************
 ** \brief Receive Time stamp modes
 **
 *****************************************************************************/
typedef enum
{
    CY_ETHIF_RX_TS_DISABLED = 0U,
    CY_ETHIF_RX_TS_PTP_EVENT_ONLY = 1U,
    CY_ETHIF_RX_TS_PTP_ALL = 2U,
    CY_ETHIF_RX_TS_ALL = 3U,
} cy_en_ethif_RxTs_mode_t;


/**
 *****************************************************************************
 ** \brief DMA data buffer length
 **
 *****************************************************************************/
typedef enum
{
    CY_ETHIF_DMA_DBUR_LEN_1 = 0U,            /**< Single burst */
    CY_ETHIF_DMA_DBUR_LEN_4 = 1U,            /**< Burst upto 4 */
    CY_ETHIF_DMA_DBUR_LEN_8 = 2U,            /**< Burst upto 8 */
    CY_ETHIF_DMA_DBUR_LEN_16 = 3U,           /**< Burst upto 16 */
} cy_en_ethif_dma_data_buffer_len_t;


/**
 *****************************************************************************
 ** \brief MDC clock divider
 **
 *****************************************************************************/
typedef enum
{
    CY_ETHIF_MDC_DIV_BY_8 = 0U,              /**< Divide by 8 */
    CY_ETHIF_MDC_DIV_BY_16 = 1U,             /**< Divide by 16 */
    CY_ETHIF_MDC_DIV_BY_32 = 2U,             /**< Divide by 32 */
    CY_ETHIF_MDC_DIV_BY_48 = 3U,             /**< Divide by 48 */
    CY_ETHIF_MDC_DIV_BY_64 = 4U,             /**< Divide by 64 */
    CY_ETHIF_MDC_DIV_BY_96 = 5U,             /**< Divide by 96 */
    CY_ETHIF_MDC_DIV_BY_128 = 6U,            /**< Divide by 128 */
    CY_ETHIF_MDC_DIV_BY_224 = 7U,            /**< Divide by 224 */
} cy_en_ethif_dma_mdc_clk_div_t;


/** \} group_ethif_enums */


/***************************************
*        Configuration Structures
***************************************/
/**
* \addtogroup group_ethif_data_structures
* \{
*/


/**
 *****************************************************************************
 ** \brief Wrapper Configuration
 *****************************************************************************/
typedef struct
{
    cy_en_ethif_speed_sel_t stcInterfaceSel;        /**< Interface selection for ENET */
    cy_en_ethif_clock_ref_t bRefClockSource;        /**< Reference clock selection */
    uint8_t u8RefClkDiv;                            /**< Actual division would be u8RefClkDiv + 1 */
} cy_stc_ethif_wrapper_config_t;


/**
 *****************************************************************************
 ** \brief Tx/Rx Queue status
 *****************************************************************************/
typedef struct
{
    bool bTxQueueDisable[CY_ETH_QS2_2+1];           /**< Tx Queue0-2 || 0: Queue Enabled, 1: Queue Disabled */
    bool bRxQueueDisable[CY_ETH_QS2_2+1];           /**< Rx Queue0-2 || 0: Queue Enabled, 1: Queue Disabled */
} cy_stc_ethif_queue_disablestatus_t;


/**
 *****************************************************************************
 ** \brief Virtual and physical addresses of DMA-addressable data buffer
 *****************************************************************************/
typedef struct
{
    uintptr_t vAddr;                /**< Virtual address */
    uintptr_t pAddr;                /**< Physical address */
}  cy_stc_ethif_buff_addr_t;


/**
 *****************************************************************************
 ** \brief Buffer status
 *****************************************************************************/
typedef struct
{
    cy_stc_ethif_buff_addr_t        cy_ethif_bufaddr;       /**< Buffer address as per requirement by Cadence driver */
    cy_en_ethif_buffer_status_t     enBufStatus;            /**< Buffer status */
} cy_stc_ethif_bufstatus_t;


/**
 *****************************************************************************
 ** \brief 1588 Timer value
 *****************************************************************************/
typedef struct
{
    /** Upper 16 bits of seconds value */
    uint16_t secsUpper;
    /** Lower 32 bits of seconds value */
    uint32_t secsLower;
    /** Upper Nanoseconds value (30 bits) */
    uint32_t nanosecs;
} cy_stc_ethif_1588_timer_val_t;


/**
 *****************************************************************************
 ** \brief writing/reading the 1588 timer increment registers
 *****************************************************************************/
typedef struct
{
    /** Whole nanoseconds to increment timer each clock cycle */
    uint8_t nanoSecsInc;
    /** Sub-nanoseconds to increment the timer (16 bits) */
    uint16_t subNsInc;
    /** Lower 8 bits of sub-nanoseconds to increment the timer */
    uint8_t lsbSubNsInc;
    /** Number of increments before changing to alternative increment. If = 0 then never use alternative increment. */
    uint8_t altIncCount;
    /** Alternative nanoseconds increment to apply */
    uint8_t altNanoSInc;
} cy_stc_ethif_timer_increment_t;


/** struct for writing/reading 1588 timer */
typedef struct
{
    cy_stc_ethif_1588_timer_val_t * pstcTimerValue;         /**< TSU Timer value     */
    cy_stc_ethif_timer_increment_t * pstcTimerIncValue;     /**< TSU Timer increment value   */
    bool bOneStepTxSyncEnable;                              /**< One step sync enable    */
    cy_en_ethif_TxTs_mode_t enTxDescStoreTimeStamp;         /**< Store Time stamp value in Tx descriptor */
    cy_en_ethif_RxTs_mode_t enRxDescStoreTimeStamp;         /**< Store Time stamp value in Rx descriptor */
    bool bStoreNSinRxDesc;                                  /**< Store NanoSecond field of TSU in Rx Descriptor  */
} cy_stc_ethif_tsu_config_t;


/**
 *****************************************************************************
 ** \brief Frame transmission complete callback function. Signals a successful
 **        completed transmission.
 **
 ** \param base[IN] Pointer to register area of Ethernet MAC
 ** \param u8Queue[IN] Queue used for transmitting the frame
 *****************************************************************************/
 typedef void (*cy_ethif_tx_msg_cb_t)(ETH_Type *base, uint8_t u8QueueIndex);


 /**
 *****************************************************************************
 ** \brief Frame transmission Error callback function. Signals a transmission
 **        error.
 **
 ** \param base[IN] Pointer to register area of Ethernet MAC
 ** \param u8Queue[IN] Queue used for transmitting the frame
 *****************************************************************************/
 typedef void (*cy_ethif_tx_error_cb_t)(ETH_Type *base, uint8_t u8QueueIndex);


 /**
 *****************************************************************************
 ** \brief Frame received callback function. Signals a successful reception
 **        of frame.
 **
 ** \param base[IN] Pointer to register area of Ethernet MAC
 ** \param u8RxBuffer[IN] Receive frame buffer
 ** \param u32Length[IN] Frame buffer length
 *****************************************************************************/
 typedef void (*cy_ethif_rx_frame_cb_t)(ETH_Type *base, uint8_t * u8RxBuffer, uint32_t u32Length);


 /**
 *****************************************************************************
 ** \brief TSU Second counter increment callback function. Signals a One second
 **        increment in the TSU.
 **
 ** \param base[IN] Pointer to register area of Ethernet MAC
 *****************************************************************************/
 typedef void (*cy_ethif_tsu_inc_cb_t)(ETH_Type *base);

/**
 *****************************************************************************
 ** \brief Get Buffer callback function. Driver call this for getting free
 **        buffer for filling subsequent receive frame.
 **
 ** \param base[IN] Pointer to register area of Ethernet MAC
 ** \param u8RxBuffer[OUT] 32 bytes aligned Frame buffer
 ** \param u32Length[OUT] Frame buffer length
 *****************************************************************************/
 typedef void (*cy_ethif_rx_getbuffer_cb_t)(ETH_Type *base, uint8_t **u8RxBuffer, uint32_t *u32Length);


/**
 *****************************************************************************
 ** \brief Pointer to a Buffer pool.
 *****************************************************************************/
 typedef uint8_t* cy_ethif_buffpool_t[CY_ETH_DEFINE_TOTAL_BD_PER_RXQUEUE];

/**
 *****************************************************************************
 ** \brief Ethernet MAC call back handlers
 *****************************************************************************/
 typedef struct
 {
    cy_ethif_tx_msg_cb_t        txcompletecb;     /**< Transmit complete    */
    cy_ethif_tx_error_cb_t      txerrorcb;        /**< Tx Error    */
    cy_ethif_rx_frame_cb_t      rxframecb;        /**< Frame Received */
    cy_ethif_tsu_inc_cb_t       tsuSecondInccb;   /**< TSU timer Second counter incremented */
    cy_ethif_rx_getbuffer_cb_t  rxgetbuff;        /**< Get buffer for Receive Frame */
 } cy_stc_ethif_cb_t;



/**
 *****************************************************************************
 ** \brief Ethernet MAC detailed configurations
 *****************************************************************************/
typedef struct
{
    bool bintrEnable;                                   /**< interrupts/events to enable on start   */
    cy_en_ethif_dma_data_buffer_len_t dmaDataBurstLen;  /**< fixed burst length for DMA data transfers */
                                                        /**< bit4:0 amba_burst_length                                  */
                                                        /**< 1xxxx: attempt use burst up to 16 (CY_ETHIF_DMA_DBUR_LEN_16)  */
                                                        /**< 01xxx: attempt use burst up to  8 (CY_ETHIF_DMA_DBUR_LEN_8)   */
                                                        /**< 001xx: attempt use burst up to  4 (CY_ETHIF_DMA_DBUR_LEN_4)   */
                                                        /**< 0001x: always use single burst                            */
                                                        /**< 00001: always use single burst    (CY_ETHIF_AMBD_BURST_LEN_1) */
                                                        /**< 00000: best AXI burst up to 256 beats                     */
    uint8_t u8dmaCfgFlags;                              /**< DMA config register bits 24, 25 & 26.                   */
                                                        /**< OR the following bit-flags to set corresponding bits -  */
                                                        /**< CY_ETHIF_CFG_DMA_DISC_RXP,              */
                                                        /**< CY_ETHIF_CFG_DMA_FRCE_RX_BRST,          */
                                                        /**< CY_ETHIF_CFG_DMA_FRCE_TX_BRST        */
    cy_en_ethif_dma_mdc_clk_div_t mdcPclkDiv;           /**< divisor to generate MDC from pclk */
                                                        /**< CY_ETHIF_MDC_DIV_BY_8 = 0       */
                                                        /**< CY_ETHIF_MDC_DIV_BY_16 = 1      */
                                                        /**< CY_ETHIF_MDC_DIV_BY_32 = 2      */
                                                        /**< CY_ETHIF_MDC_DIV_BY_48 = 3      */
                                                        /**< CY_ETHIF_MDC_DIV_BY_64 = 4      */
                                                        /**< CY_ETHIF_MDC_DIV_BY_96 = 5      */
                                                        /**< CY_ETHIF_MDC_DIV_BY_128 = 6     */
                                                        /**< CY_ETHIF_MDC_DIV_BY_224 = 7     */
    uint8_t u8rxLenErrDisc;                             /**< enable discard of frames with length field error */
    uint8_t u8disCopyPause;                             /**< disable copying Rx pause frames to memory */
    uint8_t u8chkSumOffEn;                              /**< enable checksum offload operation */
    uint8_t u8rx1536ByteEn;                             /**< enable Rx of frames up to 1536 bytes */
    uint8_t u8rxJumboFrEn;                              /**< enable Rx of jumbo frames */
    uint8_t u8enRxBadPreamble;                          /**< enable Rx frames with non-standard preamble */
    uint8_t u8ignoreIpgRxEr;                            /**< ignore IPG rx_er (NetCfg b30) */
    uint8_t u8storeUdpTcpOffset;                        /**< u8storeUdpTcpOffset */
    uint8_t u8aw2wMaxPipeline;                          /**< Maximum number of outstanding AXI write requests,
                                                        * that can be issued by DMA via the AW channel.
                                                        * Must not be = 0 if using AXI as this would disable writes
                                                        */
    uint8_t u8ar2rMaxPipeline;                          /**< Maximum number of outstanding AXI read requests,
                                                        * that can be issued by DMA via the AR channel.
                                                        * Must not be = 0 if using AXI as this would disable reads
                                                        */
    uint8_t u8pfcMultiQuantum;                          /**< enable pfc multiple quantum (8 different priorities) */
    cy_stc_ethif_wrapper_config_t * pstcWrapperConfig;  /**< Configuration for Wrapper */
    cy_stc_ethif_tsu_config_t * pstcTSUConfig;          /**< Configuration for TSU */
    bool btxq0enable;                                   /**< Tx Q0 Enable    */
    bool btxq1enable;                                   /**< Tx Q1 Enable    */
    bool btxq2enable;                                   /**< Tx Q2 Enable    */
    bool brxq0enable;                                   /**< Rx Q0 Enable    */
    bool brxq1enable;                                   /**< Rx Q1 Enable    */
    bool brxq2enable;                                   /**< Rx Q2 Enable    */
    cy_ethif_buffpool_t *pRxQbuffPool[CY_ETH_DEFINE_NUM_RXQS]; /**< Rx Queues buffer pool 32 bytes aligned */
} cy_stc_ethif_mac_config_t;


/**
 ******************************************************************************
 ** \brief Interrupt configuration for Ethernet MAC
 ******************************************************************************/
typedef struct
{
    bool btsu_time_match;                  /**< Time stamp unit time match event */
    bool bwol_rx;                          /**< Wake on LAN event received */
    bool blpi_ch_rx;                       /**< LPI indication status bit change received */    /* TODO: LPI, wait for conclusion?    */
    bool btsu_sec_inc;                     /**< TSU seconds register increment */
    bool bptp_tx_pdly_rsp;                 /**< PTP pdelay_resp frame transmitted */
    bool bptp_tx_pdly_req ;                /**< PTP pdelay_req frame transmitted */
    bool bptp_rx_pdly_rsp;                 /**< PTP pdelay_resp frame received */
    bool bptp_rx_pdly_req;                 /**< PTP pdelay_req frame received */
    bool bptp_tx_sync;                     /**< PTP sync frame transmitted */
    bool bptp_tx_dly_req;                  /**< PTP delay_req frame transmitted */
    bool bptp_rx_sync;                     /**< PTP sync frame received */
    bool bptp_rx_dly_req;                  /**< PTP delay_req frame received */
    // bool bpcs_lp_page_rx;                  /** PCS auto-negotiation link partner page received */
    // bool bpcs_an_complete;                 /** PCS auto-negotiation has completed */
    bool bext_intr;                        /**< External input interrupt detected */
    bool bpause_frame_tx;                  /**< Pause frame transmitted */
    bool bpause_time_zero;                 /**< Pause time reaches zero or zeroq pause frame received */
    bool bpause_nz_qu_rx;                  /**< Pause frame with non-zero quantum received */
    bool bhresp_not_ok;                    /**< DMA hresp not OK */
    bool brx_overrun;                      /**< Rx overrun error */
    bool bpcs_link_change_det;             /**< Link status change detected by PCS */           /* TODO: PCS, wait for conclusion   */
    bool btx_complete;                     /**< Frame has been transmitted successfully */
    bool btx_fr_corrupt;                   /**< Tx frame corruption */
    bool btx_retry_ex_late_coll;           /**< Retry limit exceeded or late collision */
    bool btx_underrun;                     /**< Tx underrun */
    bool btx_used_read;                    /**< Used bit set has been read in Tx descriptor list */
    bool brx_used_read;                    /**< Used bit set has been read in Rx descriptor list */
    bool brx_complete;                     /**< Frame received successfully and stored */
    bool bman_frame;                       /**< Management Frame Sent */
} cy_stc_ethif_intr_config_t;


/**
 ******************************************************************************
 ** \brief Ethernet MAC Address
 ******************************************************************************/
typedef struct
{
    uint8_t byte[6];                       /**< 6 bytes MAC Address */
} cy_stc_ethif_mac_address_t;


/**
 ******************************************************************************
 ** \brief filter configuration for Ethernet MAC
 ******************************************************************************/
typedef struct
{
    cy_en_ethif_filter_type_t   typeFilter;   /**< typeFilter */
    cy_stc_ethif_mac_address_t  filterAddr;   /**< filterAddr */
    uint8_t                     ignoreBytes;  /**< e.g. ignoreBytes = 0x01 implies first byte received should not be compared.
                                                 * e.g. ignoreBytes = 0x03 implies first and second byte received should not be compared. */
} cy_stc_ethif_filter_config_t;


/** \} group_ethif_data_structures */


/** \} group_ethif_data_structures */

/***************************************
*        Function Prototypes
***************************************/
/**
* \addtogroup group_ethif_functions
* \{
*/

cy_en_ethif_status_t Cy_ETHIF_MdioInit(ETH_Type *base, cy_stc_ethif_mac_config_t * pstcEthIfConfig);
cy_en_ethif_status_t Cy_ETHIF_Init(ETH_Type *base, cy_stc_ethif_mac_config_t *pstcEthIfConfig, cy_stc_ethif_intr_config_t *pstcInterruptList);
void Cy_ETHIF_RegisterCallbacks(ETH_Type *base, cy_stc_ethif_cb_t *cbFuncsList);
void Cy_ETHIF_DecodeEvent(ETH_Type *base);
cy_en_ethif_status_t Cy_ETHIF_TransmitFrame(ETH_Type *base, uint8_t * pu8TxBuffer, uint16_t u16Length, uint8_t u8QueueIndex, bool bEndBuffer);
cy_en_ethif_status_t Cy_ETHIF_Get1588TimerValue(ETH_Type *base, cy_stc_ethif_1588_timer_val_t *stcRetTmrValue);
cy_en_ethif_status_t Cy_ETHIF_Set1588TimerValue(ETH_Type *base, cy_stc_ethif_1588_timer_val_t * pstcTmrValue);
cy_en_ethif_status_t Cy_ETHIF_TxPauseFrame(ETH_Type *base, bool bZeroTQ);
cy_en_ethif_status_t Cy_ETHIF_ConfigPause(ETH_Type *base, uint16_t u16PauseQuanta);
cy_en_ethif_status_t Cy_ETHIF_PhyRegWrite(ETH_Type *base, uint8_t u8RegNo, uint16_t u16Data, uint8_t u8PHYAddr);
uint32_t Cy_ETHIF_PhyRegRead(ETH_Type *base, uint8_t u8RegNo, uint8_t u8PHYAddr);
cy_en_ethif_status_t Cy_ETHIF_SetFilterAddress(ETH_Type *base, cy_en_ethif_filter_num_t filterNo, const cy_stc_ethif_filter_config_t* config);
void Cy_ETHIF_SetPromiscuousMode(ETH_Type *base, bool toBeEnabled);
void Cy_ETHIF_SetNoBroadCast(ETH_Type *base, bool rejectBC);
void Cy_ETHIF_DiscardNonVLANFrames(ETH_Type *base, bool enable);

/** \} group_ethif_functions */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXETH */

#endif /* CY_ETHIF_H */

/** \} group_eth */

/* [] END OF FILE */
