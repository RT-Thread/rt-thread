#ifndef __OSC_H__
#define __OSC_H__

#include "hal.h"

#define OVLY_SEG(NAME)  __attribute__((section(#NAME)))

/*
        TYPES OF GENERAL EXCEPTION
*/
#define GE_ALIGN_CHECK                          0
#define GE_RESERVED_INST                        1
#define GE_TRAP                                 2
#define GE_ARITHMETIC                           3
#define GE_PRECISE_BUS_ERR                      4
#define GE_INPRECISE_BUS_ERR                    5
#define GE_COPROCESSOR                          6
#define GE_PRIVILEGE_INST                       7
#define GE_RESERVED_VALUE                       8
#define GE_NON_EXIST_LOCAL_MEM                  9
#define GE_MPZIU_CTRL                           10

/*
        structure of overlay control registers
        Please define this structure based on your hardware design
*/
typedef struct
{
        unsigned int reserved ;
        unsigned int root_size ;
        unsigned int base_addr ;
        unsigned int end_addr ;
        volatile unsigned int dma ;
} OVLY_REGS ;

typedef struct
{
        unsigned long vma;
        unsigned long size;
        unsigned long lma;
        unsigned long mapped;
} OVLY_TABLE ;

typedef struct
{
	unsigned int            ipc;
        OVLY_REGS               *povl;

} OVL_CTRL;

typedef struct {

        hal_queue_t     queue;
        hal_thread_t    th;

	OVL_CTRL		povl_ctrl;

} OSC_DRV_INFO;

/* _novlys from overlay table in linker script stands for number of overlay regions. */
extern int   _novlys;
extern OVLY_TABLE    _ovly_table[] ;
extern char __ovly_lmastart_OVL_RAM;

static volatile int overlay_busy = 0;

void __attribute__((no_prologue)) osc_init();
int _osc_drv_init(void (*handler)(unsigned int ipc),
                   void (*osc_hisr)(void *arg),
                   OSC_DRV_INFO *osc_info);

#ifdef CONFIG_OSC_DEBUG_SUPPORT
#define OVLY_DEBUG
#endif


#endif
