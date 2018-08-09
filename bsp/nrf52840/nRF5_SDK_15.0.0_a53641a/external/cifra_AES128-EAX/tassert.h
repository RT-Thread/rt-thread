/*
 * cifra - embedded cryptography library
 * Written in 2014 by Joseph Birr-Pixton <jpixton@gmail.com>
 *
 * To the extent possible under law, the author(s) have dedicated all
 * copyright and related and neighboring rights to this software to the
 * public domain worldwide. This software is distributed without any
 * warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication
 * along with this software. If not, see
 * <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#ifndef TASSERT_H
#define TASSERT_H

/* Tiny assert
 * -----------
 *
 * This is an assert(3) definition which doesn't include any
 * strings, but just branches to abort(3) on failure.
 */

#ifndef FULL_FAT_ASSERT
# include <stdlib.h>
# define assert(expr) do { if (!(expr)) abort(); } while (0)
#else
# include <assert.h>
#endif

#endif
