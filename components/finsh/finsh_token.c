/*
 * File      : finsh_token.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-22     Bernard      first version
 */
#include <finsh.h>

#include "finsh_token.h"
#include "finsh_error.h"

#define is_digit(ch)	((ch) >= '0' && (ch) <= '9')
#define is_separator(ch) !(((ch) >= 'a' && (ch) <= 'z') \
     || ((ch) >= 'A' && (ch) <= 'Z') || ((ch) >= '0' && (ch) <= '9') || ((ch) == '_'))
#define is_eof(self) (self)->eof

struct name_table
{
	char* name;
	enum finsh_token_type type;
};

/* keyword */
static const struct name_table finsh_name_table[] =
{
	{"void",		finsh_token_type_void},
	{"char",		finsh_token_type_char},
	{"short",		finsh_token_type_short},
	{"int",			finsh_token_type_int},
	{"long",		finsh_token_type_long},
	{"unsigned",	finsh_token_type_unsigned},

	{"NULL",        finsh_token_type_value_null},
	{"null",        finsh_token_type_value_null}
};

static char token_next_char(struct finsh_token* self);
static void token_prev_char(struct finsh_token* self);
static long token_spec_number(char* string, int length, int b);
static void token_run(struct finsh_token* self);
static int  token_match_name(struct finsh_token* self, const char* str);
static void token_proc_number(struct finsh_token* self);
static u_char* token_proc_string(struct finsh_token* self);
static void token_trim_space(struct finsh_token* self);
static char token_proc_char(struct finsh_token* self);
static int token_proc_escape(struct finsh_token* self);

void finsh_token_init(struct finsh_token* self, u_char* line)
{
	memset(self, 0, sizeof(struct finsh_token));

	self->line = line;
}

enum finsh_token_type finsh_token_token(struct finsh_token* self)
{
	if ( self->replay )	self->replay = 0;
	else token_run(self);

	return (enum finsh_token_type)self->current_token;
}

void finsh_token_get_token(struct finsh_token* self, u_char* token)
{
	strncpy((char*)token, (char*)self->string, FINSH_NAME_MAX);
}

int token_get_string(struct finsh_token* self, u_char* str)
{
	unsigned char *p=str;
	char ch;

	ch = token_next_char(self);
	if (is_eof(self)) return -1;

	str[0] = '\0';

	if ( is_digit(ch) )/*the first character of identifier is not a digit.*/
	{
		token_prev_char(self);
		return -1;
	}

	while (!is_separator(ch) && !is_eof(self))
	{
		*p++ = ch;

		ch = token_next_char(self);
	}
	self->eof = 0;

	token_prev_char(self);
	*p = '\0';

	return 0;
}

/*
get next character.
*/
static char token_next_char(struct finsh_token* self)
{
	if (self->eof) return '\0';

	if (self->position == (int)strlen((char*)self->line) || self->line[self->position] =='\n')
	{
			self->eof = 1;
			self->position = 0;
			return '\0';
	}

	return self->line[self->position++];
}

static void token_prev_char(struct finsh_token* self)
{
	if ( self->eof ) return;

	if ( self->position == 0 ) return;
    else self->position--;
}

