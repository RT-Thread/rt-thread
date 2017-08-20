/*
 * File      : module.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-01-09     Bernard      first version
 * 2010-04-09     yi.qiu       implement based on first version
 */

#ifndef __MODULE_H__
#define __MODULE_H__

#include <rtdef.h>

typedef rt_uint8_t              Elf_Byte;

typedef rt_uint32_t             Elf32_Addr;    /* Unsigned program address */
typedef rt_uint32_t             Elf32_Off;     /* Unsigned file offset */
typedef rt_int32_t              Elf32_Sword;   /* Signed large integer */
typedef rt_uint32_t             Elf32_Word;    /* Unsigned large integer */
typedef rt_uint16_t             Elf32_Half;    /* Unsigned medium integer */

/* e_ident[] magic number */
#define ELFMAG0                 0x7f           /* e_ident[EI_MAG0] */
#define ELFMAG1                 'E'            /* e_ident[EI_MAG1] */
#define ELFMAG2                 'L'            /* e_ident[EI_MAG2] */
#define ELFMAG3                 'F'            /* e_ident[EI_MAG3] */
#define RTMMAG                  "\177RTM"      /* magic */
#define ELFMAG                  "\177ELF"      /* magic */
#define SELFMAG                 4              /* size of magic */

#define EI_CLASS                4              /* file class */
#define EI_NIDENT               16             /* Size of e_ident[] */

/* e_ident[] file class */
#define ELFCLASSNONE            0              /* invalid */
#define ELFCLASS32              1              /* 32-bit objs */
#define ELFCLASS64              2              /* 64-bit objs */
#define ELFCLASSNUM             3              /* number of classes */

/* e_ident[] data encoding */
#define ELFDATANONE             0              /* invalid */
#define ELFDATA2LSB             1              /* Little-Endian */
#define ELFDATA2MSB             2              /* Big-Endian */
#define ELFDATANUM              3              /* number of data encode defines */

/* e_ident */
#define IS_ELF(ehdr)            ((ehdr).e_ident[EI_MAG0] == ELFMAG0 && \
                                 (ehdr).e_ident[EI_MAG1] == ELFMAG1 && \
                                 (ehdr).e_ident[EI_MAG2] == ELFMAG2 && \
                                 (ehdr).e_ident[EI_MAG3] == ELFMAG3)

#define ET_NONE                 0              /* No file type */
#define ET_REL                  1              /* Relocatable file */
#define ET_EXEC                 2              /* Executable file */
#define ET_DYN                  3              /* Shared object file */
#define ET_CORE                 4              /* Core file */

/* ELF Header */
typedef struct elfhdr
{
    unsigned char e_ident[EI_NIDENT];          /* ELF Identification */
    Elf32_Half    e_type;                      /* object file type */
    Elf32_Half    e_machine;                   /* machine */
    Elf32_Word    e_version;                   /* object file version */
    Elf32_Addr    e_entry;                     /* virtual entry point */
    Elf32_Off     e_phoff;                     /* program header table offset */
    Elf32_Off     e_shoff;                     /* section header table offset */
    Elf32_Word    e_flags;                     /* processor-specific flags */
    Elf32_Half    e_ehsize;                    /* ELF header size */
    Elf32_Half    e_phentsize;                 /* program header entry size */
    Elf32_Half    e_phnum;                     /* number of program header entries */
    Elf32_Half    e_shentsize;                 /* section header entry size */
    Elf32_Half    e_shnum;                     /* number of section header entries */
    Elf32_Half    e_shstrndx;                  /* section header table's "section
                                                  header string table" entry offset */
} Elf32_Ehdr;

/* Section Header */
typedef struct
{
    Elf32_Word sh_name;                        /* name - index into section header
                                                  string table section */
    Elf32_Word sh_type;                        /* type */
    Elf32_Word sh_flags;                       /* flags */
    Elf32_Addr sh_addr;                        /* address */
    Elf32_Off  sh_offset;                      /* file offset */
    Elf32_Word sh_size;                        /* section size */
    Elf32_Word sh_link;                        /* section header table index link */
    Elf32_Word sh_info;                        /* extra information */
    Elf32_Word sh_addralign;                   /* address alignment */
    Elf32_Word sh_entsize;                     /* section entry size */
} Elf32_Shdr;

/* Section names */
#define ELF_BSS                 ".bss"         /* uninitialized data */
#define ELF_DATA                ".data"        /* initialized data */
#define ELF_DEBUG               ".debug"       /* debug */
#define ELF_DYNAMIC             ".dynamic"     /* dynamic linking information */
#define ELF_DYNSTR              ".dynstr"      /* dynamic string table */
#define ELF_DYNSYM              ".dynsym"      /* dynamic symbol table */
#define ELF_FINI                ".fini"        /* termination code */
#define ELF_GOT                 ".got"         /* global offset table */
#define ELF_HASH                ".hash"        /* symbol hash table */
#define ELF_INIT                ".init"        /* initialization code */
#define ELF_REL_DATA            ".rel.data"    /* relocation data */
#define ELF_REL_FINI            ".rel.fini"    /* relocation termination code */
#define ELF_REL_INIT            ".rel.init"    /* relocation initialization code */
#define ELF_REL_DYN             ".rel.dyn"     /* relocaltion dynamic link info */
#define ELF_REL_RODATA          ".rel.rodata"  /* relocation read-only data */
#define ELF_REL_TEXT            ".rel.text"    /* relocation code */
#define ELF_RODATA              ".rodata"      /* read-only data */
#define ELF_SHSTRTAB            ".shstrtab"    /* section header string table */
#define ELF_STRTAB              ".strtab"      /* string table */
#define ELF_SYMTAB              ".symtab"      /* symbol table */
#define ELF_TEXT                ".text"        /* code */
#define ELF_RTMSYMTAB           "RTMSymTab"

