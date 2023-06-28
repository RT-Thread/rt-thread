/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-03-22     quanzhao     first version
 */

#ifndef __IMX6UL_H__
#define __IMX6UL_H__

#include <rthw.h>
#include <rtthread.h>

#ifdef RT_USING_LWP
#include <lwp.h>
#include <ioremap.h>
#endif

enum _gic_base_offsets
{
    kGICDBaseOffset = 0x1000,   //!< GIC distributor offset.
    kGICCBaseOffset = 0x2000     //!< GIC CPU interface offset.
};

/* SOC-relative definitions */
enum _imx_interrupts
{
    SW_INTERRUPT_0 = 0, //!< Software interrupt 0.
    SW_INTERRUPT_1 = 1, //!< Software interrupt 1.
    SW_INTERRUPT_2 = 2, //!< Software interrupt 2.
    SW_INTERRUPT_3 = 3, //!< Software interrupt 3.
    SW_INTERRUPT_4 = 4, //!< Software interrupt 4.
    SW_INTERRUPT_5 = 5, //!< Software interrupt 5.
    SW_INTERRUPT_6 = 6, //!< Software interrupt 6.
    SW_INTERRUPT_7 = 7, //!< Software interrupt 7.
    SW_INTERRUPT_8 = 8, //!< Software interrupt 8.
    SW_INTERRUPT_9 = 9, //!< Software interrupt 9.
    SW_INTERRUPT_10 = 10,   //!< Software interrupt 10.
    SW_INTERRUPT_11 = 11,   //!< Software interrupt 11.
    SW_INTERRUPT_12 = 12,   //!< Software interrupt 12.
    SW_INTERRUPT_13 = 13,   //!< Software interrupt 13.
    SW_INTERRUPT_14 = 14,   //!< Software interrupt 14.
    SW_INTERRUPT_15 = 15,   //!< Software interrupt 15.
    RSVD_INTERRUPT_16 = 16, //!< Reserved.
    RSVD_INTERRUPT_17 = 17, //!< Reserved.
    RSVD_INTERRUPT_18 = 18, //!< Reserved.
    RSVD_INTERRUPT_19 = 19, //!< Reserved.
    RSVD_INTERRUPT_20 = 20, //!< Reserved.
    RSVD_INTERRUPT_21 = 21, //!< Reserved.
    RSVD_INTERRUPT_22 = 22, //!< Reserved.
    RSVD_INTERRUPT_23 = 23, //!< Reserved.
    RSVD_INTERRUPT_24 = 24, //!< Reserved.
    RSVD_INTERRUPT_25 = 25, //!< Reserved.
    RSVD_INTERRUPT_26 = 26, //!< Reserved.
    RSVD_INTERRUPT_27 = 27, //!< Reserved.
    RSVD_INTERRUPT_28 = 28, //!< Reserved.
    RSVD_INTERRUPT_29 = 29, //!< Reserved.
    RSVD_INTERRUPT_30 = 30, //!< Reserved.
    RSVD_INTERRUPT_31 = 31, //!< Reserved.
    IMX_INT_IOMUXC_GPR = 32,   //!< General Purpose Register 1 from IOMUXC. Used to notify cores on exception condition while boot.
    IMX_INT_CHEETAH_CSYSPWRUPREQ = 33,  //!< @todo Listed as DAP in RM
    IMX_INT_SDMA = 34,  //!< Logical OR of all 48 SDMA interrupt requests/events from all channels.
    IMX_INT_TSC = 35,   //!< TSC
    IMX_INT_SNVS_LP_SET_PWR_OFF = 36,   //!< PMIC power off request.
    IMX_INT_LCDIF = 37,  //!< LCDIF interrupt request.
    IMX_INT_BEE = 38, //!< BEE interrupt request.
    IMX_INT_CSI = 39,  //!< CMOS Sensor Interface interrupt request.
    IMX_INT_PXP = 40,    //!< PXP interrupt request.
    IMX_INT_SCTR1 = 41, //!< SCTR1
    IMX_INT_SCTR2 = 42, //!< SCTR2
    IMX_INT_WDOG3 = 43,    //!< WDOG3 timer reset interrupt request.
    IMX_INT_INTERRUPT_44 = 44,   //!< Reserved.
    IMX_INT_APBH_DMA = 45,   //!< APBH DMA
    IMX_INT_EIM = 46,   //!< EIM interrupt request.
    IMX_INT_NAND_BCH = 47,   //!< Reserved.
    IMX_INT_NAND_GPMI = 48,  //!< Reserved.
    IMX_INT_UART6 = 49, //!< Logical OR of UART5 interrupt requests.
    IMX_INT_INTERRUPT_50 = 50,  //!< Reserved.
    IMX_INT_SNVS = 51,  //!< SNVS consolidated interrupt.
    IMX_INT_SNVS_SEC = 52,  //!< SNVS security interrupt.
    IMX_INT_CSU = 53,   //!< CSU interrupt request 1. Indicates to the processor that one or more alarm inputs were asserted.
    IMX_INT_USDHC1 = 54,    //!< uSDHC1 (Enhanced SDHC) interrupt request.
    IMX_INT_USDHC2 = 55,    //!< uSDHC2 (Enhanced SDHC) interrupt request.
    IMX_INT_SAI3 = 56,    //!< uSDHC3 (Enhanced SDHC) interrupt request.
    IMX_INT_SAI4 = 57,    //!< uSDHC4 (Enhanced SDHC) interrupt request.
    IMX_INT_UART1 = 58, //!< Logical OR of UART1 interrupt requests.
    IMX_INT_UART2 = 59, //!< Logical OR of UART2 interrupt requests.
    IMX_INT_UART3 = 60, //!< Logical OR of UART3 interrupt requests.
    IMX_INT_UART4 = 61, //!< Logical OR of UART4 interrupt requests.
    IMX_INT_UART5 = 62, //!< Logical OR of UART5 interrupt requests.
    IMX_INT_ECSPI1 = 63,    //!< eCSPI1 interrupt request.
    IMX_INT_ECSPI2 = 64,    //!< eCSPI2 interrupt request.
    IMX_INT_ECSPI3 = 65,    //!< eCSPI3 interrupt request.
    IMX_INT_ECSPI4 = 66,    //!< eCSPI4 interrupt request.
    IMX_INT_I2C4 = 67,    //!< Reserved.
    IMX_INT_I2C1 = 68,  //!< I2C1 interrupt request.
    IMX_INT_I2C2 = 69,  //!< I2C2 interrupt request.
    IMX_INT_I2C3 = 70,  //!< I2C3 interrupt request.
    IMX_INT_UART7 = 71, //!< Logical OR of UART5 interrupt requests.
    IMX_INT_UART8 = 72, //!< Logical OR of UART5 interrupt requests.
    IMX_INT_INTERRUPT_73 = 73,    //!< Reserved.
    IMX_INT_USB_OTG2 = 74,    //!< USB Host 1 interrupt request.
    IMX_INT_USB_OTG1 = 75,   //!< USB OTG1 interrupt request.
    IMX_INT_USB_UTMI0 = 76, //!< UTMI0 interrupt request.
    IMX_INT_USB_UTMI1 = 77, //!< UTMI1 interrupt request.
    IMX_INT_CAAM_JQ2 = 78,  //!< SSI1 interrupt request.
    IMX_INT_CAAM_ERR = 79,  //!< SSI2 interrupt request.
    IMX_INT_CAAM_RTIC = 80,  //!< SSI3 interrupt request.
    IMX_INT_TEMPERATURE = 81,   //!< Temperature Sensor (temp. greater than threshold) interrupt request.
    IMX_INT_ASRC = 82,  //!< Reserved.
    IMX_INT_INTERRUPT_83 = 83,  //!< Reserved.
    IMX_INT_SPDIF = 84, //!< Logical OR of SPDIF TX and SPDIF RX interrupts.
    IMX_INT_INTERRUPT_85 = 85,   //!< Reserved.
    IMX_INT_PMU_ANA_BO = 86,    //!< PMU analog regulator brown-out interrupt request.
    IMX_INT_GPT1 = 87,   //
    IMX_INT_EPIT1 = 88, //!< EPIT1 output compare interrupt.
    IMX_INT_EPIT2 = 89, //!< EPIT2 output compare interrupt.
    IMX_INT_GPIO1_INT7 = 90,    //!< INT7 interrupt request.
    IMX_INT_GPIO1_INT6 = 91,    //!< INT6 interrupt request.
    IMX_INT_GPIO1_INT5 = 92,    //!< INT5 interrupt request.
    IMX_INT_GPIO1_INT4 = 93,    //!< INT4 interrupt request.
    IMX_INT_GPIO1_INT3 = 94,    //!< INT3 interrupt request.
    IMX_INT_GPIO1_INT2 = 95,    //!< INT2 interrupt request.
    IMX_INT_GPIO1_INT1 = 96,    //!< INT1 interrupt request.
    IMX_INT_GPIO1_INT0 = 97,    //!< INT0 interrupt request.
    IMX_INT_GPIO1_INT15_0 = 98, //!< Combined interrupt indication for GPIO1 signals 0 - 15.
    IMX_INT_GPIO1_INT31_16 = 99,    //!< Combined interrupt indication for GPIO1 signals 16 - 31.
    IMX_INT_GPIO2_INT15_0 = 100,    //!< Combined interrupt indication for GPIO2 signals 0 - 15.
    IMX_INT_GPIO2_INT31_16 = 101,   //!< Combined interrupt indication for GPIO2 signals 16 - 31.
    IMX_INT_GPIO3_INT15_0 = 102,    //!< Combined interrupt indication for GPIO3 signals 0 - 15.
    IMX_INT_GPIO3_INT31_16 = 103,   //!< Combined interrupt indication for GPIO3 signals 16 - 31.
    IMX_INT_GPIO4_INT15_0 = 104,    //!< Combined interrupt indication for GPIO4 signals 0 - 15.
    IMX_INT_GPIO4_INT31_16 = 105,   //!< Combined interrupt indication for GPIO4 signals 16 - 31.
    IMX_INT_GPIO5_INT15_0 = 106,    //!< Combined interrupt indication for GPIO5 signals 0 - 15.
    IMX_INT_GPIO5_INT31_16 = 107,   //!< Combined interrupt indication for GPIO5 signals 16 - 31.
    IMX_INT_INTERRUPT_108 = 108,    //!< Reserved.
    IMX_INT_INTERRUPT_109 = 109,   //!< Reserved.
    IMX_INT_INTERRUPT_110 = 110,    //!< Reserved.
    IMX_INT_INTERRUPT_111 = 111,   //!< Reserved.
    IMX_INT_WDOG1 = 112,    //!< WDOG1 timer reset interrupt request.
    IMX_INT_WDOG2 = 113,    //!< WDOG2 timer reset interrupt request.
    IMX_INT_KPP = 114,  //!< Key Pad interrupt request.
    IMX_INT_PWM1 = 115, //!< Cumulative interrupt line for PWM1. Logical OR of rollover, compare, and FIFO waterlevel crossing interrupts.
    IMX_INT_PWM2 = 116, //!< Cumulative interrupt line for PWM2. Logical OR of rollover, compare, and FIFO waterlevel crossing interrupts.
    IMX_INT_PWM3 = 117, //!< Cumulative interrupt line for PWM3. Logical OR of rollover, compare, and FIFO waterlevel crossing interrupts.
    IMX_INT_PWM4 = 118, //!< Cumulative interrupt line for PWM4. Logical OR of rollover, compare, and FIFO waterlevel crossing interrupts.
    IMX_INT_CCM_INT1 = 119, //!< CCM interrupt request 1.
    IMX_INT_CCM_INT2 = 120, //!< CCM interrupt request 2.
    IMX_INT_GPC_INT1 = 121, //!< GPC interrupt request 1.
    IMX_INT_INTERRUPT_122 = 122, //!< Reserved.
    IMX_INT_SRC = 123,  //!< SRC interrupt request.
    IMX_INT_INTERRUPT_124 = 124,   //!< Logical OR of all L2 interrupt requests.
    IMX_INT_INTERRUPT_125 = 125,   //!< Parity Check error interrupt request.
    IMX_INT_CHEETAH_PERFORM = 126,  //!< Logical OR of Performance Unit interrupts.
    IMX_INT_CHEETAH_TRIGGER = 127,  //!< Logical OR of CTI trigger outputs.
    IMX_INT_SRC_CPU_WDOG = 128, //!< Combined CPU wdog interrupts (4x) out of SRC.
    IMX_INT_SAI1 = 129,    //!< EPDC interrupt request.
    IMX_INT_SAI2 = 130,    //!< EPDC interrupt request.
    IMX_INT_INTERRUPT_131 = 131,    //!< DCP general interrupt request.
    IMX_INT_ADC1 = 132,    //!< DCP channel 0 interrupt request.
    IMX_INT_ADC2 = 133,    //!< DCP secure interrupt request.
    IMX_INT_INTERRUPT_134 = 134,  //!< Reserved.
    IMX_INT_INTERRUPT_135 = 135,  //!< Reserved.
    IMX_INT_SJC = 136,  //!< SJC interrupt from General Purpose register.
    IMX_INT_CAAM_0 = 137,    //!< Reserved.
    IMX_INT_CAAM_1 = 138,    //!< Reserved.
    IMX_INT_QSPI = 139,    //!< Reserved.
    IMX_INT_TZASC1 = 140,   //!< ASC1 interrupt request.
    IMX_INT_GPT2 = 141,   //!< Reserved.
    IMX_INT_CAN1 = 142, //!< Reserved.
    IMX_INT_CAN2 = 143, //!< Reserved.
    IMX_INT_SIM1 = 144,    //!< Reserved.
    IMX_INT_SIM2 = 145,    //!< Reserved.
    IMX_INT_PWM5 = 146,    //!< Fast Ethernet Controller interrupt request.
    IMX_INT_PWM6 = 147,  //!< Reserved.
    IMX_INT_PWM7 = 148,   //!< Reserved.
    IMX_INT_PWM8 = 149, //!< Reserved.
    IMX_INT_ENET1 = 150, //!< Reserved.
    IMX_INT_ENET1_TIMER = 151,    //!< Reserved.
    IMX_INT_ENET2 = 152,   //!< Reserved.
    IMX_INT_ENET2_TIMER = 153,   //!< Reserved.
    IMX_INT_INTERRUPT_154 = 154,   //!< Reserved.
    IMX_INT_INTERRUPT_155 = 155,   //!< Reserved.
    IMX_INT_INTERRUPT_156 = 156,    //!< Reserved.
    IMX_INT_INTERRUPT_157 = 157,    //!< Reserved.
    IMX_INT_INTERRUPT_158 = 158, //!< Reserved.
    IMX_INT_PMU_DIG_BO = 159,    //!< //!< PMU digital regulator brown-out interrupt request.
    IMX_INTERRUPT_COUNT = 160   //!< Total number of interrupts.
};

