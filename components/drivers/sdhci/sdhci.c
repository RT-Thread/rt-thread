/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2020-09-27     zhujiale     first version
 */

#include <rtthread.h>
#include "sdhci.h"

static unsigned int debug_quirks = 0;
static unsigned int debug_quirks2;

static rt_bool_t sdhci_do_reset(struct sdhci_host *host, rt_uint8_t mask)
{
	if (host->quirks & SDHCI_QUIRK_NO_CARD_NO_RESET) {
		struct mmc_host *mmc = host->mmc;

		if (!mmc->ops->get_cd(mmc))
			return RT_FALSE;
	}

	host->ops->reset(host, mask);

	return RT_TRUE;
}


int sdhci_add_host(struct sdhci_host *host)
{
	int ret;

	ret = sdhci_setup_host(host);
	if (ret)
		return ret;

	ret = __sdhci_add_host(host);
	if (ret)
		goto cleanup;

	return 0;

cleanup:
	sdhci_cleanup_host(host);

	return ret;
}


static void sdhci_do_enable_v4_mode(struct sdhci_host *host)
{
	rt_uint16_t ctrl2;

	ctrl2 = sdhci_readw(host, SDHCI_HOST_CONTROL2);
	if (ctrl2 & SDHCI_CTRL_V4_MODE)
		return;

	ctrl2 |= SDHCI_CTRL_V4_MODE;
	sdhci_writew(host, ctrl2, SDHCI_HOST_CONTROL2);
}

static void sdhci_reset_for_all(struct sdhci_host *host)
{
	if (sdhci_do_reset(host, SDHCI_RESET_ALL)) {
		if (host->flags & (SDHCI_USE_SDMA | SDHCI_USE_ADMA)) {
			if (host->ops->enable_dma)
				host->ops->enable_dma(host);
		}
		/* Resetting the controller clears many */
		host->preset_enabled = RT_FALSE;
	}
}

void __sdhci_read_caps(struct sdhci_host *host, const rt_uint16_t *ver,
		       const rt_uint32_t *caps, const rt_uint32_t *caps1)
{
	rt_uint16_t v;
	rt_uint64_t dt_caps_mask = 0;
	rt_uint64_t dt_caps = 0;

	if (host->read_caps)
		return;

	host->read_caps = RT_TRUE;

	if (debug_quirks)
		host->quirks = debug_quirks;

	if (debug_quirks2)
		host->quirks2 = debug_quirks2;

	sdhci_reset_for_all(host);

	if (host->v4_mode)
		sdhci_do_enable_v4_mode(host);

	rt_ofw_prop_read_u64(mmc_dev(host->mmc),
				 "sdhci-caps-mask", &dt_caps_mask);
	rt_ofw_prop_read_u64(mmc_dev(host->mmc),
				 "sdhci-caps", &dt_caps);

	v = ver ? *ver : sdhci_readw(host, SDHCI_HOST_VERSION);
	host->version = (v & SDHCI_SPEC_VER_MASK) >> SDHCI_SPEC_VER_SHIFT;

	if (caps) {
		host->caps = *caps;
	} else {
		host->caps = sdhci_readl(host, SDHCI_CAPABILITIES);
		host->caps &= ~lower_32_bits(dt_caps_mask);
		host->caps |= lower_32_bits(dt_caps);
	}

	if (host->version < SDHCI_SPEC_300)
		return;

	if (caps1) {
		host->caps1 = *caps1;
	} else {
		host->caps1 = sdhci_readl(host, SDHCI_CAPABILITIES_1);
		host->caps1 &= ~upper_32_bits(dt_caps_mask);
		host->caps1 |= upper_32_bits(dt_caps);
	}
}

static inline rt_bool_t sdhci_can_64bit_dma(struct sdhci_host *host)
{
	/*
	 * According to SD Host Controller spec v4.10, bit[27] added from
	 * version 4.10 in Capabilities Register is used as 64-bit System
	 * Address support for V4 mode.
	 */
	if (host->version >= SDHCI_SPEC_410 && host->v4_mode)
		return host->caps & SDHCI_CAN_64BIT_V4;

	return host->caps & SDHCI_CAN_64BIT;
}

static int sdhci_set_dma_mask(struct sdhci_host *host)
{
	struct mmc_host *mmc = host->mmc;
	struct rt_device *dev = mmc_dev(mmc);
	int ret = -EINVAL;

	if (host->quirks2 & SDHCI_QUIRK2_BROKEN_64_BIT_DMA)
		host->flags &= ~SDHCI_USE_64_BIT_DMA;
#if 0
	/* Try 64-bit mask if hardware is capable  of it */
	if (host->flags & SDHCI_USE_64_BIT_DMA) {
		ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64));
		if (ret) {
			rt_kprintf("%s: Failed to set 64-bit DMA mask.\n",
				mmc_hostname(mmc));
			host->flags &= ~SDHCI_USE_64_BIT_DMA;
		}
	}

	/* 32-bit mask as default & fallback */
	if (ret) {
		ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
		if (ret)
			rt_kprintf("%s: Failed to set 32-bit DMA mask.\n",
				mmc_hostname(mmc));
	}
#endif
	return ret;
}

