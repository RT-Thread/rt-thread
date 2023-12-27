/******************************************************************************************************************************************
* 文件名称: usbh_hid_keybd.c
* 功能说明:
* 技术支持: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
* 版本日期: V1.1.0      2020年11月3日
* 升级记录:
*
*
*******************************************************************************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION
* REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE
* FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
* OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
* -ECTION WITH THEIR PRODUCTS.
*
* COPYRIGHT 2012 Synwit Technology
*******************************************************************************************************************************************/
#include <string.h>
#include "SWM341.h"
#include "usbh_hid_core.h"
#include "usbh_hid_keybd.h"


USBH_HID_cb_t USBH_HID_KeyBD_cb =
{
    USBH_HID_KeyBD_Init,
    USBH_HID_KeyBD_Decode
};


static const uint8_t HID_KEYBRD_Codes[] = {
      0,   0,   0,   0,  31,  50,  48,  33,  19,  34,  35,  36,  24,  37,  38,  39,
     52,  51,  25,  26,  17,  20,  32,  21,  23,  49,  18,  47,  22,  46,   2,   3,
      4,   5,   6,   7,   8,   9,  10,  11,  43, 110,  15,  16,  61,  12,  13,  27,
     28,  29,  42,  40,  41,   1,  53,  54,  55,  30, 112, 113, 114, 115, 116, 117,
    118, 119, 120, 121, 122, 123, 124, 125, 126,  75,  80,  85,  76,  81,  86,  89,
     79,  84,  83,  90,  95, 100, 105, 106, 108,  93,  98, 103,  92,  97, 102,  91,
     96, 101,  99, 104,  45, 129,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0, 107,   0,  56,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
     58,  44,  60, 127,  64,  57,  62, 128,
};

static const uint8_t HID_KEYBRD_Key[] = {
    '\0', '`',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',
    '9',  '0',  '-',  '=',  '\0', '\r', '\t', 'q',  'w',  'e',
    'r',  't',  'y',  'u',  'i',  'o',  'p',  '[',  ']',  '\\',
    '\0', 'a',  's',  'd',  'f',  'g',  'h',  'j',  'k',  'l',
    ';',  '\'', '\0', '\n', '\0', '\0', 'z',  'x',  'c',  'v',
    'b',  'n',  'm',  ',',  '.',  '/',  '\0', '\0', '\0', '\0',
    '\0', ' ',  '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\r', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '7',  '4',  '1',  '\0', '/',  '8',  '5',  '2',  '0',
    '*',  '9',  '6',  '3',  '.',  '-',  '+',  '\0', '\n', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
};

static const uint8_t HID_KEYBRD_ShiftKey[] = {
    '\0', '~',  '!',  '@',  '#',  '$',  '%',  '^',  '&',  '*',
    '(',  ')',  '_',  '+',  '\0', '\0', '\0', 'Q',  'W',  'E',
    'R',  'T',  'Y',  'U',  'I',  'O',  'P',  '{',  '}',  '|',
    '\0', 'A',  'S',  'D',  'F',  'G',  'H',  'J',  'K',  'L',
    ':',  '"',  '\0', '\n', '\0', '\0', 'Z',  'X',  'C',  'V',
    'B',  'N',  'M',  '<',  '>',  '?',  '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
};


static uint8_t keys_last[6];
static uint8_t nbr_keys_last;


void USBH_HID_KeyBD_Init(void)
{
    nbr_keys_last = 0;
    memset(keys_last, 0x00, 6);
}


void USBH_HID_KeyBD_Decode(uint8_t *pbuf)
{
    char key;
    uint8_t i, j;
    uint8_t keys[6];
    uint8_t keys_new[6];
    uint8_t nbr_keys;
    uint8_t nbr_keys_new;

    for(i = 2; i < 8; i++)
    {
        if((pbuf[i] == 0x01) || (pbuf[i] == 0x02) || (pbuf[i] == 0x03))
            return;
    }

    nbr_keys     = 0;
    nbr_keys_new = 0;
    for(i = 2; i < 8; i++)
    {
        if(pbuf[i] != 0x00)
        {
            keys[nbr_keys++] = pbuf[i];

            for(j = 0; j < nbr_keys_last; j++)
            {
                if(pbuf[i] == keys_last[j])
                    break;
            }

            if(j == nbr_keys_last)  // 遍历到了最后，说明 pbuf[i] 不在 keys_last 中，是新按下的
                keys_new[nbr_keys_new++] = pbuf[i];
        }
    }

    if(nbr_keys_new == 1)
    {
        if((pbuf[0] & KBD_LEFT_SHIFT) || (pbuf[0] & KBD_RIGHT_SHIFT))
        {
            key = HID_KEYBRD_ShiftKey[HID_KEYBRD_Codes[keys_new[0]]];
        }
        else
        {
            key = HID_KEYBRD_Key[HID_KEYBRD_Codes[keys_new[0]]];
        }

        USBH_HID_KeyBD_Handle(pbuf[0], key);    // call user process handle
    }

    memcpy(keys_last, keys, 6);
    nbr_keys_last = nbr_keys;
}


__attribute__((weak))
void USBH_HID_KeyBD_Handle(uint8_t ctrl, char key)
{
    if((ctrl & KBD_LEFT_CTRL) | (ctrl & KBD_RIGHT_CTRL))
        printf("Ctrl-");

    if((ctrl & KBD_LEFT_ALT) | (ctrl & KBD_RIGHT_ALT))
        printf("Alt-");

    printf("%c\r\n", key);
}
