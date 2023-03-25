/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022/12/25     flyingcys    first version
 * 2023/01/17     chushicheng  add pin and i2c
 * 2023/03/15     flyingcys    update bsp file structure
 */
#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "drv_uart.h"

#ifdef BSP_USING_SDH_SDCARD
#include "sdh_sdcard.h"
#endif

static void system_clock_init(void)
{
    /* wifipll/audiopll */
    GLB_Power_On_XTAL_And_PLL_CLK(GLB_XTAL_40M, GLB_PLL_WIFIPLL |
                                                    GLB_PLL_CPUPLL |
                                                    GLB_PLL_UHSPLL |
                                                    GLB_PLL_MIPIPLL);

    GLB_Set_MCU_System_CLK(GLB_MCU_SYS_CLK_WIFIPLL_320M);
    GLB_Set_DSP_System_CLK(GLB_DSP_SYS_CLK_CPUPLL_400M);
    GLB_Config_CPU_PLL(GLB_XTAL_40M, cpuPllCfg_480M);

    CPU_Set_MTimer_CLK(ENABLE, CPU_Get_MTimer_Source_Clock() / 1000 / 1000 - 1);
}

static void peripheral_clock_init(void)
{
    PERIPHERAL_CLOCK_ADC_DAC_ENABLE();
    PERIPHERAL_CLOCK_SEC_ENABLE();
    PERIPHERAL_CLOCK_DMA0_ENABLE();
    PERIPHERAL_CLOCK_UART0_ENABLE();
    PERIPHERAL_CLOCK_UART1_ENABLE();
    PERIPHERAL_CLOCK_SPI0_1_ENABLE();
    PERIPHERAL_CLOCK_I2C0_ENABLE();
    PERIPHERAL_CLOCK_PWM0_ENABLE();
    PERIPHERAL_CLOCK_TIMER0_1_WDG_ENABLE();
    PERIPHERAL_CLOCK_IR_ENABLE();
    PERIPHERAL_CLOCK_I2S_ENABLE();
    PERIPHERAL_CLOCK_USB_ENABLE();
    PERIPHERAL_CLOCK_CAN_UART2_ENABLE();

    GLB_Set_ADC_CLK(ENABLE, GLB_ADC_CLK_XCLK, 4);
    GLB_Set_UART_CLK(ENABLE, HBN_UART_CLK_XCLK, 0);
    GLB_Set_DSP_UART0_CLK(ENABLE, GLB_DSP_UART_CLK_DSP_XCLK, 0);
    GLB_Set_SPI_CLK(ENABLE, GLB_SPI_CLK_MCU_MUXPLL_160M, 0);
    GLB_Set_I2C_CLK(ENABLE, GLB_I2C_CLK_XCLK, 0);
    GLB_Set_IR_CLK(ENABLE, GLB_IR_CLK_SRC_XCLK, 19);
    GLB_Set_ADC_CLK(ENABLE, GLB_ADC_CLK_XCLK, 1);
    GLB_Set_DIG_CLK_Sel(GLB_DIG_CLK_XCLK);
    GLB_Set_DIG_512K_CLK(ENABLE, ENABLE, 0x4E);
    GLB_Set_PWM1_IO_Sel(GLB_PWM1_IO_DIFF_END);
    GLB_Set_CAM_CLK(ENABLE, GLB_CAM_CLK_WIFIPLL_96M, 3);

    GLB_Set_PKA_CLK_Sel(GLB_PKA_CLK_MCU_MUXPLL_160M);

#ifdef BSP_USING_SDH_SDCARD
    PERIPHERAL_CLOCK_SDH_ENABLE();
    uint32_t tmp_val;
    tmp_val = BL_RD_REG(PDS_BASE, PDS_CTL5);
    uint32_t tmp_val2 = BL_GET_REG_BITS_VAL(tmp_val, PDS_CR_PDS_GPIO_KEEP_EN);
    tmp_val2 &= ~(1 << 0);
    tmp_val = BL_SET_REG_BITS_VAL(tmp_val, PDS_CR_PDS_GPIO_KEEP_EN, tmp_val2);
    BL_WR_REG(PDS_BASE, PDS_CTL5, tmp_val);
    GLB_AHB_MCU_Software_Reset(GLB_AHB_MCU_SW_SDH);
#endif

#ifdef BSP_USING_CSI
    GLB_CSI_Config_MIPIPLL(2, 0x21000);
    GLB_CSI_Power_Up_MIPIPLL();
    GLB_Set_DSP_CLK(ENABLE, GLB_DSP_CLK_MUXPLL_160M, 1);
#endif
    GLB_Set_USB_CLK_From_WIFIPLL(1);
}

#ifdef BSP_USING_PSRAM
#define WB_4MB_PSRAM   (1)
#define UHS_32MB_PSRAM (2)
#define UHS_64MB_PSRAM (3)
#define WB_32MB_PSRAM  (4)
#define NONE_UHS_PSRAM (-1)

