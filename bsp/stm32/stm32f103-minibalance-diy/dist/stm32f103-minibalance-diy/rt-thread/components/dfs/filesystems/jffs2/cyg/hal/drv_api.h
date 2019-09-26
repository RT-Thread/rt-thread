#ifndef CYGONCE_HAL_DRV_API_H
#define CYGONCE_HAL_DRV_API_H

/*==========================================================================
//
//      drv_api.h
//
//      Native API for Kernel
//
//==========================================================================
// ####ECOSGPLCOPYRIGHTBEGIN####                                            
// -------------------------------------------                              
// This file is part of eCos, the Embedded Configurable Operating System.   
// Copyright (C) 1998, 1999, 2000, 2001, 2002 Free Software Foundation, Inc.
//
// eCos is free software; you can redistribute it and/or modify it under    
// the terms of the GNU General Public License as published by the Free     
// Software Foundation; either version 2 or (at your option) any later      
// version.                                                                 
//
// eCos is distributed in the hope that it will be useful, but WITHOUT      
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or    
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    
// for more details.                                                        
//
// You should have received a copy of the GNU General Public License        
// along with eCos; if not, write to the Free Software Foundation, Inc.,    
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.            
//
// As a special exception, if other files instantiate templates or use      
// macros or inline functions from this file, or you compile this file      
// and link it with other works to produce a work based on this file,       
// this file does not by itself cause the resulting work to be covered by   
// the GNU General Public License. However the source code for this file    
// must still be made available in accordance with section (3) of the GNU   
// General Public License v2.                                               
//
// This exception does not invalidate any other reasons why a work based    
// on this file might be covered by the GNU General Public License.         
// -------------------------------------------                              
// ####ECOSGPLCOPYRIGHTEND####                                              
//==========================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):   nickg
// Date:        1999-02-24
// Purpose:     Driver API
// Description: This file defines the API used by device drivers to access
//              system services. When the kernel is present it maps directly
//              to the Kernel C API. When the kernel is absent, it is provided
//              by a set of HAL functions.
//              
// Usage:       #include <cyg/kernel/kapi.h>
//
//####DESCRIPTIONEND####
//
//========================================================================*/

//#include <pkgconf/hal.h>  //mod by prife
#include <cyg/infra/cyg_type.h>

#ifdef CYGPKG_KERNEL

/*------------------------------------------------------------------------*/
/* Kernel co-resident version of API                                      */

#include <pkgconf/kernel.h>

#ifndef CYGFUN_KERNEL_API_C
#error Driver API requres Kernel API to be present
#endif

#include <cyg/kernel/kapi.h>

#define cyg_drv_isr_lock                    cyg_interrupt_disable
#define cyg_drv_isr_unlock                  cyg_interrupt_enable
                                     
#define cyg_drv_dsr_lock                    cyg_scheduler_lock
#define cyg_drv_dsr_unlock                  cyg_scheduler_unlock
                                     
#define cyg_drv_mutex_t                     cyg_mutex_t
#define cyg_drv_mutex_init                  cyg_mutex_init
#define cyg_drv_mutex_destroy               cyg_mutex_destroy
#define cyg_drv_mutex_lock                  cyg_mutex_lock
#define cyg_drv_mutex_trylock               cyg_mutex_trylock
#define cyg_drv_mutex_unlock                cyg_mutex_unlock
#define cyg_drv_mutex_release               cyg_mutex_release
                                     
#define cyg_drv_cond_t                      cyg_cond_t
#define cyg_drv_cond_init                   cyg_cond_init
#define cyg_drv_cond_destroy                cyg_cond_destroy
#define cyg_drv_cond_wait                   cyg_cond_wait
#define cyg_drv_cond_signal                 cyg_cond_signal
#define cyg_drv_cond_broadcast              cyg_cond_broadcast
                                     
#define cyg_drv_interrupt_create            cyg_interrupt_create
#define cyg_drv_interrupt_delete            cyg_interrupt_delete
#define cyg_drv_interrupt_attach            cyg_interrupt_attach
#define cyg_drv_interrupt_detach            cyg_interrupt_detach
#define cyg_drv_interrupt_mask              cyg_interrupt_mask
#define cyg_drv_interrupt_unmask            cyg_interrupt_unmask
#define cyg_drv_interrupt_mask_intunsafe    cyg_interrupt_mask_intunsafe
#define cyg_drv_interrupt_unmask_intunsafe  cyg_interrupt_unmask_intunsafe
#define cyg_drv_interrupt_acknowledge       cyg_interrupt_acknowledge
#define cyg_drv_interrupt_configure         cyg_interrupt_configure
#define cyg_drv_interrupt_level             cyg_interrupt_level
#define cyg_drv_interrupt_set_cpu           cyg_interrupt_set_cpu
#define cyg_drv_interrupt_get_cpu           cyg_interrupt_get_cpu
                                          
#define cyg_drv_spinlock_t                  cyg_spinlock_t
#define cyg_drv_spinlock_init               cyg_spinlock_init
#define cyg_drv_spinlock_spin               cyg_spinlock_spin
#define cyg_drv_spinlock_clear              cyg_spinlock_clear
#define cyg_drv_spinlock_try                cyg_spinlock_try
#define cyg_drv_spinlock_test               cyg_spinlock_test
#define cyg_drv_spinlock_spin_intsave       cyg_spinlock_spin_intsave
#define cyg_drv_spinlock_clear_intsave      cyg_spinlock_clear_intsave

#else /* CYGPKG_KERNEL */

/*------------------------------------------------------------------------*/
/* Non-kernel version of API                                              */
                                          
