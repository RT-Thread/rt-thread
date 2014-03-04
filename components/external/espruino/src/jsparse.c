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
 * Recursive descent parser for code execution
 * ----------------------------------------------------------------------------
 */
#include "jsparse.h"
#include "jsinteractive.h"
#include "jswrapper.h"

/* Info about execution when Parsing - this saves passing it on the stack
 * for each call */
JsExecInfo execInfo;

// ----------------------------------------------- Forward decls
JsVar *jspeBase();
JsVar *jspeBaseWithComma();
JsVar *jspeBlock();
JsVar *jspeStatement();
// ----------------------------------------------- Utils
#define JSP_MATCH_WITH_CLEANUP_AND_RETURN(TOKEN, CLEANUP_CODE, RETURN_VAL) { if (!jslMatch(execInfo.lex,(TOKEN))) { jspSetError(); CLEANUP_CODE; return RETURN_VAL; } }
#define JSP_MATCH_WITH_RETURN(TOKEN, RETURN_VAL) JSP_MATCH_WITH_CLEANUP_AND_RETURN(TOKEN, , RETURN_VAL)
#define JSP_MATCH(TOKEN) JSP_MATCH_WITH_CLEANUP_AND_RETURN(TOKEN, , 0)
#define JSP_SHOULD_EXECUTE (((execInfo.execute)&EXEC_RUN_MASK)==EXEC_YES)
#define JSP_SAVE_EXECUTE() JsExecFlags oldExecute = execInfo.execute
#define JSP_RESTORE_EXECUTE() execInfo.execute = (execInfo.execute&(JsExecFlags)(~EXEC_SAVE_RESTORE_MASK)) | (oldExecute&EXEC_SAVE_RESTORE_MASK);
#define JSP_HAS_ERROR (((execInfo.execute)&EXEC_ERROR_MASK)!=0)

/// if interrupting execution, this is set
bool jspIsInterrupted() {
  return (execInfo.execute & EXEC_INTERRUPTED)!=0;
}

/// if interrupting execution, this is set
void jspSetInterrupted(bool interrupt) {
  if (interrupt)
    execInfo.execute = execInfo.execute | EXEC_INTERRUPTED;
  else
    execInfo.execute = execInfo.execute & (JsExecFlags)~EXEC_INTERRUPTED;
}

static inline void jspSetError() {
  execInfo.execute = (execInfo.execute & (JsExecFlags)~EXEC_YES) | EXEC_ERROR;
}

bool jspHasError() {
  return JSP_HAS_ERROR;
}

///< Same as jsvSetValueOfName, but nice error message
void jspReplaceWith(JsVar *dst, JsVar *src) {
  // If this is an index in an array buffer, write directly into the array buffer
  if (jsvIsArrayBufferName(dst)) {
    JsVarInt idx = jsvGetInteger(dst);
    JsVar *arrayBuffer = jsvLock(dst->firstChild);
    jsvArrayBufferSet(arrayBuffer, idx, src);
    jsvUnLock(arrayBuffer);
    return;
  }
  // if destination isn't there, isn't a 'name', or is used, give an error
  if (!jsvIsName(dst)) {
    jsErrorAt("Unable to assign value to non-reference", execInfo.lex, execInfo.lex->tokenLastEnd);
    jspSetError();
    return;
  }
  jsvSetValueOfName(dst, src);
}

void jspeiInit(JsParse *parse, JsLex *lex) {
  execInfo.parse = parse;
  execInfo.lex = lex;
  execInfo.scopeCount = 0;
  execInfo.execute = EXEC_YES;
}

void jspeiKill() {
  execInfo.parse = 0;
  execInfo.lex = 0;
  assert(execInfo.scopeCount==0);
}

bool jspeiAddScope(JsVarRef scope) {
  if (execInfo.scopeCount >= JSPARSE_MAX_SCOPES) {
    jsError("Maximum number of scopes exceeded");
    jspSetError();
    return false;
  }
  execInfo.scopes[execInfo.scopeCount++] = jsvRefRef(scope);
  return true;
}

void jspeiRemoveScope() {
  if (execInfo.scopeCount <= 0) {
    jsErrorInternal("Too many scopes removed");
    jspSetError();
    return;
  }
  jsvUnRefRef(execInfo.scopes[--execInfo.scopeCount]);
}

JsVar *jspeiFindInScopes(const char *name) {
  int i;
  for (i=execInfo.scopeCount-1;i>=0;i--) {
    JsVar *ref = jsvFindChildFromStringRef(execInfo.scopes[i], name, false);
    if (ref) return ref;
  }
  return jsvFindChildFromString(execInfo.parse->root, name, false);
}

JsVar *jspeiFindOnTop(const char *name, bool createIfNotFound) {
  if (execInfo.scopeCount>0)
    return jsvFindChildFromStringRef(execInfo.scopes[execInfo.scopeCount-1], name, createIfNotFound);
  return jsvFindChildFromString(execInfo.parse->root, name, createIfNotFound);
}
JsVar *jspeiFindNameOnTop(JsVar *childName, bool createIfNotFound) {
  if (execInfo.scopeCount>0)
    return jsvFindChildFromVarRef(execInfo.scopes[execInfo.scopeCount-1], childName, createIfNotFound);
  return jsvFindChildFromVar(execInfo.parse->root, childName, createIfNotFound);
}

/** Here we assume that we have already looked in the parent itself -
 * and are now going down looking at the stuff it inherited */
JsVar *jspeiFindChildFromStringInParents(JsVar *parent, const char *name) {
  if (jsvIsObject(parent)) {
    // If an object, look for an 'inherits' var
    JsVar *inheritsFrom = jsvObjectGetChild(parent, JSPARSE_INHERITS_VAR, 0);

    // if there's no inheritsFrom, just default to 'Object.prototype'
    if (!inheritsFrom) {
      JsVar *obj = jsvObjectGetChild(execInfo.parse->root, "Object", 0);
      if (obj) {
        inheritsFrom = jsvObjectGetChild(obj, JSPARSE_PROTOTYPE_VAR, 0);
        jsvUnLock(obj);
      }
    }

    if (inheritsFrom && inheritsFrom!=parent) {
      // we have what it inherits from (this is ACTUALLY the prototype var)
      // https://developer.mozilla.org/en-US/docs/JavaScript/Reference/Global_Objects/Object/proto
      JsVar *child = jsvFindChildFromString(inheritsFrom, name, false);
      if (!child)
        child = jspeiFindChildFromStringInParents(inheritsFrom, name);
      jsvUnLock(inheritsFrom);
      if (child) return child;
    }
  } else { // Not actually an object - but might be an array/string/etc
    const char *objectName = jswGetBasicObjectName(parent);
    while (objectName) {
      JsVar *objName = jsvFindChildFromString(execInfo.parse->root, objectName, false);
      if (objName) {
        JsVar *result = 0;
        JsVar *obj = jsvSkipNameAndUnLock(objName);
        if (obj) {
          // We have found an object with this name - search for the prototype var
          JsVar *proto = jsvObjectGetChild(obj, JSPARSE_PROTOTYPE_VAR, 0);
          if (proto) {
            result = jsvFindChildFromString(proto, name, false);
            jsvUnLock(proto);
          }
          jsvUnLock(obj);
        }
        if (result) return result;
      }
      /* We haven't found anything in the actual object, we should check the 'Object' itself
        eg, we tried 'String', so now we should try 'Object'. Built-in types don't have room for
        a prototype field, so we hard-code it */
      objectName = jswGetBasicObjectPrototypeName(objectName);
    }
  }

  // no luck!
  return 0;
}

JsVar *jspeiGetScopesAsVar() {
  if (execInfo.scopeCount==0) return 0;
  JsVar *arr = jsvNewWithFlags(JSV_ARRAY);
  int i;
  for (i=0;i<execInfo.scopeCount;i++) {
      //printf("%d %d\n",i,execInfo.scopes[i]);
      JsVar *scope = jsvLock(execInfo.scopes[i]);
      JsVar *idx = jsvMakeIntoVariableName(jsvNewFromInteger(i), scope);
      jsvUnLock(scope);
      if (!idx) { // out of memort
        jspSetError();
        return arr;
      }
      jsvAddName(arr, idx);
      jsvUnLock(idx);
  }
  //printf("%d\n",arr->firstChild);
  return arr;
}

void jspeiLoadScopesFromVar(JsVar *arr) {
    execInfo.scopeCount = 0;
    //printf("%d\n",arr->firstChild);
    JsVarRef childref = arr->firstChild;
    while (childref) {
      JsVar *child = jsvLock(childref);
      //printf("%d %d %d %d\n",execInfo.scopeCount,childref,child, child->firstChild);
      execInfo.scopes[execInfo.scopeCount] = jsvRefRef(child->firstChild);
      execInfo.scopeCount++;
      childref = child->nextSibling;
      jsvUnLock(child);
    }
}
// -----------------------------------------------
#ifdef ARM
extern int _end;
#endif
bool jspCheckStackPosition() {
#ifdef ARM
  void *frame = __builtin_frame_address(0);
  if ((char*)frame < ((char*)&_end)+1024/*so many bytes leeway*/) {
//   jsiConsolePrintf("frame: %d,end:%d\n",(int)frame,(int)&_end);
    jsErrorAt("Too much recursion - the stack is about to overflow", execInfo.lex, execInfo.lex->tokenStart );
    jspSetInterrupted(true);
    return false;
  }
#endif
  return true;
}


// Set execFlags such that we are not executing
void jspSetNoExecute() {
  execInfo.execute = (execInfo.execute & (JsExecFlags)(int)~EXEC_RUN_MASK) | EXEC_NO;
}

// parse single variable name
bool jspParseVariableName() {
  JSP_MATCH(LEX_ID);
  return true;
}

// parse function with no arguments
bool jspParseEmptyFunction() {
  JSP_MATCH(LEX_ID);
  JSP_MATCH('(');
  if (execInfo.lex->tk != ')')
    jsvUnLock(jspeBase());
  // throw away extra params
  while (!JSP_HAS_ERROR && execInfo.lex->tk != ')') {
    JSP_MATCH(',');
    jsvUnLock(jspeBase());
  }
  JSP_MATCH(')');
  return true;
}

// parse function with a single argument, return its value (no names!)
JsVar *jspParseSingleFunction() {
  JsVar *v = 0;
  JSP_MATCH(LEX_ID);
  JSP_MATCH('(');
  if (execInfo.lex->tk != ')')
    v = jsvSkipNameAndUnLock(jspeBase());
  // throw away extra params
  while (!JSP_HAS_ERROR && execInfo.lex->tk != ')') {
    JSP_MATCH_WITH_RETURN(',', v);
    jsvUnLock(jspeBase());
  }
  JSP_MATCH_WITH_RETURN(')', v);
  return v;
}

/// parse function with max 4 arguments (can set arg to 0 to avoid parse). Usually first arg will be 0, but if we DON'T want to skip names on an arg stuff, we can say
bool jspParseFunction(JspSkipFlags skipName, JsVar **a, JsVar **b, JsVar **c, JsVar **d) {
  if (a) *a = 0;
  if (b) *b = 0;
  if (c) *c = 0; 
  if (d) *d = 0;
  JSP_MATCH(LEX_ID);
  JSP_MATCH('(');
  if (a && execInfo.lex->tk != ')') {
    *a = jspeBase();
    if (!(skipName&JSP_NOSKIP_A)) *a = jsvSkipNameAndUnLock(*a);
  }
  if (b && execInfo.lex->tk != ')') {
    JSP_MATCH(',');
    *b = jspeBase();
    if (!(skipName&JSP_NOSKIP_B)) *b = jsvSkipNameAndUnLock(*b);
  }
  if (c && execInfo.lex->tk != ')') {
    JSP_MATCH(',');
    *c = jspeBase();
    if (!(skipName&JSP_NOSKIP_C)) *c = jsvSkipNameAndUnLock(*c);
  }
  if (d && execInfo.lex->tk != ')') {
    JSP_MATCH(',');
    *d = jspeBase();
    if (!(skipName&JSP_NOSKIP_D)) *d = jsvSkipNameAndUnLock(*d);
  }
  // throw away extra params
  while (!JSP_HAS_ERROR && execInfo.lex->tk != ')') {
    JSP_MATCH(',');
    jsvUnLock(jspeBase());
  }
  JSP_MATCH(')');
  return true;
}

