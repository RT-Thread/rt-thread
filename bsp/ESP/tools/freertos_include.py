"""Build helpers shared by the ESP32 BSPs."""

import os


def _norm(path):
    return os.path.normcase(os.path.abspath(str(path))).replace('\\', '/').lower()


def fix_freertos_include_order(env):
    """Keep the RT-Thread FreeRTOS-Wrapper first in the include search order.

    ESP-IDF's scons shim (components/rtthread/scons/include/freertos/FreeRTOS.h)
    forwards <freertos/FreeRTOS.h> with #include_next, so the Wrapper include
    directories must be searched after the shim but before ESP-IDF's own
    FreeRTOS-Kernel copy.  Package SConscripts are evaluated in directory
    order, which is not stable, so enforce the order after PrepareBuilding().
    """
    cpp = list(env.get('CPPPATH', []))
    shim = None
    wrapper = []
    wrapper_keys = set()

    for path in cpp:
        norm = _norm(path)
        if norm.endswith('/components/rtthread/scons/include'):
            if shim is None:
                shim = path
        elif '/freertos_wrapper-' in norm or '/freertos-wrapper-' in norm:
            if norm not in wrapper_keys:
                wrapper_keys.add(norm)
                wrapper.append(path)

    if shim is None or not wrapper:
        return

    # Drop the Wrapper entries first so that they can be inserted right after
    # the shim, whatever order the package SConscripts ran in.
    rest = [p for p in cpp if _norm(p) not in wrapper_keys]

    shim_key = _norm(shim)
    for index, path in enumerate(rest):
        if _norm(path) == shim_key:
            rest[index + 1:index + 1] = wrapper
            env.Replace(CPPPATH=rest)
            return
