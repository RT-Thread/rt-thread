/*
 * Copyright (c) 2021-2023 HPMicro
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "board.h"
#include "hpm_uart_drv.h"
#include "hpm_gptmr_drv.h"
#include "hpm_lcdc_drv.h"
#include "hpm_i2c_drv.h"
#include "hpm_gpio_drv.h"
#include "hpm_debug_console.h"
#include "hpm_femc_drv.h"
#include "pinmux.h"
#include "hpm_pmp_drv.h"
#include "assert.h"
#include "hpm_clock_drv.h"
#include "hpm_sysctl_drv.h"
#include "hpm_sdxc_drv.h"
#include "hpm_pwm_drv.h"
#include "hpm_trgm_drv.h"
#include "hpm_pllctl_drv.h"
#include "hpm_enet_drv.h"
#include "hpm_pcfg_drv.h"

static board_timer_cb timer_cb;

/**
 * @brief FLASH configuration option definitions:
 * option[0]:
 *    [31:16] 0xfcf9 - FLASH configuration option tag
 *    [15:4]  0 - Reserved
 *    [3:0]   option words (exclude option[0])
 * option[1]:
 *    [31:28] Flash probe type
 *      0 - SFDP SDR / 1 - SFDP DDR
 *      2 - 1-4-4 Read (0xEB, 24-bit address) / 3 - 1-2-2 Read(0xBB, 24-bit address)
 *      4 - HyperFLASH 1.8V / 5 - HyperFLASH 3V
 *      6 - OctaBus DDR (SPI -> OPI DDR)
 *      8 - Xccela DDR (SPI -> OPI DDR)
 *      10 - EcoXiP DDR (SPI -> OPI DDR)
 *    [27:24] Command Pads after Power-on Reset
 *      0 - SPI / 1 - DPI / 2 - QPI / 3 - OPI
 *    [23:20] Command Pads after Configuring FLASH
 *      0 - SPI / 1 - DPI / 2 - QPI / 3 - OPI
 *    [19:16] Quad Enable Sequence (for the device support SFDP 1.0 only)
 *      0 - Not needed
 *      1 - QE bit is at bit 6 in Status Register 1
 *      2 - QE bit is at bit1 in Status Register 2
 *      3 - QE bit is at bit7 in Status Register 2
 *      4 - QE bit is at bit1 in Status Register 2 and should be programmed by 0x31
 *    [15:8] Dummy cycles
 *      0 - Auto-probed / detected / default value
 *      Others - User specified value, for DDR read, the dummy cycles should be 2 * cycles on FLASH datasheet
 *    [7:4] Misc.
 *      0 - Not used
 *      1 - SPI mode
 *      2 - Internal loopback
 *      3 - External DQS
 *    [3:0] Frequency option
 *      1 - 30MHz / 2 - 50MHz / 3 - 66MHz / 4 - 80MHz / 5 - 100MHz / 6 - 120MHz / 7 - 133MHz / 8 - 166MHz
 *
 * option[2] (Effective only if the bit[3:0] in option[0] > 1)
 *    [31:20]  Reserved
 *    [19:16] IO voltage
 *      0 - 3V / 1 - 1.8V
 *    [15:12] Pin group
 *      0 - 1st group / 1 - 2nd group
 *    [11:8] Connection selection
 *      0 - CA_CS0 / 1 - CB_CS0 / 2 - CA_CS0 + CB_CS0 (Two FLASH connected to CA and CB respectively)
 *    [7:0] Drive Strength
 *      0 - Default value
 * option[3] (Effective only if the bit[3:0] in option[0] > 2, required only for the QSPI NOR FLASH that not supports
 *              JESD216)
 *    [31:16] reserved
 *    [15:12] Sector Erase Command Option, not required here
 *    [11:8]  Sector Size Option, not required here
 *    [7:0] Flash Size Option
 *      0 - 4MB / 1 - 8MB / 2 - 16MB
 */
#if defined(FLASH_XIP) && FLASH_XIP
__attribute__ ((section(".nor_cfg_option"))) const uint32_t option[4] = {0xfcf90001, 0x00000007, 0x0, 0x0};
#endif

#if defined(FLASH_UF2) && FLASH_UF2
ATTR_PLACE_AT(".uf2_signature") const uint32_t uf2_signature = BOARD_UF2_SIGNATURE;
#endif

void board_init_console(void)
{
#if BOARD_CONSOLE_TYPE == CONSOLE_TYPE_UART
    console_config_t cfg;

    /* Configure the UART clock to 24MHz */
    clock_set_source_divider(BOARD_CONSOLE_CLK_NAME, clk_src_osc24m, 1U);

    cfg.type = BOARD_CONSOLE_TYPE;
    cfg.base = (uint32_t) BOARD_CONSOLE_BASE;
    cfg.src_freq_in_hz = clock_get_frequency(BOARD_CONSOLE_CLK_NAME);
    cfg.baudrate = BOARD_CONSOLE_BAUDRATE;

    init_uart_pins((UART_Type *) cfg.base);

    if (status_success != console_init(&cfg)) {
        /* failed to  initialize debug console */
        while (1) {
        }
    }
#else
    while(1);
#endif
}

void board_print_clock_freq(void)
{
    printf("==============================\n");
    printf(" %s clock summary\n", BOARD_NAME);
    printf("==============================\n");
    printf("cpu0:\t\t %luHz\n", clock_get_frequency(clock_cpu0));
    printf("cpu1:\t\t %luHz\n", clock_get_frequency(clock_cpu1));
    printf("axi0:\t\t %luHz\n", clock_get_frequency(clock_axi0));
    printf("axi1:\t\t %luHz\n", clock_get_frequency(clock_axi1));
    printf("axi2:\t\t %luHz\n", clock_get_frequency(clock_axi2));
    printf("ahb:\t\t %luHz\n", clock_get_frequency(clock_ahb));
    printf("mchtmr0:\t %luHz\n", clock_get_frequency(clock_mchtmr0));
    printf("mchtmr1:\t %luHz\n", clock_get_frequency(clock_mchtmr1));
    printf("xpi0:\t\t %luHz\n", clock_get_frequency(clock_xpi0));
    printf("xpi1:\t\t %luHz\n", clock_get_frequency(clock_xpi1));
    printf("femc:\t\t %luHz\n", clock_get_frequency(clock_femc));
    printf("display:\t %luHz\n", clock_get_frequency(clock_display));
    printf("cam0:\t\t %luHz\n", clock_get_frequency(clock_camera0));
    printf("cam1:\t\t %luHz\n", clock_get_frequency(clock_camera1));
    printf("jpeg:\t\t %luHz\n", clock_get_frequency(clock_jpeg));
    printf("pdma:\t\t %luHz\n", clock_get_frequency(clock_pdma));
    printf("==============================\n");
}

