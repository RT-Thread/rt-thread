/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-20     rcitach      first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "interrupt.h"
#include "board.h"
#include "drv_can.h"
#include "drv_gpio.h"

#define DBG_TAG "drv.can"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#define CAN_RET(_err, _msg) \
    do { LOG_E("%s ret=%d", (_msg), (int)(_err)); return (_err); } while (0)
#define CAN_RET_FMT(_err, _fmt, ...) \
    do { LOG_E(_fmt " ret=%d", ##__VA_ARGS__, (int)(_err)); return (_err); } while (0)


#define S100_CAN_CLK_WORKAROUND_BASE         (0x2370007CU)
#define S100_CAN_CLK_WORKAROUND_COUNT        (10U)
#define S100_CAN_CLK_WORKAROUND_ENABLE       (0x8000U)

#define S100_MCU2CAN_STB_N_PIN               (6U)
#define S100_CAN_DEFAULT_CLK_HZ              (40000000UL)

#define S100_CAN5_BASE                         (0x23720000UL)
#define S100_CAN6_BASE                         (0x23730000UL)
#define S100_CAN7_BASE                         (0x23740000UL)
#define S100_CAN8_BASE                         (0x23750000UL)
#define S100_CAN9_BASE                         (0x23760000UL)

#define S100_CAN5_IRQ                          (136U)
#define S100_CAN6_IRQ                          (140U)
#define S100_CAN7_IRQ                          (144U)
#define S100_CAN8_IRQ                          (148U)
#define S100_CAN9_IRQ                          (152U)

#define S100_CAN_MAX_MB_NUM                    (128U)
#define S100_CAN_MAX_MB_INDEX                  (55U)
#define S100_CAN_BASIC_TX_MB_START             (16U)

#define S100_CAN_DEFAULT_PRESDIV             (1U)
#define S100_CAN_DEFAULT_PROPSEG             (7U)
#define S100_CAN_DEFAULT_PSEG1               (8U)
#define S100_CAN_DEFAULT_PSEG2               (4U)
#define S100_CAN_DEFAULT_RJW                 (2U)

#define S100_CAN_BASIC_TIMEOUT_LOOP          (1000000U)
#define S100_CAN_STD_ID_SHIFT                (18U)
#define S100_CAN_STD_ID_MASK                 (0x7FFU)

#define S100_CAN_MB_CODE_TX_INACTIVE         (0x8U)
#define S100_CAN_MB_CODE_TX_DATA             (0xCU)

#define S100_CAN_ENHANCED_FILTER_STD_SHIFT1  (0U)
#define S100_CAN_ENHANCED_FILTER_STD_SHIFT2  (16U)
#define S100_CAN_ENHANCED_FILTER_FSCH_SHIFT  (30U)
#define S100_CAN_ENHANCED_FILTER_STD_MASK    (0x7FFU)

#define S100_CAN_MB_CODE_SHIFT               24U

struct s100_can_basic_frame
{
    rt_uint32_t cs;
    rt_uint32_t id;
    rt_uint32_t data0;
    rt_uint32_t data1;
};
typedef struct s100_can_basic_frame s100_can_mb_t;

struct s100_can_basic_baudrate_cfg
{
    rt_uint32_t presdiv;
    rt_uint32_t propseg;
    rt_uint32_t pseg1;
    rt_uint32_t pseg2;
    rt_uint32_t rjw;
    rt_bool_t loopback;
};

struct s100_can_basic_state
{
    struct rt_ringbuffer rx_rb;
    rt_uint8_t rx_rb_pool[S100_CAN_BASIC_TX_MB_START * sizeof(struct s100_can_basic_frame)];

    rt_uint8_t tx_done;
    rt_uint8_t ehfifo_enabled;
    rt_uint16_t rx_overrun;
};

struct s100_can_basic
{
    const char *name;
    s100_can_regs_t *regs;
    rt_int32_t irqno;
    rt_uint8_t ctrl_id;
    rt_uint8_t irq_inited;
    rt_uint32_t irq_mask_flags;
    struct s100_can_basic_state state;
#ifdef RT_CAN_USING_HDR
    rt_uint8_t filter_valid;
    struct rt_can_filter_item filter;
#endif
    struct rt_can_device can_dev;
};

static struct s100_can_basic s100_can_basics[] =
{
#ifdef BSP_USING_CAN5
    {
        .name = "can5",
        .regs = (s100_can_regs_t *)S100_CAN5_BASE,
        .irqno = S100_CAN5_IRQ,
        .ctrl_id = 5U,
    },
#endif
#ifdef BSP_USING_CAN6
    {
        .name = "can6",
        .regs = (s100_can_regs_t *)S100_CAN6_BASE,
        .irqno = S100_CAN6_IRQ,
        .ctrl_id = 6U,
    },
#endif
#ifdef BSP_USING_CAN7
    {
        .name = "can7",
        .regs = (s100_can_regs_t *)S100_CAN7_BASE,
        .irqno = S100_CAN7_IRQ,
        .ctrl_id = 7U,
    },
#endif
#ifdef BSP_USING_CAN8
    {
        .name = "can8",
        .regs = (s100_can_regs_t *)S100_CAN8_BASE,
        .irqno = S100_CAN8_IRQ,
        .ctrl_id = 8U,
    },
#endif
#ifdef BSP_USING_CAN9
    {
        .name = "can9",
        .regs = (s100_can_regs_t *)S100_CAN9_BASE,
        .irqno = S100_CAN9_IRQ,
        .ctrl_id = 9U,
    },
#endif
};

static inline s100_can_mb_t *s100_can_basic_mb(s100_can_regs_t *base, rt_uint32_t mb_index)
{
    return (s100_can_mb_t *)((rt_uintptr_t)base +
                             FLEXCAN_IP_FEATURE_RAM_OFFSET +
                             (mb_index * sizeof(s100_can_mb_t)));
}

static inline rt_uint32_t s100_can_basic_tx_box_to_mb(rt_uint32_t boxno)
{
    return S100_CAN_BASIC_TX_MB_START + boxno;
}

static void s100_can_clear_ram_words(volatile rt_uint32_t *ram, rt_uint32_t count)
{
    rt_uint32_t i;

    for (i = 0U; i < count; i++)
    {
        ram[i] = 0U;
    }
}

static rt_bool_t s100_can_basic_wait_set(volatile rt_uint32_t *reg, rt_uint32_t mask, rt_bool_t set)
{
    rt_uint32_t timeout = S100_CAN_BASIC_TIMEOUT_LOOP;

    while (timeout > 0U)
    {
        if (set != RT_FALSE)
        {
            if ((*reg & mask) == mask)
            {
                return RT_TRUE;
            }
        }
        else
        {
            if ((*reg & mask) == 0U)
            {
                return RT_TRUE;
            }
        }
        timeout--;
    }

    return RT_FALSE;
}

static rt_err_t s100_can_basic_enter_freeze(s100_can_regs_t *base)
{
    base->MCR = (base->MCR & ~FLEXCAN_MCR_FRZ_MASK) | FLEXCAN_MCR_FRZ(1U);
    base->MCR = (base->MCR & ~FLEXCAN_MCR_HALT_MASK) | FLEXCAN_MCR_HALT(1U);

    if (((base->MCR & FLEXCAN_MCR_MDIS_MASK) >> FLEXCAN_MCR_MDIS_SHIFT) != 0U)
    {
        base->MCR &= ~FLEXCAN_MCR_MDIS_MASK;
    }

    if (s100_can_basic_wait_set(&base->MCR, FLEXCAN_MCR_FRZACK_MASK, RT_TRUE) == RT_FALSE)
    {
        CAN_RET(-RT_ETIMEOUT, "enter freeze timeout");
    }

    return RT_EOK;
}

static rt_err_t s100_can_basic_exit_freeze(s100_can_regs_t *base)
{
    base->MCR = (base->MCR & ~FLEXCAN_MCR_HALT_MASK) | FLEXCAN_MCR_HALT(0U);
    if (s100_can_basic_wait_set(&base->MCR, FLEXCAN_MCR_FRZACK_MASK, RT_FALSE) == RT_FALSE)
    {
        CAN_RET(-RT_ETIMEOUT, "exit freeze timeout");
    }

    return RT_EOK;
}

static rt_err_t s100_can_basic_stop(s100_can_regs_t *base)
{
    if (0U == ((base->MCR & FLEXCAN_MCR_MDIS_MASK) >> FLEXCAN_MCR_MDIS_SHIFT))
    {
        base->MCR = (base->MCR & ~FLEXCAN_MCR_MDIS_MASK) | FLEXCAN_MCR_MDIS(1U);
        if (s100_can_basic_wait_set(&base->MCR, FLEXCAN_MCR_MDIS_MASK, RT_TRUE) == RT_FALSE)
        {
            CAN_RET(-RT_ETIMEOUT, "stop controller timeout");
        }
    }

    return RT_EOK;
}

static rt_err_t s100_can_basic_soft_reset(s100_can_regs_t *base)
{
    base->MCR = (base->MCR & ~FLEXCAN_MCR_SOFTRST_MASK) | FLEXCAN_MCR_SOFTRST(1U);
    if (s100_can_basic_wait_set(&base->MCR, FLEXCAN_MCR_SOFTRST_MASK, RT_FALSE) == RT_FALSE)
    {
        CAN_RET(-RT_ETIMEOUT, "soft reset timeout");
    }

    return RT_EOK;
}

static void s100_can_basic_init_ecc_req_ram(s100_can_regs_t *base)
{
    volatile rt_uint32_t *ram;

    ram = (volatile rt_uint32_t *)((rt_uintptr_t)base + FLEXCAN_IP_FEATURE_ENHANCED_FIFO_RAM_OFFSET);
    s100_can_clear_ram_words(ram, FLEXCAN_IP_FEATURE_ENHANCED_FIFO_RAM_COUNT);

    ram = (volatile rt_uint32_t *)((rt_uintptr_t)base + FLEXCAN_IP_FEATURE_ENHANCED_FIFO_FILTER_RAM_OFFSET);
    s100_can_clear_ram_words(ram, FLEXCAN_ERFFEL_COUNT);

    ram = (volatile rt_uint32_t *)base->RESERVED_4;
    s100_can_clear_ram_words(ram, FLEXCAN_IP_FEATURE_SMB_1_RAM_COUNT);

    ram = (volatile rt_uint32_t *)((rt_uintptr_t)base + FLEXCAN_IP_FEATURE_SMB_2_RAM_OFFSET);
    s100_can_clear_ram_words(ram, FLEXCAN_IP_FEATURE_SMB_2_RAM_COUNT);

    ram = (volatile rt_uint32_t *)((rt_uintptr_t)base + FLEXCAN_IP_FEATURE_RXSMB_TIMESTAMP_RAM_OFFSET);
    s100_can_clear_ram_words(ram, FLEXCAN_IP_FEATURE_RXSMB_TIMESTAMP_RAM_COUNT);

    s100_can_clear_ram_words(base->HR_TIME_STAMP, FLEXCAN_HR_TIME_STAMP_COUNT);
}

static void s100_can_basic_init_flexcan_ram(s100_can_regs_t *base)
{
    volatile rt_uint32_t *ram;

    ram = (volatile rt_uint32_t *)((rt_uintptr_t)base + FLEXCAN_IP_FEATURE_RAM_OFFSET);
    s100_can_clear_ram_words(ram, S100_CAN_MAX_MB_NUM * 4U);
    s100_can_clear_ram_words(base->RXIMR, S100_CAN_MAX_MB_NUM);

    base->CTRL2 = (base->CTRL2 & ~FLEXCAN_CTRL2_WRMFRZ_MASK) | FLEXCAN_CTRL2_WRMFRZ(1U);

    base->RXMGMASK = 0U;
    base->RXFGMASK = 0U;
    base->RX14MASK = 0U;
    base->RX15MASK = 0U;

    s100_can_basic_init_ecc_req_ram(base);
    base->CTRL2 = (base->CTRL2 & ~FLEXCAN_CTRL2_WRMFRZ_MASK) | FLEXCAN_CTRL2_WRMFRZ(0U);
}

static void s100_can_basic_set_mem_error_detection(s100_can_regs_t *base, rt_uint32_t eccdis)
{
    base->CTRL2 |= FLEXCAN_CTRL2_ECRWRE_MASK;
    base->MECR = 0U;
    base->MECR |= FLEXCAN_MECR_ECCDIS(eccdis);
    base->CTRL2 &= ~FLEXCAN_CTRL2_ECRWRE_MASK;
}

static rt_uint32_t s100_can_basic_build_mb_cs(rt_uint32_t code, rt_uint32_t dlc, rt_bool_t ide, rt_bool_t rtr)
{
    rt_uint32_t cs = 0U;

    cs |= ((code & 0x0FU) << 24U);
    cs |= ((dlc & 0x0FU) << 16U);
    if (ide != RT_FALSE)
    {
        cs |= (1UL << 21) | (1UL << 22);
    }

    if (rtr != RT_FALSE)
    {
        cs |= (1UL << 20);
    }

    return cs;
}

static void s100_can_basic_config_ehrxfifo_filters_all_std(struct s100_can_basic *ctrl)
{
    ctrl->regs->ERFFEL[0] =
        ((0U & S100_CAN_ENHANCED_FILTER_STD_MASK) << S100_CAN_ENHANCED_FILTER_STD_SHIFT1) |
        ((S100_CAN_STD_ID_MASK & S100_CAN_ENHANCED_FILTER_STD_MASK) << S100_CAN_ENHANCED_FILTER_STD_SHIFT2) |
        (1U << S100_CAN_ENHANCED_FILTER_FSCH_SHIFT);
}

static void s100_can_basic_read_ehrxfifo(struct s100_can_basic *ctrl, struct s100_can_basic_frame *frame)
{
    volatile const rt_uint32_t *fifo_ram;

    fifo_ram = (volatile const rt_uint32_t *)((rt_uintptr_t)ctrl->regs + FLEXCAN_IP_FEATURE_ENHANCED_FIFO_RAM_OFFSET);

    frame->cs = fifo_ram[0];
    frame->id = fifo_ram[1];
    frame->data0 = fifo_ram[2];
    frame->data1 = fifo_ram[3];
}

static rt_err_t s100_can_basic_init_ehrxfifo(struct s100_can_basic *ctrl,
                                             rt_uint32_t numOfStdIDFilters,
                                             rt_uint32_t numOfExtIDFilters,
                                             rt_uint32_t numOfWatermark)
{
    rt_uint32_t NumOfEnhancedFilters = 0U;
    s100_can_regs_t *base = ctrl->regs;

    /* NumOfEnhancedFilters equals (numOfStdIDFilters/2) + numOfExtIDFilters - 1u */
    NumOfEnhancedFilters = (numOfStdIDFilters >> 1u) + numOfExtIDFilters - 1u;
    if ((0U == numOfStdIDFilters) && (0U == numOfExtIDFilters))
    {
        CAN_RET(-RT_ERROR, "ehrxfifo invalid filter count");
    }
    /* If the no of Std Filters is odd */
    if (1U == (numOfStdIDFilters & 1U))
    {
        CAN_RET(-RT_ERROR, "ehrxfifo std filter count must be even");
    }
    /*Enhanced RX FIFO and Legacy RX FIFO cannot be enabled at the same time.*/
    if (FLEXCAN_MCR_RFEN_MASK == (base->MCR & FLEXCAN_MCR_RFEN_MASK))
    {
        CAN_RET(-RT_ERROR, "ehrxfifo conflicts with legacy rxfifo");
    }

    base->ERFIER = 0U;
    /* Enable Enhanced Rx FIFO */
    base->ERFCR = (base->ERFCR & ~FLEXCAN_ERFCR_ERFEN_MASK) | FLEXCAN_ERFCR_ERFEN(1U);
    /* Reset Enhanced Rx FIFO engine */
    base->ERFSR = (base->ERFSR & ~FLEXCAN_ERFSR_ERFCLR_MASK) | FLEXCAN_ERFSR_ERFCLR(1U);
    /* Clear the status bits of the Enhanced RX FIFO */
    base->ERFSR = FLEXCAN_ERFSR_ERFUFW_MASK |
                  FLEXCAN_ERFSR_ERFOVF_MASK |
                  FLEXCAN_ERFSR_ERFWMI_MASK |
                  FLEXCAN_ERFSR_ERFDA_MASK;
    /* Set the total number of enhanced Rx FIFO filter elements */
    base->ERFCR = (base->ERFCR & ~FLEXCAN_ERFCR_NFE_MASK) | ((NumOfEnhancedFilters << FLEXCAN_ERFCR_NFE_SHIFT) & FLEXCAN_ERFCR_NFE_MASK);
    /* Set the number of extended ID filter elements */
    base->ERFCR = (base->ERFCR & ~FLEXCAN_ERFCR_NEXIF_MASK) | ((numOfExtIDFilters << FLEXCAN_ERFCR_NEXIF_SHIFT) & FLEXCAN_ERFCR_NEXIF_MASK);
    /* Set the Enhanced Rx FIFO watermark */
    base->ERFCR = (base->ERFCR & ~FLEXCAN_ERFCR_ERFWM_MASK) | ((numOfWatermark << FLEXCAN_ERFCR_ERFWM_SHIFT) & FLEXCAN_ERFCR_ERFWM_MASK);
    s100_can_basic_config_ehrxfifo_filters_all_std(ctrl);

    return RT_EOK;
}

static void s100_can_basic_init_tx_mb(struct s100_can_basic *ctrl)
{
    rt_uint32_t i;

    for (i = S100_CAN_BASIC_TX_MB_START; i < S100_CAN_MAX_MB_INDEX; i++)
    {
        s100_can_mb_t *mb = s100_can_basic_mb(ctrl->regs, i);

        mb->cs = 0U;
        mb->id = 0U;
        mb->data0 = 0U;
        mb->data1 = 0U;
        mb->cs = s100_can_basic_build_mb_cs(S100_CAN_MB_CODE_TX_INACTIVE, 0U, RT_FALSE, RT_FALSE);
    }
}

static rt_err_t s100_can_basic_wait_ready(s100_can_regs_t *base)
{
    rt_uint32_t timeout = S100_CAN_BASIC_TIMEOUT_LOOP;

    while (timeout > 0U)
    {
        if (((base->MCR & FLEXCAN_MCR_NOTRDY_MASK) == 0U) &&
            ((base->ESR1 & FLEXCAN_ESR1_SYNCH_MASK) != 0U))
        {
            return RT_EOK;
        }
        timeout--;
    }

    CAN_RET(-RT_ETIMEOUT, "wait ready timeout");
}

static void s100_can_basic_update_irq_mask(struct s100_can_basic *ctrl, rt_uint32_t flags, rt_bool_t enable)
{
    rt_uint32_t imask1_tx = 0U;
    rt_uint32_t imask2_tx = 0U;
    rt_uint32_t i;

    if ((flags & RT_DEVICE_FLAG_INT_TX) != 0U)
    {
        for (i = S100_CAN_BASIC_TX_MB_START; i < 32U; i++)
        {
            imask1_tx |= (1UL << i);
        }

        for (i = 0U; i < (S100_CAN_MAX_MB_INDEX - 32U); i++)
        {
            imask2_tx |= (1UL << i);
        }

        if (enable != RT_FALSE)
        {
            ctrl->regs->IMASK1 |= imask1_tx;
            ctrl->regs->IMASK2 |= imask2_tx;
        }
        else
        {
            ctrl->regs->IMASK1 &= ~imask1_tx;
            ctrl->regs->IMASK2 &= ~imask2_tx;
        }
    }

    if ((flags & RT_DEVICE_FLAG_INT_RX) != 0U)
    {
        if (enable != RT_FALSE)
        {
            ctrl->regs->ERFIER |= FLEXCAN_ERFIER_ERFDAIE_MASK |
                                  FLEXCAN_ERFIER_ERFOVFIE_MASK |
                                  FLEXCAN_ERFIER_ERFUFWIE_MASK;
        }
        else
        {
            ctrl->regs->ERFIER &= ~(FLEXCAN_ERFIER_ERFDAIE_MASK |
                                    FLEXCAN_ERFIER_ERFOVFIE_MASK |
                                    FLEXCAN_ERFIER_ERFUFWIE_MASK);
        }
    }

    if ((flags & RT_DEVICE_CAN_INT_ERR) != 0U)
    {
        if (enable != RT_FALSE)
        {
            ctrl->regs->CTRL1 |= FLEXCAN_CTRL1_ERRMSK_MASK | FLEXCAN_CTRL1_BOFFMSK_MASK;
        }
        else
        {
            ctrl->regs->CTRL1 &= ~(FLEXCAN_CTRL1_ERRMSK_MASK | FLEXCAN_CTRL1_BOFFMSK_MASK);
        }
    }
}

static rt_err_t s100_can_basic_calc_baudrate_params(struct s100_can_basic *ctrl,
                                                    const struct can_configure *cfg,
                                                    struct s100_can_basic_baudrate_cfg *baud_cfg)
{
    rt_uint32_t clk_hz;
    rt_uint32_t baud;
    rt_uint32_t tq_num;
    rt_uint32_t presdiv;

    if ((cfg == RT_NULL) || (baud_cfg == RT_NULL))
    {
        CAN_RET(-RT_EINVAL, "calc baudrate params invalid argument");
    }

    baud = cfg->baud_rate;
    clk_hz = S100_CAN_DEFAULT_CLK_HZ;

    switch (baud)
    {
    case CAN1MBaud:
    case CAN500kBaud:
    case CAN250kBaud:
    case CAN125kBaud:
    case CAN100kBaud:
    case CAN50kBaud:
    case CAN20kBaud:
    case CAN10kBaud:
        tq_num = 20U;
        baud_cfg->propseg = 7U;
        baud_cfg->pseg1 = 8U;
        baud_cfg->pseg2 = 4U;
        baud_cfg->rjw = 2U;
        break;
    case CAN800kBaud:
        tq_num = 10U;
        baud_cfg->propseg = 2U;
        baud_cfg->pseg1 = 5U;
        baud_cfg->pseg2 = 2U;
        baud_cfg->rjw = 2U;
        break;
    default:
        CAN_RET_FMT(-RT_EINVAL, "unsupported nominal baud=%lu", (unsigned long)baud);
    }

    if ((baud_cfg->propseg + baud_cfg->pseg1) <= baud_cfg->pseg2)
    {
        CAN_RET_FMT(-RT_EINVAL, "invalid timing split prop=%lu pseg1=%lu pseg2=%lu",
                    (unsigned long)baud_cfg->propseg,
                    (unsigned long)baud_cfg->pseg1,
                    (unsigned long)baud_cfg->pseg2);
    }

    if (baud_cfg->rjw > ((baud_cfg->pseg1 < baud_cfg->pseg2) ? baud_cfg->pseg1 : baud_cfg->pseg2))
    {
        CAN_RET_FMT(-RT_EINVAL, "invalid sjw=%lu pseg1=%lu pseg2=%lu",
                    (unsigned long)baud_cfg->rjw,
                    (unsigned long)baud_cfg->pseg1,
                    (unsigned long)baud_cfg->pseg2);
    }

    if ((clk_hz % (baud * tq_num)) != 0U)
    {
        CAN_RET_FMT(-RT_EINVAL, "clock not divisible clk=%lu baud=%lu tq=%lu",
                    (unsigned long)clk_hz, (unsigned long)baud, (unsigned long)tq_num);
    }

    presdiv = clk_hz / (baud * tq_num);
    if ((presdiv == 0U) || (presdiv > 1024U))
    {
        CAN_RET_FMT(-RT_EINVAL, "invalid presdiv=%lu baud=%lu tq=%lu",
                    (unsigned long)presdiv, (unsigned long)baud, (unsigned long)tq_num);
    }

    baud_cfg->presdiv = presdiv;
    return RT_EOK;
}

static void s100_can_basic_program_baudrate(struct s100_can_basic *ctrl,
                                            const struct s100_can_basic_baudrate_cfg *baud_cfg)
{
    rt_uint32_t ctrl1 = 0U;
    rt_uint32_t cbt = 0U;

    ctrl1 |= FLEXCAN_CTRL1_ERRMSK(1U);
    ctrl1 |= FLEXCAN_CTRL1_BOFFMSK(1U);

    if (baud_cfg->loopback != RT_FALSE)
    {
        ctrl1 |= FLEXCAN_CTRL1_LPB(1U);
    }

    ctrl->regs->CTRL1 = ctrl1;

    cbt |= FLEXCAN_CBT_BTF(1U);
    cbt |= FLEXCAN_CBT_EPRESDIV(baud_cfg->presdiv - 1U);
    cbt |= FLEXCAN_CBT_ERJW(baud_cfg->rjw - 1U);
    cbt |= FLEXCAN_CBT_EPROPSEG(baud_cfg->propseg - 1U);
    cbt |= FLEXCAN_CBT_EPSEG1(baud_cfg->pseg1 - 1U);
    cbt |= FLEXCAN_CBT_EPSEG2(baud_cfg->pseg2 - 1U);
    ctrl->regs->CBT = cbt;
}

static void s100_can_basic_apply_baudrate(struct s100_can_basic *ctrl, const struct can_configure *cfg)
{
    struct s100_can_basic_baudrate_cfg baud_cfg;

    baud_cfg.presdiv = S100_CAN_DEFAULT_PRESDIV;
    baud_cfg.propseg = S100_CAN_DEFAULT_PROPSEG;
    baud_cfg.pseg1 = S100_CAN_DEFAULT_PSEG1;
    baud_cfg.pseg2 = S100_CAN_DEFAULT_PSEG2;
    baud_cfg.rjw = S100_CAN_DEFAULT_RJW;
    baud_cfg.loopback = ((cfg->mode & RT_CAN_MODE_LOOPBACK) != 0U) ? RT_TRUE : RT_FALSE;

    if (s100_can_basic_calc_baudrate_params(ctrl, cfg, &baud_cfg) != RT_EOK)
    {
        baud_cfg.presdiv = S100_CAN_DEFAULT_PRESDIV;
        baud_cfg.propseg = S100_CAN_DEFAULT_PROPSEG;
        baud_cfg.pseg1 = S100_CAN_DEFAULT_PSEG1;
        baud_cfg.pseg2 = S100_CAN_DEFAULT_PSEG2;
        baud_cfg.rjw = S100_CAN_DEFAULT_RJW;
    }

    s100_can_basic_program_baudrate(ctrl, &baud_cfg);
}

static rt_err_t s100_can_basic_apply_baudrate_runtime(struct s100_can_basic *ctrl, rt_uint32_t baud)
{
    struct can_configure cfg;
    struct s100_can_basic_baudrate_cfg baud_cfg;
    rt_err_t ret;

    cfg = ctrl->can_dev.config;
    cfg.baud_rate = baud;

    baud_cfg.presdiv = S100_CAN_DEFAULT_PRESDIV;
    baud_cfg.propseg = S100_CAN_DEFAULT_PROPSEG;
    baud_cfg.pseg1 = S100_CAN_DEFAULT_PSEG1;
    baud_cfg.pseg2 = S100_CAN_DEFAULT_PSEG2;
    baud_cfg.rjw = S100_CAN_DEFAULT_RJW;
    baud_cfg.loopback = ((cfg.mode & RT_CAN_MODE_LOOPBACK) != 0U) ? RT_TRUE : RT_FALSE;

    ret = s100_can_basic_calc_baudrate_params(ctrl, &cfg, &baud_cfg);
    if (ret != RT_EOK)
    {
        CAN_RET_FMT(ret, "apply baudrate runtime calc params failed baud=%lu", (unsigned long)baud);
    }

    ret = s100_can_basic_enter_freeze(ctrl->regs);
    if (ret != RT_EOK)
    {
        CAN_RET(ret, "apply baudrate runtime enter freeze failed");
    }

    s100_can_basic_program_baudrate(ctrl, &baud_cfg);
    ret = s100_can_basic_exit_freeze(ctrl->regs);
    if (ret != RT_EOK)
    {
        CAN_RET(ret, "apply baudrate runtime exit freeze failed");
    }
    return RT_EOK;
}

static rt_err_t s100_can_basic_apply_mode(struct s100_can_basic *ctrl, rt_uint32_t mode)
{
    s100_can_regs_t *base = ctrl->regs;
    rt_uint32_t mcr;
    rt_uint32_t ctrl1;
    rt_bool_t loopback;
    rt_err_t ret;

    loopback = ((mode & RT_CAN_MODE_LOOPBACK) != 0U) ? RT_TRUE : RT_FALSE;

    ret = s100_can_basic_enter_freeze(base);
    if (ret != RT_EOK)
    {
        CAN_RET(ret, "apply mode enter freeze failed");
    }

    mcr = base->MCR;
    mcr &= ~FLEXCAN_MCR_SRXDIS_MASK;
    if (loopback == RT_FALSE)
    {
        mcr |= FLEXCAN_MCR_SRXDIS(1U);
    }
    base->MCR = mcr;

    ctrl1 = base->CTRL1;
    ctrl1 &= ~FLEXCAN_CTRL1_LPB_MASK;
    if (loopback != RT_FALSE)
    {
        ctrl1 |= FLEXCAN_CTRL1_LPB(1U);
    }
    base->CTRL1 = ctrl1;

    ret = s100_can_basic_exit_freeze(base);
    if (ret != RT_EOK)
    {
        CAN_RET(ret, "apply mode exit freeze failed");
    }
    return RT_EOK;
}

static inline void s100_can_setclksrc(s100_can_regs_t *base, rt_bool_t enable)
{
    base->CTRL1 = (base->CTRL1 & ~FLEXCAN_CTRL1_CLKSRC_MASK) | FLEXCAN_CTRL1_CLKSRC(enable ? 1UL : 0UL);
}


static rt_bool_t s100_can_basic_is_enabled(s100_can_regs_t *base)
{
    return (((base->MCR & FLEXCAN_MCR_MDIS_MASK) >> FLEXCAN_MCR_MDIS_SHIFT) != 0U) ? RT_FALSE : RT_TRUE;
}

static rt_err_t s100_can_basic_init(struct s100_can_basic *ctrl, struct can_configure *cfg)
{
    rt_uint32_t mcr;
    rt_err_t ret;
    s100_can_regs_t *base = ctrl->regs;
    rt_bool_t loopback;

    if (s100_can_basic_is_enabled(base) != RT_FALSE)
    {
        ret = s100_can_basic_enter_freeze(base);
        if (ret != RT_EOK)
        {
            CAN_RET(ret, "init enter freeze before stop failed");
        }
        ret = s100_can_basic_stop(base);
        if (ret != RT_EOK)
        {
            CAN_RET(ret, "init stop failed");
        }
    }

    s100_can_setclksrc(base, RT_FALSE);
    base->MCR &= ~FLEXCAN_MCR_MDIS_MASK;
    ret = s100_can_basic_soft_reset(base);
    if (ret != RT_EOK)
    {
        CAN_RET(ret, "init soft reset failed");
    }

    ret = s100_can_basic_enter_freeze(base);
    if (ret != RT_EOK)
    {
        CAN_RET(ret, "init enter freeze failed");
    }

    mcr = base->MCR;
    mcr &= ~(FLEXCAN_MCR_MAXMB_MASK | FLEXCAN_MCR_SRXDIS_MASK);
    mcr |= FLEXCAN_MCR_AEN(1U);
    mcr |= FLEXCAN_MCR_IRMQ(1U);
    mcr |= FLEXCAN_MCR_WRNEN(1U);
    mcr |= FLEXCAN_MCR_MAXMB(S100_CAN_MAX_MB_INDEX);

    loopback = ((cfg->mode & RT_CAN_MODE_LOOPBACK) != 0U) ? RT_TRUE : RT_FALSE;
    if (loopback == RT_FALSE)
    {
        mcr |= FLEXCAN_MCR_SRXDIS(1U);
    }
    base->MCR = mcr;

    s100_can_basic_set_mem_error_detection(base, 0U);
    s100_can_basic_init_flexcan_ram(base);
    s100_can_basic_apply_baudrate(ctrl, cfg);

    base->IMASK1 = 0U;
    base->IMASK2 = 0U;
    base->IFLAG1 = 0xFFFFFFFFU;
    base->IFLAG2 = 0xFFFFFFFFU;
    base->ESR1 = FLEXCAN_IP_ALL_INT;

    s100_can_basic_init_tx_mb(ctrl);
    ctrl->state.ehfifo_enabled = 0U;
    ret = s100_can_basic_init_ehrxfifo(ctrl, 2U, 0U, 1U);
    if (ret != RT_EOK)
    {
        CAN_RET(ret, "init ehrxfifo failed");
    }
    ctrl->state.ehfifo_enabled = 1U;
    ctrl->state.tx_done = 0U;
    ret = s100_can_basic_exit_freeze(base);
    if (ret != RT_EOK)
    {
        CAN_RET(ret, "init exit freeze failed");
    }

    ret = s100_can_basic_wait_ready(base);
    if (ret != RT_EOK)
    {
        CAN_RET(ret, "init wait ready failed");
    }
    return RT_EOK;
}

static rt_err_t s100_can_basic_send_std(struct s100_can_basic *ctrl, rt_uint32_t std_id,
                                        const rt_uint8_t *data, rt_uint8_t len, rt_uint32_t boxno)
{
    s100_can_mb_t *mb;
    rt_uint32_t tx_bit;
    rt_uint32_t data0 = 0U;
    rt_uint32_t data1 = 0U;
    rt_uint32_t code;
    rt_uint32_t i;

    if ((data == RT_NULL) || (len > 8U) || (std_id > S100_CAN_STD_ID_MASK))
    {
        CAN_RET_FMT(-RT_EINVAL, "send std invalid args id=0x%lx len=%lu",
                    (unsigned long)std_id, (unsigned long)len);
    }

    if (boxno >= ctrl->can_dev.config.sndboxnumber)
    {
        CAN_RET_FMT(-RT_EINVAL, "send std invalid boxno=%lu sndboxnumber=%lu",
                    (unsigned long)boxno, (unsigned long)ctrl->can_dev.config.sndboxnumber);
    }

    mb = s100_can_basic_mb(ctrl->regs, s100_can_basic_tx_box_to_mb(boxno));
    code = (mb->cs >> S100_CAN_MB_CODE_SHIFT) & 0x0FU;
    if (code != S100_CAN_MB_CODE_TX_INACTIVE)
    {
        CAN_RET_FMT(-RT_EBUSY, "send std mailbox busy boxno=%lu code=0x%lx",
                    (unsigned long)boxno, (unsigned long)code);
    }

    for (i = 0U; i < 4U; i++)
    {
        data0 <<= 8;
        if (i < len)
        {
            data0 |= data[i];
        }
    }

    for (i = 4U; i < 8U; i++)
    {
        data1 <<= 8;
        if (i < len)
        {
            data1 |= data[i];
        }
    }

    ctrl->state.tx_done = 0U;
    mb->cs = s100_can_basic_build_mb_cs(S100_CAN_MB_CODE_TX_INACTIVE, 0U, RT_FALSE, RT_FALSE);
    mb->id = 0U;
    mb->data0 = data0;
    mb->data1 = data1;
    mb->id = (std_id & S100_CAN_STD_ID_MASK) << S100_CAN_STD_ID_SHIFT;
    mb->cs = s100_can_basic_build_mb_cs(S100_CAN_MB_CODE_TX_DATA, len, RT_FALSE, RT_FALSE);

    return RT_EOK;
}

static void s100_can_basic_handle_tx_irq_bank(struct s100_can_basic *ctrl,
                                              volatile rt_uint32_t *iflag_reg,
                                              rt_uint32_t imask,
                                              rt_uint32_t mb_base)
{
    rt_uint32_t pending;
    rt_uint32_t bit;
    rt_uint32_t mb_id;

    pending = (*iflag_reg) & imask;
    while (pending != 0U)
    {
        bit = pending & (~pending + 1U);
        mb_id = mb_base + (rt_uint32_t)__builtin_ctz(bit);

        (void)ctrl->regs->TIMER;
        *iflag_reg = bit;

        if ((mb_id >= S100_CAN_BASIC_TX_MB_START) &&
            (mb_id < S100_CAN_MAX_MB_INDEX))
        {
            ctrl->state.tx_done = 1U;

            if ((ctrl->irq_mask_flags & RT_DEVICE_FLAG_INT_TX) != 0U)
            {
                rt_hw_can_isr(&ctrl->can_dev,
                              RT_CAN_EVENT_TX_DONE | ((mb_id - S100_CAN_BASIC_TX_MB_START) << 8));
            }
        }

        pending &= ~bit;
    }
}

static void s100_can_basic_handle_ehrxfifo_irq(struct s100_can_basic *ctrl)
{
    rt_uint32_t erf_pending;
    struct s100_can_basic_frame frame;
    rt_size_t wr_len;

    if ((ctrl == RT_NULL) || (ctrl->state.ehfifo_enabled == 0U))
    {
        return;
    }

    erf_pending = ctrl->regs->ERFSR & ctrl->regs->ERFIER;

    while ((erf_pending & FLEXCAN_ERFSR_ERFDA_MASK) != 0U)
    {
        s100_can_basic_read_ehrxfifo(ctrl, &frame);

        wr_len = rt_ringbuffer_put(&ctrl->state.rx_rb,
                                   (const rt_uint8_t *)&frame,
                                   sizeof(frame));
        if (wr_len != sizeof(frame))
        {
            ctrl->state.rx_overrun++;

            if ((ctrl->irq_mask_flags & RT_DEVICE_FLAG_INT_RX) != 0U)
            {
                rt_hw_can_isr(&ctrl->can_dev, RT_CAN_EVENT_RXOF_IND | (1U << 8));
            }
        }
        else
        {
            if ((ctrl->irq_mask_flags & RT_DEVICE_FLAG_INT_RX) != 0U)
            {
                rt_hw_can_isr(&ctrl->can_dev, RT_CAN_EVENT_RX_IND | (1U << 8));
            }
        }

        ctrl->regs->ERFSR = FLEXCAN_ERFSR_ERFDA_MASK;

        erf_pending = ctrl->regs->ERFSR & ctrl->regs->ERFIER;
    }

    if ((erf_pending & FLEXCAN_ERFSR_ERFOVF_MASK) != 0U)
    {
        ctrl->regs->ERFSR = FLEXCAN_ERFSR_ERFOVF_MASK;

        if ((ctrl->irq_mask_flags & RT_DEVICE_FLAG_INT_RX) != 0U)
        {
            rt_hw_can_isr(&ctrl->can_dev, RT_CAN_EVENT_RXOF_IND | (1U << 8));
        }
    }

    if ((erf_pending & FLEXCAN_ERFSR_ERFUFW_MASK) != 0U)
    {
        ctrl->regs->ERFSR = FLEXCAN_ERFSR_ERFUFW_MASK;
    }
}

static void s100_can_basic_irq_handler(int vector, void *param)
{
    struct s100_can_basic *ctrl;

    RT_UNUSED(vector);
    ctrl = (struct s100_can_basic *)param;
    if (ctrl == RT_NULL)
    {
        return;
    }

    s100_can_basic_handle_tx_irq_bank(ctrl, &ctrl->regs->IFLAG1, ctrl->regs->IMASK1, 0U);
    s100_can_basic_handle_tx_irq_bank(ctrl, &ctrl->regs->IFLAG2, ctrl->regs->IMASK2, 32U);

    if (ctrl->state.ehfifo_enabled != 0U)
    {
        s100_can_basic_handle_ehrxfifo_irq(ctrl);
    }

    if ((ctrl->regs->ESR1 & (FLEXCAN_ESR1_ERRINT_MASK |
                             FLEXCAN_ESR1_BOFFINT_MASK |
                             FLEXCAN_ESR1_ACKERR_MASK)) != 0U)
    {
        ctrl->regs->ESR1 = FLEXCAN_IP_ALL_INT;

        if ((ctrl->irq_mask_flags & RT_DEVICE_CAN_INT_ERR) != 0U)
        {
            rt_hw_can_isr(&ctrl->can_dev, RT_CAN_EVENT_TX_FAIL | (0U << 8));
        }
    }
}

static rt_err_t s100_can_basic_configure(struct rt_can_device *can, struct can_configure *cfg)
{
    struct s100_can_basic *ctrl;
    rt_err_t ret;

    RT_ASSERT(can != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    if (cfg->sndboxnumber == 0U)
    {
        CAN_RET(-RT_EINVAL, "configure invalid sndboxnumber=0");
    }

    /* TODO legacy RXFIFO 0-S100_CAN_MAX_MB_INDEX */
    if (cfg->sndboxnumber > S100_CAN_MAX_MB_INDEX - S100_CAN_BASIC_TX_MB_START)
    {
        CAN_RET_FMT(-RT_EINVAL, "configure sndboxnumber too large=%lu",
                    (unsigned long)cfg->sndboxnumber);
    }

    if (cfg->msgboxsz == 0U)
    {
        CAN_RET(-RT_EINVAL, "configure invalid msgboxsz=0");
    }

    ctrl = (struct s100_can_basic *)can->parent.user_data;
    if (ctrl == RT_NULL)
    {
        CAN_RET(-RT_EINVAL, "configure null ctrl");
    }

    rt_ringbuffer_init(&ctrl->state.rx_rb,
            ctrl->state.rx_rb_pool,
            sizeof(ctrl->state.rx_rb_pool));

    ctrl->state.rx_overrun = 0U;

    ret = s100_can_basic_init(ctrl,cfg);
    if (ret != RT_EOK)
    {
        CAN_RET_FMT(ret, "configure init failed ctrl=%s", ctrl->name);
    }
    return RT_EOK;
}

static rt_err_t s100_can_basic_control(struct rt_can_device *can, int cmd, void *arg)
{
    struct s100_can_basic *ctrl;

    RT_ASSERT(can != RT_NULL);

    ctrl = (struct s100_can_basic *)can->parent.user_data;
    if (ctrl == RT_NULL)
    {
        CAN_RET(-RT_EINVAL, "control null ctrl");
    }

    switch (cmd)
    {
    case RT_DEVICE_CTRL_SET_INT:
    {
        rt_uint32_t flags = (rt_uint32_t)(rt_uintptr_t)arg;

        ctrl->irq_mask_flags |= flags;
        s100_can_basic_update_irq_mask(ctrl, flags, RT_TRUE);
        return RT_EOK;
    }

    case RT_DEVICE_CTRL_CLR_INT:
    {
        rt_uint32_t flags = (rt_uint32_t)(rt_uintptr_t)arg;

        ctrl->irq_mask_flags &= ~flags;
        s100_can_basic_update_irq_mask(ctrl, flags, RT_FALSE);
        return RT_EOK;
    }

    case RT_CAN_CMD_SET_BAUD:
    {
        rt_uint32_t new_baud = (rt_uint32_t)(rt_uintptr_t)arg;
        rt_err_t ret;

        ret = s100_can_basic_apply_baudrate_runtime(ctrl, new_baud);
        if (ret == RT_EOK)
        {
            can->config.baud_rate = new_baud;
        }

        if (ret != RT_EOK)
        {
            CAN_RET_FMT(ret, "control set baud failed ctrl=%s baud=%lu",
                        ctrl->name, (unsigned long)new_baud);
        }
        return RT_EOK;
    }

    case RT_CAN_CMD_SET_MODE:
    {
        rt_uint32_t new_mode = (rt_uint32_t)(rt_uintptr_t)arg;
        rt_err_t ret;

        ret = s100_can_basic_apply_mode(ctrl, new_mode);
        if (ret == RT_EOK)
        {
            can->config.mode = new_mode;
        }

        if (ret != RT_EOK)
        {
            CAN_RET_FMT(ret, "control set mode failed ctrl=%s mode=%lu",
                        ctrl->name, (unsigned long)new_mode);
        }
        return RT_EOK;
    }

    case RT_CAN_CMD_SET_PRIV:
        can->config.privmode = (rt_uint32_t)(rt_uintptr_t)arg;
        return RT_EOK;

    case RT_CAN_CMD_GET_STATUS:
        if (arg == RT_NULL)
        {
            CAN_RET(-RT_EINVAL, "control get status null arg");
        }
        can->status.snderrcnt = ctrl->regs->ECR & 0xFFU;
        can->status.rcverrcnt = (ctrl->regs->ECR >> 8U) & 0xFFU;
        can->status.errcode = ((ctrl->regs->ESR1 & FLEXCAN_ESR1_BOFFINT_MASK) != 0U) ? BUSOFF : NORMAL;
        rt_memcpy(arg, &can->status, sizeof(can->status));
        return RT_EOK;
    case RT_CAN_CMD_START:
    {
        rt_uint32_t next_status = (rt_uint32_t)(rt_uintptr_t)arg;
        if(next_status == RT_FALSE)
        {
            if(s100_can_basic_is_enabled(ctrl->regs))
            {
                return s100_can_basic_stop(ctrl->regs);
            }
        }
        return RT_EOK;
    }
    default:
        CAN_RET_FMT(-RT_EINVAL, "control unsupported cmd=%d ctrl=%s", cmd, ctrl->name);
    }
    return RT_EOK;
}

static rt_ssize_t s100_can_basic_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno)
{
    struct s100_can_basic *ctrl;
    const struct rt_can_msg *msg;
    rt_uint32_t retry;

    RT_ASSERT(can != RT_NULL);

    ctrl = (struct s100_can_basic *)can->parent.user_data;
    msg = (const struct rt_can_msg *)buf;
    if ((ctrl == RT_NULL) || (msg == RT_NULL))
    {
        CAN_RET(-RT_EINVAL, "sendmsg null ctrl or msg");
    }

    if (boxno >= ctrl->can_dev.config.sndboxnumber)
    {
        CAN_RET_FMT(-RT_EINVAL, "sendmsg invalid boxno=%lu sndboxnumber=%lu",
                    (unsigned long)boxno, (unsigned long)ctrl->can_dev.config.sndboxnumber);
    }

    if ((msg->ide != RT_CAN_STDID) || (msg->rtr != RT_CAN_DTR))
    {
        CAN_RET_FMT(-RT_ENOSYS, "sendmsg unsupported frame ide=%lu rtr=%lu",
                    (unsigned long)msg->ide, (unsigned long)msg->rtr);
    }

    return s100_can_basic_send_std(ctrl, msg->id, msg->data, (rt_uint8_t)msg->len, boxno);
}

static rt_ssize_t s100_can_basic_sendmsg_nonblocking(struct rt_can_device *can, const void *buf)
{
    rt_uint32_t boxno;
    rt_ssize_t ret;

    for (boxno = 0U; boxno < can->config.sndboxnumber; boxno++)
    {
        ret = s100_can_basic_sendmsg(can, buf, boxno);
        if (ret == RT_EOK)
        {
            return RT_EOK;
        }

        if (ret != -RT_EBUSY)
        {
            CAN_RET_FMT(ret, "sendmsg nonblocking failed boxno=%lu", (unsigned long)boxno);
        }
    }

    CAN_RET(-RT_EBUSY, "sendmsg nonblocking all mailboxes busy");
}

static rt_ssize_t s100_can_basic_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    struct s100_can_basic *ctrl;
    struct rt_can_msg *msg;
    struct s100_can_basic_frame frame;
    rt_uint32_t data_word;
    rt_uint32_t i;
    rt_size_t rd_len;
    rt_base_t level;

    RT_ASSERT(can != RT_NULL);

    ctrl = (struct s100_can_basic *)can->parent.user_data;
    msg = (struct rt_can_msg *)buf;

    if ((ctrl == RT_NULL) || (msg == RT_NULL) || (fifo == 0U))
    {
        CAN_RET_FMT(-RT_EINVAL, "recvmsg invalid args ctrl=%p msg=%p fifo=%lu",
                    ctrl, msg, (unsigned long)fifo);
    }

    level = rt_hw_interrupt_disable();
    rd_len = rt_ringbuffer_get(&ctrl->state.rx_rb,
                               (rt_uint8_t *)&frame,
                               sizeof(frame));
    rt_hw_interrupt_enable(level);

    if (rd_len != sizeof(frame))
    {
        CAN_RET(-RT_EEMPTY, "recvmsg ringbuffer empty");
    }

    if ((frame.cs & (1UL << 21)) != 0U)
    {
        CAN_RET(-RT_ENOSYS, "recvmsg ext frame unsupported");
    }

    msg->ide = RT_CAN_STDID;
    msg->rtr = ((frame.cs & (1UL << 20)) != 0U) ? RT_CAN_RTR : RT_CAN_DTR;
    msg->id = (frame.id >> S100_CAN_STD_ID_SHIFT) & S100_CAN_STD_ID_MASK;
    msg->len = (frame.cs >> 16U) & 0x0FU;
    if (msg->len > 8U)
    {
        msg->len = 8U;
    }

#ifdef RT_CAN_USING_HDR
    msg->hdr_index = -1;
#else
    msg->hdr_index = -1;
#endif

    msg->rxfifo = 0;
    msg->priv = 0U;

    data_word = frame.data0;
    for (i = 0U; i < 4U; i++)
    {
        msg->data[i] = (rt_uint8_t)((data_word >> (24U - (i * 8U))) & 0xFFU);
    }

    data_word = frame.data1;
    for (i = 0U; i < 4U; i++)
    {
        msg->data[i + 4U] = (rt_uint8_t)((data_word >> (24U - (i * 8U))) & 0xFFU);
    }

    return RT_EOK;
}

static const struct rt_can_ops s100_can_basic_ops =
{
    .configure = s100_can_basic_configure,
    .control = s100_can_basic_control,
    .sendmsg = s100_can_basic_sendmsg,
    .recvmsg = s100_can_basic_recvmsg,
    .sendmsg_nonblocking = s100_can_basic_sendmsg_nonblocking,
};

static void s100_can_enable_all_clocks_once(void)
{
    volatile rt_uint32_t *reg = (volatile rt_uint32_t *)S100_CAN_CLK_WORKAROUND_BASE;
    rt_uint32_t i;

    for (i = 0U; i < S100_CAN_CLK_WORKAROUND_COUNT; i++)
    {
        reg[i] = S100_CAN_CLK_WORKAROUND_ENABLE;
    }

    __DSB();
}

void s100_can_board_enable_transceiver(void)
{
    /* Equivalent to Dio_WriteChannel(MCU2CAN_STB_N, STD_LOW). */
    s100_gpio_write(S100_MCU2CAN_STB_N_PIN, 0U);
}

#define CAN_DEV_SND_BOX_MAX  32U

int rt_hw_can_init(void)
{
    rt_size_t i;
    rt_err_t ret;
    struct can_configure cfg = CANDEFAULTCONFIG;

    cfg.privmode = RT_CAN_MODE_NOPRIV;
    cfg.ticks = 50U;

    if (cfg.sndboxnumber > CAN_DEV_SND_BOX_MAX)
    {
        rt_uint32_t requested = cfg.sndboxnumber;

        cfg.sndboxnumber = CAN_DEV_SND_BOX_MAX;
        LOG_W("sndboxnumber=%lu exceeds max, capped to %lu",
            (unsigned long)requested,
            (unsigned long)cfg.sndboxnumber);
    }

#ifdef RT_CAN_USING_HDR
    cfg.maxhdr = 1U;
#endif
    s100_can_enable_all_clocks_once();
    s100_can_board_enable_transceiver();

    for (i = 0U; i < (sizeof(s100_can_basics) / sizeof(s100_can_basics[0])); i++)
    {
        s100_can_basics[i].can_dev.config = cfg;
        s100_can_basics[i].can_dev.parent.user_data = &s100_can_basics[i];

        ret = rt_hw_can_register(&s100_can_basics[i].can_dev,
                                 s100_can_basics[i].name,
                                 &s100_can_basic_ops,
                                 &s100_can_basics[i]);
        if (ret != RT_EOK)
        {
            CAN_RET_FMT(ret, "rt_hw_can_register failed ctrl=%s", s100_can_basics[i].name);
        }

        if (s100_can_basics[i].irq_inited == 0U)
        {
            rt_hw_interrupt_install(s100_can_basics[i].irqno,
                                    s100_can_basic_irq_handler,
                                    &s100_can_basics[i],
                                    s100_can_basics[i].name);
            rt_hw_interrupt_set_target_cpus(s100_can_basics[i].irqno, 0U);
            rt_hw_interrupt_umask(s100_can_basics[i].irqno);
            s100_can_basics[i].irq_inited = 1U;
        }
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_can_init);

