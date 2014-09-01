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
 * JavaScript methods for Arrays
 * ----------------------------------------------------------------------------
 */
#include "jswrap_array.h"
#include "jsparse.h"

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))


/*JSON{ "type":"class",
        "class" : "Array",
        "check" : "jsvIsArray(var)",
        "description" : ["This is the built-in JavaScript class for arrays.",
                         "Arrays can be defined with ```[]```, ```new Array()```, or ```new Array(length)```" ]
}*/

/*JSON{ "type":"constructor", "class": "Array",  "name": "Array",
         "description" : "Create an Array. Either give it one integer argument (>=0) which is the length of the array, or any number of arguments ",
         "generate" : "jswrap_array_constructor",
         "params" : [ [ "args", "JsVarArray", "The length of the array OR any number of items to add to the array" ] ],
         "return" : [ "JsVar", "An Array" ]

}*/
JsVar *jswrap_array_constructor(JsVar *args) {
  assert(args);
  if (jsvGetArrayLength(args)==1) {
    JsVar *firstArg = jsvSkipNameAndUnLock(jsvArrayGetLast(args)); // also the first!
    if (jsvIsInt(firstArg) && jsvGetInteger(firstArg)>=0) {
      JsVarInt count = jsvGetInteger(firstArg);
      // we cheat - no need to fill the array - just the last element
      if (count>0) {
        JsVar *arr = jsvNewWithFlags(JSV_ARRAY);
        if (!arr) return 0; // out of memory
        JsVar *idx = jsvMakeIntoVariableName(jsvNewFromInteger(count-1), 0);
        if (idx) { // could be out of memory
          jsvAddName(arr, idx);
          jsvUnLock(idx);
        }
        jsvUnLock(firstArg);
        return arr;
      }
    }
    jsvUnLock(firstArg);
  }
  // Otherwise, we just return the array!
  return jsvLockAgain(args);
}

/*JSON{ "type":"method", "class": "Array", "name" : "contains",
         "description" : "Return true if this array contains the given value",
         "generate" : "jswrap_array_contains",
         "params" : [ [ "value", "JsVar", "The value to check for"] ],
         "return" : ["bool", "Whether value is in the array or not"]
}*/
bool jswrap_array_contains(JsVar *parent, JsVar *value) {
  // ArrayIndexOf will return 0 if not found
  JsVar *arrElement = jsvGetArrayIndexOf(parent, value, false/*not exact*/);
  bool contains = arrElement!=0;
  jsvUnLock(arrElement);
  return contains;
}

/*JSON{ "type":"method", "class": "Array", "name" : "indexOf",
         "description" : "Return the index of the value in the array, or -1",
         "generate" : "jswrap_array_indexOf",
         "params" : [ [ "value", "JsVar", "The value to check for"] ],
         "return" : ["JsVar", "the index of the value in the array, or -1"]
}*/
JsVar *jswrap_array_indexOf(JsVar *parent, JsVar *value) {
  JsVar *idxName = jsvGetArrayIndexOf(parent, value, false/*not exact*/);
  // but this is the name - we must turn it into a var
  if (idxName == 0) return jsvNewFromInteger(-1); // not found!
  JsVar *idx = jsvCopyNameOnly(idxName, false/* no children */, false/* Make sure this is not a name*/);
  jsvUnLock(idxName);
  return idx;
}

/*JSON{ "type":"method", "class": "Array", "name" : "join",
         "description" : "Join all elements of this array together into one string, using 'separator' between them. eg. ```[1,2,3].join(' ')=='1 2 3'```",
         "generate" : "jswrap_array_join",
         "params" : [ [ "separator", "JsVar", "The separator"] ],
         "return" : ["JsVar", "A String representing the Joined array"]
}*/
JsVar *jswrap_array_join(JsVar *parent, JsVar *filler) {
  if (jsvIsUndefined(filler))
    filler = jsvNewFromString(","); // the default it seems
  else
    filler = jsvAsString(filler, false);
  if (!filler) return 0; // out of memory
  JsVar *str = jsvArrayJoin(parent, filler);
  jsvUnLock(filler);
  return str;
}

/*JSON{ "type":"method", "class": "Array", "name" : "push",
         "description" : "Push a new value onto the end of this array'",
         "generate_full" : "jsvArrayPush(parent, value)",
         "params" : [ [ "value", "JsVar", "The value to add"] ],
         "return" : ["int", "The new size of the array"]
}*/

