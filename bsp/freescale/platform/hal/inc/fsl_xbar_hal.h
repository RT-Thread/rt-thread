/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#if !defined(__FSL_XBAR_HAL_H__)
#define __FSL_XBAR_HAL_H__

#include <assert.h>
#include <stdbool.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_XBAR_COUNT

/*!
 * @addtogroup xbar_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! 
 * @brief XBAR active edge for detection
 */
typedef enum _xbar_active_edge_detect
{
    kXbarEdgeNone             = 0U, /*!< Edge detection status bit never asserts. */
    kXbarEdgeRising           = 1U, /*!< Edge detection status bit asserts on rising edges. */
    kXbarEdgeFalling          = 2U, /*!< Edge detection status bit asserts on falling edges. */
    kXbarEdgeRisingAndFalling = 3U  /*!< Edge detection status bit asserts on rising and falling edges. */
}xbar_active_edge_t;

/*!
 * @brief Defines XBAR status return codes.
 */
typedef enum _xbar_status
{
    kStatus_XBAR_Success         = 0U, /*!< Success */
    kStatus_XBAR_InvalidArgument = 1U, /*!< Invalid argument existed */
    kStatus_XBAR_Initialized     = 2U, /*!< XBAR has been already initialized */
    kStatus_XBAR_Failed          = 3U  /*!< Execution failed */
} xbar_status_t;

#if defined FSL_FEATURE_XBAR_HAS_SINGLE_MODULE
#define XBARA_Type                           XBAR_Type 
#define XBARA_SELx_ADDR(x, n)                 XBAR_SELx_ADDR(x, n)    
#define XBARA_CTRLx_ADDR(x, n)                XBAR_CTRLx_ADDR(x, n)     
#define XBARA_WR_SELx_SELx(x, n, v)              XBAR_WR_SELx_SELx(x, n, v) 
#define XBARA_RD_SELx_SELx(x, n)                 XBAR_RD_SELx_SELx(x, n)     
#define XBARA_WR_CTRLx_DENx(x, n, v)             XBAR_WR_CTRLx_DENx(x, n, v)
#define XBARA_RD_CTRLx_DENx(x, n)                XBAR_RD_CTRLx_DENx(x, n) 
#define XBARA_WR_CTRLx_IENx(x, n, v)             XBAR_WR_CTRLx_IENx(x, n, v)
#define XBARA_RD_CTRLx_IENx(x, n)                XBAR_RD_CTRLx_IENx(x, n)        
#define XBARA_WR_CTRLx_EDGEx(x, n, v)            XBAR_WR_CTRLx_EDGEx(x, n, v)    
#define XBARA_RD_CTRLx_EDGEx(x, n)               XBAR_RD_CTRLx_EDGEx(x, n)  
#define XBARA_CLR_CTRLx_STSx(x, n)               XBAR_WR_CTRLx_STSx(x, n, 0)  
#define XBARA_RD_CTRLx_STSx(x, n)                XBAR_RD_CTRLx_STSx(x, n)
#define FSL_FEATURE_XBARA_INTERRUPT_COUNT        FSL_FEATURE_XBAR_INTERRUPT_COUNT
#define FSL_FEATURE_XBARA_MODULE_OUTPUTS         FSL_FEATURE_XBAR_MODULE_OUTPUTS
#define FSL_FEATURE_XBARA_MODULE_INPUTS          FSL_FEATURE_XBAR_MODULE_INPUTS
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the XBARA module to the reset state.  
 *
 * @param baseAddr Register base address for XBAR module.
 */
void XBARA_HAL_Init(XBARA_Type * baseAddr);
  
/*!
 * @brief Selects which of the shared inputs XBARA_IN[*] is muxed to selected output XBARA_OUT[*].
 *
 * This function selects which of the shared inputs XBARA_IN[*] is muxed to selected output XBARA_OUT[*].
 *
 * @param baseAddr Register base address for XBARA module.
 * @param input Input to be muxed to selected XBARA_OUT[*] output.
 * @param outIndex Selected output XBARA_OUT[*].
 */