void board_init_uart(UART_Type *ptr)
{
    init_uart_pins(ptr);
    board_init_uart_clock(ptr);
}

void board_init_ahb(void)
{
    clock_set_source_divider(clock_ahb,clk_src_pll1_clk1,2);/*200m hz*/
}

void board_print_banner(void)
{
    const uint8_t banner[] = {"\n\
----------------------------------------------------------------------\n\
$$\\   $$\\ $$$$$$$\\  $$\\      $$\\ $$\\\n\
$$ |  $$ |$$  __$$\\ $$$\\    $$$ |\\__|\n\
$$ |  $$ |$$ |  $$ |$$$$\\  $$$$ |$$\\  $$$$$$$\\  $$$$$$\\   $$$$$$\\\n\
$$$$$$$$ |$$$$$$$  |$$\\$$\\$$ $$ |$$ |$$  _____|$$  __$$\\ $$  __$$\\\n\
$$  __$$ |$$  ____/ $$ \\$$$  $$ |$$ |$$ /      $$ |  \\__|$$ /  $$ |\n\
$$ |  $$ |$$ |      $$ |\\$  /$$ |$$ |$$ |      $$ |      $$ |  $$ |\n\
$$ |  $$ |$$ |      $$ | \\_/ $$ |$$ |\\$$$$$$$\\ $$ |      \\$$$$$$  |\n\
\\__|  \\__|\\__|      \\__|     \\__|\\__| \\_______|\\__|       \\______/\n\
----------------------------------------------------------------------\n"};
    printf("%s", banner);
}

static void board_turnoff_rgb_led(void)
{
    uint32_t pad_ctl = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
    HPM_IOC->PAD[IOC_PAD_PB11].FUNC_CTL = IOC_PB11_FUNC_CTL_GPIO_B_11;
    HPM_IOC->PAD[IOC_PAD_PB12].FUNC_CTL = IOC_PB12_FUNC_CTL_GPIO_B_12;
    HPM_IOC->PAD[IOC_PAD_PB13].FUNC_CTL = IOC_PB13_FUNC_CTL_GPIO_B_13;

    HPM_IOC->PAD[IOC_PAD_PB11].PAD_CTL = pad_ctl;
    HPM_IOC->PAD[IOC_PAD_PB12].PAD_CTL = pad_ctl;
    HPM_IOC->PAD[IOC_PAD_PB13].PAD_CTL = pad_ctl;
}

void board_ungate_mchtmr_at_lp_mode(void)
{
    /* Keep cpu clock on wfi, so that mchtmr irq can still work after wfi */
    sysctl_set_cpu_lp_mode(HPM_SYSCTL, BOARD_RUNNING_CORE, cpu_lp_mode_ungate_cpu_clock);
}

void board_init(void)
{
    board_turnoff_rgb_led();
    board_init_clock();
    board_init_console();
    board_init_pmp();
    board_init_ahb();
#if BOARD_SHOW_CLOCK
    board_print_clock_freq();
#endif
#if BOARD_SHOW_BANNER
    board_print_banner();
#endif
}

void board_init_sdram_pins(void)
{
    init_sdram_pins();
}

uint32_t board_init_femc_clock(void)
{
    clock_set_source_divider(clock_femc, clk_src_pll2_clk0, 2U); /* 166Mhz */
    /* clock_set_source_divider(clock_femc, clk_src_pll1_clk1, 2U); [> 200Mhz <] */

    return clock_get_frequency(clock_femc);
}

void board_power_cycle_lcd(void)
{
    /* turn off backlight */
    gpio_set_pin_output(BOARD_LCD_BACKLIGHT_GPIO_BASE, BOARD_LCD_BACKLIGHT_GPIO_INDEX, BOARD_LCD_BACKLIGHT_GPIO_PIN);
    gpio_write_pin(BOARD_LCD_BACKLIGHT_GPIO_BASE, BOARD_LCD_BACKLIGHT_GPIO_INDEX, BOARD_LCD_BACKLIGHT_GPIO_PIN, 0);

    board_delay_ms(150);
    /* power recycle */
    gpio_set_pin_output(BOARD_LCD_POWER_GPIO_BASE, BOARD_LCD_POWER_GPIO_INDEX, BOARD_LCD_POWER_GPIO_PIN);
    gpio_write_pin(BOARD_LCD_POWER_GPIO_BASE, BOARD_LCD_POWER_GPIO_INDEX, BOARD_LCD_POWER_GPIO_PIN, 0);
    board_delay_ms(150);
    gpio_write_pin(BOARD_LCD_POWER_GPIO_BASE, BOARD_LCD_POWER_GPIO_INDEX, BOARD_LCD_POWER_GPIO_PIN, 1);
    board_delay_ms(150);

    /* turn on backlight */
    gpio_write_pin(BOARD_LCD_BACKLIGHT_GPIO_BASE, BOARD_LCD_BACKLIGHT_GPIO_INDEX, BOARD_LCD_BACKLIGHT_GPIO_PIN, 1);

}

void board_init_lcd(void)
{
    board_init_lcd_clock();
    init_lcd_pins(BOARD_LCD_BASE);

    board_power_cycle_lcd();
}

void board_panel_para_to_lcdc(lcdc_config_t *config)
{
    const uint16_t panel_timing_para[] = BOARD_PANEL_TIMING_PARA;

    config->resolution_x = BOARD_LCD_WIDTH;
    config->resolution_y = BOARD_LCD_HEIGHT;

    config->hsync.pulse_width = panel_timing_para[BOARD_PANEL_TIMEING_PARA_HSPW_INDEX];
    config->hsync.back_porch_pulse = panel_timing_para[BOARD_PANEL_TIMEING_PARA_HBP_INDEX];
    config->hsync.front_porch_pulse = panel_timing_para[BOARD_PANEL_TIMEING_PARA_HFP_INDEX];

    config->vsync.pulse_width = panel_timing_para[BOARD_PANEL_TIMEING_PARA_VSPW_INDEX];
    config->vsync.back_porch_pulse = panel_timing_para[BOARD_PANEL_TIMEING_PARA_VBP_INDEX];
    config->vsync.front_porch_pulse = panel_timing_para[BOARD_PANEL_TIMEING_PARA_VFP_INDEX];

    config->control.invert_hsync = panel_timing_para[BOARD_PANEL_TIMEING_PARA_HSSP_INDEX];
    config->control.invert_vsync = panel_timing_para[BOARD_PANEL_TIMEING_PARA_VSSP_INDEX];
    config->control.invert_href = panel_timing_para[BOARD_PANEL_TIMEING_PARA_DESP_INDEX];
    config->control.invert_pixel_data = panel_timing_para[BOARD_PANEL_TIMEING_PARA_PDSP_INDEX];
    config->control.invert_pixel_clock = panel_timing_para[BOARD_PANEL_TIMEING_PARA_PCSP_INDEX];
}

