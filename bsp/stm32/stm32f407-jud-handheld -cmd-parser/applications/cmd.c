/*
 * @Author: jiejie
 * @Github: https://github.com/jiejieTop
 * @Date: 2019-12-13 10:47:30
 * @LastEditTime: 2020-05-16 15:53:35
 * @Description: the code belongs to jiejie, please keep the author information and source code according to the license.
 */
#include "cmd.h"
#include <stdio.h>
#include <rtthread.h>

static cmd_t *_cmd_begin, *_cmd_end;

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
		rt_kprintf("Cmd_list:Ignore Upper Lower\r\n");
    cmd_t *index;
    for (index = _cmd_begin; index < _cmd_end; index = _get_next_cmd(index)) {
        rt_kprintf("-$ %-16s        %-20s\r\n",index->cmd ,index->desc);
    }
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
			rt_kprintf("Error! Please use cmd_list to check cmd menue\r\n");
		}
		
}
