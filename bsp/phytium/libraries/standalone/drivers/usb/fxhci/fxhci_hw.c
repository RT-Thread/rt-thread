/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fxhci_hw.c
 * Date: 2022-02-11 13:33:12
 * LastEditTime: 2022-02-18 09:13:30
 * Description:  This files is for implementation of XHCI register functions
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/7    init commit
 */

/***************************** Include Files *********************************/
#include "fdebug.h"
#include "fgeneric_timer.h"
#include "fsleep.h"

#include "fxhci_private.h"


/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FUSB_DEBUG_TAG "FXHCI_HW"
#define FUSB_ERROR(format, ...)   FT_DEBUG_PRINT_E(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_WARN(format, ...)    FT_DEBUG_PRINT_W(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_INFO(format, ...)    FT_DEBUG_PRINT_I(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/*****************************************************************************/
FError FXhciSetupMMIO(FXhciMMIO *mmio, uintptr base_addr)
{
    FASSERT(mmio);
    u32 reg_val;

    mmio->base = base_addr;

    /* add to register base to find the beginning of the Operational Register Space */
    mmio->oper_base = mmio->base  + FtIn8(mmio->base + FXHCI_REG_CAP_CAPLENGTH);
    mmio->doorbell_base = mmio->base  + FXHCI_REG_CAP_DBOFF_GET(FtIn32(mmio->base  + FXHCI_REG_CAP_DBOFF));
    mmio->runtime_base = mmio->base  + FXHCI_REG_CAP_RTSOFF_GET(FtIn32(mmio->base  + FXHCI_REG_CAP_RTSOFF));
    mmio->port_base = mmio->oper_base + FXHCI_REG_OP_PORTS_BASE;

    /* cache static information of CAP_HCSPARAMS */
    mmio->hcx_params[0] = FtIn32(mmio->base + FXHCI_REG_CAP_HCSPARAMS1);
    mmio->hcx_params[1] = FtIn32(mmio->base + FXHCI_REG_CAP_HCSPARAMS2);
    mmio->hcx_params[2] = FtIn32(mmio->base + FXHCI_REG_CAP_HCSPARAMS3);
    mmio->hcx_params[3] = FtIn32(mmio->base + FXHCI_REG_CAP_HCCPARAMS);

    reg_val = mmio->hcx_params[3];
    mmio->xecp_base = mmio->base + (FXHCI_REG_CAP_HCCPARAMS_XECP_GET(reg_val) << 2);

    FUSB_DEBUG(" mmio base: 0x%x", mmio->base);
    FUSB_DEBUG(" oper base: 0x%x", mmio->oper_base);
    FUSB_DEBUG(" doorbell base: 0x%x", mmio->doorbell_base);
    FUSB_DEBUG(" runtime base: 0x%x", mmio->runtime_base);
    FUSB_DEBUG(" port base: 0x%x", mmio->port_base);

    return FUSB_SUCCESS;
}

