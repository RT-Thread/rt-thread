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
 * Variables
 * ----------------------------------------------------------------------------
 */
#include "jsvar.h"
#include "jslex.h"
#include "jsparse.h"
#include "jswrap_json.h"
#include "jsinteractive.h"
#include "jswrapper.h"


/** Basically, JsVars are stored in one big array, so save the need for
 * lots of memory allocation. On Linux, the arrays are in blocks, so that
 * more blocks can be allocated. We can't use realloc on one big block as
 * this may change the address of vars that are already locked!
 *
 */

#ifdef RESIZABLE_JSVARS
JsVar **jsVarBlocks = 0;
unsigned int jsVarsSize = 0;
#define JSVAR_BLOCK_SIZE 1024
#define JSVAR_BLOCK_SHIFT 10
#else
JsVar jsVars[JSVAR_CACHE_SIZE];
unsigned int jsVarsSize = JSVAR_CACHE_SIZE;
#endif

JsVarRef jsVarFirstEmpty; ///< reference of first unused variable (variables are in a linked list)

/** Return a pointer - UNSAFE for null refs.
 * This is effectively a Lock without locking! */
static inline JsVar *jsvGetAddressOf(JsVarRef ref) {
  assert(ref);
#ifdef RESIZABLE_JSVARS
  JsVarRef t = ref-1;
  return &jsVarBlocks[t>>JSVAR_BLOCK_SHIFT][t&(JSVAR_BLOCK_SIZE-1)];
#else
  return &jsVars[ref-1];
#endif
}

JsVar *_jsvGetAddressOf(JsVarRef ref) {
  return jsvGetAddressOf(ref);
}


// For debugging/testing ONLY - maximum # of vars we are allowed to use
void jsvSetMaxVarsUsed(unsigned int size) {
#ifdef RESIZABLE_JSVARS
  assert(size < JSVAR_BLOCK_SIZE); // remember - this is only for DEBUGGING - as such it doesn't use multiple blocks
#else
  assert(size < JSVAR_CACHE_SIZE);
#endif
  jsVarsSize = size;
}


// maps the empty variables in...
void jsvSoftInit() {
  jsVarFirstEmpty = 0;
  JsVar *lastEmpty = 0;
  JsVarRef i;
  for (i=1;i<=jsVarsSize;i++) {
    if ((jsvGetAddressOf(i)->flags&JSV_VARTYPEMASK) == JSV_UNUSED) {
      jsvGetAddressOf(i)->nextSibling = 0;
      if (lastEmpty)
        lastEmpty->nextSibling = i;
      else
        jsVarFirstEmpty = i;
      lastEmpty = jsvGetAddressOf(i);
    }
  }
}

void jsvSoftKill() {
}

/** This links all JsVars together, so we can have our nice
 * linked list of free JsVars. It returns the ref of the first
 * item - that we should set jsVarFirstEmpty to (if it is 0) */
static JsVarRef jsvInitJsVars(JsVarRef start, unsigned int count) {
  JsVarRef i;
  for (i=start;i<start+count;i++) {
    JsVar *v = jsvGetAddressOf(i);
    v->flags = JSV_UNUSED;
#ifdef LARGE_MEM
    v->this = i;
#endif
    // v->locks = 0; // locks is 0 anyway because it is stored in flags
    v->nextSibling = (JsVarRef)(i+1); // link to next
  }
  jsvGetAddressOf((JsVarRef)(start+count-1))->nextSibling = (JsVarRef)0; // set the final one to 0
  return start;
}

void jsvInit() {
#ifdef RESIZABLE_JSVARS
  jsVarsSize = JSVAR_BLOCK_SIZE;
  jsVarBlocks = malloc(sizeof(JsVar*)); // just 1
  jsVarBlocks[0] = malloc(sizeof(JsVar) * JSVAR_BLOCK_SIZE);
#endif

  jsVarFirstEmpty = jsvInitJsVars(1/*first*/, jsVarsSize);
  jsvSoftInit();
}

void jsvKill() {
#ifdef RESIZABLE_JSVARS

  unsigned int i;
  for (i=0;i<jsVarsSize>>JSVAR_BLOCK_SHIFT;i++)
    free(jsVarBlocks[i]);
  free(jsVarBlocks);
  jsVarBlocks = 0;
  jsVarsSize = 0;
#endif
}

/** Find or create the ROOT variable item - used mainly
 * if recovering from a saved state. */
JsVar *jsvFindOrCreateRoot() {
  JsVarRef i;
  for (i=1;i<=jsVarsSize;i++)
    if (jsvIsRoot(jsvGetAddressOf(i)))
      return jsvLock(i);

  return jsvRef(jsvNewWithFlags(JSV_ROOT));
}

/// Get number of memory records (JsVars) used
unsigned int jsvGetMemoryUsage() {
  unsigned int usage = 0;
  unsigned int i;
  for (i=1;i<=jsVarsSize;i++) {
    JsVar *v = jsvGetAddressOf((JsVarRef)i);
    if ((v->flags&JSV_VARTYPEMASK) != JSV_UNUSED)
      usage++;
  }
  return usage;
}

/// Get total amount of memory records
unsigned int jsvGetMemoryTotal() {
  return jsVarsSize;
}

/// Try and allocate more memory - only works if RESIZABLE_JSVARS is defined
void jsvSetMemoryTotal(unsigned int jsNewVarCount) {
#ifdef RESIZABLE_JSVARS
  if (jsNewVarCount <= jsVarsSize) return; // never allow us to have less!
  // When resizing, we just allocate a bunch more
  unsigned int oldSize = jsVarsSize;
  unsigned int oldBlockCount = jsVarsSize >> JSVAR_BLOCK_SHIFT;
  unsigned int newBlockCount = (jsNewVarCount+JSVAR_BLOCK_SIZE-1) >> JSVAR_BLOCK_SHIFT;
  jsVarsSize = newBlockCount << JSVAR_BLOCK_SHIFT;
  // resize block table
  jsVarBlocks = realloc(jsVarBlocks, sizeof(JsVar*)*newBlockCount);
  // allocate more blocks
  unsigned int i;
  for (i=oldBlockCount;i<newBlockCount;i++)
    jsVarBlocks[i] = malloc(sizeof(JsVar) * JSVAR_BLOCK_SIZE);
  /** and now reset all the newly allocated vars. We know jsVarFirstEmpty
   * is 0 (because jsiFreeMoreMemory returned 0) so we can just assign it.  */
  assert(!jsVarFirstEmpty);
  jsVarFirstEmpty = jsvInitJsVars(oldSize+1, jsVarsSize-oldSize);
  // jsiConsolePrintf("Resized memory from %d blocks to %d\n", oldBlockCount, newBlockCount);
#else
  NOT_USED(jsNewVarCount);
  assert(0);
#endif
}

/// Get whether memory is full or not
bool jsvIsMemoryFull() {
  return !jsVarFirstEmpty;
}

// Show what is still allocated, for debugging memory problems
void jsvShowAllocated() {
  JsVarRef i;
  for (i=1;i<=jsVarsSize;i++) {
    if ((jsvGetAddressOf(i)->flags&JSV_VARTYPEMASK) != JSV_UNUSED) {
      jsiConsolePrintf("USED VAR #%d:",i);
      jsvTrace(i, 2);
    }
  }
}

bool jsvHasCharacterData(const JsVar *v) {
  return jsvIsString(v) || jsvIsStringExt(v);
}

bool jsvHasStringExt(const JsVar *v) {
  return jsvIsString(v) || jsvIsStringExt(v);
}

bool jsvHasChildren(const JsVar *v) {
  return jsvIsFunction(v) || jsvIsObject(v) || jsvIsArray(v) || jsvIsRoot(v);
}

/// Is this variable a type that uses firstChild to point to a single Variable (ie. it doesn't have multiple children)
bool jsvHasSingleChild(const JsVar *v) {
  return jsvIsName(v) || jsvIsArrayBuffer(v) || jsvIsArrayBufferName(v);
}



JsVar *jsvNew() {
  if (jsVarFirstEmpty!=0) {
      JsVar *v = jsvLock(jsVarFirstEmpty);
      jsVarFirstEmpty = v->nextSibling; // move our reference to the next in the free list
      assert((v->flags&JSV_VARTYPEMASK) == JSV_UNUSED);
      // reset it
      v->refs = 0;
      //v->locks = 1;
      v->flags = JSV_LOCK_ONE;
      v->varData.callback = 0;
      v->firstChild = 0;
      v->lastChild = 0;
      v->prevSibling = 0;
      v->nextSibling = 0;
      // return pointer
      return v;
  }
  /* we don't have memort - second last hope - run garbage collector */
  if (jsvGarbageCollect())
    return jsvNew(); // if it freed something, continue
  /* we don't have memory - last hope - ask jsInteractive to try and free some it
   may have kicking around */
  if (jsiFreeMoreMemory())
    return jsvNew();
  /* We couldn't claim any more memory by Garbage collecting... */
#ifdef RESIZABLE_JSVARS
  jsvSetMemoryTotal(jsVarsSize*2);
  return jsvNew();
#else
  // On a micro, we're screwed.
  jsError("Out of Memory!");
  jspSetInterrupted(true);
  return 0;
#endif
}

void jsvFreePtr(JsVar *var) {
    /* To be here, we're not supposed to be part of anything else. If
     * we were, we'd have been freed by jsvGarbageCollect */
    assert(jsvIsStringExt(var) || (!var->nextSibling && !var->prevSibling));

    // Names that Link to other things
    if (jsvHasSingleChild(var)) {
      if (var->firstChild) {
        JsVar *child = jsvLock(var->firstChild);
        jsvUnRef(child); var->firstChild = 0; // unlink the child
        jsvUnLock(child); // unlock should trigger a free
      }
    }
    /* No else, because a String Name may have a single child, but
     * also StringExts  */

    /* Now, free children - see jsvar.h comments for how! */
    if (jsvHasStringExt(var)) {
      // TODO: make string free this non-recursive
      JsVarRef stringDataRef = var->lastChild;
      var->lastChild = 0;
      if (stringDataRef) {
        JsVar *child = jsvLock(stringDataRef);
        assert(jsvIsStringExt(child));
        jsvFreePtr(child);
        jsvUnLock(child);
      }
    } else if (jsvHasChildren(var)) {
      JsVarRef childref = var->firstChild;
      var->firstChild = 0;
      var->lastChild = 0;
      while (childref) {
        JsVar *child = jsvLock(childref);
        assert(jsvIsName(child));
        childref = child->nextSibling;
        child->prevSibling = 0;
        child->nextSibling = 0;
        jsvUnRef(child);
        jsvUnLock(child);
      }
    } else {
      assert(!var->firstChild);
      assert(!var->lastChild);
    }

    // free!
    var->flags = (var->flags & ~JSV_VARTYPEMASK) | JSV_UNUSED;
    // add this to our free list
    var->nextSibling = jsVarFirstEmpty;
    jsVarFirstEmpty = jsvGetRef(var);
}

/// Get a reference from a var - SAFE for null vars
JsVarRef jsvGetRef(JsVar *var) {
    if (!var) return 0;
#ifdef LARGE_MEM
    return var->this;
#else
 #ifdef RESIZABLE_JSVARS
    unsigned int i, c = jsVarsSize>>JSVAR_BLOCK_SHIFT;
    for (i=0;i<c;i++) {
      if (var>=jsVarBlocks[i] && var<&jsVarBlocks[i][JSVAR_BLOCK_SIZE]) {
        JsVarRef r = (JsVarRef)(1 + (i<<JSVAR_BLOCK_SHIFT) + (var - jsVarBlocks[i]));
        return r;
      }
    }
    return 0;
 #else
    return (JsVarRef)(1 + (var - jsVars));
 #endif
#endif
}

/// Lock this reference and return a pointer - UNSAFE for null refs
JsVar *jsvLock(JsVarRef ref) {
  JsVar *var = jsvGetAddressOf(ref);
  //var->locks++;
  assert(jsvGetLocks(var) < JSV_LOCK_MAX);
  var->flags += JSV_LOCK_ONE;
#ifdef DEBUG
  if (jsvGetLocks(var)==0) {
    jsError("Too many locks to Variable!");
    //jsPrint("Var #");jsPrintInt(ref);jsPrint("\n");
  }
#endif
  return var;
}

