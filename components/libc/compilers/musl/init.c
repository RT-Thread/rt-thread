extern char **__environ;

#if 0
void __init_libc(char **envp, char *pn)
{
    __environ = envp;
}
#endif

void __libc_exit_fini(void)
{
}

void __libc_start_init(void)
{
}
