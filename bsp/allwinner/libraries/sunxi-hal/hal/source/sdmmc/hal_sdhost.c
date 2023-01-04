/**
  * @file  hal_sdhost.c
  * @author  ALLWINNERTECH IOT WLAN Team
  */

/*
 * Copyright (C) 2017 ALLWINNERTECH TECHNOLOGY CO., LTD. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *    3. Neither the name of ALLWINNERTECH TECHNOLOGY CO., LTD. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, )|hhst->sdio_irq_maskPROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "_sdhost.h"
#include "sunxi_hal_common.h"
#include "stdint.h"
//#include "io.h"
//#include "hal_prcm.h"
#include "hal_ccm.h"
#include "hal_gpio.h"
#include "hal_board.h"

#include "hal_dev.h"
#include "hal_clock.h"
#include "sdmmc/sys/param.h"

#include "hal_sdhost.h"
#ifdef CONFIG_USE_SDIO
#include "sdio.h"
#endif
#include "sdmmc.h"

#include "_sd_define.h"
#include "_core.h"
#ifndef CONFIG_KERNEL_FREERTOS
#include "osal/os/RT-Thread/os_util.h"
#else
#include "osal/os/FreeRTOS/os_util.h"
#endif
#include "interrupt.h"

//#include "k_arch.h"
extern uint32_t sdmmc_pinctrl_init(struct mmc_host *host);
extern int mmc_gpiod_request_cd_irq(struct mmc_host* host);
//#define __dsb__() dsb(0xf)

#ifndef UINT_MAX
    #define UINT_MAX (~0U)
#endif

/*
#define SDC_REQUEST_IRQ(n, hdl)         HAL_NVIC_SetIRQHandler(n, hdl)
#define SDC_SetPriority(n, l)           HAL_NVIC_SetPriority(n, l)
#define SDC_ENABLE_IRQ(n)               HAL_NVIC_EnableIRQ(n)
#define SDC_CONFIG_IRQ(n, hdl, l)       HAL_NVIC_ConfigExtIRQ(n, hdl, l)
#define SDC_DISABLE_IRQ(n)              HAL_NVIC_DisableIRQ(n)
#define SDC_CLEAR_IRQPINGD(n)           HAL_NVIC_ClearPendingIRQ(n)
#define SDC_IRQHandler                  NVIC_IRQHandler
*/

#define SDC_REQUEST_IRQ(n, hdl,d)         ({SDC_LOGD("%s,%d,sdc %d irq request \n",__func__, __LINE__, d->sdc_id);\
                                            request_irq(n, hdl, 0, "sdmmc",d);})
#define SDC_FREE_IRQ(n, d)         (free_irq(n, d))
#define SDC_SetPriority(n, l)           ({SDC_LOGN("Not imp %s,%d\n", __FUNCTION__,__LINE__);})
#define SDC_ENABLE_IRQ(n)               enable_irq(n)
#define SDC_CONFIG_IRQ(n, hdl, l)       ({SDC_LOGN("Not imp %s,%d\n", __FUNCTION__,__LINE__);})
#define SDC_DISABLE_IRQ(n)              disable_irq(n)
//#define SDC_CLEAR_IRQPINGD(n)           gic_clear_pending(n)
#define SDC_CLEAR_IRQPINGD(n)        ({SDC_LOGN("Not imp %s,%d\n", __FUNCTION__,__LINE__);})
//#define SDC_CLEAR_IRQPINGD(n)      free_irq(n)
//#define SDC_IRQHandler                  interrupt_handler_t
#define SDC_IRQHandler                  irq_handler_t  *

#define NUSE_STANDARD_INTERFACE  1
#ifdef NUSE_STANDARD_INTERFACE
#define SDC1_SUPPORT                    1
#define SDC_CCM_SDC0_SCLK_CTRL          (SDC_CCM_BASE + 0x830)
#define SDC_CCM_SDC1_SCLK_CTRL          (SDC_CCM_BASE + 0x834)
#define SDC_CCM_SDC_BUS_GATE_RESET      (SDC_CCM_BASE + 0x84c)
/*
#define SDC0_CCM_BusForceReset()        HAL_CCM_BusForcePeriphReset(CCM_BUS_PERIPH_BIT_SDC0)
#define SDC0_CCM_BusReleaseRest()       HAL_CCM_BusReleasePeriphReset(CCM_BUS_PERIPH_BIT_SDC0)
#define SDC0_CCM_BusEnableClock()       HAL_CCM_BusEnablePeriphClock(CCM_BUS_PERIPH_BIT_SDC0)
#define SDC0_CCM_BusDisableClock()      HAL_CCM_BusDisablePeriphClock(CCM_BUS_PERIPH_BIT_SDC0)
#define SDC0_CCM_EnableMClock()         HAL_CCM_SDC0_EnableMClock()
#define SDC0_DisableMClock              HAL_CCM_SDC0_DisableMClock
#define SDC0_SetMClock                  HAL_CCM_SDC0_SetMClock
*/

#define SDC0_CCM_BusForceReset()        ({int v =  readl(SDC_CCM_SDC_BUS_GATE_RESET); v &= ~(1<<16); writel(v,SDC_CCM_SDC_BUS_GATE_RESET);})
#define SDC0_CCM_BusReleaseRest()       ({int v =  readl(SDC_CCM_SDC_BUS_GATE_RESET); v |= (1<<16); writel(v,SDC_CCM_SDC_BUS_GATE_RESET);})
#define SDC0_CCM_BusEnableClock()       ({int v =  readl(SDC_CCM_SDC_BUS_GATE_RESET); v |= (1<<0); writel(v,SDC_CCM_SDC_BUS_GATE_RESET);})
#define SDC0_CCM_BusDisableClock()      ({int v =  readl(SDC_CCM_SDC_BUS_GATE_RESET); v &= ~(1<<0); writel(v,SDC_CCM_SDC_BUS_GATE_RESET);})
#define SDC0_CCM_EnableMClock()         ({int v =  readl(SDC_CCM_SDC0_SCLK_CTRL); v |= (1<<31); writel(v,SDC_CCM_SDC0_SCLK_CTRL);})
#define SDC0_DisableMClock()              ({int v =  readl(SDC_CCM_SDC0_SCLK_CTRL); v &= ~(1<<31); writel(v,SDC_CCM_SDC0_SCLK_CTRL);})


#define SDC1_CCM_BusForceReset()        ({int v =  readl(SDC_CCM_SDC_BUS_GATE_RESET); v &= ~(1<<17); writel(v,SDC_CCM_SDC_BUS_GATE_RESET);})
#define SDC1_CCM_BusReleaseRest()       ({int v =  readl(SDC_CCM_SDC_BUS_GATE_RESET); v |= (1<<17); writel(v,SDC_CCM_SDC_BUS_GATE_RESET);})
#define SDC1_CCM_BusEnableClock()       ({int v =  readl(SDC_CCM_SDC_BUS_GATE_RESET); v |= (1<<1); writel(v,SDC_CCM_SDC_BUS_GATE_RESET);})
#define SDC1_CCM_BusDisableClock()      ({int v =  readl(SDC_CCM_SDC_BUS_GATE_RESET); v &= ~(1<<1); writel(v,SDC_CCM_SDC_BUS_GATE_RESET);})
#define SDC1_CCM_EnableMClock()         ({int v =  readl(SDC_CCM_SDC1_SCLK_CTRL); v |= (1<<31); writel(v,SDC_CCM_SDC1_SCLK_CTRL);})
#define SDC1_DisableMClock()              ({int v =  readl(SDC_CCM_SDC1_SCLK_CTRL); v &= ~(1<<31); writel(v,SDC_CCM_SDC1_SCLK_CTRL);})

#define SDC1_SET_GPIO_MUX()                   ({int v =  readl(SDC_GPIO_BASE + 0xd8);\
                                               SDC_LOGD("RAW SET SDC1 MUX\n");\
                                               v &= ~(0xffffff); v |=0x222222;\
                                               writel(v,SDC_GPIO_BASE + 0xd8);\
                                               SDC_LOGD("RAW SDC1 MUX %x\n", readl(SDC_GPIO_BASE + 0xd8));})
#define SDC1_SET_GPIO_DRV()                   ({int v =  readl(SDC_GPIO_BASE + 0xec);\
                                               SDC_LOGD("RAW SET SDC1 DRV\n");\
                                               v &= ~(0xfff);\
                                               v |=0x000; writel(v,SDC_GPIO_BASE + 0xec);\
                                                SDC_LOGD("RAW SDC1 DRV %x\n",readl(SDC_GPIO_BASE + 0xec));})
#define SDC1_SET_GPIO_PULL()                  ({int v =  readl(SDC_GPIO_BASE + 0xf4);\
                                               SDC_LOGD("RAW SET SDC1 PULL\n");\
                                               v &= ~(0xfff);\
                                               v |=0x555; writel(v,SDC_GPIO_BASE + 0xf4);\
                                                SDC_LOGD("RAW SDC1 PULL %x\n",readl(SDC_GPIO_BASE + 0xf4));})


#define SDC_TIG_SET_GPIO_MUX()                  ({int v =  readl(SDC_GPIO_BASE + 0x28);\
                                               SDC_LOGD("+RAW SET TIG SDC MUX %x\n", SDC_GPIO_BASE + 0x28);\
                                               v &= ~(0x0000F000); v |=0x00001000;\
                                               writel(v,SDC_GPIO_BASE + 0x28);\
                                                SDC_LOGD("-RAW SDC TIG MUX %x\n", readl(SDC_GPIO_BASE + 0x28));})
#define SDC_TIG_SET_GPIO_DRV()                   ({int v =  readl(SDC_GPIO_BASE + 0x38);\
                                               SDC_LOGD("+RAW SET SDC TIG DRV %x\n", SDC_GPIO_BASE + 0x38);\
                                               v &= ~(0x00C00000);\
                                               v |=0x00C00000; writel(v,SDC_GPIO_BASE + 0x38);\
                                                SDC_LOGD("-RAW SDC TRG DRV %x\n",readl(SDC_GPIO_BASE + 0x38));})
#define SDC_TIG_SET_GPIO_PULL()                  ({int v =  readl(SDC_GPIO_BASE + 0x40);\
                                               SDC_LOGD("+RAW SET SDC TRG PULL %x\n", SDC_GPIO_BASE + 0x40);\
                                               v &= ~(0x00C00000);\
                                               v |=0x00400000; writel(v,SDC_GPIO_BASE + 0x40);\
                                                SDC_LOGD("-RAW SDC1 PULL %x\n",readl(SDC_GPIO_BASE + 0x40));})

#define SDC_TIG_SET_GPIO_DAT()                  ({int v =  readl(SDC_GPIO_BASE + 0x34);\
                                               SDC_LOGD("+raw set sdc trg dat %x\n",SDC_GPIO_BASE + 0x34);\
                                               v &= ~(0x00000800);\
                                               v |=0x00000800; writel(v,SDC_GPIO_BASE + 0x34);\
                                                SDC_LOGD("-RAW SDC1 DAT %x\n",readl(SDC_GPIO_BASE + 0x34));})


#define SDC_TIG_CLR_GPIO_DAT()                  ({int v =  readl(SDC_GPIO_BASE + 0x34);\
                                               SDC_LOGD("RAW SET SDC TRG dat\n");\
                                               v &= ~(0x00000800);\
                                               v |=0x00000000; writel(v,SDC_GPIO_BASE + 0x34);\
                                                SDC_LOGD("RAW SDC1 dat %x\n",readl(SDC_GPIO_BASE + 0x34));})




#define HAL_BoardIoctl(a,b,c)           ({SDC_LOGN("NOT IMP %s,%d\n",__FUNCTION__, __LINE__);})
#define HAL_GPIO_ReadPin(cd_gpios, data) ({hal_gpio_get_data(cd_gpios, (gpio_data_t *)data);\
                        *(data);})

#else
#define SDC0_CCM_BusForceReset()        HAL_CCM_BusForcePeriphReset(CCM_BUS_PERIPH_BIT_SDC0)
#define SDC0_CCM_BusReleaseRest()       HAL_CCM_BusReleasePeriphReset(CCM_BUS_PERIPH_BIT_SDC0)
#define SDC0_CCM_BusEnableClock()       HAL_CCM_BusEnablePeriphClock(CCM_BUS_PERIPH_BIT_SDC0)
#define SDC0_CCM_BusDisableClock()      HAL_CCM_BusDisablePeriphClock(CCM_BUS_PERIPH_BIT_SDC0)
#define SDC0_CCM_EnableMClock()         HAL_CCM_SDC0_EnableMClock()
#define SDC0_DisableMClock              HAL_CCM_SDC0_DisableMClock
#define SDC0_SetMClock                  HAL_CCM_SDC0_SetMClock

#define SDC1_SUPPORT                    1
#define SDC1_CCM_BusForceReset()        HAL_CCM_BusForcePeriphReset(CCM_BUS_PERIPH_BIT_SDC1)
#define SDC1_CCM_BusReleaseRest()       HAL_CCM_BusReleasePeriphReset(CCM_BUS_PERIPH_BIT_SDC1)
#define SDC1_CCM_BusEnableClock()       HAL_CCM_BusEnablePeriphClock(CCM_BUS_PERIPH_BIT_SDC1)
#define SDC1_CCM_BusDisableClock()      HAL_CCM_BusDisablePeriphClock(CCM_BUS_PERIPH_BIT_SDC1)
#define SDC1_CCM_EnableMClock()         HAL_CCM_SDC1_EnableMClock()
#define SDC1_DisableMClock              HAL_CCM_SDC1_DisableMClock
#define SDC1_SetMClock                  HAL_CCM_SDC1_SetMClock

#endif /* NUSE_STANDARD_INTERFACE */

#ifndef SDC1_SUPPORT
#define SDC1_SUPPORT 0
#endif

#define MEMS_VA2PA(x) __va_to_pa(x)

