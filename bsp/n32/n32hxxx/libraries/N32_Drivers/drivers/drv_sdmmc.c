/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-10     Claude       N32 SDMMC driver with rt_mmcsd_host_ops,
 *                             SDMMC1/SDMMC2 dual-instance support.
 *
 * Low-level SDHOST ops (request/set_iocfg/get_card_status/enable_sdio_irq).
 * Data transfer: configurable CPU FIFO polling or SDMA.
 * INTSTS.CMDC unreliable → poll CMDINHC.
 */

#include "drv_sdmmc.h"
#include "n32h7xx_rcc.h"
#include "n32h7xx_pwr.h"
#include "n32h7xx_gpio.h"
#include <drivers/dev_mmcsd_core.h>
#include <drivers/dev_sdio.h>

#define DRV_DBG_TAG "drv.sdmmc"
#define DRV_DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_SDIO

#define N32_SDIO_CMD_TIMEOUT_MS  100U
#define N32_SDIO_DATA_TIMEOUT_MS 2000U
#define N32_SDIO_BUSY_TIMEOUT_MS 1000U

/* ═══════════════════════════════════════════════════════════════════════
 *  Instance selection — matches STM32 convention: BSP_USING_SDIOx
 *  ═══════════════════════════════════════════════════════════════════ */

#if defined(BSP_USING_SDIO1) && defined(BSP_USING_SDIO2)
#error "Only one SDIO instance supported per configuration"
#endif

#if defined(BSP_USING_SDIO1)

static struct n32_sdio_config sdio_cfg = {
    .sdhost = SDHOST1,
    .sdmmc = SDMMC1,
    .irqn = SDMMC1_IRQn,
    .clkfb_val = SDMMC1_CLKFB,
    .pwrctrl_val = HSC1_SDMMC1_PWRCTRL,
    .lpclk_en = RCC_AXI_PERIPHEN_M7_SDMMC1LP,
    .periphrst_val = (RCC_AXI_PERIPHRST_SDMMC1 | RCC_AXI_PERIPHRST_SDHOST1),
    .name = "sd0",
};
#define SDMMC_ISR           SDMMC1_IRQHandler
#define SDMMC_ENABLE_CLK_FN RCC_EnableAXIPeriphClk1
#define SDMMC_ENABLE_RST_FN RCC_EnableAXIPeriphReset1

#elif defined(BSP_USING_SDIO2)

static struct n32_sdio_config sdio_cfg = {
    .sdhost = SDHOST2,
    .sdmmc = SDMMC2,
    .irqn = SDMMC2_IRQn,
    .clkfb_val = SDMMC2_CLKFB,
    .pwrctrl_val = HSC2_SDMMC2_PWRCTRL,
    .lpclk_en = RCC_AHB1_PERIPHEN_M7_SDMMC2LP,
    .periphrst_val = (RCC_AHB1_PERIPHRST_SDMMC2 | RCC_AHB1_PERIPHRST_SDHOST2),
    .name = "sd0",
};
#define SDMMC_ISR           SDMMC2_IRQHandler
#define SDMMC_ENABLE_CLK_FN RCC_EnableAHB1PeriphClk1
#define SDMMC_ENABLE_RST_FN RCC_EnableAHB1PeriphReset1

#else
#error "Define BSP_USING_SDIO1 or BSP_USING_SDIO2"
#endif

/* ═══════════════════════════════════════════════════════════════════════
 *  Helpers
 *  ═══════════════════════════════════════════════════════════════════════ */

/* RT-Thread → N32 response type mapping.
 * RT-Thread uses bits [0:3] of flags, N32 uses CARD_ResponseType enum.     */
static SDMMC_CardRspType _map_resp_type(struct rt_mmcsd_cmd *cmd)
{
    switch (resp_type(cmd))
    {
    case RESP_NONE:
        return CARD_ResponseTypeNone;
    case RESP_R1:
        return CARD_ResponseTypeR1;
    case RESP_R1B:
        return CARD_ResponseTypeR1b;
    case RESP_R2:
        return CARD_ResponseTypeR2;
    case RESP_R3:
        return CARD_ResponseTypeR3;
    case RESP_R4:
        return CARD_ResponseTypeR4;
    case RESP_R6:
        return CARD_ResponseTypeR6;
    case RESP_R7:
        return CARD_ResponseTypeR7;
    case RESP_R5:
        return CARD_ResponseTypeR5;
    default:
        return CARD_ResponseTypeR1;
    }
}