static void token_run(struct finsh_token* self)
{
	char ch;

	token_trim_space(self); /* first trim space and tab. */
	token_get_string(self, &(self->string[0]));

	if ( is_eof(self) ) /*if it is eof, break;*/
	{
		self->current_token = finsh_token_type_eof;
		return ;
	}

	if (self->string[0] != '\0') /*It is a key word or a identifier.*/
	{
		if ( !token_match_name(self, (char*)self->string) )
		{
			self->current_token = finsh_token_type_identifier;
		}
		return;
	}
	else/*It is a operator character.*/
	{
		ch = token_next_char(self);

		switch ( ch )
		{
		case '(':
			self->current_token = finsh_token_type_left_paren;
			break;

		case ')':
			self->current_token = finsh_token_type_right_paren;
			break;

		case ',':
			self->current_token = finsh_token_type_comma;
			break;

		case ';':
			self->current_token = finsh_token_type_semicolon;
			break;

		case '&':
			self->current_token = finsh_token_type_and;
			break;

		case '*':
			self->current_token = finsh_token_type_mul;
			break;

		case '+':
			ch = token_next_char(self);

			if ( ch == '+' )
			{
				self->current_token = finsh_token_type_inc;
			}
			else
			{
				token_prev_char(self);
				self->current_token = finsh_token_type_add;
			}
			break;

		case '-':
			ch = token_next_char(self);

			if ( ch == '-' )
			{
				self->current_token = finsh_token_type_dec;
			}
			else
			{
				token_prev_char(self);
				self->current_token = finsh_token_type_sub;
			}
			break;

		case '/':
			self->current_token = finsh_token_type_div;
			break;

		case '<':
			ch = token_next_char(self);

			if ( ch == '<' )
			{
				self->current_token = finsh_token_type_shl;
			}
			else
			{
				token_prev_char(self);
				self->current_token = finsh_token_type_bad;
			}
			break;

		case '>':
			ch = token_next_char(self);

			if ( ch == '>' )
			{
				self->current_token = finsh_token_type_shr;
			}
			else
			{
				token_prev_char(self);
				self->current_token = finsh_token_type_bad;
			}
			break;

		case '|':
			self->current_token = finsh_token_type_or;
			break;

		case '%':
			self->current_token = finsh_token_type_mod;
			break;

		case '~':
			self->current_token = finsh_token_type_bitwise;
			break;

		case '^':
			self->current_token = finsh_token_type_xor;
			break;

		case '=':
			self->current_token = finsh_token_type_assign;
			break;

		case '\'':
			self->value.char_value = token_proc_char(self);
			self->current_token = finsh_token_type_value_char;
			break;

		case '"':
			token_proc_string(self);
			self->current_token = finsh_token_type_value_string;
			break;

		default:
			if ( is_digit(ch) )
			{
				token_prev_char(self);
				token_proc_number(self);
				break;
			}

			finsh_error_set(FINSH_ERROR_UNKNOWN_TOKEN);
			self->current_token = finsh_token_type_bad;

			break;
		}
	}
}

static int token_match_name(struct finsh_token* self, const char* str)
{
	int i;

	for (i = 0; i < sizeof(finsh_name_table)/sizeof(struct name_table); i++)
	{
		if ( strcmp(finsh_name_table[i].name, str)==0 )
		{
			self->current_token = finsh_name_table[i].type;
			return 1;
		}
	}

	return 0;
}

static void token_trim_space(struct finsh_token* self)
{
	char ch;
	while ( (ch = token_next_char(self)) ==' ' || ch == '\t');

	token_prev_char(self);
}

static char token_proc_char(struct finsh_token* self)
{
	char ch;
	char buf[4], *p;

	p = buf;
	ch = token_next_char(self);

	if ( ch == '\\' )
	{
		ch = token_next_char(self);
		switch ( ch )
		{
		case 'n': ch = '\n'; break;
		case 't': ch = '\t'; break;
		case 'v': ch = '\v'; break;
		case 'b': ch = '\b'; break;
		case 'r': ch = '\r'; break;
		case '\\': ch = '\\';  break;
		case '\'': ch = '\'';  break;
		default :
			while ( is_digit(ch) )/*for '\113' char*/
			{
				ch = token_next_char(self);
				*p++ = ch;
			}

			token_prev_char(self);
			*p = '\0';
			ch = atoi(p);
			break;
		}
	}

	if ( token_next_char(self) != '\'' )
	{
		token_prev_char(self);
		finsh_error_set(FINSH_ERROR_EXPECT_CHAR);
		return ch;
	}

	return ch;
}