#if 0
#define mci_readl(host, reg) \
    ({  uint32_t val;\
        SDC_LOGD("+reg add 0x%x\n", (uint32_t)(host)->reg_base + reg);\
        val = readl((uint32_t)(host)->reg_base + reg);\
        SDC_LOGD("%s,%d\n", __FUNCTION__, __LINE__);\
        SDC_LOGD("-reg val 0x%x\n", val);\
        val;})
#define mci_writel(value, host, reg) \
    ({  uint32_t val;\
        SDC_LOGD("+reg add 0x%x write val 0x%x\n", (uint32_t)(host)->reg_base + reg, value);\
        writel((value), (uint32_t)(host)->reg_base + reg);\
        val = readl((uint32_t)(host)->reg_base + reg);\
        SDC_LOGD("%s,%d\n", __FUNCTION__, __LINE__);\
        SDC_LOGD("-reg read val 0x%x\n", val);})

#define mci_readw(host, reg) \
    ({  uint32_t val;\
        SDC_LOGD("+reg add 0x%x\n", (uint32_t)(host)->reg_base + reg);\
        val = readw((uint32_t)(host)->reg_base + reg);\
        SDC_LOGD("%s,%d\n", __FUNCTION__, __LINE__);\
        SDC_LOGD("-reg val 0x%x\n", val);\
        val;})
#define mci_writew(value, host, reg) \
    ({  uint32_t val;\
        SDC_LOGD("+reg add 0x%x write val 0x%x\n", (uint32_t)(host)->reg_base + reg, value);\
        writew((value), (uint32_t)(host)->reg_base + reg);\
        val = readl((uint32_t)(host)->reg_base + reg);\
        SDC_LOGD("%s,%d\n", __FUNCTION__, __LINE__);\
        SDC_LOGD("-reg read val 0x%x\n", val);})
#define mci_readb(host, reg) \
    ({  uint32_t val;\
        SDC_LOGD("+reg add 0x%x\n", (uint32_t)(host)->reg_base + reg);\
        val = readb((uint32_t)(host)->reg_base + reg);\
        SDC_LOGD("%s,%d\n", __FUNCTION__, __LINE__);\
        SDC_LOGD("-reg val 0x%x\n", val);\
        val;})
#define mci_writeb(value, host, reg) \
    ({  uint32_t val;\
        SDC_LOGD("+reg add 0x%x write val 0x%x\n", (uint32_t)(host)->reg_base + reg, value);\
        writeb((value), (uint32_t)(host)->reg_base + reg);\
        val = readl((uint32_t)(host)->reg_base + reg);\
        SDC_LOGD("%s,%d\n", __FUNCTION__, __LINE__);\
        SDC_LOGD("-reg read val 0x%x\n", val);})


#else
#define mci_readl(host, reg) \
        readl(HAL_PT_TO_U((host)->reg_base) + reg)
#define mci_writel(value, host, reg) \
        writel((value), HAL_PT_TO_U((host)->reg_base) + reg)

#define mci_writew(value, host, reg) \
        writew((value), HAL_PT_TO_U((host)->reg_base) + reg)

#define mci_readw(host, reg) \
        readw(HAL_PT_TO_U((host)->reg_base) + reg)

#define mci_readb(host, reg) \
        readb(HAL_PT_TO_U((host)->reg_base) + reg)

#define mci_writeb(value, host, reg) \
        writeb((value),HAL_PT_TO_U((host)->reg_base) + reg)
#endif

#define SDC_BUSY_WAIT_LOOP     (0xffffffff)
int32_t __mci_check_bit_clear(struct mmc_host *host, uint32_t reg_offset, uint32_t bit_map);

static struct mmc_host *_mci_host[SDC_NUM];

/**
 * sdc timer timeout flags
 */
static int __sdc_init_timeout_flags = 0;

static uint64_t __mci_get_rate(uint64_t bytes, uint64_t time_us)
{
    uint64_t ns;

    ns = time_us * 1000;
    bytes *= 1000000000;

    while (ns > UINT_MAX) {
        bytes >>= 1;
        ns >>= 1;
    }

    if (!ns)
        return 0;

    do_div(bytes, (uint32_t)ns);

    return bytes;
}

static void __mci_force_dump_host_info(struct mmc_host *host)
{
    uint16_t debug_mask = host->debug_mask;
    host->debug_mask |= ROM_DUMP_MASK | ROM_ERR_MASK;
    SDC_LOGE("*force dump gpio reg*\n");
    sdc_hex_dump_word((void *)SDC_GPIO_BASE+0xb0,0xff);
    sdc_hex_dump_word((void *)SDC_GPIO_BASE+0x340,0xff);
    SDC_LOGE("*force dump ccmu reg*\n");
    sdc_hex_dump_word((void *)SDC_CCM_SDC0_SCLK_CTRL ,0xff);
    sdc_hex_dump_word((void *)SDC_CCM_BASE ,0xff);
    SDC_LOGE("*force dump smc reg*\n");
    sdc_hex_dump_word((void *)(SMC0_BASE + 0x1000UL * host->sdc_id) ,0x150);
    SDC_LOGE("force dump state wait:%x,int_sum %x, int_err %x\n",\
            (unsigned int)host->wait, (unsigned int)host->int_sum, (unsigned int)host->int_err);
    SDC_LOGE("force dump done dma_done:%x,transfer_done %x\n",\
            (unsigned int)host->dma_done, (unsigned int)host->trans_done);
    host->debug_mask = debug_mask;
}

static int32_t __mci_exit_host(struct mmc_host *host)
{
    uint32_t rval;

#ifdef CONFIG_SDC_SUPPORT_1V8
    host->voltage = SDC_WOLTAGE_OFF;
#endif

    rval = mci_readl(host, SDXC_REG_GCTRL) | SDXC_HWReset;
    mci_writel(rval, host, SDXC_REG_GCTRL);
    __mci_check_bit_clear(host, SDXC_REG_GCTRL, SDXC_HWReset);

    return 0;
}

static __inline void __mci_sel_access_mode(struct mmc_host *host, uint32_t access_mode)
{
    mci_writel((mci_readl(host, SDXC_REG_GCTRL) & (~SDXC_ACCESS_BY_AHB)) | access_mode,
           host, SDXC_REG_GCTRL);
}

static int32_t __mci_reset(struct mmc_host *host)
{
    uint32_t value;
    uint32_t time = HAL_Ticks() + HAL_MSecsToTicks(1000) + 1;

    value = mci_readl(host, SDXC_REG_GCTRL)|SDXC_HWReset;
    mci_writel(value, host, SDXC_REG_GCTRL);
    while ((mci_readl(host, SDXC_REG_GCTRL) & SDXC_SoftReset) && (HAL_TimeBefore(HAL_Ticks(), time)));
    if (mci_readl(host, SDXC_REG_GCTRL) & SDXC_SoftReset) {
        SDC_LOGE("SDC reset time out\n");
        return -1;
    }
    SDC_LOGD("%s,%d SDC reset finish \n", __func__, __LINE__);

    return 0;
}

static int32_t __mci_program_clk(struct mmc_host *host)
{
    uint32_t value;
    int32_t ret = 0;
    uint32_t time = HAL_Ticks() + HAL_MSecsToTicks(1000) + 1;

    /* disable command done interrupt */
    mci_writel((mci_readl(host, SDXC_REG_IMASK) & (~SDXC_CmdDone))|host->sdio_irq_mask,
           host, SDXC_REG_IMASK);

    mci_writel(mci_readl(host, SDXC_REG_CLKCR) | SDXC_Mask_Data0,\
               host, SDXC_REG_CLKCR);

    value = SDXC_Start | SDXC_UPCLKOnly | SDXC_WaitPreOver;
    mci_writel(value, host, SDXC_REG_CMDR);

    do {
        value = mci_readl(host, SDXC_REG_CMDR);
    } while ((value & SDXC_Start) && HAL_TimeBefore(HAL_Ticks(), time));

    if (mci_readl(host, SDXC_REG_CMDR) & SDXC_Start) {
        SDC_LOGE("%s,%d SDC change clock time out\n", __func__, __LINE__);
        __mci_force_dump_host_info(host);
        ret = -1;
    }

    /* clear command done flag */
    value = mci_readl(host, SDXC_REG_RINTR);
    mci_writel(value, host, SDXC_REG_RINTR);

    mci_writel(mci_readl(host, SDXC_REG_CLKCR) & ~SDXC_Mask_Data0,\
               host, SDXC_REG_CLKCR);

    /* enable command done interrupt */
    mci_writel((mci_readl(host, SDXC_REG_IMASK) | SDXC_CmdDone)|host->sdio_irq_mask,
           host, SDXC_REG_IMASK);

    return ret;
}

static void __mci_trans_by_ahb(struct mmc_host *host, struct mmc_data *data)
{
    uint32_t i, j;
    uint32_t *buf_temp; /* Cortex-M3/4 can access data with unaligned address */
    uint32_t time;

    for (i = 0; i < data->sg_len; i++) {
        buf_temp = data->sg[i].buffer;
        if (data->flags & MMC_DATA_READ) {
            for (j = 0; j < (data->sg[i].len >> 2); j++) { /* sg[i].len should be multiply of 4 */
                time = HAL_Ticks() + HAL_MSecsToTicks(1000) + 1 ;
                while ((mci_readl(host, SDXC_REG_STAS) & SDXC_FIFOEmpty) &&
                       (HAL_TimeBefore(HAL_Ticks(), time)) && host->present);
                if(mci_readl(host, SDXC_REG_STAS) & SDXC_FIFOEmpty){
                    SDC_LOGE("read from fifo timeout1\n");
                    return;
                }
                buf_temp[j] = mci_readl(host, SDXC_REG_FIFO);
            }

            if((data->sg[i].len) & 0x3) {
                time = HAL_Ticks() + HAL_MSecsToTicks(1000) + 1;
                while ((mci_readl(host, SDXC_REG_STAS) & SDXC_FIFOEmpty) &&
                        (HAL_TimeBefore(HAL_Ticks(), time)) && host->present);
                if(mci_readl(host, SDXC_REG_STAS) & SDXC_FIFOEmpty){
                    SDC_LOGE("read from fifo timeout2\n");
                    return;
                }

                if(((data->sg[i].len) & 0x3) == 2){
                        buf_temp[j] = (uint16_t)mci_readl(host, SDXC_REG_FIFO);
                }else if(((data->sg[i].len) & 0x3) == 1){
                        buf_temp[j] = (uint8_t)mci_readl(host, SDXC_REG_FIFO);
                }else
                    SDC_BUG_ON(1);
            }
        } else if (data->flags & MMC_DATA_WRITE) {
            for (j = 0; j < (data->sg[i].len >> 2); j++) { /* sg[i].len should be multiply of 4 */
                time = HAL_Ticks() + HAL_MSecsToTicks(1000) + 1;
                while ((mci_readl(host, SDXC_REG_STAS) & SDXC_FIFOFull) &&
                       (HAL_TimeBefore(HAL_Ticks(), time)) && host->present);
                if(mci_readl(host, SDXC_REG_STAS) & SDXC_FIFOFull){
                    SDC_LOGE("write to fifo timeout1\n");
                    return;
                }

                mci_writel(buf_temp[j], host, SDXC_REG_FIFO);
            }

            if((data->sg[i].len) & 0x3) {
                time = HAL_Ticks() + HAL_MSecsToTicks(1000) + 1;
                while ((mci_readl(host, SDXC_REG_STAS) & SDXC_FIFOFull) &&
                        (HAL_TimeBefore(HAL_Ticks(), time)) && host->present);
                if(mci_readl(host, SDXC_REG_STAS) & SDXC_FIFOFull){
                    SDC_LOGE("write to fifo timeout2\n");
                    return;
                }

                if(((data->sg[i].len) & 0x3) == 2){
                        mci_writel((uint16_t)buf_temp[j], host, SDXC_REG_FIFO);
                }else if(((data->sg[i].len) & 0x3) == 1){
                        mci_writel((uint8_t)buf_temp[j], host, SDXC_REG_FIFO);
                }else
                        SDC_BUG_ON(1);
            }

        } else {
            SDC_LOGW("illigle data request\n");
            SDC_BUG_ON(1);
            return ;
        }
    }
    HAL_WMB();
}

static smc_idma_des *__mci_alloc_idma_des(struct mmc_host *host, struct mmc_data *data)
{
    smc_idma_des *pdes = host->idma_des;
    uint32_t des_idx = 0;
    uint32_t buff_frag_num = 0;
    uint32_t remain;
    uint32_t i, j;
    uint32_t config;


    /* init IDMA Descriptor, two mode: 1-fixed skip length, 2-chain mode */
    for (i = 0; i < data->sg_len; i++) {
        buff_frag_num = data->sg[i].len >> SDXC_DES_NUM_SHIFT; /* num = len/8192 = len>>13  */
        remain = data->sg[i].len & (SDXC_DES_BUFFER_MAX_LEN - 1);
        if (remain) {
            buff_frag_num++;
        } else {
            remain = SDXC_DES_BUFFER_MAX_LEN;
        }

        for (j = 0; j < buff_frag_num; j++, des_idx++) {
            SDC_Memset((void *)&pdes[des_idx], 0, sizeof(smc_idma_des));
            config = SDXC_IDMAC_DES0_CH | SDXC_IDMAC_DES0_OWN | SDXC_IDMAC_DES0_DIC;
            if (buff_frag_num > 1 && j != buff_frag_num - 1) {
                pdes[des_idx].data_buf1_sz = SDXC_DES_BUFFER_MAX_LEN;
            } else {
                pdes[des_idx].data_buf1_sz = remain;
            }

            pdes[des_idx].buf_addr_ptr1 = SDXC_IDMAC_DES_ADDR((uint32_t)MEMS_VA2PA(HAL_PT_TO_U(data->sg[i].buffer)) + j * SDXC_DES_BUFFER_MAX_LEN);
            if (i == 0 && j == 0) {
                config |= SDXC_IDMAC_DES0_FD;
            }

            if ((i == data->sg_len - 1) && (j == buff_frag_num - 1)) {
                config &= ~SDXC_IDMAC_DES0_DIC;
                config |= SDXC_IDMAC_DES0_LD | SDXC_IDMAC_DES0_ER;
                pdes[des_idx].buf_addr_ptr2 = 0;
            } else {
                pdes[des_idx].buf_addr_ptr2 = SDXC_IDMAC_DES_ADDR((uint32_t)MEMS_VA2PA(HAL_PT_TO_U(&pdes[des_idx + 1])));
            }
            pdes[des_idx].config = config;
            SDC_LOGD("sg %lu, frag %lu, remain %lu, des[%lu](%p): [0]:%lx, [1]:%lx, [2]:%lx, [3]:%lx\n",
                     HAL_PR_SZ_L(i), HAL_PR_SZ_L(j), HAL_PR_SZ_L(remain), HAL_PR_SZ_L(des_idx), &pdes[des_idx],
                     HAL_PR_SZ_L(((uint32_t *)&pdes[des_idx])[0]), HAL_PR_SZ_L(((uint32_t *)&pdes[des_idx])[1]),
                     HAL_PR_SZ_L(((uint32_t *)&pdes[des_idx])[2]), HAL_PR_SZ_L(((uint32_t *)&pdes[des_idx])[3]));
        }
    }

    HAL_FlushDcacheRegion((unsigned long)pdes, HAL_ALIGN(SDXC_MAX_DES_NUM * sizeof(smc_idma_des), OS_CACHE_ALIGN_BYTES));
    HAL_WMB();
    return pdes;
}

