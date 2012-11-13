/**
 * example of adding lua external library
 */

#include "lua.h"
#include "lauxlib.h"

#include "lexlibs.h"

#define VERSION         1

int example_hello(lua_State *L)
{
    rt_kprintf("Hello, Lua on RT-Thead!\n");

    return 0;
}

int example_print(lua_State *L)
{
    int n = lua_gettop(L);
    int i;

    for (i=1; i<=n; i++)
    {
        if (i>1)
            rt_kprintf("\t");

        if (lua_isstring(L,i))
            rt_kprintf("%s",lua_tostring(L,i));
        else if (lua_isnumber(L, i))
            rt_kprintf("%d",lua_tointeger(L,i));
        else if (lua_isnil(L,i))
            rt_kprintf("%s","nil");
        else if (lua_isboolean(L,i))
            rt_kprintf("%s",lua_toboolean(L,i) ? "true" : "false");
        else
            rt_kprintf("%s:%p",luaL_typename(L,i),lua_topointer(L,i));
    }

    rt_kprintf("\n");

    return 0;
}

    
#define MIN_OPT_LEVEL       2
#include "lrodefs.h"

const LUA_REG_TYPE example_map[] =
{
    {LSTRKEY("hello"), LFUNCVAL(example_hello)},
    {LSTRKEY("print"), LFUNCVAL(example_print)},
#if LUA_OPTIMIZE_MEMORY > 0
    {LSTRKEY("version"), LNUMVAL(VERSION)},
#endif
    {LNILKEY, LNILVAL}
};

/**
 * Open exmaple library
 */
LUALIB_API int luaopen_example(lua_State *L)
{
#if LUA_OPTIMIZE_MEMORY > 0
    return 0;
#else
    luaL_register(L, EXLIB_EXAMPLE, example_map);
    lua_pushnumber(L, VERSION);
    lua_setfield(L, -2, "version");
    return 1;
#endif
}


