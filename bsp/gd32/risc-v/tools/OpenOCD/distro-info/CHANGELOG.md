## Change & release log

Releases in reverse chronological order.

### 2020-10-13

- v0.10.0-15 published
- v0.10.0-15.1 published on npmjs.com

### 2020-06-27

- v0.10.0-13.2 published on npmjs.com

### 2020-06-26

- v0.10.0-14.2 published on npmjs.com (wrong skip:3)
- v0.10.0-14.1 published on npmjs.com (wrong .tgz extension)
- v0.10.0-14 released
- add binaries for Arm 32/64-bit
- update for XBB v3.2
- based on openocd.git 8833c889da07eae750bcbc11215cc84323de9b74 from June 23rd, 2020

### 2020-03-26

- update for XBB v3.1
- based on openocd.git d9ffe75e257aa4005dd34603860e45c57b1765b6

### 2019-07-27

- bump v0.10.0-14
- add support for Arm binaries
- based on openocd.git e1e63ef30cea39aceda40daf194377c89c570101

### 2019-07-20

- v0.10.0-13.1 published on npmjs.com

### 2019-07-17

- v0.10.0-13 released

### 2019-07-08

- update to 263deb380 from 7 Jul 2019

___

## Historical GNU MCU Eclipse change log

### 2019-04-23

- v0.10.0-12-20190423 released

### 2019-04-09

- prepare - v0.10.0-12
- update to latest master from Apr 7th, 2019
- update LIBUSB1_VERSION="1.0.22"
- update LIBFTDI_VERSION="1.4"

### 2019-01-18

- v0.10.0-11-20190118 released
- update to latest master from Jan 16, 2019
- RISC-V specific patches were removed, only upstreamed functionality retained.

### 2018-10-20

- v0.10.0-10-20181020 released
- rerun, to fix the macOS file dates
- update the -bit to singular

### 2018-10-16

- v0.10.0-9-20181016 released
- update to latest master
- update to latest RISC-V
- revert some of the RISC-V patches in the common files

### 2018-06-19

- update to latest RISC-V commits, including semihosting

### 2018-06-12

- use separate README-*.md files
- update to latest commits, which include new semihosting (OpenOCD June 6th, RISC-V June 12th)

### 2018-05-12

- v0.10.0-8-20180512 released
- use new build scripts based on XBB
- update to latest commits (OpenOCD April 27th, RISC-V May 8th)

### 2018-01-23

- v0.10.0-7-20180123 released
- move semihosting code to separate files
- use them in RISC-V and ARM
- add 'arm semihosting_resexit enable' to allow exit() to return

### 2018-01-12

- v0.10.0-6-20180112 released
- update to master from Dec 20
- update to riscv from Dec 29
- remove the patch to hide the CSRs, the new version displays only a limited number of them.
- remove the `remote_bitbang.c` patch, since it compiles ok on mingw-w64
- the SiFive board scripts were upstreamed to the RISC-V fork

### 2017-11-10

- v0.10.0-5-20171110-dev released
- update to master from Oct 2
- update to riscv from Nov 4
- target.c & riscv/riscv-0[13].c: hide the 4096 CSRs from `monitor reg`
- update the SiFive board script files
- revert the risc-v changes in `remote_bitbang.c`, since they break the build on mingw-w64

### 2017-10-04

- v0.10.0-4-20171004-*-dev released
- update to master from Aug 10
- update to riscv fom Oct 2
- gdb_server.c: workaround to gdb errors; disable passing errors back to gdb since this risc-v change breaks other targets.

### 2017-08-25

- v0.10.0-3-20170826-*-dev released
- merge RISC-V tag v20170818
- server.c: fix clang warning in getsockname()

### 2017-07-03

- update build script to use Debian 9 Docker containers

### 2017-06-22

- v0.10.0-2-20170622-1535-dev released
- merge RISC-V tag v20170621

### 2017-06-15

- move the build specific gnu-mcu-eclipse folder to a separate openocd-build project

### 2017-06-12

- add --enable-riscv and #if BUILD_RISCV
- add --enable-branding

### 2017-06-07

- v0.10.0-1-20170607-2132-dev released
- add sifive-* configuration files to the board folder
- 60-openocd.rules: simplify access rights
- merge RISC-V commit '11008ba' into gnu-mcu-eclipse-dev

### 2017-06-06

- rename gnu-mcu-eclipse & content

### 2017-06-04

- merge original branch 'master' from 2017-06-02 into gnuarmeclipse-dev.
- merge RISC-V commit '51ab5a0' from 2017-05-26 into gnuarmeclipse-dev

### 2017-01-24

- v0.10.0-20170124* released (stable)
- merge original 0.10.0, override local relative path processing

### 2016-10-28

- v0.10.0-20161028*-dev released

### 2016-10-20

- nsi file: add InstallDir; silent install should honour /D

### 2016-01-10

- v0.10.0-20160110*-dev released

### 2015-10-28

- v0.10.0-20151028*-dev released

### 2015-05-19

- v0.9.0-20150519*-dev released
- remove @raggedright from openocd.texi

### 2015-05-11

- the three separate build scripts were deprecated, and a single script,
using Docker, was added to the main gnuarmeclipse-se.git/scripts.

- the greeting shows 32-bits or 64-bits (plural for bits). (wrong!)

### 2015-03-24

- v0.9.0-20150324*-dev released
- v0.8.0-20150324* released

### 2015-03-22

- the NSIS script was fixed to prevent removing the keys when
uninstalling an older version.

### 2015-03-20

- v0.9.0-20150320*-dev released
- v0.8.0-20150320* released

### 2015-03-18

- the build scripts were extended to generate both the stable and the
development version.

- multiple versions of the package can be installed in separate folders,
named using the version.

- for Windows, more accurate keys were stored, so remember separate locations
for 32/64-bit versions.

### 2015-01-31

- v0.8.0-20150131* released

### 2015-01-30

- gnuarmeclipse

All GNU ARM Eclipse OpenOCD build related files were grouped under this folder.

- README.md

Markdown files were added in all new folders, to improve the look when browsed
in the SourceForge Git web browser.

### 2015-01-19

- v0.8.0-20150119* released

### 2015-01-12

- src/openocd.c

Add branding 'GNU ARM Eclipse' to the greeting message, to
more easily identify this custom version.

- helper/options.c

Update the logic used to locate the 'scripts' folder, by
using the argv[0], as on Windows. The logic is a bit more
complicated, to accomodate 3 cases (no path, relative path
and absolute path).

