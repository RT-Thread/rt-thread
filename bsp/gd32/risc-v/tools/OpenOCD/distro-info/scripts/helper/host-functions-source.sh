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
# should be included with 'source' by the host build scripts.

# -----------------------------------------------------------------------------

function host_get_current_date() 
{
  # Use the UTC date as version in the name of the distribution file.
  DISTRIBUTION_FILE_DATE=${DISTRIBUTION_FILE_DATE:-$(date -u +%Y%m%d-%H%M)}

  # Leave a track of the start date, in case of resume needed.
  mkdir -pv "${HOST_WORK_FOLDER_PATH}"
  touch "${HOST_WORK_FOLDER_PATH}/${DISTRIBUTION_FILE_DATE}"
  echo
  echo "DISTRIBUTION_FILE_DATE=\"${DISTRIBUTION_FILE_DATE}\""
}

function host_start_timer() 
{
  HOST_BEGIN_SECOND=$(date +%s)
  echo
  echo "Script \"$0\" started at $(date)."
}

function host_stop_timer() 
{
  local host_end_second=$(date +%s)
  echo
  echo "Script \"$0\" completed at $(date)."
  local delta_seconds=$((host_end_second-HOST_BEGIN_SECOND))
  if [ ${delta_seconds} -lt 100 ]
  then
    echo "Duration: ${delta_seconds} seconds."
  else
    local delta_minutes=$(((delta_seconds+30)/60))
    echo "Duration: ${delta_minutes} minutes."
  fi
}

function host_notify_completed()
{
  if [ "${HOST_UNAME}" == "Darwin" ]
  then
    say "Wake up, the build completed successfully"
  fi
}

# -----------------------------------------------------------------------------

# Detect the machine the build runs on.
function host_detect() 
{
  echo
  uname -a

  HOST_UNAME="$(uname)"
  HOST_MACHINE="$(uname -m)"

  HOST_DISTRO_NAME="?" # Linux distribution name (Ubuntu|CentOS|...)
  HOST_DISTRO_LC_NAME="?" # Same, in lower case.

  HOST_NODE_ARCH="?" # Node.js process.arch (x32|x64|arm|arm64)
  HOST_NODE_PLATFORM="?" # Node.js process.platform (darwin|linux|win32)

  if [ "${HOST_UNAME}" == "Darwin" ]
  then
    # uname -p -> i386
    # uname -m -> x86_64

    HOST_BITS="64"

    HOST_DISTRO_NAME=Darwin
    HOST_DISTRO_LC_NAME=darwin

    HOST_NODE_ARCH="x64" # For now.
    HOST_NODE_PLATFORM="darwin"

  elif [ "${HOST_UNAME}" == "Linux" ]
  then
    # ----- Determine distribution name and word size -----

    # uname -p -> x86_64|i686 (unknown in recent versions, use -m)
    # uname -m -> x86_64|i686|aarch64|armv7l

    if [ "${HOST_MACHINE}" == "x86_64" ]
    then
      HOST_BITS="64"
      HOST_NODE_ARCH="x64"
    elif [ "${HOST_MACHINE}" == "i386" -o "${HOST_MACHINE}" == "i686" ]
    then
      HOST_BITS="32"
      HOST_NODE_ARCH="x32"
    elif [ "${HOST_MACHINE}" == "aarch64" ]
    then
      HOST_BITS="64"
      HOST_NODE_ARCH="arm64"
    elif [ "${HOST_MACHINE}" == "armv7l" -o "${HOST_MACHINE}" == "armv8l" ]
    then
      HOST_BITS="32"
      HOST_NODE_ARCH="arm"
    else
      echo "Unknown uname -m ${HOST_MACHINE}"
      exit 1
    fi

    HOST_NODE_PLATFORM="linux"

    local lsb_path=$(which lsb_release)
    if [ -z "${lsb_path}" ]
    then
      echo "Please install the lsb core package and rerun."
      exit 1
    fi

    HOST_DISTRO_NAME=$(lsb_release -si)
    HOST_DISTRO_LC_NAME=$(echo ${HOST_DISTRO_NAME} | tr "[:upper:]" "[:lower:]")

  else
    echo "Unsupported uname ${HOST_UNAME}"
    exit 1
  fi

  echo
  echo "Running on ${HOST_DISTRO_NAME} ${HOST_NODE_ARCH} (${HOST_BITS}-bit)."

  USER_ID=$(id -u)
  USER_NAME="$(id -u -n)"
  GROUP_ID=$(id -g)
  GROUP_NAME="$(id -g -n)"

  TARGET_ARCH="${HOST_NODE_ARCH}"
  TARGET_PLATFORM="${HOST_NODE_PLATFORM}"
  TARGET_MACHINE="${HOST_MACHINE}"

  IS_NATIVE=""
  IS_DEVELOP=""
  # Redefine it to "y" to run as root inside the container.
  CONTAINER_RUN_AS_ROOT=${CONTAINER_RUN_AS_ROOT:-""}
  HAS_WINPTHREAD=${HAS_WINPTHREAD:-""}
}