/* ── R2 response normalisation ───────────────────────────────────────
 * N32 SDHOST stores R2 byte-shifted; shift 8 bits left to match
 * the SDHCI layout expected by mmcsd_decode_cid / mmcsd_decode_csd.    */
static void _fixup_r2_resp(SDHOST_Module *sdhost, rt_uint32_t resp[4])
{
    rt_uint32_t r0 = sdhost->CMDRSP0;
    rt_uint32_t r1 = sdhost->CMDRSP1;
    rt_uint32_t r2 = sdhost->CMDRSP2;
    rt_uint32_t r3 = sdhost->CMDRSP3;

    /* N32 numbers R2 words from least to most significant, while
     * RT-Thread expects resp[0] to hold bits 127:96. */
    resp[0] = (r3 << 8U) | (r2 >> 24U);
    resp[1] = (r2 << 8U) | (r1 >> 24U);
    resp[2] = (r1 << 8U) | (r0 >> 24U);
    resp[3] = r0 << 8U;
}

static rt_bool_t _wait_present_clear(SDHOST_Module *sdhost,
                                     rt_uint32_t mask,
                                     rt_uint32_t timeout_ms)
{
    rt_tick_t start = rt_tick_get();
    rt_tick_t timeout = rt_tick_from_millisecond((rt_int32_t)timeout_ms);

    while (sdhost->PRESTS & mask)
    {
        if ((rt_tick_get() - start) >= timeout)
        {
            return RT_FALSE;
        }
    }

    return RT_TRUE;
}

static rt_bool_t _wait_data_status(SDHOST_Module *sdhost,
                                   rt_uint32_t ready_mask,
                                   rt_uint32_t timeout_ms,
                                   rt_uint32_t *status)
{
    rt_tick_t start = rt_tick_get();
    rt_tick_t timeout = rt_tick_from_millisecond((rt_int32_t)timeout_ms);

    do
    {
        *status = sdhost->INTSTS;
        if (*status & (ready_mask | SDHOST_DataErrorFlag | SDHOST_DmaErrorFlag))
        {
            return RT_TRUE;
        }
    } while ((rt_tick_get() - start) < timeout);

    return RT_FALSE;
}

#ifdef BSP_USING_SDIO_SDMA
static rt_bool_t _dcache_is_enabled(void)
{
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
    return (SCB->CCR & SCB_CCR_DC_Msk) != 0U ? RT_TRUE : RT_FALSE;
#else
    return RT_FALSE;
#endif
}

static void _config_sdma_boundary(SDHOST_Module *sdhost,
                                  const void *buffer,
                                  rt_uint32_t length)
{
    rt_uint32_t address = (rt_uint32_t)buffer;
    SDHOST_SDMA_Buffer_Size size;

    if (length + (address % 0x1000U) <= 0x1000U)
    {
        size = SDHOST_SDMABUFFERSIZE_4KB;
    }
    else if (length + (address % 0x2000U) <= 0x2000U)
    {
        size = SDHOST_SDMABUFFERSIZE_8KB;
    }
    else if (length + (address % 0x4000U) <= 0x4000U)
    {
        size = SDHOST_SDMABUFFERSIZE_16KB;
    }
    else if (length + (address % 0x8000U) <= 0x8000U)
    {
        size = SDHOST_SDMABUFFERSIZE_32KB;
    }
    else if (length + (address % 0x10000U) <= 0x10000U)
    {
        size = SDHOST_SDMABUFFERSIZE_64KB;
    }
    else if (length + (address % 0x20000U) <= 0x20000U)
    {
        size = SDHOST_SDMABUFFERSIZE_128KB;
    }
    else if (length + (address % 0x40000U) <= 0x40000U)
    {
        size = SDHOST_SDMABUFFERSIZE_256KB;
    }
    else
    {
        size = SDHOST_SDMABUFFERSIZE_512KB;
    }

    SDMMC_ConfigSDMABufferSize(sdhost, size);
}
#endif

/* ═══════════════════════════════════════════════════════════════════════
 *  Hardware setup (called once at host creation)
 *  ═══════════════════════════════════════════════════════════════════════ */