static smc_idma_des *__mci_prepare_dma(struct mmc_host *host, struct mmc_data *data)
{
    uint32_t temp;
    smc_idma_des *pdes = NULL;

    /* creat descriptor list, two mode: 1-fixed skip length, 2-chain mode */
    pdes = __mci_alloc_idma_des(host, data);
    if (NULL == pdes) {
        SDC_LOGW("alloc IDMA descriptor failed\n");
        return NULL;
    }

    temp = mci_readl(host, SDXC_REG_GCTRL);
    temp |= SDXC_DMAEnb;
    mci_writel(temp, host, SDXC_REG_GCTRL);
    temp |= (SDXC_DMAReset | SDXC_FIFOReset);
    mci_writel(temp, host, SDXC_REG_GCTRL);
    __mci_check_bit_clear(host, SDXC_REG_GCTRL, (SDXC_DMAReset | SDXC_FIFOReset));
    mci_writel(SDXC_IDMACSoftRST, host, SDXC_REG_DMAC); /* reset IDMAC */
    __mci_check_bit_clear(host, SDXC_REG_DMAC, SDXC_IDMACSoftRST);
    temp = SDXC_IDMACFixBurst | SDXC_IDMACIDMAOn;
    mci_writel(temp, host, SDXC_REG_DMAC);
    /* enable IDMA interrupt, here not use */
    temp = mci_readl(host, SDXC_REG_IDIE);
    temp &= ~(SDXC_IDMACReceiveInt | SDXC_IDMACTransmitInt);
    if (data->flags & MMC_DATA_WRITE) {
        ;//temp |= SDXC_IDMACTransmitInt; /* disable dma int for less irqs */
    } else {
        temp |= SDXC_IDMACReceiveInt;
    }
    mci_writel(temp, host, SDXC_REG_IDIE);

    /* write descriptor address to register */
    mci_writel(SDXC_IDMAC_DES_ADDR((uint32_t)MEMS_VA2PA(HAL_PT_TO_U(pdes))), host, SDXC_REG_DLBA);
    /* write water level */
    mci_writel((BURST_SIZE << 28) | (SMC_RX_WLEVEL << 16) | SMC_TX_WLEVEL,
           host, SDXC_REG_FTRGL);

    return pdes;
}

static void __mci_free_idma_des(smc_idma_des *pdes)
{
    pdes->config &= ~SDXC_IDMAC_DES0_OWN;
}

int32_t __mci_wait_access_done(struct mmc_host *host)
{
    int32_t own_set = 0;
    uint32_t time = HAL_Ticks() + HAL_MSecsToTicks(1000) + 1;

    while (!(mci_readl(host, SDXC_REG_GCTRL) & SDXC_MemAccessDone) && (HAL_TimeBefore(HAL_Ticks(), time)));
    if (!(mci_readl(host, SDXC_REG_GCTRL) & SDXC_MemAccessDone)) {
        SDC_LOGE("wait memory access done timeout !!\n");
    }

    return own_set;
}

static int32_t __mci_request_done(struct mmc_host *host)
{
    struct mmc_request *mrq = host->mrq;
    unsigned long iflags;
    uint32_t temp;
    int32_t ret = 0;

    iflags = HAL_EnterCriticalSection();
    if (host->wait != SDC_WAIT_FINALIZE) {
        HAL_ExitCriticalSection(iflags);
        SDC_LOGW("%s nothing finalize, wt %lx\n", __func__, HAL_PR_SZ_L(host->wait));
        return -1;
    }
    host->wait = SDC_WAIT_NONE;
    host->trans_done = 0;
    host->dma_done = 0;
    HAL_ExitCriticalSection(iflags);

    if (host->int_sum & SDXC_IntErrBit) {
        SDC_LOGE("SDC err, cmd %ld, %s%s%s%s%s%s%s%s%s%s\n",
                 HAL_PR_SZ_L(host->smc_cmd & SDXC_CMD_OPCODE),
                 host->int_sum & SDXC_RespErr    ? " RE" : "",
                 host->int_sum & SDXC_RespCRCErr  ? " RCE" : "",
                 host->int_sum & SDXC_DataCRCErr  ? " DCE" : "",
                 host->int_sum & SDXC_RespTimeout ? " RTO" : "",
                 host->int_sum & SDXC_DataTimeout ? " DTO" : "",
                 host->int_sum & SDXC_DataStarve  ? " DS" : "",
                 host->int_sum & SDXC_FIFORunErr  ? " FRE" : "",
                 host->int_sum & SDXC_HardWLocked ? " HL" : "",
                 host->int_sum & SDXC_StartBitErr ? " SBE" : "",
                 host->int_sum & SDXC_EndBitErr   ? " EBE" : "");

                sdc_hex_dump_word((void *)(SDC_GPIO_BASE+0xB0),0xff);
            if (host->sdc_id == 0) {
                sdc_hex_dump_word((void *)SDC_CCM_SDC0_SCLK_CTRL ,0x200);
                sdc_hex_dump_word((void *)SMC0_BASE ,0x200);
            } else if (host->sdc_id == 1) {
                sdc_hex_dump_word((void *)SDC_CCM_SDC1_SCLK_CTRL ,0x200);
                sdc_hex_dump_word((void *)SMC1_BASE ,0x200);
            }
        ret = -1;
        goto out;
    }

    if (mrq->cmd->flags & MMC_RSP_136) {
        mrq->cmd->resp[0] = mci_readl(host, SDXC_REG_RESP3);
        mrq->cmd->resp[1] = mci_readl(host, SDXC_REG_RESP2);
        mrq->cmd->resp[2] = mci_readl(host, SDXC_REG_RESP1);
        mrq->cmd->resp[3] = mci_readl(host, SDXC_REG_RESP0);
    } else
        mrq->cmd->resp[0] = mci_readl(host, SDXC_REG_RESP0);

out:
    if (mrq->data) {
        if (host->dma_hdle) {
            __mci_wait_access_done(host);
            mci_writel(0x337, host, SDXC_REG_IDST); /* clear interrupt flags */
            mci_writel(0, host, SDXC_REG_IDIE); /* disable idma interrupt */
            mci_writel(0, host, SDXC_REG_DMAC); /* idma off */
            temp = mci_readl(host, SDXC_REG_GCTRL);
            mci_writel(temp | SDXC_DMAReset, host, SDXC_REG_GCTRL);
            temp &= ~SDXC_DMAEnb;
            mci_writel(temp, host, SDXC_REG_GCTRL); /* disable IDMA */
            temp |= SDXC_FIFOReset;
            mci_writel(temp, host, SDXC_REG_GCTRL);
            __mci_free_idma_des((void *)host->dma_hdle);
            host->dma_hdle = NULL;
        }
        mci_writel(mci_readl(host, SDXC_REG_GCTRL) | SDXC_FIFOReset,
               host, SDXC_REG_GCTRL);
    }

#ifdef CONFIG_DETECT_CARD
    if (host->param.cd_mode == CARD_DETECT_BY_D3){
        mci_writel((SDXC_CardInsert|SDXC_CardRemove)|host->sdio_irq_mask, host, SDXC_REG_IMASK);
    } else
#endif
    {
        mci_writel(host->sdio_irq_mask, host, SDXC_REG_IMASK);
    }
    if (host->int_sum & (SDXC_RespErr | SDXC_HardWLocked | SDXC_RespTimeout)) {
        SDC_LOGE("sdc %d abnormal status: %s\n", __LINE__,
                 host->int_sum & SDXC_HardWLocked ? "HardWLocked" : "RespErr");
    }

    mci_writel(0xffff, host, SDXC_REG_RINTR);

    SDC_LOGD("SDC done, resp %lx %lx %lx %lx\n", HAL_PR_SZ_L(mrq->cmd->resp[0]),
            HAL_PR_SZ_L(mrq->cmd->resp[1]), HAL_PR_SZ_L(mrq->cmd->resp[2]), HAL_PR_SZ_L(mrq->cmd->resp[3]));

    if (mrq->data && (host->int_sum & SDXC_IntErrBit)) {
        SDC_LOGW("found data error, need to send stop command !!\n");
        __mci_reset(host);
        __mci_program_clk(host);
    }

    host->int_err = 0;
    return ret;
}

#define mci_writel_irq(value, host, reg) \
    ({  uint32_t val;\
        printf("+irq reg add 0x%x write val 0x%x\n", (uint32_t)(host)->reg_base + reg, value);\
        writel((value), (uint32_t)(host)->reg_base + reg);\
        val = readl((uint32_t)(host)->reg_base + reg);\
        printf("%s,%d\n", __FUNCTION__, __LINE__);\
        printf("-irq reg read val 0x%x\n", (unsigned int)val);})


//#ifdef CONFIG_SDIO_IRQ_SUPPORT
__nonxip_text
static void __mci_enable_sdio_irq(struct mmc_host *host, int enable)
{
    uint32_t imask;
    uint32_t flags = HAL_EnterCriticalSection();
    imask = mci_readl(host, SDXC_REG_IMASK);
    if (enable){
//      mci_writel(SDXC_SDIOInt, host, SDXC_REG_RINTR);
        host->sdio_irq_mask =  SDXC_SDIOInt;
        imask |= SDXC_SDIOInt;
    }else{
        host->sdio_irq_mask = 0;
        imask &= ~SDXC_SDIOInt;
    }
    mci_writel(imask, host, SDXC_REG_IMASK);
    HAL_ExitCriticalSection(flags);
}


__nonxip_text
static inline void __mci_signal_sdio_irq(struct mmc_host *host)
{
//  if (!host->card || !host->card->irq_handler) {
    if (!host->card) {
        SDC_IT_LOGE("BUG at __mci_signal_sdio_irq():%d\n", __LINE__);
        return;
    }
#ifdef SD_PERF_TRACE_ON
    host->start_sdio_irq_times_ns = HAL_GetTimeNs();
    host->sdio_irq_count ++;
#endif
    __mci_enable_sdio_irq(host, 0);
    host->sdio_irq_pending = true;
    //if (host.sdio_irq_thread)
        //xTaskResumeFromISR(host->sdio_irq_thread.handle);
    OS_SemaphoreRelease(&host->sdio_irq_signal);

}


void rom_HAL_SDC_Enable_Sdio_Irq(struct mmc_host *host, int enable)
{
    uint32_t flags = 0;

    __mci_enable_sdio_irq(host,enable);

}



//#endif

static void __mci_clk_prepare_enable(struct mmc_host *host)
{
    if (host->sdc_id == 0) {
        SDC0_CCM_BusEnableClock(); /* clock enable */
        SDC0_CCM_BusReleaseRest(); /* reset and gating */
        SDC0_CCM_EnableMClock();
#if SDC1_SUPPORT
    } else if (host->sdc_id == 1) {
        SDC1_CCM_BusEnableClock(); /* clock enable */
        SDC1_CCM_BusReleaseRest(); /* reset and gating */
        SDC1_CCM_EnableMClock();
#endif
    }
}

static void __mci_clk_disable_unprepare(struct mmc_host *host)
{
    if (host->sdc_id == 0) {
        SDC0_CCM_BusDisableClock();
#if SDC1_SUPPORT
    } else if (host->sdc_id == 1) {
        SDC1_CCM_BusDisableClock();
#endif
    }
}

static void __mci_hold_io(struct mmc_host* host)
{
#ifdef __CONFIG_ARCH_APP_CORE
#ifndef NUSE_STANDARD_INTERFACE
    /* disable gpio to avoid power leakage */
    if (host->pin_ref) {
        HAL_BoardIoctl(HAL_BIR_PINMUX_DEINIT, HAL_MKDEV(HAL_DEV_MAJOR_SDC,
                       host->sdc_id), SDCGPIO_BAS);
        host->pin_ref = 0;
    }
#else
    SDC_LOGN("Not implement %s,%d\n", __FUNCTION__, __LINE__);
#endif
#endif
}

static void __mci_restore_io(struct mmc_host* host)
{
#ifdef __CONFIG_ARCH_APP_CORE
#ifndef NUSE_STANDARD_INTERFACE
    if (host->pin_ref == 0) {
        HAL_BoardIoctl(HAL_BIR_PINMUX_INIT, HAL_MKDEV(HAL_DEV_MAJOR_SDC,
                       host->sdc_id), SDCGPIO_BAS);
        host->pin_ref = 1;
    }
#else
    SDC_LOGN("Not implement %s,%d\n", __FUNCTION__, __LINE__);
#endif
#
#endif
}

