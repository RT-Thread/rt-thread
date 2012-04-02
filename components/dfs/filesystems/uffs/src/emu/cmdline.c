/*
This file is part of UFFS, the Ultra-low-cost Flash File System.

Copyright (C) 2005-2009 Ricky Zheng <ricky_gz_zheng@yahoo.co.nz>

UFFS is free software; you can redistribute it and/or modify it under
the GNU Library General Public License as published by the Free Software 
Foundation; either version 2 of the License, or (at your option) any
later version.

UFFS is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
or GNU Library General Public License, as applicable, for more details.

You should have received a copy of the GNU General Public License
and GNU Library General Public License along with UFFS; if not, write
to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
Boston, MA  02110-1301, USA.

As a special exception, if other files instantiate templates or use
macros or inline functions from this file, or you compile this file
and link it with other works to produce a work based on this file,
this file does not by itself cause the resulting work to be covered
by the GNU General Public License. However the source code for this
file must still be made available in accordance with section (3) of
the GNU General Public License v2.

This exception does not invalidate any other reasons why a work based
on this file might be covered by the GNU General Public License.
*/

/**
* \file cmdline.c
* \brief command line test interface
* \author Ricky Zheng, created in 22th Feb, 2007
*/

#include <string.h>
#include <stdio.h>
//#include <conio.h>
#include "uffs_config.h"
#include "cmdline.h"
#include "uffs/uffs_fs.h"

#define PROMPT "UFFS>"

#define PFX "cli : "
#define MSGLN(msg,...) uffs_Perror(UFFS_MSG_NORMAL, msg, ## __VA_ARGS__)
#define MSG(msg,...) uffs_PerrorRaw(UFFS_MSG_NORMAL, msg, ## __VA_ARGS__)

#define MAX_CLI_ARGS_BUF_LEN	120
#define MAX_CLI_ARGS_NUM		20
#define MAX_CLI_ENV_NUM			11		// '?', '0' - '9'


struct cli_arg {
	int argc;
	char *argv[MAX_CLI_ARGS_NUM];
	char _buf[MAX_CLI_ARGS_BUF_LEN];
};

static BOOL m_exit = FALSE;
static BOOL m_abort = FALSE;
static struct cli_commandset *m_cmdset_head = NULL;

// Note: last command return code stored in env 0.
static int m_cli_envs[MAX_CLI_ENV_NUM] = {0};	// cli environment variables

static const struct cli_command * cli_find(const char *cmd);
static int cmd_help(int argc, char *argv[]);


#define FOR_EACH_CLI_CMD(set, cmd) \
	for (set = m_cmdset_head; set && set->cmds; set = set->next) \
		for (cmd = set->cmds; cmd && cmd->handler; cmd++)


/*** filter out leading and tailing spaces, discard comments
 * return pointer to start of new command line
 */
static char * cli_process_line(char *p)
{
	char *s;
	char *x;

	if (!p)
		return NULL;

	// skip leading spaces
	while (p && (*p == ' ' || *p == '\t'))
		p++;

	for (s = x = p; *p; x++, p++) {
		switch(*p) {
		case '\\':
			p++;
			if (*p) {
				switch(*p) {
				case 'n':
					*x = '\n';
					break;
				case 'r':
					*x = '\r';
					break;
				case 't':
					*x = '\t';
					break;
				case 'b':
					*x = '\b';
					break;
				default:
					if (*p >= '0' && *p <= '9')
						*x = *p - '0';
					else
						*x = *p;
					break;
				}
			}
			break;
		default:
			if (*p == '\r' || *p == '\n' || *p == '#') *p = '\0';
			*x = *p;
			break;
		}

		if (*p == 0)
			break;
	}

	// trim tailing spaces
	p--;
	while (p > s && (*p == ' ' || *p == '\t'))
		*p-- = '\0';

	return s;
}

static int cli_env_to_idx(char env)
{
	int idx = -1;

	if (env >= '0' && env <= '9') {
		idx = env - '0' + 1;
	}
	else if (env == '?') {
		idx = 0;
	}

	return idx;
}

