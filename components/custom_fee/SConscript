from building import *

objs = []
cwd = GetCurrentDir()

if not GetDepend("COMPONENT_USING_CUSTOM_FEE"):
    Return('objs')

src = [
    'fee_cfg.c',
    'fee_api.c',
    'fee_port.c',
    'fee_sched.c',
    'fee_core.c',
    'fee_gc.c',
    'fee_recovery.c',
    'fee_cache.c',
    'fee_ckpt.c',
    'fee_lane_fast.c',
    'fee_lane_log.c',
    'fee_lane_bulk.c',
    'fee_onflash.c',
    'fee_test.c',
]

CPPPATH = [cwd]
group = DefineGroup('custom_fee', src, depend = ['COMPONENT_USING_CUSTOM_FEE'], CPPPATH = CPPPATH)

Return('group')
