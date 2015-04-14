#define write_reg(a,v)	(*(volatile unsigned int *)(a) = (v))
/* Processor Reset */
#define AT91_RSTC_PROCRST (1 << 0)
#define AT91_RSTC_PERRST  (1 << 2)
#define AT91_RSTC_KEY     (0xa5 << 24)
#define AT91_MATRIX_BASE  (0XFFFFEE00)
/* Master Remap Control Register */
#define AT91_MATRIX_MRCR  (AT91_MATRIX_BASE + 0x100)
/* Remap Command for AHB Master 0 (ARM926EJ-S InSTRuction Master) */
#define AT91_MATRIX_RCB0  (1 << 0)
/* Remap Command for AHB Master 1 (ARM926EJ-S Data Master) */
#define AT91_MATRIX_RCB1  (1 << 1)
#define AT91_AIC_BASE     (0XFFFFF000)
/* Interrupt DisaBLe Command Register */
#define AT91_AIC_IDCR     (0x124)
/* Interrupt Clear Command Register */
#define AT91_AIC_ICCR     (0x128)

void rt_low_level_init(void)
{
    // Mask all IRQs by clearing all bits in the INTMRS
    write_reg(AT91_AIC_BASE + AT91_AIC_IDCR, 0xFFFFFFFF);
    write_reg(AT91_AIC_BASE + AT91_AIC_ICCR, 0xFFFFFFFF);
    // Remap internal ram to 0x00000000 Address
    write_reg(AT91_MATRIX_MRCR, AT91_MATRIX_RCB0 | AT91_MATRIX_RCB1);
}