int cli_env_set(char env, int val)
{
	int idx = cli_env_to_idx(env);

	if (idx >= 0) {
		m_cli_envs[idx] = val;
		return 0;
	}
	else
		return -1;
}

int cli_env_get(char env)
{
	int idx = cli_env_to_idx(env);

	return idx >= 0 ? m_cli_envs[idx] : 0;
}

/** exec command <n> times:
 *		exec <n> <cmd> [...]
 */
static int cmd_exec(int argc, char *argv[])
{
	int n = 0;
	const struct cli_command *cmd;

	CHK_ARGC(3, 0);

	if (sscanf(argv[1], "%d", &n) != 1)
		return CLI_INVALID_ARG;
	if (n <= 0)
		return CLI_INVALID_ARG;

	cmd = cli_find(argv[2]);
	if (cmd == NULL) {
		MSG("Unknown command '%s'\n", argv[2]);
		return -1;
	}
	else {
		argv += 2;
		while (n-- >= 0) {
			if (cmd->handler(argc - 2, argv) != 0)
				return -1;
		}
	}

	return 0;
}

/** 
 * test expression
 *	test <a> <op> <b>
 * for example:
 *	test 1 > 0    ==> return 0
 *	test 1 <= 0   ==> return -1
 */
static int cmd_test(int argc, char *argv[])
{
	int a, b;
	char *op;
	BOOL tst = FALSE;

	CHK_ARGC(4, 4);

	if (sscanf(argv[1], "%d", &a) != 1 ||
		sscanf(argv[3], "%d", &b) != 1)
	{
		return CLI_INVALID_ARG;
	}

	op = argv[2];
	if (!strcmp(op, ">")) {
		tst = (a > b);
	}
	else if (!strcmp(op, "<")) {
		tst = (a < b);
	}
	else if (!strcmp(op, "==")) {
		tst = (a == b);
	}
	else if (!strcmp(op, ">=")) {
		tst = (a >= b);
	}
	else if (!strcmp(op, "<=")) {
		tst = (a <= b);
	}
	else if (!strcmp(op, "!=")) {
		tst = (a != b);
	}
	else {
		return CLI_INVALID_ARG;
	}
	
	return tst ? 0 : -1;
}

/** if last command failed (return != 0), run <cmd>
 *    ! <cmd>
 */
static int cmd_failed(int argc, char *argv[])
{
	const struct cli_command *cmd;

	CHK_ARGC(2, 0);

	cmd = cli_find(argv[1]);
	if (cmd == NULL) {
		MSG("Unknown command '%s'\n", argv[1]);
		return -1;
	}
	else {
		argv++;
		return (cli_env_get('?') == 0 ? 0 : cmd->handler(argc - 1, argv));
	}
}

/** print messages
 *		echo [<arg> ...]
 */
static int cmd_echo(int argc, char *argv[])
{
	int i;

	for (i = 1; i < argc; i++) {
		MSG("%s%s", i > 1 ? " " : "", argv[i]);
	}
	MSG("\n");

	return 0;
}

/** set cli environment variable
 *		set <env> <value>
 */
static int cmd_set(int argc, char *argv[])
{
	int val;
	int ret = -1;

	CHK_ARGC(3, 0);

	if (sscanf(argv[2], "%d", &val) == 1) {
		ret = cli_env_set(argv[1][0], val);
	}

	return ret;
}

/** evaluation the expresstion, result to $1
 *		evl <value> <op> <value>
 */
static int cmd_evl(int argc, char *argv[])
{
	int val1, val2, result = 0;
	int ret = -1;

	CHK_ARGC(4, 4);

	if (sscanf(argv[1], "%d", &val1) == 1 &&
		sscanf(argv[3], "%d", &val2) == 1) {
		ret = 0;
		switch(argv[2][0]) {
			case '+':
				result = val1 + val2;
				break;
			case '-':
				result = val1 - val2;
				break;
			case '*':
				result = val1 * val2;
				break;
			case '/':
				if (val2 == 0)
					ret = -1;
				else
					result = val1 / val2;
				break;
			case '%':
				if (val2 == 0)
					ret = -1;
				else
					result = val1 % val2;
				break;
			default:
				ret = CLI_INVALID_ARG;
				break;
		}
	}

	if (ret == 0)
		ret = cli_env_set('1', result);

	return ret;
}

