/**
 * @file hal_clock.c
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */

#include "bl808_glb.h"
#include "hal_clock.h"

static void peripheral_clock_gate_all()
{
    uint32_t tmpVal;
    tmpVal = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG1);
    tmpVal &= (~(1 << 2));  //gpip
    tmpVal &= (~(1 << 3));  //sec_dbg
    tmpVal &= (~(1 << 4));  //sec_eng
    tmpVal &= (~(1 << 5));  //sec_eng
    tmpVal &= (~(1 << 12)); //dma
    tmpVal &= (~(1 << 13)); //usb
    tmpVal &= (~(1 << 16)); //uart0
    tmpVal &= (~(1 << 17)); //uart1
    tmpVal &= (~(1 << 18)); //spi
    tmpVal &= (~(1 << 19)); //i2c
    tmpVal &= (~(1 << 20)); //pwm
    tmpVal &= (~(1 << 21)); //timer
    tmpVal &= (~(1 << 22)); //ir
    tmpVal &= (~(1 << 23)); //cks
    tmpVal &= (~(1 << 25)); //i2c1
    tmpVal &= (~(1 << 26)); //uart2
    tmpVal &= (~(1 << 27)); //i2s
    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG1, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG2);
    tmpVal &= (~(1 << 4));  //wifi
    tmpVal &= (~(1 << 8));  //bt/ble
    tmpVal &= (~(1 << 9));  //m154
    tmpVal &= (~(1 << 10)); //bt/ble
    tmpVal &= (~(1 << 11)); //m154
    tmpVal &= (~(1 << 19)); //emac
    //tmpVal &= (~(1 << 21)); //audio
    tmpVal &= (~(1 << 22)); //sdh
    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG2, tmpVal);
}

void system_clock_init(void)
{
    GLB_Power_On_XTAL_And_PLL_CLK(XTAL_TYPE, GLB_PLL_WIFIPLL |
                                                 GLB_PLL_CPUPLL |
                                                 GLB_PLL_UHSPLL |
                                                 GLB_PLL_MIPIPLL);

#if BSP_ROOT_CLOCK_SOURCE == ROOT_CLOCK_SOURCE_XCLK
#if XTAL_TYPE == INTERNAL_RC_32M
    GLB_Set_MCU_System_CLK(GLB_MCU_SYS_CLK_RC32M);
#else
    GLB_Set_MCU_System_CLK(GLB_MCU_SYS_CLK_XTAL);
#endif
#elif BSP_ROOT_CLOCK_SOURCE == ROOT_CLOCK_SOURCE_WIFIPLL_240M
    GLB_Set_MCU_System_CLK(GLB_MCU_SYS_CLK_WIFIPLL_240M);
#elif BSP_ROOT_CLOCK_SOURCE == ROOT_CLOCK_SOURCE_WIFIPLL_320M
    GLB_Set_MCU_System_CLK(GLB_MCU_SYS_CLK_WIFIPLL_320M);
#else
#error "do not support current root clock source"
#endif
    GLB_Set_MCU_System_CLK_Div(BSP_HCLK_DIV, BSP_BCLK_DIV, BSP_LPCLK_DIV);
#if BSP_CLOCK_SOURCE_MUXPLL_160M == ROOT_CLOCK_SOURCE_WIFIPLL_160M
    GLB_Set_MCU_Muxpll_160M_Sel(0);
#elif BSP_CLOCK_SOURCE_MUXPLL_160M == ROOT_CLOCK_SOURCE_CPUPLL_160M
    GLB_Set_MCU_Muxpll_160M_Sel(1);
#elif BSP_CLOCK_SOURCE_MUXPLL_160M == ROOT_CLOCK_SOURCE_AUPLL_DIV2
    GLB_Set_MCU_Muxpll_160M_Sel(2);
#elif BSP_CLOCK_SOURCE_MUXPLL_160M == ROOT_CLOCK_SOURCE_AUPLL_DIV2P5
    GLB_Set_MCU_Muxpll_160M_Sel(3);
#else
#error "do not support current muxpll 160m clock source"
#endif

#if BSP_CLOCK_SOURCE_MUXPLL_80M == ROOT_CLOCK_SOURCE_WIFIPLL_80M
    GLB_Set_MCU_Muxpll_80M_Sel(0);
#elif BSP_CLOCK_SOURCE_MUXPLL_80M == ROOT_CLOCK_SOURCE_CPUPLL_80M
    GLB_Set_MCU_Muxpll_80M_Sel(1);
#elif BSP_CLOCK_SOURCE_MUXPLL_80M == ROOT_CLOCK_SOURCE_AUPLL_DIV5
    GLB_Set_MCU_Muxpll_80M_Sel(2);
#elif BSP_CLOCK_SOURCE_MUXPLL_80M == ROOT_CLOCK_SOURCE_AUPLL_DIV6
    GLB_Set_MCU_Muxpll_80M_Sel(3);
#else
#error "do not support current muxpll 80m clock source"
#endif

    GLB_Set_DSP_System_CLK(GLB_DSP_SYS_CLK_CPUPLL_400M);

    CPU_Set_MTimer_CLK(ENABLE, CPU_Get_MTimer_Source_Clock() / 1000 / 1000 - 1);
}

