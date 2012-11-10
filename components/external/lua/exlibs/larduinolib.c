/**
 * Arduino library for lua
 */


#include "lua.h"
#include "lauxlib.h"
#include "lexlibs.h"

#include "libarduino.h"

int arduino_pinMode(lua_State *L)
{
    pinMode(luaL_checkint(L, 1), luaL_checkint(L, 2));
    return 0;
}

int arduino_digitalWrite(lua_State *L)
{
    digitalWrite(luaL_checkint(L, 1), luaL_checkint(L, 2));
    return 0;
}

int arduino_digitalRead(lua_State *L)
{
    lua_pushinteger(L, digitalRead(luaL_checkint(L, 1)));
    return 1;
}

int arduino_analogWrite(lua_State *L)
{
    analogWrite(luaL_checkint(L, 1), luaL_checkint(L, 2));
    return 0;
}

/* the minimum optimization level at which we use rotables */
#define MIN_OPT_LEVEL   2
#include "lrodefs.h"

#if 0
/* standard table */
static const luaL_Reg arduino_map[] =
{
    {"pinMode", arduino_pinMode},
    {"digitalRead", arduino_digitalRead},
    {"digitalWrite", arduino_digitalWrite},
    {"analogWrite", arduino_analogWrite},
    {NULL, NULL}
}
#else
const LUA_REG_TYPE arduino_map[] =
{
    {LSTRKEY("pinMode"), LFUNCVAL(arduino_pinMode)},
    {LSTRKEY("digitalRead"), LFUNCVAL(arduino_digitalRead)},
    {LSTRKEY("digitalWrite"), LFUNCVAL(arduino_digitalWrite)},
    {LSTRKEY("analogWrite"), LFUNCVAL(arduino_analogWrite)},
#if LUA_OPTIMIZE_MEMORY > 0
    {LSTRKEY("HIGH"), LFUNCVAL(HIGH)},
    {LSTRKEY("LOW"), LFUNCVAL(LOW)},
    {LSTRKEY("INPUT"), LFUNCVAL(INPUT)},
    {LSTRKEY("OUTPUT"), LFUNCVAL(OUTPUT)},
    {LSTRKEY("INPUT_PULLUP"), LFUNCVAL(INPUT_PULLUP)},
#endif /* LUA_OPTIMIZE_MEMORY > 0 */
    {LNILKEY, LNILVAL}
};
#endif /* 0 */


/**
 * Open arduino library
 */
LUALIB_API int luaopen_arduino(lua_State *L)
{
#if LUA_OPTIMIZE_MEMORY > 0
    return 0;
#else
    luaL_register(L, EXLIB_ARDUINO, arduino_map);
    lua_pushnumber(L, HIGH);
    lua_setfield(L, -2, "HIGH");
    lua_pushnumber(L, LOW);
    lua_setfield(L, -2, "LOW");
    lua_pushnumber(L, INPUT);
    lua_setfield(L, -2, "INPUT");
    lua_pushnumber(L, OUTPUT);
    lua_setfield(L, -2, "OUTPUT");
    lua_pushnumber(L, INPUT_PULLUP);
    lua_setfield(L, -2, "INPUT_PULLUP");
    return 1;
#endif
}

    
