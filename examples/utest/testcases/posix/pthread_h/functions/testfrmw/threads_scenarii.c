/*
 * Copyright (c) 2004, Bull S.A..  All rights reserved.
 * Created by: Sebastien Decugis
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * This file is a helper file for the pthread_create tests
 * It defines the following objects:
 * scenarii: array of struct __scenario type.
 * NSCENAR : macro giving the total # of scenarii
 * scenar_init(): function to call before use the scenarii array.
 * scenar_fini(): function to call after end of use of the scenarii array.
 */

static struct __scenario {
    /*
     * Object to hold the given configuration,
     * and which will be used to create the threads
     */
    pthread_attr_t ta;

    /* General parameters */
    /* 0 => joinable; 1 => detached */
    int detached;

    /* Scheduling parameters */
    /*
     * 0 => sched policy is inherited;
     * 1 => sched policy from the attr param
     */
    int explicitsched;
    /* 0 => default; 1=> SCHED_FIFO; 2=> SCHED_RR */
    int schedpolicy;
    /*
     * 0 => default sched param;
     * 1 => max value for sched param;
     * -1 => min value for sched param
     */
    int schedparam;
    /*
     * 0 => default contension scope;
     * 1 => alternative contension scope
     */
    int altscope;

    /* Stack parameters */
    /* 0 => system manages the stack; 1 => stack is provided */
    int altstack;
    /*
     * 0 => default guardsize;
     * 1=> guardsize is 0;
     * 2=> guard is 1 page
     *     -- this setting only affect system stacks (not user's).
     */
    int guard;
    /*
     * 0 => default stack size;
     * 1 => stack size specified (min value)
     *      -- ignored when stack is provided
     */
    int altsize;

    /* Additionnal information */
    /* object description */
    char *descr;
    /* Stores the stack start when an alternate stack is required */
    void *bottom;
    /*
     * This thread creation is expected to:
     * 0 => succeed; 1 => fail; 2 => unknown
     */
    int result;
    /*
     * This semaphore is used to signal the end of
     * the detached threads execution
     */
    sem_t sem;
} scenarii[] =
#define CASE(det, expl, scp, spa, sco, sta, gua, ssi, desc, res)    \
{                                   \
    .detached = det,                        \
    .explicitsched = expl,                      \
    .schedpolicy = scp,                     \
    .schedparam = spa,                      \
    .altscope = sco,                        \
    .altstack = sta,                        \
    .guard = gua,                           \
    .altsize = ssi,                         \
    .descr = desc,                          \
    .bottom = NULL,                         \
    .result = res                           \
}
#define CASE_POS(det, expl, scp, spa, sco, sta, gua, ssi, desc)     \
    CASE(det, expl, scp, spa, sco, sta, gua, ssi, desc, 0)
#define CASE_NEG(det, expl, scp, spa, sco, sta, gua, ssi, desc)     \
    CASE(det, expl, scp, spa, sco, sta, gua, ssi, desc, 1)
#define CASE_UNK(det, expl, scp, spa, sco, sta, gua, ssi, desc)     \
    CASE(det, expl, scp, spa, sco, sta, gua, ssi, desc, 2)
