/***************************************************************************//**
* \file cy_usbfs_dev_drv_reg.h
* \version 2.20.3
*
* Provides register access API implementation of the USBFS driver.
*
********************************************************************************
* \copyright
* Copyright 2018-2020 Cypress Semiconductor Corporation
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


/** \cond INTERNAL */

/**
* \addtogroup group_usbfs_dev_drv_reg
* \{
*
* Register access API for the USBFS Device block.
*
* This is the API that provides an interface to the USBFS Device hardware.
* These API are intended to be used by the USBFS Device driver to access
* hardware. You can use these API to implement a custom driver based on
* the USBFS Device hardware.
*
* \defgroup group_usbfs_dev_drv_reg_macros Macros
* \{
*   \defgroup group_usbfs_dev_drv_reg_macros_hardware       Hardware-specific Constants
*   \defgroup group_usbfs_dev_drv_reg_macros_sie_intr       SIE Interrupt Sources
*   \defgroup group_usbfs_dev_drv_reg_macros_sie_mode       SIE Endpoint Modes
*   \defgroup group_usbfs_dev_drv_reg_macros_arb_ep_intr    Arbiter Endpoint Interrupt Sources
* \}
*
* \defgroup group_usbfs_drv_drv_reg_functions Functions
* \{
*   \defgroup group_usbfs_drv_drv_reg_interrupt_sources SIE Interrupt Sources Registers Access
*   \defgroup group_usbfs_drv_drv_reg_ep0_access        Endpoint 0 Registers Access
*   \defgroup group_usbfs_drv_drv_reg_sie_access        SIE Data Endpoint Registers Access
*   \defgroup group_usbfs_drv_drv_reg_arbiter           Arbiter Endpoint Registers Access
*   \defgroup group_usbfs_drv_drv_reg_arbiter_data      Arbiter Endpoint Data Registers Access
*   \defgroup group_usbfs_drv_drv_reg_misc              Miscellaneous Functions
* \}
*
* \}
*/


#if !defined(CY_USBFS_DEV_DRV_REG_H)
#define CY_USBFS_DEV_DRV_REG_H

#include "cy_device.h"

#if defined (CY_IP_MXUSBFS) && defined (CY_IP_MXPERI)

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "cy_syslib.h"

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
*                       Hardware-specific Constants
*******************************************************************************/

/**
* \addtogroup group_usbfs_dev_drv_reg_macros_hardware
* \{
*/
/** Number of data endpoints supported by the hardware */
#define CY_USBFS_DEV_DRV_NUM_EPS_MAX        (8U)

/** The hardware buffer size used for data endpoint buffers */
#define CY_USBFS_DEV_DRV_HW_BUFFER_SIZE     (512U)

/** The hardware buffer for endpoint 0 */
#define CY_USBFS_DEV_DRV_EP0_BUFFER_SIZE    (8U)
/** \} group_usbfs_dev_drv_reg_macros_hardware */


/*******************************************************************************
*                          Functions
*******************************************************************************/

/**
* \addtogroup group_usbfs_drv_drv_reg_interrupt_sources
* \{
*/
/* Access to LPM SIE interrupt sources */
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetSieInterruptStatus(USBFS_Type const *base);
__STATIC_INLINE     void Cy_USBFS_Dev_Drv_SetSieInterruptMask  (USBFS_Type *base, uint32_t mask);
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetSieInterruptMask  (USBFS_Type const *base);
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetSieInterruptStatusMasked(USBFS_Type const *base);
__STATIC_INLINE     void Cy_USBFS_Dev_Drv_ClearSieInterrupt    (USBFS_Type *base, uint32_t mask);
__STATIC_INLINE     void Cy_USBFS_Dev_Drv_SetSieInterrupt      (USBFS_Type *base, uint32_t mask);
/** \} group_usbfs_drv_drv_reg_interrupt_sources */


/**
* \addtogroup group_usbfs_drv_drv_reg_ep0_access
* \{
*/
/* Access control endpoint CR0.Mode registers */
__STATIC_INLINE void     Cy_USBFS_Dev_Drv_WriteEp0Mode(USBFS_Type *base, uint32_t mode);
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_ReadEp0Mode(USBFS_Type const *base);

__STATIC_INLINE void     Cy_USBFS_Dev_Drv_SetEp0Count(USBFS_Type *base, uint32_t count, uint32_t toggle);
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetEp0Count(USBFS_Type const *base);

__STATIC_INLINE void     Cy_USBFS_Dev_Drv_WriteEp0Data(USBFS_Type *base, uint32_t idx, uint32_t value);
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_ReadEp0Data(USBFS_Type const *base, uint32_t idx);
/** \} group_usbfs_drv_drv_reg_ep0_access */

/**
* \addtogroup group_usbfs_drv_drv_reg_sie_access
* \{
*/
/* Access SIE data endpoints CR0.Mode registers */
__STATIC_INLINE void     Cy_USBFS_Dev_Drv_SetSieEpMode   (USBFS_Type *base, uint32_t endpoint, uint32_t mode);
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetSieEpMode   (USBFS_Type const *base, uint32_t endpoint);
__STATIC_INLINE void     Cy_USBFS_Dev_Drv_SetSieEpStall  (USBFS_Type *base, bool inDirection, uint32_t endpoint);
__STATIC_INLINE void     Cy_USBFS_Dev_Drv_ClearSieEpStall(USBFS_Type *base, uint32_t endpoint, uint32_t mode);
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetSieEpError  (USBFS_Type const *base, uint32_t endpoint);

/* Access SIE data endpoints CNT0 and CNT1 registers */
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetSieEpToggle  (USBFS_Type const *base, uint32_t endpoint);
__STATIC_INLINE void     Cy_USBFS_Dev_Drv_ClearSieEpToggle(USBFS_Type *base, uint32_t endpoint);
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetSieEpCount(USBFS_Type const *base, uint32_t endpoint);
__STATIC_INLINE void     Cy_USBFS_Dev_Drv_SetSieEpCount(USBFS_Type *base, uint32_t endpoint, uint32_t count, uint32_t toggle);

