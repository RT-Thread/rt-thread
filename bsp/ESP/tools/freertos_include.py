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
    front = []
    front_keys = set()

    for path in cpp:
        norm = _norm(path)
        if norm.endswith('/components/rtthread/scons/include'):
            if shim is None:
                shim = path
            continue

        if '/freertos_wrapper-' in norm or '/freertos-wrapper-' in norm:
            if norm not in front_keys:
                front_keys.add(norm)
                wrapper.append(path)
                front.append(path)
        elif norm.endswith('/idf_port/include') or \
                norm.endswith('/idf_port/include/freertos'):
            # The BSP's FreeRTOSConfig.h must win over the ESP-IDF copy that
            # Wi-Fi/BLE configurations add to the include path.
            if norm not in front_keys:
                front_keys.add(norm)
                front.append(path)

    if shim is None or not wrapper:
        return

    # Drop the Wrapper and BSP port config entries first so that they can be
    # inserted right after the shim, whatever order the SConscripts ran in.
    rest = [p for p in cpp if _norm(p) not in front_keys]

    shim_key = _norm(shim)
    for index, path in enumerate(rest):
        if _norm(path) == shim_key:
            rest[index + 1:index + 1] = front
            env.Replace(CPPPATH=rest)
            return
