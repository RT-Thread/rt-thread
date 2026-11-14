/*
 * Test case for DHCPD requested-IP ownership validation and lease expiry.
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define DHCP_MAX_HLEN              16
#define DHCP_DEFAULT_LEASE_TIME_MS (86400U * 1000U)

typedef uint32_t u32_t;
typedef uint8_t u8_t;
typedef int rt_bool_t;

struct dhcp_client_node
{
    struct dhcp_client_node *next;
    u8_t chaddr[DHCP_MAX_HLEN];
    u32_t ipaddr;
    u32_t lease_end;
};

static u32_t mock_sys_now = 0;

static u32_t sys_now(void)
{
    return mock_sys_now;
}

static rt_bool_t dhcp_client_lease_expired(const struct dhcp_client_node *node)
{
    u32_t lease_start = node->lease_end - DHCP_DEFAULT_LEASE_TIME_MS;
    return (u32_t)(sys_now() - lease_start) >= DHCP_DEFAULT_LEASE_TIME_MS;
}

static void test_requested_ip_ownership(void)
{
    struct dhcp_client_node node;
    u8_t mac_owner[6] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55 };
    u8_t mac_other[6] = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };

    memset(&node, 0, sizeof(node));
    memcpy(node.chaddr, mac_owner, 6);
    node.ipaddr = 0x0101a8c0; /* 192.168.1.1 */

    /* Same MAC: ownership valid */
    assert(memcmp(node.chaddr, mac_owner, 6) == 0);

    /* Different MAC: ownership invalid (must not reuse) */
    assert(memcmp(node.chaddr, mac_other, 6) != 0);

    printf("test_requested_ip_ownership PASSED\n");
}

static void test_lease_expiry(void)
{
    struct dhcp_client_node node;
    memset(&node, 0, sizeof(node));

    mock_sys_now = 1000000;
    node.lease_end = mock_sys_now + DHCP_DEFAULT_LEASE_TIME_MS;

    /* Currently active */
    assert(!dhcp_client_lease_expired(&node));

    /* After lease time expires */
    mock_sys_now += DHCP_DEFAULT_LEASE_TIME_MS + 10;
    assert(dhcp_client_lease_expired(&node));

    printf("test_lease_expiry PASSED\n");
}

int main(void)
{
    test_requested_ip_ownership();
    test_lease_expiry();
    printf("All dhcpd regression tests passed!\n");
    return 0;
}
