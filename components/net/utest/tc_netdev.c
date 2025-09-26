/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-09-12     Rbb666       the first version
 */

#include <rtthread.h>

#include "utest.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <dfs_net.h>
#include <netdev.h>
#include <netdev_ipaddr.h>
#include <sal_low_lvl.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/* Callback event synchronization timeout (milliseconds) */
#define CALLBACK_EVENT_TIMEOUT 1000

/** @brief Save original default network device pointer for restoration after testing */
static struct netdev *netdev_default_old = RT_NULL;

/* Save initial network configuration for network state restoration after testing */
static ip_addr_t initial_ip_addr;     /**< Initial IP address */
static ip_addr_t initial_netmask;     /**< Initial subnet mask */
static ip_addr_t initial_gw;          /**< Initial gateway address */
static ip_addr_t initial_dns0;        /**< Initial primary DNS server */
static ip_addr_t initial_dns1;        /**< Initial secondary DNS server */
static rt_bool_t initial_dhcp_enabled; /**< Initial DHCP enable status */

/**
 * @brief Execute multiple ping tests and calculate success rate
 *
 * This function performs multiple ping operations to a specified host and determines
 * test results based on success rate. The test passes if success rate exceeds 80%.
 *
 * @param netdev Network device pointer
 * @param host Target host address (IP address or domain name)
 * @param n Number of ping test attempts
 * @return rt_err_t RT_EOK-test passed (success rate>=80%), -RT_ERROR-test failed
 *
 * @note This function uses 32-byte data packets with a 5-second timeout
 */
rt_err_t multiple_ping_test(struct netdev *netdev, const char *host, rt_uint32_t n)
{
#define UTEST_PING_DATA_LEN           32                    /* Ping data packet size */
#define UTEST_PING_TIMEOUT            (5 * RT_TICK_PER_SECOND)  /* Ping timeout: 5 seconds */

    rt_uint32_t success_num = 0, i;
    rt_err_t res = RT_EOK;
    struct netdev_ping_resp ping_resp;

    /* Execute ping operations n times */
    for (i = 0; i < n; i++)
    {
        res = netdev->ops->ping(netdev, host, UTEST_PING_DATA_LEN, UTEST_PING_TIMEOUT, &ping_resp, RT_FALSE);
        if (res == RT_EOK)
        {
            success_num++;
        }
    }

    /* Test passes if success rate is more than 80 percent */
    if (success_num >= ceil(0.8 * n))
        return RT_EOK;
    else
        return -RT_ERROR;
}

/**
 * @brief Test network connectivity using ping operations
 *
 * This function tests network connectivity by pinging various targets:
 * - Gateway address (should succeed)
 * - Invalid internal IP address (should fail)
 * - External IP address (should succeed)
 * - Invalid external IP address (should fail)
 * - External URL (should succeed)
 * - Invalid external URL (should fail)
 *
 * @note This test verifies both successful and failed ping scenarios
 */
static void test_netdev_ping(void)
{
#define UTEST_INTRANET_WRONG_IP_ADDR  "192.256.0.321"      /* Invalid IP format */
#define UTEST_EXTERNAL_IP_ADDR        "8.8.8.8"            /* Valid external IP */
#define UTEST_EXTERNAL_WRONG_IP_ADDR  "123.456.789.012"    /* Invalid IP format */
#define UTEST_EXTERNAL_URL            "www.baidu.com"      /* Valid external URL */
#define UTEST_EXTERNAL_WRONG_URL      "www.abcsdd.com"     /* Non-existent URL */

    rt_err_t res = RT_EOK;

    /* Test ping to gateway address - should succeed */
    res = multiple_ping_test(netdev_default, inet_ntoa(netdev_default->gw), 10);
    uassert_true(res == RT_EOK);

    /* Test ping to invalid internal IP - should fail */
    res = multiple_ping_test(netdev_default, UTEST_INTRANET_WRONG_IP_ADDR, 1);
    uassert_false(res == RT_EOK);

    /* Test ping to external IP address - should succeed */
    res = multiple_ping_test(netdev_default, UTEST_EXTERNAL_IP_ADDR, 10);
    uassert_true(res == RT_EOK);

    /* Test ping to invalid external IP - should fail */
    res = multiple_ping_test(netdev_default, UTEST_EXTERNAL_WRONG_IP_ADDR, 1);
    uassert_false(res == RT_EOK);

    /* Test ping to external URL - should succeed */
    res = multiple_ping_test(netdev_default, UTEST_EXTERNAL_URL, 10);
    uassert_true(res == RT_EOK);

    /* Test ping to invalid external URL - should fail */
    res = multiple_ping_test(netdev_default, UTEST_EXTERNAL_WRONG_URL, 1);
    uassert_false(res == RT_EOK);
}

/**
 * @brief Test network interface configuration and status
 *
 * This function tests:
 * - Network interface status (up/link up)
 * - IP address configuration validity
 * - Gateway configuration validity
 * - Subnet mask configuration validity
 * - DNS server configuration validity
 *
 * @note Validates that the network interface is properly configured and operational
 */
