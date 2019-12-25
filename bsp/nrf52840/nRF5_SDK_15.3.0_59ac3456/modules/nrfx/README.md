# nrfx

## Overview

nrfx is a standalone set of drivers for peripherals present in Nordic
Semiconductor's SoCs. It originated as an extract from the nRF5 SDK.
The intention was to provide drivers that can be used in various environments
without the necessity to integrate other parts of the SDK into them.
For the user's convenience, the drivers come with the MDK package. This package
contains definitions of register structures and bitfields for all supported
SoCs, as well as startup and initialization files for them.

## Supported SoCs

* nRF51 Series
* nRF52810
* nRF52811
* nRF52832
* nRF52840
* nRF9160

## Directories

```
 .
 ├── doc             # Project documentation files
 ├── drivers         # nrfx drivers files
 │   └── include     # nrfx drivers headers
 │   └── src         # nrfx drivers sources
 ├── hal             # Hardware Access Layer files
 ├── mdk             # Nordic MDK files
 ├── soc             # Nordic SoC related files
 └── templates       # Templates of nrfx integration files
```

## Generating documentation

nrfx documentation is available in the `doc\html` folder of the release package.

You can also generate documentation yourself from the source code. To do it, install doxygen
and run one of the scripts: `generate_html_doc.bat` or `generate_html_doc.sh`. Generated
documentation will be stored in the `doc\html` directory. Use `index.html` to open it.