void board_delay_ms(uint32_t ms)
{
    clock_cpu_delay_ms(ms);
}

void board_timer_isr(void)
{
    if (gptmr_check_status(BOARD_CALLBACK_TIMER, GPTMR_CH_RLD_STAT_MASK(BOARD_CALLBACK_TIMER_CH))) {
        gptmr_clear_status(BOARD_CALLBACK_TIMER, GPTMR_CH_RLD_STAT_MASK(BOARD_CALLBACK_TIMER_CH));
        timer_cb();
    }
}
SDK_DECLARE_EXT_ISR_M(BOARD_CALLBACK_TIMER_IRQ, board_timer_isr);

void board_timer_create(uint32_t ms, board_timer_cb cb)
{
    uint32_t gptmr_freq;
    gptmr_channel_config_t config;

    timer_cb = cb;
    gptmr_channel_get_default_config(BOARD_CALLBACK_TIMER, &config);

    clock_add_to_group(BOARD_CALLBACK_TIMER_CLK_NAME, 0);
    gptmr_freq = clock_get_frequency(BOARD_CALLBACK_TIMER_CLK_NAME);

    config.reload = gptmr_freq / 1000 * ms;
    gptmr_channel_config(BOARD_CALLBACK_TIMER, BOARD_CALLBACK_TIMER_CH, &config, false);
    gptmr_enable_irq(BOARD_CALLBACK_TIMER, GPTMR_CH_RLD_IRQ_MASK(BOARD_CALLBACK_TIMER_CH));
    intc_m_enable_irq_with_priority(BOARD_CALLBACK_TIMER_IRQ, 1);

    gptmr_start_counter(BOARD_CALLBACK_TIMER, BOARD_CALLBACK_TIMER_CH);
}

void board_i2c_bus_clear(I2C_Type *ptr)
{
    init_i2c_pins_as_gpio(ptr);
    if (ptr == BOARD_CAP_I2C_BASE) {
        gpio_set_pin_input(BOARD_LED_GPIO_CTRL, BOARD_CAP_I2C_SDA_GPIO_INDEX, BOARD_CAP_I2C_SDA_GPIO_PIN);
        gpio_set_pin_input(BOARD_LED_GPIO_CTRL, BOARD_CAP_I2C_CLK_GPIO_INDEX, BOARD_CAP_I2C_CLK_GPIO_PIN);
        if (!gpio_read_pin(BOARD_LED_GPIO_CTRL, BOARD_CAP_I2C_CLK_GPIO_INDEX, BOARD_CAP_I2C_CLK_GPIO_PIN)) {
            printf("CLK is low, please power cycle the board\n");
            while (1) {}
        }
        if (!gpio_read_pin(BOARD_LED_GPIO_CTRL, BOARD_CAP_I2C_SDA_GPIO_INDEX, BOARD_CAP_I2C_SDA_GPIO_PIN)) {
            printf("SDA is low, try to issue I2C bus clear\n");
        } else {
            printf("I2C bus is ready\n");
            return;
        }

        gpio_set_pin_output(BOARD_LED_GPIO_CTRL, BOARD_CAP_I2C_CLK_GPIO_INDEX, BOARD_CAP_I2C_CLK_GPIO_PIN);
        while (1) {
            for (uint32_t i = 0; i < 9; i++) {
                gpio_write_pin(BOARD_LED_GPIO_CTRL, BOARD_CAP_I2C_CLK_GPIO_INDEX, BOARD_CAP_I2C_CLK_GPIO_PIN, 1);
                board_delay_ms(10);
                gpio_write_pin(BOARD_LED_GPIO_CTRL, BOARD_CAP_I2C_CLK_GPIO_INDEX, BOARD_CAP_I2C_CLK_GPIO_PIN, 0);
                board_delay_ms(10);
            }
            board_delay_ms(100);
        }
        printf("I2C bus is cleared\n");
    }
}

void board_init_i2c(I2C_Type *ptr)
{
    hpm_stat_t stat;
    uint32_t freq;
    i2c_config_t config;

    board_i2c_bus_clear(ptr);

    init_i2c_pins(ptr);
    clock_add_to_group(clock_i2c0, 0);
    clock_add_to_group(clock_i2c1, 0);
    clock_add_to_group(clock_i2c2, 0);
    clock_add_to_group(clock_i2c3, 0);
    /* Configure the I2C clock to 24MHz */
    clock_set_source_divider(BOARD_CAP_I2C_CLK_NAME, clk_src_osc24m, 1U);

    config.i2c_mode = i2c_mode_normal;
    config.is_10bit_addressing = false;
    freq = clock_get_frequency(BOARD_CAP_I2C_CLK_NAME);
    stat = i2c_init_master(BOARD_CAP_I2C_BASE, freq, &config);
    if (stat != status_success) {
        printf("failed to initialize i2c 0x%x\n", (uint32_t)BOARD_CAP_I2C_BASE);
        while (1) {}
    }
}

