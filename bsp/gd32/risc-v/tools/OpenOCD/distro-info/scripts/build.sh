#!/usr/bin/env bash
# -----------------------------------------------------------------------------
# This file is part of the xPack distribution.
#   (https://xpack.github.io)
# Copyright (c) 2019 Liviu Ionescu.
#
# Permission to use, copy, modify, and/or distribute this software 
# for any purpose is hereby granted, under the terms of the MIT license.
# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
# Safety settings (see https://gist.github.com/ilg-ul/383869cbb01f61a51c4d).

if [[ ! -z ${DEBUG} ]]
then
  set ${DEBUG} # Activate the expand mode if DEBUG is anything but empty.
else
  DEBUG=""
fi

set -o errexit # Exit if command failed.
set -o pipefail # Exit if pipe failed.
set -o nounset # Exit if variable not set.

# Remove the initial space and instead use '\n'.
IFS=$'\n\t'

# -----------------------------------------------------------------------------
# Identify the script location, to reach, for example, the helper scripts.

build_script_path="$0"
if [[ "${build_script_path}" != /* ]]
then
  # Make relative path absolute.
  build_script_path="$(pwd)/$0"
fi

script_folder_path="$(dirname "${build_script_path}")"
script_folder_name="$(basename "${script_folder_path}")"

# =============================================================================

# Script to build the xPack OpenOCD distribution packages.
#
# Developed on macOS 10.13 High Sierra, but intended to run on
# macOS 10.10 Yosemite and CentOS 6 XBB. 

# -----------------------------------------------------------------------------

echo
echo "xPack OpenOCD distribution build script."

host_functions_script_path="${script_folder_path}/helper/host-functions-source.sh"
source "${host_functions_script_path}"

common_functions_script_path="${script_folder_path}/common-functions-source.sh"
source "${common_functions_script_path}"

defines_script_path="${script_folder_path}/defs-source.sh"
source "${defines_script_path}"

host_detect

# For clarity, explicitly define the docker images here.
docker_linux64_image=${docker_linux64_image:-"ilegeul/ubuntu:amd64-12.04-xbb-v3.2"}
docker_linux32_image=${docker_linux32_image:-"ilegeul/ubuntu:i386-12.04-xbb-v3.2"}
docker_linux_arm64_image=${docker_linux_arm64_image:-"ilegeul/ubuntu:arm64v8-16.04-xbb-v3.2"}
docker_linux_arm32_image=${docker_linux_arm32_image:-"ilegeul/ubuntu:arm32v7-16.04-xbb-v3.2"}

# -----------------------------------------------------------------------------

# Array where the remaining args will be stored.
declare -a rest

help_message="    bash $0 [--win32] [--win64] [--linux32] [--linux64] [--arm32] [--arm64] [--osx] [--all] [clean|cleanlibs|cleanall|preload-images] [--env-file file] [--disable-strip] [--without-pdf] [--with-html] [--develop] [--debug] [--jobs N] [--help]"
host_options "${help_message}" "$@"

# Intentionally moved after option parsing.
echo
echo "Host helper functions source script: \"${host_functions_script_path}\"."
echo "Common functions source script: \"${common_functions_script_path}\"."
echo "Definitions source script: \"${defines_script_path}\"."

host_common

# -----------------------------------------------------------------------------

CONTAINER_RUN_AS_ROOT="y"

if [ ! -z "${DO_BUILD_LINUX64}${DO_BUILD_WIN64}${DO_BUILD_LINUX_ARM64}${DO_BUILD_LINUX32}${DO_BUILD_WIN32}${DO_BUILD_LINUX_ARM32}" ]
then
  host_prepare_docker
fi

if [ -z "${DO_BUILD_ANY}" ]
then

  # ----- Build the native distribution. --------------------------------------

  host_build_target "Creating the native distribution..." \
    --script "${HOST_WORK_FOLDER_PATH}/${CONTAINER_BUILD_SCRIPT_REL_PATH}" \
    --env-file "${ENV_FILE}" \
    -- \
    ${rest[@]-}

else

  # ----- Build the OS X distribution. ----------------------------------------

  if [ "${DO_BUILD_OSX}" == "y" ]
  then
    if [ "${HOST_UNAME}" == "Darwin" ]
    then
      host_build_target "Creating the OS X distribution..." \
        --script "${HOST_WORK_FOLDER_PATH}/${CONTAINER_BUILD_SCRIPT_REL_PATH}" \
        --env-file "${ENV_FILE}" \
        --target-platform "darwin" \
        -- \
        ${rest[@]-}
    else
      echo "Building the macOS image is not possible on this platform."
      exit 1
    fi
  fi

  # ----- Build the GNU/Linux 64-bit distribution. ----------------------------

  if [ "${DO_BUILD_LINUX64}" == "y" ]
  then
    host_build_target "Creating the GNU/Linux 64-bit distribution..." \
      --script "${CONTAINER_WORK_FOLDER_PATH}/${CONTAINER_BUILD_SCRIPT_REL_PATH}" \
      --env-file "${ENV_FILE}" \
      --target-platform "linux" \
      --target-arch "x64" \
      --target-machine "x86_64" \
      --target-bits 64 \
      --docker-image "${docker_linux64_image}" \
      -- \
      ${rest[@]-}
  fi

  # ----- Build the Windows 64-bit distribution. ------------------------------

  if [ "${DO_BUILD_WIN64}" == "y" ]
  then
    host_build_target "Creating the Windows 64-bit distribution..." \
      --script "${CONTAINER_WORK_FOLDER_PATH}/${CONTAINER_BUILD_SCRIPT_REL_PATH}" \
      --env-file "${ENV_FILE}" \
      --target-platform "win32" \
      --target-arch "x64" \
      --target-machine "x86_64" \
      --target-bits 64 \
      --docker-image "${docker_linux64_image}" \
      -- \
      ${rest[@]-}
  fi

  # ----- Build the GNU/Linux 32-bit distribution. ----------------------------

  if [ "${DO_BUILD_LINUX32}" == "y" ]
  then
    host_build_target "Creating the GNU/Linux 32-bit distribution..." \
      --script "${CONTAINER_WORK_FOLDER_PATH}/${CONTAINER_BUILD_SCRIPT_REL_PATH}" \
      --env-file "${ENV_FILE}" \
      --target-platform "linux" \
      --target-arch "x32" \
      --target-machine "i386" \
      --target-bits 32 \
      --docker-image "${docker_linux32_image}" \
      -- \
      ${rest[@]-}
  fi

  # ----- Build the Windows 32-bit distribution. ------------------------------

  # Since the actual container is a 32-bit, use the debian32 binaries.
  if [ "${DO_BUILD_WIN32}" == "y" ]
  then
    host_build_target "Creating the Windows 32-bit distribution..." \
      --script "${CONTAINER_WORK_FOLDER_PATH}/${CONTAINER_BUILD_SCRIPT_REL_PATH}" \
      --env-file "${ENV_FILE}" \
      --target-platform "win32" \
      --target-arch "x32" \
      --target-machine "i386" \
      --target-bits 32 \
      --docker-image "${docker_linux32_image}" \
      -- \
      ${rest[@]-}
  fi

  # ----- Build the GNU/Linux Arm 64-bit distribution. ------------------------

  if [ "${DO_BUILD_LINUX_ARM64}" == "y" ]
  then
    host_build_target "Creating the GNU/Linux Arm 64-bit distribution..." \
      --script "${CONTAINER_WORK_FOLDER_PATH}/${CONTAINER_BUILD_SCRIPT_REL_PATH}" \
      --env-file "${ENV_FILE}" \
      --target-platform "linux" \
      --target-arch "arm64" \
      --target-machine "aarch64" \
      --target-bits 64 \
      --docker-image "${docker_linux_arm64_image}" \
      -- \
      ${rest[@]-}
  fi

  # ----- Build the GNU/Linux Arm 32-bit distribution. ------------------------

  if [ "${DO_BUILD_LINUX_ARM32}" == "y" ]
  then
    host_build_target "Creating the GNU/Linux Arm 32-bit distribution..." \
      --script "${CONTAINER_WORK_FOLDER_PATH}/${CONTAINER_BUILD_SCRIPT_REL_PATH}" \
      --env-file "${ENV_FILE}" \
      --target-platform "linux" \
      --target-arch "arm" \
      --target-machine "armhf" \
      --target-bits 32 \
      --docker-image "${docker_linux_arm32_image}" \
      -- \
      ${rest[@]-}
  fi

fi

host_show_sha

# -----------------------------------------------------------------------------

host_stop_timer

host_notify_completed

# Completed successfully.
exit 0

# -----------------------------------------------------------------------------