/*JSON{ "type":"method", "class": "Array", "name" : "pop",
         "description" : "Pop a new value off of the end of this array",
         "generate_full" : "jsvArrayPop(parent)",
         "return" : ["JsVar", "The value that is popped off"]
}*/

JsVar *_jswrap_array_map_or_forEach(JsVar *parent, JsVar *funcVar, JsVar *thisVar, bool isMap) {
  if (!jsvIsFunction(funcVar)) {
    jsError("Array.map's first argument should be a function");
    return 0;
  }
  if (!jsvIsUndefined(thisVar) && !jsvIsObject(thisVar)) {
    jsError("Arraymap's second argument should be undefined, or an object");
    return 0;
  }
  JsVar *array = 0;
  if (isMap)
    array = jsvNewWithFlags(JSV_ARRAY);
  if (array || !isMap) {
   JsVarRef childRef = parent->firstChild;
   while (childRef) {
     JsVar *child = jsvLock(childRef);
     if (jsvIsInt(child)) {
       JsVar *args[3], *mapped;
       args[0] = jsvLock(child->firstChild);
       // child is a variable name, create a new variable for the index
       args[1] = jsvNewFromInteger(jsvGetInteger(child));
       args[2] = parent;
       mapped = jspeFunctionCall(funcVar, 0, thisVar, false, 3, args);
       jsvUnLock(args[0]);
       jsvUnLock(args[1]);
       if (mapped) {
         if (isMap) {
           JsVar *name = jsvCopyNameOnly(child, false/*linkChildren*/, true/*keepAsName*/);
           if (name) { // out of memory?
             name->firstChild = jsvGetRef(jsvRef(mapped));
             jsvAddName(array, name);
             jsvUnLock(name);
           }
         }
         jsvUnLock(mapped);
       }
     }
     childRef = child->nextSibling;
     jsvUnLock(child);
   }
  }
  return array;
}

/*JSON{ "type":"method", "class": "Array", "name" : "map",
         "description" : "Return an array which is made from the following: ```A.map(function) = [function(A[0]), function(A[1]), ...]```",
         "generate" : "jswrap_array_map",
         "params" : [ [ "function", "JsVar", "Function used to map one item to another"] ,
                      [ "thisArg", "JsVar", "if specified, the function is called with 'this' set to thisArg (optional)"] ],
         "return" : ["JsVar", "The value that is popped off"]
}*/
JsVar *jswrap_array_map(JsVar *parent, JsVar *funcVar, JsVar *thisVar) {
  return _jswrap_array_map_or_forEach(parent, funcVar, thisVar, true);
}