# -----------------------------------------------------------------------------

function host_prepare_cache()
{
  # The folder that caches all downloads is in Work, for easy access.
  HOST_CACHE_FOLDER_PATH=${HOST_CACHE_FOLDER_PATH:-"${HOME}/Work/cache"}
  CONTAINER_CACHE_FOLDER_PATH="/Host${HOST_CACHE_FOLDER_PATH}"

  mkdir -pv "${HOST_CACHE_FOLDER_PATH}"
}

function host_options()
{
  local help_message="$1"
  shift

  ACTION=""

  DO_BUILD_SOURCES=""

  DO_BUILD_WIN32=""
  DO_BUILD_WIN64=""
  DO_BUILD_LINUX32=""
  DO_BUILD_LINUX64=""
  DO_BUILD_LINUX_ARM32=""
  DO_BUILD_LINUX_ARM64=""
  DO_BUILD_OSX=""
  ENV_FILE=""

  argc=$#
  declare -a argv
  argv=( "$@" )
  if [ ! -z "${DEBUG}" ]
  then
    echo ${argv[@]-}
  fi
  i=0

  # Must be declared by the caller.
  # declare -a rest


  # Identify some of the options. The rest are collected and passed
  # to the container script.
  while [ $i -lt $argc ]
  do

    arg="${argv[$i]}"
    case "${arg}" in

      clean|cleanlibs|cleanall|preload-images)
        ACTION="${arg}"
        ;;

      --win32|--windows32)
        DO_BUILD_WIN32="y"
        ;;

      --win64|--windows64)
        DO_BUILD_WIN64="y"
        ;;

      --linux32)
        DO_BUILD_LINUX32="y"
        ;;

      --linux64)
        DO_BUILD_LINUX64="y"
        ;;

      --arm32)
        DO_BUILD_LINUX_ARM32="y"
        ;;

      --arm64)
        DO_BUILD_LINUX_ARM64="y"
        ;;

      --osx)
        DO_BUILD_OSX="y"
        ;;

      --sources)
        DO_BUILD_SOURCES="y"
        ;;

      --all)
        if [ "${HOST_NODE_ARCH}" == "arm64" ]
        then
          DO_BUILD_LINUX_ARM32="y"
          DO_BUILD_LINUX_ARM64="y"
        elif [ "${HOST_NODE_ARCH}" == "x64" ]
        then
          DO_BUILD_WIN32="y"
          DO_BUILD_WIN64="y"
          DO_BUILD_LINUX32="y"
          DO_BUILD_LINUX64="y"
          DO_BUILD_SOURCES="y"
          if [ "$(uname)" == "Darwin" ] 
          then
            DO_BUILD_OSX="y"
          fi
        else
          echo "--all supported only on 64-bit hosts"
        fi
        ;;

      --env-file)
        ((++i))
        ENV_FILE="${argv[$i]}"
        if [ ! -f "${ENV_FILE}" ];
        then
          echo "The specified environment file \"${ENV_FILE}\" does not exist, exiting..."
          exit 1
        fi
        ;;

      # Deprecated.
      --date)
        ((++i))
        DISTRIBUTION_FILE_DATE="${argv[$i]}"
        ;;

      --help)
        echo "Usage:"
        # Some of the options are processed by the container script.
        echo "${help_message}"
        echo
        exit 1
        ;;

      *)
        # Collect all other in an array. Append to the end.
        # Will be later processed by the container script.
        set +u
        rest[${#rest[*]}]="$arg"
        set -u
        ;;

    esac
    ((++i))

  done

  DO_BUILD_ANY="${DO_BUILD_OSX}${DO_BUILD_LINUX64}${DO_BUILD_LINUX_ARM64}${DO_BUILD_WIN64}${DO_BUILD_LINUX32}${DO_BUILD_LINUX_ARM32}${DO_BUILD_WIN32}${DO_BUILD_SOURCES}"

  # The ${rest[@]} options will be passed to the inner script.
  if [ ! -z "${DEBUG}" ]
  then
    echo ${rest[@]-}
  fi
}

function host_options_windows()
{
  local help_message="$1"
  shift

  ACTION=""

  DO_BUILD_WIN32=""
  DO_BUILD_WIN64=""

  # Kept, since they are used in various common functions.
  DO_BUILD_LINUX32=""
  DO_BUILD_LINUX64=""
  DO_BUILD_LINUX_ARM32=""
  DO_BUILD_LINUX_ARM64=""
  DO_BUILD_OSX=""

  ENV_FILE=""

  argc=$#
  declare -a argv
  argv=( "$@" )
  if [ ! -z "${DEBUG}" ]
  then
    echo ${argv[@]-}
  fi
  i=0

  # Must be declared by the caller.
  # declare -a rest


  # Identify some of the options. The rest are collected and passed
  # to the container script.
  while [ $i -lt $argc ]
  do

    arg="${argv[$i]}"
    case "${arg}" in

      clean|cleanlibs|cleanall|preload-images)
        ACTION="${arg}"
        ;;

      --win32|--windows32)
        DO_BUILD_WIN32="y"
        ;;

      --win64|--windows64)
        DO_BUILD_WIN64="y"
        ;;

      --all)
        DO_BUILD_WIN32="y"
        DO_BUILD_WIN64="y"
        ;;

      --env-file)
        ((++i))
        ENV_FILE="${argv[$i]}"
        if [ ! -f "${ENV_FILE}" ];
        then
          echo "The specified environment file \"${ENV_FILE}\" does not exist, exiting..."
          exit 1
        fi
        ;;

      # Deprecated.
      --date)
        ((++i))
        DISTRIBUTION_FILE_DATE="${argv[$i]}"
        ;;

      --help)
        echo "Usage:"
        # Some of the options are processed by the container script.
        echo "${help_message}"
        echo
        exit 1
        ;;

      *)
        # Collect all other in an array. Append to the end.
        # Will be later processed by the container script.
        set +u
        rest[${#rest[*]}]="$arg"
        set -u
        ;;

    esac
    ((++i))

  done

  DO_BUILD_ANY="${DO_BUILD_WIN64}${DO_BUILD_WIN32}"

  # The ${rest[@]} options will be passed to the inner script.
  if [ ! -z "${DEBUG}" ]
  then
    echo ${rest[@]-}
  fi
}

function host_native_options()
{
  local help_message="$1"
  shift

  ACTION=""

  DO_BUILD_WIN=""
  IS_DEBUG=""
  IS_DEVELOP=""
  WITH_STRIP="y"
  WITH_TESTS="y"
  IS_NATIVE="y"

  if [ "$(uname)" == "Linux" ]
  then
    JOBS="$(nproc)"
  elif [ "$(uname)" == "Darwin" ]
  then
    JOBS="$(sysctl hw.ncpu | sed 's/hw.ncpu: //')"
  else
    JOBS="1"
  fi

  while [ $# -gt 0 ]
  do
    case "$1" in

      clean|cleanlibs|cleanall)
        ACTION="$1"
        ;;

      --win|--windows)
        DO_BUILD_WIN="y"
        ;;

      --debug)
        IS_DEBUG="y"
        ;;

      --develop)
        IS_DEVELOP="y"
        ;;

      --jobs)
        shift
        JOBS=$1
        ;;

      --disable-strip)
        WITH_STRIP="n"
        shift
        ;;

      --disable-tests)
        WITH_TESTS="n"
        shift
        ;;

      --help)
        echo "Build a local/native ${DISTRO_UC_NAME} ${APP_NAME}."
        echo "Usage:"
        # Some of the options are processed by the container script.
        echo "${help_message}"
        echo
        exit 0
        ;;

      *)
        echo "Unknown action/option $1"
        exit 1
        ;;

    esac
    shift

  done

  if [ ${IS_DEVELOP} == "y" ]
  then
    WITH_STRIP="n"
  fi

  if [ "${DO_BUILD_WIN}" == "y" ]
  then
    if [ "${HOST_NODE_PLATFORM}" == "linux" ]
    then
      TARGET_PLATFORM="win32"
    else
      echo "Windows cross builds are available only on GNU/Linux."
      exit 1
    fi
  fi
}

