
#include "cmd_parser.h"
#include <stdio.h>
#include <rtthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <rtthread.h>


#include "cmd_parser.h"
#include "strref.h"
#include "common.h"
#include "util.h"
#include "app.h"
#include "board_config.h"

#include "strref.h"

static cmd_t *_cmd_begin, *_cmd_end;
#define CMD_PACKET_MAX_LEN (64)
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

/* communication mode */
static CmdPacketBuf_T s_tCmdPacketBuf = {CMD_PACKET_EMPTY};

static void _CMD_Response(const char* pcszFmt, ...)
{
	
	char szCmdRspBuf[CMD_PACKET_MAX_LEN] = "";
	int iCmdRspLen = 0;
	va_list ap;
	va_start(ap, pcszFmt);
	iCmdRspLen = rt_vsnprintf(szCmdRspBuf, sizeof(szCmdRspBuf), pcszFmt, ap);
	va_end(ap);
	if ((iCmdRspLen > 0) && (iCmdRspLen <= (sizeof(szCmdRspBuf) - 2)))
	{
		szCmdRspBuf[iCmdRspLen++] = '\r';
		szCmdRspBuf[iCmdRspLen++] = '\n';
		/* ues the set channel send data */
		com_send_data((const uint8_t*)szCmdRspBuf, (uint32_t)iCmdRspLen);
	}
}

/*************************************************
* Function: _CMD_ClearPacketBuf
* Description: 清空CMD Packet Buffer
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
static void _CMD_ClearPacketBuf(void)
{
	//memset(&s_tCmdPacketBuf, 0, sizeof(s_tCmdPacketBuf));
	s_tCmdPacketBuf.ePacketStatus = CMD_PACKET_EMPTY;
	s_tCmdPacketBuf.u32PacketLen = 0;

}

/*************************************************
* Function: CMD_ClearPacketBuf
* Description: 清空Packet Buffer
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
void CMD_ClearPacketBuf(void)
{
	_CMD_ClearPacketBuf();
}

static void _CMD_HandlerVER(const StrConstRef_T* pctStrRefParam)
{
		_CMD_Response("[VER]=%s", VERSION);
//rt_kprintf("VER=%s\r\n", VERSION);
}
REGISTER_CMD(VER, _CMD_HandlerVER,show the version);


static int _cmd_to_lower(int c)
{
    if ((c >= 'A') && (c <= 'Z'))
        return c + ('a' - 'A');
    return c;
}

static unsigned int _cmd_hash(const char* str)
{
    int tmp, c = *str;
    unsigned int seed = CMD_HASH;  /* 'jiejie' string hash */  
    unsigned int hash = 0;
    
    while(*str) {
        tmp = _cmd_to_lower(c);
        hash = (hash ^ seed) + tmp;
        str++;
        c = *str;
    }
    return hash;
}

static void _cmd_init(const void *begin, const void *end)
{
    _cmd_begin = (cmd_t*) begin;
    _cmd_end = (cmd_t*) end;
}

static cmd_t* _get_next_cmd(cmd_t *cmd)
{
    unsigned int *ptr;
    ptr = (unsigned int*) (cmd + 1);
    while ((*ptr == 0) && ((unsigned int*)ptr < (unsigned int*) _cmd_end))
        ptr ++;

    return (cmd_t*) ptr;
}

static int _cmd_match(const char *str, const char *cmd)
{
    int c1, c2;

    do {
        c1 = _cmd_to_lower(*str++);
        c2 = _cmd_to_lower(*cmd++);
    } while((c1 == c2) && c1);

    return c1 - c2;
}

static void _list(void)
{
//	cmd_titel.Cmd_Titel_Head           =  "\r\n/*---------------------------------------------------*/";
//	cmd_titel.Cmd_Titel_Content_First  =  "$ Cmd_list:";
//	cmd_titel.Cmd_Titel_Content_Cecond =  "Ignore Upper Lower\r\n";
//	cmd_titel.Cmd_Titel_Tail           =  "/*---------------------------------------------------*/\r\n";
	
		_CMD_Response("%s",cmd_titel->Cmd_Titel_Head);
  	_CMD_Response("%-28s   %-s",cmd_titel->Cmd_Titel_Content_First,cmd_titel->Cmd_Titel_Content_Cecond);

		rt_kprintf("%s\r\n",cmd_titel->Cmd_Titel_Head);
  	rt_kprintf("%-28s   %-s\r\n",cmd_titel->Cmd_Titel_Content_First,cmd_titel->Cmd_Titel_Content_Cecond);
	
    cmd_t *index;
    for (index = _cmd_begin; index < _cmd_end; index = _get_next_cmd(index)) {
      rt_kprintf("$ %-28s %-s\r\n",index->cmd ,index->desc);
			_CMD_Response("$ %-28s %-s",index->cmd ,index->desc);
			
    }
		rt_kprintf("%s\r\n",cmd_titel->Cmd_Titel_Tail);
		_CMD_Response("%s",cmd_titel->Cmd_Titel_Tail);
}
REGISTER_CMD(cmd_list, _list,list all command);

void cmd_init(void)
{
    cmd_t *index;

#if defined(__CC_ARM) || defined(__CLANG_ARM)          /* ARM C Compiler */
    extern const int CMDS$$Base;
    extern const int CMDS$$Limit;
    _cmd_init(&CMDS$$Base, &CMDS$$Limit);
#elif defined (__ICCARM__) || defined(__ICCRX__)      /* for IAR Compiler */
    _cmd_init(__section_begin("CMDS"), __section_end("CMDS"));
#endif

    for (index = _cmd_begin; index < _cmd_end; index = _get_next_cmd(index)) {
        index->hash = _cmd_hash(index->cmd);
    }

}

void cmd_parsing(char *str)
{
    cmd_t *index;
		rt_uint8_t error_conut=0;
    unsigned int hash = _cmd_hash(str);
   
    for (index = _cmd_begin; index < _cmd_end; index = _get_next_cmd(index)) {
        if (hash == index->hash) {
            if (_cmd_match(str, index->cmd) == 0) {
								rt_kprintf("$ %s %s\r\n",index->cmd ,cmd_content->Cmd_Titel_Content_Cecond); //"is sending to vcom device !"
                index->handler();
								error_conut = 0;
							
                break;
            }
        }
				else
				{
					error_conut+= 1;
				}
    }
		
		if(error_conut != 0)
		{
			rt_kprintf("%s\r\n",cmd_content->Cmd_Titel_Content_First);//"Error! Please use cmd_list to check cmd menue and retry !"
			_CMD_Response("%s",cmd_content->Cmd_Titel_Content_First); //"Error! Please use cmd_list to check cmd menue and retry !"
			
		}
		
}
