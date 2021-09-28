/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-09-15     QiuYi        the first version
 * 2017-08-16     Parai        the 2nd version
 */

#include <rtthread.h>
#include <rthw.h>

#include <bsp.h>
#include "keyboard.h"
#include "keymap.h"

#define FALSE RT_FALSE
#define TRUE  RT_TRUE
#define PRIVATE static
#define PUBLIC
#define t_bool  rt_bool_t
#define t_8     rt_uint8_t
#define t_32    rt_uint32_t

PRIVATE KB_INPUT    kb_in;
PRIVATE t_bool      code_with_E0    = FALSE;
PRIVATE t_bool      shift_l;        /* l shift state    */
PRIVATE t_bool      shift_r;        /* r shift state    */
PRIVATE t_bool      alt_l;          /* l alt state      */
PRIVATE t_bool      alt_r;          /* r left state     */
PRIVATE t_bool      ctrl_l;         /* l ctrl state     */
PRIVATE t_bool      ctrl_r;         /* l ctrl state     */
PRIVATE t_bool      caps_lock;      /* Caps Lock        */
PRIVATE t_bool      num_lock;       /* Num Lock     */
PRIVATE t_bool      scroll_lock;        /* Scroll Lock      */
PRIVATE int     column      = 0;    /* keyrow[column] is one value of keymap */

PRIVATE t_8 get_byte_from_kb_buf();
PRIVATE void    set_leds();
PRIVATE void    kb_wait();
PRIVATE void    kb_ack();