static int _hw_setup(struct n32_sdio *sdio)
{
    const struct n32_sdio_config *c = &sdio->cfg;
    int i;

    /* 1. Power enable */
    PWR_MoudlePowerEnable(c->pwrctrl_val, ENABLE);

    /* 2. LP clock enable */
    SDMMC_ENABLE_CLK_FN(c->lpclk_en, ENABLE);

    /* 3. Peripheral reset (de-assert) */
    SDMMC_ENABLE_RST_FN(c->periphrst_val);

    /* 4. Clock-feedback select */
    AFIO_SDMMCClkSel(c->clkfb_val, ENABLE);

    /* 6. SDMMC wrapper configuration */
    {
        SDMMC_WrapperType w;
        SDMMC_StructWrapperInit(&w);
        w.MaxBlockLen = SDMMC_MAXBLOCKLEN_512B;
        w.SDBaseCLKFreq = 25;
        w.TimeOutUnit = SDMMC_TIMEOUTCLKUNIT_KHZ;
        w.TuningCNT = 0x20;
        w.WKUPSignalMode = SDMMC_ASYNCWKUP;
        w.SPIBlockMode = SDMMC_SPIBLOCKMODEUNSUPPORT;
        w.SPIMode = SDMMC_SPIMODEUNSUPPORT;
        w.DDR50 = SDMMC_DDR50SUPPORT;
        w.SDR104 = SDMMC_SDR104SUPPORT;
        w.SDR50 = SDMMC_SDR50SUPPORT;
        w.SlotType = SDMMC_SDTYPE;
        w.AsyncInt = SDMMC_ASYNCINTSUPPORT;
        w.Suspend_Resume = SDMMC_SUSRESUNSUPPORT;
        w.SDMA = SDMMC_SDMASUPPORT;
        w.HS = SDMMC_HSSUPPORT;
        w.ADMA2 = SDMMC_ADMA2SUPPORT;
        w.Embedded_8bit = SDMMC_EMBEDDEDUNSUPPORT;
        w.UseTuningSDR50 = SDMMC_SDR50TUNING;
        w.DSSDCLKFreq = 0x04;
        w.INITSDCLKFreq = 0x00;
        w.SDR12SDCLKFreq = 0x04;
        w.HSSDCLKFreq = 0x02;
        w.SDR50SDCLKFreq = 0x01;
        w.SDR25SDCLKFreq = 0x02;
        w.SDR104SDCLKFreq = 0x00;
        w.DDR50SDCLKFreq = 0x02;
        SDMMC_WrapperConfig(c->sdmmc, &w);
    }

    /* 7. Card detect — poll with timeout */
    SDMMC_ConfigCardDetectSignal(c->sdhost,
                                 SDMMC_CARDDETECT_TEST,
                                 SDMMC_CARDTESTLEVEL_HIGH);

    for (i = 0;
         SDMMC_GetPresentFlagStatus(c->sdhost, SDHOST_CardInsertedFlag) != SET && i < 1000;
         i++)
    {
        rt_thread_mdelay(1);
    }
    if (i >= 1000)
    {
        LOG_E("%s: no card detected", c->name);
        return -RT_ERROR;
    }
    LOG_D("%s: card detected", c->name);

    /* 8. Power on + init clock (400 kHz identification) */
    SDMMC_EnablePower(c->sdhost, ENABLE);
    {
        uint32_t ps;
        if (((SD_XIN_CLK % 400000U) != 0) || ((SD_XIN_CLK / 400000U) % 2 != 0))
        {
            ps = SD_XIN_CLK / 400000U / 2 + 1;
        }
        else
        {
            ps = SD_XIN_CLK / 400000U / 2;
        }
        SDMMC_SetSdClock(c->sdhost, DISABLE, ps);
    }

    /* Status bits must be enabled even when signal interrupts are disabled. */
    SDMMC_EnableFlagStatus(c->sdhost, SDHOST_AllInterruptFlags, ENABLE);

    LOG_I("%s: hw init done, data path %s", c->name,
#ifdef BSP_USING_SDIO_SDMA
          "SDMA");
#else
          "PIO");
#endif
    return RT_EOK;
}

/* ═══════════════════════════════════════════════════════════════════════
 *  rt_mmcsd_host_ops
 *  ═══════════════════════════════════════════════════════════════════════ */

/* ── request() ─────────────────────────────────────────────────────── */

static void n32_sdio_request(struct rt_mmcsd_host *host,
                             struct rt_mmcsd_req *req)
{
    struct n32_sdio *sdio = host->private_data;
    SDHOST_Module *sdh = sdio->cfg.sdhost;
    struct rt_mmcsd_cmd *cmd = req->cmd;
    struct rt_mmcsd_data *data;
    SDMMC_CMD sc;
    SDHOST_TMODE_struct tm;
#ifdef BSP_USING_SDIO_SDMA
    rt_uint32_t total_bytes;
#endif

