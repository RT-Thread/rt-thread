/*
 *  token lex for finsh shell.
 *
 * COPYRIGHT (C) 2006 - 2013, RT-Thread Development Team
 *
 *  This file is part of RT-Thread (http://www.rt-thread.org)
 *  Maintainer: bernard.xiong <bernard.xiong at gmail.com>
 *
 *  All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-22     Bernard      first version
 */
#ifndef __FINSH_TOKEN_H__
#define __FINSH_TOKEN_H__

#include <finsh.h>

enum finsh_token_type
{
	finsh_token_type_left_paren = 1,	/* (		*/
	finsh_token_type_right_paren ,		/* )		*/
	finsh_token_type_comma ,			/* ,		*/
	finsh_token_type_semicolon ,		/* ;		*/
	finsh_token_type_mul ,				/* *		*/
	finsh_token_type_add ,				/* +		*/
	finsh_token_type_inc ,				/* ++		*/
	finsh_token_type_sub ,				/* -		*/
	finsh_token_type_dec ,				/* --		*/
	finsh_token_type_div ,				/* /		*/
	finsh_token_type_mod ,				/* %		*/
	finsh_token_type_assign ,			/* =		*/
	finsh_token_type_and,				/* &		*/
	finsh_token_type_or,				/* |		*/
	finsh_token_type_xor,				/* ^		*/
	finsh_token_type_bitwise,			/* ~		*/
	finsh_token_type_shl,				/* <<		*/
	finsh_token_type_shr,				/* >>		*/
	finsh_token_type_comments, 			/* //       */
	/*-- data type --*/
	finsh_token_type_void,				/* void		*/
	finsh_token_type_char, 				/* char		*/
	finsh_token_type_short,				/* short	*/
	finsh_token_type_int,				/* int		*/
	finsh_token_type_long,				/* long		*/
	finsh_token_type_unsigned,			/* unsigned	*/
    /* data value type */
    finsh_token_type_value_char,        /* v:char   */
    finsh_token_type_value_int,         /* v:int    */
    finsh_token_type_value_long,        /* v:long   */
    finsh_token_type_value_string,      /* v:string */
	finsh_token_type_value_null,		/* NULL 	*/
	/*-- others --*/
	finsh_token_type_identifier,		/* ID		*/
	finsh_token_type_bad,				/* bad token */
	finsh_token_type_eof
};

#define finsh_token_position(self) (self)->position
#define finsh_token_replay(self) (self)->replay = 1

void finsh_token_init(struct finsh_token* self, u_char* script);

enum finsh_token_type finsh_token_token(struct finsh_token* self);
void finsh_token_get_token(struct finsh_token* self, u_char* token);

#endif