static inline void XBARA_HAL_SetOutSel(XBARA_Type * baseAddr, uint32_t outIndex, uint32_t input)
{
    assert((outIndex & 0xFFU) <= FSL_FEATURE_XBARA_MODULE_OUTPUTS);
    XBARA_WR_SELx_SELx(baseAddr, (outIndex & 0xFFU), (input & 0xFFU));
}

/*!
 * @brief Gets input XBARA_IN[*] muxed to selected output XBARA_OUT[*].
 *
 * This function gets input XBARA_IN[*] muxed to selected output XBARA_OUT[*].
 *
 * @param baseAddr Register base address for XBAR module.
 * @param outIndex Selected XBARA_OUT[*] output.
 * @return Input XBARA_IN[*] muxed to selected XBARA_OUT[*] output.
 */
static inline uint32_t XBARA_HAL_GetOutSel(XBARA_Type * baseAddr, uint32_t outIndex)
{
    assert((outIndex & 0xFFU) <= FSL_FEATURE_XBARA_MODULE_OUTPUTS);
    return (uint32_t)XBARA_RD_SELx_SELx(baseAddr, (outIndex & 0xFFU));
}

/*!
 * @brief Sets the DMA function on the corresponding XBARA_OUT[*] output.
 *
 * This function sets the DMA function on the corresponding XBARA_OUT[*]. When the interrupt is
 * enabled, the output INT_REQn reflects the value STSn. When the interrupt is disabled, INT_REQn
 * remains low. The interrupt request is cleared by writing a 1 to STSn.
 *
 * @param baseAddr Register base address for XBARA module.
 * @param outIndex Selected XBARA_OUT[*] output.
 * @param enable Bool value for enable or disable DMA request.
 */
static inline void XBARA_HAL_SetDMAOutCmd(XBARA_Type * baseAddr, uint32_t outIndex, bool enable)
{
    assert((outIndex & 0xFFU) < FSL_FEATURE_XBARA_INTERRUPT_COUNT);
    XBARA_WR_CTRLx_DENx(baseAddr, (outIndex & 0xFFU), enable);
}

/*!
 * @brief Sets the interrupt function on the corresponding XBARA_OUT[*] output.
 *
 * This function sets the interrupt function on the corresponding XBARA_OUT[*]. When enabled, DMA_REQn
 * presents the value STSn. When disabled, the DMA_REQn output remains low.
 *
 * @param baseAddr Register base address for XBARA module.
 * @param outIndex Selected XBARA_OUT[*] output.
 * @param enable Bool value for enable or disable interrupt.
 */
static inline void XBARA_HAL_SetIntOutCmd(XBARA_Type * baseAddr, uint32_t outIndex, bool enable)
{
    assert((outIndex & 0xFFU) < FSL_FEATURE_XBARA_INTERRUPT_COUNT);
    XBARA_WR_CTRLx_IENx(baseAddr, (outIndex & 0xFFU), enable);
}

/*!
 * @brief Checks whether the DMA function is enabled or disabled on the corresponding XBARA_OUT[*] output.
 *
 * @param baseAddr Register base address for XBARA module.
 * @param outIndex Selected XBARA_OUT[*] output.
 * @return DMA function is enabled (true) or disabled (false).
 */
static inline bool XBARA_HAL_GetDMAOutCmd(XBARA_Type * baseAddr, uint32_t outIndex)
{
    assert((outIndex & 0xFFU) < FSL_FEATURE_XBARA_INTERRUPT_COUNT);
    return XBARA_RD_CTRLx_DENx(baseAddr, (outIndex & 0xFFU));
}

/*!
 * @brief Checks whether the interrupt function is enabled or disabled on the corresponding XBARA_OUT[*] output.
 *
 * @param baseAddr Register base address for XBARA module.
 * @param outIndex Selected XBARA_OUT[*] output.
 * @return Interrupt function is enabled (true) or disabled (false).
 */
