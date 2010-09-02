INCLUDE_DIRECTORIES(${uffs_SOURCE_DIR}/src/inc)
INCLUDE_DIRECTORIES(${uffs_SOURCE_DIR}/src/emu)

LINK_DIRECTORIES(${uffs_BINARY_DIR}/src/emu)
LINK_DIRECTORIES(${uffs_BINARY_DIR}/src/uffs)

SET(mkuffs_SRCS mkuffs.c)
ADD_EXECUTABLE(mkuffs ${mkuffs_SRCS})
TARGET_LINK_LIBRARIES(mkuffs emu uffs emu)