int sdhci_setup_host(struct sdhci_host *host)
{
	struct rt_mmcsd_host *mmc;
	size_t max_current_caps;
	unsigned int ocr_avail;
	unsigned int override_timeout_clk;
	size_t max_clk;
	int ret = 0;
	rt_bool_t enable_vqmmc = RT_FALSE;

	RT_ASSERT(host == NULL);
	if (host == NULL)
		return -EINVAL;

	mmc = host->mmc;
#if 0
	/*
	 * If there are external regulators, get them. Note this must be done
	 * early before resetting the host and reading the capabilities so that
	 * the host can take the appropriate action if regulators are not
	 * available.
	 */
	if (!mmc->supply.vqmmc) {
		ret = mmc_regulator_get_supply(mmc);
		if (ret)
			return ret;
		enable_vqmmc  = RT_TRUE;

	}
#endif

	LOG_D("Version:   0x%08x | Present:  0x%08x\n",
	    sdhci_readw(host, SDHCI_HOST_VERSION),
	    sdhci_readl(host, SDHCI_PRESENT_STATE));
	LOG_D("Caps:      0x%08x | Caps_1:   0x%08x\n",
	    sdhci_readl(host, SDHCI_CAPABILITIES),
	    sdhci_readl(host, SDHCI_CAPABILITIES_1));

	sdhci_read_caps(host);

	override_timeout_clk = host->timeout_clk;

	if (host->version > SDHCI_SPEC_420) {
		rt_kprintf("%s: Unknown controller version (%d). You may experience problems.\n",
		       mmc_hostname(mmc), host->version);
	}

	if (host->quirks & SDHCI_QUIRK_FORCE_DMA)
		host->flags |= SDHCI_USE_SDMA;
	else if (!(host->caps & SDHCI_CAN_DO_SDMA))
		LOG_D("Controller doesn't have SDMA capability\n");
	else
		host->flags |= SDHCI_USE_SDMA;

	if ((host->quirks & SDHCI_QUIRK_BROKEN_DMA) &&
		(host->flags & SDHCI_USE_SDMA)) {
		LOG_D("Disabling DMA as it is marked broken\n");
		host->flags &= ~SDHCI_USE_SDMA;
	}

	if ((host->version >= SDHCI_SPEC_200) &&
		(host->caps & SDHCI_CAN_DO_ADMA2))
		host->flags |= SDHCI_USE_ADMA;

	if ((host->quirks & SDHCI_QUIRK_BROKEN_ADMA) &&
		(host->flags & SDHCI_USE_ADMA)) {
		LOG_D("Disabling ADMA as it is marked broken\n");
		host->flags &= ~SDHCI_USE_ADMA;
	}

	if (sdhci_can_64bit_dma(host))
		host->flags |= SDHCI_USE_64_BIT_DMA;
#if 0
	if (host->use_external_dma) {
		ret = sdhci_external_dma_init(host);
		if (ret == -EPROBE_DEFER)
			goto unreg;
		/*
		 * Fall back to use the DMA/PIO integrated in standard SDHCI
		 * instead of external DMA devices.
		 */
		else if (ret)
			sdhci_switch_external_dma(host, RT_FALSE);
		/* Disable internal DMA sources */
		else
			host->flags &= ~(SDHCI_USE_SDMA | SDHCI_USE_ADMA);
	}
#endif
	if (host->flags & (SDHCI_USE_SDMA | SDHCI_USE_ADMA)) {
		if (host->ops->set_dma_mask)
			ret = host->ops->set_dma_mask(host);
		else
			ret = sdhci_set_dma_mask(host);

		if (!ret && host->ops->enable_dma)
			ret = host->ops->enable_dma(host);

		if (ret) {
			rt_kprintf("%s: No suitable DMA available - falling back to PIO\n",
				mmc_hostname(mmc));
			host->flags &= ~(SDHCI_USE_SDMA | SDHCI_USE_ADMA);

			ret = 0;
		}
	}

	/* SDMA does not support 64-bit DMA if v4 mode not set */
	if ((host->flags & SDHCI_USE_64_BIT_DMA) && !host->v4_mode)
		host->flags &= ~SDHCI_USE_SDMA;

	//our rtos did not need scatter-gather
#if 0
	if (host->flags & SDHCI_USE_ADMA) {
		rt_uint64_t dma;
		void *buf;

		if (!(host->flags & SDHCI_USE_64_BIT_DMA))
			host->alloc_desc_sz = SDHCI_ADMA2_32_DESC_SZ;
		else if (!host->alloc_desc_sz)
			host->alloc_desc_sz = SDHCI_ADMA2_64_DESC_SZ(host);

		host->desc_sz = host->alloc_desc_sz;
		host->adma_table_sz = host->adma_table_cnt * host->desc_sz;

		host->align_buffer_sz = SDHCI_MAX_SEGS * SDHCI_ADMA2_ALIGN;
		/*
		 * Use zalloc to zero the reserved high 32-bits of 128-bit
		 * descriptors so that they never need to be written.
		 */
		buf = dma_alloc_coherent(mmc_dev(mmc),
					 host->align_buffer_sz + host->adma_table_sz,
					 &dma, 0);
		if (!buf) {
			rt_kprintf("%s: Unable to allocate ADMA buffers - falling back to standard DMA\n",
				mmc_hostname(mmc));
			host->flags &= ~SDHCI_USE_ADMA;
		} else if ((dma + host->align_buffer_sz) &
			   (SDHCI_ADMA2_DESC_ALIGN - 1)) {
			rt_kprintf("%s: unable to allocate aligned ADMA descriptor\n",
				mmc_hostname(mmc));
			host->flags &= ~SDHCI_USE_ADMA;
			dma_free_coherent(mmc_dev(mmc), host->align_buffer_sz +
					  host->adma_table_sz, buf, dma);
		} else {
			host->align_buffer = buf;
			host->align_addr = dma;

			host->adma_table = buf + host->align_buffer_sz;
			host->adma_addr = dma + host->align_buffer_sz;
		}
	}
#endif
	/*
	 * If we use DMA, then it's up to the caller to set the DMA
	 * mask, but PIO does not need the hw shim so we set a new
	 * mask here in that case.
	 */
#if 0 
	if (!(host->flags & (SDHCI_USE_SDMA | SDHCI_USE_ADMA))) {
		host->dma_mask = DMA_BIT_MASK(64);
		mmc_dev(mmc)->dma_mask = &host->dma_mask;
	}
#endif
	if (host->version >= SDHCI_SPEC_300)
		host->max_clk = FIELD_GET(SDHCI_CLOCK_V3_BASE_MASK, host->caps);
	else
		host->max_clk = FIELD_GET(SDHCI_CLOCK_BASE_MASK, host->caps);

	host->max_clk *= 1000000;
	if (host->max_clk == 0 || host->quirks &
			SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN) {
		if (!host->ops->get_max_clock) {
			rt_kprintf("%s: Hardware doesn't specify base clock frequency.\n",
			       mmc_hostname(mmc));
			ret = -ENODEV;
			goto undma;
		}
		host->max_clk = host->ops->get_max_clock(host);
	}

	/*
	 * In case of Host Controller v3.00, find out whether clock
	 * multiplier is supported.
	 */
	host->clk_mul = FIELD_GET(SDHCI_CLOCK_MUL_MASK, host->caps1);

	/*
	 * In case the value in Clock Multiplier is 0, then programmable
	 * clock mode is not supported, otherwise the actual clock
	 * multiplier is one more than the value of Clock Multiplier
	 * in the Capabilities Register.
	 */
	if (host->clk_mul)
		host->clk_mul += 1;

	/*
	 * Set host parameters.
	 */
	max_clk = host->max_clk;

	if (host->ops->get_min_clock)
		mmc->f_min = host->ops->get_min_clock(host);
	else if (host->version >= SDHCI_SPEC_300) {
		if (host->clk_mul)
			max_clk = host->max_clk * host->clk_mul;
		/*
		 * Divided Clock Mode minimum clock rate is always less than
		 * Programmable Clock Mode minimum clock rate.
		 */
		mmc->f_min = host->max_clk / SDHCI_MAX_DIV_SPEC_300;
	} else
		mmc->f_min = host->max_clk / SDHCI_MAX_DIV_SPEC_200;

	if (!mmc->f_max || mmc->f_max > max_clk)
		mmc->f_max = max_clk;

	if (!(host->quirks & SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK)) {
		host->timeout_clk = FIELD_GET(SDHCI_TIMEOUT_CLK_MASK, host->caps);

		if (host->caps & SDHCI_TIMEOUT_CLK_UNIT)
			host->timeout_clk *= 1000;

		if (host->timeout_clk == 0) {
			if (!host->ops->get_timeout_clock) {
				rt_kprintf("%s: Hardware doesn't specify timeout clock frequency.\n",
					mmc_hostname(mmc));
				ret = -ENODEV;
				goto undma;
			}

			host->timeout_clk =
				DIV_ROUND_UP(host->ops->get_timeout_clock(host),
					     1000);
		}

		if (override_timeout_clk)
			host->timeout_clk = override_timeout_clk;

		mmc->max_busy_timeout = host->ops->get_max_timeout_count ?
			host->ops->get_max_timeout_count(host) : 1 << 27;
		mmc->max_busy_timeout /= host->timeout_clk;
	}

	if (host->quirks2 & SDHCI_QUIRK2_DISABLE_HW_TIMEOUT &&
	    !host->ops->get_max_timeout_count)
		mmc->max_busy_timeout = 0;

	mmc->caps |= MMC_CAP_SDIO_IRQ | MMC_CAP_CMD23;
	mmc->caps2 |= MMC_CAP2_SDIO_IRQ_NOTHREAD;

	if (host->quirks & SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12)
		host->flags |= SDHCI_AUTO_CMD12;

	/*
	 * For v3 mode, Auto-CMD23 stuff only works in ADMA or PIO.
	 * For v4 mode, SDMA may use Auto-CMD23 as well.
	 */
	if ((host->version >= SDHCI_SPEC_300) &&
	    ((host->flags & SDHCI_USE_ADMA) ||
	     !(host->flags & SDHCI_USE_SDMA) || host->v4_mode) &&
	     !(host->quirks2 & SDHCI_QUIRK2_ACMD23_BROKEN)) {
		host->flags |= SDHCI_AUTO_CMD23;
		LOG_D("Auto-CMD23 available\n");
	} else {
		LOG_D("Auto-CMD23 unavailable\n");
	}

	/*
	 * A controller may support 8-bit width, but the board itself
	 * might not have the pins brought out.  Boards that support
	 * 8-bit width must set "mmc->caps |= MMC_CAP_8_BIT_DATA;" in
	 * their platform code before calling sdhci_add_host(), and we
	 * won't assume 8-bit width for hosts without that CAP.
	 */
	if (!(host->quirks & SDHCI_QUIRK_FORCE_1_BIT_DATA))
		mmc->caps |= MMC_CAP_4_BIT_DATA;

	if (host->quirks2 & SDHCI_QUIRK2_HOST_NO_CMD23)
		mmc->caps &= ~MMC_CAP_CMD23;

	if (host->caps & SDHCI_CAN_DO_HISPD)
		mmc->caps |= MMC_CAP_SD_HIGHSPEED | MMC_CAP_MMC_HIGHSPEED;
#if 0
	if ((host->quirks & SDHCI_QUIRK_BROKEN_CARD_DETECTION) &&
	    mmc_card_is_removable(mmc) &&
	    mmc_gpio_get_cd(mmc) < 0)
		mmc->caps |= MMC_CAP_NEEDS_POLL;

	if (!IS_ERR(mmc->supply.vqmmc)) {
		if (enable_vqmmc) {
			ret = regulator_enable(mmc->supply.vqmmc);
			host->sdhci_core_to_disable_vqmmc = !ret;
		}

		/* If vqmmc provides no 1.8V signalling, then there's no UHS */
		if (!regulator_is_supported_voltage(mmc->supply.vqmmc, 1700000,
						    1950000))
			host->caps1 &= ~(SDHCI_SUPPORT_SDR104 |
					 SDHCI_SUPPORT_SDR50 |
					 SDHCI_SUPPORT_DDR50);

		/* In eMMC case vqmmc might be a fixed 1.8V regulator */
		if (!regulator_is_supported_voltage(mmc->supply.vqmmc, 2700000,
						    3600000))
			host->flags &= ~SDHCI_SIGNALING_330;

		if (ret) {
			rt_kprintf("%s: Failed to enable vqmmc regulator: %d\n",
				mmc_hostname(mmc), ret);
			mmc->supply.vqmmc = ERR_PTR(-EINVAL);
		}

	}
#endif
	if (host->quirks2 & SDHCI_QUIRK2_NO_1_8_V) {
		host->caps1 &= ~(SDHCI_SUPPORT_SDR104 | SDHCI_SUPPORT_SDR50 |
				 SDHCI_SUPPORT_DDR50);
		/*
		 * The SDHCI controller in a SoC might support HS200/HS400
		 * (indicated using mmc-hs200-1_8v/mmc-hs400-1_8v dt property),
		 * but if the board is modeled such that the IO lines are not
		 * connected to 1.8v then HS200/HS400 cannot be supported.
		 * Disable HS200/HS400 if the board does not have 1.8v connected
		 * to the IO lines. (Applicable for other modes in 1.8v)
		 */
		mmc->caps2 &= ~(MMC_CAP2_HSX00_1_8V | MMC_CAP2_HS400_ES);
		mmc->caps &= ~(MMC_CAP_1_8V_DDR | MMC_CAP_UHS);
	}

	/* Any UHS-I mode in caps implies SDR12 and SDR25 support. */
	if (host->caps1 & (SDHCI_SUPPORT_SDR104 | SDHCI_SUPPORT_SDR50 |
			   SDHCI_SUPPORT_DDR50))
		mmc->caps |= MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25;

	/* SDR104 supports also implies SDR50 support */
	if (host->caps1 & SDHCI_SUPPORT_SDR104) {
		mmc->caps |= MMC_CAP_UHS_SDR104 | MMC_CAP_UHS_SDR50;
		/* SD3.0: SDR104 is supported so (for eMMC) the caps2
		 * field can be promoted to support HS200.
		 */
		if (!(host->quirks2 & SDHCI_QUIRK2_BROKEN_HS200))
			mmc->caps2 |= MMC_CAP2_HS200;
	} else if (host->caps1 & SDHCI_SUPPORT_SDR50) {
		mmc->caps |= MMC_CAP_UHS_SDR50;
	}

	if (host->quirks2 & SDHCI_QUIRK2_CAPS_BIT63_FOR_HS400 &&
	    (host->caps1 & SDHCI_SUPPORT_HS400))
		mmc->caps2 |= MMC_CAP2_HS400;
#if 0
	if ((mmc->caps2 & MMC_CAP2_HSX00_1_2V) &&
	    (IS_ERR(mmc->supply.vqmmc) ||
	     !regulator_is_supported_voltage(mmc->supply.vqmmc, 1100000,
					     1300000)))
		mmc->caps2 &= ~MMC_CAP2_HSX00_1_2V;
#endif
	if ((host->caps1 & SDHCI_SUPPORT_DDR50) &&
	    !(host->quirks2 & SDHCI_QUIRK2_BROKEN_DDR50))
		mmc->caps |= MMC_CAP_UHS_DDR50;

	/* Does the host need tuning for SDR50? */
	if (host->caps1 & SDHCI_USE_SDR50_TUNING)
		host->flags |= SDHCI_SDR50_NEEDS_TUNING;

	/* Driver Type(s) (A, C, D) supported by the host */
	if (host->caps1 & SDHCI_DRIVER_TYPE_A)
		mmc->caps |= MMC_CAP_DRIVER_TYPE_A;
	if (host->caps1 & SDHCI_DRIVER_TYPE_C)
		mmc->caps |= MMC_CAP_DRIVER_TYPE_C;
	if (host->caps1 & SDHCI_DRIVER_TYPE_D)
		mmc->caps |= MMC_CAP_DRIVER_TYPE_D;

	/* Initial value for re-tuning timer count */
	host->tuning_count = FIELD_GET(SDHCI_RETUNING_TIMER_COUNT_MASK,
				       host->caps1);

	/*
	 * In case Re-tuning Timer is not disabled, the actual value of
	 * re-tuning timer will be 2 ^ (n - 1).
	 */
	if (host->tuning_count)
		host->tuning_count = 1 << (host->tuning_count - 1);

	/* Re-tuning mode supported by the Host Controller */
	host->tuning_mode = FIELD_GET(SDHCI_RETUNING_MODE_MASK, host->caps1);

	ocr_avail = 0;

	/*
	 * According to SD Host Controller spec v3.00, if the Host System
	 * can afford more than 150mA, Host Driver should set XPC to 1. Also
	 * the value is meaningful only if Voltage Support in the Capabilities
	 * register is set. The actual current value is 4 times the register
	 * value.
	 */
	max_current_caps = sdhci_readl(host, SDHCI_MAX_CURRENT);
#if 0 
	if (!max_current_caps && !IS_ERR(mmc->supply.vmmc)) {
		int curr = regulator_get_current_limit(mmc->supply.vmmc);
		if (curr > 0) {

			/* convert to SDHCI_MAX_CURRENT format */
			curr = curr/1000;  /* convert to mA */
			curr = curr/SDHCI_MAX_CURRENT_MULTIPLIER;

			curr = min_t(rt_uint32_t, curr, SDHCI_MAX_CURRENT_LIMIT);
			max_current_caps =
				FIELD_PREP(SDHCI_MAX_CURRENT_330_MASK, curr) |
				FIELD_PREP(SDHCI_MAX_CURRENT_300_MASK, curr) |
				FIELD_PREP(SDHCI_MAX_CURRENT_180_MASK, curr);
		}
	}
#endif
	if (host->caps & SDHCI_CAN_VDD_330) {
		ocr_avail |= MMC_VDD_32_33 | MMC_VDD_33_34;

		mmc->max_current_330 = FIELD_GET(SDHCI_MAX_CURRENT_330_MASK,
						 max_current_caps) *
						SDHCI_MAX_CURRENT_MULTIPLIER;
	}
	if (host->caps & SDHCI_CAN_VDD_300) {
		ocr_avail |= MMC_VDD_29_30 | MMC_VDD_30_31;

		mmc->max_current_300 = FIELD_GET(SDHCI_MAX_CURRENT_300_MASK,
						 max_current_caps) *
						SDHCI_MAX_CURRENT_MULTIPLIER;
	}
	if (host->caps & SDHCI_CAN_VDD_180) {
		ocr_avail |= MMC_VDD_165_195;

		mmc->max_current_180 = FIELD_GET(SDHCI_MAX_CURRENT_180_MASK,
						 max_current_caps) *
						SDHCI_MAX_CURRENT_MULTIPLIER;
	}

	/* If OCR set by host, use it instead. */
	if (host->ocr_mask)
		ocr_avail = host->ocr_mask;

	/* If OCR set by external regulators, give it highest prio. */
	if (mmc->ocr_avail)
		ocr_avail = mmc->ocr_avail;

	mmc->ocr_avail = ocr_avail;
	mmc->ocr_avail_sdio = ocr_avail;
	if (host->ocr_avail_sdio)
		mmc->ocr_avail_sdio &= host->ocr_avail_sdio;
	mmc->ocr_avail_sd = ocr_avail;
	if (host->ocr_avail_sd)
		mmc->ocr_avail_sd &= host->ocr_avail_sd;
	else /* normal SD controllers don't support 1.8V */
		mmc->ocr_avail_sd &= ~MMC_VDD_165_195;
	mmc->ocr_avail_mmc = ocr_avail;
	if (host->ocr_avail_mmc)
		mmc->ocr_avail_mmc &= host->ocr_avail_mmc;

	if (mmc->ocr_avail == 0) {
		rt_kprintf("%s: Hardware doesn't report any support voltages.\n",
		       mmc_hostname(mmc));
		ret = -ENODEV;
		goto unreg;
	}

	if ((mmc->caps & (MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25 |
			  MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_SDR104 |
			  MMC_CAP_UHS_DDR50 | MMC_CAP_1_8V_DDR)) ||
	    (mmc->caps2 & (MMC_CAP2_HS200_1_8V_SDR | MMC_CAP2_HS400_1_8V)))
		host->flags |= SDHCI_SIGNALING_180;

	if (mmc->caps2 & MMC_CAP2_HSX00_1_2V)
		host->flags |= SDHCI_SIGNALING_120;

	rt_spin_lock_init(&host->lock);

	/*
	 * Maximum number of sectors in one transfer. Limited by SDMA boundary
	 * size (512KiB). Note some tuning modes impose a 4MiB limit, but this
	 * is less anyway.
	 */
	mmc->max_req_size = 524288;

	/*
	 * Maximum number of segments. Depends on if the hardware
	 * can do scatter/gather or not.
	 */
	if (host->flags & SDHCI_USE_ADMA) {
		mmc->max_segs = SDHCI_MAX_SEGS;
	} else if (host->flags & SDHCI_USE_SDMA) {
		mmc->max_segs = 1;
	} else { /* PIO */
		mmc->max_segs = SDHCI_MAX_SEGS;
	}
	/*
	 * Maximum segment size. Could be one segment with the maximum number
	 * of bytes. When doing hardware scatter/gather, each entry cannot
	 * be larger than 64 KiB though.
	 */
	if (host->flags & SDHCI_USE_ADMA) {
		if (host->quirks & SDHCI_QUIRK_BROKEN_ADMA_ZEROLEN_DESC) {
			host->max_adma = 65532; /* 32-bit alignment */
			mmc->max_seg_size = 65535;
		} else {
			mmc->max_seg_size = 65536;
		}
	} else {
		mmc->max_seg_size = mmc->max_req_size;
	}

	/*
	 * Maximum block size. This varies from controller to controller and
	 * is specified in the capabilities register.
	 */
	if (host->quirks & SDHCI_QUIRK_FORCE_BLK_SZ_2048) {
		mmc->max_blk_size = 2;
	} else {
		mmc->max_blk_size = (host->caps & SDHCI_MAX_BLOCK_MASK) >>
				SDHCI_MAX_BLOCK_SHIFT;
		if (mmc->max_blk_size >= 3) {
			rt_kprintf("%s: Invalid maximum block size, assuming 512 bytes\n",
				mmc_hostname(mmc));
			mmc->max_blk_size = 0;
		}
	}

	mmc->max_blk_size = 512 << mmc->max_blk_size;

	/*
	 * Maximum block count.
	 */
	mmc->max_blk_count = (host->quirks & SDHCI_QUIRK_NO_MULTIBLOCK) ? 1 : 65535;
#if 0
	if (mmc->max_segs == 1)
		/* This may alter mmc->*_blk_* parameters */
		sdhci_allocate_bounce_buffer(host);
#endif
	return 0;

unreg:
#if 0
	if (host->sdhci_core_to_disable_vqmmc)
		regulator_disable(mmc->supply.vqmmc);
#endif
undma:
	if (host->align_buffer)
		dma_free_coherent(mmc_dev(mmc), host->align_buffer_sz +
				  host->adma_table_sz, host->align_buffer,
				  host->align_addr);
	host->adma_table = NULL;
	host->align_buffer = NULL;

	return ret;
}

