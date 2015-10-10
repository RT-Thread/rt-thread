cmake -DCMAKE_TOOLCHAIN_FILE="../../../../build_system/tools/cmake_toolchain_files/armgcc.cmake" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug  .
mingw32-make -j4
cmake -DCMAKE_TOOLCHAIN_FILE="../../../../build_system/tools/cmake_toolchain_files/armgcc.cmake" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release  .
mingw32-make -j4
IF "%1" == "" ( pause )
