#ifndef __ASM_ATOMIC_H__
#define __ASM_ATOMIC_H__

#define atomic_t int
#define atomic_inc(atom) (*atom)++
#define atomic_dec(atom) (*atom)--
#define atomic_read(atom) (*atom)


#endif /* __ASM_ATOMIC_H__ */
