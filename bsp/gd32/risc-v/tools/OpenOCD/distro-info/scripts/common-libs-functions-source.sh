# -----------------------------------------------------------------------------
# This file is part of the xPack distribution.
#   (https://xpack.github.io)
# Copyright (c) 2019 Liviu Ionescu.
#
# Permission to use, copy, modify, and/or distribute this software 
# for any purpose is hereby granted, under the terms of the MIT license.
# -----------------------------------------------------------------------------

# Helper script used in the second edition of the xPack build 
# scripts. As the name implies, it should contain only functions and 
# should be included with 'source' by the container build scripts.

# -----------------------------------------------------------------------------

function do_libusb1()
{
  # https://sourceforge.net/projects/libusb/files/libusb-1.0/
  # https://aur.archlinux.org/cgit/aur.git/tree/PKGBUILD?h=mingw-w64-libusb

  # 2015-09-14, 1.0.20
  # 2018-03-25, 1.0.22

  local libusb1_version="$1"

  local libusb1_src_folder_name="libusb-${libusb1_version}"

  local libusb1_archive="${libusb1_src_folder_name}.tar.bz2"
  local libusb1_url="http://sourceforge.net/projects/libusb/files/libusb-1.0/${libusb1_src_folder_name}/${libusb1_archive}"

  local libusb1_folder_name="${libusb1_src_folder_name}"

  local libusb1_stamp_file_path="${INSTALL_FOLDER_PATH}/stamp-libusb1-${libusb1_version}-installed"
  if [ ! -f "${libusb1_stamp_file_path}" ]
  then

    cd "${SOURCES_FOLDER_PATH}"

    download_and_extract "${libusb1_url}" "${libusb1_archive}" \
      "${libusb1_src_folder_name}"

    mkdir -pv "${LOGS_FOLDER_PATH}/${libusb1_folder_name}"

    (
      mkdir -pv "${LIBS_BUILD_FOLDER_PATH}/${libusb1_folder_name}"
      cd "${LIBS_BUILD_FOLDER_PATH}/${libusb1_folder_name}"

      xbb_activate
      xbb_activate_installed_dev

      if [ "${TARGET_PLATFORM}" == "darwin" ]
      then
        # GCC-7 fails to compile Darwin USB.h:
        # error: too many #pragma options align=reset
        export CC=clang
      fi

      CPPFLAGS="${XBB_CPPFLAGS}"
      CFLAGS="${XBB_CFLAGS_NO_W}"
      CXXFLAGS="${XBB_CXXFLAGS_NO_W}"
      LDFLAGS="${XBB_LDFLAGS_LIB}"
      if [ "${TARGET_PLATFORM}" == "linux" ]
      then
        LDFLAGS+=" -Wl,-rpath,${LD_LIBRARY_PATH}"
      fi      
      if [ "${IS_DEVELOP}" == "y" ]
      then
        LDFLAGS+=" -v"
      fi

      export CPPFLAGS
      export CFLAGS
      export CXXFLAGS
      export LDFLAGS

      env | sort

      if [ ! -f "config.status" ]
      then 

        (
          echo
          echo "Running libusb1 configure..."

          bash "${SOURCES_FOLDER_PATH}/${libusb1_src_folder_name}/configure" --help

          config_options=()

          config_options+=("--prefix=${LIBS_INSTALL_FOLDER_PATH}")
            
          config_options+=("--build=${BUILD}")
          config_options+=("--host=${HOST}")
          config_options+=("--target=${TARGET}")

          run_verbose bash ${DEBUG} "${SOURCES_FOLDER_PATH}/${libusb1_src_folder_name}/configure" \
            ${config_options[@]}
          
          cp "config.log" "${LOGS_FOLDER_PATH}/${libusb1_folder_name}/config-log.txt"
        ) 2>&1 | tee "${LOGS_FOLDER_PATH}/${libusb1_folder_name}/configure-output.txt"

      fi

      (
        echo
        echo "Running libusb1 make..."

        # Build. 
        run_verbose make -j ${JOBS}

        if [ "${WITH_STRIP}" == "y" ]
        then
          run_verbose make install-strip
        else
          run_verbose make install
        fi

      ) 2>&1 | tee "${LOGS_FOLDER_PATH}/${libusb1_folder_name}/make-output.txt"

      copy_license \
        "${SOURCES_FOLDER_PATH}/${libusb1_src_folder_name}" \
        "${libusb1_folder_name}"
    )

    touch "${libusb1_stamp_file_path}"

  else
    echo "Library libusb1 already installed."
  fi
}

