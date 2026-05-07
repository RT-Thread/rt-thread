# custom_fee

This directory contains the first code skeleton for the redesigned FEE module.

Current scope:

- public API and internal type definitions
- on-flash helper interfaces
- unified fee_port entry with overridable flash driver hooks
- scheduler / recovery / GC / lane module skeletons
- default RAM-backed flash backend for bring-up and QEMU tests
- public user API guide: API列表.md
- diagnostic test guide: fee_diag_test.md

This is not a feature-complete implementation yet. It is intended to freeze module
boundaries and enable incremental bring-up.
