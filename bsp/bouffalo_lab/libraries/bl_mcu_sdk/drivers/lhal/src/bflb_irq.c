#include "bflb_irq.h"
#include "bflb_core.h"
#if defined(BL602) || defined(BL702) || defined(BL702L)
#include <risc-v/e24/clic.h>
#else
#include <csi_core.h>
#endif

extern struct bflb_irq_info_s g_irqvector[];

static void irq_unexpected_isr(int irq, void *arg)
{
    printf("irq :%d unregistered\r\n", irq);
}

void bflb_irq_initialize(void)
{
    int i;

    /* Point all interrupt vectors to the unexpected interrupt */
    for (i = 0; i < CONFIG_IRQ_NUM; i++) {
        g_irqvector[i].handler = irq_unexpected_isr;
        g_irqvector[i].arg = NULL;
    }
}

ATTR_TCM_SECTION uintptr_t bflb_irq_save(void)
{
    uintptr_t oldstat;

    /* Read mstatus & clear machine interrupt enable (MIE) in mstatus */

    asm volatile("csrrc %0, mstatus, %1"
                 : "=r"(oldstat)
                 : "r"(MSTATUS_MIE));
    return oldstat;
}

ATTR_TCM_SECTION void bflb_irq_restore(uintptr_t flags)
{
    /* Write flags to mstatus */

    asm volatile("csrw mstatus, %0"
                 : /* no output */
                 : "r"(flags));
}

int bflb_irq_attach(int irq, irq_callback isr, void *arg)
{
    if (irq > CONFIG_IRQ_NUM) {
        return -EINVAL;
    }
    g_irqvector[irq].handler = isr;
    g_irqvector[irq].arg = arg;
    return 0;
}

int bflb_irq_detach(int irq)
{
    if (irq > CONFIG_IRQ_NUM) {
        return -EINVAL;
    }
    g_irqvector[irq].handler = irq_unexpected_isr;
    g_irqvector[irq].arg = NULL;
    return 0;
}

void bflb_irq_enable(int irq)
{
#if defined(BL702) || defined(BL602) || defined(BL702L)
    putreg8(1, CLIC_HART0_BASE + CLIC_INTIE_OFFSET + irq);
#else
#if (defined(BL808) || defined(BL606P)) && defined(CPU_D0)
    if (csi_vic_get_prio(irq) == 0) {
        csi_vic_set_prio(irq, 1);
    }
#endif
    csi_vic_enable_irq(irq);
#endif
}

void bflb_irq_disable(int irq)
{
#if defined(BL702) || defined(BL602) || defined(BL702L)
    putreg8(0, CLIC_HART0_BASE + CLIC_INTIE_OFFSET + irq);
#else
    csi_vic_disable_irq(irq);
#endif
}

void bflb_irq_set_pending(int irq)
{
#if defined(BL702) || defined(BL602) || defined(BL702L)
    putreg8(1, CLIC_HART0_BASE + CLIC_INTIP_OFFSET + irq);
#else
    csi_vic_set_pending_irq(irq);
#endif
}

void bflb_irq_clear_pending(int irq)
{
#if defined(BL702) || defined(BL602) || defined(BL702L)
    putreg8(0, CLIC_HART0_BASE + CLIC_INTIP_OFFSET + irq);
#else
    csi_vic_clear_pending_irq(irq);
#endif
}

void bflb_irq_set_nlbits(uint8_t nlbits)
{
#if defined(BL702) || defined(BL602) || defined(BL702L)
    uint8_t clicCfg = getreg8(CLIC_HART0_BASE + CLIC_CFG_OFFSET);
    putreg8((clicCfg & 0xe1) | ((nlbits & 0xf) << 1), CLIC_HART0_BASE + CLIC_CFG_OFFSET);
#else
#if !defined(CPU_D0)
    CLIC->CLICCFG = ((nlbits & 0xf) << 1) | 1;
#endif
#endif
}

void bflb_irq_set_priority(int irq, uint8_t preemptprio, uint8_t subprio)
{
#if defined(BL702) || defined(BL602) || defined(BL702L)
    uint8_t nlbits = getreg8(CLIC_HART0_BASE + CLIC_CFG_OFFSET) >> 1 & 0xf;
    uint8_t clicIntCfg = getreg8(CLIC_HART0_BASE + CLIC_INTCFG_OFFSET + irq);
    putreg8((clicIntCfg & 0xf) | (preemptprio << (8 - nlbits)) | ((subprio & (0xf >> nlbits)) << 4), CLIC_HART0_BASE + CLIC_INTCFG_OFFSET + irq);
#else
    csi_vic_set_prio(irq, preemptprio);
#endif
}
