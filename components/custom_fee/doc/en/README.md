# custom_fee English Documentation

This directory contains the English documentation set for `custom_fee`.

## Recommended reading order

1. [fee_redesign.md](./fee_redesign.md)
2. [fee_API.md](./fee_API.md)
3. [fee_onflash_format.md](./fee_onflash_format.md)
4. [fee_boot_recovery.md](./fee_boot_recovery.md)
5. [fee_scheduler_gc.md](./fee_scheduler_gc.md)
6. [fee_cache_checkpoint.md](./fee_cache_checkpoint.md)
7. [fee_cfg_rules.md](./fee_cfg_rules.md)
8. [fee_port_adapter.md](./fee_port_adapter.md)
9. [fee_diag_test.md](./fee_diag_test.md)

## Document overview

- `fee_redesign.md`: system goals, architecture, storage model, and rollout plan
- `fee_API.md`: public API semantics, integration pattern, and usage pitfalls
- `fee_onflash_format.md`: sector, record, and checkpoint persistence format
- `fee_boot_recovery.md`: boot recovery states, checkpoint restore, and tail scan
- `fee_scheduler_gc.md`: request scheduling, `BUSY_INTERNAL`, and GC rules
- `fee_cache_checkpoint.md`: RAM cache structure, checkpoint policy, and bounds
- `fee_cfg_rules.md`: block configuration, lane mapping, and sizing rules
- `fee_port_adapter.md`: flash-port abstraction and backend expectations
- `fee_diag_test.md`: diagnostic test flow, dump interpretation, and performance view
