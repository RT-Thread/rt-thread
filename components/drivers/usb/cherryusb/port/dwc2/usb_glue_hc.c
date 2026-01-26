/*
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-08-08     CDT          first version
 */

#include "usbd_core.h"
#include "usbh_core.h"
#include "usb_dwc2_param.h"

#include "board_config.h"

#if defined(RT_CHERRYUSB_HOST) && defined(RT_CHERRYUSB_DEVICE)
    #if defined(HC32F460) || defined(HC32F472)
        #error "Only one USB role can be selected!"
    #endif
#endif

const struct dwc2_user_params param_fs_core =
{
    .phy_type = DWC2_PHY_TYPE_PARAM_FS,
#ifdef CONFIG_USB_DWC2_DMA_ENABLE
    .device_dma_enable = true,
#else
    .device_dma_enable = false,
#endif
    .device_dma_desc_enable = false,
    .device_rx_fifo_size = CONFIG_USB_FS_CORE_DEVICE_RX_FIFO_SIZE,
    .device_tx_fifo_size = {
        [0] =  CONFIG_USB_FS_CORE_DEVICE_TX0_FIFO_SIZE,
        [1] =  CONFIG_USB_FS_CORE_DEVICE_TX1_FIFO_SIZE,
        [2] =  CONFIG_USB_FS_CORE_DEVICE_TX2_FIFO_SIZE,
        [3] =  CONFIG_USB_FS_CORE_DEVICE_TX3_FIFO_SIZE,
        [4] =  CONFIG_USB_FS_CORE_DEVICE_TX4_FIFO_SIZE,
        [5] =  CONFIG_USB_FS_CORE_DEVICE_TX5_FIFO_SIZE,
#if defined(HC32F4A0) || defined(HC32F4A8)
        [6] =  CONFIG_USB_FS_CORE_DEVICE_TX6_FIFO_SIZE,
        [7] =  CONFIG_USB_FS_CORE_DEVICE_TX7_FIFO_SIZE,
        [8] =  CONFIG_USB_FS_CORE_DEVICE_TX8_FIFO_SIZE,
        [9] =  CONFIG_USB_FS_CORE_DEVICE_TX9_FIFO_SIZE,
        [10] = CONFIG_USB_FS_CORE_DEVICE_TX10_FIFO_SIZE,
        [11] = CONFIG_USB_FS_CORE_DEVICE_TX11_FIFO_SIZE,
        [12] = CONFIG_USB_FS_CORE_DEVICE_TX12_FIFO_SIZE,
        [13] = CONFIG_USB_FS_CORE_DEVICE_TX13_FIFO_SIZE,
        [14] = CONFIG_USB_FS_CORE_DEVICE_TX14_FIFO_SIZE,
        [15] = CONFIG_USB_FS_CORE_DEVICE_TX15_FIFO_SIZE
#elif defined(HC32F460) || defined(HC32F472)
        [6] =  0,
        [7] =  0,
        [8] =  0,
        [9] =  0,
        [10] = 0,
        [11] = 0,
        [12] = 0,
        [13] = 0,
        [14] = 0,
        [15] = 0
#endif
    },
    .total_fifo_size = CONFIG_USB_FS_CORE_TOTAL_FIFO_SIZE,

    .host_dma_desc_enable = false,
    .host_rx_fifo_size = CONFIG_USB_FS_CORE_HOST_RX_FIFO_SIZE,
    .host_nperio_tx_fifo_size = CONFIG_USB_FS_CORE_HOST_NP_FIFO_SIZE,
    .host_perio_tx_fifo_size = CONFIG_USB_FS_CORE_HOST_PE_FIFO_SIZE,
    .device_gccfg = 0,
    .host_gccfg = 0,
#if defined(HC32F4A0) || defined(HC32F4A8) || defined(HC32F460)
    .b_session_valid_override = false,
#elif defined(HC32F472)
    .b_session_valid_override = true,
#endif
};

