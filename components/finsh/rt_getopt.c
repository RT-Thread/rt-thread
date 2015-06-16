/*	$OpenBSD: getopt_long.c,v 1.21 2006/09/22 17:22:05 millert Exp $	*/
/*	$NetBSD: getopt_long.c,v 1.15 2002/01/31 22:43:40 tv Exp $	*/

/*
 * Copyright (c) 2002 Todd C. Miller <Todd.Miller@courtesan.com>
 * Copyright (c) 2012 William Pitcock
 * Copyright (c) 2012 rofl0r
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Sponsored in part by the Defense Advanced Research Projects
 * Agency (DARPA) and Air Force Research Laboratory, Air Force
 * Materiel Command, USAF, under agreement number F39502-99-1-0512.
 */
/*-
 * Copyright (c) 2000 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Dieter Baron and Thomas Klausner.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *        This product includes software developed by the NetBSD
 *        Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "rt_getopt.h"


#if 1
# define GNU_COMPATIBLE		/* Be more compatible, configure's use us! */
#endif

int	rt_optind = 1;		/* index into parent argv vector */
int	rt_optopt = '?';		/* character checked for validity */
int	rt_optreset;		/* reset getopt */
char    *rt_optarg;		/* argument associated with option */

char* argv0 = RT_NULL;

#define PRINT_ERROR	((rt_opterr) && (*options != ':'))

#define FLAG_PERMUTE	0x01	/* permute non-options to the end of argv */
#define FLAG_ALLARGS	0x02	/* treat non-options as args to option "-1" */
#define FLAG_LONGONLY	0x04	/* operate as getopt_long_only */

/* return values */
#define	BADCH		(int)'?'
#define	BADARG		((*options == ':') ? (int)':' : (int)'?')
#define	INORDER 	(int)1

#define	EMSG		""

#ifdef GNU_COMPATIBLE
#define NO_PREFIX	(-1)
#define D_PREFIX	0
#define DD_PREFIX	1
#define W_PREFIX	2
#endif

static int getopt_internal(int, char * const *, const char *,
			   const struct rt_option *, int *, int);
static int parse_long_options(char * const *, const char *,
			      const struct rt_option *, int *, int, int);
static int gcd(int, int);
static void permute_args(int, int, int, char * const *);

static char *place = EMSG; /* option letter processing */

/* XXX: set rt_optreset to 1 rather than these two */
static int nonopt_start = -1; /* first non option argument (for permute) */
static int nonopt_end = -1;   /* first option after non options (for permute) */

/* Error messages */
static const char recargchar[] = "option requires an argument -- %c";
static const char illoptchar[] = "illegal option -- %c"; /* From P1003.2 */
#ifdef GNU_COMPATIBLE
static int dash_prefix = NO_PREFIX;
static const char gnuoptchar[] = "invalid option -- %c";

static const char recargstring[] = "option `%s%s' requires an argument";
static const char ambig[] = "option `%s%.*s' is ambiguous";
static const char noarg[] = "option `%s%.*s' doesn't allow an argument";
static const char illoptstring[] = "unrecognized option `%s%s'";
#else
static const char recargstring[] = "option requires an argument -- %s";
static const char ambig[] = "ambiguous option -- %.*s";
static const char noarg[] = "option doesn't take an argument -- %.*s";
static const char illoptstring[] = "unknown option -- %s";
#endif

/*
 * Compute the greatest common divisor of a and b.
 */
static int
gcd(int a, int b)
{
	int c;

	c = a % b;
	while (c != 0) {
		a = b;
		b = c;
		c = a % b;
	}

	return (b);
}

/*
 * Exchange the block from nonopt_start to nonopt_end with the block
 * from nonopt_end to opt_end (keeping the same order of arguments
 * in each block).
 */
static void
permute_args(int panonopt_start, int panonopt_end, int opt_end,
	char * const *nargv)
{
	int cstart, cyclelen, i, j, ncycle, nnonopts, nopts, pos;
	char *swap;

	/*
	 * compute lengths of blocks and number and size of cycles
	 */
	nnonopts = panonopt_end - panonopt_start;
	nopts = opt_end - panonopt_end;
	ncycle = gcd(nnonopts, nopts);
	cyclelen = (opt_end - panonopt_start) / ncycle;

	for (i = 0; i < ncycle; i++) {
		cstart = panonopt_end+i;
		pos = cstart;
		for (j = 0; j < cyclelen; j++) {
			if (pos >= panonopt_end)
				pos -= nnonopts;
			else
				pos += nopts;
			swap = nargv[pos];
			/* LINTED const cast */
			((char **) nargv)[pos] = nargv[cstart];
			/* LINTED const cast */
			((char **)nargv)[cstart] = swap;
		}
	}
}

