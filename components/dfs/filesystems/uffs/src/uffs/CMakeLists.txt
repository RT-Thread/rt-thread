SET (libuffs_SRCS 
		uffs_badblock.c 
		uffs_blockinfo.c 
		uffs_buf.c 
		uffs_debug.c 
		uffs_device.c 
		uffs_ecc.c 
		uffs_fd.c 
		uffs_fs.c 
		uffs_init.c 
		uffs_mem.c 
		uffs_pool.c 
		uffs_public.c 
		uffs_tree.c 
		uffs_utils.c
		uffs_mtb.c
		uffs_find.c
		uffs_flash.c
		uffs_version.c
		uffs_crc.c
	 )

SET (HDR ${uffs_SOURCE_DIR}/src/inc/uffs)

SET (libuffs_HEADS 
		${HDR}/uffs.h
		${HDR}/uffs_badblock.h
		${HDR}/uffs_blockinfo.h
		${HDR}/uffs_buf.h 
		${HDR}/uffs_core.h 
		${HDR}/uffs_device.h
		${HDR}/uffs_ecc.h
		${HDR}/uffs_fd.h
		${HDR}/uffs_fs.h
		${HDR}/uffs_mem.h
        ${HDR}/uffs_os.h
        ${HDR}/uffs_pool.h
        ${HDR}/uffs_public.h
		${HDR}/uffs_tree.h
		${HDR}/uffs_types.h
		${HDR}/uffs_utils.h
		${HDR}/uffs_mtb.h
		${HDR}/uffs_find.h
		${HDR}/uffs_flash.h
		${HDR}/uffs_version.h
		${HDR}/uffs_crc.h
   )

IF (UNIX)
INCLUDE_DIRECTORIES(${uffs_SOURCE_DIR}/src/platform/posix)
ENDIF()

IF (WIN32)
INCLUDE_DIRECTORIES(${uffs_SOURCE_DIR}/src/platform/win32)
ENDIF()

INCLUDE_DIRECTORIES(${uffs_SOURCE_DIR}/src/inc)

ADD_LIBRARY( uffs STATIC ${libuffs_SRCS} ${libuffs_HEADS} )