static inline bool XBARA_HAL_GetIntOutCmd(XBARA_Type * baseAddr, uint32_t outIndex)
{
    assert((outIndex & 0xFFU) < FSL_FEATURE_XBARA_INTERRUPT_COUNT);
    return XBARA_RD_CTRLx_IENx(baseAddr, (outIndex & 0xFFU));
}

/*!
 * @brief Selects which edges on the corresponding XBARA_OUT[*] output cause STSn to assert.
 *
 * This function selects which edges on the corresponding XBARA_OUT[*] output cause STSn to assert.
 *
 * @param baseAddr Register base address for XBAR module.
 * @param outIndex Selected XBARA_OUT[*] output.
 * @param edge Active edge for edge detection.
 */
static inline void XBARA_HAL_SetOutActiveEdge(XBARA_Type * baseAddr, uint32_t outIndex, xbar_active_edge_t edge)
{
    assert((outIndex & 0xFFU) < FSL_FEATURE_XBARA_INTERRUPT_COUNT);
    XBARA_WR_CTRLx_EDGEx(baseAddr, (outIndex & 0xFFU), edge);
}

/*!
 * @brief Gets which edges on the corresponding XBARA_OUT[*] output cause STSn to assert.
 *
 * This function gets which edges on the corresponding XBARA_OUT[*] output cause STSn to assert.
 *
 * @param baseAddr Register base address for XBARA module.
 * @param outIndex Selected XBARA_OUT[*] output.
 * @return Active edge for edge detection on corresponding XBARA_OUT[*] output.
 */
static inline xbar_active_edge_t XBARA_HAL_GetOutActiveEdge(XBARA_Type * baseAddr, uint32_t outIndex)
{
    assert((outIndex & 0xFFU) < FSL_FEATURE_XBARA_INTERRUPT_COUNT);
    return (xbar_active_edge_t) XBARA_RD_CTRLx_EDGEx(baseAddr, (outIndex & 0xFFU));
}

/*!
 * @brief Clears the edge detection status for the corresponding XBARA_OUT[*] output.
 *
 * @param baseAddr Register base address for XBARA module.
 * @param outIndex Selected XBARA_OUT[*] output.
 */
static inline void XBARA_HAL_ClearEdgeDetectionStatus(XBARA_Type * baseAddr, uint32_t outIndex)
{
    assert((outIndex & 0xFFU) < FSL_FEATURE_XBARA_INTERRUPT_COUNT);
    XBARA_CLR_CTRLx_STSx(baseAddr, (outIndex & 0xFFU));  
}

/*!
 * @brief Gets the edge detection status for the corresponding XBARA_OUT[*] output.
 *
 * @param baseAddr Register base address for XBARA module.
 * @param outIndex Selected XBARA_OUT[*] output.
 * @return Active edge detected (true) or not yet detected (false) on corresponind XBARA_OUT[*] output.
 */
static inline bool XBARA_HAL_GetEdgeDetectionStatus(XBARA_Type * baseAddr, uint32_t outIndex)
{
    assert((outIndex & 0xFFU) < FSL_FEATURE_XBARA_INTERRUPT_COUNT);
    return XBARA_RD_CTRLx_STSx(baseAddr, (outIndex & 0xFFU));  
}

#if !defined FSL_FEATURE_XBAR_HAS_SINGLE_MODULE

/*!
 * @brief Initializes the XBARB module to the reset state.  
 *
 * @param baseAddr Register base address for XBARB module.
 */
void XBARB_HAL_Init(XBARB_Type * baseAddr);

/*!
 * @brief Selects which of the shared inputs XBARB_IN[*] is muxed to selected output XBARB_OUT[*]   .
 *
 * This function selects which of the shared inputs XBARB_IN[*] is muxed 
 * to selected output XBARB_OUT[*]
 *
 * @param baseAddr Register base address for XBARB module.
 * @param outIndex Selected XBARB_OUT[*] output.
 * @param input Input to be muxed to selected XBARB_OUT[*] output.
 */