uint32_t board_init_uart_clock(UART_Type *ptr)
{
    uint32_t freq = 0;
    clock_name_t clock_name = clock_uart0;
    bool need_init_clock = true;
    if (ptr == HPM_UART0) {
        clock_name = clock_uart0;
    } else if (ptr == HPM_UART1) {
        clock_name = clock_uart1;
    } else if (ptr == HPM_UART2) {
        clock_name = clock_uart2;
    } else if (ptr == HPM_UART3) {
        clock_name = clock_uart3;
    } else if (ptr == HPM_UART4) {
        clock_name = clock_uart4;
    } else if (ptr == HPM_UART5) {
        clock_name = clock_uart5;
    } else if (ptr == HPM_UART6) {
        clock_name = clock_uart6;
    } else if (ptr == HPM_UART7) {
        clock_name = clock_uart7;
    } else if (ptr == HPM_UART8) {
        clock_name = clock_uart8;
    } else if (ptr == HPM_UART9) {
        clock_name = clock_uart9;
    } else if (ptr == HPM_UART10) {
        clock_name = clock_uart10;
    } else if (ptr == HPM_UART11) {
        clock_name = clock_uart11;
    } else if (ptr == HPM_UART12) {
        clock_name = clock_uart12;
    } else if (ptr == HPM_UART13) {
        clock_name = clock_uart13;
    } else if (ptr == HPM_UART14) {
        clock_name = clock_uart14;
    } else if (ptr == HPM_UART15) {
        clock_name = clock_uart15;
    } else {
        /* Unsupported instance */
        need_init_clock = false;
    }

    if (need_init_clock) {
        clock_set_source_divider(clock_name, clk_src_osc24m, 1);
        clock_add_to_group(clock_name, 0);
        freq = clock_get_frequency(clock_name);
    }

    return freq;
}

uint32_t board_init_spi_clock(SPI_Type *ptr)
{
    if (ptr == HPM_SPI2) {
        /* SPI2 clock configure */
        clock_add_to_group(clock_spi2, 0);
        clock_set_source_divider(clock_spi2, clk_src_osc24m, 1U);

        return clock_get_frequency(clock_spi2);
    }
    return 0;
}

void board_init_cap_touch(void)
{
    init_cap_pins();
    gpio_set_pin_output_with_initial(BOARD_CAP_RST_GPIO, BOARD_CAP_RST_GPIO_INDEX, BOARD_CAP_RST_GPIO_PIN, 0);
    gpio_set_pin_output_with_initial(BOARD_CAP_INTR_GPIO, BOARD_CAP_INTR_GPIO_INDEX, BOARD_CAP_INTR_GPIO_PIN, 0);

    board_delay_ms(1);
    gpio_write_pin(BOARD_CAP_INTR_GPIO, BOARD_CAP_INTR_GPIO_INDEX, BOARD_CAP_INTR_GPIO_PIN, 1);
    board_delay_ms(10);
    gpio_write_pin(BOARD_CAP_RST_GPIO, BOARD_CAP_RST_GPIO_INDEX, BOARD_CAP_RST_GPIO_PIN, 1);

    gpio_set_pin_input(BOARD_CAP_INTR_GPIO, BOARD_CAP_INTR_GPIO_INDEX, BOARD_CAP_INTR_GPIO_PIN);
    board_init_i2c(BOARD_CAP_I2C_BASE);
}

void board_init_gpio_pins(void)
{
    init_gpio_pins();
}

void board_init_spi_pins(SPI_Type *ptr)
{
    init_spi_pins(ptr);
}

void board_init_led_pins(void)
{
    init_led_pins_as_gpio();
    gpio_set_pin_output_with_initial(BOARD_R_GPIO_CTRL, BOARD_R_GPIO_INDEX, BOARD_R_GPIO_PIN, BOARD_LED_OFF_LEVEL);
    gpio_set_pin_output_with_initial(BOARD_G_GPIO_CTRL, BOARD_G_GPIO_INDEX, BOARD_G_GPIO_PIN, BOARD_LED_OFF_LEVEL);
    gpio_set_pin_output_with_initial(BOARD_B_GPIO_CTRL, BOARD_B_GPIO_INDEX, BOARD_B_GPIO_PIN, BOARD_LED_OFF_LEVEL);
}

void board_led_toggle(void)
{
#ifdef BOARD_LED_TOGGLE_RGB
    static uint8_t i;
    gpio_write_port(BOARD_R_GPIO_CTRL, BOARD_R_GPIO_INDEX, (7 & ~(1 << i)) << BOARD_R_GPIO_PIN);
    i++;
    i = i % 3;
#else
    gpio_toggle_pin(BOARD_LED_GPIO_CTRL, BOARD_LED_GPIO_INDEX, BOARD_LED_GPIO_PIN);
#endif
}

void board_led_write(uint8_t state)
{
    gpio_write_pin(BOARD_LED_GPIO_CTRL, BOARD_LED_GPIO_INDEX, BOARD_LED_GPIO_PIN, state);
}

void board_init_cam_pins(void)
{
    init_cam_pins();
    /* enable cam RST pin out with high level */
    gpio_set_pin_output_with_initial(BOARD_CAM_RST_GPIO_CTRL, BOARD_CAM_RST_GPIO_INDEX, BOARD_CAM_RST_GPIO_PIN, 1);
}

void board_write_cam_rst(uint8_t state)
{
    gpio_write_pin(BOARD_CAM_RST_GPIO_CTRL, BOARD_CAM_RST_GPIO_INDEX, BOARD_CAM_RST_GPIO_PIN, state);

}

void board_init_usb_pins(void)
{
    /* set pull-up for USBx OC pins and ID pins */
    init_usb_pins();

    /* configure USBx ID pins as input function */
    gpio_set_pin_input(BOARD_USB0_ID_PORT, BOARD_USB0_ID_GPIO_INDEX, BOARD_USB0_ID_GPIO_PIN);
    gpio_set_pin_input(BOARD_USB1_ID_PORT, BOARD_USB1_ID_GPIO_INDEX, BOARD_USB1_ID_GPIO_PIN);

    /* configure USBx OC Flag pins as input function */
    gpio_set_pin_input(BOARD_USB0_OC_PORT, BOARD_USB0_OC_GPIO_INDEX, BOARD_USB0_OC_GPIO_PIN);
    gpio_set_pin_input(BOARD_USB1_OC_PORT, BOARD_USB1_OC_GPIO_INDEX, BOARD_USB1_OC_GPIO_PIN);
}

void board_usb_vbus_ctrl(uint8_t usb_index, uint8_t level)
{
}

void board_init_pmp(void)
{
    extern uint32_t __noncacheable_start__[];
    extern uint32_t __noncacheable_end__[];

    uint32_t start_addr = (uint32_t) __noncacheable_start__;
    uint32_t end_addr = (uint32_t) __noncacheable_end__;
    uint32_t length = end_addr - start_addr;

    if (length == 0) {
        return;
    }

    /* Ensure the address and the length are power of 2 aligned */
    assert((length & (length - 1U)) == 0U);
    assert((start_addr & (length - 1U)) == 0U);

    pmp_entry_t pmp_entry[1];
    pmp_entry[0].pmp_addr = PMP_NAPOT_ADDR(start_addr, length);
    pmp_entry[0].pmp_cfg.val = PMP_CFG(READ_EN, WRITE_EN, EXECUTE_EN, ADDR_MATCH_NAPOT, REG_UNLOCK);
    pmp_entry[0].pma_addr = PMA_NAPOT_ADDR(start_addr, length);
    pmp_entry[0].pma_cfg.val = PMA_CFG(ADDR_MATCH_NAPOT, MEM_TYPE_MEM_NON_CACHE_BUF, AMO_EN);

    pmp_config(&pmp_entry[0], ARRAY_SIZE(pmp_entry));
}

