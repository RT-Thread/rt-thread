/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hal_fsmc.h"

const uint32_t FSMC_BankBases[] =
{
    FSMC_BANK0_BASE,
    FSMC_BANK1_BASE,
    FSMC_BANK2_BASE,
    FSMC_BANK3_BASE
};

void FSMC_Init(FSMC_Type * FSMCx, FSMC_Init_Type * init)
{
    FSMCx->SMSKR0 = ( (FSMCx->SMSKR0 & ~(FSMC_SMSKR0_MEMSIZE_MASK | FSMC_SMSKR0_MEMTYPE_MASK) )
                                     |  FSMC_SMSKR0_MEMSIZE(init->MemSize)
                                     |  FSMC_SMSKR0_MEMTYPE(init->MemType) )
                                     ;
}

void FSMC_SetConf(FSMC_Type * FSMCx, uint32_t index, FSMC_Conf_Type * init)
{
    if (index >= FSMC_SMTMGR_REG_NUM)
    {
        return;
    }
    FSMCx->SMTMGRSET[index] = FSMC_SMTMGRSET_TRC(init->ReadPeriod)
                            | FSMC_SMTMGRSET_TAS(init->AddrSetTime)
                            | FSMC_SMTMGRSET_TWR(init->WriteHoldTime)
                            | FSMC_SMTMGRSET_TWP(init->WritePeriod)
                            | FSMC_SMTMGRSET_READYMODE(init->ReadySignal)
                            | FSMC_SMTMGRSET_SMREADPIPE(init->SMReadPipe)
                            ;
    switch (index)
    {
        case 0u:
            FSMCx->SMCTLR = ( (FSMCx->SMCTLR & ~FSMC_SMCTLR_SMDATAWIDTHSET0_MASK)
                                             |  FSMC_SMCTLR_SMDATAWIDTHSET0(init->BusWidth) )
                                             ;
            break;
        case 1u:
            FSMCx->SMCTLR = ( (FSMCx->SMCTLR & ~FSMC_SMCTLR_SMDATAWIDTHSET1_MASK)
                                             |  FSMC_SMCTLR_SMDATAWIDTHSET1(init->BusWidth) )
                                             ;
            break;
        case 2u:
            FSMCx->SMCTLR = ( (FSMCx->SMCTLR & ~FSMC_SMCTLR_SMDATAWIDTHSET2_MASK)
                                             |  FSMC_SMCTLR_SMDATAWIDTHSET2(init->BusWidth) )
                                             ;
            break;
        default:
            break;
    }
}

 /* only last enabled bankn is available. */
void FSMC_EnableConf(FSMC_Type * FSMCx, uint32_t index)
{
    if (index >= FSMC_SMTMGR_REG_NUM)
    {
        return;
    }
    FSMCx->SMSKR0 = ( (FSMCx->SMSKR0 & ~FSMC_SMSKR0_REGSELECT_MASK)
                                     |  FSMC_SMSKR0_REGSELECT(index) )
                                     ;
}

void FSMC_PutData32(FSMC_Type * FSMCx, uint32_t bankn, uint32_t offset, uint32_t data)
{
    (void)FSMCx;
    *( (uint32_t *)(FSMC_BankBases[bankn] + offset) ) = data;
}

uint32_t FSMC_GetData32(FSMC_Type * FSMCx, uint32_t bankn, uint32_t offset)
{
    (void)FSMCx;
    return (*( (uint32_t *)(FSMC_BankBases[bankn] + offset) ) );
}

uint32_t FSMC_GetXferDataRegAddr(FSMC_Type *FSMCx, uint32_t bankn, uint32_t offset)
{
    (void)FSMCx;
    return (FSMC_BankBases[bankn] + offset);
}

void FSMC_PutData16(FSMC_Type * FSMCx, uint32_t bankn, uint32_t offset, uint16_t data)
{
    (void)FSMCx;
    *( (uint16_t *)(FSMC_BankBases[bankn] + offset) ) = data;
}

uint16_t FSMC_GetData16(FSMC_Type * FSMCx, uint32_t bankn, uint32_t offset)
{
    (void)FSMCx;
    return (*( (uint16_t *)(FSMC_BankBases[bankn] + offset) ) );
}

void     FSMC_PutData8(FSMC_Type * FSMCx, uint32_t bankn, uint32_t offset, uint8_t data)
{
    (void)FSMCx;
    *( (uint8_t *)(FSMC_BankBases[bankn] + offset) ) = data;
}

uint8_t  FSMC_GetData8(FSMC_Type * FSMCx, uint32_t bankn, uint32_t offset)
{
    (void)FSMCx;
    return (*( (uint8_t *)(FSMC_BankBases[bankn] + offset) ) );
}

/* EOF. */