/* Access SIE data endpoints interrupt source registers */
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetSieAllEpsInterruptStatus(USBFS_Type const *base);
__STATIC_INLINE void     Cy_USBFS_Dev_Drv_EnableSieEpInterrupt (USBFS_Type *base, uint32_t endpoint);
__STATIC_INLINE void     Cy_USBFS_Dev_Drv_DisableSieEpInterrupt(USBFS_Type *base, uint32_t endpoint);
__STATIC_INLINE void     Cy_USBFS_Dev_Drv_ClearSieEpInterrupt  (USBFS_Type *base, uint32_t endpoint);
/** \} group_usbfs_drv_drv_reg_sie_access */

/**
* \addtogroup group_usbfs_drv_drv_reg_arbiter
* \{
*/
/* Access Arbiter data endpoints interrupt sources registers */
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetArbAllEpsInterruptStatus(USBFS_Type const *base);
__STATIC_INLINE void     Cy_USBFS_Dev_Drv_EnableArbEpInterrupt (USBFS_Type *base, uint32_t endpoint);
__STATIC_INLINE void     Cy_USBFS_Dev_Drv_DisableArbEpInterrupt(USBFS_Type *base, uint32_t endpoint);
__STATIC_INLINE void     Cy_USBFS_Dev_Drv_SetArbEpInterruptMask(USBFS_Type *base, uint32_t endpoint, uint32_t mask);
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetArbEpInterruptMask(USBFS_Type const *base, uint32_t endpoint);
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetArbEpInterruptStatusMasked(USBFS_Type const *base, uint32_t endpoint);
__STATIC_INLINE void     Cy_USBFS_Dev_Drv_ClearArbEpInterrupt(USBFS_Type *base, uint32_t endpoint, uint32_t mask);

/* Access Arbiter data endpoints configuration register */
__STATIC_INLINE void Cy_USBFS_Dev_Drv_SetArbEpConfig       (USBFS_Type *base, uint32_t endpoint, uint32_t cfg);
__STATIC_INLINE void Cy_USBFS_Dev_Drv_SetArbCfgEpInReady   (USBFS_Type *base, uint32_t endpoint);
__STATIC_INLINE void Cy_USBFS_Dev_Drv_ClearArbCfgEpInReady (USBFS_Type *base, uint32_t endpoint);
__STATIC_INLINE void Cy_USBFS_Dev_Drv_TriggerArbCfgEpDmaReq(USBFS_Type *base, uint32_t endpoint);

/* Access Arbiter data endpoints WA (Write Address and RA(Read Address) registers */
__STATIC_INLINE void     Cy_USBFS_Dev_Drv_SetArbWriteAddr(USBFS_Type *base, uint32_t endpoint, uint32_t wa);
__STATIC_INLINE void     Cy_USBFS_Dev_Drv_SetArbReadAddr (USBFS_Type *base, uint32_t endpoint, uint32_t ra);
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetArbWriteAddr(USBFS_Type const *base, uint32_t endpoint);
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetArbReadAddr (USBFS_Type const *base, uint32_t endpoint);
/** \} group_usbfs_drv_drv_reg_arbiter */

/**
* \addtogroup group_usbfs_drv_drv_reg_arbiter_data
* \{
*/
/* Access data endpoints data registers. Used to get/put data into endpoint buffer */
__STATIC_INLINE void     Cy_USBFS_Dev_Drv_WriteData  (USBFS_Type *base, uint32_t endpoint, uint8_t  byte);
__STATIC_INLINE void     Cy_USBFS_Dev_Drv_WriteData16(USBFS_Type *base, uint32_t endpoint, uint16_t halfword);
__STATIC_INLINE uint8_t  Cy_USBFS_Dev_Drv_ReadData   (USBFS_Type const *base, uint32_t endpoint);
__STATIC_INLINE uint16_t Cy_USBFS_Dev_Drv_ReadData16 (USBFS_Type const *base, uint32_t endpoint);
__STATIC_INLINE volatile uint32_t * Cy_USBFS_Dev_Drv_GetDataRegAddr  (USBFS_Type *base, uint32_t endpoint);
__STATIC_INLINE volatile uint32_t * Cy_USBFS_Dev_Drv_GetDataReg16Addr(USBFS_Type *base, uint32_t endpoint);
__STATIC_INLINE void     Cy_USBFS_Dev_Drv_FlushInBuffer (USBFS_Type *base, uint32_t endpoint);
/** \} group_usbfs_drv_drv_reg_arbiter_data */

/**
* \addtogroup group_usbfs_drv_drv_reg_misc
* \{
*/
__STATIC_INLINE void     Cy_USBFS_Dev_Drv_SetEpType  (USBFS_Type *base, bool inDirection, uint32_t endpoint);
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetSofNubmer(USBFS_Type const *base);
/** \} group_usbfs_drv_drv_reg_misc */


/*******************************************************************************
*                       API Constants
*******************************************************************************/

/** /cond INTERNAL */
/* Macro to access ODD offset registers: Cypress ID# 299773 */
#define CY_USBFS_DEV_DRV_WRITE_ODD(val)  ( (val) | ((uint32_t) (val) << 8U) )
#define CY_USBFS_DEV_READ_ODD(reg)       ( (uint32_t) (CY_LO8((reg) | ((reg) >> 8U))) )
/** /endcond */

