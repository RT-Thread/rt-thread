/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_EDMA_SOC_H_
#define _FSL_EDMA_SOC_H_

#include "fsl_common.h"

/*!
 * @addtogroup edma_soc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*@{*/
/*! @brief Driver version 1.0.0. */
#define FSL_EDMA_SOC_DRIVER_VERSION (MAKE_VERSION(1, 0, 0))
/*@}*/

/*!@brief DMA IP version */
#define FSL_EDMA_SOC_IP_DMA3 (1)
#define FSL_EDMA_SOC_IP_DMA4 (0)

/*!@brief DMA base table */
#define EDMA_BASE_PTRS \
    {                  \
        DMA0, DMA1     \
    }

#define EDMA_CHN_IRQS                                                                                               \
    {                                                                                                               \
        {EDMA_0_CH0_IRQn,  EDMA_0_CH1_IRQn,  EDMA_0_CH2_IRQn,  EDMA_0_CH3_IRQn, EDMA_0_CH4_IRQn,  EDMA_0_CH5_IRQn,  \
         EDMA_0_CH6_IRQn,  EDMA_0_CH7_IRQn,  EDMA_0_CH8_IRQn,  EDMA_0_CH9_IRQn, EDMA_0_CH10_IRQn, EDMA_0_CH11_IRQn, \
         EDMA_0_CH12_IRQn, EDMA_0_CH13_IRQn, EDMA_0_CH14_IRQn, EDMA_0_CH15_IRQn},                                   \
        {                                                                                                           \
            EDMA_1_CH0_IRQn, EDMA_1_CH1_IRQn, EDMA_1_CH2_IRQn, EDMA_1_CH3_IRQn, EDMA_1_CH4_IRQn, EDMA_1_CH5_IRQn,   \
                EDMA_1_CH6_IRQn, EDMA_1_CH7_IRQn, EDMA_1_CH8_IRQn, EDMA_1_CH9_IRQn, EDMA_1_CH10_IRQn,               \
                EDMA_1_CH11_IRQn, EDMA_1_CH12_IRQn, EDMA_1_CH13_IRQn, EDMA_1_CH14_IRQn, EDMA_1_CH15_IRQn            \
        }                                                                                                           \
    }

