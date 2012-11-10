/*
** $Id: lmathlib.c,v 1.67.1.1 2007/12/27 13:02:25 roberto Exp $
** Standard mathematical library
** See Copyright Notice in lua.h
*/


#include <stdlib.h>
#include <math.h>

#define lmathlib_c
#define LUA_LIB

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"
#include "lrotable.h"

#undef PI
#define PI (3.14159265358979323846)
#define RADIANS_PER_DEGREE (PI/180.0)



static int math_abs (lua_State *L) {
#ifdef LUA_NUMBER_INTEGRAL
  lua_Number x = luaL_checknumber(L, 1);
  if (x < 0) x = -x;	//fails for -2^31
  lua_pushnumber(L, x);
#else
  lua_pushnumber(L, fabs(luaL_checknumber(L, 1)));
#endif
  return 1;
}

#ifndef LUA_NUMBER_INTEGRAL

static int math_sin (lua_State *L) {
  lua_pushnumber(L, sin(luaL_checknumber(L, 1)));
  return 1;
}

static int math_sinh (lua_State *L) {
  lua_pushnumber(L, sinh(luaL_checknumber(L, 1)));
  return 1;
}

static int math_cos (lua_State *L) {
  lua_pushnumber(L, cos(luaL_checknumber(L, 1)));
  return 1;
}

static int math_cosh (lua_State *L) {
  lua_pushnumber(L, cosh(luaL_checknumber(L, 1)));
  return 1;
}

static int math_tan (lua_State *L) {
  lua_pushnumber(L, tan(luaL_checknumber(L, 1)));
  return 1;
}

static int math_tanh (lua_State *L) {
  lua_pushnumber(L, tanh(luaL_checknumber(L, 1)));
  return 1;
}

static int math_asin (lua_State *L) {
  lua_pushnumber(L, asin(luaL_checknumber(L, 1)));
  return 1;
}

static int math_acos (lua_State *L) {
  lua_pushnumber(L, acos(luaL_checknumber(L, 1)));
  return 1;
}

static int math_atan (lua_State *L) {
  lua_pushnumber(L, atan(luaL_checknumber(L, 1)));
  return 1;
}

static int math_atan2 (lua_State *L) {
  lua_pushnumber(L, atan2(luaL_checknumber(L, 1), luaL_checknumber(L, 2)));
  return 1;
}

static int math_ceil (lua_State *L) {
  lua_pushnumber(L, ceil(luaL_checknumber(L, 1)));
  return 1;
}

static int math_floor (lua_State *L) {
  lua_pushnumber(L, floor(luaL_checknumber(L, 1)));
  return 1;
}

static int math_fmod (lua_State *L) {
  lua_pushnumber(L, fmod(luaL_checknumber(L, 1), luaL_checknumber(L, 2)));
  return 1;
}

static int math_modf (lua_State *L) {
  double ip;
  double fp = modf(luaL_checknumber(L, 1), &ip);
  lua_pushnumber(L, ip);
  lua_pushnumber(L, fp);
  return 2;
}

#else  // #ifndef LUA_NUMBER_INTEGRAL

// In integer math, floor() and ceil() give the same value;
// having them in the integer library allows you to write code that
// works in both integer and floating point versions of Lua.
// This identity function is used for them.

static int math_identity (lua_State *L) {
  lua_pushnumber(L, luaL_checknumber(L, 1));
  return 1;
}

#endif // #ifndef LUA_NUMBER_INTEGRAL

#ifdef LUA_NUMBER_INTEGRAL
// Integer square root for integer version
static lua_Number isqrt(lua_Number x)
{
  lua_Number op, res, one;

  op = x; res = 0;

  /* "one" starts at the highest power of four <= than the argument. */
  one = 1 << 30;  /* second-to-top bit set */
  while (one > op) one >>= 2;

  while (one != 0) {
    if (op >= res + one) {
      op = op - (res + one);
      res = res +  2 * one;
    }
    res >>= 1;
    one >>= 2;
  }
  return(res);
}
#endif

static int math_sqrt (lua_State *L) {
#ifdef LUA_NUMBER_INTEGRAL
  lua_Number x = luaL_checknumber(L, 1);
  luaL_argcheck(L, 0<=x, 1, "negative");
  lua_pushnumber(L, isqrt(x));
#else
  lua_pushnumber(L, sqrt(luaL_checknumber(L, 1)));
#endif
  return 1;
}

#ifdef LUA_NUMBER_INTEGRAL
# define pow(a,b) luai_ipow(a,b)
#endif

static int math_pow (lua_State *L) {
  lua_pushnumber(L, pow(luaL_checknumber(L, 1), luaL_checknumber(L, 2)));
  return 1;
}

