#ifndef _VDSO_DATAPAGE_H
#define _VDSO_DATAPAGE_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#include <time.h>
#include "vdso_config.h"

typedef struct {

    uint64_t realTimeSec;
    uint64_t realTimeNsec;
    uint64_t monoTimeSec;
    uint64_t monoTimeNsec;

    uint64_t lockCount;
} VdsoDataPage;

#define MAX_CLOCKS			16

#define VDSO_BASES	(CLOCK_TAI + 1)
#define VDSO_REALTIME	(BIT(CLOCK_REALTIME)	| \
			 BIT(CLOCK_REALTIME_COARSE))
#define VDSO_MONOTIME	(BIT(CLOCK_MONOTONIC)	| \
			 BIT(CLOCK_MONOTONIC_COARSE)        | \
             BIT(CLOCK_MONOTONIC_RAW)           | \
             BIT(CLOCK_BOOTTIME))

#define CS_HRES_COARSE	0
#define CS_RAW		1
#define CS_BASES	(CS_RAW + 1)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _VDSO_DATAPAGE_H */