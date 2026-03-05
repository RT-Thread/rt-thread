// -*- mode: C++; c-file-style: "cc-mode" -*-
//*************************************************************************
//
// Code available from: https://verilator.org
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of either the GNU Lesser General Public License Version 3
// or the Perl Artistic License Version 2.0.
// SPDX-FileCopyrightText: 2003-2026 Wilson Snyder
// SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0
//
//*************************************************************************
///
/// \file
/// \brief Verilated/Verilator common implementation for OS portability
///
/// This is compiled as part of other .cpp files to reduce compile time
/// and as such is a .h file rather than .cpp file.
///
//*************************************************************************

#ifndef VL_ALLOW_VERILATEDOS_C
#error "This file should be included only from V3Os.cpp/Verilated.cpp"
#endif

#include "verilatedos.h"

#include <fstream>
#include <sstream>

// clang-format off
#if defined(_WIN32) || defined(__MINGW32__)
# include <windows.h>   // LONG for bcrypt.h on MINGW
# include <processthreadsapi.h>  // GetProcessTimes
# include <psapi.h>   // GetProcessMemoryInfo
#endif

#if defined(__linux)
# include <sched.h>  // For sched_getcpu()
#endif
#if defined(__APPLE__) && !defined(__arm64__) && !defined(__POWERPC__)
# include <cpuid.h>  // For __cpuid_count()
#endif
#if defined(__FreeBSD__)
# include <pthread_np.h>  // For pthread_getaffinity_np()
#endif

#if defined(__APPLE__) && defined(__MACH__)
# include <mach/mach.h>  // For task_info()
#endif
// clang-format on

namespace VlOs {

//=========================================================================
// VlOs::VlGetCpuTime/VlGetWallTime implementation

double DeltaCpuTime::gettime() VL_MT_SAFE {
#if defined(_WIN32) || defined(__MINGW32__)
    FILETIME lpCreationTime, lpExitTime, lpKernelTime, lpUserTime;
    if (0
        != GetProcessTimes(GetCurrentProcess(), &lpCreationTime, &lpExitTime, &lpKernelTime,
                           &lpUserTime)) {
        return static_cast<double>(static_cast<uint64_t>(lpUserTime.dwLowDateTime)
                                   | static_cast<uint64_t>(lpUserTime.dwHighDateTime) << 32ULL)
               * 1e-7;
    }
#else
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
    timespec ts;
    if (0 == clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts))  // MT-Safe  // LCOV_EXCL_BR_LINE
        return ts.tv_sec + ts.tv_nsec * 1e-9;
#endif
    return 0.0;  // LCOV_EXCL_LINE
}
double DeltaWallTime::gettime() VL_MT_SAFE {
#if defined(_WIN32) || defined(__MINGW32__)
    FILETIME ft;  // contains number of 0.1us intervals since the beginning of 1601 UTC.
    GetSystemTimeAsFileTime(&ft);
    const uint64_t tenthus
        = ((static_cast<uint64_t>(ft.dwHighDateTime) << 32) + ft.dwLowDateTime + 5ULL);
    return static_cast<double>(tenthus) * 1e-7;
#else
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
    timespec ts;
    if (0 == clock_gettime(CLOCK_MONOTONIC, &ts))  // MT-Safe  // LCOV_EXCL_BR_LINE
        return ts.tv_sec + ts.tv_nsec * 1e-9;
    return 0.0;  // LCOV_EXCL_LINE
#endif
}

//=============================================================================
// Vlos::getcpu implementation

uint16_t getcpu() VL_MT_SAFE {
#if defined(__linux)
    return sched_getcpu();  // TODO: this is a system call. Not exactly cheap.
#elif defined(__APPLE__) && !defined(__arm64__) && !defined(__POWERPC__)
    uint32_t info[4];
    __cpuid_count(1, 0, info[0], info[1], info[2], info[3]);
    // info[1] is EBX, bits 24-31 are APIC ID
    if ((info[3] & (1 << 9)) == 0) {
        return 0;  // no APIC on chip
    } else {
        return (unsigned)info[1] >> 24;
    }
#elif defined(_WIN32)
    return GetCurrentProcessorNumber();
#else
    return 0;
#endif
}

