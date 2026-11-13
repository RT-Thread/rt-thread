/* SPDX-License-Identifier: Apache-2.0 */
/* Keep a GLOBAL/FUNC/UND symbol without introducing an import relocation. */
__asm__(".global external_func\n.type external_func, %function\n");

#ifdef ZERO_EXPORTS
int initialized = 7;
#else
int present(void)
{
    return 42;
}
#endif
