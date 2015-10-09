This is an updated release of the Kinetis MMCAU security function library.


This release:

  - new asm-cm0p library created, optimized for ARMv6-M ISA
  - minor improvements to asm-cm4 library, optimized for ARMv7-M ISA


This release contains the following structure for the mmcau directory:

README.txt (this file)

asm-cm0p
|-- cau_api.h
|-- lib_mmcau-cm0p.a
|-- lst
|   |-- mmcau_aes_functions.lst
|   |-- mmcau_des_functions.lst
|   |-- mmcau_md5_functions.lst
|   |-- mmcau_sha1_functions.lst
|   `-- mmcau_sha256_functions.lst
`-- src
    |-- cau2_defines.hdr
    |-- mmcau_aes_functions.s
    |-- mmcau_des_functions.s
    |-- mmcau_md5_functions.s
    |-- mmcau_sha1_functions.s
    `-- mmcau_sha256_functions.s

asm-cm4
|-- cau_api.h
|-- lib_mmcau.a
|-- lst
|   |-- mmcau_aes_functions.lst
|   |-- mmcau_des_functions.lst
|   |-- mmcau_md5_functions.lst
|   |-- mmcau_sha1_functions.lst
|   `-- mmcau_sha256_functions.lst
`-- src
    |-- cau2_defines.hdr
    |-- mmcau_aes_functions.s
    |-- mmcau_des_functions.s
    |-- mmcau_md5_functions.s
    |-- mmcau_sha1_functions.s
    `-- mmcau_sha256_functions.s



Each mmcau optimized assembly library (cm0p, cm4) is contained in 5
files (18 functions) and is archived in a lib_mmcau*.a file.


Each library was assembled with:
GNU assembler version 4.3.3 (arm-none-linux-gnueabi-as)


This mmcau library update is checked-in under Design Sync:
sync://sync-15010:15010/Projects/mcp_armp/mmcau_apb3/tool_data/lib/
tagged as: mmcau_apb3.01.00.00.11



asm-cm0p : mmcau assembly library optimized for the ARMv6-M ISA
********

Includes the following file versions (with checkin timestamps): 

12/19/2013 10:01    1.1     cau_api.h
11/13/2013 11:30    1.1     lib_mmcau-cm0p.a
                            (checked in as lib_mmcau-v6m.a)
08/22/2010 22:52    1.1     cau2_defines.hdr
10/31/2013 12:21    1.1     mmcau_aes_functions.s
10/31/2013 12:21    1.1     mmcau_des_functions.s
10/31/2013 12:21    1.1     mmcau_md5_functions.s
10/31/2013 12:21    1.1     mmcau_sha1_functions.s
11/20/2013 09:27    1.2     mmcau_sha256_functions.s

The following additional asm listing files not under revision control are
also included (with last modified timestamps):

11/19/2013 11:36            mmcau_aes_functions.lst
11/19/2013 11:36            mmcau_des_functions.lst
11/19/2013 11:36            mmcau_md5_functions.lst
11/19/2013 11:36            mmcau_sha1_functions.lst
11/19/2013 11:36            mmcau_sha256_functions.lst


asm-cm4 : mmcau assembly library optimized for the ARMv7-M ISA
*******

Includes the following file versions (with checkin timestamps): 

12/19/2013 10:01    1.1     cau_api.h
11/21/2013 13:41    1.6     lib_mmcau.a
08/22/2010 22:52    1.1     cau2_defines.hdr
11/21/2013 13:17    1.4     mmcau_aes_functions.s
11/21/2013 13:17    1.4     mmcau_des_functions.s
11/21/2013 13:17    1.6     mmcau_md5_functions.s
11/21/2013 13:17    1.5     mmcau_sha1_functions.s
11/21/2013 13:18    1.6     mmcau_sha256_functions.s

The following additional asm listing files not under revision control are
also included (with last modified timestamps):

11/21/2013 13:23            mmcau_aes_functions.lst
11/21/2013 13:23            mmcau_des_functions.lst
11/21/2013 13:23            mmcau_md5_functions.lst
11/21/2013 13:23            mmcau_sha1_functions.lst
11/21/2013 13:23            mmcau_sha256_functions.lst



The calling conventions for the mmcau functions are as follows:
---------------------------------------------------------------

mmcau_aes_functions:
    void    mmcau_aes_set_key (const unsigned char *key,
                               const int key_size,
                               unsigned char *key_sch)
    void    mmcau_aes_encrypt (const unsigned char *in,
                               const unsigned char *key_sch,
                               const int nr,
                               unsigned char *out)
    void    mmcau_aes_decrypt (const unsigned char *in,
                               const unsigned char *key_sch,
                               const int nr,
                               unsigned char *out)


mmcau_des_functions:
    int     mmcau_des_chk_parity (const unsigned char *key)
    void    mmcau_des_encrypt (const unsigned char *in,
                               const unsigned char *key,
                               unsigned char *out)
    void    mmcau_des_decrypt (const unsigned char *in,
                               const unsigned char *key,
                               unsigned char *out)


mmcau_md5_functions:
    void    mmcau_md5_initialize_output (const unsigned char *md5_state)
    void    mmcau_md5_hash_n (const unsigned char *msg_data,
                              const int num_blks,
                              unsigned char *md5_state)
    void    mmcau_md5_update (const unsigned char *msg_data,
                              const int num_blks,
                              unsigned char *md5_state)
    void    mcau_md5_hash    (const unsigned char *msg_data,
                              unsigned char *md5_state)


mmcau_sha1_functions:
    void    mmcau_sha1_initialize_output (const unsigned int *sha1_state)
    void    mmcau_sha1_hash_n (const unsigned char *msg_data,
                               const int num_blks,
                               unsigned int *sha1_state)
    void    mmcau_sha1_update (const unsigned char *msg_data,
                               const int num_blks,
                               unsigned int *sha1_state)
    void    mmcau_sha1_hash   (const unsigned char *msg_data,
                               unsigned int *sha1_state)


mmcau_sha256_functions:
    int     mmcau_sha256_initialize_output (const unsigned int *output)
    void    mmcau_sha256_hash_n (const unsigned char *input,
                                 const int num_blks,
                                 unsigned int *output)
    void    mmcau_sha256_update (const unsigned char *input,
                                 const int num_blks,
                                 unsigned int *output)
    void    mmcau_sha256_hash   (const unsigned char *input,
                                 unsigned int *output)
