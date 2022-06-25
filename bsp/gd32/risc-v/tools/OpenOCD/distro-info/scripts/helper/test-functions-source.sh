# -----------------------------------------------------------------------------
# This file is part of the xPack distribution.
#   (https://xpack.github.io)
# Copyright (c) 2020 Liviu Ionescu.
#
# Permission to use, copy, modify, and/or distribute this software 
# for any purpose is hereby granted, under the terms of the MIT license.
# -----------------------------------------------------------------------------

# Helper script used in the tests.

# -----------------------------------------------------------------------------

# https://github.com/docker-library/official-images#architectures-other-than-amd64
# - https://hub.docker.com/_/ubuntu
# - https://hub.docker.com/r/i386/ubuntu/
# - https://hub.docker.com/r/arm32v7/ubuntu
# - https://hub.docker.com/_/debian
# - https://hub.docker.com/r/i386/debian
# - https://hub.docker.com/r/arm32v7/debian
# - https://hub.docker.com/_/centos
# - https://hub.docker.com/r/i386/centos
# - https://hub.docker.com/r/opensuse/tumbleweed
# - https://hub.docker.com/_/fedora
# - https://hub.docker.com/_/archlinux
# - https://hub.docker.com/u/manjarolinux
# - https://hub.docker.com/r/gentoo/portage

# "i386/ubuntu:20.04" # Fails to install prerequisites
# "i386/ubuntu:12.04" --skip-gdb-py # Not available
# "i386/centos:8" # not available

# arm32v7/fedora:29 - Error: Failed to synchronize cache for repo 'fedora-modular'
# arm32v7/fedora:27 - Error: Failed to synchronize cache for repo 'fedora-modular'
# arm32v7/fedora:25 - KeyError: 'armv8l'

# Debian versions: 
# - 8 jessie
# - 9 stretch
# - 10 buster