static inline void XBARB_HAL_SetOutSel(XBARB_Type * baseAddr, uint32_t outIndex, uint32_t input)
{
    assert((outIndex & 0xFFU) < FSL_FEATURE_XBARB_MODULE_OUTPUTS);
    XBARB_WR_SELx_SELx(baseAddr, (outIndex & 0xFFU), (input & 0xFFU));
}

/*!
 * @brief Gets input XBARB_IN[*] muxed to selected output XBARB_OUT[*] .
 *
 * This function gets input XBARB_IN[*] muxed to selected output XBARB_OUT[*]
 *
 * @param baseAddr Register base address for XBARB module.
 * @param outIndex Selected XBARB_OUT[*] output.
 * @return Input XBARB_IN[*] muxed to selected XBARB_OUT[*] output.
 */
static inline uint32_t XBARB_HAL_GetOutSel(XBARB_Type * baseAddr, uint32_t outIndex)
{
    assert((outIndex & 0xFFU) < FSL_FEATURE_XBARB_MODULE_OUTPUTS);
    return (uint32_t)XBARB_RD_SELx_SELx(baseAddr, (outIndex & 0xFFU));
}
#else
/*!
 * @brief Initializes the XBAR module to the reset state.  
 *
 * @param baseAddr Register base address for XBAR module.
 */
static inline void XBAR_HAL_Init(XBAR_Type * baseAddr)
{
    XBARA_HAL_Init(baseAddr);
}
  
/*!
 * @brief Selects which of the shared inputs XBAR_IN[*] is muxed to selected output XBAR_OUT[*].
 *
 * This function selects which of the shared inputs XBAR_IN[*] is muxed to selected output XBAR_OUT[*].
 *
 * @param baseAddr Register base address for XBAR module.
 * @param input Input to be muxed to selected XBAR_OUT[*] output.
 * @param outIndex Selected output XBAR_OUT[*].
 */
static inline void XBAR_HAL_SetOutSel(XBAR_Type * baseAddr, uint32_t outIndex, uint32_t input)
{
    XBARA_HAL_SetOutSel(baseAddr, outIndex, input);
}

/*!
 * @brief Gets input XBAR_IN[*] muxed to selected output XBAR_OUT[*].
 *
 * This function gets input XBAR_IN[*] muxed to selected output XBAR_OUT[*].
 *
 * @param baseAddr Register base address for XBAR module.
 * @param outIndex Selected XBAR_OUT[*] output.
 * @return Input XBARA_IN[*] muxed to selected XBAR_OUT[*] output.
 */
static inline uint32_t XBAR_HAL_GetOutSel(XBAR_Type * baseAddr, uint32_t outIndex)
{
    return XBARA_HAL_GetOutSel(baseAddr, outIndex);
}

/*!
 * @brief Sets the DMA function on the corresponding XBARA_OUT[*] output.
 *
 * This function sets the DMA function on the corresponding XBARA_OUT[*]. When the interrupt is
 * enabled, the output INT_REQn reflects the value STSn. When the interrupt is disabled, INT_REQn
 * remains low. The interrupt request is cleared by writing a 1 to STSn.
 *
 * @param baseAddr Register base address for XBARA module.
 * @param outIndex Selected XBARA_OUT[*] output.
 * @param enable Bool value for enable or disable DMA request.
 */
static inline void XBAR_HAL_SetDMAOutCmd(XBAR_Type * baseAddr, uint32_t outIndex, bool enable)
{
    XBARA_HAL_SetDMAOutCmd(baseAddr, outIndex, enable);
}

/*!
 * @brief Sets the interrupt function on the corresponding XBAR_OUT[*] output.
 *
 * This function sets the interrupt function on the corresponding XBAR_OUT[*]. When enabled, DMA_REQn
 * presents the value STSn. When disabled, the DMA_REQn output remains low.
 *
 * @param baseAddr Register base address for XBAR module.
 * @param outIndex Selected XBAR_OUT[*] output.
 * @param enable Bool value for enable or disable interrupt.
 */