    RT_ASSERT(cmd != RT_NULL);

    /* ── N32 SDHOST quirks ─────────────────────────────────────────
     * CMD5: memory cards return bogus R4 → skip init_sdio() path.     */
    if (cmd->cmd_code == SD_IO_SEND_OP_COND)
    {
        cmd->err = -RT_ERROR;
        mmcsd_req_complete(host);
        return;
    }

    data = cmd->data;
    cmd->err = RT_EOK;
    if (data != RT_NULL)
    {
        data->err = RT_EOK;
    }

    rt_memset(&sc, 0, sizeof(sc));
    SDMMC_TModeStructInit(&tm);

    /* Do not let status from the previous transaction poison this request. */
    SDMMC_ClrFlag(sdh, SDHOST_CommandFlag | SDHOST_DataFlag |
                           SDHOST_DmaErrorFlag | SDHOST_DmaCompleteFlag);

    /* ── Populate N32 command descriptor ─────────────────────── */
    sc.index = cmd->cmd_code;
    sc.argument = cmd->arg;
    sc.type = CARD_CommandTypeNormal;
    sc.responseType = _map_resp_type(cmd);
    sc.flags = 0;
    sc.responseErrorFlags = 0;

    /* ── Data transfer setup ─────────────────────────────────── */
    if (data != RT_NULL)
    {
        sc.flags |= SDHOST_DataPresentFlag;

#ifdef BSP_USING_SDIO_SDMA
        tm.DMAE = SDHOST_TMODE_DMAENABLE;
#else
        tm.DMAE = SDHOST_TMODE_DMADISABLE;
#endif
        tm.DATDIR = (data->flags & DATA_DIR_READ)
                        ? SDHOST_TMODE_DATDIR_READ
                        : SDHOST_TMODE_DATDIR_WRITE;
        tm.BCNTE = (data->blks > 1)
                       ? SDHOST_TMODE_BLOCKCNTENABLE
                       : SDHOST_TMODE_BLOCKCNTDISABLE;
        tm.BLKSEL = (data->blks > 1)
                        ? SDHOST_TMODE_MULTIBLK
                        : SDHOST_TMODE_SINGLEBLK;
        /* Auto CMD12 disabled — driver sends CMD12 manually in _out */
        tm.ACMDE = SDHOST_TMODE_NOACMDEN;

        sdh->BLKCFG = (sdh->BLKCFG & ~(SDHOST_BLKCFG_CNT | SDHOST_BLKCFG_SIZE)) | ((data->blks << SDHOST_BLOCK_COUNT_OFFSET) & SDHOST_BLKCFG_CNT) | (data->blksize & SDHOST_BLKCFG_SIZE);

#ifdef BSP_USING_SDIO_SDMA
        total_bytes = data->blks * data->blksize;

        if ((((rt_uint32_t)data->buf) & 3U) != 0U)
        {
            data->err = -RT_EINVAL;
            goto _out;
        }

        _config_sdma_boundary(sdh, data->buf, total_bytes);

        /* ── SDMA: cache maintenance ──────────────────────────── */
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
        if (_dcache_is_enabled() && (data->flags & DATA_DIR_READ))
        {
            SCB_CleanInvalidateDCache_by_Addr((uint32_t *)data->buf,
                                              (int32_t)total_bytes);
        }
        else if (_dcache_is_enabled())
        {
            SCB_CleanDCache_by_Addr((uint32_t *)data->buf,
                                    (int32_t)total_bytes);
        }
#endif
        /* ── SDMA: system address + DMA mode ──────────────────── */
        sdh->DSADD = (uint32_t)(data->buf);
        sdh->CTRL1 &= ~SDHOST_CTRL1_DMASEL;   /* SDMA mode (DMASEL=0) */
#endif
    }

    /* ── Fire command ─────────────────────────────────────────── */
    SDMMC_SendCommand(sdh, &sc, &tm);

    /* ── Wait command completion (poll CMDINHC — INTSTS.CMDC unreliable) ── */
    if (!_wait_present_clear(sdh, SDHOST_CommandInhibitFlag,
                             N32_SDIO_CMD_TIMEOUT_MS))
    {
        cmd->err = -RT_ETIMEOUT;
        SDMMC_SoftWareReset(sdh, SDHOST_SOFTWARE_CMDLINE);
        goto _out;
    }