/// Lock this pointer and return a pointer - UNSAFE for null pointer
JsVar *jsvLockAgain(JsVar *var) {
  assert(var);
  assert(jsvGetLocks(var) < JSV_LOCK_MAX);
  var->flags += JSV_LOCK_ONE;
#ifdef DEBUG
  if (var->locks==0) {
    jsError("Too many locks to Variable!");
    //jsPrint("Var #");jsPrintInt(ref);jsPrint("\n");
  }
#endif
  return var;
}

/// Unlock this variable - this is SAFE for null variables
void jsvUnLock(JsVar *var) {
  if (!var) return;
  assert(jsvGetLocks(var)>0);
  var->flags -= JSV_LOCK_ONE;
  /* if we know we're free, then we can just free
   * this variable right now. Loops of variables
   * are handled by the Garbage Collector.
   * Note: we check var->refs first as it is fastest and most likely to be false */
  if (var->refs == 0 && jsvHasRef(var) && jsvGetLocks(var) == 0 && (var->flags&JSV_VARTYPEMASK)!=JSV_UNUSED) {
    jsvFreePtr(var);
  }
}

/// Reference - set this variable as used by something
JsVar *jsvRef(JsVar *v) {
  assert(v && jsvHasRef(v));
  v->refs++;
  return v;
}

/// Unreference - set this variable as not used by anything
void jsvUnRef(JsVar *var) {
  assert(var && var->refs>0 && jsvHasRef(var));
  var->refs--;
  // locks are never 0 here, so why bother checking!
  assert(jsvGetLocks(var)>0);
}

/// Helper fn, Reference - set this variable as used by something
JsVarRef jsvRefRef(JsVarRef ref) {
  JsVar *v;
  assert(ref);
  v = jsvLock(ref);
  assert(!jsvIsStringExt(v));
  jsvRef(v);
  jsvUnLock(v);
  return ref;
}

/// Helper fn, Unreference - set this variable as not used by anything
JsVarRef jsvUnRefRef(JsVarRef ref) {
  JsVar *v;
  assert(ref);
  v = jsvLock(ref);
  assert(!jsvIsStringExt(v));
  jsvUnRef(v);
  jsvUnLock(v);
  return 0;
}

JsVar *jsvNewFromString(const char *str) {
  // Create a var
  JsVar *first = jsvNewWithFlags(JSV_STRING);
  if (!first) {
    jsWarn("Unable to create string as not enough memory");
    return 0;
  }
  // Now we copy the string, but keep creating new jsVars if we go
  // over the end
  JsVar *var = jsvLockAgain(first);
  while (*str) {
    // copy data in
    size_t i, l = jsvGetMaxCharactersInVar(var);
    for (i=0;i<l && *str;i++)
      var->varData.str[i] = *(str++);
    // might as well shove a zero terminator on it if we can
    if (i<l) var->varData.str[i]=0;
    // we've stopped if the string was empty
    jsvSetCharactersInVar(var, i);

    // if there is still some left, it's because we filled up our var...
    // make a new one, link it in, and unlock the old one.
    if (*str) {
      JsVar *next = jsvNewWithFlags(JSV_STRING_EXT);
      if (!next) {
        jsWarn("Truncating string as not enough memory");
        jsvUnLock(var);
        return first;
      }
      // we don't ref, because  StringExts are never reffed as they only have one owner (and ALWAYS have an owner)
      var->lastChild = jsvGetRef(next);
      jsvUnLock(var);
      var = next;
    }
  }
  jsvUnLock(var);
  // return
  return first;
}

JsVar *jsvNewStringOfLength(unsigned int byteLength) {
  // Create a var
    JsVar *first = jsvNewWithFlags(JSV_STRING);
    if (!first) {
      jsWarn("Unable to create string as not enough memory");
      return 0;
    }
    // Now zero the string, but keep creating new jsVars if we go
    // over the end
    JsVar *var = jsvLockAgain(first);
    while (byteLength>0) {
      // copy data in
      size_t i, l = jsvGetMaxCharactersInVar(var);
      for (i=0;i<l && byteLength>0;i++,byteLength--)
        var->varData.str[i] = 0;
      // might as well shove a zero terminator on it if we can
      if (i<l) var->varData.str[i]=0;
      // we've stopped if the string was empty
      jsvSetCharactersInVar(var, i);

      // if there is still some left, it's because we filled up our var...
      // make a new one, link it in, and unlock the old one.
      if (byteLength>0) {
        JsVar *next = jsvNewWithFlags(JSV_STRING_EXT);
        if (!next) {
          jsWarn("Truncating string as not enough memory");
          jsvUnLock(var);
          return first;
        }
        // we don't ref, because  StringExts are never reffed as they only have one owner (and ALWAYS have an owner)
        var->lastChild = jsvGetRef(next);
        jsvUnLock(var);
        var = next;
      }
    }
    jsvUnLock(var);
    // return
    return first;
}

JsVar *jsvNewFromLexer(struct JsLex *lex, JslCharPos charFrom, JslCharPos charTo) {
  // Create a var
  JsVar *var = jsvNewFromEmptyString();
  if (!var) { // out of memory
    return 0;
  }

  jsvAppendStringVar(var, lex->sourceVar, charFrom, (JslCharPos)charTo-charFrom);
  return var;
}

JsVar *jsvNewWithFlags(JsVarFlags flags) {
  JsVar *var = jsvNew();
  if (!var) return 0; // no memory
  var->flags = (var->flags&(JsVarFlags)(~JSV_VARTYPEMASK)) | (flags&(JsVarFlags)(~JSV_LOCK_MASK));
  return var;
}
JsVar *jsvNewFromInteger(JsVarInt value) {
  JsVar *var = jsvNewWithFlags(JSV_INTEGER);
  if (!var) return 0; // no memory
  var->varData.integer = value;
  return var;
}
JsVar *jsvNewFromBool(bool value) {
  JsVar *var = jsvNewWithFlags(JSV_BOOLEAN);
  if (!var) return 0; // no memory
  var->varData.integer = value ? 1 : 0;
  return var;
}
JsVar *jsvNewFromFloat(JsVarFloat value) {
  JsVar *var = jsvNewWithFlags(JSV_FLOAT);
  if (!var) return 0; // no memory
  var->varData.floating = value;
  return var;
}
JsVar *jsvMakeIntoVariableName(JsVar *var, JsVar *valueOrZero) {
  if (!var) return 0;
  assert(var->refs==0); // make sure it's unused
  var->flags |= JSV_NAME;
  if (valueOrZero)
    var->firstChild = jsvGetRef(jsvRef(valueOrZero));
  return var;
}

JsVar *jsvNewFromPin(int pin) {
  JsVar *v = jsvNewFromInteger((JsVarInt)pin);
  if (v) {
    v->flags = (JsVarFlags)((v->flags & ~JSV_VARTYPEMASK) | JSV_PIN);
  }
  return v;
}

bool jsvIsBasicVarEqual(JsVar *a, JsVar *b) {
  // quick checks
  if (a==b) return true;
  if (!a || !b) return false; // one of them is undefined
  // OPT: would this be useful as compare instead?
  assert(jsvIsBasic(a) && jsvIsBasic(b));
  if (jsvIsNumeric(a) && jsvIsNumeric(b)) {
    if (jsvIsInt(a)) {
      if (jsvIsInt(b)) {
        return a->varData.integer == b->varData.integer;
      } else {
        assert(jsvIsFloat(b));
        return a->varData.integer == b->varData.floating;
      }
    } else {
      assert(jsvIsFloat(a));
      if (jsvIsInt(b)) {
        return a->varData.floating == b->varData.integer;
      } else {
        assert(jsvIsFloat(b));
        return a->varData.floating == b->varData.floating;
      }
    }
  } else if (jsvIsString(a) && jsvIsString(b)) {
    JsvStringIterator ita, itb;
    jsvStringIteratorNew(&ita, a, 0);
    jsvStringIteratorNew(&itb, b, 0);
    while (true) {
      char a = jsvStringIteratorGetChar(&ita);
      char b = jsvStringIteratorGetChar(&itb);
      if (a != b) {
        jsvStringIteratorFree(&ita);
        jsvStringIteratorFree(&itb);
        return false;
      }
      if (!a) { // equal, but end of string
        jsvStringIteratorFree(&ita);
        jsvStringIteratorFree(&itb);
        return true;
      }
      jsvStringIteratorNext(&ita);
      jsvStringIteratorNext(&itb);
    }
    // we never get here
    return false; // make compiler happy
  } else {
    //TODO: are there any other combinations we should check here?? String v int?
    return false;
  }
}

bool jsvIsEqual(JsVar *a, JsVar *b) {
  if (jsvIsBasic(a) && jsvIsBasic(b))
    return jsvIsBasicVarEqual(a,b);
  return jsvGetRef(a)==jsvGetRef(b);
}

/// Get a const string representing this variable - if we can. Otherwise return 0
const char *jsvGetConstString(const JsVar *v) {
    if (jsvIsUndefined(v)) {
      return "undefined";
    } else if (jsvIsNull(v)) {
      return "null";
    } else if (jsvIsBoolean(v)) {
      return jsvGetBool(v) ? "true" : "false";
    } else if (jsvIsRoot(v)) {
      return "[object Hardware]";
    } else if (jsvIsObject(v)) {
      return "[object Object]";
    }
    return 0;
}

/// Return the 'type' of the JS variable (eg. JS's typeof operator)
const char *jsvGetTypeOf(const JsVar *v) {
  if (jsvIsNull(v)) return "object";
  if (jsvIsUndefined(v)) return "undefined";
  if (jsvIsFunction(v)) return "function";
  if (jsvIsObject(v) || jsvIsArray(v)) return "object";
  if (jsvIsString(v)) return "string";
  if (jsvIsBoolean(v)) return "boolean";
  if (jsvIsNumeric(v)) return "number";
  return "?";
}

/// Save this var as a string to the given buffer, and return how long it was (return val doesn't include terminating 0)
size_t jsvGetString(const JsVar *v, char *str, size_t len) {
   const char *s = jsvGetConstString(v);
   if (s) {
     strncpy(str, s, len);
     return strlen(s);
   } else if (jsvIsInt(v)) {
     itoa(v->varData.integer, str, 10);
     return strlen(str);
   } else if (jsvIsFloat(v)) {
     ftoa(v->varData.floating, str);
     return strlen(str);
   } else if (jsvHasCharacterData(v)) {
       if (jsvIsStringExt(v))
         jsErrorInternal("Calling jsvGetString on a JSV_STRING_EXT");
      size_t l = len;
      JsvStringIterator it;
      jsvStringIteratorNewConst(&it, v, 0);
      while (jsvStringIteratorHasChar(&it)) {
        if (l--<=1) {
          *str = 0;
          jsWarn("jsvGetString overflowed\n");
          jsvStringIteratorFree(&it);
          return len;
        }
        *(str++) = jsvStringIteratorGetChar(&it);
        jsvStringIteratorNext(&it);
      }
      jsvStringIteratorFree(&it);
      *str = 0;
      return len-l;
    } else {
      // Try and get as a JsVar string, and try again
      JsVar *stringVar = jsvAsString((JsVar*)v, false); // we know we're casting to non-const here
      if (stringVar) {
        size_t l = jsvGetString(stringVar, str, len); // call again - but this time with converted var
        jsvUnLock(stringVar);
        return l;
      } else {
        strncpy(str, "", len);
        jsErrorInternal("Variable type cannot be converted to string");
        return 0;
      }
    }
}

/// Set the Data in this string. This must JUST overwrite - not extend or shrink
void jsvSetString(JsVar *v, char *str, size_t len) {
  assert(jsvHasCharacterData(v));
  assert(len == jsvGetStringLength(v));

  JsvStringIterator it;
  jsvStringIteratorNew(&it, v, 0);
  size_t i;
  for (i=0;i<len;i++) {
    jsvStringIteratorSetChar(&it, str[i]);
    jsvStringIteratorNext(&it);
  }
  jsvStringIteratorFree(&it);
}

