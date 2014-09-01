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
 * JavaScript methods for ArrayBuffers
 * ----------------------------------------------------------------------------
 */
#include "jswrap_arraybuffer.h"
#include "jsparse.h"
#include "jsinteractive.h"

/*JSON{ "type":"class",
        "class" : "ArrayBuffer",
        "check" : "jsvIsArrayBuffer(var) && var->varData.arraybuffer.type==ARRAYBUFFERVIEW_ARRAYBUFFER",
        "not_real_object" : "Don't treat this as a real object - it's handled differently internally",
        "description" : ["This is the built-in JavaScript class for array buffers." ]
}*/

/*JSON{ "type":"class",
        "class" : "ArrayBufferView",
        "description" : ["This is the built-in JavaScript class that is the prototype for Uint8Array / Float32Array / etc" ]
}*/

/*JSON{ "type":"class",
        "class" : "Uint8Array", "prototype" : "ArrayBufferView",
        "check" : "jsvIsArrayBuffer(var) && var->varData.arraybuffer.type==ARRAYBUFFERVIEW_UINT8",
        "not_real_object" : "Don't treat this as a real object - it's handled differently internally",
        "description" : ["This is the built-in JavaScript class for a typed array.",
                         "Instantiate this in order to efficiently store arrays of data (Espruino's normal arrays store data in a map, which is inefficient for non-sparse arrays). " ]
}*/
/*JSON{ "type":"class",
        "class" : "Int8Array", "prototype" : "ArrayBufferView",
        "check" : "jsvIsArrayBuffer(var) && var->varData.arraybuffer.type==ARRAYBUFFERVIEW_INT8",
        "not_real_object" : "Don't treat this as a real object - it's handled differently internally",
        "description" : ["This is the built-in JavaScript class for a typed array.",
                         "Instantiate this in order to efficiently store arrays of data (Espruino's normal arrays store data in a map, which is inefficient for non-sparse arrays). " ]
}*/
/*JSON{ "type":"class",
        "class" : "Uint16Array", "prototype" : "ArrayBufferView",
        "check" : "jsvIsArrayBuffer(var) && var->varData.arraybuffer.type==ARRAYBUFFERVIEW_UINT16",
        "not_real_object" : "Don't treat this as a real object - it's handled differently internally",
        "description" : ["This is the built-in JavaScript class for a typed array.",
                         "Instantiate this in order to efficiently store arrays of data (Espruino's normal arrays store data in a map, which is inefficient for non-sparse arrays). " ]
}*/
/*JSON{ "type":"class",
        "class" : "Int16Array", "prototype" : "ArrayBufferView",
        "check" : "jsvIsArrayBuffer(var) && var->varData.arraybuffer.type==ARRAYBUFFERVIEW_INT16",
        "not_real_object" : "Don't treat this as a real object - it's handled differently internally",
        "description" : ["This is the built-in JavaScript class for a typed array.",
                         "Instantiate this in order to efficiently store arrays of data (Espruino's normal arrays store data in a map, which is inefficient for non-sparse arrays). " ]
}*/
/*JSON{ "type":"class",
        "class" : "Uint32Array", "prototype" : "ArrayBufferView",
        "check" : "jsvIsArrayBuffer(var) && var->varData.arraybuffer.type==ARRAYBUFFERVIEW_UINT32",
        "not_real_object" : "Don't treat this as a real object - it's handled differently internally",
        "description" : ["This is the built-in JavaScript class for a typed array.",
                         "Instantiate this in order to efficiently store arrays of data (Espruino's normal arrays store data in a map, which is inefficient for non-sparse arrays). " ]
}*/
/*JSON{ "type":"class",
        "class" : "Int32Array", "prototype" : "ArrayBufferView",
        "check" : "jsvIsArrayBuffer(var) && var->varData.arraybuffer.type==ARRAYBUFFERVIEW_INT32",
        "not_real_object" : "Don't treat this as a real object - it's handled differently internally",
        "description" : ["This is the built-in JavaScript class for a typed array.",
                         "Instantiate this in order to efficiently store arrays of data (Espruino's normal arrays store data in a map, which is inefficient for non-sparse arrays). " ]
}*/
/*JSON{ "type":"class",
        "class" : "Float32Array", "prototype" : "ArrayBufferView",
        "check" : "jsvIsArrayBuffer(var) && var->varData.arraybuffer.type==ARRAYBUFFERVIEW_FLOAT32",
        "not_real_object" : "Don't treat this as a real object - it's handled differently internally",
        "description" : ["This is the built-in JavaScript class for a typed array.",
                         "Instantiate this in order to efficiently store arrays of data (Espruino's normal arrays store data in a map, which is inefficient for non-sparse arrays). " ]
}*/
/*JSON{ "type":"class",
        "class" : "Float64Array", "prototype" : "ArrayBufferView",
        "check" : "jsvIsArrayBuffer(var) && var->varData.arraybuffer.type==ARRAYBUFFERVIEW_FLOAT64",
        "not_real_object" : "Don't treat this as a real object - it's handled differently internally",
        "description" : ["This is the built-in JavaScript class for a typed array.",
                         "Instantiate this in order to efficiently store arrays of data (Espruino's normal arrays store data in a map, which is inefficient for non-sparse arrays). " ]
}*/