static int cmd_exit(int argc, char *argv[])
{
	m_exit = TRUE;
	return 0;
}

/** Abort current script
 *		abort [...]
 */
static int cmd_abort(int argc, char *argv[])
{
	if (argc > 1) {
		cmd_echo(argc, argv);
	}

	m_abort = TRUE;

	return 0;
}

/** run local file system's script
 *		script <filename>
 */
static int cmd_script(int argc, char *argv[])
{
	char line_buf[256];
	char *p;
	FILE *fp;
	const char *name;
	int ret = 0;
	static int stack = 0;

	CHK_ARGC(2, 0);

	if (stack++ == 0)
		m_abort = FALSE;

	name = argv[1];
	fp = fopen(name, "r");

	if (fp) {
		memset(line_buf, 0, sizeof(line_buf));
		while (!m_abort && fgets(line_buf, sizeof(line_buf) - 1, fp)) {
			p = line_buf + sizeof(line_buf) - 1;
			while (*p == 0 && p > line_buf)
				p--;
			while ((*p == '\r' || *p == '\n') && p > line_buf) {
				*p-- = 0;
			}
			p = cli_process_line(line_buf);
			if (*p)
				ret = cli_interpret(p);
			memset(line_buf, 0, sizeof(line_buf));
		}
		fclose(fp);
	}
	else {
		MSG("Can't open host script file '%s' for read\n", name);
		ret = -1;
	}

	stack--;

	return ret;
}



static const struct cli_command default_cmds[] = 
{
	{ cmd_help,		"help|?",	"[<command>]",		"show commands or help on one command" },
	{ cmd_exit,		"exit",		NULL,				"exit command line" },
	{ cmd_exec,		"*",		"<n> <cmd> [...]>",	"run <cmd> <n> times" },
	{ cmd_failed,	"!",		"<cmd> [...]",		"run <cmd> if last command failed" },
	{ cmd_echo,		"echo",		"[...]",			"print messages" },
	{ cmd_set,		"set",		"<env> <val>",		"set env variable" },
	{ cmd_evl,		"evl",		"<val> <op> <val>",	"evaluation expresstion" },
	{ cmd_test,		"test",		"<a> <op> <b>",		"test expression: <a> <op> <b>" },
	{ cmd_script,   "script",   "<file>",           "run host script <file>" },
	{ cmd_abort,	"abort",	NULL,				"abort from the running script" },
	{ NULL, NULL, NULL, NULL }
};

static struct cli_commandset default_cmdset = {
	default_cmds,
};

static BOOL match_cmd(const char *src, int start, int end, const char *des)
{
	while (src[start] == ' ' && start < end) 
		start++;

	while (src[end] == ' ' && start < end) 
		end--;

	if ((int)strlen(des) == (end - start + 1)) {
		if (memcmp(src + start, des, end - start + 1) == 0) {
			return TRUE;
		}
	}

	return FALSE;
}

static BOOL check_cmd(const char *cmds, const char *cmd)
{
	int start, end;

	for (start = end = 0; cmds[end] != 0 && cmds[end] != '|'; end++);

	while (end > start) {
		if (match_cmd(cmds, start, end - 1, cmd) == TRUE) 
			return TRUE;
		if (cmds[end] == 0) 
			break;
		if (cmds[end] == '|') {
			end++;
			for (start = end; cmds[end] != 0 && cmds[end] != '|'; end++);
		}
	} 

	return FALSE;
}

static const struct cli_command * cli_find(const char *cmd)
{
	struct cli_commandset *work;
	const struct cli_command *s;

	FOR_EACH_CLI_CMD(work, s) {
		if (check_cmd(s->cmd, cmd) == TRUE)
			return s;
	}

	return NULL;
}