/// parse function with max 8 arguments (can set arg to 0 to avoid parse). Usually first arg will be 0, but if we DON'T want to skip names on an arg stuff, we can say
bool jspParseFunction8(JspSkipFlags skipName, JsVar **a, JsVar **b, JsVar **c, JsVar **d, JsVar **e, JsVar **f, JsVar **g, JsVar **h) {
  if (a) *a = 0;
  if (b) *b = 0;
  if (c) *c = 0;
  if (d) *d = 0;
  if (e) *e = 0;
  if (f) *f = 0;
  if (g) *g = 0;
  if (h) *h = 0;
  JSP_MATCH(LEX_ID);
  JSP_MATCH('(');
  if (a && execInfo.lex->tk != ')') {
    *a = jspeBase();
    if (!(skipName&JSP_NOSKIP_A)) *a = jsvSkipNameAndUnLock(*a);
  }
  if (b && execInfo.lex->tk != ')') {
    JSP_MATCH(',');
    *b = jspeBase();
    if (!(skipName&JSP_NOSKIP_B)) *b = jsvSkipNameAndUnLock(*b);
  }
  if (c && execInfo.lex->tk != ')') {
    JSP_MATCH(',');
    *c = jspeBase();
    if (!(skipName&JSP_NOSKIP_C)) *c = jsvSkipNameAndUnLock(*c);
  }
  if (d && execInfo.lex->tk != ')') {
    JSP_MATCH(',');
    *d = jspeBase();
    if (!(skipName&JSP_NOSKIP_D)) *d = jsvSkipNameAndUnLock(*d);
  }
  if (e && execInfo.lex->tk != ')') {
    JSP_MATCH(',');
    *e = jspeBase();
    if (!(skipName&JSP_NOSKIP_E)) *e = jsvSkipNameAndUnLock(*e);
  }
  if (f && execInfo.lex->tk != ')') {
    JSP_MATCH(',');
    *f = jspeBase();
    if (!(skipName&JSP_NOSKIP_F)) *f = jsvSkipNameAndUnLock(*f);
  }
  if (g && execInfo.lex->tk != ')') {
    JSP_MATCH(',');
    *g = jspeBase();
    if (!(skipName&JSP_NOSKIP_G)) *g = jsvSkipNameAndUnLock(*g);
  }
  if (h && execInfo.lex->tk != ')') {
    JSP_MATCH(',');
    *h = jspeBase();
    if (!(skipName&JSP_NOSKIP_H)) *h = jsvSkipNameAndUnLock(*h);
  }
  // throw away extra params
  while (!JSP_HAS_ERROR && execInfo.lex->tk != ')') {
    JSP_MATCH(',');
    jsvUnLock(jspeBase());
  }
  JSP_MATCH(')');
  return true;
}

/// parse a function with any number of argument, and return an array of de-named aruments
JsVar *jspParseFunctionAsArray() {
  JSP_MATCH(LEX_ID);
  JsVar *arr = jsvNewWithFlags(JSV_ARRAY);
  if (!arr) return 0; // out of memory
  JSP_MATCH_WITH_CLEANUP_AND_RETURN('(', jsvUnLock(arr), 0);
  while (!JSP_HAS_ERROR && execInfo.lex->tk!=')' && execInfo.lex->tk!=LEX_EOF) {
    JsVar *arg = jsvSkipNameAndUnLock(jspeBase());
    jsvArrayPushAndUnLock(arr, arg); // even if undefined
    if (execInfo.lex->tk!=')') JSP_MATCH_WITH_CLEANUP_AND_RETURN(',', jsvUnLock(arr), 0);
  }
  JSP_MATCH_WITH_CLEANUP_AND_RETURN(')', jsvUnLock(arr), 0);
  return arr;
}

// ----------------------------------------------

// we return a value so that JSP_MATCH can return 0 if it fails (if we pass 0, we just parse all args)
bool jspeFunctionArguments(JsVar *funcVar) {
  JSP_MATCH('(');
  while (execInfo.lex->tk!=')') {
      if (funcVar) {
        JsVar *param = jsvAddNamedChild(funcVar, 0, jslGetTokenValueAsString(execInfo.lex));
        if (!param) { // out of memory
          jspSetError();
          return false;
        }
        param->flags |= JSV_FUNCTION_PARAMETER; // force this to be called a function parameter
        jsvUnLock(param);
      }
      JSP_MATCH(LEX_ID);
      if (execInfo.lex->tk!=')') JSP_MATCH(',');
  }
  JSP_MATCH(')');
  return true;
}

bool jspeParseNativeFunction(JsCallback callbackPtr) {
    char funcName[JSLEX_MAX_TOKEN_LENGTH];
    JsVar *funcVar;
    JsVar *base = jsvLockAgain(execInfo.parse->root);
    JSP_MATCH(LEX_R_FUNCTION);
    // not too bothered about speed/memory here as only called on init :)
    strncpy(funcName, jslGetTokenValueAsString(execInfo.lex), JSLEX_MAX_TOKEN_LENGTH);
    JSP_MATCH(LEX_ID);
    /* Check for dots, we might want to do something like function 'String.substring' ... */
    while (execInfo.lex->tk == '.') {
      JsVar *link;
      JSP_MATCH('.');
      link = jsvFindChildFromString(base, funcName, false);
      // if it doesn't exist, make a new object class
      if (!link) {
        JsVar *obj = jsvNewWithFlags(JSV_OBJECT);
        link = jsvAddNamedChild(base, obj, funcName);
        jsvUnLock(obj);
      }
      // set base to the object (not the name)
      jsvUnLock(base);
      base = jsvSkipNameAndUnLock(link);
      // Look for another name
      strncpy(funcName, jslGetTokenValueAsString(execInfo.lex), JSLEX_MAX_TOKEN_LENGTH);
      JSP_MATCH(LEX_ID);
    }
    // So now, base points to an object where we want our function
    funcVar = jsvNewWithFlags(JSV_FUNCTION | JSV_NATIVE);
    if (!funcVar) {
      jsvUnLock(base);
      jspSetError();
      return false; // Out of memory
    }
    funcVar->varData.callback = callbackPtr;
    jspeFunctionArguments(funcVar);

    if (JSP_HAS_ERROR) { // probably out of memory while parsing
      jsvUnLock(base);
      jsvUnLock(funcVar);
      return false;
    }
    // Add the function with its name
    JsVar *funcNameVar = jsvFindChildFromString(base, funcName, true);
    if (funcNameVar) // could be out of memory
      jsvUnLock(jsvSetValueOfName(funcNameVar, funcVar)); // unlocks funcNameVar
    jsvUnLock(base);
    jsvUnLock(funcVar);
    return true;
}

bool jspAddNativeFunction(JsParse *parse, const char *funcDesc, JsCallback callbackPtr) {
    JsVar *fncode = jsvNewFromString(funcDesc);
    if (!fncode) return false; // out of memory!

    JSP_SAVE_EXECUTE();
    JsExecInfo oldExecInfo = execInfo;

    // Set up Lexer

    JsLex lex;
    jslInit(&lex, fncode);
    jsvUnLock(fncode);

    
    jspeiInit(parse, &lex);

    // Parse
    bool success = jspeParseNativeFunction(callbackPtr);
    if (!success) {
      jsError("Parsing Native Function failed!");
      jspSetError();
    }


    // cleanup
    jspeiKill();
    jslKill(&lex);
    JSP_RESTORE_EXECUTE();
    oldExecInfo.execute = execInfo.execute; // JSP_RESTORE_EXECUTE has made this ok.
    execInfo = oldExecInfo;

    return success;
}

JsVar *jspeFunctionDefinition() {
  // actually parse a function... We assume that the LEX_FUNCTION and name
  // have already been parsed
  JsVar *funcVar = 0;
  if (JSP_SHOULD_EXECUTE)
    funcVar = jsvNewWithFlags(JSV_FUNCTION);
  // Get arguments save them to the structure
  if (!jspeFunctionArguments(funcVar)) {
    jsvUnLock(funcVar);
    // parse failed
    return 0;
  }
  // Get the code - first parse it so we know where it stops
  JslCharPos funcBegin = execInfo.lex->tokenStart;
  JSP_SAVE_EXECUTE();
  jspSetNoExecute();
  jsvUnLock(jspeBlock());
  JSP_RESTORE_EXECUTE();
  // Then create var and set
  if (JSP_SHOULD_EXECUTE) {
    // code var
    JsVar *funcCodeVar = jsvNewFromLexer(execInfo.lex, funcBegin, (JslCharPos)(execInfo.lex->tokenLastEnd+1));
    jsvUnLock(jsvAddNamedChild(funcVar, funcCodeVar, JSPARSE_FUNCTION_CODE_NAME));
    jsvUnLock(funcCodeVar);
    // scope var
    JsVar *funcScopeVar = jspeiGetScopesAsVar();
    if (funcScopeVar) {
      jsvUnLock(jsvAddNamedChild(funcVar, funcScopeVar, JSPARSE_FUNCTION_SCOPE_NAME));
      jsvUnLock(funcScopeVar);
    }
  }
  return funcVar;
}

/* Parse just the brackets of a function - and throw
 * everything away */
bool jspeParseFunctionCallBrackets() {
  JSP_MATCH('(');
  while (!JSP_HAS_ERROR && execInfo.lex->tk != ')') {
    jsvUnLock(jspeBase());
    if (execInfo.lex->tk!=')') JSP_MATCH(',');
  }
  if (!JSP_HAS_ERROR) JSP_MATCH(')');
  return 0;
}

/** Handle a function call (assumes we've parsed the function name and we're
 * on the start bracket). 'thisArg' is the value of the 'this' variable when the
 * function is executed (it's usually the parent object)
 *
 * If !isParsing and arg0!=0, argument 0 is set to what is supplied (same with arg1)
 *
 * functionName is used only for error reporting - and can be 0
 */
