/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "hal_syscfg.h"

#define SYSCFG_EXTICR_MASK(x)   ( (0x0Fu) << ( ( (uint32_t)(x) & 0x3u ) << 2u ) ) /* mask bit for clear exti line. */
#define SYSCFG_EXTICR(x, y)     ( (uint32_t)( (uint32_t)(x) << ( ( (uint32_t)(y) & 0x3u ) << 2u ) ) ) /* set the data for indicated exti port and line. */

void SYSCFG_SetBootMemMode(SYSCFG_BootMemMode_Type mode)
{
    SYSCFG->CFGR = ( SYSCFG->CFGR & ~ SYSCFG_CFGR_MEMMODE_MASK )
                 | SYSCFG_CFGR_MEMMODE(mode);
}

void SYSCFG_SetFSMCPinUseMode(SYSCFG_FSMCPinUseMode_Type mode)
{
    SYSCFG->CFGR = ( SYSCFG->CFGR & ~ SYSCFG_CFGR_FCODATAEN_MASK )
                 | SYSCFG_CFGR_FCODATAEN(mode);
}

void SYSCFG_SetFSMCMode(SYSCFG_FSMCMode_Type mode)
{
    SYSCFG->CFGR = ( SYSCFG->CFGR & ~ SYSCFG_CFGR_MODESEL_MASK )
                 | SYSCFG_CFGR_MODESEL(mode);
}

void SYSCFG_SetExtIntMux(SYSCFG_EXTIPort_Type port, SYSCFG_EXTILine_Type line)
{
    if ( line < SYSCFG_EXTILine_4)
    {
        SYSCFG->EXTICR1 = ( SYSCFG->EXTICR1 & ~ SYSCFG_EXTICR_MASK(line) )
                        | ( SYSCFG_EXTICR(port, line) );
    }
    else if ( line < SYSCFG_EXTILine_8 )
    {
        SYSCFG->EXTICR2 = ( SYSCFG->EXTICR1 & ~ SYSCFG_EXTICR_MASK(line) )
                        | ( SYSCFG_EXTICR(port, line) );
    }
    else if ( line < SYSCFG_EXTILine_12 )
    {
        SYSCFG->EXTICR3 = ( SYSCFG->EXTICR1 & ~ SYSCFG_EXTICR_MASK(line) )
                        | ( SYSCFG_EXTICR(port, line) );
    }
    else
    {
        SYSCFG->EXTICR4 = ( SYSCFG->EXTICR1 & ~ SYSCFG_EXTICR_MASK(line) )
                        | ( SYSCFG_EXTICR(port, line) );
    }
}

void SYSCFG_SetI2C0PortMode(SYSCFG_I2CPortMode_Type mode)
{
    SYSCFG->CFGR2 = ( SYSCFG->CFGR2 & ~ SYSCFG_CFGR2_I2C1MODESEL_MASK )
                  | SYSCFG_CFGR2_I2C1MODESEL(mode);
}

void SYSCFG_SetI2C1PortMode(SYSCFG_I2CPortMode_Type mode)
{
    SYSCFG->CFGR2 = ( SYSCFG->CFGR2 & ~ SYSCFG_CFGR2_I2C2MODESEL_MASK )
                  | SYSCFG_CFGR2_I2C2MODESEL(mode);
}

void SYSCFG_SetENETPortMode(SYSCFG_ENETPortMode_Type mode)
{
    SYSCFG->CFGR2 = ( SYSCFG->CFGR2 & ~ SYSCFG_CFGR2_MIIRMIISEL_MASK )
                  | SYSCFG_CFGR2_MIIRMIISEL(mode);
}

void SYSCFG_SetENETSpeedMode(SYSCFG_ENETSpeedMode_Type mode)
{
    SYSCFG->CFGR2 = ( SYSCFG->CFGR2 & ~ SYSCFG_CFGR2_MACSPDSEL_MASK )
                  | SYSCFG_CFGR2_MACSPDSEL(mode);
}

void SYSCFG_EnablePVD(SYSCFG_PVDConf_Type * conf)
{
    if (conf == NULL)
    {
        SYSCFG->PDETCSR &= ~ SYSCFG_PDETCSR_PVDE_MASK;
    }
    else
    {
        SYSCFG->PDETCSR = ( ( SYSCFG->PDETCSR & ~ ( SYSCFG_PDETCSR_PVDE_MASK
                                              | SYSCFG_PDETCSR_PLS_MASK
                                              | SYSCFG_PDETCSR_PVDO_MASK
                                              ) )
                        | SYSCFG_PDETCSR_PLS(conf->Thold)
                        | SYSCFG_PDETCSR_PVDO(conf->Output)
                        | SYSCFG_PDETCSR_PVDE_MASK
                        );

    }
}

void SYSCFG_EnableVDT(SYSCFG_VDTConf_Type * conf)
{
    if (conf == NULL)
    {
        SYSCFG->PDETCSR &= ~ SYSCFG_PDETCSR_VDTE_MASK;
    }
    else
    {
        SYSCFG->PDETCSR = ( ( SYSCFG->PDETCSR & ~ ( SYSCFG_PDETCSR_VDTE_MASK
                                              | SYSCFG_PDETCSR_VDTLS_MASK
                                              | SYSCFG_PDETCSR_VDTO_MASK
                                              ) )
                        | SYSCFG_PDETCSR_VDTLS(conf->Thold)
                        | SYSCFG_PDETCSR_VDTO(conf->Output)
                        | SYSCFG_PDETCSR_VDTE_MASK
                        );
    }
}

void SYSCFG_EnableADCCheckVBatDiv3(bool enable)
{
    if (enable)
    {
        SYSCFG->PDETCSR |= SYSCFG_PDETCSR_VBATDIV3EN_MASK;
    }
    else
    {
        SYSCFG->PDETCSR &= ~ SYSCFG_PDETCSR_VBATDIV3EN_MASK;
    }
}

void SYSCFG_SetVOSDelayValue(uint32_t val)
{
    SYSCFG->VOSDLY = val;
}

/* EOF. */
