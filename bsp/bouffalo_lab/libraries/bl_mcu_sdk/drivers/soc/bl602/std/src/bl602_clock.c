/**
  ******************************************************************************
  * @file    bl602_clock.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#include "bl602_clock.h"
// #include "bl602_pwm.h"

/** @addtogroup  BL602_Peripheral_Driver
 *  @{
 */

/** @addtogroup  CLOCK
 *  @{
 */

/** @defgroup  CLOCK_Private_Macros
 *  @{
 */

/*@} end of group CLOCK_Private_Macros */

/** @defgroup  CLOCK_Private_Types
 *  @{
 */

/*@} end of group CLOCK_Private_Types */

/** @defgroup  CLOCK_Private_Variables
 *  @{
 */
//static inline Clock_Cfg_Type clkCfg;

/*@} end of group CLOCK_Private_Variables */

/** @defgroup  CLOCK_Global_Variables
 *  @{
 */

/*@} end of group CLOCK_Global_Variables */

/** @defgroup  CLOCK_Private_Fun_Declaration
 *  @{
 */

/*@} end of group CLOCK_Private_Fun_Declaration */

/** @defgroup  CLOCK_Private_Functions
 *  @{
 */

/*@} end of group CLOCK_Private_Functions */

/** @defgroup  CLOCK_Public_Functions
 *  @{
 */

static inline uint32_t Clock_Xtal_Output(void)
{
    uint32_t tmpVal;

    /* get clkpll_sdmin */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CLKPLL_SDM);
    tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_SDMIN);

    switch (tmpVal) {
        case 0x500000:
            /* 24m */
            return (24 * 1000 * 1000);

        case 0x3C0000:
            /* 32m */
            return (32 * 1000 * 1000);

        case 0x320000:
            /* 38.4m */
            return (384 * 100 * 1000);

        case 0x300000:
            /* 40m */
            return (40 * 1000 * 1000);

        case 0x49D39D:
            /* 26m */
            return (26 * 1000 * 1000);

        default:
            /* 32m */
            return (32 * 1000 * 1000);
    }
}

static inline uint32_t Clock_XClk_Mux_Output(uint8_t sel)
{
    if (sel == 0) {
        /* rc32m */
        return (32 * 1000 * 1000);
    } else {
        /* xtal */
        return Clock_Xtal_Output();
    }
}

static inline uint8_t Clock_Get_MCU_XClk_Sel_Val(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG0);
    tmpVal = BL_GET_REG_BITS_VAL(tmpVal, GLB_HBN_ROOT_CLK_SEL);

    return (tmpVal & 0x1);
}

static inline uint8_t Clock_Get_MCU_Root_Clk_Sel_Val(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG0);
    tmpVal = BL_GET_REG_BITS_VAL(tmpVal, GLB_HBN_ROOT_CLK_SEL);

    return ((tmpVal >> 1) & 0x1);
}

static inline uint32_t Clock_MCU_Clk_Mux_Output(uint8_t sel)
{
    if (sel == 0) {
        /* pll 48m */
        return (48 * 1000 * 1000);
    } else if (sel == 1) {
        /* pll 120m */
        return (120 * 1000 * 1000);
    } else if (sel == 2) {
        /* pll 160m */
        return (160 * 1000 * 1000);
    } else if (sel == 3) {
        /* pll 192m */
        return (192 * 1000 * 1000);
    } else {
        return 0;
    }
}

static inline uint32_t Clock_MCU_Root_Clk_Mux_Output(uint8_t sel)
{
    uint32_t tmpVal;

    if (sel == 0) {
        /* xclk */
        return Clock_XClk_Mux_Output(Clock_Get_MCU_XClk_Sel_Val());
    } else if (sel == 1) {
        /* pll */
        tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG0);
        tmpVal = BL_GET_REG_BITS_VAL(tmpVal, GLB_REG_PLL_SEL);
        return Clock_MCU_Clk_Mux_Output(tmpVal);
    } else {
        return 0;
    }
}

