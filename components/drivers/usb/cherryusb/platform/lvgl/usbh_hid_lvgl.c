/*
 * Copyright (c) 2025, sakumisu
 * Copyright (c) 2025, RCSN
 *
 * SPDX-License-Identifier: Apache-2.0
 */

//Refer to https://github.com/espressif/esp-bsp/blob/master/components/esp_lvgl_port/src/lvgl9/esp_lvgl_port_usbhid.c

#include "usbh_core.h"
#include "usbh_hid.h"
#include "usbh_hid_lvgl.h"

/* LVGL image of cursor */
LV_IMG_DECLARE(img_cursor)

const uint8_t keycode2ascii[57][2] = {
    {0, 0}, /* HID_KEY_NO_PRESS */
    {0, 0}, /* HID_KEY_ROLLOVER */
    {0, 0}, /* HID_KEY_POST_FAIL */
    {0, 0}, /* HID_KEY_ERROR_UNDEFINED */
    {'a', 'A'}, /* HID_KEY_A */
    {'b', 'B'}, /* HID_KEY_B */
    {'c', 'C'}, /* HID_KEY_C */
    {'d', 'D'}, /* HID_KEY_D */
    {'e', 'E'}, /* HID_KEY_E */
    {'f', 'F'}, /* HID_KEY_F */
    {'g', 'G'}, /* HID_KEY_G */
    {'h', 'H'}, /* HID_KEY_H */
    {'i', 'I'}, /* HID_KEY_I */
    {'j', 'J'}, /* HID_KEY_J */
    {'k', 'K'}, /* HID_KEY_K */
    {'l', 'L'}, /* HID_KEY_L */
    {'m', 'M'}, /* HID_KEY_M */
    {'n', 'N'}, /* HID_KEY_N */
    {'o', 'O'}, /* HID_KEY_O */
    {'p', 'P'}, /* HID_KEY_P */
    {'q', 'Q'}, /* HID_KEY_Q */
    {'r', 'R'}, /* HID_KEY_R */
    {'s', 'S'}, /* HID_KEY_S */
    {'t', 'T'}, /* HID_KEY_T */
    {'u', 'U'}, /* HID_KEY_U */
    {'v', 'V'}, /* HID_KEY_V */
    {'w', 'W'}, /* HID_KEY_W */
    {'x', 'X'}, /* HID_KEY_X */
    {'y', 'Y'}, /* HID_KEY_Y */
    {'z', 'Z'}, /* HID_KEY_Z */
    {'1', '!'}, /* HID_KEY_1 */
    {'2', '@'}, /* HID_KEY_2 */
    {'3', '#'}, /* HID_KEY_3 */
    {'4', '$'}, /* HID_KEY_4 */
    {'5', '%'}, /* HID_KEY_5 */
    {'6', '^'}, /* HID_KEY_6 */
    {'7', '&'}, /* HID_KEY_7 */
    {'8', '*'}, /* HID_KEY_8 */
    {'9', '('}, /* HID_KEY_9 */
    {'0', ')'}, /* HID_KEY_0 */
    {'\r', '\r'}, /* HID_KEY_ENTER */
    {0, 0},       /* HID_KEY_ESC */
    {'\b', 0},    /* HID_KEY_DEL */
    {0, 0},       /* HID_KEY_TAB */
    {' ', ' '},   /* HID_KEY_SPACE */
    {'-', '_'},   /* HID_KEY_MINUS */
    {'=', '+'},   /* HID_KEY_EQUAL */
    {'[', '{'},   /* HID_KEY_OPEN_BRACKET */
    {']', '}'},   /* HID_KEY_CLOSE_BRACKET */
    {'\\', '|'},  /* HID_KEY_BACK_SLASH */
    {'\\', '|'},  /* HID_KEY_SHARP */
    {';', ':'},   /* HID_KEY_COLON */
    {'\'', '"'},  /* HID_KEY_QUOTE */
    {'`', '~'},   /* HID_KEY_TILDE */
    {',', '<'},   /* HID_KEY_LESS */
    {'.', '>'},   /* HID_KEY_GREATER */
    {'/', '?'}    /* HID_KEY_SLASH */
};