typedef CYG_ADDRWORD cyg_addrword_t;        /* May hold pointer or word   */
typedef cyg_addrword_t cyg_handle_t;        /* Object handle              */
typedef cyg_uint32   cyg_priority_t;        /* type for priorities        */
typedef cyg_uint32   cyg_vector_t;          /* Interrupt vector id        */
typedef cyg_uint32   cyg_cpu_t;             /* CPU id                     */
typedef int          cyg_bool_t;            
typedef cyg_int32    cyg_code_t;            /* type for various codes     */

typedef cyg_uint32 cyg_ISR_t( cyg_vector_t vector, cyg_addrword_t data);
typedef void cyg_DSR_t(cyg_vector_t vector,
                       cyg_ucount32 count,
                       cyg_addrword_t data);


externC void cyg_drv_isr_lock(void);
externC void cyg_drv_isr_unlock(void);

externC void cyg_drv_dsr_lock(void);
externC void cyg_drv_dsr_unlock(void);

typedef struct
{
    cyg_atomic          lock;
} cyg_drv_mutex_t;

externC void cyg_drv_mutex_init( cyg_drv_mutex_t *mutex );
externC void cyg_drv_mutex_destroy( cyg_drv_mutex_t *mutex );
externC cyg_bool_t cyg_drv_mutex_lock( cyg_drv_mutex_t *mutex );
externC cyg_bool_t cyg_drv_mutex_trylock( cyg_drv_mutex_t *mutex );
externC void cyg_drv_mutex_unlock( cyg_drv_mutex_t *mutex );
externC void cyg_drv_mutex_release( cyg_drv_mutex_t *mutex );

typedef struct
{
    cyg_atomic          wait;
    cyg_drv_mutex_t       *mutex;
} cyg_drv_cond_t;

externC void cyg_drv_cond_init( cyg_drv_cond_t  *cond, cyg_drv_mutex_t *mutex );
externC void cyg_drv_cond_destroy( cyg_drv_cond_t  *cond );
externC cyg_bool_t cyg_drv_cond_wait( cyg_drv_cond_t *cond );
externC void cyg_drv_cond_signal( cyg_drv_cond_t *cond );
externC void cyg_drv_cond_broadcast( cyg_drv_cond_t *cond );

typedef struct cyg_interrupt
{
    cyg_vector_t        vector;
    cyg_priority_t      priority;
    cyg_ISR_t           *isr;
    cyg_DSR_t           *dsr;
    CYG_ADDRWORD        data;

    struct cyg_interrupt* volatile next_dsr;
    volatile cyg_int32             dsr_count;
    
#ifdef CYGIMP_HAL_COMMON_INTERRUPTS_CHAIN
    struct cyg_interrupt *next;
#endif

} cyg_interrupt;

externC void cyg_drv_interrupt_create(
                     cyg_vector_t        vector,
                     cyg_priority_t      priority,
                     cyg_addrword_t      data,
                     cyg_ISR_t           *isr,
                     cyg_DSR_t           *dsr,
                     cyg_handle_t        *handle,
                     cyg_interrupt       *intr
                     );
externC void cyg_drv_interrupt_delete( cyg_handle_t interrupt );
externC void cyg_drv_interrupt_attach( cyg_handle_t interrupt );
externC void cyg_drv_interrupt_detach( cyg_handle_t interrupt );

externC void cyg_drv_interrupt_mask( cyg_vector_t vector );
externC void cyg_drv_interrupt_mask_intunsafe( cyg_vector_t vector );
externC void cyg_drv_interrupt_unmask( cyg_vector_t vector );
externC void cyg_drv_interrupt_unmask_intunsafe( cyg_vector_t vector );
externC void cyg_drv_interrupt_acknowledge( cyg_vector_t vector );
externC void cyg_drv_interrupt_configure(
                     cyg_vector_t        vector,
                     cyg_bool_t          level,
                     cyg_bool_t          up
                     );
externC void cyg_drv_interrupt_level( cyg_vector_t vector, cyg_priority_t level );
externC void cyg_drv_interrupt_set_cpu( cyg_vector_t vector, cyg_cpu_t cpu );
externC cyg_cpu_t cyg_drv_interrupt_get_cpu( cyg_vector_t vector );


enum cyg_ISR_results
{
    CYG_ISR_HANDLED  = 1,               /* Interrupt was handled             */
    CYG_ISR_CALL_DSR = 2                /* Schedule DSR                      */
};


typedef struct
{
    cyg_atomic          lock;
} cyg_drv_spinlock_t;

void cyg_drv_spinlock_init(
    cyg_drv_spinlock_t  *lock,          /* spinlock to initialize            */
    cyg_bool_t          locked          /* init locked or unlocked           */
);

void cyg_drv_spinlock_destroy( cyg_drv_spinlock_t *lock );

void cyg_drv_spinlock_spin( cyg_drv_spinlock_t *lock );

void cyg_drv_spinlock_clear( cyg_drv_spinlock_t *lock );

cyg_bool_t cyg_drv_spinlock_try( cyg_drv_spinlock_t *lock );

cyg_bool_t cyg_drv_spinlock_test( cyg_drv_spinlock_t *lock );

void cyg_drv_spinlock_spin_intsave( cyg_drv_spinlock_t *lock,
                                    cyg_addrword_t *istate );

void cyg_drv_spinlock_clear_intsave( cyg_drv_spinlock_t *lock,
                                     cyg_addrword_t istate );

#endif /* CYGPKG_KERNEL */

/*------------------------------------------------------------------------*/
/* EOF drv_api.h                                                          */
#endif // CYGONCE_HAL_DRV_API_H
