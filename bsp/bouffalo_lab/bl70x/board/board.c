/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023/03/25     flyingcys    first version
 */
#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "drv_uart.h"

static void system_clock_init(void)
{
    GLB_Set_System_CLK(GLB_DLL_XTAL_32M, GLB_SYS_CLK_DLL144M);
    GLB_Set_MTimer_CLK(1, GLB_MTIMER_CLK_BCLK, 71);
}

static void peripheral_clock_init(void)
{
    PERIPHERAL_CLOCK_ADC_DAC_ENABLE();
    PERIPHERAL_CLOCK_SEC_ENABLE();
    PERIPHERAL_CLOCK_DMA0_ENABLE();
    PERIPHERAL_CLOCK_UART0_ENABLE();
    PERIPHERAL_CLOCK_UART1_ENABLE();
    PERIPHERAL_CLOCK_SPI0_ENABLE();
    PERIPHERAL_CLOCK_I2C0_ENABLE();
    PERIPHERAL_CLOCK_PWM0_ENABLE();
    PERIPHERAL_CLOCK_TIMER0_1_WDG_ENABLE();
    PERIPHERAL_CLOCK_IR_ENABLE();
    PERIPHERAL_CLOCK_I2S_ENABLE();
    PERIPHERAL_CLOCK_USB_ENABLE();
    GLB_AHB_Slave1_Clock_Gate(DISABLE, BL_AHB_SLAVE1_CAM);

    GLB_Set_UART_CLK(ENABLE, HBN_UART_CLK_96M, 0);
    GLB_Set_SPI_CLK(ENABLE, 0);
    GLB_Set_I2C_CLK(ENABLE, 0);
    GLB_Set_IR_CLK(ENABLE, GLB_IR_CLK_SRC_XCLK, 15);

    GLB_Set_ADC_CLK(ENABLE, GLB_ADC_CLK_XCLK, 1);
    GLB_Set_DAC_CLK(ENABLE, GLB_DAC_CLK_XCLK, 0x3E);

    GLB_Set_USB_CLK(ENABLE);
}

#ifdef BSP_USING_PSRAM
struct spi_psram_cfg_type ap_memory1604 = {
    .read_id_cmd = 0x9F,
    .read_id_dmy_clk = 0,
    .burst_toggle_cmd = 0xC0,
    .reset_enable_cmd = 0x66,
    .reset_cmd = 0x99,
    .enter_quad_mode_cmd = 0x35,
    .exit_quad_mode_cmd = 0xF5,
    .read_reg_cmd = 0xB5,
    .read_reg_dmy_clk = 1,
    .write_reg_cmd = 0xB1,
    .read_cmd = 0x03,
    .read_dmy_clk = 0,
    .f_read_cmd = 0x0B,
    .f_read_dmy_clk = 1,
    .f_read_quad_cmd = 0xEB,
    .f_read_quad_dmy_clk = 3,
    .write_cmd = 0x02,
    .quad_write_cmd = 0x38,
    .page_size = 512,
    .ctrl_mode = PSRAM_SPI_CTRL_MODE,
    .drive_strength = PSRAM_DRIVE_STRENGTH_50_OHMS,
    .burst_length = PSRAM_BURST_LENGTH_512_BYTES,
};

struct sf_ctrl_cmds_cfg cmds_cfg = {
    .cmds_core_en = 1,
    .cmds_en = 1,
    .burst_toggle_en = 1,
    .cmds_wrap_mode = 0,
    .cmds_wrap_len = SF_CTRL_WRAP_LEN_512,
};
struct sf_ctrl_psram_cfg psram_cfg = {
    .owner = SF_CTRL_OWNER_SAHB,
    .pad_sel = SF_CTRL_SEL_DUAL_CS_SF2,
    .bank_sel = SF_CTRL_SEL_PSRAM,
    .psram_rx_clk_invert_src = 1,
    .psram_rx_clk_invert_sel = 0,
    .psram_delay_src = 1,
    .psram_clk_delay = 1,
};