PUBLIC void init_keyboard()
{
    kb_in.count = 0;
    kb_in.p_head = kb_in.p_tail = kb_in.buf;

    caps_lock   = 0;
    num_lock    = 1;
    scroll_lock = 0;

    set_leds();
}
PUBLIC rt_bool_t keyboard_read(rt_uint32_t *pkey)
{
    t_8 scan_code;
    t_bool  make;   /* TRUE : make  */
            /* FALSE: break */
    t_32    key = 0;
    t_32*   keyrow;

    if(kb_in.count > 0){
        code_with_E0 = FALSE;
        scan_code = get_byte_from_kb_buf();

        /* start scan */
        if (scan_code == 0xE1) {
            int i;
            static const t_8 pausebreak_scan_code[] = {0xE1, 0x1D, 0x45, 0xE1, 0x9D, 0xC5};
            t_bool is_pausebreak = TRUE;
            for(i=1;i<6;i++){
                if (get_byte_from_kb_buf() != pausebreak_scan_code[i]) {
                    is_pausebreak = FALSE;
                    break;
                }
            }
            if (is_pausebreak) {
                key = PAUSEBREAK;
            }
        }
        else if (scan_code == 0xE0) {
            code_with_E0 = TRUE;
            scan_code = get_byte_from_kb_buf();

            /* PrintScreen pressed */
            if (scan_code == 0x2A) {
                code_with_E0 = FALSE;
                if ((scan_code = get_byte_from_kb_buf()) == 0xE0) {
                    code_with_E0 = TRUE;
                    if ((scan_code = get_byte_from_kb_buf()) == 0x37) {
                        key = PRINTSCREEN;
                        make = TRUE;
                    }
                }
            }
            /* PrintScreen released */
            else if (scan_code == 0xB7) {
                code_with_E0 = FALSE;
                if ((scan_code = get_byte_from_kb_buf()) == 0xE0) {
                    code_with_E0 = TRUE;
                    if ((scan_code = get_byte_from_kb_buf()) == 0xAA) {
                        key = PRINTSCREEN;
                        make = FALSE;
                    }
                }
            }
        } /* if is not PrintScreen, scan_code is the one after 0xE0 */
        if ((key != PAUSEBREAK) && (key != PRINTSCREEN)) {
            /* is Make Code or Break Code */
            make = (scan_code & FLAG_BREAK ? FALSE : TRUE);

            keyrow = &keymap[(scan_code & 0x7F) * MAP_COLS];

            column = 0;

            t_bool caps = shift_l || shift_r;
            if (caps_lock) {
                if ((keyrow[0] >= 'a') && (keyrow[0] <= 'z')){
                    caps = !caps;
                }
            }
            if (caps) {
                column = 1;
            }

            if (code_with_E0) {
                column = 2;
            }

            key = keyrow[column];

            switch(key) {
            case SHIFT_L:
                shift_l = make;
                break;
            case SHIFT_R:
                shift_r = make;
                break;
            case CTRL_L:
                ctrl_l  = make;
                break;
            case CTRL_R:
                ctrl_r  = make;
                break;
            case ALT_L:
                alt_l   = make;
                break;
            case ALT_R:
                alt_l   = make;
                break;
            case CAPS_LOCK:
                if (make) {
                    caps_lock   = !caps_lock;
                    set_leds();
                }
                break;
            case NUM_LOCK:
                if (make) {
                    num_lock    = !num_lock;
                    set_leds();
                }
                break;
            case SCROLL_LOCK:
                if (make) {
                    scroll_lock = !scroll_lock;
                    set_leds();
                }
                break;
            default:
                break;
            }
        }

        if(make){ /* ignore Break Code */
            t_bool pad = FALSE;

            /* handle the small pad first */
            if ((key >= PAD_SLASH) && (key <= PAD_9)) {
                pad = TRUE;
                switch(key) {   /* '/', '*', '-', '+', and 'Enter' in num pad  */
                case PAD_SLASH:
                    key = '/';
                    break;
                case PAD_STAR:
                    key = '*';
                    break;
                case PAD_MINUS:
                    key = '-';
                    break;
                case PAD_PLUS:
                    key = '+';
                    break;
                case PAD_ENTER:
                    key = ENTER;
                    break;
                default:    /* keys whose value depends on the NumLock */
                    if (num_lock) { /* '0' ~ '9' and '.' in num pad */
                        if ((key >= PAD_0) && (key <= PAD_9)) {
                            key = key - PAD_0 + '0';
                        }
                        else if (key == PAD_DOT) {
                            key = '.';
                        }
                    }
                    else{
                        switch(key) {
                        case PAD_HOME:
                            key = HOME;
                            break;
                        case PAD_END:
                            key = END;
                            break;
                        case PAD_PAGEUP:
                            key = PAGEUP;
                            break;
                        case PAD_PAGEDOWN:
                            key = PAGEDOWN;
                            break;
                        case PAD_INS:
                            key = INSERT;
                            break;
                        case PAD_UP:
                            key = UP;
                            break;
                        case PAD_DOWN:
                            key = DOWN;
                            break;
                        case PAD_LEFT:
                            key = LEFT;
                            break;
                        case PAD_RIGHT:
                            key = RIGHT;
                            break;
                        case PAD_DOT:
                            key = DELETE;
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                }
            }
            key |= shift_l  ? FLAG_SHIFT_L  : 0;
            key |= shift_r  ? FLAG_SHIFT_R  : 0;
            key |= ctrl_l   ? FLAG_CTRL_L   : 0;
            key |= ctrl_r   ? FLAG_CTRL_R   : 0;
            key |= alt_l    ? FLAG_ALT_L    : 0;
            key |= alt_r    ? FLAG_ALT_R    : 0;
            key |= pad  ? FLAG_PAD  : 0;

            *pkey = key;
            return TRUE;
        }
    }

    return FALSE;
}

PRIVATE t_8 get_byte_from_kb_buf()
{
    t_8 scan_code;

    RT_ASSERT(kb_in.count>0);
    scan_code = *(kb_in.p_tail);
    kb_in.p_tail++;
    if (kb_in.p_tail == kb_in.buf + KB_IN_BYTES) {
        kb_in.p_tail = kb_in.buf;
    }
    kb_in.count--;

    return scan_code;
}

PRIVATE void kb_wait() /* wait inpit cache of 8042 */
{
    t_8 kb_stat;

    do {
        kb_stat = inb(KB_CMD);
    } while (kb_stat & 0x02);
}

PRIVATE void kb_ack()
{
    t_8 kb_read;

    do {
        kb_read = inb(KB_DATA);
    } while (kb_read != KB_ACK);
}

PRIVATE void set_leds()
{
    t_8 leds = (caps_lock << 2) | (num_lock << 1) | scroll_lock;

    kb_wait();
    outb(KB_DATA, LED_CODE);
    kb_ack();

    kb_wait();
    outb(KB_DATA, leds);
    kb_ack();
}

/**
 * @addtogroup QEMU
 */
/*@{*/

void rt_keyboard_isr(void)
{
    rt_uint8_t data;

    if ((inb(KBSTATP) & KBS_DIB) == 0)
        return ;

    data = inb(KBDATAP);

    if (kb_in.count < KB_IN_BYTES) {
        *(kb_in.p_head) = data;
        kb_in.p_head++;
        if (kb_in.p_head == kb_in.buf + KB_IN_BYTES) {
            kb_in.p_head = kb_in.buf;
        }
        kb_in.count++;
    }
}
/* generally, this should be called in task level for all key inpit support,
but here only support a key that is composed of 2 bytes */
rt_bool_t rt_keyboard_getc(char* c)
{
    if(kb_in.count>=2)
    {
        rt_uint32_t key = 0;
        rt_bool_t rv=keyboard_read(&key);

        switch(key)
        {
            case TAB:
                *c = '\t';
                break;
            case ENTER:
                *c = '\n';
                break;
            case BACKSPACE:
                *c = '\b';
                break;
            default:
                *c = key;
                break;
        }

        return rv;
    }

    return RT_FALSE;
}

/*@}*/