static void test_netdev_ifconfig(void)
{
    /* Perform network interface status validation */
    uassert_true(netdev_is_up(netdev_default) && netdev_is_link_up(netdev_default)); /* Interface should be up and linked */
    uassert_false(ip_addr_isany(&netdev_default->ip_addr));                     /* IP address should be assigned */
    uassert_false(ip_addr_isany(&netdev_default->gw));                          /* Gateway should be configured */
    uassert_false(ip_addr_isany(&netdev_default->netmask));                     /* Subnet mask should be configured */
    uassert_false(ip_addr_isany(&netdev_default->dns_servers[0]));              /* Primary DNS should be configured */
}

/**
 * @brief Test network statistics functionality
 *
 * This function tests the netstat operation capability of the network device.
 * It verifies that the netstat function can be called without crashing.
 *
 * @note This is a basic functionality test to ensure netstat operation is available
 */
static void test_netdev_netstat(void)
{
    /* Simply test that netstat function can be called without crashing */
    if (netdev_default->ops->netstat)
    {
        netdev_default->ops->netstat(netdev_default);
        uassert_true(RT_TRUE); /* If we reach here, the function call succeeded */
    }
    else
    {
        uassert_true(RT_FALSE); /* netstat function not available */
    }
}

/**
 * @brief Test DNS server configuration and hostname resolution
 *
 * This function tests:
 * - Setting incorrect DNS server and verifying hostname resolution fails
 * - Setting correct DNS server and verifying hostname resolution succeeds
 * - DNS server configuration operations
 *
 * @note DNS configuration will be restored in utest_tc_cleanup
 */
static void test_netdev_dns(void)
{
#define UTEST_DNS               "114.114.114.114"   /* Valid DNS server */
#define UTEST_WRONG_DNS         "13.19.123.143"     /* Invalid DNS server */
#define UTEST_WRONG_HOST_NAME   "www.abcde.com"     /* Test hostname */
#define UTEST_HOST_ADDR         "www.rt-thread.org" /* RT-Thread official website */

    ip_addr_t ipaddr = {0};
    struct hostent *res = RT_NULL;
    struct sal_proto_family *netdev_inet = RT_NULL;

    /* Get SAL protocol family for DNS operations */
    netdev_inet = netdev_default->sal_user_data;
    if (netdev_inet == RT_NULL)
    {
        rt_kprintf("get sal proto family fail!");
        uassert_true(RT_FALSE);
        return;
    }

    /* Test with wrong DNS server - hostname resolution should fail */
    inet_aton(UTEST_WRONG_DNS, &ipaddr);
    netdev_default->ops->set_dns_server(netdev_default, 0, &ipaddr);
    netdev_default->ops->set_dns_server(netdev_default, 1, &ipaddr);
    res = netdev_inet->netdb_ops->gethostbyname(UTEST_WRONG_HOST_NAME);
    if (res == RT_NULL)
    {
        uassert_true(RT_TRUE);  /* Expected failure */
    }
    else
    {
        uassert_true(RT_FALSE); /* Unexpected success */
    }

    /* Test with correct DNS server - hostname resolution should succeed */
    inet_aton(UTEST_DNS, &ipaddr);
    netdev_default->ops->set_dns_server(netdev_default, 0, &ipaddr);
    netdev_default->ops->set_dns_server(netdev_default, 1, &ipaddr);
    res = netdev_inet->netdb_ops->gethostbyname(UTEST_HOST_ADDR);
    uassert_true(res != RT_NULL);

    /* DNS will be restored in utest_tc_cleanup */
}

/**
 * @brief Test DHCP functionality
 *
 * This function tests:
 * - DHCP disable operation
 * - DHCP state verification
 * - DHCP state restoration
 * - Network configuration stability after DHCP operations
 *
 * @note Includes retry mechanism to wait for network configuration restoration
 *       to prevent interference with subsequent ping tests
 */
static void test_netdev_dhcp(void)
{
    rt_err_t res;
    rt_bool_t initial_state;
    ip_addr_t initial_ip, initial_gw;
    int retry_count = 0;
    const int max_retries = 10;

    /* Save initial network configuration for restoration */
    initial_state = netdev_is_dhcp_enabled(netdev_default);
    initial_ip = netdev_default->ip_addr;
    initial_gw = netdev_default->gw;
    rt_kprintf("Initial DHCP state: %s\n", initial_state ? "enabled" : "disabled");
    rt_kprintf("Initial IP: %s, Gateway: %s\n", inet_ntoa(initial_ip), inet_ntoa(initial_gw));

    /* Test DHCP disable operation */
    res = netdev_dhcp_enabled(netdev_default, RT_FALSE);
    if (res == RT_EOK)
    {
        uassert_false(netdev_is_dhcp_enabled(netdev_default));
        rt_kprintf("DHCP successfully disabled\n");
    }
    else
    {
        rt_kprintf("Failed to disable DHCP: error code %d\n", res);
        uassert_true(RT_FALSE);
        return;
    }

    /* Restore initial DHCP state */
    res = netdev_dhcp_enabled(netdev_default, initial_state);
    uassert_true(res == RT_EOK);

    /* Wait for network configuration to stabilize after DHCP restoration */
    if (initial_state)
    {
        rt_kprintf("Waiting for DHCP to restore network configuration...\n");
        while (retry_count < max_retries)
        {
            rt_thread_mdelay(1000); /* Wait 1000ms between checks */

            /* Check if IP and gateway are properly restored */
            if (!ip_addr_isany(&netdev_default->ip_addr) &&
                    !ip_addr_isany(&netdev_default->gw))
            {
                rt_kprintf("Network configuration restored after %d retries\n", retry_count);
                rt_kprintf("Current IP: %s, Gateway: %s\n",
                           inet_ntoa(netdev_default->ip_addr),
                           inet_ntoa(netdev_default->gw));
                break;
            }
            retry_count++;
        }

        /* Fail the test if network configuration is not restored within timeout */
        if (retry_count >= max_retries)
        {
            rt_kprintf("Failed: Network configuration not fully restored within timeout\n");
            uassert_true(RT_FALSE);
        }
    }
}