#define BFLB_EXTFLASH_CS_GPIO    GLB_GPIO_PIN_25
#define BFLB_EXTPSRAM_CLK_GPIO   GLB_GPIO_PIN_27
#define BFLB_EXTPSRAM_CS_GPIO    GLB_GPIO_PIN_17
#define BFLB_EXTPSRAM_DATA0_GPIO GLB_GPIO_PIN_28
#define BFLB_EXTPSRAM_DATA1_GPIO GLB_GPIO_PIN_24
#define BFLB_EXTPSRAM_DATA2_GPIO GLB_GPIO_PIN_23
#define BFLB_EXTPSRAM_DATA3_GPIO GLB_GPIO_PIN_26

void ATTR_TCM_SECTION psram_gpio_init(void)
{
    GLB_GPIO_Cfg_Type cfg;
    uint8_t gpiopins[7];
    uint8_t i = 0;

    cfg.gpioMode = GPIO_MODE_AF;
    cfg.pullType = GPIO_PULL_UP;
    cfg.drive = 3;
    cfg.smtCtrl = 1;
    cfg.gpioFun = GPIO_FUN_FLASH_PSRAM;

    gpiopins[0] = BFLB_EXTPSRAM_CLK_GPIO;
    gpiopins[1] = BFLB_EXTPSRAM_CS_GPIO;
    gpiopins[2] = BFLB_EXTPSRAM_DATA0_GPIO;
    gpiopins[3] = BFLB_EXTPSRAM_DATA1_GPIO;
    gpiopins[4] = BFLB_EXTPSRAM_DATA2_GPIO;
    gpiopins[5] = BFLB_EXTPSRAM_DATA3_GPIO;
    gpiopins[6] = BFLB_EXTFLASH_CS_GPIO;

    for (i = 0; i < sizeof(gpiopins); i++) {
        cfg.gpioPin = gpiopins[i];

        if (i == 0 || i == 1 || i == 6) {
            /*flash clk and cs is output*/
            cfg.gpioMode = GPIO_MODE_OUTPUT;
        } else {
            /*data are bidir*/
            cfg.gpioMode = GPIO_MODE_AF;
        }

        GLB_GPIO_Init(&cfg);
    }
}

uint8_t psramId[8] = { 0 };

void ATTR_TCM_SECTION board_psram_init(void)
{
    psram_gpio_init();

    bflb_psram_init(&ap_memory1604, &cmds_cfg, &psram_cfg);

    bflb_psram_softwarereset(&ap_memory1604, ap_memory1604.ctrl_mode);

    bflb_psram_readid(&ap_memory1604, psramId);
    bflb_psram_cache_write_set(&ap_memory1604, SF_CTRL_QIO_MODE, ENABLE, DISABLE, DISABLE);
    L1C_Cache_Enable_Set(L1C_WAY_DISABLE_NONE);
}
#endif

/* This is the timer interrupt service routine. */
static void systick_isr(void)
{
    rt_tick_increase();
}

void rt_hw_board_init(void)
{
    bflb_flash_init();

    system_clock_init();
    peripheral_clock_init();
    bflb_irq_initialize();

    bflb_mtimer_config(HW_MTIMER_CLOCK / RT_TICK_PER_SECOND, systick_isr);

#ifdef RT_USING_HEAP
    /* initialize memory system */
    rt_kprintf("RT_HW_HEAP_BEGIN:%x RT_HW_HEAP_END:%x\r\n", RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif

    /* UART driver initialization is open by default */
#ifdef RT_USING_SERIAL
    rt_hw_uart_init();
#endif

#ifdef BSP_USING_PSRAM
    board_psram_init();
#endif

    /* Set the shell console output device */
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

void rt_hw_cpu_reset(void)
{
    GLB_SW_POR_Reset();
}

MSH_CMD_EXPORT_ALIAS(rt_hw_cpu_reset, reboot, reset machine);
