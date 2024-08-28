/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_USB_DRV_H
#define HPM_USB_DRV_H
/*---------------------------------------------------------------------
 * Includes
 *---------------------------------------------------------------------
 */
#include "hpm_common.h"
#include "hpm_usb_regs.h"
#include "hpm_soc_feature.h"

/**
 * @brief USB driver APIs
 * @defgroup usb_interface USB driver APIs
 * @ingroup communication_interfaces
 * @{
 */

/*---------------------------------------------------------------------
 *  Macro Constant Declarations
 *---------------------------------------------------------------------
 */
#define USB_PHY_INIT_DELAY_COUNT  (16U) /**< a delay count for USB phy initialization */
#define USB_HOST_FRAMELIST_SIZE   (8U)  /**< a frame list size in USB host mode */

/*---------------------------------------------------------------------
 *  Macro Enum Declarations
 *---------------------------------------------------------------------
 */
/**
 * @brief USB transfer direction types
 */
typedef enum {
    usb_dir_out     = 0,
    usb_dir_in      = 1,
    usb_dir_in_mask = 0x80
} usb_dir_t;    /**< usb_dir_t */

/**
 * @brief USB transfer types
 */
typedef enum {
    usb_xfer_control = 0,
    usb_xfer_isochronous,
    usb_xfer_bulk,
    usb_xfer_interrupt
} usb_xfer_type_t;    /**< usb_xfer_type_t */

/**
 * @brief USB controller work modes
 */
typedef enum {
    usb_ctrl_mode_otg    = 0,
    usb_ctrl_mode_device = 2,
    usb_ctrl_mode_host   = 3
} usb_controller_mode_t;    /**< usb_controller_mode_t */

/**
 * @brief USB line state
 */
typedef enum {
    usb_line_state0 = 0,
    usb_line_state1 = 1,
    usb_line_state2 = 2
} usb_line_state_t;    /**< usb_line_state_t */

/**
 * @brief USB transceiver
 */
typedef enum {
    usb_tran_parallel = 0,
    usb_tran_serial = 1
} usb_transceiver_t;    /**< usb_transceiver_t */

/**
 * @brief USB test modes
 */
typedef enum {
    usb_test_mode_disable = 0,
    usb_test_j_state,
    usb_test_k_state,
    usb_test_se0_nak,
    usb_test_packet,
    usb_test_force_hs,
    usb_test_force_fs,
    usb_test_force_ls,
} usb_test_mode_t;    /**< usb_test_mode_t */

/**
 * @brief USB vbus wakeup source
 */
typedef enum {
    usb_vbus_wakeup_vbus_valid = 0,
    usb_vbus_wakeup_session_valid,
} usb_vbus_wakeup_source_t;    /**< usb_vbus_wakeup_source_t */

/*---------------------------------------------------------------------
 * Structure Declarations
 *---------------------------------------------------------------------
 */
/**
 * @brief Control request structure
 */
typedef struct  __attribute__ ((packed)) {
    union {
        struct  __attribute__ ((packed)) {
            uint8_t recipient :  5;
            uint8_t type      :  2;
            uint8_t direction :  1;
        } bmRequestType_bit;

        uint8_t bmRequestType;
    };

    uint8_t  bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
} usb_control_request_t;

/**
 * @brief Endpoint config structure
 */
typedef struct {
    uint8_t  xfer;
    uint8_t  ep_addr;
    uint16_t max_packet_size;
} usb_endpoint_config_t;