# Required by GNU/Linux and macOS.
function do_libusb0()
{
  # https://sourceforge.net/projects/libusb/files/libusb-compat-0.1/

  # 2013-05-21, 0.1.5, latest
  
  local libusb0_version="$1"

  local libusb0_src_folder_name="libusb-compat-${libusb0_version}"

  local libusb0_archive="${libusb0_src_folder_name}.tar.bz2"
  local libusb0_url="http://sourceforge.net/projects/libusb/files/libusb-compat-0.1/${libusb0_src_folder_name}/${libusb0_archive}"

  local libusb0_folder_name="${libusb0_src_folder_name}"

  local libusb0_stamp_file_path="${INSTALL_FOLDER_PATH}/stamp-libusb0-${libusb0_version}-installed"
  if [ ! -f "${libusb0_stamp_file_path}" ]
  then

    cd "${SOURCES_FOLDER_PATH}"

    download_and_extract "${libusb0_url}" "${libusb0_archive}" \
      "${libusb0_src_folder_name}"

    mkdir -pv "${LOGS_FOLDER_PATH}/${libusb0_folder_name}"

    (
      mkdir -pv "${LIBS_BUILD_FOLDER_PATH}/${libusb0_folder_name}"
      cd "${LIBS_BUILD_FOLDER_PATH}/${libusb0_folder_name}"

      xbb_activate
      xbb_activate_installed_dev

      CPPFLAGS="${XBB_CPPFLAGS}"
      CFLAGS="${XBB_CFLAGS_NO_W}"
      CXXFLAGS="${XBB_CXXFLAGS_NO_W}"
      LDFLAGS="${XBB_LDFLAGS_LIB}"
      if [ "${TARGET_PLATFORM}" == "linux" ]
      then
        LDFLAGS+=" -Wl,-rpath,${LD_LIBRARY_PATH}"
      fi      
      if [ "${IS_DEVELOP}" == "y" ]
      then
        LDFLAGS+=" -v"
      fi

      export CPPFLAGS
      export CFLAGS
      export CXXFLAGS
      export LDFLAGS

      env | sort

      if [ ! -f "config.status" ]
      then 

        (
          echo
          echo "Running libusb0 configure..."

          bash "${SOURCES_FOLDER_PATH}/${libusb0_src_folder_name}/configure" --help

          config_options=()

          config_options+=("--prefix=${LIBS_INSTALL_FOLDER_PATH}")
            
          config_options+=("--build=${BUILD}")
          config_options+=("--host=${HOST}")
          config_options+=("--target=${TARGET}")

          run_verbose bash ${DEBUG} "${SOURCES_FOLDER_PATH}/${libusb0_src_folder_name}/configure" \
            ${config_options[@]}
          
          cp "config.log" "${LOGS_FOLDER_PATH}/${libusb0_folder_name}/config-log.txt"
        ) 2>&1 | tee "${LOGS_FOLDER_PATH}/${libusb0_folder_name}/configure-output.txt"

      fi

      (
        echo
        echo "Running libusb0 make..."

        # Build.
        run_verbose make -j ${JOBS}

        if [ "${WITH_STRIP}" == "y" ]
        then
          run_verbose make install-strip
        else
          run_verbose make install
        fi

      ) 2>&1 | tee "${LOGS_FOLDER_PATH}/${libusb0_folder_name}/make-output.txt"

      copy_license \
        "${SOURCES_FOLDER_PATH}/${libusb0_src_folder_name}" \
        "${libusb0_folder_name}"
    )

    touch "${libusb0_stamp_file_path}"

  else
    echo "Library libusb0 already installed."
  fi
}