    /* ── Check hardware errors ────────────────────────────────── */
    {
        uint32_t ints = sdh->INTSTS;
        if (ints & SDHOST_CommandErrorFlag)
        {
            sdh->INTSTS = (ints & SDHOST_CommandErrorFlag);
            cmd->err = (ints & SDHOST_CommandTimeoutFlag)
                           ? -RT_ETIMEOUT
                           : -RT_ERROR;
            SDMMC_SoftWareReset(sdh, SDHOST_SOFTWARE_CMDLINE);
            goto _out;
        }
    }

    /* ── Read response ────────────────────────────────────────── */
    if (sc.responseType == CARD_ResponseTypeR2)
    {
        _fixup_r2_resp(sdh, cmd->resp);
    }
    else if (sc.responseType != CARD_ResponseTypeNone)
    {
        cmd->resp[0] = sdh->CMDRSP0;
    }
    SDMMC_ClrFlag(sdh, SDHOST_CommandFlag);

    if (data == RT_NULL && sc.responseType == CARD_ResponseTypeR1b &&
        !_wait_present_clear(sdh, SDHOST_DataLineActiveFlag,
                             N32_SDIO_BUSY_TIMEOUT_MS))
    {
        cmd->err = -RT_ETIMEOUT;
        SDMMC_SoftWareReset(sdh, SDHOST_SOFTWARE_DATALINE);
        goto _out;
    }

    /* ── Data transfer ───────────────────────────────────────── */
    if (data != RT_NULL)
    {
#ifdef BSP_USING_SDIO_SDMA
        /* ── SDMA path ────────────────────────────────────────── */
        volatile uint32_t to;
        uint32_t ints;
        uint32_t sdma_addr;

        /* Poll for TC or error (HAL-style loop with DSADD re-write) */
        to = 0x800000U;
        while (1)
        {
            ints = sdh->INTSTS;

            if (ints & SDHOST_DmaCompleteFlag)
            {
                sdh->INTSTS = SDHOST_DmaCompleteFlag;
                sdma_addr = sdh->DSADD;
                sdh->DSADD = sdma_addr;
            }

            if (ints & (SDHOST_DataCompleteFlag | SDHOST_DataErrorFlag | SDHOST_DmaErrorFlag))
            {
                break;
            }

            if (--to == 0)
            {
                data->err = -RT_ETIMEOUT;
                goto _data_error;
            }
        }

        if (ints & (SDHOST_DataErrorFlag | SDHOST_DmaErrorFlag))
        {
            LOG_E("sdma cmd=%u failed: intsts=0x%08x prests=0x%08x dsadd=0x%08x",
                  cmd->cmd_code, ints, sdh->PRESTS, sdh->DSADD);
            sdh->INTSTS = (ints & (SDHOST_DataErrorFlag | SDHOST_DmaErrorFlag));
            data->err = (ints & SDHOST_DataTimeoutFlag)
                            ? -RT_ETIMEOUT
                            : -RT_ERROR;
            goto _data_error;
        }

        sdh->INTSTS = SDHOST_DataCompleteFlag | SDHOST_DmaCompleteFlag;

#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
        if (_dcache_is_enabled() && (data->flags & DATA_DIR_READ))
        {
            SCB_InvalidateDCache_by_Addr((uint32_t *)data->buf,
                                         (int32_t)total_bytes);
        }
#endif
#else
        /* ── CPU FIFO path ────────────────────────────────────── */
        rt_uint32_t block;
        rt_uint32_t i;
        rt_uint32_t words_per_block;
        uint32_t ints;

        if ((data->blksize & 3U) != 0U)
        {
            data->err = -RT_EINVAL;
            goto _data_error;
        }
        words_per_block = data->blksize / 4U;

        if (data->flags & DATA_DIR_READ)
        {
            rt_uint32_t *dst = (rt_uint32_t *)data->buf;
            for (block = 0; block < data->blks; block++)
            {
                if (!_wait_data_status(sdh, SDHOST_BufferReadReadyFlag,
                                       N32_SDIO_DATA_TIMEOUT_MS, &ints))
                {
                    data->err = -RT_ETIMEOUT;
                    goto _data_error;
                }
                if (ints & (SDHOST_DataErrorFlag | SDHOST_DmaErrorFlag))
                {
                    data->err = (ints & SDHOST_DataTimeoutFlag)
                                    ? -RT_ETIMEOUT
                                    : -RT_ERROR;
                    goto _data_error;
                }

                /* One BUFRRDY event makes one complete block available. */
                SDMMC_ClrFlag(sdh, SDHOST_BufferReadReadyFlag);
                for (i = 0; i < words_per_block; i++)
                {
                    *dst++ = SDMMC_ReadData(sdh);
                }
            }
        }
        else
        {
            const rt_uint32_t *src = (const rt_uint32_t *)data->buf;
            for (block = 0; block < data->blks; block++)
            {
                if (!_wait_data_status(sdh, SDHOST_BufferWriteReadyFlag,
                                       N32_SDIO_DATA_TIMEOUT_MS, &ints))
                {
                    data->err = -RT_ETIMEOUT;
                    goto _data_error;
                }
                if (ints & (SDHOST_DataErrorFlag | SDHOST_DmaErrorFlag))
                {
                    data->err = (ints & SDHOST_DataTimeoutFlag)
                                    ? -RT_ETIMEOUT
                                    : -RT_ERROR;
                    goto _data_error;
                }

                /* One BUFWRDY event accepts one complete block. */
                SDMMC_ClrFlag(sdh, SDHOST_BufferWriteReadyFlag);
                for (i = 0; i < words_per_block; i++)
                {
                    SDMMC_WriteData(sdh, *src++);
                }
            }
        }

        if (!_wait_data_status(sdh, SDHOST_DataCompleteFlag,
                               N32_SDIO_DATA_TIMEOUT_MS, &ints))
        {
            data->err = -RT_ETIMEOUT;
            goto _data_error;
        }
        if (ints & (SDHOST_DataErrorFlag | SDHOST_DmaErrorFlag))
        {
            data->err = (ints & SDHOST_DataTimeoutFlag)
                            ? -RT_ETIMEOUT
                            : -RT_ERROR;
            goto _data_error;
        }
        SDMMC_ClrFlag(sdh, SDHOST_DataFlag | SDHOST_DmaCompleteFlag);
#endif

        /* Multi-block transfers are terminated by CMD12 below. */
        if (req->stop == RT_NULL &&
            !_wait_present_clear(sdh, SDHOST_DataLineActiveFlag,
                                 N32_SDIO_BUSY_TIMEOUT_MS))
        {
            data->err = -RT_ETIMEOUT;
            goto _data_error;
        }
    }

