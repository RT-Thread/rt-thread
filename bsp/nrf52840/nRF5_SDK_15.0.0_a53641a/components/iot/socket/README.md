# Socket module

The socket module contains the BSD socket implementation for the IoT SDK. The purpose of the socket
API is to

* Provide a common API for all platforms
* Simplify porting of pc network applications

The socket API hides details of the underlying transport, but supports proprietary extensions for
controlling configuration settings and using underlying transport layers.

<pre>
socket/
    api/            - Public socket API headers
    common/         - Common implementation of API and implementation code shared by all platforms (main socket API implementation, with hooks for different transports)
    libraries/      - Generic libraries that are not tied to a specific platform
        portdb/     - Port database to track and allocate socket ports
        addr_util/  - Common address utilities
        mbuf/       - Memory buffer utilities
    transport/      - Transport/network stack hooks
        ipv6/       - Nordic IPv6 stack transport hook
        lwip/       - LwIP transport hook
        test/       - Integration tests shared between transport stacks
    platform/       - Platform specific code
        ble/        - BLE specific code (only wrappers around sd_ble_app_evt_())
    config/         - Configuration socket implementations
        medium/     - Medium configuration socket implementation
</pre>
