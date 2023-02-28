/****************************************************************************
 * @file     nutool_pincfg.c
 * @version  V1.24
 * @Date     2021/08/03-14:56:47
 * @brief    NuMicro generated code file
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright (C) 2013-2021 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

/********************
MCU:MA35D16A887C(BGA312)
Pin Configuration:

PinG16:UART16_nRTS
PinH16:UART16_nCTS
PinJ16:UART16_TXD
PinK16:UART16_RXD
********************/

#include "ma35d1.h"
void nutool_pincfg_init_uart16(void)
{
    SYS->GPK_MFPL &= ~(SYS_GPK_MFPL_PK3MFP_Msk | SYS_GPK_MFPL_PK2MFP_Msk | SYS_GPK_MFPL_PK1MFP_Msk | SYS_GPK_MFPL_PK0MFP_Msk);
    SYS->GPK_MFPL |= (SYS_GPK_MFPL_PK3MFP_UART16_TXD | SYS_GPK_MFPL_PK2MFP_UART16_RXD | SYS_GPK_MFPL_PK1MFP_UART16_nRTS | SYS_GPK_MFPL_PK0MFP_UART16_nCTS);

    return;
}

void nutool_pincfg_deinit_uart16(void)
{
    SYS->GPK_MFPL &= ~(SYS_GPK_MFPL_PK3MFP_Msk | SYS_GPK_MFPL_PK2MFP_Msk | SYS_GPK_MFPL_PK1MFP_Msk | SYS_GPK_MFPL_PK0MFP_Msk);

    return;
}
void nutool_pincfg_init(void)
{
    nutool_pincfg_init_uart16();

    return;
}

void nutool_pincfg_deinit(void)
{

    nutool_pincfg_deinit_uart16();

    return;
}

/*** (C) COPYRIGHT 2013-2021 Nuvoton Technology Corp. ***/
