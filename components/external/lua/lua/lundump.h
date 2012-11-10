/*
** $Id: lundump.h,v 1.37.1.1 2007/12/27 13:02:25 roberto Exp $
** load precompiled Lua chunks
** See Copyright Notice in lua.h
*/

#ifndef lundump_h
#define lundump_h

#include <stdint.h>

#include "lobject.h"
#include "lzio.h"

typedef uint32_t strsize_t;

/* info about target machine for cross-compilation */
typedef struct {
 int little_endian;
 int sizeof_int;
 int sizeof_strsize_t;
 int sizeof_lua_Number;
 int lua_Number_integral;
 int is_arm_fpa;
} DumpTargetInfo;

/* load one chunk; from lundump.c */
LUAI_FUNC Proto* luaU_undump (lua_State* L, ZIO* Z, Mbuffer* buff, const char* name);

/* make header; from lundump.c */
LUAI_FUNC void luaU_header (char* h);

/* dump one chunk to a different target; from ldump.c */
int luaU_dump_crosscompile (lua_State* L, const Proto* f, lua_Writer w, void* data, int strip, DumpTargetInfo target);

/* dump one chunk; from ldump.c */
LUAI_FUNC int luaU_dump (lua_State* L, const Proto* f, lua_Writer w, void* data, int strip);

#ifdef luac_c
/* print one chunk; from print.c */
LUAI_FUNC void luaU_print (const Proto* f, int full);
#endif

/* for header of binary files -- this is Lua 5.1 */
#define LUAC_VERSION		0x51

/* for header of binary files -- this is the official format */
#define LUAC_FORMAT		0

/* size of header of binary files */
#define LUAC_HEADERSIZE		12

/* error codes from cross-compiler */
/* target integer is too small to hold a value */
#define LUA_ERR_CC_INTOVERFLOW 101

/* target lua_Number is integral but a constant is non-integer */
#define LUA_ERR_CC_NOTINTEGER 102

#endif
