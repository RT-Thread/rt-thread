# Templates to be used with copy/paste in the bash source files.

# Build xxx library.

function do_xxx() 
{
  # XXX_VERSION="1.1"

  XXX_SRC_FOLDER_NAME="xxx-${XXX_VERSION}"
  XXX_FOLDER_NAME="${XXX_SRC_FOLDER_NAME}"
  local xxx_archive="${XXX_SRC_FOLDER_NAME}.tar.gz"
  local xxx_url="http://.../${xxx_archive}"

  local xxx_stamp_file_path="${STAMPS_FOLDER_PATH}/stamp-xxx-installed"
  if [ ! -f "${xxx_stamp_file_path}" ]
  then

    cd "${WORK_FOLDER_PATH}"

    download_and_extract "${xxx_url}" "${xxx_archive}" \
      "${XXX_SRC_FOLDER_NAME}"

    (
      mkdir -pv "${BUILD_FOLDER_PATH}/${XXX_FOLDER_NAME}"
      cd "${BUILD_FOLDER_PATH}/${XXX_FOLDER_NAME}"

      xbb_activate

      export CFLAGS="${XBB_CFLAGS}"
      export CPPFLAGS="${XBB_CPPFLAGS}"
      export LDFLAGS="${XBB_LDFLAGS}"
      
      if [ ! -f "config.status" ]
      then 

        echo
        echo "Running xxx configure..."

        (
          bash "${WORK_FOLDER_PATH}/${XXX_SRC_FOLDER_NAME}/configure" --help

          bash "${WORK_FOLDER_PATH}/${XXX_SRC_FOLDER_NAME}/configure" \
            --prefix="${INSTALL_FOLDER_PATH}" \
            \
            --build=${BUILD} \
            --host=${HOST} \
            --target=${TARGET} \
            \
            --disable-shared \
            --enable-static

        ) 2>&1 | tee "${INSTALL_FOLDER_PATH}/configure-xxx-output.txt"
        cp "config.log" "${INSTALL_FOLDER_PATH}"/config-xxx-log.txt

      fi

      echo
      echo "Running xxx make..."

      (
        # Build.
        make -j ${JOBS}
        if [ "${WITH_STRIP}" == "y" ]
        then
          make install-strip
        else
          make install
        fi
      ) 2>&1 | tee "${INSTALL_FOLDER_PATH}/make-xxx-output.txt"
    )

    touch "${xxx_stamp_file_path}"

  else
    echo "Library xxx already installed."
  fi
}
