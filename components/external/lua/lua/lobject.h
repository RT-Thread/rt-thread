/*
** $Id: lobject.h,v 2.20.1.2 2008/08/06 13:29:48 roberto Exp $
** Type definitions for Lua objects
** See Copyright Notice in lua.h
*/


#ifndef lobject_h
#define lobject_h


#include <stdarg.h>


#include "llimits.h"
#include "lua.h"


/* tags for values visible from Lua */
#define LAST_TAG	LUA_TTHREAD

#define NUM_TAGS	(LAST_TAG+1)

/* mask for 'read-only' objects. must match READONLYBIT in lgc.h' */
#define READONLYMASK  128


/*
** Extra tags for non-values
*/
#define LUA_TPROTO	(LAST_TAG+1)
#define LUA_TUPVAL	(LAST_TAG+2)
#define LUA_TDEADKEY	(LAST_TAG+3)


/*
** Union of all collectable objects
*/
typedef union GCObject GCObject;


/*
** Common Header for all collectable objects (in macro form, to be
** included in other objects)
*/
#define CommonHeader	GCObject *next; lu_byte tt; lu_byte marked


/*
** Common header in struct form
*/
typedef struct GCheader {
  CommonHeader;
} GCheader;




/*
** Union of all Lua values
*/
#if defined( LUA_PACK_VALUE ) && defined( ELUA_ENDIAN_BIG )
typedef union {
  struct {
    int _pad0;
    GCObject *gc;
  };
  struct {
    int _pad1;
    void *p;
  };
  lua_Number n;
  struct {
    int _pad2;
    int b;
  };
} Value;
#else // #if defined( LUA_PACK_VALUE ) && defined( ELUA_ENDIAN_BIG )
typedef union {
  GCObject *gc;
  void *p;
  lua_Number n;
  int b;
} Value;
#endif // #if defined( LUA_PACK_VALUE ) && defined( ELUA_ENDIAN_BIG )

/*
** Tagged Values
*/

#ifndef LUA_PACK_VALUE
#define TValuefields	Value value; int tt
#define LUA_TVALUE_NIL {NULL}, LUA_TNIL

typedef struct lua_TValue {
  TValuefields;
} TValue;
#else // #ifndef LUA_PACK_VALUE
#ifdef ELUA_ENDIAN_LITTLE
#define TValuefields union { \
  struct { \
    int _pad0; \
    int tt_sig; \
  } _ts; \
  struct { \
    int _pad; \
    short tt; \
    short sig; \
  } _t; \
  Value value; \
}
#define LUA_TVALUE_NIL {0, add_sig(LUA_TNIL)}
#else // #ifdef ELUA_ENDIAN_LITTLE
#define TValuefields union { \
  struct { \
    int tt_sig; \
    int _pad0; \
  } _ts; \
  struct { \
    short sig; \
    short tt; \
    int _pad; \
  } _t; \
  Value value; \
}
#define LUA_TVALUE_NIL {add_sig(LUA_TNIL), 0}
#endif // #ifdef ELUA_ENDIAN_LITTLE
#define LUA_NOTNUMBER_SIG (-1)
#define add_sig(tt) ( 0xffff0000 | (tt) )

typedef TValuefields TValue;
#endif // #ifndef LUA_PACK_VALUE

