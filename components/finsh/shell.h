#ifndef __SHELL_H__
#define __SHELL_H__

#include <rtthread.h>

#define FINSH_USING_HISTORY
#ifndef FINSH_THREAD_PRIORITY
#define FINSH_THREAD_PRIORITY 20
#endif
#ifndef FINSH_THREAD_STACK_SIZE
#define FINSH_THREAD_STACK_SIZE 2048
#endif
#define FINSH_CMD_SIZE		80

#define FINSH_OPTION_ECHO	0x01
#define FINSH_PROMPT		"finsh>>"

#ifdef FINSH_USING_HISTORY
enum input_stat
{
	WAIT_NORMAL,
	WAIT_SPEC_KEY,
	WAIT_FUNC_KEY,
};
	#ifndef FINSH_HISTORY_LINES
		#define FINSH_HISTORY_LINES 5
	#endif
#endif

struct finsh_shell
{
	struct rt_semaphore rx_sem;

	enum input_stat stat;

	rt_uint8_t echo_mode:1;
	rt_uint8_t use_history:1;

#ifdef FINSH_USING_HISTORY
	rt_uint8_t current_history;
	rt_uint16_t history_count;

	char cmd_history[FINSH_HISTORY_LINES][FINSH_CMD_SIZE];
#endif

	struct finsh_parser parser;

	char line[FINSH_CMD_SIZE];
	rt_uint8_t line_position;

	rt_device_t device;
};

void finsh_set_echo(rt_uint32_t enable);
rt_uint32_t finsh_get_echo(void);

void finsh_set_device(const char* device_name);

#endif
