/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "sys_driver.h"
#include "gpio_driver.h"
#include <driver/gpio.h>
#include <driver/gpio_types.h>
#include <driver/int.h>
#include "bk_misc.h"
#include "usbd_core.h"
#include "usbh_core.h"
#include "usb_musb_reg.h"

#define USB_BASE_ADDR SOC_USB_REG_BASE

#if (CONFIG_SOC_BK7271)
#define REG_AHB2_USB_OTG_CFG  (*((volatile unsigned char *)(USB_BASE_ADDR + 0x80)))
#define REG_AHB2_USB_DMA_ENDP (*((volatile unsigned char *)(USB_BASE_ADDR + 0x84)))
#define REG_AHB2_USB_VTH      (*((volatile unsigned char *)(USB_BASE_ADDR + 0x88)))
#define REG_AHB2_USB_GEN      (*((volatile unsigned char *)(USB_BASE_ADDR + 0x8C)))
#define REG_AHB2_USB_STAT     (*((volatile unsigned char *)(USB_BASE_ADDR + 0x90)))
#define REG_AHB2_USB_INT      (*((volatile unsigned char *)(USB_BASE_ADDR + 0x94)))
#define REG_AHB2_USB_RESET    (*((volatile unsigned char *)(USB_BASE_ADDR + 0x98)))
#define REG_AHB2_USB_DEV_CFG  (*((volatile unsigned char *)(USB_BASE_ADDR + 0x9C)))
#elif (CONFIG_SOC_BK7256XX)
#define REG_AHB2_USB_OTG_CFG  (*((volatile unsigned char *)(USB_BASE_ADDR + 0x280)))
#define REG_AHB2_USB_DMA_ENDP (*((volatile unsigned char *)(USB_BASE_ADDR + 0x284)))
#define REG_AHB2_USB_VTH      (*((volatile unsigned char *)(USB_BASE_ADDR + 0x288)))
#define REG_AHB2_USB_GEN      (*((volatile unsigned char *)(USB_BASE_ADDR + 0x28C)))
#define REG_AHB2_USB_STAT     (*((volatile unsigned char *)(USB_BASE_ADDR + 0x290)))
#define REG_AHB2_USB_INT      (*((volatile unsigned char *)(USB_BASE_ADDR + 0x294)))
#define REG_AHB2_USB_RESET    (*((volatile unsigned char *)(USB_BASE_ADDR + 0x298)))
#define REG_AHB2_USB_DEV_CFG  (*((volatile unsigned char *)(USB_BASE_ADDR + 0x29C)))
#elif (CONFIG_SOC_BK7236XX) || (CONFIG_SOC_BK7239XX) || (CONFIG_SOC_BK7286XX)
#define REG_AHB2_USB_DEVICE_ID     (*((volatile unsigned char *)(USB_BASE_ADDR + 0x280)))
#define REG_AHB2_USB_VERSION_ID    (*((volatile unsigned char *)(USB_BASE_ADDR + 0x284)))
#define REG_AHB2_USB_GLOBAL_CTRL   (*((volatile unsigned char *)(USB_BASE_ADDR + 0x288)))
#define REG_AHB2_USB_DEVICE_STATUS (*((volatile unsigned char *)(USB_BASE_ADDR + 0x28c)))
#define REG_AHB2_USB_OTG_CFG       (*((volatile unsigned char *)(USB_BASE_ADDR + 0x290)))
#define REG_AHB2_USB_DMA_ENDP      (*((volatile unsigned char *)(USB_BASE_ADDR + 0x294)))
#define REG_AHB2_USB_VTH           (*((volatile unsigned char *)(USB_BASE_ADDR + 0x298)))
#define REG_AHB2_USB_GEN           (*((volatile unsigned char *)(USB_BASE_ADDR + 0x29C)))
#define REG_AHB2_USB_STAT          (*((volatile unsigned char *)(USB_BASE_ADDR + 0x2A0)))
#define REG_AHB2_USB_INT           (*((volatile unsigned char *)(USB_BASE_ADDR + 0x2A4)))
#define REG_AHB2_USB_RESET         (*((volatile unsigned char *)(USB_BASE_ADDR + 0x2A8)))
#define REG_AHB2_USB_DEV_CFG       (*((volatile unsigned char *)(USB_BASE_ADDR + 0x2AC)))

