/*
 * @Author: your name
 * @Date: 2020-11-18 10:10:38
 * @LastEditTime: 2020-11-20 15:01:24
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \stm32f407-handheld - program\applications\cmd_parser.h
 */

#ifndef _CMD_H_
#define _CMD_H_

#include "stdio.h"
 
#define CMD_HASH 0x0b72ab26 //my name and my birthday joaat result

#if defined(__CC_ARM) || defined(__CLANG_ARM)   /* ARM Compiler */
    #define SECTION(x)                  __attribute__((section(x)))
    #define CMD_USED                    __attribute__((used))

#elif defined (__IAR_SYSTEMS_ICC__)             /* IAR Compiler */
    #define SECTION(x)                  @ x
    #define CMD_USED                    __root
    
#elif defined (__GNUC__)                        /* GNU GCC Compiler */
    #define SECTION(x)                  __attribute__((section(x)))
    #define CMD_USED                    __attribute__((used))
#else
    #error "not supported tool chain..."
#endif

typedef void (*cmd_handler)(void);
#define CMD_PACKET_MAX_LEN      (64)
#define CMD_TITEL_MAX_LEN       (64)
#define CMD_CONTENT_MAX_LEN     (64)

typedef struct cmd {
    const char*     cmd;
    const char*     desc;
    unsigned int    hash;
    cmd_handler     handler;
    //const char*     desc;	
} cmd_t;

typedef struct
{
	const char* Cmd_Titel_Head;
	const char* Cmd_Titel_Content_First;
	const char* Cmd_Titel_Content_Cecond;
	const char* Cmd_Titel_Content_Third;
	const char* Cmd_Titel_Tail;
}Cmd_Titel;

static Cmd_Titel cmd_titel[]   =
{
"\r\n/*---------------------------------------------------*/",
"$ Cmd_list:",
"Ignore Upper Lower\r\n",
	NULL,
"/*---------------------------------------------------*/\r\n",
};

static Cmd_Titel cmd_content[] = 
{
	NULL, 
"Error! Please use cmd_list to check cmd menue and retry !",
"is sending to vcom device !",
	NULL,
	NULL,
	NULL,
};

typedef enum
{
    CMD_PACKET_EMPTY = 0, // 空状态
    CMD_PACKET_HEAD, // 收到包头状态
    CMD_PACKET_COMPLETED // 收到完整包状态
} CMD_PACKET_BUF_STATUS_E;

typedef struct
{
    CMD_PACKET_BUF_STATUS_E ePacketStatus;
    uint32_t u32PacketLen;
    uint8_t pu8PacketBuf[CMD_PACKET_MAX_LEN];
} CmdPacketBuf_T;

#define REGISTER_CMD(cmd, handler,desc)                         \
    const char _register_##cmd##_cmd[] = #cmd;                  \
    const char _register_##cmd##_desc[] = #desc;                \
    CMD_USED cmd_t _register_##cmd SECTION("CMDS")=             \
    {                                                           \
        _register_##cmd##_cmd,                                  \
        _register_##cmd##_desc,                                 \
        (unsigned int)CMD_HASH,                                 \
        (cmd_handler)&handler                                   \
    };

void cmd_init(void);
void cmd_parsing(char *str);

#endif