struct usbh_hid_lvgl {
    struct {
        lv_indev_t *indev;   /* LVGL mouse input device driver */
        uint8_t sensitivity; /* Mouse sensitivity (cannot be zero) */
        int16_t x;           /* Mouse X coordinate */
        int16_t y;           /* Mouse Y coordinate */
        bool left_button;    /* Mouse left button state */
    } mouse;
    struct {
        lv_indev_t *indev; /* LVGL keyboard input device driver */
        uint32_t last_key;
        bool pressed;
    } kb;
};

static struct usbh_hid_lvgl g_hid_lvgl;

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t hid_mouse_buffer[64];
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t hid_keyboard_buffer[64];

#if defined(LVGL_VERSION_MAJOR) && (LVGL_VERSION_MAJOR == 9)
static void usbh_hid_lvgl_read_mouse(lv_indev_t *indev_drv, lv_indev_data_t *data)
{
    int16_t width = 0;
    int16_t height = 0;
    struct usbh_hid_lvgl *ctx = &g_hid_lvgl;

    lv_display_t *disp = lv_indev_get_display(indev_drv);
    if (lv_display_get_rotation(disp) == LV_DISPLAY_ROTATION_0 || lv_display_get_rotation(disp) == LV_DISPLAY_ROTATION_180) {
        width = lv_display_get_physical_horizontal_resolution(disp);
        height = lv_display_get_vertical_resolution(disp);
    } else {
        width = lv_display_get_vertical_resolution(disp);
        height = lv_display_get_physical_horizontal_resolution(disp);
    }

    /* Screen borders */
    if (ctx->mouse.x < 0) {
        ctx->mouse.x = 0;
    } else if (ctx->mouse.x >= width * ctx->mouse.sensitivity) {
        ctx->mouse.x = (width * ctx->mouse.sensitivity) - 1;
    }
    if (ctx->mouse.y < 0) {
        ctx->mouse.y = 0;
    } else if (ctx->mouse.y >= height * ctx->mouse.sensitivity) {
        ctx->mouse.y = (height * ctx->mouse.sensitivity) - 1;
    }

    /* Get coordinates by rotation with sensitivity */
    switch (lv_display_get_rotation(disp)) {
        case LV_DISPLAY_ROTATION_0:
            data->point.x = ctx->mouse.x / ctx->mouse.sensitivity;
            data->point.y = ctx->mouse.y / ctx->mouse.sensitivity;
            break;
        case LV_DISPLAY_ROTATION_90:
            data->point.y = width - ctx->mouse.x / ctx->mouse.sensitivity;
            data->point.x = ctx->mouse.y / ctx->mouse.sensitivity;
            break;
        case LV_DISPLAY_ROTATION_180:
            data->point.x = width - ctx->mouse.x / ctx->mouse.sensitivity;
            data->point.y = height - ctx->mouse.y / ctx->mouse.sensitivity;
            break;
        case LV_DISPLAY_ROTATION_270:
            data->point.y = ctx->mouse.x / ctx->mouse.sensitivity;
            data->point.x = height - ctx->mouse.y / ctx->mouse.sensitivity;
            break;
    }

    if (ctx->mouse.left_button) {
        data->state = LV_INDEV_STATE_PRESSED;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

static void usbh_hid_lvgl_read_keyboard(lv_indev_t *indev_drv, lv_indev_data_t *data)
{
    (void)indev_drv;
    struct usbh_hid_lvgl *ctx = &g_hid_lvgl;

    data->key = ctx->kb.last_key;
    if (ctx->kb.pressed) {
        data->state = LV_INDEV_STATE_PRESSED;
        ctx->kb.pressed = false;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
        ctx->kb.last_key = 0;
    }
}

#elif defined(LVGL_VERSION_MAJOR) && (LVGL_VERSION_MAJOR == 8)
static lv_indev_drv_t indev_drv;
static lv_indev_drv_t keyboard_drv;
static void hpm_lvgl_indev_read_cb(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    int16_t width = 0;
    int16_t height = 0;
    struct usbh_hid_lvgl *ctx = &g_hid_lvgl;
    
    if ((indev_drv->disp->driver->rotated == LV_DISP_ROT_NONE) || (indev_drv->disp->driver->rotated == LV_DISP_ROT_180)) {
        width = indev_drv->disp->driver->hor_res;
        height = indev_drv->disp->driver->ver_res;
    } else {
        width = indev_drv->disp->driver->ver_res;
        height = indev_drv->disp->driver->hor_res;    
    }


    /* Screen borders */
    if (ctx->mouse.x < 0) {
        ctx->mouse.x = 0;
    } else if (ctx->mouse.x >= width * ctx->mouse.sensitivity) {
        ctx->mouse.x = (width * ctx->mouse.sensitivity) - 1;
    }
    if (ctx->mouse.y < 0) {
        ctx->mouse.y = 0;
    } else if (ctx->mouse.y >= height * ctx->mouse.sensitivity) {
        ctx->mouse.y = (height * ctx->mouse.sensitivity) - 1;
    }

    /* Get coordinates by rotation with sensitivity */
    switch (indev_drv->disp->driver->rotated) {
    case LV_DISP_ROT_NONE:
        data->point.x = ctx->mouse.x / ctx->mouse.sensitivity;
        data->point.y = ctx->mouse.y / ctx->mouse.sensitivity;
        break;
    case LV_DISP_ROT_90:
        data->point.y = width - ctx->mouse.x / ctx->mouse.sensitivity;
        data->point.x = ctx->mouse.y / ctx->mouse.sensitivity;
        break;
    case LV_DISP_ROT_180:
        data->point.x = width - ctx->mouse.x / ctx->mouse.sensitivity;
        data->point.y = height - ctx->mouse.y / ctx->mouse.sensitivity;
        break;
    case LV_DISP_ROT_270:
        data->point.y = ctx->mouse.x / ctx->mouse.sensitivity;
        data->point.x = height - ctx->mouse.y / ctx->mouse.sensitivity;
        break;
    }

    if (ctx->mouse.left_button) {
        data->state = LV_INDEV_STATE_PRESSED;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

static void usbh_hid_lvgl_read_keyboard(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    (void)indev_drv;
    struct usbh_hid_lvgl *ctx = &g_hid_lvgl;

    data->key = ctx->kb.last_key;
    if (ctx->kb.pressed) {
        data->state = LV_INDEV_STATE_PRESSED;
        ctx->kb.pressed = false;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
        ctx->kb.last_key = 0;
    }
}
#endif

lv_indev_t *usbh_hid_lvgl_add_mouse(uint8_t sensitivity)
{
    int32_t ver_res, hor_res;
    lv_indev_t *indev;

    /* Initialize USB HID */
    struct usbh_hid_lvgl *hid_ctx = &g_hid_lvgl;

    /* Mouse sensitivity cannot be zero */
    hid_ctx->mouse.sensitivity = (sensitivity == 0 ? 1 : sensitivity);

#if defined(LVGL_VERSION_MAJOR) && (LVGL_VERSION_MAJOR == 9)
    ver_res = lv_display_get_vertical_resolution(lv_display_get_default());
    hor_res = lv_display_get_physical_horizontal_resolution(lv_display_get_default());
#elif defined(LVGL_VERSION_MAJOR) && (LVGL_VERSION_MAJOR == 8)
    lv_disp_t * disp = lv_disp_get_default();
    ver_res = disp->driver->hor_res;
    hor_res = disp->driver->ver_res;
#endif
    /* Default coordinates to screen center */
    hid_ctx->mouse.x = (hor_res * hid_ctx->mouse.sensitivity) / 2;
    hid_ctx->mouse.y = (ver_res * hid_ctx->mouse.sensitivity) / 2;

    /* Register a mouse input device */
#if defined(LVGL_VERSION_MAJOR) && (LVGL_VERSION_MAJOR == 9)
    indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, usbh_hid_lvgl_read_mouse);
    lv_indev_set_driver_data(indev, hid_ctx);
    hid_ctx->mouse.indev = indev;
#elif defined(LVGL_VERSION_MAJOR) && (LVGL_VERSION_MAJOR == 8)
    lv_indev_drv_init(&indev_drv);
    indev_drv.read_cb = hpm_lvgl_indev_read_cb;
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.user_data = (void *)hid_ctx;
    indev = lv_indev_drv_register(&indev_drv);
#endif
    /* Set image of cursor */
    lv_obj_t *cursor;
    cursor = lv_img_create(lv_scr_act());
    lv_img_set_src(cursor, &img_cursor);
    lv_indev_set_cursor(indev, cursor);

    return indev;
}

lv_indev_t *usbh_hid_lvgl_add_keyboard(void)
{
    lv_indev_t *indev;

    /* Initialize USB HID */
    struct usbh_hid_lvgl *hid_ctx = &g_hid_lvgl;

    /* Register a keyboard input device */
#if defined(LVGL_VERSION_MAJOR) && (LVGL_VERSION_MAJOR == 9)
    indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_KEYPAD);
    lv_indev_set_read_cb(indev, usbh_hid_lvgl_read_keyboard);
    lv_indev_set_driver_data(indev, hid_ctx);
    hid_ctx->kb.indev = indev;
#elif defined(LVGL_VERSION_MAJOR) && (LVGL_VERSION_MAJOR == 8)
    lv_indev_drv_init(&keyboard_drv);
    keyboard_drv.read_cb = usbh_hid_lvgl_read_keyboard;
    keyboard_drv.type = LV_INDEV_TYPE_KEYPAD;
    keyboard_drv.user_data = (void *)hid_ctx;
    indev = lv_indev_drv_register(&keyboard_drv);
#endif
    return indev;
}

void usbh_hid_mouse_callback(void *arg, int nbytes)
{
    struct usbh_hid *hid_class = (struct usbh_hid *)arg;

    if (nbytes > 0) {
        struct usbh_hid_lvgl *hid_ctx = &g_hid_lvgl;

        hid_ctx->mouse.left_button = hid_mouse_buffer[0];
        hid_ctx->mouse.x += (int8_t)hid_mouse_buffer[1];
        hid_ctx->mouse.y += (int8_t)hid_mouse_buffer[2];

        usbh_int_urb_fill(&hid_class->intin_urb, hid_class->hport, hid_class->intin, hid_mouse_buffer, hid_class->intin->wMaxPacketSize, 0,
                          usbh_hid_mouse_callback, hid_class);
        usbh_submit_urb(&hid_class->intin_urb);
    } else if (nbytes == -USB_ERR_NAK) { /* only dwc2 should do this */
        usbh_int_urb_fill(&hid_class->intin_urb, hid_class->hport, hid_class->intin, hid_mouse_buffer, hid_class->intin->wMaxPacketSize, 0,
                          usbh_hid_mouse_callback, hid_class);
        usbh_submit_urb(&hid_class->intin_urb);
    } else {
    }
}

static char usb_hid_get_keyboard_char(uint8_t key, uint8_t shift)
{
    char ret_key = 0;
    static bool cap_lock = false;

    if (shift > 1) {
        shift = 1;
    }

    if ((key >= HID_KBD_USAGE_A) && (key <= HID_KBD_USAGE_QUESTION)) {
        ret_key = (cap_lock == false) ?  keycode2ascii[key][0] : keycode2ascii[key][1];
    } else if ((key >= HID_KBD_USAGE_1) && (key <= HID_KBD_USAGE_QUESTION)) {
        ret_key = keycode2ascii[key][shift];
    } else if ((key >= HID_KBD_USAGE_KPD1) && (key <= HID_KBD_USAGE_KPD0)) {
        ret_key = keycode2ascii[(key - HID_KBD_USAGE_KPD1) + HID_KBD_USAGE_1][0];
    } else if ((key >= HID_KBD_USAGE_KPDDIV) && (key <= HID_KBD_USAGE_KPDEMTER)) {
        switch (key) {
        case HID_KBD_USAGE_KPDDIV:
            ret_key = '/';
            break;
        case HID_KBD_USAGE_KPDMUL:
            ret_key = '*';
            break;
        case HID_KBD_USAGE_KPDHMINUS:
            ret_key = '-';
            break;
        case HID_KBD_USAGE_KPDPLUS:
            ret_key = '+';
            break;
        default:
            break;
        }
    } else if (key == HID_KBD_USAGE_KPDDELETE) {
        ret_key = '.';
    } else if (key == HID_KBD_USAGE_CAPSLOCK) {
        cap_lock = !cap_lock;
    }

    return ret_key;
}

void usbh_hid_keyboard_callback(void *arg, int nbytes)
{
    struct usbh_hid *hid_class = (struct usbh_hid *)arg;

    if (nbytes > 0) {
        struct usbh_hid_lvgl *hid_ctx = &g_hid_lvgl;
        struct usb_hid_kbd_report *keyboard = (struct usb_hid_kbd_report *)hid_keyboard_buffer;

        for (int i = 0; i < 6; i++) {
            if ((keyboard->key[i] <= HID_KBD_USAGE_MAX) && (keyboard->key[i] > HID_KBD_USAGE_NONE)) {
                char key = 0;

                /* LVGL special keys */
                if (keyboard->key[i] == HID_KBD_USAGE_TAB) {
                    if (((keyboard->modifier & HID_MODIFIER_LSHIFT) || (keyboard->modifier & HID_MODIFIER_RSHIFT))) {
                        key = LV_KEY_PREV;
                    } else {
                        key = LV_KEY_NEXT;
                    }
                } else if (keyboard->key[i] == HID_KBD_USAGE_RIGHT) {
                    key = LV_KEY_RIGHT;
                } else if (keyboard->key[i] == HID_KBD_USAGE_LEFT) {
                    key = LV_KEY_LEFT;
                } else if (keyboard->key[i] == HID_KBD_USAGE_DOWN) {
                    key = LV_KEY_DOWN;
                } else if (keyboard->key[i] == HID_KBD_USAGE_UP) {
                    key = LV_KEY_UP;
                } else if (keyboard->key[i] == HID_KBD_USAGE_ENTER || keyboard->key[i] == HID_KBD_USAGE_KPDEMTER) {
                    key = LV_KEY_ENTER;
                } else if (keyboard->key[i] == HID_KBD_USAGE_DELETE) {
                    key = LV_KEY_BACKSPACE;
                } else if (keyboard->key[i] == HID_KBD_USAGE_HOME) {
                    key = LV_KEY_HOME;
                } else if (keyboard->key[i] == HID_KBD_USAGE_END) {
                    key = LV_KEY_END;
                } else if (keyboard->key[i] == HID_KBD_USAGE_DELFWD) {
                    key = LV_KEY_DEL;
                } else {
                    /* Get ASCII char */
                    key = usb_hid_get_keyboard_char(keyboard->key[i], ((keyboard->modifier & HID_MODIFIER_LSHIFT) || (keyboard->modifier & HID_MODIFIER_RSHIFT)));
                }

                if (key == 0) {
                    USB_LOG_ERR("Not recognized key: %c (%d)\r\n", keyboard->key[i], keyboard->key[i]);
                }
                hid_ctx->kb.last_key = key;
                hid_ctx->kb.pressed = true;
            }
        }

        usbh_int_urb_fill(&hid_class->intin_urb, hid_class->hport, hid_class->intin, hid_keyboard_buffer, hid_class->intin->wMaxPacketSize, 0,
                        usbh_hid_keyboard_callback, hid_class);
        usbh_submit_urb(&hid_class->intin_urb);
    } else if (nbytes == -USB_ERR_NAK) { /* only dwc2 should do this */
        usbh_int_urb_fill(&hid_class->intin_urb, hid_class->hport, hid_class->intin, hid_keyboard_buffer, hid_class->intin->wMaxPacketSize, 0,
                        usbh_hid_keyboard_callback, hid_class);
        usbh_submit_urb(&hid_class->intin_urb);
    } else {
    }
}

extern int usbh_hid_set_protocol(struct usbh_hid *hid_class, uint8_t protocol);

void usbh_hid_run(struct usbh_hid *hid_class)
{
    usbh_hid_set_protocol(hid_class, 0);

    if (hid_class->hport->config.intf[hid_class->intf].altsetting[0].intf_desc.bInterfaceProtocol == HID_PROTOCOL_KEYBOARD) {
        usbh_int_urb_fill(&hid_class->intin_urb, hid_class->hport, hid_class->intin, hid_keyboard_buffer, hid_class->intin->wMaxPacketSize, 0,
                          usbh_hid_keyboard_callback, hid_class);
        usbh_submit_urb(&hid_class->intin_urb);
    } else if (hid_class->hport->config.intf[hid_class->intf].altsetting[0].intf_desc.bInterfaceProtocol == HID_PROTOCOL_MOUSE) {
        usbh_int_urb_fill(&hid_class->intin_urb, hid_class->hport, hid_class->intin, hid_mouse_buffer, hid_class->intin->wMaxPacketSize, 0,
                          usbh_hid_mouse_callback, hid_class);
        usbh_submit_urb(&hid_class->intin_urb);
    } else {
    }
}

void usbh_hid_stop(struct usbh_hid *hid_class)
{
    (void)hid_class;
}