#if defined(HC32F4A0) || defined(HC32F4A8)
const struct dwc2_user_params param_hs_core =
{
#ifdef CONFIG_USB_HS
    .phy_type = DWC2_PHY_TYPE_PARAM_UTMI,
#else
    .phy_type = DWC2_PHY_TYPE_PARAM_FS,
#endif
#ifdef CONFIG_USB_DWC2_DMA_ENABLE
    .device_dma_enable = true,
#else
    .device_dma_enable = false,
#endif
    .device_dma_desc_enable = false,
    .device_rx_fifo_size = CONFIG_USB_HS_CORE_DEVICE_RX_FIFO_SIZE,
    .device_tx_fifo_size = {
        [0] =  CONFIG_USB_HS_CORE_DEVICE_TX0_FIFO_SIZE,
        [1] =  CONFIG_USB_HS_CORE_DEVICE_TX1_FIFO_SIZE,
        [2] =  CONFIG_USB_HS_CORE_DEVICE_TX2_FIFO_SIZE,
        [3] =  CONFIG_USB_HS_CORE_DEVICE_TX3_FIFO_SIZE,
        [4] =  CONFIG_USB_HS_CORE_DEVICE_TX4_FIFO_SIZE,
        [5] =  CONFIG_USB_HS_CORE_DEVICE_TX5_FIFO_SIZE,
        [6] =  CONFIG_USB_HS_CORE_DEVICE_TX6_FIFO_SIZE,
        [7] =  CONFIG_USB_HS_CORE_DEVICE_TX7_FIFO_SIZE,
        [8] =  CONFIG_USB_HS_CORE_DEVICE_TX8_FIFO_SIZE,
        [9] =  CONFIG_USB_HS_CORE_DEVICE_TX9_FIFO_SIZE,
        [10] = CONFIG_USB_HS_CORE_DEVICE_TX10_FIFO_SIZE,
        [11] = CONFIG_USB_HS_CORE_DEVICE_TX11_FIFO_SIZE,
        [12] = CONFIG_USB_HS_CORE_DEVICE_TX12_FIFO_SIZE,
        [13] = CONFIG_USB_HS_CORE_DEVICE_TX13_FIFO_SIZE,
        [14] = CONFIG_USB_HS_CORE_DEVICE_TX14_FIFO_SIZE,
        [15] = CONFIG_USB_HS_CORE_DEVICE_TX15_FIFO_SIZE
    },
    .total_fifo_size = CONFIG_USB_HS_CORE_TOTAL_FIFO_SIZE,

    .host_dma_desc_enable = false,
    .host_rx_fifo_size = CONFIG_USB_HS_CORE_HOST_RX_FIFO_SIZE,
    .host_nperio_tx_fifo_size = CONFIG_USB_HS_CORE_HOST_NP_FIFO_SIZE,
    .host_perio_tx_fifo_size = CONFIG_USB_HS_CORE_HOST_PE_FIFO_SIZE,
    .device_gccfg = 0,
    .host_gccfg = 0,
    .b_session_valid_override = false,
};
#endif

#ifndef CONFIG_USB_DWC2_CUSTOM_PARAM
void dwc2_get_user_params(uint32_t reg_base, struct dwc2_user_params *params)
{
#if defined(HC32F4A0) || defined(HC32F4A8)
    if (reg_base == CM_USBHS_BASE)
    {
        memcpy(params, &param_hs_core, sizeof(struct dwc2_user_params));
    }
    else
#endif
    {
        memcpy(params, &param_fs_core, sizeof(struct dwc2_user_params));
    }
#ifdef CONFIG_USB_DWC2_CUSTOM_FIFO
    struct usb_dwc2_user_fifo_config s_dwc2_fifo_config;

    dwc2_get_user_fifo_config(reg_base, &s_dwc2_fifo_config);

    params->device_rx_fifo_size = s_dwc2_fifo_config.device_rx_fifo_size;
    for (uint8_t i = 0; i < MAX_EPS_CHANNELS; i++)
    {
        params->device_tx_fifo_size[i] = s_dwc2_fifo_config.device_tx_fifo_size[i];
    }
#endif
}
#endif

#define BOARD_INIT_USB_HOST_MODE    (0U)
#define BOARD_INIT_USB_DEVICE_MODE  (1U)
extern rt_err_t rt_hw_usbfs_board_init(uint8_t devmode);
static uint8_t g_usb_fs_busid = 0U;
#if defined(HC32F4A0) || defined(HC32F4A8)
    extern rt_err_t rt_hw_usbhs_board_init(uint8_t devmode);
    static uint8_t g_usb_hs_busid = 0U;
#endif

#if defined(RT_CHERRYUSB_HOST)
static void usbh_fs_irq_handler(void)
{
    USBH_IRQHandler(g_usb_fs_busid);
}

#if defined(HC32F4A0) || defined(HC32F4A8)
static void usbh_hs_irq_handler(void)
{
    USBH_IRQHandler(g_usb_hs_busid);
}
#endif