function host_common()
{
  if [ -f "${script_folder_path}/VERSION" ]
  then
    # When running from the distribution folder.
    RELEASE_VERSION=${RELEASE_VERSION:-"$(cat "${script_folder_path}"/VERSION)"}
  fi

  echo
  echo "Preparing release ${RELEASE_VERSION}..."

  # -----------------------------------------------------------------------------

  common_helper_functions_script_path="${script_folder_path}/helper/common-functions-source.sh"
  echo "Common helper functions source script: \"${common_helper_functions_script_path}\"."
  source "${common_helper_functions_script_path}"

  # May override some of the helper/common definitions.
  common_functions_script_path="${script_folder_path}/common-functions-source.sh"
  if [ -f "${common_functions_script_path}" ]
  then
    echo "Common functions source script: \"${common_functions_script_path}\"."
    source "${common_functions_script_path}"
  fi

  # ---------------------------------------------------------------------------

  # The Work folder is in HOME.
  HOST_WORK_FOLDER_PATH=${WORK_FOLDER_PATH:-"${HOME}/Work"}
  if [ "${IS_NATIVE}" == "y" -a "${IS_DEVELOP}" == "y" ]
  then
    HOST_WORK_FOLDER_PATH+="/${APP_LC_NAME}-dev"
  else
    HOST_WORK_FOLDER_PATH+="/${APP_LC_NAME}-${RELEASE_VERSION}"
  fi
  CONTAINER_WORK_FOLDER_PATH="/Host${HOST_WORK_FOLDER_PATH}"

  SOURCES_FOLDER_PATH="${SOURCES_FOLDER_PATH:-"${HOST_WORK_FOLDER_PATH}/sources"}"

  do_actions

  host_prepare_cache

  CONTAINER_BUILD_SCRIPT_REL_PATH="build.git/scripts/${CONTAINER_SCRIPT_NAME}"
  echo "Container build script: \"${HOST_WORK_FOLDER_PATH}/${CONTAINER_BUILD_SCRIPT_REL_PATH}\"."

  # ---------------------------------------------------------------------------

  mkdir -pv "${HOST_WORK_FOLDER_PATH}"
  mkdir -pv "${SOURCES_FOLDER_PATH}"

  # ---------------------------------------------------------------------------

  # Set the DISTRIBUTION_FILE_DATE.
  host_get_current_date

  # ---------------------------------------------------------------------------

  host_start_timer

  host_prepare_prerequisites

  # ---------------------------------------------------------------------------

  copy_build_git
}