JsVar *jspeFunctionCall(JsVar *function, JsVar *functionName, JsVar *thisArg, bool isParsing, int argCount, JsVar **argPtr) {
  if (JSP_SHOULD_EXECUTE && !function) {
      jsErrorAt("Function not found! Skipping.", execInfo.lex, execInfo.lex->tokenLastStart );
      jspSetError();
  }

  if (JSP_SHOULD_EXECUTE) jspCheckStackPosition(); // try and ensure that we won't overflow our stack

  if (JSP_SHOULD_EXECUTE && function) {
    JsVar *functionRoot;
    JsVar *functionCode = 0;
    JsVar *returnVarName;
    JsVar *returnVar;
    JsVarRef v;
    if (!jsvIsFunction(function)) {
        char buf[JS_ERROR_BUF_SIZE];
        strncpy(buf, "Expecting a function to call", JS_ERROR_BUF_SIZE);
        const char *name = jswGetBasicObjectName(function);
        if (name) {
          strncat(buf, ", got a ", JS_ERROR_BUF_SIZE);
          strncat(buf, name, JS_ERROR_BUF_SIZE);
        }
        jsErrorAt(buf, execInfo.lex, execInfo.lex->tokenLastStart );
        jspSetError();
        return 0;
    }

    /** Special case - we're parsing and we hit an already-defined function
     * that has no 'code'. This means that we should use jswHandleFunctionCall
     * to try and parse it */
    if (!jsvIsNative(function)) {
      functionCode = jsvFindChildFromString(function, JSPARSE_FUNCTION_CODE_NAME, false);
      if (isParsing && !functionCode) {
        char buf[32];
        jsvGetString(functionName, buf, sizeof(buf));
        JslCharPos pos = execInfo.lex->tokenStart;
        jslSeekTo(execInfo.lex, execInfo.lex->tokenLastStart); // NASTY! because jswHandleFunctionCall expects to parse IDs
        JsVar *res = jswHandleFunctionCall(0, 0, buf);
        // but we didn't find anything - so just carry on...
        if (res!=JSW_HANDLEFUNCTIONCALL_UNHANDLED)
          return res;
        jslSeekTo(execInfo.lex, pos); // NASTY!
      }
    }

    if (isParsing) JSP_MATCH('(');
    // create a new symbol table entry for execution of this function
    // OPT: can we cache this function execution environment + param variables?
    // OPT: Probably when calling a function ONCE, use it, otherwise when recursing, make new?
    functionRoot = jsvNewWithFlags(JSV_FUNCTION);
    if (!functionRoot) { // out of memory
      jspSetError();
      return 0;
    }
    JsVar *oldThisVar = execInfo.thisVar;
    execInfo.thisVar = thisArg;
    if (isParsing) {
      int hadParams = 0;
      // grab in all parameters. We go around this loop until we've run out
      // of named parameters AND we've parsed all the supplied arguments
      v = function->firstChild;
      while (!JSP_HAS_ERROR && (v || execInfo.lex->tk!=')')) {
        JsVar *param = 0;
        if (v) param = jsvLock(v);
        bool paramDefined = jsvIsFunctionParameter(param);
        if (execInfo.lex->tk!=')' || paramDefined) {
          hadParams++;
          JsVar *value = 0;
          // ONLY parse this if it was supplied, otherwise leave 0 (undefined)
          if (execInfo.lex->tk!=')')
            value = jspeBase();
          // and if execute, copy it over
          if (JSP_SHOULD_EXECUTE) {
            value = jsvSkipNameAndUnLock(value);
            JsVar *paramName = paramDefined ? jsvCopy(param) : jsvNewFromEmptyString();
            paramName->flags |= JSV_FUNCTION_PARAMETER; // force this to be called a function parameter
            JsVar *newValueName = jsvMakeIntoVariableName(paramName, value);
            if (newValueName) { // could be out of memory
              jsvAddName(functionRoot, newValueName);
            } else
              jspSetError();
            jsvUnLock(newValueName);
          }
          jsvUnLock(value);
          if (execInfo.lex->tk!=')') JSP_MATCH(',');
        }
        if (param) {
          v = param->nextSibling;
          jsvUnLock(param);
        }
      }
      JSP_MATCH(')');
    } else if (JSP_SHOULD_EXECUTE && argCount>0) {  // and NOT isParsing
      int args = 0;
      v = function->firstChild;
      while (args<argCount) {
        JsVar *param = v ? jsvLock(v) : 0;
        bool paramDefined = jsvIsFunctionParameter(param);
        JsVar *paramName = paramDefined ? jsvCopy(param) : jsvNewFromEmptyString();
        paramName->flags |= JSV_FUNCTION_PARAMETER; // force this to be called a function parameter
        JsVar *newValueName = jsvMakeIntoVariableName(paramName, argPtr[args]);
        if (newValueName) // could be out of memory - or maybe just not supplied!
          jsvAddName(functionRoot, newValueName);
        jsvUnLock(newValueName);
        args++;
        if (param) {
          v = param->nextSibling;
          jsvUnLock(param);
        }
      }
    } 
    // setup a return variable
    returnVarName = jsvAddNamedChild(functionRoot, 0, JSPARSE_RETURN_VAR);
    if (!returnVarName) // out of memory
      jspSetError();
    //jsvTrace(jsvGetRef(functionRoot), 5); // debugging

    if (!JSP_HAS_ERROR) {
      if (jsvIsNative(function)) {
        assert(function->varData.callback);
        if (function->varData.callback)
          function->varData.callback(jsvGetRef(functionRoot));
      } else {
        // save old scopes
        JsVarRef oldScopes[JSPARSE_MAX_SCOPES];
        int oldScopeCount;
        int i;
        oldScopeCount = execInfo.scopeCount;
        for (i=0;i<execInfo.scopeCount;i++)
          oldScopes[i] = execInfo.scopes[i];
        // if we have a scope var, load it up. We may not have one if there were no scopes apart from root
        JsVar *functionScope = jsvFindChildFromString(function, JSPARSE_FUNCTION_SCOPE_NAME, false);
        if (functionScope) {
            JsVar *functionScopeVar = jsvLock(functionScope->firstChild);
            //jsvTrace(jsvGetRef(functionScopeVar),5);
            jspeiLoadScopesFromVar(functionScopeVar);
            jsvUnLock(functionScopeVar);
            jsvUnLock(functionScope);
        } else {
            // no scope var defined? We have no scopes at all!
            execInfo.scopeCount = 0;
        }
        // add the function's execute space to the symbol table so we can recurse
        if (jspeiAddScope(jsvGetRef(functionRoot))) {
          /* Adding scope may have failed - we may have descended too deep - so be sure
           * not to pull somebody else's scope off
           */

          /* we just want to execute the block, but something could
           * have messed up and left us with the wrong ScriptLex, so
           * we want to be careful here... */
          if (functionCode) {
            JsLex *oldLex;
            JsVar* functionCodeVar = jsvSkipNameAndUnLock(functionCode);
            JsLex newLex;
            jslInit(&newLex, functionCodeVar);
            jsvUnLock(functionCodeVar);

            oldLex = execInfo.lex;
            execInfo.lex = &newLex;
            JSP_SAVE_EXECUTE();
            jspeBlock();
            bool hasError = JSP_HAS_ERROR;
            JSP_RESTORE_EXECUTE(); // because return will probably have set execute to false
            jslKill(&newLex);
            execInfo.lex = oldLex;
            if (hasError) {
              jsiConsolePrint("in function ");
              if (jsvIsString(functionName)) {
                jsiConsolePrint("\"");
                jsiConsolePrintStringVar(functionName);
                jsiConsolePrint("\" ");
              }
              jsiConsolePrint("called from ");
              if (execInfo.lex)
                jsiConsolePrintPosition(execInfo.lex, execInfo.lex->tokenLastEnd);
              else
                jsiConsolePrint("system\n");
              jspSetError();
            }
          }

          jspeiRemoveScope();
        }

        // Unref old scopes
        for (i=0;i<execInfo.scopeCount;i++)
            jsvUnRefRef(execInfo.scopes[i]);
        // restore function scopes
        for (i=0;i<oldScopeCount;i++)
            execInfo.scopes[i] = oldScopes[i];
        execInfo.scopeCount = oldScopeCount;
      }
    }

    /* Return to old 'this' var. No need to unlock as we never locked before */
    execInfo.thisVar = oldThisVar;

    /* get the real return var before we remove it from our function */
    returnVar = jsvSkipNameAndUnLock(returnVarName);
    if (returnVarName) // could have failed with out of memory
      jsvSetValueOfName(returnVarName, 0); // remove return value (which helps stops circular references)
    jsvUnLock(functionRoot);
    if (returnVar)
      return returnVar;
    else
      return 0;
  } else if (isParsing) { // ---------------------------------- function, but not executing - just parse args and be done
    jspeParseFunctionCallBrackets();
    /* Do not return function, as it will be unlocked! */
    return 0;
  } else return 0;
}

JsVar *jspeFactorSingleId() {
  JsVar *a = JSP_SHOULD_EXECUTE ? jspeiFindInScopes(jslGetTokenValueAsString(execInfo.lex)) : 0;
  if (JSP_SHOULD_EXECUTE && !a) {
    const char *tokenName = jslGetTokenValueAsString(execInfo.lex); // BEWARE - this won't hang around forever!
    /* Special case! We haven't found the variable, so check out
     * and see if it's one of our builtins...  */
    if (jswIsBuiltInObject(tokenName)) {
      JsVar *obj = jspNewBuiltin(tokenName);
      if (obj) { // not out of memory
        a = jsvAddNamedChild(execInfo.parse->root, obj, tokenName);
        jsvUnLock(obj);
      }
    } else {
      a = jswHandleFunctionCall(0, 0, tokenName);
      if (a != JSW_HANDLEFUNCTIONCALL_UNHANDLED)
        return a;
      /* Variable doesn't exist! JavaScript says we should create it
       * (we won't add it here. This is done in the assignment operator)*/
      a = jsvMakeIntoVariableName(jslGetTokenValueAsVar(execInfo.lex), 0);
    }
  }
  JSP_MATCH_WITH_RETURN(LEX_ID, a);

  return a;
}

