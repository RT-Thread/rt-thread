# -----------------------------------------------------------------------------
# This file is part of the xPack distribution.
#   (https://xpack.github.io)
# Copyright (c) 2020 Liviu Ionescu.
#
# Permission to use, copy, modify, and/or distribute this software 
# for any purpose is hereby granted, under the terms of the MIT license.
# -----------------------------------------------------------------------------

# Helper script used in the second edition of the xPack build 
# scripts. As the name implies, it should contain only functions and 
# should be included with 'source' by the build scripts (both native
# and container).

# -----------------------------------------------------------------------------

# Default empty definition, if XBB is available, it should
# redefine it.
function xbb_activate()
{
  :
}

function xbb_activate_dev()
{
  # Add XBB include in front of XBB_CPPFLAGS.
  XBB_CPPFLAGS="-I${XBB_FOLDER_PATH}/include ${XBB_CPPFLAGS}"

  if [ -d "${XBB_FOLDER_PATH}/lib" ]
  then
    # Add XBB lib in front of XBB_LDFLAGS.
    XBB_LDFLAGS="-L${XBB_FOLDER_PATH}/lib ${XBB_LDFLAGS}"
    XBB_LDFLAGS_LIB="-L${XBB_FOLDER_PATH}/lib ${XBB_LDFLAGS_LIB}"
    XBB_LDFLAGS_APP="-L${XBB_FOLDER_PATH}/lib ${XBB_LDFLAGS_APP}"
    XBB_LDFLAGS_APP_STATIC_GCC="-L${XBB_FOLDER_PATH}/lib ${XBB_LDFLAGS_APP_STATIC_GCC}"

    # Add XBB lib in front of PKG_CONFIG_PATH.
    if [ -d "${XBB_FOLDER_PATH}/lib/pkgconfig" ]
    then
      if [ -z "${PKG_CONFIG_PATH}" ]
      then
        PKG_CONFIG_PATH="${XBB_FOLDER_PATH}/lib/pkgconfig"
      else
        PKG_CONFIG_PATH="${XBB_FOLDER_PATH}/lib/pkgconfig:${PKG_CONFIG_PATH}"
      fi
    fi
  fi

  if [ -d "${XBB_FOLDER_PATH}/lib64" ]
  then
    # For 64-bit systems, add XBB lib64 in front of paths.
    XBB_LDFLAGS="-L${XBB_FOLDER_PATH}/lib64 ${XBB_LDFLAGS_LIB}"
    XBB_LDFLAGS_LIB="-L${XBB_FOLDER_PATH}/lib64 ${XBB_LDFLAGS_LIB}"
    XBB_LDFLAGS_APP="-L${XBB_FOLDER_PATH}/lib64 ${XBB_LDFLAGS_APP}"
    XBB_LDFLAGS_APP_STATIC_GCC="-L${XBB_FOLDER_PATH}/lib64 ${XBB_LDFLAGS_APP_STATIC_GCC}"

    if [ -d "${XBB_FOLDER_PATH}/lib64/pkgconfig" ]
    then
      if [ -z "${PKG_CONFIG_PATH}" ]
      then
        PKG_CONFIG_PATH="${XBB_FOLDER_PATH}/lib64/pkgconfig"
      else
        PKG_CONFIG_PATH="${XBB_FOLDER_PATH}/lib64/pkgconfig:${PKG_CONFIG_PATH}"
      fi
    fi
  fi

  export XBB_CPPFLAGS

  export XBB_LDFLAGS
  export XBB_LDFLAGS_LIB
  export XBB_LDFLAGS_APP
  export XBB_LDFLAGS_APP_STATIC_GCC

  export PKG_CONFIG_PATH
}

function xbb_activate_libs()
{
  LD_LIBRARY_PATH=${LD_LIBRARY_PATH:-""}

  if [ -d "${XBB_FOLDER_PATH}/lib" ]
  then
    if [ -z "${LD_LIBRARY_PATH}" ]
    then
      LD_LIBRARY_PATH="${XBB_FOLDER_PATH}/lib"
    else
      LD_LIBRARY_PATH="${XBB_FOLDER_PATH}/lib:${LD_LIBRARY_PATH}"
    fi
  fi

  if [ -d "${XBB_FOLDER_PATH}/lib64" ]
  then
    if [ -z "${LD_LIBRARY_PATH}" ]
    then
      LD_LIBRARY_PATH="${XBB_FOLDER_PATH}/lib64"
    else
      LD_LIBRARY_PATH="${XBB_FOLDER_PATH}/lib64:${LD_LIBRARY_PATH}"
    fi
  fi

  export LD_LIBRARY_PATH
}

# Add the freshly built binaries.
function xbb_activate_installed_bin()
{
  # Add the XBB bin to the PATH.
  PATH="${LIBS_INSTALL_FOLDER_PATH}/bin:${PATH}"

  export PATH
}

# Add the freshly built headrs and libraries.
function xbb_activate_installed_dev()
{
  # Add XBB include in front of XBB_CPPFLAGS.
  XBB_CPPFLAGS="-I${LIBS_INSTALL_FOLDER_PATH}/include ${XBB_CPPFLAGS}"

  if [ -d "${LIBS_INSTALL_FOLDER_PATH}/lib" ]
  then
    # Add XBB lib in front of XBB_LDFLAGS.
    XBB_LDFLAGS="-L${LIBS_INSTALL_FOLDER_PATH}/lib ${XBB_LDFLAGS}"
    XBB_LDFLAGS_LIB="-L${LIBS_INSTALL_FOLDER_PATH}/lib ${XBB_LDFLAGS_LIB}"
    XBB_LDFLAGS_APP="-L${LIBS_INSTALL_FOLDER_PATH}/lib ${XBB_LDFLAGS_APP}"
    XBB_LDFLAGS_APP_STATIC_GCC="-L${LIBS_INSTALL_FOLDER_PATH}/lib ${XBB_LDFLAGS_APP_STATIC_GCC}"

    # Add XBB lib in front of PKG_CONFIG_PATH.
    PKG_CONFIG_PATH="${LIBS_INSTALL_FOLDER_PATH}/lib/pkgconfig:${PKG_CONFIG_PATH}"

    # Needed by internal binaries, like the bootstrap compiler, which do not
    # have a rpath.
    if [ -z "${LD_LIBRARY_PATH}" ]
    then
      LD_LIBRARY_PATH="${LIBS_INSTALL_FOLDER_PATH}/lib"
    else
      LD_LIBRARY_PATH="${LIBS_INSTALL_FOLDER_PATH}/lib:${LD_LIBRARY_PATH}"
    fi
  fi

  # Used by libffi, for example.
  if [ -d "${LIBS_INSTALL_FOLDER_PATH}/lib64" ]
  then
    # For 64-bit systems, add XBB lib64 in front of paths.
    XBB_LDFLAGS="-L${LIBS_INSTALL_FOLDER_PATH}/lib64 ${XBB_LDFLAGS_LIB}"
    XBB_LDFLAGS_LIB="-L${LIBS_INSTALL_FOLDER_PATH}/lib64 ${XBB_LDFLAGS_LIB}"
    XBB_LDFLAGS_APP="-L${LIBS_INSTALL_FOLDER_PATH}/lib64 ${XBB_LDFLAGS_APP}"
    XBB_LDFLAGS_APP_STATIC_GCC="-L${LIBS_INSTALL_FOLDER_PATH}/lib64 ${XBB_LDFLAGS_APP_STATIC_GCC}"

    PKG_CONFIG_PATH="${LIBS_INSTALL_FOLDER_PATH}/lib64/pkgconfig:${PKG_CONFIG_PATH}"

    if [ -z "${LD_LIBRARY_PATH}" ]
    then
      LD_LIBRARY_PATH="${LIBS_INSTALL_FOLDER_PATH}/lib64"
    else
      LD_LIBRARY_PATH="${LIBS_INSTALL_FOLDER_PATH}/lib64:${LD_LIBRARY_PATH}"
    fi
  fi

  export XBB_CPPFLAGS

  export XBB_LDFLAGS
  export XBB_LDFLAGS_LIB
  export XBB_LDFLAGS_APP
  export XBB_LDFLAGS_APP_STATIC_GCC

  export PKG_CONFIG_PATH
  export LD_LIBRARY_PATH

  echo
  env | sort
}

function xbb_activate_tex()
{
  :
}

# -----------------------------------------------------------------------------

function do_config_guess() 
{
  if [ -f "${XBB_FOLDER_PATH}/share/libtool/build-aux/config.guess" ]
  then
    BUILD="$(${XBB_FOLDER_PATH}/share/libtool/build-aux/config.guess)"
  elif [ -f "/usr/share/libtool/build-aux/config.guess" ]
  then
    BUILD="$(/usr/share/libtool/build-aux/config.guess)"
  elif [ -f "/usr/share/misc/config.guess" ]
  then
    BUILD="$(/usr/share/misc/config.guess)"
  else
    echo "Could not find config.guess."
    exit 1
  fi
}

