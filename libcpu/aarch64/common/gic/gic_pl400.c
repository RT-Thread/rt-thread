/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include "gic_pl400.h"
#include "iomap.h"

#define BIT(n) (1ul<<(n))
#define MASK(n) (BIT(n)-1ul)

/* Setters/getters helpers */
#define IRQ_REG(IRQ) ((IRQ) / 32)
#define IRQ_BIT(IRQ) BIT((IRQ) % 32)
#define IRQ_MASK MASK(10)
#define IS_IRQ_VALID(X) (((X)&IRQ_MASK) < SPECIAL_IRQ_START)

#define CPU(X) (1<<(X))
#define TARGET_CPU_ALLINT(CPU) ( \
        ( ((CPU)&0xff)<<0  ) |\
        ( ((CPU)&0xff)<<8  ) |\
        ( ((CPU)&0xff)<<16 ) |\
        ( ((CPU)&0xff)<<24 ) \
    )
#define TARGET_CPU0_ALLINT   TARGET_CPU_ALLINT(CPU(0))


#define IRQ_SET_ALL 0xffffffff;

/* Special IRQ's */
#define SPECIAL_IRQ_START 1020
#define IRQ_NONE          1023

/* Memory map for GIC distributor */
struct gic_dist_map {
    uint32_t enable;                /* 0x000 */
    uint32_t ic_type;               /* 0x004 */
    uint32_t dist_ident;            /* 0x008 */
    uint32_t res1[29];              /* [0x00C, 0x080) */

    uint32_t group[32];          /* [0x080, 0x100) */

    uint32_t enable_set[32];        /* [0x100, 0x180) */
    uint32_t enable_clr[32];        /* [0x180, 0x200) */
    uint32_t pending_set[32];       /* [0x200, 0x280) */
    uint32_t pending_clr[32];       /* [0x280, 0x300) */
    uint32_t active[32];            /* [0x300, 0x380) */
    uint32_t active_clr[32];        /* [0x380, 0x400) */

    uint32_t priority[255];         /* [0x400, 0x7FC) */
    uint32_t res2;                  /* 0x7FC */

    uint32_t targets[255];          /* [0x800, 0xBFC) */
    uint32_t res3;                  /* 0xBFC */

    uint32_t config[64];             /* [0xC00, 0xD00) */

    uint32_t ppi_status;            /* [0xD00, 0xD04) */
    uint32_t spi_status[15];        /* [0xD04, 0xD40) */
    uint32_t res4[112];              /* [0xD40, 0xF00) */

    uint32_t sgi_control;           /* 0xF00 */
    uint32_t res5[3];               /* [0xF04, 0xF10) */
    uint32_t sgi_pending_clr[4];    /* [0xF10, 0xF20) */
    uint32_t sgi_pending_set[4];    /* [0xF20, 0xF30) */
    uint32_t res10[40];             /* [0xF30, 0xFD0) */

    uint32_t periph_id[8];         /* [0xFD0, 0xFF0) */
    uint32_t component_id[4];       /* [0xFF0, 0xFFF] */
};


/* Memory map for GIC  cpu interface */
struct gic_cpu_iface_map {
    uint32_t icontrol;              /*  0x000         */
    uint32_t pri_msk_c;             /*  0x004         */
    uint32_t bp_c;                  /*  0x008         */
    uint32_t int_ack;               /*  0x00C         */
    uint32_t eoi;                   /*  0x010         */
    uint32_t run_priority;          /*  0x014         */
    uint32_t hi_pend;               /*  0x018         */
    uint32_t ns_alias_bp_c;         /*  0x01C         */
    uint32_t ns_alias_ack;          /*  0x020 GIC_PL400 only */
    uint32_t ns_alias_eoi;          /*  0x024 GIC_PL400 only */
    uint32_t ns_alias_hi_pend;      /*  0x028 GIC_PL400 only */

    uint32_t res1[41];              /* [0x02C, 0x0D0) */
    uint32_t active_priority[4];    /* [0x0D0, 0xC0] GIC_PL400 only */
    uint32_t ns_active_priority[4]; /* [0xE0,0xF0] GIC_PL400 only */
    uint32_t res4[3];               /* [0xF0, 0xFC] */

    uint32_t cpu_if_ident;          /*  0x0FC         */
    uint32_t deactive;              /* [0x1000] */
};

volatile struct gic_dist_map *gic_dist =
    (volatile struct gic_dist_map*)(GIC_PL400_DISTRIBUTOR_PPTR);

volatile struct gic_cpu_iface_map *gic_cpuiface =
    (volatile struct gic_cpu_iface_map*)(GIC_PL400_CONTROLLER_PPTR);

/* Helpers */
static inline int
is_irq_pending(irq_t irq)
{
    int word = irq / 32;
    int bit = irq & 0x1f;
    return !!(gic_dist->pending_set[word] & BIT(bit));
}

static inline int
is_irq_active(irq_t irq)
{
    int word = irq / 32;
    int bit = irq & 0x1f;
    return !!(gic_dist->active[word] & BIT(bit));
}

static inline int
is_irq_enabled(irq_t irq)
{
    int word = irq / 32;
    int bit = irq & 0x1f;
    return !!(gic_dist->enable_set[word] & BIT(bit));
}

static inline int
is_irq_edge_triggered(irq_t irq)
{
    int word = irq / 16;
    int bit = ((irq & 0xf) * 2);
    return !!(gic_dist->config[word] & BIT(bit + 1));
}

static inline int
is_irq_1_N(irq_t irq)
{
    int word = irq / 16;
    int bit = ((irq & 0xf) * 2);
    return !!(gic_dist->config[word] & BIT(bit + 0));
}

