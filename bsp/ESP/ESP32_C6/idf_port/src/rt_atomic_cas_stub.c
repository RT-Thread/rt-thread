#include <rtthread.h>

/*
 * spi_common.c claims a bus with
 *     atomic_compare_exchange_strong(&spi_periph_claimed[host], &expected, value)
 * on an _Atomic bool, and an ESP32-C6 core can only reserve a whole word, so
 * this gcc emits a call to the out-of-line helper instead of an lr/sc sequence.
 * The install has no __atomic_compare_exchange_1:
 *     riscv32-esp-elf/bin/../lib/gcc/riscv32-esp-elf/11.2.0/libgcc.a  ->  0 hits
 * and there is no libatomic.a next to it, so the name stays undefined at link
 * time. The prototype below is the one the compiler itself declares -- it
 * rejects any other spelling with -Wbuiltin-declaration-mismatch -- and it
 * matches what the call site really passes: the address of the object, the
 * address of the expected byte, the desired byte, and two memory orders. The
 * `weak` argument is not passed in a register at all (an atomic_compare_exchange
 * weak/strong pair compiles to the same five loads), which is why it is ignored
 * here; the helper's answer is always the strong one, so a weak CAS merely gets
 * one it did not ask for.
 *
 * Masking interrupts is enough for this SoC: it has one core, so the only other
 * writer of these bytes is an interrupt handler.
 */
_Bool __atomic_compare_exchange_1(volatile void *object,
                                  void *expected,
                                  unsigned char desired,
                                  _Bool weak,
                                  int success,
                                  int failure)
{
    volatile unsigned char *addr = (volatile unsigned char *)object;
    unsigned char *compare = (unsigned char *)expected;
    rt_base_t level;
    _Bool exchanged;

    (void)weak;
    (void)success;
    (void)failure;

    level = rt_hw_interrupt_disable();

    if (*addr == *compare)
    {
        *addr = desired;
        exchanged = 1;
    }
    else
    {
        *compare = *addr;
        exchanged = 0;
    }

    rt_hw_interrupt_enable(level);

    return exchanged;
}