/* Macros to test type */
#ifndef LUA_PACK_VALUE
#define ttisnil(o)	(ttype(o) == LUA_TNIL)
#define ttisnumber(o)	(ttype(o) == LUA_TNUMBER)
#define ttisstring(o)	(ttype(o) == LUA_TSTRING)
#define ttistable(o)	(ttype(o) == LUA_TTABLE)
#define ttisfunction(o)	(ttype(o) == LUA_TFUNCTION)
#define ttisboolean(o)	(ttype(o) == LUA_TBOOLEAN)
#define ttisuserdata(o)	(ttype(o) == LUA_TUSERDATA)
#define ttisthread(o)	(ttype(o) == LUA_TTHREAD)
#define ttislightuserdata(o)	(ttype(o) == LUA_TLIGHTUSERDATA)
#define ttisrotable(o) (ttype(o) == LUA_TROTABLE)
#define ttislightfunction(o)  (ttype(o) == LUA_TLIGHTFUNCTION)
#else // #ifndef LUA_PACK_VALUE
#define ttisnil(o) (ttype_sig(o) == add_sig(LUA_TNIL))
#define ttisnumber(o)  ((o)->_t.sig != LUA_NOTNUMBER_SIG)
#define ttisstring(o)  (ttype_sig(o) == add_sig(LUA_TSTRING))
#define ttistable(o) (ttype_sig(o) == add_sig(LUA_TTABLE))
#define ttisfunction(o)  (ttype_sig(o) == add_sig(LUA_TFUNCTION))
#define ttisboolean(o) (ttype_sig(o) == add_sig(LUA_TBOOLEAN))
#define ttisuserdata(o)  (ttype_sig(o) == add_sig(LUA_TUSERDATA))
#define ttisthread(o)  (ttype_sig(o) == add_sig(LUA_TTHREAD))
#define ttislightuserdata(o) (ttype_sig(o) == add_sig(LUA_TLIGHTUSERDATA))
#define ttisrotable(o) (ttype_sig(o) == add_sig(LUA_TROTABLE))
#define ttislightfunction(o)  (ttype_sig(o) == add_sig(LUA_TLIGHTFUNCTION))
#endif // #ifndef LUA_PACK_VALUE

/* Macros to access values */
#ifndef LUA_PACK_VALUE
#define ttype(o)	((o)->tt)
#else // #ifndef LUA_PACK_VALUE
#define ttype(o)	((o)->_t.sig == LUA_NOTNUMBER_SIG ? (o)->_t.tt : LUA_TNUMBER)
#define ttype_sig(o)	((o)->_ts.tt_sig)
#endif // #ifndef LUA_PACK_VALUE
#define gcvalue(o)	check_exp(iscollectable(o), (o)->value.gc)
#define pvalue(o)	check_exp(ttislightuserdata(o), (o)->value.p)
#define rvalue(o)	check_exp(ttisrotable(o), (o)->value.p)
#define fvalue(o) check_exp(ttislightfunction(o), (o)->value.p)
#define nvalue(o)	check_exp(ttisnumber(o), (o)->value.n)
#define rawtsvalue(o)	check_exp(ttisstring(o), &(o)->value.gc->ts)
#define tsvalue(o)	(&rawtsvalue(o)->tsv)
#define rawuvalue(o)	check_exp(ttisuserdata(o), &(o)->value.gc->u)
#define uvalue(o)	(&rawuvalue(o)->uv)
#define clvalue(o)	check_exp(ttisfunction(o), &(o)->value.gc->cl)
#define hvalue(o)	check_exp(ttistable(o), &(o)->value.gc->h)
#define bvalue(o)	check_exp(ttisboolean(o), (o)->value.b)
#define thvalue(o)	check_exp(ttisthread(o), &(o)->value.gc->th)

#define l_isfalse(o)	(ttisnil(o) || (ttisboolean(o) && bvalue(o) == 0))

/*
** for internal debug only
*/
#ifndef LUA_PACK_VALUE
#define checkconsistency(obj) \
  lua_assert(!iscollectable(obj) || (ttype(obj) == (obj)->value.gc->gch.tt))

#define checkliveness(g,obj) \
  lua_assert(!iscollectable(obj) || \
  ((ttype(obj) == (obj)->value.gc->gch.tt) && !isdead(g, (obj)->value.gc)))
#else // #ifndef LUA_PACK_VALUE
#define checkconsistency(obj) \
  lua_assert(!iscollectable(obj) || (ttype(obj) == (obj)->value.gc->gch._t.tt))

#define checkliveness(g,obj) \
  lua_assert(!iscollectable(obj) || \
  ((ttype(obj) == (obj)->value.gc->gch._t.tt) && !isdead(g, (obj)->value.gc)))
#endif // #ifndef LUA_PACK_VALUE