/*!@brief dma request source */
typedef enum _dma_request_source
{
    kDmaRequestDisabled                        = 0U,           /**< DSisabled*/
    kDmaRequestMuxFlexSpi0Rx                   = 1 | 0x100U,   /**< FlexSPI0 Receive event */
    kDmaRequestMuxFlexSpi0Tx                   = 2 | 0x100U,   /**< FlexSPI0 Transmit event */
    kDmaRequestMuxPinInt0                      = 3 | 0x100U,   /**< PinInt0 */
    kDmaRequestMuxPinInt1                      = 4 | 0x100U,   /**< PinInt1 */
    kDmaRequestMuxPinInt2                      = 5 | 0x100U,   /**< PinInt2 */
    kDmaRequestMuxPinInt3                      = 6 | 0x100U,   /**< PinInt3 */
    kDmaRequestMuxCtimer0M0                    = 7 | 0x100U,   /**< Ctimer0_M0 */
    kDmaRequestMuxCtimer0M1                    = 8 | 0x100U,   /**< Ctimer0_M1 */
    kDmaRequestMuxCtimer1M0                    = 9 | 0x100U,   /**< Ctimer1_M0 */
    kDmaRequestMuxCtimer1M1                    = 10 | 0x100U,  /**< Ctimer1_M1 */
    kDmaRequestMuxCtimer2M0                    = 11 | 0x100U,  /**< Ctimer2_M0 */
    kDmaRequestMuxCtimer2M1                    = 12 | 0x100U,  /**< Ctimer2_M1 */
    kDmaRequestMuxCtimer3M0                    = 13 | 0x100U,  /**< Ctimer3_M0 */
    kDmaRequestMuxCtimer3M1                    = 14 | 0x100U,  /**< Ctimer3_M1 */
    kDmaRequestMuxCtimer4M0                    = 15 | 0x100U,  /**< Ctimer4_M0 */
    kDmaRequestMuxCtimer5M1                    = 16 | 0x100U,  /**< Ctimer4_M1 */
    kDmaRequestMuxWuu0                         = 17 | 0x100U,  /**< Wake up event */
    kDmaRequestMuxMicfil0FifoRequest           = 18 | 0x100U,  /**< MICFIL0 FIFO_request */
    kDmaRequestMuxSct0Dma0                     = 19 | 0x100U,  /**< SCT0 DMA0 */
    kDmaRequestMuxSct0Dma1                     = 20 | 0x100U,  /**< SCT0 DMA1 */
    kDmaRequestMuxAdc0FifoARequest             = 21 | 0x100U,  /**< ADC0 FIFO A request */
    kDmaRequestMuxAdc0FifoBRequest             = 22 | 0x100U,  /**< ADC0 FIFO B request */
    kDmaRequestMuxAdc1FifoARequest             = 23 | 0x100U,  /**< ADC1 FIFO A request */
    kDmaRequestMuxAdc1FifoBRequest             = 24 | 0x100U,  /**< ADC1 FIFO B request */
    kDmaRequestMuxDac0FifoRequest              = 25 | 0x100U,  /**< DAC0 FIFO_request */
    kDmaRequestMuxDac1FifoRequest              = 26 | 0x100U,  /**< DAC1 FIFO_request */
    kDmaRequestMuxHpDac0FifoRequest            = 27 | 0x100U,  /**< HP DAC0 FIFO_request */
    kDmaRequestMuxHsCmp0DmaRequest             = 28 | 0x100U,  /**< HS CMP0 DMA_request */
    kDmaRequestMuxHsCmp1DmaRequest             = 29 | 0x100U,  /**< HS CMP0 DMA_request */
    kDmaRequestMuxHsCmp2DmaRequest             = 30 | 0x100U,  /**< HS CMP0 DMA_request */
    kDmaRequestMuxEvtg0Out0A                   = 31 | 0x100U,  /**< EVTG0 OUT0A */
    kDmaRequestMuxEvtg0Out0B                   = 32 | 0x100U,  /**< EVTG0 OUT0B */
    kDmaRequestMuxEvtg0Out1A                   = 33 | 0x100U,  /**< EVTG0 OUT1A */
    kDmaRequestMuxEvtg0Out1B                   = 34 | 0x100U,  /**< EVTG0 OUT1B */
    kDmaRequestMuxEvtg0Out2A                   = 35 | 0x100U,  /**< EVTG0 OUT2A */
    kDmaRequestMuxEvtg0Out2B                   = 36 | 0x100U,  /**< EVTG0 OUT2B */
    kDmaRequestMuxEvtg0Out3A                   = 37 | 0x100U,  /**< EVTG0 OUT3A */
    kDmaRequestMuxEvtg0Out3B                   = 38 | 0x100U,  /**< EVTG0 OUT3B */
    kDmaRequestMuxFlexPwm0ReqCapt0             = 39 | 0x100U,  /**< FlexPWM0 Req_capt0 */
    kDmaRequestMuxFlexPwm0ReqCapt1             = 40 | 0x100U,  /**< FlexPWM0 Req_capt1 */
    kDmaRequestMuxFlexPwm0ReqCapt2             = 41 | 0x100U,  /**< FlexPWM0 Req_capt2 */
    kDmaRequestMuxFlexPwm0ReqCapt3             = 42 | 0x100U,  /**< FlexPWM0 Req_capt3 */
    kDmaRequestMuxFlexPwm0ReqVal0              = 43 | 0x100U,  /**< FlexPWM0 Req_val0 */
    kDmaRequestMuxFlexPwm0ReqVal1              = 44 | 0x100U,  /**< FlexPWM0 Req_val1 */
    kDmaRequestMuxFlexPwm0ReqVal2              = 45 | 0x100U,  /**< FlexPWM0 Req_val2 */
    kDmaRequestMuxFlexPwm0ReqVal3              = 46 | 0x100U,  /**< FlexPWM0 Req_val3 */
    kDmaRequestMuxFlexPwm1ReqCapt0             = 47 | 0x100U,  /**< FlexPWM1 Req_capt0 */
    kDmaRequestMuxFlexPwm1ReqCapt1             = 48 | 0x100U,  /**< FlexPWM1 Req_capt1 */
    kDmaRequestMuxFlexPwm1ReqCapt2             = 49 | 0x100U,  /**< FlexPWM1 Req_capt2 */
    kDmaRequestMuxFlexPwm1ReqCapt3             = 50 | 0x100U,  /**< FlexPWM1 Req_capt3 */
    kDmaRequestMuxFlexPwm1ReqVal0              = 51 | 0x100U,  /**< FlexPWM1 Req_val0 */
    kDmaRequestMuxFlexPwm1ReqVal1              = 52 | 0x100U,  /**< FlexPWM1 Req_val1 */
    kDmaRequestMuxFlexPwm1ReqVal2              = 53 | 0x100U,  /**< FlexPWM1 Req_val2 */
    kDmaRequestMuxFlexPwm1ReqVal3              = 54 | 0x100U,  /**< FlexPWM1 Req_val3 */
    kDmaRequestMuxItrc0TmprOut0                = 55 | 0x100U,  /**< ITRC0 TMPR_OUT0 */
    kDmaRequestMuxItrc0TmprOut1                = 56 | 0x100U,  /**< ITRC0 TMPR_OUT1 */
    kDmaRequestMuxLptmr0                       = 57 | 0x100U,  /**< LPTMR0 Counter match event */
    kDmaRequestMuxLptmr1                       = 58 | 0x100U,  /**< LPTMR1 Counter match event */
    kDmaRequestMuxFlexCan0DmaRequest           = 59 | 0x100U,  /**< FlexCAN0 DMA request */
    kDmaRequestMuxFlexCan1DmaRequest           = 60 | 0x100U,  /**< FlexCAN1 DMA request */
    kDmaRequestMuxFlexIO0ShiftRegister0Request = 61 | 0x100U,  /**< FlexIO0 Shift Register 0 request */
    kDmaRequestMuxFlexIO0ShiftRegister1Request = 62 | 0x100U,  /**< FlexIO0 Shift Register 1 request */
    kDmaRequestMuxFlexIO0ShiftRegister2Request = 63 | 0x100U,  /**< FlexIO0 Shift Register 2 request */
    kDmaRequestMuxFlexIO0ShiftRegister3Request = 64 | 0x100U,  /**< FlexIO0 Shift Register 3 request */
    kDmaRequestMuxFlexIO0ShiftRegister4Request = 65 | 0x100U,  /**< FlexIO0 Shift Register 4 request */
    kDmaRequestMuxFlexIO0ShiftRegister5Request = 66 | 0x100U,  /**< FlexIO0 Shift Register 5 request */
    kDmaRequestMuxFlexIO0ShiftRegister6Request = 67 | 0x100U,  /**< FlexIO0 Shift Register 6 request */
    kDmaRequestMuxFlexIO0ShiftRegister7Request = 68 | 0x100U,  /**< FlexIO0 Shift Register 7 request */
    kDmaRequestMuxLpFlexcomm0Rx                = 69 | 0x100U,  /**< LP_FLEXCOMM0 Receive request */
    kDmaRequestMuxLpFlexcomm0Tx                = 70 | 0x100U,  /**< LP_FLEXCOMM0 Transmit request */
    kDmaRequestMuxLpFlexcomm1Rx                = 71 | 0x100U,  /**< LP_FLEXCOMM1 Receive request */
    kDmaRequestMuxLpFlexcomm1Tx                = 72 | 0x100U,  /**< LP_FLEXCOMM1 Transmit request */
    kDmaRequestMuxLpFlexcomm2Rx                = 73 | 0x100U,  /**< LP_FLEXCOMM2 Receive request */
    kDmaRequestMuxLpFlexcomm2Tx                = 74 | 0x100U,  /**< LP_FLEXCOMM2 Transmit request */
    kDmaRequestMuxLpFlexcomm3Rx                = 75 | 0x100U,  /**< LP_FLEXCOMM3 Receive request */
    kDmaRequestMuxLpFlexcomm3Tx                = 76 | 0x100U,  /**< LP_FLEXCOMM3 Transmit request */
    kDmaRequestMuxLpFlexcomm4Rx                = 77 | 0x100U,  /**< LP_FLEXCOMM4 Receive request */
    kDmaRequestMuxLpFlexcomm4Tx                = 78 | 0x100U,  /**< LP_FLEXCOMM4 Transmit request */
    kDmaRequestMuxLpFlexcomm5Rx                = 79 | 0x100U,  /**< LP_FLEXCOMM5 Receive request */
    kDmaRequestMuxLpFlexcomm5Tx                = 80 | 0x100U,  /**< LP_FLEXCOMM5 Transmit request */
    kDmaRequestMuxLpFlexcomm6Rx                = 81 | 0x100U,  /**< LP_FLEXCOMM6 Receive request */
    kDmaRequestMuxLpFlexcomm6Tx                = 82 | 0x100U,  /**< LP_FLEXCOMM6 Transmit request */
    kDmaRequestMuxLpFlexcomm7Rx                = 83 | 0x100U,  /**< LP_FLEXCOMM7 Receive request */
    kDmaRequestMuxLpFlexcomm7Tx                = 84 | 0x100U,  /**< LP_FLEXCOMM7 Transmit request */
    kDmaRequestMuxLpFlexcomm8Rx                = 85 | 0x100U,  /**< LP_FLEXCOMM8 Receive request */
    kDmaRequestMuxLpFlexcomm8Tx                = 86 | 0x100U,  /**< LP_FLEXCOMM8 Transmit request */
    kDmaRequestMuxLpFlexcomm9Rx                = 87 | 0x100U,  /**< LP_FLEXCOMM9 Receive request */
    kDmaRequestMuxLpFlexcomm9Tx                = 88 | 0x100U,  /**< LP_FLEXCOMM9 Transmit request */
    kDmaRequestMuxESpi0Ch0                     = 89 | 0x100U,  /**< eSPI0 channel 0 */
    kDmaRequestMuxESpi0Ch1                     = 90 | 0x100U,  /**< eSPI0 channel 1 */
    kDmaRequestMuxEmvSim0Rx                    = 91 | 0x100U,  /**< EMVSIM0 Receive request */
    kDmaRequestMuxEmvSim0Tx                    = 92 | 0x100U,  /**< EMVSIM0 Transmit request */
    kDmaRequestMuxEmvSim1Rx                    = 93 | 0x100U,  /**< EMVSIM1 Receive request */
    kDmaRequestMuxEmvSim1Tx                    = 94 | 0x100U,  /**< EMVSIM1 Transmit request */
    kDmaRequestMuxI3c0Rx                       = 95 | 0x100U,  /**< I3C0 Receive request */
    kDmaRequestMuxI3c0Tx                       = 96 | 0x100U,  /**< I3C0 Transmit request */
    kDmaRequestMuxI3c1Rx                       = 97 | 0x100U,  /**< I3C0 Receive request */
    kDmaRequestMuxI3c1Tx                       = 98 | 0x100U,  /**< I3C0 Transmit request */
    kDmaRequestMuxSai0Rx                       = 99 | 0x100U,  /**< SAI0 Receive request */
    kDmaRequestMuxSai0Tx                       = 100 | 0x100U, /**< SAI0 Receive request */
    kDmaRequestMuxSai1Rx                       = 101 | 0x100U, /**< SAI1 Receive request */
    kDmaRequestMuxSai1Tx                       = 102 | 0x100U, /**< SAI1 Receive request */
    kDmaRequestMuxSinc0IpdReqSincAlt0          = 103 | 0x100U, /**< SINC0 ipd_req_sinc[0] or ipd_req_alt [0] */
    kDmaRequestMuxSinc0IpdReqSincAlt1          = 104 | 0x100U, /**< SINC0 ipd_req_sinc[1] or ipd_req_alt [1] */
    kDmaRequestMuxSinc0IpdReqSincAlt2          = 105 | 0x100U, /**< SINC0 ipd_req_sinc[2] or ipd_req_alt [2] */
    kDmaRequestMuxSinc0IpdReqSincAlt3          = 106 | 0x100U, /**< SINC0 ipd_req_sinc[3] or ipd_req_alt [3] */
    kDmaRequestMuxSinc0IpdReqSincAlt4          = 107 | 0x100U, /**< SINC0 ipd_req_sinc[4] or ipd_req_alt [4] */
    kDmaRequestMuxGpio0PinEventRequest0        = 108 | 0x100U, /**< GPIO0 Pin event request 0 */
    kDmaRequestMuxGpio0PinEventRequest1        = 109 | 0x100U, /**< GPIO0 Pin event request 1 */
    kDmaRequestMuxGpio1PinEventRequest0        = 110 | 0x100U, /**< GPIO1 Pin event request 0 */
    kDmaRequestMuxGpio1PinEventRequest1        = 111 | 0x100U, /**< GPIO1 Pin event request 1 */
    kDmaRequestMuxGpio2PinEventRequest0        = 112 | 0x100U, /**< GPIO2 Pin event request 0 */
    kDmaRequestMuxGpio2PinEventRequest1        = 113 | 0x100U, /**< GPIO2 Pin event request 1 */
    kDmaRequestMuxGpio3PinEventRequest0        = 114 | 0x100U, /**< GPIO3 Pin event request 0 */
    kDmaRequestMuxGpio3PinEventRequest1        = 115 | 0x100U, /**< GPIO3 Pin event request 1 */
    kDmaRequestMuxGpio4PinEventRequest0        = 116 | 0x100U, /**< GPIO4 Pin event request 0 */
    kDmaRequestMuxGpio4PinEventRequest1        = 117 | 0x100U, /**< GPIO4 Pin event request 1 */
    kDmaRequestMuxGpio5PinEventRequest0        = 118 | 0x100U, /**< GPIO5 Pin event request 0 */
    kDmaRequestMuxGpio5PinEventRequest1        = 119 | 0x100U, /**< GPIO5 Pin event request 1 */
    kDmaRequestMuxTsi0EndOfScan                = 120 | 0x100U, /**< TSI0 End of Scan */
    kDmaRequestMuxTsi0OutOfRange               = 121 | 0x100U, /**< TSI0 Out of Range */
} dma_request_source_t;

