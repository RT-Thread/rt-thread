/*
 * Copyright (c) 2026, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbd_hid.h"
#include "usbd_gamepad.h"

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t gamepad_report_buffer[64];

static int xinput_vendor_class_request_handler(uint8_t busid, struct usb_setup_packet *setup, uint8_t **data, uint32_t *len)
{
    struct xinput_in_report xinput_report;

    memset(&xinput_report, 0, sizeof(xinput_report));
    xinput_report.report_size = 20;

    memcpy(*data, &xinput_report, sizeof(xinput_report));
    *len = sizeof(xinput_report);
    return 0;
}

int usbd_gamepad_xinput_send_report(uint8_t ep, struct usb_gamepad_report *report)
{
    struct xinput_in_report *xinput_report;

    xinput_report = (struct xinput_in_report *)gamepad_report_buffer;
    memset(xinput_report, 0, sizeof(xinput_report));
    xinput_report->report_size = 20;

    if (report->buttons & USB_GAMEPAD_BUTTON_DU)
        xinput_report->buttons |= XINPUT_BUTTON_MASK_UP;
    if (report->buttons & USB_GAMEPAD_BUTTON_DD)
        xinput_report->buttons |= XINPUT_BUTTON_MASK_DOWN;
    if (report->buttons & USB_GAMEPAD_BUTTON_DL)
        xinput_report->buttons |= XINPUT_BUTTON_MASK_LEFT;
    if (report->buttons & USB_GAMEPAD_BUTTON_DR)
        xinput_report->buttons |= XINPUT_BUTTON_MASK_RIGHT;
    if (report->buttons & USB_GAMEPAD_BUTTON_S2)
        xinput_report->buttons |= XINPUT_BUTTON_MASK_START;
    if (report->buttons & USB_GAMEPAD_BUTTON_S1)
        xinput_report->buttons |= XINPUT_BUTTON_MASK_BACK;
    if (report->buttons & USB_GAMEPAD_BUTTON_L3)
        xinput_report->buttons |= XINPUT_BUTTON_MASK_L3;
    if (report->buttons & USB_GAMEPAD_BUTTON_R3)
        xinput_report->buttons |= XINPUT_BUTTON_MASK_R3;
    if (report->buttons & USB_GAMEPAD_BUTTON_L1)
        xinput_report->buttons |= XINPUT_BUTTON_MASK_LB;
    if (report->buttons & USB_GAMEPAD_BUTTON_R1)
        xinput_report->buttons |= XINPUT_BUTTON_MASK_RB;
    if (report->buttons & USB_GAMEPAD_BUTTON_A1)
        xinput_report->buttons |= XINPUT_BUTTON_MASK_GUIDE;
    if (report->buttons & USB_GAMEPAD_BUTTON_B1)
        xinput_report->buttons |= XINPUT_BUTTON_MASK_A;
    if (report->buttons & USB_GAMEPAD_BUTTON_B2)
        xinput_report->buttons |= XINPUT_BUTTON_MASK_B;
    if (report->buttons & USB_GAMEPAD_BUTTON_B3)
        xinput_report->buttons |= XINPUT_BUTTON_MASK_X;
    if (report->buttons & USB_GAMEPAD_BUTTON_B4)
        xinput_report->buttons |= XINPUT_BUTTON_MASK_Y;

    // Analog triggers (0-255), fall back to digital if analog is 0 but button pressed
    xinput_report->lt = report->lt;
    xinput_report->rt = report->rt;
    if (xinput_report->lt == 0 && (report->buttons & USB_GAMEPAD_BUTTON_L2))
        xinput_report->lt = 0xFF;
    if (xinput_report->rt == 0 && (report->buttons & USB_GAMEPAD_BUTTON_R2))
        xinput_report->rt = 0xFF;

    return usbd_ep_start_write(0, ep, gamepad_report_buffer, sizeof(struct xinput_in_report));
}

// Convert gamepad dpad mask to switch hat value
static uint8_t convert_dpad_to_switch_hat(uint32_t buttons)
{
    // Joypad uses active-high (1 = pressed)
    uint8_t up = (buttons & USB_GAMEPAD_BUTTON_DU) ? 1 : 0;
    uint8_t down = (buttons & USB_GAMEPAD_BUTTON_DD) ? 1 : 0;
    uint8_t left = (buttons & USB_GAMEPAD_BUTTON_DL) ? 1 : 0;
    uint8_t right = (buttons & USB_GAMEPAD_BUTTON_DR) ? 1 : 0;

    if (up && right)
        return SWITCH_HAT_UP_RIGHT;
    if (up && left)
        return SWITCH_HAT_UP_LEFT;
    if (down && right)
        return SWITCH_HAT_DOWN_RIGHT;
    if (down && left)
        return SWITCH_HAT_DOWN_LEFT;
    if (up)
        return SWITCH_HAT_UP;
    if (down)
        return SWITCH_HAT_DOWN;
    if (left)
        return SWITCH_HAT_LEFT;
    if (right)
        return SWITCH_HAT_RIGHT;

    return SWITCH_HAT_CENTER;
}

int usbd_gamepad_switch_send_report(uint8_t ep, struct usb_gamepad_report *report)
{
    struct switch_in_report *switch_report;

    switch_report = (struct switch_in_report *)gamepad_report_buffer;
    memset(switch_report, 0, sizeof(switch_report));

    if (report->buttons & USB_GAMEPAD_BUTTON_S1)
        switch_report->buttons |= SWITCH_MASK_MINUS;
    if (report->buttons & USB_GAMEPAD_BUTTON_S2)
        switch_report->buttons |= SWITCH_MASK_PLUS;
    if (report->buttons & USB_GAMEPAD_BUTTON_L1)
        switch_report->buttons |= SWITCH_MASK_L;
    if (report->buttons & USB_GAMEPAD_BUTTON_R1)
        switch_report->buttons |= SWITCH_MASK_R;
    if (report->buttons & USB_GAMEPAD_BUTTON_L2)
        switch_report->buttons |= SWITCH_MASK_ZL;
    if (report->buttons & USB_GAMEPAD_BUTTON_R2)
        switch_report->buttons |= SWITCH_MASK_ZR;
    if (report->buttons & USB_GAMEPAD_BUTTON_L3)
        switch_report->buttons |= SWITCH_MASK_L3;
    if (report->buttons & USB_GAMEPAD_BUTTON_R3)
        switch_report->buttons |= SWITCH_MASK_R3;
    if (report->buttons & USB_GAMEPAD_BUTTON_A1)
        switch_report->buttons |= SWITCH_MASK_HOME;
    if (report->buttons & USB_GAMEPAD_BUTTON_A2)
        switch_report->buttons |= SWITCH_MASK_CAPTURE;
    if (report->buttons & USB_GAMEPAD_BUTTON_B1)
        switch_report->buttons |= SWITCH_MASK_B;
    if (report->buttons & USB_GAMEPAD_BUTTON_B2)
        switch_report->buttons |= SWITCH_MASK_A;
    if (report->buttons & USB_GAMEPAD_BUTTON_B3)
        switch_report->buttons |= SWITCH_MASK_Y;
    if (report->buttons & USB_GAMEPAD_BUTTON_B4)
        switch_report->buttons |= SWITCH_MASK_X;

    switch_report->hat = convert_dpad_to_switch_hat(report->buttons);

    // Analog sticks (HID convention: 0=up, 255=down - no inversion needed)
    switch_report->lx = report->lx;
    switch_report->ly = report->ly;
    switch_report->rx = report->rx;
    switch_report->ry = report->ry;

    switch_report->vendor = 0;

    return usbd_ep_start_write(0, ep, gamepad_report_buffer, sizeof(struct switch_in_report));
}

struct usbd_interface *usbd_gamepad_xinput_init_intf(struct usbd_interface *intf)
{
    intf->class_interface_handler = NULL;
    intf->class_endpoint_handler = NULL;
    intf->vendor_handler = xinput_vendor_class_request_handler;
    intf->notify_handler = NULL;

    return intf;
}

static const uint8_t hid_switch_report_desc[HID_SWITCH_REPORT_DESC_SIZE] = {
    0x05, 0x01,       // Usage Page (Generic Desktop Ctrls)
    0x09, 0x05,       // Usage (Game Pad)
    0xA1, 0x01,       // Collection (Application)
    0x15, 0x00,       //   Logical Minimum (0)
    0x25, 0x01,       //   Logical Maximum (1)
    0x35, 0x00,       //   Physical Minimum (0)
    0x45, 0x01,       //   Physical Maximum (1)
    0x75, 0x01,       //   Report Size (1)
    0x95, 0x10,       //   Report Count (16)
    0x05, 0x09,       //   Usage Page (Button)
    0x19, 0x01,       //   Usage Minimum (Button 1)
    0x29, 0x10,       //   Usage Maximum (Button 16)
    0x81, 0x02,       //   Input (Data,Var,Abs)
    0x05, 0x01,       //   Usage Page (Generic Desktop Ctrls)
    0x25, 0x07,       //   Logical Maximum (7)
    0x46, 0x3B, 0x01, //   Physical Maximum (315)
    0x75, 0x04,       //   Report Size (4)
    0x95, 0x01,       //   Report Count (1)
    0x65, 0x14,       //   Unit (Eng Rot:Angular Pos)
    0x09, 0x39,       //   Usage (Hat switch)
    0x81, 0x42,       //   Input (Data,Var,Abs,Null)
    0x65, 0x00,       //   Unit (None)
    0x95, 0x01,       //   Report Count (1)
    0x81, 0x01,       //   Input (Const) - 4-bit padding
    0x26, 0xFF, 0x00, //   Logical Maximum (255)
    0x46, 0xFF, 0x00, //   Physical Maximum (255)
    0x09, 0x30,       //   Usage (X) - Left Stick X
    0x09, 0x31,       //   Usage (Y) - Left Stick Y
    0x09, 0x32,       //   Usage (Z) - Right Stick X
    0x09, 0x35,       //   Usage (Rz) - Right Stick Y
    0x75, 0x08,       //   Report Size (8)
    0x95, 0x04,       //   Report Count (4)
    0x81, 0x02,       //   Input (Data,Var,Abs)
    0x06, 0x00, 0xFF, //   Usage Page (Vendor Defined)
    0x09, 0x20,       //   Usage (0x20)
    0x95, 0x01,       //   Report Count (1)
    0x81, 0x02,       //   Input (Data,Var,Abs) - Vendor byte
    0x0A, 0x21, 0x26, //   Usage (0x2621)
    0x95, 0x08,       //   Report Count (8)
    0x91, 0x02,       //   Output (Data,Var,Abs) - Rumble
    0xC0,             // End Collection
};

struct usbd_interface *usbd_gamepad_switch_init_intf(struct usbd_interface *intf)
{
    return usbd_hid_init_intf(0, intf, hid_switch_report_desc, HID_SWITCH_REPORT_DESC_SIZE);
}