/** If var is a string, lock and return it, else
 * create a new string. unlockVar means this will auto-unlock 'var'  */
JsVar *jsvAsString(JsVar *v, bool unlockVar) {
  JsVar *str = 0;
  // If it is string-ish, but not quite a string, copy it
  if (jsvHasCharacterData(v) && jsvIsName(v)) {
    str = jsvNewFromEmptyString();
    if (str) jsvAppendStringVarComplete(str,v);
  } else if (jsvIsString(v)) { // If it is a string - just return a reference
    str = jsvLockAgain(v);
  } else {
    const char *constChar = jsvGetConstString(v);
    if (constChar) {
      // if we could get this as a simple const char, do that..
      str = jsvNewFromString(constChar);
    } else if (jsvIsPin(v)) {
      char buf[8];
      jshGetPinString(buf, (Pin)v->varData.integer);
      str = jsvNewFromString(buf);
    } else if (jsvIsInt(v)) {
      char buf[JS_NUMBER_BUFFER_SIZE];
      itoa(v->varData.integer, buf, 10);
      str = jsvNewFromString(buf);
    } else if (jsvIsFloat(v)) {
      char buf[JS_NUMBER_BUFFER_SIZE];
      ftoa(v->varData.floating, buf);
      str = jsvNewFromString(buf);
    } else if (jsvIsArray(v) || jsvIsArrayBuffer(v)) {
      JsVar *filler = jsvNewFromString(",");
      str = jsvArrayJoin(v, filler);
      jsvUnLock(filler);
    } else if (jsvIsFunction(v)) {
      str = jsvNewFromEmptyString();
      if (str) jsfGetJSON(v, str);
    } else {
      jsErrorInternal("Variable type cannot be converted to string");
      str = 0;
    }
  }

  if (unlockVar) jsvUnLock(v);
  return str;
}

size_t jsvGetStringLength(JsVar *v) {
  size_t strLength = 0;
  JsVar *var = v;
  JsVarRef ref = 0;

  if (!jsvHasCharacterData(v)) return 0;

  while (var) {
    JsVarRef refNext = var->lastChild;
    strLength += jsvGetCharactersInVar(var);

    // Go to next
    if (ref) jsvUnLock(var); // note use of if (ref), not var
    ref = refNext;
    var = ref ? jsvLock(ref) : 0;
  }
  if (ref) jsvUnLock(var); // note use of if (ref), not var
  return strLength;
}

//  IN A STRING  get the number of lines in the string (min=1)
int jsvGetLinesInString(JsVar *v) {
  int lines = 1;
  JsvStringIterator it;
  jsvStringIteratorNew(&it, v, 0);
  while (jsvStringIteratorHasChar(&it)) {
    if (jsvStringIteratorGetChar(&it)=='\n') lines++;
    jsvStringIteratorNext(&it);
  }
  jsvStringIteratorFree(&it);
  return lines;
}

// IN A STRING Get the number of characters on a line - lines start at 1
int jsvGetCharsOnLine(JsVar *v, int line) {
  int currentLine = 1;
  int chars = 0;
  JsvStringIterator it;
  jsvStringIteratorNew(&it, v, 0);
  while (jsvStringIteratorHasChar(&it)) {
    if (jsvStringIteratorGetChar(&it)=='\n') {
      currentLine++;
      if (currentLine > line) break;
    } else if (currentLine==line) chars++;
    jsvStringIteratorNext(&it);
  }
  jsvStringIteratorFree(&it);
  return chars;
}

//  IN A STRING, get the line and column of the given character. Both values must be non-null
void jsvGetLineAndCol(JsVar *v, int charIdx, int* line, int *col) {
  int x = 1;
  int y = 1;
  int n = 0;
  assert(line && col);

  JsvStringIterator it;
  jsvStringIteratorNew(&it, v, 0);
  while (jsvStringIteratorHasChar(&it)) {
    char ch = jsvStringIteratorGetChar(&it);
    if (n==charIdx) {
      jsvStringIteratorFree(&it);
      *line = y;
      *col = x;
      return;
    }
    x++;
    if (ch=='\n') {
      x=1; y++;
    }
    n++;
    jsvStringIteratorNext(&it);
  }
  jsvStringIteratorFree(&it);
  // uh-oh - not found
  *line = y;
  *col = x;
}

//  IN A STRING, get a character index from a line and column
int jsvGetIndexFromLineAndCol(JsVar *v, int line, int col) {
  int x = 1;
  int y = 1;
  int n = 0;
  JsvStringIterator it;
  jsvStringIteratorNew(&it, v, 0);
  while (jsvStringIteratorHasChar(&it)) {
    char ch = jsvStringIteratorGetChar(&it);
    if ((y==line && x>=col) || y>line) {
      jsvStringIteratorFree(&it);
      return (y>line) ? (n-1) : n;
    }
    x++;
    if (ch=='\n') {
      x=1; y++;
    }
    n++;
    jsvStringIteratorNext(&it);
  }
  jsvStringIteratorFree(&it);
  return n;
}

void jsvAppendString(JsVar *var, const char *str) {
  assert(jsvIsString(var));
  JsVar *block = jsvLockAgain(var);
  // Find the block at end of the string...
  while (block->lastChild) {
    JsVarRef next = block->lastChild;
    jsvUnLock(block);
    block = jsvLock(next);
  }
  // find how full the block is
  size_t blockChars = jsvGetCharactersInVar(block);
  // now start appending
  while (*str) {
    // copy data in
    size_t i, l=jsvGetMaxCharactersInVar(block);
    for (i=blockChars;i<l && *str;i++) {
      block->varData.str[i] = *(str++);
    }
    jsvSetCharactersInVar(block, i);
    // if there is still some left, it's because we filled up our var...
    // make a new one, link it in, and unlock the old one.
    if (*str) {
      JsVar *next = jsvNewWithFlags(JSV_STRING_EXT);
      if (!next) break;
      // we don't ref, because  StringExts are never reffed as they only have one owner (and ALWAYS have an owner)
      block->lastChild = jsvGetRef(next);
      jsvUnLock(block);
      block = next;
      blockChars=0; // it's new, so empty
    }
  }
  jsvUnLock(block);
}

void jsvAppendStringBuf(JsVar *var, const char *str, int length) {
  assert(jsvIsString(var));
  JsVar *block = jsvLockAgain(var);
  // Find the block at end of the string...
  while (block->lastChild) {
    JsVarRef next = block->lastChild;
    jsvUnLock(block);
    block = jsvLock(next);
  }
  // find how full the block is
  size_t blockChars = jsvGetCharactersInVar(block);
  // now start appending
  while (length) {
    // copy data in
    size_t i, l=jsvGetMaxCharactersInVar(block);
    for (i=blockChars;i<l && length;i++) {
      block->varData.str[i] = *(str++);
      length--;
    }
    jsvSetCharactersInVar(block, i);
    // if there is still some left, it's because we filled up our var...
    // make a new one, link it in, and unlock the old one.
    if (length) {
      JsVar *next = jsvNewWithFlags(JSV_STRING_EXT);
      if (!next) break;
      // we don't ref, because  StringExts are never reffed as they only have one owner (and ALWAYS have an owner)
      block->lastChild = jsvGetRef(next);
      jsvUnLock(block);
      block = next;
      blockChars=0; // it's new, so empty
    }
  }
  jsvUnLock(block);
}

static void _jsvAppendPrintf(const char *str, void *user_data) {
  while (*str)
    jsvStringIteratorAppend((JsvStringIterator *)user_data, *(str++));
}

void jsvAppendPrintf(JsVar *var, const char *fmt, ...) {
  JsvStringIterator it;
  jsvStringIteratorNew(&it, var, 0);
  jsvStringIteratorGotoEnd(&it);

  va_list argp;
  va_start(argp, fmt);
  vcbprintf((vcbprintf_callback)&_jsvAppendPrintf,&it, fmt, argp);
  va_end(argp);

  jsvStringIteratorFree(&it);
}

/** Append str to var. Both must be strings. stridx = start char or str, maxLength = max number of characters (can be JSVAPPENDSTRINGVAR_MAXLENGTH).
 *  stridx can be negative to go from end of string */
void jsvAppendStringVar(JsVar *var, const JsVar *str, int stridx, int maxLength) {
  JsVar *block = jsvLockAgain(var);
  assert(jsvIsString(var));
  // Find the block at end of the string...
  while (block->lastChild) {
    JsVarRef next = block->lastChild;
    jsvUnLock(block);
    block = jsvLock(next);
  }
  // find how full the block is
  size_t blockChars = jsvGetCharactersInVar(block);
  // now start appending
  JsvStringIterator it;
  jsvStringIteratorNewConst(&it, str, stridx);
  while (jsvStringIteratorHasChar(&it) && (maxLength-->0)) {
    char ch = jsvStringIteratorGetChar(&it);
    if (blockChars >= jsvGetMaxCharactersInVar(block)) {
      jsvSetCharactersInVar(block, blockChars);
      JsVar *next = jsvNewWithFlags(JSV_STRING_EXT);
      if (!next) break; // out of memory
      // we don't ref, because  StringExts are never reffed as they only have one owner (and ALWAYS have an owner)
      block->lastChild = jsvGetRef(next);
      jsvUnLock(block);
      block = next;
      blockChars=0; // it's new, so empty
    }
    block->varData.str[blockChars++] = ch;
    jsvStringIteratorNext(&it);
  }
  jsvStringIteratorFree(&it);
  jsvSetCharactersInVar(block, blockChars);
  jsvUnLock(block);
}

/** Append all of str to var. Both must be strings.  */
void jsvAppendStringVarComplete(JsVar *var, const JsVar *str) {
  jsvAppendStringVar(var, str, 0, JSVAPPENDSTRINGVAR_MAXLENGTH);
}

char jsvGetCharInString(JsVar *v, int idx) {
  if (!jsvIsString(v)) return 0;
  if (idx<0) idx += (int)jsvGetStringLength(v); // <0 goes from end of string
  if (idx<0) return 0;

  JsvStringIterator it;
  jsvStringIteratorNew(&it, v, idx);
  char ch = jsvStringIteratorGetChar(&it);
  jsvStringIteratorFree(&it);
  return ch;
}

/** Does this string contain only Numeric characters? */
bool jsvIsStringNumeric(const JsVar *var) {
  assert(jsvIsString(var));
  JsvStringIterator it;
  jsvStringIteratorNewConst(&it, var, 0); // we know it's non const
  int chars = 0;
  while (jsvStringIteratorHasChar(&it)) {
    chars++;
    char ch = jsvStringIteratorGetChar(&it);
    if (!isNumeric(ch)) { // FIXME: should check for non-integer values (floating point?)
      jsvStringIteratorFree(&it);
      return false;
    }
    jsvStringIteratorNext(&it);
  }
  jsvStringIteratorFree(&it);
  return chars>0;
}

/** Does this string contain only Numeric characters? This is for arrays
 * and makes the assertion that int_to_string(string_to_int(var))==var */
bool jsvIsStringNumericStrict(const JsVar *var) {
  assert(jsvIsString(var));
  JsvStringIterator it;
  jsvStringIteratorNewConst(&it, var, 0);  // we know it's non const
  bool hadNonZero = false;
  bool hasLeadingZero = false;
  int chars = 0;
  while (jsvStringIteratorHasChar(&it)) {
    chars++;
    char ch = jsvStringIteratorGetChar(&it);
    if (!isNumeric(ch)) {
      // test for leading zero ensures int_to_string(string_to_int(var))==var
      jsvStringIteratorFree(&it);
      return false;
    }
    if (!hadNonZero && ch=='0') hasLeadingZero=true;
    if (ch!='0') hadNonZero=true;
    jsvStringIteratorNext(&it);
  }
  jsvStringIteratorFree(&it);
  return chars>0 && (!hasLeadingZero || chars==1);
}

