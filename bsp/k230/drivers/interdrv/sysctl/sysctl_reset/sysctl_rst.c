/* Copyright (c) 2023, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <rtthread.h>
#include <stdbool.h>
#include "sysctl_rst.h"
#include "ioremap.h"
#include "board.h"

volatile sysctl_rst_t* sysctl_rst = (volatile sysctl_rst_t*)RMU_BASE_ADDR;

static bool sysctl_reset_cpu(volatile uint32_t *reset_reg, uint8_t reset_bit, uint8_t done_bit)
{
    /* clear done bit */
    *reset_reg |= (1 << done_bit);
    *reset_reg |= (1 << (done_bit + 0x10));  /* write enable */
    /* usleep(100); */
    rt_thread_delay(1);

    /* set reset bit */
    *reset_reg |= (1 << reset_bit);
    *reset_reg |= (1 << (reset_bit + 0x10));  /* write enable */
    /* usleep(100); */
    rt_thread_delay(1);

    /* clear reset bit */
    if(0x9110100c == (uint64_t)reset_reg)
    {
        *reset_reg &= ~(1 << reset_bit);
        *reset_reg |= (1 << (reset_bit + 0x10));   /* write enable */
    }
    /* usleep(100); */
    rt_thread_delay(1);

    /* check done bit */
    if(*reset_reg & (1 << done_bit))
        return true;
    else
        return false;
}

static bool sysctl_reset_hw_done(volatile uint32_t *reset_reg, uint8_t reset_bit, uint8_t done_bit)
{
    *reset_reg |= (1 << done_bit);      /* clear done bit */
    /* usleep(100); */
    rt_thread_delay(1);

    *reset_reg |= (1 << reset_bit);     /* set reset bit */
    /* usleep(100); */
    rt_thread_delay(1);
    /* check done bit */
    if(*reset_reg & (1 << done_bit))
        return true;
    else
        return false;
}

static bool sysctl_reset_sw_done(volatile uint32_t *reset_reg, uint8_t reset_bit, uint32_t reset_en)
{
    if(0 == reset_en)
    {
        if((0x91101020 == (uint64_t)reset_reg) || (0x91101024 == (uint64_t)reset_reg) || (0x91101080 == (uint64_t)reset_reg) || (0x91101064 == (uint64_t)reset_reg))
        {
            *reset_reg &= ~(1 << reset_bit);     /* set reset bit, 0 is assert */
        }
        else
        {
            *reset_reg |= (1 << reset_bit);     /* set reset bit, 1 is assert */
        }
    }
    else
    {
        *reset_reg |= (1 << reset_bit) | (1 << reset_en);     /* set reset bit */
    }
    /* usleep(100); */
    rt_thread_delay(1);

    if((0x91101004 != (uint64_t)reset_reg) && (0x9110100c != (uint64_t)reset_reg))
    {
        if(0x911010a8 == (uint64_t)reset_reg)
        {
            *reset_reg &= ~(1 << reset_bit);    /* clear reset bit, 0 is clear */
        }
        else
        {
            *reset_reg |= (1 << reset_bit);    /* clear reset bit, 1 is clear */
        }
    }
    /* usleep(100); */
    rt_thread_delay(1);

    return true;
}

