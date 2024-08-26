#!/bin/bash

#
# Copyright (c) 2024, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#
# Change Logs:
# Date           Author       Notes
# 2024-08-27     Supperthomas the first version
#

#这个脚本用于安装RT-Thread开发环境 请确保网络畅通

# 设置环境变量 如果希望生效请在当前shell中执行source install.sh

export RTT_ROOT=$(pwd)
export RTT_CC=gcc

echo "RTT_ROOT is set to: $RTT_ROOT"

# 检测操作系统类型和发行版
detect_os() {
    if command -v uname >/dev/null 2>&1; then
        OS=$(uname -s)
    else
        if [ -f "/etc/os-release" ]; then
            OS="Linux"
        elif [ -f "/System/Library/CoreServices/SystemVersion.plist" ]; then
            OS="macOS"
        elif [[ -d "/mnt/c/Windows" || -d "/c/Windows" ]]; then
            OS="WSL"
        else
            OS="UNKNOWN"
        fi
    fi

    if [ "$OS" == "Linux" ]; then
        if [ -f /etc/os-release ]; then
            . /etc/os-release
            DISTRO=$ID
            VERSION=$VERSION_ID
        elif [ -f /etc/lsb-release ]; then
            . /etc/lsb-release
            DISTRO=$DISTRIB_ID
            VERSION=$DISTRIB_RELEASE
        else
            DISTRO="UNKNOWN"
            VERSION="UNKNOWN"
        fi
    fi

    echo "Detected Operating System: $OS, Distribution: $DISTRO, Version: $VERSION"
}

# 安装函数
install_on_ubuntu() {
    echo "Installing on Debian/Ubuntu..."
    wget https://raw.githubusercontent.com/RT-Thread/env/master/install_ubuntu.sh
    chmod 777 install_ubuntu.sh
    ./install_ubuntu.sh
}

install_on_fedora() {
    echo "Installing on Fedora..."

}

install_on_centos() {
    echo "Installing on CentOS/RHEL..."
}

install_on_arch() {
    echo "Installing on Arch Linux..."
}

install_on_macos() {
    echo "Installing on macOS..."
    wget https://raw.githubusercontent.com/RT-Thread/env/master/install_macos.sh
    chmod 777 install_macos.sh
    ./install_macos.sh
}

install_on_wsl() {
    echo "Installing on Windows Subsystem for Linux (WSL)..."
}

install_on_windows() {
    echo "Installing on Windows using PowerShell..."
    wget https://raw.githubusercontent.com/RT-Thread/env/master/install_windows.ps1
    chmod 777 install_windows.ps1
    ./install_windows.ps1
}

install_on_opensuse() {
    echo "Installing on openSUSE..."
    wget https://raw.githubusercontent.com/RT-Thread/env/master/install_suse.sh
    chmod 777 install_suse.sh
    ./install_suse.sh
}
# 主函数
main() {
    detect_os
    case "$OS" in
        Linux)
            case "$DISTRO" in
                ubuntu|debian)
                    install_on_ubuntu
                    ;;
                fedora)
                    install_on_fedora
                    ;;
                centos|rhel)
                    install_on_centos
                    ;;
                arch)
                    install_on_arch
                    ;;
                *)
                    echo "Unsupported Linux distribution: $DISTRO"
                    exit 1
                    ;;
            esac
            ;;
        macOS)
            install_on_macos
            ;;
        WSL)
            install_on_wsl
            ;;
        Windows)
            install_on_windows
            ;;
        *)
            echo "Unsupported Operating System: $OS"
            exit 1
            ;;
    esac
    echo "Installation completed!"
}

# 执行主函数
main