    goto _out;

_data_error:
#ifdef BSP_USING_SDIO_SDMA
    LOG_E("sdma cmd=%u data error=%d: intsts=0x%08x prests=0x%08x dsadd=0x%08x",
          cmd->cmd_code, data != RT_NULL ? data->err : 0,
          sdh->INTSTS, sdh->PRESTS, sdh->DSADD);
#endif
    SDMMC_ClrFlag(sdh, SDHOST_DataFlag | SDHOST_DmaErrorFlag |
                           SDHOST_DmaCompleteFlag);
    SDMMC_SoftWareReset(sdh, SDHOST_SOFTWARE_DATALINE);

_out:
    /* ── Stop command (CMD12) if multi-block ─────────────────── */
    if (req->stop != RT_NULL)
    {
        SDMMC_CMD sc_s;
        SDHOST_TMODE_struct tm_s;

        rt_memset(&sc_s, 0, sizeof(sc_s));
        SDMMC_TModeStructInit(&tm_s);

        sc_s.index = req->stop->cmd_code;
        sc_s.argument = req->stop->arg;
        sc_s.type = CARD_CommandTypeAbort;
        sc_s.responseType = _map_resp_type(req->stop);
        sc_s.flags = 0;
        sc_s.responseErrorFlags = 0;

        SDMMC_ClrFlag(sdh, SDHOST_CommandFlag);
        SDMMC_SendCommand(sdh, &sc_s, &tm_s);
        if (!_wait_present_clear(sdh, SDHOST_CommandInhibitFlag,
                                 N32_SDIO_CMD_TIMEOUT_MS))
        {
            req->stop->err = -RT_ETIMEOUT;
            SDMMC_SoftWareReset(sdh, SDHOST_SOFTWARE_CMDLINE);
        }
        else
        {
            uint32_t ints = sdh->INTSTS;
            if (ints & SDHOST_CommandErrorFlag)
            {
                req->stop->err = (ints & SDHOST_CommandTimeoutFlag)
                                     ? -RT_ETIMEOUT
                                     : -RT_ERROR;
            }
            else
            {
                if (sc_s.responseType == CARD_ResponseTypeR2)
                {
                    _fixup_r2_resp(sdh, req->stop->resp);
                }
                else if (sc_s.responseType != CARD_ResponseTypeNone)
                {
                    req->stop->resp[0] = sdh->CMDRSP0;
                }
                req->stop->err = RT_EOK;

                if (!_wait_present_clear(sdh, SDHOST_DataLineActiveFlag,
                                         N32_SDIO_BUSY_TIMEOUT_MS))
                {
                    req->stop->err = -RT_ETIMEOUT;
                    SDMMC_SoftWareReset(sdh, SDHOST_SOFTWARE_DATALINE);
                }
            }
            SDMMC_ClrFlag(sdh, SDHOST_CommandFlag);
        }
    }