static inline void XBAR_HAL_SetIntOutCmd(XBAR_Type * baseAddr, uint32_t outIndex, bool enable)
{
    XBARA_HAL_SetIntOutCmd(baseAddr, outIndex, enable);
}

/*!
 * @brief Checks whether the DMA function is enabled or disabled on the corresponding XBAR_OUT[*] output.
 *
 * @param baseAddr Register base address for XBAR module.
 * @param outIndex Selected XBAR_OUT[*] output.
 * @return DMA function is enabled (true) or disabled (false).
 */
static inline bool XBAR_HAL_GetDMAOutCmd(XBAR_Type * baseAddr, uint32_t outIndex)
{
    return XBARA_HAL_GetDMAOutCmd(baseAddr, outIndex);
}

/*!
 * @brief Checks whether the interrupt function is enabled or disabled on the corresponding XBAR_OUT[*] output.
 *
 * @param baseAddr Register base address for XBAR module.
 * @param outIndex Selected XBAR_OUT[*] output.
 * @return Interrupt function is enabled (true) or disabled (false).
 */
static inline bool XBAR_HAL_GetIntOutCmd(XBAR_Type * baseAddr, uint32_t outIndex)
{
    return XBARA_HAL_GetIntOutCmd(baseAddr, outIndex);
}

/*!
 * @brief Selects which edges on the corresponding XBAR_OUT[*] output cause STSn to assert.
 *
 * This function selects which edges on the corresponding XBAR_OUT[*] output cause STSn to assert.
 *
 * @param baseAddr Register base address for XBAR module.
 * @param outIndex Selected XBAR_OUT[*] output.
 * @param edge Active edge for edge detection.
 */
static inline void XBAR_HAL_SetOutActiveEdge(XBAR_Type * baseAddr, uint32_t outIndex, xbar_active_edge_t edge)
{
    XBARA_HAL_SetOutActiveEdge(baseAddr, outIndex, edge);
}

/*!
 * @brief Gets which edges on the corresponding XBAR_OUT[*] output cause STSn to assert.
 *
 * This function gets which edges on the corresponding XBAR_OUT[*] output cause STSn to assert.
 *
 * @param baseAddr Register base address for XBAR module.
 * @param outIndex Selected XBAR_OUT[*] output.
 * @return Active edge for edge detection on corresponding XBAR_OUT[*] output.
 */
static inline xbar_active_edge_t XBAR_HAL_GetOutActiveEdge(XBAR_Type * baseAddr, uint32_t outIndex)
{
    return XBARA_HAL_GetOutActiveEdge(baseAddr, outIndex);
}

/*!
 * @brief Clears the edge detection status for the corresponding XBAR_OUT[*] output.
 *
 * @param baseAddr Register base address for XBAR module.
 * @param outIndex Selected XBAR_OUT[*] output.
 */
static inline void XBAR_HAL_ClearEdgeDetectionStatus(XBAR_Type * baseAddr, uint32_t outIndex)
{
    XBARA_HAL_ClearEdgeDetectionStatus(baseAddr, outIndex);
}

/*!
 * @brief Gets the edge detection status for the corresponding XBAR_OUT[*] output.
 *
 * @param baseAddr Register base address for XBAR module.
 * @param outIndex Selected XBAR_OUT[*] output.
 * @return Active edge detected (true) or not yet detected (false) on corresponind XBAR_OUT[*] output.
 */
static inline bool XBAR_HAL_GetEdgeDetectionStatus(XBAR_Type * baseAddr, uint32_t outIndex)
{
    return XBARA_HAL_GetEdgeDetectionStatus(baseAddr, outIndex);
}

#endif/* FSL_FEATURE_XBAR_HAS_SINGLE_MODULE */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif
#endif /* __FSL_XBAR_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/
