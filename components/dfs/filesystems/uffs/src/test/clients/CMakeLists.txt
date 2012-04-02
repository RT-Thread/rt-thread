INCLUDE_DIRECTORIES(${uffs_SOURCE_DIR}/src/inc)
INCLUDE_DIRECTORIES(${uffs_SOURCE_DIR}/src/emu)
INCLUDE_DIRECTORIES(${uffs_SOURCE_DIR}/src/test/api_test)

IF (UNIX)
	SET(example_SRCS example.c)
	SET(example2_SRCS example-2.c)
	ADD_EXECUTABLE(example ${example_SRCS})
	ADD_EXECUTABLE(example-2 ${example2_SRCS})
	TARGET_LINK_LIBRARIES(example apitest_client)
	TARGET_LINK_LIBRARIES(example-2 apitest_client)
ENDIF()


