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
[e5be992df](https://github.com/xpack-dev-tools/openocd/commit/e5be992df1a893e2e865419a02a564d5f9ccd9dd)
from June 23, 2020.

## Changes

Compared to the upstream master branch, the following changes were applied:

- a configure option was added to configure branding (`--enable-branding`)
- the src/openocd.c file was edited to display the branding string
- the contrib/60-openocd.rules file was simplified to avoid protection related issues.

## Build

The scripts used to build this distribution are in:

- `distro-info/scripts`

For the prerequisites and more details on the build procedure, please see the
[How to build](https://github.com/xpack-dev-tools/openocd-xpack/blob/xpack/README-BUILD.md) page.

## Documentation

The original documentation is available in the `share/doc` folder.

## More info

For more info and support, please see the xPack project pages from:

  http://xpack.github.io/dev-tools/openocd

Thank you for using open source software,

Liviu Ionescu
