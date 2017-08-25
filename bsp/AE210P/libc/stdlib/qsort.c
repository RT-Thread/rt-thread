//
// qsort.c
//
// Quick sort
//
// Copyright (C) 2002 Michael Ringgaard. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 
// 1. Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimer.  
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.  
// 3. Neither the name of the project nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission. 
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
// SUCH DAMAGE.
// 

#define CUTOFF 8

static void shortsort(char *lo, char *hi, unsigned width, int (*comp)(const void *, const void *));
static void swap(char *p, char *q, unsigned int width);

__attribute__((used))
void qsort(void *base, unsigned num, unsigned width, int (*comp)(const void *, const void *))
{
  char *lo, *hi;
  char *mid;
  char *loguy, *higuy;
  unsigned size;
  char *lostk[30], *histk[30];
  int stkptr;

  if (num < 2 || width == 0) return;
  stkptr = 0;

  lo = base;
  hi = (char *) base + width * (num - 1);

recurse:
  size = (hi - lo) / width + 1;

  if (size <= CUTOFF) 
  {
    shortsort(lo, hi, width, comp);
  }
  else 
  {
    mid = lo + (size / 2) * width;
    swap(mid, lo, width);

    loguy = lo;
    higuy = hi + width;

    for (;;) 
    {
      do { loguy += width; } while (loguy <= hi && comp(loguy, lo) <= 0);
      do { higuy -= width; } while (higuy > lo && comp(higuy, lo) >= 0);
      if (higuy < loguy) break;
      swap(loguy, higuy, width);
    }

    swap(lo, higuy, width);

    if (higuy - 1 - lo >= hi - loguy) 
    {
      if (lo + width < higuy) 
      {
	lostk[stkptr] = lo;
	histk[stkptr] = higuy - width;
	++stkptr;
      }

      if (loguy < hi) 
      {
	lo = loguy;
	goto recurse;
      }
    }
    else
    {
      if (loguy < hi) 
      {
        lostk[stkptr] = loguy;
        histk[stkptr] = hi;
        ++stkptr;
      }

      if (lo + width < higuy) 
      {
      	hi = higuy - width;
      	goto recurse;
      }
    }
  }

  --stkptr;
  if (stkptr >= 0) 
  {
    lo = lostk[stkptr];
    hi = histk[stkptr];
    goto recurse;
  }
  else
    return;
}

static void shortsort(char *lo, char *hi, unsigned width, int (*comp)(const void *, const void *))
{
  char *p, *max;

  while (hi > lo) 
  {
    max = lo;
    for (p = lo+width; p <= hi; p += width) if (comp(p, max) > 0) max = p;
    swap(max, hi, width);
    hi -= width;
  }
}

static void swap(char *a, char *b, unsigned width)
{
  char tmp;

  if (a != b)
  {
    while (width--) 
    {
      tmp = *a;
      *a++ = *b;
      *b++ = tmp;
    }
  }
}