/* Symbol Table Entry */
typedef struct elf32_sym
{
    Elf32_Word    st_name;                     /* name - index into string table */
    Elf32_Addr    st_value;                    /* symbol value */
    Elf32_Word    st_size;                     /* symbol size */
    unsigned char st_info;                     /* type and binding */
    unsigned char st_other;                    /* 0 - no defined meaning */
    Elf32_Half    st_shndx;                    /* section header index */
} Elf32_Sym;

#define STB_LOCAL               0              /* BIND */
#define STB_GLOBAL              1
#define STB_WEAK                2
#define STB_NUM                 3

#define STB_LOPROC              13             /* processor specific range */
#define STB_HIPROC              15

#define STT_NOTYPE              0              /* symbol type is unspecified */
#define STT_OBJECT              1              /* data object */
#define STT_FUNC                2              /* code object */
#define STT_SECTION             3              /* symbol identifies an ELF section */
#define STT_FILE                4              /* symbol's name is file name */
#define STT_COMMON              5              /* common data object */
#define STT_TLS                 6              /* thread-local data object */
#define STT_NUM                 7              /* # defined types in generic range */
#define STT_LOOS                10             /* OS specific range */
#define STT_HIOS                12
#define STT_LOPROC              13             /* processor specific range */
#define STT_HIPROC              15

#define STN_UNDEF               0              /* undefined */

#define ELF_ST_BIND(info)       ((info) >> 4)
#define ELF_ST_TYPE(info)       ((info) & 0xf)
#define ELF_ST_INFO(bind, type) (((bind)<<4)+((type)&0xf))

/* Relocation entry with implicit addend */
typedef struct
{
    Elf32_Addr r_offset;                       /* offset of relocation */
    Elf32_Word r_info;                         /* symbol table index and type */
} Elf32_Rel;

/* Relocation entry with explicit addend */
typedef struct
{
    Elf32_Addr  r_offset;                      /* offset of relocation */
    Elf32_Word  r_info;                        /* symbol table index and type */
    Elf32_Sword r_addend;
} Elf32_Rela;

/* Extract relocation info - r_info */
#define ELF32_R_SYM(i)          ((i) >> 8)
#define ELF32_R_TYPE(i)         ((unsigned char) (i))
#define ELF32_R_INFO(s,t)       (((s) << 8) + (unsigned char)(t))

/*
 * Relocation type for arm
 */
#define R_ARM_NONE              0
#define R_ARM_PC24              1
#define R_ARM_ABS32             2
#define R_ARM_REL32             3
#define R_ARM_THM_CALL          10
#define R_ARM_GLOB_DAT          21
#define R_ARM_JUMP_SLOT         22
#define R_ARM_RELATIVE          23
#define R_ARM_GOT_BREL          26
#define R_ARM_PLT32             27
#define R_ARM_CALL              28
#define R_ARM_JUMP24            29
#define R_ARM_THM_JUMP24        30
#define R_ARM_V4BX              40

/*
 * Relocation type for arm
 */
#define R_386_GLOB_DAT          6
#define R_386_JUMP_SLOT         7
#define R_386_RELATIVE          8

/* Program Header */
typedef struct
{
    Elf32_Word p_type;                         /* segment type */
    Elf32_Off  p_offset;                       /* segment offset */
    Elf32_Addr p_vaddr;                        /* virtual address of segment */
    Elf32_Addr p_paddr;                        /* physical address - ignored? */
    Elf32_Word p_filesz;                       /* number of bytes in file for seg. */
    Elf32_Word p_memsz;                        /* number of bytes in mem. for seg. */
    Elf32_Word p_flags;                        /* flags */
    Elf32_Word p_align;                        /* memory alignment */
} Elf32_Phdr;

/* p_type */
#define PT_NULL                 0
#define PT_LOAD                 1
#define PT_DYNAMIC              2
#define PT_INTERP               3
#define PT_NOTE                 4
#define PT_SHLIB                5
#define PT_PHDR                 6
#define PT_TLS                  7
#define PT_NUM                  8
#define PT_LOOS                 0x60000000
#define PT_HIOS                 0x6fffffff
#define PT_LOPROC               0x70000000
#define PT_HIPROC               0x7fffffff

/* p_flags */
#define PF_X                    1
#define PF_W                    2
#define PF_R                    4

/* sh_type */
#define SHT_NULL                0              /* inactive */
#define SHT_PROGBITS            1              /* program defined information */
#define SHT_SYMTAB              2              /* symbol table section */
#define SHT_STRTAB              3              /* string table section */
#define SHT_RELA                4              /* relocation section with addends*/
#define SHT_HASH                5              /* symbol hash table section */
#define SHT_DYNAMIC             6              /* dynamic section */
#define SHT_NOTE                7              /* note section */
#define SHT_NOBITS              8              /* no space section */
#define SHT_REL                 9              /* relocation section without addends */
#define SHT_SHLIB               10             /* reserved - purpose unknown */
#define SHT_DYNSYM              11             /* dynamic symbol table section */
#define SHT_NUM                 12             /* number of section types */
#define SHT_LOPROC              0x70000000     /* reserved range for processor */
#define SHT_HIPROC              0x7fffffff     /* specific section header types */
#define SHT_LOUSER              0x80000000     /* reserved range for application */
#define SHT_HIUSER              0xffffffff     /* specific indexes */

/* Section Attribute Flags - sh_flags */
#define SHF_WRITE               0x1            /* Writable */
#define SHF_ALLOC               0x2            /* occupies memory */
#define SHF_EXECINSTR           0x4            /* executable */
#define SHF_MASKPROC            0xf0000000     /* reserved bits for processor */
/* specific section attributes */

#endif