//=============================================================================
// Vlos::getProcessAvailableParallelism implementation

unsigned getProcessAvailableParallelism() VL_MT_SAFE {
#if defined(__linux) || defined(CPU_ZERO)  // Linux-like; assume we have pthreads etc
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    const int rc = pthread_getaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
    if (rc == 0) {
        unsigned nCpus = 0;
        for (int i = 0; i < CPU_SETSIZE; ++i) {
            if (CPU_ISSET(i, &cpuset)) ++nCpus;
        }
        return nCpus;
    }
#endif
    // Cannot determine
    return 0;
}

//=============================================================================
// Vlos::getProcessDefaultParallelism implementation

unsigned getProcessDefaultParallelism() VL_MT_SAFE {
    const unsigned n = getProcessAvailableParallelism();
    // cppcheck-suppress knownConditionTrueFalse
    return n ? n : std::thread::hardware_concurrency();
}

//=========================================================================
// VlOs::memPeakUsageBytes implementation

void memUsageBytes(uint64_t& peakr, uint64_t& currentr) VL_MT_SAFE {
    peakr = 0;
    currentr = 0;
#if defined(_WIN32) || defined(__MINGW32__)
    const HANDLE process = GetCurrentProcess();
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(process, &pmc, sizeof(pmc))) {
        // The best we can do using simple Windows APIs is to get the size of the working set.
        peakr = pmc.PeakWorkingSetSize;
        currentr = pmc.WorkingSetSize;
    }
#elif defined(__APPLE__) && defined(__MACH__)
    mach_task_basic_info_data_t info;
    mach_msg_type_number_t count = MACH_TASK_BASIC_INFO_COUNT;
    const kern_return_t ret
        = task_info(mach_task_self(), MACH_TASK_BASIC_INFO, (task_info_t)&info, &count);
    if (ret == KERN_SUCCESS && count == MACH_TASK_BASIC_INFO_COUNT) {
        peakr = info.resident_size_max;
        currentr = info.resident_size;
    }
#else
    // Highly unportable. Sorry
    std::ifstream is{"/proc/self/status"};
    if (!is) return;
    std::string line;
    uint64_t vmPeak = 0;
    uint64_t vmRss = 0;
    uint64_t vmSwap = 0;
    std::string field;
    while (std::getline(is, line)) {
        if (line.rfind("VmPeak:", 0) == 0) {
            std::stringstream ss{line};
            ss >> field >> vmPeak;
        } else if (line.rfind("VmRSS:", 0) == 0) {
            std::stringstream ss{line};
            ss >> field >> vmRss;
        } else if (line.rfind("VmSwap:", 0) == 0) {
            std::stringstream ss{line};
            ss >> field >> vmSwap;
        }
    }
    peakr = vmPeak * 1024;
    currentr = (vmRss + vmSwap) * 1024;
#endif
}

//=========================================================================
// VlOs::getenvStr implementation

std::string getenvStr(const std::string& envvar, const std::string& defaultValue) VL_MT_SAFE {
    std::string ret;
#if defined(_MSC_VER)
    // Note: MinGW does not offer _dupenv_s
    const char* envvalue = nullptr;
    _dupenv_s((char**)&envvalue, nullptr, envvar.c_str());
    if (envvalue != nullptr) {
        const std::string result{envvalue};
        free((void*)envvalue);
        ret = result;
    } else {
        ret = defaultValue;
    }
#else
    if (const char* const envvalue = getenv(envvar.c_str())) {
        ret = envvalue;
    } else {
        ret = defaultValue;
    }
#endif
    return ret;
}

//=========================================================================
}  //namespace VlOs
