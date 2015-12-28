/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2015 Liviu Ionescu.
 *
 * µOS++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, version 3.
 *
 * µOS++ is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DIAG_TRACE_H_
#define DIAG_TRACE_H_

// ----------------------------------------------------------------------------

#include <stdint.h>
#include <sys/types.h>

// ----------------------------------------------------------------------------

// The trace device is an independent output channel, intended for diagnostic
// purposes.
//
// The API is simple, and mimics the standard output calls:
// - trace_printf()
// - trace_puts()
// - trace_putchar();
//
// The implementation is done in
// - trace_write()
//
// Trace support is enabled by adding the TRACE definition.
//
// When TRACE is not defined, all functions are inlined to empty bodies.
// This has the advantage that the trace call do not need to be conditionally
// compiled with #ifdef TRACE/#endif

#if defined(TRACE)

#if defined(__cplusplus)
extern "C"
{
#endif

  // ----- Implementation -----
  // These two functions must be implemented for a specific trace channel.

  void
  trace_initialize (void);

  ssize_t
  trace_write (const char* buf, size_t nbyte);

  // ----- Portable -----

  int
  trace_printf (const char* format, ...);

  int
  trace_puts (const char* s);

  int
  trace_putchar (int c);

  void
  trace_dump_args (int argc, char* argv[]);

#if defined(__cplusplus)
}
#endif

#else // !defined(TRACE)

#if defined(__cplusplus)
extern "C"
  {
#endif

    inline void
    trace_initialize (void);

    // Implementation dependent
    inline ssize_t
    trace_write (const char* buf, size_t nbyte);

    inline int
    trace_printf (const char* format, ...);

    inline int
    trace_puts (const char* s);

    inline int
    trace_putchar (int c);

    inline void
    trace_dump_args (int argc, char* argv[]);

#if defined(__cplusplus)
  }
#endif

inline void
__attribute__((always_inline))
trace_initialize (void)
  {
  }

// Empty definitions when trace is not defined

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

inline ssize_t
__attribute__((always_inline))
trace_write (const char* buf, size_t nbyte)
  {
    return 0;
  }

inline int
__attribute__((always_inline))
trace_printf (const char* format, ...)
  {
    return 0;
  }

inline int
__attribute__((always_inline))
trace_puts (const char* s)
  {
    return 0;
  }

inline int
__attribute__((always_inline))
trace_putchar (int c)
  {
    return c;
  }

inline void
__attribute__((always_inline))
trace_dump_args (int argc, char* argv[])
  {
  }

#endif // defined(TRACE)

// ----------------------------------------------------------------------------

#endif // DIAG_TRACE_H_
