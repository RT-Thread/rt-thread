/*
 * magic.c - PPP Magic Number routines.
 *
 * Copyright (c) 1984-2000 Carnegie Mellon University. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The name "Carnegie Mellon University" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For permission or any legal
 *    details, please contact
 *      Office of Technology Transfer
 *      Carnegie Mellon University
 *      5000 Forbes Avenue
 *      Pittsburgh, PA  15213-3890
 *      (412) 268-4387, fax: (412) 268-7395
 *      tech-transfer@andrew.cmu.edu
 *
 * 4. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by Computing Services
 *     at Carnegie Mellon University (http://www.cmu.edu/computing/)."
 *
 * CARNEGIE MELLON UNIVERSITY DISCLAIMS ALL WARRANTIES WITH REGARD TO
 * THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS, IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY BE LIABLE
 * FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
/*****************************************************************************
* randm.c - Random number generator program file.
*
* Copyright (c) 2003 by Marc Boucher, Services Informatiques (MBSI) inc.
* Copyright (c) 1998 by Global Election Systems Inc.
*
* The authors hereby grant permission to use, copy, modify, distribute,
* and license this software and its documentation for any purpose, provided
* that existing copyright notices are retained in all copies and that this
* notice and the following disclaimer are included verbatim in any
* distributions. No written agreement, license, or royalty fee is required
* for any of the authorized uses.
*
* THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS *AS IS* AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL THE CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************
* REVISION HISTORY
*
* 03-01-01 Marc Boucher <marc@mbsi.ca>
*   Ported to lwIP.
* 98-06-03 Guy Lancaster <lancasterg@acm.org>, Global Election Systems Inc.
*   Extracted from avos.
*****************************************************************************/

#include "lwip/opt.h"
#if PPP_SUPPORT /* don't build if not configured for use in lwipopts.h */

#include "netif/ppp/ppp_impl.h"
#include "netif/ppp/magic.h"

#if PPP_MD5_RANDM /* Using MD5 for better randomness if enabled */

#if LWIP_INCLUDED_POLARSSL_MD5
#include "netif/ppp/polarssl/md5.h"
#else
#include "polarssl/md5.h"
#endif

#define MAGIC_RANDPOOLSIZE 16   /* Bytes stored in the pool of randomness. */

/*****************************/
/*** LOCAL DATA STRUCTURES ***/
/*****************************/
static char magic_randpool[MAGIC_RANDPOOLSIZE];   /* Pool of randomness. */
static long magic_randcount = 0;      /* Pseudo-random incrementer */


/***********************************/
/*** PUBLIC FUNCTION DEFINITIONS ***/
/***********************************/

/*
 * Churn the randomness pool on a random event.  Call this early and often
 *  on random and semi-random system events to build randomness in time for
 *  usage.  For randomly timed events, pass a null pointer and a zero length
 *  and this will use the system timer and other sources to add randomness.
 *  If new random data is available, pass a pointer to that and it will be
 *  included.
 *
 * Ref: Applied Cryptography 2nd Ed. by Bruce Schneier p. 427
 */
void magic_churnrand(char *rand_data, u32_t rand_len) {
  md5_context md5;

  /* LWIP_DEBUGF(LOG_INFO, ("magic_churnrand: %u@%P\n", rand_len, rand_data)); */
  md5_starts(&md5);
  md5_update(&md5, (u_char *)magic_randpool, sizeof(magic_randpool));
  if (rand_data) {
    md5_update(&md5, (u_char *)rand_data, rand_len);
  } else {
    struct {
      /* INCLUDE fields for any system sources of randomness */
      u32_t jiffies;
    } sys_data;
    sys_data.jiffies = sys_jiffies();
    /* Load sys_data fields here. */
    md5_update(&md5, (u_char *)&sys_data, sizeof(sys_data));
  }
  md5_finish(&md5, (u_char *)magic_randpool);
/*  LWIP_DEBUGF(LOG_INFO, ("magic_churnrand: -> 0\n")); */
}

/*
 * Initialize the random number generator.
 */
