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


#ifndef _UFFS_CLI_H_
#define _UFFS_CLI_H_

#ifndef BOOL
#define BOOL int
#endif

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define CLI_INVALID_ARG			-100

typedef int command_t(int argc, char *argv[]);

struct cli_command {
    command_t *handler;
    const char *cmd;
    const char *args;
    const char *descr;
};

struct cli_commandset {
	const struct cli_command *cmds;
	struct cli_commandset *next;
};

void cli_add_commandset(struct cli_commandset *set);
int cli_interpret(const char *line);
int cli_env_get(char env);
int cli_env_set(char env, int val);
void cli_main_entry();

#define u_assert(x) \
	((x) ? TRUE : \
			(uffs_PerrorRaw(UFFS_MSG_NORMAL, \
				"Assert failed at %s:%s:%d: '%s' is not true.\n", \
				__FILE__, __FUNCTION__, __LINE__, #x), FALSE))


#define CHK_ARGC(min, max) \
	if (argc < min || (max > 0 && argc > max)) \
		return CLI_INVALID_ARG

#endif