# Required by Windows.
function do_libusb_w32()
{
  # https://sourceforge.net/projects/libusb-win32/files/libusb-win32-releases/
  # 2012-01-17, 1.2.6.0 
  # libusb_w32_version="1.2.6.0" # +PATCH!

  local libusb_w32_version="$1"

  local libusb_w32_prefix="libusb-win32"
  local libusb_w32_prefix_version="${libusb_w32_prefix}-${libusb_w32_version}"

  local libusb_w32_src_folder_name="${libusb_w32_prefix}-src-${libusb_w32_version}"

  local libusb_w32_archive="${libusb_w32_src_folder_name}.zip"
  local linusb_w32_url="http://sourceforge.net/projects/libusb-win32/files/libusb-win32-releases/${libusb_w32_version}/${libusb_w32_archive}"

  local libusb_w32_folder_name="${libusb_w32_src_folder_name}"

  local libusb_w32_patch="libusb-win32-${libusb_w32_version}-mingw-w64.patch"

  local libusb_w32_stamp_file_path="${INSTALL_FOLDER_PATH}/stamp-libusb-w32-${libusb_w32_version}-installed"
  if [ ! -f "${libusb_w32_stamp_file_path}" ]
  then

    cd "${SOURCES_FOLDER_PATH}"

    download_and_extract "${linusb_w32_url}" "${libusb_w32_archive}" \
      "${libusb_w32_src_folder_name}"

    mkdir -pv "${LOGS_FOLDER_PATH}/${libusb_w32_folder_name}"

    # Mandatory build in the source folder, so make a local copy.
    rm -rf "${LIBS_BUILD_FOLDER_PATH}/${libusb_w32_folder_name}"
    mkdir -pv "${LIBS_BUILD_FOLDER_PATH}/${libusb_w32_folder_name}"
    cp -r "${SOURCES_FOLDER_PATH}/${libusb_w32_src_folder_name}"/* \
      "${LIBS_BUILD_FOLDER_PATH}/${libusb_w32_folder_name}"

    (
      echo
      echo "Running libusb-win32 make..."

      cd "${LIBS_BUILD_FOLDER_PATH}/${libusb_w32_folder_name}"

      xbb_activate
      xbb_activate_installed_dev

      # Patch from:
      # https://gitorious.org/jtag-tools/openocd-mingw-build-scripts

      # The conversions are needed to avoid errors like:
      # 'Hunk #1 FAILED at 31 (different line endings).'
      dos2unix src/install.c
      dos2unix src/install_filter_win.c
      dos2unix src/registry.c

      if [ -f "${BUILD_GIT_PATH}/patches/${libusb_w32_patch}" ]
      then
        patch -p0 < "${BUILD_GIT_PATH}/patches/${libusb_w32_patch}"
      fi

      # Build.
      (
          CPPFLAGS="${XBB_CPPFLAGS}"
          CFLAGS="${XBB_CFLAGS_NO_W}"
          CXXFLAGS="${XBB_CXXFLAGS_NO_W}"
          LDFLAGS="${XBB_LDFLAGS_LIB}"
          if [ "${IS_DEVELOP}" == "y" ]
          then
            LDFLAGS+=" -v"
          fi

          export CPPFLAGS
          export CFLAGS
          export CXXFLAGS
          export LDFLAGS

          env | sort

          run_verbose make \
            host_prefix=${CROSS_COMPILE_PREFIX} \
            host_prefix_x86=i686-w64-mingw32 \
            dll
          
          # Manually install, could not find a make target.
          mkdir -pv "${LIBS_INSTALL_FOLDER_PATH}/bin"

          # Skipping it does not remove the reference from openocd, so for the
          # moment it is preserved.
          cp -v "${LIBS_BUILD_FOLDER_PATH}/${libusb_w32_folder_name}/libusb0.dll" \
            "${LIBS_INSTALL_FOLDER_PATH}/bin"

          mkdir -pv "${LIBS_INSTALL_FOLDER_PATH}/lib"
          cp -v "${LIBS_BUILD_FOLDER_PATH}/${libusb_w32_folder_name}/libusb.a" \
            "${LIBS_INSTALL_FOLDER_PATH}/lib"

          mkdir -pv "${LIBS_INSTALL_FOLDER_PATH}/lib/pkgconfig"
          sed -e "s|XXX|${LIBS_INSTALL_FOLDER_PATH}|" \
            "${BUILD_GIT_PATH}/pkgconfig/${libusb_w32_prefix_version}.pc" \
            > "${LIBS_INSTALL_FOLDER_PATH}/lib/pkgconfig/libusb.pc"

          mkdir -pv "${LIBS_INSTALL_FOLDER_PATH}/include/libusb"
          cp -v "${LIBS_BUILD_FOLDER_PATH}/${libusb_w32_folder_name}/src/lusb0_usb.h" \
            "${LIBS_INSTALL_FOLDER_PATH}/include/libusb/usb.h"

      ) 2>&1 | tee "${LOGS_FOLDER_PATH}/${libusb_w32_folder_name}/make-output.txt"

      copy_license \
        "${SOURCES_FOLDER_PATH}/${libusb_w32_src_folder_name}" \
        "${libusb_w32_folder_name}"
    )

    touch "${libusb_w32_stamp_file_path}"

  else
    echo "Library libusb-w32 already installed."
  fi
}

function do_libftdi()
{
  # http://www.intra2net.com/en/developer/libftdi/download.php
  # https://www.intra2net.com/en/developer/libftdi/download/libftdi1-1.4.tar.bz2

  # 1.2 (no date)
  # libftdi_version="1.2" # +PATCH!

  local libftdi_version="$1"

  local libftdi_src_folder_name="libftdi1-${libftdi_version}"

  local libftdi_archive="${libftdi_src_folder_name}.tar.bz2"

  libftdi_url="http://www.intra2net.com/en/developer/libftdi/download/${libftdi_archive}"

  local libftdi_folder_name="${libftdi_src_folder_name}"

  local libftdi_patch="libftdi1-${libftdi_version}-cmake-FindUSB1.patch"

  local libftdi_stamp_file_path="${INSTALL_FOLDER_PATH}/stamp-libftdi-${libftdi_version}-installed"
  if [ ! -f "${libftdi_stamp_file_path}" ]
  then

    cd "${SOURCES_FOLDER_PATH}"

    download_and_extract "${libftdi_url}" "${libftdi_archive}" \
      "${libftdi_src_folder_name}" \
      "${libftdi_patch}"

    mkdir -pv "${LOGS_FOLDER_PATH}/${libftdi_folder_name}"

    (
      mkdir -pv "${LIBS_BUILD_FOLDER_PATH}/${libftdi_folder_name}"
      cd "${LIBS_BUILD_FOLDER_PATH}/${libftdi_folder_name}"

      xbb_activate
      xbb_activate_installed_dev

      CPPFLAGS="${XBB_CPPFLAGS}"
      CFLAGS="${XBB_CFLAGS_NO_W}"
      CXXFLAGS="${XBB_CXXFLAGS_NO_W}"
      LDFLAGS="${XBB_LDFLAGS_LIB}"
      if [ "${TARGET_PLATFORM}" == "linux" ]
      then
        LDFLAGS+=" -Wl,-rpath,${LD_LIBRARY_PATH}"
      fi      
      if [ "${IS_DEVELOP}" == "y" ]
      then
        LDFLAGS+=" -v"
      fi

      export CPPFLAGS
      export CFLAGS
      export CXXFLAGS
      export LDFLAGS

      env | sort

      (
        echo
        echo "Running libftdi configure..."
        
        if [ "${TARGET_PLATFORM}" == "win32" ]
        then

          # Configure for Windows.
          run_verbose cmake \
            -DPKG_CONFIG_EXECUTABLE="${PKG_CONFIG}" \
            -DCMAKE_TOOLCHAIN_FILE="${SOURCES_FOLDER_PATH}/${libftdi_src_folder_name}/cmake/Toolchain-${CROSS_COMPILE_PREFIX}.cmake" \
            -DCMAKE_INSTALL_PREFIX="${LIBS_INSTALL_FOLDER_PATH}" \
            -DLIBUSB_INCLUDE_DIR="${LIBS_INSTALL_FOLDER_PATH}/include/libusb-1.0" \
            -DLIBUSB_LIBRARIES="${LIBS_INSTALL_FOLDER_PATH}/lib/libusb-1.0.a" \
            -DBUILD_TESTS:BOOL=off \
            -DFTDIPP:BOOL=off \
            -DPYTHON_BINDINGS:BOOL=off \
            -DEXAMPLES:BOOL=off \
            -DDOCUMENTATION:BOOL=off \
            -DFTDI_EEPROM:BOOL=off \
            "${SOURCES_FOLDER_PATH}/${libftdi_src_folder_name}"

        else

          # Configure for GNU/Linux and macOS.
          run_verbose cmake \
            -DPKG_CONFIG_EXECUTABLE="${PKG_CONFIG}" \
            -DCMAKE_INSTALL_PREFIX="${LIBS_INSTALL_FOLDER_PATH}" \
            -DBUILD_TESTS:BOOL=off \
            -DFTDIPP:BOOL=off \
            -DPYTHON_BINDINGS:BOOL=off \
            -DEXAMPLES:BOOL=off \
            -DDOCUMENTATION:BOOL=off \
            -DFTDI_EEPROM:BOOL=off \
            "${SOURCES_FOLDER_PATH}/${libftdi_src_folder_name}"

        fi
      ) 2>&1 | tee "${LOGS_FOLDER_PATH}/${libftdi_folder_name}/configure-output.txt"

      (
        echo
        echo "Running libftdi make..."

        # Build.
        run_verbose make -j ${JOBS}

        run_verbose make install

      ) 2>&1 | tee "${LOGS_FOLDER_PATH}/${libftdi_folder_name}/make-output.txt"

      copy_license \
        "${SOURCES_FOLDER_PATH}/${libftdi_src_folder_name}" \
        "${libftdi_folder_name}"
    )

    touch "${libftdi_stamp_file_path}"

  else
    echo "Library libftdi already installed."
  fi
}

function do_hidapi() 
{
  # https://github.com/signal11/hidapi/downloads

  # Oct 26, 2011, "0.7.0"

  # https://github.com/signal11/hidapi/archive/hidapi-0.8.0-rc1.zip
  # Oct 7, 2013, "0.8.0-rc1", latest on signal11's repository

  # https://github.com/libusb/hidapi/releases
  # https://github.com/libusb/hidapi/archive/hidapi-0.9.0.zip
  # Jun 19 2019 "hidapi-0.9.0", maintained releases by libusb

  local hidapi_version="$1"

  local hidapi_src_folder_name="hidapi-hidapi-${hidapi_version}"

  local hidapi_archive="hidapi-${hidapi_version}.zip"
  local hidapi_url="https://github.com/libusb/hidapi/archive/${hidapi_archive}"

  local hidapi_folder_name="${hidapi_src_folder_name}"

  local hidapi_stamp_file_path="${INSTALL_FOLDER_PATH}/stamp-hidapi-${hidapi_version}-installed"
  if [ ! -f "${hidapi_stamp_file_path}" ]
  then

    cd "${SOURCES_FOLDER_PATH}"

    download_and_extract "${hidapi_url}" "${hidapi_archive}" \
      "${hidapi_src_folder_name}"

    mkdir -pv "${LOGS_FOLDER_PATH}/${hidapi_folder_name}"

    # Mandatory build in the source folder, so make a local copy.
    rm -rf "${LIBS_BUILD_FOLDER_PATH}/${hidapi_folder_name}"
    mkdir -pv "${LIBS_BUILD_FOLDER_PATH}/${hidapi_folder_name}"
    cp -r "${SOURCES_FOLDER_PATH}/${hidapi_src_folder_name}"/* \
      "${LIBS_BUILD_FOLDER_PATH}/${hidapi_folder_name}"

    (
      cd "${LIBS_BUILD_FOLDER_PATH}/${hidapi_folder_name}"

      xbb_activate
      xbb_activate_installed_dev

      if [ "${TARGET_PLATFORM}" == "win32" ]
      then

        hidapi_OBJECT="hid.o"
        hidapi_A="libhid.a"

        cd "${LIBS_BUILD_FOLDER_PATH}/${hidapi_folder_name}/windows"

        CPPFLAGS="${XBB_CPPFLAGS}"
        CFLAGS="${XBB_CFLAGS_NO_W}"
        CXXFLAGS="${XBB_CXXFLAGS_NO_W}"
        LDFLAGS="${XBB_LDFLAGS_LIB}"
        if [ "${IS_DEVELOP}" == "y" ]
        then
          LDFLAGS+=" -v"
        fi

        export CPPFLAGS
        export CFLAGS
        export CXXFLAGS
        export LDFLAGS

        env | sort

        run_verbose make -f Makefile.mingw \
          CC=${CROSS_COMPILE_PREFIX}-gcc \
          "${hidapi_OBJECT}"

        # Make just compiles the file. Create the archive and convert it to library.
        # No dynamic/shared libs involved.
        ar -r  "${hidapi_A}" "${hidapi_OBJECT}"
        ${CROSS_COMPILE_PREFIX}-ranlib "${hidapi_A}"

        mkdir -pv "${LIBS_INSTALL_FOLDER_PATH}/lib"
        cp -v "${hidapi_A}" \
          "${LIBS_INSTALL_FOLDER_PATH}/lib"

        mkdir -pv "${LIBS_INSTALL_FOLDER_PATH}/lib/pkgconfig"
        sed -e "s|XXX|${LIBS_INSTALL_FOLDER_PATH}|" \
          "${BUILD_GIT_PATH}/pkgconfig/hidapi-${hidapi_version}-windows.pc" \
          > "${LIBS_INSTALL_FOLDER_PATH}/lib/pkgconfig/hidapi.pc"

        mkdir -pv "${LIBS_INSTALL_FOLDER_PATH}/include/hidapi"
        cp -v "${SOURCES_FOLDER_PATH}/${hidapi_folder_name}/hidapi/hidapi.h" \
          "${LIBS_INSTALL_FOLDER_PATH}/include/hidapi"

      elif [ "${TARGET_PLATFORM}" == "linux" -o "${TARGET_PLATFORM}" == "darwin" ]
      then

        if [ "${TARGET_PLATFORM}" == "linux" ]
        then
          do_copy_libudev

          export LIBS="-liconv"
        elif [ "${TARGET_PLATFORM}" == "darwin" ]
        then
          # error: unknown type name ‘dispatch_block_t’
          export CC="clang"
        fi

        echo
        echo "Running hidapi bootstrap..."

        run_verbose bash bootstrap

        CPPFLAGS="${XBB_CPPFLAGS}"
        CFLAGS="${XBB_CFLAGS_NO_W}"
        CXXFLAGS="${XBB_CXXFLAGS_NO_W}"
        LDFLAGS="${XBB_LDFLAGS_LIB}"
        if [ "${TARGET_PLATFORM}" == "linux" ]
        then
          LDFLAGS+=" -Wl,-rpath,${LD_LIBRARY_PATH}"
        fi      
        if [ "${IS_DEVELOP}" == "y" ]
        then
          LDFLAGS+=" -v"
        fi

        export CPPFLAGS
        export CFLAGS
        export CXXFLAGS
        export LDFLAGS

        env | sort

        (
          echo
          echo "Running hidapi configure..."

          bash "configure" --help
  
          config_options=()

          config_options+=("--prefix=${LIBS_INSTALL_FOLDER_PATH}")
            
          config_options+=("--build=${BUILD}")
          config_options+=("--host=${HOST}")
          config_options+=("--target=${TARGET}")

          config_options+=("--disable-testgui")

          run_verbose bash ${DEBUG} "configure" \
            ${config_options[@]}
        
          cp "config.log" "${LOGS_FOLDER_PATH}/${hidapi_folder_name}/config-log.txt"
        ) 2>&1 | tee "${LOGS_FOLDER_PATH}/${hidapi_folder_name}/configure-output.txt"

        (
          echo
          echo "Running hidapi make..."

          # Build.
          run_verbose make -j ${JOBS}

          if [ "${WITH_STRIP}" == "y" ]
          then
            run_verbose make install-strip
          else
            run_verbose make install
          fi

        ) 2>&1 | tee "${LOGS_FOLDER_PATH}/${hidapi_folder_name}/make-output.txt"

      fi

      rm -f "${LIBS_INSTALL_FOLDER_PATH}"/lib*/libhidapi-hidraw.la

      copy_license \
        "${SOURCES_FOLDER_PATH}/${hidapi_src_folder_name}" \
        "${hidapi_folder_name}"
    )

    touch "${hidapi_stamp_file_path}"

  else
    echo "Library hidapi already installed."
  fi
}