JsVar *jspeFactorMember(JsVar *a, JsVar **parentResult) {
  /* The parent if we're executing a method call */
  JsVar *parent = 0;

  while (execInfo.lex->tk=='.' || execInfo.lex->tk=='[') {
      if (execInfo.lex->tk == '.') { // ------------------------------------- Record Access
          JSP_MATCH('.');
          if (JSP_SHOULD_EXECUTE) {
            // Note: name will go away when we oarse something else!
            const char *name = jslGetTokenValueAsString(execInfo.lex);

            JsVar *aVar = jsvSkipName(a);
            JsVar *child = 0;
            if (aVar && jswGetBasicObjectName(aVar)) {
              // if we're an object (or pretending to be one)
              if (jsvHasChildren(aVar))
                child = jsvFindChildFromString(aVar, name, false);

              if (!child)
                child = jspeiFindChildFromStringInParents(aVar, name);


              if (child) {
                // it was found - no need for name ptr now, so match!
                JSP_MATCH_WITH_CLEANUP_AND_RETURN(LEX_ID, jsvUnLock(parent);jsvUnLock(a);, child);
              } else { // NOT FOUND...
                /* Check for builtins via separate function
                 * This way we save on RAM for built-ins because all comes out of program code.
                 *
                 * We don't check for prototype vars, so people can overload the built
                 * in functions (eg. Person.prototype.toString). HOWEVER if we did
                 * this for 'this' then we couldn't say 'this.toString()'
                 * */
                if (!jsvIsString(a) || (!jsvIsStringEqual(a, JSPARSE_PROTOTYPE_VAR))) // don't try and use builtins on the prototype var!
                  child = jswHandleFunctionCall(aVar, a/*name*/, name);
                else
                  child = JSW_HANDLEFUNCTIONCALL_UNHANDLED;
                if (child == JSW_HANDLEFUNCTIONCALL_UNHANDLED) {
                  child = 0;
                  // It wasn't handled... We already know this is an object so just add a new child
                  if (jsvIsObject(aVar) || jsvIsFunction(aVar) || jsvIsArray(aVar)) {
                    JsVar *value = 0;
                    if (jsvIsFunction(aVar) && strcmp(name, JSPARSE_PROTOTYPE_VAR)==0)
                      value = jsvNewWithFlags(JSV_OBJECT); // prototype is supposed to be an object
                    child = jsvAddNamedChild(aVar, value, name);
                    jsvUnLock(value);
                  } else {
                    // could have been a string...
                    jsErrorAt("Field or method does not already exist, and can't create it on a non-object", execInfo.lex, execInfo.lex->tokenLastEnd);
                    jspSetError();
                  }
                  JSP_MATCH_WITH_CLEANUP_AND_RETURN(LEX_ID, jsvUnLock(parent);jsvUnLock(a);, child);
                }
              }
            } else {
                jsErrorAt("Using '.' operator on non-object", execInfo.lex, execInfo.lex->tokenLastEnd);
                jspSetError();
                JSP_MATCH_WITH_CLEANUP_AND_RETURN(LEX_ID, jsvUnLock(parent);jsvUnLock(a);, child);
            }
            jsvUnLock(parent);
            parent = aVar;
            jsvUnLock(a);
            a = child;
          } else {
            // Not executing, just match
            JSP_MATCH_WITH_RETURN(LEX_ID, a);
          }
      } else if (execInfo.lex->tk == '[') { // ------------------------------------- Array Access
          JsVar *index;
          JSP_MATCH('[');
          index = jspeBase();
          JSP_MATCH_WITH_CLEANUP_AND_RETURN(']', jsvUnLock(parent);jsvUnLock(index);, a);
          if (JSP_SHOULD_EXECUTE) {
            /* Index filtering (bug #19) - if we have an array index A that is:
             is_string(A) && int_to_string(string_to_int(A)) = =A
             then convert it to an integer. Should be too nasty for performance
             as we only do this when accessing an array with a string */
            if (jsvIsString(index) && jsvIsStringNumericStrict(index)) {
              JsVar *v = jsvNewFromInteger(jsvGetInteger(index));
              jsvUnLock(index);
              index = v;
            }

            JsVar *aVar = jsvSkipName(a);
            if (aVar && (jsvIsArrayBuffer(aVar))) {
              // for array buffers, we actually create a NAME, and hand that back - then when we assign (or use SkipName) we pull out the correct data
              JsVar *indexValue = jsvSkipName(index);
              jsvUnLock(a);
              a = jsvMakeIntoVariableName(jsvNewFromInteger(jsvGetInteger(indexValue)), aVar);
              jsvUnLock(indexValue);
              if (a) // turn into an 'array buffer name'
                a->flags = (a->flags & ~(JSV_NAME|JSV_VARTYPEMASK)) | JSV_ARRAYBUFFERNAME;
            } else if (aVar && (jsvIsArray(aVar) || jsvIsObject(aVar) || jsvIsFunction(aVar))) {
                // TODO: If we set to undefined, maybe we should remove the name?
                JsVar *indexValue = jsvSkipName(index);
                if (!jsvIsString(indexValue) && !jsvIsNumeric(indexValue))
                  indexValue = jsvAsString(indexValue, true);
                JsVar *child = jsvFindChildFromVar(aVar, indexValue, true);
                jsvUnLock(indexValue);

                jsvUnLock(parent);
                parent = jsvLockAgain(aVar);
                jsvUnLock(a);
                a = child;
            } else if (aVar && (jsvIsString(aVar))) {
                JsVarInt idx = jsvGetIntegerAndUnLock(jsvSkipName(index));
                JsVar *child = 0;
                if (idx>=0 && idx<(JsVarInt)jsvGetStringLength(aVar)) {
                  char ch = jsvGetCharInString(aVar, (int)idx);
                  child = jsvNewFromEmptyString();
                  if (child) jsvAppendStringBuf(child, &ch, 1);
                }
                jsvUnLock(parent);
                parent = jsvLockAgain(aVar);
                jsvUnLock(a);
                a = child;
            } else {
                jsWarnAt("Variable is not an Array or Object", execInfo.lex, execInfo.lex->tokenLastEnd);
                jsvUnLock(parent);
                parent = 0;
                jsvUnLock(a);
                a = 0;
            }
            jsvUnLock(aVar);
          }
          jsvUnLock(index);
      } else {
        assert(0);
      }
  }

  if (parentResult) *parentResult = parent;
  else jsvUnLock(parent);
  return a;
}

JsVar *jspeFactor();
void jspEnsureIsPrototype(JsVar *prototypeName);

JsVar *jspeConstruct(JsVar *func, JsVar *funcName, bool hasArgs) {
  assert(JSP_SHOULD_EXECUTE);
  if (!jsvIsFunction(func)) {
    jsErrorAt("Constructor should be a function", execInfo.lex, execInfo.lex->tokenLastEnd);
    jspSetError();
    return 0;
  }

  JsVar *thisObj = jsvNewWithFlags(JSV_OBJECT);
  // Make sure the function has a 'prototype' var
  JsVar *prototypeName = jsvFindChildFromString(func, JSPARSE_PROTOTYPE_VAR, true);
  jspEnsureIsPrototype(prototypeName); // make sure it's an object
  jsvUnLock(jsvAddNamedChild(thisObj, prototypeName, JSPARSE_INHERITS_VAR));
  jsvUnLock(prototypeName);

  JsVar *a = jspeFunctionCall(func, funcName, thisObj, hasArgs, 0, 0);

  if (a) {
    jsvUnLock(thisObj);
    thisObj = a;
  } else {
    jsvUnLock(a);
    JsVar *constructor = jsvFindChildFromString(thisObj, JSPARSE_CONSTRUCTOR_VAR, true);
    if (constructor) {
      jsvSetValueOfName(constructor, funcName);
      jsvUnLock(constructor);
    }
  }
  return thisObj;
}

JsVar *jspeFactorFunctionCall() {
  /* The parent if we're executing a method call */
  bool isConstructor = false;
  if (execInfo.lex->tk==LEX_R_NEW) {
    JSP_MATCH(LEX_R_NEW);
    isConstructor = true;

    if (execInfo.lex->tk==LEX_R_NEW) {
      jsError("Nesting 'new' operators is unsupported");
      jspSetError();
      return 0;
    }
  }

  JsVar *parent = 0;
  JsVar *a = jspeFactorMember(jspeFactor(), &parent);

  while (execInfo.lex->tk=='(' || (isConstructor && JSP_SHOULD_EXECUTE)) {
    JsVar *funcName = a;
    JsVar *func = jsvSkipName(funcName);

    /* The constructor function doesn't change parsing, so if we're
     * not executing, just short-cut it. */
    if (isConstructor && JSP_SHOULD_EXECUTE) {
      // If we have '(' parse an argument list, otherwise don't look for any args
      bool parseArgs = execInfo.lex->tk=='(';
      a = jspeConstruct(func, funcName, parseArgs);
      isConstructor = false; // don't treat subsequent brackets as constructors
    } else
      a = jspeFunctionCall(func, funcName, parent, true, 0, 0);

    jsvUnLock(funcName);
    jsvUnLock(func);

    jsvUnLock(parent); parent=0;
    a = jspeFactorMember(a, &parent);
  }

  jsvUnLock(parent);
  return a;
}

JsVar *jspeFactorId() {
  return jspeFactorSingleId();
}


JsVar *jspeFactorObject() {
  if (JSP_SHOULD_EXECUTE) {
    JsVar *contents = jsvNewWithFlags(JSV_OBJECT);
    if (!contents) { // out of memory
      jspSetError();
      return 0;
    }
    /* JSON-style object definition */
    JSP_MATCH_WITH_RETURN('{', contents);
    while (!JSP_HAS_ERROR && execInfo.lex->tk != '}') {
      JsVar *varName = 0;
      if (JSP_SHOULD_EXECUTE) {
        varName = jslGetTokenValueAsVar(execInfo.lex);
        if (!varName) { // out of memory
          return contents;
        }
      }
      // we only allow strings or IDs on the left hand side of an initialisation
      if (execInfo.lex->tk==LEX_STR) {
        JSP_MATCH_WITH_CLEANUP_AND_RETURN(LEX_STR, jsvUnLock(varName), contents);
      } else {
        JSP_MATCH_WITH_CLEANUP_AND_RETURN(LEX_ID, jsvUnLock(varName), contents);
      }
      JSP_MATCH_WITH_CLEANUP_AND_RETURN(':', jsvUnLock(varName), contents);
      if (JSP_SHOULD_EXECUTE) {
        JsVar *valueVar;
        JsVar *value = jspeBase(); // value can be 0 (could be undefined!)
        valueVar = jsvSkipNameAndUnLock(value);
        varName = jsvMakeIntoVariableName(varName, valueVar);
        jsvAddName(contents, varName);
        jsvUnLock(valueVar);
      }
      jsvUnLock(varName);
      // no need to clean here, as it will definitely be used
      if (execInfo.lex->tk != '}') JSP_MATCH_WITH_RETURN(',', contents);
    }
    JSP_MATCH_WITH_RETURN('}', contents);
    return contents;
  } else {
    // Not executing so do fast skip
    return jspeBlock();
  }
}

JsVar *jspeFactorArray() {
  int idx = 0;
  JsVar *contents = 0;
  if (JSP_SHOULD_EXECUTE) {
    contents = jsvNewWithFlags(JSV_ARRAY);
    if (!contents) { // out of memory
      jspSetError();
      return 0;
    }
  }
  /* JSON-style array */
  JSP_MATCH_WITH_RETURN('[', contents);
  while (!JSP_HAS_ERROR && execInfo.lex->tk != ']') {
    if (JSP_SHOULD_EXECUTE) {
      // OPT: Store array indices as actual ints
      JsVar *a;
      JsVar *aVar;
      JsVar *indexName;
      a = jspeBase();
      aVar = jsvSkipNameAndUnLock(a);
      indexName = jsvMakeIntoVariableName(jsvNewFromInteger(idx),  aVar);
      if (indexName) { // could be out of memory
        jsvAddName(contents, indexName);
        jsvUnLock(indexName);
      }
      jsvUnLock(aVar);
    } else {
      jsvUnLock(jspeBase());
    }
    // no need to clean here, as it will definitely be used
    if (execInfo.lex->tk != ']') JSP_MATCH_WITH_RETURN(',', contents);
    idx++;
  }
  JSP_MATCH_WITH_RETURN(']', contents);
  return contents;
}

void jspEnsureIsPrototype(JsVar *prototypeName) {
  if (!prototypeName) return;
  JsVar *prototypeVar = jsvSkipName(prototypeName);
  if (!jsvIsObject(prototypeVar)) {
    if (!jsvIsUndefined(prototypeVar))
      jsWarn("Prototype is not an Object, so setting it to {}");    
    jsvUnLock(prototypeVar);
    prototypeVar = jsvNewWithFlags(JSV_OBJECT); // prototype is supposed to be an object
    JsVar *lastName = jsvSkipToLastName(prototypeName);
    jsvSetValueOfName(lastName, prototypeVar);
    jsvUnLock(lastName);
  }
  jsvUnLock(prototypeVar);
}

JsVar *jspeFactorTypeOf() {
  JSP_MATCH(LEX_R_TYPEOF);
  JsVar *a = jspeBase();
  JsVar *result = 0;
  if (JSP_SHOULD_EXECUTE) {
    a = jsvSkipNameAndUnLock(a);
    result=jsvNewFromString(jsvGetTypeOf(a));
  }
  jsvUnLock(a);
  return result;
}