function prepare_xbb_env() 
{
  # Defaults, to ensure the variables are defined.
  PATH="${PATH:-""}"
  LD_LIBRARY_PATH="${LD_LIBRARY_PATH:-""}"

  if [ -f "${HOME}/opt/xbb/xbb-source.sh" ]
  then
    XBB_FOLDER_PATH="${HOME}/opt/xbb"
    echo
    echo "Sourcing ${HOME}/opt/xbb/xbb-source.sh..."
    source "${HOME}/opt/xbb/xbb-source.sh"
  elif [ -f "${HOME}/opt/homebrew/xbb/xbb-source.sh" ]
  then
    XBB_FOLDER_PATH="${HOME}/opt/homebrew/xbb"
    # Deprecated, on macOS it was moved to HOME/opt/xbb
    echo
    echo "Sourcing ${HOME}/opt/homebrew/xbb/xbb-source.sh..."
    source "${HOME}/opt/homebrew/xbb/xbb-source.sh"
  elif [ -f "/opt/xbb/xbb-source.sh" ]
  then
    XBB_FOLDER_PATH="/opt/xbb"
    echo
    echo "Sourcing /opt/xbb/xbb-source.sh..."
    source "/opt/xbb/xbb-source.sh"
  else
    XBB_FOLDER_PATH=""
  fi

  TARGET_FOLDER_NAME="${TARGET_PLATFORM}-${TARGET_ARCH}"

  # Compute the BUILD/HOST/TARGET for configure.
  CROSS_COMPILE_PREFIX=""
  if [ "${TARGET_PLATFORM}" == "win32" ]
  then

    # Disable test when cross compiling for Windows.
    WITH_TESTS="n"

    # For Windows targets, decide which cross toolchain to use.
    if [ ${TARGET_ARCH} == "x32" ]
    then
      CROSS_COMPILE_PREFIX="i686-w64-mingw32"
    elif [ ${TARGET_ARCH} == "x64" ]
    then
      CROSS_COMPILE_PREFIX="x86_64-w64-mingw32"
    else
      echo "Oops! Unsupported ${TARGET_ARCH}."
      exit 1
    fi

    do_config_guess

    HOST="${CROSS_COMPILE_PREFIX}"
    TARGET="${HOST}"

  elif [ "${TARGET_PLATFORM}" == "darwin" ]
  then

    do_config_guess

    HOST="${BUILD}"
    TARGET="${HOST}"

  elif [ "${TARGET_PLATFORM}" == "linux" ]
  then

    do_config_guess

    HOST="${BUILD}"
    TARGET="${HOST}"

  else
    echo "Oops! Unsupported ${TARGET_PLATFORM}."
    exit 1
  fi

  if [ -f "/.dockerenv" ]
  then
    WORK_FOLDER_PATH="${CONTAINER_WORK_FOLDER_PATH}"
    DOWNLOAD_FOLDER_PATH="${CONTAINER_CACHE_FOLDER_PATH}"
  else
    WORK_FOLDER_PATH="${HOST_WORK_FOLDER_PATH}"
    DOWNLOAD_FOLDER_PATH="${HOST_CACHE_FOLDER_PATH}"
  fi

  # Develop builds use the host folder.
  BUILD_FOLDER_PATH="${WORK_FOLDER_PATH}/${TARGET_FOLDER_NAME}/build"
  if [ -f "/.dockerenv" ]
  then 
    if [ "${IS_DEVELOP}" != "y" ]
    then
      # Docker builds use a temporary folder.
      BUILD_FOLDER_PATH="/tmp/${TARGET_FOLDER_NAME}/build"
    fi
  fi

  LIBS_BUILD_FOLDER_PATH="${BUILD_FOLDER_PATH}/libs"
  mkdir -pv "${LIBS_BUILD_FOLDER_PATH}"

  APP_BUILD_FOLDER_PATH="${BUILD_FOLDER_PATH}/${APP_LC_NAME}"
  # Do it later, only if needed.
  # mkdir -pv "${APP_BUILD_FOLDER_PATH}"

  INSTALL_FOLDER_PATH="${WORK_FOLDER_PATH}/${TARGET_FOLDER_NAME}/install"
  STAMPS_FOLDER_PATH="${INSTALL_FOLDER_PATH}"

  LIBS_INSTALL_FOLDER_PATH="${INSTALL_FOLDER_PATH}/libs"
  # Use explicit include & especially lib, to prevent compiler complaining
  # for missing folders.
  mkdir -pv "${LIBS_INSTALL_FOLDER_PATH}/include"
  mkdir -pv "${LIBS_INSTALL_FOLDER_PATH}/lib"

  APP_INSTALL_FOLDER_PATH="${INSTALL_FOLDER_PATH}/${APP_LC_NAME}"
  mkdir -pv "${APP_INSTALL_FOLDER_PATH}"

  LOGS_FOLDER_NAME=${LOGS_FOLDER_NAME:-"logs"}
  LOGS_FOLDER_PATH="${WORK_FOLDER_PATH}/${TARGET_FOLDER_NAME}/${LOGS_FOLDER_NAME}"
  mkdir -pv "${LOGS_FOLDER_PATH}"

  DEPLOY_FOLDER_NAME=${DEPLOY_FOLDER_NAME:-"deploy"}
  DEPLOY_FOLDER_PATH="${WORK_FOLDER_PATH}/${DEPLOY_FOLDER_NAME}"
  # Do it later, only if needed.
  # mkdir -pv "${DEPLOY_FOLDER_PATH}"

  DISTRO_INFO_NAME=${DISTRO_INFO_NAME:-"distro-info"}
  
  BUILD_GIT_PATH="${WORK_FOLDER_PATH}/build.git"

  # ---------------------------------------------------------------------------

  APP_PREFIX="${INSTALL_FOLDER_PATH}/${APP_LC_NAME}"
  # The documentation location is now the same on all platforms.
  APP_PREFIX_DOC="${APP_PREFIX}/share/doc"

  # ---------------------------------------------------------------------------

  SOURCES_FOLDER_PATH=${SOURCES_FOLDER_PATH:-"${WORK_FOLDER_PATH}/sources"}
  mkdir -pv "${SOURCES_FOLDER_PATH}"

  # Empty defaults.
  IS_DEVELOP=${IS_DEVELOP:-""}
  IS_DEBUG=${IS_DEBUG:-""}
  WITH_PDF=${WITH_PDF:-""}
  WITH_HTML=${WITH_HTML:-""}
  WITH_TESTS=${WITH_TESTS:-"y"}

  # Redefine this to "y" to create files that include the architecture.
  HAS_NAME_ARCH=${HAS_NAME_ARCH:-""}

  USE_TAR_GZ=${USE_TAR_GZ:-"y"}
  USE_SINGLE_FOLDER_PATH=${USE_SINGLE_FOLDER_PATH:-"y"}

  # ---------------------------------------------------------------------------

  export LANGUAGE="en_US:en"
  export LANG="en_US.UTF-8"
  export LC_ALL="en_US.UTF-8"
  export LC_COLLATE="en_US.UTF-8"
  export LC_CTYPE="UTF-8"
  export LC_MESSAGES="en_US.UTF-8"
  export LC_MONETARY="en_US.UTF-8"
  export LC_NUMERIC="en_US.UTF-8"
  export LC_TIME="en_US.UTF-8"

  export PATH
  export LD_LIBRARY_PATH

  export SOURCES_FOLDER_PATH

  # libtool fails with the Ubuntu /bin/sh.
  export SHELL="/bin/bash"
  export CONFIG_SHELL="/bin/bash"

  echo
  env | sort
}

function prepare_xbb_extras()
{
  # ---------------------------------------------------------------------------

  XBB_CPPFLAGS=""

  XBB_CFLAGS="-ffunction-sections -fdata-sections -pipe"
  XBB_CXXFLAGS="-ffunction-sections -fdata-sections -pipe"

  if [ "${TARGET_ARCH}" == "x64" -o "${TARGET_ARCH}" == "x32" ]
  then
    XBB_CFLAGS+=" -m${TARGET_BITS}"
    XBB_CXXFLAGS+=" -m${TARGET_BITS}"
  fi

  XBB_LDFLAGS=""

  if [ "${IS_DEBUG}" == "y" ]
  then
    XBB_CFLAGS+=" -g -O0"
    XBB_CXXFLAGS+=" -g -O0"
    XBB_LDFLAGS+=" -g -O0"
  else
    XBB_CFLAGS+=" -O2"
    XBB_CXXFLAGS+=" -O2"
    XBB_LDFLAGS+=" -O2"
  fi

  if [ ! -z "$(xbb_activate; which "g++-xbb")" ]
  then
    prepare_gcc_env "" "-xbb"
  elif [ ! -z "$(xbb_activate; which "g++-9")" ]
  then
    prepare_gcc_env "" "-9"
  elif [ ! -z "$(xbb_activate; which "g++-8")" ]
  then
    prepare_gcc_env "" "-8"
  elif [ ! -z "$(xbb_activate; which "g++-7")" ]
  then
    prepare_gcc_env "" "-7"
  else
    prepare_gcc_env "" ""
  fi

  if [ "${TARGET_PLATFORM}" == "linux" ]
  then
    SHLIB_EXT="so"

    # Do not add -static here, it fails.
    # Do not try to link pthread statically, it must match the system glibc.
    XBB_LDFLAGS_LIB="${XBB_LDFLAGS}"
    XBB_LDFLAGS_APP="${XBB_LDFLAGS} -Wl,--gc-sections"
    XBB_LDFLAGS_APP_STATIC_GCC="${XBB_LDFLAGS_APP} -static-libgcc -static-libstdc++"
  elif [ "${TARGET_PLATFORM}" == "darwin" ]
  then
    SHLIB_EXT="dylib"

    # Note: macOS linker ignores -static-libstdc++, so 
    # libstdc++.6.dylib should be handled.
    XBB_LDFLAGS+=" -Wl,-macosx_version_min,10.10"
    XBB_LDFLAGS_LIB="${XBB_LDFLAGS}"
    XBB_LDFLAGS_APP="${XBB_LDFLAGS} -Wl,-dead_strip"
    XBB_LDFLAGS_APP_STATIC_GCC="${XBB_LDFLAGS_APP}"
  elif [ "${TARGET_PLATFORM}" == "win32" ]
  then
    SHLIB_EXT="dll"

    export NATIVE_CC=${CC}
    export NATIVE_CXX=${CXX}
    
    prepare_gcc_env "${CROSS_COMPILE_PREFIX}-"

    # CRT_glob is from Arm script
    # -static avoids libwinpthread-1.dll 
    # -static-libgcc avoids libgcc_s_sjlj-1.dll 
    XBB_LDFLAGS_LIB="${XBB_LDFLAGS}"
    XBB_LDFLAGS_APP="${XBB_LDFLAGS} -Wl,--gc-sections"
    XBB_LDFLAGS_APP_STATIC_GCC="${XBB_LDFLAGS_APP} -static-libgcc -static-libstdc++"
  else
    echo "Oops! Unsupported ${TARGET_PLATFORM}."
    exit 1
  fi

  XBB_CFLAGS_NO_W="${XBB_CFLAGS} -w"
  XBB_CXXFLAGS_NO_W="${XBB_CXXFLAGS} -w"

  set +u
  if [ ! -z "${XBB_FOLDER_PATH}" -a -x "${XBB_FOLDER_PATH}/bin/pkg-config-verbose" ]
  then
    PKG_CONFIG="${XBB_FOLDER_PATH}/bin/pkg-config-verbose"
  else
    PKG_CONFIG="$(which pkg-config)"
  fi
  set -u

  # Hopefully defining it empty would be enough...
  PKG_CONFIG_PATH=${PKG_CONFIG_PATH:-""}

  # Prevent pkg-config to search the system folders (configured in the
  # pkg-config at build time).
  PKG_CONFIG_LIBDIR=${PKG_CONFIG_LIBDIR:-""}

  set +u
  echo
  echo "CC=${CC}"
  echo "CXX=${CXX}"
  echo "XBB_CPPFLAGS=${XBB_CPPFLAGS}"
  echo "XBB_CFLAGS=${XBB_CFLAGS}"
  echo "XBB_CXXFLAGS=${XBB_CXXFLAGS}"

  echo "XBB_LDFLAGS_LIB=${XBB_LDFLAGS_LIB}"
  echo "XBB_LDFLAGS_APP=${XBB_LDFLAGS_APP}"
  echo "XBB_LDFLAGS_APP_STATIC_GCC=${XBB_LDFLAGS_APP_STATIC_GCC}"

  echo "PKG_CONFIG=${PKG_CONFIG}"
  echo "PKG_CONFIG_PATH=${PKG_CONFIG_PATH}"
  echo "PKG_CONFIG_LIBDIR=${PKG_CONFIG_LIBDIR}"
  set -u

  (
    xbb_activate

    which ${CC}
    ${CC} --version

    which make
    make --version
  )

  # ---------------------------------------------------------------------------

  export SHLIB_EXT

  # CC & co were exported by prepare_gcc_env.
  export XBB_CPPFLAGS

  export XBB_CFLAGS
  export XBB_CXXFLAGS

  export XBB_CFLAGS_NO_W
  export XBB_CXXFLAGS_NO_W

  export XBB_LDFLAGS
  export XBB_LDFLAGS_LIB
  export XBB_LDFLAGS_APP
  export XBB_LDFLAGS_APP_STATIC_GCC

  export PKG_CONFIG
  export PKG_CONFIG_PATH
  export PKG_CONFIG_LIBDIR
}