void peripheral_clock_init(void)
{
    uint32_t tmpVal;

    peripheral_clock_gate_all();

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG1);
#if defined(BSP_USING_UART0) || defined(BSP_USING_UART1) || defined(BSP_USING_UART2)
#if defined(BSP_USING_UART0)
    tmpVal |= (1 << 16);
#endif
#if defined(BSP_USING_UART1)
    tmpVal |= (1 << 17);
#endif
#if defined(BSP_USING_UART2)
    tmpVal |= (1 << 26);
#endif

#if BSP_UART_CLOCK_SOURCE == ROOT_CLOCK_SOURCE_XCLK
    GLB_Set_UART_CLK(ENABLE, HBN_UART_CLK_XCLK, BSP_UART_CLOCK_DIV);
#elif BSP_UART_CLOCK_SOURCE == BSP_CLOCK_SOURCE_BCLK
    GLB_Set_UART_CLK(ENABLE, HBN_UART_CLK_MCU_PBCLK, BSP_UART_CLOCK_DIV);
#elif BSP_UART_CLOCK_SOURCE == BSP_CLOCK_SOURCE_MUXPLL_160M
    GLB_Set_UART_CLK(ENABLE, HBN_UART_CLK_160M, BSP_UART_CLOCK_DIV);
#else
#error "do not support current uart clock source"
#endif
#endif

#if defined(BSP_USING_UART3)
#if BSP_UART_CLOCK_SOURCE == ROOT_CLOCK_SOURCE_XCLK
    GLB_Set_DSP_UART0_CLK(ENABLE, GLB_DSP_UART_CLK_DSP_XCLK, BSP_UART_CLOCK_DIV);
#elif BSP_UART_CLOCK_SOURCE == BSP_CLOCK_SOURCE_BCLK
    GLB_Set_DSP_UART0_CLK(ENABLE, GLB_DSP_UART_CLK_DSP_PBCLK, BSP_UART_CLOCK_DIV);
#elif BSP_UART_CLOCK_SOURCE == BSP_CLOCK_SOURCE_MUXPLL_160M
    GLB_Set_DSP_UART0_CLK(ENABLE, GLB_DSP_UART_CLK_MUXPLL_160M, BSP_UART_CLOCK_DIV);
#else
#error "do not support current uart clock source"
#endif
#endif

#if defined(BSP_USING_I2C0) || defined(BSP_USING_I2C1)
#if defined(BSP_USING_I2C0)
    tmpVal |= (1 << 19);
#elif defined(BSP_USING_I2C1)
    tmpVal |= (1 << 25);
#endif

