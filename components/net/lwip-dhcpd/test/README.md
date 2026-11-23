# DHCPD lease host test

Host-side regression test for `../dhcp_server_raw.c`.  It compiles the
production source against the lwIP / RT-Thread stubs in `mock/`, so the lease
lookup, allocation, expiry and lifecycle paths under test are the real ones.

Run it with:

```sh
make run
```

or directly:

```sh
cc -std=c99 -Wall -Wextra -Wno-unused-function -Wno-unused-parameter \
   -I mock test_dhcpd_lease.c -o /tmp/dhcpd_lease_test
/tmp/dhcpd_lease_test
```

No board, QEMU or RT-Thread build is needed: the whole lwIP surface used by
this component is stubbed in `mock/mock_lwip.h`.  The test exits non-zero when
a check fails, so it can run in CI (see
`.github/workflows/dhcpd_host_test.yml`).

## What it covers

- `REQUESTED_IP` ownership: a lease is only returned to its own MAC.
- Expired-lease reclaim in `dhcp_client_remove_expired()` / allocation.
- `sys_now()` wrap-around handling of the lease expiry arithmetic.
- The Ethernet-only entry gate (`hlen == 6`) and short hardware addresses.
- Start/stop register and cancel exactly one periodic recycle timeout, a
  repeated start does not stack a second one, and stop leaves no timer behind.
- Calls made from the tcpip thread itself run in place instead of deadlocking
  on `tcpip_callback()`.
- Full pool: allocation fails while all addresses are leased, and succeeds
  after the periodic timer reclaims them without any incoming packet.
- A lease that crosses the 32-bit millisecond wrap stays valid, and more than
  a whole `2^32 ms` idle period with the recycle timer running keeps the pool
  usable.

## What it does not cover

The mock models the lwIP tcpip thread (timeouts and callbacks), but it is
single-threaded: it cannot reproduce the real race in lwIP 2.0.3's
`sys_check_timeouts()` and it does not exercise a board or QEMU.  A firmware
cross build is still required for that.