function create_stable_data_file()
{
  local message="$1"
  local branch="$2"
  local base_url="$3"
  local data_file_path="$4"

# Note: __EOF__ is NOT quoted to allow substitutions.
cat <<__EOF__ > "${data_file_path}"
{
  "request": {
    "message": "${message}",
    "branch": "${branch}",
    "config": {
      "merge_mode": "replace",
      "jobs": [
        {
          "name": "Ubuntu 12, 14, 16, 18, 20 (Intel 64-bit)",
          "os": "linux",
          "arch": "amd64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh ubuntu:20.04 ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh ubuntu:18.04 ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh ubuntu:16.04 ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh ubuntu:14.04 ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh ubuntu:12.04 ${base_url} "
          ]
        },
        {
          "name": "Ubuntu 14, 16, 18 (Intel 32-bit)",
          "os": "linux",
          "arch": "amd64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 i386/ubuntu:18.04 ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 i386/ubuntu:16.04 ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 i386/ubuntu:14.04 ${base_url} "
          ]
        },
        {
          "name": "Ubuntu 16, 18, 20 (Arm 64-bit)",
          "os": "linux",
          "arch": "arm64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh ubuntu:20.04 ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh ubuntu:18.04 ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh ubuntu:16.04 ${base_url} "
          ]
        },
        {
          "name": "Ubuntu 16, 18 (Arm 32-bit)",
          "os": "linux",
          "arch": "arm64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 arm32v7/ubuntu:18.04 ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 arm32v7/ubuntu:16.04 ${base_url} "
          ]
        },
        {
          "name": "Debian 8, 9, 10 (Intel 64-bit)",
          "os": "linux",
          "arch": "amd64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh debian:buster ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh debian:stretch ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh debian:jessie ${base_url} "
          ]
        },
        {
          "name": "Debian 8, 9, 10 (Intel 32-bit)",
          "os": "linux",
          "arch": "amd64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 i386/debian:buster ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 i386/debian:stretch ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 i386/debian:jessie ${base_url} "
          ]
        },
        {
          "name": "Debian 9, 10 (Arm 64-bit)",
          "os": "linux",
          "arch": "arm64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh debian:buster ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh debian:stretch ${base_url} "
          ]
        },
        {
          "name": "Debian 9, 10 (Arm 32-bit)",
          "os": "linux",
          "arch": "arm64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 arm32v7/debian:buster ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 arm32v7/debian:stretch ${base_url} "
          ]
        },
        {
          "name": "CentOS 7, 8 (Intel 64-bit)",
          "os": "linux",
          "arch": "amd64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh centos:8 ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh centos:7 ${base_url} "
          ]
        },
        {
          "name": "CentOS 7 (Intel 32-bit)",
          "os": "linux",
          "arch": "amd64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 i386/centos:7 ${base_url} "
          ]
        },
        {
          "name": "CentOS 7, 8 (Arm 64-bit)",
          "os": "linux",
          "arch": "arm64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh centos:8 ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh centos:7 ${base_url} "
          ]
        },
        {
          "name": "OpenSUSE 13, 15 (Intel 64-bit)",
          "os": "linux",
          "arch": "amd64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh opensuse/leap:15 ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh opensuse/amd64:13.2 ${base_url} "
          ]
        },
        {
          "name": "OpenSUSE 15 (Arm 64-bit)",
          "os": "linux",
          "arch": "arm64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh opensuse/leap:15 ${base_url} "
          ]
        },
        {
          "name": "Fedora 20, 25, 27, 29, 31 (Intel 64-bit)",
          "os": "linux",
          "arch": "amd64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh fedora:31 ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh fedora:29 ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh fedora:27 ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh fedora:25 ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh fedora:20 ${base_url} "
          ]
        },
        {
          "name": "Fedora 27, 29, 31 (Arm 64-bit)",
          "os": "linux",
          "arch": "arm64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh fedora:31 ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh fedora:29 ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh fedora:27 ${base_url} "
          ]
        },
        {
          "name": "Raspbian 8, 9 (Arm 32-bit)",
          "os": "linux",
          "arch": "arm64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 raspbian/stretch ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 raspbian/jessie ${base_url} "
          ]
        },
        {
          "name": "macOS 10.15 Intel",
          "os": "osx",
          "arch": "amd64",
          "osx_image": "xcode11.5",
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/native-test.sh ${base_url}" 
          ]
        },
        {
          "name": "macOS 10.14 Intel",
          "os": "osx",
          "arch": "amd64",
          "osx_image": "xcode11.3",
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/native-test.sh ${base_url}" 
          ]
        },
        {
          "name": "macOS 10.13 Intel",
          "os": "osx",
          "arch": "amd64",
          "osx_image": "xcode10.1",
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/native-test.sh ${base_url}" 
          ]
        },
        {
          "name": "macOS 10.12 Intel",
          "os": "osx",
          "arch": "amd64",
          "osx_image": "xcode9.2",
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/native-test.sh ${base_url}" 
          ]
        },
        {
          "name": "macOS 10.11 Intel",
          "os": "osx",
          "arch": "amd64",
          "osx_image": "xcode8",
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/native-test.sh ${base_url}" 
          ]
        },
        {
          "name": "macOS 10.10 Intel",
          "os": "osx",
          "arch": "amd64",
          "osx_image": "xcode6.4",
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/native-test.sh ${base_url}" 
          ]
        },
        {
          "name": "Windows 10 (Intel 64-bit)",
          "os": "windows",
          "arch": "amd64",
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/native-test.sh ${base_url} " 
          ]
        },
        {
          "name": "Windows 10 (Intel 32-bit)",
          "os": "windows",
          "arch": "amd64",
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/native-test.sh --32 ${base_url} " 
          ]
        }
      ],
      "notifications": {
        "email": {
          "on_success": "always",
          "on_failure": "always"
        }
      }
    }
  }
}
__EOF__

}