#define REG_USB_USR_700 (*((volatile unsigned long *)(USB_BASE_ADDR + 0x700)))
#define REG_USB_USR_704 (*((volatile unsigned long *)(USB_BASE_ADDR + 0x704)))
#define REG_USB_USR_708 (*((volatile unsigned long *)(USB_BASE_ADDR + 0x708)))
#define REG_USB_USR_70C (*((volatile unsigned long *)(USB_BASE_ADDR + 0x70C)))
#define REG_USB_USR_710 (*((volatile unsigned long *)(USB_BASE_ADDR + 0x710)))
#define REG_USB_USR_714 (*((volatile unsigned long *)(USB_BASE_ADDR + 0x714)))
#define REG_USB_PHY_00  (*((volatile unsigned long *)(USB_BASE_ADDR + 0x400)))
#define REG_USB_PHY_01  (*((volatile unsigned long *)(USB_BASE_ADDR + 0x404)))
#endif

#define USB_DP_CAPABILITY_VALUE (0xF)
#define USB_DN_CAPABILITY_VALUE (0xF)

#define NANENG_PHY_FC_REG01      (0x01 * 4)
#define NANENG_PHY_FC_REG02      (0x02 * 4)
#define NANENG_PHY_FC_REG03      (0x03 * 4)
#define NANENG_PHY_FC_REG04      (0x04 * 4)
#define NANENG_PHY_FC_REG05      (0x05 * 4)
#define NANENG_PHY_FC_REG06      (0x06 * 4)
#define NANENG_PHY_FC_REG07      (0x07 * 4)
#define NANENG_PHY_FC_REG08      (0x08 * 4)
#define NANENG_PHY_FC_REG09      (0x09 * 4)
#define NANENG_PHY_FC_REG0A      (0x0A * 4)
#define NANENG_PHY_FC_REG0B      (0x0B * 4)
#define NANENG_PHY_FC_REG0C      (0x0C * 4)
#define NANENG_PHY_FC_REG0D      (0x0D * 4)
#define NANENG_PHY_FC_REG0E      (0x0E * 4)
#define NANENG_PHY_FC_REG0F      (0x0F * 4)
#define NANENG_PHY_FC_REG0F_BYTE 0x0F

#define NANENG_PHY_FC_REG10 (0x10 * 4)
#define NANENG_PHY_FC_REG11 (0x11 * 4)
#define NANENG_PHY_FC_REG12 (0x12 * 4)
#define NANENG_PHY_FC_REG13 (0x13 * 4)
#define NANENG_PHY_FC_REG14 (0x14 * 4)
#define NANENG_PHY_FC_REG15 (0x15 * 4)
#define NANENG_PHY_FC_REG16 (0x16 * 4)
#define NANENG_PHY_FC_REG17 (0x17 * 4)
#define NANENG_PHY_FC_REG18 (0x18 * 4)
#define NANENG_PHY_FC_REG19 (0x19 * 4)
#define NANENG_PHY_FC_REG1A (0x1A * 4)
#define NANENG_PHY_FC_REG1B (0x1B * 4)
#define NANENG_PHY_FC_REG1C (0x1C * 4)
#define NANENG_PHY_FC_REG1D (0x1D * 4)
#define NANENG_PHY_FC_REG1E (0x1E * 4)
#define NANENG_PHY_FC_REG1F (0x1F * 4)

#if CONFIG_USBDEV_EP_NUM != 8
#error beken chips only support 8 endpoints
#endif

#if CONFIG_USBHOST_PIPE_NUM != 8
#error beken chips only support 8 pipes
#endif

// clang-format off
static struct musb_fifo_cfg musb_device_table[] = {
{ .ep_num =  0, .style = FIFO_TXRX, .maxpacket = 64, },
{ .ep_num =  1, .style = FIFO_TX,   .maxpacket = 1024, },
{ .ep_num =  1, .style = FIFO_RX,   .maxpacket = 1024, },
{ .ep_num =  2, .style = FIFO_TX,   .maxpacket = 512, },
{ .ep_num =  2, .style = FIFO_RX,   .maxpacket = 512, },
{ .ep_num =  3, .style = FIFO_TX,   .maxpacket = 512, },
{ .ep_num =  3, .style = FIFO_RX,   .maxpacket = 512, },
{ .ep_num =  4, .style = FIFO_TX,   .maxpacket = 512, },
{ .ep_num =  4, .style = FIFO_RX,   .maxpacket = 512, },
{ .ep_num =  5, .style = FIFO_TX,   .maxpacket = 512, },
{ .ep_num =  5, .style = FIFO_RX,   .maxpacket = 512, },
{ .ep_num =  6, .style = FIFO_TXRX, .maxpacket = 512, },
{ .ep_num =  7, .style = FIFO_TXRX, .maxpacket = 512, }
};