/*
 * parse_long_options --
 *	Parse long options in argc/argv argument vector.
 * Returns -1 if short_too is set and the option does not match long_options.
 */
static int
parse_long_options(char * const *nargv, const char *options,
	const struct rt_option *long_options, int *idx, int short_too, int flags)
{
	char *current_argv, *has_equal;
#ifdef GNU_COMPATIBLE
	char *current_dash;
#endif
	rt_size_t current_argv_len;
	int i, match, exact_match, second_partial_match;

	current_argv = place;
#ifdef GNU_COMPATIBLE
	switch (dash_prefix) {
		case D_PREFIX:
			current_dash = "-";
			break;
		case DD_PREFIX:
			current_dash = "--";
			break;
		case W_PREFIX:
			current_dash = "-W ";
			break;
		default:
			current_dash = "";
			break;
	}
#endif
	match = -1;
	exact_match = 0;
	second_partial_match = 0;

	rt_optind++;

	if ((has_equal = rt_strchr(current_argv, '=')) != RT_NULL) {
		/* argument found (--option=arg) */
		current_argv_len = has_equal - current_argv;
		has_equal++;
	} else
		current_argv_len = rt_strlen(current_argv);

	for (i = 0; long_options[i].name; i++) {
		/* find matching long option */
		if (rt_strncmp(current_argv, long_options[i].name,
		    current_argv_len))
			continue;

		if (rt_strlen(long_options[i].name) == current_argv_len) {
			/* exact match */
			match = i;
			exact_match = 1;
			break;
		}
		/*
		 * If this is a known short option, don't allow
		 * a partial match of a single character.
		 */
		if (short_too && current_argv_len == 1)
			continue;

		if (match == -1)        /* first partial match */
			match = i;
		else if ((flags & FLAG_LONGONLY) ||
			 long_options[i].has_arg !=
			     long_options[match].has_arg ||
			 long_options[i].flag != long_options[match].flag ||
			 long_options[i].val != long_options[match].val)
			second_partial_match = 1;
	}
	if (!exact_match && second_partial_match) {
		/* ambiguous abbreviation */
		if (PRINT_ERROR) {
			rt_kprintf("pkgconf: ");
			rt_kprintf(ambig,
#ifdef GNU_COMPATIBLE
			     current_dash,
#endif
			     (int)current_argv_len,
			     current_argv);
			rt_kprintf("\n");
		}
		rt_optopt = 0;
		return (BADCH);
	}
	if (match != -1) {		/* option found */
		if (long_options[match].has_arg == no_argument
		    && has_equal) {
			if (PRINT_ERROR) {
				rt_kprintf("pkgconf: ");
				rt_kprintf(noarg,
#ifdef GNU_COMPATIBLE
				     current_dash,
#endif
				     (int)current_argv_len,
				     current_argv);
				rt_kprintf("\n");
			}
			/*
			 * XXX: GNU sets rt_optopt to val regardless of flag
			 */
			if (long_options[match].flag == RT_NULL)
				rt_optopt = long_options[match].val;
			else
				rt_optopt = 0;
#ifdef GNU_COMPATIBLE
			return (BADCH);
#else
			return (BADARG);
#endif
		}
		if (long_options[match].has_arg == required_argument ||
		    long_options[match].has_arg == optional_argument) {
			if (has_equal)
				rt_optarg = has_equal;
			else if (long_options[match].has_arg ==
			    required_argument) {
				/*
				 * optional argument doesn't use next nargv
				 */
				rt_optarg = nargv[rt_optind++];
			}
		}
		if ((long_options[match].has_arg == required_argument)
		    && (rt_optarg == RT_NULL)) {
			/*
			 * Missing argument; leading ':' indicates no error
			 * should be generated.
			 */
			if (PRINT_ERROR) {
				rt_kprintf("pkgconf: ");
				rt_kprintf(recargstring,
#ifdef GNU_COMPATIBLE
				    current_dash,
#endif
				    current_argv);
				rt_kprintf("\n");
			}
			/*
			 * XXX: GNU sets rt_optopt to val regardless of flag
			 */
			if (long_options[match].flag == RT_NULL)
				rt_optopt = long_options[match].val;
			else
				rt_optopt = 0;
			--rt_optind;
			return (BADARG);
		}
	} else {			/* unknown option */
		if (short_too) {
			--rt_optind;
			return (-1);
		}
		if (PRINT_ERROR) {
			rt_kprintf("pkgconf: ");
			rt_kprintf(illoptstring,
#ifdef GNU_COMPATIBLE
			      current_dash,
#endif
			      current_argv);
			rt_kprintf("\n");
		}
		rt_optopt = 0;
		return (BADCH);
	}
	if (idx)
		*idx = match;
	if (long_options[match].flag) {
		*long_options[match].flag |= long_options[match].val;
		return (0);
	} else
		return (long_options[match].val);
}