/*JSON{ "type":"constructor", "class": "ArrayBuffer",  "name": "ArrayBuffer",
         "description" : "Create an Array Buffer object",
         "generate" : "jswrap_arraybuffer_constructor",
         "params" : [ [ "byteLength", "int", "The length in Bytes" ] ],
         "return" : [ "JsVar", "An ArrayBuffer object" ]

}*/
JsVar *jswrap_arraybuffer_constructor(JsVarInt byteLength) {
  if (byteLength <= 0 || byteLength>65535) {
    jsError("Invalid length for ArrayBuffer\n");
    return 0;
  }
  if (byteLength > JSV_ARRAYBUFFER_MAX_LENGTH) {
    jsError("ArrayBuffer too long\n");
    return 0;
  }
  JsVar *arrData = jsvNewStringOfLength((unsigned int)byteLength);
  if (!arrData) return 0;
  JsVar *arr = jsvNewWithFlags(JSV_ARRAYBUFFER);
  if (!arr) {
    jsvUnLock(arrData);
    return 0;
  }
  arr->firstChild = jsvGetRef(jsvRef(arrData));
  jsvUnLock(arrData);
  arr->varData.arraybuffer.type = ARRAYBUFFERVIEW_ARRAYBUFFER;
  arr->varData.arraybuffer.byteOffset = 0;
  arr->varData.arraybuffer.length = (unsigned short)byteLength;
  return arr;
}


/*
 * Potential invocations:
 * Uint8Array Uint8Array(unsigned long length);
 * Uint8Array Uint8Array(TypedArray array);
 * Uint8Array Uint8Array(sequence<type> array);
 * Uint8Array Uint8Array(ArrayBuffer buffer, optional unsigned long byteOffset, optional unsigned long length);
 */

