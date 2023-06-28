/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016 - 2017 NXP
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
 * o Neither the name of the copyright holder nor the names of its
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
#ifndef __USB_PHY_H__
#define __USB_PHY_H__

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef struct _usb_phy_config_struct
{
    uint8_t D_CAL;     /* Decode to trim the nominal 17.78mA current source */
    uint8_t TXCAL45DP; /* Decode to trim the nominal 45-Ohm series termination resistance to the USB_DP output pin */
    uint8_t TXCAL45DM; /* Decode to trim the nominal 45-Ohm series termination resistance to the USB_DM output pin */
} usb_phy_config_struct_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief EHCI PHY get USB phy bass address.
 *
 * This function is used to get USB phy bass address.
 *
 * @param[in] controllerId    EHCI controller ID; See the #usb_controller_index_t.
 *
 * @retval USB phy bass address.
 */
extern void *USB_EhciPhyGetBase(uint8_t controllerId);

/*!
 * @brief EHCI PHY initialization.
 *
 * This function initializes the EHCI PHY IP.
 *
 * @param[in] controllerId    EHCI controller ID; See the #usb_controller_index_t.
 * @param[in] freq            The external input clock.
 *
 * @retval kStatus_USB_Success      Cancel successfully.
 * @retval kStatus_USB_Error        The freq value is incorrect.
 */
extern uint32_t USB_EhciPhyInit(uint8_t controllerId, uint32_t freq, usb_phy_config_struct_t *phyConfig);

/*!
 * @brief ehci phy initialization for suspend and resume.
 *
 * This function initialize ehci phy IP for suspend and resume.
 *
 * @param[in] controllerId   ehci controller id, please reference to #usb_controller_index_t.
 * @param[in] freq            the external input clock.
 *                            for example: if the external input clock is 16M, the parameter freq should be 16000000.
 *
 * @retval kStatus_USB_Success      cancel successfully.
 * @retval kStatus_USB_Error        the freq value is incorrect.
 */
extern uint32_t USB_EhciLowPowerPhyInit(uint8_t controllerId, uint32_t freq, usb_phy_config_struct_t *phyConfig);

/*!
 * @brief EHCI PHY deinitialization.
 *
 * This function deinitializes the EHCI PHY IP.
 *
 * @param[in] controllerId   EHCI controller ID; See #usb_controller_index_t.
 */
extern void USB_EhciPhyDeinit(uint8_t controllerId);

/*!
 * @brief EHCI PHY disconnect detection enable or disable.
 *
 * This function enable/disable the host EHCI disconnect detection.
 *
 * @param[in] controllerId   EHCI controller ID; See #usb_controller_index_t.
 * @param[in] enable
 *            1U - enable;
 *            0U - disable;
 */
extern void USB_EhcihostPhyDisconnectDetectCmd(uint8_t controllerId, uint8_t enable);

#if defined(__cplusplus)
}
#endif

#endif /* __USB_PHY_H__ */