/* SOC-relative definitions */
#include "MCIMX6Y2.h"

#include "fsl_cache.h"
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "fsl_gpio.h"
#include "fsl_elcdif.h"
#include "fsl_usdhc.h"
#include "fsl_card.h"
#include "fsl_wdog.h"
#include "fsl_i2c.h"
#include "fsl_ecspi.h"
#include "fsl_snvs_hp.h"
#include "fsl_adc.h"

#define IMX6ULL_PERIPH_SIZE         (16 * 1024)

/* Interrupt Control Interface */
#define ARM_GIC_CPU_BASE            0x00A00000

/*
 * Peripheral addresses
 */
#define IMX6ULL_UART1_BASE          UART1_BASE  /* UART 1 */
#define IMX6ULL_UART2_BASE          UART2_BASE  /* UART 2 */
#define IMX6ULL_UART3_BASE          UART3_BASE  /* UART 3 */
#define IMX6ULL_UART4_BASE          UART4_BASE  /* UART 4 */
#define IMX6ULL_UART5_BASE          UART5_BASE  /* UART 5 */
#define IMX6ULL_UART6_BASE          UART6_BASE  /* UART 6 */
#define IMX6ULL_UART7_BASE          UART7_BASE  /* UART 7 */
#define IMX6ULL_UART8_BASE          UART8_BASE  /* UART 8 */

