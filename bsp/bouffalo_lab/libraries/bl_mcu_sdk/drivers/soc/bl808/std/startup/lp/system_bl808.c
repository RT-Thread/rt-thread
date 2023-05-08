#include "bl808.h"

void SystemInit(void)
{
    uint32_t i = 0;

    /* get interrupt level from info */
    CLIC->CLICCFG = (((CLIC->CLICINFO & CLIC_INFO_CLICINTCTLBITS_Msk) >> CLIC_INFO_CLICINTCTLBITS_Pos) << CLIC_CLICCFG_NLBIT_Pos);

    /* Every interrupt should be clear by software*/
    for (i = 0; i < IRQn_LAST; i++) {
        CLIC->CLICINT[i].IE = 0;
        CLIC->CLICINT[i].IP = 0;
        CLIC->CLICINT[i].ATTR = 1; /* use vector interrupt */
    }

    CLIC->CLICINT[MSOFT_IRQn].ATTR = 0x3;
}

void System_Post_Init(void)
{
    /* global IRQ enable */
    __enable_irq();
}