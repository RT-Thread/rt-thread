# The xPack OpenOCD

This is the **xPack** version of **OpenOCD** (formerly part of the
GNU MCU Eclipse project).

For details, see
[The xPack OpenOCD](https://xpack.github.io/openocd/) pages.

## Compliance

The xPack OpenOCD generally follows the official
[OpenOCD](http://openocd.org) releases.

The current version is based on:

- OpenOCD version 0.10.0, the development commit
[263deb380](https://github.com/xpack-dev-tools/openocd/commit/263deb3802a515ba8155b6c59146f0f539de4e43)
from 7 July 2019

## Changes

Compared to the master branch, the following changes were applied:

- a configure option was added to configure branding (`--enable-branding`)
- the src/openocd.c file was edited to display the branding string
- the contrib/60-openocd.rules file was simplified to avoid protection related issues.

## Build

The scripts used to build this distribution are in:

- `distro-info/scripts`

For the prerequisites and more details on the build procedure, please see the
[How to build?](https://github.com/xpack-dev-tools/openocd-xpack/blob/xpack/README-BUILD.md) page.

## Documentation

The original documentation is available in the `share/doc` folder.

## More info

For more info and support, please see the xPack project pages from:

  http://xpack.github.io/dev-tools/openocd

Thank you for using open source software,

Liviu Ionescu