#define IMX6ULL_WATCHDOG1_BASE      WDOG1_BASE  /* watchdog 1 */
#define IMX6ULL_WATCHDOG2_BASE      WDOG2_BASE  /* watchdog 2 */
#define IMX6ULL_WATCHDOG3_BASE      WDOG3_BASE  /* watchdog 3 */

#define IMX6ULL_GPIO1_BASE          GPIO1_BASE  /* GPIO port 0 */
#define IMX6ULL_GPIO2_BASE          GPIO2_BASE  /* GPIO port 1 */
#define IMX6ULL_GPIO3_BASE          GPIO3_BASE  /* GPIO port 2 */
#define IMX6ULL_GPIO4_BASE          GPIO4_BASE  /* GPIO port 3 */
#define IMX6ULL_GPIO5_BASE          GPIO5_BASE  /* GPIO port 4 */

#define IMX6ULL_SNVS_BASE           SNVS_BASE   /* Real Time Clock */

#define IMX6ULL_SCTL_BASE           0x021DC000u /* System Controller */

#define IMX6ULL_CLCD_BASE           LCDIF_BASE  /* CLCD */

#define IMX6ULL_GIC_DIST_BASE       (ARM_GIC_CPU_BASE+kGICDBaseOffset)  /* Generic interrupt controller distributor */
#define IMX6ULL_GIC_CPU_BASE        (ARM_GIC_CPU_BASE+kGICCBaseOffset)  /* Generic interrupt controller CPU interface */