void board_init_clock(void)
{
    uint32_t cpu0_freq = clock_get_frequency(clock_cpu0);
    hpm_core_clock = cpu0_freq;
    if (cpu0_freq == PLLCTL_SOC_PLL_REFCLK_FREQ) {
        /* Configure the External OSC ramp-up time: ~9ms */
        pllctl_xtal_set_rampup_time(HPM_PLLCTL, 32UL * 1000UL * 9U);

        /* Select clock setting preset1 */
        sysctl_clock_set_preset(HPM_SYSCTL, sysctl_preset_1);
    }

    /* Add most Clocks to group 0 */
    clock_add_to_group(clock_cpu0, 0);
    clock_add_to_group(clock_mchtmr0, 0);
    clock_add_to_group(clock_axi0, 0);
    clock_add_to_group(clock_axi1, 0);
    clock_add_to_group(clock_axi2, 0);
    clock_add_to_group(clock_ahb, 0);
    clock_add_to_group(clock_femc, 0);
    clock_add_to_group(clock_xpi0, 0);
    clock_add_to_group(clock_xpi1, 0);
    clock_add_to_group(clock_gptmr0, 0);
    clock_add_to_group(clock_gptmr1, 0);
    clock_add_to_group(clock_gptmr2, 0);
    clock_add_to_group(clock_gptmr3, 0);
    clock_add_to_group(clock_gptmr4, 0);
    clock_add_to_group(clock_gptmr5, 0);
    clock_add_to_group(clock_gptmr6, 0);
    clock_add_to_group(clock_gptmr7, 0);
    clock_add_to_group(clock_uart0, 0);
    clock_add_to_group(clock_i2c0, 0);
    clock_add_to_group(clock_i2c1, 0);
    clock_add_to_group(clock_i2c2, 0);
    clock_add_to_group(clock_i2c3, 0);
    clock_add_to_group(clock_spi0, 0);
    clock_add_to_group(clock_spi1, 0);
    clock_add_to_group(clock_spi2, 0);
    clock_add_to_group(clock_spi3, 0);
    clock_add_to_group(clock_can0, 0);
    clock_add_to_group(clock_can1, 0);
    clock_add_to_group(clock_can2, 0);
    clock_add_to_group(clock_can3, 0);
    clock_add_to_group(clock_display, 0);
    clock_add_to_group(clock_sdxc0, 0);
    clock_add_to_group(clock_sdxc1, 0);
    clock_add_to_group(clock_camera0, 0);
    clock_add_to_group(clock_camera1, 0);
    clock_add_to_group(clock_ptpc, 0);
    clock_add_to_group(clock_ref0, 0);
    clock_add_to_group(clock_ref1, 0);
    clock_add_to_group(clock_watchdog0, 0);
    clock_add_to_group(clock_eth0, 0);
    clock_add_to_group(clock_eth1, 0);
    clock_add_to_group(clock_sdp, 0);
    clock_add_to_group(clock_xdma, 0);
    clock_add_to_group(clock_ram0, 0);
    clock_add_to_group(clock_ram1, 0);
    clock_add_to_group(clock_usb0, 0);
    clock_add_to_group(clock_usb1, 0);
    clock_add_to_group(clock_jpeg, 0);
    clock_add_to_group(clock_pdma, 0);
    clock_add_to_group(clock_kman, 0);
    clock_add_to_group(clock_gpio, 0);
    clock_add_to_group(clock_mbx0, 0);
    clock_add_to_group(clock_hdma, 0);
    clock_add_to_group(clock_rng, 0);
    clock_add_to_group(clock_mot0, 0);
    clock_add_to_group(clock_mot1, 0);
    clock_add_to_group(clock_mot2, 0);
    clock_add_to_group(clock_mot3, 0);
    clock_add_to_group(clock_acmp, 0);
    clock_add_to_group(clock_dao, 0);
    clock_add_to_group(clock_msyn, 0);
    clock_add_to_group(clock_lmm0, 0);
    clock_add_to_group(clock_lmm1, 0);
    clock_add_to_group(clock_pdm, 0);

    clock_add_to_group(clock_adc0, 0);
    clock_add_to_group(clock_adc1, 0);
    clock_add_to_group(clock_adc2, 0);
    clock_add_to_group(clock_adc3, 0);

    clock_add_to_group(clock_i2s0, 0);
    clock_add_to_group(clock_i2s1, 0);
    clock_add_to_group(clock_i2s2, 0);
    clock_add_to_group(clock_i2s3, 0);
    /* Connect Group0 to CPU0 */
    clock_connect_group_to_cpu(0, 0);

    /* Add the CPU1 clock to Group1 */
    clock_add_to_group(clock_mchtmr1, 1);
    clock_add_to_group(clock_mbx1, 1);
    /* Connect Group1 to CPU1 */
    clock_connect_group_to_cpu(1, 1);

    /* Bump up DCDC voltage to 1200mv */
    pcfg_dcdc_set_voltage(HPM_PCFG, 1200);

    if (status_success != pllctl_init_int_pll_with_freq(HPM_PLLCTL, 0, BOARD_CPU_FREQ)) {
        printf("Failed to set pll0_clk0 to %ldHz\n", BOARD_CPU_FREQ);
        while (1) {
        }
    }

    clock_set_source_divider(clock_cpu0, clk_src_pll0_clk0, 1);
    clock_set_source_divider(clock_cpu1, clk_src_pll0_clk0, 1);
    /* Connect Group1 to CPU1 */
    clock_connect_group_to_cpu(1, 1);

    clock_set_source_divider(clock_aud1, clk_src_pll3_clk0, 54); /* config clock_aud1 for 44100*n sample rate */
}

uint32_t board_init_cam_clock(CAM_Type *ptr)
{
    uint32_t freq = 0;
    if (ptr == HPM_CAM0) {
        /* Configure camera clock to 24MHz */
        clock_set_source_divider(clock_camera0, clk_src_osc24m, 1U);
        freq = clock_get_frequency(clock_camera0);
    } else if (ptr == HPM_CAM1) {
        /* Configure camera clock to 24MHz */
        clock_set_source_divider(clock_camera1, clk_src_osc24m, 1U);
        freq = clock_get_frequency(clock_camera1);
    } else {
        /* Invalid camera instance */
    }
    return freq;
}