void sdhci_cleanup_host(struct sdhci_host *host)
{
	struct mmc_host *mmc = host->mmc;
#if 0
	if (host->sdhci_core_to_disable_vqmmc)
		regulator_disable(mmc->supply.vqmmc);
#endif
	if (host->align_buffer)
		dma_free_coherent(mmc_dev(mmc), host->align_buffer_sz +
				  host->adma_table_sz, host->align_buffer,
				  host->align_addr);

	if (host->use_external_dma)
		sdhci_external_dma_release(host);

	host->adma_table = NULL;
	host->align_buffer = NULL;
}

static rt_bool_t sdhci_needs_reset(struct sdhci_host *host, struct rt_mmcsd_req *mrq)
{
	return (!(host->flags & SDHCI_DEVICE_DEAD) &&
		((mrq->cmd && mrq->cmd->err) ||
		 (mrq->sbc && mrq->sbc->err) ||
		 (mrq->data && mrq->data->stop && mrq->data->stop->err) ||
		 (host->quirks & SDHCI_QUIRK_RESET_AFTER_REQUEST)));
}

static void sdhci_set_default_irqs(struct sdhci_host *host)
{
	host->ier = SDHCI_INT_BUS_POWER | SDHCI_INT_DATA_END_BIT |
		    SDHCI_INT_DATA_CRC | SDHCI_INT_DATA_TIMEOUT |
		    SDHCI_INT_INDEX | SDHCI_INT_END_BIT | SDHCI_INT_CRC |
		    SDHCI_INT_TIMEOUT | SDHCI_INT_DATA_END |
		    SDHCI_INT_RESPONSE;

	if (host->tuning_mode == SDHCI_TUNING_MODE_2 ||
	    host->tuning_mode == SDHCI_TUNING_MODE_3)
		host->ier |= SDHCI_INT_RETUNE;

	sdhci_writel(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_writel(host, host->ier, SDHCI_SIGNAL_ENABLE);
}


static void sdhci_init(struct sdhci_host *host, int soft)
{
	struct mmc_host *mmc = host->mmc;
	unsigned long flags;

	if (soft)
        sdhci_do_reset(host, SDHCI_RESET_CMD | SDHCI_RESET_DATA);
    else
        sdhci_do_reset(host, SDHCI_RESET_ALL);

	if (host->v4_mode)
		sdhci_do_enable_v4_mode(host);

	rt_spin_lock_irqsave(&host->lock);
	sdhci_set_default_irqs(host);
	rt_spin_unlock_irqrestore(&host->lock,1);

	host->cqe_on = RT_FALSE;

	if (soft) {
		/* force clock reconfiguration */
		host->clock = 0;
		host->reinit_uhs = RT_TRUE;
		mmc->ops->set_ios(mmc, &mmc->ios);
	}
}

static void sdhci_runtime_pm_bus_off(struct sdhci_host *host)
{
    if (!host->bus_on)
        return;
    host->bus_on = RT_FALSE;
#if 0
    pm_runtime_put_noidle(host->mmc->parent);
#endif
}

void sdhci_reset(struct sdhci_host* host, rt_uint8_t mask)
{
	ssize_t timeout;

	sdhci_writeb(host, mask, SDHCI_SOFTWARE_RESET);

	if (mask & SDHCI_RESET_ALL) {
		host->clock = 0;
		/* Reset-all turns off SD Bus Power */
		if (host->quirks2 & SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON)
			sdhci_runtime_pm_bus_off(host);
	}

	/* Wait max 100 ms */
	timeout = ktime_add_ms(ktime_get(), 100);

	/* hw clears the bit when it's done */
	while (1) {
		rt_bool_t timedout = ktime_after(ktime_get(), timeout);

		if (!(sdhci_readb(host, SDHCI_SOFTWARE_RESET) & mask))
			break;
		if (timedout) {
			rt_kprintf("%s: Reset 0x%x never completed.\n",
				mmc_hostname(host->mmc), (int)mask);
			sdhci_err_stats_inc(host, CTRL_TIMEOUT);
			sdhci_dumpregs(host);
			return;
		}
		udelay(10);
	}
}

int __sdhci_add_host(struct sdhci_host *host)
{
		struct mmc_host *mmc = host->mmc;
	int ret;

	if ((mmc->caps2 & MMC_CAP2_CQE) &&
	    (host->quirks & SDHCI_QUIRK_BROKEN_CQE)) {
		mmc->caps2 &= ~MMC_CAP2_CQE;
		mmc->cqe_ops = NULL;
	}

	host->complete_wq = rt_workqueue_create("sdhci", 4096, 20);
	if (!host->complete_wq)
		return -ENOMEM;

	rt_work_init(&host->complete_work, sdhci_complete_work,host);

	rt_timer_init(&host->timer,"sdhci_timer", sdhci_timeout_timer, host,0,RT_TIMER_FLAG_SOFT_TIMER);
	rt_timer_init(&host->data_timer, "sdhci_data_timer",sdhci_timeout_data_timer,host ,0,RT_TIMER_FLAG_SOFT_TIMER);

	rt_wqueue_init(&host->buf_ready_int);

	sdhci_init(host, 0);


    host->irq_wq = rt_workqueue_create("sdhci_irq",8192,1);
    rt_work_init(&host->irq_work,sdhci_thread_irq,host);
	ret = rt_hw_interrupt_install(host->irq, sdhci_irq,host, mmc_hostname(mmc));
	if (ret) {
		rt_kprintf("%s: Failed to request IRQ %d: %d\n",
		       mmc_hostname(mmc), host->irq, ret);
		goto unwq;
	}

	ret = mmc_add_host(mmc);
	if (ret)
		goto unirq;

	rt_kprintf("%s: SDHCI controller on %s [%s] using %s\n",
		mmc_hostname(mmc), host->hw_name, dev_name(mmc_dev(mmc)),
		host->use_external_dma ? "External DMA" :
		(host->flags & SDHCI_USE_ADMA) ?
		(host->flags & SDHCI_USE_64_BIT_DMA) ? "ADMA 64-bit" : "ADMA" :
		(host->flags & SDHCI_USE_SDMA) ? "DMA" : "PIO");

	sdhci_enable_card_detection(host);

	return 0;

unirq:
	sdhci_reset_for_all(host);
	sdhci_writel(host, 0, SDHCI_INT_ENABLE);
	sdhci_writel(host, 0, SDHCI_SIGNAL_ENABLE);
	// free_irq(host->irq, host);
unwq:
	rt_workqueue_destroy(host->complete_wq);
    rt_workqueue_destroy(host->irq_wq);

	return ret;
}

static void sdhci_enable_card_detection(struct sdhci_host *host)
{
	sdhci_set_card_detection(host, RT_TRUE);
}


static void sdhci_set_card_detection(struct sdhci_host *host, rt_bool_t enable)
{
	rt_uint32_t present;

	if ((host->quirks & SDHCI_QUIRK_BROKEN_CARD_DETECTION) ||
	    !mmc_card_is_removable(host->mmc))
		return;

	if (enable) {
		present = sdhci_readl(host, SDHCI_PRESENT_STATE) &
				      SDHCI_CARD_PRESENT;

		host->ier |= present ? SDHCI_INT_CARD_REMOVE :
				       SDHCI_INT_CARD_INSERT;
	} else {
		host->ier &= ~(SDHCI_INT_CARD_REMOVE | SDHCI_INT_CARD_INSERT);
	}

	sdhci_writel(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_writel(host, host->ier, SDHCI_SIGNAL_ENABLE);
}

// #if IS_ENABLED(CONFIG_MMC_SDHCI_EXTERNAL_DMA)

// static int sdhci_external_dma_init(struct sdhci_host *host)
// {
// 	int ret = 0;
// 	struct mmc_host *mmc = host->mmc;

// 	host->tx_chan = dma_request_chan(mmc_dev(mmc), "tx");
// 	if (IS_ERR(host->tx_chan)) {
// 		ret = PTR_ERR(host->tx_chan);
// 		if (ret != -EPROBE_DEFER)
// 			pr_warn("Failed to request TX DMA channel.\n");
// 		host->tx_chan = NULL;
// 		return ret;
// 	}

// 	host->rx_chan = dma_request_chan(mmc_dev(mmc), "rx");
// 	if (IS_ERR(host->rx_chan)) {
// 		if (host->tx_chan) {
// 			dma_release_channel(host->tx_chan);
// 			host->tx_chan = NULL;
// 		}

// 		ret = PTR_ERR(host->rx_chan);
// 		if (ret != -EPROBE_DEFER)
// 			pr_warn("Failed to request RX DMA channel.\n");
// 		host->rx_chan = NULL;
// 	}

// 	return ret;
// }

// static struct dma_chan *sdhci_external_dma_channel(struct sdhci_host *host,
// 						   struct rt_mmcsd_data *data)
// {
// 	return data->flags & MMC_DATA_WRITE ? host->tx_chan : host->rx_chan;
// }

// static int sdhci_external_dma_setup(struct sdhci_host *host,
// 				    struct rt_mmcsd_cmd *cmd)
// {
// 	int ret, i;
// 	enum dma_transfer_direction dir;
// 	struct dma_async_tx_descriptor *desc;
// 	struct rt_mmcsd_data *data = cmd->data;
// 	struct dma_chan *chan;
// 	struct dma_slave_config cfg;
// 	dma_cookie_t cookie;
// 	int sg_cnt;

// 	if (!host->mapbase)
// 		return -EINVAL;

// 	memset(&cfg, 0, sizeof(cfg));
// 	cfg.src_addr = host->mapbase + SDHCI_BUFFER;
// 	cfg.dst_addr = host->mapbase + SDHCI_BUFFER;
// 	cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
// 	cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
// 	cfg.src_maxburst = data->blksz / 4;
// 	cfg.dst_maxburst = data->blksz / 4;

// 	/* Sanity check: all the SG entries must be aligned by block size. */
// 	for (i = 0; i < data->sg_len; i++) {
// 		if ((data->sg + i)->length % data->blksz)
// 			return -EINVAL;
// 	}

// 	chan = sdhci_external_dma_channel(host, data);

// 	ret = dmaengine_slave_config(chan, &cfg);
// 	if (ret)
// 		return ret;

// 	sg_cnt = sdhci_pre_dma_transfer(host, data, COOKIE_MAPPED);
// 	if (sg_cnt <= 0)
// 		return -EINVAL;

// 	dir = data->flags & MMC_DATA_WRITE ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM;
// 	desc = dmaengine_prep_slave_sg(chan, data->sg, data->sg_len, dir,
// 				       DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
// 	if (!desc)
// 		return -EINVAL;

// 	desc->callback = NULL;
// 	desc->callback_param = NULL;

// 	cookie = dmaengine_submit(desc);
// 	if (dma_submit_error(cookie))
// 		ret = cookie;

// 	return ret;
// }

// static void sdhci_external_dma_release(struct sdhci_host *host)
// {
// 	if (host->tx_chan) {
// 		dma_release_channel(host->tx_chan);
// 		host->tx_chan = NULL;
// 	}

// 	if (host->rx_chan) {
// 		dma_release_channel(host->rx_chan);
// 		host->rx_chan = NULL;
// 	}

// 	sdhci_switch_external_dma(host, false);
// }

// static void __sdhci_external_dma_prepare_data(struct sdhci_host *host,
// 					      struct rt_mmcsd_cmd *cmd)
// {
// 	struct rt_mmcsd_data *data = cmd->data;

// 	sdhci_initialize_data(host, data);

// 	host->flags |= SDHCI_REQ_USE_DMA;
// 	sdhci_set_transfer_irqs(host);

// 	sdhci_set_block_info(host, data);
// }

// static void sdhci_external_dma_prepare_data(struct sdhci_host *host,
// 					    struct rt_mmcsd_cmd *cmd)
// {
// 	if (!sdhci_external_dma_setup(host, cmd)) {
// 		__sdhci_external_dma_prepare_data(host, cmd);
// 	} else {
// 		sdhci_external_dma_release(host);
// 		pr_err("%s: Cannot use external DMA, switch to the DMA/PIO which standard SDHCI provides.\n",
// 		       mmc_hostname(host->mmc));
// 		sdhci_prepare_data(host, cmd);
// 	}
// }

// static void sdhci_external_dma_pre_transfer(struct sdhci_host *host,
// 					    struct rt_mmcsd_cmd *cmd)
// {
// 	struct dma_chan *chan;

// 	if (!cmd->data)
// 		return;

// 	chan = sdhci_external_dma_channel(host, cmd->data);
// 	if (chan)
// 		dma_async_issue_pending(chan);
// }

// #else

static inline int sdhci_external_dma_init(struct sdhci_host *host)
{
	return -EOPNOTSUPP;
}

static inline void sdhci_external_dma_release(struct sdhci_host *host)
{
}

static inline void sdhci_external_dma_prepare_data(struct sdhci_host *host,
						   struct rt_mmcsd_cmd *cmd)
{
	/* This should never happen */
}

static inline void sdhci_external_dma_pre_transfer(struct sdhci_host *host,
						   struct rt_mmcsd_cmd *cmd)
{
}

static inline struct dma_chan *sdhci_external_dma_channel(struct sdhci_host *host,
							  struct rt_mmcsd_data *data)
{
	return NULL;
}

// #endif

static void sdhci_set_mrq_done(struct sdhci_host *host, struct rt_mmcsd_req *mrq)
{
	int i;

	for (i = 0; i < SDHCI_MAX_MRQS; i++) {
		if (host->mrqs_done[i] == mrq) {
			LOG_D(1);
			return;
		}
	}

	for (i = 0; i < SDHCI_MAX_MRQS; i++) {
		if (!host->mrqs_done[i]) {
			host->mrqs_done[i] = mrq;
			break;
		}
	}

	LOG_D(i >= SDHCI_MAX_MRQS);
}

static inline rt_bool_t sdhci_defer_done(struct sdhci_host *host,
				    struct rt_mmcsd_req *mrq)
{
	struct rt_mmcsd_data *data = mrq->data;

	return host->pending_reset || host->always_defer_done ||
	       ((host->flags & SDHCI_REQ_USE_DMA) && data &&
		data->host_cookie == COOKIE_MAPPED);
}

/********************************************************* */
/*                       data                              */
/********************************************************* */

/********************************************************* */
/*                        pio                              */
/********************************************************* */
static void sdhci_transfer_pio(struct sdhci_host *host)
{
	rt_uint32_t mask;

	if (host->blocks == 0)
		return;

	if (host->data->flags & DATA_DIR_READ)
		mask = SDHCI_DATA_AVAILABLE;
	else
		mask = SDHCI_SPACE_AVAILABLE;

	/*
	 * Some controllers (JMicron JMB38x) mess up the buffer bits
	 * for transfers < 4 bytes. As long as it is just one block,
	 * we can ignore the bits.
	 */
	if ((host->quirks & SDHCI_QUIRK_BROKEN_SMALL_PIO) &&
		(host->data->blks == 1))
		{
		mask = ~0;
		}
	while (sdhci_readl(host, SDHCI_PRESENT_STATE) & mask) {
		if (host->quirks & SDHCI_QUIRK_PIO_NEEDS_DELAY)
			rt_hw_us_delay(100);

		if (host->data->flags & DATA_DIR_READ)
			sdhci_read_block_pio(host);
		else
			sdhci_write_block_pio(host);

		host->blocks--;
		if (host->blocks == 0)
			break;
	}

}

static void sdhci_read_block_pio(struct sdhci_host *host)
{
	rt_uint32_t scratch;  
    size_t len;  
	rt_uint32_t *buf;
	buf = host->data->buf;
	int blksize = host->data->blksize;
    while (blksize) {  
        len = min(4U, blksize); 
  
        scratch = sdhci_readl(host, SDHCI_BUFFER);  
  
        memcpy(buf, &scratch, len);  
  
        buf += len;  
        blksize -= len;  
    }  

}

static void sdhci_write_block_pio(struct sdhci_host *host)
{
	size_t blksize, len, chunk;
	rt_uint32_t scratch;
	rt_uint32_t *buf;

	LOG_D("PIO writing\n");

	blksize = host->data->blksize;
	chunk = 0;
	scratch = 0;
	buf = host->data->buf;
	while (blksize) {
		len = min(4U, blksize); 
		memcpy(&scratch,buf,len);
		buf += len;	
		blksize -=len;		
		sdhci_writel(host, scratch, SDHCI_BUFFER);
	
	}

}

/********************************************************* */
/*                        cmd                              */
/********************************************************* */

static inline void sdhci_auto_cmd_select(struct sdhci_host *host,
					 struct rt_mmcsd_cmd *cmd,
					 rt_uint16_t *mode)
{
	rt_bool_t use_cmd12 = sdhci_auto_cmd12(host, cmd->mrq) &&
			 (cmd->cmd_code != SD_IO_RW_EXTENDED);
	rt_bool_t use_cmd23 = sdhci_auto_cmd23(host, cmd->mrq);
	rt_uint16_t ctrl2;

	/*
	 * In case of Version 4.10 or later, use of 'Auto CMD Auto
	 * Select' is recommended rather than use of 'Auto CMD12
	 * Enable' or 'Auto CMD23 Enable'. We require Version 4 Mode
	 * here because some controllers (e.g sdhci-of-dwmshc) expect it.
	 */
	if (host->version >= SDHCI_SPEC_410 && host->v4_mode &&
	    (use_cmd12 || use_cmd23)) {
		*mode |= SDHCI_TRNS_AUTO_SEL;

		ctrl2 = sdhci_readw(host, SDHCI_HOST_CONTROL2);
		if (use_cmd23)
			ctrl2 |= SDHCI_CMD23_ENABLE;
		else
			ctrl2 &= ~SDHCI_CMD23_ENABLE;
		sdhci_writew(host, ctrl2, SDHCI_HOST_CONTROL2);

		return;
	}

	/*
	 * If we are sending CMD23, CMD12 never gets sent
	 * on successful completion (so no Auto-CMD12).
	 */
	if (use_cmd12)
		*mode |= SDHCI_TRNS_AUTO_CMD12;
	else if (use_cmd23)
		*mode |= SDHCI_TRNS_AUTO_CMD23;
}

static inline rt_bool_t sdhci_auto_cmd23(struct sdhci_host *host,
				    struct rt_mmcsd_req *mrq)
{
	return mrq->sbc && (host->flags & SDHCI_AUTO_CMD23);
}

static inline rt_bool_t sdhci_auto_cmd12(struct sdhci_host *host,
                    struct rt_mmcsd_req *mrq)
{
    return !mrq->sbc && (host->flags & SDHCI_AUTO_CMD12) &&
           !mrq->cap_cmd_during_tfr;
}

static inline rt_bool_t sdhci_data_line_cmd(struct rt_mmcsd_cmd *cmd)
{
	return cmd->data || cmd->flags & MMC_RSP_BUSY;
}

/********************************************************* */
/*                        dma                              */
/********************************************************* */
//our rtos did not need sg
#if 0
static int sdhci_pre_dma_transfer(struct sdhci_host *host,
				  struct mmc_data *data, int cookie)
{
	int sg_count;

	/*
	 * If the data buffers are already mapped, return the previous
	 * dma_map_sg() result.
	 */
	if (data->host_cookie == COOKIE_PRE_MAPPED)
		return data->sg_count;

	/* Bounce write requests to the bounce buffer */
	if (host->bounce_buffer) {
		unsigned int length = data->blksz * data->blocks;

		if (length > host->bounce_buffer_size) {
			pr_err("%s: asked for transfer of %u bytes exceeds bounce buffer %u bytes\n",
			       mmc_hostname(host->mmc), length,
			       host->bounce_buffer_size);
			return -EIO;
		}
		if (mmc_get_dma_dir(data) == DMA_TO_DEVICE) {
			/* Copy the data to the bounce buffer */
			if (host->ops->copy_to_bounce_buffer) {
				host->ops->copy_to_bounce_buffer(host,
								 data, length);
			} else {
				sg_copy_to_buffer(data->sg, data->sg_len,
						  host->bounce_buffer, length);
			}
		}
		/* Switch ownership to the DMA */
		dma_sync_single_for_device(mmc_dev(host->mmc),
					   host->bounce_addr,
					   host->bounce_buffer_size,
					   mmc_get_dma_dir(data));
		/* Just a dummy value */
		sg_count = 1;
	} else {
		/* Just access the data directly from memory */
		sg_count = dma_map_sg(mmc_dev(host->mmc),
				      data->sg, data->sg_len,
				      mmc_get_dma_dir(data));
	}

	if (sg_count == 0)
		return -ENOSPC;

	data->sg_count = sg_count;
	data->host_cookie = cookie;

	return sg_count;
}


static void sdhci_adma_table_pre(struct sdhci_host *host,
	struct mmc_data *data, int sg_count)
{
	struct scatterlist *sg;
	unsigned long addr, align_addr;
	void *desc, *align;
	char *buffer;
	int len, offset, i;

	/*
	 * The spec does not specify endianness of descriptor table.
	 * We currently guess that it is LE.
	 */

	host->sg_count = sg_count;

	desc = host->adma_table;
	align = host->align_buffer;

	align_addr = host->align_addr;

	for_each_sg(data->sg, sg, host->sg_count, i) {
		addr = sg_dma_address(sg);
		len = sg_dma_len(sg);

		/*
		 * The SDHCI specification states that ADMA addresses must
		 * be 32-bit aligned. If they aren't, then we use a bounce
		 * buffer for the (up to three) bytes that screw up the
		 * alignment.
		 */
		offset = (SDHCI_ADMA2_ALIGN - (addr & SDHCI_ADMA2_MASK)) &
			 SDHCI_ADMA2_MASK;
		if (offset) {
			if (data->flags & MMC_DATA_WRITE) {
				buffer = sdhci_kmap_atomic(sg);
				memcpy(align, buffer, offset);
				sdhci_kunmap_atomic(buffer);
			}

			/* tran, valid */
			__sdhci_adma_write_desc(host, &desc, align_addr,
						offset, ADMA2_TRAN_VALID);

			BUG_ON(offset > 65536);

			align += SDHCI_ADMA2_ALIGN;
			align_addr += SDHCI_ADMA2_ALIGN;

			addr += offset;
			len -= offset;
		}

		/*
		 * The block layer forces a minimum segment size of PAGE_SIZE,
		 * so 'len' can be too big here if PAGE_SIZE >= 64KiB. Write
		 * multiple descriptors, noting that the ADMA table is sized
		 * for 4KiB chunks anyway, so it will be big enough.
		 */
		while (len > host->max_adma) {
			int n = 32 * 1024; /* 32KiB*/

			__sdhci_adma_write_desc(host, &desc, addr, n, ADMA2_TRAN_VALID);
			addr += n;
			len -= n;
		}

		/* tran, valid */
		if (len)
			__sdhci_adma_write_desc(host, &desc, addr, len,
						ADMA2_TRAN_VALID);

		/*
		 * If this triggers then we have a calculation bug
		 * somewhere. :/
		 */
		WARN_ON((desc - host->adma_table) >= host->adma_table_sz);
	}

	if (host->quirks & SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC) {
		/* Mark the last descriptor as the terminating descriptor */
		if (desc != host->adma_table) {
			desc -= host->desc_sz;
			sdhci_adma_mark_end(desc);
		}
	} else {
		/* Add a terminating entry - nop, end, valid */
		__sdhci_adma_write_desc(host, &desc, 0, 0, ADMA2_NOP_END_VALID);
	}
}

static void sdhci_adma_show_error(struct sdhci_host *host)
{
	void *desc = host->adma_table;
	unsigned long dma = host->adma_addr;

	sdhci_dumpregs(host);

	while (RT_TRUE) {
		struct sdhci_adma2_64_desc *dma_desc = desc;

		if (host->flags & SDHCI_USE_64_BIT_DMA)
			SDHCI_DUMP("%08llx: DMA 0x%08x%08x, LEN 0x%04x, Attr=0x%02x\n",
			    (unsigned long long)dma,
			    le32_to_cpu(dma_desc->addr_hi),
			    le32_to_cpu(dma_desc->addr_lo),
			    le16_to_cpu(dma_desc->len),
			    le16_to_cpu(dma_desc->cmd));
		else
			SDHCI_DUMP("%08llx: DMA 0x%08x, LEN 0x%04x, Attr=0x%02x\n",
			    (unsigned long long)dma,
			    le32_to_cpu(dma_desc->addr_lo),
			    le16_to_cpu(dma_desc->len),
			    le16_to_cpu(dma_desc->cmd));

		desc += host->desc_sz;
		dma += host->desc_sz;

		if (dma_desc->cmd & cpu_to_le16(ADMA2_END))
			break;
	}
}

#endif


static unsigned long sdhci_sdma_address(struct sdhci_host *host)
{
	return host->data_buf;
}

static void sdhci_set_sdma_addr(struct sdhci_host *host, unsigned long addr)
{
	if (host->v4_mode)
		sdhci_set_adma_addr(host, addr);
	else
		sdhci_writel(host, addr, SDHCI_DMA_ADDRESS);
}

static void sdhci_set_adma_addr(struct sdhci_host *host, unsigned long addr)
{
	sdhci_writel(host, lower_32_bits(addr), SDHCI_ADMA_ADDRESS);
	if (host->flags & SDHCI_USE_64_BIT_DMA)
		sdhci_writel(host, upper_32_bits(addr), SDHCI_ADMA_ADDRESS_HI);
}




static void sdhci_config_dma(struct sdhci_host *host)
{
	rt_uint8_t ctrl;
	rt_uint16_t ctrl2;

	if (host->version < SDHCI_SPEC_200)
		return;

	ctrl = sdhci_readb(host, SDHCI_HOST_CONTROL);

	/*
	 * Always adjust the DMA selection as some controllers
	 * (e.g. JMicron) can't do PIO properly when the selection
	 * is ADMA.
	 */
	ctrl &= ~SDHCI_CTRL_DMA_MASK;
	if (!(host->flags & SDHCI_REQ_USE_DMA))
		goto out;

	/* Note if DMA Select is zero then SDMA is selected */
	if (host->flags & SDHCI_USE_ADMA)
		ctrl |= SDHCI_CTRL_ADMA32;

	if (host->flags & SDHCI_USE_64_BIT_DMA) {
		/*
		 * If v4 mode, all supported DMA can be 64-bit addressing if
		 * controller supports 64-bit system address, otherwise only
		 * ADMA can support 64-bit addressing.
		 */
		if (host->v4_mode) {
			ctrl2 = sdhci_readw(host, SDHCI_HOST_CONTROL2);
			ctrl2 |= SDHCI_CTRL_64BIT_ADDR;
			sdhci_writew(host, ctrl2, SDHCI_HOST_CONTROL2);
		} else if (host->flags & SDHCI_USE_ADMA) {
			/*
			 * Don't need to undo SDHCI_CTRL_ADMA32 in order to
			 * set SDHCI_CTRL_ADMA64.
			 */
			ctrl |= SDHCI_CTRL_ADMA64;
		}
	}

out:
	sdhci_writeb(host, ctrl, SDHCI_HOST_CONTROL);
}

/********************************************************* */
/*                     irq                                 */
/********************************************************* */


static rt_isr_handler_t  sdhci_irq(int irq, void *dev_id)
{
	struct rt_mmcsd_req *mrqs_done[SDHCI_MAX_MRQS] = {0};
	struct sdhci_host *host = dev_id;
	rt_uint32_t intmask, mask, unexpected = 0;
	int max_loops = 16;
	int i,result;

	rt_spin_lock(&host->lock);

	if (host->runtime_suspended) {
		rt_spin_unlock(&host->lock);
		return 0;
	}

	intmask = sdhci_readl(host, SDHCI_INT_STATUS);
	if (!intmask || intmask == 0xffffffff) {
		result = 0;
		goto out;
	}

	do {
		LOG_D("IRQ status 0x%08x\n", intmask);

		if (host->ops->irq) {
			intmask = host->ops->irq(host, intmask);
			if (!intmask)
				goto cont;
		}

		/* Clear selected interrupts. */
		mask = intmask & (SDHCI_INT_CMD_MASK | SDHCI_INT_DATA_MASK |
				  SDHCI_INT_BUS_POWER);
		sdhci_writel(host, mask, SDHCI_INT_STATUS);

		if (intmask & (SDHCI_INT_CARD_INSERT | SDHCI_INT_CARD_REMOVE)) {
			rt_uint32_t present = sdhci_readl(host, SDHCI_PRESENT_STATE) &
				      SDHCI_CARD_PRESENT;

			/*
			 * There is a observation on i.mx esdhc.  INSERT
			 * bit will be immediately set again when it gets
			 * cleared, if a card is inserted.  We have to mask
			 * the irq to prevent interrupt storm which will
			 * freeze the system.  And the REMOVE gets the
			 * same situation.
			 *
			 * More testing are needed here to ensure it works
			 * for other platforms though.
			 */
			host->ier &= ~(SDHCI_INT_CARD_INSERT |
				       SDHCI_INT_CARD_REMOVE);
			host->ier |= present ? SDHCI_INT_CARD_REMOVE :
					       SDHCI_INT_CARD_INSERT;
			sdhci_writel(host, host->ier, SDHCI_INT_ENABLE);
			sdhci_writel(host, host->ier, SDHCI_SIGNAL_ENABLE);

			sdhci_writel(host, intmask & (SDHCI_INT_CARD_INSERT |
				     SDHCI_INT_CARD_REMOVE), SDHCI_INT_STATUS);

			host->thread_isr |= intmask & (SDHCI_INT_CARD_INSERT |
						       SDHCI_INT_CARD_REMOVE);
			result = RT_EOK;
		}

		if (intmask & SDHCI_INT_CMD_MASK)
			sdhci_cmd_irq(host, intmask & SDHCI_INT_CMD_MASK, &intmask);

		if (intmask & SDHCI_INT_DATA_MASK)
			sdhci_data_irq(host, intmask & SDHCI_INT_DATA_MASK);

		if (intmask & SDHCI_INT_BUS_POWER)
			rt_kprintf("%s: Card is consuming too much power!\n",
				mmc_hostname(host->mmc));
#if 0
		if (intmask & SDHCI_INT_RETUNE)
			mmc_retune_needed(host->mmc);

		if ((intmask & SDHCI_INT_CARD_INT) &&
		    (host->ier & SDHCI_INT_CARD_INT)) {
			sdhci_enable_sdio_irq_nolock(host, RT_FALSE);
			sdio_signal_irq(host->mmc);
		}
#endif
		intmask &= ~(SDHCI_INT_CARD_INSERT | SDHCI_INT_CARD_REMOVE |
			     SDHCI_INT_CMD_MASK | SDHCI_INT_DATA_MASK |
			     SDHCI_INT_ERROR | SDHCI_INT_BUS_POWER |
			     SDHCI_INT_RETUNE | SDHCI_INT_CARD_INT);

		if (intmask) {
			unexpected |= intmask;
			sdhci_writel(host, intmask, SDHCI_INT_STATUS);
		}
cont:
		intmask = sdhci_readl(host, SDHCI_INT_STATUS);
	} while (intmask && --max_loops);

	/* Determine if mrqs can be completed immediately */
	for (i = 0; i < SDHCI_MAX_MRQS; i++) {
		struct rt_mmcsd_req *mrq = host->mrqs_done[i];

		if (!mrq)
			continue;

		if (sdhci_defer_done(host, mrq)) {
			result = RT_EOK;
		} else {
			mrqs_done[i] = mrq;
			host->mrqs_done[i] = NULL;
		}
	}
out:
	if (host->deferred_cmd)
		result = RT_EOK;

	rt_spin_unlock(&host->lock);

	/* Process mrqs ready for immediate completion */
	for (i = 0; i < SDHCI_MAX_MRQS; i++) {
		if (!mrqs_done[i])
			continue;

		if (host->ops->request_done)
			host->ops->request_done(host, mrqs_done[i]);
		else
			mmc_request_done(host->mmc, mrqs_done[i]);
	}

	if (unexpected) {
        pr_err("%s: Unexpected interrupt 0x%08x.\n",
               mmc_hostname(host->mmc), unexpected);
        sdhci_dumpregs(host);
    }

    if(result == RT_EOK)
    {
        rt_workqueue_submit_work(host->irq_wq, &host->irq_work, 0);
    }
}

static rt_isr_handler_t sdhci_thread_irq(struct rt_work *work, void *work_data)
{
	struct sdhci_host *host = work_data;
	struct rt_mmcsd_cmd *cmd;
	unsigned long flags;
	rt_uint32_t isr;

	while (!sdhci_request_done(host))
		;

	rt_spin_lock_irqsave(&host->lock);

	isr = host->thread_isr;
	host->thread_isr = 0;

	cmd = host->deferred_cmd;
	if (cmd && !sdhci_send_command_retry(host, cmd, flags))
		sdhci_finish_mrq(host, cmd->mrq);

	spin_unlock_irqrestore(&host->lock, flags);

	if (isr & (SDHCI_INT_CARD_INSERT | SDHCI_INT_CARD_REMOVE)) {
		struct mmc_host *mmc = host->mmc;

		mmc->ops->card_event(mmc);
#if 0 
		mmc_detect_change(mmc, msecs_to_jiffies(200));
#endif
	}

	return RT_EOK;
}


static void sdhci_data_irq(struct sdhci_host *host, rt_uint32_t intmask)
{
	    rt_uint32_t command;
	/*
	 * CMD19 generates _only_ Buffer Read Ready interrupt if
	 * use sdhci_send_tuning.
	 * Need to exclude this case: PIO mode and use mmc_send_tuning,
	 * If not, sdhci_transfer_pio will never be called, make the
	 * SDHCI_INT_DATA_AVAIL always there, stuck in irq storm.
	 */
	if (intmask & SDHCI_INT_DATA_AVAIL && !host->data) {
		command = SDHCI_GET_CMD(sdhci_readw(host, SDHCI_COMMAND));
        if (command == MMC_SEND_TUNING_BLOCK ||
            command == MMC_SEND_TUNING_BLOCK_HS200) {
			host->tuning_done = 1;
			rt_wqueue_wakeup(&host->buf_ready_int,0);
			return;
		}
	}

	if (!host->data) {
		struct rt_mmcsd_cmd *data_cmd = host->data_cmd;

		/*
		 * The "data complete" interrupt is also used to
		 * indicate that a busy state has ended. See comment
		 * above in sdhci_cmd_irq().
		 */
		if (data_cmd && (data_cmd->flags & MMC_RSP_BUSY)) {
			if (intmask & SDHCI_INT_DATA_TIMEOUT) {
				host->data_cmd = NULL;
				data_cmd->err = -ETIMEDOUT;
				__sdhci_finish_mrq(host, data_cmd->mrq);
				return;
			}
			if (intmask & SDHCI_INT_DATA_END) {
				host->data_cmd = NULL;
				/*
				 * Some cards handle busy-end interrupt
				 * before the command completed, so make
				 * sure we do things in the proper order.
				 */
				if (host->cmd == data_cmd)
					return;

				__sdhci_finish_mrq(host, data_cmd->mrq);
				return;
			}
		}

		/*
		 * SDHCI recovers from errors by resetting the cmd and data
		 * circuits. Until that is done, there very well might be more
		 * interrupts, so ignore them in that case.
		 */
		if (host->pending_reset)
			return;

		rt_kprintf("%s: Got data interrupt 0x%08x even though no data operation was in progress.\n",
		       mmc_hostname(host->mmc), (unsigned)intmask);
		sdhci_dumpregs(host);

		return;
	}

	if (intmask & SDHCI_INT_DATA_TIMEOUT)
        host->data->err = -ETIMEDOUT;
    else if (intmask & SDHCI_INT_DATA_END_BIT)
        host->data->err = -EILSEQ;
    else if ((intmask & SDHCI_INT_DATA_CRC) &&
        SDHCI_GET_CMD(sdhci_readw(host, SDHCI_COMMAND))
            != MMC_BUS_TEST_R)
        host->data->err = -EILSEQ;
    else if (intmask & SDHCI_INT_ADMA_ERROR) {
        pr_err("%s: ADMA error: 0x%08x\n", mmc_hostname(host->mmc),
               intmask);
        sdhci_adma_show_error(host);
        host->data->err = -EIO;
        if (host->ops->adma_workaround)
            host->ops->adma_workaround(host, intmask);
    }

	if (host->data->err)
		sdhci_finish_data(host);
	else {
		if (intmask & (SDHCI_INT_DATA_AVAIL | SDHCI_INT_SPACE_AVAIL))
			sdhci_transfer_pio(host);

		/*
		 * We currently don't do anything fancy with DMA
		 * boundaries, but as we can't disable the feature
		 * we need to at least restart the transfer.
		 *
		 * According to the spec sdhci_readl(host, SDHCI_DMA_ADDRESS)
		 * should return a valid address to continue from, but as
		 * some controllers are faulty, don't trust them.
		 */
		if (intmask & SDHCI_INT_DMA_END) {
			unsigned long dmastart, dmanow;

			dmastart = sdhci_sdma_address(host);
			dmanow = dmastart + host->data->bytes_xfered;
			/*
			 * Force update to the next DMA block boundary.
			 */
			dmanow = (dmanow &
				~((unsigned long)SDHCI_DEFAULT_BOUNDARY_SIZE - 1)) +
				SDHCI_DEFAULT_BOUNDARY_SIZE;
			host->data->bytes_xfered = dmanow - dmastart;
			DBG("DMA base %pad, transferred 0x%06x bytes, next %pad\n",
			    &dmastart, host->data->bytes_xfered, &dmanow);
			sdhci_set_sdma_addr(host, dmanow);
		}

		if (intmask & SDHCI_INT_DATA_END) {
			if (host->cmd == host->data_cmd) {
				/*
				 * Data managed to finish before the
				 * command completed. Make sure we do
				 * things in the proper order.
				 */
				host->data_early = 1;
			} else {
				sdhci_finish_data(host);
			}
		}
	}
}

static void sdhci_cmd_irq(struct sdhci_host *host, rt_uint32_t intmask, rt_uint32_t *intmask_p)
{
    /* Handle auto-CMD12 error */
    if (intmask & SDHCI_INT_AUTO_CMD_ERR && host->data_cmd) {
        struct rt_mmcsd_req *mrq = host->data_cmd->mrq;
        rt_uint16_t auto_cmd_status = sdhci_readw(host, SDHCI_AUTO_CMD_STATUS);
        int data_err_bit = (auto_cmd_status & SDHCI_AUTO_CMD_TIMEOUT) ?
                   SDHCI_INT_DATA_TIMEOUT :
                   SDHCI_INT_DATA_CRC;

        /* Treat auto-CMD12 error the same as data error */
        if (!mrq->sbc && (host->flags & SDHCI_AUTO_CMD12)) {
            *intmask_p |= data_err_bit;
            return;
        }
    }

    if (!host->cmd) {
        /*
         * SDHCI recovers from errors by resetting the cmd and data
         * circuits.  Until that is done, there very well might be more
         * interrupts, so ignore them in that case.
         */
        if (host->pending_reset)
            return;
        rt_kprintf("%s: Got command interrupt 0x%08x even though no command operation was in progress.\n",
               mmc_hostname(host->mmc), (unsigned)intmask);
        sdhci_dumpregs(host);
        return;
    }

    if (intmask & (SDHCI_INT_TIMEOUT | SDHCI_INT_CRC |
               SDHCI_INT_END_BIT | SDHCI_INT_INDEX)) {
        if (intmask & SDHCI_INT_TIMEOUT)
            host->cmd->err = -ETIMEDOUT;
        else
            host->cmd->err = -EILSEQ;

        /* Treat data command CRC error the same as data CRC error */
        if (host->cmd->data &&
            (intmask & (SDHCI_INT_CRC | SDHCI_INT_TIMEOUT)) ==
             SDHCI_INT_CRC) {
            host->cmd = NULL;
            *intmask_p |= SDHCI_INT_DATA_CRC;
            return;
        }

        __sdhci_finish_mrq(host, host->cmd->mrq);
        return;
    }

    /* Handle auto-CMD23 error */
    if (intmask & SDHCI_INT_AUTO_CMD_ERR) {
        struct rt_mmcsd_req *mrq = host->cmd->mrq;
        rt_uint16_t auto_cmd_status = sdhci_readw(host, SDHCI_AUTO_CMD_STATUS);
        int err = (auto_cmd_status & SDHCI_AUTO_CMD_TIMEOUT) ?
              -ETIMEDOUT :
              -EILSEQ;

        if (mrq->sbc && (host->flags & SDHCI_AUTO_CMD23)) {
            mrq->sbc->err = err;
            __sdhci_finish_mrq(host, mrq);
            return;
        }
    }

    if (intmask & SDHCI_INT_RESPONSE)
        sdhci_finish_command(host);
}

static void sdhci_set_transfer_irqs(struct sdhci_host *host)
{
	rt_uint32_t pio_irqs = SDHCI_INT_DATA_AVAIL | SDHCI_INT_SPACE_AVAIL;
	rt_uint32_t dma_irqs = SDHCI_INT_DMA_END | SDHCI_INT_ADMA_ERROR;

	if (host->flags & SDHCI_REQ_USE_DMA)
		host->ier = (host->ier & ~pio_irqs) | dma_irqs;
	else
		host->ier = (host->ier & ~dma_irqs) | pio_irqs;

	if (host->flags & (SDHCI_AUTO_CMD23 | SDHCI_AUTO_CMD12))
		host->ier |= SDHCI_INT_AUTO_CMD_ERR;
	else
		host->ier &= ~SDHCI_INT_AUTO_CMD_ERR;

	sdhci_writel(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_writel(host, host->ier, SDHCI_SIGNAL_ENABLE);
}

void sdhci_set_data_timeout_irq(struct sdhci_host *host, rt_bool_t enable)
{
	if (enable)
		host->ier |= SDHCI_INT_DATA_TIMEOUT;
	else
		host->ier &= ~SDHCI_INT_DATA_TIMEOUT;
	sdhci_writel(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_writel(host, host->ier, SDHCI_SIGNAL_ENABLE);
}

static void sdhci_enable_sdio_irq_nolock(struct sdhci_host *host, int enable)
{
	if (!(host->flags & SDHCI_DEVICE_DEAD)) {
		if (enable)
			host->ier |= SDHCI_INT_CARD_INT;
		else
			host->ier &= ~SDHCI_INT_CARD_INT;

		sdhci_writel(host, host->ier, SDHCI_INT_ENABLE);
		sdhci_writel(host, host->ier, SDHCI_SIGNAL_ENABLE);
	}
}

/********************************************************* */
/*                     request                             */
/********************************************************* */


static rt_bool_t sdhci_send_command_retry(struct sdhci_host *host,
				     struct rt_mmcsd_cmd *cmd,
				     unsigned long flags)
{
	struct rt_mmcsd_cmd *deferred_cmd = host->deferred_cmd;
	int timeout = 10; /* Approx. 10 ms */
	rt_bool_t present;

	while (!sdhci_send_command(host, cmd)) {
		if (!timeout--) {
			rt_kprintf("%s: Controller never released inhibit bit(s).\n",
			       mmc_hostname(host->mmc));
			sdhci_dumpregs(host);
			cmd->err = -EIO;
			return RT_FALSE;
		}

		rt_spin_unlock_irqrestore(&host->lock, flags);

		usleep_range(1000, 1250);

		present = host->mmc->ops->get_cd(host->mmc);

		rt_spin_lock_irqsave(&host->lock);

		/* A deferred command might disappear, handle that */
		if (cmd == deferred_cmd && cmd != host->deferred_cmd)
			return RT_TRUE;

		if (sdhci_present_error(host, cmd, present))
			return RT_FALSE;
	}

	if (cmd == host->deferred_cmd)
		host->deferred_cmd = NULL;

	return RT_TRUE;
}

static rt_bool_t sdhci_request_done(struct sdhci_host *host)
{
	unsigned long flags;
	struct rt_mmcsd_req *mrq;
	int i;

	rt_spin_lock_irqsave(&host->lock);

	for (i = 0; i < SDHCI_MAX_MRQS; i++) {
		mrq = host->mrqs_done[i];
		if (mrq)
			break;
	}

	if (!mrq) {
		rt_spin_unlock_irqrestore(&host->lock, flags);
		return RT_TRUE;
	}

	/*
	 * The controller needs a reset of internal state machines
	 * upon error conditions.
	 */
	if (sdhci_needs_reset(host, mrq)) {
		/*
		 * Do not finish until command and data lines are available for
		 * reset. Note there can only be one other mrq, so it cannot
		 * also be in mrqs_done, otherwise host->cmd and host->data_cmd
		 * would both be null.
		 */
		if (host->cmd || host->data_cmd) {
			rt_spin_unlock_irqrestore(&host->lock, flags);
			return RT_TRUE;
		}

		/* Some controllers need this kick or reset won't work here */
		if (host->quirks & SDHCI_QUIRK_CLOCK_BEFORE_RESET)
			/* This is to force an update */
			host->ops->set_clock(host, host->clock);

		sdhci_do_reset(host, SDHCI_RESET_CMD);
        sdhci_do_reset(host, SDHCI_RESET_DATA);

		host->pending_reset = RT_FALSE;
	}

	/*
	 * Always unmap the data buffers if they were mapped by
	 * sdhci_prepare_data() whenever we finish with a request.
	 * This avoids leaking DMA mappings on error.
	 */
	if (host->flags & SDHCI_REQ_USE_DMA) {
		struct rt_mmcsd_data *data = mrq->data;

		if (host->use_external_dma && data &&
		    (mrq->cmd->err || data->err)) {
			struct dma_chan *chan = sdhci_external_dma_channel(host, data);

			host->mrqs_done[i] = NULL;
			sdhci_set_mrq_done(host, mrq);
		}
#if 0
		if (data && data->host_cookie == COOKIE_MAPPED) {
			if (host->bounce_buffer) {
				/*
				 * On reads, copy the bounced data into the
				 * sglist
				 */
				if (mmc_get_dma_dir(data) == DMA_FROM_DEVICE) {
					unsigned int length = data->bytes_xfered;

					if (length > host->bounce_buffer_size) {
						rt_kprintf("%s: bounce buffer is %u bytes but DMA claims to have transferred %u bytes\n",
						       mmc_hostname(host->mmc),
						       host->bounce_buffer_size,
						       data->bytes_xfered);
						/* Cap it down and continue */
						length = host->bounce_buffer_size;
					}
					dma_sync_single_for_cpu(
						mmc_dev(host->mmc),
						host->bounce_addr,
						host->bounce_buffer_size,
						DMA_FROM_DEVICE);

				} else {
					/* No copying, just switch ownership */
					dma_sync_single_for_cpu(
						mmc_dev(host->mmc),
						host->bounce_addr,
						host->bounce_buffer_size,
						mmc_get_dma_dir(data));
				}
			} else {
				/* Unmap the raw data */
				dma_unmap_sg(mmc_dev(host->mmc), data->sg,
					     data->sg_len,
					     mmc_get_dma_dir(data));
			}
			data->host_cookie = COOKIE_UNMAPPED;
		}
#endif
	}

	host->mrqs_done[i] = NULL;

	rt_spin_unlock_irqrestore(&host->lock, flags);

	if (host->ops->request_done)
		host->ops->request_done(host, mrq);
	else
		mmc_request_done(host->mmc, mrq);

	return RT_FALSE;
}

static inline void sdhci_set_block_info(struct sdhci_host *host,
					struct rt_mmcsd_data *data)
{
	/* Set the DMA boundary value and block size */
	sdhci_writew(host,
		     SDHCI_MAKE_BLKSZ(host->sdma_boundary, data->blksize),
		     SDHCI_BLOCK_SIZE);
	/*
	 * For Version 4.10 onwards, if v4 mode is enabled, 32-bit Block Count
	 * can be supported, in that case 16-bit block count register must be 0.
	 */
	if (host->version >= SDHCI_SPEC_410 && host->v4_mode &&
	    (host->quirks2 & SDHCI_QUIRK2_USE_32BIT_BLK_CNT)) {
		if (sdhci_readw(host, SDHCI_BLOCK_COUNT))
			sdhci_writew(host, 0, SDHCI_BLOCK_COUNT);
		sdhci_writew(host, data->blks, SDHCI_32BIT_BLK_CNT);
	} else {
		sdhci_writew(host, data->blks, SDHCI_BLOCK_COUNT);
	}
}

static void sdhci_set_transfer_mode(struct sdhci_host *host,
	struct rt_mmcsd_cmd *cmd)
{
	rt_uint16_t mode = 0;
	struct rt_mmcsd_data *data = cmd->data;

	if (data == NULL) {
		if (host->quirks2 &
			SDHCI_QUIRK2_CLEAR_TRANSFERMODE_REG_BEFORE_CMD) {
			/* must not clear SDHCI_TRANSFER_MODE when tuning */
			if (!mmc_op_tuning(cmd->cmd_code))
				sdhci_writew(host, 0x0, SDHCI_TRANSFER_MODE);
		} else {
		/* clear Auto CMD settings for no data CMDs */
			mode = sdhci_readw(host, SDHCI_TRANSFER_MODE);
			sdhci_writew(host, mode & ~(SDHCI_TRNS_AUTO_CMD12 |
				SDHCI_TRNS_AUTO_CMD23), SDHCI_TRANSFER_MODE);
		}
		return;
	}


	if (!(host->quirks2 & SDHCI_QUIRK2_SUPPORT_SINGLE))
		mode = SDHCI_TRNS_BLK_CNT_EN;

	if (mmc_op_multi(cmd->cmd_code) || data->blks > 1) {
		mode = SDHCI_TRNS_BLK_CNT_EN | SDHCI_TRNS_MULTI;
		sdhci_auto_cmd_select(host, cmd, &mode);
		if (sdhci_auto_cmd23(host, cmd->mrq))
			sdhci_writel(host, cmd->mrq->sbc->arg, SDHCI_ARGUMENT2);
	}

	if (data->flags & DATA_DIR_READ)
		mode |= SDHCI_TRNS_READ;
	if (host->flags & SDHCI_REQ_USE_DMA)
		mode |= SDHCI_TRNS_DMA;

	sdhci_writew(host, mode, SDHCI_TRANSFER_MODE);
}

static rt_bool_t sdhci_send_command(struct sdhci_host *host, struct rt_mmcsd_cmd *cmd)
{
	int flags;
	rt_uint32_t mask;
	unsigned long timeout;

	/* Initially, a command has no error */
	cmd->err = 0;

	if ((host->quirks2 & SDHCI_QUIRK2_STOP_WITH_TC) &&
	    cmd->cmd_code == MMC_STOP_TRANSMISSION)
		cmd->flags |= MMC_RSP_BUSY;

	mask = SDHCI_CMD_INHIBIT;
	if (sdhci_data_line_cmd(cmd))
		mask |= SDHCI_DATA_INHIBIT;

	/* We shouldn't wait for data inihibit for stop commands, even
	   though they might use busy signaling */
	if (cmd->mrq->data && (cmd == cmd->mrq->data->stop))
		mask &= ~SDHCI_DATA_INHIBIT;

	if (sdhci_readl(host, SDHCI_PRESENT_STATE) & mask)
		return RT_FALSE;

	host->cmd = cmd;
	host->data_timeout = 0;
	if (sdhci_data_line_cmd(cmd)) {
		host->data_cmd = cmd;
		sdhci_set_timeout(host, cmd);
	}

	if (cmd->data) {
		if (host->use_external_dma)
			sdhci_external_dma_prepare_data(host, cmd);
		else
			sdhci_prepare_data(host, cmd);
	}

	sdhci_writel(host, cmd->arg, SDHCI_ARGUMENT);

	sdhci_set_transfer_mode(host, cmd);

	if ((cmd->flags & MMC_RSP_136) && (cmd->flags & MMC_RSP_BUSY)) {
		/*
		 * This does not happen in practice because 136-bit response
		 * commands never have busy waiting, so rather than complicate
		 * the error path, just remove busy waiting and continue.
		 */
		cmd->flags &= ~MMC_RSP_BUSY;
	}

	if (!(cmd->flags & MMC_RSP_PRESENT))
		flags = SDHCI_CMD_RESP_NONE;
	else if (cmd->flags & MMC_RSP_136)
		flags = SDHCI_CMD_RESP_LONG;
	else if (cmd->flags & MMC_RSP_BUSY)
		flags = SDHCI_CMD_RESP_SHORT_BUSY;
	else
		flags = SDHCI_CMD_RESP_SHORT;

	if (cmd->flags & MMC_RSP_CRC)
		flags |= SDHCI_CMD_CRC;
	if (cmd->flags & MMC_RSP_OPCODE)
		flags |= SDHCI_CMD_INDEX;

	/* CMD19 is special in that the Data Present Select should be set */
	if (cmd->data || mmc_op_tuning(cmd->cmd_code))
		flags |= SDHCI_CMD_DATA;

	timeout = rt_tick_get();
	if (host->data_timeout)
		timeout += nsecs_to_jiffies(host->data_timeout);
	else if (!cmd->data && cmd->busy_timeout > 9000)
		timeout += DIV_ROUND_UP(cmd->busy_timeout, 1000) * RT_TICK_PER_SECOND + RT_TICK_PER_SECOND;
	else
		timeout += 10 * RT_TICK_PER_SECOND;
	sdhci_mod_timer(host, cmd->mrq, timeout);

	if (host->use_external_dma)
		sdhci_external_dma_pre_transfer(host, cmd);

	sdhci_writew(host, SDHCI_MAKE_CMD(cmd->cmd_code, flags), SDHCI_COMMAND);

	return RT_TRUE;
}

static void sdhci_complete_work(struct rt_work *work, void *work_data)
{
	struct sdhci_host *host = work_data;

	while (!sdhci_request_done(host))
		;
}

/********************************************************* */
/*                      data                               */
/********************************************************* */
static void sdhci_prepare_data(struct sdhci_host *host, struct rt_mmcsd_cmd *cmd)
{
	struct rt_mmcsd_data *data = cmd->data;

	sdhci_initialize_data(host, data);

	if (host->flags & (SDHCI_USE_SDMA | SDHCI_USE_ADMA)) {
		struct scatterlist *sg;
		unsigned int length_mask, offset_mask;
		int i;

		host->flags |= SDHCI_REQ_USE_DMA;

		/*
		 * FIXME: This doesn't account for merging when mapping the
		 * scatterlist.
		 *
		 * The assumption here being that alignment and lengths are
		 * the same after DMA mapping to device address space.
		 */
		length_mask = 0;
		offset_mask = 0;
		if (host->flags & SDHCI_USE_ADMA) {
			if (host->quirks & SDHCI_QUIRK_32BIT_ADMA_SIZE) {
				length_mask = 3;
				/*
				 * As we use up to 3 byte chunks to work
				 * around alignment problems, we need to
				 * check the offset as well.
				 */
				offset_mask = 3;
			}
		} else {
			if (host->quirks & SDHCI_QUIRK_32BIT_DMA_SIZE)
				length_mask = 3;
			if (host->quirks & SDHCI_QUIRK_32BIT_DMA_ADDR)
				offset_mask = 3;
		}

		if (length_mask | offset_mask) {
			host->flags &= ~SDHCI_REQ_USE_DMA;
		}
	}

	sdhci_config_dma(host);

	if (host->flags & SDHCI_REQ_USE_DMA) {
		sdhci_set_sdma_addr(host, sdhci_sdma_address(host));
	}

	if (!(host->flags & SDHCI_REQ_USE_DMA)) {
		host->blocks = data->blks;
	}

	sdhci_set_transfer_irqs(host);

	sdhci_set_block_info(host, data);
}

static void sdhci_initialize_data(struct sdhci_host *host,
				  struct rt_mmcsd_data *data)
{
	if(!host->data)
	{
		rt_backtrace();
	}

	/* Sanity checks */
	LOG_D(data->blksize * data->blks > 524288);
	LOG_D(data->blksize > host->mmc->max_blk_size);
	LOG_D(data->blks > 65535);

	host->data = data;
	host->data_early = 0;
	host->data->bytes_xfered = 0;
}

/********************************************************* */
/*                     timer                               */
/********************************************************* */

static unsigned int sdhci_target_timeout(struct sdhci_host *host,
					 struct rt_mmcsd_cmd *cmd,
					 struct rt_mmcsd_data *data)
{
	unsigned int target_timeout;

	/* timeout in us */
	if (!data) {
		target_timeout = cmd->busy_timeout * 1000;
	} else {
		target_timeout = DIV_ROUND_UP(data->timeout_ns, 1000);
		if (host->clock && data->timeout_clks) {
			unsigned long long val;

			/*
			 * data->timeout_clks is in units of clock cycles.
			 * host->clock is in Hz.  target_timeout is in us.
			 * Hence, us = 1000000 * cycles / Hz.  Round up.
			 */
			val = 1000000ULL * data->timeout_clks;
			if (do_div(val, host->clock))
				target_timeout++;
			target_timeout += val;
		}
	}

	return target_timeout;
}

static void sdhci_timeout_timer(void* parameter)
{
	struct sdhci_host *host = parameter;
	unsigned long flags;

	rt_spin_lock_irqsave(&host->lock);

	if (host->cmd && !sdhci_data_line_cmd(host->cmd)) {
		rt_kprintf("%s: Timeout waiting for hardware cmd interrupt.\n",
		       mmc_hostname(host->mmc));
		sdhci_dumpregs(host);

		host->cmd->err = -ETIMEDOUT;
		sdhci_finish_mrq(host, host->cmd->mrq);
	}

	rt_spin_unlock_irqrestore(&host->lock, flags);
}

static rt_uint8_t sdhci_calc_timeout(struct sdhci_host *host, struct rt_mmcsd_cmd *cmd,
			     rt_bool_t *too_big)
{
	rt_uint8_t count;
	struct rt_mmcsd_data *data;
	unsigned target_timeout, current_timeout;

	*too_big = RT_FALSE;

	/*
	 * If the host controller provides us with an incorrect timeout
	 * value, just skip the check and use the maximum. The hardware may take
	 * longer to time out, but that's much better than having a too-short
	 * timeout value.
	 */
	if (host->quirks & SDHCI_QUIRK_BROKEN_TIMEOUT_VAL)
		return host->max_timeout_count;

	/* Unspecified command, assume max */
	if (cmd == NULL)
		return host->max_timeout_count;

	data = cmd->data;
	/* Unspecified timeout, assume max */
	if (!data && !cmd->busy_timeout)
		return host->max_timeout_count;

	/* timeout in us */
	target_timeout = sdhci_target_timeout(host, cmd, data);

	/*
	 * Figure out needed cycles.
	 * We do this in steps in order to fit inside a 32 bit int.
	 * The first step is the minimum timeout, which will have a
	 * minimum resolution of 6 bits:
	 * (1) 2^13*1000 > 2^22,
	 * (2) host->timeout_clk < 2^16
	 *     =>
	 *     (1) / (2) > 2^6
	 */
	count = 0;
	current_timeout = (1 << 13) * 1000 / host->timeout_clk;
	while (current_timeout < target_timeout) {
		count++;
		current_timeout <<= 1;
		if (count > host->max_timeout_count) {
			if (!(host->quirks2 & SDHCI_QUIRK2_DISABLE_HW_TIMEOUT))
				LOG_D("Too large timeout 0x%x requested for CMD%d!\n",
				    count, cmd->cmd_code);
			count = host->max_timeout_count;
			*too_big = RT_TRUE;
			break;
		}
	}

	return count;
}

static void sdhci_timeout_data_timer(void* parameter)
{
	struct sdhci_host *host = parameter;
	unsigned long flags;

	rt_spin_lock_irqsave(&host->lock);

	if (host->data || host->data_cmd ||
	    (host->cmd && sdhci_data_line_cmd(host->cmd))) {
		rt_kprintf("%s: Timeout waiting for hardware interrupt.\n",
		       mmc_hostname(host->mmc));
		sdhci_err_stats_inc(host, REQ_TIMEOUT);
		sdhci_dumpregs(host);

		if (host->data) {
			host->data->err = -ETIMEDOUT;
			__sdhci_finish_data(host, RT_TRUE);
			rt_workqueue_submit_work(host->complete_wq, &host->complete_work,0);
		} else if (host->data_cmd) {
			host->data_cmd->err = -ETIMEDOUT;
			sdhci_finish_mrq(host, host->data_cmd->mrq);
		} else {
			host->cmd->err = -ETIMEDOUT;
			sdhci_finish_mrq(host, host->cmd->mrq);
		}
	}

	rt_spin_unlock_irqrestore(&host->lock, flags);
}

static void sdhci_del_timer(struct sdhci_host *host, struct rt_mmcsd_req *mrq)
{
	if (sdhci_data_line_cmd(mrq->cmd))
		rt_timer_delete(&host->data_timer);
	else
		rt_timer_delete(&host->timer);
}

static void sdhci_calc_sw_timeout(struct sdhci_host *host,
				  struct rt_mmcsd_cmd *cmd)
{
	struct rt_mmcsd_data *data = cmd->data;
	struct mmc_host *mmc = host->mmc;
	struct rt_mmcsd_io_cfg *ios = &mmc->ios;
	unsigned char bus_width = 1 << ios->bus_width;
	unsigned int blksz;
	unsigned int freq;
	rt_uint64_t target_timeout;
	rt_uint64_t transfer_time;

	target_timeout = sdhci_target_timeout(host, cmd, data);
	target_timeout *= NSEC_PER_USEC;

	if (data) {
		blksz = data->blksize;
		freq = mmc->actual_clock ? : host->clock;
		transfer_time = (rt_uint64_t)blksz * NSEC_PER_SEC * (8 / bus_width);
		do_div(transfer_time, freq);
		/* multiply by '2' to account for any unknowns */
		transfer_time = transfer_time * 2;
		/* calculate timeout for the entire data */
		host->data_timeout = data->blks * target_timeout +
				     transfer_time;
	} else {
		host->data_timeout = target_timeout;
	}

	if (host->data_timeout)
		host->data_timeout += MMC_CMD_TRANSFER_TIME;
}

void __sdhci_set_timeout(struct sdhci_host *host, struct rt_mmcsd_cmd *cmd)
{
	rt_bool_t too_big = RT_FALSE;
	rt_uint8_t count = sdhci_calc_timeout(host, cmd, &too_big);

	if (too_big &&
	    host->quirks2 & SDHCI_QUIRK2_DISABLE_HW_TIMEOUT) {
		sdhci_calc_sw_timeout(host, cmd);
		sdhci_set_data_timeout_irq(host, RT_FALSE);
	} else if (!(host->ier & SDHCI_INT_DATA_TIMEOUT)) {
		sdhci_set_data_timeout_irq(host, RT_FALSE);
	}

	sdhci_writeb(host, count, SDHCI_TIMEOUT_CONTROL);
}

static void sdhci_set_timeout(struct sdhci_host *host, struct rt_mmcsd_cmd *cmd)
{
	if (host->ops->set_timeout)
		host->ops->set_timeout(host, cmd);
	else
		__sdhci_set_timeout(host, cmd);
}

static void sdhci_mod_timer(struct sdhci_host *host, struct rt_mmcsd_req *mrq,
			    unsigned long timeout)
{
	if (sdhci_data_line_cmd(mrq->cmd))
		mod_timer(&host->data_timer, timeout);
	else
		mod_timer(&host->timer, timeout);
}


/********************************************************* */
/*                     reset                               */
/********************************************************* */
enum sdhci_reset_reason {
	SDHCI_RESET_FOR_INIT,
	SDHCI_RESET_FOR_REQUEST_ERROR,
	SDHCI_RESET_FOR_REQUEST_ERROR_DATA_ONLY,
	SDHCI_RESET_FOR_TUNING_ABORT,
	SDHCI_RESET_FOR_CARD_REMOVED,
	SDHCI_RESET_FOR_CQE_RECOVERY,
};
static void sdhci_reset_for_reason(struct sdhci_host *host, enum sdhci_reset_reason reason)
{
	if (host->quirks2 & SDHCI_QUIRK2_ISSUE_CMD_DAT_RESET_TOGETHER) {
		sdhci_do_reset(host, SDHCI_RESET_CMD | SDHCI_RESET_DATA);
		return;
	}

	switch (reason) {
	case SDHCI_RESET_FOR_INIT:
		sdhci_do_reset(host, SDHCI_RESET_CMD | SDHCI_RESET_DATA);
		break;
	case SDHCI_RESET_FOR_REQUEST_ERROR:
	case SDHCI_RESET_FOR_TUNING_ABORT:
	case SDHCI_RESET_FOR_CARD_REMOVED:
	case SDHCI_RESET_FOR_CQE_RECOVERY:
		sdhci_do_reset(host, SDHCI_RESET_CMD);
		sdhci_do_reset(host, SDHCI_RESET_DATA);
		break;
	case SDHCI_RESET_FOR_REQUEST_ERROR_DATA_ONLY:
		sdhci_do_reset(host, SDHCI_RESET_DATA);
		break;
	}
}

#define sdhci_reset_for(h, r) sdhci_reset_for_reason((h), SDHCI_RESET_FOR_##r)


/********************************************************* */
/*                      done                               */
/********************************************************* */
static void sdhci_finish_data(struct sdhci_host *host)
{
	__sdhci_finish_data(host, RT_FALSE);
}

static void __sdhci_finish_data(struct sdhci_host *host, rt_bool_t sw_data_timeout)
{
	struct rt_mmcsd_cmd *data_cmd = host->data_cmd;
	struct rt_mmcsd_data *data = host->data;

	host->data = NULL;
	host->data_cmd = NULL;

	/*
	 * The controller needs a reset of internal state machines upon error
	 * conditions.
	 */
	if (data->err) {
		if (!host->cmd || host->cmd == data_cmd)
			sdhci_reset_for(host, REQUEST_ERROR);
		else
			sdhci_reset_for(host, REQUEST_ERROR_DATA_ONLY);
	}

	if ((host->flags & (SDHCI_REQ_USE_DMA | SDHCI_USE_ADMA)) ==
	    (SDHCI_REQ_USE_DMA | SDHCI_USE_ADMA))
		//we use a continuous memory ,wo we did not need align
		// sdhci_adma_table_post(host, data);

	/*
	 * The specification states that the block count register must
	 * be updated, but it does not specify at what point in the
	 * data flow. That makes the register entirely useless to read
	 * back so we have to assume that nothing made it to the card
	 * in the event of an error.
	 */
	if (data->err)
	{
		data->bytes_xfered = 0;
	}
	else
	{
		data->bytes_xfered = data->blksize * data->blks;
	}
	/*
	 * Need to send CMD12 if -
	 * a) open-ended multiblock transfer not using auto CMD12 (no CMD23)
	 * b) error in multiblock transfer
	 */
	if (data->stop &&
	    ((!data->mrq->sbc && !sdhci_auto_cmd12(host, data->mrq)) ||
	     data->err)) {
		/*
		 * 'cap_cmd_during_tfr' request must not use the command line
		 * after mmc_command_done() has been called. It is upper layer's
		 * responsibility to send the stop command if required.
		 */
		if (data->mrq->cap_cmd_during_tfr) {
			__sdhci_finish_mrq(host, data->mrq);
		} else {
			/* Avoid triggering warning in sdhci_send_command() */
			host->cmd = NULL;
			if (!sdhci_send_command(host, data->stop->err)) {
				if (sw_data_timeout) {
					/*
					 * This is anyway a sw data timeout, so
					 * give up now.
					 */
					data->stop->err = -EIO;
					__sdhci_finish_mrq(host, data->mrq);
				} else {
					host->deferred_cmd = data->stop;
				}
			}
		}
	} else {
		__sdhci_finish_mrq(host, data->mrq);
	}
}

static void sdhci_finish_mrq(struct sdhci_host *host, struct rt_mmcsd_req *mrq)
{
	__sdhci_finish_mrq(host, mrq);

	rt_workqueue_submit_work(host->complete_wq, &host->complete_work,0);
}

static void __sdhci_finish_mrq(struct sdhci_host *host, struct rt_mmcsd_req *mrq)
{
	if (host->cmd && host->cmd->mrq == mrq)
		host->cmd = NULL;

	if (host->data_cmd && host->data_cmd->mrq == mrq)
		host->data_cmd = NULL;

	if (host->deferred_cmd && host->deferred_cmd->mrq == mrq)
		host->deferred_cmd = NULL;

	if (host->data && host->data->mrq == mrq)
		host->data = NULL;

	if (sdhci_needs_reset(host, mrq))
		host->pending_reset = RT_TRUE;

	sdhci_set_mrq_done(host, mrq);

	sdhci_del_timer(host, mrq);
	
}

static void sdhci_finish_command(struct sdhci_host *host)
{
	struct rt_mmcsd_cmd *cmd = host->cmd;

	host->cmd = NULL;

	if (cmd->flags & MMC_RSP_PRESENT) {
		if (cmd->flags & MMC_RSP_136) {
			sdhci_read_rsp_136(host, cmd);
		} else {
			cmd->resp[0] = sdhci_readl(host, SDHCI_RESPONSE);
		}
	}

	if (cmd->mrq->cap_cmd_during_tfr && cmd == cmd->mrq->cmd)

#if 0
		mmc_command_done(host->mmc, cmd->mrq);
#endif

	/*
	 * The host can send and interrupt when the busy state has
	 * ended, allowing us to wait without wasting CPU cycles.
	 * The busy signal uses DAT0 so this is similar to waiting
	 * for data to complete.
	 *
	 * Note: The 1.0 specification is a bit ambiguous about this
	 *       feature so there might be some problems with older
	 *       controllers.
	 */
	if (cmd->flags & MMC_RSP_BUSY) {
		if (cmd->data) {
			LOG_D("Cannot wait for busy signal when also doing a data transfer");
		} else if (!(host->quirks & SDHCI_QUIRK_NO_BUSY_IRQ) &&
			   cmd == host->data_cmd) {
			/* Command complete before busy is ended */
			return;
		}
	}

	/* Finished CMD23, now send actual command. */
	if (cmd == cmd->mrq->sbc) {
		if (!sdhci_send_command(host, cmd->mrq->cmd)) {
			host->deferred_cmd = cmd->mrq->cmd;
		}
	} else {

		/* Processed actual command. */
		if (host->data && host->data_early)
			sdhci_finish_data(host);

		if (!cmd->data)
			__sdhci_finish_mrq(host, cmd->mrq);
	}
}


/********************************************************* */
/*                     error                               */
/********************************************************* */

void sdhci_dumpregs(struct sdhci_host *host)
{
#define SDHCI_DUMP rt_kprintf
	SDHCI_DUMP("============ SDHCI REGISTER DUMP ===========\n");

	SDHCI_DUMP("Sys addr:  0x%08x | Version:  0x%08x\n",
		   sdhci_readl(host, SDHCI_DMA_ADDRESS),
		   sdhci_readw(host, SDHCI_HOST_VERSION));
	SDHCI_DUMP("Blk size:  0x%08x | Blk cnt:  0x%08x\n",
		   sdhci_readw(host, SDHCI_BLOCK_SIZE),
		   sdhci_readw(host, SDHCI_BLOCK_COUNT));
	SDHCI_DUMP("Argument:  0x%08x | Trn mode: 0x%08x\n",
		   sdhci_readl(host, SDHCI_ARGUMENT),
		   sdhci_readw(host, SDHCI_TRANSFER_MODE));
	SDHCI_DUMP("Present:   0x%08x | Host ctl: 0x%08x\n",
		   sdhci_readl(host, SDHCI_PRESENT_STATE),
		   sdhci_readb(host, SDHCI_HOST_CONTROL));
	SDHCI_DUMP("Power:     0x%08x | Blk gap:  0x%08x\n",
		   sdhci_readb(host, SDHCI_POWER_CONTROL),
		   sdhci_readb(host, SDHCI_BLOCK_GAP_CONTROL));
	SDHCI_DUMP("Wake-up:   0x%08x | Clock:    0x%08x\n",
		   sdhci_readb(host, SDHCI_WAKE_UP_CONTROL),
		   sdhci_readw(host, SDHCI_CLOCK_CONTROL));
	SDHCI_DUMP("Timeout:   0x%08x | Int stat: 0x%08x\n",
		   sdhci_readb(host, SDHCI_TIMEOUT_CONTROL),
		   sdhci_readl(host, SDHCI_INT_STATUS));
	SDHCI_DUMP("Int enab:  0x%08x | Sig enab: 0x%08x\n",
		   sdhci_readl(host, SDHCI_INT_ENABLE),
		   sdhci_readl(host, SDHCI_SIGNAL_ENABLE));
	SDHCI_DUMP("ACmd stat: 0x%08x | Slot int: 0x%08x\n",
		   sdhci_readw(host, SDHCI_AUTO_CMD_STATUS),
		   sdhci_readw(host, SDHCI_SLOT_INT_STATUS));
	SDHCI_DUMP("Caps:      0x%08x | Caps_1:   0x%08x\n",
		   sdhci_readl(host, SDHCI_CAPABILITIES),
		   sdhci_readl(host, SDHCI_CAPABILITIES_1));
	SDHCI_DUMP("Cmd:       0x%08x | Max curr: 0x%08x\n",
		   sdhci_readw(host, SDHCI_COMMAND),
		   sdhci_readl(host, SDHCI_MAX_CURRENT));
	SDHCI_DUMP("Resp[0]:   0x%08x | Resp[1]:  0x%08x\n",
		   sdhci_readl(host, SDHCI_RESPONSE),
		   sdhci_readl(host, SDHCI_RESPONSE + 4));
	SDHCI_DUMP("Resp[2]:   0x%08x | Resp[3]:  0x%08x\n",
		   sdhci_readl(host, SDHCI_RESPONSE + 8),
		   sdhci_readl(host, SDHCI_RESPONSE + 12));
	SDHCI_DUMP("Host ctl2: 0x%08x\n",
		   sdhci_readw(host, SDHCI_HOST_CONTROL2));

	if (host->flags & SDHCI_USE_ADMA) {
		if (host->flags & SDHCI_USE_64_BIT_DMA) {
			SDHCI_DUMP("ADMA Err:  0x%08x | ADMA Ptr: 0x%08x%08x\n",
				   sdhci_readl(host, SDHCI_ADMA_ERROR),
				   sdhci_readl(host, SDHCI_ADMA_ADDRESS_HI),
				   sdhci_readl(host, SDHCI_ADMA_ADDRESS));
		} else {
			SDHCI_DUMP("ADMA Err:  0x%08x | ADMA Ptr: 0x%08x\n",
				   sdhci_readl(host, SDHCI_ADMA_ERROR),
				   sdhci_readl(host, SDHCI_ADMA_ADDRESS));
		}
	}

	if (host->ops->dump_vendor_regs)
		host->ops->dump_vendor_regs(host);

	SDHCI_DUMP("============================================\n");
}



static rt_bool_t sdhci_present_error(struct sdhci_host *host,
				struct rt_mmcsd_cmd *cmd, rt_bool_t present)
{
	if (!present || host->flags & SDHCI_DEVICE_DEAD) {
		cmd->err = -ENOMEDIUM;
		return RT_TRUE;
	}

	return RT_FALSE;
}

//------------------------------------------------------------------------------------------------------------------------------------//