__nonxip_text
static irqreturn_t __mci_irq_handler(uint32_t sdc_id)
{
    struct mmc_host *host = _mci_host[sdc_id];
    uint32_t sdio_int = 0;
    uint32_t raw_int;
    uint32_t msk_int;
    uint32_t idma_inte;
    uint32_t idma_int;

#if (defined(__CONFIG_SECTION_ATTRIBUTE_NONXIP) && SDC_DEBUG)
    __nonxip_rodata static const char __s_func[] = "__mci_irq_handler";
#endif
    //SDC_IT_LOGD("***%s,%d***\n",__FUNCTION__, __LINE__);
    if (!host) {
        SDC_IT_LOGE_RAW(ROM_ERR_MASK, "%s,%d no host exist!\n", __func__, __LINE__);
        return IRQ_NONE;
    }

    if (!host->present) {
        if (host->sdc_id == 0) {
            SDC0_CCM_BusEnableClock();
#if SDC1_SUPPORT
        } else if (host->sdc_id == 1) {
            SDC1_CCM_BusEnableClock();
#endif
        }
    }

    idma_int = mci_readl(host, SDXC_REG_IDST);
    idma_inte = mci_readl(host, SDXC_REG_IDIE);
    raw_int = mci_readl(host, SDXC_REG_RINTR);
    msk_int = mci_readl(host, SDXC_REG_MISTA);

    if (!msk_int && !idma_int) {
        SDC_IT_LOGE("sdc nop irq: ri:%08lx mi:%08lx ie:%08lx idi:%08lx\n",
                 HAL_PR_SZ_L(raw_int), HAL_PR_SZ_L(msk_int), HAL_PR_SZ_L(idma_inte), HAL_PR_SZ_L(idma_int));
        return IRQ_NONE;
    }

    host->int_sum = raw_int;
    SDC_IT_LOGD("sdc %d ri:%02x(%02x), mi:%x, ie:%x, idi:%x\n", __LINE__,
             (int)raw_int, (int)host->int_sum,
             (int)msk_int, (int)idma_inte, (int)idma_int);

    (void)idma_inte;

#ifdef CONFIG_SDIO_IRQ_SUPPORT
    if (msk_int & SDXC_SDIOInt) {
        sdio_int = 1;
        mci_writel(SDXC_SDIOInt, host, SDXC_REG_RINTR);
        goto sdio_out;
    }
#endif

#ifdef CONFIG_DETECT_CARD
    if (host->param.cd_mode == CARD_DETECT_BY_D3) {
        if (msk_int & SDXC_CardInsert) {
            SDC_IT_LOGN("Card Insert !!\n");
            host->present = 1;
            SDC_IT_ModTimer(&host->cd_timer, 10);
        } else if (msk_int & SDXC_CardRemove) {
            SDC_IT_LOGN("Card Remove !!\n");
            host->present = 0;
            SDC_IT_ModTimer(&host->cd_timer, 10);
        }
    }
#endif

    if (host->wait == SDC_WAIT_NONE && !sdio_int) {
        SDC_IT_LOGE("%s nothing to complete, ri:%08lx, mi:%08lx\n",
                 __s_func, HAL_PR_SZ_L(raw_int), HAL_PR_SZ_L(msk_int));
        goto irq_out;
    }

    if ((raw_int & SDXC_IntErrBit) || (idma_int & SDXC_IDMA_ERR)) {
        host->int_err = raw_int & SDXC_IntErrBit;
        host->wait = SDC_WAIT_FINALIZE;
        SDC_IT_LOGE("%s,%d raw_int:%lx err!\n", __s_func, __LINE__, HAL_PR_SZ_L(raw_int));
        goto irq_out;
    }
    if (raw_int & SDXC_HardWLocked) {
        SDC_IT_LOGE("command hardware lock\n");
    }

    if (idma_int & (SDXC_IDMACTransmitInt|SDXC_IDMACReceiveInt)) {
        host->dma_done = 1;
        mci_writel(idma_int, host, SDXC_REG_IDST);
    }
    if (msk_int & (SDXC_AutoCMDDone|SDXC_DataOver|SDXC_CmdDone|SDXC_VolChgDone))
        host->trans_done = 1;
    if ((host->trans_done && \
        (host->wait == SDC_WAIT_AUTOCMD_DONE || host->wait == SDC_WAIT_DATA_OVER
         || host->wait == SDC_WAIT_CMD_DONE || host->wait == SDC_WAIT_SWITCH1V8))
         || (host->trans_done && host->dma_done && (host->wait & SDC_WAIT_IDMA_DONE))) {
        host->wait = SDC_WAIT_FINALIZE;
    }

irq_out:
    mci_writel(msk_int & (~SDXC_SDIOInt), host, SDXC_REG_RINTR);

    if (host->wait == SDC_WAIT_FINALIZE) {
#ifdef CONFIG_DETECT_CARD
        if (host->param.cd_mode == CARD_DETECT_BY_D3){
            mci_writel(SDXC_CardInsert|SDXC_CardRemove|host->sdio_irq_mask,
                   host, SDXC_REG_IMASK);
        } else
#endif
        {
            mci_writel(host->sdio_irq_mask, host, SDXC_REG_IMASK);
        }

        HAL_WMB();
        if(!OS_IsISRContext()){
            SDC_BUG_ON(1);
            sys_abort();
        }

        SDC_SemPost(&host->lock);
        SDC_IT_LOGD("SDC irq post, trans:%d, dma:%d\n",
                    (int)host->trans_done, (int)host->dma_done);
    }

#ifdef CONFIG_SDIO_IRQ_SUPPORT
sdio_out:
    if (sdio_int)
        __mci_signal_sdio_irq(host);
#endif
    return IRQ_HANDLED;
}
__nonxip_text
 irqreturn_t SDC0_IRQHandler(int id, void *data)
{
    return __mci_irq_handler(SDC0);
}

#if SDC1_SUPPORT
__nonxip_text
 irqreturn_t SDC1_IRQHandler(int id, void *data) //static
{
    return __mci_irq_handler(SDC1);
}
#endif

/* clock config:
 * SYS_CRYSTAL: 26M
 * 400K, SCLK-26M, 26M/(2^3)/(7+1)/2 = 361K
 * SYS_CRYSTAL: 24M
 * 400K, SCLK-24M, 24M/(2^2)/(7+1)/2 = 375K
 *
 * 25M, SCLK-192M, 192M/(2^0)/(3+1)/2 = 24M
 * 50M, SCLK-192M, 192M/(2^0)/(1+1)/2 = 48M
 * 64M, SCLK-192M, 192M/(2^0)/(1+1)/2 = 48M
 */
#define DEFINE_SYS_CRYSTAL  HAL_GetHFClock()
#define DEFINE_SYS_DEVCLK   HAL_GetDevClock()

static int32_t __mci_update_clock(struct mmc_host *host, uint32_t cclk)
{
    uint32_t sclk;
    uint32_t div;
    uint32_t rval;
    uint32_t src = 0;
    uint32_t m, n;

    if (cclk > DEFINE_SYS_CRYSTAL/2) {
#ifdef NUSE_STANDARD_INTERFACE
        src = 1;
#else
        src = CCM_AHB_PERIPH_CLK_SRC_DEVCLK;
#endif
        sclk = DEFINE_SYS_DEVCLK;
    } else {
#ifdef NUSE_STANDARD_INTERFACE
        src = 0;
#else
        src = CCM_AHB_PERIPH_CLK_SRC_HFCLK;
#endif
        sclk = DEFINE_SYS_CRYSTAL;
    }
    cclk = cclk * 2; /* 2x MODE clock configure */
    div = (2 * sclk + cclk) / (2 * cclk);
    div = div == 0 ? 1 : div;
    if (div > 128) {
        n = 3;
        m = 16;
        SDC_LOGE("source clk is too high!\n");
    } else if (div > 64) {
        n = 3;
        m = div >> 3;
    } else if (div > 32) {
        n = 2;
        m = div >> 2;
    } else if (div > 16) {
        n = 1;
        m = div >> 1;
    } else {
        n = 0;
        m = div;
    }
     m = m - 1;
#ifdef NUSE_STANDARD_INTERFACE
/*
    if (src) {
        rval |= (2U << 20) | (1 << 8);
        SDC_LOGN("%s,%d check spec. bit20, 8!!\n", __func__, __LINE__);
    }
*/

    if (host->sdc_id == 0) {
        rval = readl(SDC_CCM_SDC0_SCLK_CTRL);
        rval &= ~(1U<<31);
        writel(rval,SDC_CCM_SDC0_SCLK_CTRL);
        HAL_WMB();
        rval = (src << 24) | (n << 8) | (m);

        writel(rval,SDC_CCM_SDC0_SCLK_CTRL);
        HAL_WMB();
        rval = readl(SDC_CCM_SDC0_SCLK_CTRL);
        rval |= (1U<<31);
        writel(rval,SDC_CCM_SDC0_SCLK_CTRL);
        HAL_WMB();

        SDC_LOGN("SDC clock=%ld kHz,src:%x, n:%d, m:%d\n",
            HAL_PR_SZ_L((src ? DEFINE_SYS_DEVCLK:DEFINE_SYS_CRYSTAL)/(1<<n)/(m+1)/2),
            (int)src, (int)n, (int)m);
#if SDC1_SUPPORT
        } else if (host->sdc_id == 1) {
            rval = readl(SDC_CCM_SDC1_SCLK_CTRL);
            rval &= ~(1U<<31);
            writel(rval,SDC_CCM_SDC1_SCLK_CTRL);

            HAL_WMB();
            rval = (src << 24) | (n << 8) | (m);
            writel(rval,SDC_CCM_SDC1_SCLK_CTRL);

            HAL_WMB();
            rval = readl(SDC_CCM_SDC1_SCLK_CTRL);
            rval |= (1U<<31);
            writel(rval,SDC_CCM_SDC1_SCLK_CTRL);
            HAL_WMB();
            SDC_LOGN("SDC clock=%ld kHz,src:%x, n:%d, m:%d\n",
                HAL_PR_SZ_L((src?DEFINE_SYS_DEVCLK:DEFINE_SYS_CRYSTAL)/(1<<n)/(m+1)/2),
                (int)src, (int)n, (int)m);
#endif
    }

#else
    if (host->sdc_id == 0) {
        SDC0_DisableMClock();
        SDC0_SetMClock(src, n << CCM_PERIPH_CLK_DIV_N_SHIFT, m << CCM_PERIPH_CLK_DIV_M_SHIFT);
        SDC0_CCM_EnableMClock();
#if SDC1_SUPPORT
    } else if (host->sdc_id == 1) {
        SDC1_DisableMClock();
        SDC1_SetMClock(src, n << CCM_PERIPH_CLK_DIV_N_SHIFT, m << CCM_PERIPH_CLK_DIV_M_SHIFT);
        SDC1_CCM_EnableMClock();
#endif
    }
    SDC_LOGN("SDC source:%u MHz clock=%u kHz, src:%x, n:%d, m:%d\n", sclk/1000000,
         sclk/(1<<n)/(m+1)/2000, (int)src, (int)n, (int)m);
#endif

    /* clear internal divider */
    rval = mci_readl(host, SDXC_REG_CLKCR) & (~0xff);
    mci_writel(rval, host, SDXC_REG_CLKCR);
    sdc_hex_dump_word((void *)SDC_CCM_BASE  ,0x900);

    return cclk;
}

int32_t rom_HAL_SDC_Update_Clk(struct mmc_host *host, uint32_t clk)
{
    uint32_t rval;

    if (!host || clk < 200000) { /* 200K */
        SDC_LOGE_RAW(ROM_ERR_MASK, "%s,%d err", __func__, __LINE__);
        return -1;
    }

    /* Disable Clock */
    rval = mci_readl(host, SDXC_REG_CLKCR) & (~SDXC_CardClkOn) & (~SDXC_LowPowerOn);
    mci_writel(rval, host, SDXC_REG_CLKCR);
    if (__mci_program_clk(host)) {
        SDC_LOGE("Clock Program Failed 0!!\n");
        return -1;
    }

    __mci_update_clock(host, clk);

    /* Re-enable Clock */
    rval = mci_readl(host, SDXC_REG_CLKCR) | (SDXC_CardClkOn);// | SDXC_LowPowerOn;
    mci_writel(rval, host, SDXC_REG_CLKCR);
    if (__mci_program_clk(host)) {
        SDC_LOGE("Clock Program Failed 1!!\n");
        return -1;
    }

    host->clk = clk;

    return 0;
}

static int32_t __mci_update_clk(struct mmc_host *host)
{
    uint32_t rval;
    int32_t ret = 0;
    uint32_t time = HAL_Ticks() + HAL_MSecsToTicks(1000) + 1;

    mci_writel(mci_readl(host, SDXC_REG_CLKCR) | SDXC_Mask_Data0,\
               host, SDXC_REG_CLKCR);

    rval = SDXC_Start|SDXC_UPCLKOnly|SDXC_WaitPreOver;
#ifdef CONFIG_SDC_SUPPORT_1V8
    if (host->voltage_switching)
        rval |= SDXC_VolSwitch;
#endif
    mci_writel(rval, host, SDXC_REG_CMDR);

    do {
        rval = mci_readl(host, SDXC_REG_CMDR);
    } while ((rval & SDXC_Start) && HAL_TimeBefore(HAL_Ticks(), time));

    if (mci_readl(host, SDXC_REG_CMDR) & SDXC_Start) {
        SDC_LOGE("sdc update clock timeout, fatal error!!!\n");
        __mci_force_dump_host_info(host);
        ret = -1;
    }

    if (!ret)
        SDC_LOGD("sdc update clock ok\n");

    /* clear command done flag */
    rval = mci_readl(host, SDXC_REG_RINTR);
    mci_writel(rval, host, SDXC_REG_RINTR);

    mci_writel(mci_readl(host, SDXC_REG_CLKCR) & ~SDXC_Mask_Data0,\
               host, SDXC_REG_CLKCR);

    return ret;
}