/*JSON{ "type":"constructor", "class": "Uint8Array",  "name": "Uint8Array",
         "description" : "Create a typed array based on the given input. Either an existing Array Buffer, an Integer as a Length, or a simple array",
         "generate_full" : "jswrap_typedarray_constructor(ARRAYBUFFERVIEW_UINT8, arr, jsvGetInteger(byteOffset), jsvGetInteger(length))",
         "params" : [ [ "arr", "JsVar", "The array or typed array to base this off, or an integer which is the array length" ],
                      [ "byteOffset", "int", "The byte offset in the ArrayBuffer  (ONLY IF the first argument was an ArrayBuffer)" ],
                      [ "length", "int", "The length (ONLY IF the first argument was an ArrayBuffer)" ] ],
         "return" : [ "JsVar", "A typed array" ]
}*/
/*JSON{ "type":"constructor", "class": "Int8Array",  "name": "Int8Array",
         "description" : "Create a typed array based on the given input. Either an existing Array Buffer, an Integer as a Length, or a simple array",
         "generate_full" : "jswrap_typedarray_constructor(ARRAYBUFFERVIEW_INT8, arr, jsvGetInteger(byteOffset), jsvGetInteger(length))",
         "params" : [ [ "arr", "JsVar", "The array or typed array to base this off, or an integer which is the array length" ],
                      [ "byteOffset", "int", "The byte offset in the ArrayBuffer  (ONLY IF the first argument was an ArrayBuffer)" ],
                      [ "length", "int", "The length (ONLY IF the first argument was an ArrayBuffer)" ] ],
         "return" : [ "JsVar", "A typed array" ]
}*/
/*JSON{ "type":"constructor", "class": "Uint16Array",  "name": "Uint16Array",
         "description" : "Create a typed array based on the given input. Either an existing Array Buffer, an Integer as a Length, or a simple array",
         "generate_full" : "jswrap_typedarray_constructor(ARRAYBUFFERVIEW_UINT16, arr, jsvGetInteger(byteOffset), jsvGetInteger(length))",
         "params" : [ [ "arr", "JsVar", "The array or typed array to base this off, or an integer which is the array length" ],
                      [ "byteOffset", "int", "The byte offset in the ArrayBuffer  (ONLY IF the first argument was an ArrayBuffer)" ],
                      [ "length", "int", "The length (ONLY IF the first argument was an ArrayBuffer)" ] ],
         "return" : [ "JsVar", "A typed array" ]
}*/
/*JSON{ "type":"constructor", "class": "Int16Array",  "name": "Int16Array",
         "description" : "Create a typed array based on the given input. Either an existing Array Buffer, an Integer as a Length, or a simple array",
         "generate_full" : "jswrap_typedarray_constructor(ARRAYBUFFERVIEW_INT16, arr, jsvGetInteger(byteOffset), jsvGetInteger(length))",
         "params" : [ [ "arr", "JsVar", "The array or typed array to base this off, or an integer which is the array length" ],
                      [ "byteOffset", "int", "The byte offset in the ArrayBuffer  (ONLY IF the first argument was an ArrayBuffer)" ],
                      [ "length", "int", "The length (ONLY IF the first argument was an ArrayBuffer)" ] ],
         "return" : [ "JsVar", "A typed array" ]
}*/
/*JSON{ "type":"constructor", "class": "Uint32Array",  "name": "Uint32Array",
         "description" : "Create a typed array based on the given input. Either an existing Array Buffer, an Integer as a Length, or a simple array",
         "generate_full" : "jswrap_typedarray_constructor(ARRAYBUFFERVIEW_UINT32, arr, jsvGetInteger(byteOffset), jsvGetInteger(length))",
         "params" : [ [ "arr", "JsVar", "The array or typed array to base this off, or an integer which is the array length" ],
                      [ "byteOffset", "int", "The byte offset in the ArrayBuffer  (ONLY IF the first argument was an ArrayBuffer)" ],
                      [ "length", "int", "The length (ONLY IF the first argument was an ArrayBuffer)" ] ],
         "return" : [ "JsVar", "A typed array" ]
}*/
/*JSON{ "type":"constructor", "class": "Int32Array",  "name": "Int32Array",
         "description" : "Create a typed array based on the given input. Either an existing Array Buffer, an Integer as a Length, or a simple array",
         "generate_full" : "jswrap_typedarray_constructor(ARRAYBUFFERVIEW_INT32, arr, jsvGetInteger(byteOffset), jsvGetInteger(length))",
         "params" : [ [ "arr", "JsVar", "The array or typed array to base this off, or an integer which is the array length" ],
                      [ "byteOffset", "int", "The byte offset in the ArrayBuffer  (ONLY IF the first argument was an ArrayBuffer)" ],
                      [ "length", "int", "The length (ONLY IF the first argument was an ArrayBuffer)" ] ],
         "return" : [ "JsVar", "A typed array" ]
}*/
/*JSON{ "type":"constructor", "class": "Float32Array",  "name": "Float32Array",
         "description" : "Create a typed array based on the given input. Either an existing Array Buffer, an Integer as a Length, or a simple array",
         "generate_full" : "jswrap_typedarray_constructor(ARRAYBUFFERVIEW_FLOAT32, arr, jsvGetInteger(byteOffset), jsvGetInteger(length))",
         "params" : [ [ "arr", "JsVar", "The array or typed array to base this off, or an integer which is the array length" ],
                      [ "byteOffset", "int", "The byte offset in the ArrayBuffer  (ONLY IF the first argument was an ArrayBuffer)" ],
                      [ "length", "int", "The length (ONLY IF the first argument was an ArrayBuffer)" ] ],
         "return" : [ "JsVar", "A typed array" ]
}*/
/*JSON{ "type":"constructor", "class": "Float64Array",  "name": "Float64Array",
         "description" : "Create a typed array based on the given input. Either an existing Array Buffer, an Integer as a Length, or a simple array",
         "generate_full" : "jswrap_typedarray_constructor(ARRAYBUFFERVIEW_FLOAT64, arr, jsvGetInteger(byteOffset), jsvGetInteger(length))",
         "params" : [ [ "arr", "JsVar", "The array or typed array to base this off, or an integer which is the array length" ],
                      [ "byteOffset", "int", "The byte offset in the ArrayBuffer  (ONLY IF the first argument was an ArrayBuffer)" ],
                      [ "length", "int", "The length (ONLY IF the first argument was an ArrayBuffer)" ] ],
         "return" : [ "JsVar", "A typed array" ]
}*/