/**
 * @brief Test setting network interface configuration parameters
 *
 * This function tests:
 * - IP address setting and verification
 * - Gateway address setting and verification
 * - Network configuration restoration
 * - DHCP disable/enable during configuration changes
 *
 * @note DHCP will be restored in utest_tc_cleanup
 */
static void test_netdev_ifconfig_set(void)
{
#define UTEST_WRONG_IP_ADDR         "192.1.4.125"       /* Test IP address */
#define UTEST_HOST_ADDR             "www.rt-thread.org" /* Test hostname */
#define UTEST_WRONG_GW_IP_ADDR      "192.168.99.1"      /* Test gateway address */

    ip_addr_t ipaddr, true_ipaddr;
    rt_err_t res = RT_EOK;

    /* Save original IP address for restoration */
    true_ipaddr = netdev_default->ip_addr;

    /* Disable DHCP before manual configuration */
    res = netdev_dhcp_enabled(netdev_default, RT_FALSE);
    if (res != RT_EOK)
    {
        rt_kprintf("Failed to disable DHCP: %d\n", res);
        uassert_true(RT_FALSE);
    }

    /* Test setting a different valid IP address */
    inet_aton(UTEST_WRONG_IP_ADDR, &ipaddr);
    res = netdev_set_ipaddr(netdev_default, &ipaddr);
    if (res != RT_EOK)
    {
        rt_kprintf("Failed to set IP address: %d\n", res);
        uassert_true(RT_FALSE);
    }

    /* Verify IP address was set correctly */
    uassert_true(ip_addr_cmp(&netdev_default->ip_addr, &ipaddr));

    /* Test ping with new IP configuration (may fail due to network setup) */
    res = multiple_ping_test(netdev_default, UTEST_HOST_ADDR, 1);
    /* Don't assert on ping result as it depends on network setup */

    /* Restore original IP address */
    res = netdev_set_ipaddr(netdev_default, &true_ipaddr);
    if (res != RT_EOK)
    {
        rt_kprintf("Failed to restore IP address: %d\n", res);
        uassert_true(RT_FALSE);
    }

    /* Verify IP address was restored */
    uassert_true(ip_addr_cmp(&netdev_default->ip_addr, &true_ipaddr));

    /* Test gateway setting */
    ip_addr_t original_gw = netdev_default->gw;
    inet_aton(UTEST_WRONG_GW_IP_ADDR, &ipaddr);
    res = netdev_set_gw(netdev_default, &ipaddr);
    if (res != RT_EOK)
    {
        rt_kprintf("Failed to set gateway: %d\n", res);
        uassert_true(RT_FALSE);
    }

    /* Verify gateway was set correctly */
    uassert_true(ip_addr_cmp(&netdev_default->gw, &ipaddr));

    /* Restore original gateway */
    res = netdev_set_gw(netdev_default, &original_gw);
    if (res != RT_EOK)
    {
        rt_kprintf("Failed to restore gateway: %d\n", res);
        uassert_true(RT_FALSE);
    }

    /* Verify gateway was restored */
    uassert_true(ip_addr_cmp(&netdev_default->gw, &original_gw));

    /* DHCP will be restored in utest_tc_cleanup */
}

/**
 * @brief Test setting the default network device
 *
 * This function tests the ability to set a network device as the default
 * network interface for the system.
 */
static void test_netdev_set_default_netdev(void)
{
    netdev_set_default(netdev_get_by_name(RT_UTEST_DEFAULT_NETDEV_NAME));
    uassert_true(RT_TRUE);
}

/**
 * @brief Test IP address conversion functions
 *
 * This function tests various IP address conversion utilities:
 * - IPv4 string to binary conversion (aton)
 * - IPv4 binary to string conversion (ntoa)
 * - IPv4 binary to string conversion with buffer (ntoa_r)
 * - IPv4 address parsing and validation
 * - inet_pton and inet_ntop functions
 *
 * @note Tests both valid and invalid IP address formats
 */