function prepare_gcc_env()
{
  local prefix="$1"

  local suffix
  if [ $# -ge 2 ]
  then
    suffix="$2"
  else
    suffix=""
  fi

  export CC="${prefix}gcc${suffix}"
  export CXX="${prefix}g++${suffix}"

  export AR="${prefix}gcc-ar${suffix}"
  export AS="${prefix}as"
  export DLLTOOL="${prefix}dlltool"
  export LD="${prefix}ld"
  export NM="${prefix}gcc-nm${suffix}"
  export OBJCOPY="${prefix}objcopy"
  export OBJDUMP="${prefix}objdump"
  export RANLIB="${prefix}gcc-ranlib${suffix}"
  export READELF="${prefix}readelf"
  export SIZE="${prefix}size"
  export STRIP="${prefix}strip"
  export WINDRES="${prefix}windres"
  export WINDMC="${prefix}windmc"
  export RC="${prefix}windres"
}

function unset_gcc_env()
{
  unset CC
  unset CXX
  unset AR
  unset AS
  unset DLLTOOL
  unset LD
  unset NM
  unset OBJCOPY
  unset OBJDUMP
  unset RANLIB
  unset READELF
  unset SIZE
  unset STRIP
  unset WINDRES
  unset WINDMC
  unset RC
}

# -----------------------------------------------------------------------------

function do_actions()
{
  if [ "${ACTION}" == "clean" ]
  then
    echo

    if [ "${IS_NATIVE}" == "y" ]
    then
      echo "Removing the ${TARGET_FOLDER_NAME} build and install ${APP_LC_NAME} folders..."

      rm -rf "${HOST_WORK_FOLDER_PATH}/${TARGET_FOLDER_NAME}/build/${APP_LC_NAME}"
      rm -rf "${HOST_WORK_FOLDER_PATH}/${TARGET_FOLDER_NAME}/install/${APP_LC_NAME}"
    elif [ ! -z "${DO_BUILD_WIN32}${DO_BUILD_WIN64}${DO_BUILD_LINUX32}${DO_BUILD_LINUX64}${DO_BUILD_OSX}" ]
    then
      if [ "${DO_BUILD_WIN32}" == "y" ]
      then
        echo "Removing the win32-x32 build and install ${APP_LC_NAME} folders..."

        rm -rf "${HOST_WORK_FOLDER_PATH}/win32-x32/build/${APP_LC_NAME}"
        rm -rf "${HOST_WORK_FOLDER_PATH}/win32-x32/install/${APP_LC_NAME}"
      fi
      if [ "${DO_BUILD_WIN64}" == "y" ]
      then
        echo "Removing the win32-x64 build and install ${APP_LC_NAME} folders..."

        rm -rf "${HOST_WORK_FOLDER_PATH}/win32-x64/build/${APP_LC_NAME}"
        rm -rf "${HOST_WORK_FOLDER_PATH}/win32-x64/install/${APP_LC_NAME}"
      fi
      if [ "${DO_BUILD_LINUX32}" == "y" ]
      then
        echo "Removing the linux-x32 build and install ${APP_LC_NAME} folders..."

        rm -rf "${HOST_WORK_FOLDER_PATH}/linux-x32/build/${APP_LC_NAME}"
        rm -rf "${HOST_WORK_FOLDER_PATH}/linux-x32/install/${APP_LC_NAME}"
      fi
      if [ "${DO_BUILD_LINUX64}" == "y" ]
      then
        echo "Removing the linux-x64 build and install ${APP_LC_NAME} folders..."

        rm -rf "${HOST_WORK_FOLDER_PATH}/linux-x64/build/${APP_LC_NAME}"
        rm -rf "${HOST_WORK_FOLDER_PATH}/linux-x64/install/${APP_LC_NAME}"
      fi
      if [ "${DO_BUILD_OSX}" == "y" ]
      then
        echo "Removing the darwin-x64 build and install ${APP_LC_NAME} folders..."

        rm -rf "${HOST_WORK_FOLDER_PATH}/darwin-x64/build/${APP_LC_NAME}"
        rm -rf "${HOST_WORK_FOLDER_PATH}/darwin-x64/install/${APP_LC_NAME}"
      fi
    else
      echo "Removing the ${HOST_NODE_PLATFORM}-${HOST_NODE_ARCH} build and install ${APP_LC_NAME} folders..."

      rm -rf "${HOST_WORK_FOLDER_PATH}/${HOST_NODE_PLATFORM}-${HOST_NODE_ARCH}/build/${APP_LC_NAME}"
      rm -rf "${HOST_WORK_FOLDER_PATH}/${HOST_NODE_PLATFORM}-${HOST_NODE_ARCH}/install/${APP_LC_NAME}"
    fi
  fi

  if [ "${ACTION}" == "cleanlibs" ]
  then
    echo

    if [ "${IS_NATIVE}" == "y" ]
    then
      echo "Removing the ${TARGET_FOLDER_NAME} build and install libs folders..."

      rm -rf "${HOST_WORK_FOLDER_PATH}/${TARGET_FOLDER_NAME}/build/libs"
      rm -rf "${HOST_WORK_FOLDER_PATH}/${TARGET_FOLDER_NAME}/install/libs"
      rm -rf "${HOST_WORK_FOLDER_PATH}/${TARGET_FOLDER_NAME}/install"/stamp-*-installed
    elif [ ! -z "${DO_BUILD_WIN32}${DO_BUILD_WIN64}${DO_BUILD_LINUX32}${DO_BUILD_LINUX64}${DO_BUILD_OSX}" ]
    then
      if [ "${DO_BUILD_WIN32}" == "y" ]
      then
        echo "Removing the win32-x32 build and install libs folders..."

        rm -rf "${HOST_WORK_FOLDER_PATH}/win32-x32/build/libs"
        rm -rf "${HOST_WORK_FOLDER_PATH}/win32-x32/install/libs"
        rm -rf "${HOST_WORK_FOLDER_PATH}/win32-x32/install"/stamp-*-installed
      fi
      if [ "${DO_BUILD_WIN64}" == "y" ]
      then
        echo "Removing the win32-x64 build and install libs folders..."

        rm -rf "${HOST_WORK_FOLDER_PATH}/win32-x64/build/libs"
        rm -rf "${HOST_WORK_FOLDER_PATH}/win32-x64/install/libs"
        rm -rf "${HOST_WORK_FOLDER_PATH}/win32-x64/install"/stamp-*-installed
      fi
      if [ "${DO_BUILD_LINUX32}" == "y" ]
      then
        echo "Removing the linux-x32 build and install libs folders..."

        rm -rf "${HOST_WORK_FOLDER_PATH}/linux-x32/build/libs"
        rm -rf "${HOST_WORK_FOLDER_PATH}/linux-x32/install/libs"
        rm -rf "${HOST_WORK_FOLDER_PATH}/linux-x32/install"/stamp-*-installed
      fi
      if [ "${DO_BUILD_LINUX64}" == "y" ]
      then
        echo "Removing the linux-x64 build and install libs folders..."

        rm -rf "${HOST_WORK_FOLDER_PATH}/linux-x64/build/libs"
        rm -rf "${HOST_WORK_FOLDER_PATH}/linux-x64/install/libs"
        rm -rf "${HOST_WORK_FOLDER_PATH}/linux-x64/install"/stamp-*-installed
      fi
      if [ "${DO_BUILD_OSX}" == "y" ]
      then
        echo "Removing the darwin-x64 build and install libs folders..."

        rm -rf "${HOST_WORK_FOLDER_PATH}/darwin-x64/build/libs"
        rm -rf "${HOST_WORK_FOLDER_PATH}/darwin-x64/install/libs"
        rm -rf "${HOST_WORK_FOLDER_PATH}/darwin-x64/install"/stamp-*-installed
      fi
    else
      echo "Removing the ${HOST_NODE_PLATFORM}-${HOST_NODE_ARCH} build and install libs folders..."

      rm -rf "${HOST_WORK_FOLDER_PATH}/${HOST_NODE_PLATFORM}-${HOST_NODE_ARCH}/build/libs"
      rm -rf "${HOST_WORK_FOLDER_PATH}/${HOST_NODE_PLATFORM}-${HOST_NODE_ARCH}/install/libs"
      rm -rf "${HOST_WORK_FOLDER_PATH}/${HOST_NODE_PLATFORM}-${HOST_NODE_ARCH}/install"/stamp-*-installed
    fi
  fi

  if [ "${ACTION}" == "cleanall" ]
  then
    echo
    if [ "${IS_NATIVE}" == "y" ]
    then
      echo "Removing the ${TARGET_FOLDER_NAME} folder..."
  
      rm -rf "${HOST_WORK_FOLDER_PATH}/${TARGET_FOLDER_NAME}"
    elif [ ! -z "${DO_BUILD_WIN32}${DO_BUILD_WIN64}${DO_BUILD_LINUX32}${DO_BUILD_LINUX64}${DO_BUILD_OSX}" ]
    then
      if [ "${DO_BUILD_WIN32}" == "y" ]
      then
        echo "Removing the win32-x32 folder..."

        rm -rf "${HOST_WORK_FOLDER_PATH}/win32-x32"
      fi
      if [ "${DO_BUILD_WIN64}" == "y" ]
      then
        echo "Removing the win32-x64 folder..."

        rm -rf "${HOST_WORK_FOLDER_PATH}/win32-x64"
      fi
      if [ "${DO_BUILD_LINUX32}" == "y" ]
      then
        echo "Removing the linux-x32 folder..."

        rm -rf "${HOST_WORK_FOLDER_PATH}/linux-x32"
      fi
      if [ "${DO_BUILD_LINUX64}" == "y" ]
      then
        echo "Removing the linux-x64 folder..."

        rm -rf "${HOST_WORK_FOLDER_PATH}/linux-x64"
      fi
      if [ "${DO_BUILD_OSX}" == "y" ]
      then
        echo "Removing the darwin-x64 folder..."

        rm -rf "${HOST_WORK_FOLDER_PATH}/darwin-x64"
      fi
    else
      echo "Removing the ${HOST_NODE_PLATFORM}-${HOST_NODE_ARCH} folder..."

      rm -rf "${HOST_WORK_FOLDER_PATH}/${HOST_NODE_PLATFORM}-${HOST_NODE_ARCH}"
    fi
  fi

  if [ "${ACTION}" == "clean" -o "${ACTION}" == "cleanlibs" -o "${ACTION}" == "cleanall" ]
  then
    echo
    echo "Clean completed. Proceed with a regular build."

    exit 0
  fi

  # Not used for native buils. Otherwise the names of the docker images
  # must be set.
  if [ "${ACTION}" == "preload-images" ]
  then
    host_start_timer

    host_prepare_docker

    echo
    echo "Check/Preload Docker images..."

    if [ "${HOST_MACHINE}" == "aarch64" -o "${HOST_MACHINE}" == "armv7l" -o "${HOST_MACHINE}" == "armv8l" ]
    then
      echo
      docker run --interactive --tty "${docker_linux_arm64_image}" \
        lsb_release --description --short

      echo
      docker run --interactive --tty "${docker_linux_arm32_image}" \
        lsb_release --description --short
    else
      echo
      docker run --interactive --tty "${docker_linux64_image}" \
        lsb_release --description --short

      echo
      docker run --interactive --tty "${docker_linux32_image}" \
        lsb_release --description --short
    fi

    echo
    docker images

    host_stop_timer

    exit 0
  fi
}

# -----------------------------------------------------------------------------

function run_verbose()
{
  # Does not include the .exe extension.
  local app_path=$1
  shift

  echo
  echo "[${app_path} $@]"
  "${app_path}" "$@" 2>&1
}

function run_app()
{
  # Does not include the .exe extension.
  local app_path=$1
  shift

  echo
  echo "${app_path} $@"
  if [ "${TARGET_PLATFORM}" == "linux" ]
  then
    "${app_path}" "$@"
  elif [ "${TARGET_PLATFORM}" == "darwin" ]
  then
    "${app_path}" "$@"
  elif [ "${TARGET_PLATFORM}" == "win32" ]
  then
    local wsl_path=$(which wsl.exe)
    if [ ! -z "${wsl_path}" ]
    then
      "${app_path}.exe" "$@"
    else 
      (
        xbb_activate
        
        local wine_path=$(which wine)
        if [ ! -z "${wine_path}" ]
        then
          wine "${app_path}.exe" "$@"
        else
          echo "Install wine if you want to run the .exe binaries on Linux."
        fi
      )
    fi
  else
    echo "Oops! Unsupported ${TARGET_PLATFORM}."
    exit 1
  fi
}

function show_libs()
{
  # Does not include the .exe extension.
  local app_path=$1
  shift

  (
    xbb_activate

    if [ "${TARGET_PLATFORM}" == "linux" ]
    then
      echo
      echo "readelf -d ${app_path} | egrep -i ..."
      # Ignore errors in case it is not using shared libraries.
      set +e 
      readelf -d "${app_path}" | egrep -i '(SONAME)' || true
      readelf -d "${app_path}" | egrep -i '(RUNPATH|RPATH)' || true
      readelf -d "${app_path}" | egrep -i '(NEEDED)' || true
      echo "ldd -v ${app_path}"
      ldd -v "${app_path}" || true
      set -e
    elif [ "${TARGET_PLATFORM}" == "darwin" ]
    then
      echo
      echo "otool -L ${app_path}"
      otool -L "${app_path}"
    elif [ "${TARGET_PLATFORM}" == "win32" ]
    then
      if [ -f "${app_path}" ]
      then
        echo
        echo "${CROSS_COMPILE_PREFIX}-objdump -x ${app_path}"
        ${CROSS_COMPILE_PREFIX}-objdump -x ${app_path} | grep -i 'DLL Name' 
      elif [ -f "${app_path}.exe" ]
      then
        echo
        echo "${CROSS_COMPILE_PREFIX}-objdump -x ${app_path}.exe"
        ${CROSS_COMPILE_PREFIX}-objdump -x ${app_path}.exe | grep -i 'DLL Name' 
      else
        echo
        echo "${app_path} neither exe nor dll"
      fi
    else
      echo "Oops! Unsupported ${TARGET_PLATFORM}."
      exit 1
    fi
  )
}

# -----------------------------------------------------------------------------

function do_patch()
{
  if [ ! -z "$1" ]
  then
    local patch_file_name="$1"
    local patch_path="${BUILD_GIT_PATH}/patches/${patch_file_name}"
    if [ -f "${patch_path}" ]
    then
      echo "Patching..."
      patch -p0 < "${patch_path}"
    fi
  fi
}

function extract()
{
  local archive_name="$1"
  local folder_name="$2"
  # local patch_file_name="$3"
  local pwd="$(pwd)"

  if [ ! -d "${folder_name}" ]
  then
    (
      xbb_activate

      echo
      echo "Extracting \"${archive_name}\" -> \"${pwd}/${folder_name}\"..."
      if [[ "${archive_name}" == *zip ]]
      then
        unzip "${archive_name}" 
      else
        if [ ! -z "${DEBUG}" ]
        then
          tar -x -v -f "${archive_name}" --no-same-owner
        else
          tar -x -f "${archive_name}" --no-same-owner
        fi
      fi

      if [ $# -ge 3 ]
      then
        cd "${folder_name}"
        do_patch "$3"
      fi
    )
  else
    echo "Folder \"${pwd}/${folder_name}\" already present."
  fi
}


function download()
{
  local url="$1"
  local archive_name="$2"

  if [ ! -f "${DOWNLOAD_FOLDER_PATH}/${archive_name}" ]
  then
    (
      xbb_activate

      echo
      echo "Downloading \"${archive_name}\" from \"${url}\"..."
      rm -f "${DOWNLOAD_FOLDER_PATH}/${archive_name}.download"
      mkdir -pv "${DOWNLOAD_FOLDER_PATH}"
      curl --fail -L -o "${DOWNLOAD_FOLDER_PATH}/${archive_name}.download" "${url}"
      mv "${DOWNLOAD_FOLDER_PATH}/${archive_name}.download" "${DOWNLOAD_FOLDER_PATH}/${archive_name}"
    )
  else
    echo "File \"${DOWNLOAD_FOLDER_PATH}/${archive_name}\" already downloaded."
  fi
}

# $4 is the patch file name
function download_and_extract()
{
  local url="$1"
  local archive_name="$2"
  local folder_name="$3"

  download "${url}" "${archive_name}"
  if [ $# -ge 4 ]
  then
    extract "${DOWNLOAD_FOLDER_PATH}/${archive_name}" "${folder_name}" "$4"
  else
    extract "${DOWNLOAD_FOLDER_PATH}/${archive_name}" "${folder_name}"
  fi
}

function git_clone()
{
  local url="$1"
  local branch="$2"
  local commit="$3"
  local folder_name="$4"

  (
    echo
    echo "Cloning \"${folder_name}\" from \"${url}\"..."
    git clone --branch="${branch}" "${url}" "${folder_name}"
    if [ -n "${commit}" ]
    then
      cd "${folder_name}"
      git checkout -qf "${commit}"
    fi
  )
}

# Copy the build files to the Work area, to make them easily available. 
function copy_build_git()
{
  rm -rf "${HOST_WORK_FOLDER_PATH}/build.git"
  mkdir -pv "${HOST_WORK_FOLDER_PATH}/build.git"
  cp -r "$(dirname ${script_folder_path})"/* "${HOST_WORK_FOLDER_PATH}/build.git"
  rm -rf "${HOST_WORK_FOLDER_PATH}/build.git/scripts/helper/.git"
  rm -rf "${HOST_WORK_FOLDER_PATH}/build.git/scripts/helper/build-helper.sh"
}

# -----------------------------------------------------------------------------

function check_binary()
{
  local file_path="$1"

  if file --mime "${file_path}" | grep -q text
  then
    echo "${file_path} has no text"
    return 0
  fi

  check_binary_for_libraries "$1"
}

function check_binary_for_libraries()
{
  local file_path="$1"
  local file_name="$(basename ${file_path})"
  local folder_path="$(dirname ${file_path})"

  (
    xbb_activate

    if [ "${TARGET_PLATFORM}" == "win32" ]
    then
      echo
      echo "${file_name} (${file_path})"
      set +e
      ${CROSS_COMPILE_PREFIX}-objdump -x "${file_path}" | grep -i 'DLL Name'

      local dll_names=$(${CROSS_COMPILE_PREFIX}-objdump -x "${file_path}" \
        | grep -i 'DLL Name' \
        | sed -e 's/.*DLL Name: \(.*\)/\1/' \
      )

      local n
      for n in ${dll_names}
      do
        if [ ! -f "${folder_path}/${n}" ] 
        then
          if is_win_sys_dll "${n}"
          then
            :
          elif [ "${n}${HAS_WINPTHREAD}" == "libwinpthread-1.dlly" ]
          then
            :
          else
            echo "Unexpected |${n}|"
            exit 1
          fi
        fi
      done
      set -e
    elif [ "${TARGET_PLATFORM}" == "darwin" ]
    then
      echo
      (
        set +e
        cd ${folder_path}
        otool -L "${file_name}"
        set -e
      )

      # Skip the first line which is the binary itself.
      local libs
      if is_darwin_dylib "${file_path}"
      then
        # Skip the second line too, which is the library again.
        lib_paths=$(otool -L "${file_path}" \
              | sed '1d' \
              | sed '1d' \
              | sed -e 's|[[:space:]]*\(.*\) (.*)|\1|' \
            )
      else
        lib_paths=$(otool -L "${file_path}" \
              | sed '1d' \
              | sed -e 's|[[:space:]]*\(.*\) (.*)|\1|' \
            )
      fi
      local exec_prefix="@executable_path/"
      for lib_path in ${lib_paths}
      do
        if [ "${lib_path:0:1}" != "@" ]
        then
          if is_darwin_allowed_sys_dylib "${lib_path}"
          then
            :
          else
            echo ">>> \"${lib_path}\" is not expected here"
            exit 1
          fi
        elif [ "${lib_path:0:${#exec_prefix}}" == "${exec_prefix}" ]
        then
          if [ ! -f "${folder_path}/${lib_path:${#exec_prefix}}" ]
          then
            echo ">>> \"${lib_path:${#exec_prefix}}\" is expected in \"${folder_path}\""
            exit 1
          fi
        fi
      done

      # More or less deprecated by the above.
      set +e
      local unxp
      if [[ "${file_name}" == *\.dylib ]]
      then
        unxp=$(otool -L "${file_path}" | sed '1d' | sed '1d' | grep -v "${file_name}" | egrep -e "(macports|homebrew|opt|install)/")
      else
        unxp=$(otool -L "${file_path}" | sed '1d' | grep -v "${file_name}" | egrep -e "(macports|homebrew|opt|install)/")
      fi
      set -e

      # echo "|${unxp}|"
      if [ ! -z "$unxp" ]
      then
        echo "Unexpected |${unxp}|"
        exit 1
      fi
    elif [ "${TARGET_PLATFORM}" == "linux" ]
    then
      echo
      echo "${file_name} (${file_path})"
      set +e
      readelf -d "${file_path}" | egrep -i '(SONAME)'
      readelf -d "${file_path}" | egrep -i '(RUNPATH|RPATH)'
      readelf -d "${file_path}" | egrep -i '(NEEDED)'

      if has_rpath_origin "${file_path}"
      then 
        :
      else
        echo "${file_path} has no DT_RPATH \$ORIGIN ?????????????????????????????????????????"
        exit 1
      fi

      local so_names=$(readelf -d "${file_path}" \
        | grep -i 'Shared library' \
        | sed -e 's/.*Shared library: \[\(.*\)\]/\1/' \
      )

      local relative_path=$(readelf -d "${file_path}" | egrep -i '(RUNPATH|RPATH)' | sed -e 's/.*\[\$ORIGIN//' | sed -e 's/\].*//')
      # echo $relative_path

      for so_name in ${so_names}
      do
        if [ ! -f "${folder_path}${relative_path}/${so_name}" ] 
        then
          if is_linux_sys_so "${so_name}"
          then
            :
          elif [[ ${so_name} == libpython* ]] && [[ ${file_name} == *-gdb-py ]]
          then
            :
          else
            echo "Unexpected |${so_name}|"
            exit 1
          fi
        fi
      done
      set -e
    else
      echo "Oops! Unsupported ${TARGET_PLATFORM}."
      exit 1
    fi
  )
}

function is_win_sys_dll() 
{
  local dll_name="$(echo "$1" | tr "[:upper:]" "[:lower:]")"

  # DLLs that are expected to be present on any Windows.
  # Be sure all names are lower case!
  local sys_dlls=( \
    advapi32.dll \
    bcrypt.dll \
    cabinet.dll \
    cfgmgr32.dll \
    comctl32.dll
    crypt32.dll \
    dnsapi.dll \
    gdi32.dll \
    imm32.dll \
    imm32.dll \
    iphlpapi.dll \
    iphlpapi.dll \
    kernel32.dll \
    msi.dll \
    msvcr71.dll \
    msvcr80.dll \
    msvcr90.dll \
    msvcrt.dll \
    ole32.dll \
    oleaut32.dll \
    psapi.dll \
    rpcrt4.dll \
    setupapi.dll \
    shell32.dll \
    shlwapi.dll \
    user32.dll \
    userenv.dll \
    vcruntime140.dll \
    version.dll \
    winmm.dll \
    winmm.dll \
    ws2_32.dll \
    \
    api-ms-win-crt-conio-l1-1-0.dll \
    api-ms-win-crt-convert-l1-1-0.dll \
    api-ms-win-crt-environment-l1-1-0.dll \
    api-ms-win-crt-filesystem-l1-1-0.dll \
    api-ms-win-crt-heap-l1-1-0.dll \
    api-ms-win-crt-locale-l1-1-0.dll \
    api-ms-win-crt-math-l1-1-0.dll \
    api-ms-win-crt-process-l1-1-0.dll \
    api-ms-win-crt-runtime-l1-1-0.dll \
    api-ms-win-crt-string-l1-1-0.dll \
    api-ms-win-crt-stdio-l1-1-0.dll \
    api-ms-win-crt-time-l1-1-0.dll \
    api-ms-win-crt-utility-l1-1-0.dll \
  )

  # The Python DLL were a permanent source of trouble.
  # python27.dll \
  # The latest Python 2.7.18 has no DLL at all, so it cannot be skipped.
  # python37.dll \
  # The Python 3 seems better, allow to copy it in the archive,
  # to be sure it matches the version used during build.

  local dll
  for dll in "${sys_dlls[@]}"
  do
    if [ "${dll}" == "${dll_name}" ]
    then
      return 0 # True
    fi
  done
  return 1 # False
}

function is_linux_sys_so() 
{
  local lib_name="$1"

  # Do not add these two, they are present if the toolchain is installed, 
  # but this is not guaranteed, so better copy them from the xbb toolchain.
  # libstdc++.so.6 
  # libgcc_s.so.1 

  # Shared libraries that are expected to be present on any Linux.
  # Note the X11 libraries.
  local sys_lib_names=(\
    librt.so.1 \
    libm.so.6 \
    libc.so.6 \
    libnsl.so.1 \
    libutil.so.1 \
    libpthread.so.0 \
    libdl.so.2 \
    ld-linux.so.2 \
    ld-linux.so.3 \
    ld-linux-x86-64.so.2 \
    ld-linux-armhf.so.3 \
    ld-linux-arm64.so.1 \
    ld-linux-aarch64.so.1 \
    libX11.so.6 \
    libXau.so.6 \
    libxcb.so.1 \
  )

  local sys_lib_name
  for sys_lib_name in "${sys_lib_names[@]}"
  do
    if [ "${lib_name}" == "${sys_lib_name}" ]
    then
      return 0 # True
    fi
  done
  return 1 # False
}

function is_darwin_sys_dylib() 
{
  local lib_name="$1"

  if [[ ${lib_name} == /usr/lib* ]]
  then
    return 0 # True
  fi
  if [[ ${lib_name} == /System/Library/Frameworks/* ]]
  then
    return 0 # True
  fi
  if [[ ${lib_name} == /Library/Frameworks/* ]]
  then
    return 0 # True
  fi

  return 1 # False
}

function is_darwin_allowed_sys_dylib() 
{
  local lib_name="$1"

  # Since there is no -static-libc++, the first attempt was to not 
  # define these here and have the 10.10 ones copied to the application. 
  # Building CMake proved that this is ok with 10.11 and 10.12, but 
  # failes on 10.13 and 10.14 with:
  # dyld: Symbol not found: __ZNSt3__118shared_timed_mutex13unlock_sharedEv
  # Referenced from: /System/Library/Frameworks/CoreDisplay.framework/Versions/A/CoreDisplay
  # Expected in: /Users/travis/test-cmake/xpack-cmake-3.17.1-1/bin/libc++.1.dylib
  # in /System/Library/Frameworks/CoreDisplay.framework/Versions/A/CoreDisplay
  #
  # /usr/lib/libc++.dylib \
  # /usr/lib/libc++.1.dylib \
  # /usr/lib/libc++abi.dylib \

  # Same for -static-libgcc; there were no cases which failed on later releases,
  # but for consistency, they are also included here.
  #
  # /usr/lib/libgcc_s.1.dylib \

  local sys_libs=(\
    /usr/lib/libgcc_s.1.dylib \
    \
    /usr/lib/libc++.dylib \
    /usr/lib/libc++.1.dylib \
    /usr/lib/libc++abi.dylib \
    \
    /usr/lib/libSystem.B.dylib \
    /usr/lib/libobjc.A.dylib \
    \
    /usr/lib/libutil.dylib \
  )

  if [[ ${lib_name} == /System/Library/Frameworks/* ]]
  then
    # Allow all system frameworks.
    return 0 # True
  fi

  local lib
  for lib in "${sys_libs[@]}"
  do
    if [ "${lib}" == "${lib_name}" ]
    then
      return 0 # True
    fi
  done
  return 1 # False
}

# -----------------------------------------------------------------------------

function has_origin()
{
  if [ $# -lt 1 ]
  then
    warning "has_origin: Missing file argument"
    exit 1
  fi

  local elf="$1"
  if [ "${TARGET_PLATFORM}" == "linux" ]
  then
    local origin=$(readelf -d ${elf} | egrep 'Library (runpath|rpath): \[\$ORIGIN\]')
    if [ ! -z "${origin}" ]
    then
      return 0 # true
    fi
  fi
  return 1 # false
}

function has_rpath_origin()
{
  if [ $# -lt 1 ]
  then
    warning "has_rpath_origin: Missing file argument"
    exit 1
  fi

  local elf="$1"
  if [ "${TARGET_PLATFORM}" == "linux" ]
  then
    local origin=$(readelf -d ${elf} | grep 'Library rpath: \[\$ORIGIN\]')
    if [ ! -z "${origin}" ]
    then
      return 0 # true
    fi
  fi
  return 1 # false
}

# DT_RPATH is searchd before LD_LIBRARY_PATH and DT_RUNPATH.
function has_rpath()
{
  if [ $# -lt 1 ]
  then
    warning "has_rpath: Missing file argument"
    exit 1
  fi

  local elf="$1"
  if [ "${TARGET_PLATFORM}" == "linux" ]
  then
    
    local rpath=$(readelf -d ${elf} | egrep -i '(RUNPATH|RPATH)')
    if [ ! -z "${rpath}" ]
    then
      return 0 # true
    fi
    
  fi
  return 1 # false
}


function strip_binaries()
{
  local folder_path="${APP_PREFIX}"
  if [ $# -ge 1 ]
  then
    folder_path="$1"
  fi

  if [ "${WITH_STRIP}" == "y" ]
  then
    (
      xbb_activate

      echo
      echo "Stripping binaries..."

      # Otherwise `find` may fail.
      cd "${WORK_FOLDER_PATH}"

      local binaries
      if [ "${TARGET_PLATFORM}" == "win32" ]
      then

        binaries=$(find "${folder_path}" \( -name \*.exe -o -name '*.dll' \))
        for bin in ${binaries} 
        do
          strip_binary "${bin}"
        done

      elif [ "${TARGET_PLATFORM}" == "darwin" ]
      then

        binaries=$(find "${folder_path}" -name \* -perm +111  -type f)
        for bin in ${binaries} 
        do
          if is_elf "${bin}"
          then
            if is_target "${bin}"
            then
              strip_binary "${bin}"
            else
              if [ "${IS_DEVELOP}" == "y" ]
              then
                echo "$(file "${bin}") (not for target architecture)"
              fi
            fi
          fi
        done

      elif [ "${TARGET_PLATFORM}" == "linux" ]
      then

        binaries=$(find "${folder_path}" -name \* -type f)
        for bin in ${binaries} 
        do
          if is_elf "${bin}"
          then
            if is_target "${bin}"
            then
              strip_binary "${bin}"
            else
              if [ "${IS_DEVELOP}" == "y" ]
              then
                echo "$(file "${bin}") (not for target architecture)"
              fi
            fi
          fi
        done

      fi
    )
  fi
}


# Strip binary files as in "strip binary" form, for both native
# (linux/mac) and mingw.
function strip_binary2() 
{
  (
    set +e
    if [ $# -lt 2 ]
    then
        warning "strip_binary: Missing arguments"
        exit 1
    fi

    local strip="$1"
    local bin="$2"

    if is_elf "${bin}"
    then
      if has_origin "${bin}"
      then
        echo "${strip} ${bin} skipped (patched)"
      else
        echo "${strip} ${bin}"
        # ${strip} ${bin} 2>/dev/null || true
        "${strip}" -S "${bin}" || true
      fi
    else
      echo $(file "${bin}")
    fi

    set -e
  )
}

function strip_binary() 
{
  if [ $# -lt 1 ]
  then
    warning "strip_binary: Missing file argument"
    exit 1
  fi

  local file_path="$1"

  local strip
  set +u
  strip="${STRIP}"
  if [ "${TARGET_PLATFORM}" == "win32" ]
  then
    if [ -z "${strip}" ]
    then
      strip="${CROSS_COMPILE_PREFIX}-strip"
    fi
    if [[ "${file_path}" != *.exe ]] && [[ "${file_path}" != *.dll ]]
    then
      file_path="${file_path}.exe"
    fi
  else
    if [ -z "${strip}" ]
    then
      strip="strip"
    fi
  fi
  set -u

  if is_elf "${file_path}"
  then
    :
  else
    echo $(file "${file_path}")
    return
  fi  

  if has_origin "${file_path}"
  then
    # If the file was patched, skip strip, otherwise
    # we may damage the binary due to a bug in strip.
    echo "${strip} ${file_path} skipped (patched)"
    return
  fi

  echo "${strip} ${file_path}"
  "${strip}" -S "${file_path}" || true
}

function is_elf()
{
  if [ $# -lt 1 ]
  then
    warning "is_elf: Missing arguments"
    exit 1
  fi

  local bin_path="$1"

  # Symlinks do not match.
  if [ -L "${bin_path}" ]
  then
    return 1
  fi

  if [ -f "${bin_path}" ]
  then
    # Return 0 (true) if found.
    if [ "${TARGET_PLATFORM}" == "linux" ]
    then
      file ${bin_path} | egrep -q "( ELF )"
    elif [ "${TARGET_PLATFORM}" == "darwin" ]
    then
      file ${bin_path} | egrep -q "( Mach-O )"
    elif [ "${TARGET_PLATFORM}" == "win32" ]
    then
      file ${bin_path} | egrep -q "( PE )|( PE32 )|( PE32\+ )"
    fi
  else
    return 1
  fi
}

function is_target()
{
  if [ $# -lt 1 ]
  then
    warning "is_target: Missing arguments"
    exit 1
  fi

  local bin_path="$1"

  # Symlinks do not match.
  if [ -L "${bin_path}" ]
  then
    return 1
  fi

  if [ -f "${bin_path}" ]
  then
    # Return 0 (true) if found.
    if [ "${TARGET_PLATFORM}" == "linux" -a "${TARGET_ARCH}" == "x64" ]
    then
      file ${bin_path} | egrep -q ", x86-64, "
    elif [ "${TARGET_PLATFORM}" == "linux" -a "${TARGET_ARCH}" == "x32" ]
    then
      file ${bin_path} | egrep -q ", Intel 80386, "
    elif [ "${TARGET_PLATFORM}" == "linux" -a "${TARGET_ARCH}" == "arm64" ]
    then
      file ${bin_path} | egrep -q ", ARM aarch64, "
    elif [ "${TARGET_PLATFORM}" == "linux" -a "${TARGET_ARCH}" == "arm" ]
    then
      file ${bin_path} | egrep -q ", ARM, "
    elif [ "${TARGET_PLATFORM}" == "darwin"-a "${TARGET_ARCH}" == "x64" ]
    then
      file ${bin_path} | egrep -q " x86_64"
    elif [ "${TARGET_PLATFORM}" == "win32" -a "${TARGET_ARCH}" == "x64" ]
    then
      file ${bin_path} | egrep -q " x86-64 "
    elif [ "${TARGET_PLATFORM}" == "win32" -a "${TARGET_ARCH}" == "x32" ]
    then
      file ${bin_path} | egrep -q " Intel 80386"
    fi
  else
    return 1
  fi
}

function is_elf_dynamic()
{
  if [ $# -lt 1 ]
  then
    warning "is_elf_dynamic: Missing arguments"
    exit 1
  fi

  local bin_path="$1"

  if is_elf "${bin_path}"
  then
    # Return 0 (true) if found.
    file ${bin_path} | egrep -q "dynamically"
  else
    return 1
  fi

}

function is_dynamic()
{
  if [ $# -lt 1 ]
  then
    warning "is_dynamic: Missing arguments"
    exit 1
  fi

  local bin_path="$1"

  if [ -f "${bin_path}" ]
  then
    # Return 0 (true) if found.
    file ${bin_path} | egrep -q "dynamically"
  else
    return 1
  fi
}

function is_darwin_dylib()
{
  if [ $# -lt 1 ]
  then
    warning "is_darwin_dylib: Missing arguments"
    exit 1
  fi

  local bin_path="$1"
  local real_path

  # Follow symlinks.
  if [ -L "${bin_path}" ]
  then
    real_path="$(realpath "${bin_path}")"
  else
    real_path="${bin_path}"
  fi

  if [ -f "${real_path}" ]
  then
    # Return 0 (true) if found.
    file ${real_path} | egrep -q "dynamically linked shared library"
  else
    return 1
  fi
}

function is_ar()
{
  if [ $# -lt 1 ]
  then
    warning "is_ar: Missing arguments"
    exit 1
  fi

  local bin_path="$1"

  # Symlinks do not match.
  if [ -L "${bin_path}" ]
  then
    return 1
  fi

  if [ -f "${bin_path}" ]
  then
    # Return 0 (true) if found.
    file ${bin_path} | egrep -q "ar archive"
  else
    return 1
  fi
}

# -----------------------------------------------------------------------------

# Deprecated, use copy_dependencies_recursive().
function copy_win_gcc_dll() 
{
  local dll_name="$1"

  # Identify the current cross gcc version, to locate the specific dll folder.
  local cross_gcc_version=$(${CROSS_COMPILE_PREFIX}-gcc --version | grep 'gcc' | sed -e 's/.*\s\([0-9]*\)[.]\([0-9]*\)[.]\([0-9]*\).*/\1.\2.\3/')
  local cross_gcc_version_short=$(echo ${cross_gcc_version} | sed -e 's/\([0-9]*\)[.]\([0-9]*\)[.]\([0-9]*\).*/\1.\2/')
  local SUBLOCATION="-win32"

  # First try Ubuntu specific locations,
  # then do a long full search.

  if [ -f "${XBB_FOLDER_PATH}/${CROSS_COMPILE_PREFIX}/lib/${dll_name}" ]
  then
    cp -v "${XBB_FOLDER_PATH}/${CROSS_COMPILE_PREFIX}/lib/${dll_name}" \
      "${APP_PREFIX}/bin"
  elif [ -f "/usr/lib/gcc/${CROSS_COMPILE_PREFIX}/${cross_gcc_version}/${dll_name}" ]
  then
    cp -v "/usr/lib/gcc/${CROSS_COMPILE_PREFIX}/${cross_gcc_version}/${dll_name}" \
      "${APP_PREFIX}/bin"
  elif [ -f "/usr/lib/gcc/${CROSS_COMPILE_PREFIX}/${cross_gcc_version_short}/${dll_name}" ]
  then
    cp -v "/usr/lib/gcc/${CROSS_COMPILE_PREFIX}/${cross_gcc_version_short}/${dll_name}" \
      "${APP_PREFIX}/bin"
  elif [ -f "/usr/lib/gcc/${CROSS_COMPILE_PREFIX}/${cross_gcc_version_short}${SUBLOCATION}/${dll_name}" ]
  then
    cp -v "/usr/lib/gcc/${CROSS_COMPILE_PREFIX}/${cross_gcc_version_short}${SUBLOCATION}/${dll_name}" \
      "${APP_PREFIX}/bin"
  else
    echo "Searching /usr for ${dll_name}..."
    SJLJ_PATH=$(find "${XBB_FOLDER_PATH}/${CROSS_COMPILE_PREFIX}" /usr \! -readable -prune -o -name ${dll_name} -print | grep ${CROSS_COMPILE_PREFIX})
    cp -v ${SJLJ_PATH} "${APP_PREFIX}/bin"
  fi
}

# Deprecated, use copy_dependencies_recursive().
function copy_win_libwinpthread_dll() 
{
  if [ -f "${XBB_FOLDER_PATH}/${CROSS_COMPILE_PREFIX}/bin/libwinpthread-1.dll" ]
  then
    cp "${XBB_FOLDER_PATH}/${CROSS_COMPILE_PREFIX}/bin/libwinpthread-1.dll" \
      "${APP_PREFIX}/bin"
  else
    echo "No libwinpthread-1.dll"
    exit 1
  fi
}

# -----------------------------------------------------------------------------

function change_dylib()
{
  local dylib_name="$1"
  local file_path="$2"

  local dylib_path="$(otool -L "${file_path}" | sed '1d' | sed -e 's|[[:space:]]*\(.*\)[[:space:]][(].*[)]|\1|' | grep "${dylib_name}")"

  if [ -z "${dylib_path}" ]
  then
    echo "Dylib ${dylib_name} may not used in binary ${file_path}..."
    # for example libftdi1.2.4.0.dylib has the name libftdi1.2.dylib.
    # exit 1
  elif [ $(printf "${dylib_path}" | wc -l) -gt 1 ]
  then
    echo "${file_path} has multiple ${dylib_name} libraries..."
    exit 1
  fi

  # Hack to bring Python library name in line with the other libraries.
  if [ "${dylib_name}" == "Python" ]
  then
    local version="$(otool -L "${file_path}" | grep "${dylib_name}" | sed -e 's|.*current version \([0-9][0-9]*\.[0-9][0-9]*\).*|\1|')"
    dylib_name="libpython${version}.dylib"
    rm -rf "$(dirname ${file_path})/Python"
  fi

  chmod +w "${file_path}"
  install_name_tool \
    -change "${dylib_path}" \
    "@executable_path/${dylib_name}" \
    "${file_path}"

  if [ ! -f "$(dirname ${file_path})/${dylib_name}" ]
  then
    install -v -c -m 644 "${dylib_path}" "$(dirname ${file_path})/${dylib_name}"
  fi
}

# Workaround to Docker error on 32-bit image:
# stat: Value too large for defined data type (requires -D_FILE_OFFSET_BITS=64)
function patch_linux_elf_origin()
{
  if [ $# -lt 1 ]
  then 
    echo "patch_linux_elf_origin requires 1 args." 
    exit 1
  fi

  local file_path="$1"
  local libexec_path
  if [ $# -ge 2 ]
  then
    libexec_path="$2"
  else
    libexec_path="$(dirname "${file_path}")"
  fi

  local tmp_path=$(mktemp)
  rm -rf "${tmp_path}"
  cp "${file_path}" "${tmp_path}"

  if file "${tmp_path}" | grep statically
  then
    file "${file_path}"
  else
    if has_rpath "${file_path}"
    then
      echo patchelf --force-rpath --set-rpath "\$ORIGIN" "${file_path}"
      patchelf --force-rpath --set-rpath "\$ORIGIN" "${tmp_path}"
    else
      echo "${file_path} has no rpath!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
      exit 1
    fi
  fi

  cp "${tmp_path}" "${file_path}"
  rm -rf "${tmp_path}"
}

# $1 - absolute path to executable
# Note: must pass libexec path
# For single apps, otherwise use prepare_app_folder_libraries
# Does not use libexec.
function prepare_app_libraries()
{
  local app_path="$1"
  shift

  (
    xbb_activate

    local app_folder_path="$(dirname "${app_path}")"

    if [ "${WITH_STRIP}" == "y" ]
    then
      strip_binary "${app_path}"
    fi

    if [ "${TARGET_PLATFORM}" == "linux" ]
    then
      echo
      echo "Shared libraries:"
      echo "${app_path}"
      set +e
      readelf -d "${app_path}" | grep 'Shared library:'
      set -e

      echo
      echo "Preparing libraries..."
      patch_linux_elf_origin "${app_path}"

      echo
      copy_dependencies_recursive "${app_path}" "${app_folder_path}"

      echo
      echo "Updated shared libraries:"
      echo ldd -v "${app_path}"
      ldd -v "${app_path}"
    elif [ "${TARGET_PLATFORM}" == "darwin" ]
    then
      echo
      echo "Initial dynamic libraries:"
      otool -L "${app_path}"

      echo
      echo "Preparing libraries..."
      copy_dependencies_recursive "${app_path}" "${app_folder_path}"

      echo
      echo "Updated dynamic libraries:"
      otool -L "${app_path}"
    elif [ "${TARGET_PLATFORM}" == "win32" ]
    then
      echo
      echo "Dynamic libraries:"
      echo "${app_path}.exe"
      ${CROSS_COMPILE_PREFIX}-objdump -x "${app_path}.exe" | grep -i 'DLL Name'

      echo
      echo "Preparing libraries..."
      copy_dependencies_recursive "${app_path}.exe" "${app_folder_path}"
    else
      echo "Oops! Unsupported ${TARGET_PLATFORM}."
      exit 1
    fi
  )
}

# Process all executables and shared libraries.
function prepare_app_folder_libraries()
{
  local folder_path
  if [ $# -ge 1 ]
  then
    folder_path="$1"
  else
    folder_path="${APP_PREFIX}"
  fi

  local libexec_folder_path
  if [ $# -ge 2 ]
  then
    libexec_folder_path="$2"
  else
    libexec_folder_path="${APP_PREFIX}/libexec"
  fi

  (
    xbb_activate

    echo
    echo "Preparing ${folder_path} libraries..."

    # Otherwise `find` may fail.
    cd "${WORK_FOLDER_PATH}"

    local binaries
    if [ "${TARGET_PLATFORM}" == "win32" ]
    then

      binaries=$(find "${folder_path}" -name \*.exe)
      for bin in ${binaries} 
      do
        echo
        echo "Preparing $(basename "${bin}") ${bin} libraries..."
        # On Windows the DLLs are copied in the same folder.
        copy_dependencies_recursive "${bin}" "$(dirname "${bin}")"
      done

    elif [ "${TARGET_PLATFORM}" == "darwin" ]
    then

      binaries=$(find "${folder_path}" -name \* -perm +111 -type f)
      for bin in ${binaries} 
      do
        if is_elf "${bin}"
        then
          echo
          echo "Preparing $(basename "${bin}") ${bin} libraries..."
          copy_dependencies_recursive "${bin}" "$(dirname "${bin}")"
        fi
      done

    elif [ "${TARGET_PLATFORM}" == "linux" ]
    then

      binaries=$(find "${folder_path}" -name \* -type f)
      for bin_path in ${binaries} 
      do
        if is_elf_dynamic "${bin_path}"
        then
          echo
          echo "Preparing $(basename "${bin_path}") (${bin_path}) libraries..."
          # On Linux the shared libraries can be copied in the libexec folder,
          # and links be kept in the current folder, but not for 32-bit
          # Intel distros.
          # For consistency reasons, do the same on all platforms.
          if true # [ "${TARGET_ARCH}" == "x32" ]
          then
            copy_dependencies_recursive "${bin_path}" \
              "$(dirname "${bin_path}")"
          else
            copy_dependencies_recursive "${bin_path}" \
              "$(dirname "${bin_path}")" "${libexec_folder_path}"
          fi

          # echo $(basename "${bin_path}") $(readelf -d "${bin_path}" | egrep -i '(RUNPATH|RPATH)')
        fi
      done

    else
      echo "Oops! Unsupported ${TARGET_PLATFORM}."
      exit 1
    fi
  )
}

function copy_dependencies_recursive()
{
  if [ $# -lt 2 ]
  then 
    echo "copy_dependencies_recursive requires at least 2 arg." 
    exit 1
  fi

  local source_file_path="$1"
  local dest_folder_path="$2"

  local libexec_folder_path
  if [ $# -ge 3 ]
  then 
    libexec_folder_path="$3"
  else
    libexec_folder_path="${dest_folder_path}"
  fi

  # The first step is to copy the file to libexec/destination and link it.

  local source_file_name="$(basename "${source_file_path}")"
  local source_folder_path="$(dirname "${source_file_path}")"

  local actual_source_file_path=""
  local copied_file_path="${dest_folder_path}/${source_file_name}"

  # echo "I. Processing ${source_file_path} itself..."

  if [ ! -f "${dest_folder_path}/${source_file_name}" ]
  then

    if [ "${TARGET_PLATFORM}" == "win32" ]
    then
      # On Windows don't bother with sym links, simply copy the file
      # to the destination.

      actual_source_file_path="$(readlink -f "${source_file_path}")"
      copied_file_path="${dest_folder_path}/${source_file_name}"

    else
      # On POSIX copy to libexec and place a symlink at destination.
      
      if [ -L "${source_file_path}" ]
      then
        #
        # Compute the final absolute path of the link, regardless
        # how many links there are on the way.
        actual_source_file_path="$(readlink -f "${source_file_path}")"
        copied_file_path="${libexec_folder_path}/$(basename "${actual_source_file_path}")"
        
      elif is_elf "${source_file_path}"
      then

        if [ "${IS_DEVELOP}" == "y" ]
        then
          # The file is definitelly an elf, not a link.
          echo "is_elf ${source_file_name}"
        fi

        actual_source_file_path="${source_file_path}"
        copied_file_path="${libexec_folder_path}/${source_file_name}"

      else
        # Not a symlink and not an elf. Ignore it.
        echo "!!!!!!!!!!!!!!"
        return
      fi
    fi

  else
    : #echo "${dest_folder_path}/${source_file_name} already there"
  fi

  if [ ! -z "${actual_source_file_path}" ]
  then
    if [ ! -f "${copied_file_path}" ]
    then
      install -v -c -m 644 "${actual_source_file_path}" "${copied_file_path}"
    fi
  else
    actual_source_file_path="${source_file_path}"
  fi

  if [ "${WITH_STRIP}" == "y" ]
  then
    strip_binary "${copied_file_path}"
  fi

  if [ "${TARGET_PLATFORM}" == "linux" ]
  then
    patch_linux_elf_origin "${copied_file_path}"
  fi
  
  # If libexec is the destination, there is no need to link.
  if [ ! -f "${dest_folder_path}/${source_file_name}" ]
  then
    (
      cd "${dest_folder_path}"

      local link_relative_path="$(realpath --relative-to="${dest_folder_path}" "${copied_file_path}")"
      ln -sv "${link_relative_path}" "${source_file_name}" 
    )
  fi

  local actual_dest_file_path="$(realpath "${dest_folder_path}/${source_file_name}")"
  local actual_dest_folder_path="$(dirname "${actual_dest_file_path}")"

  # echo "II. Processing ${source_file_path} dependencies..."
  if [ "${TARGET_PLATFORM}" == "linux" ]
  then
    # The file must be an elf. Get its shared libraries.
    local lib_names=$(readelf -d "${dest_folder_path}/${source_file_name}" \
          | grep -i 'Shared library' \
          | sed -e 's/.*Shared library: \[\(.*\)\]/\1/')
    local lib_name
    for lib_name in ${lib_names}
    do
      if is_linux_sys_so "${lib_name}"
      then
        continue # System library, no need to copy it.
      else
        
        if [ -f "$(dirname "${actual_source_file_path}")/${lib_name}" ]
        then
          copy_dependencies_recursive "$(dirname "${actual_source_file_path}")/${lib_name}" \
            "${actual_dest_folder_path}" "${libexec_folder_path}" 
        elif [ -f "${LIBS_INSTALL_FOLDER_PATH}/lib64/${lib_name}" ]
        then
          copy_dependencies_recursive "${LIBS_INSTALL_FOLDER_PATH}/lib64/${lib_name}" \
            "${actual_dest_folder_path}" "${libexec_folder_path}" 
        elif [ -f "${LIBS_INSTALL_FOLDER_PATH}/lib/${lib_name}" ]
        then
          copy_dependencies_recursive "${LIBS_INSTALL_FOLDER_PATH}/lib/${lib_name}" \
            "${actual_dest_folder_path}" "${libexec_folder_path}"
        else
          # Not a compiled dependency, perhas a compiler dependency.
          local full_path=$(${CC} -print-file-name=${lib_name})
          # -print-file-name outputs back the requested name if not found.
          if [ "${full_path}" != "${lib_name}" ]
          then
            copy_dependencies_recursive "${full_path}" \
              "${actual_dest_folder_path}" "${libexec_folder_path}"
          else
            # If no toolchain library either, last chance is the XBB libraries.
            if [ -f "${XBB_FOLDER_PATH}/lib64/${lib_name}" ]
            then
              copy_dependencies_recursive "${XBB_FOLDER_PATH}/lib64/${lib_name}" \
                "${actual_dest_folder_path}" "${libexec_folder_path}"
            elif [ -f "${XBB_FOLDER_PATH}/lib/${lib_name}" ]
            then
              copy_dependencies_recursive "${XBB_FOLDER_PATH}/lib/${lib_name}" \
                "${actual_dest_folder_path}" "${libexec_folder_path}"
            else
              echo "${lib_name} not found in the compiled or XBB libraries."
              exit 1
            fi
          fi
        fi

        if [ ! -f "${actual_dest_folder_path}/${lib_name}" ]
        then
          echo "Oops! Dependency ${actual_dest_folder_path}/${lib_name} of ${source_file_name} not found"
          exit 1
        fi
      fi
    done
    # echo "iterate ${dest_folder_path}/${source_file_name} done"
  elif [ "${TARGET_PLATFORM}" == "darwin" ]
  then
    echo
    otool -L "${dest_folder_path}/${source_file_name}"
    local lib_paths
    if is_darwin_dylib "${dest_folder_path}/${source_file_name}"
    then
      lib_paths=$(otool -L "${dest_folder_path}/${source_file_name}" \
            | sed '1d' \
            | sed '1d' \
            | sed -e 's|[[:space:]]*\(.*\) (.*)|\1|' \
          )
    else
      lib_paths=$(otool -L "${dest_folder_path}/${source_file_name}" \
            | sed '1d' \
            | sed -e 's|[[:space:]]*\(.*\) (.*)|\1|' \
          )
    fi
    local exec_prefix="@executable_path/"
    local loader_path="@loader_path/"
    local lib_name
    for lib_path in ${lib_paths}
    do
      local lib_link_base
      if [ "${lib_path:0:1}" != "@" ]
      then
        lib_link_name="$(basename $(readlink -f ${lib_path}))"
        lib_name="$(basename "${lib_path}")"
      else
        lib_link_base=""
        lib_name="${lib_path:${#exec_prefix}}"
      fi

      if [ "${lib_path}" == "${exec_prefix}${source_file_name}" ]
      then
        :
      elif [ "${lib_path}" == "${loader_path}${source_file_name}" ]
      then
        :
      elif [ "${lib_link_name}" == "${source_file_name}" ]
      then
        : # Libraries return a line with their own name.
      else
        if is_darwin_sys_dylib "${lib_path}"
        then
          : # System library, no need to copy it.
          if is_darwin_allowed_sys_dylib "${lib_path}"
          then
            continue # System library, no need to copy it.
          else
            echo "Oops! \"${lib_path}\" should not be there!"
            exit 1
          fi
        else
          if [ -f "$(dirname "${actual_source_file_path}")/${lib_name}" ]
          then
            copy_dependencies_recursive "$(dirname "${actual_source_file_path}")/${lib_name}" \
              "${actual_dest_folder_path}" "${libexec_folder_path}" 
          elif [ -f "${LIBS_INSTALL_FOLDER_PATH}/lib64/${lib_name}" ]
          then
            copy_dependencies_recursive "${LIBS_INSTALL_FOLDER_PATH}/lib64/${lib_name}" \
              "${actual_dest_folder_path}" "${libexec_folder_path}" 
          elif [ -f "${LIBS_INSTALL_FOLDER_PATH}/lib/${lib_name}" ]
          then
            copy_dependencies_recursive "${LIBS_INSTALL_FOLDER_PATH}/lib/${lib_name}" \
              "${actual_dest_folder_path}" "${libexec_folder_path}"
          else
            # Not a compiled dependency, perhas a compiler dependency.
            local full_path=$(${CC} -print-file-name=${lib_name})
            # -print-file-name outputs back the requested name if not found.
            if [ "${full_path}" != "${lib_name}" ]
            then
              copy_dependencies_recursive "${full_path}" \
                "${actual_dest_folder_path}" "${libexec_folder_path}"
            else
              # If no toolchain library either, last chance is the XBB libraries.
              if [ -f "${XBB_FOLDER_PATH}/lib64/${lib_name}" ]
              then
                copy_dependencies_recursive "${XBB_FOLDER_PATH}/lib64/${lib_name}" \
                  "${actual_dest_folder_path}" "${libexec_folder_path}"
              elif [ -f "${XBB_FOLDER_PATH}/lib/${lib_name}" ]
              then
                copy_dependencies_recursive "${XBB_FOLDER_PATH}/lib/${lib_name}" \
                  "${actual_dest_folder_path}" "${libexec_folder_path}"
              else
                echo "${lib_name} not found in the compiled or XBB libraries."
                exit 1
              fi
            fi
          fi

          # Change library path to '@executable_path' inside the lib or app.
          change_dylib "${lib_name}" "${dest_folder_path}/${source_file_name}"
        fi
      fi
    done
  elif [ "${TARGET_PLATFORM}" == "win32" ]
  then
    local libs=$(${CROSS_COMPILE_PREFIX}-objdump -x "${dest_folder_path}/${source_file_name}" \
          | grep -i 'DLL Name' \
          | sed -e 's/.*DLL Name: \(.*\)/\1/' \
        )
    local lib_name
    for lib_name in ${libs}
    do
      if is_win_sys_dll "${lib_name}"
      then
        : # System DLL, no need to copy it.
      else
        if [ -f "${LIBS_INSTALL_FOLDER_PATH}/bin/${lib_name}" ]
        then
          # The first source is the install/libs/bin.
          copy_dependencies_recursive "${LIBS_INSTALL_FOLDER_PATH}/bin/${lib_name}" \
            "${dest_folder_path}"
        elif [ -f "${XBB_FOLDER_PATH}/${CROSS_COMPILE_PREFIX}/bin/${lib_name}" ]
        then
          copy_dependencies_recursive "${XBB_FOLDER_PATH}/${CROSS_COMPILE_PREFIX}/bin/${lib_name}" \
            "${dest_folder_path}"
        elif [ -f "${XBB_FOLDER_PATH}/mingw/bin/${lib_name}" ]
        then
          # Mainly to get libwinpthread-1.dll.
          copy_dependencies_recursive "${XBB_FOLDER_PATH}/mingw/bin/${lib_name}" \
            "${dest_folder_path}"
        else
          local full_path=$(${CROSS_COMPILE_PREFIX}-gcc -print-file-name=${lib_name})
          # -print-file-name outputs back the requested name if not found.
          if [ "${full_path}" != "${lib_name}" ]
          then
            copy_dependencies_recursive "${full_path}" "${dest_folder_path}"
          else
            echo "${lib_name} required by ${source_file_name}, not found"
            exit 1
          fi
        fi
      fi
    done
  else
    echo "Oops! Unsupported ${TARGET_PLATFORM}."
    exit 1
  fi

  if [ "${IS_DEVELOP}" == "y" ]
  then
    echo "dependency ${source_file_path} done"
  fi
}

function check_binaries()
{
  local folder_path="${APP_PREFIX}"
  if [ $# -ge 1 ]
  then
    folder_path="$1"
  fi

  (
    xbb_activate
    
    echo
    echo "Checking binaries for unwanted libraries..."

    # Otherwise `find` may fail.
    cd "${WORK_FOLDER_PATH}"

    local binaries
    if [ "${TARGET_PLATFORM}" == "win32" ]
    then

      binaries=$(find "${folder_path}" \( -name \*.exe -o -name \*.dll -o -name \*.pyd \))
      for bin in ${binaries} 
      do
        check_binary "${bin}"
      done

    elif [ "${TARGET_PLATFORM}" == "darwin" ]
    then

      binaries=$(find "${folder_path}" -name \* -type f)
      for bin in ${binaries} 
      do
        if is_elf "${bin}"
        then
          check_binary "${bin}"
        else
          if [ "${IS_DEVELOP}" == "y" ]
          then
            echo "$(file "${bin}") (not elf)"
          fi
        fi
      done

    elif [ "${TARGET_PLATFORM}" == "linux" ]
    then

      binaries=$(find "${folder_path}" -name \* -type f)
      for bin in ${binaries} 
      do
        if is_elf_dynamic "${bin}"
        then
          check_binary "${bin}"
        else
          if [ "${IS_DEVELOP}" == "y" ]
          then
            echo "$(file "${bin}") (not dynamic elf)"
          fi
        fi
      done

    else
      echo "Oops! Unsupported ${TARGET_PLATFORM}."
      exit 1
    fi
  )
}

# -----------------------------------------------------------------------------

# $1 - absolute path to input folder
# $2 - name of output folder below INSTALL_FOLDER
function copy_license() 
{
  # Iterate all files in a folder and install some of them in the
  # destination folder
  (
    if [ -z "$2" ]
    then
      return
    fi

    echo
    echo "Copying license files for $2..."

    cd "$1"
    local f
    for f in *
    do
      if [ -f "$f" ]
      then
        if [[ "$f" =~ AUTHORS.*|NEWS.*|COPYING.*|README.*|LICENSE.*|Copyright.*|COPYRIGHT.*|FAQ.*|DEPENDENCIES.*|THANKS.*|CHANGES.* ]]
        then
          install -d -m 0755 \
            "${APP_PREFIX}/${DISTRO_INFO_NAME}/licenses/$2"
          install -v -c -m 644 "$f" \
            "${APP_PREFIX}/${DISTRO_INFO_NAME}/licenses/$2"
        fi
      elif [ -d "$f" ] && [[ "$f" =~ [Ll][Ii][Cc][Ee][Nn][Ss][Ee]* ]]
      then
        install -d -m 0755 \
          "${APP_PREFIX}/${DISTRO_INFO_NAME}/licenses/$2"
        install -v -c -m 644 "$f"/* \
          "${APP_PREFIX}/${DISTRO_INFO_NAME}/licenses/$2"
      fi
    done
  )
  (
    xbb_activate

    if [ "${TARGET_PLATFORM}" == "win32" ]
    then
      find "${APP_PREFIX}/${DISTRO_INFO_NAME}/licenses" \
        -type f \
        -exec unix2dos '{}' ';'
    fi
  )
}

function copy_build_files()
{
  echo
  echo "Copying build files..."

  (
    cd "${BUILD_GIT_PATH}"

    mkdir -pv patches

    # Ignore hidden folders/files (like .DS_Store).
    find scripts patches -type d ! -iname '.*' \
      -exec install -d -m 0755 \
        "${APP_PREFIX}/${DISTRO_INFO_NAME}"/'{}' ';'

    find scripts patches -type f ! -iname '.*' \
      -exec install -v -c -m 644 \
        '{}' "${APP_PREFIX}/${DISTRO_INFO_NAME}"/'{}' ';'

    if [ -f CHANGELOG.txt ]
    then
      install -v -c -m 644 \
          CHANGELOG.txt "${APP_PREFIX}/${DISTRO_INFO_NAME}"
    fi
    if [ -f CHANGELOG.md ]
    then
      install -v -c -m 644 \
          CHANGELOG.md "${APP_PREFIX}/${DISTRO_INFO_NAME}"
    fi
  )
}

# Must be called in the build folder, like 
# cd "${LIBS_BUILD_FOLDER_PATH}"
# cd "${BUILD_FOLDER_PATH}"

function copy_cmake_logs()
{
  local folder_name="$1"

  echo
  echo "Preserving CMake log files..."
  rm -rf "${LOGS_FOLDER_PATH}/${folder_name}"
  mkdir -pv "${LOGS_FOLDER_PATH}/${folder_name}/CMakeFiles"

  (
    cd "${folder_name}"
    cp -v "CMakeCache.txt" "${LOGS_FOLDER_PATH}/${folder_name}"

    cp -v "CMakeFiles"/*.log "${LOGS_FOLDER_PATH}/${folder_name}/CMakeFiles"
  )
}

# -----------------------------------------------------------------------------

# Copy one folder to another
function copy_dir() 
{
  local from_path="$1"
  local to_path="$2"

  set +u
  # rm -rf "${to_path}"
  mkdir -pv "${to_path}"

  (
    cd "${from_path}"
    if [ "${TARGET_PLATFORM}" == "darwin" ]
    then
      find . -xdev -print0 | cpio -oa0 | (cd "${to_path}" && cpio -im)
    else
      find . -xdev -print0 | cpio -oa0V | (cd "${to_path}" && cpio -imuV)
    fi
  )

  set -u
}

# -----------------------------------------------------------------------------

function create_archive()
{
  (
    xbb_activate

    local distribution_file_version="${RELEASE_VERSION}"

    local target_folder_name=${TARGET_FOLDER_NAME}

    if [ "${HAS_NAME_ARCH}" != "y" ]
    then
      # Pre xPack distributions use the old file name convention.
      distribution_file_version="${RELEASE_VERSION}-${DISTRIBUTION_FILE_DATE}"

      if [ "${TARGET_PLATFORM}" == "win32" ]
      then
        target_folder_name="win${TARGET_BITS}"
      elif [ "${TARGET_PLATFORM}" == "darwin" ]
      then
        target_folder_name="macos"
      elif [ "${TARGET_PLATFORM}" == "linux" ]
      then
        target_folder_name="${CONTAINER_DISTRO_LC_NAME}${TARGET_BITS}"
      else
        echo "Oops! Unsupported ${TARGET_PLATFORM}."
        exit 1
      fi
    fi

    local distribution_file="${DEPLOY_FOLDER_PATH}/${DISTRO_LC_NAME}-${APP_LC_NAME}-${distribution_file_version}-${target_folder_name}"

    local archive_version_path
    archive_version_path="${INSTALL_FOLDER_PATH}/archive/${DISTRO_LC_NAME}-${APP_LC_NAME}-${distribution_file_version}"

    cd "${APP_PREFIX}"
    find . -name '.DS_Store' -exec rm '{}' ';'

    echo
    echo "Creating distribution..."

    mkdir -pv "${DEPLOY_FOLDER_PATH}"

    # The folder is temprarily moved into a versioned folder like
    # xpack-<app-name>-<version>, or, in previous versions, 
    # in a more elaborate hierarchy like
    # xPacks/<app-name>/<version>.
    # After the archive is created, the folders are moved back.
    # The atempt to transform the tar path fails, since symlinks were
    # also transformed, which is bad.
    if [ "${TARGET_PLATFORM}" == "win32" ]
    then

      local distribution_file="${distribution_file}.zip"

      if [ "${USE_SINGLE_FOLDER_PATH}" != "y" ]
      then
        # DEPRECATED!
        archive_version_path="${INSTALL_FOLDER_PATH}/archive/${DISTRO_UC_NAME}/${APP_UC_NAME}/${distribution_file_version}"
      fi

      echo
      echo "ZIP file: \"${distribution_file}\"."

      rm -rf "${INSTALL_FOLDER_PATH}/archive"
      mkdir -pv "${archive_version_path}"
      mv "${APP_PREFIX}"/* "${archive_version_path}"

      cd "${INSTALL_FOLDER_PATH}/archive"
      zip -r9 -q "${distribution_file}" *

      # Put everything back.
      mv "${archive_version_path}"/* "${APP_PREFIX}"

    else

      # Unfortunately on node.js, xz & bz2 require native modules, which
      # proved unsafe, some xz versions failed to compile on node.js v9.x,
      # so use the good old .tar.gz.
      local distribution_file
      if [ "${USE_TAR_GZ}" == "y" ]
      then
        # Some platforms (like Arduino) accept only this explicit path.
        distribution_file="${distribution_file}.tar.gz"
      else
        distribution_file="${distribution_file}.tgz"
      fi

      local archive_version_path
      if [ "${USE_SINGLE_FOLDER_PATH}" != "y" ]
      then
        # DEPRECATED!
        archive_version_path="${INSTALL_FOLDER_PATH}/archive/${DISTRO_TOP_FOLDER_PATH}/${APP_LC_NAME}/${distribution_file_version}"
      fi

      echo "Compressed tarball: \"${distribution_file}\"."

      rm -rf "${INSTALL_FOLDER_PATH}/archive"
      mkdir -pv "${archive_version_path}"
      mv -v "${APP_PREFIX}"/* "${archive_version_path}"

      # Without --hard-dereference the hard links may be turned into
      # broken soft links on macOS.
      cd "${INSTALL_FOLDER_PATH}"/archive
      # -J uses xz for compression; best compression ratio.
      # -j uses bz2 for compression; good compression ratio.
      # -z uses gzip for compression; fair compression ratio.
      tar -c -z -f "${distribution_file}" \
        --owner=0 \
        --group=0 \
        --format=posix \
        --hard-dereference \
        *

      # Put folders back.
      mv -v "${archive_version_path}"/* "${APP_PREFIX}"

    fi

    cd "${DEPLOY_FOLDER_PATH}"
    compute_sha shasum -a 256 "$(basename ${distribution_file})"
  )
}

# -----------------------------------------------------------------------------

# $1 = application name
function check_application()
{
  local app_name=$1

  if [ "${TARGET_PLATFORM}" == "linux" ]
  then

    echo
    echo "Checking binaries for unwanted shared libraries..."

    check_binary "${APP_PREFIX}/bin/${app_name}"

    local libs=$(find "${APP_PREFIX}/bin" -name \*.so.\* -type f)
    local lib
    for lib in ${libs} 
    do
      check_binary_for_libraries "${lib}"
    done

  elif [ "${TARGET_PLATFORM}" == "darwin" ]
  then

    echo
    echo "Checking binaries for unwanted dynamic libraries..."

    check_binary "${APP_PREFIX}/bin/${app_name}"

    local libs=$(find "${APP_PREFIX}/bin" -name \*.dylib -type f)
    local lib
    for lib in ${libs} 
    do
      check_binary_for_libraries "${lib}"
    done

  elif [ "${TARGET_PLATFORM}" == "win32" ]
  then

    echo
    echo "Checking binaries for unwanted DLLs..."

    check_binary "${APP_PREFIX}/bin/${app_name}.exe"

    local libs=$(find "${APP_PREFIX}/bin" -name \*.dll -type f)
    local lib
    for lib in ${libs} 
    do
      check_binary_for_libraries "${lib}"
    done

  else
    echo "Oops! Unsupported ${TARGET_PLATFORM}."
    exit 1
  fi

  echo
}

# -----------------------------------------------------------------------------

function compute_sha() 
{
  # $1 shasum program
  # $2.. options
  # ${!#} file

  file=${!#}
  sha_file="${file}.sha"
  "$@" >"${sha_file}"
  echo "SHA: $(cat ${sha_file})"
}

# -----------------------------------------------------------------------------

function prime_wine()
{
  if [  "${TARGET_PLATFORM}" == "win32" ]
  then
    (
      xbb_activate

      echo
      winecfg &>/dev/null
      echo "wine primed, testing..."
    )
  fi
}

# -----------------------------------------------------------------------------

function copy_distro_files()
{
  (
    xbb_activate

    echo
    mkdir -pv "${APP_PREFIX}/${DISTRO_INFO_NAME}"

    copy_build_files

    echo
    echo "Copying xPack files..."

    cd "${BUILD_GIT_PATH}"
    README_OUT_FILE_NAME="${README_OUT_FILE_NAME:-README-OUT.md}"
    install -v -c -m 644 "scripts/${README_OUT_FILE_NAME}" \
      "${APP_PREFIX}/README.md"
  )
}

# -----------------------------------------------------------------------------

function tests_initialize()
{
  test_functions=()
}

function tests_add()
{
  test_functions+=("$1")
}

function tests_run()
{
  echo
  echo "Runnng final tests..."

  for test_function in ${test_functions[@]}
  do
    echo
    local func=$(echo ${test_function} | sed -e 's|-|_|g')
    echo "Running ${func}..."
    ${func}
  done
}

# -----------------------------------------------------------------------------