static u_char* token_proc_string(struct finsh_token* self)
{
	u_char* p;

	for ( p = &self->string[0]; p - &(self->string[0]) < FINSH_STRING_MAX; )
	{
		char ch = token_next_char(self);

		if ( is_eof(self) )
		{
			finsh_error_set(FINSH_ERROR_UNEXPECT_END);
			return NULL;;
		}
		if ( ch == '\\' )
		{
			ch = token_proc_escape(self);
		}
		else if ( ch == '"' )/*end of string.*/
		{
			*p = '\0';
			return self->string;
		}

		*p++ = ch;
	}

	return NULL;
}

static int token_proc_escape(struct finsh_token* self)
{
	char ch;
	int result=0;

	ch = token_next_char(self);
	switch (ch)
	{
	case 'n':
		result = '\n';
		break;
	case 't':
		result = '\t';
		break;
	case 'v':
		result = '\v';
		break;
	case 'b':
		result = '\b';
		break;
	case 'r':
		result = '\r';
		break;
	case 'f':
		result = '\f';
		break;
	case 'a':
		result = '\007';
		break;
	case 'x':
		result = 0;
		ch  = token_next_char(self);
		while ( (ch - '0')<16u )
		{
			result = result*16 + ch - '0';
			ch = token_next_char(self);
		}
		token_prev_char(self);
		break;
	default:
		if ( (ch - '0') < 8u)
		{
			result = 0;
			while ( (ch - '0') < 8u )
			{
				result = result*8 + ch - '0';
				ch = token_next_char(self);
			}

			token_prev_char(self);
		}
		break;
	}

	return result;
}

/*
(0|0x|0X|0b|0B)number+(l|L)
*/
static void token_proc_number(struct finsh_token* self)
{
	char ch;
	int b;
	char *p, buf[128];
	long value;

	value = 0;
	p = buf;
	b = 10;

	ch  = token_next_char(self);
	if ( ch == '0' )
	{
		ch = token_next_char(self);
		if ( ch == 'x' || ch == 'X' )/*it's a hex number*/
		{
			b = 16;
			ch = token_next_char(self);
			while ( is_digit(ch) || isalpha(ch) )
			{
				*p++ = ch;
				ch = token_next_char(self);
			}

			*p = '\0';
		}
		else if ( ch == 'b' || ch == 'B' )
		{
			b = 2;
			ch = token_next_char(self);
			while ( (ch=='0')||(ch=='1') )
			{
				*p++ = ch;
				ch = token_next_char(self);
			}

			*p = '\0';
		}
		else
		{
			b = 8;
			while ( is_digit(ch) )
			{
				*p++ = ch;
				ch = token_next_char(self);
			}

			*p = '\0';
		}

		self->value.int_value = token_spec_number(buf, strlen(buf), b);
		self->current_token = finsh_token_type_value_int;
	}
	else
	{
		while ( is_digit(ch) )
		{
			value = value*10 + ( ch - '0' );
			ch = token_next_char(self);
		}

		self->value.int_value = value;
		self->current_token = finsh_token_type_value_int;
	}

	switch ( ch )
	{
	case 'l':
	case 'L':
		self->current_token = finsh_token_type_value_long;
		break;

	default:
		token_prev_char(self);
		break;
	}
}

/*use 64 bit number*/
#define BN_SIZE 2

static long token_spec_number(char* string, int length, int b)
{
	char* p;
	int t;
	int i, j, shift=1;
	unsigned int bn[BN_SIZE], v;
	long d;

	p = string;
	i = 0;

	switch ( b )
	{
	case 16: shift = 4;
		break;
	case 8:  shift = 3;
		break;
	case 2:  shift = 1;
		break;
	default: break;
	}

	for ( j=0; j<BN_SIZE ; j++) bn[j] = 0;

	while ( i<length )
	{
		t = *p++;
		if ( t>='a' && t <='f' )
		{
			t = t - 'a' +10;
		}
		else if ( t >='A' && t <='F' )
		{
			t = t - 'A' +10;
		}
		else t = t - '0';

		for ( j=0; j<BN_SIZE ; j++)
		{
			v = bn[j];
			bn[j] = (v<<shift) | t;
			t = v >> (32 - shift);
		}
		i++;
	}

	d = (long)bn[0];

	return d;
}
