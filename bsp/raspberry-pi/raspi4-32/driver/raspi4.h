#ifndef __RASPI4_H__
#define __RASPI4_H__
//https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2711/rpi_DATA_2711_1p0.pdf

#define __REG32(x)  (*((volatile unsigned int *)(x)))
#define __REG16(x)  (*((volatile unsigned short *)(x)))

/* GIC IRQ MAX */
#define MAX_HANDLERS                (256)

/* base address */
#define PER_BASE                    (0xFE000000)

//gpio offset
#define GPIO_BASE_OFFSET            (0x00200000)

//pl011 offset
#define PL011_UART0_BASE_OFFSET     (0x00201000)
#define PL011_UART2_BASE_OFFSET     (0x00201400)
#define PL011_UART3_BASE_OFFSET     (0x00201600)
#define PL011_UART4_BASE_OFFSET     (0x00201800)
#define PL011_UART5_BASE_OFFSET     (0x00201A00)

//pactl cs offset
#define PACTL_CS_OFFSET             (0x00204E00)

//aux offset
#define AUX_BASE_OFFSET             (0x00215000)

/* GPIO */
#define GPIO_BASE                   (PER_BASE + GPIO_BASE_OFFSET)
#define GPIO_IRQ_NUM                (3)   //40 pin mode
#define IRQ_GPIO0                   (96 + 49) //bank0 (0 to 27)
#define IRQ_GPIO1                   (96 + 50) //bank1 (28 to 45)
#define IRQ_GPIO2                   (96 + 51) //bank2 (46 to 57)
#define IRQ_GPIO3                   (96 + 52) //bank3

/* Timer (ARM side) */
#define ARM_TIMER_IRQ       (64)
#define ARM_TIMER_BASE      (PER_BASE + 0xB000)
#define ARM_TIMER_LOAD      HWREG32(ARM_TIMER_BASE + 0x400)
#define ARM_TIMER_VALUE     HWREG32(ARM_TIMER_BASE + 0x404)
#define ARM_TIMER_CTRL      HWREG32(ARM_TIMER_BASE + 0x408)
#define ARM_TIMER_IRQCLR    HWREG32(ARM_TIMER_BASE + 0x40C)
#define ARM_TIMER_RAWIRQ    HWREG32(ARM_TIMER_BASE + 0x410)
#define ARM_TIMER_MASKIRQ   HWREG32(ARM_TIMER_BASE + 0x414)
#define ARM_TIMER_RELOAD    HWREG32(ARM_TIMER_BASE + 0x418)
#define ARM_TIMER_PREDIV    HWREG32(ARM_TIMER_BASE + 0x41C)
#define ARM_TIMER_CNTR      HWREG32(ARM_TIMER_BASE + 0x420)

/* UART PL011 */
#define UART0_BASE                  (PER_BASE + PL011_UART0_BASE_OFFSET)
#define UART2_BASE                  (PER_BASE + PL011_UART2_BASE_OFFSET)
#define UART3_BASE                  (PER_BASE + PL011_UART3_BASE_OFFSET)
#define UART4_BASE                  (PER_BASE + PL011_UART4_BASE_OFFSET)
#define UART5_BASE                  (PER_BASE + PL011_UART5_BASE_OFFSET)
#define IRQ_AUX_UART                (96 + 29)
#define UART_REFERENCE_CLOCK        (48000000)

/* AUX */
#define AUX_BASE                    (PER_BASE + AUX_BASE_OFFSET)
#define IRQ_PL011                   (96 + 57)

/* SPI */
#define SPI_0_BASE_OFFSET     (0x00204000)
#define SPI_3_BASE_OFFSET     (0x00204600)
#define SPI_4_BASE_OFFSET     (0x00204800)
#define SPI_5_BASE_OFFSET     (0x00204A00)
#define SPI_6_BASE_OFFSET     (0x00204C00)

#define SPI_0_BASE            (PER_BASE + SPI_0_BASE_OFFSET)
#define SPI_3_BASE            (PER_BASE + SPI_3_BASE_OFFSET)
#define SPI_4_BASE            (PER_BASE + SPI_4_BASE_OFFSET)
#define SPI_5_BASE            (PER_BASE + SPI_5_BASE_OFFSET)
#define SPI_6_BASE            (PER_BASE + SPI_6_BASE_OFFSET)
/* Peripheral IRQ OR-ing */
#define PACTL_CS                    HWREG32((PER_BASE + PACTL_CS_OFFSET))
typedef enum {
    IRQ_SPI0 = 0x00000000,
    IRQ_SPI1 = 0x00000002,
    IRQ_SPI2 = 0x00000004,
    IRQ_SPI3 = 0x00000008,
    IRQ_SPI4 = 0x00000010,
    IRQ_SPI5 = 0x00000020,
    IRQ_SPI6 = 0x00000040,
    IRQ_I2C0 = 0x00000100,
    IRQ_I2C1 = 0x00000200,
    IRQ_I2C2 = 0x00000400,
    IRQ_I2C3 = 0x00000800,
    IRQ_I2C4 = 0x00001000,
    IRQ_I2C5 = 0x00002000,
    IRQ_I2C6 = 0x00004000,
    IRQ_I2C7 = 0x00008000,
    IRQ_UART5 = 0x00010000,
    IRQ_UART4 = 0x00020000,
    IRQ_UART3 = 0x00040000,
    IRQ_UART2 = 0x00080000,
    IRQ_UART0 = 0x00100000
} PACTL_CS_VAL;