function host_prepare_prerequisites() 
{
  if [ "${HOST_UNAME}" == "Darwin" ]
  then
    local xbb_folder_path

    
    local must_install=""

    if [ -d "${HOME}/opt/xbb" ]
    then
      xbb_folder_path="${HOME}/opt/xbb"
    elif [ -d "${HOME}/opt/homebrew/xbb" ]
    then
      xbb_folder_path="${HOME}/opt/homebrew/xbb"
    else
      must_install="y"
    fi


    if [ ! -z "${xbb_folder_path}" ]
    then

      echo
      echo "Checking XBB in '${xbb_folder_path}'..."
      if [ ! -f "${xbb_folder_path}/xbb-source.sh" ]
      then
        must_install="y"
      fi
      
    fi

    if [ -n "${must_install}" ]
    then

      echo
      echo "Please install the macOS XBB and rerun."
      echo "https://github.com/xpack/xpack-build-box/tree/master/macos"
      
      exit 1

    fi

    if true
    then

      local tl_folder="$HOME/opt/texlive"

      must_install=""
      # Check local TeX Live.
      if [ ! -d "${tl_folder}" ]
      then
        must_install="y"
      else

        PATH="${tl_folder}/bin/x86_64-darwin:${PATH}"
        export PATH

        echo
        echo "Checking TeX Live in '${tl_folder}'..."
        set +e
        tex --version | grep 'TeX 3'
        if [ $? != 0 ]
        then
          must_install="y"
        fi
        set -e

      fi

      if [ -n "${must_install}" ]
      then

        echo
        echo "Please install TeX Live and rerun."
        echo "Alternatively restart the build script using '--without-pdf'."
        echo "https://github.com/xpack/xpack-build-box/blob/master/macos/README.md#install-tex"

        exit 1

      fi

    fi # -z "${no_pdf}"
  fi # "${HOST_UNAME}" == "Darwin"

  host_prepare_cache

  # The host script will pass to the container script
  # various environment variables.
  HOST_DEFINES_SCRIPT_PATH="${HOST_WORK_FOLDER_PATH}/build.git/scripts/host-defs-source.sh"

  DEPLOY_FOLDER_NAME=${DEPLOY_FOLDER_NAME:-"deploy"}
}