bool sysctl_reset(sysctl_reset_e reset)
{
    switch(reset)
    {
        case SYSCTL_RESET_CPU0_CORE:
            return sysctl_reset_cpu((volatile uint32_t *)&sysctl_rst->cpu0_rst_ctl, 0, 12);
        case SYSCTL_RESET_CPU1_CORE:
            return sysctl_reset_cpu((volatile uint32_t *)&sysctl_rst->cpu1_rst_ctl, 0, 12);

        case SYSCTL_RESET_AI:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->ai_rst_ctl, 0, 31);
        case SYSCTL_RESET_VPU:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->vpu_rst_ctl, 0, 31);
        case SYSCTL_RESET_HS:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->hisys_rst_ctl, 0, 4);
        case SYSCTL_RESET_HS_AHB:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->hisys_rst_ctl, 1, 5);
        case SYSCTL_RESET_SDIO0:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->sdc_rst_ctl, 0, 28);
        case SYSCTL_RESET_SDIO1:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->sdc_rst_ctl, 1, 29);
        case SYSCTL_RESET_SDIO_AXI:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->sdc_rst_ctl, 2, 30);
        case SYSCTL_RESET_USB0:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->usb_rst_ctl, 0, 28);
        case SYSCTL_RESET_USB1:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->usb_rst_ctl, 1, 29);
        case SYSCTL_RESET_USB0_AHB:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->usb_rst_ctl, 0, 30);
        case SYSCTL_RESET_USB1_AHB:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->usb_rst_ctl, 1, 31);
        case SYSCTL_RESET_SPI0:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->spi_rst_ctl, 0, 28);
        case SYSCTL_RESET_SPI1:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->spi_rst_ctl, 1, 29);
        case SYSCTL_RESET_SPI2:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->spi_rst_ctl, 2, 30);
        case SYSCTL_RESET_SEC:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->sec_rst_ctl, 0, 31);
        case SYSCTL_RESET_PDMA:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->dma_rst_ctl, 0, 28);
        case SYSCTL_RESET_SDMA:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->dma_rst_ctl, 1, 29);
        case SYSCTL_RESET_DECOMPRESS:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->decompress_rst_ctl, 0, 31);
        case SYSCTL_RESET_SRAM:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->sram_rst_ctl, 0, 28);
        case SYSCTL_RESET_SHRM_AXIM:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->sram_rst_ctl, 2, 30);
        case SYSCTL_RESET_SHRM_AXIS:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->sram_rst_ctl, 3, 31);
        case SYSCTL_RESET_NONAI2D:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->nonai2d_rst_ctl, 0, 31);
        case SYSCTL_RESET_MCTL:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->mctl_rst_ctl, 0, 31);
        case SYSCTL_RESET_ISP:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->isp_rst_ctl, 6, 29);
        case SYSCTL_RESET_ISP_DW:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->isp_rst_ctl, 5, 28);
        case SYSCTL_RESET_DPU:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->dpu_rst_ctl, 0, 31);
        case SYSCTL_RESET_DISP:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->disp_rst_ctl, 0, 31);
        case SYSCTL_RESET_GPU:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->v2p5d_rst_ctl, 0, 31);
        case SYSCTL_RESET_AUDIO:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->audio_rst_ctl, 0, 31);

        case SYSCTL_RESET_TIMER0:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl, 0, 0);
        case SYSCTL_RESET_TIMER1:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl, 1, 0);
        case SYSCTL_RESET_TIMER2:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl, 2, 0);
        case SYSCTL_RESET_TIMER3:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl, 3, 0);
        case SYSCTL_RESET_TIMER4:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl, 4, 0);
        case SYSCTL_RESET_TIMER5:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl, 5, 0);
        case SYSCTL_RESET_TIMER_APB:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl, 6, 0);
        case SYSCTL_RESET_HDI:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl, 7, 0);
        case SYSCTL_RESET_WDT0:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl, 12, 0);
        case SYSCTL_RESET_WDT1:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl, 13, 0);
        case SYSCTL_RESET_WDT0_APB:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl, 14, 0);
        case SYSCTL_RESET_WDT1_APB:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl, 15, 0);
        case SYSCTL_RESET_TS_APB:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl, 16, 0);
        case SYSCTL_RESET_MAILBOX:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl, 17, 0);
        case SYSCTL_RESET_STC:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl, 18, 0);
        case SYSCTL_RESET_PMU:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl, 19, 0);
        case SYSCTL_RESET_LS_APB:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->losys_rst_ctl, 0, 0);
        case SYSCTL_RESET_UART0:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->losys_rst_ctl, 1, 0);
        case SYSCTL_RESET_UART1:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->losys_rst_ctl, 2, 0);
        case SYSCTL_RESET_UART2:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->losys_rst_ctl, 3, 0);
        case SYSCTL_RESET_UART3:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->losys_rst_ctl, 4, 0);
        case SYSCTL_RESET_UART4:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->losys_rst_ctl, 5, 0);
        case SYSCTL_RESET_I2C0:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->losys_rst_ctl, 6, 0);
        case SYSCTL_RESET_I2C1:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->losys_rst_ctl, 7, 0);
        case SYSCTL_RESET_I2C2:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->losys_rst_ctl, 8, 0);
        case SYSCTL_RESET_I2C3:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->losys_rst_ctl, 9, 0);
        case SYSCTL_RESET_I2C4:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->losys_rst_ctl, 10, 0);
        case SYSCTL_RESET_JAMLINK0_APB:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->losys_rst_ctl, 11, 0);
        case SYSCTL_RESET_JAMLINK1_APB:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->losys_rst_ctl, 12, 0);
        case SYSCTL_RESET_JAMLINK2_APB:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->losys_rst_ctl, 13, 0);
        case SYSCTL_RESET_JAMLINK3_APB:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->losys_rst_ctl, 14, 0);
        case SYSCTL_RESET_CODEC_APB:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->losys_rst_ctl, 17, 0);
        case SYSCTL_RESET_GPIO_DB:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->losys_rst_ctl, 18, 0);
        case SYSCTL_RESET_GPIO_APB:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->losys_rst_ctl, 19, 0);
        case SYSCTL_RESET_ADC:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->losys_rst_ctl, 20, 0);
        case SYSCTL_RESET_ADC_APB:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->losys_rst_ctl, 21, 0);
        case SYSCTL_RESET_PWM_APB:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->losys_rst_ctl, 22, 0);

        case SYSCTL_RESET_CPU0_FLUSH:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->cpu0_rst_ctl, 4, 20);
        case SYSCTL_RESET_CPU1_FLUSH:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->cpu1_rst_ctl, 4, 20);
        case SYSCTL_RESET_SHRM_APB:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->sram_rst_ctl, 1, 0);
        case SYSCTL_RESET_CSI0_APB:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->isp_rst_ctl, 0, 0);
        case SYSCTL_RESET_CSI1_APB:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->isp_rst_ctl, 1, 0);
        case SYSCTL_RESET_CSI2_APB:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->isp_rst_ctl, 2, 0);
        case SYSCTL_RESET_CSI_DPHY_APB:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->isp_rst_ctl, 3, 0);
        case SYSCTL_RESET_ISP_AHB:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->isp_rst_ctl, 4, 0);
        case SYSCTL_RESET_M0:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->isp_rst_ctl, 7, 0);
        case SYSCTL_RESET_M1:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->isp_rst_ctl, 8, 0);
        case SYSCTL_RESET_M2:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->isp_rst_ctl, 9, 0);
        case SYSCTL_RESET_SPI2AXI:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->spi2axi_rst_ctl, 0, 0);

        default:
            return false;
    }
}

