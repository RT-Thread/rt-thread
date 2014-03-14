/*
 * This file is part of Espruino, a JavaScript interpreter for Microcontrollers
 *
 * Copyright (C) 2013 Gordon Williams <gw@pur3.co.uk>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * ----------------------------------------------------------------------------
 * This file is designed to be parsed during the build process
 *
 * Contains built-in functions for Maths
 * ----------------------------------------------------------------------------
 */
#include "jswrap_math.h"

/*JSON{ "type":"class",
        "class" : "Math",
        "description" : "This is a standard JavaScript class that contains useful Maths routines"
}*/

// -------------------------------------------------------------------- Integer
/*JSON{ "type":"staticmethod",
         "class" : "Integer", "name" : "valueOf",
         "generate" : "jswrap_integer_valueOf",
         "description" : "Given a string containing a single character, return the numeric value of it",
         "params" : [ [ "character" ,"JsVar", "A string containing a single character"] ],
         "return" : ["int", "The integer value of char"]
}*/
JsVarInt jswrap_integer_valueOf(JsVar *v) {
  if (!jsvIsString(v) || jsvGetStringLength(v)!=1)
    return 0;
  return (int)v->varData.str[0];
}
/*JSON{ "type":"variable", "name" : "NaN",
         "generate_full" : "NAN",
         "return" : ["float", "Not a  Number"]
}*/
 // -------------------------------------------------------------------- Double
/*JSON{ "type":"staticmethod",
         "class" : "Double", "name" : "doubleToIntBits",
         "generate_full" : "*(JsVarInt*)&x",
         "description" : " Convert the floating point value given into an integer representing the bits contained in it",
         "params" : [ [ "x", "float", "A floating point number"] ],
         "return" : ["int", "The integer representation of x"]
}*/
// -------------------------------------------------------------------- Math
/*JSON{ "type":"staticproperty",
         "class" : "Math", "name" : "E",
         "generate_full" : "2.71828182846",
         "return" : ["float", "The value of E - 2.71828182846"]
}*/
/*JSON{ "type":"staticproperty",
         "class" : "Math", "name" : "PI",
         "generate_full" : "3.14159265359",
         "return" : ["float", "The value of PI - 3.14159265359"]
}*/
/*JSON{ "type":"staticmethod",
         "class" : "Math", "name" : "abs",
         "generate" : "jswrap_math_abs",
         "params" : [ [ "x", "float", "A floating point value"] ],
         "return" : ["float", "The absolute value of x (eg, ```Math.abs(2)==2```, but also ```Math.abs(-2)==2```)"]
}*/
JsVarFloat jswrap_math_abs(JsVarFloat x) {
  return (x<0)?-x:x;
}
/*JSON{ "type":"staticmethod",
         "class" : "Math", "name" : "acos",
         "generate" : "acos",
         "params" : [ [ "x", "float", "The value to get the arc cosine of"] ],
         "return" : ["float", "The arc cosine of x, between 0 and PI"]
}*/
/*JSON{ "type":"staticmethod",
         "class" : "Math", "name" : "asin",
         "generate" : "asin",
         "params" : [ [ "x", "float", "The value to get the arc sine of"] ],
         "return" : ["float", "The arc sine of x, between -PI/2 and PI/2"]
}*/
/*JSON{ "type":"staticmethod",
         "class" : "Math", "name" : "atan",
         "generate" : "atan",
         "params" : [ [ "x", "float", "The value to get the arc tangent  of"] ],
         "return" : ["float", "The arc tangent of x, between -PI/2 and PI/2"]
}*/
/*JSON{ "type":"staticmethod",
        "class" : "Math", "name" : "atan2",
         "generate" : "atan2",
         "params" : [ [ "y", "float", "The Y-part of the angle to get the arc tangent of"],
                      [ "x", "float", "The X-part of the angle to get the arc tangent of"] ],
         "return" : ["float", "The arctangent of Y/X, between -PI and PI"]
}*/

/* we use sin here, not cos, to try and save a bit of code space */
/*JSON{ "type":"staticmethod",
         "class" : "Math", "name" : "cos",
         "generate_full" : "sin(jsvGetFloat(theta) + (3.14159265359/2.0))",
         "params" : [ [ "theta", "float", "The angle to get the cosine of"] ],
         "return" : ["float", "The cosine of theta"]
}*/

#define DBL_MAX    1.7976931348623157E+308

