SET (libemu_SRCS 
		cmdline.c
		cmdline.h
		helper_cmds.c
		uffs_fileem.c
		uffs_fileem_share.c
		uffs_fileem_wrap.c
		uffs_fileem_ecc_soft.c
		uffs_fileem_ecc_hw.c
		uffs_fileem_ecc_hw_auto.c
		uffs_fileem.h
		test_cmds.c
	)

IF (UNIX)
	INCLUDE_DIRECTORIES(${uffs_SOURCE_DIR}/src/platform/posix)
ENDIF()
IF (WIN32)
	INCLUDE_DIRECTORIES(${uffs_SOURCE_DIR}/src/platform/win32)
ENDIF()
INCLUDE_DIRECTORIES(${uffs_SOURCE_DIR}/src/inc)
INCLUDE_DIRECTORIES(${uffs_SOURCE_DIR}/src/test/api_test)
ADD_LIBRARY(emu STATIC ${libemu_SRCS} )