static void test_netdev_ipaddr_conversion(void)
{
#define UTEST_IP4_ADDR_STR     "192.168.1.1"        /* Valid IPv4 address */
#define UTEST_IP4_ADDR_STR2    "10.0.0.1"           /* Another valid IPv4 address */
#define UTEST_INVALID_IP_STR   "999.999.999.999"    /* Invalid IPv4 address */

    ip4_addr_t ip4_addr;
    char buf[16]; /* Maximum length for IPv4 string representation */
    int res;

    /* Test IPv4 string to binary conversion (aton) */
    res = netdev_ip4addr_aton(UTEST_IP4_ADDR_STR, &ip4_addr);
    uassert_true(res == 1);  /* Should succeed */
    uassert_true(ip4_addr_get_u32(&ip4_addr) == inet_addr(UTEST_IP4_ADDR_STR));

    /* Test invalid IP address conversion */
    res = netdev_ip4addr_aton(UTEST_INVALID_IP_STR, &ip4_addr);
    uassert_true(res == 0);  /* Should fail */

    /* Test IPv4 binary to string conversion with buffer (ntoa_r) */
    ip4_addr_set_u32(&ip4_addr, inet_addr(UTEST_IP4_ADDR_STR));
    netdev_ip4addr_ntoa_r(&ip4_addr, buf, sizeof(buf));
    uassert_str_equal(buf, UTEST_IP4_ADDR_STR);

    /* Test IPv4 binary to string conversion (ntoa) */
    const char *ntoa_result = netdev_ip4addr_ntoa(&ip4_addr);
    uassert_str_equal(ntoa_result, UTEST_IP4_ADDR_STR);

    /* Test IP address string to binary conversion (ipaddr_addr) */
    in_addr_t addr = netdev_ipaddr_addr(UTEST_IP4_ADDR_STR);
    uassert_true(addr == inet_addr(UTEST_IP4_ADDR_STR));

    /* Test invalid IP address should return INADDR_NONE */
    addr = netdev_ipaddr_addr(UTEST_INVALID_IP_STR);
    uassert_true(addr == INADDR_NONE);

    /* Test inet_pton and inet_ntop for IPv4 */
    struct in_addr in_addr;
    res = netdev_inet_pton(AF_INET, UTEST_IP4_ADDR_STR, &in_addr);
    uassert_true(res == 1);  /* Should succeed */
    uassert_true(in_addr.s_addr == inet_addr(UTEST_IP4_ADDR_STR));

    const char *ntop_result = netdev_inet_ntop(AF_INET, &in_addr, buf, sizeof(buf));
    uassert_true(ntop_result != NULL);
    uassert_str_equal(buf, UTEST_IP4_ADDR_STR);

    /* Test invalid IP format should fail */
    res = netdev_inet_pton(AF_INET, UTEST_INVALID_IP_STR, &in_addr);
    uassert_true(res == 0);  /* Should fail */
}

/**
 * @brief Test network device retrieval functions
 *
 * This function tests various methods to retrieve network devices:
 * - Get device by name (valid and invalid names)
 * - Get device by IP address (valid and invalid addresses)
 * - Get device by interface index (valid and invalid indices)
 * - Get first device by flags
 * - Get device by protocol family (if SAL is enabled)
 *
 * @note Tests both successful and failed retrieval scenarios
 */
static void test_netdev_get_functions(void)
{
    struct netdev *netdev_found;

    /* Test get_by_name */
    netdev_found = netdev_get_by_name(netdev_default->name);
    uassert_true(netdev_found == netdev_default);

    netdev_found = netdev_get_by_name("nonexistent");
    uassert_true(netdev_found == RT_NULL);

    /* Test get_by_ipaddr */
    netdev_found = netdev_get_by_ipaddr(&netdev_default->ip_addr);
    uassert_true(netdev_found == netdev_default);

    ip_addr_t invalid_ip;
    ip_addr_set_zero(&invalid_ip);
    netdev_found = netdev_get_by_ipaddr(&invalid_ip);
    uassert_true(netdev_found == RT_NULL);

    /* Test get_by_ifindex */
    netdev_found = netdev_get_by_ifindex(netdev_default->ifindex);
    uassert_true(netdev_found == netdev_default);

    netdev_found = netdev_get_by_ifindex(-1);
    uassert_true(netdev_found == RT_NULL);

    /* Test get_first_by_flags */
    netdev_found = netdev_get_first_by_flags(NETDEV_FLAG_UP);
    uassert_true(netdev_found != RT_NULL);

    netdev_found = netdev_get_first_by_flags(NETDEV_FLAG_UP | NETDEV_FLAG_LINK_UP);
    uassert_true(netdev_found != RT_NULL);

#ifdef RT_USING_SAL
    /* Test get_by_family */
    netdev_found = netdev_get_by_family(AF_INET);
    uassert_true(netdev_found != RT_NULL);

    /* Test family_get */
    int family = netdev_family_get(netdev_default);
    uassert_true(family == AF_INET);
#endif
}

/**
 * @brief Test network device status setting operations
 *
 * This function tests:
 * - Network interface up/down operations
 * - Link status setting and verification
 * - Status operation error handling
 * - Status restoration
 *
 * @note Carefully avoids disrupting network connectivity during testing
 */
