/*
 * @[H]: Copyright (C) 2014-2021 Phytium Technology.  All rights reserved.
 * 
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 * 
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 * 
 *  Use of the Software is limited solely to applications:
 *  (a) running on a Phytium device, or
 *  (b) that interact with a Phytium device through a bus or interconnect.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *  PHYTIUM  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 *  OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 * 
 *  Except as contained in this notice, the name of the Phytium shall not be used
 *  in advertising or otherwise to promote the sale, use or other dealings in
 *  this Software without prior written authorization from Phytium. 
 * 
 * @Date: 2021-04-27 13:52:41
 * @LastEditTime: 2021-04-27 13:52:41
 * @Description:  Description of file
 * @Modify History: 
 * * * Ver   Who        Date         Changes
 * * ----- ------     --------    --------------------------------------
 */

#include "ft_can_hw.h"
#include "ft_can.h"
#include "ft_mux.h"
#include "ft_parameters.h"
#include "ft_math.h"
#include "ft_assert.h"
#include "ft_debug.h"

#define CAN_HW_DEBUG_TAG "CAN_HW"

#define CAN_HW_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(CAN_HW_DEBUG_TAG, format, ##__VA_ARGS__)
#define CAN_HW_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(CAN_HW_DEBUG_TAG, format, ##__VA_ARGS__)
#define CAN_HW_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(CAN_HW_DEBUG_TAG, format, ##__VA_ARGS__)

void FCan_Reset(FCan_t *Can_p)
{
    u32 RegValue;
    FCan_Config_t *Config_p;
    Ft_assertVoid(Can_p != NULL);
    Ft_assertVoid(Can_p->IsReady == FT_COMPONENT_IS_READLY);
    Config_p = &Can_p->Config;

    RegValue = FCan_ReadReg(Config_p->CanBaseAddress, FCAN_CTRL_OFFSET);

    if (RegValue & FCAN_CTRL_XFER_MASK)
    {
        CAN_HW_DEBUG_E("FT can is not in configration mode\n");
        Ft_assertVoid(0);
        return;
    }

    FCan_WriteReg(FT_PIN_DEMUX_BASE, FT_PIN_DEMUX_REG204_OFFSET, 0x89999990); // Reuse can IO

    FCan_WriteReg(Config_p->CanBaseAddress, FCAN_CTRL_OFFSET, FCAN_CTRL_RESET_MASK);
    FCan_SetBit(Config_p->CanBaseAddress, FCAN_CTRL_OFFSET, FCAN_CTRL_AIME_MASK);
    FCan_WriteReg(Config_p->CanBaseAddress, FCAN_ACC_ID0_MASK_OFFSET, FCAN_ACC_IDN_MASK);
    FCan_WriteReg(Config_p->CanBaseAddress, FCAN_ACC_ID1_MASK_OFFSET, FCAN_ACC_IDN_MASK);
    FCan_WriteReg(Config_p->CanBaseAddress, FCAN_ACC_ID2_MASK_OFFSET, FCAN_ACC_IDN_MASK);
    FCan_WriteReg(Config_p->CanBaseAddress, FCAN_ACC_ID3_MASK_OFFSET, FCAN_ACC_IDN_MASK);
    FCan_ClearBit(Config_p->CanBaseAddress, FCAN_CTRL_OFFSET, FCAN_CTRL_RESET_MASK);
    FCan_WriteReg(Config_p->CanBaseAddress, FCAN_INTR_OFFSET, FCAN_INTR_TEIE_MASK | FCAN_INTR_REIE_MASK);
}