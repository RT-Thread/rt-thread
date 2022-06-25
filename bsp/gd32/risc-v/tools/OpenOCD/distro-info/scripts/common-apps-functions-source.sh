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

function download_openocd() 
{
  if [ ! -d "${WORK_FOLDER_PATH}/${OPENOCD_SRC_FOLDER_NAME}" ]
  then
    (
      xbb_activate

      cd "${WORK_FOLDER_PATH}"
      git_clone "${OPENOCD_GIT_URL}" "${OPENOCD_GIT_BRANCH}" \
          "${OPENOCD_GIT_COMMIT}" "${OPENOCD_SRC_FOLDER_NAME}"
      cd "${WORK_FOLDER_PATH}/${OPENOCD_SRC_FOLDER_NAME}"
      git submodule update --init --recursive --remote
    )
  fi
}

# -----------------------------------------------------------------------------

function do_openocd()
{
    download_openocd

    (
      xbb_activate
      xbb_activate_installed_dev

      cd "${WORK_FOLDER_PATH}/${OPENOCD_SRC_FOLDER_NAME}"
      if [ ! -d "autom4te.cache" ]
      then
        ./bootstrap
      fi

      mkdir -pv "${APP_BUILD_FOLDER_PATH}"
      cd "${APP_BUILD_FOLDER_PATH}"

      export JAYLINK_CFLAGS='${XBB_CFLAGS} -fvisibility=hidden'

      config_options=()

      config_options+=("--prefix=${APP_PREFIX}")
        
      config_options+=("--build=${BUILD}")
      config_options+=("--host=${HOST}")
      config_options+=("--target=${TARGET}")

      config_options+=("--datarootdir=${INSTALL_FOLDER_PATH}")
      config_options+=("--localedir=${APP_PREFIX}/share/locale")
      config_options+=("--mandir=${APP_PREFIX_DOC}/man")
      config_options+=("--pdfdir=${APP_PREFIX_DOC}/pdf")
      config_options+=("--infodir=${APP_PREFIX_DOC}/info")
      config_options+=("--docdir=${APP_PREFIX_DOC}")
            
      config_options+=("--disable-wextra")
      config_options+=("--disable-werror")
      config_options+=("--enable-dependency-tracking")
            
      config_options+=("--enable-branding=${BRANDING}")
    
      # Add explicit functionality.
      config_options+=("--enable-aice")
      config_options+=("--enable-armjtagew")
      config_options+=("--enable-at91rm9200")
      config_options+=("--enable-bcm2835gpio")
      config_options+=("--enable-cmsis-dap")
      config_options+=("--enable-dummy")
      config_options+=("--enable-ep93xx")
      config_options+=("--enable-ft232r")
      config_options+=("--enable-ftdi")
      config_options+=("--enable-imx_gpio")
      config_options+=("--enable-jlink")
      config_options+=("--enable-jtag_vpi")
      config_options+=("--enable-kitprog")
      config_options+=("--enable-oocd_trace")
      config_options+=("--enable-opendous")
      config_options+=("--enable-openjtag")
      config_options+=("--enable-osbdm")
      config_options+=("--enable-presto")
      config_options+=("--enable-remote-bitbang")
      config_options+=("--enable-rlink")
      config_options+=("--enable-stlink")
      config_options+=("--enable-ti-icdi")
      config_options+=("--enable-ulink")
      config_options+=("--enable-usb-blaster")
      config_options+=("--enable-usb_blaster_2")
      config_options+=("--enable-usbprog")
      config_options+=("--enable-vsllink")
      config_options+=("--enable-xds110")

      # Disable drivers that apparently failed to build on all platforms.
      config_options+=("--disable-zy1000-master")
      config_options+=("--disable-zy1000")
      config_options+=("--disable-ioutil")
      config_options+=("--disable-minidriver-dummy")
      config_options+=("--disable-parport-ppdev")

      if [ "${TARGET_PLATFORM}" == "win32" ]
      then

        export OUTPUT_DIR="${BUILD_FOLDER_PATH}"
        
        # Without it, mingw redefines it as 0.
        CPPFLAGS="${XBB_CPPFLAGS} -D__USE_MINGW_ANSI_STDIO=1"
        CFLAGS="${XBB_CFLAGS_NO_W}" 
        CXXFLAGS="${XBB_CXXFLAGS_NO_W}" 
        LDFLAGS="${XBB_LDFLAGS_APP}"
        LIBS=""

        # --enable-minidriver-dummy -> configure error
        # --enable-zy1000 -> netinet/tcp.h: No such file or directory

        # --enable-openjtag_ftdi -> --enable-openjtag
        # --enable-presto_libftdi -> --enable-presto
        # --enable-usb_blaster_libftdi -> --enable-usb_blaster

        config_options+=("--enable-amtjtagaccel")
        config_options+=("--enable-gw16012")
        config_options+=("--enable-parport")
        config_options+=("--enable-parport-giveio")

        # --enable-sysfsgpio -> available only on Linux
        config_options+=("--disable-sysfsgpio")
        # --enable-buspirate -> not supported on mingw
        config_options+=("--disable-buspirate")

        # oocd_trace.h:22:10: fatal error: termios.h: No such file or directory
        config_options+=("--disable-oocd_trace")

      elif [ "${TARGET_PLATFORM}" == "linux" ]
      then

        CPPFLAGS="${XBB_CPPFLAGS}"
        CFLAGS="${XBB_CFLAGS_NO_W}"
        CXXFLAGS="${XBB_CXXFLAGS_NO_W}"
        LDFLAGS="${XBB_LDFLAGS_APP}" 
        LDFLAGS+=" -Wl,-rpath,${LD_LIBRARY_PATH}"
        LIBS="-lpthread -lrt -ludev"

        # --enable-minidriver-dummy -> configure error

        # --enable-openjtag_ftdi -> --enable-openjtag
        # --enable-presto_libftdi -> --enable-presto
        # --enable-usb_blaster_libftdi -> --enable-usb_blaster

        config_options+=("--enable-amtjtagaccel")
        config_options+=("--enable-buspirate")
        config_options+=("--enable-gw16012")
        config_options+=("--enable-parport")
        config_options+=("--enable-parport-giveio")
        config_options+=("--enable-sysfsgpio")

        config_options+=("--enable-oocd_trace")

      elif [ "${TARGET_PLATFORM}" == "darwin" ]
      then

        CPPFLAGS="${XBB_CPPFLAGS}"
        CFLAGS="${XBB_CFLAGS_NO_W}"
        CXXFLAGS="${XBB_CXXFLAGS_NO_W}"
        LDFLAGS="${XBB_LDFLAGS_APP}"
        LIBS="" # "-lobjc"

        # --enable-minidriver-dummy -> configure error

        # --enable-openjtag_ftdi -> --enable-openjtag
        # --enable-presto_libftdi -> --enable-presto
        # --enable-usb_blaster_libftdi -> --enable-usb_blaster

        config_options+=("--enable-buspirate")

        # --enable-amtjtagaccel -> 'sys/io.h' file not found
        config_options+=("--disable-amtjtagaccel")
        # --enable-gw16012 -> 'sys/io.h' file not found
        config_options+=("--disable-gw16012")
        config_options+=("--disable-parport")
        config_options+=("--disable-parport-giveio")
        # --enable-sysfsgpio -> available only on Linux
        config_options+=("--disable-sysfsgpio")

        # /Users/ilg/Work/openocd-0.10.0-14/openocd.git/src/target/oocd_trace.c: In function ‘oocd_trace_init’:
        # /Users/ilg/Work/openocd-0.10.0-14/openocd.git/src/target/oocd_trace.c:121:54: error: ‘B2500000’ undeclared (first use in this function)
        config_options+=("--disable-oocd_trace")

      else

        echo "Unsupported target platorm ${TARGET_PLATFORM}."
        exit 1

      fi

      export CPPFLAGS 
      export CFLAGS 
      export CXXFLAGS 
      export LDFLAGS
      export LIBS

      env | sort

      if [ ! -f "config.status" ]
      then

        # May be required for repetitive builds, because this is an executable built 
        # in place and using one for a different architecture may not be a good idea.
        rm -rfv "${WORK_FOLDER_PATH}/${OPENOCD_SRC_FOLDER_NAME}/jimtcl/autosetup/jimsh0"

        (
          echo
          echo "Running openocd configure..."
      
          bash "${WORK_FOLDER_PATH}/${OPENOCD_SRC_FOLDER_NAME}/configure" --help

          run_verbose bash ${DEBUG} "${WORK_FOLDER_PATH}/${OPENOCD_SRC_FOLDER_NAME}/configure" \
            ${config_options[@]}

          cp "config.log" "${LOGS_FOLDER_PATH}/config-openocd-log.txt"
        ) 2>&1 | tee "${LOGS_FOLDER_PATH}/configure-openocd-output.txt"

      fi

      (
        echo
        echo "Running openocd make..."
      
        # Build.
        run_verbose make -j ${JOBS} bindir="bin" pkgdatadir=""

        if [ "${WITH_STRIP}" == "y" ]
        then
          run_verbose make install-strip
        else
          run_verbose make install  
        fi

        if [ "${TARGET_PLATFORM}" == "linux" ]
        then
          # Hack to get libudev.so in line with the all rpath policy.
          # Manually add $ORIGIN to libudev.so (fingers crossed!).
          cp "${LIBS_INSTALL_FOLDER_PATH}/lib/libudev.so" "${APP_PREFIX}/bin"
          run_verbose patchelf --force-rpath --set-rpath "\$ORIGIN" "${APP_PREFIX}/bin/libudev.so"
        fi

        prepare_app_libraries "${APP_PREFIX}/bin/openocd"

        if [ "${TARGET_PLATFORM}" == "win32" ]
        then
          rm -f "${APP_PREFIX}/bin/openocdw.exe"
        fi

        (
          xbb_activate_tex

          if [ "${WITH_PDF}" == "y" ]
          then
            run_verbose make bindir="bin" pkgdatadir="" pdf 
            run_verbose make install-pdf
          fi

          if [ "${WITH_HTML}" == "y" ]
          then
            run_verbose make bindir="bin" pkgdatadir="" html
            run_verbose make install-html
          fi
        )

      ) 2>&1 | tee "${LOGS_FOLDER_PATH}/make-openocd-output.txt"

      copy_license \
        "${WORK_FOLDER_PATH}/${OPENOCD_SRC_FOLDER_NAME}" \
        "${OPENOCD_FOLDER_NAME}"
    )
}

function run_openocd()
{
  run_app "${APP_PREFIX}/bin/openocd" --version

  # Does not return 0.
  run_app "${APP_PREFIX}/bin/openocd" --help || true
}

# -----------------------------------------------------------------------------