static struct musb_fifo_cfg musb_host_table[] = {
{ .ep_num =  0, .style = FIFO_TXRX, .maxpacket = 64, },
{ .ep_num =  1, .style = FIFO_TX,   .maxpacket = 1024, },
{ .ep_num =  1, .style = FIFO_RX,   .maxpacket = 1024, },
{ .ep_num =  2, .style = FIFO_TX,   .maxpacket = 512, },
{ .ep_num =  2, .style = FIFO_RX,   .maxpacket = 512, },
{ .ep_num =  3, .style = FIFO_TX,   .maxpacket = 512, },
{ .ep_num =  3, .style = FIFO_RX,   .maxpacket = 512, },
{ .ep_num =  4, .style = FIFO_TX,   .maxpacket = 512, },
{ .ep_num =  4, .style = FIFO_RX,   .maxpacket = 512, },
{ .ep_num =  5, .style = FIFO_TX,   .maxpacket = 512, },
{ .ep_num =  5, .style = FIFO_RX,   .maxpacket = 512, },
{ .ep_num =  6, .style = FIFO_TXRX, .maxpacket = 512, },
{ .ep_num =  7, .style = FIFO_TXRX, .maxpacket = 512, }
};
// clang-format on

uint8_t usbd_get_musb_fifo_cfg(struct musb_fifo_cfg **cfg)
{
    *cfg = musb_device_table;
    return sizeof(musb_device_table) / sizeof(musb_device_table[0]);
}

uint8_t usbh_get_musb_fifo_cfg(struct musb_fifo_cfg **cfg)
{
    *cfg = musb_host_table;
    return sizeof(musb_host_table) / sizeof(musb_host_table[0]);
}

uint32_t usb_get_musb_ram_size(void)
{
    return 8192;
}

extern void USBD_IRQHandler(uint8_t busid);

void USBD_IRQ(void)
{
    USBD_IRQHandler(0);
}

static void bk_analog_layer_usb_sys_related_ops(uint32_t usb_mode, bool ops)
{
    extern void delay(INT32 num);

#if 0
	sys_drv_usb_analog_phy_en(ops, NULL);
	sys_drv_usb_analog_speed_en(ops, NULL);
	sys_drv_usb_analog_ckmcu_en(ops, NULL);
#endif
    if (ops) {
        sys_drv_usb_clock_ctrl(true, NULL);
        delay(100);
#if 0
		sys_drv_usb_analog_deepsleep_en(false);
#endif
        sys_drv_usb_analog_dp_capability(USB_DP_CAPABILITY_VALUE);
        sys_drv_usb_analog_dn_capability(USB_DN_CAPABILITY_VALUE);
        if (!sys_hal_psram_ldo_status()) {
            sys_drv_psram_ldo_enable(1);
        }
        sys_drv_usb_analog_phy_en(1, NULL);

        if (usb_mode == 0) {
            REG_USB_USR_708 = 0x0;
            REG_USB_USR_710 &= ~(0x1 << 7);
            delay(100);

            REG_USB_USR_710 |= (0x1 << 15);
            //REG_USB_USR_710 |= (0x1<<14);
            REG_USB_USR_710 |= (0x1 << 16);
            REG_USB_USR_710 |= (0x1 << 17);
            REG_USB_USR_710 |= (0x1 << 18);
            REG_USB_USR_710 |= (0x1 << 19);
            REG_USB_USR_710 &= ~(0x1 << 20);
            REG_USB_USR_710 |= (0x1 << 21);
            REG_USB_USR_710 |= (0x0 << 0);
            REG_USB_USR_710 |= (0x1 << 5);
            REG_USB_USR_710 |= (0x1 << 6);
            REG_USB_USR_710 |= (0x1 << 9);
            REG_USB_USR_710 |= (0x1 << 10);
            REG_USB_USR_710 |= (0x1 << 1);

            REG_USB_USR_710 |= (0x1 << 7);
            REG_USB_USR_708 = 0x1;
#if 0
			REG_USB_PHY_00   = 0x08;
			REG_USB_PHY_01   = 0x02;
			REG_USB_USR_710 |= (0x1<< 8);
        	while(1){
				reg = REG_USB_USR_70C;
				if(reg & 0x100){
					USB_DRIVER_LOGI("SelfTest Fin!\r\n");
					USB_DRIVER_LOGI("test end!\r\n");
					break;
				} else {
					USB_DRIVER_LOGI("70c_reg:0x%x\r\n", reg);
					delay(10000);
				}
        	}
			REG_USB_PHY_00   &= ~0x08;
			REG_USB_PHY_01   &= ~0x02;
			REG_USB_USR_710 &= ~(0x1<< 8);
#endif
        } else {
            REG_USB_USR_710 |= (0x1 << 15);
            REG_USB_USR_710 |= (0x1 << 14);
            REG_USB_USR_710 |= (0x1 << 16);
            REG_USB_USR_710 |= (0x1 << 17);
            REG_USB_USR_710 |= (0x1 << 18);
            REG_USB_USR_710 |= (0x1 << 19);
            REG_USB_USR_710 &= ~(0x1 << 20);
            REG_USB_USR_710 |= (0x1 << 21);
            REG_USB_USR_710 |= (0x0 << 0);
            REG_USB_USR_710 |= (0x1 << 5);
            REG_USB_USR_710 |= (0x1 << 6);
            REG_USB_USR_710 |= (0x1 << 9);
            REG_USB_USR_710 |= (0x1 << 10);
            REG_USB_USR_710 |= (0x1 << 7);

            REG_USB_USR_708 = 0x1;
        }
    } else {
        sys_drv_usb_analog_phy_en(0, NULL);
        sys_drv_usb_clock_ctrl(false, NULL);
    }
}