uint32_t board_init_lcd_clock(void)
{
    uint32_t freq;
    clock_add_to_group(clock_display, 0);
    /* Configure LCDC clock to 29.7MHz */
    clock_set_source_divider(clock_display, clock_source_pll4_clk0, 20U);
    freq = clock_get_frequency(clock_display);
    return freq;
}

uint32_t board_init_adc12_clock(ADC12_Type *ptr)
{
    uint32_t freq = 0;
    switch ((uint32_t) ptr) {
    case HPM_ADC0_BASE:
        /* Configure the ADC clock to 200MHz */
        clock_set_adc_source(clock_adc0, clk_adc_src_ana0);
        clock_set_source_divider(clock_ana0, clk_src_pll1_clk1, 2U);
        freq = clock_get_frequency(clock_adc0);
        break;
    case HPM_ADC1_BASE:
        /* Configure the ADC clock to 200MHz */
        clock_set_adc_source(clock_adc1, clk_adc_src_ana0);
        clock_set_source_divider(clock_ana0, clk_src_pll1_clk1, 2U);
        freq = clock_get_frequency(clock_adc1);
        break;
    case HPM_ADC2_BASE:
        /* Configure the ADC clock to 200MHz */
        clock_set_adc_source(clock_adc2, clk_adc_src_ana0);
        clock_set_source_divider(clock_ana0, clk_src_pll1_clk1, 2U);
        freq = clock_get_frequency(clock_adc2);
        break;
    default:
        /* Invalid ADC instance */
        break;
    }

    return freq;
}

uint32_t board_init_dao_clock(void)
{
    clock_add_to_group(clock_dao, 0);

    sysctl_config_clock(HPM_SYSCTL, clock_node_aud0, clock_source_pll3_clk0, 25);
    sysctl_set_adc_i2s_clock_mux(HPM_SYSCTL, clock_node_i2s1, clock_source_i2s_aud0_clk);

    return clock_get_frequency(clock_dao);
}

uint32_t board_init_pdm_clock(void)
{
    clock_add_to_group(clock_pdm, 0);

    sysctl_config_clock(HPM_SYSCTL, clock_node_aud0, clock_source_pll3_clk0, 25);
    sysctl_set_adc_i2s_clock_mux(HPM_SYSCTL, clock_node_i2s0, clock_source_i2s_aud0_clk);

    return clock_get_frequency(clock_pdm);
}

uint32_t board_init_i2s_clock(I2S_Type *ptr)
{
    if (ptr == HPM_I2S0) {
        clock_add_to_group(clock_i2s0, 0);

        sysctl_config_clock(HPM_SYSCTL, clock_node_aud0, clock_source_pll3_clk0, 25);
        sysctl_set_adc_i2s_clock_mux(HPM_SYSCTL, clock_node_i2s0, clock_source_i2s_aud0_clk);

        return clock_get_frequency(clock_i2s0);
    }
    return 0;
}

uint32_t board_init_adc16_clock(ADC16_Type *ptr)
{
    uint32_t freq = 0;
    if (ptr == HPM_ADC3) {
        /* Configure the ADC clock to 200MHz */
        clock_set_adc_source(clock_adc3, clk_adc_src_ana1);
        clock_set_source_divider(clock_ana1, clk_src_pll1_clk1, 2U);
        freq = clock_get_frequency(clock_adc3);
    }

    return freq;
}

void board_init_can(CAN_Type *ptr)
{
    init_can_pins(ptr);
}

uint32_t board_init_can_clock(CAN_Type *ptr)
{
    uint32_t freq = 0;
    if (ptr == HPM_CAN0) {
        /* Set the CAN0 peripheral clock to 80MHz */
        clock_set_source_divider(clock_can0, clk_src_pll1_clk1, 5);
        freq = clock_get_frequency(clock_can0);
    } else if (ptr == HPM_CAN1) {
        /* Set the CAN1 peripheral clock to 80MHz */
        clock_set_source_divider(clock_can1, clk_src_pll1_clk1, 5);
        freq = clock_get_frequency(clock_can1);
    } else if (ptr == HPM_CAN2) {
        /* Set the CAN2 peripheral clock to 80MHz */
        clock_set_source_divider(clock_can2, clk_src_pll1_clk1, 5);
        freq = clock_get_frequency(clock_can2);
    } else if (ptr == HPM_CAN3) {
        /* Set the CAN3 peripheral clock to 80MHz */
        clock_set_source_divider(clock_can3, clk_src_pll1_clk1, 5);
        freq = clock_get_frequency(clock_can3);
    } else {
        /* Invalid CAN instance */
    }
    return freq;
}

uint32_t board_init_gptmr_clock(GPTMR_Type *ptr)
{
    uint32_t freq = 0;

    if (ptr == HPM_GPTMR0) {
        clock_add_to_group(clock_gptmr0, 0);
        clock_set_source_divider(clock_gptmr0, clk_src_pll1_clk1, 4);
        freq = clock_get_frequency(clock_gptmr0);
    }
    else if (ptr == HPM_GPTMR1) {
        clock_add_to_group(clock_gptmr1, 0);
        clock_set_source_divider(clock_gptmr1, clk_src_pll1_clk1, 4);
        freq = clock_get_frequency(clock_gptmr1);
    }
    else if (ptr == HPM_GPTMR2) {
        clock_add_to_group(clock_gptmr2, 0);
        clock_set_source_divider(clock_gptmr2, clk_src_pll1_clk1, 4);
        freq = clock_get_frequency(clock_gptmr2);
    }
    else if (ptr == HPM_GPTMR3) {
        clock_add_to_group(clock_gptmr3, 0);
        clock_set_source_divider(clock_gptmr3, clk_src_pll1_clk1, 4);
        freq = clock_get_frequency(clock_gptmr3);
    }
    else if (ptr == HPM_GPTMR4) {
        clock_add_to_group(clock_gptmr4, 0);
        clock_set_source_divider(clock_gptmr4, clk_src_pll1_clk1, 4);
        freq = clock_get_frequency(clock_gptmr4);
    }
    else if (ptr == HPM_GPTMR5) {
        clock_add_to_group(clock_gptmr5, 0);
        clock_set_source_divider(clock_gptmr5, clk_src_pll1_clk1, 4);
        freq = clock_get_frequency(clock_gptmr5);
    }
    else if (ptr == HPM_GPTMR6) {
        clock_add_to_group(clock_gptmr6, 0);
        clock_set_source_divider(clock_gptmr6, clk_src_pll1_clk1, 4);
        freq = clock_get_frequency(clock_gptmr6);
    }
    else if (ptr == HPM_GPTMR7) {
        clock_add_to_group(clock_gptmr7, 0);
        clock_set_source_divider(clock_gptmr7, clk_src_pll1_clk1, 4);
        freq = clock_get_frequency(clock_gptmr7);
    }
    else {
        /* Invalid instance */
    }
}