int32_t rom_HAL_SDC_Clk_PWR_Opt(struct mmc_host *host, uint32_t oclk_en, uint32_t pwr_save)
{
    uint32_t rval;

    if (!host->power_on)
        return 0;

    rval = mci_readl(host, SDXC_REG_CLKCR);

    rval &= ~(SDXC_CardClkOn | SDXC_LowPowerOn);
    if (oclk_en)
        rval |= SDXC_CardClkOn;
    if (pwr_save)
        rval |= SDXC_LowPowerOn;
    mci_writel(rval, host, SDXC_REG_CLKCR);

    __mci_update_clk(host);

    return 0;
}

static void __mci_debounce_onoff(struct mmc_host *host, uint32_t onoff)
{
    uint32_t rval = mci_readl(host, SDXC_REG_GCTRL);

    rval &= ~SDXC_DebounceEnb;
    if (onoff)
        rval |= SDXC_DebounceEnb;
    mci_writel(rval, host, SDXC_REG_GCTRL);
    SDC_LOGD("%s,%d,%ld\n",__FUNCTION__,__LINE__, HAL_PR_SZ_L(onoff));
}

uint32_t HAL_SDC_Is_Busy(struct mmc_host *host)
{
    return mci_readl(host, SDXC_REG_STAS) & SDXC_CardBusy;
}

static int32_t __mci_check_busy_over(struct mmc_host *host)
{
    uint32_t i;
    for(i = 0; i< SDC_BUSY_WAIT_LOOP; i++){
        if(!(mci_readl(host, SDXC_REG_STAS) & SDXC_CardBusy)){
            return 0;
        }
        if(i>(SDC_BUSY_WAIT_LOOP/8)) {
            mmc_mdelay(10);
            if(i%8)
                SDC_LOGW("Waiting reg %x bitmap %x clear v %x，i %x\n",\
                        HAL_PR_SZ(HAL_PT_TO_U(host->reg_base)) + SDXC_REG_STAS,\
                         (unsigned int)SDXC_CardBusy,\
                         (unsigned int)mci_readl(host, SDXC_CardBusy),\
                         (unsigned int)i);
        }
        SDC_LOGD("Waiting reg %x bitmap %x clear v %x，i %x\n",\
                         HAL_PR_SZ(HAL_PT_TO_U(host->reg_base)) + SDXC_REG_STAS,\
                         (unsigned int)SDXC_CardBusy,\
                         (unsigned int)mci_readl(host, SDXC_CardBusy),\
                         (unsigned int)i);
    }
    SDC_LOGE("Wait busy timeout %x，%x\n",
            (unsigned int)mci_readl(host, SDXC_REG_STAS), (unsigned int)i);
    return -1;
}

int32_t __mci_check_bit_clear(struct mmc_host *host, uint32_t reg_offset, uint32_t bit_map)
{
    uint32_t i;
    for(i = 0; i< SDC_BUSY_WAIT_LOOP; i++){
        if(!(mci_readl(host, reg_offset) & bit_map)){
            SDC_LOGD("Wait reg %p bitmap %x clear v %lx，i %x ok\n",\
                     (host->reg_base) + reg_offset,\
                     (unsigned int)bit_map,\
                     HAL_PR_SZ_L(mci_readl(host, reg_offset)),\
                     (unsigned int)i);
            return 0;
        }
        if(i>(SDC_BUSY_WAIT_LOOP/8)) {
            mmc_mdelay(10);
            if(i%8)
                SDC_LOGW("Waiting reg %p bitmap %x clear v %lx，i %x\n",\
                         (host->reg_base) + reg_offset,\
                         (unsigned int)bit_map,\
                         HAL_PR_SZ_L(mci_readl(host, reg_offset)),\
                         (unsigned int)i);
        }
    }
    SDC_LOGE("Wait reg %p bitmap %x clear timeout v %lx，i %x\n",\
             (host->reg_base) + reg_offset,\
             (unsigned int) bit_map,\
             HAL_PR_SZ_L(mci_readl(host, reg_offset)),\
             (unsigned int)i);
    return -1;
}


void HAL_SDC_Set_BusWidth(struct mmc_host *host, uint32_t width)
{
    if (!host) {
        SDC_LOGE_RAW(ROM_ERR_MASK, "%s,%d err", __func__, __LINE__);
        return ;
    }

    switch (width) {
    case MMC_BUS_WIDTH_1:
        mci_writel(SDXC_WIDTH1, host, SDXC_REG_WIDTH);
        break;
    case MMC_BUS_WIDTH_4:
        mci_writel(SDXC_WIDTH4, host, SDXC_REG_WIDTH);
        break;
#ifdef CONFIG_USE_MMC
    case MMC_BUS_WIDTH_8:
        mci_writel(SDXC_WIDTH8, host, SDXC_REG_WIDTH);
        break;
#endif
    default:
        SDC_BUG_ON(1);
        return ;
    }

    host->buswidth = width;
}

static void __mci_send_cmd(struct mmc_host *host, struct mmc_command *cmd)
{
    uint32_t imask = SDXC_IntErrBit;
    uint32_t cmd_val = SDXC_Start | (cmd->opcode & 0x3f);
    unsigned long iflags;
    uint32_t wait = SDC_WAIT_CMD_DONE;
    struct mmc_data *data = cmd->data;

    if (cmd->opcode == MMC_GO_IDLE_STATE) {
        cmd_val |= SDXC_SendInitSeq;
        imask |= SDXC_CmdDone;
    }

#ifdef CONFIG_SDC_SUPPORT_1V8
    if (cmd->opcode == SD_SWITCH_VOLTAGE) {
        cmd_val |= SDXC_VolSwitch;
        imask |= SDXC_VolChgDone;
        host->voltage_switching = 1;
        wait = SDC_WAIT_SWITCH1V8;
        /* switch controller to high power mode */
        HAL_SDC_Clk_PWR_Opt(host, 1, 0);
    }
#endif

    if (cmd->flags & MMC_RSP_PRESENT) { /* with response */
        cmd_val |= SDXC_RspExp;
        if (cmd->flags & MMC_RSP_136) /* long response */
            cmd_val |= SDXC_LongRsp;
        if (cmd->flags & MMC_RSP_CRC)
            cmd_val |= SDXC_CheckRspCRC;

        if (mmc_cmd_type(cmd) == MMC_CMD_ADTC) { /* with data */
            if (!data) {
                SDC_LOGE("%s,%d no data exist!\n", __func__, __LINE__);
                return ;
            }
            cmd_val |= SDXC_DataExp | SDXC_WaitPreOver;
            wait = SDC_WAIT_DATA_OVER;
            if (data->flags & MMC_DATA_STREAM) { /* sequence mode */
                imask |= SDXC_AutoCMDDone;
                cmd_val |= SDXC_Seqmod | SDXC_SendAutoStop;
                wait = SDC_WAIT_AUTOCMD_DONE;
            }
            if (cmd->stop) {
                imask |= SDXC_AutoCMDDone;
                cmd_val |= SDXC_SendAutoStop;
                wait = SDC_WAIT_AUTOCMD_DONE;
            } else
                imask |= SDXC_DataOver;

            if (data->flags & MMC_DATA_WRITE) {
                cmd_val |= SDXC_Write;
            } else if (host->dma_hdle) {
                wait |= SDC_WAIT_IDMA_DONE;
            }
            SDC_LOGD("blk_size:%lu, sg len:%lu\n",HAL_PR_SZ_L(data->blksz), HAL_PR_SZ_L(data->sg->len));
        } else
            imask |= SDXC_CmdDone;
    } else
        imask |= SDXC_CmdDone;

    SDC_LOGD("sdc cmd:%ld(%lx), arg:%lx ie:%lx wt:%lx len:%lu\n",
             HAL_PR_SZ_L(cmd_val & SDXC_CMD_OPCODE), HAL_PR_SZ_L(cmd_val), HAL_PR_SZ_L(cmd->arg), HAL_PR_SZ_L(imask), HAL_PR_SZ_L(wait),
             HAL_PR_SZ_L(cmd->data ? cmd->data->blksz * cmd->data->blocks : 0));

    iflags = HAL_EnterCriticalSection();
    host->smc_cmd = cmd_val;
    host->wait = wait;

    mci_writel(imask | host->sdio_irq_mask, host, SDXC_REG_IMASK);

    if (cmd_val & SDXC_SendAutoStop)
        mci_writel(0, host, SDXC_REG_A12A);
    else
        mci_writel(0xffff, host, SDXC_REG_A12A);

    mci_writel(cmd->arg, host, SDXC_REG_CARG);
    HAL_WMB();
    mci_writel(cmd_val, host, SDXC_REG_CMDR);


    HAL_ExitCriticalSection(iflags);
    if (data && NULL == host->dma_hdle) {
        __mci_trans_by_ahb(host, data);
    }
}

#ifdef SD_PERF_TRACE_ON
static void __mci_start_data_time_stats(struct mmc_host *host, struct mmc_request *mrq)
{
    if((mrq->data) && (mmc_cmd_type(mrq->cmd) == MMC_CMD_ADTC)){
        if( (mrq->data->blksz * mrq->data->blocks) > 4 )
            host->start_times_us = HAL_GetTimeUs();
    }

}

/*this func can not be called by irq_server_function;
 *because there are using printf(only printf support u64).
 *if you want to use it in irq_server_funciton,printf to printk
 * */
static void __mci_end_data_time_stats(struct mmc_host *host, struct mmc_request *mrq)
{
    if((mrq->data) && (mmc_cmd_type(mrq->cmd) == MMC_CMD_ADTC) \
       && ((mrq->data->blksz * mrq->data->blocks) > 4)){
        uint64_t time_use_us =  (uint64_t)HAL_GetTimeUs() - host->start_times_us;
        if((mrq->data->flags) & MMC_DATA_WRITE ) {
            host->wbytes += mrq->data->blksz * mrq->data->blocks ;
            host->wtimes_us += time_use_us;
            host->wcount ++;
            if(host->wcount && !(host->wcount % SD_PERF_TRACE_COUNT)) {
                printf("Stats Total write:bytes %lld, time us %lu, count %lld, %lld KB\n",\
                         host->wbytes, host->wtimes_us, host->wcount,\
                         __mci_get_rate(host->wbytes, host->wtimes_us)/1024);
                //host->wtimes_us = 0;
                //host->wbytes = 0;
                //host->wcount = 0;
            }
        } else if((mrq->data->flags) & MMC_DATA_READ) {
            host->rbytes += mrq->data->blksz * mrq->data->blocks;
            host->rtimes_us += time_use_us;
            host->rcount++;
            if( host->rcount &&!(host->rcount % SD_PERF_TRACE_COUNT)) {
                printf("Stats Total read: byte %lld, time us %lu, count %lld, %lldKB\n",\
                     host->rbytes, host->rtimes_us, host->rcount,\
                     __mci_get_rate(host->rbytes, host->rtimes_us)/1024);
                //host->rtimes_us = 0;
                //host->rbytes = 0;
                //host->rcount = 0;
            }
        }

    }
}
#endif