void usb_dc_low_level_init(void)
{
#if CONFIG_SYS_CPU0
    bk_pm_module_vote_sleep_ctrl(PM_SLEEP_MODULE_NAME_USB_1, 0x0, 0x0);
#endif
    bk_analog_layer_usb_sys_related_ops(1, true);
    bk_gpio_set_output_high(CONFIG_USB_VBAT_CONTROL_GPIO_ID);

    bk_pm_module_vote_cpu_freq(PM_DEV_ID_USB_1, PM_CPU_FRQ_120M);

    sys_hal_usb_analog_phy_en(true);

    sys_drv_usb_clock_ctrl(true, NULL);
    sys_drv_int_enable(USB_INTERRUPT_CTRL_BIT);

    bk_int_isr_register(INT_SRC_USB, USBD_IRQ, NULL);
    bk_int_set_priority(INT_SRC_USB, 2);
}

void usb_dc_low_level_deinit(void)
{
    bk_pm_module_vote_cpu_freq(PM_DEV_ID_USB_1, PM_CPU_FRQ_DEFAULT);
    sys_hal_usb_analog_phy_en(false);
    sys_drv_usb_clock_ctrl(false, NULL);
    sys_drv_int_disable(USB_INTERRUPT_CTRL_BIT);
    bk_int_isr_unregister(INT_SRC_USB);
    bk_analog_layer_usb_sys_related_ops(1, false);
    sys_drv_dev_clk_pwr_up(CLK_PWR_ID_USB_1, CLK_PWR_CTRL_PWR_DOWN);
}

void usbd_musb_delay_ms(uint8_t ms)
{
    /* implement later */
}

extern void USBH_IRQHandler(uint8_t busid);

void USBH_IRQ(void)
{
    USBH_IRQHandler(0);
}

#define NANENG_PHY_CFG 1
#define USB_PHY_BASE   (SOC_USB_REG_BASE + 0x400)

#define HWREG(x) \
    (*((volatile uint32_t *)(x)))
#define HWREGH(x) \
    (*((volatile uint16_t *)(x)))
#define HWREGB(x) \
    (*((volatile uint8_t *)(x)))

void usb_hc_low_level_init(struct usbh_bus *bus)
{
#if CONFIG_SYS_CPU0
    bk_pm_module_vote_sleep_ctrl(PM_SLEEP_MODULE_NAME_USB_1, 0x0, 0x0);
#endif
    bk_analog_layer_usb_sys_related_ops(0, true);
    bk_gpio_set_output_high(CONFIG_USB_VBAT_CONTROL_GPIO_ID);

#if NANENG_PHY_CFG
    //NANENG_PHY_CFG_HSRX_TEST
    HWREGB(USB_PHY_BASE + NANENG_PHY_FC_REG0F) |= (0x1 << 4);
    //disconnect value 640mv
    HWREGB(USB_PHY_BASE + NANENG_PHY_FC_REG0B) = 0x7C;
#endif
    bk_int_isr_register(INT_SRC_USB, USBH_IRQ, NULL);
    sys_drv_int_enable(USB_INTERRUPT_CTRL_BIT);
}

void usb_hc_low_level_deinit(struct usbh_bus *bus)
{
    sys_drv_int_disable(USB_INTERRUPT_CTRL_BIT);
    bk_int_isr_unregister(INT_SRC_USB);
    sys_drv_dev_clk_pwr_up(CLK_PWR_ID_USB_1, CLK_PWR_CTRL_PWR_DOWN);
    bk_analog_layer_usb_sys_related_ops(0, false);
}