/*
 * this function will be called during startup to initialize external memory for data use
 */
void _init_ext_ram(void)
{
    uint32_t femc_clk_in_hz;
    clock_add_to_group(clock_femc, 0);
    board_init_sdram_pins();
    femc_clk_in_hz = board_init_femc_clock();

    femc_config_t config = {0};
    femc_sdram_config_t sdram_config = {0};

    femc_default_config(HPM_FEMC, &config);
    config.dqs = FEMC_DQS_INTERNAL;
    femc_init(HPM_FEMC, &config);

    sdram_config.bank_num = FEMC_SDRAM_BANK_NUM_4;
    sdram_config.prescaler = 0x3;
    sdram_config.burst_len_in_byte = 8;
    sdram_config.auto_refresh_count_in_one_burst = 1;
    sdram_config.col_addr_bits = FEMC_SDRAM_COLUMN_ADDR_9_BITS;
    sdram_config.cas_latency = FEMC_SDRAM_CAS_LATENCY_3;

    sdram_config.precharge_to_act_in_ns = 18;   /* Trp */
    sdram_config.act_to_rw_in_ns = 18;          /* Trcd */
    sdram_config.refresh_recover_in_ns = 70;     /* Trfc/Trc */
    sdram_config.write_recover_in_ns = 12;      /* Twr/Tdpl */
    sdram_config.cke_off_in_ns = 42;             /* Trcd */
    sdram_config.act_to_precharge_in_ns = 42;   /* Tras */

    sdram_config.self_refresh_recover_in_ns = 66;   /* Txsr */
    sdram_config.refresh_to_refresh_in_ns = 66;     /* Trfc/Trc */
    sdram_config.act_to_act_in_ns = 12;             /* Trrd */
    sdram_config.idle_timeout_in_ns = 6;
    sdram_config.cs_mux_pin = FEMC_IO_MUX_NOT_USED;

    sdram_config.cs = BOARD_SDRAM_CS;
    sdram_config.base_address = BOARD_SDRAM_ADDRESS;
    sdram_config.size_in_byte = BOARD_SDRAM_SIZE;
    sdram_config.port_size = BOARD_SDRAM_PORT_SIZE;
    sdram_config.refresh_count = BOARD_SDRAM_REFRESH_COUNT;
    sdram_config.refresh_in_ms = BOARD_SDRAM_REFRESH_IN_MS;
    sdram_config.data_width_in_byte = BOARD_SDRAM_DATA_WIDTH_IN_BYTE;
    sdram_config.delay_cell_value = 29;

    femc_config_sdram(HPM_FEMC, femc_clk_in_hz, &sdram_config);
}


void board_init_sd_pins(SDXC_Type *ptr)
{
    init_sdxc_pins(ptr, false);
    init_sdxc_card_detection_pin(ptr);
}

void board_sd_power_switch(SDXC_Type *ptr, bool on_off)
{
    /* This feature is not supported on current board */
}


uint32_t board_sd_configure_clock(SDXC_Type *ptr, uint32_t freq)
{
    uint32_t actual_freq = 0;
    do {
        if (ptr != HPM_SDXC1) {
            break;
        }
        clock_name_t sdxc_clk = (ptr == HPM_SDXC0) ? clock_sdxc0 : clock_sdxc1;
        sdxc_enable_inverse_clock(ptr, false);
        sdxc_enable_sd_clock(ptr, false);
        /* Configure the clock below 400KHz for the identification state */
        if (freq <= 400000UL) {
            clock_set_source_divider(sdxc_clk, clk_src_osc24m, 63);
        }
            /* configure the clock to 24MHz for the SDR12/Default speed */
        else if (freq <= 25000000UL) {
            clock_set_source_divider(sdxc_clk, clk_src_osc24m, 1);
        }
            /* Configure the clock to 50MHz for the SDR25/High speed/50MHz DDR/50MHz SDR */
        else if (freq <= 50000000UL) {
            clock_set_source_divider(sdxc_clk, clk_src_pll1_clk1, 8);
        }
            /* Configure the clock to 100MHz for the SDR50 */
        else if (freq <= 100000000UL) {
            clock_set_source_divider(sdxc_clk, clk_src_pll1_clk1, 4);
        }
            /* Configure the clock to 166MHz for SDR104/HS200/HS400  */
        else if (freq <= 208000000UL) {
            clock_set_source_divider(sdxc_clk, clk_src_pll2_clk0, 2);
        }
            /* For other unsupported clock ranges, configure the clock to 24MHz */
        else {
            clock_set_source_divider(sdxc_clk, clk_src_osc24m, 1);
        }
        sdxc_enable_inverse_clock(ptr, true);
        sdxc_enable_sd_clock(ptr, true);
        actual_freq = clock_get_frequency(sdxc_clk);
    } while (false);

    return actual_freq;
}

void board_sd_switch_pins_to_1v8(SDXC_Type *ptr)
{
    /* This feature is not supported */
}

bool board_sd_detect_card(SDXC_Type *ptr)
{
    return ((BOARD_APP_SDCARD_CDN_GPIO_CTRL->DI[GPIO_DI_GPIOD].VALUE & (1UL << BOARD_APP_SDCARD_CDN_GPIO_PIN)) == 0U);
}

static void set_rgb_output_off(PWM_Type *ptr, uint8_t pin, uint8_t cmp_index)
{
    pwm_cmp_config_t cmp_config = {0};
    pwm_output_channel_t ch_config = {0};

    pwm_stop_counter(ptr);
    pwm_get_default_cmp_config(ptr, &cmp_config);
    pwm_get_default_output_channel_config(ptr, &ch_config);

    pwm_set_reload(ptr, 0, 0xF);
    pwm_set_start_count(ptr, 0, 0);

    cmp_config.mode = pwm_cmp_mode_output_compare;
    cmp_config.cmp = 0x10;
    cmp_config.update_trigger = pwm_shadow_register_update_on_modify;
    pwm_config_cmp(ptr, cmp_index, &cmp_config);

    ch_config.cmp_start_index = cmp_index;
    ch_config.cmp_end_index = cmp_index;
    ch_config.invert_output = false;

    pwm_config_output_channel(ptr, pin, &ch_config);
}