static inline uint8_t Clock_Get_MCU_HClk_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal, GLB_REG_HCLK_DIV);
}

static inline uint8_t Clock_Get_Peri_BClk_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal, GLB_REG_BCLK_DIV);
}

static inline uint32_t Clock_F32k_Mux_Output(uint8_t sel)
{
    uint32_t tmpVal;
    uint32_t div = 0;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL);
    div = BL_GET_REG_BITS_VAL(tmpVal, GLB_DIG_32K_DIV);

    if (sel == 0) {
        /* src32K */
        return (32 * 1000);
    } else if (sel == 1) {
        /* xtal 32K */
        return (32 * 1000);
    } else {
        return Clock_Xtal_Output() / (div + 1);
    }
}

static inline uint8_t Clock_Get_F32k_Sel_Val(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_GLB);

    return BL_GET_REG_BITS_VAL(tmpVal, HBN_F32K_SEL);
}

/****************************************************************************/ /**
 * @brief  Get System Clock
 *
 * @param  type: System clock type
 *
 * @return System clock value
 *
*******************************************************************************/
uint32_t Clock_System_Clock_Get(BL_System_Clock_Type type)
{
    uint32_t clock = 0;
    uint32_t div = 0;

    switch (type) {
        case BL_SYSTEM_CLOCK_XCLK:
            /*!< mcu xclk clock */
            return Clock_XClk_Mux_Output(Clock_Get_MCU_XClk_Sel_Val());

        case BL_SYSTEM_CLOCK_ROOT:
            /*!< mcu root clock */
            return Clock_MCU_Root_Clk_Mux_Output(Clock_Get_MCU_Root_Clk_Sel_Val());

        case BL_SYSTEM_CLOCK_FCLK:
            /*!< mcu fast clock/cpu clock */
            clock = Clock_MCU_Root_Clk_Mux_Output(Clock_Get_MCU_Root_Clk_Sel_Val());
            div = Clock_Get_MCU_HClk_Div_Val();
            return clock / (div + 1);

        case BL_SYSTEM_CLOCK_BCLK:
            /*!< mcu peri bus clock */
            clock = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_FCLK);
            div = Clock_Get_Peri_BClk_Div_Val();
            return clock / (div + 1);

        case BL_SYSTEM_CLOCK_XTAL:
            /*!< xtal clock */
            return Clock_Xtal_Output();

        case BL_SYSTEM_CLOCK_F32K:
            /*!< f32k clock */
            return Clock_F32k_Mux_Output(Clock_Get_F32k_Sel_Val());

        default:
            return 0;
    }
}

static inline uint32_t Clock_UART_Clk_Mux_Output(uint8_t sel)
{
    if (sel == 0) {
        /* fclk */
        return Clock_System_Clock_Get(BL_SYSTEM_CLOCK_FCLK);
    } else {
        /* 160m */
        return (160 * 1000 * 1000);
    }
}

static inline uint8_t Clock_Get_UART_Clk_Sel_Val(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_GLB);

    return BL_GET_REG_BITS_VAL(tmpVal, HBN_UART_CLK_SEL);
}

static inline uint8_t Clock_Get_UART_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG2);

    return BL_GET_REG_BITS_VAL(tmpVal, GLB_UART_CLK_DIV);
}

static inline uint32_t Clock_SPI_Clk_Mux_Output(void)
{
    /* pbclk */
    return Clock_System_Clock_Get(BL_SYSTEM_CLOCK_BCLK);
}

static inline uint8_t Clock_Get_SPI_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG3);

    return BL_GET_REG_BITS_VAL(tmpVal, GLB_SPI_CLK_DIV);
}

static inline uint32_t Clock_I2C_Clk_Mux_Output()
{
    /* pbclk */
    return Clock_System_Clock_Get(BL_SYSTEM_CLOCK_BCLK);
}

static inline uint8_t Clock_Get_I2C_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG3);

    return BL_GET_REG_BITS_VAL(tmpVal, GLB_I2C_CLK_DIV);
}

