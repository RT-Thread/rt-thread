// See LICENSE for license details.

#include "sifive/devices/plic.h"
#include "plic/plic_driver.h"
#include "platform.h"
#include "encoding.h"
#include <string.h>


// Note that there are no assertions or bounds checking on these
// parameter values.

void volatile_memzero(uint8_t * base, unsigned int size)
{
  volatile uint8_t * ptr;
  for (ptr = base; ptr < (base + size); ptr++){
    *ptr = 0;
  }
}

void PLIC_init (
                plic_instance_t * this_plic,
                uintptr_t         base_addr,
                uint32_t num_sources,
                uint32_t num_priorities
                )
{

  this_plic->base_addr = base_addr;
  this_plic->num_sources = num_sources;
  this_plic->num_priorities = num_priorities;

  // Disable all interrupts (don't assume that these registers are reset).
  unsigned long hart_id = read_csr(mhartid);
  volatile_memzero((uint8_t*) (this_plic->base_addr +
                               PLIC_ENABLE_OFFSET +
                               (hart_id << PLIC_ENABLE_SHIFT_PER_TARGET)),
                   (num_sources + 8) / 8);

  // Set all priorities to 0 (equal priority -- don't assume that these are reset).
  volatile_memzero ((uint8_t *)(this_plic->base_addr +
                                PLIC_PRIORITY_OFFSET),
                    (num_sources + 1) << PLIC_PRIORITY_SHIFT_PER_SOURCE);

  // Set the threshold to 0.
  volatile plic_threshold* threshold = (plic_threshold*)
    (this_plic->base_addr +
     PLIC_THRESHOLD_OFFSET +
     (hart_id << PLIC_THRESHOLD_SHIFT_PER_TARGET));

  *threshold = 0;

}

void PLIC_set_threshold (plic_instance_t * this_plic,
             plic_threshold threshold){

  unsigned long hart_id = read_csr(mhartid);
  volatile plic_threshold* threshold_ptr = (plic_threshold*) (this_plic->base_addr +
                                                              PLIC_THRESHOLD_OFFSET +
                                                              (hart_id << PLIC_THRESHOLD_SHIFT_PER_TARGET));

  *threshold_ptr = threshold;

}


void PLIC_enable_interrupt (plic_instance_t * this_plic, plic_source source){

  unsigned long hart_id = read_csr(mhartid);
  volatile uint8_t * current_ptr = (volatile uint8_t *)(this_plic->base_addr +
                                                        PLIC_ENABLE_OFFSET +
                                                        (hart_id << PLIC_ENABLE_SHIFT_PER_TARGET) +
                                                        (source >> 3));
  uint8_t current = *current_ptr;
  current = current | ( 1 << (source & 0x7));
  *current_ptr = current;

}

void PLIC_disable_interrupt (plic_instance_t * this_plic, plic_source source){

  unsigned long hart_id = read_csr(mhartid);
  volatile uint8_t * current_ptr = (volatile uint8_t *) (this_plic->base_addr +
                                                         PLIC_ENABLE_OFFSET +
                                                         (hart_id << PLIC_ENABLE_SHIFT_PER_TARGET) +
                                                         (source >> 3));
  uint8_t current = *current_ptr;
  current = current & ~(( 1 << (source & 0x7)));
  *current_ptr = current;

}

void PLIC_set_priority (plic_instance_t * this_plic, plic_source source, plic_priority priority){

  if (this_plic->num_priorities > 0) {
    volatile plic_priority * priority_ptr = (volatile plic_priority *)
      (this_plic->base_addr +
       PLIC_PRIORITY_OFFSET +
       (source << PLIC_PRIORITY_SHIFT_PER_SOURCE));
    *priority_ptr = priority;
  }
}

plic_source PLIC_claim_interrupt(plic_instance_t * this_plic){

  unsigned long hart_id = read_csr(mhartid);

  volatile plic_source * claim_addr = (volatile plic_source * )
    (this_plic->base_addr +
     PLIC_CLAIM_OFFSET +
     (hart_id << PLIC_CLAIM_SHIFT_PER_TARGET));

  return  *claim_addr;

}

void PLIC_complete_interrupt(plic_instance_t * this_plic, plic_source source){

  unsigned long hart_id = read_csr(mhartid);
  volatile plic_source * claim_addr = (volatile plic_source *) (this_plic->base_addr +
                                                                PLIC_CLAIM_OFFSET +
                                                                (hart_id << PLIC_CLAIM_SHIFT_PER_TARGET));
  *claim_addr = source;

}