#define IMX6ULL_IOMUXC_BASE         IOMUXC_BASE
#define IMX6ULL_IOMUXC_SNVS_BASE    IOMUXC_SNVS_BASE
#define IMX6ULL_IOMUXC_GPR_BASE     IOMUXC_GPR_BASE

#define IMX6ULL_CCM_BASE            0x20C4000u
#define IMX6ULL_CCM_ANALOGY_BASE    0x20C8000u
#define IMX6ULL_PMU_BASE            0x20C8110u

#define IMX6ULL_ENET1_BASE          ENET1_BASE
#define IMX6ULL_ENET2_BASE          ENET2_BASE

#define IMX6ULL_GPT1_BASE           GPT1_BASE
#define IMX6ULL_GPT2_BASE           GPT2_BASE

#define IMX6ULL_ECSPI1_BASE         ECSPI1_BASE
#define IMX6ULL_ECSPI2_BASE         ECSPI2_BASE
#define IMX6ULL_ECSPI3_BASE         ECSPI3_BASE
#define IMX6ULL_ECSPI4_BASE         ECSPI4_BASE

#define IMX6ULL_I2C1_BASE           I2C1_BASE
#define IMX6ULL_I2C2_BASE           I2C2_BASE
#define IMX6ULL_I2C3_BASE           I2C3_BASE
#define IMX6ULL_I2C4_BASE           I2C4_BASE

