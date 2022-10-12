#ifndef __DRV_SYS_H__
#define __DRV_SYS_H__

#include <rtthread.h>
#include "drv_common.h"
#include "NuMicro.h"

struct nu_module
{
    char      *name;
    void      *m_pvBase;
    uint32_t   u32RstId;
    IRQn_Type  eIRQn;
} ;
typedef struct nu_module *nu_module_t;

typedef struct
{
    vu32     vu32RegAddr;
    vu32     vu32BitMask;
    vu32     vu32Value;
    char    *szName;
} S_NU_REG;

#define NUREG_EXPORT(vu32RegAddr, vu32BitMask, vu32Value)  { vu32RegAddr, vu32BitMask, vu32Value, #vu32Value }

#endif
