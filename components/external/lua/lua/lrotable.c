/* Read-only tables for Lua */

#include <string.h>
#include "lrotable.h"
#include "lua.h"
#include "lauxlib.h"
#include "lstring.h"
#include "lobject.h"
#include "lapi.h"

/* Local defines */
#define LUAR_FINDFUNCTION     0
#define LUAR_FINDVALUE        1

/* Externally defined read-only table array */
extern const luaR_table lua_rotable[];

/* Find a global "read only table" in the constant lua_rotable array */
void* luaR_findglobal(const char *name, unsigned len) {
  unsigned i;    
  
  if (strlen(name) > LUA_MAX_ROTABLE_NAME)
    return NULL;
  for (i=0; lua_rotable[i].name; i ++)
    if (*lua_rotable[i].name != '\0' && strlen(lua_rotable[i].name) == len && !strncmp(lua_rotable[i].name, name, len)) {
      return (void*)(lua_rotable[i].pentries);
    }
  return NULL;
}

/* Find an entry in a rotable and return it */
static const TValue* luaR_auxfind(const luaR_entry *pentry, const char *strkey, luaR_numkey numkey, unsigned *ppos) {
  const TValue *res = NULL;
  unsigned i = 0;
  
  if (pentry == NULL)
    return NULL;  
  while(pentry->key.type != LUA_TNIL) {
    if ((strkey && (pentry->key.type == LUA_TSTRING) && (!strcmp(pentry->key.id.strkey, strkey))) || 
        (!strkey && (pentry->key.type == LUA_TNUMBER) && ((luaR_numkey)pentry->key.id.numkey == numkey))) {
      res = &pentry->value;
      break;
    }
    i ++; pentry ++;
  }
  if (res && ppos)
    *ppos = i;   
  return res;
}

int luaR_findfunction(lua_State *L, const luaR_entry *ptable) {
  const TValue *res = NULL;
  const char *key = luaL_checkstring(L, 2);
    
  res = luaR_auxfind(ptable, key, 0, NULL);  
  if (res && ttislightfunction(res)) {
    luaA_pushobject(L, res);
    return 1;
  }
  else
    return 0;
}

/* Find an entry in a rotable and return its type 
   If "strkey" is not NULL, the function will look for a string key,
   otherwise it will look for a number key */
const TValue* luaR_findentry(void *data, const char *strkey, luaR_numkey numkey, unsigned *ppos) {
  return luaR_auxfind((const luaR_entry*)data, strkey, numkey, ppos);
}

/* Find the metatable of a given table */
void* luaR_getmeta(void *data) {
#ifdef LUA_META_ROTABLES
  const TValue *res = luaR_auxfind((const luaR_entry*)data, "__metatable", 0, NULL);
  return res && ttisrotable(res) ? rvalue(res) : NULL;
#else
  return NULL;
#endif
}

static void luaR_next_helper(lua_State *L, const luaR_entry *pentries, int pos, TValue *key, TValue *val) {
  setnilvalue(key);
  setnilvalue(val);
  if (pentries[pos].key.type != LUA_TNIL) {
    /* Found an entry */
    if (pentries[pos].key.type == LUA_TSTRING)
      setsvalue(L, key, luaS_newro(L, pentries[pos].key.id.strkey))
    else
      setnvalue(key, (lua_Number)pentries[pos].key.id.numkey)
   setobj2s(L, val, &pentries[pos].value);
  }
}
/* next (used for iteration) */
void luaR_next(lua_State *L, void *data, TValue *key, TValue *val) {
  const luaR_entry* pentries = (const luaR_entry*)data;
  char strkey[LUA_MAX_ROTABLE_NAME + 1], *pstrkey = NULL;
  luaR_numkey numkey = 0;
  unsigned keypos;
  
  /* Special case: if key is nil, return the first element of the rotable */
  if (ttisnil(key)) 
    luaR_next_helper(L, pentries, 0, key, val);
  else if (ttisstring(key) || ttisnumber(key)) {
    /* Find the previoud key again */  
    if (ttisstring(key)) {
      luaR_getcstr(strkey, rawtsvalue(key), LUA_MAX_ROTABLE_NAME);          
      pstrkey = strkey;
    } else   
      numkey = (luaR_numkey)nvalue(key);
    luaR_findentry(data, pstrkey, numkey, &keypos);
    /* Advance to next key */
    keypos ++;    
    luaR_next_helper(L, pentries, keypos, key, val);
  }
}

/* Convert a Lua string to a C string */
void luaR_getcstr(char *dest, const TString *src, size_t maxsize) {
  if (src->tsv.len+1 > maxsize)
    dest[0] = '\0';
  else {
    memcpy(dest, getstr(src), src->tsv.len);
    dest[src->tsv.len] = '\0';
  } 
}

/* Return 1 if the given pointer is a rotable */
#ifdef LUA_META_ROTABLES

#include "compiler.h"

int luaR_isrotable(void *p) {
  return RODATA_START_ADDRESS <= (char*)p && (char*)p <= RODATA_END_ADDRESS;
}
#endif