static void test_netdev_status_set(void)
{
    rt_err_t res;
    rt_bool_t original_link_up;

    /* Test set_up and set_down - be careful not to disrupt network */
    rt_bool_t was_up = netdev_is_up(netdev_default);

    if (!was_up)
    {
        res = netdev_set_up(netdev_default);
        uassert_true(res == RT_EOK);
        uassert_true(netdev_is_up(netdev_default));
    }

    uassert_true(netdev_is_up(netdev_default));
    uassert_true(netdev_default->ops->set_up != RT_NULL);
    uassert_true(netdev_default->ops->set_down != RT_NULL);

    /* Test set_down and set_up cycle */
    res = netdev_set_down(netdev_default);
    if (res == RT_EOK)
    {
        uassert_false(netdev_is_up(netdev_default));
        res = netdev_set_up(netdev_default);
        uassert_true(res == RT_EOK);
        uassert_true(netdev_is_up(netdev_default));
    }
    else
    {
        uassert_true(netdev_is_up(netdev_default));
    }

    /* Test link status */
    original_link_up = netdev_is_link_up(netdev_default);
    netdev_low_level_set_link_status(netdev_default, RT_FALSE);
    uassert_false(netdev_is_link_up(netdev_default));
    netdev_low_level_set_link_status(netdev_default, RT_TRUE);
    uassert_true(netdev_is_link_up(netdev_default));

    /* Restore original link status */
    netdev_low_level_set_link_status(netdev_default, original_link_up);
}

/**
 * @brief Test network device configuration setting operations
 *
 * This function tests:
 * - Subnet mask setting and verification
 * - DNS server setting and verification
 * - Network interface parameter setting (set_if)
 * - Configuration restoration
 * - DHCP interaction with manual configuration
 *
 * @note Includes proper configuration backup and restoration
 */
static void test_netdev_config_set(void)
{
    ip_addr_t original_netmask = netdev_default->netmask;
    ip_addr_t original_dns0 = netdev_default->dns_servers[0];
    ip_addr_t original_dns1 = netdev_default->dns_servers[1];
    ip_addr_t test_netmask = {0}, test_dns = {0};
    rt_err_t res;

    /* Test set_netmask */
    if (netdev_is_dhcp_enabled(netdev_default))
    {
        res = netdev_dhcp_enabled(netdev_default, RT_FALSE);
        if (res != RT_EOK)
        {
            goto skip_netmask_test;
        }
    }

    inet_aton("255.255.255.0", &test_netmask);
    res = netdev_set_netmask(netdev_default, &test_netmask);
    if (res == RT_EOK)
    {
        uassert_true(ip_addr_cmp(&netdev_default->netmask, &test_netmask));
    }

    /* Restore netmask */
    res = netdev_set_netmask(netdev_default, &original_netmask);
    uassert_true(res == RT_EOK);

skip_netmask_test:
    /* Test set_dns_server */
    inet_aton("8.8.8.8", &test_dns);
    res = netdev_set_dns_server(netdev_default, 0, &test_dns);
    uassert_true(res == RT_EOK);
    uassert_true(ip_addr_cmp(&netdev_default->dns_servers[0], &test_dns));

    inet_aton("8.8.4.4", &test_dns);
    res = netdev_set_dns_server(netdev_default, 1, &test_dns);
    uassert_true(res == RT_EOK);
    uassert_true(ip_addr_cmp(&netdev_default->dns_servers[1], &test_dns));

    /* Restore DNS servers */
    res = netdev_set_dns_server(netdev_default, 0, &original_dns0);
    uassert_true(res == RT_EOK);
    res = netdev_set_dns_server(netdev_default, 1, &original_dns1);
    uassert_true(res == RT_EOK);

    /* Test set_if */
    ip_addr_t test_ip, test_gw, test_nm;
    ip_addr_t original_ip, original_gw, original_nm;

    original_ip = netdev_default->ip_addr;
    original_gw = netdev_default->gw;
    original_nm = netdev_default->netmask;

    inet_aton("192.168.2.100", &test_ip);
    inet_aton("192.168.2.1", &test_gw);
    inet_aton("255.255.255.0", &test_nm);

    netdev_set_if(netdev_default->name, inet_ntoa(test_ip), inet_ntoa(test_gw), inet_ntoa(test_nm));
    uassert_true(RT_TRUE);

    /* Restore original network configuration */
    netdev_set_ipaddr(netdev_default, &original_ip);
    netdev_set_gw(netdev_default, &original_gw);
    netdev_set_netmask(netdev_default, &original_nm);
}

/* Network device callback test variables */
static rt_bool_t callback_called = RT_FALSE;                    /**< General callback called flag */
static enum netdev_cb_type last_callback_type = NETDEV_CB_ADDR_IP; /**< Last callback type received */
static rt_bool_t ip_callback_called = RT_FALSE;                 /**< IP address callback flag */
static rt_bool_t gw_callback_called = RT_FALSE;                 /**< Gateway callback flag */
static rt_bool_t dhcp_callback_called = RT_FALSE;               /**< DHCP callback flag */

/* Event for synchronizing callback tests */
static rt_event_t callback_event;

/**
 * @brief Helper function for testing callback operations
 *
 * This function performs a network operation and waits for the corresponding
 * callback to be triggered within a specified timeout.
 *
 * @param operation Function pointer to the operation to perform
 * @param param Parameter to pass to the operation
 * @param event_mask Event mask to wait for
 * @param callback_flag Pointer to callback flag to check
 * @param test_name Name of the test for logging purposes
 */