/*
 * This array gives the different combinations of threads
 * attributes for the testcases.
 *
 * Some combinations must be avoided.
 * -> Do not have a detached thread use an alternative stack;
 *     as we don't know when the thread terminates to free the stack memory
 * -> ... (to be completed)
 */
{
    /* Unary tests */
    CASE_POS(0, 0, 0, 0, 0, 0, 0, 0, "default"),
        CASE_POS(1, 0, 0, 0, 0, 0, 0, 0, "detached"),
        CASE_POS(0, 1, 0, 0, 0, 0, 0, 0, "Explicit sched"),
        CASE_UNK(0, 0, 1, 0, 0, 0, 0, 0, "FIFO Policy"),
        CASE_UNK(0, 0, 2, 0, 0, 0, 0, 0, "RR Policy"),
        CASE_UNK(0, 0, 0, 1, 0, 0, 0, 0, "Max sched param"),
        CASE_UNK(0, 0, 0, -1, 0, 0, 0, 0, "Min sched param"),
        CASE_POS(0, 0, 0, 0, 1, 0, 0, 0, "Alternative contension scope"),
        CASE_POS(0, 0, 0, 0, 0, 1, 0, 0, "Alternative stack"),
        CASE_POS(0, 0, 0, 0, 0, 0, 1, 0, "No guard size"),
        CASE_UNK(0, 0, 0, 0, 0, 0, 2, 0, "1p guard size"),
        CASE_POS(0, 0, 0, 0, 0, 0, 0, 1, "Min stack size"),
        /* Stack play */
        CASE_POS(0, 0, 0, 0, 0, 0, 1, 1, "Min stack size, no guard"),
        CASE_UNK(0, 0, 0, 0, 0, 0, 2, 1, "Min stack size, 1p guard"),
        CASE_POS(1, 0, 0, 0, 0, 1, 0, 0, "Detached, Alternative stack"),
        CASE_POS(1, 0, 0, 0, 0, 0, 1, 1,
             "Detached, Min stack size, no guard"), CASE_UNK(1, 0, 0, 0,
                                     0, 0, 2, 1,
                                     "Detached, Min stack size, 1p guard"),
        /*
         * Scheduling play
         *   -- all results are unknown since it might depend on
         *      the user priviledges
         */
CASE_UNK(0, 1, 1, 1, 0, 0, 0, 0, "Explicit FIFO max param"),
        CASE_UNK(0, 1, 2, 1, 0, 0, 0, 0,
                 "Explicit RR max param"),
        CASE_UNK(0, 1, 1, -1, 0, 0, 0, 0,
                 "Explicit FIFO min param"),
        CASE_UNK(0, 1, 2, -1, 0, 0, 0, 0,
                 "Explicit RR min param"),
        CASE_UNK(0, 1, 1, 1, 1, 0, 0, 0,
                 "Explicit FIFO max param, alt scope"),
        CASE_UNK(0, 1, 2, 1, 1, 0, 0, 0,
                 "Explicit RR max param, alt scope"),
        CASE_UNK(0, 1, 1, -1, 1, 0, 0, 0,
                 "Explicit FIFO min param, alt scope"),
        CASE_UNK(0, 1, 2, -1, 1, 0, 0, 0,
                 "Explicit RR min param, alt scope"),
        CASE_UNK(1, 1, 1, 1, 0, 0, 0, 0,
                 "Detached, explicit FIFO max param"),
        CASE_UNK(1, 1, 2, 1, 0, 0, 0, 0,
                 "Detached, explicit RR max param"),
        CASE_UNK(1, 1, 1, -1, 0, 0, 0, 0,
                 "Detached, explicit FIFO min param"),
        CASE_UNK(1, 1, 2, -1, 0, 0, 0, 0,
                 "Detached, explicit RR min param"),
        CASE_UNK(1, 1, 1, 1, 1, 0, 0, 0,
                 "Detached, explicit FIFO max param,"
                 " alt scope"), CASE_UNK(1, 1, 2, 1,
                                     1,
                                     0,
                                     0,
                                     0,
                                     "Detached, explicit RR max param,"
                                     " alt scope"),
        CASE_UNK(1, 1, 1, -1, 1, 0, 0, 0,
                 "Detached, explicit FIFO min param,"
                 " alt scope"), CASE_UNK(1, 1, 2,
                                     -1,
                                     1,
                                     0,
                                     0,
                                     0,
                                     "Detached, explicit RR min param,"
                                     " alt scope"),};

#define NSCENAR (sizeof(scenarii) / sizeof(scenarii[0]))

/*
 * This function will initialize every pthread_attr_t object
 * in the scenarii array
 */
