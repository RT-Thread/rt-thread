// -*- mode: C++; c-file-style: "cc-mode" -*-
//=============================================================================
//
// Code available from: https://verilator.org
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of either the GNU Lesser General Public License Version 3
// or the Perl Artistic License Version 2.0.
// SPDX-FileCopyrightText: 2001-2026 Wilson Snyder
// SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0
//
//=============================================================================
///
/// \file
/// \brief Verilated save/restore implementation code
///
/// This file must be compiled and linked against all Verilated objects
/// that use --savable.
///
/// Use "verilator --savable" to add this to the Makefile for the linker.
///
//=============================================================================

#define VERILATOR_VERILATED_SAVE_CPP_

#include "verilatedos.h"

#include "verilated_save.h"

#include "verilated.h"
#include "verilated_imp.h"

#include <cerrno>
#include <fcntl.h>

// clang-format off
#if defined(_WIN32) && !defined(__MINGW32__) && !defined(__CYGWIN__)
# include <io.h>
#else
# include <unistd.h>
#endif

#ifndef O_LARGEFILE  // WIN32 headers omit this
# define O_LARGEFILE 0
#endif
#ifndef O_NONBLOCK  // WIN32 headers omit this
# define O_NONBLOCK 0
#endif
#ifndef O_CLOEXEC  // WIN32 headers omit this
# define O_CLOEXEC 0
#endif
// clang-format on

// CONSTANTS
// Value of first bytes of each file (must be multiple of 8 bytes)
static const char* const VLTSAVE_HEADER_STR = "verilatorsave02\n";
// Value of last bytes of each file (must be multiple of 8 bytes)
static const char* const VLTSAVE_TRAILER_STR = "vltsaved";

//=============================================================================
//=============================================================================
//=============================================================================
// Serialization

bool VerilatedDeserialize::readDiffers(const void* __restrict datap,
                                       size_t size) VL_MT_UNSAFE_ONE {
    bufferCheck();
    const uint8_t* __restrict dp = static_cast<const uint8_t* __restrict>(datap);
    uint8_t miss = 0;
    while (size--) miss |= (*dp++ ^ *m_cp++);
    return (miss != 0);
}

VerilatedDeserialize& VerilatedDeserialize::readAssert(const void* __restrict datap,
                                                       size_t size) VL_MT_UNSAFE_ONE {
    if (VL_UNLIKELY(readDiffers(datap, size))) {
        const std::string fn = filename();
        const std::string msg
            = "Can't deserialize save-restore file as was made from different model: "
              + filename();
        VL_FATAL_MT(fn.c_str(), 0, "", msg.c_str());
        // Die before we close() as close would infinite loop
    }
    return *this;  // For function chaining
}

void VerilatedSerialize::header() VL_MT_UNSAFE_ONE {
    VerilatedSerialize& os = *this;  // So can cut and paste standard << code below
    assert((std::strlen(VLTSAVE_HEADER_STR) & 7) == 0);  // Keep aligned
    os.write(VLTSAVE_HEADER_STR, std::strlen(VLTSAVE_HEADER_STR));
}

void VerilatedDeserialize::header() VL_MT_UNSAFE_ONE {
    VerilatedDeserialize& os = *this;  // So can cut and paste standard >> code below
    if (VL_UNLIKELY(os.readDiffers(VLTSAVE_HEADER_STR, std::strlen(VLTSAVE_HEADER_STR)))) {
        const std::string fn = filename();
        const std::string msg
            = "Can't deserialize; file has wrong header signature, or file not found: "s
              + filename();
        VL_FATAL_MT(fn.c_str(), 0, "", msg.c_str());
        // Die before we close() as close would infinite loop
    }
}

void VerilatedSerialize::trailer() VL_MT_UNSAFE_ONE {
    VerilatedSerialize& os = *this;  // So can cut and paste standard << code below
    assert((std::strlen(VLTSAVE_TRAILER_STR) & 7) == 0);  // Keep aligned
    os.write(VLTSAVE_TRAILER_STR, std::strlen(VLTSAVE_TRAILER_STR));
}

void VerilatedDeserialize::trailer() VL_MT_UNSAFE_ONE {
    VerilatedDeserialize& os = *this;  // So can cut and paste standard >> code below
    if (VL_UNLIKELY(os.readDiffers(VLTSAVE_TRAILER_STR, std::strlen(VLTSAVE_TRAILER_STR)))) {
        const std::string fn = filename();
        const std::string msg
            = "Can't deserialize; file has wrong end-of-file signature: "s + filename();
        VL_FATAL_MT(fn.c_str(), 0, "", msg.c_str());
        // Die before we close() as close would infinite loop
    }
}

//=============================================================================
//=============================================================================
//=============================================================================
// Opening/Closing