/* Macros to set values */
#ifndef LUA_PACK_VALUE
#define setnilvalue(obj) ((obj)->tt=LUA_TNIL)

#define setnvalue(obj,x) \
  { lua_Number i_x = (x); TValue *i_o=(obj); i_o->value.n=i_x; i_o->tt=LUA_TNUMBER; }

#define setpvalue(obj,x) \
  { void *i_x = (x); TValue *i_o=(obj); i_o->value.p=i_x; i_o->tt=LUA_TLIGHTUSERDATA; }
  
#define setrvalue(obj,x) \
  { void *i_x = (x); TValue *i_o=(obj); i_o->value.p=i_x; i_o->tt=LUA_TROTABLE; }
  
#define setfvalue(obj,x) \
  { void *i_x = (x); TValue *i_o=(obj); i_o->value.p=i_x; i_o->tt=LUA_TLIGHTFUNCTION; }

#define setbvalue(obj,x) \
  { int i_x = (x); TValue *i_o=(obj); i_o->value.b=i_x; i_o->tt=LUA_TBOOLEAN; }

#define setsvalue(L,obj,x) \
  { GCObject *i_x = cast(GCObject *, (x)); \
    TValue *i_o=(obj); \
    i_o->value.gc=i_x; i_o->tt=LUA_TSTRING; \
    checkliveness(G(L),i_o); }

#define setuvalue(L,obj,x) \
  { GCObject *i_x = cast(GCObject *, (x)); \
    TValue *i_o=(obj); \
    i_o->value.gc=i_x; i_o->tt=LUA_TUSERDATA; \
    checkliveness(G(L),i_o); }

#define setthvalue(L,obj,x) \
  { GCObject *i_x = cast(GCObject *, (x)); \
    TValue *i_o=(obj); \
    i_o->value.gc=i_x; i_o->tt=LUA_TTHREAD; \
    checkliveness(G(L),i_o); }

#define setclvalue(L,obj,x) \
  { GCObject *i_x = cast(GCObject *, (x)); \
    TValue *i_o=(obj); \
    i_o->value.gc=i_x; i_o->tt=LUA_TFUNCTION; \
    checkliveness(G(L),i_o); }

#define sethvalue(L,obj,x) \
  { GCObject *i_x = cast(GCObject *, (x)); \
    TValue *i_o=(obj); \
    i_o->value.gc=i_x; i_o->tt=LUA_TTABLE; \
    checkliveness(G(L),i_o); }

#define setptvalue(L,obj,x) \
  { GCObject *i_x = cast(GCObject *, (x)); \
    TValue *i_o=(obj); \
    i_o->value.gc=i_x; i_o->tt=LUA_TPROTO; \
    checkliveness(G(L),i_o); }




#define setobj(L,obj1,obj2) \
  { const TValue *o2=(obj2); TValue *o1=(obj1); \
    o1->value = o2->value; o1->tt=o2->tt; \
    checkliveness(G(L),o1); }
#else // #ifndef LUA_PACK_VALUE
#define setnilvalue(obj) ( ttype_sig(obj) = add_sig(LUA_TNIL) )

#define setnvalue(obj,x) \
  { TValue *i_o=(obj); i_o->value.n=(x); }

#define setpvalue(obj,x) \
  { TValue *i_o=(obj); i_o->value.p=(x); i_o->_ts.tt_sig=add_sig(LUA_TLIGHTUSERDATA);}

#define setrvalue(obj,x) \
  { TValue *i_o=(obj); i_o->value.p=(x); i_o->_ts.tt_sig=add_sig(LUA_TROTABLE);}

#define setfvalue(obj,x) \
  { TValue *i_o=(obj); i_o->value.p=(x); i_o->_ts.tt_sig=add_sig(LUA_TLIGHTFUNCTION);}

#define setbvalue(obj,x) \
  { TValue *i_o=(obj); i_o->value.b=(x); i_o->_ts.tt_sig=add_sig(LUA_TBOOLEAN);}