/**
* \addtogroup group_usbfs_dev_drv_reg_macros_sie_intr
* \{
*/
#define CY_USBFS_DEV_DRV_INTR_SIE_SOF       USBFS_USBLPM_INTR_SIE_SOF_INTR_Msk        /**< SOF frame detected */
#define CY_USBFS_DEV_DRV_INTR_SIE_BUS_RESET USBFS_USBLPM_INTR_SIE_BUS_RESET_INTR_Msk  /**< Bus Reset detected */
#define CY_USBFS_DEV_DRV_INTR_SIE_EP0       USBFS_USBLPM_INTR_SIE_EP0_INTR_Msk        /**< EP0 access detected */
#define CY_USBFS_DEV_DRV_INTR_SIE_LPM       USBFS_USBLPM_INTR_SIE_LPM_INTR_Msk        /**< Link Power Management request detected */
#define CY_USBFS_DEV_DRV_INTR_SIE_RESUME    USBFS_USBLPM_INTR_SIE_RESUME_INTR_Msk     /**< Resume condition detected */
/** \} group_usbfs_dev_drv_reg_macros_sie_intr */

/**
* \addtogroup group_usbfs_dev_drv_reg_macros_sie_mode
* \{
*/
/* Modes for endpoint 0 (control endpoint) */
#define CY_USBFS_DEV_DRV_EP_CR_DISABLE           (0U)  /**< Data endpoint disabled */
#define CY_USBFS_DEV_DRV_EP_CR_NAK_INOUT         (1U)  /**< Data endpoint NAK IN and OUT requests */
#define CY_USBFS_DEV_DRV_EP_CR_STALL_INOUT       (3U)  /**< Data endpoint STALL IN and OUT requests */
#define CY_USBFS_DEV_DRV_EP_CR_STATUS_OUT_ONLY   (2U)  /**< Data endpoint ACK only Status OUT requests */
#define CY_USBFS_DEV_DRV_EP_CR_STATUS_IN_ONLY    (6U)  /**< Data endpoint ACK only Status IN requests */
#define CY_USBFS_DEV_DRV_EP_CR_ACK_OUT_STATUS_IN (11U) /**< Data endpoint ACK only Data and Status OUT requests */
#define CY_USBFS_DEV_DRV_EP_CR_ACK_IN_STATUS_OUT (15U) /**< Data endpoint ACK only Data and Status IN requests */

/* Modes for ISO data endpoints */
#define CY_USBFS_DEV_DRV_EP_CR_ISO_OUT          (5U)   /**< Data endpoint is ISO OUT */
#define CY_USBFS_DEV_DRV_EP_CR_ISO_IN           (7U)   /**< Data endpoint is ISO IN */

/* Modes for Control/Bulk/Interrupt OUT data endpoints */
#define CY_USBFS_DEV_DRV_EP_CR_NAK_OUT          (8U)   /**< Data endpoint NAK OUT requests */
#define CY_USBFS_DEV_DRV_EP_CR_ACK_OUT          (9U)   /**< Data endpoint ACK OUT requests */

/* Modes for Control/Bulk/Interrupt IN data endpoints */
#define CY_USBFS_DEV_DRV_EP_CR_NAK_IN           (12U)   /**< Data endpoint NAK IN requests */
#define CY_USBFS_DEV_DRV_EP_CR_ACK_IN           (13U)   /**< Data endpoint ACK IN requests */
/** \} group_usbfs_dev_drv_reg_macros_sie_mode */

/**
* \addtogroup group_usbfs_dev_drv_reg_macros_arb_ep_intr ARB_EP_SR/INT_EN 1-8 registers
* \{
*/

/** Data endpoint IN buffer full interrupt source */
#define USBFS_USBDEV_ARB_EP_IN_BUF_FULL_Msk USBFS_USBDEV_ARB_EP1_INT_EN_IN_BUF_FULL_EN_Msk
/** Data endpoint grant interrupt source (DMA complete read/write) */
#define USBFS_USBDEV_ARB_EP_DMA_GNT_Msk     USBFS_USBDEV_ARB_EP1_INT_EN_DMA_GNT_EN_Msk
/** Data endpoint overflow interrupt source (applicable only for Automatic DMA mode) */
#define USBFS_USBDEV_ARB_EP_BUF_OVER_Msk    USBFS_USBDEV_ARB_EP1_INT_EN_BUF_OVER_EN_Msk
/** Data endpoint underflow interrupt source (applicable only for Automatic DMA mode) */
#define USBFS_USBDEV_ARB_EP_BUF_UNDER_Msk   USBFS_USBDEV_ARB_EP1_INT_EN_BUF_UNDER_EN_Msk
/** Endpoint Error in Transaction interrupt source */
#define USBFS_USBDEV_ARB_EP_ERR_Msk         USBFS_USBDEV_ARB_EP1_INT_EN_ERR_INT_EN_Msk
/** Data endpoint terminate interrupt source (DMA complete reading) */
#define USBFS_USBDEV_ARB_EP_DMA_TERMIN_Msk  USBFS_USBDEV_ARB_EP1_SR_DMA_TERMIN_Msk
/** \} group_usbfs_dev_drv_reg_macros_arb_ep_intr */

/**
* \addtogroup group_usbfs_dev_drv_reg_macros
* \{
*/
/** Data toggle mask in CNT0 register */
#define USBFS_USBDEV_SIE_EP_DATA_TOGGLE_Msk USBFS_USBDEV_SIE_EP1_CNT0_DATA_TOGGLE_Msk
/** \} group_usbfs_dev_drv_reg_macros */

/** /cond INTERNAL */

/* Extended cyip_usbfs.h */

/* Count registers includes CRC size (2 bytes) */
#define CY_USBFS_DEV_DRV_EP_CRC_SIZE        (2U)

/* DYN_RECONFIG register */
#define USBFS_USBDEV_DYN_RECONFIG_EN_Msk       USBFS_USBDEV_DYN_RECONFIG_DYN_CONFIG_EN_Msk
#define USBFS_USBDEV_DYN_RECONFIG_EPNO_Pos     USBFS_USBDEV_DYN_RECONFIG_DYN_RECONFIG_EPNO_Pos
#define USBFS_USBDEV_DYN_RECONFIG_EPNO_Msk     USBFS_USBDEV_DYN_RECONFIG_DYN_RECONFIG_EPNO_Msk
#define USBFS_USBDEV_DYN_RECONFIG_RDY_STS_Msk  USBFS_USBDEV_DYN_RECONFIG_DYN_RECONFIG_RDY_STS_Msk