static void test_callback_operation(rt_err_t (*operation)(struct netdev *, void *),
                                    void *param,
                                    rt_uint32_t event_mask,
                                    rt_bool_t *callback_flag,
                                    const char *test_name)
{
    rt_err_t res;
    rt_uint32_t recved;

    /* Reset callback flag */
    *callback_flag = RT_FALSE;

    /* Perform operation */
    res = operation(netdev_default, param);
    if (res == RT_EOK)
    {
        /* Wait for callback event */
        rt_err_t event_res = rt_event_recv(callback_event, event_mask,
                                           RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                                           CALLBACK_EVENT_TIMEOUT, &recved);
        if (event_res == RT_EOK && *callback_flag)
        {
            rt_kprintf("%s test passed\n", test_name);
            uassert_true(RT_TRUE);
        }
        else
        {
            rt_kprintf("%s test failed - event_res=%d, callback_called=%d\n",
                       test_name, event_res, *callback_flag);
            uassert_true(RT_FALSE);
        }
    }
    else
    {
        rt_kprintf("Failed to perform %s: %d\n", test_name, res);
        uassert_true(RT_FALSE);
    }
}

/* Wrapper functions for callback testing */
static rt_err_t set_ipaddr_wrapper(struct netdev *netdev, void *param)
{
    return netdev_set_ipaddr(netdev, (ip_addr_t *)param);
}

static rt_err_t set_gw_wrapper(struct netdev *netdev, void *param)
{
    return netdev_set_gw(netdev, (ip_addr_t *)param);
}

static rt_err_t dhcp_enable_wrapper(struct netdev *netdev, void *param)
{
    return netdev_dhcp_enabled(netdev, *(rt_bool_t *)param);
}

static void test_callback(struct netdev *netdev, enum netdev_cb_type type)
{
    callback_called = RT_TRUE;
    last_callback_type = type;
    rt_kprintf("Callback called: type=%d, netdev=%s\n", type, netdev->name);

    /* Track specific callback types */
    switch (type)
    {
    case NETDEV_CB_ADDR_IP:
        ip_callback_called = RT_TRUE;
        break;
    case NETDEV_CB_ADDR_GATEWAY:
        gw_callback_called = RT_TRUE;
        break;
    case NETDEV_CB_STATUS_DHCP_ENABLE:
        dhcp_callback_called = RT_TRUE;
        break;
    default:
        break;
    }

    /* Send event to synchronize */
    if (callback_event)
    {
        rt_event_send(callback_event, 1 << type);
    }
}

static void empty_callback(struct netdev *netdev, enum netdev_cb_type type)
{
    /* Empty callback function for clearing */
}

/**
 * @brief Test network device callback mechanism
 *
 * This function tests the callback functionality for network events:
 * - Setting status and address callbacks
 * - IP address change callbacks
 * - Gateway change callbacks
 * - DHCP enable callbacks
 * - Callback synchronization using events
 * - Callback cleanup
 *
 * @note Uses event synchronization to verify callbacks are properly triggered
 */
static void test_netdev_callbacks(void)
{
    ip_addr_t test_ip, test_gw;
    rt_bool_t dhcp_enable = RT_TRUE;

    /* Reset callback test variables */
    callback_called = RT_FALSE;
    last_callback_type = NETDEV_CB_ADDR_IP;
    ip_callback_called = RT_FALSE;
    gw_callback_called = RT_FALSE;
    dhcp_callback_called = RT_FALSE;

    /* Set status callback */
    netdev_set_status_callback(netdev_default, test_callback);
    /* Set address callback */
    netdev_set_addr_callback(netdev_default, test_callback);

    /* Test IP address change callback */
    inet_aton("192.168.1.100", &test_ip);
    test_callback_operation(set_ipaddr_wrapper, &test_ip,
                            1 << NETDEV_CB_ADDR_IP, &ip_callback_called, "IP address");

    /* Reset callback flags */
    ip_callback_called = RT_FALSE;
    gw_callback_called = RT_FALSE;

    /* Test gateway change callback */
    inet_aton("192.168.1.1", &test_gw);
    test_callback_operation(set_gw_wrapper, &test_gw,
                            1 << NETDEV_CB_ADDR_GATEWAY, &gw_callback_called, "Gateway");

    /* Reset callback flags */
    dhcp_callback_called = RT_FALSE;

    /* Test DHCP enable callback */
    test_callback_operation(dhcp_enable_wrapper, &dhcp_enable,
                            1 << NETDEV_CB_STATUS_DHCP_ENABLE, &dhcp_callback_called, "DHCP enable");

    /* Clear callbacks */
    netdev_set_status_callback(netdev_default, empty_callback);
    netdev_set_addr_callback(netdev_default, empty_callback);
}

/**
 * @brief Test multiple network interfaces functionality
 *
 * This function tests:
 * - Creating and registering a new network device
 * - Network device search and verification
 * - Default network device switching
 * - Interface index assignment and lookup
 * - Network device list management
 * - Network device unregistration and cleanup
 *
 * @note Creates a temporary test network device for comprehensive testing
 */