#ifdef LUA_NUMBER_INTEGRAL
# undef pow
#endif


#ifndef LUA_NUMBER_INTEGRAL

static int math_log (lua_State *L) {
  lua_pushnumber(L, log(luaL_checknumber(L, 1)));
  return 1;
}

static int math_log10 (lua_State *L) {
  lua_pushnumber(L, log10(luaL_checknumber(L, 1)));
  return 1;
}

static int math_exp (lua_State *L) {
  lua_pushnumber(L, exp(luaL_checknumber(L, 1)));
  return 1;
}

static int math_deg (lua_State *L) {
  lua_pushnumber(L, luaL_checknumber(L, 1)/RADIANS_PER_DEGREE);
  return 1;
}

static int math_rad (lua_State *L) {
  lua_pushnumber(L, luaL_checknumber(L, 1)*RADIANS_PER_DEGREE);
  return 1;
}

static int math_frexp (lua_State *L) {
  int e;
  lua_pushnumber(L, frexp(luaL_checknumber(L, 1), &e));
  lua_pushinteger(L, e);
  return 2;
}

static int math_ldexp (lua_State *L) {
  lua_pushnumber(L, ldexp(luaL_checknumber(L, 1), luaL_checkint(L, 2)));
  return 1;
}

#endif // #ifdef LUA_NUMBER_INTEGRAL

static int math_min (lua_State *L) {
  int n = lua_gettop(L);  /* number of arguments */
  lua_Number dmin = luaL_checknumber(L, 1);
  int i;
  for (i=2; i<=n; i++) {
    lua_Number d = luaL_checknumber(L, i);
    if (d < dmin)
      dmin = d;
  }
  lua_pushnumber(L, dmin);
  return 1;
}


static int math_max (lua_State *L) {
  int n = lua_gettop(L);  /* number of arguments */
  lua_Number dmax = luaL_checknumber(L, 1);
  int i;
  for (i=2; i<=n; i++) {
    lua_Number d = luaL_checknumber(L, i);
    if (d > dmax)
      dmax = d;
  }
  lua_pushnumber(L, dmax);
  return 1;
}


#ifdef LUA_NUMBER_INTEGRAL

static int math_random (lua_State *L) {
  lua_Number r = (lua_Number)(rand()%RAND_MAX);

  switch (lua_gettop(L)) {  /* check number of arguments */
    case 0: {  /* no arguments */
      lua_pushnumber(L, 0);  /* Number between 0 and 1 - always 0 with ints */
      break;
    }
    case 1: {  /* only upper limit */
      int u = luaL_checkint(L, 1);
      luaL_argcheck(L, 1<=u, 1, "interval is empty");
      lua_pushnumber(L, (r % u)+1);  /* int between 1 and `u' */
      break;
    }
    case 2: {  /* lower and upper limits */
      int l = luaL_checkint(L, 1);
      int u = luaL_checkint(L, 2);
      luaL_argcheck(L, l<=u, 2, "interval is empty");
      lua_pushnumber(L, (r%(u-l+1))+l);  /* int between `l' and `u' */
      break;
    }
    default: return luaL_error(L, "wrong number of arguments");
  }
  return 1;
}

#else

static int math_random (lua_State *L) {
  /* the `%' avoids the (rare) case of r==1, and is needed also because on
     some systems (SunOS!) `rand()' may return a value larger than RAND_MAX */
  lua_Number r = (lua_Number)(rand()%RAND_MAX) / (lua_Number)RAND_MAX;
  switch (lua_gettop(L)) {  /* check number of arguments */
    case 0: {  /* no arguments */
      lua_pushnumber(L, r);  /* Number between 0 and 1 */
      break;
    }
    case 1: {  /* only upper limit */
      int u = luaL_checkint(L, 1);
      luaL_argcheck(L, 1<=u, 1, "interval is empty");
      lua_pushnumber(L, floor(r*u)+1);  /* int between 1 and `u' */
      break;
    }
    case 2: {  /* lower and upper limits */
      int l = luaL_checkint(L, 1);
      int u = luaL_checkint(L, 2);
      luaL_argcheck(L, l<=u, 2, "interval is empty");
      lua_pushnumber(L, floor(r*(u-l+1))+l);  /* int between `l' and `u' */
      break;
    }
    default: return luaL_error(L, "wrong number of arguments");
  }
  return 1;
}

#endif


static int math_randomseed (lua_State *L) {
  srand(luaL_checkint(L, 1));
  return 0;
}

