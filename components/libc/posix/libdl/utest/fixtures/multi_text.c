/* SPDX-License-Identifier: Apache-2.0 */
__attribute__((section(".text.first"))) int first(void)
{
    return 11;
}

__attribute__((section(".text.second"))) int second(void)
{
    return 22;
}