void magic_init() {
  magic_churnrand(NULL, 0);
}

/*
 * Randomize our random seed value.
 */
void magic_randomize(void) {
  magic_churnrand(NULL, 0);
}

/*
 * random_bytes - Fill a buffer with random bytes.
 *
 * Use the random pool to generate random data.  This degrades to pseudo
 *  random when used faster than randomness is supplied using magic_churnrand().
 * Note: It's important that there be sufficient randomness in magic_randpool
 *  before this is called for otherwise the range of the result may be
 *  narrow enough to make a search feasible.
 *
 * Ref: Applied Cryptography 2nd Ed. by Bruce Schneier p. 427
 *
 * XXX Why does he not just call magic_churnrand() for each block?  Probably
 *  so that you don't ever publish the seed which could possibly help
 *  predict future values.
 * XXX Why don't we preserve md5 between blocks and just update it with
 *  magic_randcount each time?  Probably there is a weakness but I wish that
 *  it was documented.
 */
void random_bytes(unsigned char *buf, u32_t buf_len) {
  md5_context md5;
  u_char tmp[16];
  u32_t n;

  while (buf_len > 0) {
    n = LWIP_MIN(buf_len, MAGIC_RANDPOOLSIZE);
    md5_starts(&md5);
    md5_update(&md5, (u_char *)magic_randpool, sizeof(magic_randpool));
    md5_update(&md5, (u_char *)&magic_randcount, sizeof(magic_randcount));
    md5_finish(&md5, tmp);
    magic_randcount++;
    MEMCPY(buf, tmp, n);
    buf += n;
    buf_len -= n;
  }
}

/*
 * Return a new random number.
 */
u32_t magic() {
  u32_t new_rand;

  random_bytes((unsigned char *)&new_rand, sizeof(new_rand));

  return new_rand;
}

#else /* PPP_MD5_RANDM */

/*****************************/
/*** LOCAL DATA STRUCTURES ***/
/*****************************/
static int  magic_randomized = 0;       /* Set when truely randomized. */
static u32_t magic_randomseed = 0;      /* Seed used for random number generation. */


/***********************************/
/*** PUBLIC FUNCTION DEFINITIONS ***/
/***********************************/

/*
 * Initialize the random number generator.
 *
 * Here we attempt to compute a random number seed but even if
 * it isn't random, we'll randomize it later.
 *
 * The current method uses the fields from the real time clock,
 * the idle process counter, the millisecond counter, and the
 * hardware timer tick counter.  When this is invoked
 * in startup(), then the idle counter and timer values may
 * repeat after each boot and the real time clock may not be
 * operational.  Thus we call it again on the first random
 * event.
 */
void magic_init() {
  magic_randomseed += sys_jiffies();

  /* Initialize the Borland random number generator. */
  srand((unsigned)magic_randomseed);
}

/*
 * magic_init - Initialize the magic number generator.
 *
 * Randomize our random seed value.  Here we use the fact that
 * this function is called at *truely random* times by the polling
 * and network functions.  Here we only get 16 bits of new random
 * value but we use the previous value to randomize the other 16
 * bits.
 */
void magic_randomize(void) {
  static u32_t last_jiffies;

  if (!magic_randomized) {
    magic_randomized = !0;
    magic_init();
    /* The initialization function also updates the seed. */
  } else {
    /* magic_randomseed += (magic_randomseed << 16) + TM1; */
    magic_randomseed += (sys_jiffies() - last_jiffies); /* XXX */
  }
  last_jiffies = sys_jiffies();
}

/*
 * Return a new random number.
 *
 * Here we use the Borland rand() function to supply a pseudo random
 * number which we make truely random by combining it with our own
 * seed which is randomized by truely random events.
 * Thus the numbers will be truely random unless there have been no
 * operator or network events in which case it will be pseudo random
 * seeded by the real time clock.
 */
u32_t magic() {
  return ((((u32_t)rand() << 16) + rand()) + magic_randomseed);
}

#endif /* PPP_MD5_RANDM */

#endif /* PPP_SUPPORT */
