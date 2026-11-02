@page page_bsp_contribution_guide_en BSP Contribution Guide

# BSP Contribution Guide

This document describes the directory hierarchy requirements for adding or
updating BSPs, so board-level, chip-level, and architecture-level code stay in
clear layers.

## BSP Directory Hierarchy

BSP directories usually fall into two hierarchy styles depending on where shared
code is kept: vendor-level sharing, and vendor + series-level sharing. In either
case, follow these principles:

- `board/` contains board initialization, pin settings, clock settings, linker
  scripts, and other files that only belong to the current board.
- The upper or sibling shared `libraries/` directory contains chip libraries,
  HAL, CMSIS, SDK, drivers, and driver adaptation code shared by BSPs from the
  same vendor or series. Driver directories should also be placed under
  `libraries/`.
- The sibling `tools/` directory contains helper scripts shared by BSPs from the
  same vendor or series.

If multiple BSPs share the same package or SDK, do not maintain duplicate copies
under each BSP. Put the shared source in the common layer or use the package
mechanism, then reference it from the BSP build scripts. When adding a BSP, do
not create extra directory levels without a clear need, and do not place BSP
code under non-BSP directories such as `components/`, `src/`, or `include/`.
Abstract driver frameworks belong in `components/drivers/`, and shared chip or
CPU architecture porting code belongs in `libcpu/`.

### Vendor-Level Shared Layout (STM32 Example)

STM32 BSPs are usually placed directly under `bsp/stm32/<board>`. Driver
adaptation code, templates, tools, and package selections shared by STM32 BSPs
are kept under `bsp/stm32/libraries/` and `bsp/stm32/tools/`:

```text
bsp/stm32/
├── libraries/
│   ├── HAL_Drivers/        # Driver adaptation shared by STM32 BSPs
│   ├── drivers/            # Drivers shared by multiple STM32 BSPs, if any
│   ├── templates/          # Reference templates for new BSPs
│   └── Kconfig             # Vendor HAL/CMSIS package selections
├── tools/                  # Vendor-level helper scripts
├── stm32f407-atk-explorer/
│   ├── board/              # Board-only initialization, pins, clocks, linker scripts
│   ├── Kconfig
│   ├── SConscript
│   └── SConstruct
└── stm32f429-atk-apollo/
    ├── board/
    ├── Kconfig
    ├── SConscript
    └── SConstruct
```

### Vendor + Series-Level Shared Layout (NXP Example)

NXP-style BSPs are usually split first by vendor, product line, or chip series.
Driver adaptation code, templates, tools, and package selections shared by a
series are kept under that series directory. For example, i.MX RT uses
`bsp/nxp/imx/imxrt/libraries/`, LPC55S uses
`bsp/nxp/lpc/lpc55sxx/libraries/`, and MCX keeps separate `libraries/`
directories under series such as `mcxa`, `mcxc`, `mcxe`, and `mcxn`.

The NXP tree also contains historical BSP layouts, such as single-BSP LPC
directories like `lpc176x`, and a few older directories named `Libraries/`.
Do not extend those legacy layouts when adding or restructuring BSPs. If
drivers, SDK code, or templates are reused by multiple BSPs, move or place them
under the corresponding series-level `libraries/` and `tools/` layer.

```text
bsp/nxp/
├── imx/
│   └── imxrt/
│       ├── libraries/
│       │   ├── drivers/        # Drivers and driver adaptation shared by i.MX RT BSPs
│       │   ├── templates/      # Reference templates for new BSPs
│       │   └── Kconfig         # NXP i.MX RT SDK package selections
│       ├── tools/              # Helper scripts shared by this series
│       └── imxrt1052-nxp-evk/
│           ├── board/          # Board-only initialization, pins, clocks, linker scripts
│           ├── Kconfig
│           ├── SConscript
│           └── SConstruct
├── lpc/
│   └── lpc55sxx/
│       ├── libraries/          # Driver adaptation, templates, and package selections shared by LPC55S BSPs
│       ├── tools/
│       └── lpc55s69_nxp_evk/
│           ├── board/
│           ├── Kconfig
│           ├── SConscript
│           └── SConstruct
└── mcx/
    ├── tools/                  # Helper tools shared by MCX series
    └── mcxn/
        ├── libraries/          # CMSIS, series drivers, and package selections shared by MCXN BSPs
        └── frdm-mcxn947/
            ├── board/
            ├── Kconfig
            ├── SConscript
            └── SConstruct
```

### Vendor HAL/SDK Packages

If the vendor HAL, CMSIS, or SDK is already provided as an RT-Thread package,
the BSP should not submit or maintain another full copy of the same source code.
The BSP should select the corresponding `PKG_USING_*` package in `Kconfig` and
reference package contents from `SConscript` according to the enabled
configuration. `pkgs --update` is responsible for downloading package sources.

In this case, `libraries/` mainly keeps driver adaptation code, reusable
drivers, templates, helper scripts, and package selection logic. Do not commit
package directories downloaded by `pkgs --update` as BSP source, and do not let
`scons --dist` include packages or libraries that are not enabled by the current
BSP.

## Submission Requirements

- Keep the BSP hierarchy clear and only submit board-level files required by the
  current board.
- Libraries, driver adaptation code, reusable drivers, templates, and scripts
  shared by BSPs from the same vendor or series should be placed in the shared
  `libraries/` or `tools/` layer to avoid duplicate copies across BSPs.
- Driver adaptation code and reusable drivers should be placed under
  `libraries/`, not under a single board directory.
- If the vendor HAL, CMSIS, or SDK has been packaged, prefer the package
  mechanism and do not submit duplicate package source code under the BSP.
- Build scripts should reference common code from the shared layer, and
  `scons --dist` should not include packages or libraries that are not required
  by the current BSP.