#define IMX6ULL_SDMA_BASE           SDMAARM_BASE

#define IMX6ULL_USDHC1_BASE         USDHC1_BASE
#define IMX6ULL_USDHC2_BASE         USDHC2_BASE

#define IMX6ULL_SRC_BASE            SRC_BASE

#define IMX6ULL_GPMI_BASE           GPMI_BASE
#define IMX6ULL_BCH_BASE            BCH_BASE
#define IMX6ULL_APBH_BASE           APBH_BASE

#define IMX6ULL_CSI_BASE            CSI_BASE

#define IMX6ULL_CAN1_BASE           CAN1_BASE
#define IMX6ULL_CAN2_BASE           CAN2_BASE

#define IMX6ULL_USBPHY1_BASE                0x20C9000u
#define IMX6ULL_USBPHY2_BASE                0x20CA000u

#define IMX6ULL_USB1_BASE                   0x2184000u
#define IMX6ULL_USB2_BASE                   0x2184200u

#define IMX6ULL_USB_ANALOG_BASE             0x20C81A0u
/* the maximum number of gic */
#define ARM_GIC_MAX_NR 1

#define _internal_ro                static const
#define _internal_rw                static
#define _internal_zi                static

#define GET_ARRAY_NUM(ins)          ((uint32_t)(sizeof(ins)/sizeof(ins[0])))

