# Finds (or builds) the PICOTOOL executable
#
# This will define the following variables
#
#    PICOTOOL_FOUND
#
# and the following imported targets
#
#     PICOTOOL
#

if (NOT PICOTOOL_FOUND)
    # todo we would like to use pckgconfig to look for it first
    # see https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/

    include(ExternalProject)

    set(PICOTOOL_SOURCE_DIR ${PICO_SDK_PATH}/tools/picotool)
    set(PICOTOOL_BINARY_DIR ${CMAKE_BINARY_DIR}/picotool)

    set(PICOTOOL_BUILD_TARGET PicotoolBuild)
    set(PICOTOOL_TARGET Picotool)

    if (NOT TARGET ${PICOTOOL_BUILD_TARGET})
        message("PICOTOOL will need to be built")
        ExternalProject_Add(${PICOTOOL_BUILD_TARGET}
                PREFIX picotool SOURCE_DIR ${PICOTOOL_SOURCE_DIR}
                BINARY_DIR ${PICOTOOL_BINARY_DIR}
                BUILD_ALWAYS 1 # force dependency checking
                INSTALL_COMMAND ""
                )
    endif()

    set(PICOTOOL_EXECUTABLE ${PICOTOOL_BINARY_DIR}/picotool)
    if(NOT TARGET ${PICOTOOL_TARGET})
        add_executable(${PICOTOOL_TARGET} IMPORTED)
    endif()
    set_property(TARGET ${PICOTOOL_TARGET} PROPERTY IMPORTED_LOCATION
            ${PICOTOOL_EXECUTABLE})

    add_dependencies(${PICOTOOL_TARGET} ${PICOTOOL_BUILD_TARGET})
    set(PICOTOOL_FOUND 1)
endif()