/* Read-only tables for Lua */

#ifndef lrotable_h
#define lrotable_h

#include "lua.h"
#include "llimits.h"
#include "lobject.h"
#include "luaconf.h"

/* Macros one can use to define rotable entries */
#ifndef LUA_PACK_VALUE
#define LRO_FUNCVAL(v)  {{.p = v}, LUA_TLIGHTFUNCTION}
#define LRO_NUMVAL(v)   {{.n = v}, LUA_TNUMBER}
#define LRO_ROVAL(v)    {{.p = (void*)v}, LUA_TROTABLE}
#define LRO_NILVAL      {{.p = NULL}, LUA_TNIL}
#else // #ifndef LUA_PACK_VALUE
#define LRO_NUMVAL(v)   {.value.n = v}
#ifdef ELUA_ENDIAN_LITTLE
#define LRO_FUNCVAL(v)  {{(int)v, add_sig(LUA_TLIGHTFUNCTION)}}
#define LRO_ROVAL(v)    {{(int)v, add_sig(LUA_TROTABLE)}}
#define LRO_NILVAL      {{0, add_sig(LUA_TNIL)}}
#else // #ifdef ELUA_ENDIAN_LITTLE
#define LRO_FUNCVAL(v)  {{add_sig(LUA_TLIGHTFUNCTION), (int)v}}
#define LRO_ROVAL(v)    {{add_sig(LUA_TROTABLE), (int)v}}
#define LRO_NILVAL      {{add_sig(LUA_TNIL), 0}}
#endif // #ifdef ELUA_ENDIAN_LITTLE
#endif // #ifndef LUA_PACK_VALUE

#define LRO_STRKEY(k)   {LUA_TSTRING, {.strkey = k}}
#define LRO_NUMKEY(k)   {LUA_TNUMBER, {.numkey = k}}
#define LRO_NILKEY      {LUA_TNIL, {.strkey=NULL}}

/* Maximum length of a rotable name and of a string key*/
#define LUA_MAX_ROTABLE_NAME      32

/* Type of a numeric key in a rotable */
typedef int luaR_numkey;

/* The next structure defines the type of a key */
typedef struct
{
  int type;
  union
  {
    const char*   strkey;
    luaR_numkey   numkey;
  } id;
} luaR_key;

/* An entry in the read only table */
typedef struct
{
  const luaR_key key;
  const TValue value;
} luaR_entry;

/* A rotable */
typedef struct
{
  const char *name;
  const luaR_entry *pentries;
} luaR_table;

void* luaR_findglobal(const char *key, unsigned len);
int luaR_findfunction(lua_State *L, const luaR_entry *ptable);
const TValue* luaR_findentry(void *data, const char *strkey, luaR_numkey numkey, unsigned *ppos);
void luaR_getcstr(char *dest, const TString *src, size_t maxsize);
void luaR_next(lua_State *L, void *data, TValue *key, TValue *val);
void* luaR_getmeta(void *data);
#ifdef LUA_META_ROTABLES
int luaR_isrotable(void *p);
#else
#define luaR_isrotable(p)     (0)
#endif

#endif