#define setsvalue(L,obj,x) \
  { TValue *i_o=(obj); \
    i_o->value.gc=cast(GCObject *, (x)); i_o->_ts.tt_sig=add_sig(LUA_TSTRING); \
    checkliveness(G(L),i_o); }

#define setuvalue(L,obj,x) \
  { TValue *i_o=(obj); \
    i_o->value.gc=cast(GCObject *, (x)); i_o->_ts.tt_sig=add_sig(LUA_TUSERDATA); \
    checkliveness(G(L),i_o); }

#define setthvalue(L,obj,x) \
  { TValue *i_o=(obj); \
    i_o->value.gc=cast(GCObject *, (x)); i_o->_ts.tt_sig=add_sig(LUA_TTHREAD); \
    checkliveness(G(L),i_o); }

#define setclvalue(L,obj,x) \
  { TValue *i_o=(obj); \
    i_o->value.gc=cast(GCObject *, (x)); i_o->_ts.tt_sig=add_sig(LUA_TFUNCTION); \
    checkliveness(G(L),i_o); }

#define sethvalue(L,obj,x) \
  { TValue *i_o=(obj); \
    i_o->value.gc=cast(GCObject *, (x)); i_o->_ts.tt_sig=add_sig(LUA_TTABLE); \
    checkliveness(G(L),i_o); }

#define setptvalue(L,obj,x) \
  { TValue *i_o=(obj); \
    i_o->value.gc=cast(GCObject *, (x)); i_o->_ts.tt_sig=add_sig(LUA_TPROTO); \
    checkliveness(G(L),i_o); }




#define setobj(L,obj1,obj2) \
  { const TValue *o2=(obj2); TValue *o1=(obj1); \
    o1->value = o2->value; \
    checkliveness(G(L),o1); }
#endif // #ifndef LUA_PACK_VALUE

/*
** different types of sets, according to destination
*/

/* from stack to (same) stack */
#define setobjs2s	setobj
/* to stack (not from same stack) */
#define setobj2s	setobj
#define setsvalue2s	setsvalue
#define sethvalue2s	sethvalue
#define setptvalue2s	setptvalue
/* from table to same table */
#define setobjt2t	setobj
/* to table */
#define setobj2t	setobj
/* to new object */
#define setobj2n	setobj
#define setsvalue2n	setsvalue

#ifndef LUA_PACK_VALUE
#define setttype(obj, tt) (ttype(obj) = (tt))
#else // #ifndef LUA_PACK_VALUE
/* considering it used only in lgc to set LUA_TDEADKEY */
/* we could define it this way */
#define setttype(obj, _tt) ( ttype_sig(obj) = add_sig(_tt) )
#endif // #ifndef LUA_PACK_VALUE

#define iscollectable(o)	(ttype(o) >= LUA_TSTRING)



typedef TValue *StkId;  /* index to stack elements */


/*
** String headers for string table
*/
typedef union TString {
  L_Umaxalign dummy;  /* ensures maximum alignment for strings */
  struct {
    CommonHeader;
    unsigned int hash;
    size_t len;
  } tsv;
} TString;


#define getstr(ts)	(((ts)->tsv.marked & READONLYMASK) ? cast(const char *, *(const char**)((ts) + 1)) : cast(const char *, (ts) + 1))
#define svalue(o)       getstr(rawtsvalue(o))



typedef union Udata {
  L_Umaxalign dummy;  /* ensures maximum alignment for `local' udata */
  struct {
    CommonHeader;
    struct Table *metatable;
    struct Table *env;
    size_t len;
  } uv;
} Udata;




/*
** Function Prototypes
*/
typedef struct Proto {
  CommonHeader;
  TValue *k;  /* constants used by the function */
  Instruction *code;
  struct Proto **p;  /* functions defined inside the function */
  int *lineinfo;  /* map from opcodes to source lines */
  struct LocVar *locvars;  /* information about local variables */
  TString **upvalues;  /* upvalue names */
  TString  *source;
  int sizeupvalues;
  int sizek;  /* size of `k' */
  int sizecode;
  int sizelineinfo;
  int sizep;  /* size of `p' */
  int sizelocvars;
  int linedefined;
  int lastlinedefined;
  GCObject *gclist;
  lu_byte nups;  /* number of upvalues */
  lu_byte numparams;
  lu_byte is_vararg;
  lu_byte maxstacksize;
} Proto;