#define MIN_OPT_LEVEL 1
#include "lrodefs.h"
const LUA_REG_TYPE math_map[] = {
#ifdef LUA_NUMBER_INTEGRAL
  {LSTRKEY("abs"),   LFUNCVAL(math_abs)},
  {LSTRKEY("ceil"),  LFUNCVAL(math_identity)},
  {LSTRKEY("floor"), LFUNCVAL(math_identity)},
  {LSTRKEY("max"),   LFUNCVAL(math_max)},
  {LSTRKEY("min"),   LFUNCVAL(math_min)},
  {LSTRKEY("pow"),   LFUNCVAL(math_pow)},
  {LSTRKEY("random"),     LFUNCVAL(math_random)},
  {LSTRKEY("randomseed"), LFUNCVAL(math_randomseed)},
  {LSTRKEY("sqrt"),  LFUNCVAL(math_sqrt)},
#if LUA_OPTIMIZE_MEMORY > 0
  {LSTRKEY("huge"),  LNUMVAL(LONG_MAX)},
#endif
#else
  {LSTRKEY("abs"),   LFUNCVAL(math_abs)},
  {LSTRKEY("acos"),  LFUNCVAL(math_acos)},
  {LSTRKEY("asin"),  LFUNCVAL(math_asin)},
  {LSTRKEY("atan2"), LFUNCVAL(math_atan2)},
  {LSTRKEY("atan"),  LFUNCVAL(math_atan)},
  {LSTRKEY("ceil"),  LFUNCVAL(math_ceil)},
  {LSTRKEY("cosh"),  LFUNCVAL(math_cosh)},
  {LSTRKEY("cos"),   LFUNCVAL(math_cos)},
  {LSTRKEY("deg"),   LFUNCVAL(math_deg)},
  {LSTRKEY("exp"),   LFUNCVAL(math_exp)},
  {LSTRKEY("floor"), LFUNCVAL(math_floor)},
  {LSTRKEY("fmod"),  LFUNCVAL(math_fmod)},
#if LUA_OPTIMIZE_MEMORY > 0 && defined(LUA_COMPAT_MOD)
  {LSTRKEY("mod"),   LFUNCVAL(math_fmod)}, 
#endif
  {LSTRKEY("frexp"), LFUNCVAL(math_frexp)},
  {LSTRKEY("ldexp"), LFUNCVAL(math_ldexp)},
  {LSTRKEY("log10"), LFUNCVAL(math_log10)},
  {LSTRKEY("log"),   LFUNCVAL(math_log)},
  {LSTRKEY("max"),   LFUNCVAL(math_max)},
  {LSTRKEY("min"),   LFUNCVAL(math_min)},
  {LSTRKEY("modf"),   LFUNCVAL(math_modf)},
  {LSTRKEY("pow"),   LFUNCVAL(math_pow)},
  {LSTRKEY("rad"),   LFUNCVAL(math_rad)},
  {LSTRKEY("random"),     LFUNCVAL(math_random)},
  {LSTRKEY("randomseed"), LFUNCVAL(math_randomseed)},
  {LSTRKEY("sinh"),   LFUNCVAL(math_sinh)},
  {LSTRKEY("sin"),   LFUNCVAL(math_sin)},
  {LSTRKEY("sqrt"),  LFUNCVAL(math_sqrt)},
  {LSTRKEY("tanh"),   LFUNCVAL(math_tanh)},
  {LSTRKEY("tan"),   LFUNCVAL(math_tan)},
#if LUA_OPTIMIZE_MEMORY > 0
  {LSTRKEY("pi"),    LNUMVAL(PI)},
  {LSTRKEY("huge"),  LNUMVAL(HUGE_VAL)},
#endif // #if LUA_OPTIMIZE_MEMORY > 0
#endif // #ifdef LUA_NUMBER_INTEGRAL
  {LNILKEY, LNILVAL}
};


/*
** Open math library
*/

#if defined LUA_NUMBER_INTEGRAL
# include <limits.h>		/* for LONG_MAX */
#endif

LUALIB_API int luaopen_math (lua_State *L) {
#if LUA_OPTIMIZE_MEMORY > 0
  return 0;
#else
  luaL_register(L, LUA_MATHLIBNAME, math_map);
# if defined LUA_NUMBER_INTEGRAL
  lua_pushnumber(L, LONG_MAX);
  lua_setfield(L, -2, "huge");
# else
  lua_pushnumber(L, PI);
  lua_setfield(L, -2, "pi");
  lua_pushnumber(L, HUGE_VAL);
  lua_setfield(L, -2, "huge");
#  if defined(LUA_COMPAT_MOD)
  lua_getfield(L, -1, "fmod");
  lua_setfield(L, -2, "mod");
#  endif
# endif
  return 1;
#endif
}