function create_latest_data_file()
{
  local message="$1"
  local branch="$2"
  local base_url="$3"
  local data_file_path="$4"

# Note: __EOF__ is NOT quoted to allow substitutions.
cat <<__EOF__ > "${data_file_path}"
{
  "request": {
    "message": "${message}",
    "branch": "${branch}",
    "config": {
      "merge_mode": "replace",
      "jobs": [
        {
          "name": "Ubuntu rolling, latest (Intel 64-bit)",
          "os": "linux",
          "arch": "amd64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh ubuntu:latest ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh ubuntu:rolling ${base_url} "
          ]
        },
        {
          "name": "Ubuntu rolling, latest (Intel 32-bit)",
          "os": "linux",
          "arch": "amd64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 i386/ubuntu:latest ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 i386/ubuntu:rolling ${base_url} "
          ]
        },
        {
          "name": "Ubuntu rolling, latest (Arm 64-bit)",
          "os": "linux",
          "arch": "arm64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh ubuntu:latest ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh ubuntu:rolling ${base_url} "
          ]
        },
        {
          "name": "Ubuntu rolling, latest (Arm 32-bit)",
          "os": "linux",
          "arch": "arm64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 arm32v7/ubuntu:latest ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 arm32v7/ubuntu:rolling ${base_url} "
          ]
        },
        {
          "name": "Debian latest, testing (Intel 64-bit)",
          "os": "linux",
          "arch": "amd64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh debian:testing ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh debian:latest ${base_url} "
          ]
        },
        {
          "name": "Debian testing (Intel 32-bit)",
          "os": "linux",
          "arch": "amd64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 i386/debian:testing ${base_url} "
          ]
        },
        {
          "name": "Debian latest, testing (Arm 64-bit)",
          "os": "linux",
          "arch": "arm64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh debian:testing ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh debian:latest ${base_url} "
          ]
        },
        {
          "name": "Debian testing (Arm 32-bit)",
          "os": "linux",
          "arch": "arm64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 arm32v7/debian:testing ${base_url} "
          ]
        },
        {
          "name": "CentOS latest (Intel 64-bit)",
          "os": "linux",
          "arch": "amd64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh centos:latest ${base_url} "
          ]
        },
        {
          "name": "CentOS latest (Intel 32-bit)",
          "os": "linux",
          "arch": "amd64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 i386/centos:latest ${base_url} "
          ]
        },
        {
          "name": "CentOS latest (Arm 64-bit)",
          "os": "linux",
          "arch": "arm64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh centos:latest ${base_url} "
          ]
        },
        {
          "name": "OpenSUSE tumbleweed (Intel 64-bit)",
          "os": "linux",
          "arch": "amd64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh opensuse/tumbleweed ${base_url} "
          ]
        },
        {
          "name": "OpenSUSE tumbleweed (Arm 64-bit)",
          "os": "linux",
          "arch": "arm64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh opensuse/tumbleweed ${base_url} "
          ]
        },
        {
          "name": "Fedora latest, rawhide (Intel 64-bit)",
          "os": "linux",
          "arch": "amd64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh fedora:rawhide ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh fedora:latest ${base_url} "
          ]
        },
        {
          "name": "Fedora latest, rawhide (Arm 64-bit)",
          "os": "linux",
          "arch": "arm64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh fedora:rawhide ${base_url} ",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh fedora:latest ${base_url} "
          ]
        },
        {
          "name": "Arch latest (Intel 64-bit)",
          "os": "linux",
          "arch": "amd64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh archlinux:latest ${base_url} "
          ]
        },
        {
          "name": "Manjaro base (Intel 64-bit)",
          "os": "linux",
          "arch": "amd64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh manjarolinux/base ${base_url} "
          ]
        },
        {}
      ],
      "notifications": {
        "email": {
          "on_success": "always",
          "on_failure": "always"
        }
      }
    }
  }
}
__EOF__

}

function create_macos_data_file()
{
  local message="$1"
  local branch="$2"
  local base_url="$3"
  local data_file_path="$4"

# Note: __EOF__ is NOT quoted to allow substitutions.
cat <<__EOF__ > "${data_file_path}"
{
  "request": {
    "message": "${message}",
    "branch": "${branch}",
    "config": {
      "merge_mode": "replace",
      "jobs": [
        {
          "name": "macOS 10.15 Intel",
          "os": "osx",
          "arch": "amd64",
          "osx_image": "xcode11.5",
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/native-test.sh ${base_url}" 
          ]
        },
        {
          "name": "macOS 10.14 Intel",
          "os": "osx",
          "arch": "amd64",
          "osx_image": "xcode11.3",
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/native-test.sh ${base_url}" 
          ]
        },
        {
          "name": "macOS 10.13 Intel",
          "os": "osx",
          "arch": "amd64",
          "osx_image": "xcode10.1",
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/native-test.sh ${base_url}" 
          ]
        },
        {
          "name": "macOS 10.12 Intel",
          "os": "osx",
          "arch": "amd64",
          "osx_image": "xcode9.2",
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/native-test.sh ${base_url}" 
          ]
        },
        {
          "name": "macOS 10.11 Intel",
          "os": "osx",
          "arch": "amd64",
          "osx_image": "xcode8",
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/native-test.sh ${base_url}" 
          ]
        },
        {
          "name": "macOS 10.10 Intel",
          "os": "osx",
          "arch": "amd64",
          "osx_image": "xcode6.4",
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/native-test.sh ${base_url}" 
          ]
        }
      ],
      "notifications": {
        "email": {
          "on_success": "always",
          "on_failure": "always"
        }
      }
    }
  }
}
__EOF__

}