/*JSON{ "type":"method", "class": "Array", "name" : "splice",
         "description" : "Both remove and add items to an array",
         "generate" : "jswrap_array_splice",
         "params" : [ [ "index", "int", "Index at which to start changing the array. If negative, will begin that many elements from the end"],
                      [ "howMany", "JsVar", "An integer indicating the number of old array elements to remove. If howMany is 0, no elements are removed."],
                      [ "element1", "JsVar", "A new item to add (optional)" ],
                      [ "element2", "JsVar", "A new item to add (optional)" ],
                      [ "element3", "JsVar", "A new item to add (optional)" ],
                      [ "element4", "JsVar", "A new item to add (optional)" ],
                      [ "element5", "JsVar", "A new item to add (optional)" ],
                      [ "element6", "JsVar", "A new item to add (optional)" ] ],
         "return" : ["JsVar", "An array containing the removed elements. If only one element is removed, an array of one element is returned."]
}*/
JsVar *jswrap_array_splice(JsVar *parent, JsVarInt index, JsVar *howManyVar, JsVar *element1, JsVar *element2, JsVar *element3, JsVar *element4, JsVar *element5, JsVar *element6) {
  JsVarInt len = jsvGetArrayLength(parent);
  if (index<0) index+=len;
  if (index<0) index=0;
  if (index>len) index=len;
  JsVarInt howMany = len; // how many to delete!
  if (jsvIsInt(howManyVar)) howMany = jsvGetInteger(howManyVar);
  if (howMany > len-index) howMany = len-index;
  JsVarInt newItems = 0;
  if (element1) newItems++;
  if (element2) newItems++;
  if (element3) newItems++;
  if (element4) newItems++;
  if (element5) newItems++;
  if (element6) newItems++;
  JsVarInt shift = newItems-howMany;

  bool needToAdd = false;
  JsVar *result = jsvNewWithFlags(JSV_ARRAY);

  JsArrayIterator it;
  jsvArrayIteratorNew(&it, parent);
  while (jsvArrayIteratorHasElement(&it) && !needToAdd) {
    bool goToNext = true;
    JsVar *idxVar = jsvArrayIteratorGetIndex(&it);
    if (idxVar && jsvIsInt(idxVar)) {
      JsVarInt idx = jsvGetInteger(idxVar);
      if (idx<index) {
        // do nothing...
      } else if (idx<index+howMany) { // must delete
        if (result) { // append to result array
          JsVar *el = jsvArrayIteratorGetElement(&it);
          jsvArrayPushAndUnLock(result, el);
        }
        // delete
        goToNext = false;
        JsVar *toRemove = jsvArrayIteratorGetIndex(&it);
        jsvArrayIteratorNext(&it);
        jsvRemoveChild(parent, toRemove);
        jsvUnLock(toRemove);
      } else { // we're greater than the amount we need to remove now
        needToAdd = true;
        goToNext = false;
      }
    }
    jsvUnLock(idxVar);
    if (goToNext) jsvArrayIteratorNext(&it);
  }
  // now we add everything
  JsVar *beforeIndex = jsvArrayIteratorGetIndex(&it);
  if (element1) jsvArrayInsertBefore(parent, beforeIndex, element1);
  if (element2) jsvArrayInsertBefore(parent, beforeIndex, element2);
  if (element3) jsvArrayInsertBefore(parent, beforeIndex, element3);
  if (element4) jsvArrayInsertBefore(parent, beforeIndex, element4);
  if (element5) jsvArrayInsertBefore(parent, beforeIndex, element5);
  if (element6) jsvArrayInsertBefore(parent, beforeIndex, element6);
  jsvUnLock(beforeIndex);
  // And finally renumber
  while (jsvArrayIteratorHasElement(&it)) {
      JsVar *idxVar = jsvArrayIteratorGetIndex(&it);
      if (idxVar && jsvIsInt(idxVar)) {
        jsvSetInteger(idxVar, jsvGetInteger(idxVar)+shift);
      }
      jsvUnLock(idxVar);
      jsvArrayIteratorNext(&it);
    }
  // free
  jsvArrayIteratorFree(&it);

  return result;
}


/*JSON{ "type":"method", "class": "Array", "name" : "slice",
         "description" : "Return a copy of a portion of the calling array",
         "generate" : "jswrap_array_slice",
         "params" : [ [ "start", "JsVar", "Start index"],
                      [ "end", "JsVar", "End index (optional)"] ],
         "return" : ["JsVar", "A new array"]
}*/
JsVar *jswrap_array_slice(JsVar *parent, JsVar *startVar, JsVar *endVar) {
  JsVarInt len = jsvGetArrayLength(parent);
  JsVarInt start = 0;
  JsVarInt end = len;

  if (!jsvIsUndefined(startVar))
    start = jsvGetInteger(startVar);

  if (!jsvIsUndefined(endVar))
    end = jsvGetInteger(endVar);

  JsVarInt k = 0;
  JsVarInt final = len;
  JsVar *array = jsvNewWithFlags(JSV_ARRAY);

  if (!array) return 0;

  if (start<0) k = max((len + start), 0);
  else k = min(start, len);

  if (end<0) final = max((len + end), 0);
  else final = min(end, len);

  bool isDone = false;

  JsArrayIterator it;
  jsvArrayIteratorNew(&it, parent);

  while (jsvArrayIteratorHasElement(&it) && !isDone) {
    JsVarInt idx = jsvGetInteger(jsvArrayIteratorGetIndex(&it));

    if (idx < k) {
      jsvArrayIteratorNext(&it);
    } else {
      if (k < final) {
        jsvArrayPushAndUnLock(array, jsvArrayIteratorGetElement(&it));
        jsvArrayIteratorNext(&it);
        k++;
      } else {
        isDone = true;
      }
    }
  }

  jsvArrayIteratorFree(&it);

  return array;
}


/*JSON{ "type":"method", "class": "Array", "name" : "forEach",
         "description" : "Executes a provided function once per array element.",
         "generate" : "jswrap_array_forEach",
         "params" : [ [ "function", "JsVar", "Function to be executed"] ,
                      [ "thisArg", "JsVar", "if specified, the function is called with 'this' set to thisArg (optional)"] ]
}*/
void jswrap_array_forEach(JsVar *parent, JsVar *funcVar, JsVar *thisVar) {
  _jswrap_array_map_or_forEach(parent, funcVar, thisVar, false);
}
