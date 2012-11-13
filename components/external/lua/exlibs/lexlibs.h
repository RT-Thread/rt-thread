/**
 * External library
 */

#ifndef __LEXLIBS_H__
#define __LEXLIBS_H__

/* Arduino library source - larduinolib.c is placed in ART's directories */
#if defined(RT_LUA_USE_ARDUINOLIB)
#define EXLIB_ARDUINO       "arduino"
#define ROM_EXLIB_ARDUINO   \
    _ROM(EXLIB_ARDUINO, luaopen_arduino, arduino_map)
#else
#define ROM_EXLIB_ARDUINO
#endif

#define EXLIB_EXAMPLE       "example"
#define ROM_EXLIB_EXAMPLE   \
        _ROM(EXLIB_EXAMPLE, luaopen_example, example_map)

#define LUA_EXLIBS_ROM      \
        ROM_EXLIB_EXAMPLE   \
        ROM_EXLIB_ARDUINO

#endif