JsVar *jswrap_typedarray_constructor(JsVarDataArrayBufferViewType type, JsVar *arr, JsVarInt byteOffset, JsVarInt length) {
  JsVar *arrayBuffer = 0;
  if (jsvIsArrayBuffer(arr)) {
    arrayBuffer = jsvLockAgain(arr);
  } else if (jsvIsInt(arr)) {
    length = jsvGetInteger(arr);
    byteOffset = 0;
    arrayBuffer = jswrap_arraybuffer_constructor(JSV_ARRAYBUFFER_GET_SIZE(type)*length);
  } else if (jsvIsArray(arr)) {
    length = jsvGetArrayLength(arr);
    byteOffset = 0;
    arrayBuffer = jswrap_arraybuffer_constructor(JSV_ARRAYBUFFER_GET_SIZE(type)*length);
    // later on we'll populate this
  }
  if (!arrayBuffer) {
    jsError("Unsupported first argument\n");
    return 0;
  }
  if (length<=0) length = (JsVarInt)jsvGetArrayBufferLength(arrayBuffer) / JSV_ARRAYBUFFER_GET_SIZE(type);
  JsVar *typedArr = jsvNewWithFlags(JSV_ARRAYBUFFER);
  if (typedArr) {
    typedArr->varData.arraybuffer.type = type;
    typedArr->varData.arraybuffer.byteOffset = (unsigned short)byteOffset;
    typedArr->varData.arraybuffer.length = (unsigned short)length;
    typedArr->firstChild = jsvGetRef(jsvRef(arrayBuffer));

    if (jsvIsArray(arr)) {
      // if we were given an array, populate this ArrayBuffer
      JsArrayIterator it;
      jsvArrayIteratorNew(&it, arr);
      while (jsvArrayIteratorHasElement(&it)) {
        JsVar *idx = jsvArrayIteratorGetIndex(&it);
        if (jsvIsInt(idx)) {
          JsVar *val = jsvArrayIteratorGetElement(&it);
          jsvArrayBufferSet(typedArr, jsvGetInteger(idx), val);
          jsvUnLock(val);
        }
        jsvUnLock(idx);
        jsvArrayIteratorNext(&it);
      }
      jsvArrayIteratorFree(&it);
    }
  }
  jsvUnLock(arrayBuffer);
  return typedArr;
}