function create_windows_data_file()
{
  local message="$1"
  local branch="$2"
  local base_url="$3"
  local data_file_path="$4"

# Note: __EOF__ is NOT quoted to allow substitutions.
cat <<__EOF__ > "${data_file_path}"
{
  "request": {
    "message": "${message}",
    "branch": "${branch}",
    "config": {
      "merge_mode": "replace",
      "jobs": [
        {
          "name": "Windows 10 (Intel 64-bit)",
          "os": "windows",
          "arch": "amd64",
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/native-test.sh ${base_url} " 
          ]
        },
        {
          "name": "Windows 10 (Intel 32-bit)",
          "os": "windows",
          "arch": "amd64",
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/native-test.sh --32 ${base_url} " 
          ]
        }
      ],
      "notifications": {
        "email": {
          "on_success": "always",
          "on_failure": "always"
        }
      }
    }
  }
}
__EOF__

}


function create_quick_data_file()
{
  local message="$1"
  local branch="$2"
  local base_url="$3"
  local data_file_path="$4"

# Note: __EOF__ is NOT quoted to allow substitutions.
cat <<__EOF__ > "${data_file_path}"
{
  "request": {
    "message": "${message}",
    "branch": "${branch}",
    "config": {
      "merge_mode": "replace",
      "jobs": [
        {
          "name": "Debian 10 (Intel 64-bit)",
          "os": "linux",
          "arch": "amd64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh debian:buster ${base_url} "
          ]
        },
        {
          "name": "Debian 10 (Intel 32-bit)",
          "os": "linux",
          "arch": "amd64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 i386/debian:buster ${base_url} "
          ]
        },
        {
          "name": "Debian 10 (Arm 64-bit)",
          "os": "linux",
          "arch": "arm64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh debian:buster ${base_url} "
          ]
        },
        {
          "name": "Debian 10 (Arm 32-bit)",
          "os": "linux",
          "arch": "arm64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 arm32v7/debian:buster ${base_url} "
          ]
        },
        {
          "name": "macOS 10.15 Intel",
          "os": "osx",
          "arch": "amd64",
          "osx_image": "xcode11.5",
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/native-test.sh ${base_url}" 
          ]
        },
        {
          "name": "Windows 10 (Intel 64-bit)",
          "os": "windows",
          "arch": "amd64",
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/native-test.sh ${base_url} " 
          ]
        },
        {
          "name": "Windows 10 (Intel 32-bit)",
          "os": "windows",
          "arch": "amd64",
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/native-test.sh --32 ${base_url} " 
          ]
        }
      ],
      "notifications": {
        "email": {
          "on_success": "always",
          "on_failure": "always"
        }
      }
    }
  }
}
__EOF__

}


function create_xpm_install_data_file()
{
  local message="$1"
  local branch="$2"
  local data_file_path="$3"

# Note: __EOF__ is NOT quoted to allow substitutions.
cat <<__EOF__ > "${data_file_path}"
{
  "request": {
    "message": "${message}",
    "branch": "${branch}",
    "config": {
      "merge_mode": "replace",
      "_jobs": [
        {
          "name": "Ubuntu 18 (Intel 32-bit)",
          "os": "linux",
          "arch": "amd64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 --script container-xpm-install-test.sh i386/ubuntu:18.04 "
          ]
        },
        {
          "name": "Ubuntu 18 (Arm 32-bit)",
          "os": "linux",
          "arch": "arm64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --32 --script container-xpm-install-test.sh arm32v7/ubuntu:18.04 "
          ]
        }
      ],
      "jobs": [
        {
          "name": "Ubuntu 18 (Intel 64-bit)",
          "os": "linux",
          "arch": "amd64",
          "dist": "bionic",
          "language": "node_js",
          "before_script": [
            "nvm install --lts node",
            "nvm use --lts node",
            "nvm install-latest-npm",
            "npm install --global xpm@latest"
          ],
          "script": [
            "env | sort",
            "pwd",
            "xpm install --global ${npm_package}"
          ]
        },
        {
          "name": "Ubuntu 18 (Arm 64-bit)",
          "os": "linux",
          "arch": "arm64",
          "dist": "bionic",
          "services": [ "docker" ],
          "language": "minimal",
          "script": [
            "env | sort",
            "pwd",
            "DEBUG=${DEBUG} bash tests/scripts/docker-test.sh --script container-xpm-install-test.sh ubuntu:18.04 "
          ]
        },
        {
          "name": "macOS 10.15 Intel",
          "os": "osx",
          "arch": "amd64",
          "osx_image": "xcode11.5",
          "language": "node_js",
          "before_script": [
            "nvm install --lts node",
            "nvm use --lts node",
            "nvm install-latest-npm",
            "npm install --global xpm@latest"
          ],
          "script": [
            "env | sort",
            "pwd",
            "xpm install --global ${npm_package}"
          ]
        },
        {
          "name": "Windows 10 (Intel 64-bit)",
          "os": "windows",
          "arch": "amd64",
          "language": "node_js",
          "node_js": "lts/*",
          "before_script": [
            "npm install --global xpm@latest"
          ],
          "script": [
            "env | sort",
            "pwd",
            "xpm install --global ${npm_package}"
          ]
        }
      ],
      "notifications": {
        "email": {
          "on_success": "always",
          "on_failure": "always"
        }
      }
    }
  }
}
__EOF__

}


