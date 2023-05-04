/*******************************************************************************
* \file cy_canfd.c
* \version 1.30
*
* \brief
*  Provides an API implementation of the CAN FD driver.
*
********************************************************************************
* \copyright
* Copyright 2019-2020 Cypress Semiconductor Corporation
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

#include "cy_device.h"

#if defined (CY_IP_MXTTCANFD)

#include "cy_canfd.h"

#if defined(__cplusplus)
extern "C" {
#endif

/* Define for size of extended filter in word */
#define CY_CANFD_SIZE_OF_EXTID_FILTER_IN_WORD   (2U)

/* Define for size of transmit event FIFO in word */
#define CY_CANFD_SIZE_OF_TXEVENT_FIFO_IN_WORD   (2U)

/* Define for half maximum Rx buffers */
#define CY_CANFD_MESSAGE_HALF_OF_RX_BUFFERS     (32UL)

#define CY_CANFD_INTERRUPT_ENABLE_DEFAULT       (CANFD_CH_M_TTCAN_IE_DRXE_Msk |  /* Message stored to Rx Buffer */\
                                                 CANFD_CH_M_TTCAN_IE_RF1NE_Msk | /* Rx FIFO 1 New Message */\
                                                 CANFD_CH_M_TTCAN_IE_RF0NE_Msk)  /* Rx FIFO 0 New Message */
#define CY_CANFD_EXT_IDENTIFIER_LENGTH          (18U)

/* The configurable start addresses are 32-bit word addresses i.e. only bits 15
* to 2 are evaluated, the two least significant bits are ignored */
#define CY_CANFD_MRAM_SIGNIFICANT_BYTES_SHIFT   (2U)

/* Size of R0 and R1 fields of Rx Buffer or FIFO Element in 32-bit words */
#define CY_CANFD_R0_R1_SIZE                     (2UL)

/* Size of T0 and T1 fields of Tx Buffer in 32-bit words */
#define CY_CANFD_T0_T1_SIZE                     (2UL)
#define CY_CANFD_TX_EVENT_FIFO_ELEMENTS_NUM     (10UL)
#define CY_CANFD_CHANNEL_ADDR_MASK              (0xFFFF0000UL)

/* Standard Filter ID 2 */
#define CY_CANFD_SID_FILTER_S0_SFID2_Pos        (0UL)
#define CY_CANFD_SID_FILTER_S0_SFID2_Msk        (0x000007FFUL)

/* Standard Filter ID 1 */
#define CY_CANFD_SID_FILTER_S0_SFID1_Pos        (16UL)
#define CY_CANFD_SID_FILTER_S0_SFID1_Msk        (0x07FF0000UL)

/* Standard Filter Element Configuration */
#define CY_CANFD_SID_FILTER_S0_SFEC_Pos         (27UL)
#define CY_CANFD_SID_FILTER_S0_SFEC_Msk         (0x38000000UL)

/* Standard Filter Type */
#define CY_CANFD_SID_FILTER_S0_SFT_Pos          (30UL)
#define CY_CANFD_SID_FILTER_S0_SFT_Msk          (0xC0000000UL)

/* Extended Filter ID 2 */
#define CY_CANFD_XID_FILTER_F1_EFID2_Pos        (0UL)
#define CY_CANFD_XID_FILTER_F1_EFID2_Msk        (0x1FFFFFFFUL)

/* Extended Filter ID 1 */
#define CY_CANFD_XID_FILTER_F0_EFID1_Pos        (0UL)
#define CY_CANFD_XID_FILTER_F0_EFID1_Msk        (0x1FFFFFFFUL)

/* Extended Filter Element Configuration */
#define CY_CANFD_XID_FILTER_F0_EFEC_Pos         (29UL)
#define CY_CANFD_XID_FILTER_F0_EFEC_Msk         (0xE0000000UL)

/* Extended Filter Type */
#define CY_CANFD_XID_FILTER_F1_ETF_Pos          (30UL)
#define CY_CANFD_XID_FILTER_F1_ETF_Msk          (0xC0000000UL)

/* Tx Buffer Element Error State Indicator (ESI) */
#define CY_CANFD_TX_BUFFER_T0_ESI_Pos           (31UL)
#define CY_CANFD_TX_BUFFER_T0_ESI_Msk           (0x80000000UL)

/* Tx Buffer Element Extended Identifier (XTD) */
#define CY_CANFD_TX_BUFFER_T0_XTD_Pos           (30UL)
#define CY_CANFD_TX_BUFFER_T0_XTD_Msk           (0x40000000UL)

/* Tx Buffer Element Remote Transmission Request (RTR) */
#define CY_CANFD_TX_BUFFER_T0_RTR_Pos           (29UL)
#define CY_CANFD_TX_BUFFER_T0_RTR_Msk           (0x20000000UL)

/* Tx Buffer Element Identifier (ID) */
#define CY_CANFD_TX_BUFFER_T0_ID_Pos            (0UL)
#define CY_CANFD_TX_BUFFER_T0_ID_Msk            (0x1FFFFFFFUL)

/* Tx Buffer Element Message Marker (MM) */
#define CY_CANFD_TX_BUFFER_T1_MM_Pos            (24UL)
#define CY_CANFD_TX_BUFFER_T1_MM_Msk            (0xFF000000UL)

/* Tx Buffer Element Event FIFO Control (EFC) */
#define CY_CANFD_TX_BUFFER_T1_EFC_Pos           (23UL)
#define CY_CANFD_TX_BUFFER_T1_EFC_Msk           (0x00800000UL)

/* Tx Buffer Element FD Format (FDF) */
#define CY_CANFD_TX_BUFFER_T1_FDF_Pos           (21UL)
#define CY_CANFD_TX_BUFFER_T1_FDF_Msk           (0x00200000UL)

/* Tx Buffer Element Bit Rate Switching (BRS) */
#define CY_CANFD_TX_BUFFER_T1_BRS_Pos           (20UL)
#define CY_CANFD_TX_BUFFER_T1_BRS_Msk           (0x00100000UL)

/* Tx Buffer Element Data Length Code (DLC) */
#define CY_CANFD_TX_BUFFER_T1_DLC_Pos           (16UL)
#define CY_CANFD_TX_BUFFER_T1_DLC_Msk           (0x000F0000UL)

/* Rx Buffer and FIFO Element Identifier (ID) */
#define CY_CANFD_RX_BUFFER_R0_ID_Pos            (0UL)
#define CY_CANFD_RX_BUFFER_R0_ID_Msk            (0x1FFFFFFFUL)

/* Rx Buffer and FIFO Element Remote Transmission Request (RTR) */
#define CY_CANFD_RX_BUFFER_R0_RTR_Pos           (29UL)
#define CY_CANFD_RX_BUFFER_R0_RTR_Msk           (0x20000000UL)

/* Rx Buffer and FIFO Element Extended Identifier (XTD) */
#define CY_CANFD_RX_BUFFER_R0_XTD_Pos           (30UL)
#define CY_CANFD_RX_BUFFER_R0_XTD_Msk           (0x40000000UL)

/* Rx Buffer and FIFO Element Error State Indicator (ESI) */
#define CY_CANFD_RX_BUFFER_R0_ESI_Pos           (31UL)
#define CY_CANFD_RX_BUFFER_R0_ESI_Msk           (0x80000000UL)

/* Rx Buffer and FIFO Element Rx Timestamp (RXTS) */
#define CY_CANFD_RX_BUFFER_R1_RXTS_Pos          (0UL)
#define CY_CANFD_RX_BUFFER_R1_RXTS_Msk          (0x0000FFFFUL)

/* Rx Buffer and FIFO Element Data Length Code (DLC) */
#define CY_CANFD_RX_BUFFER_R1_DLC_Pos           (16UL)
#define CY_CANFD_RX_BUFFER_R1_DLC_Msk           (0x000F0000UL)

/* Rx Buffer and FIFO Element Bit Rate Switch (BRS) */
#define CY_CANFD_RX_BUFFER_R1_BRS_Pos           (20UL)
#define CY_CANFD_RX_BUFFER_R1_BRS_Msk           (0x00100000UL)

/* Rx Buffer and FIFO Element FD Format (FDF) */
#define CY_CANFD_RX_BUFFER_R1_FDF_Pos           (21UL)
#define CY_CANFD_RX_BUFFER_R1_FDF_Msk           (0x00200000UL)

/* Rx Buffer and FIFO Element Filter Index (FIDX) */
#define CY_CANFD_RX_BUFFER_R1_FIDX_Pos          (24UL)
#define CY_CANFD_RX_BUFFER_R1_FIDX_Msk          (0x7F000000UL)

/* Rx Buffer and FIFO Element Accepted Non-matching Frame (ANMF) */
#define CY_CANFD_RX_BUFFER_R1_ANMF_Pos          (31UL)
#define CY_CANFD_RX_BUFFER_R1_ANMF_Msk          (0x80000000UL)

#define CY_CANFD_ERRORS_MASK     (CANFD_CH_M_TTCAN_IR_RF0W_Msk  | /* Rx FIFO 0 Watermark Reached */\
                                  CANFD_CH_M_TTCAN_IR_RF0F_Msk  | /* Rx FIFO 0 Full */\
                                  CANFD_CH_M_TTCAN_IR_RF0L__Msk | /* Rx FIFO 0 Message Lost */\
                                  CANFD_CH_M_TTCAN_IR_RF1W_Msk  | /* Rx FIFO 1 Watermark Reached */\
                                  CANFD_CH_M_TTCAN_IR_RF1F_Msk  | /* Rx FIFO 1 Full */\
                                  CANFD_CH_M_TTCAN_IR_RF1L__Msk | /* Rx FIFO 1 Message Lost */\
                                  CANFD_CH_M_TTCAN_IR_TEFW_Msk  | /* Tx Event FIFO Watermark Reached */\
                                  CANFD_CH_M_TTCAN_IR_TEFF_Msk  | /* Tx Event FIFO Full */\
                                  CANFD_CH_M_TTCAN_IR_TEFL__Msk | /* Tx Event FIFO Element Lost */\
                                  CANFD_CH_M_TTCAN_IR_TSW_Msk  | /* Timestamp Wraparound */\
                                  CANFD_CH_M_TTCAN_IR_MRAF_Msk | /* Message RAM Access Failure */\
                                  CANFD_CH_M_TTCAN_IR_TOO_Msk  | /* Timeout Occurred */\
                                  CANFD_CH_M_TTCAN_IR_BEC_Msk  | /* Bit Error Corrected */\
                                  CANFD_CH_M_TTCAN_IR_BEU_Msk  | /* Bit Error Uncorrected */\
                                  CANFD_CH_M_TTCAN_IR_ELO_Msk  | /* Error Logging Overflow */\
                                  CANFD_CH_M_TTCAN_IR_EP__Msk  | /* Error Passive */\
                                  CANFD_CH_M_TTCAN_IR_EW__Msk  | /* Warning Status */\
                                  CANFD_CH_M_TTCAN_IR_BO__Msk  | /* Bus_Off Status */\
                                  CANFD_CH_M_TTCAN_IR_WDI_Msk  | /* Watchdog Interrupt */\
                                  CANFD_CH_M_TTCAN_IR_PEA_Msk  | /* Protocol Error in Arb. Phase */\
                                  CANFD_CH_M_TTCAN_IR_PED_Msk  | /* Protocol Error in Data Phase */\
                                  CANFD_CH_M_TTCAN_IR_ARA_Msk)   /* Access to Reserved Address */