void board_init_rgb_pwm_pins(void)
{
    trgm_output_t config = {0};
    board_turnoff_rgb_led();

    set_rgb_output_off(BOARD_RED_PWM, BOARD_RED_PWM_OUT, BOARD_RED_PWM_CMP);
    set_rgb_output_off(BOARD_GREEN_PWM, BOARD_GREEN_PWM_OUT, BOARD_GREEN_PWM_CMP);
    set_rgb_output_off(BOARD_BLUE_PWM, BOARD_BLUE_PWM_OUT, BOARD_BLUE_PWM_CMP);

    init_rgb_pwm_pins();

    config.type = 0;
    config.invert = false;

    /* Red: TRGM1 P1 */
    config.input = HPM_TRGM1_INPUT_SRC_PWM1_CH8REF;
    trgm_output_config(HPM_TRGM1, TRGM_TRGOCFG_TRGM_OUT1, &config);

    /* Green: TRGM0 P6 */
    config.input = HPM_TRGM0_INPUT_SRC_PWM0_CH8REF;
    trgm_output_config(HPM_TRGM0, TRGM_TRGOCFG_TRGM_OUT6, &config);

    /* Blue: TRGM1 P3 */
    config.input = HPM_TRGM1_INPUT_SRC_PWM1_CH9REF;
    trgm_output_config(HPM_TRGM1, TRGM_TRGOCFG_TRGM_OUT3, &config);
}

void board_disable_output_rgb_led(uint8_t color)
{
    switch (color) {
    case BOARD_RGB_RED:
        trgm_disable_io_output(HPM_TRGM1, 1 << 1);
        break;
    case BOARD_RGB_GREEN:
        trgm_disable_io_output(HPM_TRGM0, 1 << 6);
        break;
    case BOARD_RGB_BLUE:
        trgm_disable_io_output(HPM_TRGM1, 1 << 3);
        break;
    default:
        while (1) {
            ;
        }
    }
}

void board_enable_output_rgb_led(uint8_t color)
{
    switch (color) {
    case BOARD_RGB_RED:
        trgm_enable_io_output(HPM_TRGM1, 1 << 1);
        break;
    case BOARD_RGB_GREEN:
        trgm_enable_io_output(HPM_TRGM0, 1 << 6);
        break;
    case BOARD_RGB_BLUE:
        trgm_enable_io_output(HPM_TRGM1, 1 << 3);
        break;
    default:
        while (1) {
            ;
        }
    }
}

hpm_stat_t board_init_enet_ptp_clock(ENET_Type *ptr)
{
    /* set clock source */
    if (ptr == HPM_ENET0) {
        /* make sure pll0_clk0 output clock at 400MHz to get a clock at 100MHz for the enet0 ptp function */
        clock_set_source_divider(clock_ptp0, clk_src_pll1_clk1, 4); /* 100MHz */
    } else if (ptr == HPM_ENET1) {
        /* make sure pll0_clk0 output clock at 400MHz to get a clock at 100MHz for the enet1 ptp function */
        clock_set_source_divider(clock_ptp1, clk_src_pll1_clk1, 4); /* 100MHz */
    } else {
        return status_invalid_argument;
    }

    return status_success;
}

hpm_stat_t board_init_enet_rmii_reference_clock(ENET_Type *ptr, bool internal)
{
    if (internal == false) {
        return status_success;
    }
    /* Configure Enet clock to output reference clock */
    if (ptr == HPM_ENET0) {
        /* make sure pll2_clk1 output clock at 250MHz then set 50MHz for enet0 */
        clock_set_source_divider(clock_eth0, clk_src_pll2_clk1, 5);
    } else if (ptr == HPM_ENET1) {
        /* make sure pll2_clk1 output clock at 250MHz then set 50MHz for enet1 */
        clock_set_source_divider(clock_eth1, clk_src_pll2_clk1, 5); /* set 50MHz for enet1 */
    } else {
        return status_invalid_argument;
    }
    return status_success;
}

void board_init_adc12_pins(void)
{
    init_adc12_pins();
}

void board_init_adc16_pins(void)
{
    init_adc16_pins();
}

hpm_stat_t board_init_enet_pins(ENET_Type *ptr)
{
    init_enet_pins(ptr);

    if (ptr == HPM_ENET0) {
        gpio_set_pin_output_with_initial(BOARD_ENET0_RST_GPIO, BOARD_ENET0_RST_GPIO_INDEX, BOARD_ENET0_RST_GPIO_PIN, 0);
       } else if (ptr == HPM_ENET1) {
        gpio_set_pin_output_with_initial(BOARD_ENET1_RST_GPIO, BOARD_ENET1_RST_GPIO_INDEX, BOARD_ENET1_RST_GPIO_PIN, 0);
    } else {
        return status_invalid_argument;
    }

    return status_success;
}

hpm_stat_t board_reset_enet_phy(ENET_Type *ptr)
{
    if (ptr == HPM_ENET0) {
        gpio_write_pin(BOARD_ENET0_RST_GPIO, BOARD_ENET0_RST_GPIO_INDEX, BOARD_ENET0_RST_GPIO_PIN, 0);
        board_delay_ms(BOARD_ENET0_PHY_RST_TIME);
        gpio_write_pin(BOARD_ENET0_RST_GPIO, BOARD_ENET0_RST_GPIO_INDEX, BOARD_ENET0_RST_GPIO_PIN, 1);
    } else if (ptr == HPM_ENET1) {
        gpio_write_pin(BOARD_ENET1_RST_GPIO, BOARD_ENET1_RST_GPIO_INDEX, BOARD_ENET1_RST_GPIO_PIN, 0);
        board_delay_ms(BOARD_ENET1_PHY_RST_TIME);
        gpio_write_pin(BOARD_ENET1_RST_GPIO, BOARD_ENET1_RST_GPIO_INDEX, BOARD_ENET1_RST_GPIO_PIN, 1);
    } else {
        return status_invalid_argument;
    }

    return status_success;
}

uint8_t board_enet_get_dma_pbl(ENET_Type *ptr)
{
    return enet_pbl_32;
}
