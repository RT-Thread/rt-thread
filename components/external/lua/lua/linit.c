/*
** $Id: linit.c,v 1.14.1.1 2007/12/27 13:02:25 roberto Exp $
** Initialization of libraries for lua.c
** See Copyright Notice in lua.h
*/


#define linit_c
#define LUA_LIB

#include "lua.h"

#include "lualib.h"
#include "lauxlib.h"
#include "lrotable.h"
#include "luaconf.h"

#if defined(RT_LUA_USE_EXLIBS)
#include "lexlibs.h"
#endif

#if defined(LUA_EXLIBS_ROM)
#undef _ROM
#define _ROM( name, openf, table ) extern int openf(lua_State *);
LUA_EXLIBS_ROM
#endif

static const luaL_Reg lualibs[] = {
  {"", luaopen_base},
  {LUA_LOADLIBNAME, luaopen_package},
  {LUA_IOLIBNAME, luaopen_io},
  {LUA_STRLIBNAME, luaopen_string},    
#if LUA_OPTIMIZE_MEMORY == 0
  {LUA_MATHLIBNAME, luaopen_math},
  {LUA_TABLIBNAME, luaopen_table},  
  {LUA_DBLIBNAME, luaopen_debug},  
#endif
#if defined(LUA_EXLIBS_ROM)
#undef _ROM
#define _ROM( name, openf, table ) { name, openf },
  LUA_EXLIBS_ROM
#endif
  {NULL, NULL}
};

extern const luaR_entry strlib[];
extern const luaR_entry syslib[];
extern const luaR_entry tab_funcs[];
extern const luaR_entry dblib[];
extern const luaR_entry co_funcs[];
#if defined(LUA_EXLIBS_ROM) && LUA_OPTIMIZE_MEMORY == 2
#undef _ROM
#define _ROM( name, openf, table ) extern const luaR_entry table[];
LUA_EXLIBS_ROM
#endif
const luaR_table lua_rotable[] = 
{
#if LUA_OPTIMIZE_MEMORY > 0
  {LUA_STRLIBNAME, strlib},
  {LUA_TABLIBNAME, tab_funcs},
  {LUA_DBLIBNAME, dblib},
  {LUA_COLIBNAME, co_funcs},
#if defined(LUA_EXLIBS_ROM) && LUA_OPTIMIZE_MEMORY == 2
#undef _ROM
#define _ROM( name, openf, table ) { name, table },
  LUA_EXLIBS_ROM
#endif
#endif
  {NULL, NULL}
};

LUALIB_API void luaL_openlibs (lua_State *L) {
  const luaL_Reg *lib = lualibs;
  for (; lib->func; lib++) {
    lua_pushcfunction(L, lib->func);
    lua_pushstring(L, lib->name);
    lua_call(L, 1, 0);
  }
}

