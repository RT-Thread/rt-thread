/*
** $Id: ldump.c,v 2.8.1.1 2007/12/27 13:02:25 roberto Exp $
** save precompiled Lua chunks
** See Copyright Notice in lua.h
*/

#include <stddef.h>
#include <string.h>

#define ldump_c
#define LUA_CORE

#include "lua.h"

#include "lobject.h"
#include "lstate.h"
#include "lundump.h"

typedef struct {
 lua_State* L;
 lua_Writer writer;
 void* data;
 int strip;
 int status;
 DumpTargetInfo target;
 size_t wrote;
} DumpState;

#define DumpMem(b,n,size,D)	DumpBlock(b,(n)*(size),D)
#define DumpVar(x,D)	 	DumpMem(&x,1,sizeof(x),D)

static void DumpBlock(const void* b, size_t size, DumpState* D)
{
 if (D->status==0)
 {
  lua_unlock(D->L);
  D->status=(*D->writer)(D->L,b,size,D->data);
  D->wrote+=size;
  lua_lock(D->L);
 }
}

static void DumpChar(int y, DumpState* D)
{
 char x=(char)y;
 DumpVar(x,D);
}

static void Align4(DumpState *D)
{
 while(D->wrote&3)
  DumpChar(0,D);
}

static void MaybeByteSwap(char *number, size_t numbersize, DumpState *D)
{
 int x=1;
 int platform_little_endian = *(char*)&x;
 if (platform_little_endian != D->target.little_endian)
 {
  unsigned long i;
  for (i=0; i<numbersize/2; i++)
  {
   char temp = number[i];
   number[i] = number[numbersize-1-i];
   number[numbersize-1-i] = temp;
  }
 }
}

static void DumpIntWithSize(int x, int sizeof_int, DumpState* D)
{
 /* dump signed integer */
 switch(sizeof_int) {
  case 1: {
   if (x>0x7F || x<(-0x80)) D->status=LUA_ERR_CC_INTOVERFLOW; 
   DumpChar(x,D);
  } break;
  case 2: {
   if (x>0x7FFF || x<(-0x8000)) D->status=LUA_ERR_CC_INTOVERFLOW; 
   int16_t y=(int16_t)x;
   MaybeByteSwap((char*)&y,2,D);
   DumpVar(y,D);
  } break;
  case 4: {
   /* Need to reduce bounds by 1 to avoid messing 32-bit compilers up */
   if (x>0x7FFFFFFE || x<(-0x7FFFFFFF)) D->status=LUA_ERR_CC_INTOVERFLOW; 
   int32_t y=(int32_t)x;
   MaybeByteSwap((char*)&y,4,D);
   DumpVar(y,D);
  } break;
  default: lua_assert(0);
 }
}

static void DumpInt(int x, DumpState* D)
{
 DumpIntWithSize(x,D->target.sizeof_int,D);
}

static void DumpSize(uint32_t x, DumpState* D)
{
 /* dump unsigned integer */
 switch(D->target.sizeof_strsize_t) {
  case 1: {
   if (x>0xFF) D->status=LUA_ERR_CC_INTOVERFLOW; 
   DumpChar(x,D);
  } break;
  case 2: {
   if (x>0xFFFF) D->status=LUA_ERR_CC_INTOVERFLOW;
   uint16_t y=(uint16_t)x;
   MaybeByteSwap((char*)&y,2,D);
   DumpVar(y,D);
  } break;
  case 4: {
   /* Reduce bounds to avoid messing 32-bit compilers up */
   if (x>0xFFFFFFFE) D->status=LUA_ERR_CC_INTOVERFLOW;
   uint32_t y=x;
   MaybeByteSwap((char*)&y,4,D);
   DumpVar(y,D);
  } break;
  default: lua_assert(0);
 }
}

static void DumpNumber(lua_Number x, DumpState* D)
{
#if defined( LUA_NUMBER_INTEGRAL ) && !defined( LUA_CROSS_COMPILER )
  DumpIntWithSize(x,D->target.sizeof_lua_Number,D);
#else // #if defined( LUA_NUMBER_INTEGRAL ) && !defined( LUA_CROSS_COMPILER )
 if (D->target.lua_Number_integral)
 {
  if (((float)(int)x)!=x) D->status=LUA_ERR_CC_NOTINTEGER;
  DumpIntWithSize(x,D->target.sizeof_lua_Number,D);
 }
 else
 {
  switch(D->target.sizeof_lua_Number)
  {
   /* do we need bounds checking? */
   case 4: {
    float y=x;
    MaybeByteSwap((char*)&y,4,D);
    DumpVar(y,D);
   } break;
   case 8: {
    double y=x;
    // ARM FPA mode: keep endianness, but swap high and low parts of the 
    // memory representation. This is the default compilation mode for ARM 
    // targets with non-EABI gcc
    if(D->target.is_arm_fpa)
    {
      char *pnum=(char*)&y, temp[4];
      memcpy(temp,pnum,4);
      memcpy(pnum,pnum+4,4);
      memcpy(pnum+4,temp,4);
    }    
    MaybeByteSwap((char*)&y,8,D);
    DumpVar(y,D);
   } break;
   default: lua_assert(0);
  }
 }
#endif // #if defined( LUA_NUMBER_INTEGRAL ) && !defined( LUA_CROSS_COMPILER )
}

