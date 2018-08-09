# nrfx

## Overview

nrfx is an extract from the nRF5 SDK that contains solely the drivers for
peripherals present in Nordic SoCs, for convenience complemented with the MDK
package containing required structures and bitfields definitions, startup
files etc.

## Supported SoCs

* nRF51 Series
* nRF52810
* nRF52832
* nRF52840

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

nrfx documentation is availabe in the `doc\html` folder of the release package.

You can also generate documentation yourself from the source code. To do it, install doxygen
and run one of the scripts: `generate_html_doc.bat` or `generate_html_doc.sh`. Generated
documentation will be stored in the `doc\html` directory. Use `index.html` to open it.