JsVarInt jsvGetInteger(const JsVar *v) {
    if (!v) return 0; // undefined
    /* strtol understands about hex and octal */
    if (jsvIsInt(v) || jsvIsBoolean(v) || jsvIsPin(v) || jsvIsArrayBufferName(v)) return v->varData.integer;
    if (jsvIsNull(v)) return 0;
    if (jsvIsUndefined(v)) return 0;
    if (jsvIsFloat(v)) return (JsVarInt)v->varData.floating;
    if (jsvIsString(v) && jsvIsStringNumeric(v)) {
      char buf[32];
      jsvGetString(v, buf, sizeof(buf));
      return stringToInt(buf);
    }
    return 0;
}

void jsvSetInteger(JsVar *v, JsVarInt value) {
  assert(jsvIsInt(v));
  v->varData.integer  = value;
}

bool jsvGetBool(const JsVar *v) {
  return jsvGetInteger(v)!=0;
}

JsVarFloat jsvGetFloat(const JsVar *v) {
    if (!v) return NAN; // undefined
    if (jsvIsFloat(v)) return v->varData.floating;
    if (jsvIsInt(v)) return (JsVarFloat)v->varData.integer;
    if (jsvIsNull(v)) return 0;
    if (jsvIsString(v) && jsvIsStringNumeric(v)) {
      char buf[32];
      jsvGetString(v, buf, sizeof(buf));
      return stringToFloat(buf);
    }
    return NAN;
}

/// Convert the given variable to a number
JsVar *jsvAsNumber(JsVar *var) {
  if (jsvIsInt(var) || jsvIsFloat(var)) return jsvLockAgain(var);
  if (jsvIsBoolean(var) || jsvIsPin(var)) return jsvNewFromInteger(var->varData.integer);
  return jsvNewFromFloat(jsvGetFloat(var));
}

#ifdef SAVE_ON_FLASH
JsVarInt jsvGetIntegerAndUnLock(JsVar *v) { return _jsvGetIntegerAndUnLock(v); }
JsVarFloat jsvGetFloatAndUnLock(JsVar *v) { return _jsvGetFloatAndUnLock(v); }
bool jsvGetBoolAndUnLock(JsVar *v) { return _jsvGetBoolAndUnLock(v); }
#endif

/** Get the item at the given location in the array buffer and return the result */
size_t jsvGetArrayBufferLength(JsVar *arrayBuffer) {
  assert(jsvIsArrayBuffer(arrayBuffer));
  return arrayBuffer->varData.arraybuffer.length;
}

/** Get the item at the given location in the array buffer and return the result */
JsVar *jsvArrayBufferGet(JsVar *arrayBuffer, JsVarInt idx) {
  JsvArrayBufferIterator it;
  jsvArrayBufferIteratorNew(&it, arrayBuffer, idx);
  JsVar *v = jsvArrayBufferIteratorGetValue(&it);
  jsvArrayBufferIteratorFree(&it);
  return v;
}

/** Set the item at the given location in the array buffer */
void jsvArrayBufferSet(JsVar *arrayBuffer, JsVarInt idx, JsVar *value) {
  JsvArrayBufferIterator it;
  jsvArrayBufferIteratorNew(&it, arrayBuffer, idx);
  jsvArrayBufferIteratorSetValue(&it, value);
  jsvArrayBufferIteratorFree(&it);
}


/** Given an integer name that points to an arraybuffer or an arraybufferview, evaluate it and return the result */
JsVar *jsvArrayBufferGetFromName(JsVar *name) {
  assert(jsvIsArrayBufferName(name));
  JsVarInt idx = jsvGetInteger(name);
  JsVar *arrayBuffer = jsvLock(name->firstChild);
  JsVar *value = jsvArrayBufferGet(arrayBuffer, idx);
  jsvUnLock(arrayBuffer);
  return value;
}

/** If a is a name skip it and go to what it points to - and so on.
 * ALWAYS locks - so must unlock what it returns. It MAY
 * return 0. */
JsVar *jsvSkipName(JsVar *a) {
  JsVar *pa = a;
  if (!a) return 0;
  if (jsvIsArrayBufferName(pa)) return jsvArrayBufferGetFromName(pa);
  while (jsvIsName(pa)) {
    JsVarRef n = pa->firstChild;
    if (pa!=a) jsvUnLock(pa);
    if (!n) return 0;
    pa = jsvLock(n);
  }
  if (pa==a) jsvLockAgain(pa);
  return pa;
}

/** If a is a name skip it and go to what it points to.
 * ALWAYS locks - so must unlock what it returns. It MAY
 * return 0.  */
JsVar *jsvSkipOneName(JsVar *a) {
  JsVar *pa = a;
  if (!a) return 0;
  if (jsvIsArrayBufferName(pa)) return jsvArrayBufferGetFromName(pa);
  if (jsvIsName(pa)) {
    JsVarRef n = pa->firstChild;
    if (pa!=a) jsvUnLock(pa);
    if (!n) return 0;
    pa = jsvLock(n);
  }
  if (pa==a) jsvLockAgain(pa);
  return pa;
}

/** If a is a's child is a name skip it and go to what it points to.
 * ALWAYS locks - so must unlock what it returns.  */
JsVar *jsvSkipToLastName(JsVar *a) {
  assert(jsvIsName(a));
  a = jsvLockAgain(a);
  while (true) {
    if (!a->firstChild) return a;
    JsVar *child = jsvLock(a->firstChild);
    if (jsvIsName(child)) {
      jsvUnLock(a);
      a = child;
    } else {
      jsvUnLock(child);
      return a;
    }
  }
  return 0; // not called
}


// Also see jsvIsBasicVarEqual
bool jsvIsStringEqual(JsVar *var, const char *str) {
  if (!jsvHasCharacterData(var)) {
    assert(jsvIsBasic(var));
    return 0; // not a string so not equal!
  }

  JsvStringIterator it;
  jsvStringIteratorNew(&it, var, 0);
  while (jsvStringIteratorHasChar(&it) && *str) {
    if (jsvStringIteratorGetChar(&it) != *str) {
      jsvStringIteratorFree(&it);
      return false;
    }
    str++;
    jsvStringIteratorNext(&it);
  }
  bool eq = jsvStringIteratorGetChar(&it)==*str; // should both be 0 if equal
  jsvStringIteratorFree(&it);
  return eq;
}


/** Compare 2 strings, starting from the given character positions. equalAtEndOfString means that
 * if one of the strings ends, we treat them as equal.
 * For a basic strcmp, do: jsvCompareString(a,b,0,0,false)
 *  */
int jsvCompareString(JsVar *va, JsVar *vb, int starta, int startb, bool equalAtEndOfString) {
  JsvStringIterator ita, itb;
  jsvStringIteratorNew(&ita, va, starta);
  jsvStringIteratorNew(&itb, vb, startb);
   // step to first positions
  while (true) {
    int ca = jsvStringIteratorGetCharOrMinusOne(&ita);
    int cb = jsvStringIteratorGetCharOrMinusOne(&itb);

    if (ca != cb) {
      jsvStringIteratorFree(&ita);
      jsvStringIteratorFree(&itb);
      if ((ca<0 || cb<0) && equalAtEndOfString) return 0;
      return ca - cb;
    }
    if (ca < 0) { // both equal, but end of string
      jsvStringIteratorFree(&ita);
      jsvStringIteratorFree(&itb);
      return 0;
    }
    jsvStringIteratorNext(&ita);
    jsvStringIteratorNext(&itb);
  }
  // never get here, but the compiler warns...
  return true;
}

/** Compare 2 integers, >0 if va>vb,  <0 if va<vb. If compared with a non-integer, that gets put later */
int jsvCompareInteger(JsVar *va, JsVar *vb) {
  if (jsvIsInt(va) && jsvIsInt(vb))
    return (int)(jsvGetInteger(va) - jsvGetInteger(vb));
  else if (jsvIsInt(va))
    return -1;
  else if (jsvIsInt(vb))
    return 1;
  else
    return 0;
}

/** Copy only a name, not what it points to. ALTHOUGH the link to what it points to is maintained unless linkChildren=false
    If keepAsName==false, this will be converted into a normal variable */
JsVar *jsvCopyNameOnly(JsVar *src, bool linkChildren, bool keepAsName) {
  assert(jsvIsName(src));
  JsVarFlags flags = src->flags;
  if (!keepAsName) flags &= (JsVarFlags)~JSV_NAME; // make sure this is NOT a name
  JsVar *dst = jsvNewWithFlags(flags);
  if (!dst) return 0; // out of memory

  memcpy(&dst->varData, &src->varData, sizeof(JsVarData));

  dst->lastChild = 0;
  dst->firstChild = 0;
  dst->prevSibling = 0;
  dst->nextSibling = 0;
  // Copy LINK of what it points to
  if (linkChildren && src->firstChild) {
    dst->firstChild = jsvRefRef(src->firstChild);
  }
  // Copy extra string data if there was any
  if (jsvHasStringExt(src)) {
      // copy extra bits of string if there were any
      if (src->lastChild) {
        JsVar *child = jsvLock(src->lastChild);
        JsVar *childCopy = jsvCopy(child);
        if (childCopy) { // could be out of memory
          dst->lastChild = jsvGetRef(childCopy); // no ref for stringext
          jsvUnLock(childCopy);
        }
        jsvUnLock(child);
      }
  } else {
    assert(jsvIsBasic(src)); // in case we missed something!
  }
  return dst;
}

JsVar *jsvCopy(JsVar *src) {
  JsVar *dst = jsvNewWithFlags(src->flags);
  if (!dst) return 0; // out of memory
  if (!jsvIsStringExt(src)) {
    memcpy(&dst->varData, &src->varData, sizeof(JsVarData));
    dst->lastChild = 0;
    dst->firstChild = 0;
    dst->prevSibling = 0;
    dst->nextSibling = 0;
  } else {
    // stringexts use the extra pointers after varData to store characters
    // see jsvGetMaxCharactersInVar
    memcpy(&dst->varData, &src->varData, JSVAR_DATA_STRING_MAX_LEN);
    dst->lastChild = 0;
  }

  // Copy what names point to
  if (jsvIsName(src)) {
    if (src->firstChild) {
      JsVar *child = jsvLock(src->firstChild);
      JsVar *childCopy = jsvRef(jsvCopy(child));
      jsvUnLock(child);
      if (childCopy) { // could have been out of memory
        dst->firstChild = jsvGetRef(childCopy);
        jsvUnLock(childCopy);
      }
    }
  }

  if (jsvHasStringExt(src)) {
    // copy extra bits of string if there were any
    if (src->lastChild) {
      JsVar *child = jsvLock(src->lastChild);
      JsVar *childCopy = jsvCopy(child);
      if (childCopy) {// could be out of memory
        dst->lastChild = jsvGetRef(childCopy); // no ref for stringext
        jsvUnLock(childCopy);
      }
      jsvUnLock(child);
    }
  } else if (jsvHasChildren(src)) {
    // Copy children..
    JsVarRef vr;
    vr = src->firstChild;
    while (vr) {
      JsVar *name = jsvLock(vr);
      JsVar *child = jsvCopyNameOnly(name, true/*link children*/, true/*keep as name*/); // NO DEEP COPY!
      if (child) { // could have been out of memory
        jsvAddName(dst, child);
        jsvUnLock(child);
      }
      vr = name->nextSibling;
      jsvUnLock(name);
    }
  } else {
    assert(jsvIsBasic(src)); // in case we missed something!
  }

  return dst;
}