bool sysctl_set_reset_time(sysctl_reset_time_e reset, uint32_t tim0, uint32_t tim1, uint32_t tim2)
{
    volatile uint32_t ret;

    switch(reset)
    {
        case SYSCTL_RESET_TIME_CPU0:
        {
            if((tim1 > 0xF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->cpu0_rst_tim;
                ret &= 0xf0000fff;
                sysctl_rst->cpu0_rst_tim = ret | ((tim1 << 12) | (tim2 << 20));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_CPU0_APB:
        {
            if((tim1 > 0xF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->cpu0_rst_tim;
                ret &= 0xfffff00f;
                sysctl_rst->cpu0_rst_tim = ret | ((tim1 << 4) | (tim2 << 8));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_CPU1:
        {
            if((tim1 > 0xF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->cpu1_rst_tim;
                ret &= 0xfff00fff;
                sysctl_rst->cpu1_rst_tim = ret | ((tim1 << 12) | (tim2 << 16));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_CPU1_APB:
        {
            if((tim1 > 0xF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->cpu1_rst_tim;
                ret &= 0xfffff00f;
                sysctl_rst->cpu1_rst_tim = ret | ((tim1 << 4) | (tim2 << 8));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_AI:
        {
            if((tim1 > 0xF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->ai_rst_tim;
                ret &= 0xfffff00f;
                sysctl_rst->ai_rst_tim = ret | ((tim1 << 4) | (tim2 << 8));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_VPU:
        {
            if((tim1 > 0xF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->vpu_rst_tim;
                ret &= 0xfffff00f;
                sysctl_rst->vpu_rst_tim = ret | ((tim1 << 4) | (tim2 << 8));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_HS_HCLK:
        {
            if((tim1 > 0x1F) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->hisys_hclk_tim;
                ret &= 0xfff0f0ff;
                sysctl_rst->hisys_hclk_tim = ret | ((tim1 << 8) | (tim2 << 16));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_SDCTL:
        {
            if((tim1 > 0x1F) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->sdctl_rst_tim;
                ret &= 0xfff0f0ff;
                sysctl_rst->sdctl_rst_tim = ret | ((tim1 << 8) | (tim2 << 16));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_USB:
        {
            if((tim1 > 0xF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->usb_rst_tim;
                ret &= 0xffffff00;
                sysctl_rst->usb_rst_tim = ret | ((tim1 << 0) | (tim2 << 4));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_USB_AHB:
        {
            if((tim1 > 0xF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->usb_rst_tim;
                ret &= 0xff0000ff;
                sysctl_rst->usb_rst_tim = ret | ((tim1 << 8) | (tim2 << 16));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_SPI:
        {
            if((tim1 > 0x3F) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->spi_rst_tim;
                ret &= 0xfff0f0ff;
                sysctl_rst->spi_rst_tim = ret | ((tim1 << 8) | (tim2 << 16));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_SEC_SYS:
        {
            if((tim1 > 0xFF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->sec_sys_rst_tim;
                ret &= 0xfff0f0ff;
                sysctl_rst->sec_sys_rst_tim = ret | ((tim1 << 8) | (tim2 << 16));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_DMAC:
        {
            if((tim1 > 0x7) || (tim2 > 0x7))
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->dmac_rst_tim;
                ret &= 0xfff0f0ff;
                sysctl_rst->dmac_rst_tim = ret | ((tim1 << 8) | (tim2 << 16));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_DECOMPRESS:
        {
            if((tim1 > 0x7) || (tim2 > 0x7))
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->decompress_rst_tim;
                ret &= 0xfff0f0ff;
                sysctl_rst->decompress_rst_tim = ret | ((tim1 << 8) | (tim2 << 16));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_SRAM:
        {
            if((tim1 > 0xF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->sram_rst_tim;
                ret &= 0xfff0f0ff;
                sysctl_rst->sram_rst_tim = ret | ((tim1 << 8) | (tim2 << 16));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_NONAI2D:
        {
            if((tim1 > 0xF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->nonai2d_rst_tim;
                ret &= 0xfff0f0ff;
                sysctl_rst->nonai2d_rst_tim = ret | ((tim1 << 8) | (tim2 << 16));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_MCTL:
        {
            if(tim0 > 0xF)
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->mctl_rst_tim;
                ret &= 0xffffffc0;
                sysctl_rst->mctl_rst_tim = ret | (tim0 << 0);
                return true;
            }
        }
        case SYSCTL_RESET_TIME_ISP:
        {
            if((tim0 > 0xFF) || (tim1 > 0xF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->isp_rst_tim;
                ret &= 0xfff0f0f0;
                sysctl_rst->isp_rst_tim = ret | ((tim0 << 0) | (tim1 << 8) | (tim2 << 16));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_ISP_DW:
        {
            if((tim0 > 0xFF) || (tim1 > 0xF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->isp_dw_rst_tim;
                ret &= 0xfff0f0f0;
                sysctl_rst->isp_dw_rst_tim = ret | ((tim0 << 0) | (tim1 << 8) | (tim2 << 16));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_DPU:
        {
            if((tim1 > 0xF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->dpu_rst_tim;
                ret &= 0xfff0f0ff;
                sysctl_rst->dpu_rst_tim = ret | ((tim1 << 8) | (tim2 << 16));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_DISP_SYS:
        {
            if((tim0 > 0xFF) || (tim1 > 0xFF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->disp_sys_rst_tim;
                ret &= 0xfff0f0f0;
                sysctl_rst->disp_sys_rst_tim = ret | ((tim0 << 0) | (tim1 << 8) | (tim2 << 16));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_V2P5D_SYS:
        {
            if((tim0 > 0xFF) || (tim1 > 0xFF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->v2p5d_sys_rst_tim;
                ret &= 0xfff0f0f0;
                sysctl_rst->v2p5d_sys_rst_tim = ret | ((tim0 << 0) | (tim1 << 8) | (tim2 << 16));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_AUDIO:
        {
            if((tim1 > 0xF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                ret = sysctl_rst->audio_rst_tim;
                ret &= 0xfffff00f;
                sysctl_rst->audio_rst_tim = ret | ((tim1 << 4) | (tim2 << 8));
                return true;
            }
        }

        default:
            return false;
    }
}

int rt_hw_sysctl_rst_init(void)
{
    sysctl_rst = rt_ioremap((void*)RMU_BASE_ADDR, RMU_IO_SIZE);
    if(!sysctl_rst)
    {
        rt_kprintf("sysctl_rst ioremap error\n");
        return -1;
    }

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_sysctl_rst_init);