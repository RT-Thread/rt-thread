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
# should be included with 'source' by the container build scripts.

# -----------------------------------------------------------------------------

function start_timer() 
{
  CONTAINER_BEGIN_SECOND=$(date +%s)
  echo
  echo "Container script \"$0\" started at $(date)."
}

function stop_timer() 
{
  local end_second=$(date +%s)
  echo
  echo "Container script \"$0\" completed at $(date)."
  local delta_seconds=$((end_second-CONTAINER_BEGIN_SECOND))
  if [ ${delta_seconds} -lt 100 ]
  then
    echo "Duration: ${delta_seconds} seconds."
  else
    local delta_minutes=$(((delta_seconds+30)/60))
    echo "Duration: ${delta_minutes} minutes."
  fi
}

# -----------------------------------------------------------------------------

function detect_container() 
{
  echo
  uname -a

  CONTAINER_DISTRO_NAME=""
  CONTAINER_UNAME="$(uname)"
  CONTAINER_NODE_PLATFORM=""
  CONTAINER_NODE_ARCH=""

  if [ "${CONTAINER_UNAME}" == "Darwin" ]
  then

    CONTAINER_BITS="64"
    CONTAINER_MACHINE="x86_64"

    CONTAINER_NODE_PLATFORM="darwin"
    CONTAINER_NODE_ARCH="x64"

    CONTAINER_DISTRO_NAME=Darwin
    CONTAINER_DISTRO_LC_NAME=darwin

  elif [ "${CONTAINER_UNAME}" == "Linux" ]
  then
    # ----- Determine distribution name and word size -----

    set +e
    CONTAINER_DISTRO_NAME=$(lsb_release -si)
    set -e

    CONTAINER_NODE_PLATFORM="linux"

    if [ -z "${CONTAINER_DISTRO_NAME}" ]
    then
      echo "Please install the lsb core package and rerun."
      CONTAINER_DISTRO_NAME="Linux"
    fi

    CONTAINER_MACHINE="$(uname -m)"
    if [ "${CONTAINER_MACHINE}" == "x86_64" ]
    then
      CONTAINER_BITS="64"
      CONTAINER_NODE_ARCH="x64"
    elif [ "${CONTAINER_MACHINE}" == "i686" ]
    then
      CONTAINER_BITS="32"
      CONTAINER_NODE_ARCH="x32"
    elif [ "${CONTAINER_MACHINE}" == "aarch64" ]
    then
      CONTAINER_BITS="64"
      CONTAINER_NODE_ARCH="arm64"
    elif [ "${CONTAINER_MACHINE}" == "armv7l" \
      -o "${CONTAINER_MACHINE}" == "armv8l" ]
    then
      CONTAINER_BITS="32"
      CONTAINER_NODE_ARCH="arm"
    else
      echo "Unknown uname -m ${CONTAINER_MACHINE}"
      exit 1
    fi

    CONTAINER_DISTRO_LC_NAME=$(echo ${CONTAINER_DISTRO_NAME} | tr "[:upper:]" "[:lower:]")

  else
    echo "Unknown uname ${CONTAINER_UNAME}"
    exit 1
  fi

  echo
  echo "Container script running on ${CONTAINER_DISTRO_NAME} ${CONTAINER_NODE_ARCH} (${CONTAINER_BITS}-bit)."
  echo "User $(whoami), in '${HOME}'"

  HAS_WINPTHREAD=${HAS_WINPTHREAD:-""}
  CONTAINER_ROOT_UMASK=${CONTAINER_ROOT_UMASK:-"000"}

  if [ -f "/.dockerenv" -a "$(whoami)" == "root" ]
  then
    umask ${CONTAINER_ROOT_UMASK}
  fi
}


# -----------------------------------------------------------------------------

function fix_ownership()
{
  if [ -f "/.dockerenv" -a "${CONTAINER_RUN_AS_ROOT}" == "y" ]
  then
    (
      xbb_activate
      
      # Set the owner of the folder and files created by the docker CentOS 
      # container to match the user running the build script on the host. 
      # When running on linux host, these folders and their content remain  
      # owned by root if this is not done. However, on macOS  
      # the owner used by Docker is the same as the macOS user, so an 
      # ownership change is not realy necessary. 
      echo
      echo "Changing ownership to non-root GNU/Linux user..."

      if [ -d "${BUILD_FOLDER_PATH}" ]
      then
        chown -R ${USER_ID}:${GROUP_ID} "${BUILD_FOLDER_PATH}"
      fi
      if [ -d "${INSTALL_FOLDER_PATH}" ]
      then
        chown -R ${USER_ID}:${GROUP_ID} "${INSTALL_FOLDER_PATH}"
      fi
      chown -R ${USER_ID}:${GROUP_ID} "${DEPLOY_FOLDER_PATH}"
    )
  fi
}

# -----------------------------------------------------------------------------

# Hack to make pdftex ignore errors.
# Used for newlib manuals, which issue some errors, but the
# pdf file is generated anyway.
function hack_pdfetex()
{
  local bin=$(which pdfetex)
  local hacked_pdfetex="hack/pdfetex"

  mkdir -pv "$(dirname "${hacked_pdfetex}")"
  rm -rf "${hacked_pdfetex}"
  echo '#!/usr/bin/env bash' >"${hacked_pdfetex}"
  echo 'set -x' >>"${hacked_pdfetex}"
  echo 'set +e' >>"${hacked_pdfetex}"
  echo "${bin}" '$@' >>"${hacked_pdfetex}"
  echo 'set -e' >>"${hacked_pdfetex}"
  echo 'true' >>"${hacked_pdfetex}"
  chmod +x "${hacked_pdfetex}"

  export PATH="$(pwd)/$(dirname "${hacked_pdfetex}"):${PATH}"
}