void jsvAddName(JsVar *parent, JsVar *namedChild) {
  namedChild = jsvRef(namedChild); // ref here VERY important as adding to structure!
  assert(jsvIsName(namedChild));

  if (parent->lastChild) { // we have children already
    JsVar *insertAfter = jsvLock(parent->lastChild);
    if (jsvIsArray(parent)) {
      // we must insert in order - so step back until we get the right place
      while (insertAfter && jsvCompareInteger(namedChild, insertAfter)<0) {
        JsVarRef prev = insertAfter->prevSibling;
        jsvUnLock(insertAfter);
        insertAfter = prev ? jsvLock(prev) : 0;
      }
    }

    if (insertAfter) {
      if (insertAfter->nextSibling) {
        // great, we're in the middle...
        JsVar *insertBefore = jsvLock(insertAfter->nextSibling);
        insertBefore->prevSibling = jsvGetRef(namedChild);
        namedChild->nextSibling = jsvGetRef(insertBefore);
        jsvUnLock(insertBefore);
      } else {
        // We're at the end - just set up the parent
        parent->lastChild = jsvGetRef(namedChild);
      }
      insertAfter->nextSibling = jsvGetRef(namedChild);
      namedChild->prevSibling = jsvGetRef(insertAfter);
      jsvUnLock(insertAfter);
    } else { // Insert right at the beginning of the array
      // Link 2 children together
      JsVar *firstChild = jsvLock(parent->firstChild);
      firstChild->prevSibling = jsvGetRef(namedChild);
      jsvUnLock(firstChild);

      namedChild->nextSibling = parent->firstChild;
      // finally set the new child as the first one
      parent->firstChild = jsvGetRef(namedChild);
    }
  } else { // we have no children - just add it
    parent->firstChild = parent->lastChild = jsvGetRef(namedChild);

  }
}

JsVar *jsvAddNamedChild(JsVar *parent, JsVar *child, const char *name) {
  JsVar *namedChild = jsvMakeIntoVariableName(jsvNewFromString(name), child);
  if (!namedChild) return 0; // Out of memory
  jsvAddName(parent, namedChild);
  return namedChild;
}

JsVar *jsvSetNamedChild(JsVar *parent, JsVar *child, const char *name) {
  JsVar *namedChild = jsvFindChildFromString(parent, name, true);
  if (namedChild) // could be out of memory
    return jsvSetValueOfName(namedChild, child);
  return 0;
}

JsVar *jsvSetValueOfName(JsVar *name, JsVar *src) {
  assert(name && jsvIsName(name));
  assert(name!=src); // no infinite loops!
  // all is fine, so replace the existing child...
  /* Existing child may be null in the case of Z = 0 where
   * we create 'Z' and pass it down to '=' to have the value
   * filled in (or it may be undefined). */
  if (name->firstChild) jsvUnRefRef(name->firstChild); // free existing
  if (src) {
      // we can link to a name if we want (so can remove the assert!)
      name->firstChild = jsvGetRef(jsvRef(src));
  } else
      name->firstChild = 0;
  return name;
}

JsVar *jsvFindChildFromString(JsVar *parent, const char *name, bool addIfNotFound) {
  /* Pull out first 4 bytes, and ensure that everything
   * is 0 padded so that we can do a nice speedy check. */
  char fastCheck[4];
  fastCheck[0] = name[0];
  if (name[0]) {
    fastCheck[1] = name[1];
    if (name[1]) {
      fastCheck[2] = name[2];
      if (name[2]) {
        fastCheck[3] = name[3];
      } else {
        fastCheck[3] = 0;
      }
    } else {
      fastCheck[2] = 0;
      fastCheck[3] = 0;
    }
  } else {
    fastCheck[1] = 0;
    fastCheck[2] = 0;
    fastCheck[3] = 0;
  }

  assert(jsvHasChildren(parent));
  JsVarRef childref = parent->firstChild;
  while (childref) {
    // Don't Lock here, just use GetAddressOf - to try and speed up the finding
    // TODO: We can do this now, but when/if we move to cacheing vars, it'll break
    JsVar *child = jsvGetAddressOf(childref);
    if (*(int*)fastCheck==*(int*)child->varData.str && // speedy check of first 4 bytes
        jsvIsStringEqual(child, name)) {
       // found it! unlock parent but leave child locked
       return jsvLockAgain(child);
    }
    childref = child->nextSibling;
  }

  JsVar *child = 0;
  if (addIfNotFound) {
    child = jsvMakeIntoVariableName(jsvNewFromString(name), 0);
    if (child) // could be out of memory
      jsvAddName(parent, child);
  }
  return child;
}

/** Non-recursive finding */
JsVar *jsvFindChildFromVar(JsVar *parent, JsVar *childName, bool addIfNotFound) {
  JsVar *child;
  JsVarRef childref = parent->firstChild;

  while (childref) {
    child = jsvLock(childref);
    if (jsvIsBasicVarEqual(child, childName)) {
      // found it! unlock parent but leave child locked
      return child;
    }
    childref = child->nextSibling;
    jsvUnLock(child);
  }

  child = 0;
  if (addIfNotFound && childName) {
    if (childName->refs == 0) {
      // Not reffed - great! let's just use it
      if (!jsvIsName(childName))
        childName = jsvMakeIntoVariableName(childName, 0);
      child = jsvLockAgain(childName);
    } else { // it was reffed, we must add a new one
      child = jsvMakeIntoVariableName(jsvCopy(childName), 0);
    }
    jsvAddName(parent, child);
  }
  return child;
}

void jsvRemoveChild(JsVar *parent, JsVar *child) {
    assert(jsvHasChildren(parent));
    JsVarRef childref = jsvGetRef(child);
    // unlink from parent
    if (parent->firstChild == childref)
        parent->firstChild = child->nextSibling;
    if (parent->lastChild == childref)
        parent->lastChild = child->prevSibling;
    // unlink from child list
    if (child->prevSibling) {
        JsVar *v = jsvLock(child->prevSibling);
        v->nextSibling = child->nextSibling;
        jsvUnLock(v);
    }
    if (child->nextSibling) {
        JsVar *v = jsvLock(child->nextSibling);
        v->prevSibling = child->prevSibling;
        jsvUnLock(v);
    }
    child->prevSibling = 0;
    child->nextSibling = 0;

    jsvUnRef(child);
}

void jsvRemoveAllChildren(JsVar *parent) {
    assert(jsvHasChildren(parent));
    while (parent->firstChild) {
      JsVar *v = jsvLock(parent->firstChild);
      jsvRemoveChild(parent, v);
      jsvUnLock(v);
    }
}

/// Get the named child of an object. If createChild!=0 then create the child
JsVar *jsvObjectGetChild(JsVar *obj, const char *name, JsVarFlags createChild) {
  if (!obj) return 0;
  assert(jsvHasChildren(obj));
  JsVar *childName = jsvFindChildFromString(obj, name, createChild);
  if (!childName && createChild) {
    JsVar *child = jsvNewWithFlags(createChild);
    jsvSetValueOfName(childName, child);
    jsvUnLock(childName);
    return child;
  }
  if (childName)
    return jsvSkipNameAndUnLock(childName);
  return 0;
}

/// Set the named child of an object, and return the child (so you can choose to unlock it if you want)
JsVar *jsvObjectSetChild(JsVar *obj, const char *name, JsVar *child) {
  assert(jsvHasChildren(obj));
  // child can actually be a name (for instance if it is a named function)
  JsVar *childName = jsvFindChildFromString(obj, name, true);
  if (!childName) return 0; // out of memory
  jsvSetValueOfName(childName, child);
  jsvUnLock(childName);
  return child;
}

int jsvGetChildren(JsVar *v) {
  //OPT: could length be stored as the value of the array?
  int children = 0;
  JsVarRef childref = v->firstChild;
  while (childref) {
    JsVar *child = jsvLock(childref);
    children++;
    childref = child->nextSibling;
    jsvUnLock(child);
  }
  return children;
}


JsVarInt jsvGetArrayLength(JsVar *arr) {
  JsVarRef childref = arr->lastChild;
  // Just look at last non-string element!
  while (childref) {
    JsVar *child = jsvLock(childref);
    if (jsvIsInt(child)) {
      JsVarInt lastIdx = jsvGetInteger(child);
      jsvUnLock(child);
      return lastIdx+1;
    }
    // if not an int, keep going
    childref = child->prevSibling;
    jsvUnLock(child);
  }
  return 0;
}

JsVarInt jsvGetLength(JsVar *src) {
  if (jsvIsArray(src)) {
    return jsvGetArrayLength(src);
  } else if (jsvIsArrayBuffer(src)) {
    return (JsVarInt)jsvGetArrayBufferLength(src);
  } else if (jsvIsString(src)) {
    return (JsVarInt)jsvGetStringLength(src);
  } else if (jsvIsObject(src) || jsvIsFunction(src)) {
      return jsvGetChildren(src);
  } else {
    return 1;
  }
}

/** Count the amount of JsVars used. Mostly useful for debugging */
size_t jsvCountJsVarsUsed(JsVar *v) {
  size_t count = 1;
  if (jsvHasChildren(v)) {
    JsVarRef childref = v->firstChild;
    while (childref) {
      JsVar *child = jsvLock(childref);
      count += jsvCountJsVarsUsed(child);
      childref = child->nextSibling;
      jsvUnLock(child);
    }
  }
  if (jsvHasCharacterData(v)) {
    size_t count = 0;
    JsVarRef childref = v->lastChild;
    while (childref) {
      JsVar *child = jsvLock(childref);
      count++;
      childref = child->lastChild;
      jsvUnLock(child);
    }
  }
  if (jsvIsName(v) && v->firstChild) {
    JsVar *child = jsvLock(v->firstChild);
    count += jsvCountJsVarsUsed(child);
    jsvUnLock(child);
  }
  return count;
}


JsVar *jsvGetArrayItem(JsVar *arr, int index) {
  JsVarRef childref = arr->firstChild;
  while (childref) {
    JsVarInt childIndex;
    JsVar *child = jsvLock(childref);

    assert(jsvIsInt(child));
    childIndex = jsvGetInteger(child);
    if (childIndex == index) {
      JsVar *item = child->firstChild ? jsvLock(child->firstChild) : 0;
      jsvUnLock(child);
      return item;
    }
    childref = child->nextSibling;
    jsvUnLock(child);
  }
  return 0; // undefined
}

/// Get the index of the value in the array (matchExact==use pointer, not equality check)
JsVar *jsvGetArrayIndexOf(JsVar *arr, JsVar *value, bool matchExact) {
  JsVarRef indexref;
  assert(jsvIsArray(arr) || jsvIsObject(arr));
  indexref = arr->firstChild;
  while (indexref) {
    JsVar *childIndex = jsvLock(indexref);
    assert(jsvIsName(childIndex))
    if (childIndex->firstChild) {
      JsVar *childValue = jsvLock(childIndex->firstChild);
      if ((matchExact && childValue==value) ||
          (!matchExact && jsvIsBasicVarEqual(childValue, value))) {
        jsvUnLock(childValue);
        return childIndex;
      }
      jsvUnLock(childValue);
    } else if (jsvIsUndefined(value))
      return childIndex; // both are undefined, so we return the index
    indexref = childIndex->nextSibling;
    jsvUnLock(childIndex);
  }
  return 0; // undefined
}

/// Adds new elements to the end of an array, and returns the new length. initialValue is the item index when no items are currently in the array.
JsVarInt jsvArrayPushWithInitialSize(JsVar *arr, JsVar *value, JsVarInt initialValue) {
  assert(jsvIsArray(arr));
  JsVarInt index = jsvGetArrayLength(arr);
  if (index==0) index=initialValue;
  JsVar *idx = jsvMakeIntoVariableName(jsvNewFromInteger(index), value);
  if (!idx) {
    jsWarn("Out of memory while appending to array");
    return 0;
  }
  jsvAddName(arr, idx);
  jsvUnLock(idx);
  return index+1; // new size
}

/// Adds new elements to the end of an array, and returns the new length
JsVarInt jsvArrayPush(JsVar *arr, JsVar *value) {
  return jsvArrayPushWithInitialSize(arr, value, 0);
}

/// Adds a new element to the end of an array, unlocks it, and returns the new length
JsVarInt jsvArrayPushAndUnLock(JsVar *arr, JsVar *value) {
  JsVarInt l = jsvArrayPushWithInitialSize(arr, value, 0);
  jsvUnLock(value);
  return l;
}

/// Removes the last element of an array, and returns that element (or 0 if empty). includes the NAME
JsVar *jsvArrayPop(JsVar *arr) {
  assert(jsvIsArray(arr));
  if (arr->lastChild) {
    JsVar *child = jsvLock(arr->lastChild);
    if (arr->firstChild == arr->lastChild)
      arr->firstChild = 0; // if 1 item in array
    arr->lastChild = child->prevSibling; // unlink from end of array
    jsvUnRef(child); // as no longer in array
    if (child->prevSibling) {
      JsVar *v = jsvLock(child->prevSibling);
      v->nextSibling = 0;
      jsvUnLock(v);
    }
    child->prevSibling = 0;
    return child; // and return it
  } else {
    // no children!
    return 0;
  }
}