static inline uint8_t Clock_Get_GPADC_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_GPADC_32M_SRC_CTRL);

    return BL_GET_REG_BITS_VAL(tmpVal, GLB_GPADC_32M_CLK_DIV);
}

static inline uint32_t Clock_GPADC_Clk_Output(uint8_t sel)
{
    if (sel == 0) {
        /* 96m */
        return (96 * 1000 * 1000);
    } else {
        /* xclk */
        return Clock_System_Clock_Get(BL_SYSTEM_CLOCK_XCLK);
    }
}

static inline uint8_t Clock_Get_GPADC_32M_Clk_Sel_Val(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_GPADC_32M_SRC_CTRL);

    return BL_GET_REG_BITS_VAL(tmpVal, GLB_GPADC_32M_CLK_SEL);
}

static inline uint32_t Clock_GPADC_Clk_Mux_Output(uint8_t sel)
{
    uint32_t div = 0;

    if (sel == 1) {
        /* f32k clk */
        return Clock_F32k_Mux_Output(Clock_Get_F32k_Sel_Val());
    } else {
        div = Clock_Get_GPADC_Div_Val();
        return Clock_GPADC_Clk_Output(Clock_Get_GPADC_32M_Clk_Sel_Val()) / (div + 1);
    }
}

static inline uint8_t Clock_Get_GPADC_Clk_Sel_Val(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_PIR_CFG);

    return BL_GET_REG_BITS_VAL(tmpVal, HBN_PIR_EN);
}

static inline uint32_t Clock_GPDAC_Clk_Mux_Output(uint8_t sel)
{
    if (sel == 0) {
        /* pll 32m */
        return (32 * 1000 * 1000);
    } else {
        /* xclk */
        return Clock_System_Clock_Get(BL_SYSTEM_CLOCK_XCLK);
    }
}

static inline uint8_t Clock_Get_GPDAC_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL);

    return BL_GET_REG_BITS_VAL(tmpVal, GLB_DIG_512K_DIV);
}

static inline uint8_t Clock_Get_GPDAC_Clk_Sel_Val(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DIG32K_WAKEUP_CTRL);

    return BL_GET_REG_BITS_VAL(tmpVal, GLB_DIG_CLK_SRC_SEL);
}

// static inline uint32_t Clock_PWM_Clk_Mux_Output(uint8_t sel)
// {
//     if (sel == 0) {
//         /* xclk */
//         return Clock_System_Clock_Get(BL_SYSTEM_CLOCK_XCLK);
//     } else if (sel == 1) {
//         /* pbclk */
//         return Clock_System_Clock_Get(BL_SYSTEM_CLOCK_BCLK);
//     } else {
//         /* f32k clk */
//         return Clock_F32k_Mux_Output(Clock_Get_F32k_Sel_Val());
//     }
// }

// static inline uint8_t Clock_Get_PWM_Div_Val(void)
// {
//     uint32_t tmpVal;

//     tmpVal = BL_RD_REG(PWM_BASE + PWM_CHANNEL_OFFSET, PWM_CLKDIV);

//     return tmpVal;
// }

// static inline uint8_t Clock_Get_PWM_Clk_Sel_Val(void)
// {
//     uint32_t tmpVal;

//     tmpVal = BL_RD_REG(PWM_BASE + PWM_CHANNEL_OFFSET, PWM_CONFIG);

//     return BL_GET_REG_BITS_VAL(tmpVal, PWM_REG_CLK_SEL);
// }

static inline uint32_t Clock_IR_Clk_Mux_Output(void)
{
    /* xclk */
    return Clock_System_Clock_Get(BL_SYSTEM_CLOCK_XCLK);
}

static inline uint8_t Clock_Get_IR_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG2);

    return BL_GET_REG_BITS_VAL(tmpVal, GLB_IR_CLK_DIV);
}

static inline uint8_t Clock_Get_SF_Clk_Sel2_Val(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG2);

    return BL_GET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL2);
}

