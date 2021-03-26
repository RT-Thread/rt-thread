/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico.h"
#include "pico/time.h"
#include "hardware/structs/usb.h"
#include "hardware/gpio.h"
#include "pico/fix/rp2040_usb_device_enumeration.h"

#define LS_SE0 0b00
#define LS_J   0b01
#define LS_K   0b10
#define LS_SE1 0b11

static void hw_enumeration_fix_wait_se0(void);
static void hw_enumeration_fix_force_ls_j(void);
static void hw_enumeration_fix_finish(void);

void rp2040_usb_device_enumeration_fix(void) {
    // After coming out of reset, the hardware expects 800us of LS_J (linestate J) time
    // before it will move to the connected state. However on a hub that broadcasts packets
    // for other devices this isn't the case. The plan here is to wait for the end of the bus
    // reset, force an LS_J for 1ms and then switch control back to the USB phy. Unfortunately
    // this requires us to use GPIO15 as there is no other way to force the input path.
    // We only need to force DP as DM can be left at zero. It will be gated off by GPIO
    // logic if it isn't func selected.

    // Wait SE0 phase will call force ls_j phase which will call finish phase
    hw_enumeration_fix_wait_se0();
}

static inline uint8_t hw_line_state(void) {
    return (usb_hw->sie_status & USB_SIE_STATUS_LINE_STATE_BITS) >> USB_SIE_STATUS_LINE_STATE_LSB;
}

int64_t hw_enumeration_fix_wait_se0_callback(alarm_id_t id, void *user_data) {
    if (hw_line_state() == LS_SE0) {
        // Come back in 1ms and check again
        return 1000;
    } else {
        // Now force LS_J (next stage of fix)
        hw_enumeration_fix_force_ls_j();
        // No more repeats
        return 0;
    }
}

static inline void hw_enumeration_fix_busy_wait_se0(void) {
    while (hw_line_state() == LS_SE0) tight_loop_contents();
    // Now force LS_J (next stage of fix)
    hw_enumeration_fix_force_ls_j();
}

static void hw_enumeration_fix_wait_se0(void) {
    // Wait for SE0 to end (i.e. the host to stop resetting). This reset can last quite long.
    // 10-15ms so we are going to set a timer callback.

#if !PICO_TIME_DEFAULT_ALARM_POOL_DISABLED
    if (add_alarm_in_ms(1, hw_enumeration_fix_wait_se0_callback, NULL, true) >= 0) {
        // hw_enumeration_fix_wait_se0_callback will be called in 1ms to check if se0 has finished
        // (and will poll every 1ms from there)
        return;
    }
#endif
    // if timer pool disabled, or no timer available, have to busy wait.
    hw_enumeration_fix_busy_wait_se0();
}

int64_t hw_enumeration_fix_force_ls_j_done(alarm_id_t id, void *user_data) {
    hw_enumeration_fix_finish();
    return 0;
}

static void hw_enumeration_fix_force_ls_j(void) {
    // Force LS_J
    const uint dp = 15;
    //const uint dm = 16;
    gpio_set_function(dp, 8);
    // TODO: assert dm is not funcseld to usb

    // J state is a differential 1 for a full speed device so
    // DP = 1 and DM = 0. Don't actually need to set DM low as it
    // is already gated assuming it isn't funcseld.
    gpio_set_inover(dp, GPIO_OVERRIDE_HIGH);

    // TODO: What to do about existing DP state here?

    // Force PHY pull up to stay before switching away from the phy
    hw_set_alias(usb_hw)->phy_direct = USB_USBPHY_DIRECT_DP_PULLUP_EN_BITS;
    hw_set_alias(usb_hw)->phy_direct_override = USB_USBPHY_DIRECT_OVERRIDE_DP_PULLUP_EN_OVERRIDE_EN_BITS;

    // Switch to GPIO phy with LS_J forced
    usb_hw->muxing = USB_USB_MUXING_TO_DIGITAL_PAD_BITS | USB_USB_MUXING_SOFTCON_BITS;

    // LS_J is now forced but while loop here just to check
    hard_assert(hw_line_state() == LS_J); // "LS_J not forced!"

#if !PICO_TIME_DEFAULT_ALARM_POOL_DISABLED
    if (add_alarm_in_ms(1, hw_enumeration_fix_force_ls_j_done, NULL, true) >= 0) {
        // hw_enumeration_fix_force_ls_j_done will be called in 1ms
        return;
    }
#endif
    // if timer pool disabled, or no timer available, have to busy wait.
    busy_wait_us(1000);
    hw_enumeration_fix_finish();
}

static void hw_enumeration_fix_finish(void) {
    // Should think we are connected now
    while (!(usb_hw->sie_status & USB_SIE_STATUS_CONNECTED_BITS)) tight_loop_contents();

    // Switch back to USB phy
    usb_hw->muxing = USB_USB_MUXING_TO_PHY_BITS | USB_USB_MUXING_SOFTCON_BITS;

    // Get rid of DP pullup override
    hw_clear_alias(usb_hw)->phy_direct_override = USB_USBPHY_DIRECT_OVERRIDE_DP_PULLUP_EN_OVERRIDE_EN_BITS;
}