int32_t do_rom_HAL_SDC_Request(struct mmc_host *host, struct mmc_request *mrq)
{
    int32_t ret = 0;
    struct mmc_command *cmd = mrq->cmd;
    struct mmc_data *data = mrq->data;
#ifdef CONFIG_SDC_DMA_USED
    uint32_t sdc_use_dma = host->dma_use;
#else
    uint32_t sdc_use_dma = 0;
#endif

    if (!host->present) {
        SDC_LOGW("sdc:%p no medium present\n", host);
        SDC_SemRest((&host->lock));
        return -1;
    }

#ifdef CONFIG_SD_PM
    if (host->suspend) {
        SDC_LOGE("sdc:%p has suspended!\n", host);
        return -1;
    }
#endif
#ifdef SD_PERF_TRACE_ON
    __mci_start_data_time_stats(host, mrq);
#endif
    __mci_check_busy_over(host);
    __mci_check_bit_clear(host, SDXC_REG_GCTRL, SDXC_HWReset);

    SDC_MutexLock(&host->thread_lock, SDC_THREAD_TIMEOUT);

    /* disable debounce */
    __mci_debounce_onoff(host, 0);

    host->mrq = mrq;

    if (data) {
        uint32_t i;
        uint32_t byte_cnt = 0;
        struct scatterlist *sg = data->sg;
        uint32_t sg_len = data->sg_len;
        unsigned long addr = 0;
        uint32_t len = 0;

        for (i = 0; i < sg_len; i++) {
            addr = HAL_PT_TO_U(sg[i].buffer);
            len = sg[i].len;
            byte_cnt += sg[i].len;
#ifdef CONFIG_SDC_DMA_USED
            if ((addr & 0x03)) {
                sdc_use_dma = 0;
                SDC_LOGW("unalign addr %lx, len %ld wr %lx\n", HAL_PR_SZ_L(addr), HAL_PR_SZ_L(len), HAL_PR_SZ_L(data->flags & MMC_DATA_WRITE));
                continue;
            }

            if((addr & (OS_CACHE_ALIGN_BYTES - 1))\
              || (len & (OS_CACHE_ALIGN_BYTES - 1))) {
                SDC_LOGD("unalign addr %lx, len %ld wr %lx\n", HAL_PR_SZ_L(addr), HAL_PR_SZ_L(len), HAL_PR_SZ_L(data->flags & MMC_DATA_WRITE));
            }

            HAL_FlushDcacheRegion((unsigned long)sg[i].buffer, HAL_ALIGN(sg[i].len, OS_CACHE_ALIGN_BYTES));
#endif
        }
#ifdef CONFIG_SDC_DMA_USED
        if (byte_cnt <= SDC_MAX_CPU_TRANS_LEN) {
            sdc_use_dma = 0;
        }
#endif

        if (byte_cnt != (data->blksz * data->blocks)) {
            SDC_LOGE("sg data len %ld not equel data's len %ld\n", HAL_PR_SZ_L(byte_cnt), HAL_PR_SZ_L(data->blksz * data->blocks));
        }

        mci_writel(data->blksz, host, SDXC_REG_BLKSZ);
        mci_writel(byte_cnt, host, SDXC_REG_BCNTR);

        if (sdc_use_dma && byte_cnt > SDC_MAX_CPU_TRANS_LEN) { /* transfer by idma */
            __mci_sel_access_mode(host, SDXC_ACCESS_BY_DMA);
            host->dma_hdle = __mci_prepare_dma(host, data);
            if (NULL == host->dma_hdle) {
                SDC_LOGW("SDC prepare DMA failed\n");
                __mci_sel_access_mode(host, SDXC_ACCESS_BY_AHB);
            }
        } else {
            /* switch data bus to ahb */
            __mci_sel_access_mode(host, SDXC_ACCESS_BY_AHB);
        }
    }

    __mci_send_cmd(host, cmd);

#if defined(CONFIG_SOC_SUN20IW1) && defined(CONFIG_OS_MELIS)
    struct timespec64 time0 ={0}, time1={0};

    do_gettimeofday(&time0);
    ret = SDC_SemPend(&host->lock, SDC_DMA_TIMEOUT);
    do_gettimeofday(&time1);

    if ((ret != HAL_OK && host->present) && \
        (((time1.tv_sec*1000+time1.tv_nsec/1000000) - (time0.tv_sec*1000+time0.tv_nsec/1000000)) < SDC_DMA_TIMEOUT))
    {
        //增加这里的原因是防止读写sdmmc的task被esKRNL_TimeDlyResume,出现这种情况，会导致信号量提前退出
        //如果是正常的timeout则不会跑到这里面
        SDC_LOGE("===SDC_SemPend abnormal===\n");
        ret = SDC_SemPend(&host->lock, SDC_DMA_TIMEOUT);
    }
#else
    ret = SDC_SemPend(&host->lock, SDC_DMA_TIMEOUT);
#endif

    if (ret != HAL_OK && host->present){
        uint32_t sg_len = data->sg_len;
        uint32_t i;
        uint32_t rval = 0;

        SDC_LOGE("sdc cmd:%ld, wait command done timeout !!\n",
                 HAL_PR_SZ_L(host->smc_cmd & SDXC_CMD_OPCODE));
        host->debug_mask |= ROM_DUMP_MASK | ROM_ERR_MASK;
#if 1
        __mci_force_dump_host_info(host);
        if (data) {
            SDC_LOGE("dump data blksz %ld,blocks %ld,flags %lx\n", HAL_PR_SZ_L(data->blksz), HAL_PR_SZ_L(data->blocks), HAL_PR_SZ_L(data->flags));
        }
#endif
        SDC_LOGE("%s,%d\n",__FUNCTION__,__LINE__);
        for (i = 0; i < sg_len; i++) {
            struct scatterlist *sg = data->sg;
            uint32_t *buf_temp = (uint32_t *)sg[i].buffer;
#ifdef CONFIG_SDC_DMA_USED
            if (HAL_PT_TO_U(sg[i].buffer) & 0x03) {
                sdc_use_dma = 0;
                SDC_LOGW("%s,%d\n",__FUNCTION__,__LINE__);
                break;
            }
            SDC_LOGE("%s,%d\n",__FUNCTION__,__LINE__);
            HAL_InvalidDcacheRegion((unsigned long )(sg[i].buffer), HAL_ALIGN(sg[i].len, OS_CACHE_ALIGN_BYTES));
            SDC_LOGE("%s,%d\n",__FUNCTION__,__LINE__);
            SDC_LOGE("buf addr %lx buffer0 %x buffer1 %x\n", HAL_PR_SZ_L(sg[i].buffer), (unsigned int)buf_temp[0],(unsigned int) buf_temp[1]);
#endif
        }

        SDC_LOGE("%s,%d\n",__FUNCTION__,__LINE__);
        mci_writel(0xdeb, host, SDXC_REG_TMOUT);
        SDC_LOGE("*force wr smc timeout reg %x*\n",(unsigned int)mci_readl(host, SDXC_REG_TMOUT));
#if 1
        SDC_LOGE("*force dump sram*\n");
        rval = readl(0x03000000+0x0048);
        rval |= 1 << 4;
        writel(rval, 0x03000000+0x0048);
        sdc_hex_dump_word((void *)SMC1_BASE ,0x100);
#endif
        SDC_LOGE("%s,%d\n",__FUNCTION__,__LINE__);

        SDC_BUG_ON(1);
        sys_abort();
        /*sdc_hex_dump_word((void *)0x4002000 ,0x200);*/
        host->debug_mask &= ~ROM_DUMP_MASK;
        goto out;
    }

    ret = __mci_request_done(host);
    if (ret) {
        goto out;
    }


out:
    /* enable debounce */
    __mci_debounce_onoff(host, 1);

    if(data && (data->flags & MMC_DATA_READ )){
        uint32_t i;
        uint32_t byte_cnt = 0;
        struct scatterlist *sg = data->sg;
        uint32_t sg_len = data->sg_len;
        for (i = 0; i < sg_len; i++) {
            byte_cnt += sg[i].len;
#ifdef CONFIG_SDC_DMA_USED
            if (HAL_PT_TO_U(sg[i].buffer) & 0x03) {
                sdc_use_dma = 0;
                break;
            }
            HAL_InvalidDcacheRegion((unsigned long)(sg[i].buffer), HAL_ALIGN(sg[i].len, OS_CACHE_ALIGN_BYTES));
#endif
        }
    }



    SDC_MutexUnlock(&host->thread_lock);

#ifdef SD_PERF_TRACE_ON
    __mci_end_data_time_stats(host, mrq);
#endif
    return ret;
}

int32_t rom_HAL_SDC_Request(struct mmc_host *host, struct mmc_request *mrq)
{
    int32_t ret = 0;
#ifdef CONFIG_SDC_DMA_USED
    uint32_t sdc_use_dma_buf = 0;
    struct scatterlist sg_dma = {0};
    struct scatterlist *sg = NULL;
    uint32_t sg_len = 0;
    struct mmc_data *data;
    uint32_t i = 0;
    uint32_t byte_cnt = 0;
    unsigned long addr = 0;
    uint32_t len = 0;


    if (mrq->data) {
        data =  mrq->data;
        sg_len = data->sg_len;
        sg = data->sg;

        for (i = 0; i < sg_len; i++) {
            addr = HAL_PT_TO_U(sg[i].buffer);
            len = sg[i].len;
            byte_cnt += sg[i].len;
            if ((addr & 0x03)\
                || (addr & (OS_CACHE_ALIGN_BYTES - 1))
                || (len & (OS_CACHE_ALIGN_BYTES - 1))) {
                sdc_use_dma_buf = 1;
                SDC_LOGD("try to use dma debounce buff, addr %lx, len %ld\n", \
                         HAL_PR_SZ_L(addr), HAL_PR_SZ_L(byte_cnt));
            }
        }

        if (sdc_use_dma_buf) {
            if (byte_cnt > SDC_ALIGN_DMA_BUF_SIZE) {
                SDC_LOGE("byte count %ld over dma debounce buf size %d\n", \
                         HAL_PR_SZ_L(byte_cnt), SDC_ALIGN_DMA_BUF_SIZE);
                return -1;
            } else if (byte_cnt < SDC_MAX_CPU_TRANS_LEN) {
                    SDC_LOGD("byte cnt %ld is too small not use dma align buf\n", \
                         HAL_PR_SZ_L(byte_cnt));
                sdc_use_dma_buf = 0;
            } else {
                uint32_t total_len = 0;
                if (data->flags & MMC_DATA_WRITE) {
                    for (i = 0; i < sg_len; i++) {
                        addr = HAL_PT_TO_U(sg[i].buffer);
                        len = sg[i].len;
                        HAL_Memcpy((char *)(host->align_dma_buf + total_len), (char *)addr, len);
                        total_len += len;
                    }
                }
                sg_dma.buffer = host->align_dma_buf;
                sg_dma.len = byte_cnt;
                data->sg = &sg_dma;
                data->sg_len = 1;
                SDC_LOGD("use dma debounce buff addr %lx, len %d, align_dma_buf %lx\n", \
                         HAL_PT_TO_U(sg[0].buffer),\
                         (unsigned int)byte_cnt,\
                         HAL_PT_TO_U(host->align_dma_buf));

            }
        }
    }
#endif
    ret = do_rom_HAL_SDC_Request(host, mrq);

#ifdef CONFIG_SDC_DMA_USED
    if(!ret && data && sdc_use_dma_buf) {
        if (data->flags & MMC_DATA_READ) {
            uint32_t total_len = 0;
            for (i = 0; i < sg_len; i++) {
                addr = HAL_PT_TO_U(sg[i].buffer);
                len = sg[i].len;
                HAL_Memcpy((char *)addr, (char *)(host->align_dma_buf + total_len), len);
                total_len += len;
            }
            SDC_LOGD("copy back to dst buffer%ld\n", HAL_PR_SZ_L(byte_cnt));
        }
        data->sg = sg;
        data->sg_len = sg_len;
    }

#endif
    return ret;
}


#ifdef CONFIG_SDC_EXCLUSIVE_HOST
/**
 *  HAL_SDC_Claim_Host - exclusively claim a host
 *  @host: mmc host to claim
 *
 *  Claim a host for a set of operations.
 */
int32_t HAL_SDC_Claim_Host(struct mmc_host *host)
{
    return (SDC_SemPend(&host->exclusive_lock, OS_WAIT_FOREVER) == OS_OK ? 0 : -1);
}

/**
 *  HAL_SDC_Release_Host - release a host
 *  @host: mmc host to release
 *
 *  Release a MMC host, allowing others to claim the host
 *  for their operations.
 */
void HAL_SDC_Release_Host(struct mmc_host *host)
{
    SDC_SemPost(&host->exclusive_lock);
}
#endif

#ifdef CONFIG_SDC_READONLY_USED
int32_t HAL_SDC_Get_ReadOnly(struct mmc_host *host)
{
    uint32_t wp_val;
    GPIO_PinMuxParam *ro_gpio = &host->ro_gpio;

    wp_val = (GPIO_PIN_HIGH == HAL_GPIO_ReadPin(ro_gpio->port, ro_gpio->pin)) ? 1 : 0;
    SDC_LOGN("sdc fetch card wp pin status: %u\n", (unsigned int)wp_val);

    if (!wp_val) {
        host->read_only = 0;
        return 0;
    } else {
        SDC_LOGN("Card is write-protected\n");
        host->read_only = 1;
        return 1;
    }

    return 0;
}
#endif

#ifdef CONFIG_DETECT_CARD

static  irqreturn_t __mci_cd_irq(int unuse, void *arg);
static void __mci_enable_cd_pin_irq(struct mmc_host *host)
{
    //SDC_LOGD("Not implement %s,%d\n", __FUNCTION__,__LINE__);
    //SDC_ENABLE_IRQ(host->cd_irq);
    hal_gpio_irq_enable(host->cd_irq);
}

static void __mci_disable_cd_pin_irq(struct mmc_host *host)
{
//  HAL_GPIO_DisableIRQ(host->cd_port, host->cd_pin);
//  SDC_LOGE("Not implement %s,%d\n", __FUNCTION__,__LINE__);

    //SDC_DISABLE_IRQ(host->cd_irq);
    hal_gpio_irq_disable(host->cd_irq);
}

static void __mci_voltage_stable_det(void *arg)
{
    struct mmc_host *host = (struct mmc_host *)arg;

    if (!host->present || host->wait_voltage_stable || !host->cd_delay) {
        host->wait_voltage_stable = 0;
        __mci_enable_cd_pin_irq(host);
        host->param.cd_cb(host->present);
    } else {
        SDC_ModTimer(&host->cd_timer, host->cd_delay);
        host->wait_voltage_stable = 1;
    }
}

static void __mci_cd_timer(void *arg)
{
    struct mmc_host *host = (struct mmc_host *)arg;
    uint32_t gpio_val = 0;
    uint32_t present;
    gpio_val = (host->cd_pin_present_val == HAL_GPIO_ReadPin(host->cd_gpio_pin, &gpio_val)) ? 1 : 0;
    //SDC_LOGE("Not implement %s,%d\n", __FUNCTION__,__LINE__);
    if (gpio_val) {
        present = 1;
    } else {
        present = 0;
    }

    SDC_LOGD("cd %lu, host present %lu, cur present %lu\n",
             HAL_PR_SZ_L(gpio_val), HAL_PR_SZ_L(host->present), HAL_PR_SZ_L(present));
    if (host->present ^ present || host->wait_voltage_stable) {
        SDC_LOGD("sdc detect change, present %lu\n", HAL_PR_SZ_L(present));
        host->present = present;
        __mci_voltage_stable_det(host);
    }
    else {
        __mci_enable_cd_pin_irq(host);
    }
    __sdc_init_timeout_flags = 1;
    return ;
}

static void __mci_dat3_det(void *arg)
{
    struct mmc_host *host = (struct mmc_host *)arg;

    SDC_LOGD("***dat3 det***\n");

    __mci_voltage_stable_det(host);
}

static irqreturn_t __mci_cd_irq(int unuse, void *arg)
{
    struct mmc_host *host = (struct mmc_host *)arg;

    SDC_LOGD("***in cd***\n");
    if (!SDC_TimerIsActive(&host->cd_timer) || host->wait_voltage_stable) {
        host->wait_voltage_stable = 0;
        SDC_ModTimer(&host->cd_timer, 10);
        __mci_disable_cd_pin_irq(host);
    }
    return (irqreturn_t)NULL;
}
#endif