/* masks for new-style vararg */
#define VARARG_HASARG		1
#define VARARG_ISVARARG		2
#define VARARG_NEEDSARG		4


typedef struct LocVar {
  TString *varname;
  int startpc;  /* first point where variable is active */
  int endpc;    /* first point where variable is dead */
} LocVar;



/*
** Upvalues
*/

typedef struct UpVal {
  CommonHeader;
  TValue *v;  /* points to stack or to its own value */
  union {
    TValue value;  /* the value (when closed) */
    struct {  /* double linked list (when open) */
      struct UpVal *prev;
      struct UpVal *next;
    } l;
  } u;
} UpVal;


/*
** Closures
*/

#define ClosureHeader \
	CommonHeader; lu_byte isC; lu_byte nupvalues; GCObject *gclist; \
	struct Table *env

typedef struct CClosure {
  ClosureHeader;
  lua_CFunction f;
  TValue upvalue[1];
} CClosure;


typedef struct LClosure {
  ClosureHeader;
  struct Proto *p;
  UpVal *upvals[1];
} LClosure;


typedef union Closure {
  CClosure c;
  LClosure l;
} Closure;


#define iscfunction(o)	((ttype(o) == LUA_TFUNCTION && clvalue(o)->c.isC)||(ttype(o)==LUA_TLIGHTFUNCTION))
#define isLfunction(o)	(ttype(o) == LUA_TFUNCTION && !clvalue(o)->c.isC)


/*
** Tables
*/

#ifndef LUA_PACK_VALUE
typedef union TKey {
  struct {
    TValuefields;
    struct Node *next;  /* for chaining */
  } nk;
  TValue tvk;
} TKey;

#define LUA_TKEY_NIL {LUA_TVALUE_NIL, NULL}
#else // #ifndef LUA_PACK_VALUE
typedef struct TKey {
  TValue tvk;
  struct {
     struct Node *next; /* for chaining */
  } nk;
} TKey;

#define LUA_TKEY_NIL {LUA_TVALUE_NIL}, {NULL}
#endif // #ifndef LUA_PACK_VALUE

typedef struct Node {
  TValue i_val;
  TKey i_key;
} Node;


typedef struct Table {
  CommonHeader;
  lu_byte flags;  /* 1<<p means tagmethod(p) is not present */ 
  lu_byte lsizenode;  /* log2 of size of `node' array */
  struct Table *metatable;
  TValue *array;  /* array part */
  Node *node;
  Node *lastfree;  /* any free position is before this position */
  GCObject *gclist;
  int sizearray;  /* size of `array' array */
} Table;


/*
** `module' operation for hashing (size is always a power of 2)
*/
#define lmod(s,size) \
	(check_exp((size&(size-1))==0, (cast(int, (s) & ((size)-1)))))


#define twoto(x)	(1<<(x))
#define sizenode(t)	(twoto((t)->lsizenode))


#define luaO_nilobject		(&luaO_nilobject_)

LUAI_DATA const TValue luaO_nilobject_;

#define ceillog2(x)	(luaO_log2((x)-1) + 1)

LUAI_FUNC int luaO_log2 (unsigned int x);
LUAI_FUNC int luaO_int2fb (unsigned int x);
LUAI_FUNC int luaO_fb2int (int x);
LUAI_FUNC int luaO_rawequalObj (const TValue *t1, const TValue *t2);
LUAI_FUNC int luaO_str2d (const char *s, lua_Number *result);
LUAI_FUNC const char *luaO_pushvfstring (lua_State *L, const char *fmt,
                                                       va_list argp);
LUAI_FUNC const char *luaO_pushfstring (lua_State *L, const char *fmt, ...);
LUAI_FUNC void luaO_chunkid (char *out, const char *source, size_t len);


#endif

