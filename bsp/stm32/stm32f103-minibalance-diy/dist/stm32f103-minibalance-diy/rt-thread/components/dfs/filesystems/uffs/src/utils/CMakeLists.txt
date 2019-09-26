IF (UNIX)
	INCLUDE_DIRECTORIES(${uffs_SOURCE_DIR}/src/platform/posix)
ENDIF()
IF (WIN32)
	INCLUDE_DIRECTORIES(${uffs_SOURCE_DIR}/src/platform/win32)
ENDIF()
INCLUDE_DIRECTORIES(${uffs_SOURCE_DIR}/src/inc)
INCLUDE_DIRECTORIES(${uffs_SOURCE_DIR}/src/emu)

LINK_DIRECTORIES(${uffs_BINARY_DIR}/src/emu)
LINK_DIRECTORIES(${uffs_BINARY_DIR}/src/uffs)

SET(mkuffs_SRCS mkuffs.c)
ADD_EXECUTABLE(mkuffs ${mkuffs_SRCS})
TARGET_LINK_LIBRARIES(mkuffs emu uffs emu platform apitest_server)
IF (UNIX)
	TARGET_LINK_LIBRARIES(mkuffs pthread)
ENDIF ()