#if defined __cplusplus
extern "C" {
#endif /* __cplusplus */

/*---------------------------------------------------------------------
 * Common API
 *---------------------------------------------------------------------
 */

/**
 * @brief Get the mask of all enabled interrupts
 *
 * @param[in] ptr A USB peripheral base address.
 * @retval Mask of all enabled interrupts.
 */
static inline uint32_t usb_get_interrupts(USB_Type *ptr)
{
    return ptr->USBINTR;
}

/**
 * @brief Enable interrupts
 *
 * @param[in] ptr A USB peripheral base address
 * @param[in] mask Mask value for interrupt events
 */
static inline void usb_enable_interrupts(USB_Type *ptr, uint32_t mask)
{
    ptr->USBINTR |= mask;
}

/**
 * @brief Get all USB status flags
 *
 * @param[in] ptr A USB peripheral base address
 * @retval The USB interrupt status flags
 */
static inline uint32_t usb_get_status_flags(USB_Type *ptr)
{
    return ptr->USBSTS;
}

/**
 * @brief Clear status flags
 *
 * Only the specified flags can be cleared by writing USBSTS register.
 *
 * @param[in] ptr A USB peripheral base address
 * @param[in] mask Mask value for flags to be cleared.
 */

static inline void usb_clear_status_flags(USB_Type *ptr, uint32_t mask)
{
    ptr->USBSTS = mask;
}

/**
 * @brief Enable otg vbus wakeup
 *
 * @param[in] ptr A USB peripheral base address
 */
static inline void usb_otg_enable_vbus_wakeup(USB_Type *ptr)
{
    ptr->OTG_CTRL0 |=  USB_OTG_CTRL0_OTG_VBUS_WAKEUP_EN_MASK;
}

/**
 * @brief Disbable otg vbus wakeup
 *
 * @param[in] ptr A USB peripheral base address
 */
static inline void usb_otg_disable_vbus_wakeup(USB_Type *ptr)
{
    ptr->OTG_CTRL0 &=  ~USB_OTG_CTRL0_OTG_VBUS_WAKEUP_EN_MASK;
}

/**
 * @brief Set otg vbus wakeup source
 *
 * @param[in] ptr A USB peripheral base address
 * @param[in] src wakeup source, @ref usb_vbus_wakeup_source_t
 */
static inline void usb_otg_set_vbus_wakeup_source(USB_Type *ptr, usb_vbus_wakeup_source_t src)
{
    ptr->OTG_CTRL0 = (ptr->OTG_CTRL0 & ~USB_OTG_CTRL0_OTG_VBUS_SOURCE_SEL_MASK) | USB_OTG_CTRL0_OTG_VBUS_SOURCE_SEL_SET(src);
}

/**
 * @brief Enable otg wakeup interrupt
 *
 * @param[in] ptr A USB peripheral base address
 */
static inline void usb_otg_enable_wakeup_int(USB_Type *ptr)
{
    ptr->OTG_CTRL0 |=  USB_OTG_CTRL0_OTG_WAKEUP_INT_ENABLE_MASK;
}

/**
 * @brief Disable otg wakeup interrupt
 *
 * @param[in] ptr A USB peripheral base address
 */
static inline void usb_otg_disable_wakeup_int(USB_Type *ptr)
{
    ptr->OTG_CTRL0 &= ~USB_OTG_CTRL0_OTG_WAKEUP_INT_ENABLE_MASK;
}

/**
 * @brief Get otg wakeup status flags
 *
 * @param[in] ptr A USB peripheral base address
 * @retval The USB otg wakeup interrupt status flag
 */
static inline bool usb_get_otg_wakeup_int_flag(USB_Type *ptr)
{
    return (USB_TOP_STATUS_WAKEUP_INT_STATUS_GET(ptr->TOP_STATUS) != 0) ? true : false;
}

/**
 * @brief Get USB suspend status
 *
 * @param[in] ptr A USB peripheral base address
 * @retval The USB controller suspend status
 */
static inline uint8_t usb_get_suspend_status(USB_Type *ptr)
{
    return USB_PORTSC1_SUSP_GET(ptr->PORTSC1);
}

/**
 * @brief Get USB reset status
 *
 * @param[in] ptr A USB peripheral base address
 * @retval The USB controller reset status
 */
static inline bool usb_get_port_reset_status(USB_Type *ptr)
{
    return USB_PORTSC1_PR_GET(ptr->PORTSC1);
}

/**
 * @brief Get USB current connect status
 *
 * @param[in] ptr A USB peripheral base address
 * @retval The USB controller reset status
 */
static inline bool usb_get_port_ccs(USB_Type *ptr)
{
    return USB_PORTSC1_CCS_GET(ptr->PORTSC1);
}

/**
 * @brief Get USB port speed status
 *
 * @param[in] ptr A USB peripheral base address
 * @retval The USB controller port speed status
 */
static inline uint8_t usb_get_port_speed(USB_Type *ptr)
{
    return USB_PORTSC1_PSPD_GET(ptr->PORTSC1);
}

/**
 * @brief Set port test control mode
 *
 * @param[in] ptr A USB peripheral base address
 * @param[in] test_mode usb test mode, @ref usb_test_mode_t
 */
static inline void usb_set_port_test_mode(USB_Type *ptr, usb_test_mode_t test_mode)
{
    ptr->PORTSC1 = (ptr->PORTSC1 & ~USB_PORTSC1_PTC_MASK) | USB_PORTSC1_PTC_SET(test_mode);
}

/**
 * @brief USB set port suspend
 *
 * @param[in] ptr A USB peripheral base address
 * @param[in] suspend true - suspend, false - not suspend
 */
static inline void usb_set_port_suspend(USB_Type *ptr, bool suspend)
{
    ptr->PORTSC1 = (ptr->PORTSC1 & ~USB_PORTSC1_SUSP_MASK) | USB_PORTSC1_SUSP_SET(suspend);
}

/**
 * @brief USB force port resume
 *
 * @param[in] ptr A USB peripheral base address
 */
static inline void usb_force_port_resume(USB_Type *ptr)
{
    ptr->PORTSC1 |= USB_PORTSC1_FPR_MASK;
}

/**
 * @brief USB phy enter low power suspend
 *
 * @param[in] ptr A USB peripheral base address
 */
static inline void usb_phy_enter_low_power_suspend(USB_Type *ptr)
{
    ptr->PORTSC1 |= USB_PORTSC1_PHCD_MASK;
}

/**
 * @brief USB phy exit low power suspend
 *
 * @param[in] ptr A USB peripheral base address
 */
static inline void usb_phy_exit_low_power_suspend(USB_Type *ptr)
{
    ptr->PORTSC1 &= ~USB_PORTSC1_PHCD_MASK;
    /* otg utmi clock detection */
    ptr->PHY_STATUS |= USB_PHY_STATUS_UTMI_CLK_VALID_MASK;                 /* write 1 to clear valid status */
    while (USB_PHY_STATUS_UTMI_CLK_VALID_GET(ptr->PHY_STATUS) == 0) {      /* get utmi clock status */
        ;
    }
}

/**
 * @brief Get phy session valid flag
 *
 * @param[in] ptr A USB peripheral base address
 * @retval The phy session valid flag
 */
static inline bool usb_phy_get_session_valid_flag(USB_Type *ptr)
{
    return (USB_PHY_STATUS_UTMI_SESS_VALID_GET(ptr->PHY_STATUS) != 0) ? true : false;
}

/**
 * @brief enable otgsc session valid change interrupt
 *
 * @param[in] ptr A USB peripheral base address
 */
static inline void usb_otgsc_enable_session_valid_chg_int(USB_Type *ptr)
{
    ptr->OTGSC |= USB_OTGSC_ASVIE_MASK;
}

/**
 * @brief disable otgsc session valid change interrupt
 *
 * @param[in] ptr A USB peripheral base address
 */
static inline void usb_otgsc_disable_session_valid_chg_int(USB_Type *ptr)
{
    ptr->OTGSC &= ~USB_OTGSC_ASVIE_MASK;
}

/**
 * @brief get otgsc session valid change flag
 *
 * @param[in] ptr A USB peripheral base address
 * @retval The otgsc session valid flag
 */
static inline bool usb_otgsc_get_session_valid_chg_flag(USB_Type *ptr)
{
    return (USB_OTGSC_ASVIS_SET(ptr->OTGSC) != 0) ? true : false;
}

/**
 * @brief clear otgsc session valid change flag
 *
 * @param[in] ptr A USB peripheral base address
 */
static inline void usb_otgsc_clear_session_valid_chg_flag(USB_Type *ptr)
{
    ptr->OTGSC |= USB_OTGSC_ASVIS_MASK;
}

/**
 * @brief Get otgsc session valid flag
 *
 * @param[in] ptr A USB peripheral base address
 * @retval The otgsc session valid flag
 */
static inline bool usb_otgsc_get_session_valid_flag(USB_Type *ptr)
{
    return (USB_OTGSC_ASV_GET(ptr->OTGSC) != 0) ? true : false;
}

/**
 * @brief Initialize USB phy
 *
 * @param[in] ptr A USB peripheral base address
 */
void usb_phy_init(USB_Type *ptr);

/**
 * @brief USB phy get line status
 *
 * @param[in] ptr A USB peripheral base address
 */
static inline uint8_t usb_phy_get_line_state(USB_Type *ptr)
{
    return USB_PHY_STATUS_LINE_STATE_GET(ptr->PHY_STATUS);
}

/**
 * @brief USB phy using internal vbus
 *
 * @param[in] ptr A USB peripheral base address
 */
static inline void usb_phy_using_internal_vbus(USB_Type *ptr)
{
    ptr->PHY_CTRL0 |= (USB_PHY_CTRL0_VBUS_VALID_OVERRIDE_MASK | USB_PHY_CTRL0_SESS_VALID_OVERRIDE_MASK)
                    | (USB_PHY_CTRL0_VBUS_VALID_OVERRIDE_EN_MASK | USB_PHY_CTRL0_SESS_VALID_OVERRIDE_EN_MASK);
}

/**
 * @brief USB phy using external vbus
 *
 * @param[in] ptr A USB peripheral base address
 */
static inline void usb_phy_using_external_vbus(USB_Type *ptr)
{
    ptr->PHY_CTRL0 &= ~((USB_PHY_CTRL0_VBUS_VALID_OVERRIDE_MASK | USB_PHY_CTRL0_SESS_VALID_OVERRIDE_MASK)
                      | (USB_PHY_CTRL0_VBUS_VALID_OVERRIDE_EN_MASK | USB_PHY_CTRL0_SESS_VALID_OVERRIDE_EN_MASK));
}

/**
 * @brief USB phy disconnect dp/dm pins pulldown resistance
 *
 * @param[in] ptr A USB peripheral base address
 */
static inline void usb_phy_disable_dp_dm_pulldown(USB_Type *ptr)
{
    ptr->PHY_CTRL0 |= 0x001000E0u;
}

/**
 * @brief USB phy connect dp/dm pins pulldown resistance
 *
 * @param[in] ptr A USB peripheral base address
 */
static inline void usb_phy_enable_dp_dm_pulldown(USB_Type *ptr)
{
    ptr->PHY_CTRL0 &= ~0x001000E0u;
}

/**
 * @brief Set phyctrl1 not utmi suspend
 *
 * @param[in] ptr A USB peripheral base address
 */
static inline void usb_phyctrl1_set_not_utmi_suspend(USB_Type *ptr)
{
    ptr->PHY_CTRL1 |= USB_PHY_CTRL1_UTMI_OTG_SUSPENDM_MASK;
}

/*---------------------------------------------------------------------
 * Device API
 *---------------------------------------------------------------------
 */

/**
 * @brief USB device bus reset
 *
 * @param[in] ptr A USB peripheral base address
 * @param[in] ep0_max_packet_size The maximum packet size of endpoint 0
 */
void usb_dcd_bus_reset(USB_Type *ptr, uint16_t ep0_max_packet_size);

/**
 * @brief Initialize controller to device mode
 *
 * @param[in] ptr A USB peripheral base address
 */
void usb_dcd_init(USB_Type *ptr);

/**
 * @brief Deinitialize controller to device
 *
 * @param[in] ptr A USB peripheral base address
 */
void usb_dcd_deinit(USB_Type *ptr);

/**
 * @brief Wakeup from host
 *
 * @param[in] ptr A USB peripheral base address
 */
void usb_dcd_remote_wakeup(USB_Type *ptr);

/**
 * @brief Open an endpoint
 *
 * @param[in] ptr A USB peripheral base address
 * @param[in] config A pointer to the specified endpoint config struct
 */
void usb_dcd_edpt_open(USB_Type *ptr, usb_endpoint_config_t *config);

/**
 * @brief get a specified endpoint type
 *
 * @param[in] ptr A USB peripheral base address
 * @param[in] ep_addr Endpoint address
 */
uint8_t usb_dcd_edpt_get_type(USB_Type *ptr, uint8_t ep_addr);

/**
 * @brief Submit a transfer
 *
 * @param[in] ptr A USB peripheral base address
 * @param[in] ep_idx An index of the specified endpoint
 */
void usb_dcd_edpt_xfer(USB_Type *ptr, uint8_t ep_idx);

/**
 * @brief Stall endpoint
 *
 * @param[in] ptr A USB peripheral base address
 * @param[in] ep_addr An address of the specified endpoint
 */
void usb_dcd_edpt_stall(USB_Type *ptr, uint8_t ep_addr);

/**
 * @brief Clear stall
 *
 * @param[in] ptr A USB peripheral base address
 * @param[in] ep_addr An address of the specified endpoint
 */
void usb_dcd_edpt_clear_stall(USB_Type *ptr, uint8_t ep_addr);

/**
 * @brief Clear stall
 *
 * @param[in] ptr A USB peripheral base address
 * @param[in] ep_addr An address of the specified endpoint
 * @retval The status of endpoint stall, true is stall, false is not stall
 */
bool usb_dcd_edpt_check_stall(USB_Type *ptr, uint8_t ep_addr);

/**
 * @brief Close a specified endpoint
 *
 * @param[in] ptr A USB peripheral base address
 * @param[in] ep_addr An address of the specified endpoint
 */
void usb_dcd_edpt_close(USB_Type *ptr, uint8_t ep_addr);

/**
 * @brief Connect by enabling internal pull-up resistor on D+/D-
 *
 * @param[in] ptr A USB peripheral base address
 */
void usb_dcd_connect(USB_Type *ptr);

/**
 * @brief Disconnect by disabling internal pull-up resistor on D+/D-
 *
 * @param[in] ptr A USB peripheral base address
 */
void usb_dcd_disconnect(USB_Type *ptr);

/**
 * @brief Get setup status of endpoint
 *
 * @param[in] ptr A USB peripheral base address
 * @retval The status of setup endpoint
 */
static inline uint32_t usb_dcd_get_edpt_setup_status(USB_Type *ptr)
{
    return ptr->ENDPTSETUPSTAT;
}

/**
 * @brief Clear the setup status of all specified endpoints
 *
 * @param[in] ptr A USB peripheral base address
 * @param[in] mask A mask of all specified endpoints
 */
static inline void usb_dcd_clear_edpt_setup_status(USB_Type *ptr, uint32_t mask)
{
    ptr->ENDPTSETUPSTAT = mask;
}

/**
 * @brief Set address
 *
 * @param[in] ptr A USB peripheral base address
 * @param[in] dev_addr An assigned endpoint address from USB host
 */
static inline void usb_dcd_set_address(USB_Type *ptr, uint8_t dev_addr)
{
    ptr->DEVICEADDR = USB_DEVICEADDR_USBADR_SET(dev_addr) | USB_DEVICEADDR_USBADRA_MASK;
}

/**
 * @brief Set endpoint list address
 *
 * @param[in] ptr A USB peripheral base address
 * @param[in] addr A start address of the endpoint qtd list
 */
static inline void usb_dcd_set_edpt_list_addr(USB_Type *ptr, uint32_t addr)
{
    ptr->ENDPTLISTADDR = addr & USB_ENDPTLISTADDR_EPBASE_MASK;
}

/**
 * @brief Get device address
 *
 * @param[in] ptr A USB peripheral base address
 * @retval The endpoint address
 */
static inline uint8_t usb_dcd_get_device_addr(USB_Type *ptr)
{
    return USB_DEVICEADDR_USBADR_GET(ptr->DEVICEADDR);
}

/**
 * @brief Get complete status of endpoint
 *
 * @param[in] ptr A USB peripheral base address
 * @retval The complete status od endpoint
 */
static inline uint32_t usb_dcd_get_edpt_complete_status(USB_Type *ptr)
{
    return ptr->ENDPTCOMPLETE;
}

/**
 * @brief Clear complete status of endpoint
 *
 * @param[in] ptr A USB peripheral base address
 * @param[in] mask A mask of the specified endpoints
 */
static inline void usb_dcd_clear_edpt_complete_status(USB_Type *ptr, uint32_t mask)
{
    ptr->ENDPTCOMPLETE = mask;
}

/*---------------------------------------------------------------------
 * Host API
 *---------------------------------------------------------------------
 */
/**
 * @brief Initialize controller to host mode
 *
 * @param[in] ptr A USB peripheral base address
 * @param[in] int_mask A mask of all required interrupts
 * @param[in] framelist_size A size of the frame list
 */
bool usb_hcd_init(USB_Type *ptr, uint32_t int_mask, uint16_t framelist_size);

/**
 * @brief Initialize controller to host modeHost Reset port
 *
 * @param[in] ptr A USB peripheral base address
 */
void usb_hcd_port_reset(USB_Type *ptr);

/**
 * @brief Initialize controller to host modeHost set command register
 *
 * @param[in] ptr A USB peripheral base address
 * @param[in] mask A mask of all required commands
 */
static inline void usb_hcd_set_command(USB_Type *ptr, uint32_t mask)
{
    ptr->USBCMD |= mask;
}

/**
 * @brief Get frame index
 *
 * @param[in] ptr A USB peripheral base address
 * @retval A index of the current frame list
 */
static inline uint32_t usb_hcd_get_frame_index(USB_Type *ptr)
{
    return ptr->FRINDEX;
}

/**
 * @brief Get port connect status change
 *
 * @param[in] ptr A USB peripheral base address
 * @retval A connect status change
 */
static inline bool usb_hcd_get_port_csc(USB_Type *ptr)
{
    return USB_PORTSC1_CSC_GET(ptr->PORTSC1);
}

/**
 * @brief Set power ctrl polarity
 *
 * @param[in] ptr A USB peripheral base address
 * @param[in] high true - vbus high level enable, false - vbus low level enable
 */
static inline void usb_hcd_set_power_ctrl_polarity(USB_Type *ptr, bool high)
{
    if (high) {
        ptr->OTG_CTRL0 |= USB_OTG_CTRL0_OTG_POWER_MASK_MASK;
    } else {
        ptr->OTG_CTRL0 &= ~USB_OTG_CTRL0_OTG_POWER_MASK_MASK;
    }
}

/**
 * @brief Enable port power
 *
 * @param[in] ptr A USB peripheral base address
 */
static inline void usb_hcd_enable_port_power(USB_Type *ptr)
{
    ptr->PORTSC1 |= USB_PORTSC1_PP_MASK;
}

/**
 * @brief Get port connect status changeSet async list address
 *
 * @param[in] ptr A USB peripheral base address
 * @param[in] addr An the start address of the async endpoint list
 */
static inline void usb_hcd_set_async_list_addr(USB_Type *ptr, uint32_t addr)
{
    ptr->ASYNCLISTADDR = addr & USB_ASYNCLISTADDR_ASYBASE_MASK;
}

/**
 * @brief Set periodic list address
 *
 * @param[in] ptr A USB peripheral base address
 * @param[in] addr An start address of the periodic endpoint list
 */
static inline void usb_hcd_set_periodic_list_addr(USB_Type *ptr, uint32_t addr)
{
    ptr->PERIODICLISTBASE = addr & USB_PERIODICLISTBASE_BASEADR_MASK;
}

/**
 * @brief Start hcd controller
 *
 * @param[in] ptr A USB peripheral base address
 */
static inline void usb_hcd_run(USB_Type *ptr)
{
    ptr->USBCMD |= USB_USBCMD_RS_MASK;
}

/**
 * @brief Stop hcd controller
 *
 * @param[in] ptr A USB peripheral base address
 */
static inline void usb_hcd_stop(USB_Type *ptr)
{
    ptr->USBCMD &= ~USB_USBCMD_RS_MASK;
}

#if defined __cplusplus
}
#endif /* __cplusplus */

/** @} */
#endif /* HPM_USB_DRV_H */
