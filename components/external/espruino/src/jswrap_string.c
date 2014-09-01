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
 * JavaScript String Functions
 * ----------------------------------------------------------------------------
 */
#include "jswrap_string.h"

/*JSON{ "type":"class",
        "class" : "String",
        "check" : "jsvIsString(var)",
        "description" : ["This is the built-in class for Text Strings.",
                         "Text Strings in Espruino are not zero-terminated, so you can store zeros in them." ]
}*/

/*JSON{ "type":"constructor", "class": "String",  "name": "String",
         "description" : "Create a new String",
         "generate" : "jswrap_string_constructor",
         "params" : [ [ "str", "JsVar", "A value to turn into a string. If undefined or not supplied, an empty String is created." ] ],
         "return" : [ "JsVar", "A String" ]

}*/
JsVar *jswrap_string_constructor(JsVar *a) {
  if (!a) return jsvNewFromEmptyString(); // no argument - return an empty string
  return jsvAsString(a, false);
}

/*JSON{ "type":"staticmethod", "class": "String", "name" : "fromCharCode",
         "description" : "Return the character represented by the given character code.",
         "generate" : "jswrap_string_fromCharCode",
         "params" : [ [ "code", "int", "The character code to create a character from (range 0-255)"] ],
         "return" : ["JsVar", "The character"]
}*/
JsVar *jswrap_string_fromCharCode(JsVarInt code) {
  // We do this so we can handle '/0' in a string
  JsVar *r = jsvNewFromEmptyString();
  if (r) { // out of mem?
    char ch = (char)code;
    jsvAppendStringBuf(r, &ch, 1);
  }
  return r;
}

/*JSON{ "type":"method", "class": "String", "name" : "charAt",
         "description" : "Return a single character at the given position in the String.",
         "generate" : "jswrap_string_charAt",
         "params" : [ [ "pos", "int", "The character number in the string. Negative values return characters from end of string (-1 = last char)"] ],
         "return" : ["JsVar", "The character in the string"]
}*/
JsVar *jswrap_string_charAt(JsVar *parent, JsVarInt idx) {
  // We do this so we can handle '/0' in a string
  JsVar *r = jsvNewFromEmptyString();
  if (r) { // out of mem?
    char ch = jsvGetCharInString(parent, (int)idx);
    jsvAppendStringBuf(r, &ch, 1);
  }
  return r;
}

/*JSON{ "type":"method", "class": "String", "name" : "charCodeAt",
         "description" : ["Return the integer value of a single character at the given position in the String.",
                          "Note that this returns 0 not 'NaN' for out of bounds characters"],
         "generate" : "jswrap_string_charCodeAt",
         "params" : [ [ "pos", "int", "The character number in the string. Negative values return characters from end of string (-1 = last char)"] ],
         "return" : ["int", "The integer value of a character in the string"]
}*/
JsVarInt jswrap_string_charCodeAt(JsVar *parent, JsVarInt idx) {
  return jsvGetCharInString(parent, (int)idx);
}


/*JSON{ "type":"method", "class": "String", "name" : "indexOf",
         "description" : "Return the index of substring in this string, or -1 if not found",
         "generate" : "jswrap_string_indexOf",
         "params" : [ [ "substring", "JsVar", "The string to search for"] ],
         "return" : ["int", "The index of the string, or -1 if not found"]
}*/
JsVarInt jswrap_string_indexOf(JsVar *parent, JsVar *v) {
  // slow, but simple!
   v = jsvAsString(v, false);
   if (!v) return 0; // out of memory
   int idx = -1;
   int l = (int)jsvGetStringLength(parent) - (int)jsvGetStringLength(v);
   for (idx=0;idx<=l;idx++) {
     if (jsvCompareString(parent, v, idx, 0, true)==0) {
       jsvUnLock(v);
       return idx;
     }
   }
   jsvUnLock(v);
   return -1;
}

/*JSON{ "type":"method", "class": "String", "name" : "substring",
         "generate" : "jswrap_string_substring",
         "params" : [ [ "start", "int", "The start character index"],
                      [ "end", "JsVar", "The end character index"] ],
         "return" : ["JsVar", "The part of this string between start and end"]
}*/
JsVar *jswrap_string_substring(JsVar *parent, JsVarInt pStart, JsVar *vEnd) {
  JsVar *res;
  JsVarInt pEnd = jsvIsUndefined(vEnd) ? JSVAPPENDSTRINGVAR_MAXLENGTH : (int)jsvGetInteger(vEnd);
  if (pStart<0) pStart=0;
  if (pEnd<0) pEnd=0;
  if (pEnd<pStart) {
    JsVarInt l = pStart;
    pStart = pEnd;
    pEnd = l;
  }
  res = jsvNewWithFlags(JSV_STRING);
  if (!res) return 0; // out of memory
  jsvAppendStringVar(res, parent, (int)pStart, (int)(pEnd-pStart));
  return res;
}

/*JSON{ "type":"method", "class": "String", "name" : "substr",
         "generate" : "jswrap_string_substr",
         "params" : [ [ "start", "int", "The start character index"],
                      [ "len", "JsVar", "The number of characters"] ],
         "return" : ["JsVar", "Part of this string from start for len characters"]
}*/
JsVar *jswrap_string_substr(JsVar *parent, JsVarInt pStart, JsVar *vLen) {
  JsVar *res;
  JsVarInt pLen = jsvIsUndefined(vLen) ? JSVAPPENDSTRINGVAR_MAXLENGTH : (int)jsvGetInteger(vLen);
  if (pLen<0) pLen=0;
  res = jsvNewWithFlags(JSV_STRING);
  if (!res) return 0; // out of memory
  jsvAppendStringVar(res, parent, (int)pStart, (int)pLen);
  return res;
}

/*JSON{ "type":"method", "class": "String", "name" : "split",
         "description" : "Return an array made by splitting this string up by the separator. eg. ```'1,2,3'.split(',')==[1,2,3]```",
         "generate" : "jswrap_string_split",
         "params" : [ [ "separator", "JsVar", "The start character index"] ],
         "return" : ["JsVar", "Part of this string from start for len characters"]
}*/
JsVar *jswrap_string_split(JsVar *parent, JsVar *split) {
  JsVar *array;
  int last, idx, arraylen=0;
  int splitlen =  (int)jsvGetStringLength(split);
  int l = (int)jsvGetStringLength(parent) - splitlen;
  last = 0;

  array = jsvNewWithFlags(JSV_ARRAY);
  if (!array) return 0; // out of memory

  for (idx=0;idx<=l;idx++) {
    if (idx==l || jsvCompareString(parent, split, idx, 0, true)==0) {
      JsVar *part = jsvNewFromEmptyString();
      if (!part) break; // out of memory
      JsVar *idxvar = jsvMakeIntoVariableName(jsvNewFromInteger(arraylen++), part);
      if (idxvar) { // could be out of memory
        if (idx==l) idx=l+splitlen; // if the last element, do to the end of the string
        jsvAppendStringVar(part, parent, last, idx-last);
        jsvAddName(array, idxvar);
        last = idx+splitlen;
        jsvUnLock(idxvar);
      }
      jsvUnLock(part);
    }
  }
  return array;
}