int32_t rom_HAL_SDC_PowerOn(struct mmc_host *host)
{
    uint32_t rval;

    if (!host) {
        SDC_LOGE_RAW(ROM_ERR_MASK, "%s,%d err", __func__, __LINE__);
        return -1;
    }

    SDC_LOGD("MMC Driver init host\n");

    __mci_restore_io(host);
    __mci_clk_prepare_enable(host);


    /* delay 1ms ? */
    __mci_update_clock(host, 400000);
    host->clk = 400000;

    /* reset controller*/
    rval = mci_readl(host, SDXC_REG_GCTRL)|SDXC_HWReset|SDXC_INTEnb|
           SDXC_AccessDoneDirect;
    mci_writel(rval, host, SDXC_REG_GCTRL);
    __mci_check_bit_clear(host, SDXC_REG_GCTRL, SDXC_HWReset);
    SDC_LOGD("%s,%d\n",__FUNCTION__,__LINE__);

    mci_writel(0xffffffff, host, SDXC_REG_RINTR);

#ifdef CONFIG_DETECT_CARD
    if (host->param.cd_mode == CARD_DETECT_BY_D3) {
        mci_writel(SDXC_CardInsert|SDXC_CardRemove|host->sdio_irq_mask, host, SDXC_REG_IMASK);
    } else
#endif
    {
        mci_writel(host->sdio_irq_mask, host, SDXC_REG_IMASK);
    }

#define SDMC_DATA_TIMEOUT  0x0ffffffU
#define SDMC_RESP_TIMEOUT  0xffU
    /* Set Data & Response Timeout Value */
    mci_writel((SDMC_DATA_TIMEOUT<<8)|SDMC_RESP_TIMEOUT, host, SDXC_REG_TMOUT);
#undef SDMC_RESP_TIMEOUT
#undef SDMC_DATA_TIMEOUT

    HAL_SDC_Set_BusWidth(host, MMC_BUS_WIDTH_1);

#ifdef SDC_DEBUG
    mci_writel(0xdeb, host, SDXC_REG_DBGC);
    mci_writel(0xceaa0000, host, SDXC_REG_FUNS);
#endif

#ifdef CONFIG_DETECT_CARD
    if (host->param.cd_mode == CARD_DETECT_BY_D3){
        rval |= SDXC_DebounceEnb;
    }
    mci_writel(rval, host, SDXC_REG_GCTRL);
#endif

    if (host->sdc_id == 0) {
        SDC_ENABLE_IRQ(SDC0_IRQn);
    }
#if SDC1_SUPPORT
    else if (host->sdc_id == 1)
        SDC_ENABLE_IRQ(SDC1_IRQn);
#endif

    host->power_on = 1;

    return 0;
}

int32_t rom_HAL_SDC_PowerOff(struct mmc_host *host)
{
    if (!host) {
        SDC_LOGE_RAW(ROM_ERR_MASK, "%s,%d err", __func__, __LINE__);
        return -1;
    }

#ifdef CONFIG_DETECT_CARD
    if (host->param.cd_mode != CARD_DETECT_BY_D3)
#endif
    {
        uint32_t rval;

        if (host->sdc_id == 0)
            SDC_DISABLE_IRQ(SDC0_IRQn);
#if SDC1_SUPPORT
        else if (host->sdc_id == 1)
            SDC_DISABLE_IRQ(SDC1_IRQn);
#endif

        rval = mci_readl(host, SDXC_REG_GCTRL) | SDXC_HWReset;
        mci_writel(rval, host, SDXC_REG_GCTRL);
        __mci_check_bit_clear(host, SDXC_REG_GCTRL, SDXC_HWReset);
        rval = mci_readl(host, SDXC_REG_MISTA);
        mci_writel(rval & (~SDXC_SDIOInt), host, SDXC_REG_RINTR);

        if (host->sdc_id == 0)
            SDC_CLEAR_IRQPINGD(SDC0_IRQn);
#if SDC1_SUPPORT
        else if (host->sdc_id == 1)
            SDC_CLEAR_IRQPINGD(SDC1_IRQn);
#endif

        __mci_clk_disable_unprepare(host);

        __mci_hold_io(host);
        host->power_on = 0;
    }

    return 0;
}

#ifdef CONFIG_SD_PM

static void __mci_regs_save(struct mmc_host *host)
{
    struct __mci_ctrl_regs *bak_regs = &host->regs_back;

    bak_regs->gctrl = mci_readl(host, SDXC_REG_GCTRL);
    bak_regs->clkc = mci_readl(host, SDXC_REG_CLKCR);
    bak_regs->timeout = mci_readl(host, SDXC_REG_TMOUT);
    bak_regs->buswid = mci_readl(host, SDXC_REG_WIDTH);
    bak_regs->waterlvl = mci_readl(host, SDXC_REG_FTRGL);
    bak_regs->funcsel = mci_readl(host, SDXC_REG_FUNS);
    bak_regs->idmacc = mci_readl(host, SDXC_REG_DMAC);
}

static void __mci_regs_restore(struct mmc_host *host)
{
    struct __mci_ctrl_regs* bak_regs = &host->regs_back;

    mci_writel(bak_regs->gctrl, host, SDXC_REG_GCTRL);
    mci_writel(bak_regs->clkc, host, SDXC_REG_CLKCR);
    mci_writel(bak_regs->timeout, host, SDXC_REG_TMOUT);
    mci_writel(bak_regs->buswid, host, SDXC_REG_WIDTH);
    mci_writel(bak_regs->waterlvl, host, SDXC_REG_FTRGL);
    mci_writel(bak_regs->funcsel, host, SDXC_REG_FUNS);
#ifdef SDC_DEBUG
    mci_writel(0xdeb, host, SDXC_REG_DBGC);
    mci_writel(0xceaa0000, host, SDXC_REG_FUNS);
#endif
    mci_writel(bak_regs->idmacc, host, SDXC_REG_DMAC);
}

static int __mci_suspend(struct soc_device *dev, enum suspend_state_t state)
{
    int ret = 0;
    struct mmc_host *host = dev->platform_data;
    uint32_t _timeout = HAL_Ticks() + HAL_MSecsToTicks(SDC_DMA_TIMEOUT) + 1;

    if (host->bus_ops && host->bus_ops->suspend)
        ret = host->bus_ops->suspend(host);
    if (ret) {
        if (host->bus_ops->resume)
            host->bus_ops->resume(host);
        SDC_LOGE("%s bus id:%d faild\n", __func__, host->sdc_id);
        goto err;
    }

    host->suspend = 1;
    while ((host->wait != SDC_WAIT_NONE) && HAL_TimeBefore(HAL_Ticks(), _timeout)) {
    }
    if (HAL_TimeAfterEqual(HAL_Ticks(), _timeout) && (host->wait != SDC_WAIT_NONE)) {
        ret = -1;
        host->suspend = 0;
        if (host->bus_ops && host->bus_ops->resume)
            ret = host->bus_ops->resume(host);
        SDC_LOGE("%s id:%d faild\n", __func__, host->sdc_id);
        goto err;
    }
    __mci_regs_save(host);

    /* gate clock for lower power */
    if (host->sdc_id == 0) {
        SDC0_DisableMClock();
        SDC0_CCM_BusForceReset();
#if SDC1_SUPPORT
    } else if (host->sdc_id == 1) {
        SDC1_DisableMClock();
        SDC1_CCM_BusForceReset();
#endif
    }
    __mci_clk_disable_unprepare(host);

#ifdef CONFIG_DETECT_CARD
    if (host->param.cd_mode == CARD_DETECT_BY_D3) {
        __mci_exit_host(host);

        if (host->sdc_id == 0) {
            SDC0_DisableMClock();
            SDC0_CCM_BusForceReset();
#if SDC1_SUPPORT
        } else if (host->sdc_id == 1) {
            SDC1_DisableMClock();
            SDC1_CCM_BusForceReset();
#endif
        }
        __mci_hold_io(host);

        SDC_LOGD("sdc card_power_off ok\n");

        //__mci_set_vddio(host, SDC_WOLTAGE_OFF);
        //usleep_range(1000, 1500);
        host->power_on = 0;

    }
#endif

    SDC_LOGD("%s id:%d ok\n", __func__, host->sdc_id);

err:
    return ret;
}

static int __mci_resume(struct soc_device *dev, enum suspend_state_t state)
{
    int ret = 0;
    struct mmc_host *host = dev->platform_data;
    uint32_t clk = host->clk;

    __mci_restore_io(host);

    if (host->sdc_id == 0) {
        SDC0_CCM_BusForceReset();
#if SDC1_SUPPORT
    } else if (host->sdc_id == 1) {
        SDC1_CCM_BusForceReset();
#endif
    }
    __mci_clk_disable_unprepare(host);
    mmc_udelay(35);

    /* enable clock for resotre */
    __mci_clk_prepare_enable(host);
    mmc_udelay(50);
    __mci_update_clock(host, clk);
    mmc_udelay(100);

    __mci_regs_restore(host);
#ifdef CONFIG_DETECT_CARD
#else
    mci_writel(SDXC_CardInsert, host, SDXC_REG_RINTR);
#endif
    __mci_update_clk(host);

    /* register IRQ */
    if (host->sdc_id == 0)
        SDC_CONFIG_IRQ(SDC0_IRQn, &SDC0_IRQHandler, NVIC_PERIPH_PRIO_DEFAULT);
#if SDC1_SUPPORT
    else if (host->sdc_id == 1)
        SDC_CONFIG_IRQ(SDC1_IRQn, &SDC1_IRQHandler, NVIC_PERIPH_PRIO_DEFAULT);
#endif
    mmc_udelay(100);

#ifdef CONFIG_DETECT_CARD
    if (host->param.cd_mode == CARD_DETECT_BY_GPIO_IRQ)
        __mci_cd_timer(host);

    if (host->param.cd_mode == CARD_DETECT_BY_D3) {
        uint32_t rval = 0;

        //__mci_set_vddio(host, host->regulator_voltage);
        //usleep_range(1000, 1500);
        host->power_on = 1;

        __mci_restore_io(host);
        __mci_clk_prepare_enable(host);

        mmc_mdelay(1);
        rval = mci_readl(host, SDXC_REG_RINTR);
        SDC_LOGD(">> REG_RINTR=0x%x\n", (unsigned int)rval);
        (void)rval;
    }
#endif

    host->suspend = 0;

    if (host->bus_ops && host->bus_ops->resume)
        ret = host->bus_ops->resume(host);

    SDC_LOGD("%s id:%d ok\n", __func__, host->sdc_id);

    return ret;
}

static const struct soc_device_driver sdc_drv = {
    .name = "sdc",
    .suspend = __mci_suspend,
    .resume = __mci_resume,
};

static struct soc_device sdc_dev[SDC_NUM] = {
    { .name = "sdc0", .driver = &sdc_drv, },
    { .name = "sdc1", .driver = &sdc_drv, }
};

#define SDC_DEV(id) (&sdc_dev[id])

#endif /* CONFIG_SD_PM */

int hal_sdc_init_timeout(void)
{
    return __sdc_init_timeout_flags;
}

/**
 * @brief Initializes the SDC peripheral.
 * @param sdc_id:
 *        @arg sdc_id->SDC ID.
 * @param param:
 *        @arg param->[in] The configuration information.
 * @retval  SDC handler.
 */
struct mmc_host *hal_sdc_init(struct mmc_host *host)
{
    __sdc_init_timeout_flags = 0;

#ifdef __CONFIG_ARCH_APP_CORE
    const HAL_SDCGPIOCfg *sd_gpio_cfg = NULL;
    const HAL_SDCGPIOCfg sd_gpio_cfg_entry;
    sd_gpio_cfg = &sd_gpio_cfg_entry;
#endif
    int ret = 0;

    if (host->State != SDC_STATE_RESET) {
        SDC_LOGW("%s----%d reinit sdc!\n", __func__,__LINE__);
        return NULL;
    }

    if (host->sdc_id == 0) {
        host->reg_base = (volatile void *)SMC0_BASE;
#if SDC1_SUPPORT
    } else if (host->sdc_id == 1) {
        host->reg_base = (volatile void *)SMC1_BASE;
#endif
    } else {
        SDC_LOGW("%s unsupport sdc id:%d!\n", __func__, host->sdc_id);
        return NULL;
    }

#ifdef __CONFIG_PLATFORM_FPGA
    host->caps = MMC_CAP_MMC_HIGHSPEED  | MMC_CAP_WAIT_WHILE_BUSY |
             MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25 | MMC_CAP_UHS_SDR50;
    if (HAL_GetDevClock() > 25000000) {
        host->caps |= MMC_CAP_SD_HIGHSPEED;
    }
#else
    host->caps = MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED | MMC_CAP_WAIT_WHILE_BUSY | \
                 MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25 | MMC_CAP_UHS_SDR50|MMC_CAP_SDIO_IRQ;
    if (host->param.low_speed)
        host->caps &= ~(MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED);
#endif
#ifdef CONFIG_SD_PM
    host->pm_caps = MMC_PM_KEEP_POWER | MMC_PM_WAKE_SDIO_IRQ;
#endif

#ifdef __CONFIG_ARCH_APP_CORE
#ifdef NUSE_STANDARD_INTERFACE
    if (host->sdc_id == 0) {
#ifndef SDC_FPGA
        sdmmc_pinctrl_init(host);
#endif
        host->caps |= MMC_CAP_4_BIT_DATA;
    } else if (host->sdc_id == 1) {
        sdmmc_pinctrl_init(host);
#if 0
        SDC1_SET_GPIO_PULL();
        SDC1_SET_GPIO_DRV();
        SDC1_SET_GPIO_MUX();
#endif
        host->caps &= ~MMC_CAP_4_BIT_DATA;
    }
#else
    HAL_BoardIoctl(HAL_BIR_GET_CFG, HAL_MKDEV(HAL_DEV_MAJOR_SDC, host->sdc_id),
                   (uint32_t)&sd_gpio_cfg);
    /*test gpio_detect by gpio irq*/
    sd_gpio_cfg->has_detect_gpio = 1;
    if (!sd_gpio_cfg)
        host->caps |= MMC_CAP_8_BIT_DATA | MMC_CAP_4_BIT_DATA;
    else if (sd_gpio_cfg->data_bits == 8)
        host->caps |= MMC_CAP_8_BIT_DATA | MMC_CAP_4_BIT_DATA;
    else if (sd_gpio_cfg->data_bits == 4)
        host->caps |= MMC_CAP_4_BIT_DATA;
#endif
#else
    host->caps |= MMC_CAP_4_BIT_DATA;
#endif