/// Removes the first element of an array, and returns that element (or 0 if empty).
JsVar *jsvArrayPopFirst(JsVar *arr) {
  assert(jsvIsArray(arr));
  if (arr->firstChild) {
    JsVar *child = jsvLock(arr->firstChild);
    if (arr->firstChild == arr->lastChild)
      arr->lastChild = 0; // if 1 item in array
    arr->firstChild = child->nextSibling; // unlink from end of array
    jsvUnRef(child); // as no longer in array
    if (child->nextSibling) {
      JsVar *v = jsvLock(child->nextSibling);
      v->prevSibling = 0;
      jsvUnLock(v);
    }
    child->nextSibling = 0;
    return child; // and return it
  } else {
    // no children!
    return 0;
  }
}

///  Get the last element of an array (does not remove, unlike jsvArrayPop), and returns that element (or 0 if empty) includes the NAME
JsVar *jsvArrayGetLast(JsVar *arr) {
  assert(jsvIsArray(arr));
  if (arr->lastChild) {
    return jsvLock(arr->lastChild);
  } else { // no children!
    return 0;
  }
}

/// Join all elements of an array together into a string
JsVar *jsvArrayJoin(JsVar *arr, JsVar *filler) {
  JsVar *str = jsvNewFromEmptyString();
  if (!str) return 0; // out of memory

  JsVarInt index = 0;
  JsvIterator it;
  jsvIteratorNew(&it, arr);
  while (jsvIteratorHasElement(&it)) {
    JsVar *key = jsvIteratorGetKey(&it);
    if (jsvIsInt(key)) {
      JsVarInt thisIndex = jsvGetInteger(key);
      // add the filler
      if (filler) {
        while (index<thisIndex) {
          index++;
          jsvAppendStringVarComplete(str, filler);
        }
      }
      // add the value
      JsVar *value = jsvIteratorGetValue(&it);
      if (value) {
        JsVar *valueStr = jsvAsString(value, true /* UNLOCK */);
        if (valueStr) { // could be out of memory
          jsvAppendStringVarComplete(str, valueStr);
          jsvUnLock(valueStr);
        }
      }
    }
    jsvUnLock(key);
    jsvIteratorNext(&it);
  }
  jsvIteratorFree(&it);
  return str;
}

/// Insert a new element before beforeIndex, DOES NOT UPDATE INDICES
void jsvArrayInsertBefore(JsVar *arr, JsVar *beforeIndex, JsVar *element) {
  if (beforeIndex) {
    JsVar *idxVar = jsvMakeIntoVariableName(jsvNewFromInteger(0), element);
    if (!idxVar) return; // out of memory

    JsVarRef idxRef = jsvGetRef(jsvRef(idxVar));
    JsVarRef prev = beforeIndex->prevSibling;
    if (prev) {
      JsVar *prevVar = jsvRef(jsvLock(prev));
      jsvSetInteger(idxVar, jsvGetInteger(prevVar)+1); // update index number
      prevVar->nextSibling = idxRef;
      jsvUnLock(prevVar);
      idxVar->prevSibling = prev;
    } else {
      idxVar->prevSibling = 0;
      arr->firstChild = idxRef;
    }
    beforeIndex->prevSibling = idxRef;
    idxVar->nextSibling = jsvGetRef(jsvRef(beforeIndex));
    jsvUnLock(idxVar);
  } else
    jsvArrayPush(arr, element);
}

/** Same as jsvMathsOpPtr, but if a or b are a name, skip them
 * and go to what they point to. */
JsVar *jsvMathsOpSkipNames(JsVar *a, JsVar *b, int op) {
  JsVar *pa = jsvSkipName(a);
  JsVar *pb = jsvSkipName(b);
  JsVar *res = jsvMathsOp(pa,pb,op);
  jsvUnLock(pa);
  jsvUnLock(pb);
  return res;
}


JsVar *jsvMathsOpError(int op, const char *datatype) {
    char buf[JS_ERROR_BUF_SIZE];
    size_t bufpos = 0;
    strncpy(&buf[bufpos], "Operation ", JS_ERROR_BUF_SIZE-bufpos);
    bufpos=strlen(buf);
    jslTokenAsString(op, &buf[bufpos], JS_ERROR_TOKEN_BUF_SIZE-bufpos);
    bufpos=strlen(buf);
    strncat(&buf[bufpos], " not supported on the  ", JS_ERROR_BUF_SIZE-bufpos);
    bufpos=strlen(buf);
    strncat(&buf[bufpos], datatype, JS_ERROR_BUF_SIZE-bufpos);
    bufpos=strlen(buf);
    strncat(&buf[bufpos], " datatype", JS_ERROR_BUF_SIZE-bufpos);
    jsError(buf);
    return 0;
}

JsVar *jsvMathsOp(JsVar *a, JsVar *b, int op) {
    // Type equality check
    if (op == LEX_TYPEEQUAL || op == LEX_NTYPEEQUAL) {
      // check type first, then call again to check data
      bool eql = (a==0) == (b==0);
      if (a && b) eql = ((a->flags & JSV_VARTYPEMASK) ==
                         (b->flags & JSV_VARTYPEMASK));
      if (eql) {
        JsVar *contents = jsvMathsOp(a,b, LEX_EQUAL);
        if (!jsvGetBool(contents)) eql = false;
        jsvUnLock(contents);
      }
      if (op == LEX_TYPEEQUAL)
        return jsvNewFromBool(eql);
      else
        return jsvNewFromBool(!eql);
    }

    bool needsInt = op=='&' || op=='|' || op=='^' || op=='%' || op==LEX_LSHIFT || op==LEX_RSHIFT || op==LEX_RSHIFTUNSIGNED;
    bool needsNumeric = needsInt || op=='*' || op=='/' || op=='%' || op=='-';

    // do maths...
    if (jsvIsUndefined(a) && jsvIsUndefined(b)) {
      if (op == LEX_EQUAL)
        return jsvNewFromBool(true);
      else if (op == LEX_NEQUAL)
        return jsvNewFromBool(false);
      else
        return 0; // undefined
    } else if (needsNumeric ||
               ((jsvIsNumeric(a) || jsvIsUndefined(a) || jsvIsNull(a)) &&
                (jsvIsNumeric(b) || jsvIsUndefined(b) || jsvIsNull(b)))) {
      if (needsInt || !(jsvIsFloat(a) || jsvIsFloat(b))) {
            // use ints
            JsVarInt da = jsvGetInteger(a);
            JsVarInt db = jsvGetInteger(b);
            switch (op) {
                case '+': return jsvNewFromInteger(da+db);
                case '-': return jsvNewFromInteger(da-db);
                case '*': return jsvNewFromInteger(da*db);
                case '/': return jsvNewFromFloat((JsVarFloat)da/(JsVarFloat)db);
                case '&': return jsvNewFromInteger(da&db);
                case '|': return jsvNewFromInteger(da|db);
                case '^': return jsvNewFromInteger(da^db);
                case '%': return jsvNewFromInteger(da%db);
                case LEX_LSHIFT: return jsvNewFromInteger(da << db);
                case LEX_RSHIFT: return jsvNewFromInteger(da >> db);
                case LEX_RSHIFTUNSIGNED: return jsvNewFromInteger((JsVarInt)(((JsVarIntUnsigned)da) >> db));
                case LEX_EQUAL:     return jsvNewFromBool(da==db);
                case LEX_NEQUAL:    return jsvNewFromBool(da!=db);
                case '<':           return jsvNewFromBool(da<db);
                case LEX_LEQUAL:    return jsvNewFromBool(da<=db);
                case '>':           return jsvNewFromBool(da>db);
                case LEX_GEQUAL:    return jsvNewFromBool(da>=db);
                default: return jsvMathsOpError(op, "Integer");
            }
        } else {
            // use doubles
            JsVarFloat da = jsvGetFloat(a);
            JsVarFloat db = jsvGetFloat(b);
            switch (op) {
                case '+': return jsvNewFromFloat(da+db);
                case '-': return jsvNewFromFloat(da-db);
                case '*': return jsvNewFromFloat(da*db);
                case '/': return jsvNewFromFloat(da/db);
                case LEX_EQUAL:     return jsvNewFromBool(da==db);
                case LEX_NEQUAL:    return jsvNewFromBool(da!=db);
                case '<':           return jsvNewFromBool(da<db);
                case LEX_LEQUAL:    return jsvNewFromBool(da<=db);
                case '>':           return jsvNewFromBool(da>db);
                case LEX_GEQUAL:    return jsvNewFromBool(da>=db);
                default: return jsvMathsOpError(op, "Double");
            }
        }
    } else if ((jsvIsArray(a) || jsvIsObject(a) ||
                jsvIsArray(b) || jsvIsObject(b)) &&
                (op == LEX_EQUAL || op==LEX_NEQUAL)) {
      bool isArray = jsvIsArray(a);
      /* Just check pointers */
      switch (op) {
           case LEX_EQUAL:  return jsvNewFromBool(a==b);
           case LEX_NEQUAL: return jsvNewFromBool(a!=b);
           default: return jsvMathsOpError(op, isArray?"Array":"Object");
      }
    } else {
       JsVar *da = jsvAsString(a, false);
       JsVar *db = jsvAsString(b, false);
       if (!da || !db) { // out of memory
         jsvUnLock(da);
         jsvUnLock(db);
         return 0;
       }
       if (op=='+') {
         JsVar *v = jsvCopy(da);
         // TODO: can we be fancy and not copy da if we know it isn't reffed? what about locks?
         if (v) // could be out of memory
           jsvAppendStringVarComplete(v, db);
         jsvUnLock(da);
         jsvUnLock(db);
         return v;
       }

       int cmp = jsvCompareString(da,db,0,0,false);
       jsvUnLock(da);
       jsvUnLock(db);
       // use strings
       switch (op) {
           case LEX_EQUAL:     return jsvNewFromBool(cmp==0);
           case LEX_NEQUAL:    return jsvNewFromBool(cmp!=0);
           case '<':           return jsvNewFromBool(cmp<0);
           case LEX_LEQUAL:    return jsvNewFromBool(cmp<=0);
           case '>':           return jsvNewFromBool(cmp>0);
           case LEX_GEQUAL:    return jsvNewFromBool(cmp>=0);
           default: return jsvMathsOpError(op, "String");
       }
    }
}

JsVar *jsvNegateAndUnLock(JsVar *v) {
  JsVar *zero = jsvNewFromInteger(0);
  JsVar *res = jsvMathsOpSkipNames(zero, v, '-');
  jsvUnLock(zero);
  jsvUnLock(v);
  return res;
}

void jsvTraceLockInfo(JsVar *v) {
    jsiConsolePrintf("#%d[r%d,l%d] ",jsvGetRef(v),v->refs,jsvGetLocks(v)-1);
}

/** Get the lowest level at which searchRef appears */
int _jsvTraceGetLowestLevel(JsVarRef ref, JsVarRef searchRef) {
  if (ref == searchRef) return 0;
  int found = -1;
  JsVar *var = jsvLock(ref);

  // Use IS_RECURSING  flag to stop recursion
  if (var->flags & JSV_IS_RECURSING) {
    jsvUnLock(var);
    return -1;
  }
  var->flags |= JSV_IS_RECURSING;

  if (jsvHasSingleChild(var) && var->firstChild) {
    int f = _jsvTraceGetLowestLevel(var->firstChild, searchRef);
    if (f>=0 && (found<0 || f<found)) found=f+1;
  }
  if (jsvHasChildren(var)) {
    JsVarRef childRef = var->firstChild;
    while (childRef) {
      int f = _jsvTraceGetLowestLevel(childRef, searchRef);
      if (f>=0 && (found<0 || f<found)) found=f+1;

      JsVar *child = jsvLock(childRef);
      childRef = child->nextSibling;
      jsvUnLock(child);
    }
  }

  var->flags &= ~JSV_IS_RECURSING;
  jsvUnLock(var);

  return found; // searchRef not found
}