static void scenar_init(void)
{
    int ret = 0;
    unsigned int i;
    int old;
    long pagesize, minstacksize;
    long tsa, tss, tps;

    pagesize = sysconf(_SC_PAGESIZE);
    minstacksize = sysconf(_SC_THREAD_STACK_MIN);
    tsa = sysconf(_SC_THREAD_ATTR_STACKADDR);
    tss = sysconf(_SC_THREAD_ATTR_STACKSIZE);
    tps = sysconf(_SC_THREAD_PRIORITY_SCHEDULING);

#if VERBOSE > 0
    output("System abilities:\n");
    output(" TSA: %li\n", tsa);
    output(" TSS: %li\n", tss);
    output(" TPS: %li\n", tps);
    output(" pagesize: %li\n", pagesize);
    output(" min stack size: %li\n", minstacksize);
#endif

    if (minstacksize % pagesize)
        UNTESTED("The min stack size is not a multiple"
             " of the page size");

    for (i = 0; i < NSCENAR; i++) {
#if VERBOSE > 2
        output("Initializing attribute for scenario %i: %s\n",
               i, scenarii[i].descr);
#endif

        ret = pthread_attr_init(&scenarii[i].ta);
        if (ret != 0)
            UNRESOLVED(ret, "Failed to initialize a"
                   " thread attribute object");

        /* Set the attributes according to the scenario */
        if (scenarii[i].detached == 1) {
            ret = pthread_attr_setdetachstate(&scenarii[i].ta,
                              PTHREAD_CREATE_DETACHED);
            if (ret != 0)
                UNRESOLVED(ret, "Unable to set detachstate");
        } else {
            ret =
                pthread_attr_getdetachstate(&scenarii[i].ta, &old);
            if (ret != 0)
                UNRESOLVED(ret, "Unable to get detachstate"
                       " from initialized attribute");
            if (old != PTHREAD_CREATE_JOINABLE)
                FAILED("The default attribute is not"
                       " PTHREAD_CREATE_JOINABLE");
        }
#if VERBOSE > 4
        output("Detach state was set sucessfully\n");
#endif

        /* Sched related attributes */
        /*
         * This routine is dependent on the Thread Execution
         * Scheduling option
         */
        if (tps > 0) {
            if (scenarii[i].explicitsched == 1)
                ret =
                    pthread_attr_setinheritsched(&scenarii
                                 [i].ta,
                                 PTHREAD_EXPLICIT_SCHED);
            else
                ret =
                    pthread_attr_setinheritsched(&scenarii
                                 [i].ta,
                                 PTHREAD_INHERIT_SCHED);
            if (ret != 0)
                UNRESOLVED(ret, "Unable to set inheritsched"
                       " attribute");
#if VERBOSE > 4
            output("inheritsched state was set sucessfully\n");
#endif
        }
#if VERBOSE > 4
        else
            output("TPS unsupported => inheritsched parameter"
                   " untouched\n");
#endif

        if (tps > 0) {
            if (scenarii[i].schedpolicy == 1)
                ret =
                    pthread_attr_setschedpolicy(&scenarii[i].ta,
                                SCHED_FIFO);
            if (scenarii[i].schedpolicy == 2)
                ret =
                    pthread_attr_setschedpolicy(&scenarii[i].ta,
                                SCHED_RR);
            if (ret != 0)
                UNRESOLVED(ret, "Unable to set the"
                       " sched policy");
#if VERBOSE > 4
            if (scenarii[i].schedpolicy)
                output("Sched policy was set sucessfully\n");
            else
                output("Sched policy untouched\n");
#endif
        }
#if VERBOSE > 4
        else
            output("TPS unsupported => sched policy parameter"
                   " untouched\n");
#endif

        if (scenarii[i].schedparam != 0) {
            struct sched_param sp;

            ret =
                pthread_attr_getschedpolicy(&scenarii[i].ta, &old);
            if (ret != 0)
                UNRESOLVED(ret, "Unable to get sched policy"
                       " from attribute");

            if (scenarii[i].schedparam == 1)
                sp.sched_priority = sched_get_priority_max(old);
            if (scenarii[i].schedparam == -1)
                sp.sched_priority = sched_get_priority_min(old);

            ret = pthread_attr_setschedparam(&scenarii[i].ta, &sp);
            if (ret != 0)
                UNRESOLVED(ret,
                       "Failed to set the sched param");

#if VERBOSE > 4
            output("Sched param was set sucessfully to %i\n",
                   sp.sched_priority);
        } else {
            output("Sched param untouched\n");
#endif
        }

        if (tps > 0) {
            ret = pthread_attr_getscope(&scenarii[i].ta, &old);
            if (ret != 0)
                UNRESOLVED(ret, "Failed to get contension"
                       " scope from thread attribute");

            if (scenarii[i].altscope != 0) {
                if (old == PTHREAD_SCOPE_PROCESS)
                    old = PTHREAD_SCOPE_SYSTEM;
                else
                    old = PTHREAD_SCOPE_PROCESS;

                ret =
                    pthread_attr_setscope(&scenarii[i].ta, old);

#if VERBOSE > 0
                if (ret != 0)
                    output("WARNING: The TPS option is"
                           " claimed to be supported but"
                           " setscope fails\n");
#endif

#if VERBOSE > 4
                output("Contension scope set to %s\n",
                       old == PTHREAD_SCOPE_PROCESS ?
                       "PTHREAD_SCOPE_PROCESS" :
                       "PTHREAD_SCOPE_SYSTEM");
            } else {
                output("Contension scope untouched (%s)\n",
                       old == PTHREAD_SCOPE_PROCESS ?
                       "PTHREAD_SCOPE_PROCESS" :
                       "PTHREAD_SCOPE_SYSTEM");
#endif
            }
        }
#if VERBOSE > 4
        else
            output("TPS unsupported => sched contension scope"
                   " parameter untouched\n");
#endif

        /* Stack related attributes */
        /*
         * This routine is dependent on the Thread Stack Address
         * Attribute and Thread Stack Size Attribute options
         */
        if ((tss > 0) && (tsa > 0)) {
            if (scenarii[i].altstack != 0) {
                /*
                 * This is slightly more complicated.
                 * We need to alloc a new stackand free
                 * it upon test termination.
                 * We will alloc with a simulated guardsize
                 * of 1 pagesize */
                scenarii[i].bottom = malloc(minstacksize + pagesize);
                if (scenarii[i].bottom == NULL)
                    UNRESOLVED(errno, "Unable to alloc"
                           " enough memory for"
                           " alternative stack");

                ret = pthread_attr_setstack(&scenarii[i].ta,
                                scenarii[i].bottom,
                                minstacksize);
                if (ret != 0)
                    UNRESOLVED(ret, "Failed to specify"
                           " alternate stack");

#if VERBOSE > 1
                output("Alternate stack created successfully."
                       " Bottom=%p, Size=%i\n",
                       scenarii[i].bottom, minstacksize);
#endif
            }
        }
#if VERBOSE > 4
        else
            output("TSA or TSS unsupported => "
                   "No alternative stack\n");
#endif

#ifndef WITHOUT_XOPEN
        if (scenarii[i].guard != 0) {
            if (scenarii[i].guard == 1)
                ret =
                    pthread_attr_setguardsize(&scenarii[i].ta,
                                  0);
            if (scenarii[i].guard == 2)
                ret =
                    pthread_attr_setguardsize(&scenarii[i].ta,
                                  pagesize);
            if (ret != 0)
                UNRESOLVED(ret, "Unable to set guard area"
                       " size in thread stack");
#if VERBOSE > 4
            output("Guard size set to %i\n",
                   scenarii[i].guard == 1 ? 1 : pagesize);
#endif
        }
#endif

        if (tss > 0) {
            if (scenarii[i].altsize != 0) {
                ret = pthread_attr_setstacksize(&scenarii[i].ta,
                                minstacksize);
                if (ret != 0)
                    UNRESOLVED(ret, "Unable to change"
                           " stack size");
#if VERBOSE > 4
                output("Stack size set to %i (this is the "
                       "min)\n", minstacksize);
#endif
            }
        }
#if VERBOSE > 4
        else
            output("TSS unsupported => stack size unchanged\n");
#endif

        ret = sem_init(&scenarii[i].sem, 0, 0);
        if (ret == -1)
            UNRESOLVED(errno, "Unable to init a semaphore");

    }
#if VERBOSE > 0
    output("All %i thread attribute objects were initialized\n\n", NSCENAR);
#endif
}

