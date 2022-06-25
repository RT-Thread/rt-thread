[![Github All Releases](https://img.shields.io/github/downloads/xpack-dev-tools/openocd-xpack/total.svg)](https://github.com/xpack-dev-tools/openocd-xpack/releases/)

# The xPack OpenOCD fork

This repository is a fork of the official [OpenOCD](http://openocd.org)
repository, and was created
to store the few changes that were performed in 
[The xPack OpenOCD](https://github.com/xpack-dev-tools/openocd-xpack).

## URLs

- `https://github.com/xpack-dev-tools/openocd.git` - the URL of this fork
- `git://git.code.sf.net/p/openocd/code` - the URL of the upstream repo.

## Branches

- `xpack` - the updated content, used during the builds
- `xpack-develop` - the updated content, used during development
- `master` - the original content, it follows the upstream master.

## Changes

The changes are minimal and should not introduce functional differences:

- a configure option was added to configure branding (`--enable-branding`)
- the `src/openocd.c` file was edited to display the branding string
- the `contrib/60-openocd.rules` file was simplified to avoid protection 
  related issues.

## How to use

Details on how to install and use **The xPack OpenOCD** are available in the
separate [xpack-dev-tools/openocd-xpack](https://github.com/xpack-dev-tools/openocd-xpack) project.

## Support

For issues related to the OpenOCD functionality, please use the 
[official discussion channels](http://openocd.org/discussion/).

## Contributing & patches

This repository plans to follow the upstream OpenOCD repository; if you have
patches that fix various issues, please **do not** submit them here
since they'll most probably be ignored.

Instead, submit them to the upstream Gerrit server; for details please see the 
[Submitting patches to the OpenOCD Gerrit server](http://openocd.org/doc-release/doxygen/patchguide.html) page.

