
#include "lua.h"
#include "lauxlib.h"

#include "finsh.h"

int c_print(lua_State *L)
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

/**
 * lua call c function
 */
int luacprint()
{
    lua_State *L = luaL_newstate();
    lua_register(L, "c_print", c_print);
    
    rt_kprintf("lua test - c_print: c_print('lua for rt-thread')\n");
    luaL_dostring(L, "c_print('lua for rt-thread')");
    rt_kprintf("done\n");
    
    lua_close(L);

    return 0;
}
FINSH_FUNCTION_EXPORT(luacprint, register c function in lua and call it)