/*
 * getopt_internal --
 *	Parse argc/argv argument vector.  Called by user level routines.
 */
static int
getopt_internal(int nargc, char * const *nargv, const char *options,
	const struct rt_option *long_options, int *idx, int flags)
{
	char *oli;				/* option letter list index */
	int optchar, short_too;
	int posixly_correct;	/* no static, can be changed on the fly */
	
	if(!argv0) argv0 = nargv[0];

	if (options == RT_NULL)
		return (-1);

	/*
	 * Disable GNU extensions if POSIXLY_CORRECT is set or options
	 * string begins with a '+'.
	 */
//	posixly_correct = (getenv("POSIXLY_CORRECT") != RT_NULL);
        posixly_correct = RT_TRUE;
#ifdef GNU_COMPATIBLE
	if (*options == '-')
		flags |= FLAG_ALLARGS;
	else if (posixly_correct || *options == '+')
		flags &= ~FLAG_PERMUTE;
#else
	if (posixly_correct || *options == '+')
		flags &= ~FLAG_PERMUTE;
	else if (*options == '-')
		flags |= FLAG_ALLARGS;
#endif
#if HAVE_STRICT_MODE >= 1
	flags &= ~FLAG_PERMUTE;
#endif
	if (*options == '+' || *options == '-')
		options++;

	/*
	 * XXX Some GNU programs (like cvs) set rt_optind to 0 instead of
	 * XXX using rt_optreset.  Work around this braindamage.
	 */
	if (rt_optind == 0)
		rt_optind = rt_optreset = 1;

	rt_optarg = RT_NULL;
	if (rt_optreset)
		nonopt_start = nonopt_end = -1;
start:
	if (rt_optreset || !*place) {		/* update scanning pointer */
		rt_optreset = 0;
		if (rt_optind >= nargc) {          /* end of argument vector */
			place = EMSG;
			if (nonopt_end != -1) {
				/* do permutation, if we have to */
				permute_args(nonopt_start, nonopt_end,
				    rt_optind, nargv);
				rt_optind -= nonopt_end - nonopt_start;
			}
			else if (nonopt_start != -1) {
				/*
				 * If we skipped non-options, set rt_optind
				 * to the first of them.
				 */
				rt_optind = nonopt_start;
			}
			nonopt_start = nonopt_end = -1;
			return (-1);
		}
		if (*(place = nargv[rt_optind]) != '-' ||
#ifdef GNU_COMPATIBLE
		    place[1] == '\0') {
#else
		    (place[1] == '\0' && rt_strchr(options, '-') == RT_NULL)) {
#endif
			place = EMSG;		/* found non-option */
			if (flags & FLAG_ALLARGS) {
				/*
				 * GNU extension:
				 * return non-option as argument to option 1
				 */
				rt_optarg = nargv[rt_optind++];
				return (INORDER);
			}
			if (!(flags & FLAG_PERMUTE)) {
				/*
				 * If no permutation wanted, stop parsing
				 * at first non-option.
				 */
				return (-1);
			}
			/* do permutation */
			if (nonopt_start == -1)
				nonopt_start = rt_optind;
			else if (nonopt_end != -1) {
				permute_args(nonopt_start, nonopt_end,
				    rt_optind, nargv);
				nonopt_start = rt_optind -
				    (nonopt_end - nonopt_start);
				nonopt_end = -1;
			}
			rt_optind++;
			/* process next argument */
			goto start;
		}
		if (nonopt_start != -1 && nonopt_end == -1)
			nonopt_end = rt_optind;

		/*
		 * If we have "-" do nothing, if "--" we are done.
		 */
		if (place[1] != '\0' && *++place == '-' && place[1] == '\0') {
			rt_optind++;
			place = EMSG;
			/*
			 * We found an option (--), so if we skipped
			 * non-options, we have to permute.
			 */
			if (nonopt_end != -1) {
				permute_args(nonopt_start, nonopt_end,
				    rt_optind, nargv);
				rt_optind -= nonopt_end - nonopt_start;
			}
			nonopt_start = nonopt_end = -1;
			return (-1);
		}
	}

	/*
	 * Check long options if:
	 *  1) we were passed some
	 *  2) the arg is not just "-"
	 *  3) either the arg starts with -- we are getopt_long_only()
	 */
	if (long_options != RT_NULL && place != nargv[rt_optind] &&
	    (*place == '-' || (flags & FLAG_LONGONLY))) {
		short_too = 0;
#ifdef GNU_COMPATIBLE
		dash_prefix = D_PREFIX;
#endif
		if (*place == '-') {
			place++;		/* --foo long option */
#ifdef GNU_COMPATIBLE
			dash_prefix = DD_PREFIX;
#endif
		} else if (*place != ':' && rt_strchr(options, *place) != RT_NULL)
			short_too = 1;		/* could be short option too */

		optchar = parse_long_options(nargv, options, long_options,
		    idx, short_too, flags);
		if (optchar != -1) {
			place = EMSG;
			return (optchar);
		}
	}

	if ((optchar = (int)*place++) == (int)':' ||
	    (optchar == (int)'-' && *place != '\0') ||
	    (oli = rt_strchr(options, optchar)) == RT_NULL) {
		/*
		 * If the user specified "-" and  '-' isn't listed in
		 * options, return -1 (non-option) as per POSIX.
		 * Otherwise, it is an unknown option character (or ':').
		 */
		if (optchar == (int)'-' && *place == '\0')
			return (-1);
		if (!*place)
			++rt_optind;
#ifdef GNU_COMPATIBLE
		if (PRINT_ERROR) {
			rt_kprintf("%s: ", argv0);
			rt_kprintf( posixly_correct ? illoptchar : gnuoptchar,
					optchar);
			rt_kprintf("\n");
		}
#else
		if (PRINT_ERROR) {
			rt_kprintf("%s: ", argv0);
			rt_kprintf(illoptchar, optchar);
			rt_kprintf("\n");
		}
#endif
		rt_optopt = optchar;
		return (BADCH);
	}
	if (long_options != RT_NULL && optchar == 'W' && oli[1] == ';') {
		/* -W long-option */
		if (*place)			/* no space */
			/* NOTHING */;
		else if (++rt_optind >= nargc) {	/* no arg */
			place = EMSG;
			if (PRINT_ERROR) {
				rt_kprintf("%s: ", argv0);
				rt_kprintf(recargchar, optchar);
				rt_kprintf("\n");
			}
			rt_optopt = optchar;
			return (BADARG);
		} else				/* white space */
			place = nargv[rt_optind];
#ifdef GNU_COMPATIBLE
		dash_prefix = W_PREFIX;
#endif
		optchar = parse_long_options(nargv, options, long_options,
		    idx, 0, flags);
		place = EMSG;
		return (optchar);
	}
	if (*++oli != ':') {			/* doesn't take argument */
		if (!*place)
			++rt_optind;
	} else {				/* takes (optional) argument */
		rt_optarg = RT_NULL;
		if (*place)			/* no white space */
			rt_optarg = place;
		else if (oli[1] != ':') {	/* arg not optional */
			if (++rt_optind >= nargc) {	/* no arg */
				place = EMSG;
				if (PRINT_ERROR) {
					rt_kprintf("%s: ", argv0);
					rt_kprintf(recargchar, optchar);
					rt_kprintf("\n");
				}
				rt_optopt = optchar;
				return (BADARG);
			} else
				rt_optarg = nargv[rt_optind];
		}
		place = EMSG;
		++rt_optind;
	}
	/* dump back option letter */
	return (optchar);
}