    __mci_restore_io(host);
    host->clk = 400000;

    /* register IRQ */
    if (host->sdc_id == 0) {
        ret = SDC_REQUEST_IRQ(SDC0_IRQn, SDC0_IRQHandler, host);
        if (ret != 0) {
            SDC_LOGE("%s,%d err:%d\n",__func__, __LINE__, ret);
            return NULL;
        }
        SDC_SetPriority(SDC0_IRQn, NVIC_PERIPH_PRIO_DEFAULT);
#if SDC1_SUPPORT
    } else if (host->sdc_id == 1) {
        ret = SDC_REQUEST_IRQ(SDC1_IRQn, SDC1_IRQHandler, host);
        if (ret != 0) {
            SDC_LOGE("%s,%d err:%d\n",__func__, __LINE__, ret);
            return NULL;
        }
        SDC_SetPriority(SDC1_IRQn, NVIC_PERIPH_PRIO_DEFAULT);
#endif
    }

#ifdef CONFIG_DETECT_CARD
    if (host->param.cd_mode == CARD_ALWAYS_PRESENT) {
        host->present = 1;
    } else if (host->param.cd_mode == CARD_DETECT_BY_GPIO_IRQ) {
#if 0
        if (!sd_gpio_cfg || (!sd_gpio_cfg->has_detect_gpio)) {
            SDC_LOGE("%s,%d cd_mode:%ld with no detect_gpio!\n",
                    __func__, __LINE__, host->param.cd_mode);
            return NULL;
        }
#endif

        //host->cd_port = sd_gpio_cfg->detect_port;
        //host->cd_pin = sd_gpio_cfg->detect_pin;
        //host->cd_pin_present_val = sd_gpio_cfg->detect_pin_present_val;
#ifndef CONFIG_DRIVERS_SDC_CDPIN_PRESENT_VAL
#define CONFIG_DRIVERS_SDC_CDPIN_PRESENT_VAL 0
#endif
        host->cd_pin_present_val = CONFIG_DRIVERS_SDC_CDPIN_PRESENT_VAL;
        //HAL_BoardIoctl(HAL_BIR_PINMUX_INIT, HAL_MKDEV(HAL_DEV_MAJOR_SDC,
        //               host->sdc_id), SDCGPIO_DET);
        SDC_LOGN("%s,%d no imp\n",__func__, __LINE__);

        //host->cd_delay = sd_gpio_cfg->detect_delay;
        host->cd_delay = 10;    /* short delay */
        SDC_InitTimer(&host->cd_timer, &__mci_cd_timer, host, 10);

        //HAL_GPIO_SetDebounce(&Irq_param, (2U << 4) | 1); /* set debounce clock */
        __mci_enable_cd_pin_irq(host);
        SDC_LOGN("%s,%d no imp\n",__func__, __LINE__);
        host->present = (host->cd_pin_present_val ==
                         HAL_GPIO_ReadPin(host->cd_gpio_pin, &host->present)) ? 1 : 0;
        //host->present = 1;

    } else if (host->param.cd_mode == CARD_DETECT_BY_D3) {
        uint32_t rval;

        //host->cd_delay = sd_gpio_cfg->detect_delay;
        host->cd_delay = 100;

        __mci_clk_prepare_enable(host);
        mmc_mdelay(1);
        host->present = 1;
        rval = mci_readl(host, SDXC_REG_RINTR);
        SDC_LOGD("sdc +> REG_RINTR=0x%x\n", (unsigned int)rval);
        if ((rval & SDXC_CardRemove)) {
            SDC_LOGD("sdc data[3] detect Card Remove\n");
            host->present = 0;
        }
        SDC_InitTimer(&host->cd_timer, &__mci_dat3_det, host, 300);
    }
#else
    host->present = 1;
#endif
    host->align_dma_buf = HAL_MallocAlign(SDC_ALIGN_DMA_BUF_SIZE);
    host->idma_des = HAL_MallocAlign(HAL_ALIGN(SDXC_MAX_DES_NUM * sizeof(smc_idma_des), OS_CACHE_ALIGN_BYTES));
    if (HAL_PT_TO_U(host->idma_des) & 0x07U) {
        SDC_LOGE_RAW(ROM_ERR_MASK, "%s malloc not aligned by 8B\n", __func__);
        return NULL;
    }

    SDC_LOGD("idma_des %lx\n",HAL_PR_SZ_L(host->idma_des));

    host->max_blk_count = 8192;
    host->max_blk_size = 4096;
    host->max_req_size = host->max_blk_size * host->max_blk_count;
    host->max_seg_size = host->max_req_size;
    host->max_segs = 128;
    host->ocr_avail = MMC_VDD_28_29 | MMC_VDD_29_30 | MMC_VDD_30_31 | MMC_VDD_31_32
                      | MMC_VDD_32_33 | MMC_VDD_33_34;

    SDC_LOGN("SDC Host Capability:0x%x Ocr avail:0x%x\n", (unsigned int)host->caps, (unsigned int)host->ocr_avail);

    /* init semaphore */
    SDC_SemCreate(&host->lock, 0);
    SDC_MutexCreate(&host->thread_lock);
#ifdef CONFIG_SDC_EXCLUSIVE_HOST
    SDC_SemCreate(&host->exclusive_lock, 1);
#endif

#ifdef CONFIG_DETECT_CARD
    if (host->param.cd_mode == CARD_DETECT_BY_D3 && host->present == 0) {
        SDC_LOGD("SDC power init.\n");
        HAL_SDC_PowerOn(host);
    } else if (host->present == 0) {
        /* if card is not present and the card detect mode is not CARD_DETECT_BY_D3,
         * we shutdown io voltage to save power. */
        SDC_LOGD("SDC no card detected, shutdown io voltage.\n");
        __mci_hold_io(host);
        //__mci_set_vddio(host, SDC_VOLTAGE_OFF);
    }
#endif

#ifdef CONFIG_SD_PM
    SDC_DEV(host->sdc_id)->platform_data = host;
    pm_register_ops(SDC_DEV(host->sdc_id));
#endif

    host->State = SDC_STATE_READY;
    host->wait = SDC_WAIT_NONE;

#ifdef CONFIG_DETECT_CARD
    //if (host->param.cd_mode != CARD_ALWAYS_PRESENT && host->present) {
    if (host->param.cd_mode != CARD_ALWAYS_PRESENT) {
        host->wait_voltage_stable = 1;
        if (host->cd_delay == 0) {
            SDC_ModTimer(&host->cd_timer, 10);
        } else {
            SDC_ModTimer(&host->cd_timer, host->cd_delay);
        }
    }
    SDC_LOGN("SDC cd_mode:%d present_val:%d\n", (unsigned int)host->param.cd_mode,
             (unsigned int)host->cd_pin_present_val);
#endif
    SDC_LOGN("SDC id:%d dma_use:%d present:%d\n driver version %s init ok.\n", (unsigned int)host->sdc_id,
             (unsigned int)host->dma_use, (unsigned int)host->present ,SDMMC_DRIVER_VERSION);
#ifdef SDC_FPGA
    SDC_LOGN("SDC ***Warning: use FPGA config,Are you sure?***\n wmb,cache unsupport now\n");
#endif
    sdc_hex_dump_word((const void *)(SDC_GPIO_BASE+0xb0),0x400);
    sdc_hex_dump_word((const void *)0x4002000, 0x200);

    return host;
}

/**
 * @brief DeInitializes the SDC peripheral.
 * @param sdc_id:
 *        @arg sdc_id-> SDC ID.
 * @retval  None.
 */
int32_t hal_sdc_deinit(uint32_t sdc_id)
{
    struct mmc_host *host = _mci_host[sdc_id];

    if (!host) {
        SDC_LOGE_RAW(ROM_ERR_MASK, "%s,%d err", __func__, __LINE__);
        return -1;
    }

#ifdef CONFIG_DETECT_CARD
    host->param.cd_mode = 0;
#endif

#ifdef CONFIG_SD_PM
    pm_unregister_ops(SDC_DEV(host->sdc_id));
#endif

    __mci_exit_host(host);
    if (host->sdc_id == 0) {
        SDC0_DisableMClock();
        SDC0_CCM_BusForceReset();
#if SDC1_SUPPORT
    } else if (host->sdc_id == 1) {
        SDC1_DisableMClock();
        SDC1_CCM_BusForceReset();
#endif
    }

#ifdef CONFIG_DETECT_CARD
    HAL_BoardIoctl(HAL_BIR_PINMUX_DEINIT, HAL_MKDEV(HAL_DEV_MAJOR_SDC,
                   host->sdc_id), SDCGPIO_DET);
#endif

#ifdef CONFIG_SDC_EXCLUSIVE_HOST
    SDC_SemDel(&host->exclusive_lock);
#endif
    SDC_MutexDelete(&host->thread_lock);
    SDC_SemDel(&host->lock);

    HAL_FreeAlign(host->idma_des);
    HAL_FreeAlign(host->align_dma_buf);
#ifdef CONFIG_DETECT_CARD
    if ((host->param.cd_mode == CARD_DETECT_BY_GPIO_IRQ)||
        (host->param.cd_mode == CARD_DETECT_BY_D3)) {
        SDC_DelTimer(&host->cd_timer);
    }
#endif
    if (host->sdc_id == 0) {
        SDC_FREE_IRQ(SDC0_IRQn, host);
#if SDC1_SUPPORT
    } else if (host->sdc_id == 1) {
        SDC_FREE_IRQ(SDC1_IRQn, host);
#endif
    }
    SDC_LOGD("sdc:%ld deinit ok.\n", HAL_PR_SZ_L(sdc_id));

    return 0;
}

/**
 * @brief malloc for sd host.
 * @param sdc_id:
 *        @arg host ID.
 * @retval  0 if success or other if failed.
 */
struct mmc_host *hal_sdc_create(uint32_t sdc_id, SDC_InitTypeDef *param)
{
    struct mmc_host *host = _mci_host[sdc_id];
    int ret;

    rt_kprintf("hal_sdc_create %d\n",sdc_id);

    if (host) {
        SDC_LOGE_RAW(ROM_ERR_MASK, "%s has already created!\n", __func__);
        return host;
    }

    host = HAL_Malloc(sizeof(struct mmc_host));
    if (host == NULL) {
        SDC_LOGE_RAW(ROM_ERR_MASK, "%s malloc fail\n", __func__);
    } else {
        SDC_Memset(host, 0, sizeof(struct mmc_host));
        host->sdc_id = sdc_id;
        host->ref = 0;
#ifdef __CONFIG_ARCH_APP_CORE
        memcpy(&host->param, param, sizeof(SDC_InitTypeDef));
        host->debug_mask = param->debug_mask;
        host->dma_use = param->dma_use;
#ifdef CONFIG_DETECT_CARD
        if (param->cd_mode == CARD_DETECT_BY_GPIO_IRQ || param->cd_mode == CARD_DETECT_BY_D3) {
            host->cd_gpio_isr = __mci_cd_irq;
            ret = mmc_gpiod_request_cd_irq(host);
            if (!param->cd_cb && ret < 0) {
                HAL_Free(host);
                SDC_LOGE("%s,%d cd_mode:%ld with no cb!\n",
                         __func__, __LINE__, HAL_PR_SZ_L(param->cd_mode));
                return NULL;
            }
        }
#endif
#endif
        _mci_host[sdc_id] = host;
        SDC_LOGN("%s host:%p id:%d\n", __func__, host, host->sdc_id);
    }

    return host;
}

/**
 * @brief free for sd host.
 * @param host:
 *        @arg host ID.
 * @param flg:
 *        @arg 0:normal delete, 1:unnormal delete, internal use.
 * @retval  0 if success or other if failed.
 */
int32_t hal_sdc_destroy(struct mmc_host *host)
{
    if (host == NULL) {
        SDC_LOGW_RAW(ROM_WRN_MASK, "%s host not exit!\n", __func__);
        return -1;
    }

    if (host->ref != 0) {
        SDC_LOGW("%s fail, ref:%d\n", __func__, host->ref);
        return -1;
    }
    _mci_host[host->sdc_id] = NULL;
    SDC_LOGD("%s host:%p id:%d\n", __func__, host, host->sdc_id);
    HAL_Free(host);

    return 0;
}

/**
 * @brief get pointer of mmc_host.
 * @param sdc_id:
 *        @arg host ID.
 * @retval  pointer of mmc_card if success or NULL if failed.
 */
struct mmc_host *hal_sdc_open(uint32_t sdc_id)
{
    struct mmc_host *host = _mci_host[sdc_id];

    if (host == NULL || host->sdc_id != sdc_id) {
        SDC_LOGW_RAW(ROM_WRN_MASK, "%s host not exit! id:%d,host:%x\n",  __func__, (unsigned int)sdc_id, HAL_PR_SZ(HAL_PT_TO_U(host)));
        return NULL;
    }

    host->ref++;

    return host;
}

/**
 * @brief close mmc_host.
 * @param host_id:
 *        @arg host ID.
 * @retval  0 if success or other if failed.
 */
uint32_t hal_sdc_close(uint32_t sdc_id)
{
    struct mmc_host *host = _mci_host[sdc_id];

    if (host == NULL || host->sdc_id != sdc_id || host->ref < 1) {
        SDC_LOGW_RAW(ROM_WRN_MASK, "%s fail! id:%ld\n",  __func__, HAL_PR_SZ_L(sdc_id));
        return -1;
    }
    host->ref--;

    return 0;
}
