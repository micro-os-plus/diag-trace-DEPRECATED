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

#if defined(TRACE)

#include "diag/trace.h"
#include <unistd.h>

// ----------------------------------------------------------------------------

void
trace_initialize (void)
{
  ; // For POSIX no inits are required.
}

// ----------------------------------------------------------------------------

ssize_t
trace_write (const char* buf, size_t nbyte)
{
  return write (2, buf, nbyte); // Forward to STDERR.
}

#endif // defined(TRACE)

// ----------------------------------------------------------------------------