/*
 * getopt --
 *	Parse argc/argv argument vector.
 *
 * [eventually this will replace the BSD getopt]
 */
int
rt_getopt(int nargc, char * const *nargv, const char *options)
{

	/*
	 * We don't pass FLAG_PERMUTE to getopt_internal() since
	 * the BSD getopt(3) (unlike GNU) has never done this.
	 *
	 * Furthermore, since many privileged programs call getopt()
	 * before dropping privileges it makes sense to keep things
	 * as simple (and bug-free) as possible.
	 */
	return (getopt_internal(nargc, nargv, options, RT_NULL, RT_NULL, FLAG_PERMUTE));
}

/*
 * getopt_long --
 *	Parse argc/argv argument vector.
 */
int
rt_getopt_long(int nargc, char * const *nargv, const char *options,
	const struct rt_option *long_options, int *idx)
{

	return (getopt_internal(nargc, nargv, options, long_options, idx,
	    FLAG_PERMUTE));
}

/*
 * getopt_long_only --
 *	Parse argc/argv argument vector.
 */
int
rt_getopt_long_only(int nargc, char * const *nargv, const char *options,
	const struct rt_option *long_options, int *idx)
{

	return (getopt_internal(nargc, nargv, options, long_options, idx,
	    FLAG_PERMUTE|FLAG_LONGONLY));
}
