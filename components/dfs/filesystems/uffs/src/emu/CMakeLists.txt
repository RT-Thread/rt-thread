SET(libemu_SRCS cmdline.c cmdline.h helper_cmds.c uffs_fileem.c uffs_fileem.h uffs_os_posix.c test_cmds.c)

INCLUDE_DIRECTORIES(${uffs_SOURCE_DIR}/src/inc)
ADD_LIBRARY(emu STATIC ${libemu_SRCS} )