#if BSP_I2C_CLOCK_SOURCE == ROOT_CLOCK_SOURCE_XCLK
    GLB_Set_I2C_CLK(ENABLE, GLB_I2C_CLK_XCLK, BSP_I2C_CLOCK_DIV);
#elif BSP_I2C_CLOCK_SOURCE == BSP_CLOCK_SOURCE_BCLK
    GLB_Set_I2C_CLK(ENABLE, GLB_I2C_CLK_BCLK, BSP_I2C_CLOCK_DIV);
#else
#error "do not support current i2c clock source"
#endif
#endif

#if defined(BSP_USING_I2C2)
#if BSP_I2C_CLOCK_SOURCE == ROOT_CLOCK_SOURCE_XCLK
    GLB_Set_DSP_I2C0_CLK(ENABLE, GLB_I2C_CLK_XCLK, BSP_I2C_CLOCK_DIV);
#elif BSP_I2C_CLOCK_SOURCE == BSP_CLOCK_SOURCE_BCLK
    GLB_Set_DSP_I2C0_CLK(ENABLE, GLB_I2C_CLK_BCLK, BSP_I2C_CLOCK_DIV);
#else
#error "do not support current i2c clock source"
#endif
#endif

#if defined(BSP_USING_I2C3)
#if BSP_I2C_CLOCK_SOURCE == ROOT_CLOCK_SOURCE_XCLK
    GLB_Set_DSP_I2C1_CLK(ENABLE, GLB_I2C_CLK_XCLK, BSP_I2C_CLOCK_DIV);
#elif BSP_I2C_CLOCK_SOURCE == BSP_CLOCK_SOURCE_BCLK
    GLB_Set_DSP_I2C1_CLK(ENABLE, GLB_I2C_CLK_BCLK, BSP_I2C_CLOCK_DIV);
#else
#error "do not support current i2c clock source"
#endif
#endif

#if defined(BSP_USING_SPI0)
    tmpVal |= (1 << 18);
#if BSP_UART_CLOCK_SOURCE == ROOT_CLOCK_SOURCE_XCLK
    GLB_Set_SPI_CLK(ENABLE, GLB_SPI_CLK_XCLK, BSP_SPI_CLOCK_DIV);
#elif BSP_UART_CLOCK_SOURCE == BSP_CLOCK_SOURCE_MUXPLL_160M
    GLB_Set_SPI_CLK(ENABLE, GLB_SPI_CLK_MCU_MUXPLL_160M, BSP_SPI_CLOCK_DIV);
#else
#error "do not support current spi clock source"
#endif
#endif

#if defined(BSP_USING_SPI1)
#if BSP_UART_CLOCK_SOURCE == ROOT_CLOCK_SOURCE_XCLK
    GLB_Set_DSP_SPI_CLK(ENABLE, GLB_DSP_SPI_CLK_DSP_XCLK, BSP_SPI_CLOCK_DIV);
#elif BSP_UART_CLOCK_SOURCE == BSP_CLOCK_SOURCE_MUXPLL_160M
    GLB_Set_DSP_SPI_CLK(ENABLE, GLB_DSP_SPI_CLK_DSP_MUXPLL_160M, BSP_SPI_CLOCK_DIV);
#else
#error "do not support current spi clock source"
#endif
#endif

#if defined(BSP_USING_ADC0)
    tmpVal |= (1 << 2);
#if BSP_ADC_CLOCK_SOURCE == ROOT_CLOCK_SOURCE_AUPLL_CLK
    GLB_Set_ADC_CLK(ENABLE, GLB_ADC_CLK_AUPLL, BSP_ADC_CLOCK_DIV);
#elif BSP_ADC_CLOCK_SOURCE == ROOT_CLOCK_SOURCE_XCLK
    GLB_Set_ADC_CLK(ENABLE, GLB_ADC_CLK_XCLK, BSP_ADC_CLOCK_DIV);
#else
#error "do not support current adc clock source"
#endif
#endif

#if defined(BSP_USING_DAC0)
    tmpVal |= (1 << 2);