// 0x40, 0x44, 0x48, 0x4c: Core 0~3 Timers interrupt control
#define CORE0_TIMER_IRQ_CTRL        HWREG32(0xFF800040)
#define TIMER_IRQ                   30
#define NON_SECURE_TIMER_IRQ        (1 << 1)

/* GIC */
#define INTC_BASE                   (0xff800000)
#define ARM_GIC_NR_IRQS             (512)
#define ARM_GIC_MAX_NR              (512)
#define GIC_V2_DISTRIBUTOR_BASE     (INTC_BASE + 0x00041000)
#define GIC_V2_CPU_INTERFACE_BASE   (INTC_BASE + 0x00042000)
#define GIC_V2_HYPERVISOR_BASE      (INTC_BASE + 0x00044000)
#define GIC_V2_VIRTUAL_CPU_BASE     (INTC_BASE + 0x00046000)

#define GIC_PL400_DISTRIBUTOR_PPTR  GIC_V2_DISTRIBUTOR_BASE
#define GIC_PL400_CONTROLLER_PPTR   GIC_V2_CPU_INTERFACE_BASE

#define GIC_IRQ_START   0

#define GIC_ACK_INTID_MASK  0x000003ff

//watchdog
#define PM_RSTC         HWREG32(PER_BASE + 0x0010001c)
#define PM_RSTS         HWREG32(PER_BASE + 0x00100020)
#define PM_WDOG         HWREG32(PER_BASE + 0x00100024)

#define PM_PASSWORD                 (0x5A000000)
#define PM_WDOG_TIME_SET            (0x000fffff)
#define PM_RSTS_HADWRH_SET          (0x00000040)
#define PM_RSTC_WRCFG_FULL_RESET    (0x00000020)
#define PM_RSTC_WRCFG_CLR           (0xffffffcf)
#define PM_RSTC_RESET               (0x00000102)

//timer
#define ST_BASE_OFFSET     (0x003000)
#define STIMER_BASE  (PER_BASE  + ST_BASE_OFFSET)
#define STIMER_CS    __REG32(STIMER_BASE + 0x0000)
#define STIMER_CLO   __REG32(STIMER_BASE + 0x0004)
#define STIMER_CHI   __REG32(STIMER_BASE + 0x0008)
#define STIMER_C0    __REG32(STIMER_BASE + 0x000C)
#define STIMER_C1    __REG32(STIMER_BASE + 0x0010)
#define STIMER_C2    __REG32(STIMER_BASE + 0x0014)
#define STIMER_C3    __REG32(STIMER_BASE + 0x0018)

#define DELAY_MICROS(micros) \
    do{ \
 rt_uint32_t compare = STIMER_CLO + micros * 25; \
 while (STIMER_CLO < compare); \
    } while (0) \

//External Mass Media Controller (SD Card)
#define MMC0_BASE_ADDR      (PER_BASE+0x300000)
#define MMC2_BASE_ADDR      (PER_BASE+0x340000)

#define ETH_IRQ                 (160+29)

//I2C
#define BSC0_BASE_OFFSET            (0x205000)
#define BSC1_BASE_OFFSET            (0x804000)
#define BSC3_BASE_OFFSET            (0x205600)
#define BSC4_BASE_OFFSET            (0x205800)
#define BSC5_BASE_OFFSET            (0x205A80)
#define BSC6_BASE_OFFSET            (0x205C00)

//BSC2 and BSC7 masters are dedicated for use by the
//HDMI interfaces and should not be accessed byuser programs.
#define BSC0_BASE                   (PER_BASE + BSC0_BASE_OFFSET)
#define BSC1_BASE                   (PER_BASE + BSC1_BASE_OFFSET)
#define BSC3_BASE                   (PER_BASE + BSC3_BASE_OFFSET)
#define BSC4_BASE                   (PER_BASE + BSC4_BASE_OFFSET)
#define BSC5_BASE                   (PER_BASE + BSC5_BASE_OFFSET)
#define BSC6_BASE                   (PER_BASE + BSC6_BASE_OFFSET)

/* the basic constants and interfaces needed by gic */
rt_inline rt_uint32_t platform_get_gic_dist_base(void)
{
    return GIC_PL400_DISTRIBUTOR_PPTR;
}

rt_inline rt_uint32_t platform_get_gic_cpu_base(void)
{
    return GIC_PL400_CONTROLLER_PPTR;
}

static inline  void __DSB(void)
{
    __asm__ volatile ("dsb 0xF":::"memory");
}

#endif
