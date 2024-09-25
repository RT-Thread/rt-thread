OpenSBI as coreboot payload
===========================

[coreboot] is a free/libre and open source firmware platform support multiple
hardware architectures(x86, ARMv7, arm64, PowerPC64, MIPS and RISC-V) and
diverse hardware models. In RISC-V world, coreboot currently support HiFive
Unleashed with OpenSBI as a payload to boot GNU/Linux:

```
SiFive HiFive unleashed's original firmware boot process:
                                    +-----------+
+------+    +------+    +------+    | BBL       |
| MSEL |--->| ZSBL |--->| FSBL |--->|   +-------+
+------+    +------+    +------+    |   | linux |
                                    +---+-------+

coreboot boot process:
                      +---------------------------------------------------------------------+
                      | coreboot                                                            |
+------+   +------+   |  +-----------+  +----------+  +----------+  +-----------------------+
| MSEL |-->| ZSBL |-->|  | bootblock |->| romstage |->| ramstage |->| payload ( OpenSBI)    |
+------+   +------+   |  +-----------+  +----------+  +----------+  |             +-------+ |
                      |                                             |             | linux | |
                      +---------------------------------------------+-------------+-------+-+
```

The upstreaming work is still in progress. There's a [documentation] about how
to build [out-of-tree code] to load OpenSBI.

[coreboot]: https://www.coreboot.org/
[documentation]: https://github.com/hardenedlinux/embedded-iot_profile/blob/master/docs/riscv/hifiveunleashed_coreboot_notes-en.md
[out-of-tree code]: https://github.com/hardenedlinux/coreboot-HiFiveUnleashed