void _jsvTrace(JsVarRef ref, int indent, JsVarRef baseRef, int level) {
#ifdef SAVE_ON_FLASH
  jsiConsolePrint("Trace unimplemented in this version.\n");
#else
    int i;
    for (i=0;i<indent;i++) jsiConsolePrint(" ");

    if (!ref) {
        jsiConsolePrint("undefined\n");
        return;
    }
    /*jsiConsolePrint("<");
    jsiConsolePrintInt(level);
    jsiConsolePrint(":");
    jsiConsolePrintInt(_jsvTraceGetLowestLevel(baseRef, ref));
    jsiConsolePrint("> ");*/


    JsVar *var = jsvLock(ref);
    jsvTraceLockInfo(var);


    if (jsvIsName(var)) {
      if (jsvIsFunctionParameter(var))
        jsiConsolePrint("Param ");
      JsVar *str = jsvAsString(var, false);
      if (jsvIsInt(var)) {
        jsiConsolePrintf("Name: int %v  ", str);
      } else if (jsvIsFloat(var)) {
        jsiConsolePrintf("Name: flt %v  ", str);
      } else if (jsvIsString(var) || jsvIsFunctionParameter(var)) {
        jsiConsolePrintf("Name: '%v'  ", str);
      } else if (jsvIsArrayBufferName(var)) {
        jsiConsolePrintf("ArrayBufferName[%d] ", jsvGetInteger(var));
      } else {
        assert(0);
      }
      jsvUnLock(str);
      // go to what the name points to
      ref = var->firstChild;
      jsvUnLock(var);
      if (ref) {
        level++;
        int lowestLevel = _jsvTraceGetLowestLevel(baseRef, ref);
        /*jsiConsolePrint("<");
        jsiConsolePrintInt(level);
        jsiConsolePrint(":");
        jsiConsolePrintInt(lowestLevel);
        jsiConsolePrint("> ");*/

        var = jsvLock(ref);
        jsvTraceLockInfo(var);
        if (lowestLevel < level) {
          // If this data is available elsewhere in the tree (but nearer the root)
          // then don't print it. This makes the dump significantly more readable!
          // It also stops us getting in recursive loops ...
          jsiConsolePrint("...\n");
          jsvUnLock(var);
          return;
        }

      } else {
        jsiConsolePrint("undefined\n");
        return;
      }
    }

    if (jsvIsName(var)) {
      jsiConsolePrint("\n");
      _jsvTrace(jsvGetRef(var), indent+2, baseRef, level+1);
      jsvUnLock(var);
      return;
    }
    if (jsvIsObject(var)) jsiConsolePrint("Object {");
    else if (jsvIsArray(var)) jsiConsolePrint("Array [");
    else if (jsvIsPin(var)) jsiConsolePrint("Pin ");
    else if (jsvIsInt(var)) jsiConsolePrint("Integer ");
    else if (jsvIsBoolean(var)) jsiConsolePrint("Bool ");
    else if (jsvIsFloat(var)) jsiConsolePrint("Double ");
    else if (jsvIsString(var)) jsiConsolePrint("String ");
    else if (jsvIsArrayBuffer(var)) {
      jsiConsolePrintf("%s ", jswGetBasicObjectName(var)); // way to get nice name
      _jsvTrace(var->firstChild, indent+1, baseRef, level+1);
      jsvUnLock(var);
      return;
    } else if (jsvIsFunction(var)) jsiConsolePrint("Function {");
    else {
        jsiConsolePrintf("Flags %d\n", var->flags & (JsVarFlags)~(JSV_LOCK_MASK));
    }

    if (!jsvIsObject(var) && !jsvIsArray(var) && !jsvIsFunction(var)) {
      JsVar *str = jsvAsString(var, false);
      if (str) {
        JsvStringIterator it;
        jsvStringIteratorNew(&it, str, 0);
        while (jsvStringIteratorHasChar(&it)) {
          char ch = jsvStringIteratorGetChar(&it);
          jsiConsolePrint(escapeCharacter(ch));
          jsvStringIteratorNext(&it);
        }
        jsvStringIteratorFree(&it);
        jsvUnLock(str);
      }
    }

    if (jsvHasStringExt(var)) {
      if (!jsvIsStringExt(var) && var->firstChild) { // stringext don't have children (the use them for chars)
        jsiConsolePrint("( Multi-block string ");
        JsVarRef child = var->firstChild;
        while (child) {
          JsVar *childVar = jsvLock(child);
          jsvTraceLockInfo(childVar);
          child = childVar->firstChild;
          jsvUnLock(childVar);
        }
        jsiConsolePrint(")\n");
      } else
          jsiConsolePrint("\n");
    } else {
      JsVarRef child = var->firstChild;
      jsiConsolePrint("\n");
      // dump children
      while (child) {
        JsVar *childVar;
        _jsvTrace(child, indent+2, baseRef, level+1);
        childVar = jsvLock(child);
        child = childVar->nextSibling;
        jsvUnLock(childVar);
      }
    }

    if (jsvIsObject(var) || jsvIsFunction(var) || jsvIsArray(var)) {
      int i;
      for (i=0;i<indent;i++) jsiConsolePrint(" ");
      jsiConsolePrint(jsvIsArray(var) ? "]\n" : "}\n");
    }

    jsvUnLock(var);
#endif
}

/** Write debug info for this Var out to the console */
void jsvTrace(JsVarRef ref, int indent) {
  _jsvTrace(ref,indent,ref,0);
}


/** Recursively mark the variable */
static void jsvGarbageCollectMarkUsed(JsVar *var) {
  var->flags &= (JsVarFlags)~JSV_GARBAGE_COLLECT;

  if (jsvHasCharacterData(var)) {
      if (var->lastChild) {
        JsVar *childVar = jsvGetAddressOf(var->lastChild);
        if (childVar->flags & JSV_GARBAGE_COLLECT)
          jsvGarbageCollectMarkUsed(childVar);
      }
  }
  // intentionally no else
  if (jsvHasSingleChild(var)) {
    if (var->firstChild) {
      JsVar *childVar = jsvGetAddressOf(var->firstChild);
      if (childVar->flags & JSV_GARBAGE_COLLECT)
        jsvGarbageCollectMarkUsed(childVar);
    }
  } else if (jsvHasChildren(var)) {
    JsVarRef child = var->firstChild;
    while (child) {
      JsVar *childVar;
      childVar = jsvGetAddressOf(child);
      if (childVar->flags & JSV_GARBAGE_COLLECT)
        jsvGarbageCollectMarkUsed(childVar);
      child = childVar->nextSibling;
    }
  }
}

/** Run a garbage collection sweep - return true if things have been freed */
bool jsvGarbageCollect() {
  JsVarRef i;
  // clear garbage collect flags
  for (i=1;i<=jsVarsSize;i++)  {
    JsVar *var = jsvGetAddressOf(i);
    if ((var->flags&JSV_VARTYPEMASK) != JSV_UNUSED) // if it is not unused
      var->flags |= (JsVarFlags)JSV_GARBAGE_COLLECT;
  }
  // recursively add 'native' vars
  for (i=1;i<=jsVarsSize;i++)  {
      JsVar *var = jsvGetAddressOf(i);
    if ((var->flags & JSV_GARBAGE_COLLECT) && // not already GC'd
        jsvGetLocks(var)>0) // or it is locked
      jsvGarbageCollectMarkUsed(var);
  }
  // now sweep for things that we can GC!
  bool freedSomething = false;
  for (i=1;i<=jsVarsSize;i++)  {
    JsVar *var = jsvGetAddressOf(i);
    if (var->flags & JSV_GARBAGE_COLLECT) {
      freedSomething = true;
      // free!
      var->flags = JSV_UNUSED;
      // add this to our free list
      var->nextSibling = jsVarFirstEmpty;
      jsVarFirstEmpty = jsvGetRef(var);
    }
  }
  return freedSomething;
}

/** Remove whitespace to the right of a string - on MULTIPLE LINES */
JsVar *jsvStringTrimRight(JsVar *srcString) {
  JsvStringIterator src, dst;
  JsVar *dstString = jsvNewFromEmptyString();
  jsvStringIteratorNew(&src, srcString, 0);
  jsvStringIteratorNew(&dst, dstString, 0);
  int spaces = 0;
  while (jsvStringIteratorHasChar(&src)) {
    char ch = jsvStringIteratorGetChar(&src);
    jsvStringIteratorNext(&src);

    if (ch==' ') spaces++;
    else if (ch=='\n') {
      spaces = 0;
      jsvStringIteratorAppend(&dst, ch);
    } else {
      for (;spaces>0;spaces--)
        jsvStringIteratorAppend(&dst, ' ');
      jsvStringIteratorAppend(&dst, ch);
    }
  }
  jsvStringIteratorFree(&src);
  jsvStringIteratorFree(&dst);
  return dstString;
}

/// If v is the key of a function, return true if it is internal and shouldn't be visible to the user
bool jsvIsInternalFunctionKey(JsVar *v) {
  return (jsvIsString(v) && (
              v->varData.str[0]==JS_HIDDEN_CHAR)
                            ) ||
         jsvIsFunctionParameter(v);
}

/// If v is the key of an object, return true if it is internal and shouldn't be visible to the user
bool jsvIsInternalObjectKey(JsVar *v) {
  return (jsvIsString(v) && (
              v->varData.str[0]==JS_HIDDEN_CHAR ||
              jsvIsStringEqual(v, JSPARSE_INHERITS_VAR) ||
              jsvIsStringEqual(v, JSPARSE_CONSTRUCTOR_VAR)
                            ));
}

// --------------------------------------------------------------------------------------------

void jsvStringIteratorNew(JsvStringIterator *it, JsVar *str, int startIdx) {
  assert(jsvHasCharacterData(str));
  it->var = jsvLockAgain(str);
  it->charsInVar = jsvGetCharactersInVar(str);
  it->charIdx = (size_t)startIdx;
  it->index = (size_t)startIdx;
  while (it->charIdx>0 && it->charIdx >= it->charsInVar) {
    it->charIdx -= it->charsInVar;
    if (it->var) {
      if (it->var->lastChild) {
        JsVar *next = jsvLock(it->var->lastChild);
        jsvUnLock(it->var);
        it->var = next;
        it->charsInVar = jsvGetCharactersInVar(it->var);
      } else {
        jsvUnLock(it->var);
        it->var = 0;
        it->charsInVar = 0;
        return; // get out of loop
      }
    }
  }
}

void jsvStringIteratorNext(JsvStringIterator *it) {
  jsvStringIteratorNextInline(it);
}

void jsvStringIteratorGotoEnd(JsvStringIterator *it) {
  assert(it->var);
  while (it->var->lastChild) {
     it->index += it->charsInVar;
     JsVar *next = jsvLock(it->var->lastChild);
     jsvUnLock(it->var);
     it->var = next;
     it->charsInVar = jsvGetCharactersInVar(it->var);
   }
  if (it->charsInVar) it->charIdx = it->charsInVar-1;
  else it->charIdx = 0;
}

void jsvStringIteratorAppend(JsvStringIterator *it, char ch) {
  if (!it->var) return;
  if (it->charsInVar>0) {
    assert(it->charIdx+1 == it->charsInVar /* check at end */);
    it->charIdx++;
    it->index++;
  } else
    assert(it->charIdx == 0);
  if (it->charIdx >= jsvGetMaxCharactersInVar(it->var)) {
    assert(!it->var->lastChild);
    JsVar *next = jsvNewWithFlags(JSV_STRING_EXT);
    if (!next) return; // out of memory
    // we don't ref, because  StringExts are never reffed as they only have one owner (and ALWAYS have an owner)
    it->var->lastChild = jsvGetRef(next);
    jsvUnLock(it->var);
    it->var = next;

    it->charIdx = 0; // it's new, so empty
  }

  it->var->varData.str[it->charIdx] = ch;
  it->charsInVar = it->charIdx+1;
  jsvSetCharactersInVar(it->var, it->charsInVar);
}


