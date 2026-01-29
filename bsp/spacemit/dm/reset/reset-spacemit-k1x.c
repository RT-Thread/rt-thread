/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "reset.spacemit.k1x"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <k1-cru.h>
#include <dt-bindings/reset/k1x.h>

struct spacemit_reset_signal
{
    rt_uint32_t offset;
    rt_uint32_t mask;
    rt_uint32_t deassert_val;
    rt_uint32_t assert_val;
    enum cru_type type;
};

struct spacemit_reset
{
    struct rt_reset_controller parent;

    union
    {
        struct
        {
            void *mpmu_base;
            void *apmu_base;
            void *apbc_base;
            void *apbs_base;
            void *ciu_base;
            void *dciu_base;
            void *ddrc_base;
            void *apbc2_base;
            void *rcpu_base;
            void *rcpu2_base;
            void *audpmu_base;
            void *audio_ctrl_base;
        };
        void *mmio[CRU_BASE_TYPE_MAX];
    };

    rt_uint32_t signals_nr;
    const struct spacemit_reset_signal *signals;
};

#define RESET_SIGNAL(name, offset, mask, deassert_val, assert_val, type)    \
[RESET_##name] =                                                            \
{                                                                           \
    offset, mask, deassert_val, assert_val, CRU_BASE_TYPE_##type,           \
}                                                                           \

static const struct spacemit_reset_signal k1x_reset_signals[RESET_NUMBER] =
{
    RESET_SIGNAL(UART1, APBC_UART1_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(UART2, APBC_UART2_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(GPIO, APBC_GPIO_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(PWM0, APBC_PWM0_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), APBC),
    RESET_SIGNAL(PWM1, APBC_PWM1_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), APBC),
    RESET_SIGNAL(PWM2, APBC_PWM2_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), APBC),
    RESET_SIGNAL(PWM3, APBC_PWM3_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), APBC),
    RESET_SIGNAL(PWM4, APBC_PWM4_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), APBC),
    RESET_SIGNAL(PWM5, APBC_PWM5_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), APBC),
    RESET_SIGNAL(PWM6, APBC_PWM6_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), APBC),
    RESET_SIGNAL(PWM7, APBC_PWM7_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), APBC),
    RESET_SIGNAL(PWM8, APBC_PWM8_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), APBC),
    RESET_SIGNAL(PWM9, APBC_PWM9_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), APBC),
    RESET_SIGNAL(PWM10, APBC_PWM10_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), APBC),
    RESET_SIGNAL(PWM11, APBC_PWM11_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), APBC),
    RESET_SIGNAL(PWM12, APBC_PWM12_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), APBC),
    RESET_SIGNAL(PWM13, APBC_PWM13_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), APBC),
    RESET_SIGNAL(PWM14, APBC_PWM14_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), APBC),
    RESET_SIGNAL(PWM15, APBC_PWM15_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), APBC),
    RESET_SIGNAL(PWM16, APBC_PWM16_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), APBC),
    RESET_SIGNAL(PWM17, APBC_PWM17_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), APBC),
    RESET_SIGNAL(PWM18, APBC_PWM18_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), APBC),
    RESET_SIGNAL(PWM19, APBC_PWM19_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), APBC),
    RESET_SIGNAL(SSP3, APBC_SSP3_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(UART3, APBC_UART3_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(RTC, APBC_RTC_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(TWSI0, APBC_TWSI0_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(TIMERS1, APBC_TIMERS1_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(AIB, APBC_AIB_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(TIMERS2, APBC_TIMERS2_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(ONEWIRE, APBC_ONEWIRE_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(SSPA0, APBC_SSPA0_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(SSPA1, APBC_SSPA1_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(DRO, APBC_DRO_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(IR, APBC_IR_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(TWSI1, APBC_TWSI1_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(TSEN, APBC_TSEN_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(TWSI2, APBC_TWSI2_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(TWSI4, APBC_TWSI4_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(TWSI5, APBC_TWSI5_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(TWSI6, APBC_TWSI6_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(TWSI7, APBC_TWSI7_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(TWSI8, APBC_TWSI8_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(IPC_AP2AUD, APBC_IPC_AP2AUD_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(UART4, APBC_UART4_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(UART5, APBC_UART5_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(UART6, APBC_UART6_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(UART7, APBC_UART7_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(UART8, APBC_UART8_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(UART9, APBC_UART9_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    RESET_SIGNAL(CAN0, APBC_CAN0_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC),
    /* MPMU */
    RESET_SIGNAL(WDT, MPMU_WDTPCR, RT_BIT(2), 0, RT_BIT(2), MPMU),
    /* APMU */
    RESET_SIGNAL(JPG, APMU_JPG_CLK_RES_CTRL, RT_BIT(0), RT_BIT(0), 0, APMU),
    RESET_SIGNAL(CSI, APMU_CSI_CCIC2_CLK_RES_CTRL, RT_BIT(1), RT_BIT(1), 0, APMU),
    RESET_SIGNAL(CCIC2_PHY, APMU_CSI_CCIC2_CLK_RES_CTRL, RT_BIT(2), RT_BIT(2), 0, APMU),
    RESET_SIGNAL(CCIC3_PHY, APMU_CSI_CCIC2_CLK_RES_CTRL, RT_BIT(29), RT_BIT(29), 0, APMU),
    RESET_SIGNAL(ISP, APMU_ISP_CLK_RES_CTRL, RT_BIT(0), RT_BIT(0), 0, APMU),
    RESET_SIGNAL(ISP_AHB, APMU_ISP_CLK_RES_CTRL, RT_BIT(3), RT_BIT(3), 0, APMU),
    RESET_SIGNAL(ISP_CI, APMU_ISP_CLK_RES_CTRL, RT_BIT(16), RT_BIT(16), 0, APMU),
    RESET_SIGNAL(ISP_CPP, APMU_ISP_CLK_RES_CTRL, RT_BIT(27), RT_BIT(27), 0, APMU),
    RESET_SIGNAL(LCD, APMU_LCD_CLK_RES_CTRL1, RT_BIT(4), RT_BIT(4), 0, APMU),
    RESET_SIGNAL(DSI_ESC, APMU_LCD_CLK_RES_CTRL1, RT_BIT(3), RT_BIT(3), 0, APMU),
    RESET_SIGNAL(V2D, APMU_LCD_CLK_RES_CTRL1, RT_BIT(27), RT_BIT(27), 0, APMU),
    RESET_SIGNAL(MIPI, APMU_LCD_CLK_RES_CTRL1, RT_BIT(15), RT_BIT(15), 0, APMU),
    RESET_SIGNAL(LCD_SPI, APMU_LCD_SPI_CLK_RES_CTRL, RT_BIT(0), RT_BIT(0), 0, APMU),
    RESET_SIGNAL(LCD_SPI_BUS, APMU_LCD_SPI_CLK_RES_CTRL, RT_BIT(4), RT_BIT(4), 0, APMU),
    RESET_SIGNAL(LCD_SPI_HBUS, APMU_LCD_SPI_CLK_RES_CTRL, RT_BIT(2), RT_BIT(2), 0, APMU),
    RESET_SIGNAL(LCD_MCLK, APMU_LCD_CLK_RES_CTRL2, RT_BIT(9), RT_BIT(9), 0, APMU),
    RESET_SIGNAL(CCIC_4X, APMU_CCIC_CLK_RES_CTRL, RT_BIT(1), RT_BIT(1), 0, APMU),
    RESET_SIGNAL(CCIC1_PHY, APMU_CCIC_CLK_RES_CTRL, RT_BIT(2), RT_BIT(2), 0, APMU),
    RESET_SIGNAL(SDH_AXI, APMU_SDH0_CLK_RES_CTRL, RT_BIT(0), RT_BIT(0), 0, APMU),
    RESET_SIGNAL(SDH0, APMU_SDH0_CLK_RES_CTRL, RT_BIT(1), RT_BIT(1), 0, APMU),
    RESET_SIGNAL(SDH1, APMU_SDH1_CLK_RES_CTRL, RT_BIT(1), RT_BIT(1), 0, APMU),
    RESET_SIGNAL(USB_AXI, APMU_USB_CLK_RES_CTRL, RT_BIT(0), RT_BIT(0), 0, APMU),
    RESET_SIGNAL(USBP1_AXI, APMU_USB_CLK_RES_CTRL, RT_BIT(4), RT_BIT(4), 0, APMU),
    RESET_SIGNAL(COMBO_PHY, APMU_PCIE_CLK_RES_CTRL_0, RT_BIT(8), 0, RT_BIT(8), APMU),
    RESET_SIGNAL(USB3_0, APMU_USB_CLK_RES_CTRL, RT_BIT(9) | RT_BIT(10) | RT_BIT(11), RT_BIT(9) | RT_BIT(10) | RT_BIT(11), 0, APMU),
    RESET_SIGNAL(QSPI, APMU_QSPI_CLK_RES_CTRL, RT_BIT(1), RT_BIT(1), 0, APMU),
    RESET_SIGNAL(QSPI_BUS, APMU_QSPI_CLK_RES_CTRL, RT_BIT(0), RT_BIT(0), 0, APMU),
    RESET_SIGNAL(DMA, APMU_DMA_CLK_RES_CTRL, RT_BIT(0), RT_BIT(0), 0, APMU),
    RESET_SIGNAL(AES, APMU_AES_CLK_RES_CTRL, RT_BIT(4), RT_BIT(4), 0, APMU),
    RESET_SIGNAL(VPU, APMU_VPU_CLK_RES_CTRL, RT_BIT(0), RT_BIT(0), 0, APMU),
    RESET_SIGNAL(GPU, APMU_GPU_CLK_RES_CTRL, RT_BIT(1), RT_BIT(1), 0, APMU),
    RESET_SIGNAL(SDH2, APMU_SDH2_CLK_RES_CTRL, RT_BIT(1), RT_BIT(1), 0, APMU),
    RESET_SIGNAL(MC, APMU_PMUA_MC_CTRL, RT_BIT(0), RT_BIT(0), 0, APMU),
    RESET_SIGNAL(EM_AXI, APMU_PMUA_EM_CLK_RES_CTRL, RT_BIT(0), RT_BIT(0), 0, APMU),
    RESET_SIGNAL(EM, APMU_PMUA_EM_CLK_RES_CTRL, RT_BIT(1), RT_BIT(1), 0, APMU),
    RESET_SIGNAL(AUDIO_SYS, APMU_AUDIO_CLK_RES_CTRL, RT_BIT(0) | RT_BIT(2) | RT_BIT(3), RT_BIT(0) | RT_BIT(2) | RT_BIT(3), 0, APMU),
    RESET_SIGNAL(HDMI, APMU_HDMI_CLK_RES_CTRL, RT_BIT(9), RT_BIT(9), 0, APMU),
    RESET_SIGNAL(PCIE0, APMU_PCIE_CLK_RES_CTRL_0, RT_BIT(3) | RT_BIT(4) | RT_BIT(5) | RT_BIT(8), RT_BIT(3) | RT_BIT(4) | RT_BIT(5), RT_BIT(8), APMU),
    RESET_SIGNAL(PCIE1, APMU_PCIE_CLK_RES_CTRL_1, RT_BIT(3) | RT_BIT(4) | RT_BIT(5) | RT_BIT(8), RT_BIT(3) | RT_BIT(4) | RT_BIT(5), RT_BIT(8), APMU),
    RESET_SIGNAL(PCIE2, APMU_PCIE_CLK_RES_CTRL_2, 0x138, 0x38, 0x100, APMU),
    RESET_SIGNAL(EMAC0, APMU_EMAC0_CLK_RES_CTRL, RT_BIT(1), RT_BIT(1), 0, APMU),
    RESET_SIGNAL(EMAC1, APMU_EMAC1_CLK_RES_CTRL, RT_BIT(1), RT_BIT(1), 0, APMU),
    /* APBC2 */
    RESET_SIGNAL(SEC_UART1, APBC2_UART1_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC2),
    RESET_SIGNAL(SEC_SSP2, APBC2_SSP2_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC2),
    RESET_SIGNAL(SEC_TWSI3, APBC2_TWSI3_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC2),
    RESET_SIGNAL(SEC_RTC, APBC2_RTC_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC2),
    RESET_SIGNAL(SEC_TIMERS0, APBC2_TIMERS0_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC2),
    RESET_SIGNAL(SEC_KPC, APBC2_KPC_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC2),
    RESET_SIGNAL(SEC_GPIO, APBC2_GPIO_CLK_RST, RT_BIT(2), 0, RT_BIT(2), APBC2),
    /* RCPU */
    RESET_SIGNAL(RCPU_HDMIAUDIO, RCPU_HDMI_CLK_RST, RT_BIT(0), RT_BIT(0), 0, RCPU),
    RESET_SIGNAL(RCPU_CAN, RCPU_CAN_CLK_RST, RT_BIT(0), RT_BIT(0), 0, RCPU),
    /* RCPU */
    RESET_SIGNAL(RCPU_I2C0, RCPU_I2C0_CLK_RST, RT_BIT(0), RT_BIT(0), 0, RCPU),
    RESET_SIGNAL(RCPU_SSP0, RCPU_SSP0_CLK_RST, RT_BIT(0), RT_BIT(0), 0, RCPU),
    RESET_SIGNAL(RCPU_IR, RCPU_IR_CLK_RST, RT_BIT(0), RT_BIT(0), 0, RCPU),
    RESET_SIGNAL(RCPU_UART0, RCPU_UART0_CLK_RST, RT_BIT(0), RT_BIT(0), 0, RCPU),
    RESET_SIGNAL(RCPU_UART1, RCPU_UART1_CLK_RST, RT_BIT(0), RT_BIT(0), 0, RCPU),
    /* RCPU2 */
    RESET_SIGNAL(RCPU2_PWM0, RCPU2_PWM0_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), RCPU2),
    RESET_SIGNAL(RCPU2_PWM1, RCPU2_PWM1_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), RCPU2),
    RESET_SIGNAL(RCPU2_PWM2, RCPU2_PWM2_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), RCPU2),
    RESET_SIGNAL(RCPU2_PWM3, RCPU2_PWM3_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), RCPU2),
    RESET_SIGNAL(RCPU2_PWM4, RCPU2_PWM4_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), RCPU2),
    RESET_SIGNAL(RCPU2_PWM5, RCPU2_PWM5_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), RCPU2),
    RESET_SIGNAL(RCPU2_PWM6, RCPU2_PWM6_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), RCPU2),
    RESET_SIGNAL(RCPU2_PWM7, RCPU2_PWM7_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), RCPU2),
    RESET_SIGNAL(RCPU2_PWM8, RCPU2_PWM8_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), RCPU2),
    RESET_SIGNAL(RCPU2_PWM9, RCPU2_PWM9_CLK_RST, RT_BIT(2) | RT_BIT(0), RT_BIT(0), RT_BIT(2), RCPU2),
};

static rt_uint32_t spacemit_reset_read(struct spacemit_reset *reset,
        rt_uint32_t id)
{
    const struct spacemit_reset_signal *signal = &reset->signals[id];

    return HWREG32(reset->mmio[signal->type] + signal->offset);
}

static void spacemit_reset_write(struct spacemit_reset *reset,
        rt_uint32_t value, rt_uint32_t id)
{
    const struct spacemit_reset_signal *signal = &reset->signals[id];

    HWREG32(reset->mmio[signal->type] + signal->offset) = value;
}

static void spacemit_reset_set(struct spacemit_reset *reset,
        rt_uint32_t id, rt_bool_t assert)
{
    rt_uint32_t value = spacemit_reset_read(reset, id);

    value &= ~reset->signals[id].mask;

    if (assert)
    {
        value |=reset->signals[id].assert_val;
    }
    else
    {
        value |= reset->signals[id].deassert_val;
    }

    spacemit_reset_write(reset, value, id);
}

static rt_err_t spacemit_reset_update(struct rt_reset_control *rstc,
        rt_ubase_t id, rt_bool_t assert)
{
    rt_ubase_t level;
    struct spacemit_reset *reset = rstc->rstcer->priv;

    if (id == RESET_TWSI8)
    {
        return RT_EOK;
    }

    level = rt_spin_lock_irqsave(&k1_cru_lock);

    spacemit_reset_set(reset, id, assert);

    rt_spin_unlock_irqrestore(&k1_cru_lock, level);

    return RT_EOK;
}

static rt_err_t spacemit_reset_assert(struct rt_reset_control *rstc)
{
    return spacemit_reset_update(rstc, rstc->id, RT_TRUE);
}

static rt_err_t spacemit_reset_deassert(struct rt_reset_control *rstc)
{
    return spacemit_reset_update(rstc, rstc->id, RT_FALSE);
}

const static struct rt_reset_control_ops spacemit_reset_ops =
{
    .assert = spacemit_reset_assert,
    .deassert = spacemit_reset_deassert,
};

static rt_err_t spacemit_reset_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct spacemit_reset *reset = rt_calloc(1, sizeof(*reset));

    if (!reset)
    {
        return -RT_ENOMEM;
    }

    for (int i = 0; i < CRU_BASE_TYPE_AUDPMU; ++i)
    {
        reset->mmio[i] = rt_dm_dev_iomap(dev, i);

        if (!reset->mmio[i])
        {
            err = -RT_EIO;
            goto _fail;
        }
    }

    reset->signals_nr = RT_ARRAY_SIZE(k1x_reset_signals);
    reset->signals = k1x_reset_signals;

    reset->parent.priv = reset;
    reset->parent.ofw_node = dev->ofw_node;
    reset->parent.ops = &spacemit_reset_ops;

    if ((err = rt_reset_controller_register(&reset->parent)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    for (int i = 0; i < CRU_BASE_TYPE_AUDPMU; ++i)
    {
        if (reset->mmio[i])
        {
            rt_iounmap(reset->mmio[i]);
        }
    }

    rt_free(reset);

    return err;
}

static const struct rt_ofw_node_id spacemit_reset_ofw_ids[] =
{
    { .compatible = "spacemit,k1x-reset" },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_reset_driver =
{
    .name = "reset-spacemit",
    .ids = spacemit_reset_ofw_ids,

    .probe = spacemit_reset_probe,
};

static int spacemit_reset_register(void)
{
    rt_platform_driver_register(&spacemit_reset_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(spacemit_reset_register);