# -----------------------------------------------------------------------------

function host_prepare_docker() 
{
  echo
  echo "Checking Docker..."

  set +e
  docker --version
  if [ $? != 0 ]
  then
    echo "Please start docker daemon and rerun."
    echo "If not installed, see https://docs.docker.com/installation/."
    exit 1
  fi

  echo
  echo "Pruning Docker..."
  
  docker system prune -f
  set -e
}

# -----------------------------------------------------------------------------

function host_build_target() 
{
  message="$1"
  shift

  echo
  echo "================================================================================"
  echo "=== ${message}"

  echo
  echo "$@"

  local container_script_path=""
  local target_platform="${HOST_NODE_PLATFORM}"
  local target_arch="${HOST_NODE_ARCH}"
  local target_machine="${HOST_MACHINE}"
  local target_bits="${HOST_BITS}"
  # If the docker image is not set, it is a native build.
  local docker_image=""
  local build_binaries_path=""
  local env_file=""

  while [ $# -gt 0 ]
  do

    case "$1" in
      --script)
        container_script_path="$2"
        shift 2
        ;;

      --target-platform)
        target_platform="$2"
        shift 2
        ;;

      --target-arch)
        target_arch="$2"
        shift 2
        ;;

      --target-machine)
        target_machine="$2"
        shift 2
        ;;

      --target-bits)
        target_bits="$2"
        shift 2
        ;;

      --docker-image)
        docker_image="$2"
        shift 2
        ;;

      --env-file)
        env_file="$2"
        shift 2
        ;;

      --)
        shift
        break
        ;;

      *)
        echo "Unknown option $1, exit."
        exit 1

    esac

  done

  if [ "${target_platform}" == "sources" ]
  then
    target_arch="none"
    target_bits=""
  fi

  # The remaining "$@" options will be passed to the inner script.
  if [ -n "${DEBUG}" ]
  then
    echo "$@"
  fi

  # ---------------------------------------------------------------------------

  mkdir -pv "$(dirname "${HOST_DEFINES_SCRIPT_PATH}")"
  echo "${RELEASE_VERSION}" >"$(dirname "${HOST_DEFINES_SCRIPT_PATH}")"/VERSION

  rm -rf "${HOST_DEFINES_SCRIPT_PATH}"
  touch "${HOST_DEFINES_SCRIPT_PATH}"

  echo "RELEASE_VERSION=\"${RELEASE_VERSION}\"" >>"${HOST_DEFINES_SCRIPT_PATH}"

  echo "DISTRIBUTION_FILE_DATE=\"${DISTRIBUTION_FILE_DATE}\"" >>"${HOST_DEFINES_SCRIPT_PATH}"

  echo "TARGET_PLATFORM=\"${target_platform}\"" >>"${HOST_DEFINES_SCRIPT_PATH}"
  echo "TARGET_ARCH=\"${target_arch}\"" >>"${HOST_DEFINES_SCRIPT_PATH}"
  echo "TARGET_MACHINE=\"${target_machine}\"" >>"${HOST_DEFINES_SCRIPT_PATH}"
  echo "TARGET_BITS=\"${target_bits}\"" >>"${HOST_DEFINES_SCRIPT_PATH}"

  echo "HOST_UNAME=\"${HOST_UNAME}\"" >>"${HOST_DEFINES_SCRIPT_PATH}"

  echo "USER_ID=\"${USER_ID}\"" >>"${HOST_DEFINES_SCRIPT_PATH}"
  echo "USER_NAME=\"${USER_NAME}\"" >>"${HOST_DEFINES_SCRIPT_PATH}"
  echo "GROUP_ID=\"${GROUP_ID}\"" >>"${HOST_DEFINES_SCRIPT_PATH}"
  echo "GROUP_NAME=\"${GROUP_NAME}\"" >>"${HOST_DEFINES_SCRIPT_PATH}"

  echo "CONTAINER_RUN_AS_ROOT=\"${CONTAINER_RUN_AS_ROOT}\"" >>"${HOST_DEFINES_SCRIPT_PATH}"

  echo "HOST_WORK_FOLDER_PATH=\"${HOST_WORK_FOLDER_PATH}\"" >>"${HOST_DEFINES_SCRIPT_PATH}"
  echo "CONTAINER_WORK_FOLDER_PATH=\"${CONTAINER_WORK_FOLDER_PATH}\"" >>"${HOST_DEFINES_SCRIPT_PATH}"

  echo "HOST_CACHE_FOLDER_PATH=\"${HOST_CACHE_FOLDER_PATH}\"" >>"${HOST_DEFINES_SCRIPT_PATH}"
  echo "CONTAINER_CACHE_FOLDER_PATH=\"${CONTAINER_CACHE_FOLDER_PATH}\"" >>"${HOST_DEFINES_SCRIPT_PATH}"

  echo "DEPLOY_FOLDER_NAME=\"${DEPLOY_FOLDER_NAME}\"" >>"${HOST_DEFINES_SCRIPT_PATH}"

  if [ -z "${docker_image}" ]
  then

    host_run_native_script \
      --script "${container_script_path}" \
      --env-file "${env_file}" \
      -- \
      "$@"

  else

    host_run_docker_script \
      --script "${container_script_path}" \
      --docker-image "${docker_image}" \
      --docker-container-name "${APP_LC_NAME}-${target_platform}-${target_arch}-build" \
      --env-file "${env_file}" \
      --host-uname "${HOST_UNAME}" \
      -- \
      "$@"    

  fi

  if [ -n "${DEBUG}" ]
  then
    echo "host_build_target ${rest[@]-} completed."
  fi
}