static inline int
is_irq_N_N(irq_t irq)
{
    return !(is_irq_1_N(irq));
}

static inline void
dist_pending_clr(irq_t irq)
{
    int word = irq / 32;
    int bit = irq & 0x1f;
    /* Using |= here is detrimental to your health */
    gic_dist->pending_clr[word] = BIT(bit);
}

static inline void
dist_pending_set(irq_t irq)
{
    int word = irq / 32;
    int bit = irq & 0x1f;
    gic_dist->pending_set[word] = BIT(bit);
}

static inline void
dist_enable_clr(irq_t irq)
{
    int word = irq / 32;
    int bit = irq & 0x1f;
    /* Using |= here is detrimental to your health */
    gic_dist->enable_clr[word] = BIT(bit);
}

static inline void
dist_enable_set(irq_t irq)
{
    int word = irq / 32;
    int bit = irq & 0x1f;
    gic_dist->enable_set[word] = BIT(bit);
}

/**
   DONT_TRANSLATE
 */
static void dist_init(void)
{
    int i;
    int nirqs = 32 * ((gic_dist->ic_type & 0x1f) + 1);
    gic_dist->enable = 0;

#if 0
    /* configure to group 0 for security */
    for (i = 0; i < nirqs; i += 32) {
        gic_dist->group[i / 32] = 0xffffffff;
    }
#endif

    for (i = 0; i < nirqs; i += 32) {
        /* disable */
        gic_dist->enable_clr[i / 32] = IRQ_SET_ALL;
        /* clear pending */
        gic_dist->pending_clr[i / 32] = IRQ_SET_ALL;
    }

    /* reset interrupts priority */
    for (i = 32; i < nirqs; i += 4) {
        gic_dist->priority[i / 4] = 0x0;
    }

    /*
     * reset int target to cpu 0
     * (Should really query which processor we're running on and use that)
     */
    for (i = 0; i < nirqs; i += 4) {
        gic_dist->targets[i / 4] = TARGET_CPU0_ALLINT;
    }

    /* level-triggered, 1-N */
    for (i = 64; i < nirqs; i += 32) {
        gic_dist->config[i / 32] = 0;
        //gic_dist->config[i / 32] = 0x55555555;
    }
    /* enable the int controller */
    gic_dist->enable = 1;
}

/**
   DONT_TRANSLATE
 */
static void cpu_iface_init(void)
{
    uint32_t i;

    /* For non-Exynos4, the registers are banked per CPU, need to clear them */
    gic_dist->enable_clr[0] = IRQ_SET_ALL;
    gic_dist->pending_clr[0] = IRQ_SET_ALL;
    gic_dist->priority[0] = 0x00;
    /* put everything in group 0 */

    /* clear any software generated interrupts */
    for (i = 0; i < 16; i += 4) {
        gic_dist->sgi_pending_clr[i / 4] = IRQ_SET_ALL;
    }

    gic_cpuiface->icontrol = 0;
    gic_cpuiface->pri_msk_c = 0x000000f0;
    gic_cpuiface->bp_c = 0x00000003;

    while (((i = gic_cpuiface->int_ack) & IRQ_MASK) != IRQ_NONE) {
        gic_cpuiface->eoi = i;
    }
    gic_cpuiface->icontrol = 0x1;
}

/**
   DONT_TRANSLATE
 */
void initIRQController(void)
{
    dist_init();
    cpu_iface_init();
}



/*
 * The only sane way to get an GIC IRQ number that can be properly
 * ACKED later is through the int_ack register. Unfortunately, reading
 * this register changes the interrupt state to pending so future
 * reads will not return the same value For this reason, we have a
 * global variable to store the IRQ number.
 */
static uint32_t active_irq = IRQ_NONE;

/**
   DONT_TRANSLATE
 */
interrupt_t
getActiveIRQ(void)
{
    uint32_t irq;
    if (!IS_IRQ_VALID(active_irq)) {
        active_irq = gic_cpuiface->int_ack;
    }

    if (IS_IRQ_VALID(active_irq)) {
        irq = active_irq & IRQ_MASK;
    } else {
        irq = 1023;
    }

    return irq;
}

/*
 * GIC has 4 states: pending->active(+pending)->inactive
 * seL4 expects two states: active->inactive.
 * We ignore the active state in GIC to conform
 */
/**
   DONT_TRANSLATE
 */
bool_t
isIRQPending(void)
{
    return IS_IRQ_VALID(gic_cpuiface->hi_pend);
}


/**
   DONT_TRANSLATE
 */
void
maskInterrupt(bool_t disable, interrupt_t irq)
{
    if (disable) {
        dist_enable_clr(irq);
    } else {
        dist_enable_set(irq);
    }
}

/**
   DONT_TRANSLATE
 */
void
ackInterrupt(irq_t irq)
{
    if (!(IS_IRQ_VALID(active_irq) && (active_irq & IRQ_MASK) == irq)) {
		return;
	}
    if (is_irq_edge_triggered(irq)) {
        dist_pending_clr(irq);
    }
    gic_cpuiface->eoi = active_irq;
    active_irq = IRQ_NONE;
}

void
handleSpuriousIRQ(void)
{
}

void rt_hw_interrupt_mask(int vector)
{
    maskInterrupt(1, vector);
}

void rt_hw_interrupt_umask(int vector)
{
    maskInterrupt(0, vector);
}

int rt_hw_interrupt_get_irq(void)
{
    return getActiveIRQ();
}

void rt_hw_interrupt_ack(int fiq_irq)
{
    return ackInterrupt(fiq_irq);
}
