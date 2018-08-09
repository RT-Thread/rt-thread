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

#ifndef CF_CONFIG_H
#define CF_CONFIG_H

/**
 * Library configuration
 * =====================
 */

/* .. c:macro:: CF_SIDE_CHANNEL_PROTECTION
 * Define this as 1 if you need all available side channel protections.
 * **This option may alter the ABI**.
 *
 * This has a non-trivial performance penalty.  Where a
 * side-channel free option is cheap or free (like checking
 * a MAC) this is always done in a side-channel free way.
 *
 * The default is **on** for all available protections.
 */
#ifndef CF_SIDE_CHANNEL_PROTECTION
# define CF_SIDE_CHANNEL_PROTECTION 1
#endif

/* .. c:macro:: CF_TIME_SIDE_CHANNEL_PROTECTION
 * Define this as 1 if you need timing/branch prediction side channel
 * protection.
 *
 * You probably want this.  The default is on. */
#ifndef CF_TIME_SIDE_CHANNEL_PROTECTION
# define CF_TIME_SIDE_CHANNEL_PROTECTION CF_SIDE_CHANNEL_PROTECTION
#endif

/* .. c:macro:: CF_CACHE_SIDE_CHANNEL_PROTECTION
 * Define this as 1 if you need cache side channel protection.
 *
 * If you have a microcontroller with no cache, you can turn this off
 * without negative effects.
 *
 * The default is on.  This will have some performance impact,
 * especially on AES.
 */
#ifndef CF_CACHE_SIDE_CHANNEL_PROTECTION
# define CF_CACHE_SIDE_CHANNEL_PROTECTION CF_SIDE_CHANNEL_PROTECTION
#endif

#endif