    mmcsd_req_complete(host);
}

/* ── set_iocfg() ───────────────────────────────────────────────────── */

static void n32_sdio_set_iocfg(struct rt_mmcsd_host *host,
                               struct rt_mmcsd_io_cfg *io_cfg)
{
    struct n32_sdio *sdio = host->private_data;
    SDHOST_Module *sdh = sdio->cfg.sdhost;
    rt_uint32_t clk = io_cfg->clock;
    rt_uint32_t ps;

    /* ── Power mode ─────────────────────────────────────────── */
    switch (io_cfg->power_mode)
    {
    case MMCSD_POWER_OFF:
        SDMMC_EnablePower(sdh, DISABLE);
        return;
    case MMCSD_POWER_UP:
        /* clock stopped during power-up transition */
        SDMMC_EnablePower(sdh, ENABLE);
        SDMMC_SetSdClock(sdh, DISABLE, 0);
        return;
    case MMCSD_POWER_ON:
        break;   /* proceed to clock + bus width config */
    default:
        return;
    }

    /* ── Sanity checks ───────────────────────────────────────── */
    if (clk == 0U)
    {
        LOG_W("%s: zero clock requested, keeping current", sdio->cfg.name);
        return;
    }

    if (clk > host->freq_max)
    {
        clk = host->freq_max;
    }

    if (clk > (SD_XIN_CLK / 2U))
    {
        LOG_W("%s: clk %u > max %u, clamping",
              sdio->cfg.name, clk, SD_XIN_CLK / 2U);
        clk = SD_XIN_CLK / 2U;
    }

    /* SDCLK = SD_XIN_CLK / (2 * prescaler) */
    ps = (SD_XIN_CLK + (2U * clk) - 1U) / (2U * clk);
    if (ps < 1U)
    {
        ps = 1U;
    }

    LOG_D("%s: set clk req=%u real=%u ps=%lu bus=%s",
          sdio->cfg.name,
          clk / 1000U,
          (SD_XIN_CLK / (2U * ps)) / 1000U,
          ps,
          io_cfg->bus_width == MMCSD_BUS_WIDTH_4 ? "4-bit" : io_cfg->bus_width == MMCSD_BUS_WIDTH_8 ? "8-bit"
                                                                                                    : "1-bit");

    /* ── Apply clock ─────────────────────────────────────────── */
    SDMMC_SetSdClock(sdh, DISABLE, ps);

    /* ── Bus width ───────────────────────────────────────────── */
    if (io_cfg->bus_width == MMCSD_BUS_WIDTH_4)
    {
        SDMMC_ConfigBusWidth(sdh, SDHOST_DataBusWidth4Bit);
    }
    else if (io_cfg->bus_width == MMCSD_BUS_WIDTH_8)
    {
        SDMMC_ConfigBusWidth(sdh, SDHOST_DataBusWidth8Bit);
    }
    else
    {
        SDMMC_ConfigBusWidth(sdh, SDHOST_DataBusWidth1Bit);
    }
}

/* ── get_card_status() ─────────────────────────────────────────────── */

static rt_int32_t n32_sdio_get_card_status(struct rt_mmcsd_host *host)
{
    struct n32_sdio *sdio = host->private_data;

    if (SDMMC_GetPresentFlagStatus(sdio->cfg.sdhost,
                                   SDHOST_CardInsertedFlag) == SET)
    {
        return 1;   /* card present */
    }
    return 0;
}

/* ── enable_sdio_irq() ─────────────────────────────────────────────── */