void VerilatedSave::open(const char* filenamep) VL_MT_UNSAFE_ONE {
    m_assertOne.check();
    if (isOpen()) return;
    VL_DEBUG_IF(VL_DBG_MSGF("- save: opening save file %s\n", filenamep););

    if (VL_UNCOVERABLE(filenamep[0] == '|')) {
        assert(0);  // LCOV_EXCL_LINE // Not supported yet.
    } else {
        // cppcheck-suppress duplicateExpression
        m_fd = ::open(filenamep,
                      O_CREAT | O_WRONLY | O_TRUNC | O_LARGEFILE | O_NONBLOCK | O_CLOEXEC, 0666);
        if (VL_UNLIKELY(m_fd < 0)) {
            // User code can check isOpen()
            m_isOpen = false;
            return;
        }
    }
    m_isOpen = true;
    m_filename = filenamep;
    m_cp = m_bufp;
    header();
}

void VerilatedRestore::open(const char* filenamep) VL_MT_UNSAFE_ONE {
    m_assertOne.check();
    if (isOpen()) return;
    VL_DEBUG_IF(VL_DBG_MSGF("- restore: opening restore file %s\n", filenamep););

    if (VL_UNCOVERABLE(filenamep[0] == '|')) {
        assert(0);  // LCOV_EXCL_LINE // Not supported yet.
    } else {
        // cppcheck-suppress duplicateExpression
        m_fd = ::open(filenamep, O_CREAT | O_RDONLY | O_LARGEFILE | O_CLOEXEC, 0666);
        if (VL_UNLIKELY(m_fd < 0)) {
            // User code can check isOpen()
            m_isOpen = false;
            return;
        }
    }
    m_isOpen = true;
    m_filename = filenamep;
    m_cp = m_bufp;
    m_endp = m_bufp;
    header();
}

void VerilatedSave::closeImp() VL_MT_UNSAFE_ONE {
    if (!isOpen()) return;
    trailer();
    flushImp();
    m_isOpen = false;
    ::close(m_fd);  // May get error, just ignore it
}

void VerilatedRestore::closeImp() VL_MT_UNSAFE_ONE {
    if (!isOpen()) return;
    trailer();
    flushImp();
    m_isOpen = false;
    ::close(m_fd);  // May get error, just ignore it
}

//=============================================================================
// Buffer management

void VerilatedSave::flushImp() VL_MT_UNSAFE_ONE {
    m_assertOne.check();
    if (VL_UNLIKELY(!isOpen())) return;
    const uint8_t* wp = m_bufp;
    while (true) {
        const ssize_t remaining = (m_cp - wp);
        if (remaining == 0) break;
        errno = 0;
        const ssize_t got = ::write(m_fd, wp, remaining);
        if (got > 0) {
            wp += got;
        } else if (VL_UNCOVERABLE(got < 0)) {
            if (VL_UNCOVERABLE(errno != EAGAIN && errno != EINTR)) {
                // LCOV_EXCL_START
                // write failed, presume error (perhaps out of disk space)
                const std::string msg = std::string{__FUNCTION__} + ": " + std::strerror(errno);
                VL_FATAL_MT("", 0, "", msg.c_str());
                close();
                break;
                // LCOV_EXCL_STOP
            }
        }
    }
    m_cp = m_bufp;  // Reset buffer
}

void VerilatedRestore::fill() VL_MT_UNSAFE_ONE {
    m_assertOne.check();
    if (VL_UNLIKELY(!isOpen())) return;
    // Move remaining characters down to start of buffer.  (No memcpy, overlaps allowed)
    uint8_t* rp = m_bufp;
    for (const uint8_t* sp = m_cp; sp < m_endp; *rp++ = *sp++) {}  // Overlaps
    m_endp = m_bufp + (m_endp - m_cp);
    m_cp = m_bufp;  // Reset buffer
    // Read into buffer starting at m_endp
    while (true) {
        const ssize_t remaining = (m_bufp + bufferSize() - m_endp);
        if (remaining == 0) break;
        errno = 0;
        const ssize_t got = ::read(m_fd, m_endp, remaining);
        if (got > 0) {
            m_endp += got;
        } else if (VL_UNCOVERABLE(got < 0)) {
            if (VL_UNCOVERABLE(errno != EAGAIN && errno != EINTR)) {
                // LCOV_EXCL_START
                // write failed, presume error (perhaps out of disk space)
                const std::string msg = std::string{__FUNCTION__} + ": " + std::strerror(errno);
                VL_FATAL_MT("", 0, "", msg.c_str());
                close();
                break;
                // LCOV_EXCL_STOP
            }
        } else {  // got==0, EOF
            // Fill buffer from here to end with NULLs so reader's don't
            // need to check eof each character.
            while (m_endp < m_bufp + bufferSize()) *m_endp++ = '\0';
            break;
        }
    }
}

//=============================================================================
// Serialization of types

VerilatedSerialize& operator<<(VerilatedSerialize& os, VerilatedContext* rhsp) {
    os.write(rhsp->serialized1Ptr(), rhsp->serialized1Size());
    os << rhsp->impp()->timeFormatSuffix();
    os << rhsp->dumpfile();
    return os;
}
VerilatedDeserialize& operator>>(VerilatedDeserialize& os, VerilatedContext* rhsp) {
    os.read(rhsp->serialized1Ptr(), rhsp->serialized1Size());
    std::string s;
    os >> s;
    rhsp->impp()->timeFormatSuffix(s);
    os >> s;
    rhsp->dumpfile(s);
    return os;
}