# -----------------------------------------------------------------------------

function host_run_native_script() 
{
  local local_script=""
  local env_file=""

  while [ $# -gt 0 ]
  do

    case "$1" in

      --script)
        local_script="$2"
        shift 2
        ;;

      --env-file)
        env_file="$2"
        shift 2
        ;;

      --)
        shift
        break
        ;;

      *)
        echo "Unknown option $1, exit."
        exit 1

    esac

  done

  # The remaining $@ options will be passed to the inner script.

  echo
  echo "Running script \"$(basename "${local_script}")\" natively..."

  # Run the inner script in a local sub-shell, possibly with the 
  # custom environment.
  (
    if [ -n "${env_file}" -a -f "${env_file}" ]
    then
      source "${env_file}"
    fi
    /bin/bash ${DEBUG} "${local_script}" "$@"
  )
}

# -----------------------------------------------------------------------------

function host_run_docker_script() 
{
  local docker_script=""
  local docker_image=""
  local docker_container_name=""
  local host_uname=""
  local env_file=""
  local opt_env_file=

  while [ $# -gt 0 ]
  do

    case "$1" in

      --script)
        docker_script="$2"
        shift 2
        ;;

      --docker-image)
        docker_image="$2"
        shift 2
        ;;

      --docker-container-name)
        docker_container_name="$2"
        shift 2
        ;;

      --host-uname)
        host_uname="$2"
        shift 2
        ;;

      --env-file)
        env_file="$2"
        shift 2
        ;;

      --)
        shift
        break
        ;;

      *)
        echo "Unknown option $1, exit."
        exit 1

    esac

  done

  set +e
  # Remove a possible previously crashed container.
  docker rm --force "${docker_container_name}" > /dev/null 2> /dev/null
  set -e

  echo
  echo "Running script \"$(basename "${docker_script}")\" inside docker image \"${docker_image}\"..."


  local env_file_option=""
  # Run the inner script in a fresh Docker container.
  if [ -n "${env_file}" -a -f "${env_file}" ]
  then
    env_file_option="--env-file=\"${env_file}\""
  fi

  if [ "${HOST_UNAME}" == "Darwin" -o "${CONTAINER_RUN_AS_ROOT}" == "y" ]
  then

    docker run \
      --name="${docker_container_name}" \
      --tty \
      --hostname "docker" \
      --workdir="/root" \
      --volume="${HOST_WORK_FOLDER_PATH}/:${CONTAINER_WORK_FOLDER_PATH}" \
      --volume="${HOST_CACHE_FOLDER_PATH}/:${CONTAINER_CACHE_FOLDER_PATH}" \
      ${env_file_option} \
      "${docker_image}" \
      /bin/bash ${DEBUG} "${docker_script}" "$@"

  else

    # This is a bit tricky, since it needs to do multiple actions in
    # one go: add a new user and run the script with that user credentials,
    # including passing the extra args (in the middle of the string).
    #
    # From the [bash manual](https://www.gnu.org/software/bash/manual/bash.html):
    # ($*) Expands to the positional parameters, starting from one. 
    # When the expansion is not within double quotes, each positional 
    # parameter expands to a separate word. In contexts where it is 
    # performed, those words are subject to further word splitting and 
    # pathname expansion. When the expansion occurs within double quotes, 
    # it expands to a single word with the value of each parameter separated 
    # by the first character of the IFS special variable. That is, "$*" 
    # is equivalent to "$1c$2c…", where c is the first character of the 
    # value of the IFS variable. If IFS is unset, the parameters are 
    # separated by spaces. If IFS is null, the parameters are joined 
    # without intervening separators.
    local ifs="${IFS}"
    IFS=" "
    # Without -m, wine fails to create .wine.
    local cmd_string="groupadd -g ${GROUP_ID} ${GROUP_NAME} && useradd -m -u ${USER_ID} -g ${GROUP_ID} ${USER_NAME} && su -c \"DEBUG=${DEBUG} bash ${docker_script} $*\" ${USER_NAME}"
    IFS="${ifs}"
 
    docker run \
      --name="${docker_container_name}" \
      --tty \
      --hostname "docker" \
      --workdir="/root" \
      --volume="${HOST_WORK_FOLDER_PATH}/:${CONTAINER_WORK_FOLDER_PATH}" \
      --volume="${HOST_CACHE_FOLDER_PATH}/:${CONTAINER_CACHE_FOLDER_PATH}" \
      ${env_file_option} \
      "${docker_image}" \
      /bin/bash ${DEBUG} -c "${cmd_string}"

  fi

  # Remove the container.
  echo "Docker container \"$(docker rm --force "${docker_container_name}")\" removed."
}