static void n32_sdio_enable_sdio_irq(struct rt_mmcsd_host *host,
                                     rt_int32_t enable)
{
    struct n32_sdio *sdio = host->private_data;
    SDHOST_Module *sdh = sdio->cfg.sdhost;

    if (enable)
    {
        LOG_D("%s: enable sdio irq", sdio->cfg.name);
        SDMMC_ClrFlag(sdh, SDHOST_CardInterruptFlag);
        SDMMC_EnableFlagStatus(sdh, SDHOST_CardInterruptFlag, ENABLE);
        SDMMC_ConfigInt(sdh, SDHOST_CardInterruptFlag, ENABLE);
        NVIC_SetPriority(sdio->cfg.irqn, 1);
        NVIC_EnableIRQ(sdio->cfg.irqn);
    }
    else
    {
        LOG_D("%s: disable sdio irq", sdio->cfg.name);
        NVIC_DisableIRQ(sdio->cfg.irqn);
        SDMMC_ConfigInt(sdh, SDHOST_CardInterruptFlag, DISABLE);
        SDMMC_EnableFlagStatus(sdh, SDHOST_CardInterruptFlag, DISABLE);
    }
}

/* ═══════════════════════════════════════════════════════════════════════
 *  Host ops table
 *  ═══════════════════════════════════════════════════════════════════════ */

static const struct rt_mmcsd_host_ops n32_sdio_ops = {
    .request = n32_sdio_request,
    .set_iocfg = n32_sdio_set_iocfg,
    .get_card_status = n32_sdio_get_card_status,
    .enable_sdio_irq = n32_sdio_enable_sdio_irq,
    /* tuning / card_busy / signal_voltage_switch → deferred to future */
};

/* ═══════════════════════════════════════════════════════════════════════
 *  ISR — forwards to RT-Thread SDIO framework
 *  ═══════════════════════════════════════════════════════════════════════ */

static struct n32_sdio *sdio_inst = RT_NULL;   /* singleton for ISR */

void SDMMC_ISR(void)
{
    rt_interrupt_enter();

    if (sdio_inst != RT_NULL && sdio_inst->host != RT_NULL)
    {
        uint32_t pending = sdio_inst->cfg.sdhost->INTSTS & SDHOST_CardInterruptFlag;

        /* Card interrupt (SDIO I/O) → wake up sdio_irq thread */
        if (pending & SDHOST_INTSTS_CINT)
        {
            SDMMC_ClrFlag(sdio_inst->cfg.sdhost, SDHOST_CardInterruptFlag);
            sdio_irq_wakeup(sdio_inst->host);
        }
    }

    rt_interrupt_leave();
}

/* ═══════════════════════════════════════════════════════════════════════
 *  Initialisation
 *  ═══════════════════════════════════════════════════════════════════════ */

int n32_hw_sdio_init(void)
{
    struct n32_sdio *sdio;
    struct rt_mmcsd_host *host;
    int ret;

    sdio = (struct n32_sdio *)rt_malloc(sizeof(*sdio));
    if (sdio == RT_NULL)
    {
        LOG_E("malloc n32_sdio failed");
        return -RT_ENOMEM;
    }
    rt_memset(sdio, 0, sizeof(*sdio));
    sdio->cfg = sdio_cfg;       /* copy per-instance config */

    /* ── Hardware init ──────────────────────────────────────── */
    ret = _hw_setup(sdio);
    if (ret != RT_EOK)
    {
        rt_free(sdio);
        return ret;
    }

    /* ── Allocate & configure mmcsd host ─────────────────────── */
    host = mmcsd_alloc_host();
    if (host == RT_NULL)
    {
        LOG_E("mmcsd_alloc_host failed");
        rt_free(sdio);
        return -RT_ENOMEM;
    }

    host->name[0] = 's';
    host->name[1] = 'd';
    host->name[2] = '0';
    host->name[3] = '\0';
    host->ops = &n32_sdio_ops;
    host->freq_min = SD_INIT_FREQ;
    host->freq_max = SDIO_MAX_FREQ;
    host->valid_ocr = 0x00FFFF80U;  /* 1.65V – 3.6V (same as STM32) */
    host->flags = MMCSD_BUSWIDTH_4 | MMCSD_MUTBLKWRITE | MMCSD_SUP_HIGHSPEED;
    host->max_seg_size = SDIO_BUFF_SIZE;
    host->max_dma_segs = 1;
    host->max_blk_size = 512;
    host->max_blk_count = 256;

    host->private_data = sdio;
    sdio->host = host;
    sdio_inst = sdio;     /* for ISR */

    mmcsd_change(host);

    LOG_I("n32 sdio host registered as sd0");
    return RT_EOK;
}
INIT_DEVICE_EXPORT(n32_hw_sdio_init);

#endif /* RT_USING_SDIO */