# data_file_path
# github_org
# github_repo
function trigger_travis()
{
  local github_org="$1"
  local github_repo="$2"
  local data_file_path="$3"

  curl -v -X POST \
   -H "Content-Type: application/json" \
   -H "Accept: application/json" \
   -H "Travis-API-Version: 3" \
   -H "Authorization: token ${TRAVIS_ORG_TOKEN}" \
   --data-binary @"${data_file_path}" \
   https://api.travis-ci.org/repo/${github_org}%2F${github_repo}/requests
}

# -----------------------------------------------------------------------------

# Runs inside a container.
# Set the following variables:
#
# - node_platform={win32,linux,darwin}
# - node_architecture={x64,x32,arm64,arm}
# - bits={32,64}

function detect_architecture()
{
  uname -a

  uname_platform=$(uname -s | tr '[:upper:]' '[:lower:]')
  uname_machine=$(uname -m | tr '[:upper:]' '[:lower:]')

  node_platform="${uname_platform}"
  # Travis uses Msys2; git for Windows uses mingw-w64.
  if [[ "${uname_platform}" == msys_nt* ]] \
  || [[ "${uname_platform}" == mingw64_nt* ]] \
  || [[ "${uname_platform}" == mingw32_nt* ]]
  then
    node_platform="win32"
  fi

  node_architecture=""
  bits=""
  if [ "${uname_machine}" == "x86_64" ]
  then
    node_architecture="x64"
    bits="64"
  elif [ "${uname_machine}" == "i386" -o "${uname_machine}" == "i586" -o "${uname_machine}" == "i686" ]
  then
    node_architecture="x32"
    bits="32"
  elif [ "${uname_machine}" == "aarch64" ]
  then
    node_architecture="arm64"
    bits="64"
  elif [ "${uname_machine}" == "armv7l" -o "${uname_machine}" == "armv8l" ]
  then
    node_architecture="arm"
    bits="32"
  else
    echo "${uname_machine} not supported"
    exit 1
  fi
}

function prepare_env() 
{
  container_work_folder_path="/Host/Work"
  container_repo_folder_path="/Host/repo"

  if [ -f "/.dockerenv" -a -d "${container_work_folder_path}" ]
  then
    work_folder_path="${container_work_folder_path}"
    repo_folder_path="${container_repo_folder_path}"
  else
    work_folder_path="${HOME}/Work"
    # On the host, it must be called using the script folder path.
    repo_folder_path="$1"
  fi

  cache_folder_path="${work_folder_path}/cache"

  # Extract only the first line
  version="$(cat ${repo_folder_path}/scripts/VERSION | sed -e '2,$d')"
  if [ -z "${version}" ]
  then
    echo "Check the version, it cannot be empty."
    exit 1
  fi

  # Always in the user home, even when inside a container.
  test_folder_path="${HOME}/tmp/test-${app_lc_name}"
}

# -----------------------------------------------------------------------------

# Requires base_url and lots of other variables.
function install_archive()
{
  local archive_extension
  local archive_architecture="${node_architecture}"
  if [ "${node_platform}" == "win32" ]
  then
    archive_extension="zip"
    if [ "${force_32_bit}" == "y" ]
    then
      archive_architecture="x32"
    fi
  else
    archive_extension="tar.gz"
  fi
  archive_name="xpack-${app_lc_name}-${version}-${node_platform}-${archive_architecture}.${archive_extension}"
  archive_folder_name="xpack-${app_lc_name}-${version}"

  mkdir -pv "${cache_folder_path}"

  if [ ! -f "${cache_folder_path}/${archive_name}" ]
  then
    echo
    echo "Downloading ${archive_name}..."
    curl -L --fail -o "${cache_folder_path}/${archive_name}" \
      "${base_url}/${archive_name}"
    echo
  fi

  app_folder_path="${test_folder_path}/${archive_folder_name}"

  rm -rf "${app_folder_path}"

  mkdir -pv "${test_folder_path}"
  cd "${test_folder_path}"

  echo
  echo "Extracting ${archive_name}..."
  if [[ "${archive_name}" == *.zip ]]
  then
    unzip -q "${cache_folder_path}/${archive_name}"
  else 
    tar xf "${cache_folder_path}/${archive_name}"
  fi

  echo ls -lL "${app_folder_path}"
  ls -lL "${app_folder_path}"
}