function do_copy_libudev()
{
  cp -v "/usr/include/libudev.h" "${LIBS_INSTALL_FOLDER_PATH}/include"

  if [ "${TARGET_ARCH}" == "x64" ]
  then
    if [ -f "/usr/lib/x86_64-linux-gnu/libudev.so" ]
    then
      cp -v "/usr/lib/x86_64-linux-gnu/libudev.so" "${LIBS_INSTALL_FOLDER_PATH}/lib"
      cp -v "/usr/lib/x86_64-linux-gnu/pkgconfig/libudev.pc" "${LIBS_INSTALL_FOLDER_PATH}/lib/pkgconfig"
    elif [ -f "/lib/x86_64-linux-gnu/libudev.so" ]
    then
      # In Debian 9 the location changed to /lib
      cp -v "/lib/x86_64-linux-gnu/libudev.so" "${LIBS_INSTALL_FOLDER_PATH}/lib"
      cp -v "/usr/lib/x86_64-linux-gnu/pkgconfig/libudev.pc" "${LIBS_INSTALL_FOLDER_PATH}/lib/pkgconfig"
    elif [ -f "/usr/lib/libudev.so" ]
    then
      # In ARCH the location is /usr/lib
      cp -v "/usr/lib/libudev.so" "${LIBS_INSTALL_FOLDER_PATH}/lib"
      cp -v "/usr/lib/pkgconfig/libudev.pc" "${LIBS_INSTALL_FOLDER_PATH}/lib/pkgconfig"
    elif [ -f "/usr/lib64/libudev.so" ]
    then
      # In CentOS the location is /usr/lib64
      cp -v "/usr/lib64/libudev.so" "${LIBS_INSTALL_FOLDER_PATH}/lib"
      cp -v "/usr/lib64/pkgconfig/libudev.pc" "${LIBS_INSTALL_FOLDER_PATH}/lib/pkgconfig"
    else
      echo "No libudev.so; abort."
      exit 1
    fi
  elif [ "${TARGET_ARCH}" == "x32" ] 
  then
    if [ -f "/usr/lib/i386-linux-gnu/libudev.so" ]
    then
      cp -v "/usr/lib/i386-linux-gnu/libudev.so" "${LIBS_INSTALL_FOLDER_PATH}/lib"
      cp -v "/usr/lib/i386-linux-gnu/pkgconfig/libudev.pc" "${LIBS_INSTALL_FOLDER_PATH}/lib/pkgconfig"
    elif [ -f "/lib/i386-linux-gnu/libudev.so" ]
    then
      # In Debian 9 the location changed to /lib
      cp -v "/lib/i386-linux-gnu/libudev.so" "${LIBS_INSTALL_FOLDER_PATH}/lib"
      cp -v "/usr/lib/i386-linux-gnu/pkgconfig/libudev.pc" "${LIBS_INSTALL_FOLDER_PATH}/lib/pkgconfig"
    elif [ -f "/lib/libudev.so.0" ]
    then
      # In CentOS the location is /lib 
      cp -v "/lib/libudev.so.0" "${LIBS_INSTALL_FOLDER_PATH}/lib"
      cp -v "/usr/lib/pkgconfig/libudev.pc" "${LIBS_INSTALL_FOLDER_PATH}/lib/pkgconfig"
    else
      echo "No libudev.so; abort."
      exit 1
    fi
  elif [ "${TARGET_ARCH}" == "arm64" ] 
  then
    if [ -f "/usr/lib/aarch64-linux-gnu/libudev.so" ]
    then
      cp -v "/usr/lib/aarch64-linux-gnu/libudev.so" "${LIBS_INSTALL_FOLDER_PATH}/lib"
      cp -v "/usr/lib/aarch64-linux-gnu/pkgconfig/libudev.pc" "${LIBS_INSTALL_FOLDER_PATH}/lib/pkgconfig"
    elif [ -f "/lib/aarch64-linux-gnu/libudev.so" ]
    then
      # In Debian 9 the location changed to /lib
      cp -v "/lib/aarch64-linux-gnu/libudev.so" "${LIBS_INSTALL_FOLDER_PATH}/lib"
      cp -v "/usr/lib/aarch64-linux-gnu/pkgconfig/libudev.pc" "${LIBS_INSTALL_FOLDER_PATH}/lib/pkgconfig"
    else
      echo "No libudev.so; abort."
      exit 1
    fi
  elif [ "${TARGET_ARCH}" == "arm" ] 
  then
    if [ -f "/usr/lib/arm-linux-gnueabihf/libudev.so" ]
    then
      cp -v "/usr/lib/arm-linux-gnueabihf/libudev.so" "${LIBS_INSTALL_FOLDER_PATH}/lib"
      cp -v "/usr/lib/arm-linux-gnueabihf/pkgconfig/libudev.pc" "${LIBS_INSTALL_FOLDER_PATH}/lib/pkgconfig"
    elif [ -f "/lib/arm-linux-gnueabihf/libudev.so" ]
    then
      # In Debian 9 the location changed to /lib
      cp -v "/lib/arm-linux-gnueabihf/libudev.so" "${LIBS_INSTALL_FOLDER_PATH}/lib"
      cp -v "/usr/lib/arm-linux-gnueabihf/pkgconfig/libudev.pc" "${LIBS_INSTALL_FOLDER_PATH}/lib/pkgconfig"
    else
      echo "No libudev.so; abort."
      exit 1
    fi
  fi
}
