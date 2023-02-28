#include "bl808.h"
#include "bl808_clock.h"
#ifdef BOOTROM
#include "bflb_bootrom.h"
#endif

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define SYSTEM_CLOCK (16000000UL)

/*----------------------------------------------------------------------------
  System initialization function
 *----------------------------------------------------------------------------*/

void System_BOR_Init(void)
{
    //HBN_BOR_CFG_Type borCfg = {1/* pu_bor */, 0/* irq_bor_en */, 1/* bor_vth */, 1/* bor_sel */};
    //HBN_Set_BOR_Cfg(&borCfg);
}

void System_Core_Clock_Set(BL_System_Clock_Type type, uint32_t clock)
{
    Clock_Cfg_Type *pClk = (Clock_Cfg_Type *)SYS_CLOCK_CFG_ADDR;

    CHECK_PARAM(IS_BL_SYSTEM_CLOCK_TYPE(type));

    if (type < BL_SYSTEM_CLOCK_MAX) {
        pClk->systemClock[type] = clock;
        pClk->magic = SYS_CLOCK_CFG_MAGIC;
    }
}

void System_Init(void)
{
    uint32_t i = 0;

    /* get interrupt level from info */
    CLIC->CLICCFG = (((CLIC->CLICINFO & CLIC_INFO_CLICINTCTLBITS_Msk) >> CLIC_INFO_CLICINTCTLBITS_Pos) << CLIC_CLICCFG_NLBIT_Pos);

    /* Every interrupt should be clear by software*/
    for (i = 0; i < IRQn_LAST; i++) {
        CLIC->CLICINT[i].IP = 0;
        CLIC->CLICINT[i].ATTR = 1; /* use vector interrupt */
    }

    /* tspend interrupt will be clear auto*/
    /* tspend use positive interrupt */
    CLIC->CLICINT[MSOFT_IRQn].ATTR = 0x3;

    //csi_dcache_enable();
    //csi_icache_enable();
    //CPU_Interrupt_Enable(MSOFT_IRQn);

    /* init bor for all platform */
    System_BOR_Init();
}

void System_Post_Init(void)
{
    System_Interrupt_Init();

    /* global IRQ enable */
    __enable_irq();
}

void System_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{
    if (IRQn >= CPU_LP_MAX_IRQ_NUM) {
        IRQn -= 32;
    }

    csi_vic_set_prio(IRQn, PreemptPriority);
}

int32_t drv_get_cpu_id(void)
{
    return __get_MHARTID();
}

int32_t drv_get_cpu_freq(int32_t idx)
{
    return 16 * 1000 * 1000UL;
}