static inline uint32_t Clock_SF_SEL2_Clk_Mux_Output(uint8_t sel)
{
    if (sel == 0) {
        /* 120m */
        return (120 * 1000 * 1000);
    } else if (sel == 1) {
        /* xclk */
        return Clock_System_Clock_Get(BL_SYSTEM_CLOCK_XCLK);
    } else {
        /* 48m */
        return (48 * 1000 * 1000);
    }
}

static inline uint32_t Clock_SF_SEL_Clk_Mux_Output(uint8_t sel)
{
    if (sel == 0) {
        /* sf sel2 */
        return Clock_SF_SEL2_Clk_Mux_Output(Clock_Get_SF_Clk_Sel2_Val());
    } else if (sel == 1) {
        /* 80m */
        return (80 * 1000 * 1000);
    } else if (sel == 2) {
        /* pbclk */
        return Clock_System_Clock_Get(BL_SYSTEM_CLOCK_BCLK);
    } else {
        /* 96m */
        return (96 * 1000 * 1000);
    }
}

static inline uint8_t Clock_Get_SF_Clk_Sel_Val(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG2);

    return BL_GET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_SEL);
}

static inline uint8_t Clock_Get_SF_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CLK_CFG2);

    return BL_GET_REG_BITS_VAL(tmpVal, GLB_SF_CLK_DIV);
}

/****************************************************************************/ /**
 * @brief  Get Peripheral Clock
 *
 * @param  type: Peripheral clock type
 *
 * @return Peripheral clock value
 *
*******************************************************************************/
uint32_t Clock_Peripheral_Clock_Get(BL_Peripheral_Type type)
{
    uint32_t clock = 0;
    uint32_t div = 0;

    switch (type) {
        /*!< uart0 clock */
        case BL_PERIPHERAL_CLOCK_UART0:
            ATTR_FALLTHROUGH();

        /*!< uart1 clock */
        case BL_PERIPHERAL_CLOCK_UART1:
            clock = Clock_UART_Clk_Mux_Output(Clock_Get_UART_Clk_Sel_Val());
            div = Clock_Get_UART_Div_Val();
            return clock / (div + 1);

        /*!< FLASH clock */
        case BL_PERIPHERAL_CLOCK_FLASH:
            clock = Clock_SF_SEL_Clk_Mux_Output(Clock_Get_SF_Clk_Sel_Val());
            div = Clock_Get_SF_Div_Val();
            return clock / (div + 1);

        /*!< spi0 clock */
        case BL_PERIPHERAL_CLOCK_SPI0:
            clock = Clock_SPI_Clk_Mux_Output();
            div = Clock_Get_SPI_Div_Val();
            return clock / (div + 1);

        /*!< i2c0 clock */
        case BL_PERIPHERAL_CLOCK_I2C0:
            clock = Clock_I2C_Clk_Mux_Output();
            div = Clock_Get_I2C_Div_Val();
            return clock / (div + 1);

        /*!< GPADC clock */
        case BL_PERIPHERAL_CLOCK_GPADC:
            return Clock_GPADC_Clk_Mux_Output(Clock_Get_GPADC_Clk_Sel_Val());

        /*!< GPDAC clock */
        case BL_PERIPHERAL_CLOCK_GPDAC:
            clock = Clock_GPDAC_Clk_Mux_Output(Clock_Get_GPDAC_Clk_Sel_Val());
            div = Clock_Get_GPDAC_Div_Val();
            return clock / (div + 1);

        /*!< PWM clock */
        // case BL_PERIPHERAL_CLOCK_PWM:
        //     clock = Clock_PWM_Clk_Mux_Output(Clock_Get_PWM_Clk_Sel_Val());
        //     div = Clock_Get_PWM_Div_Val();
        //     return clock / div;

        /*!< IR clock */
        case BL_PERIPHERAL_CLOCK_IR:
            clock = Clock_IR_Clk_Mux_Output();
            div = Clock_Get_IR_Div_Val();
            return clock / (div + 1);

        default:
            return 0;
    }
}

/*@} end of group CLOCK_Public_Functions */

/*@} end of group CLOCK */

/*@} end of group BL602_Peripheral_Driver */