JsVar *jspeFactor() {
    if (execInfo.lex->tk=='(') {
        JsVar *a = 0;
        JSP_MATCH('(');
        if (jspCheckStackPosition())
          a = jspeBaseWithComma();
        if (!JSP_HAS_ERROR) JSP_MATCH_WITH_RETURN(')',a);
        return a;
    } else if (execInfo.lex->tk==LEX_R_TRUE) {
        JSP_MATCH(LEX_R_TRUE);
        return JSP_SHOULD_EXECUTE ? jsvNewFromBool(true) : 0;
    } else if (execInfo.lex->tk==LEX_R_FALSE) {
        JSP_MATCH(LEX_R_FALSE);
        return JSP_SHOULD_EXECUTE ? jsvNewFromBool(false) : 0;
    } else if (execInfo.lex->tk==LEX_R_NULL) {
        JSP_MATCH(LEX_R_NULL);
        return JSP_SHOULD_EXECUTE ? jsvNewWithFlags(JSV_NULL) : 0;
    } else if (execInfo.lex->tk==LEX_R_UNDEFINED) {
        JSP_MATCH(LEX_R_UNDEFINED);
        return 0;
    } else if (execInfo.lex->tk==LEX_ID) {
      return jspeFactorId();
    } else if (execInfo.lex->tk==LEX_INT) {
        // atol works only on decimals
        // strtol handles 0x12345 as well
        //JsVarInt v = (JsVarInt)atol(jslGetTokenValueAsString(execInfo.lex));
        //JsVarInt v = (JsVarInt)strtol(jslGetTokenValueAsString(execInfo.lex),0,0); // broken on PIC
        if (JSP_SHOULD_EXECUTE) {
          JsVarInt v = stringToInt(jslGetTokenValueAsString(execInfo.lex));
          JSP_MATCH(LEX_INT);
          return jsvNewFromInteger(v);
        } else {
          JSP_MATCH(LEX_INT);
          return 0;
        }
    } else if (execInfo.lex->tk==LEX_FLOAT) {
      if (JSP_SHOULD_EXECUTE) {
        JsVarFloat v = stringToFloat(jslGetTokenValueAsString(execInfo.lex));
        JSP_MATCH(LEX_FLOAT);
        return jsvNewFromFloat(v);
      } else {
        JSP_MATCH(LEX_FLOAT);
        return 0;
      }
    } else if (execInfo.lex->tk==LEX_STR) {
      if (JSP_SHOULD_EXECUTE) {
        JsVar *a = jslGetTokenValueAsVar(execInfo.lex);
        JSP_MATCH_WITH_RETURN(LEX_STR, a);
        return a;
      } else {
        JSP_MATCH(LEX_STR);
        return 0;
      }
    } else if (execInfo.lex->tk=='{') {
      return jspeFactorObject();
    } else if (execInfo.lex->tk=='[') {
        return jspeFactorArray();
    } else if (execInfo.lex->tk==LEX_R_FUNCTION) {
      JSP_MATCH(LEX_R_FUNCTION);
      return jspeFunctionDefinition();
    } else if (execInfo.lex->tk==LEX_R_THIS) {
      JSP_MATCH(LEX_R_THIS);
      return jsvLockAgain( execInfo.thisVar ? execInfo.thisVar : execInfo.parse->root );
    } else if (execInfo.lex->tk==LEX_R_TYPEOF) {
      return jspeFactorTypeOf();
    } else if (execInfo.lex->tk==LEX_R_VOID) {
      JSP_MATCH(LEX_R_VOID);
      jsvUnLock(jspeFactor());
      return 0;
    }
    // Nothing we can do here... just hope it's the end...
    JSP_MATCH(LEX_EOF);
    return 0;
}

__attribute((noinline)) JsVar *__jspePostfix(JsVar *a) {
  while (execInfo.lex->tk==LEX_PLUSPLUS || execInfo.lex->tk==LEX_MINUSMINUS) {
    int op = execInfo.lex->tk;
    JSP_MATCH(execInfo.lex->tk);
    if (JSP_SHOULD_EXECUTE) {
        JsVar *one = jsvNewFromInteger(1);
        JsVar *res = jsvMathsOpSkipNames(a, one, op==LEX_PLUSPLUS ? '+' : '-');
        JsVar *oldValue;
        jsvUnLock(one);
        oldValue = jsvSkipName(a); // keep the old value
        // in-place add/subtract
        jspReplaceWith(a, res);
        jsvUnLock(res);
        // but then use the old value
        jsvUnLock(a);
        a = oldValue;
    }
  }
  return a;
}

JsVar *jspePostfix() {
  JsVar *a;
  if (execInfo.lex->tk==LEX_PLUSPLUS || execInfo.lex->tk==LEX_MINUSMINUS) {
      int op = execInfo.lex->tk;
      JSP_MATCH(execInfo.lex->tk);
      a = jspePostfix();
      if (JSP_SHOULD_EXECUTE) {
          JsVar *one = jsvNewFromInteger(1);
          JsVar *res = jsvMathsOpSkipNames(a, one, op==LEX_PLUSPLUS ? '+' : '-');
          jsvUnLock(one);
          // in-place add/subtract
          jspReplaceWith(a, res);
          jsvUnLock(res);
      }
  } else
    a = jspeFactorFunctionCall();
  return __jspePostfix(a);
}

JsVar *jspeUnary() {
    if (execInfo.lex->tk=='!' || execInfo.lex->tk=='~' || execInfo.lex->tk=='-' || execInfo.lex->tk=='+') {
      short tk = execInfo.lex->tk;
      JSP_MATCH(execInfo.lex->tk);
      if (!JSP_SHOULD_EXECUTE) {
        return jspePostfix();
      }
      if (tk=='!') { // logical not
        return jsvNewFromBool(!jsvGetBoolAndUnLock(jsvSkipNameAndUnLock(jspeUnary())));
      } else if (tk=='~') { // bitwise not
        return jsvNewFromInteger(~jsvGetIntegerAndUnLock(jsvSkipNameAndUnLock(jspeUnary())));
      } else if (tk=='-') { // unary minus
        return jsvNegateAndUnLock(jspeUnary()); // names already skipped
      }  else if (tk=='+') { // unary plus (convert to number)
        return jsvAsNumber(jspeUnary()); // names already skipped
      }
      assert(0);
      return 0;
    } else
      return jspePostfix();
}

__attribute((noinline)) JsVar *__jspeTerm(JsVar *a) {
    while (execInfo.lex->tk=='*' || execInfo.lex->tk=='/' || execInfo.lex->tk=='%') {
        JsVar *b;
        int op = execInfo.lex->tk;
        JSP_MATCH(execInfo.lex->tk);
        b = jspeUnary();
        if (JSP_SHOULD_EXECUTE) {
          JsVar *res = jsvMathsOpSkipNames(a, b, op);
          jsvUnLock(a); a = res;
        }
        jsvUnLock(b);
    }
    return a;
}

JsVar *jspeTerm() {
    return __jspeTerm(jspeUnary());
}

__attribute((noinline)) JsVar *__jspeExpression(JsVar *a) {
  while (execInfo.lex->tk=='+' || execInfo.lex->tk=='-') {
      int op = execInfo.lex->tk;
      JSP_MATCH(execInfo.lex->tk);
      JsVar *b = jspeTerm();
      if (JSP_SHOULD_EXECUTE) {
          // not in-place, so just replace
        JsVar *res = jsvMathsOpSkipNames(a, b, op);
        jsvUnLock(a); a = res;
      }
      jsvUnLock(b);
  }
  return a;
}


JsVar *jspeExpression() {
    return __jspeExpression(jspeTerm());
}

__attribute((noinline)) JsVar *__jspeShift(JsVar *a) {
  if (execInfo.lex->tk==LEX_LSHIFT || execInfo.lex->tk==LEX_RSHIFT || execInfo.lex->tk==LEX_RSHIFTUNSIGNED) {
    JsVar *b;
    int op = execInfo.lex->tk;
    JSP_MATCH(op);
    b = jspeExpression();
    if (JSP_SHOULD_EXECUTE) {
      JsVar *res = jsvMathsOpSkipNames(a, b, op);
      jsvUnLock(a); a = res;
    }
    jsvUnLock(b);
  }
  return a;
}

JsVar *jspeShift() {
  return __jspeShift(jspeExpression());
}

__attribute((noinline)) JsVar *__jspeCondition(JsVar *a) {
    JsVar *b;
    while (execInfo.lex->tk==LEX_EQUAL || execInfo.lex->tk==LEX_NEQUAL ||
           execInfo.lex->tk==LEX_TYPEEQUAL || execInfo.lex->tk==LEX_NTYPEEQUAL ||
           execInfo.lex->tk==LEX_LEQUAL || execInfo.lex->tk==LEX_GEQUAL ||
           execInfo.lex->tk=='<' || execInfo.lex->tk=='>' ||
           execInfo.lex->tk==LEX_R_INSTANCEOF ||
           (execInfo.lex->tk==LEX_R_IN && !(execInfo.execute&EXEC_FOR_INIT))) {
        int op = execInfo.lex->tk;
        JSP_MATCH(execInfo.lex->tk);
        b = jspeShift();
        if (JSP_SHOULD_EXECUTE) {
          JsVar *res = 0;
          if (op==LEX_R_IN) {
            JsVar *av = jsvSkipName(a);
            JsVar *bv = jsvSkipName(b);
            if (jsvIsArray(bv) || jsvIsObject(bv)) {
              JsVar *varFound = jsvGetArrayIndexOf(bv, av, false/*not exact*/); // ArrayIndexOf will return 0 if not found
              res = jsvNewFromBool(varFound!=0);
              jsvUnLock(varFound);
            } // else it will be undefined
            jsvUnLock(av);
            jsvUnLock(bv);
          } else if (op==LEX_R_INSTANCEOF) {
            bool inst = false;
            JsVar *av = jsvSkipName(a);
            JsVar *bv = jsvSkipName(b);
            if (!jsvIsFunction(bv)) {
              jsErrorAt("Expecting a function on RHS in instanceof check", execInfo.lex, execInfo.lex->tokenLastEnd);
              jspSetError();
            } else {
              if (jsvIsObject(av)) {
                JsVar *constructor = jsvObjectGetChild(av, JSPARSE_CONSTRUCTOR_VAR, 0);
                if (constructor==bv) inst=true;
                else inst = jspIsConstructor(bv,"Object");
                jsvUnLock(constructor);
              } else {
                const char *name = jswGetBasicObjectName(av);
                if (name) {
                  inst = jspIsConstructor(bv, name);
                }
              }
            }
            jsvUnLock(av);
            jsvUnLock(bv);
            res = jsvNewFromBool(inst);
          } else {
            res = jsvMathsOpSkipNames(a, b, op);

          }
          jsvUnLock(a); a = res;
        }
        jsvUnLock(b);
    }
    return a;
}

JsVar *jspeCondition() {
  return __jspeCondition(jspeShift());
}

__attribute((noinline)) JsVar *__jspeLogic(JsVar *a) {
    JsVar *b = 0;
    while (execInfo.lex->tk=='&' || execInfo.lex->tk=='|' || execInfo.lex->tk=='^' || execInfo.lex->tk==LEX_ANDAND || execInfo.lex->tk==LEX_OROR) {
        bool shortCircuit = false;
        bool boolean = false;
        int op = execInfo.lex->tk;
        JSP_MATCH(execInfo.lex->tk);
        
        // if we have short-circuit ops, then if we know the outcome
        // we don't bother to execute the other op. Even if not
        // we need to tell mathsOp it's an & or |
        if (op==LEX_ANDAND) {
            op = '&';
            shortCircuit = !jsvGetBoolAndUnLock(jsvSkipName(a));
            boolean = true;
        } else if (op==LEX_OROR) {
            op = '|';
            shortCircuit = jsvGetBoolAndUnLock(jsvSkipName(a));
            boolean = true;
        }
        
        JSP_SAVE_EXECUTE();
        if (shortCircuit) jspSetNoExecute(); 
        b = jspeCondition();
        if (shortCircuit) JSP_RESTORE_EXECUTE();
        if (JSP_SHOULD_EXECUTE && !shortCircuit) {
            JsVar *res;
            if (boolean) {
              JsVar *newa = jsvNewFromBool(jsvGetBoolAndUnLock(jsvSkipName(a)));
              JsVar *newb = jsvNewFromBool(jsvGetBoolAndUnLock(jsvSkipName(b)));
              jsvUnLock(a); a = newa;
              jsvUnLock(b); b = newb;
            }
            res = jsvMathsOpSkipNames(a, b, op);
            jsvUnLock(a); a = res;
        }
        jsvUnLock(b);
    }
    return a;
}