#include "bsp_clock.h"

/* the maximum number of interrupts */
#define ARM_GIC_NR_IRQS IMX_INTERRUPT_COUNT

/* the maximum entries of the interrupt table */
#define MAX_HANDLERS IMX_INTERRUPT_COUNT

/* the basic constants needed by gic */
rt_inline rt_uint32_t platform_get_gic_dist_base(void)
{
    rt_uint32_t gic_base;
    asm volatile ("mrc p15, 4, %0, c15, c0, 0" : "=r"(gic_base));
    return gic_base + kGICDBaseOffset;
}

rt_inline rt_uint32_t platform_get_gic_cpu_base(void)
{
    rt_uint32_t gic_base;
    asm volatile ("mrc p15, 4, %0, c15, c0, 0" : "=r"(gic_base));
    return gic_base + kGICCBaseOffset;
}

rt_inline rt_uint32_t platform_get_periph_vaddr(rt_uint32_t paddr)
{
#ifdef RT_USING_SMART
    rt_uint32_t mask = IMX6ULL_PERIPH_SIZE - 1;
    return (rt_uint32_t)rt_ioremap((void*)(paddr&(~mask)), IMX6ULL_PERIPH_SIZE) + (paddr & mask);
#else
    return paddr;
#endif
}

#define GIC_IRQ_START   0

#define GIC_ACK_INTID_MASK              0x000003ff

/* the definition needed by gic.c */
#define __REG32(x)  (*((volatile unsigned int *)(x)))

/* keep compatible with platform SDK */
typedef enum {
    CPU_0,
    CPU_1,
    CPU_2,
    CPU_3,
} cpuid_e;

enum _gicd_sgi_filter
{
    //! Forward the interrupt to the CPU interfaces specified in the @a target_list parameter.
    kGicSgiFilter_UseTargetList = 0,

    //! Forward the interrupt to all CPU interfaces except that of the processor that requested
    //! the interrupt.
    kGicSgiFilter_AllOtherCPUs = 1,

    //! Forward the interrupt only to the CPU interface of the processor that requested the
    //! interrupt.
    kGicSgiFilter_OnlyThisCPU = 2
};

typedef void (*irq_hdlr_t) (void);

extern void rt_hw_interrupt_mask(int vector);
extern void rt_hw_interrupt_umask(int vector);
extern rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
    void *param, const char *name);

rt_inline void register_interrupt_routine(uint32_t irq_id, irq_hdlr_t isr)
{
    rt_hw_interrupt_install(irq_id, (rt_isr_handler_t)isr, RT_NULL, "unknown");
}

rt_inline void enable_interrupt(uint32_t irq_id, uint32_t cpu_id, uint32_t priority)
{
    rt_hw_interrupt_umask(irq_id);
}

rt_inline void disable_interrupt(uint32_t irq_id, uint32_t cpu_id)
{
    rt_hw_interrupt_mask(irq_id);
}

#endif  /* __IMX6UL_H__ */