static void show_cmd_usage(const struct cli_command *cmd)
{
	MSG("%s: %s\n", cmd->cmd, cmd->descr);
	MSG("Usage: %s %s\n", cmd->cmd, cmd->args ? cmd->args : "");
}

static int cmd_help(int argc, char *argv[])
{
	const struct cli_command *cmd;
	struct cli_commandset *cmdset;
	int i, n;

	if (argc < 2)  {
		MSG("Available commands:\n");
		n = 0;
		FOR_EACH_CLI_CMD(cmdset, cmd) {
			MSG("%s", cmd->cmd);
			for (i = strlen(cmd->cmd); i%10; i++, MSG(" "));
			if ((++n % 5) == 0) MSG("\n");
		}
		MSG("\n");
	}
	else {
		cmd = cli_find(argv[1]);
		if (cmd == NULL) {
			MSG("No such command\n");
			return -1;
		}
		else {
			show_cmd_usage(cmd);
		}
	}

	return 0;
}

static void cli_parse_args(const char *cmd, struct cli_arg *arg)
{
	char *p;
	int val;

	if (arg) {
		arg->argc = 0;
		if (cmd) {
			p = arg->_buf;
			while (*cmd && arg->argc < MAX_CLI_ARGS_NUM && (p - arg->_buf < MAX_CLI_ARGS_BUF_LEN)) {
				while(*cmd && (*cmd == ' ' || *cmd == '\t'))
					cmd++;

				arg->argv[arg->argc] = p;
				while (*cmd && (*cmd != ' ' && *cmd != '\t') && (p - arg->_buf < MAX_CLI_ARGS_BUF_LEN)) {
					if (*cmd == '$') {
						// command env replacement
						cmd++;
						val = cli_env_get(*cmd++);
						if (p - arg->_buf < MAX_CLI_ARGS_BUF_LEN - 12) {  // 12 is long enough for 32bit 'int'
							p += sprintf(p, "%d", val & 0xFFFFFFFF);
						}
					}
					else
						*p++ = *cmd++;
				}
				*p++ = '\0';

				if (*(arg->argv[arg->argc]) == '\0')
					break;
				arg->argc++;
			}
		}
	}
}

int cli_interpret(const char *line)
{
	struct cli_arg arg = {0};
	const struct cli_command *cmd;
	int ret = -1;

	cli_parse_args(line, &arg);

	if (arg.argc > 0) {
		cmd = cli_find(arg.argv[0]);
		if (cmd == NULL) {
			MSG("Unknown command '%s'\n", arg.argv[0]);
		}
		else {
			ret = cmd->handler(arg.argc, arg.argv);
			if (ret == CLI_INVALID_ARG) {
				MSG("\n");
				show_cmd_usage(cmd);
			}
		}
	}

	cli_env_set('?', ret);	// $? = last command return code

	return ret;
}

void cli_add_commandset(struct cli_commandset *set)
{
	if (set) {
		set->next = m_cmdset_head;
		m_cmdset_head = set;
	}
}

void cli_main_entry()
{
	char line[80];
	int linelen = 0;
	char *p;

	MSG("$ ");
	cli_add_commandset(&default_cmdset);

	while (!m_exit) {
		char ch;
		if (linelen >= sizeof(line))
			continue;
		ch = getc(stdin);
		switch (ch) {
		case 8:
		case 127:
			if (linelen > 0) {
				--linelen;
				MSG("\x08 \x08");
			}
			break;

		case '\r':
		case '\n':
			//MSG("\r\n");
			if (linelen > 0) {
				line[linelen] = 0;
				p = cli_process_line(line);
				if (*p)
					cli_interpret(p);
				linelen = 0;
			}
			MSG("$ ");
			break;

		case 21:
			while (linelen > 0) {
				--linelen;
				MSG("\x08 \x08");
			}
			break;

		default:
			if (ch >= ' ' && ch < 127 && linelen < sizeof(line) - 1) {
				line[linelen++] = ch;
				//MSG("%c", ch);
			}
		}
	}
}
