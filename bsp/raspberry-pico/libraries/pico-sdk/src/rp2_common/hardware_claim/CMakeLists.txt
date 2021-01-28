add_library(hardware_claim INTERFACE)
target_include_directories(hardware_claim INTERFACE include)
target_sources(hardware_claim INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/claim.c)

target_link_libraries(hardware_claim INTERFACE hardware_sync)