JsVar *jspeLogic() {
  return __jspeLogic(jspeCondition());
}

__attribute((noinline)) JsVar *__jspeTernary(JsVar *lhs) {
  if (execInfo.lex->tk=='?') {
    JSP_MATCH('?');
    if (!JSP_SHOULD_EXECUTE) {
      // just let lhs pass through
      jsvUnLock(jspeBase());
      JSP_MATCH(':');
      jsvUnLock(jspeBase());
    } else {
      bool first = jsvGetBoolAndUnLock(jsvSkipName(lhs));
      jsvUnLock(lhs);
      if (first) {
        lhs = jspeBase();
        JSP_MATCH(':');
        JSP_SAVE_EXECUTE();
        jspSetNoExecute();
        jsvUnLock(jspeBase());
        JSP_RESTORE_EXECUTE();
      } else {
        JSP_SAVE_EXECUTE();
        jspSetNoExecute();
        jsvUnLock(jspeBase());
        JSP_RESTORE_EXECUTE();
        JSP_MATCH(':');
        lhs = jspeBase();
      }
    }
  }

  return lhs;
}

JsVar *jspeTernary() {
  return __jspeTernary(jspeLogic());
}

__attribute((noinline)) JsVar *__jspeBase(JsVar *lhs) {
    if (execInfo.lex->tk=='=' || execInfo.lex->tk==LEX_PLUSEQUAL || execInfo.lex->tk==LEX_MINUSEQUAL ||
                                 execInfo.lex->tk==LEX_MULEQUAL || execInfo.lex->tk==LEX_DIVEQUAL || execInfo.lex->tk==LEX_MODEQUAL ||
                                 execInfo.lex->tk==LEX_ANDEQUAL || execInfo.lex->tk==LEX_OREQUAL ||
                                 execInfo.lex->tk==LEX_XOREQUAL || execInfo.lex->tk==LEX_RSHIFTEQUAL ||
                                 execInfo.lex->tk==LEX_LSHIFTEQUAL || execInfo.lex->tk==LEX_RSHIFTUNSIGNEDEQUAL) {
        JsVar *rhs;
        /* If we're assigning to this and we don't have a parent,
         * add it to the symbol table root as per JavaScript. */
        if (JSP_SHOULD_EXECUTE && lhs && !lhs->refs) {
          if (jsvIsName(lhs)/* && jsvGetStringLength(lhs)>0*/) {
            if (!jsvIsArrayBufferName(lhs))
              jsvAddName(execInfo.parse->root, lhs);
          } else // TODO: Why was this here? can it happen?
            jsWarnAt("Trying to assign to an un-named type\n", execInfo.lex, execInfo.lex->tokenLastEnd);
        }

        int op = execInfo.lex->tk;
        JSP_MATCH(execInfo.lex->tk);
        rhs = jspeBase();
        rhs = jsvSkipNameAndUnLock(rhs); // ensure we get rid of any references on the RHS
        if (JSP_SHOULD_EXECUTE && lhs) {
            if (op=='=') {
                jspReplaceWith(lhs, rhs);
            } else {
                if (op==LEX_PLUSEQUAL) op='+';
                else if (op==LEX_MINUSEQUAL) op='-';
                else if (op==LEX_MULEQUAL) op='*';
                else if (op==LEX_DIVEQUAL) op='/';
                else if (op==LEX_MODEQUAL) op='%';
                else if (op==LEX_ANDEQUAL) op='&';
                else if (op==LEX_OREQUAL) op='|';
                else if (op==LEX_XOREQUAL) op='^';
                else if (op==LEX_RSHIFTEQUAL) op=LEX_RSHIFT;
                else if (op==LEX_LSHIFTEQUAL) op=LEX_LSHIFT;
                else if (op==LEX_RSHIFTUNSIGNEDEQUAL) op=LEX_RSHIFTUNSIGNED;
                if (op=='+' && jsvIsName(lhs)) {
                  JsVar *currentValue = jsvSkipName(lhs);
                  if (jsvIsString(currentValue) && currentValue->refs==1) {
                    /* A special case for string += where this is the only use of the string,
                     * as we may be able to do a simple append (rather than clone + append)*/
                    JsVar *str = jsvAsString(rhs, false);
                    jsvAppendStringVarComplete(currentValue, str);
                    jsvUnLock(str);
                    op = 0;
                  }
                  jsvUnLock(currentValue);
                }
                if (op) {
                  /* Fallback which does a proper add */
                  JsVar *res = jsvMathsOpSkipNames(lhs,rhs,op);
                  jspReplaceWith(lhs, res);
                  jsvUnLock(res);
                }
            }
        }
        jsvUnLock(rhs);
    }
    return lhs;
}


JsVar *jspeBase() {
  return __jspeBase(jspeTernary());
}

// jspeBase where ',' is allowed to add multiple expressions
JsVar *jspeBaseWithComma() {
  while (!JSP_HAS_ERROR) {
    JsVar *a = jspeBase();
    if (execInfo.lex->tk!=',') return a;
    // if we get a comma, we just forget this data and parse the next bit...
    jsvUnLock(a);
    JSP_MATCH(',');
  }
  return 0;
}

JsVar *jspeBlock() {
    JSP_MATCH('{');
    if (JSP_SHOULD_EXECUTE) {
      while (execInfo.lex->tk && execInfo.lex->tk!='}') {
        jsvUnLock(jspeStatement());
        if (JSP_HAS_ERROR) {
          if (execInfo.lex && !(execInfo.execute&EXEC_ERROR_LINE_REPORTED)) {
            execInfo.execute = (JsExecFlags)(execInfo.execute | EXEC_ERROR_LINE_REPORTED);
            jsiConsolePrint("at ");
            jsiConsolePrintPosition(execInfo.lex, execInfo.lex->tokenLastEnd);
            jsiConsolePrintTokenLineMarker(execInfo.lex, execInfo.lex->tokenLastEnd);
          }
          return 0;
        }
      }
      JSP_MATCH('}');
    } else {
      // fast skip of blocks
      int brackets = 1;
      while (execInfo.lex->tk && brackets) {
        if (execInfo.lex->tk == '{') brackets++;
        if (execInfo.lex->tk == '}') brackets--;
        JSP_MATCH(execInfo.lex->tk);
      }
    }
    return 0;
}

JsVar *jspeBlockOrStatement() {
    if (execInfo.lex->tk=='{') 
       return jspeBlock();
    else {
       JsVar *v = jspeStatement();
       if (execInfo.lex->tk==';') JSP_MATCH(';');
       return v;
    }
}

JsVar *jspeStatementVar() {
  JsVar *lastDefined = 0;
   /* variable creation. TODO - we need a better way of parsing the left
    * hand side. Maybe just have a flag called can_create_var that we
    * set and then we parse as if we're doing a normal equals.*/
   JSP_MATCH(LEX_R_VAR);
   bool hasComma = true; // for first time in loop
   while (hasComma && execInfo.lex->tk == LEX_ID) {
     JsVar *a = 0;
     if (JSP_SHOULD_EXECUTE) {
       a = jspeiFindOnTop(jslGetTokenValueAsString(execInfo.lex), true);
       if (!a) { // out of memory
         jspSetError();
         return lastDefined;
       }
     }
     JSP_MATCH_WITH_CLEANUP_AND_RETURN(LEX_ID, jsvUnLock(a), lastDefined);
     // now do stuff defined with dots
     while (execInfo.lex->tk == '.') {
         JSP_MATCH_WITH_CLEANUP_AND_RETURN('.', jsvUnLock(a), lastDefined);
         if (JSP_SHOULD_EXECUTE) {
             JsVar *lastA = a;
             a = jsvFindChildFromString(lastA, jslGetTokenValueAsString(execInfo.lex), true);
             jsvUnLock(lastA);
         }
         JSP_MATCH_WITH_CLEANUP_AND_RETURN(LEX_ID, jsvUnLock(a), lastDefined);
     }
     // sort out initialiser
     if (execInfo.lex->tk == '=') {
         JsVar *var;
         JSP_MATCH_WITH_CLEANUP_AND_RETURN('=', jsvUnLock(a), lastDefined);
         var = jsvSkipNameAndUnLock(jspeBase());
         if (JSP_SHOULD_EXECUTE)
             jspReplaceWith(a, var);
         jsvUnLock(var);
     }
     jsvUnLock(lastDefined);
     lastDefined = a;
     hasComma = execInfo.lex->tk == ',';
     if (hasComma) JSP_MATCH_WITH_RETURN(',', lastDefined);
   }
   return lastDefined;
}

JsVar *jspeStatementIf() {
  bool cond;
  JsVar *var;
  JSP_MATCH(LEX_R_IF);
  JSP_MATCH('(');
  var = jspeBase();
  JSP_MATCH(')');
  cond = JSP_SHOULD_EXECUTE && jsvGetBoolAndUnLock(jsvSkipName(var));
  jsvUnLock(var);

  JSP_SAVE_EXECUTE();
  if (!cond) jspSetNoExecute();
  jsvUnLock(jspeBlockOrStatement());
  if (!cond) JSP_RESTORE_EXECUTE();
  if (execInfo.lex->tk==LEX_R_ELSE) {
      //JSP_MATCH(';'); ???
      JSP_MATCH(LEX_R_ELSE);
      JSP_SAVE_EXECUTE();
      if (cond) jspSetNoExecute();
      jsvUnLock(jspeBlockOrStatement());
      if (cond) JSP_RESTORE_EXECUTE();
  }
  return 0;
}

JsVar *jspeStatementSwitch() {
  JSP_MATCH(LEX_R_SWITCH);
  JSP_MATCH('(');
  JsVar *switchOn = jspeBase();
  JSP_MATCH_WITH_CLEANUP_AND_RETURN(')', jsvUnLock(switchOn), 0);
  JSP_MATCH_WITH_CLEANUP_AND_RETURN('{', jsvUnLock(switchOn), 0);
  JSP_SAVE_EXECUTE();
  bool execute = JSP_SHOULD_EXECUTE;
  bool hasExecuted = false;
  if (execute) execInfo.execute=EXEC_NO|EXEC_IN_SWITCH;
  while (execInfo.lex->tk==LEX_R_CASE) {
    JSP_MATCH_WITH_CLEANUP_AND_RETURN(LEX_R_CASE, jsvUnLock(switchOn), 0);
    JsExecFlags oldFlags = execInfo.execute;
    if (execute) execInfo.execute=EXEC_YES|EXEC_IN_SWITCH;
    JsVar *test = jspeBase();
    execInfo.execute = oldFlags|EXEC_IN_SWITCH;;
    JSP_MATCH_WITH_CLEANUP_AND_RETURN(':', jsvUnLock(switchOn);jsvUnLock(test), 0);
    bool cond = false;
    if (execute)
      cond = jsvGetBoolAndUnLock(jsvMathsOpSkipNames(switchOn, test, LEX_EQUAL));
    if (cond) hasExecuted = true;
    jsvUnLock(test);
    if (cond && (execInfo.execute&EXEC_RUN_MASK)==EXEC_NO)
      execInfo.execute=EXEC_YES|EXEC_IN_SWITCH;
    while (!JSP_HAS_ERROR && execInfo.lex->tk!=LEX_EOF && execInfo.lex->tk!=LEX_R_CASE && execInfo.lex->tk!=LEX_R_DEFAULT && execInfo.lex->tk!='}')
      jsvUnLock(jspeBlockOrStatement());
  }
  jsvUnLock(switchOn);
  if (execute && (execInfo.execute&EXEC_RUN_MASK)==EXEC_BREAK)
    execInfo.execute=EXEC_YES|EXEC_IN_SWITCH;
  JSP_RESTORE_EXECUTE();

  if (execInfo.lex->tk==LEX_R_DEFAULT) {
    JSP_MATCH(LEX_R_DEFAULT);
    JSP_MATCH(':');
    JSP_SAVE_EXECUTE();
    if (hasExecuted) jspSetNoExecute();
    while (!JSP_HAS_ERROR && execInfo.lex->tk!=LEX_EOF && execInfo.lex->tk!='}')
      jsvUnLock(jspeBlockOrStatement());
    JSP_RESTORE_EXECUTE();
  }
  JSP_MATCH('}');
  return 0;
}