double fs_fmod(double x, double y)
{
  double a, b;
  const double c = x;

  if (0 > c) {
    x = -x;
  }
  if (0 > y) {
    y = -y;
  }
  if (y != 0 && DBL_MAX >= y && DBL_MAX >= x) {
    while (x >= y) {
      a = x / 2;
      b = y;
      while (a >= b) {
        b *= 2;
      }
      x -= b;
    }
  } else {
    x = 0;
  }
  return 0 > c ? -x : x;
}

double jswrap_math_pow(double x, double y)
{
  double p;
  if (0 > x && fs_fmod(y, 1) == 0) {
    if (fs_fmod(y, 2) == 0) {
      p = exp(log(-x) * y);
    } else {
      p = -exp(log(-x) * y);
    }
  } else {
    if (x != 0 || 0 >= y) {
      p = exp(log( x) * y);
    } else {
      p = 0;
    }
  }
  return p;
}


/*JSON{ "type":"staticmethod",
         "class" : "Math", "name" : "pow",
         "generate" : "jswrap_math_pow",
         "params" : [ [ "x", "float", "The value to raise to the power"],
                      [ "y", "float", "The power x should be raised to"] ],
         "return" : ["float", "x raised to the power y (x^y)"]
}*/
/*JSON{ "type":"staticmethod",
         "class" : "Math", "name" : "random",
         "generate_full" : "(JsVarFloat)rand() / (JsVarFloat)RAND_MAX",
         "return" : ["float", "A random number between 0 and 1"]
}*/
/*JSON{ "type":"staticmethod",
         "class" : "Math", "name" : "round",
         "generate" : "(JsVarInt)round",
         "params" : [ [ "x", "float", "The value to round"] ],
         "return" : ["int", "x, rounded to the nearest integer"]
}*/
/*JSON{ "type":"staticmethod",
         "class" : "Math", "name" : "sin",
         "generate" : "sin",
         "params" : [ [ "theta", "float", "The angle to get the sine of"] ],
         "return" : ["float", "The sine of theta"]
}*/

/* we could use the real sqrt - but re-use pow to save on code space */
/*JSON{ "type":"staticmethod",
         "class" : "Math", "name" : "sqrt",
         "generate_full" : "jswrap_math_pow(jsvGetFloat(x),0.5)",
         "params" : [ [ "x", "float", "The value to take the square root of"] ],
         "return" : ["float", "The square root of x"]
}*/

/*JSON{ "type":"staticmethod",
         "class" : "Math", "name" : "ceil",
         "generate" : "ceil",
         "params" : [ [ "x", "float", "The value to round up"] ],
         "return" : ["float", "x, rounded upwards to the nearest integer"]
}*/
/*JSON{ "type":"staticmethod",
         "class" : "Math", "name" : "floor",
         "generate" : "floor",
         "params" : [ [ "x", "float", "The value to round down"] ],
         "return" : ["float", "x, rounded downwards to the nearest integer"]
}*/

/*JSON{ "type":"staticmethod",
         "class" : "Math", "name" : "exp",
         "generate" : "exp",
         "params" : [ [ "x", "float", "The value raise E to the power of"] ],
         "return" : ["float", "E^x"]
}*/
/*JSON{ "type":"staticmethod",
         "class" : "Math", "name" : "log",
         "generate" : "log",
         "params" : [ [ "x", "float", "The value to take the logarithm (base E) root of"] ],
         "return" : ["float", "The log (base E) of x"]
}*/

/*JSON{ "type":"staticmethod", "ifndef" : "SAVE_ON_FLASH",
         "class" : "Math", "name" : "clip",
         "generate" : "jswrap_math_clip",
         "description" : "Clip a number to be between min and max (inclusive)",
         "params" : [ [ "x", "float", "A floating point value to clip"],
                      [ "min", "float", "The smallest the value should be"],
                      [ "max", "float", "The largest the value should be"] ],
         "return" : ["float", "The value of x, clipped so as not to be below min or above max."]
}*/
JsVarFloat jswrap_math_clip(JsVarFloat x, JsVarFloat min, JsVarFloat max) {
  if (x<min) x=min;
  if (x>max) x=max;
  return x;
}

/*JSON{ "type":"staticmethod", "ifndef" : "SAVE_ON_FLASH",
         "class" : "Math", "name" : "wrap",
         "generate" : "wrapAround",
         "description" : "Wrap a number around if it is less than 0 or greater than or equal to max. For instance you might do: ```Math.wrap(angleInDegrees, 360)```",
         "params" : [ [ "x", "float", "A floating point value to wrap"],
                      [ "max", "float", "The largest the value should be"] ],
         "return" : ["float", "The value of x, wrapped so as not to be below min or above max."]
}*/