/*JSON{ "type":"property", "class": "ArrayBufferView",  "name": "buffer",
         "description" : "The buffer this view references",
         "generate_full" : "jsvLock(parent->firstChild)",
         "return" : [ "JsVar", "An ArrayBuffer object" ]
}*/
/*JSON{ "type":"property", "class": "ArrayBufferView",  "name": "byteLength",
         "description" : "The length, in bytes, of the view",
         "generate_full" : "parent->varData.arraybuffer.length * JSV_ARRAYBUFFER_GET_SIZE(parent->varData.arraybuffer.type)",
         "return" : [ "int", "The Length" ]
}*/
/*JSON{ "type":"property", "class": "ArrayBufferView",  "name": "byteOffset",
         "description" : "The offset, in bytes, to the first byte of the view within the ArrayBuffer",
         "generate_full" : "parent->varData.arraybuffer.byteOffset",
         "return" : [ "int", "The byte Offset" ]
}*/

/*JSON{ "type":"method", "class": "ArrayBufferView",  "name": "interpolate",
         "description" : "Interpolate between two adjacent values in the Typed Array",
         "generate" : "jswrap_arraybufferview_interpolate",
         "params" : [ [ "index", "float", "Floating point index to access" ] ],
         "return" : [ "float", "The result of interpolating between (int)index and (int)(index+1)" ]
}*/
JsVarFloat jswrap_arraybufferview_interpolate(JsVar *parent, JsVarFloat findex) {
  int idx = (int)findex;
  JsVarFloat a = findex-idx;
  JsvArrayBufferIterator it;
  jsvArrayBufferIteratorNew(&it, parent, idx);
  JsVarFloat fa = jsvArrayBufferIteratorGetFloatValue(&it);
  jsvArrayBufferIteratorNext(&it);
  JsVarFloat fb = jsvArrayBufferIteratorGetFloatValue(&it);
  jsvArrayBufferIteratorFree(&it);
  return fa*(1-a) + fb*a;
} 

/*JSON{ "type":"method", "class": "ArrayBufferView",  "name": "interpolate2d",
         "description" : "Interpolate between two adjacent values in the Typed Array",
         "generate" : "jswrap_arraybufferview_interpolate2d",
         "params" : [ [ "width", "int", "Integer 'width' of 2d array" ],
                      [ "x", "float", "Floating point X index to access" ],
                      [ "y", "float", "Floating point Y index to access" ] ],
         "return" : [ "float", "The result of interpolating in 2d between the 4 surrounding cells" ]
}*/
JsVarFloat jswrap_arraybufferview_interpolate2d(JsVar *parent, JsVarInt width, JsVarFloat x, JsVarFloat y) {
  int yidx = (int)y;
  JsVarFloat ay = y-yidx;

  JsVarFloat findex = x + (JsVarFloat)(yidx*width);
  int idx = (int)findex;
  JsVarFloat ax = findex-idx;

  JsvArrayBufferIterator it;
  jsvArrayBufferIteratorNew(&it, parent, idx);

  JsVarFloat xa,xb;
  int i;

  xa = jsvArrayBufferIteratorGetFloatValue(&it);
  jsvArrayBufferIteratorNext(&it);
  xb = jsvArrayBufferIteratorGetFloatValue(&it);
  JsVarFloat ya = xa*(1-ax) + xb*ax;

  for (i=1;i<width;i++) jsvArrayBufferIteratorNext(&it);

  xa = jsvArrayBufferIteratorGetFloatValue(&it);
  jsvArrayBufferIteratorNext(&it);
  xb = jsvArrayBufferIteratorGetFloatValue(&it);
  jsvArrayBufferIteratorFree(&it);
  JsVarFloat yb = xa*(1-ax) + xb*ax;

  return ya*(1-ay) + yb*ay;
}