/*!< Verify dma base and request source */
#define EDMA_CHANNEL_HAS_REQUEST_SOURCE(base, source) ((source)&0x100U)

#define FSL_FEATURE_EDMA_MODULE_CHANNEL(base)                (16U)
#define FSL_FEATURE_EDMA_MODULE_MAX_CHANNEL                  (16)
#define FSL_FEATURE_EDMA_HAS_GLOBAL_MASTER_ID_REPLICATION    (1)
#define FSL_FEATURE_EDMA_HAS_CONTINUOUS_LINK_MODE            (0)
#define FSL_FEATURE_EDMA_MODULE_COUNT                        (2)
#define FSL_FEATURE_EDMA_HAS_CHANNEL_CONFIG                  (1)
#define FSL_FEATURE_EDMA_HAS_CHANNEL_SWAP_SIZE               (0)
#define FSL_FEATURE_EDMA_HAS_CHANNEL_ACCESS_TYPE             (0)
#define FSL_FEATURE_EDMA_HAS_CHANNEL_MEMRORY_ATTRIBUTE       (0)
#define FSL_FEATURE_EDMA_HAS_CHANNEL_SIGN_EXTENSION          (0)
#define FSL_FEATURE_EDMA_MODULE_SUPPORT_MATTR(base)          (0U)
#define FSL_FEATURE_EDMA_MODULE_SUPPORT_SIGN_EXTENSION(base) (0U)
#define FSL_FEATURE_EDMA_MODULE_SUPPORT_SWAP(base)           (0U)
#define FSL_FEATURE_EDMA_MODULE_SUPPORT_INSTR(base)          (0U)

/*!@brief EDMA base address convert macro */
#define EDMA_CHANNEL_OFFSET           0x1000U
#define EDMA_CHANNEL_ARRAY_STEP(base) (0x1000U)

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* _FSL_EDMA_SOC_H_ */
