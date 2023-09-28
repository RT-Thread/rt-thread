if (NOT TARGET pico_stdlib_headers)
    add_library(pico_stdlib_headers INTERFACE)
    target_include_directories(pico_stdlib_headers INTERFACE include)
    # dependencies handled in implementation CMakeLists.txt
endif()