// --------------------------------------------------------------------------------------------
void   jsvArrayBufferIteratorNew(JsvArrayBufferIterator *it, JsVar *arrayBuffer, JsVarInt index) {
  assert(jsvIsArrayBuffer(arrayBuffer));
  it->index = index;
  it->type = arrayBuffer->varData.arraybuffer.type;
  it->byteLength = arrayBuffer->varData.arraybuffer.length * JSV_ARRAYBUFFER_GET_SIZE(it->type);
  it->byteOffset = arrayBuffer->varData.arraybuffer.byteOffset;
  JsVar *arrayBufferData = jsvLock(arrayBuffer->firstChild);
  while (jsvIsArrayBuffer(arrayBufferData)) {
    JsVar *s = jsvLock(arrayBufferData->firstChild);
    jsvUnLock(arrayBufferData);
    arrayBufferData = s;
  }
  assert(jsvIsString(arrayBufferData));

  it->byteLength += it->byteOffset; // because we'll check if we have more bytes using this
  it->byteOffset = it->byteOffset + index*JSV_ARRAYBUFFER_GET_SIZE(it->type);
  if (it->byteOffset<0 || (it->byteLength>=0 && it->byteOffset>=(it->byteLength+1-JSV_ARRAYBUFFER_GET_SIZE(it->type)))) {
    jsvUnLock(arrayBufferData);
    it->type = ARRAYBUFFERVIEW_UNDEFINED;
    return;
  }
  jsvStringIteratorNew(&it->it, arrayBufferData, (int)it->byteOffset);
  jsvUnLock(arrayBufferData);
  it->hasAccessedElement = false;
}

static void jsvArrayBufferIteratorGetValueData(JsvArrayBufferIterator *it, char *data) {
  if (it->type == ARRAYBUFFERVIEW_UNDEFINED) return;
  assert(!it->hasAccessedElement); // we just haven't implemented this case yet
  unsigned int i,dataLen = JSV_ARRAYBUFFER_GET_SIZE(it->type);
  for (i=0;i<dataLen;i++) {
    data[i] = jsvStringIteratorGetChar(&it->it);
    if (dataLen!=1) jsvStringIteratorNext(&it->it);
  }
  if (dataLen!=1) it->hasAccessedElement = true;
}

static JsVarInt jsvArrayBufferIteratorDataToInt(JsvArrayBufferIterator *it, char *data) {
  unsigned int dataLen = JSV_ARRAYBUFFER_GET_SIZE(it->type);
  JsVarInt v = 0;
  if (dataLen==1) v = *(char*)data;
  else if (dataLen==2) v = *(short*)data;
  else if (dataLen==4) v = *(int*)data;
  else if (dataLen==8) v = *(long long*)data;
  else assert(0);
  if ((!JSV_ARRAYBUFFER_IS_SIGNED(it->type)) && v<0)
    v += 1 << (8*dataLen);
  return v;
}

static JsVarFloat jsvArrayBufferIteratorDataToFloat(JsvArrayBufferIterator *it, char *data) {
  unsigned int dataLen = JSV_ARRAYBUFFER_GET_SIZE(it->type);
  JsVarFloat v = 0;
  if (dataLen==4) v = *(float*)data;
  else if (dataLen==8) v = *(double*)data;
  else assert(0);
  return v;
}

JsVar *jsvArrayBufferIteratorGetValue(JsvArrayBufferIterator *it) {
  if (it->type == ARRAYBUFFERVIEW_UNDEFINED) return 0;
  char data[8];
  jsvArrayBufferIteratorGetValueData(it, data);
  if (JSV_ARRAYBUFFER_IS_FLOAT(it->type)) {
    return jsvNewFromFloat(jsvArrayBufferIteratorDataToFloat(it, data));
  } else {
    return jsvNewFromInteger(jsvArrayBufferIteratorDataToInt(it, data));
  }
}

JsVarInt jsvArrayBufferIteratorGetIntegerValue(JsvArrayBufferIterator *it) {
  if (it->type == ARRAYBUFFERVIEW_UNDEFINED) return 0;
  char data[8];
  jsvArrayBufferIteratorGetValueData(it, data);
  if (JSV_ARRAYBUFFER_IS_FLOAT(it->type)) {
    return (JsVarInt)jsvArrayBufferIteratorDataToFloat(it, data);
  } else {
    return jsvArrayBufferIteratorDataToInt(it, data);
  }
}

JsVarFloat jsvArrayBufferIteratorGetFloatValue(JsvArrayBufferIterator *it) {
  if (it->type == ARRAYBUFFERVIEW_UNDEFINED) return 0;
  char data[8];
  jsvArrayBufferIteratorGetValueData(it, data);
  if (JSV_ARRAYBUFFER_IS_FLOAT(it->type)) {
    return jsvArrayBufferIteratorDataToFloat(it, data);
  } else {
    return (JsVarFloat)jsvArrayBufferIteratorDataToInt(it, data);
  }
}

void   jsvArrayBufferIteratorSetValue(JsvArrayBufferIterator *it, JsVar *value) {
  if (it->type == ARRAYBUFFERVIEW_UNDEFINED) return;
  assert(!it->hasAccessedElement); // we just haven't implemented this case yet
  char data[8];
  unsigned int i,dataLen = JSV_ARRAYBUFFER_GET_SIZE(it->type);

  if (JSV_ARRAYBUFFER_IS_FLOAT(it->type)) {
    JsVarFloat v = jsvGetFloat(value);       ;
    if (dataLen==4) { float f = (float)v; memcpy(data,&f,dataLen); }
    else if (dataLen==8) { double f = (double)v; memcpy(data,&f,dataLen); }
    else assert(0);
  } else {
    JsVarInt v = jsvGetInteger(value);
    // we don't care about sign when writing - as it gets truncated
    if (dataLen==1) { char c = (char)v; memcpy(data,&c,dataLen); }
    else if (dataLen==2) { short c = (short)v; memcpy(data,&c,dataLen); }
    else if (dataLen==4) { int c = (int)v; memcpy(data,&c,dataLen); }
    else if (dataLen==8) { long long c = (long long)v; memcpy(data,&c,dataLen); }
    else assert(0);
  }

  for (i=0;i<dataLen;i++) {
    jsvStringIteratorSetChar(&it->it, data[i]);
    if (dataLen!=1) jsvStringIteratorNext(&it->it);
  }
  if (dataLen!=1) it->hasAccessedElement = true;
}

void   jsvArrayBufferIteratorSetIntegerValue(JsvArrayBufferIterator *it, JsVarInt value) {
  // FIXME: Do this without the allocation!
  JsVar *val = jsvNewFromInteger(value);
  jsvArrayBufferIteratorSetValue(it, val);
  jsvUnLock(val);
}

JsVar* jsvArrayBufferIteratorGetIndex(JsvArrayBufferIterator *it) {
  return jsvNewFromInteger(it->index);
}

bool   jsvArrayBufferIteratorHasElement(JsvArrayBufferIterator *it) {
  if (it->type == ARRAYBUFFERVIEW_UNDEFINED) return false;
  if (it->hasAccessedElement) return true;
  if (it->byteLength>=0)
    return it->byteOffset <= (it->byteLength-JSV_ARRAYBUFFER_GET_SIZE(it->type));
  else
    return jsvStringIteratorHasChar(&it->it);
}

void   jsvArrayBufferIteratorNext(JsvArrayBufferIterator *it) {
  it->index++;
  it->byteOffset += JSV_ARRAYBUFFER_GET_SIZE(it->type);
  if (!it->hasAccessedElement) {
    unsigned int i,dataLen = JSV_ARRAYBUFFER_GET_SIZE(it->type);
    for (i=0;i<dataLen;i++)
      jsvStringIteratorNext(&it->it);
  } else
    it->hasAccessedElement = false;
}

void   jsvArrayBufferIteratorFree(JsvArrayBufferIterator *it) {
  if (it->type == ARRAYBUFFERVIEW_UNDEFINED) return;
  jsvStringIteratorFree(&it->it);
}
// --------------------------------------------------------------------------------------------
/* General Purpose iterator, for Strings, Arrays, Objects, Typed Arrays */

void jsvIteratorNew(JsvIterator *it, JsVar *obj) {
  if (jsvIsArray(obj)) {
    it->type = JSVI_ARRAY;
    jsvArrayIteratorNew(&it->it.arr, obj);
  } else if (jsvIsObject(obj) || jsvIsFunction(obj)) {
    it->type = JSVI_OBJECT;
    jsvObjectIteratorNew(&it->it.obj, obj);
  } else if (jsvIsArrayBuffer(obj)) {
    it->type = JSVI_ARRAYBUFFER;
    jsvArrayBufferIteratorNew(&it->it.buf, obj, 0);
  } else if (jsvHasCharacterData(obj)) {
    it->type = JSVI_STRING;
    jsvStringIteratorNew(&it->it.str, obj, 0);
  } else assert(0);
}

JsVar *jsvIteratorGetKey(JsvIterator *it) {
  switch (it->type) {
  case JSVI_ARRAY : return jsvArrayIteratorGetIndex(&it->it.arr);
  case JSVI_OBJECT : return jsvObjectIteratorGetKey(&it->it.obj);
  case JSVI_STRING : return jsvNewFromInteger((JsVarInt)jsvStringIteratorGetIndex(&it->it.str));
  case JSVI_ARRAYBUFFER : return jsvArrayBufferIteratorGetIndex(&it->it.buf);
  default: assert(0); return 0;
  }
}

JsVar *jsvIteratorGetValue(JsvIterator *it) {
  switch (it->type) {
  case JSVI_ARRAY : return jsvArrayIteratorGetElement(&it->it.arr);
  case JSVI_OBJECT : return jsvObjectIteratorGetValue(&it->it.obj);
  case JSVI_STRING : { char buf[2] = {jsvStringIteratorGetChar(&it->it.str),0}; return jsvNewFromString(buf); }
  case JSVI_ARRAYBUFFER : return jsvArrayBufferIteratorGetValue(&it->it.buf);
  default: assert(0); return 0;
  }
}

JsVarInt jsvIteratorGetIntegerValue(JsvIterator *it) {
  switch (it->type) {
  case JSVI_ARRAY : return jsvGetIntegerAndUnLock(jsvArrayIteratorGetElement(&it->it.arr));
  case JSVI_OBJECT : return jsvGetIntegerAndUnLock(jsvObjectIteratorGetValue(&it->it.obj));
  case JSVI_STRING : return (JsVarInt)jsvStringIteratorGetChar(&it->it.str);
  case JSVI_ARRAYBUFFER : return jsvArrayBufferIteratorGetIntegerValue(&it->it.buf);
  default: assert(0); return 0;
  }
}

bool jsvIteratorHasElement(JsvIterator *it) {
  switch (it->type) {
  case JSVI_ARRAY : return jsvArrayIteratorHasElement(&it->it.arr);
  case JSVI_OBJECT : return jsvObjectIteratorHasElement(&it->it.obj);
  case JSVI_STRING : return jsvStringIteratorHasChar(&it->it.str);
  case JSVI_ARRAYBUFFER : return jsvArrayBufferIteratorHasElement(&it->it.buf);
  default: assert(0); return 0;
  }
}

void jsvIteratorNext(JsvIterator *it) {
  switch (it->type) {
  case JSVI_ARRAY : jsvArrayIteratorNext(&it->it.arr); break;
  case JSVI_OBJECT : jsvObjectIteratorNext(&it->it.obj); break;
  case JSVI_STRING : jsvStringIteratorNext(&it->it.str); break;
  case JSVI_ARRAYBUFFER : jsvArrayBufferIteratorNext(&it->it.buf); break;
  default: assert(0); break;
  }
}
void jsvIteratorFree(JsvIterator *it) {
  switch (it->type) {
  case JSVI_ARRAY : jsvArrayIteratorFree(&it->it.arr); break;
  case JSVI_OBJECT : jsvObjectIteratorFree(&it->it.obj); break;
  case JSVI_STRING : jsvStringIteratorFree(&it->it.str); break;
  case JSVI_ARRAYBUFFER : jsvArrayBufferIteratorFree(&it->it.buf); break;
  default: assert(0); break;
  }
}