#if defined(HC32F472)
void USBFS_Handler(void)
{
    usbh_fs_irq_handler();
}
#endif

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    struct hc32_irq_config irq_config;

#if defined(HC32F4A0) || defined(HC32F4A8)
    if (bus->hcd.reg_base == CM_USBHS_BASE)
    {
        g_usb_hs_busid = bus->hcd.hcd_id;

        rt_hw_usbhs_board_init(BOARD_INIT_USB_HOST_MODE);
        FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_USBHS, ENABLE);
#ifndef CONFIG_USB_HS
        /* enable the embedded PHY in USBHS mode */
        CM_PERIC->USB_SYCTLREG |= PERIC_USB_SYCTLREG_USBHS_FSPHYE;
#endif

        irq_config.irq_num = BSP_USBHS_GLB_IRQ_NUM;
        irq_config.int_src = INT_SRC_USBHS_GLB;
        irq_config.irq_prio = BSP_USBHS_GLB_IRQ_PRIO;
        /* register interrupt */
        hc32_install_irq_handler(&irq_config,
                                 usbh_hs_irq_handler,
                                 RT_TRUE);
    }
    else
#endif
    {
        g_usb_fs_busid = bus->hcd.hcd_id;

        rt_hw_usbfs_board_init(BOARD_INIT_USB_HOST_MODE);
        FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_USBFS, ENABLE);

        irq_config.irq_num = BSP_USBFS_GLB_IRQ_NUM;
        irq_config.int_src = INT_SRC_USBFS_GLB;
        irq_config.irq_prio = BSP_USBFS_GLB_IRQ_PRIO;
        /* register interrupt */
        hc32_install_irq_handler(&irq_config,
                                 usbh_fs_irq_handler,
                                 RT_TRUE);
    }

}
#endif

#if defined(RT_CHERRYUSB_DEVICE)
static void usbd_fs_irq_handler(void)
{
    USBD_IRQHandler(g_usb_fs_busid);
}

#if defined(HC32F4A0) || defined(HC32F4A8)
static void usbd_hs_irq_handler(void)
{
    USBD_IRQHandler(g_usb_hs_busid);
}
#endif

#if defined(HC32F472)
void USBFS_Handler(void)
{
    usbd_fs_irq_handler();
}
#endif

void usb_dc_low_level_init(uint8_t busid)
{
    struct hc32_irq_config irq_config;

#if defined(HC32F4A0) || defined(HC32F4A8)
    if (g_usbdev_bus[busid].reg_base == CM_USBHS_BASE)
    {
        g_usb_hs_busid = busid;

        rt_hw_usbhs_board_init(BOARD_INIT_USB_DEVICE_MODE);
        FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_USBHS, ENABLE);

#ifndef CONFIG_USB_HS
        /* enable the embedded PHY in USBHS mode */
        CM_PERIC->USB_SYCTLREG |= PERIC_USB_SYCTLREG_USBHS_FSPHYE;
#endif

        irq_config.irq_num = BSP_USBHS_GLB_IRQ_NUM;
        irq_config.int_src = INT_SRC_USBHS_GLB;
        irq_config.irq_prio = BSP_USBHS_GLB_IRQ_PRIO;
        /* register interrupt */
        hc32_install_irq_handler(&irq_config,
                                 usbd_hs_irq_handler,
                                 RT_TRUE);
    }
    else
#endif
    {
        g_usb_fs_busid = busid;

        rt_hw_usbfs_board_init(BOARD_INIT_USB_DEVICE_MODE);
        FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_USBFS, ENABLE);

        irq_config.irq_num = BSP_USBFS_GLB_IRQ_NUM;
        irq_config.int_src = INT_SRC_USBFS_GLB;
        irq_config.irq_prio = BSP_USBFS_GLB_IRQ_PRIO;
        /* register interrupt */
        hc32_install_irq_handler(&irq_config,
                                 usbd_fs_irq_handler,
                                 RT_TRUE);
    }
}

void usb_dc_low_level_deinit(uint8_t busid)
{
    (void)busid;
    /* reserved */
}

#endif

extern uint32_t SystemCoreClock;

void usbd_dwc2_delay_ms(uint8_t ms)
{
    uint32_t count = SystemCoreClock / 1000 * ms;
    while (count--) {
        __asm volatile("nop");
    }
}

uint32_t usbd_dwc2_get_system_clock(void)
{
    return SystemCoreClock;
}