/* LPM_CTL register */
#define USBFS_USBLPM_LPM_CTL_LPM_RESP_Pos   (USBFS_USBLPM_LPM_CTL_LPM_ACK_RESP_Pos)
#define USBFS_USBLPM_LPM_CTL_LPM_RESP_Msk   (USBFS_USBLPM_LPM_CTL_LPM_ACK_RESP_Msk | \
                                             USBFS_USBLPM_LPM_CTL_NYET_EN_Msk)

/* ARB_EP_CFG 1-8 registers (default configuration) */
#define USBFS_USBDEV_ARB_EP_CFG_CRC_BYPASS_Msk USBFS_USBDEV_ARB_EP1_CFG_CRC_BYPASS_Msk
#define USBFS_USBDEV_ARB_EP_CFG_RESET_PTR_Msk  USBFS_USBDEV_ARB_EP1_CFG_CRC_BYPASS_Msk
/** /endcond */


/*******************************************************************************
*                         In-line Function Implementation
*******************************************************************************/

/**
* \addtogroup group_usbfs_drv_drv_reg_interrupt_sources
* \{
*/

/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_GetSieInterruptStatus
****************************************************************************//**
*
* Returns the SIE interrupt request register.
* This register contains the current status of the SIE interrupt sources.
*
* \param base
* The pointer to the USBFS instance.
*
* \return
* The current status of the SIE interrupt sources.
* Each constant is a bit field value. The value returned may have multiple
* bits set to indicate the current status.
* See \ref group_usbfs_dev_drv_reg_macros_sie_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetSieInterruptStatus(USBFS_Type const *base)
{
    return USBFS_DEV_LPM_INTR_SIE(base);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_SetSieInterruptMask
****************************************************************************//**
*
* Writes the SIE interrupt mask register.
* This register configures which bits from the SIE interrupt request register
* can trigger an interrupt event.
*
* \param base
* The pointer to the USBFS instance.
*
* \param mask
* Enabled SIE interrupt sources.
* See \ref group_usbfs_dev_drv_reg_macros_sie_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_SetSieInterruptMask(USBFS_Type *base, uint32_t mask)
{
    USBFS_DEV_LPM_INTR_SIE_MASK(base) = mask;
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_GetSieInterruptMask
****************************************************************************//**
*
* Returns the SIE interrupt mask register.
* This register specifies which bits from the SIE interrupt request register
* trigger can an interrupt event.
*
* \param base
* The pointer to the USBFS instance.
*
* \return
* Enabled SIE interrupt sources.
* See \ref group_usbfs_dev_drv_reg_macros_sie_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetSieInterruptMask(USBFS_Type const *base)
{
    return USBFS_DEV_LPM_INTR_SIE_MASK(base);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_GetSieInterruptStatusMasked
****************************************************************************//**
*
* Returns the SIE interrupt masked request register.
* This register contains a logical AND of corresponding bits from the SIE
* interrupt request and mask registers.
* This function is intended to be used in the interrupt service routine to
* identify which of the enabled SIE interrupt sources caused the interrupt
* event.
*
* \param base
* The pointer to the USBFS instance.
*
* \return
* The current status of enabled SIE interrupt sources.
* See \ref group_usbfs_dev_drv_reg_macros_sie_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetSieInterruptStatusMasked(USBFS_Type const *base)
{
    return USBFS_DEV_LPM_INTR_SIE_MASKED(base);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_ClearSieInterrupt
****************************************************************************//**
*
* Clears the SIE interrupt sources in the interrupt request register.
*
* \param base
* The pointer to the USBFS instance.
*
* \param mask
* The SIE interrupt sources to be cleared.
* See \ref group_usbfs_dev_drv_reg_macros_sie_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_ClearSieInterrupt(USBFS_Type *base, uint32_t mask)
{
    USBFS_DEV_LPM_INTR_SIE(base) = mask;
    (void) USBFS_DEV_LPM_INTR_SIE(base);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_SetSieInterrupt
****************************************************************************//**
*
* Sets the SIE interrupt sources in the interrupt request register.
*
* \param base
* The pointer to the USBFS instance.
*
* \param mask
* The SIE interrupt sources to be set in the SIE interrupt request register.
* See \ref group_usbfs_dev_drv_reg_macros_sie_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_SetSieInterrupt(USBFS_Type *base, uint32_t mask)
{
    USBFS_DEV_LPM_INTR_SIE_SET(base) = mask;
}
/** \} group_usbfs_drv_drv_reg_interrupt_sources */


/**
* \addtogroup group_usbfs_drv_drv_reg_ep0_access
* \{
*/
/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_WriteEp0Mode
****************************************************************************//**
*
* Sets a mode in the CR0 register of endpoint 0 (clears all other bits in the
* register).
*
* \param base
* The pointer to the USBFS instance.
*
* \param mode
* SIE mode defines the data endpoint 0 response to a host request.
* See \ref group_usbfs_dev_drv_reg_macros_sie_mode for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_WriteEp0Mode(USBFS_Type *base, uint32_t mode)
{
    USBFS_DEV_EP0_CR(base) = mode;
    (void) USBFS_DEV_EP0_CR(base);
}

/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_ReadEp0Mode
****************************************************************************//**
*
* Returns a mode in the CR0 register of endpoint 0.
*
* \param base
* The pointer to the USBFS instance.
*
* \return
* SIE mode (defines the endpoint 0 response to a host request).
* See \ref group_usbfs_dev_drv_reg_macros_sie_mode for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_ReadEp0Mode(USBFS_Type const *base)
{
    return USBFS_DEV_EP0_CR(base);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_SetSieEpCount
****************************************************************************//**
*
* Configures the number of bytes and toggle bit to return to a host read request
* to endpoint 0.
*
* \param base
* The pointer to the USBFS instance.
*
* \param count
* The number of bytes to return to a host read request.
*
* \param toggle
* The data toggle bit.
* The range of valid values: 0 and \ref USBFS_USBDEV_SIE_EP_DATA_TOGGLE_Msk.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_SetEp0Count(USBFS_Type *base, uint32_t count, uint32_t toggle)
{
    count = _VAL2FLD(USBFS_USBDEV_EP0_CNT_BYTE_COUNT, count);
    USBFS_DEV_EP0_CNT(base) = CY_USBFS_DEV_DRV_WRITE_ODD(count | toggle);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_GetEp0Count
****************************************************************************//**
*
* Returns the number of data bytes written into endpoint 0 by the host.
*
* \param base
* The pointer to the USBFS instance.
*
* \return
* The number of bytes written by the host into the endpoint.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetEp0Count(USBFS_Type const *base)
{
    uint32_t ep0Cnt = CY_USBFS_DEV_READ_ODD(USBFS_DEV_EP0_CNT(base));

    /* Excludes the CRC size */
    return (_FLD2VAL(USBFS_USBDEV_EP0_CNT_BYTE_COUNT, ep0Cnt) - CY_USBFS_DEV_DRV_EP_CRC_SIZE);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_WriteEp0Data
****************************************************************************//**
*
* Writes an 8-bit byte into the endpoint 0 hardware buffer.
*
* \param base
* The pointer to the USBFS instance.
*
* \param idx
* The index of the endpoint 0 hardware buffer entry.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_EP0_BUFFER_SIZE - 1 ).
*
* \param value
* The value to be written into the endpoint 0 hardware buffer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_WriteEp0Data(USBFS_Type *base, uint32_t idx, uint32_t value)
{
    if (0U == (idx & 0x1U))
    {
        USBFS_DEV_EP0_DR(base, idx) = value;
    }
    else
    {
        /* Applies a special write for odd offset registers */
        USBFS_DEV_EP0_DR(base, idx) = CY_USBFS_DEV_DRV_WRITE_ODD(value);
    }
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_ReadEp0Data
****************************************************************************//**
*
* Reads an 8-bit byte from the endpoint 0 hardware buffer.
*
* \param base
* The pointer to the USBFS instance.
*
* \param idx
* The index of the endpoint 0 hardware buffer entry.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_EP0_BUFFER_SIZE - 1 ).
*
* \return
* The byte of data to read from the hardware buffer.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_ReadEp0Data(USBFS_Type const *base, uint32_t idx)
{
    uint32_t value;

    if (0U == (idx & 0x1U))
    {
        value = USBFS_DEV_EP0_DR(base, idx);
    }
    else
    {
        /* Applies a special write for odd offset registers */
        value = CY_USBFS_DEV_READ_ODD(USBFS_DEV_EP0_DR(base, idx));
    }

    return (value);
}
/** \} group_usbfs_drv_drv_reg_ep0_access */


/**
* \addtogroup group_usbfs_drv_drv_reg_sie_access
* \{
*/

/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_SetSieEpMode
****************************************************************************//**
*
* Sets SIE mode in the CR0 register of the endpoint (does not touch other bits).
* All other bits except NAK_INT_EN are cleared by the hardware on any write
* in the register.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
* \param mode
* SIE mode defines data endpoint response to host request.
* See \ref group_usbfs_dev_drv_reg_macros_sie_mode for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_SetSieEpMode(USBFS_Type *base, uint32_t endpoint, uint32_t mode)
{
    USBFS_DEV_SIE_EP_CR0(base, endpoint) = _CLR_SET_FLD32U(USBFS_DEV_SIE_EP_CR0(base, endpoint),
                                                            USBFS_USBDEV_SIE_EP1_CR0_MODE, mode);
    (void) USBFS_DEV_SIE_EP_CR0(base, endpoint);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_GetSieEpMode
****************************************************************************//**
*
* Returns SIE mode in the CR0 register of the endpoint.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
* \return
* SIE mode (defines data endpoint response to host request).
* See \ref group_usbfs_dev_drv_reg_macros_sie_mode for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetSieEpMode(USBFS_Type const *base, uint32_t endpoint)
{
    return (USBFS_DEV_SIE_EP_CR0(base, endpoint) & USBFS_USBDEV_SIE_EP1_CR0_MODE_Msk);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_SetSieEpStall
****************************************************************************//**
*
* Configures endpoint to STALL requests.
*
* \param base
* The pointer to the USBFS instance.
*
* \param inDirection
*  Defines whether endpoint direction is IN (true) or OUT (false).
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_SetSieEpStall(USBFS_Type *base, bool inDirection, uint32_t endpoint)
{
    /* STALL endpoint */
    USBFS_DEV_SIE_EP_CR0(base, endpoint) = USBFS_USBDEV_SIE_EP1_CR0_STALL_Msk |
                                            (inDirection ? CY_USBFS_DEV_DRV_EP_CR_ACK_IN :
                                                           CY_USBFS_DEV_DRV_EP_CR_ACK_OUT);
    (void) USBFS_DEV_SIE_EP_CR0(base, endpoint);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_ClearSieEpStall
****************************************************************************//**
*
* Writes SIE mode register of the data endpoint and clears other bits in this
* register.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
* \param mode
* SIE mode defines data endpoint response to host request.
* See \ref group_usbfs_dev_drv_reg_macros_sie_mode for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_ClearSieEpStall(USBFS_Type *base, uint32_t endpoint, uint32_t mode)
{
    /* Set mode bits */
    uint32_t regVal = _CLR_SET_FLD32U(USBFS_DEV_SIE_EP_CR0(base, endpoint),
                                      USBFS_USBDEV_SIE_EP1_CR0_MODE, mode);

    /* Clear STALL condition */
    regVal &= ~USBFS_USBDEV_SIE_EP1_CR0_STALL_Msk;

    /* Clear STALL condition and set mode */
    USBFS_DEV_SIE_EP_CR0(base, endpoint) = regVal;
    (void) USBFS_DEV_SIE_EP_CR0(base, endpoint);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_GetSieEpError
****************************************************************************//**
*
* Returns value of data endpoint error in transaction bit.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
* \return
* Value of data endpoint error in transaction bit.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetSieEpError(USBFS_Type const *base, uint32_t endpoint)
{
    return (USBFS_DEV_SIE_EP_CR0(base, endpoint) & USBFS_USBDEV_SIE_EP1_CR0_ERR_IN_TXN_Msk);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_GetSieEpToggle
****************************************************************************//**
*
* Returns current value of data endpoint toggle bit.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
* \return
* Value of data endpoint toggle bit.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetSieEpToggle(USBFS_Type const *base, uint32_t endpoint)
{
    /* Return data toggle bit */
    return (USBFS_DEV_SIE_EP_CNT0(base, endpoint) & USBFS_USBDEV_SIE_EP1_CNT0_DATA_TOGGLE_Msk);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_ClearSieEpToggle
****************************************************************************//**
*
* Resets to zero data endpoint toggle bit.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
* \return
* Number of bytes written by the host into the endpoint.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_ClearSieEpToggle(USBFS_Type *base, uint32_t endpoint)
{
    /* Clear data toggle bit */
    USBFS_DEV_SIE_EP_CNT0(base, endpoint) &= ~USBFS_USBDEV_SIE_EP1_CNT0_DATA_TOGGLE_Msk;
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_GetSieEpCount
****************************************************************************//**
*
* Returns the number of data bytes written into the OUT data endpoint
* by the host.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
* \return
* Number of bytes written by the host into the endpoint.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetSieEpCount(USBFS_Type const *base, uint32_t endpoint)
{
    uint32_t size;

    /* Get number of bytes transmitted or received by SIE */
    size = _FLD2VAL(USBFS_USBDEV_SIE_EP1_CNT0_DATA_COUNT_MSB, USBFS_DEV_SIE_EP_CNT0(base, endpoint));
    size = (size << 8U) | CY_USBFS_DEV_READ_ODD(USBFS_DEV_SIE_EP_CNT1(base, endpoint));

    /* Exclude CRC size */
    return (size - CY_USBFS_DEV_DRV_EP_CRC_SIZE);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_SetSieEpCount
****************************************************************************//**
*
* Configures number of bytes and toggle bit to return on the host read request
* to the IN data endpoint.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
* \param count
* The number of bytes to return on the host read request.
*
* \param toggle
* The data toggle bit.
* The range of valid values: 0 and \ref USBFS_USBDEV_SIE_EP_DATA_TOGGLE_Msk.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_SetSieEpCount(USBFS_Type *base, uint32_t endpoint,
                                                    uint32_t count, uint32_t toggle)
{
    USBFS_DEV_SIE_EP_CNT1(base, endpoint) = (uint32_t) CY_USBFS_DEV_DRV_WRITE_ODD(CY_LO8(count));
    USBFS_DEV_SIE_EP_CNT0(base, endpoint) = (uint32_t) CY_HI8(count) | toggle;
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_GetSieAllEpsInterruptStatus
****************************************************************************//**
*
* Returns the SIE data endpoints interrupt request register.
* This register contains the current status of the SIE data endpoints transfer
* completion interrupt.
*
* \param base
* The pointer to the USBFS instance.
*
* \return
* The current status of the SIE interrupt sources.
* The returned status specifies for which endpoint interrupt is active as
* follows: bit 0 corresponds to data endpoint 1, bit 1 data endpoint 2 and so
* on up to \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetSieAllEpsInterruptStatus(USBFS_Type const *base)
{
    return USBFS_DEV_SIE_EP_INT_SR(base);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_EnableSieEpInterrupt
****************************************************************************//**
*
* Enables SIE data endpoint transfer completion interrupt.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_EnableSieEpInterrupt(USBFS_Type *base, uint32_t endpoint)
{
    USBFS_DEV_SIE_EP_INT_EN(base) |= (uint32_t)(1UL << endpoint);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_DisableSieEpInterrupt
****************************************************************************//**
*
* Disables SIE data endpoint transfer completion interrupt.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_DisableSieEpInterrupt(USBFS_Type *base, uint32_t endpoint)
{
    USBFS_DEV_SIE_EP_INT_EN(base) &= ~ (uint32_t)(1UL << endpoint);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_ClearSieEpInterrupt
****************************************************************************//**
*
* Clears the SIE EP interrupt sources in the interrupt request register.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_ClearSieEpInterrupt(USBFS_Type *base, uint32_t endpoint)
{
    USBFS_DEV_SIE_EP_INT_SR(base) = (uint32_t)(1UL << endpoint);
    (void)  USBFS_DEV_SIE_EP_INT_SR(base);
}
/** \} group_usbfs_drv_drv_reg_sie_access */


/**
* \addtogroup group_usbfs_drv_drv_reg_arbiter
* \{
*/

/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_GetArbAllEpsInterruptStatus
****************************************************************************//**
*
* Returns the arbiter interrupt request register.
* This register contains the current status of the data endpoints arbiter
* interrupt.
*
* \param base
* The pointer to the USBFS instance.
*
* \return
* The current status of the SIE interrupt sources.
* The returned status specifies for which endpoint interrupt is active as
* follows: bit 0 corresponds to data endpoint 1, bit 1 data endpoint 2, and so
* on up to \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetArbAllEpsInterruptStatus(USBFS_Type const *base)
{
    return CY_USBFS_DEV_READ_ODD(USBFS_DEV_ARB_INT_SR(base));
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_EnableArbEpInterrupt
****************************************************************************//**
*
* Enables the arbiter interrupt for the specified data endpoint.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_EnableArbEpInterrupt(USBFS_Type *base, uint32_t endpoint)
{
    USBFS_DEV_ARB_INT_EN(base) |= (uint32_t)(1UL << endpoint);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_DisableArbEpInterrupt
****************************************************************************//**
*
* Disabled arbiter interrupt for the specified data endpoint.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_DisableArbEpInterrupt(USBFS_Type *base, uint32_t endpoint)
{
    USBFS_DEV_ARB_INT_EN(base) &= ~(uint32_t)(1UL << endpoint);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_SetArbEpInterruptMask
****************************************************************************//**
*
* Enables the arbiter interrupt sources which trigger the arbiter interrupt for
* the specified data endpoint.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
* \param mask
* The arbiter interrupt sources.
* See \ref group_usbfs_dev_drv_reg_macros_arb_ep_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_SetArbEpInterruptMask(USBFS_Type *base, uint32_t endpoint, uint32_t mask)
{
    USBFS_DEV_ARB_EP_INT_EN(base, endpoint) = mask;
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_GetArbEpInterruptMask
****************************************************************************//**
*
* Returns the arbiter interrupt sources which trigger the arbiter interrupt for
* the specified data endpoint.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
* \return
* The arbiter interrupt sources.
* See \ref group_usbfs_dev_drv_reg_macros_arb_ep_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetArbEpInterruptMask(USBFS_Type const *base, uint32_t endpoint)
{
    return USBFS_DEV_ARB_EP_INT_EN(base, endpoint);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_GetArbEpInterruptStatusMasked
****************************************************************************//**
*
* Returns the current status of the enabled arbiter interrupt sources for
* the specified data endpoint.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
* \return
* The current status of the enabled arbiter interrupt sources
* See \ref group_usbfs_dev_drv_reg_macros_arb_ep_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetArbEpInterruptStatusMasked(USBFS_Type const *base, uint32_t endpoint)
{
    uint32_t mask = CY_USBFS_DEV_READ_ODD(USBFS_DEV_ARB_EP_INT_EN(base, endpoint));
    return (USBFS_DEV_ARB_EP_SR(base, endpoint) & mask);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_ClearArbEpInterrupt
****************************************************************************//**
*
* Clears the current status of the arbiter interrupt sources for the specified
* data endpoint.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
* \param mask
* The arbiter interrupt sources to be cleared.
* See \ref group_usbfs_dev_drv_reg_macros_arb_ep_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_ClearArbEpInterrupt(USBFS_Type *base, uint32_t endpoint, uint32_t mask)
{
    USBFS_DEV_ARB_EP_SR(base, endpoint) = mask;
    (void) USBFS_DEV_ARB_EP_SR(base, endpoint);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_SetArbEpConfig
****************************************************************************//**
*
* Writes the configuration register for the specified data endpoint.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
* \param cfg
* The value written into the data endpoint configuration register.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_SetArbEpConfig(USBFS_Type *base, uint32_t endpoint, uint32_t cfg)
{
    USBFS_DEV_ARB_EP_CFG(base, endpoint) = cfg;
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_SetArbCfgEpInReady
****************************************************************************//**
*
* Notifies hardware that IN endpoint data buffer is read to be loaded in
* the hardware buffer.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_SetArbCfgEpInReady(USBFS_Type *base, uint32_t endpoint)
{
    USBFS_DEV_ARB_EP_CFG(base, endpoint) |= USBFS_USBDEV_ARB_EP1_CFG_IN_DATA_RDY_Msk;
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_ClearArbCfgEpInReady
****************************************************************************//**
*
* Clears hardware notification that IN endpoint data buffer is read to be loaded
* in the hardware buffer. This function needs to be called after buffer was
* copied into the hardware buffer.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).

*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_ClearArbCfgEpInReady(USBFS_Type *base, uint32_t endpoint)
{
    USBFS_DEV_ARB_EP_CFG(base, endpoint) &= ~USBFS_USBDEV_ARB_EP1_CFG_IN_DATA_RDY_Msk;
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_TriggerArbCfgEpDmaReq
****************************************************************************//**
*
* Triggers a DMA request to read from or write data into the hardware buffer.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_TriggerArbCfgEpDmaReq(USBFS_Type *base, uint32_t endpoint)
{
    /* Generates DMA request */
    USBFS_DEV_ARB_EP_CFG(base, endpoint) |=  USBFS_USBDEV_ARB_EP1_CFG_DMA_REQ_Msk;
    (void) USBFS_DEV_ARB_EP_CFG(base, endpoint);
    USBFS_DEV_ARB_EP_CFG(base, endpoint) &= ~USBFS_USBDEV_ARB_EP1_CFG_DMA_REQ_Msk;
    (void) USBFS_DEV_ARB_EP_CFG(base, endpoint);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_SetArbWriteAddr
****************************************************************************//**
*
* Sets write address in the hardware buffer for the specified endpoint.
* This is the start address of the endpoint buffer.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
* \param wa
* Write address value.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_SetArbWriteAddr(USBFS_Type *base, uint32_t endpoint, uint32_t wa)
{
    USBFS_DEV_ARB_RW_WA16(base, endpoint) = wa;
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_SetArbReadAddr
****************************************************************************//**
*
* Sets read address in the hardware buffer for the specified endpoint.
* This is the start address of the endpoint buffer.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
* \param ra
* Read address value.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_SetArbReadAddr(USBFS_Type *base, uint32_t endpoint, uint32_t ra)
{
    USBFS_DEV_ARB_RW_RA16(base, endpoint) = ra;
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_GetArbWriteAddr
****************************************************************************//**
*
* Returns write address in the hardware buffer for the specified endpoint.
* This is the start address of the endpoint buffer.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
* \return
* Write address in the hardware buffer for the specified endpoint.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetArbWriteAddr(USBFS_Type const *base, uint32_t endpoint)
{
    return (USBFS_DEV_ARB_RW_WA16(base, endpoint));
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_GetArbReadAddr
****************************************************************************//**
*
* Returns read address in the hardware buffer for the specified endpoint.
* This is the start address of the endpoint buffer.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
* \return
* Read address in the hardware buffer for the specified endpoint.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetArbReadAddr(USBFS_Type const *base, uint32_t endpoint)
{
    return (USBFS_DEV_ARB_RW_RA16(base, endpoint));
}
/** \} group_usbfs_drv_drv_reg_arbiter */


/**
* \addtogroup group_usbfs_drv_drv_reg_arbiter_data
* \{
*/

/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_WriteData
****************************************************************************//**
*
* Writes a byte (8-bit) into the hardware buffer.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
* \param byte
* The byte of data to be written into the hardware buffer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_WriteData(USBFS_Type *base, uint32_t endpoint, uint8_t byte)
{
    USBFS_DEV_ARB_RW_DR(base, endpoint) = (uint32_t) byte;
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_WriteData16
****************************************************************************//**
*
* Writes a half-word (16-bit) into the hardware buffer.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
* \param halfword
* The half-word of data to be written into the hardware buffer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_WriteData16(USBFS_Type *base, uint32_t endpoint, uint16_t halfword)
{
    USBFS_DEV_ARB_RW_DR16(base, endpoint) = (uint32_t) halfword;
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_ReadData
****************************************************************************//**
*
* Reads a byte (8-bit) from the hardware buffer.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
* \return
* The byte of data to be read from the hardware buffer.
*
*******************************************************************************/
__STATIC_INLINE uint8_t Cy_USBFS_Dev_Drv_ReadData(USBFS_Type const *base, uint32_t endpoint)
{
    return ((uint8_t) USBFS_DEV_ARB_RW_DR(base, endpoint));
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_ReadData16
****************************************************************************//**
*
* Reads a half-word (16-bit) from the hardware buffer.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
* \return
* The half-word of data to be read from the hardware buffer.
*
*******************************************************************************/
__STATIC_INLINE uint16_t Cy_USBFS_Dev_Drv_ReadData16(USBFS_Type const *base, uint32_t endpoint)
{
    return ((uint16_t) USBFS_DEV_ARB_RW_DR16(base, endpoint));
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_GetDataRegAddr
****************************************************************************//**
*
* Returns pointer to the 8-bit data register for the specified endpoint.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
* \return
* The pointer to the 8-bit data register for the specified endpoint.
*
*******************************************************************************/
__STATIC_INLINE volatile uint32_t * Cy_USBFS_Dev_Drv_GetDataRegAddr(USBFS_Type *base, uint32_t endpoint)
{
   return (&USBFS_DEV_ARB_RW_DR(base, endpoint));
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_GetDataReg16Addr
****************************************************************************//**
*
* Returns pointer to the 16-bit data register for the specified endpoint.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range (0 - \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1).
*
* \return
* The pointer to the 16-bit data register for the specified endpoint.
*
*******************************************************************************/
__STATIC_INLINE volatile uint32_t * Cy_USBFS_Dev_Drv_GetDataReg16Addr(USBFS_Type *base, uint32_t endpoint)
{
    return (&USBFS_DEV_ARB_RW_DR16(base, endpoint));
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_FlushInBuffer
****************************************************************************//**
*
* Flushes IN endpoint buffer: sets WA pointer (controlled by CPU/DMA) to equal
* RA (controlled by SIE; gets automatically reset on transfer completion).
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_FlushInBuffer(USBFS_Type *base, uint32_t endpoint)
{
    Cy_USBFS_Dev_Drv_SetArbWriteAddr(base, endpoint,
                     Cy_USBFS_Dev_Drv_GetArbReadAddr(base, endpoint));
}
/** \} group_usbfs_drv_drv_reg_arbiter_data */


/**
* \addtogroup group_usbfs_drv_drv_reg_misc
* \{
*/

/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_SetEpType
****************************************************************************//**
*
* Sets the data endpoint direction.
*
* \param base
* The pointer to the USBFS instance.
*
* \param inDirection
*  Defines whether endpoint direction is IN (true) or OUT (false).
*
* \param endpoint
* Physical endpoint number.
* Valid range: 0 - ( \ref CY_USBFS_DEV_DRV_NUM_EPS_MAX - 1 ).
*
*******************************************************************************/
__STATIC_INLINE void Cy_USBFS_Dev_Drv_SetEpType(USBFS_Type *base, bool inDirection, uint32_t endpoint)
{
    uint32_t mask     = (uint32_t) (0x1UL << endpoint);
    uint32_t regValue = CY_USBFS_DEV_READ_ODD(USBFS_DEV_EP_TYPE(base));

    if (inDirection)
    {
        /* IN direction: clear bit */
        regValue &= ~mask;
    }
    else
    {
        /* OUT direction: set bit */
        regValue |= mask;
    }

    USBFS_DEV_EP_TYPE(base) = CY_USBFS_DEV_DRV_WRITE_ODD(regValue);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_GetSofNubmer
****************************************************************************//**
*
* Returns the SOF frame number.
*
* \param base
* The pointer to the USBFS instance.
*
* \return
* The SOF frame number.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USBFS_Dev_Drv_GetSofNubmer(USBFS_Type const *base)
{
    return _FLD2VAL(USBFS_USBDEV_SOF16_FRAME_NUMBER16, USBFS_DEV_SOF16(base));
}
/** \} group_usbfs_drv_drv_reg_misc */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXUSBFS */

#endif /* (CY_USBFS_DEV_DRV_REG_H) */

/** \endcond */


/* [] END OF FILE */