/* Defines for default values */
#define CANFD_NBTP_DEF_VAL        (0x06000A03UL)
#define CANFD_DBTP_DEF_VAL        (0x00000A33UL)


/*****************************************************************************
 *  DLC-Word conversion
 *****************************************************************************/
static const uint8_t dataBufferSizeInWord[] =
{
    2u,            /**<  8 bytes */
    3u,            /**< 12 bytes */
    4u,            /**< 16 bytes */
    5u,            /**< 20 bytes */
    6u,            /**< 24 bytes */
    8u,            /**< 32 bytes */
    12u,           /**< 48 bytes */
    16u            /**< 64 bytes */
};


/*****************************************************************************
* Local function prototypes ('static')
*****************************************************************************/

static uint32_t Cy_CANFD_CalcTxBufAdrs(CANFD_Type const *base, uint32_t chan,
                                        uint32_t index,
                                        cy_stc_canfd_context_t const *context);


/*******************************************************************************
* Function Name: Cy_CANFD_Init
****************************************************************************//**
*
* Initializes the CAN FD module.
*
* \note The function does not enable the Tx Event FIFO but reserves 10
* Tx Event FIFO elements in Message RAM.
* \note The function enables the "Message stored to Rx Buffer",
* "Rx FIFO 1 New Message" and "Rx FIFO 0 New Message" interrupt events only.
* Other interrupts can be configured with the Cy_CANFD_SetInterruptMask() function.
* \note If the channel was disabled, call Cy_CANFD_Enable before calling Cy_CANFD_Init.
* \note Call this function only after all debug messages reception is completed.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
* The CAN FD channel number.
*
* \param *config
* The pointer to the CAN FD configuration structure.
*
* \param *context
* The pointer to the context structure \ref cy_stc_canfd_context_t allocated
* by the user. The structure is used during the CAN FD operation for internal
* configuration and data retention. User must not modify anything in this
* structure.
*
* \return
* \ref cy_en_canfd_status_t
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_Init
*
*******************************************************************************/
cy_en_canfd_status_t Cy_CANFD_Init(CANFD_Type *base, uint32_t chan,
                                   const cy_stc_canfd_config_t *config,
                                   cy_stc_canfd_context_t *context)
{
    cy_en_canfd_status_t ret = CY_CANFD_BAD_PARAM;
    volatile uint32_t* address;
    uint32_t  count;
    uint32_t  sizeInWord;

    /* Check for NULL pointers */
    if ((NULL != base) &&
        (NULL != context) &&
        (NULL != config) &&
        (NULL != config->bitrate) &&
        (NULL != config->globalFilterConfig) &&
        (NULL != config->rxFIFO0Config) &&
        (NULL != config->rxFIFO1Config)
       )
    {
        CY_ASSERT_L2(CY_CANFD_IS_CHANNEL_VALID(chan));
        CY_ASSERT_L2(CY_CANFD_IS_NOM_PRESCALER_VALID(config->bitrate->prescaler));
        CY_ASSERT_L2(CY_CANFD_IS_NOM_TIME_SEG_1_VALID(config->bitrate->timeSegment1));
        CY_ASSERT_L2(CY_CANFD_IS_NOM_TIME_SEG_2_VALID(config->bitrate->timeSegment2));
        CY_ASSERT_L2(CY_CANFD_IS_NOM_SYNC_JUMP_WIDTH_VALID(config->bitrate->syncJumpWidth));

        CY_ASSERT_L2(CY_CANFD_IS_SID_FILTERS_VALID(config->sidFilterConfig->numberOfSIDFilters));
        CY_ASSERT_L2(CY_CANFD_IS_XID_FILTERS_VALID(config->extidFilterConfig->numberOfEXTIDFilters));

        CY_ASSERT_L3(CY_CANFD_IS_ACCEPT_MATCHING_VALID(config->globalFilterConfig->nonMatchingFramesStandard));
        CY_ASSERT_L3(CY_CANFD_IS_ACCEPT_MATCHING_VALID(config->globalFilterConfig->nonMatchingFramesExtended));

        CY_ASSERT_L3(CY_CANFD_IS_BUF_DATA_SIZE_VALID(config->rxBufferDataSize, config->canFDMode));
        CY_ASSERT_L3(CY_CANFD_IS_BUF_DATA_SIZE_VALID(config->rxFIFO1DataSize, config->canFDMode));
        CY_ASSERT_L3(CY_CANFD_IS_BUF_DATA_SIZE_VALID(config->rxFIFO0DataSize, config->canFDMode));
        CY_ASSERT_L3(CY_CANFD_IS_BUF_DATA_SIZE_VALID(config->txBufferDataSize, config->canFDMode));

        CY_ASSERT_L3(CY_CANFD_IS_FIFO_MODE_VALID(config->rxFIFO0Config->mode));
        CY_ASSERT_L3(CY_CANFD_IS_FIFO_MODE_VALID(config->rxFIFO1Config->mode));

        CY_ASSERT_L2(CY_CANFD_IS_FIFO_NUM_VALID(config->rxFIFO0Config->numberOfFIFOElements));
        CY_ASSERT_L2(CY_CANFD_IS_FIFO_NUM_VALID(config->rxFIFO1Config->numberOfFIFOElements));

        CY_ASSERT_L2(CY_CANFD_IS_WATERMARK_VALID(config->rxFIFO1Config->watermark));
        CY_ASSERT_L2(CY_CANFD_IS_WATERMARK_VALID(config->rxFIFO1Config->watermark));

        CY_ASSERT_L2(CY_CANFD_IS_RX_BUF_NUM_VALID(config->noOfRxBuffers));
        CY_ASSERT_L2(CY_CANFD_IS_TX_BUF_NUM_VALID(config->noOfTxBuffers));

        /* Set the notification callback functions */
        context->canFDInterruptHandling.canFDTxInterruptFunction = config->txCallback;
        context->canFDInterruptHandling.canFDRxInterruptFunction = config->rxCallback;
        context->canFDInterruptHandling.canFDErrorInterruptFunction = config->errorCallback;

        /* Set CCCR_INIT and CCCR_CCE bits  */
        ret = Cy_CANFD_ConfigChangesEnable(base, chan);

        if (CY_CANFD_SUCCESS == ret)
        {
            /* Save the message RAM offset and size for the current CAN FD channel */
            context->messageRAMaddress = config->messageRAMaddress;
            context->messageRAMsize = config->messageRAMsize;

            if ((0U   != config->sidFilterConfig->numberOfSIDFilters) &&
                (NULL != config->sidFilterConfig->sidFilter))
            {
                /* Configure a standard ID filter:
                * The number of SID filters and Start address (word) of the SID filter
                * configuration in Message RAM
                */
                CANFD_SIDFC(base, chan) =
                _VAL2FLD(CANFD_CH_M_TTCAN_SIDFC_LSS, config->sidFilterConfig->numberOfSIDFilters) |
                _VAL2FLD(CANFD_CH_M_TTCAN_SIDFC_FLSSA, config->messageRAMaddress >> CY_CANFD_MRAM_SIGNIFICANT_BYTES_SHIFT);
            }
            else
            {
                CANFD_SIDFC(base, chan) = 0U;
            }

            if((0U   != config->extidFilterConfig->numberOfEXTIDFilters) &&
               (NULL != config->extidFilterConfig->extidFilter))
            {
                /* Configure an extended ID filter:
                * The number of XID filters and start address (word) of the ext id
                * filter configuration in Message RAM
                */
                CANFD_XIDFC(base, chan) =
                _VAL2FLD(CANFD_CH_M_TTCAN_XIDFC_LSE, config->extidFilterConfig->numberOfEXTIDFilters) |
                _VAL2FLD(CANFD_CH_M_TTCAN_XIDFC_FLESA, _FLD2VAL(CANFD_CH_M_TTCAN_SIDFC_FLSSA, CANFD_SIDFC(base, chan)) +
                                                           (config->sidFilterConfig->numberOfSIDFilters));

                /* Update the extended ID AND Mask */
                CANFD_XIDAM(base, chan) = _VAL2FLD(CANFD_CH_M_TTCAN_XIDAM_EIDM, config->extidFilterConfig->extIDANDMask);
            }
            else
            {
                CANFD_XIDFC(base, chan) = 0U;
                CANFD_XIDAM(base, chan) = 0U;
            }

            /* Configuration of Rx Buffer and Rx FIFO */
            CANFD_RXESC(base, chan) =
            _VAL2FLD(CANFD_CH_M_TTCAN_RXESC_RBDS, config->rxBufferDataSize) | /* Rx Buffer Data Size */
            _VAL2FLD(CANFD_CH_M_TTCAN_RXESC_F1DS, config->rxFIFO1DataSize) | /* Rx FIFO 1 Data Size */
            _VAL2FLD(CANFD_CH_M_TTCAN_RXESC_F0DS, config->rxFIFO0DataSize);  /* Rx FIFO 0 Data Size */

            /* Set the Rx FIFO 0 configuration:
             *  CAN FD RX FIFO 0 operating mode
             *  RX FIFO 0 Watermark
             *  The number of RX FIFO 0 Elements
             *  The start address of Rx FIFO 0 in Message RAM
             */
            CANFD_RXF0C(base, chan) =
            _VAL2FLD(CANFD_CH_M_TTCAN_RXF0C_F0OM, config->rxFIFO0Config->mode) |
            _VAL2FLD(CANFD_CH_M_TTCAN_RXF0C_F0WM, config->rxFIFO0Config->watermark) |
            _VAL2FLD(CANFD_CH_M_TTCAN_RXF0C_F0S, config->rxFIFO0Config->numberOfFIFOElements) |
            _VAL2FLD(CANFD_CH_M_TTCAN_RXF0C_F0SA, _FLD2VAL(CANFD_CH_M_TTCAN_XIDFC_FLESA, CANFD_XIDFC(base, chan)) +
                                                          (config->extidFilterConfig->numberOfEXTIDFilters *
                                                           CY_CANFD_SIZE_OF_EXTID_FILTER_IN_WORD));

            /* Set the Rx FIFO 1 configuration:
             *  CAN FD RX FIFO  1 operating mode
             *  RX FIFO 1 Watermark
             *  The number of RX FIFO 1 Elements
             *  The start address of Rx FIFO 1 in Message RAM
            */
            CANFD_RXF1C(base, chan) =
            _VAL2FLD(CANFD_CH_M_TTCAN_RXF1C_F1OM, config->rxFIFO1Config->mode) |
            _VAL2FLD(CANFD_CH_M_TTCAN_RXF1C_F1WM, config->rxFIFO1Config->watermark) |
            _VAL2FLD(CANFD_CH_M_TTCAN_RXF1C_F1S, config->rxFIFO1Config->numberOfFIFOElements) |
            _VAL2FLD(CANFD_CH_M_TTCAN_RXF1C_F1SA,
                    _FLD2VAL(CANFD_CH_M_TTCAN_RXF0C_F0SA, CANFD_RXF0C(base, chan)) +
                            (config->rxFIFO0Config->numberOfFIFOElements *
                             (CY_CANFD_R0_R1_SIZE + dataBufferSizeInWord[config->rxFIFO0DataSize])));

            /* Configure the Rx FIFO 0,1 Top pointer logic configuration */
            CANFD_RXFTOP_CTL(base, chan) =
            _VAL2FLD(CANFD_CH_RXFTOP_CTL_F0TPE, (config->rxFIFO0Config->topPointerLogicEnabled) ? 1UL : 0UL) |
            _VAL2FLD(CANFD_CH_RXFTOP_CTL_F1TPE, (config->rxFIFO1Config->topPointerLogicEnabled) ? 1UL : 0UL);

            /* Set the start address of the Rx buffer in Message RAM */
            CANFD_RXBC(base, chan) =
            _VAL2FLD(CANFD_CH_M_TTCAN_RXBC_RBSA, _FLD2VAL(CANFD_CH_M_TTCAN_RXF1C_F1SA, CANFD_RXF1C(base, chan)) +
                                     (config->rxFIFO1Config->numberOfFIFOElements *
                                     (CY_CANFD_R0_R1_SIZE + dataBufferSizeInWord[config->rxFIFO1DataSize])));

            /* Configure Tx Buffer and Tx FIFO/Queue */
            CANFD_TXESC(base, chan) = _VAL2FLD(CANFD_CH_M_TTCAN_TXESC_TBDS, config->txBufferDataSize);

            /* Set Tx FIFO/QUEUE (not used):
             *  The Watermark interrupt disabled
             *  Tx Event FIFO disabled
             *  The start address of Tx Event FIFO in Message RAM
            */
            CANFD_TXEFC(base, chan) =
            _VAL2FLD(CANFD_CH_M_TTCAN_TXEFC_EFWM, 0UL) |
            _VAL2FLD(CANFD_CH_M_TTCAN_TXEFC_EFS, 0UL)  |
            _VAL2FLD(CANFD_CH_M_TTCAN_TXEFC_EFSA, _FLD2VAL(CANFD_CH_M_TTCAN_RXBC_RBSA, CANFD_RXBC(base, chan)) +
                                                          (config->noOfRxBuffers * (CY_CANFD_R0_R1_SIZE +
                                                           dataBufferSizeInWord[config->rxBufferDataSize])));

            /* Update Tx buffer configuration:
             *  The Tx FIFO operation
             *  No Tx FIFO/Queue
             *  The number of Dedicated Tx Buffers
             *  Reserve memory for 10 Tx Event FIFO elements for easy use in future
             */
            CANFD_TXBC(base, chan) =
            _VAL2FLD(CANFD_CH_M_TTCAN_TXBC_TFQM, 0UL) |
            _VAL2FLD(CANFD_CH_M_TTCAN_TXBC_TFQS, 0UL) |
            _VAL2FLD(CANFD_CH_M_TTCAN_TXBC_NDTB, config->noOfTxBuffers) |
            _VAL2FLD(CANFD_CH_M_TTCAN_TXBC_TBSA, _FLD2VAL(CANFD_CH_M_TTCAN_TXEFC_EFSA, CANFD_TXEFC(base, chan)) +
                                                                     (CY_CANFD_TX_EVENT_FIFO_ELEMENTS_NUM *
                                                                      CY_CANFD_SIZE_OF_TXEVENT_FIFO_IN_WORD));

            /* Initialize the Message RAM area (Entire region zeroing) for channel */
            address = (volatile uint32_t *)(config->messageRAMaddress);
            sizeInWord = config->messageRAMsize >> CY_CANFD_MRAM_SIGNIFICANT_BYTES_SHIFT;
            for(count = 0UL; count < sizeInWord; count++)
            {
                address[count] = 0UL;
            }

            /* The configuration of the CAN bus */

            /* CCCR register */
            CANFD_CCCR(base, chan) = _VAL2FLD(CANFD_CH_M_TTCAN_CCCR_INIT, 1UL) | /* Keep in initialization state */
                               _VAL2FLD(CANFD_CH_M_TTCAN_CCCR_CCE, 1UL)  | /* Keep CCE to enabled */
                               _VAL2FLD(CANFD_CH_M_TTCAN_CCCR_TXP, 0UL)  | /* Transmit pause disabled */
                               _VAL2FLD(CANFD_CH_M_TTCAN_CCCR_BRSE, ((config->canFDMode) ? 1UL : 0UL)) | /* Bit rate */
                               _VAL2FLD(CANFD_CH_M_TTCAN_CCCR_FDOE, ((config->canFDMode) ? 1UL : 0UL)) | /* FD mode */
                               _VAL2FLD(CANFD_CH_M_TTCAN_CCCR_TEST, 0UL) | /* Normal operation */
                               _VAL2FLD(CANFD_CH_M_TTCAN_CCCR_DAR, 0UL)  | /* Automatic retransmission enabled */
                               _VAL2FLD(CANFD_CH_M_TTCAN_CCCR_MON_, 0UL) | /* Bus Monitoring Mode is disabled */
                               _VAL2FLD(CANFD_CH_M_TTCAN_CCCR_CSR, 0UL)  | /* No clock stop is requested */
                               _VAL2FLD(CANFD_CH_M_TTCAN_CCCR_ASM, 0UL);   /* Normal CAN operation */

            /* The nominal bit timing & prescaler register */
            Cy_CANFD_SetBitrate(base, chan, config->bitrate);

            if (config->canFDMode)
            {
                if (NULL != config->fastBitrate)
                {
                    CY_ASSERT_L2(CY_CANFD_IS_DAT_PRESCALER_VALID(config->fastBitrate->prescaler));
                    CY_ASSERT_L2(CY_CANFD_IS_DAT_TIME_SEG_1_VALID(config->fastBitrate->timeSegment1));
                    CY_ASSERT_L2(CY_CANFD_IS_DAT_TIME_SEG_2_VALID(config->fastBitrate->timeSegment2));
                    CY_ASSERT_L2(CY_CANFD_IS_DAT_SYNC_JUMP_WIDTH_VALID(config->fastBitrate->syncJumpWidth));

                    /* Set data bit timing & prescaler */
                    Cy_CANFD_SetFastBitrate(base, chan, config->fastBitrate);
                }
                else
                {
                   ret = CY_CANFD_BAD_PARAM;
                }

                if ((NULL != config->tdcConfig) && (ret != CY_CANFD_BAD_PARAM))
                {
                    CY_ASSERT_L2(CY_CANFD_IS_TDCO_VALID(config->tdcConfig->tdcOffset));
                    CY_ASSERT_L2(CY_CANFD_IS_TDCF_VALID(config->tdcConfig->tdcFilterWindow));

                    /* Transmitter delay compensation */
                    Cy_CANFD_SetTDC(base, chan, config->tdcConfig);
                }
                else
                {
                   ret = CY_CANFD_BAD_PARAM;
                }
            }

            if (ret != CY_CANFD_BAD_PARAM)
            {
                /* The configuration of a global filter */
                CANFD_GFC(base, chan) =
                _VAL2FLD(CANFD_CH_M_TTCAN_GFC_ANFS, config->globalFilterConfig->nonMatchingFramesStandard) |
                _VAL2FLD(CANFD_CH_M_TTCAN_GFC_ANFE, config->globalFilterConfig->nonMatchingFramesExtended) |
                _VAL2FLD(CANFD_CH_M_TTCAN_GFC_RRFS, ((config->globalFilterConfig->rejectRemoteFramesStandard) ? 1UL : 0UL))|
                _VAL2FLD(CANFD_CH_M_TTCAN_GFC_RRFE, ((config->globalFilterConfig->rejectRemoteFramesExtended) ? 1UL : 0UL));

                if (0U != config->sidFilterConfig->numberOfSIDFilters)
                {
                    /* Standard Message ID filters */
                    Cy_CANFD_SidFiltersSetup(base, chan, config->sidFilterConfig, context);
                }

                if(0U   != config->extidFilterConfig->numberOfEXTIDFilters)
                {
                    /* Extended Message ID filters */
                    Cy_CANFD_XidFiltersSetup(base, chan,  config->extidFilterConfig, context);
                }

                /* Configure the interrupt */
                Cy_CANFD_SetInterruptMask(base, chan, CY_CANFD_INTERRUPT_ENABLE_DEFAULT);

                /* Enable TX complete interrupts for used TX buffers */
                CANFD_TXBTIE(base, chan) = (uint32_t)(~(0xFFFFFFFFUL << config->noOfTxBuffers));

                /* Set interrupt line 0 */
                Cy_CANFD_SetInterruptLine(base, chan, 0UL);

                /* Enable interrupt line 0 */
                Cy_CANFD_EnableInterruptLine(base, chan, CANFD_CH_M_TTCAN_ILE_EINT0_Msk);

                /* Clear CCCR_INIT bit and wait until it is updated to finalize CAN FD initialization */
                ret = Cy_CANFD_ConfigChangesDisable(base, chan);
            }
        }
        else
        {
           ret = CY_CANFD_ERROR_TIMEOUT;
        }
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_CANFD_DeInit
****************************************************************************//**
*
*  De-initializes the CAN FD block, returns registers values to default.
*
* \note Do not call Cy_CANFD_Disable before Cy_CANFD_DeInit.
* \note Call this function only after all debug messages reception is completed.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
*  The CAN FD channel number.
*
* \param *context
* The pointer to the context structure \ref cy_stc_canfd_context_t allocated
* by the user. The structure is used during the CAN FD operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
*
* \return
* \ref cy_en_canfd_status_t
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_DeInit
*
*******************************************************************************/
cy_en_canfd_status_t Cy_CANFD_DeInit(CANFD_Type *base, uint32_t chan, cy_stc_canfd_context_t *context)
{
    volatile uint32_t* address;
    uint32_t  retry = CY_CANFD_RETRY_COUNT;
    uint32_t  count;
    uint32_t  sizeInWord;
    cy_en_canfd_status_t ret = CY_CANFD_ERROR_TIMEOUT;

    /* Reset the notification callback functions */
    context->canFDInterruptHandling.canFDTxInterruptFunction = NULL;
    context->canFDInterruptHandling.canFDRxInterruptFunction = NULL;
    context->canFDInterruptHandling.canFDErrorInterruptFunction = NULL;

    /* Set the CCCR_INIT bit and wait until it is updated */
    CANFD_CCCR(base, chan) = CANFD_CH_M_TTCAN_CCCR_INIT_Msk;

    while ((retry > 0UL) && !_FLD2BOOL(CANFD_CH_M_TTCAN_CCCR_INIT, CANFD_CCCR(base, chan)))
    {
        Cy_SysLib_DelayUs(CY_CANFD_INIT_TIMEOUT_US);
        retry--;
    }

    if (retry > 0UL)
    {
        /* Enable configuration changes */
        CANFD_CCCR(base, chan) |= CANFD_CH_M_TTCAN_CCCR_CCE_Msk;

        /* Standard ID filter */
        CANFD_SIDFC(base, chan) = 0UL;

        /* Extended ID filter */
        CANFD_XIDFC(base, chan) = 0UL;

        /* Extended ID AND Mask */
        CANFD_XIDAM(base, chan) = CANFD_CH_M_TTCAN_XIDAM_EIDM_Msk;

        /* Configuration of Rx Buffer and Rx FIFO */
        CANFD_RXESC(base, chan) = 0UL;

        /* Rx FIFO 0 */
        CANFD_RXF0C(base, chan) = 0UL;

        /* Rx FIFO 1 */
        CANFD_RXF1C(base, chan) = 0UL;

        /* Rx FIFO Top pointer logic*/
        CANFD_RXFTOP_CTL(base, chan) = 0UL;

        /* Rx buffer */
        CANFD_RXBC(base, chan) = 0UL;

        /* Configuration of Tx Buffer and Tx FIFO/Queue */
        CANFD_TXESC(base, chan) = 0UL;

        /* Tx FIFO/QUEUE (not used) */
        CANFD_TXEFC(base, chan) = 0UL;

        /* Tx buffer */
        CANFD_TXBC(base, chan) = 0UL;

        /* Initialize the Message RAM area (Entire region zeroing) for the channel */
        address = (volatile uint32_t *)(context->messageRAMaddress);
        sizeInWord = context->messageRAMsize >> CY_CANFD_MRAM_SIGNIFICANT_BYTES_SHIFT;
        for(count = 0UL; count < sizeInWord; count++)
        {
            address[count] = 0UL;
        }

        /* The configuration of the CAN bus */

        /* Keep the initialization and configuration change enabled */
        CANFD_CCCR(base, chan) = CANFD_CH_M_TTCAN_CCCR_INIT_Msk | CANFD_CH_M_TTCAN_CCCR_CCE_Msk;

        /* Set the nominal bit timing & prescaler register to the default value */
        CANFD_NBTP(base, chan) = CANFD_NBTP_DEF_VAL;

        /* Set the data bit timing & prescaler register to the default value */
        CANFD_DBTP(base, chan) = CANFD_DBTP_DEF_VAL;

        /* Transmitter delay compensation */
        CANFD_TDCR(base, chan) = 0UL;

        /* The configuration of a global filter */
        CANFD_GFC(base, chan) = 0UL;

        /* Enable interrupt configuration */
        CANFD_IE(base, chan) = 0UL;

        /* Select interrupt line configuration */
        CANFD_ILS(base, chan) = 0UL;

        /* Enable the interrupt line configuration */
        CANFD_ILE(base, chan) = 0UL;

        ret = CY_CANFD_SUCCESS;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_CANFD_GetLastError
****************************************************************************//**
*
*  Returns the value of Protocol Status Register (PSR). \n
*  Use the \ref group_canfd_last_state_masks to extract necessary fields from
*  the register. \n
*  Use the \ref cy_en_canfd_LEC_t enumeration to interpret LEC and DLEC fields. \n
*  Use the \ref cy_en_canfd_PSR_ACT_t enumeration to interpret the  ACT field.
*
* \note Protocol Status Register has reset on read fields. Reading the register
*  will clear the bits PXE, RFDF, RBRS and RESI, and set DLEC[2:0] and LEC[2:0].
*
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
*  The CAN FD channel number.
*
* \return
*  Content of the Protocol Status Register (PSR).
*
*******************************************************************************/
uint32_t Cy_CANFD_GetLastError(CANFD_Type const *base, uint32_t chan)
{
    return CANFD_PSR(base, chan);
}


/*******************************************************************************
* Function Name: Cy_CANFD_CalcRxBufAdrs
****************************************************************************//**
*
*  Calculates the address of the RX buffer element.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
* The CAN FD channel number.
*
* \param index
* The message buffer index for reception (0-63).
*
* \param context
* The pointer to the context structure \ref cy_stc_canfd_context_t allocated
* by the user. The structure is used during the CAN FD operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
*
* \return
* The message buffer address corresponding to the index. Can be 0 if the index
* is invalid.
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_GetRxBuffer
*
*******************************************************************************/
uint32_t  Cy_CANFD_CalcRxBufAdrs(CANFD_Type const *base, uint32_t chan,
                                uint32_t index,
                                cy_stc_canfd_context_t const *context)
{
    uint32_t address;

    if (index > (CY_CANFD_MESSAGE_RX_BUFFERS_MAX_CNT - 1UL))
    {
        /* Sets 0 to the return value if the index is invalid */
        address = 0UL;
    }
    else
    {
        /* Sets the message buffer address to the return value if the index is available  */
        address = context->messageRAMaddress;
        address += (_FLD2VAL(CANFD_CH_M_TTCAN_RXBC_RBSA, CANFD_RXBC(base, chan))
                     * sizeof(uint32_t));  /* Convert the word to the byte offset */
        address += index * (CY_CANFD_R0_R1_SIZE +
                            dataBufferSizeInWord[_FLD2VAL(CANFD_CH_M_TTCAN_RXESC_RBDS, CANFD_RXESC(base, chan))])*
                            sizeof(uint32_t);   /* Convert the word to the byte offset */
    }
    return address;
}


/*******************************************************************************
* Function Name: Cy_CANFD_CalcTxBufAdrs
****************************************************************************//**
*
*  Calculates the address of the TX buffer element.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
* The CAN FD channel number.
*
* \param index
* The Message buffer index for the transmission (0-31).
*
* \param context
* The pointer to the context structure \ref cy_stc_canfd_context_t allocated
* by the user. The structure is used during the CAN FD operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
*
* \return
* The Message buffer address corresponding to the index.
* Can be 0 if the index is invalid.
*
*******************************************************************************/
static uint32_t Cy_CANFD_CalcTxBufAdrs(CANFD_Type const *base, uint32_t chan, uint32_t index, cy_stc_canfd_context_t const *context)
{
    uint32_t address = 0UL;

    /* Set the message buffer address to the return value if the index is available */
    address = context->messageRAMaddress;
    address += (_FLD2VAL(CANFD_CH_M_TTCAN_TXBC_TBSA, CANFD_TXBC(base, chan))  /* Tx 32-bit Start Address */
                * sizeof(uint32_t));  /* Convert the word to the byte offset */

    if (index < (CY_CANFD_MESSAGE_TX_BUFFERS_MAX_CNT))
    {
        address += index * (CY_CANFD_T0_T1_SIZE +
                            dataBufferSizeInWord[_FLD2VAL(CANFD_CH_M_TTCAN_TXESC_TBDS, CANFD_TXESC(base, chan))]) *
                            sizeof(uint32_t);   /* Converts the word to the byte offset */
    }
    else
    {
        address = 0UL;
    }

    return address;
}


/*******************************************************************************
* Function Name: Cy_CANFD_CalcRxFifoAdrs
****************************************************************************//**
*
*  Calculates the address of the RX FIFO element.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
* The CAN FD channel number.
*
* \param fifoNumber
* The FIFO number (0 or 1).
*
* \param index
* The Message buffer index for the reception (0-63).
*
* \param context
* The pointer to the context structure \ref cy_stc_canfd_context_t allocated
* by the user. The structure is used during the CAN FD operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
*
* \return
* The Message buffer address corresponding to the index.
* Can be 0 if the index is invalid.
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_GetRxBuffer
*
*******************************************************************************/
uint32_t Cy_CANFD_CalcRxFifoAdrs(CANFD_Type const *base, uint32_t chan,
                                 uint32_t fifoNumber,
                                 uint32_t index,
                                 cy_stc_canfd_context_t const *context)
{
    uint32_t address = 0UL;
    CY_ASSERT_L2(CY_CANFD_IS_FIFO_NUM_VALID(index));
    if(fifoNumber <= CY_CANFD_RX_FIFO1)
    {
        /* Sets the message buffer address to the return value if the index is available */
        address = context->messageRAMaddress;
        address += (((CY_CANFD_RX_FIFO0 == fifoNumber) ?
                     _FLD2VAL(CANFD_CH_M_TTCAN_RXF0C_F0SA, CANFD_RXF0C(base, chan)) :  /* Rx FIFO 0 32-bit Start Address */
                     _FLD2VAL(CANFD_CH_M_TTCAN_RXF1C_F1SA, CANFD_RXF1C(base, chan)))   /* Rx FIFO 1 32-bit Start Address */
                     * sizeof(uint32_t));  /* Convert the word to the byte offset */
        address += index * (CY_CANFD_R0_R1_SIZE +
                            dataBufferSizeInWord[(CY_CANFD_RX_FIFO0 == fifoNumber) ?
                                                 _FLD2VAL(CANFD_CH_M_TTCAN_RXESC_F0DS, CANFD_RXESC(base, chan)) :
                                                 _FLD2VAL(CANFD_CH_M_TTCAN_RXESC_F1DS, CANFD_RXESC(base, chan))]) *
                           sizeof(uint32_t);   /* Converts the word to the byte offset */
    }

    return address;
}


/*******************************************************************************
* Function Name: Cy_CANFD_SidFilterSetup
****************************************************************************//**
*
* Updates the Standard Message ID Filter Element configuration in Message RAM.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
* The CAN FD channel number.
*
* \param *filter
*  The SID Filter register element structure.
*
* \param index
*  The SID filter index.
*
* \param *context
* The pointer to the context structure \ref cy_stc_canfd_context_t allocated
* by the user. The structure is used during the CAN FD operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_SidFilterSetup
*
*******************************************************************************/
void Cy_CANFD_SidFilterSetup(CANFD_Type const *base, uint32_t chan,
                             const cy_stc_id_filter_t *filter,
                             uint32_t index,
                             cy_stc_canfd_context_t const *context)
{
    uint32_t *filterAddr;

    if ((NULL != filter) && (NULL != context))
    {
        CY_ASSERT_L2(CY_CANFD_IS_SFID_VALID(filter->sfid2));
        CY_ASSERT_L2(CY_CANFD_IS_SFID_VALID(filter->sfid1));
        CY_ASSERT_L3(CY_CANFD_IS_SFEC_VALID(filter->sfec));
        CY_ASSERT_L3(CY_CANFD_IS_SFT_VALID(filter->sft));
        CY_ASSERT_L2(CY_CANFD_IS_SID_FILTERS_VALID(index + 1U));

        /* The Standard Message ID Filter address */
        filterAddr = (uint32_t *)(context->messageRAMaddress +
                                   (_FLD2VAL(CANFD_CH_M_TTCAN_SIDFC_FLSSA, CANFD_SIDFC(base, chan))
                                     << CY_CANFD_MRAM_SIGNIFICANT_BYTES_SHIFT));

        /* The Standard Message ID Filter element address */
        filterAddr += index;

        /* Configuration of Rx Buffer and Rx FIFO */
        *filterAddr = _VAL2FLD(CY_CANFD_SID_FILTER_S0_SFID2, filter->sfid2) | /* Standard Filter ID 2 */
                      _VAL2FLD(CY_CANFD_SID_FILTER_S0_SFID1, filter->sfid1) | /* Standard Filter ID 1 */
                      _VAL2FLD(CY_CANFD_SID_FILTER_S0_SFEC , filter->sfec)  | /* Standard Filter Element Configuration*/
                      _VAL2FLD(CY_CANFD_SID_FILTER_S0_SFT, filter->sft);      /* Standard Filter Type */
    }
}


/*******************************************************************************
* Function Name: Cy_CANFD_SidFiltersSetup
****************************************************************************//**
*
*  Updates the Standard Message ID Filters configuration in Message RAM.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
*  The CAN FD channel number.
*
* \param filterConfig
*  The Standard ID filter configuration structure.
*
* \param context
* The pointer to the context structure \ref cy_stc_canfd_context_t allocated
* by the user. The structure is used during the CAN FD operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
*
*******************************************************************************/
void Cy_CANFD_SidFiltersSetup(CANFD_Type const *base, uint32_t chan,
                              const cy_stc_canfd_sid_filter_config_t *filterConfig,
                              cy_stc_canfd_context_t const *context)
{
    uint32_t index;

    if ((NULL != filterConfig) && (NULL != context))
    {
        CY_ASSERT_L2(CY_CANFD_IS_SID_FILTERS_VALID(filterConfig->numberOfSIDFilters));

        for (index = 0UL; index < filterConfig->numberOfSIDFilters; index++)
        {
            Cy_CANFD_SidFilterSetup(base, chan, (filterConfig->sidFilter + index), index, context);
        }
    }
}


/*******************************************************************************
* Function Name: Cy_CANFD_XidFilterSetup
****************************************************************************//**
*
*  Updates the Extended Message ID Filter Element configuration in Message RAM.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
* The CAN FD channel number.
*
* \param filter
* The XID Filter register element structure.
*
* \param index
*     The XID filter index.
*
* \param context
* The pointer to the context structure \ref cy_stc_canfd_context_t allocated
* by the user. The structure is used during the CAN FD operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_XidFilterSetup
*
*******************************************************************************/
void Cy_CANFD_XidFilterSetup(CANFD_Type const *base, uint32_t chan,
                             const cy_stc_extid_filter_t *filter,
                             uint32_t index,
                             cy_stc_canfd_context_t const *context)
{
    uint32_t* filterAddr;

    if ((NULL != filter) && (NULL != context))
    {
        CY_ASSERT_L2(CY_CANFD_IS_EFID_VALID(filter->f1_f->efid2));
        CY_ASSERT_L2(CY_CANFD_IS_EFID_VALID(filter->f0_f->efid1));
        CY_ASSERT_L3(CY_CANFD_IS_EFEC_VALID(filter->f0_f->efec));
        CY_ASSERT_L3(CY_CANFD_IS_EFT_VALID(filter->f1_f->eft));
        CY_ASSERT_L2(CY_CANFD_IS_XID_FILTERS_VALID(index + 1U));

        /* The Extended Message ID Filter address */
        filterAddr = (uint32_t *)(context->messageRAMaddress +
                                (_FLD2VAL(CANFD_CH_M_TTCAN_XIDFC_FLESA, CANFD_XIDFC(base, chan))
                                  << CY_CANFD_MRAM_SIGNIFICANT_BYTES_SHIFT));

        /* The Extended Message ID Filter element address */
        filterAddr += (index << 1U);  /* The shift to 1 defines F0 and F1 fields */

        /* Configuration of F0 for the Rx Buffer and Rx FIFO filter element */
        *filterAddr = _VAL2FLD(CY_CANFD_XID_FILTER_F0_EFID1, filter->f0_f->efid1) | /* XID Filter ID 1 */
                      _VAL2FLD(CY_CANFD_XID_FILTER_F0_EFEC, filter->f0_f->efec); /* XID Filter Element Configuration */

        /* Increment the address to get the address for F1 */
        filterAddr++;

        /* Configuration of F1 for the Rx Buffer and Rx FIFO filter element */
        *filterAddr = _VAL2FLD(CY_CANFD_XID_FILTER_F1_EFID2, filter->f1_f->efid2) | /* XID Filter ID 2 */
                      _VAL2FLD(CY_CANFD_XID_FILTER_F1_ETF, filter->f1_f->eft);     /* XID Filter Type */
    }
}


/*******************************************************************************
* Function Name: Cy_CANFD_XidFiltersSetup
****************************************************************************//**
*
*  Updates the Extended Message ID Filters configuration in Message RAM.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
* The CAN FD channel number.
*
* \param filterConfig
* The Extended ID filter configuration structure.
*
* \param context
* The pointer to the context structure \ref cy_stc_canfd_context_t allocated
* by the user. The structure is used during the CAN FD operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
*
*******************************************************************************/
void Cy_CANFD_XidFiltersSetup(CANFD_Type const *base, uint32_t chan,
                              const cy_stc_canfd_extid_filter_config_t *filterConfig,
                              cy_stc_canfd_context_t const *context)
{
    uint32_t index;

    if ((NULL != filterConfig) && (NULL != context))
    {
        CY_ASSERT_L2(CY_CANFD_IS_XID_FILTERS_VALID(filterConfig->numberOfEXTIDFilters));

        for (index = 0UL; index < filterConfig->numberOfEXTIDFilters; index++)
        {
            Cy_CANFD_XidFilterSetup(base, chan, (filterConfig->extidFilter + index), index, context);
        }
    }
}


/*******************************************************************************
* Function Name: Cy_CANFD_GetRxBuffer
****************************************************************************//**
*
* Extracts the RX Buffer from Message RAM.
*
* \note Remember to clear the NDAT register bits after the RX buffer is read.
* \note Remember to acknowledge the FIFO buffer after reading one FIFO element.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
* The CAN FD channel number.
*
* \param bufferAddress
*  The Rx, FIFO 0 or FIFO 1 Buffer element address in CAN Message RAM.
*
* \param *rxBuffer
*  The Rx Buffer structure in RAM.
*
* \return
* \ref cy_en_canfd_status_t
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_GetRxBuffer
*
*******************************************************************************/
cy_en_canfd_status_t Cy_CANFD_GetRxBuffer(CANFD_Type const *base, uint32_t chan,
                                          const uint32_t bufferAddress,
                                          cy_stc_canfd_rx_buffer_t const *rxBuffer)
{
    cy_en_canfd_status_t ret = CY_CANFD_BAD_PARAM;
    volatile const uint32_t* address = (uint32_t*)bufferAddress;
    uint32_t count    = 0UL;
    uint32_t dlcIndex = 0UL;

    (void)base; /* Suppress warning */
    (void)chan; /* Suppress warning */

    /* Checks for the NULL pointers */
    if (NULL != rxBuffer)
    {
        if ((NULL != rxBuffer->r0_f) && (NULL != rxBuffer->r1_f) &&
            (NULL != rxBuffer->data_area_f))
        {
            rxBuffer->r0_f->id = _FLD2VAL(CY_CANFD_RX_BUFFER_R0_ID, *address);
            rxBuffer->r0_f->rtr = (cy_en_canfd_rtr_t)((uint32_t)_FLD2VAL(CY_CANFD_RX_BUFFER_R0_RTR, *address));
            rxBuffer->r0_f->xtd = (cy_en_canfd_xtd_t)((uint32_t)_FLD2VAL(CY_CANFD_RX_BUFFER_R0_XTD, *address));
            rxBuffer->r0_f->esi = (cy_en_canfd_esi_t)((uint32_t)_FLD2VAL(CY_CANFD_RX_BUFFER_R0_ESI, *address));

            address++;
            rxBuffer->r1_f->rxts = _FLD2VAL(CY_CANFD_RX_BUFFER_R1_RXTS, *address);
            rxBuffer->r1_f->dlc = _FLD2VAL(CY_CANFD_RX_BUFFER_R1_DLC, *address);
            rxBuffer->r1_f->brs = _FLD2BOOL(CY_CANFD_RX_BUFFER_R1_BRS, *address);
            rxBuffer->r1_f->fdf = (cy_en_canfd_fdf_t)((uint32_t)_FLD2VAL(CY_CANFD_RX_BUFFER_R1_FDF, *address));
            rxBuffer->r1_f->fidx = _FLD2VAL(CY_CANFD_RX_BUFFER_R1_FIDX, *address);
            rxBuffer->r1_f->anmf = (cy_en_canfd_anmf_t)((uint32_t)_FLD2VAL(CY_CANFD_RX_BUFFER_R1_ANMF, *address));

            /* ID : Shifts a standard RxID to its position */
            if (rxBuffer->r0_f->xtd == CY_CANFD_XTD_STANDARD_ID)
            {
                rxBuffer->r0_f->id >>= CY_CANFD_EXT_IDENTIFIER_LENGTH;
            }

            /* Copies the 0-64 byte of the data area */
            if (rxBuffer->r1_f->dlc > CY_CANFD_CLASSIC_CAN_DATA_LENGTH)
            {
                dlcIndex = (uint32_t)(rxBuffer->r1_f->dlc - CY_CANFD_CLASSIC_CAN_DATA_LENGTH);
            }

            for (count = 0UL; count < (uint32_t)dataBufferSizeInWord[dlcIndex]; count++)
            {
                address++;
                rxBuffer->data_area_f[count] = *address;
            }

            ret = CY_CANFD_SUCCESS;
        }
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_CANFD_GetFIFOTop
****************************************************************************//**
*
* Extracts one RX FIFO Buffer element using the FIFO TOP register logic.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
* The CAN FD channel number.
*
* \param FIFONumber
*  The CY_CANFD_RX_FIFO0 or CY_CANFD_RX_FIFO1, FIFO Buffer number.
*
* \param *rxBuffer
*  The Rx Buffer structure in RAM.
*
* \return
* \ref cy_en_canfd_status_t
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_GetFIFOTop
*
*******************************************************************************/
cy_en_canfd_status_t Cy_CANFD_GetFIFOTop(CANFD_Type const *base, uint32_t chan,
                                          const uint8_t FIFONumber,
                                          cy_stc_canfd_rx_buffer_t const *rxBuffer)
{
    cy_en_canfd_status_t ret = CY_CANFD_BAD_PARAM;
    volatile const uint32_t* address;
    uint32_t count    = 0UL;
    uint32_t dataSize = 0UL;
    uint32_t tmpregister = 0UL;

    /* Checks for the NULL pointers */
    if (NULL != rxBuffer)
    {
        if ((NULL != rxBuffer->r0_f) && (NULL != rxBuffer->r1_f) &&
            (NULL != rxBuffer->data_area_f))
        {
            /* Selects a corresponding FIFO TOP address and FIFO element size */
            if (CY_CANFD_RX_FIFO0 == FIFONumber)
            {
                address = (uint32_t*)&CANFD_RXFTOP0_DATA(base, chan);
                dataSize = (uint32_t)dataBufferSizeInWord[_FLD2VAL(CANFD_CH_M_TTCAN_RXESC_F0DS,
                                                          CANFD_RXESC(base, chan))];
            }
            else
            {
                address = (uint32_t*)&CANFD_RXFTOP1_DATA(base, chan);
                dataSize = (uint32_t)dataBufferSizeInWord[_FLD2VAL(CANFD_CH_M_TTCAN_RXESC_F1DS,
                                                          CANFD_RXESC(base, chan))];
            }

            tmpregister = *address; /* The FIFO Read pointer is post-incremented by the HW */
            rxBuffer->r0_f->id = _FLD2VAL(CY_CANFD_RX_BUFFER_R0_ID, tmpregister);
            rxBuffer->r0_f->rtr = (cy_en_canfd_rtr_t)((uint32_t)_FLD2VAL(CY_CANFD_RX_BUFFER_R0_RTR, tmpregister));
            rxBuffer->r0_f->xtd = (cy_en_canfd_xtd_t)((uint32_t)_FLD2VAL(CY_CANFD_RX_BUFFER_R0_XTD, tmpregister));
            rxBuffer->r0_f->esi = (cy_en_canfd_esi_t)((uint32_t)_FLD2VAL(CY_CANFD_RX_BUFFER_R0_ESI, tmpregister));

            tmpregister = *address; /* The FIFO Read pointer is post-incremented by the HW */
            rxBuffer->r1_f->rxts = _FLD2VAL(CY_CANFD_RX_BUFFER_R1_RXTS, tmpregister);
            rxBuffer->r1_f->dlc = _FLD2VAL(CY_CANFD_RX_BUFFER_R1_DLC, tmpregister);
            rxBuffer->r1_f->brs = _FLD2BOOL(CY_CANFD_RX_BUFFER_R1_BRS, tmpregister);
            rxBuffer->r1_f->fdf = (cy_en_canfd_fdf_t)((uint32_t)_FLD2VAL(CY_CANFD_RX_BUFFER_R1_FDF, tmpregister));
            rxBuffer->r1_f->fidx = _FLD2VAL(CY_CANFD_RX_BUFFER_R1_FIDX, tmpregister);
            rxBuffer->r1_f->anmf = (cy_en_canfd_anmf_t)((uint32_t)_FLD2VAL(CY_CANFD_RX_BUFFER_R1_ANMF, tmpregister));

            /* ID : Shifts a standard RxID to its position */
            if (rxBuffer->r0_f->xtd == CY_CANFD_XTD_STANDARD_ID)
            {
                rxBuffer->r0_f->id >>= CY_CANFD_EXT_IDENTIFIER_LENGTH;
            }

            /* Copies the whole data area of one FIFO element */
            for (count = 0UL; count < dataSize; count++)
            {
                rxBuffer->data_area_f[count] = *address; /* The FIFO read pointer is post-incremented by the HW */
            }

            ret = CY_CANFD_SUCCESS;
        }
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_CANFD_ExtractMsgFromRXBuffer
****************************************************************************//**
*
* Extracts one RX buffer or one FIFO buffer element.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
* The CAN FD channel number.
*
* \param rxFIFOMsg
*  The buffer to read: True for FIFO buffers and False for RX buffers.
*
* \param msgBufOrRxFIFONum
*  The RX buffer element index or FIFO buffer number.
*
* \param *rxBuffer
*  The Rx buffer structure in RAM.
*
* \param context
* The pointer to the context structure \ref cy_stc_canfd_context_t allocated
* by the user. The structure is used during the CAN FD operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
*
* \return
* \ref cy_en_canfd_status_t
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_ExtractMsgFromRXBuffer
*
*******************************************************************************/
cy_en_canfd_status_t Cy_CANFD_ExtractMsgFromRXBuffer(CANFD_Type *base, uint32_t chan,
                                                     bool rxFIFOMsg, uint8_t msgBufOrRxFIFONum,
                                                     cy_stc_canfd_rx_buffer_t const *rxBuffer,
                                                     cy_stc_canfd_context_t const *context)
{
    cy_en_canfd_status_t ret = CY_CANFD_BAD_PARAM;
    uint32_t address = 0UL;
    if (rxFIFOMsg)
    {
        /* Reading from the FIFO buffer */
        if (0U == msgBufOrRxFIFONum)
        {
            /* FIFO0 is used */
            if (_FLD2BOOL(CANFD_CH_RXFTOP_CTL_F0TPE, CANFD_RXFTOP_CTL(base, chan)))   /* The RxFifo Top pointer logic is used. */
            {
                /* Gets data from the FIFO top register. The Read address is incremented by HW */
                ret = Cy_CANFD_GetFIFOTop(base, chan, CY_CANFD_RX_FIFO0, rxBuffer);

            }
            else        /* The RxFifo Top pointer logic is not used */
            {
                address = Cy_CANFD_CalcRxFifoAdrs(base, chan,
                                                  CY_CANFD_RX_FIFO0,
                                                  _FLD2VAL(CANFD_CH_M_TTCAN_RXF0S_F0GI, CANFD_RXF0S(base, chan)),
                                                  context);

                if (0UL != address)
                {
                    /* Extracts the received message from the buffer */
                    ret = Cy_CANFD_GetRxBuffer(base, chan, address, rxBuffer);

                    /* Acknowledges the FIFO message */
                    CANFD_RXF0A(base, chan) = _CLR_SET_FLD32U(CANFD_RXF0A(base, chan),
                                                        CANFD_CH_M_TTCAN_RXF0A_F0AI,
                                                        _FLD2VAL(CANFD_CH_M_TTCAN_RXF0S_F0GI, CANFD_RXF0S(base, chan)));
                }
            }
        }
        else
        {
            /* FIFO1 is used */
            if (_FLD2BOOL(CANFD_CH_RXFTOP_CTL_F1TPE, CANFD_RXFTOP_CTL(base, chan)))  /* The RxFifo Top pointer logic is used. */
            {
                /* Gets data from the FIFO top register. The Read address is incremented by the HW */
                ret = Cy_CANFD_GetFIFOTop(base, chan, CY_CANFD_RX_FIFO1, rxBuffer);
            }
            else        /* The RxFifo Top pointer logic is not used */
            {
                address = Cy_CANFD_CalcRxFifoAdrs(base, chan,
                                                  CY_CANFD_RX_FIFO1,
                                                  _FLD2VAL(CANFD_CH_M_TTCAN_RXF1S_F1GI, CANFD_RXF1S(base, chan)),
                                                  context);

                if(0UL != address)
                {
                    ret = Cy_CANFD_GetRxBuffer(base, chan, address, rxBuffer);

                    /* Acknowledges the FIFO message */
                    CANFD_RXF1A(base, chan) = _CLR_SET_FLD32U(CANFD_RXF1A(base, chan),
                                                        CANFD_CH_M_TTCAN_RXF1A_F1AI,
                                                        _FLD2VAL(CANFD_CH_M_TTCAN_RXF1S_F1GI, CANFD_RXF1S(base, chan)));
                }
            }
        }
    }
    else
    {
        /* Reads from the dedicated RX buffer */
        address = Cy_CANFD_CalcRxBufAdrs(base, chan, msgBufOrRxFIFONum, context);

        if (0UL != address)
        {
            /* Extracts the received message from the buffer */
            ret = Cy_CANFD_GetRxBuffer(base, chan, address, rxBuffer);

            if (msgBufOrRxFIFONum < CY_CANFD_MESSAGE_HALF_OF_RX_BUFFERS)
            {
                /* Clears the NDAT1 register */
                CANFD_NDAT1(base, chan) = (1UL << (msgBufOrRxFIFONum));
            }
            else
            {
                /* Clears the NDAT2 register */
                CANFD_NDAT2(base, chan) = (1UL << (msgBufOrRxFIFONum - (CY_CANFD_MESSAGE_HALF_OF_RX_BUFFERS)));
            }
        }
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_CANFD_AckRxBuf
****************************************************************************//**
*
*  Acknowledges the data reading and makes the buffer element available for
*  a next message.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
*     The CAN FD channel number.
*
* \param bufNum
*    The RX buffer element index.
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_GetRxBuffer
*
*******************************************************************************/
void Cy_CANFD_AckRxBuf(CANFD_Type *base, uint32_t chan, uint32_t bufNum)
{
    CY_ASSERT_L2(CY_CANFD_IS_RX_BUF_NUM_VALID(bufNum));
    if (bufNum < CY_CANFD_MESSAGE_HALF_OF_RX_BUFFERS)
    {
        /* Clears the NDAT1 register */
        CANFD_NDAT1(base, chan) = (1UL << (bufNum));
    }
    else
    {
        /* Clears the NDAT2 register */
        CANFD_NDAT2(base, chan) = (1UL << (bufNum - (CY_CANFD_MESSAGE_HALF_OF_RX_BUFFERS)));
    }
}


/*******************************************************************************
* Function Name: Cy_CANFD_AckRxFifo
****************************************************************************//**
*
*  Acknowledges the data reading and makes the buffer element available for
*  a next message.
* \note Do not use this function with Cy_CANFD_GetFIFOTop(). FIFO top logic
*  takes care on updating the FIFO read pointer buffer with hardware.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
*  The CAN FD channel number.
*
* \param FIFOnumber
*  The RX buffer element index.
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_GetRxBuffer
*
*******************************************************************************/
void Cy_CANFD_AckRxFifo(CANFD_Type *base, uint32_t chan, uint32_t FIFOnumber)
{
    switch (FIFOnumber)
    {
        case CY_CANFD_RX_FIFO0:
            /* Acknowledges the FIFO message */
            CANFD_RXF0A(base, chan) = _CLR_SET_FLD32U(CANFD_RXF0A(base, chan),
                                                CANFD_CH_M_TTCAN_RXF0A_F0AI,
                                                _FLD2VAL(CANFD_CH_M_TTCAN_RXF0S_F0GI, CANFD_RXF0S(base, chan)));
            break;
        case CY_CANFD_RX_FIFO1:
            /* Acknowledges the FIFO message */
            CANFD_RXF1A(base, chan) = _CLR_SET_FLD32U(CANFD_RXF1A(base, chan),
                                                CANFD_CH_M_TTCAN_RXF1A_F1AI,
                                                _FLD2VAL(CANFD_CH_M_TTCAN_RXF1S_F1GI, CANFD_RXF1S(base, chan)));
            break;
        default:
            /* Invalid FIFO number */
            break;
    }
}


/*******************************************************************************
* Function Name: Cy_CANFD_IrqHandler
****************************************************************************//**
*
*  CAN FD (Status/Error/Rx/Tx) interrupt ISR.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
*     The CAN FD channel number.
*
* \param context
* The pointer to the context structure \ref cy_stc_canfd_context_t allocated
* by the user. The structure is used during the CAN FD operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
*
*******************************************************************************/
void Cy_CANFD_IrqHandler(CANFD_Type *base, uint32_t chan, cy_stc_canfd_context_t const *context)
{
    uint32_t           address = 0UL;
    uint32_t           messageBufferNumber;
    uint32_t           rxData[CY_CANFD_DATA_ELEMENTS_MAX];
    cy_stc_canfd_r0_t  r0RxBuffer;
    cy_stc_canfd_r1_t  r1RxBuffer;

    cy_stc_canfd_rx_buffer_t rxBuffer =
    {
        /* .r0_f         */ &r0RxBuffer,
        /* .r1_f         */ &r1RxBuffer,
        /* .data_area_f  */ rxData
    };

    /* Other than a Tx/Rx interrupt occurred */
    if (0UL != (Cy_CANFD_GetInterruptStatus(base, chan) & CY_CANFD_ERRORS_MASK))
    {
        /* Calls the callback function if it was set previously */
        if (NULL != context->canFDInterruptHandling.canFDErrorInterruptFunction)
        {
            context->canFDInterruptHandling.canFDErrorInterruptFunction(Cy_CANFD_GetInterruptStatus(base, chan));
        }
        else
        {
            uint32_t status = Cy_CANFD_GetInterruptStatus(base, chan) & CY_CANFD_ERRORS_MASK;
            Cy_CANFD_ClearInterrupt(base, chan, status);
        }
    }

    /* At least one received message must be stored into the Rx Buffer */
    if (CANFD_CH_M_TTCAN_IR_DRX_Msk == (Cy_CANFD_GetInterruptStatus(base, chan) & CANFD_CH_M_TTCAN_IR_DRX_Msk))
    {
        /* Clears the Message stored to the Dedicated Rx Buffer flag */
        Cy_CANFD_ClearInterrupt(base, chan, CANFD_CH_M_TTCAN_IR_DRX_Msk);

        if (0UL != CANFD_NDAT1(base, chan))       /* Message buffers 0-31 */
        {
            for (messageBufferNumber = 0UL;
                 messageBufferNumber < (CY_CANFD_MESSAGE_HALF_OF_RX_BUFFERS);
                 messageBufferNumber++)
            {
                if (0UL != (CANFD_NDAT1(base, chan) & (1UL << messageBufferNumber)))
                {
                    /* Calculates the Rx Buffer address */
                    address = Cy_CANFD_CalcRxBufAdrs(base, chan, messageBufferNumber, context);

                    /* Clears the NDAT1 register */
                    CANFD_NDAT1(base, chan) = (1UL << messageBufferNumber);

                    break;
                }
            }
        }
        else /* Message buffers 32-63 */
        {
            for (messageBufferNumber = CY_CANFD_MESSAGE_HALF_OF_RX_BUFFERS;
                 messageBufferNumber < (CY_CANFD_MESSAGE_HALF_OF_RX_BUFFERS + CY_CANFD_MESSAGE_HALF_OF_RX_BUFFERS);
                 messageBufferNumber++)
            {
                if (0UL != (CANFD_NDAT2(base, chan) & (1UL << (messageBufferNumber - CY_CANFD_MESSAGE_HALF_OF_RX_BUFFERS))))
                {
                    /* Calculates the Rx Buffer address */
                    address = Cy_CANFD_CalcRxBufAdrs(base, chan, messageBufferNumber, context);

                    /* Clears the NDAT2 register */
                    CANFD_NDAT2(base, chan) = (1UL << (messageBufferNumber - (CY_CANFD_MESSAGE_HALF_OF_RX_BUFFERS)));

                    break;
                }
            }
        }

        if (0UL != address)
        {
            /* Extracts the received message from a buffer */
            (void)Cy_CANFD_GetRxBuffer(base, chan, address, &rxBuffer);

            /* After a CAN FD message is received, checks if there is a callback function */
            /* Calls the callback function if it was set previously */
            if (NULL != context->canFDInterruptHandling.canFDRxInterruptFunction)
            {
                context->canFDInterruptHandling.canFDRxInterruptFunction(false, messageBufferNumber, &rxBuffer);
            }
        }
    }
    else if (CANFD_CH_M_TTCAN_IR_RF0N_Msk ==
             (Cy_CANFD_GetInterruptStatus(base, chan) & CANFD_CH_M_TTCAN_IR_RF0N_Msk)) /* New message stored into RxFIFO 0 */
    {
        /* Clears the new message interrupt flag */
        Cy_CANFD_ClearInterrupt(base, chan, CANFD_CH_M_TTCAN_IR_RF0N_Msk);

        while (_FLD2VAL(CANFD_CH_M_TTCAN_RXF0S_F0FL, CANFD_RXF0S(base, chan)) > 0UL)    /* Checks the Rx FIFO 0 fill level */
        {
            if (_FLD2BOOL(CANFD_CH_RXFTOP_CTL_F0TPE, CANFD_RXFTOP_CTL(base, chan)))   /* The RxFifo Top pointer logic is used */
            {
                /* Gets data from the FIFO top register. The Read address is incremented by HW */
                (void)Cy_CANFD_GetFIFOTop(base, chan, CY_CANFD_RX_FIFO0, &rxBuffer);

                /* After a CAN FD message is received, checks if there is a callback function */
                /* Calls the callback function if it was set previously */
                if (NULL != context->canFDInterruptHandling.canFDRxInterruptFunction)
                {
                    context->canFDInterruptHandling.canFDRxInterruptFunction(true, CY_CANFD_RX_FIFO0, &rxBuffer);
                }
            }
            else        /* The RxFifo Top pointer logic is not used */
            {
                address = Cy_CANFD_CalcRxFifoAdrs(base, chan,
                                                  CY_CANFD_RX_FIFO0,
                                                  _FLD2VAL(CANFD_CH_M_TTCAN_RXF0S_F0GI, CANFD_RXF0S(base, chan)),
                                                  context);

                if (0UL != address)
                {
                    /* Extracts the received message from a buffer */
                    (void)Cy_CANFD_GetRxBuffer(base, chan, address, &rxBuffer);

                    /* Acknowledges the FIFO message */
                    CANFD_RXF0A(base, chan) = _CLR_SET_FLD32U(CANFD_RXF0A(base, chan),
                                                        CANFD_CH_M_TTCAN_RXF0A_F0AI,
                                                        _FLD2VAL(CANFD_CH_M_TTCAN_RXF0S_F0GI, CANFD_RXF0S(base, chan)));

                    /* After a CAN FD message received, checks if there is a callback function */
                    /* Calls the callback function if it was set previously */
                    if (NULL != context->canFDInterruptHandling.canFDRxInterruptFunction)
                    {
                        context->canFDInterruptHandling.canFDRxInterruptFunction(true, CY_CANFD_RX_FIFO0, &rxBuffer);
                    }
                }
            }
        }
    }
    else if (CANFD_CH_M_TTCAN_IR_RF1N_Msk ==
             (Cy_CANFD_GetInterruptStatus(base, chan) & CANFD_CH_M_TTCAN_IR_RF1N_Msk)) /* New message stored into RxFIFO 1 */
    {
        /* Clears the new message interrupt flag */
        Cy_CANFD_ClearInterrupt(base, chan, CANFD_CH_M_TTCAN_IR_RF1N_Msk);
        while (_FLD2VAL(CANFD_CH_M_TTCAN_RXF1S_F1FL, CANFD_RXF1S(base, chan)) > 0UL) /* Checks the Rx FIFO 1 fill level */
        {
            if (_FLD2BOOL(CANFD_CH_RXFTOP_CTL_F1TPE, CANFD_RXFTOP_CTL(base, chan)))  /* The RxFifo Top pointer logic is used */
            {
                /* Gets data from the FIFO top register. The Read address is incremented by the HW */
                (void)Cy_CANFD_GetFIFOTop(base, chan, CY_CANFD_RX_FIFO1, &rxBuffer);

                /* After a CAN FD message is received, checks if there is a callback function */
                /* Calls the callback function if it was set previously */
                if (NULL != context->canFDInterruptHandling.canFDRxInterruptFunction)
                {
                    context->canFDInterruptHandling.canFDRxInterruptFunction(true,
                                                                             CY_CANFD_RX_FIFO1,
                                                                             &rxBuffer);
                }
            }
            else        /* The RxFifo Top pointer logic is not used */
            {
                address = Cy_CANFD_CalcRxFifoAdrs(base, chan,
                                                  CY_CANFD_RX_FIFO1,
                                                  _FLD2VAL(CANFD_CH_M_TTCAN_RXF1S_F1GI, CANFD_RXF1S(base, chan)),
                                                  context);

                if(0UL != address)
                {
                    (void)Cy_CANFD_GetRxBuffer(base, chan, address, &rxBuffer);

                    /* Acknowledges the FIFO message */
                    CANFD_RXF1A(base, chan) = _CLR_SET_FLD32U(CANFD_RXF1A(base, chan),
                                                        CANFD_CH_M_TTCAN_RXF1A_F1AI,
                                                        _FLD2VAL(CANFD_CH_M_TTCAN_RXF1S_F1GI, CANFD_RXF1S(base, chan)));

                    /* After a CAN FD message is received, checks if there is a callback function */
                    /* Calls the callback function if it was set previously */
                    if (NULL != context->canFDInterruptHandling.canFDRxInterruptFunction)
                    {
                        context->canFDInterruptHandling.canFDRxInterruptFunction(true,
                                                                                 CY_CANFD_RX_FIFO1,
                                                                                 &rxBuffer);
                    }
                }
            }
        }
    }
    else if (CANFD_CH_M_TTCAN_IR_TC_Msk ==
             (Cy_CANFD_GetInterruptStatus(base, chan) & CANFD_CH_M_TTCAN_IR_TC_Msk)) /* Transmission Completed */
    {
        /* The CAN FD message is successfully transmitted */
        /* Clears the Transmission completed flag */
        Cy_CANFD_ClearInterrupt(base, chan, CANFD_CH_M_TTCAN_IR_TC_Msk);

        /* Calls the callback function if it was set previously */
        if (NULL != context->canFDInterruptHandling.canFDTxInterruptFunction)
        {
            context->canFDInterruptHandling.canFDTxInterruptFunction();
        }
    }
    else
    {
        /* An unused event occurs. Skip it */
    }
}


/*******************************************************************************
* Function Name: Cy_CANFD_TxBufferConfig
****************************************************************************//**
*
* Updates the T0 and T1 Tx buffer element parameters in Message RAM and copies
* data from cy_stc_canfd_tx_buffer_t structure to Message RAM.
* \note Function Cy_CANFD_Init() must be called before setting up an identifier
*  and enabling this message buffer.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
* The CAN FD channel number.
*
* \param *txBuffer
* The Tx Buffer configuration structure.
*
* \param index
* the message buffer index (0-31).
*
* \param context
* The pointer to the context structure \ref cy_stc_canfd_context_t allocated
* by the user. The structure is used during the CAN FD operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
*
* \return
* \ref cy_en_canfd_status_t
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_TxBufferConfig
*
*******************************************************************************/
cy_en_canfd_status_t Cy_CANFD_TxBufferConfig(CANFD_Type const *base, uint32_t chan,
                                             const cy_stc_canfd_tx_buffer_t *txBuffer,
                                             uint8_t index,
                                             cy_stc_canfd_context_t const *context)
{
    cy_en_canfd_status_t ret = CY_CANFD_BAD_PARAM;
    uint32_t* bufferAddress;
    uint32_t dlcIndex;
    uint32_t count;
    uint8_t  dataLengthWord;

    /* Check for NULL pointers */
    if ((NULL != context) && (NULL != txBuffer))
    {
        if((NULL != txBuffer->t0_f) && (NULL != txBuffer->t1_f))
        {
            CY_ASSERT_L2(CY_CANFD_IS_ID_VALID(txBuffer->t0_f->id));
            CY_ASSERT_L3(CY_CANFD_IS_RTR_VALID(txBuffer->t0_f->rtr));
            CY_ASSERT_L3(CY_CANFD_IS_XTD_VALID(txBuffer->t0_f->xtd));
            CY_ASSERT_L3(CY_CANFD_IS_ESI_VALID(txBuffer->t0_f->esi));
            CY_ASSERT_L2(CY_CANFD_IS_DLC_VALID(txBuffer->t1_f->dlc));
            CY_ASSERT_L3(CY_CANFD_IS_FDF_VALID(txBuffer->t1_f->fdf));
            CY_ASSERT_L2(CY_CANFD_IS_TX_BUFFER_MM_VALID(txBuffer->t1_f->mm));
            CY_ASSERT_L2(CY_CANFD_IS_MESSAGE_BUFFER_IDX_VALID(index));

            /* Get the Tx Buffer address (T0 element) */
            bufferAddress = (uint32_t *)Cy_CANFD_CalcTxBufAdrs(base, chan, index, context);

            /* Checks whether the CAN FD controller is not in the INIT state and Tx buffer is empty or not */
            if((!((_FLD2BOOL(CANFD_CH_M_TTCAN_CCCR_INIT, CANFD_CCCR(base, chan))) ||
                (0UL != (CANFD_TXBRP(base, chan) & (1UL << index))))) &&
                (NULL != bufferAddress))
            {
                /* T0 Configuration */
                *bufferAddress =
                _VAL2FLD(CY_CANFD_TX_BUFFER_T0_ESI, txBuffer->t0_f->esi) | /* The error state indicator */
                _VAL2FLD(CY_CANFD_TX_BUFFER_T0_XTD, txBuffer->t0_f->xtd) | /* The extended identifier */
                _VAL2FLD(CY_CANFD_TX_BUFFER_T0_RTR, txBuffer->t0_f->rtr) | /* A remote transmission request */
                _VAL2FLD(CY_CANFD_TX_BUFFER_T0_ID, ((CY_CANFD_XTD_STANDARD_ID == txBuffer->t0_f->xtd) ?
                        (txBuffer->t0_f->id
                        << CY_CANFD_EXT_IDENTIFIER_LENGTH) :   /* The 11-bit standard identifier */
                        txBuffer->t0_f->id));                    /* The 29-bit extended identifier */

                /* The T1 element address of Tx Buffer*/
                bufferAddress ++;

                /* Configure T1 */
                *bufferAddress = _VAL2FLD(CY_CANFD_TX_BUFFER_T1_MM, txBuffer->t1_f->mm) | /* The message marker */
                                _BOOL2FLD(CY_CANFD_TX_BUFFER_T1_EFC, txBuffer->t1_f->efc) | /* Event FIFO control */
                                _VAL2FLD(CY_CANFD_TX_BUFFER_T1_FDF, txBuffer->t1_f->fdf) | /* FD format */
                                _BOOL2FLD(CY_CANFD_TX_BUFFER_T1_BRS, txBuffer->t1_f->brs) | /* Bit rate switching */
                                _VAL2FLD(CY_CANFD_TX_BUFFER_T1_DLC, txBuffer->t1_f->dlc);  /* Data length code */

                /* Convert the DLC to data byte word */
                if (txBuffer->t1_f->dlc < CY_CANFD_CLASSIC_CAN_DATA_LENGTH)
                {
                    dlcIndex = 0UL;
                }
                else
                {
                    dlcIndex = (uint32_t)(txBuffer->t1_f->dlc - CY_CANFD_CLASSIC_CAN_DATA_LENGTH);
                }
                dataLengthWord = dataBufferSizeInWord[dlcIndex];

                /* Data set */
                bufferAddress++; /* The data area field address of Tx Buffer*/
                if ((CY_CANFD_RTR_DATA_FRAME == txBuffer->t0_f->rtr) && (NULL != txBuffer->data_area_f))
                {
                    for (count = 0UL; count < dataLengthWord; count++)
                    {
                        *bufferAddress = txBuffer->data_area_f[count];
                        bufferAddress++;
                    }
                }

                ret = CY_CANFD_SUCCESS;
            }
        }
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_CANFD_TransmitTxBuffer
****************************************************************************//**
*
* Starts transmission of the message prepared with Cy_CANFD_TxBufferConfig().
* Transmits the message immediately.
* Function CanFD_Init() must be called before setting up the identifier and enabling
* this message buffer.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
* The CAN FD channel number.
*
* \param index
* Message buffer index (0-31).
*
*
* \return \ref cy_en_canfd_status_t
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_TransmitTxBuffer
*
*******************************************************************************/
cy_en_canfd_status_t Cy_CANFD_TransmitTxBuffer(CANFD_Type *base, uint32_t chan,
                                                         uint8_t index)
{
    cy_en_canfd_status_t ret = CY_CANFD_BAD_PARAM;

    CY_ASSERT_L2(CY_CANFD_IS_MESSAGE_BUFFER_IDX_VALID(index));

    /* Checks whether the CAN FD controller is not in the INIT state and Tx buffer is empty or not */
    if(!((_FLD2BOOL(CANFD_CH_M_TTCAN_CCCR_INIT, CANFD_CCCR(base, chan))) ||
         (0UL != (CANFD_TXBRP(base, chan) & (1UL << index)))))
    {
        CANFD_TXBAR(base, chan) = 1UL << index; /* Transmits the buffer add request */

        ret = CY_CANFD_SUCCESS;
    }
    return ret;
}


/*******************************************************************************
* Function Name: Cy_CANFD_UpdateAndTransmitMsgBuffer
****************************************************************************//**
*
* Updates the T0 and T1 Tx buffer element parameters in Message RAM and copies
* data from cy_stc_canfd_tx_buffer_t structure to Message RAM.
* Transmits the message immediately.
* Function CanFD_Init() must be called before setting up the identifier and enabling
* this message buffer.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
* The CAN FD channel number.
*
* \param *txBuffer
* The Tx Buffer configuration structure.
*
* \param index
* the message buffer index (0-31).
*
* \param context
* The pointer to the context structure \ref cy_stc_canfd_context_t allocated
* by the user. The structure is used during the CAN FD operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
*
* \return \ref cy_en_canfd_status_t
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_UpdateAndTransmitMsgBuffer
*
*******************************************************************************/
cy_en_canfd_status_t Cy_CANFD_UpdateAndTransmitMsgBuffer(CANFD_Type *base, uint32_t chan,
                                                         const cy_stc_canfd_tx_buffer_t *txBuffer,
                                                         uint8_t index,
                                                         cy_stc_canfd_context_t const *context)
{
    cy_en_canfd_status_t ret = CY_CANFD_BAD_PARAM;

    ret = Cy_CANFD_TxBufferConfig(base, chan, txBuffer, index, context);

    if (CY_CANFD_SUCCESS == ret)
    {
        ret = Cy_CANFD_TransmitTxBuffer(base, chan, index);
    }
    return ret;
}


/*******************************************************************************
* Function Name: Cy_CANFD_GetTxBufferStatus
****************************************************************************//**
*
*  Gets the status of the CAN FD Tx buffer.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
* The CAN FD channel number.
*
* \param index
* Message buffer index (0-31).
*
* \return \ref cy_en_canfd_status_t
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_GetTxBufferStatus
*
*******************************************************************************/
cy_en_canfd_tx_buffer_status_t Cy_CANFD_GetTxBufferStatus(CANFD_Type const *base, uint32_t chan, uint8_t index)
{
    cy_en_canfd_tx_buffer_status_t enTxBufferStatus;

    CY_ASSERT_L2(CY_CANFD_IS_MESSAGE_BUFFER_IDX_VALID(index));

    /* Initializes return value */
    enTxBufferStatus = CY_CANFD_TX_BUFFER_IDLE;

    if(0UL != (CANFD_TXBRP(base, chan) & (1UL << index)))    /* Pending transmission request */
    {
        /* Checks if the cancel request was issued */
        if(0UL == (CANFD_TXBCR(base, chan) & (1UL << index)))
        {
            /* No cancellation request */
            enTxBufferStatus = CY_CANFD_TX_BUFFER_PENDING;
        }
        else
        {
            /* Cancel request issued */
            enTxBufferStatus = CY_CANFD_TX_BUFFER_CANCEL_REQUESTED;
        }
    }
    else if(0UL != (CANFD_TXBTO(base, chan) & (1UL << index))) /* Transmission occurred */
    {
        enTxBufferStatus = CY_CANFD_TX_BUFFER_TRANSMIT_OCCURRED;
    }
    else if(0UL != (CANFD_TXBCF(base, chan) & (1UL << index))) /* Cancellation finished */
    {
        enTxBufferStatus = CY_CANFD_TX_BUFFER_CANCEL_FINISHED;
    }
    else
    {
        /* Closing if-else-if sequence */
    }

    return enTxBufferStatus;
}

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXTTCANFD */


/* [] END OF FILE */
