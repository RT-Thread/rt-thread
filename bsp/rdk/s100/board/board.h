#ifndef __BOARD_H__
#define __BOARD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <rtdef.h>
#include <rthw.h>
#include <cp15.h>

#ifdef __GNUC__
extern char OS_HEAP_START_ADDR;
extern char OS_HEAP_END_ADDR;
#define HEAP_BEGIN ((void *)&OS_HEAP_START_ADDR)
#define HEAP_END   ((void *)&OS_HEAP_END_ADDR)
#else
#error "GCC support only!"
#endif

#ifndef __DSB
#define __DSB() __asm volatile ("dsb" : : : "memory")
#endif

#ifndef __ISB
#define __ISB() __asm volatile ("isb" : : : "memory")
#endif

/***********************************************************************************************************************
 * GIC definitions
 **********************************************************************************************************************/
#define S100_GICD_BASE          0x22000000UL
#define S100_GICR0_OFFSET       0x100000UL

#define GIC_IRQ_START   0
#define GIC_ACK_INTID_MASK  (0x000003FFU)

/* number of interrupts on board */
#define ARM_GIC_NR_IRQS     (448)
#define MAX_HANDLERS ARM_GIC_NR_IRQS
/* only one GIC available */
#define ARM_GIC_MAX_NR      1
/*  end defined */

#define GICV3_DISTRIBUTOR_BASE_ADDR     (S100_GICD_BASE)
#define GICV3_REDISTRIBUTOR_BASE_ADDR   (S100_GICD_BASE + S100_GICR0_OFFSET)

/*
 * Board-level IRQ description used by the S100 BSP.
 *
 * Reason:
 * The SoC GIC can see many more interrupt IDs than this RT-Thread board
 * actually uses. MCU0 already occupies part of the required interrupt
 * resources, so this board only maintains the IRQs used by the current
 * port. We keep a board whitelist so GICv3 only configures and controls
 * the interrupts that belong to the current board port, which avoids
 * touching unrelated SPI lines and reduces the risk of conflicting with
 * the interrupts used by MCU0.
 *
 * Fields:
 * irq_number: GIC interrupt ID used by the board.
 * enable: whether this IRQ is expected to be enabled by board-level init.
 * name: short readable name for debug and dump output.
 */
typedef struct
{
    int irq_number;
    rt_bool_t enable;
    const char *name;
} s100_rt_irq_config_t;

/*
 * Board-supported external IRQ whitelist.
 *
 * s100_mcu1_rt_irq_configs records the SPI interrupts currently owned by this
 * board port. GICv3 uses this table to decide which external interrupts may be
 * initialized, enabled, masked, dumped, or otherwise managed.
 * The main purpose is to maintain only the interrupts actually used by this
 * side, so we do not accidentally configure or disturb interrupt lines that
 * are already required by MCU0.
 *
 * Private interrupts (SGI/PPI, INTID 0-31) are not listed here because they
 * are CPU-local resources and are handled separately.
 */
extern const s100_rt_irq_config_t s100_mcu1_rt_irq_configs[];
extern const rt_size_t s100_mcu1_rt_irq_configs_count;

/* Returns RT_TRUE only for IRQs that are managed by the current board port. */
rt_bool_t s100_board_irq_is_supported(int irq);

/* the basic constants and interfaces needed by gic */
rt_inline rt_uint32_t platform_get_gic_dist_base(void)
{
    return GICV3_DISTRIBUTOR_BASE_ADDR;
}

rt_inline rt_uint32_t platform_get_gic_redist_base(void)
{
    return GICV3_REDISTRIBUTOR_BASE_ADDR;
}

#ifdef __cplusplus
}
#endif

#endif