static void DumpCode(const Proto *f, DumpState* D)
{
 DumpInt(f->sizecode,D);
 char buf[10];
 int i;
 Align4(D);
 for (i=0; i<f->sizecode; i++)
 {
  memcpy(buf,&f->code[i],sizeof(Instruction));
  MaybeByteSwap(buf,sizeof(Instruction),D);
  DumpBlock(buf,sizeof(Instruction),D);
 }
}

static void DumpString(const TString* s, DumpState* D)
{
 if (s==NULL || getstr(s)==NULL)
 {
  strsize_t size=0;
  DumpSize(size,D);
 }
 else
 {
  strsize_t size=( strsize_t )s->tsv.len+1;		/* include trailing '\0' */
  DumpSize(size,D);
  DumpBlock(getstr(s),size,D);
 }
}

static void DumpFunction(const Proto* f, const TString* p, DumpState* D);

static void DumpConstants(const Proto* f, DumpState* D)
{
 int i,n=f->sizek;
 DumpInt(n,D);
 for (i=0; i<n; i++)
 {
  const TValue* o=&f->k[i];
  DumpChar(ttype(o),D);
  switch (ttype(o))
  {
   case LUA_TNIL:
	break;
   case LUA_TBOOLEAN:
	DumpChar(bvalue(o),D);
	break;
   case LUA_TNUMBER:
	DumpNumber(nvalue(o),D);
	break;
   case LUA_TSTRING:
	DumpString(rawtsvalue(o),D);
	break;
   default:
	lua_assert(0);			/* cannot happen */
	break;
  }
 }
 n=f->sizep;
 DumpInt(n,D);
 for (i=0; i<n; i++) DumpFunction(f->p[i],f->source,D);
}

static void DumpDebug(const Proto* f, DumpState* D)
{
 int i,n;
 n= (D->strip) ? 0 : f->sizelineinfo;
 DumpInt(n,D);
 Align4(D);
 for (i=0; i<n; i++)
 {
  DumpInt(f->lineinfo[i],D);
 }
 
 n= (D->strip) ? 0 : f->sizelocvars;
 DumpInt(n,D);
 for (i=0; i<n; i++)
 {
  DumpString(f->locvars[i].varname,D);
  DumpInt(f->locvars[i].startpc,D);
  DumpInt(f->locvars[i].endpc,D);
 }

 n= (D->strip) ? 0 : f->sizeupvalues;
 DumpInt(n,D);
 for (i=0; i<n; i++) DumpString(f->upvalues[i],D);
}

static void DumpFunction(const Proto* f, const TString* p, DumpState* D)
{
 DumpString((f->source==p || D->strip) ? NULL : f->source,D);
 DumpInt(f->linedefined,D);
 DumpInt(f->lastlinedefined,D);
 DumpChar(f->nups,D);
 DumpChar(f->numparams,D);
 DumpChar(f->is_vararg,D);
 DumpChar(f->maxstacksize,D);
 DumpCode(f,D);
 DumpConstants(f,D);
 DumpDebug(f,D);
}

static void DumpHeader(DumpState* D)
{
 char buf[LUAC_HEADERSIZE];
 char *h=buf;
 
 /* This code must be kept in sync wiht luaU_header */
 memcpy(h,LUA_SIGNATURE,sizeof(LUA_SIGNATURE)-1);
 h+=sizeof(LUA_SIGNATURE)-1;
 *h++=(char)LUAC_VERSION;
 *h++=(char)LUAC_FORMAT;
 *h++=(char)D->target.little_endian;
 *h++=(char)D->target.sizeof_int;
 *h++=(char)D->target.sizeof_strsize_t;
 *h++=(char)sizeof(Instruction);
 *h++=(char)D->target.sizeof_lua_Number;
 *h++=(char)D->target.lua_Number_integral;
 
 DumpBlock(buf,LUAC_HEADERSIZE,D);
}

/*
** dump Lua function as precompiled chunk with specified target
*/
int luaU_dump_crosscompile (lua_State* L, const Proto* f, lua_Writer w, void* data, int strip, DumpTargetInfo target)
{
 DumpState D;
 D.L=L;
 D.writer=w;
 D.data=data;
 D.strip=strip;
 D.status=0;
 D.target=target;
 D.wrote=0;
 DumpHeader(&D);
 DumpFunction(f,NULL,&D);
 return D.status;
}

/*
 ** dump Lua function as precompiled chunk with local machine as target
 */
int luaU_dump (lua_State* L, const Proto* f, lua_Writer w, void* data, int strip)
{
 DumpTargetInfo target;
 int test=1;
 target.little_endian=*(char*)&test;
 target.sizeof_int=sizeof(int);
 target.sizeof_strsize_t=sizeof(strsize_t);
 target.sizeof_lua_Number=sizeof(lua_Number);
 target.lua_Number_integral=(((lua_Number)0.5)==0);
 target.is_arm_fpa=0;
 return luaU_dump_crosscompile(L,f,w,data,strip,target);
}