# -----------------------------------------------------------------------------

function install_xpm()
{
  curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/master/install.sh | bash
  
  export NVM_DIR="${HOME}/.nvm"
  [ -s "${NVM_DIR}/nvm.sh" ] && \. "${NVM_DIR}/nvm.sh"  # This loads nvm
  [ -s "${NVM_DIR}/bash_completion" ] && \. "${NVM_DIR}/bash_completion"  # This loads nvm bash_completion

  nvm install --lts node
  nvm use --lts node

  nvm install-latest-npm

  npm install --global xpm@latest
}

# -----------------------------------------------------------------------------

# $1 = image name
# $2 = base URL
function docker_run_test() {

  local script_name
  if [ $# -gt 0 -a "$1" == "--script" ]
  then
    script_name="$2"
    shift
    shift
  else
    script_name="container-test.sh"
  fi

  local image_name="$1"
  shift

  (
    prefix32="${prefix32:-""}"

    # For --security-opt see:
    # https://github.com/tianon/docker-brew-ubuntu-core/issues/183

    docker run \
      --tty \
      --security-opt seccomp:unconfined \
      --hostname "docker" \
      --workdir="/root" \
      --env DEBUG=${DEBUG} \
      --volume "${work_folder_path}:${container_work_folder_path}" \
      --volume "${repo_folder_path}:${container_repo_folder_path}" \
      "${image_name}" \
      ${prefix32} /bin/bash "${container_repo_folder_path}/tests/scripts/${script_name}" \
        "${image_name}" \
        "$@"
  )
}

function docker_run_test_32() {
  (
    prefix32="linux32"

    docker_run_test "$@"
  )
}

# -----------------------------------------------------------------------------

function show_libs()
{
  # Does not include the .exe extension.
  local app_path=$1
  shift
  if [ "${node_platform}" == "win32" ]
  then
    app_path+='.exe'
  fi

  if [ "${node_platform}" == "linux" ]
  then
    echo
    echo "readelf -d ${app_path} | egrep -i ..."
    readelf -d "${app_path}" | egrep -i '(SONAME)' || true
    readelf -d "${app_path}" | egrep -i '(RUNPATH|RPATH)' || true
    readelf -d "${app_path}" | egrep -i '(NEEDED)' || true
    echo
    echo "ldd -v ${app_path}"
    ldd -v "${app_path}" 2>&1 || true
  elif [ "${node_platform}" == "darwin" ]
  then
    echo
    echo "otool -L ${app_path}"
    otool -L "${app_path}"
  fi
}

function run_verbose()
{
  echo
  echo "$@"
  "$@" 2>&1
}

function run_app()
{
  local app_path=$1
  shift
  if [ "${node_platform}" == "win32" ]
  then
    app_path+='.exe'
  fi

  echo
  echo "${app_path} $@"
  "${app_path}" "$@" 2>&1
}

function run_app_silent()
{
  local app_path=$1
  shift
  if [ "${node_platform}" == "win32" ]
  then
    app_path+='.exe'
  fi

  "${app_path}" "$@" 2>&1
}

function do_run()
{
  local app_path=$1
  shift

  echo
  echo "${app_path} $@"
  "${app_path}" "$@" 2>&1
}

function do_expect()
{
  local app_name="$1"
  local expected="$2"

  show_libs "${app_name}"

  local output="$(run_app_silent "./${app_name}")"

  if [ "x${output}x" == "x${expected}x" ]
  then
    echo "Test ${app_name} ok"
  else
    exit 1
  fi
}

function good_bye()
{
  echo
  echo "All tests completed successfully."

  do_run uname -a
  if [ "${node_platform}" == "linux" ]
  then
    do_run lsb_release -a
    do_run ldd --version
  elif [ "${node_platform}" == "darwin" ]
  then
    do_run sw_vers
  fi
}

# -----------------------------------------------------------------------------