#if BSP_ADC_CLOCK_SOURCE == ROOT_CLOCK_SOURCE_WIFIPLL_32M
    //GLB_Set_DAC_CLK(ENABLE, GLB_DAC_CLK_32M, BSP_DAC_CLOCK_DIV);
#elif BSP_ADC_CLOCK_SOURCE == ROOT_CLOCK_SOURCE_XCLK
    //GLB_Set_DAC_CLK(ENABLE, GLB_DAC_CLK_XCLK, BSP_DAC_CLOCK_DIV);
#else
#error "do not support current dac clock source"
#endif
#endif

#if defined(BSP_USING_USB)
    tmpVal |= (1 << 13);
    GLB_Set_USB_CLK_From_WIFIPLL(1);
#endif
#if defined(BSP_USING_SDH)
    uint32_t tmp_val;
    tmp_val = BL_RD_REG(PDS_BASE, PDS_CTL5);
    uint32_t tmp_val2 = BL_GET_REG_BITS_VAL(tmp_val, PDS_CR_PDS_GPIO_KEEP_EN);
    tmp_val2 &= ~(1 << 0);
    tmp_val = BL_SET_REG_BITS_VAL(tmp_val, PDS_CR_PDS_GPIO_KEEP_EN, tmp_val2);
    BL_WR_REG(PDS_BASE, PDS_CTL5, tmp_val);

    GLB_Set_SDH_CLK(1, GLB_SDH_CLK_WIFIPLL_96M, 0);
    GLB_PER_Clock_UnGate(GLB_AHB_CLOCK_SDH);
    GLB_AHB_MCU_Software_Reset(GLB_AHB_MCU_SW_SDH);
#endif
    tmpVal |= (1 << 12); //enable dma
    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG1, tmpVal);

    GLB_Set_DSP_DSP2_CLK(1, GLB_DSP_DSP2_CLK_CPUPLL_400M, 0);
}

uint32_t system_clock_get(enum system_clock_type type)
{
    switch (type) {
        case SYSTEM_CLOCK_ROOT_CLOCK:
            return Clock_System_Clock_Get(BL_SYSTEM_CLOCK_MCU_ROOT_CLK);

        case SYSTEM_CLOCK_FCLK:
            return Clock_System_Clock_Get(BL_SYSTEM_CLOCK_MCU_CLK);

        case SYSTEM_CLOCK_BCLK:
            return Clock_System_Clock_Get(BL_SYSTEM_CLOCK_MCU_BCLK);

        case SYSTEM_CLOCK_XCLK:
            return Clock_System_Clock_Get(BL_SYSTEM_CLOCK_MCU_XCLK);

        case SYSTEM_CLOCK_DSP_CLK:
            return Clock_System_Clock_Get(BL_SYSTEM_CLOCK_DSP_CLK);

        case SYSTEM_CLOCK_DSP_BCLK:
            return Clock_System_Clock_Get(BL_SYSTEM_CLOCK_DSP_BCLK);

        case SYSTEM_CLOCK_DSP_PBCLK:
            return Clock_System_Clock_Get(BL_SYSTEM_CLOCK_DSP_PBCLK);

        case SYSTEM_CLOCK_LP_CLK:
            return Clock_System_Clock_Get(BL_SYSTEM_CLOCK_LP_CLK);

        case SYSTEM_CLOCK_32K_CLK:
            return Clock_System_Clock_Get(BL_SYSTEM_CLOCK_F32K);

        default:
            break;
    }
    return 0;
}

uint32_t peripheral_clock_get(enum peripheral_clock_type type)
{
    return 0;
}

void system_mtimer_clock_init(void)
{
    CPU_Reset_MTimer();
    /* set mtimer clock 1M */
    CPU_Set_MTimer_CLK(ENABLE, CPU_Get_MTimer_Source_Clock() / 1000000);
}

void system_mtimer_clock_reinit(void)
{
    /* ToDo */
}
