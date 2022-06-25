#!/usr/bin/env bash
rm -rf "${HOME}/Downloads/openocd-xpack.git"
git clone --recurse-submodules https://github.com/xpack-dev-tools/openocd-xpack.git "${HOME}/Downloads/openocd-xpack.git"
