/*
 * Copyright (c) 2004, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the uIP TCP/IP stack
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: memb.h,v 1.1 2006/06/12 08:21:43 adam Exp $
 */

/**
 * \defgroup memb Memory block management functions
 *
 * The memory block allocation routines provide a simple yet powerful
 * set of functions for managing a set of memory blocks of fixed
 * size. A set of memory blocks is statically declared with the
 * MEMB() macro. Memory blocks are allocated from the declared
 * memory by the memb_alloc() function, and are deallocated with the
 * memb_free() function.
 *
 * \note Because of namespace clashes only one MEMB() can be
 * declared per C module, and the name scope of a MEMB() memory
 * block is local to each C module.
 *
 * The following example shows how to declare and use a memory block
 * called "cmem" which has 8 chunks of memory with each memory chunk
 * being 20 bytes large.
 *
 * @{
 */


/**
 * \file
 *         Memory block allocation routines.
 * \author
 *         Adam Dunkels <adam@sics.se>
 *
 */

#ifndef __MEMB_H__
#define __MEMB_H__

/*
 * Here we define a C preprocessing macro for concatenating to
 * strings. We need use two macros in order to allow concatenation of
 * two #defined macros.
 */
#define MEMB_CONCAT2(s1, s2) s1##s2
#define MEMB_CONCAT(s1, s2) MEMB_CONCAT2(s1, s2)

/**
 * Declare a memory block.
 *
 * This macro is used to staticall declare a block of memory that can
 * be used by the block allocation functions. The macro statically
 * declares a C array with a size that matches the specified number of
 * blocks and their individual sizes.
 *
 * Example:
 \code
MEMB(connections, sizeof(struct connection), 16);
 \endcode
 *
 * \param name The name of the memory block (later used with
 * memb_init(), memb_alloc() and memb_free()).
 *
 * \param size The size of each memory chunk, in bytes.
 *
 * \param num The total number of memory chunks in the block.
 *
 */
#define MEMB(name, structure, num) \
        static char MEMB_CONCAT(name,_memb_count)[num]; \
        static structure MEMB_CONCAT(name,_memb_mem)[num]; \
        static struct memb_blocks name = {sizeof(structure), num, \
                                          MEMB_CONCAT(name,_memb_count), \
                                          (void *)MEMB_CONCAT(name,_memb_mem)}

struct memb_blocks {
  unsigned short size;
  unsigned short num;
  char *count;
  void *mem;
};

/**
 * Initialize a memory block that was declared with MEMB().
 *
 * \param m A memory block previosly declared with MEMB().
 */
void  memb_init(struct memb_blocks *m);

/**
 * Allocate a memory block from a block of memory declared with MEMB().
 *
 * \param m A memory block previosly declared with MEMB().
 */
void *memb_alloc(struct memb_blocks *m);

/**
 * Deallocate a memory block from a memory block previously declared
 * with MEMB().
 *
 * \param m m A memory block previosly declared with MEMB().
 *
 * \param ptr A pointer to the memory block that is to be deallocated.
 *
 * \return The new reference count for the memory block (should be 0
 * if successfully deallocated) or -1 if the pointer "ptr" did not
 * point to a legal memory block.
 */
char  memb_free(struct memb_blocks *m, void *ptr);

/** @} */

#endif /* __MEMB_H__ */