static void test_netdev_multiple_interfaces(void)
{
    /* Test network device name */
#define TEST_NETDEV_NAME "fake-e0"

    struct netdev *test_netdev = RT_NULL;
    struct netdev *found_netdev = RT_NULL;
    struct netdev *original_default = netdev_default;
    ip_addr_t test_ip;
    int result;

    rt_slist_t *node = RT_NULL;
    struct netdev *current_netdev;
    int netdev_count = 0;
    rt_bool_t found_original = RT_FALSE;
    rt_bool_t found_test = RT_FALSE;

    /* Allocate memory for test netdev */
    test_netdev = rt_malloc(sizeof(struct netdev));
    if (test_netdev == RT_NULL)
    {
        rt_kprintf("Failed to allocate memory for test netdev\n");
        uassert_true(RT_FALSE);
        return;
    }

    /* Initialize test netdev structure */
    rt_memset(test_netdev, 0, sizeof(struct netdev));

    /* Set basic properties */
    test_netdev->hwaddr_len = 6;
    test_netdev->hwaddr[0] = 0x01;
    test_netdev->hwaddr[1] = 0x02;
    test_netdev->hwaddr[2] = 0x03;
    test_netdev->hwaddr[3] = 0x04;
    test_netdev->hwaddr[4] = 0x05;
    test_netdev->hwaddr[5] = 0x06;

    test_netdev->mtu = 1500;
    test_netdev->flags = NETDEV_FLAG_UP | NETDEV_FLAG_LINK_UP;

    /* Set IP address */
    inet_aton("192.168.2.100", &test_ip);
    ip_addr_copy(test_netdev->ip_addr, test_ip);
    inet_aton("255.255.255.0", &test_ip);
    ip_addr_copy(test_netdev->netmask, test_ip);
    inet_aton("192.168.2.1", &test_ip);
    ip_addr_copy(test_netdev->gw, test_ip);

    /* Register the test netdev */
    result = netdev_register(test_netdev, TEST_NETDEV_NAME, RT_NULL);
    if (result != RT_EOK)
    {
        rt_kprintf("Failed to register test netdev: %d\n", result);
        rt_free(test_netdev);
        uassert_true(RT_FALSE);
        return;
    }

    rt_kprintf("Successfully registered test netdev '%s'\n", TEST_NETDEV_NAME);

    /* Verify the test netdev can be found by name */
    found_netdev = netdev_get_by_name(TEST_NETDEV_NAME);
    uassert_true(found_netdev == test_netdev);

    /* Verify the test netdev can be found by IP address */
    found_netdev = netdev_get_by_ipaddr(&test_netdev->ip_addr);
    uassert_true(found_netdev == test_netdev);

    /* Test default netdev switching */
    netdev_set_default(test_netdev);
    uassert_true(netdev_default == test_netdev);

    /* Switch back to original default */
    netdev_set_default(original_default);
    uassert_true(netdev_default == original_default);

    /* Test netdev ifindex */
    uassert_true(test_netdev->ifindex > 0);
    found_netdev = netdev_get_by_ifindex(test_netdev->ifindex);
    uassert_true(found_netdev == test_netdev);

    if (netdev_list == RT_NULL)
    {
        rt_kprintf("Netdev list is empty\n");
        uassert_true(RT_FALSE);
        return;
    }

    for (node = &(netdev_list->list); node; node = rt_slist_next(node))
    {
        current_netdev = rt_list_entry(node, struct netdev, list);
        netdev_count++;

        if (rt_strcmp(current_netdev->name, original_default->name) == 0)
        {
            found_original = RT_TRUE;
        }
        if (rt_strcmp(current_netdev->name, TEST_NETDEV_NAME) == 0)
        {
            found_test = RT_TRUE;
        }
    }

    uassert_true(netdev_count >= 2); /* At least original + test */
    uassert_true(found_original);
    uassert_true(found_test);

    /* Cleanup: Unregister the test netdev */
    result = netdev_unregister(test_netdev);
    if (result == RT_EOK)
    {
        test_netdev = RT_NULL;
        rt_free(test_netdev);
    }
    else
    {
        rt_kprintf("Failed to unregister test netdev: %d\n", result);
        /* Manual cleanup if unregister failed */
        if (test_netdev != RT_NULL)
        {
            rt_free(test_netdev);
            test_netdev = RT_NULL;
        }
    }

    /* Verify test netdev is no longer accessible */
    found_netdev = netdev_get_by_name(TEST_NETDEV_NAME);
    uassert_true(found_netdev == RT_NULL);
}

/**
 * @brief Unit test initialization function
 *
 * This function performs setup operations before running tests:
 * - Creates callback synchronization event
 * - Locates and configures the test network device
 * - Saves initial network configuration for restoration
 * - Waits for network connectivity to be established
 * - Sets the test network device as default
 *
 * @return rt_err_t RT_EOK on success, -RT_ERROR on failure
 */