/*
 * This function will free all resources consumed
 * in the scenar_init() routine
 */
static void scenar_fini(void)
{
    int ret = 0;
    unsigned int i;

    for (i = 0; i < NSCENAR; i++) {
        if (scenarii[i].bottom != NULL)
            free(scenarii[i].bottom);

        ret = sem_destroy(&scenarii[i].sem);
        if (ret == -1)
            UNRESOLVED(errno, "Unable to destroy a semaphore");

        ret = pthread_attr_destroy(&scenarii[i].ta);
        if (ret != 0)
            UNRESOLVED(ret, "Failed to destroy a thread"
                   " attribute object");
    }
}

static unsigned int sc;

#ifdef STD_MAIN

static void *threaded(void *arg);

int main(void)
{
    int ret = 0;
    pthread_t child;

    output_init();
    scenar_init();

    for (sc = 0; sc < NSCENAR; sc++) {
#if VERBOSE > 0
        output("-----\n");
        output("Starting test with scenario (%i): %s\n",
               sc, scenarii[sc].descr);
#endif

        ret = pthread_create(&child, &scenarii[sc].ta, threaded, NULL);
        switch (scenarii[sc].result) {
        case 0: /* Operation was expected to succeed */
            if (ret != 0)
                UNRESOLVED(ret, "Failed to create this thread");
            break;
        case 1: /* Operation was expected to fail */
            if (ret == 0)
                UNRESOLVED(-1, "An error was expected but the"
                       " thread creation succeeded");
            break;
        case 2: /* We did not know the expected result */
        default:
#if VERBOSE > 0
            if (ret == 0)
                output("Thread has been created successfully"
                       " for this scenario\n");
            else
                output("Thread creation failed with the error:"
                       " %s\n", strerror(ret));
#endif
        }
        if (ret == 0) {
            if (scenarii[sc].detached == 0) {
                ret = pthread_join(child, NULL);
                if (ret != 0)
                    UNRESOLVED(ret, "Unable to join a"
                           " thread");
            } else {
                /* Just wait for the thread to terminate */
                do {
                    ret = sem_wait(&scenarii[sc].sem);
                } while ((ret == -1) && (errno == EINTR));
                if (ret == -1)
                    UNRESOLVED(errno, "Failed to wait for"
                           " the semaphore");
            }
        }
    }

    scenar_fini();
#if VERBOSE > 0
    output("-----\n");
    output("All test data destroyed\n");
    output("Test PASSED\n");
#endif

    PASSED;
}
#endif