JsVar *jspeStatementWhile() {
#ifdef JSPARSE_MAX_LOOP_ITERATIONS
  int loopCount = JSPARSE_MAX_LOOP_ITERATIONS;
#endif
  JsVar *cond;
  bool loopCond;
  bool hasHadBreak = false;
  // We do repetition by pulling out the string representing our statement
  // there's definitely some opportunity for optimisation here
  JSP_MATCH(LEX_R_WHILE);
  JSP_MATCH('(');
  JslCharPos whileCondStart = execInfo.lex->tokenStart;
  cond = jspeBase();
  loopCond = JSP_SHOULD_EXECUTE && jsvGetBoolAndUnLock(jsvSkipName(cond));
  jsvUnLock(cond);
  JSP_MATCH(')');
  JslCharPos whileBodyStart = execInfo.lex->tokenStart;
  JSP_SAVE_EXECUTE();
  // actually try and execute first bit of while loop (we'll do the rest in the actual loop later)
  if (!loopCond) jspSetNoExecute();
  execInfo.execute |= EXEC_IN_LOOP;
  jsvUnLock(jspeBlockOrStatement());
  JslCharPos whileBodyEnd = execInfo.lex->tokenStart;
  execInfo.execute &= (JsExecFlags)~EXEC_IN_LOOP;
  if (execInfo.execute == EXEC_CONTINUE)
    execInfo.execute = EXEC_YES;
  if (execInfo.execute == EXEC_BREAK) {
    execInfo.execute = EXEC_YES;
    hasHadBreak = true; // fail loop condition, so we exit
  }
  if (!loopCond) JSP_RESTORE_EXECUTE();

  while (!hasHadBreak && loopCond
#ifdef JSPARSE_MAX_LOOP_ITERATIONS
         && loopCount-->0
#endif
         ) {
      jslSeekTo(execInfo.lex, whileCondStart);
      cond = jspeBase();
      loopCond = JSP_SHOULD_EXECUTE && jsvGetBoolAndUnLock(jsvSkipName(cond));
      jsvUnLock(cond);
      if (loopCond) {
          jslSeekTo(execInfo.lex, whileBodyStart);
          execInfo.execute |= EXEC_IN_LOOP;
          jsvUnLock(jspeBlockOrStatement());
          execInfo.execute &= (JsExecFlags)~EXEC_IN_LOOP;
          if (execInfo.execute == EXEC_CONTINUE)
            execInfo.execute = EXEC_YES;
          if (execInfo.execute == EXEC_BREAK) {
            execInfo.execute = EXEC_YES;
            hasHadBreak = true;
          }
      }
  }
  jslSeekTo(execInfo.lex, whileBodyEnd);
#ifdef JSPARSE_MAX_LOOP_ITERATIONS
  if (loopCount<=0) {
    jsErrorAt("WHILE Loop exceeded the maximum number of iterations (" STRINGIFY(JSPARSE_MAX_LOOP_ITERATIONS) ")", execInfo.lex, execInfo.lex->tokenLastEnd);
    jspSetError();
  }
#endif
  return 0;
}

JsVar *jspeStatementFor() {
  JSP_MATCH(LEX_R_FOR);
  JSP_MATCH('(');
  execInfo.execute |= EXEC_FOR_INIT;
  // initialisation
  JsVar *forStatement = 0;
  // we could have 'for (;;)' - so don't munch up our semicolon if that's all we have
  if (execInfo.lex->tk != ';') 
    forStatement = jspeStatement(); 
  execInfo.execute &= (JsExecFlags)~EXEC_FOR_INIT;
  if (execInfo.lex->tk == LEX_R_IN) {
    // for (i in array)
    // where i = jsvUnLock(forStatement);
    if (!jsvIsName(forStatement)) {
      jsvUnLock(forStatement);
      jsErrorAt("FOR a IN b - 'a' must be a variable name", execInfo.lex, execInfo.lex->tokenLastEnd);
      jspSetError();
      return 0;
    }
    bool addedIteratorToScope = false;
    if (JSP_SHOULD_EXECUTE && !forStatement->refs) {
      // if the variable did not exist, add it to the scope
      addedIteratorToScope = true;
      jsvAddName(execInfo.parse->root, forStatement);
    }
    JSP_MATCH_WITH_CLEANUP_AND_RETURN(LEX_R_IN, jsvUnLock(forStatement), 0);
    JsVar *array = jsvSkipNameAndUnLock(jspeExpression());
    JSP_MATCH_WITH_CLEANUP_AND_RETURN(')', jsvUnLock(forStatement);jsvUnLock(array), 0);
    JslCharPos forBodyStart = execInfo.lex->tokenStart;
    JSP_SAVE_EXECUTE();
    jspSetNoExecute();
    execInfo.execute |= EXEC_IN_LOOP;
    jsvUnLock(jspeBlockOrStatement());
    JslCharPos forBodyEnd = execInfo.lex->tokenStart;
    execInfo.execute &= (JsExecFlags)~EXEC_IN_LOOP;
    JSP_RESTORE_EXECUTE();

    if (jsvIsIterable(array)) {
      bool (*checkerFunction)(JsVar*) = 0;
      if (jsvIsFunction(array)) checkerFunction = jsvIsInternalFunctionKey;
      else if (jsvIsObject(array)) checkerFunction = jsvIsInternalObjectKey;
      JsvIterator it;
      jsvIteratorNew(&it, array);
      bool hasHadBreak = false;
      while (JSP_SHOULD_EXECUTE && jsvIteratorHasElement(&it) && !hasHadBreak) {
          JsVar *loopIndexVar = jsvIteratorGetKey(&it);
          bool ignore = false;
          if (checkerFunction && checkerFunction(loopIndexVar))
            ignore = true;
          if (!ignore) {
            JsVar *indexValue = jsvIsName(loopIndexVar) ?
                                  jsvCopyNameOnly(loopIndexVar, false/*no copy children*/, false/*not a name*/) :
                                  loopIndexVar;
            if (indexValue) { // could be out of memory
              assert(!jsvIsName(indexValue) && indexValue->refs==0);
              jsvSetValueOfName(forStatement, indexValue);
              if (indexValue!=loopIndexVar) jsvUnLock(indexValue);
  
              jsvIteratorNext(&it);
 
              jslSeekTo(execInfo.lex, forBodyStart);
              execInfo.execute |= EXEC_IN_LOOP;
              jsvUnLock(jspeBlockOrStatement());
              execInfo.execute &= (JsExecFlags)~EXEC_IN_LOOP;

              if (execInfo.execute == EXEC_CONTINUE)
                execInfo.execute = EXEC_YES;
              if (execInfo.execute == EXEC_BREAK) {
                execInfo.execute = EXEC_YES;
                hasHadBreak = true;
              }
            }
          } else
            jsvIteratorNext(&it);
          jsvUnLock(loopIndexVar);
      }
      jsvIteratorFree(&it);
    } else {
      jsErrorAt("FOR loop can only iterate over Arrays, Strings or Objects", execInfo.lex, execInfo.lex->tokenLastEnd);
      jspSetError();
    }

    jslSeekTo(execInfo.lex, forBodyEnd);

    if (addedIteratorToScope) {
      jsvRemoveChild(execInfo.parse->root, forStatement);
    }
    jsvUnLock(forStatement);
    jsvUnLock(array);
  } else { // NORMAL FOR LOOP
#ifdef JSPARSE_MAX_LOOP_ITERATIONS
    int loopCount = JSPARSE_MAX_LOOP_ITERATIONS;
#endif
    bool loopCond = true;
    bool hasHadBreak = false;

    jsvUnLock(forStatement);
    JSP_MATCH(';');
    JslCharPos forCondStart = execInfo.lex->tokenStart;
    if (execInfo.lex->tk != ';') {
      JsVar *cond = jspeBase(); // condition
      loopCond = JSP_SHOULD_EXECUTE && jsvGetBoolAndUnLock(jsvSkipName(cond));
      jsvUnLock(cond);
    }
    JSP_MATCH(';');
    JslCharPos forIterStart = execInfo.lex->tokenStart;
    if (execInfo.lex->tk != ')')  { // we could have 'for (;;)'
      JSP_SAVE_EXECUTE();
      jspSetNoExecute();
      jsvUnLock(jspeBase()); // iterator
      JSP_RESTORE_EXECUTE();
    }
    JSP_MATCH(')');

    JslCharPos forBodyStart = execInfo.lex->tokenStart; // actual for body
    JSP_SAVE_EXECUTE();
    if (!loopCond) jspSetNoExecute();
    execInfo.execute |= EXEC_IN_LOOP;
    jsvUnLock(jspeBlockOrStatement());
    JslCharPos forBodyEnd = execInfo.lex->tokenStart;
    execInfo.execute &= (JsExecFlags)~EXEC_IN_LOOP;
    if (execInfo.execute == EXEC_CONTINUE)
      execInfo.execute = EXEC_YES;
    if (execInfo.execute == EXEC_BREAK) {
      execInfo.execute = EXEC_YES;
      hasHadBreak = true;
    }
    if (!loopCond) JSP_RESTORE_EXECUTE();
    if (loopCond) {
        jslSeekTo(execInfo.lex, forIterStart);
        if (execInfo.lex->tk != ')') jsvUnLock(jspeBase());
    }
    while (!hasHadBreak && JSP_SHOULD_EXECUTE && loopCond
#ifdef JSPARSE_MAX_LOOP_ITERATIONS
           && loopCount-->0
#endif
           ) {
        jslSeekTo(execInfo.lex, forCondStart);
        ;
        if (execInfo.lex->tk == ';') {
          loopCond = true;
        } else {
          JsVar *cond = jspeBase();
          loopCond = jsvGetBoolAndUnLock(jsvSkipName(cond));
          jsvUnLock(cond);
        }
        if (JSP_SHOULD_EXECUTE && loopCond) {
            jslSeekTo(execInfo.lex, forBodyStart);
            execInfo.execute |= EXEC_IN_LOOP;
            jsvUnLock(jspeBlockOrStatement());
            execInfo.execute &= (JsExecFlags)~EXEC_IN_LOOP;
            if (execInfo.execute == EXEC_CONTINUE)
              execInfo.execute = EXEC_YES;
            if (execInfo.execute == EXEC_BREAK) {
              execInfo.execute = EXEC_YES;
              hasHadBreak = true;
            }
        }
        if (JSP_SHOULD_EXECUTE && loopCond) {
            jslSeekTo(execInfo.lex, forIterStart);
            if (execInfo.lex->tk != ')') jsvUnLock(jspeBase());
        }
    }
    jslSeekTo(execInfo.lex, forBodyEnd);
#ifdef JSPARSE_MAX_LOOP_ITERATIONS
    if (loopCount<=0) {
        jsErrorAt("FOR Loop exceeded the maximum number of iterations ("STRINGIFY(JSPARSE_MAX_LOOP_ITERATIONS)")", execInfo.lex, execInfo.lex->tokenLastEnd);
        jspSetError();
    }
#endif
  }
  return 0;
}