static void FXhciParseExtCap(FXhciMMIO *mmio, const uintptr offset, const u32 cap_id)
{
    FASSERT(mmio);
    FASSERT(mmio->base != 0);
    u32 reg_val;
    u32 major_ver, minor_ver;
    u32 psic; /* Protocol Speed ID (PSI) */

    switch (cap_id)
    {
        case FXHCI_EXT_CAP_ID_USB_LEGACY_SUPPORT:
            reg_val = FXhciReadExtCap32(mmio, offset + FXHCI_REG_EXT_CAP_USBLEGSUP_OFFSET);
            FUSB_INFO(" BIOS owned %d OS owned %d",
                      FXHCI_USBLEGSUP_BIOS_OWNED_SEMAPHORE & reg_val,
                      FXHCI_USBLEGSUP_OS_OWNED_SEMAPHORE & reg_val);

            reg_val = FXhciReadExtCap32(mmio, offset + FXHCI_REG_EXT_CAP_USBLEGCTLSTS_OFFSET);
            FUSB_INFO(" SMI ctrl/status 0x%x", reg_val);
            break;
        case FXHCI_EXT_CAP_ID_SUPPORT_PROTOCOL:
            reg_val = FXhciReadExtCap32(mmio, offset + FXHCI_REG_EXT_CAP_USBSPCFDEF_OFFSET);
            FUSB_INFO(" Name: %c%c%c%c",
                      *((char *)&reg_val),  *((char *)&reg_val + 1),
                      *((char *)&reg_val + 2),  *((char *)&reg_val + 3));

            reg_val = FXhciReadExtCap32(mmio, offset + FXHCI_REG_EXT_CAP_USBSPCF_OFFSET);
            major_ver = FXHCI_USBSPCF_MAJOR_REVERSION_GET(reg_val);
            minor_ver = FXHCI_USBSPCF_MINOR_REVERSION_GET(reg_val);
            FUSB_INFO(" Version: %d.%d", major_ver, minor_ver);

            reg_val = FXhciReadExtCap32(mmio, offset + FXHCI_REG_EXT_CAP_USBSPCFDEF2_OFFSET);
            FUSB_INFO(" Compatible ports: [%d-%d]",
                      FXHCI_USBSPCFDEF2_COMPATIBLE_PORT_OFF_GET(reg_val),
                      FXHCI_USBSPCFDEF2_COMPATIBLE_PORT_OFF_GET(reg_val) + FXHCI_USBSPCFDEF2_COMPATIBLE_PORT_CNT_GET(reg_val) - 1);

            if (FXHCI_MAJOR_REVERSION_USB2 == major_ver)
            {
                mmio->usb2_ports.port_beg = FXHCI_USBSPCFDEF2_COMPATIBLE_PORT_OFF_GET(reg_val);
                mmio->usb2_ports.port_end = FXHCI_USBSPCFDEF2_COMPATIBLE_PORT_OFF_GET(reg_val) + FXHCI_USBSPCFDEF2_COMPATIBLE_PORT_CNT_GET(reg_val) - 1;

                FUSB_INFO(" High-speed only: %d, Integrated hub: %d, Hardware LMP: %d",
                          FXHCI_USBSPCFDEF2_USB2_HIGH_SPEED_ONLY & reg_val,
                          FXHCI_USBSPCFDEF2_USB2_INTERGRATED_HUB & reg_val,
                          FXHCI_USBSPCFDEF2_USB2_HW_LMP_CAP & reg_val);
            }
            else if (FXHCI_MAJOR_REVERSION_USB3 == major_ver)
            {
                mmio->usb3_ports.port_beg = FXHCI_USBSPCFDEF2_COMPATIBLE_PORT_OFF_GET(reg_val);
                mmio->usb3_ports.port_end = FXHCI_USBSPCFDEF2_COMPATIBLE_PORT_OFF_GET(reg_val) + FXHCI_USBSPCFDEF2_COMPATIBLE_PORT_CNT_GET(reg_val) - 1;
            }

            psic = FXHCI_USBSPCFDEF2_PROTOCOL_SPEED_ID_CNT_GET(reg_val);
            FUSB_INFO(" PSIC: 0x%x", psic);

            if (0 != psic)
            {
                reg_val = FXhciReadExtCap32(mmio, offset + FXHCI_REG_PROTOCOL_SPEED_ID_OFFSET(psic));

                FUSB_INFO(" Protocol speed-id: %d^%d",
                          FXHCI_PROTOCOL_SPEED_ID_VALUE_GET(reg_val),
                          FXHCI_PROTOCOL_SPEED_ID_EXPONENT_GET(reg_val));
                FUSB_INFO(" PSI type: %d, PSI full-duplex: %d,  Mantissa: 0x%x",
                          FXHCI_PROTOCOL_SPEED_ID_PSI_TYPE_GET(reg_val),
                          (FXHCI_PROTOCOL_SPEED_ID_PSI_FULL_DUPLEX & reg_val == FXHCI_PROTOCOL_SPEED_ID_PSI_FULL_DUPLEX),
                          FXHCI_PROTOCOL_SPEED_ID_MANTISSA_GET(reg_val));
            }
            else
            {
                if (FXHCI_MAJOR_REVERSION_USB3 == major_ver)
                {
                    FUSB_INFO("For USB3, only the default super speed bit rate is supported !!!");
                }
                else if (FXHCI_MAJOR_REVERSION_USB2 == major_ver)
                {
                    FUSB_INFO("For USB2, default full speed, low speed and high speed bit rate supported !!!");
                }
            }

            break;
        case FXHCI_EXT_CAP_ID_USB_DEBUG_CAPABILITY:

            break;
        default:
            FUSB_WARN("Unhandled extend capabilities %d", cap_id);
            break;
    }

    return;
}

void FXhciListExtCap(FXhciMMIO *mmio)
{
    FASSERT(mmio);
    FASSERT(mmio->base != 0);

    uintptr next_ext_cap_offset = 0;
    uintptr ext_cap_offset = 0;
    u32 cap_id = 0;
    u32 reg_val;

    FUSB_INFO("Extended capabilities");
    do
    {
        reg_val = FXhciReadExtCap32(mmio, ext_cap_offset);
        next_ext_cap_offset = (FXHCI_REG_EXT_CAP_NEXT_CAP_PTR_GET(reg_val) << 2);
        cap_id = FXHCI_REG_EXT_CAP_CAP_ID_GET(reg_val);
        FXhciParseExtCap(mmio, ext_cap_offset, cap_id);

        FUSB_INFO("Capability ID: %d, Next Capability Pointer: 0x%x",
                  cap_id, next_ext_cap_offset);
        ext_cap_offset += next_ext_cap_offset;
    }
    while (0 != next_ext_cap_offset);

    return;
}

FError FXhciWaitOper32(FXhciMMIO *mmio, u32 offset, u32 mask, u32 exp_val, u32 timeout_tick)
{
    FASSERT(mmio);
    FASSERT(mmio->base != 0);
    FError ret = FUSB_ERR_WAIT_TIMEOUT;
    u32 tick = 0U;

    do
    {
        if ((FXhciReadOper32(mmio, offset) & mask) == exp_val)
        {
            ret = FUSB_SUCCESS;
            break;
        }
        fsleep_millisec(10);
    }
    while (tick++ < timeout_tick);

    if (FUSB_SUCCESS != ret)
    {
        FUSB_ERROR("Waitting status 0x%x timeout, current 0x%x, tick: %ld", exp_val, mask, tick);
    }

    return ret;
}