# -----------------------------------------------------------------------------

function host_build_all() {

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
      linux_install_relative_path="linux-x64/install"

      host_build_target "Creating the Windows 64-bit distribution..." \
        --script "${CONTAINER_WORK_FOLDER_PATH}/${CONTAINER_BUILD_SCRIPT_REL_PATH}" \
        --env-file "${ENV_FILE}" \
        --target-platform "win32" \
        --target-arch "x64" \
        --target-machine "x86_64" \
        --target-bits 64 \
        --docker-image "${docker_linux64_image}" \
        -- \
        --linux-install-relative-path "${linux_install_relative_path}" \
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
      linux_install_relative_path="linux-x32/install"

      host_build_target "Creating the Windows 32-bit distribution..." \
        --script "${CONTAINER_WORK_FOLDER_PATH}/${CONTAINER_BUILD_SCRIPT_REL_PATH}" \
        --env-file "${ENV_FILE}" \
        --target-platform "win32" \
        --target-arch "x32" \
        --target-machine "i386" \
        --target-bits 32 \
        --docker-image "${docker_linux32_image}" \
        -- \
        --linux-install-relative-path "${linux_install_relative_path}" \
        ${rest[@]-}
    fi

    # ----- Build the GNU/Linux Arm 64-bit distribution. ---------------------------

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

    # ----- Build the GNU/Linux Arm 32-bit distribution. ---------------------------

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
}

# -----------------------------------------------------------------------------

function host_show_sha() {

  if [ -d "${HOST_WORK_FOLDER_PATH}/${DEPLOY_FOLDER_NAME}" ]
  then
    echo
    echo "${HOST_WORK_FOLDER_PATH}/${DEPLOY_FOLDER_NAME}"
    ls -l "${HOST_WORK_FOLDER_PATH}/${DEPLOY_FOLDER_NAME}"
    echo
    echo "SHA signatures..."
    set +e
    cat "${HOST_WORK_FOLDER_PATH}/${DEPLOY_FOLDER_NAME}"/*.sha
    set -e
  fi
}

# -----------------------------------------------------------------------------