JsVar *jspeStatementReturn() {
  JsVar *result = 0;
  JSP_MATCH(LEX_R_RETURN);
  if (execInfo.lex->tk != ';') {
    // we only want the value, so skip the name if there was one
    result = jsvSkipNameAndUnLock(jspeBaseWithComma());
  }
  if (JSP_SHOULD_EXECUTE) {
    JsVar *resultVar = jspeiFindOnTop(JSPARSE_RETURN_VAR, false);
    if (resultVar) {
      jspReplaceWith(resultVar, result);
      jsvUnLock(resultVar);
    } else {
      jsErrorAt("RETURN statement, but not in a function.\n", execInfo.lex, execInfo.lex->tokenLastEnd);
      jspSetError();
    }
    jspSetNoExecute(); // Stop anything else in this function executing
  }
  jsvUnLock(result);
  return 0;
}

JsVar *jspeStatementFunctionDecl() {
  JsVar *funcName = 0;
  JsVar *funcVar;
  JSP_MATCH(LEX_R_FUNCTION);
  if (JSP_SHOULD_EXECUTE)
    funcName = jsvMakeIntoVariableName(jsvNewFromString(jslGetTokenValueAsString(execInfo.lex)), 0);
  if (!funcName) { // out of memory
    jspSetError();
    return 0;
  }
  JSP_MATCH(LEX_ID);
  funcVar = jspeFunctionDefinition();
  if (JSP_SHOULD_EXECUTE) {
    // find a function with the same name (or make one)
    // OPT: can Find* use just a JsVar that is a 'name'?
    JsVar *existingFunc = jspeiFindNameOnTop(funcName, true);
    // replace it
    jspReplaceWith(existingFunc, funcVar);
    jsvUnLock(funcName);
    funcName = existingFunc;
  }
  jsvUnLock(funcVar);
  return funcName;
}

JsVar *jspeStatement() {
    if (execInfo.lex->tk==LEX_ID ||
        execInfo.lex->tk==LEX_INT ||
        execInfo.lex->tk==LEX_FLOAT ||
        execInfo.lex->tk==LEX_STR ||
        execInfo.lex->tk==LEX_R_NEW ||
        execInfo.lex->tk==LEX_R_NULL ||
        execInfo.lex->tk==LEX_R_UNDEFINED ||
        execInfo.lex->tk==LEX_R_TRUE ||
        execInfo.lex->tk==LEX_R_FALSE ||
        execInfo.lex->tk==LEX_R_THIS ||
        execInfo.lex->tk==LEX_R_TYPEOF ||
        execInfo.lex->tk==LEX_R_VOID ||
        execInfo.lex->tk==LEX_PLUSPLUS ||
        execInfo.lex->tk==LEX_MINUSMINUS ||
        execInfo.lex->tk=='!' ||
        execInfo.lex->tk=='-' ||
        execInfo.lex->tk=='+' ||
        execInfo.lex->tk=='~' ||
        execInfo.lex->tk=='[' ||
        execInfo.lex->tk=='(') {
        /* Execute a simple statement that only contains basic arithmetic... */
      return jspeBaseWithComma();
    } else if (execInfo.lex->tk=='{') {
        /* A block of code */
        return jspeBlock();
    } else if (execInfo.lex->tk==';') {
        /* Empty statement - to allow things like ;;; */
        JSP_MATCH(';');
        return 0;
    } else if (execInfo.lex->tk==LEX_R_VAR) {
        return jspeStatementVar();
    } else if (execInfo.lex->tk==LEX_R_IF) {
        return jspeStatementIf();
    } else if (execInfo.lex->tk==LEX_R_WHILE) {
        return jspeStatementWhile();
    } else if (execInfo.lex->tk==LEX_R_FOR) {
        return jspeStatementFor();
    } else if (execInfo.lex->tk==LEX_R_RETURN) {
        return jspeStatementReturn();
    } else if (execInfo.lex->tk==LEX_R_FUNCTION) {
        return jspeStatementFunctionDecl();
    } else if (execInfo.lex->tk==LEX_R_CONTINUE) {
      JSP_MATCH(LEX_R_CONTINUE);
      if (JSP_SHOULD_EXECUTE) {
        if (!(execInfo.execute & EXEC_IN_LOOP))
          jsErrorAt("CONTINUE statement outside of FOR or WHILE loop", execInfo.lex, execInfo.lex->tokenLastEnd);
        else
          execInfo.execute = (execInfo.execute & (JsExecFlags)~EXEC_RUN_MASK) |  EXEC_CONTINUE;
      }
    } else if (execInfo.lex->tk==LEX_R_BREAK) {
      JSP_MATCH(LEX_R_BREAK);
      if (JSP_SHOULD_EXECUTE) {
        if (!(execInfo.execute & (EXEC_IN_LOOP|EXEC_IN_SWITCH)))
          jsErrorAt("BREAK statement outside of SWITCH, FOR or WHILE loop", execInfo.lex, execInfo.lex->tokenLastEnd);
        else
          execInfo.execute = (execInfo.execute & (JsExecFlags)~EXEC_RUN_MASK) | EXEC_BREAK;
      }
    } else if (execInfo.lex->tk==LEX_R_SWITCH) {
      return jspeStatementSwitch();
    } else JSP_MATCH(LEX_EOF);
    return 0;
}

// -----------------------------------------------------------------------------
/// Create a new built-in object that jswrapper can use to check for built-in functions
JsVar *jspNewBuiltin(const char *instanceOf) {
  JsVar *objFunc = jsvNewWithFlags(JSV_FUNCTION);
  if (!objFunc) return 0; // out of memory
  // set object data to be object name
  if (strlen(instanceOf)==sizeof(objFunc->varData))
    memcpy(objFunc->varData.str, instanceOf, sizeof(objFunc->varData)); // no trailing zero!
  else
    strncpy(objFunc->varData.str, instanceOf, sizeof(objFunc->varData));
  return objFunc;
}


JsVar *jspNewObject(JsParse *parse, const char *name, const char *instanceOf) {
  JsVar *objFuncName = jsvFindChildFromString(parse->root, instanceOf, true);
  if (!objFuncName) // out of memory
    return 0;

  JsVar *objFunc = jsvSkipName(objFuncName);
  if (!objFunc) {
    objFunc = jspNewBuiltin(instanceOf);
    if (!objFunc) { // out of memory
      jsvUnLock(objFuncName);
      return 0;
    }

    // set up name
    jsvSetValueOfName(objFuncName, objFunc);
  }

  JsVar *prototypeName = jsvFindChildFromString(objFunc, JSPARSE_PROTOTYPE_VAR, true);
  jspEnsureIsPrototype(prototypeName); // make sure it's an object
  jsvUnLock(objFunc);
  if (!prototypeName) { // out of memory
    jsvUnLock(objFuncName);
    return 0;
  }

  JsVar *obj = jsvNewWithFlags(JSV_OBJECT);
  if (!obj) { // out of memory
    jsvUnLock(objFuncName);
    jsvUnLock(prototypeName);
    return 0;
  }
  if (name) {
    // set object data to be object name
    strncpy(obj->varData.str, name, sizeof(obj->varData));
  }
  // add inherits/constructor/etc
  jsvUnLock(jsvAddNamedChild(obj, prototypeName, JSPARSE_INHERITS_VAR));
  jsvUnLock(prototypeName);prototypeName=0;
  jsvUnLock(jsvAddNamedChild(obj, objFuncName, JSPARSE_CONSTRUCTOR_VAR));
  jsvUnLock(objFuncName);
  if (name) {
    JsVar *objName = jsvAddNamedChild(parse->root, obj, name);
    jsvUnLock(obj);
    if (!objName) { // out of memory
      return 0;
    }
    return objName;
  } else
    return obj;
}

/** Returns true if the constructor function given is the same as that
 * of the object with the given name. */
bool jspIsConstructor(JsVar *constructor, const char *constructorName) {
  JsVar *objFunc = jsvObjectGetChild(execInfo.parse->root, constructorName, 0);
  if (!objFunc) return false;
  bool isConstructor = objFunc == constructor;
  jsvUnLock(objFunc);
  return isConstructor;
}

// -----------------------------------------------------------------------------

void jspSoftInit(JsParse *parse) {
  parse->root = jsvFindOrCreateRoot();
  // Root now has a lock and a ref
}

/** Is v likely to have been created by this parser? */
bool jspIsCreatedObject(JsParse *parse, JsVar *v) {
  return
      v==parse->root;
}

void jspSoftKill(JsParse *parse) {
  jsvUnLock(parse->root);
  // Root now has just a ref
}

void jspInit(JsParse *parse) {
  jspSoftInit(parse);
}

void jspKill(JsParse *parse) {
  jspSoftKill(parse);
  // Unreffing this should completely kill everything attached to root
  JsVar *r = jsvFindOrCreateRoot();
  jsvUnRef(r);
  jsvUnLock(r);
}



JsVar *jspEvaluateVar(JsParse *parse, JsVar *str, JsVar *scope) {
  JsLex lex;
  JsVar *v = 0;
  JSP_SAVE_EXECUTE();
  JsExecInfo oldExecInfo = execInfo;

  assert(jsvIsString(str));
  jslInit(&lex, str);

  jspeiInit(parse, &lex);
  bool scopeAdded = false;
  if (scope)
    scopeAdded = jspeiAddScope(jsvGetRef(scope));
  while (!JSP_HAS_ERROR && execInfo.lex->tk != LEX_EOF) {
    jsvUnLock(v);
    v = jspeBlockOrStatement();
  }
  // clean up
  if (scopeAdded) jspeiRemoveScope();
  jspeiKill();
  jslKill(&lex);

  // restore state
  JSP_RESTORE_EXECUTE();
  oldExecInfo.execute = execInfo.execute; // JSP_RESTORE_EXECUTE has made this ok.
  execInfo = oldExecInfo;

  // It may have returned a reference, but we just want the value...
  if (v) {
    return jsvSkipNameAndUnLock(v);
  }
  // nothing returned
  return 0;
}

JsVar *jspEvaluate(JsParse *parse, const char *str) {
  JsVar *v = 0;

  JsVar *evCode = jsvNewFromString(str);
  if (!jsvIsMemoryFull())
    v = jspEvaluateVar(parse, evCode, 0);
  jsvUnLock(evCode);

  return v;
}

bool jspExecuteFunction(JsParse *parse, JsVar *func, JsVar *parent, int argCount, JsVar **argPtr) {
  JSP_SAVE_EXECUTE();
  JsExecInfo oldExecInfo = execInfo;

  jspeiInit(parse, 0);
  JsVar *resultVar = jspeFunctionCall(func, 0, parent, false, argCount, argPtr);
  bool result = jsvGetBool(resultVar);
  jsvUnLock(resultVar);
  // clean up
  jspeiKill();
  // restore state
  JSP_RESTORE_EXECUTE();
  oldExecInfo.execute = execInfo.execute; // JSP_RESTORE_EXECUTE has made this ok.
  execInfo = oldExecInfo;


  return result;
}


/// Evaluate a JavaScript module and return its exports
JsVar *jspEvaluateModule(JsParse *parse, JsVar *moduleContents) {
  assert(jsvIsString(moduleContents));
  JsVar *scope = jsvNewWithFlags(JSV_OBJECT);
  if (!scope) return 0; // out of mem
  JsVar *scopeExports = jsvNewWithFlags(JSV_OBJECT);
  if (!scopeExports) { jsvUnLock(scope); return 0; } // out of mem
  jsvUnLock(jsvAddNamedChild(scope, scopeExports, "exports"));

  jsvUnLock(jspEvaluateVar(parse, moduleContents, scope));

  jsvUnLock(scope);
  return scopeExports;
}