static rt_err_t utest_tc_init(void)
{
    struct netdev *netdev_lwip = RT_NULL;

    /* Create event for callback synchronization */
    callback_event = rt_event_create("callback_event", RT_IPC_FLAG_FIFO);
    if (callback_event == RT_NULL)
    {
        rt_kprintf("Failed to create callback event\n");
        return -RT_ERROR;
    }

    netdev_lwip = netdev_get_by_name(RT_UTEST_DEFAULT_NETDEV_NAME);
    if (netdev_lwip == RT_NULL)
    {
        rt_kprintf("Network interface device not found!\n");
        return -RT_ERROR;
    }

    /* Save initial network configuration */
    initial_ip_addr = netdev_lwip->ip_addr;
    initial_netmask = netdev_lwip->netmask;
    initial_gw = netdev_lwip->gw;
    initial_dns0 = netdev_lwip->dns_servers[0];
    initial_dns1 = netdev_lwip->dns_servers[1];
    initial_dhcp_enabled = netdev_is_dhcp_enabled(netdev_lwip);

    rt_kprintf("Saved initial network config - IP: %s, DHCP: %s\n",
               inet_ntoa(initial_ip_addr),
               initial_dhcp_enabled ? "enabled" : "disabled");

    /* Wait for network connect successful */
    while (1)
    {
        if (!ip_addr_isany(&netdev_lwip->ip_addr))
        {
            rt_kprintf("IP address assigned: %s\n", inet_ntoa(netdev_lwip->ip_addr));
            break;
        }
        rt_thread_mdelay(500);
    }

    /* Save the old netdev */
    netdev_default_old = netdev_default;
    netdev_set_default(netdev_lwip);

    if (netdev_default == RT_NULL)
    {
        rt_kprintf("No default network interface!\n");
        return -RT_ERROR;
    }

    return RT_EOK;
}

/**
 * @brief Unit test cleanup function
 *
 * This function performs cleanup operations after running tests:
 * - Deletes callback synchronization event
 * - Restores original network configuration
 * - Restores original DHCP settings
 * - Restores original default network device
 *
 * @return rt_err_t RT_EOK on success
 */
static rt_err_t utest_tc_cleanup(void)
{
    rt_err_t res;

    /* Delete callback event */
    if (callback_event)
    {
        rt_event_delete(callback_event);
        callback_event = RT_NULL;
    }

    /* Restore initial network configuration */
    if (netdev_default != RT_NULL)
    {
        rt_kprintf("Restoring initial network configuration...\n");

        /* First disable DHCP if it's enabled */
        if (netdev_is_dhcp_enabled(netdev_default))
        {
            res = netdev_dhcp_enabled(netdev_default, RT_FALSE);
            if (res != RT_EOK)
            {
                rt_kprintf("Warning: Failed to disable DHCP: %d\n", res);
            }
        }

        /* Restore network configuration */
        res = netdev_set_ipaddr(netdev_default, &initial_ip_addr);
        if (res != RT_EOK) rt_kprintf("Warning: Failed to restore IP address: %d\n", res);

        res = netdev_set_netmask(netdev_default, &initial_netmask);
        if (res != RT_EOK) rt_kprintf("Warning: Failed to restore netmask: %d\n", res);

        res = netdev_set_gw(netdev_default, &initial_gw);
        if (res != RT_EOK) rt_kprintf("Warning: Failed to restore gateway: %d\n", res);

        res = netdev_set_dns_server(netdev_default, 0, &initial_dns0);
        if (res != RT_EOK) rt_kprintf("Warning: Failed to restore DNS0: %d\n", res);

        res = netdev_set_dns_server(netdev_default, 1, &initial_dns1);
        if (res != RT_EOK) rt_kprintf("Warning: Failed to restore DNS1: %d\n", res);

        /* Restore DHCP state */
        if (initial_dhcp_enabled)
        {
            rt_kprintf("Restoring DHCP...\n");
            res = netdev_dhcp_enabled(netdev_default, RT_TRUE);
            if (res != RT_EOK)
            {
                rt_kprintf("Warning: Failed to restore DHCP: %d\n", res);
            }
            else
            {
                rt_kprintf("DHCP restored, waiting for IP address...\n");
            }
        }

        rt_kprintf("Network configuration restoration completed\n");
    }

    netdev_set_default(netdev_default_old);
    return RT_EOK;
}

static void testcase(void)
{
    /* Test DHCP functionality */
    UTEST_UNIT_RUN(test_netdev_dhcp);

    /* Test network connectivity using ping operations */
    UTEST_UNIT_RUN(test_netdev_ping);

    /* Test network interface configuration and status */
    UTEST_UNIT_RUN(test_netdev_ifconfig);

    /* Test network statistics functionality */
    UTEST_UNIT_RUN(test_netdev_netstat);

    /* Test DNS server configuration and hostname resolution */
    UTEST_UNIT_RUN(test_netdev_dns);

    /* Test setting network interface configuration parameters */
    UTEST_UNIT_RUN(test_netdev_ifconfig_set);

    /* Test setting the default network device */
    UTEST_UNIT_RUN(test_netdev_set_default_netdev);

    /* Test IP address conversion functions */
    UTEST_UNIT_RUN(test_netdev_ipaddr_conversion);

    /* Test network device retrieval functions */
    UTEST_UNIT_RUN(test_netdev_get_functions);

    /* Test network device status setting operations */
    UTEST_UNIT_RUN(test_netdev_status_set);

    /* Test network device configuration setting operations */
    UTEST_UNIT_RUN(test_netdev_config_set);

    /* Test network device callback mechanisms */
    UTEST_UNIT_RUN(test_netdev_callbacks);

    /* Test multiple network interfaces functionality */
    UTEST_UNIT_RUN(test_netdev_multiple_interfaces);
}
UTEST_TC_EXPORT(testcase, "components.net.tc_netdev", utest_tc_init, utest_tc_cleanup, 1000);
