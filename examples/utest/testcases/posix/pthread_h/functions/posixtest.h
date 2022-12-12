/*
 * Copyright (c) 2002, Intel Corporation. All rights reserved.
 * Created by:  julie.n.fleischer REMOVE-THIS AT intel DOT com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.
 */

/*
 * return codes
 */

#define PTS_PASS        0
#define PTS_FAIL        1
#define PTS_UNRESOLVED  2
#define PTS_UNSUPPORTED 4
#define PTS_UNTESTED    5

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#endif

#define PTS_ATTRIBUTE_NORETURN      __attribute__((noreturn))
#define PTS_ATTRIBUTE_UNUSED        __attribute__((unused))
#define PTS_ATTRIBUTE_UNUSED_RESULT __attribute__((warn_unused_result))
