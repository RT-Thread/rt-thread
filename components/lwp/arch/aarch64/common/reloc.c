#include <rtthread.h>
#include <stdint.h>
#include <string.h>
#include <elf.h>
#ifdef ARCH_MM_MMU
#include <mmu.h>
#include <page.h>
#endif

#define Elf_Word Elf64_Word
#define Elf_Addr Elf64_Addr
#define Elf_Half Elf64_Half
#define Elf_Ehdr Elf64_Ehdr                                                   #define Elf_Phdr Elf64_Phdr
#define Elf_Shdr Elf64_Shdr

typedef struct
{
    Elf_Word st_name;
    Elf_Addr st_value;
    Elf_Word st_size;
    unsigned char st_info;
    unsigned char st_other;
    Elf_Half st_shndx;
} Elf_sym;

void arch_elf_reloc(void *text_start, void *rel_dyn_start, size_t rel_dyn_size, void *got_start, size_t got_size, Elf_sym *dynsym)
{
}