int uhs_psram_init(void)
{
    PSRAM_UHS_Cfg_Type psramDefaultCfg = {
        2000,
        PSRAM_MEM_SIZE_32MB,
        PSRAM_PAGE_SIZE_2KB,
        PSRAM_UHS_NORMAL_TEMP,
    };

    bflb_efuse_device_info_type chip_info;
    bflb_ef_ctrl_get_device_info(&chip_info);
    if (chip_info.psramInfo == UHS_32MB_PSRAM) {
        psramDefaultCfg.psramMemSize = PSRAM_MEM_SIZE_32MB;
    } else if (chip_info.psramInfo == UHS_64MB_PSRAM) {
        psramDefaultCfg.psramMemSize = PSRAM_MEM_SIZE_64MB;
    } else {
        return -1;
    }

    //init uhs PLL; Must open uhs pll first, and then initialize uhs psram
    GLB_Config_UHS_PLL(GLB_XTAL_40M, uhsPllCfg_2000M);
    //init uhs psram ;
    // Psram_UHS_x16_Init(Clock_Peripheral_Clock_Get(BL_PERIPHERAL_CLOCK_PSRAMA) / 1000000);
    Psram_UHS_x16_Init_Override(&psramDefaultCfg);
    Tzc_Sec_PSRAMA_Access_Release();

    // example: 2000Mbps typical cal values
    uhs_phy_cal_res->rl = 39;
    uhs_phy_cal_res->rdqs = 3;
    uhs_phy_cal_res->rdq = 0;
    uhs_phy_cal_res->wl = 13;
    uhs_phy_cal_res->wdqs = 4;
    uhs_phy_cal_res->wdq = 5;
    uhs_phy_cal_res->ck = 9;
    /* TODO: use uhs psram trim update */
    set_uhs_latency_r(uhs_phy_cal_res->rl);
    cfg_dqs_rx(uhs_phy_cal_res->rdqs);
    cfg_dq_rx(uhs_phy_cal_res->rdq);
    set_uhs_latency_w(uhs_phy_cal_res->wl);
    cfg_dq_drv(uhs_phy_cal_res->wdq);
    cfg_ck_cen_drv(uhs_phy_cal_res->wdq + 4, uhs_phy_cal_res->wdq + 1);
    cfg_dqs_drv(uhs_phy_cal_res->wdqs);
    // set_odt_en();
    mr_read_back();
    return 0;
}
#endif

/* This is the timer interrupt service routine. */
static void systick_isr(void)
{
    rt_tick_increase();
}

void rt_hw_board_init(void)
{
    GLB_Halt_CPU(GLB_CORE_ID_D0);
    GLB_Halt_CPU(GLB_CORE_ID_LP);

    bflb_flash_init();

    system_clock_init();
    peripheral_clock_init();
    bflb_irq_initialize();

    bflb_mtimer_config(CPU_Get_MTimer_Clock() / RT_TICK_PER_SECOND, systick_isr);

#ifdef RT_USING_HEAP
    /* initialize memory system */
    rt_kprintf("RT_HW_HEAP_BEGIN:%x RT_HW_HEAP_END:%x size: %d\r\n", RT_HW_HEAP_BEGIN, RT_HW_HEAP_END, RT_HW_HEAP_END - RT_HW_HEAP_BEGIN);
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif

    /* UART driver initialization is open by default */
#ifdef RT_USING_SERIAL
    rt_hw_uart_init();
#endif

#ifdef BSP_USING_PSRAM
    if (uhs_psram_init() < 0)
    {
        rt_kprintf("uhs_psram_init failed!\n");
    }
#endif

    /* Set the shell console output device */
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

    /* set CPU D0 boot XIP address and flash address */
    Tzc_Sec_Set_CPU_Group(GLB_CORE_ID_D0, 1);
    /* D0 boot from 0x58000000 */
    GLB_Set_CPU_Reset_Address(GLB_CORE_ID_D0, 0x58000000);
    /* D0 image offset on flash is CONFIG_D0_FLASH_ADDR+0x1000(header) */
    bflb_sf_ctrl_set_flash_image_offset(CONFIG_D0_FLASH_ADDR + 0x1000, 1, SF_CTRL_FLASH_BANK0);

    Tzc_Sec_Set_CPU_Group(GLB_CORE_ID_LP, 0);
    /* LP boot from 0x580C0000 */
    GLB_Set_CPU_Reset_Address(GLB_CORE_ID_LP, 0x580C0000);

    GLB_Release_CPU(GLB_CORE_ID_D0);
    GLB_Release_CPU(GLB_CORE_ID_LP);

    /* release d0 and then do can run */
    BL_WR_WORD(IPC_SYNC_ADDR1, IPC_SYNC_FLAG);
    BL_WR_WORD(IPC_SYNC_ADDR2, IPC_SYNC_FLAG);
    L1C_DCache_Clean_By_Addr(IPC_SYNC_ADDR1, 8);
}

void rt_hw_cpu_reset(void)
{
    GLB_SW_POR_Reset();
}
MSH_CMD_EXPORT_ALIAS(rt_hw_cpu_reset, reboot, reset machine);
