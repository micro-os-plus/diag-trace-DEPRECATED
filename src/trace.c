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

// ----------------------------------------------------------------------------
#if defined(TRACE)

#include <stdio.h>
#include <stdarg.h>
#include "diag/Trace.h"
#include "string.h"

#ifndef OS_INTEGER_TRACE_PRINTF_TMP_ARRAY_SIZE
#define OS_INTEGER_TRACE_PRINTF_TMP_ARRAY_SIZE (128)
#endif

// ----------------------------------------------------------------------------

int
trace_printf (const char* format, ...)
{
  va_list args;
  va_start(args, format);

  // Caution: allocated on the stack!
  char buf[OS_INTEGER_TRACE_PRINTF_TMP_ARRAY_SIZE];

  // TODO: rewrite it to no longer use newlib, it is way too heavy.

  // Print to the local buffer
  int ret;
  ret = vsnprintf(buf, sizeof(buf), format, args);
  if (ret > 0)
    {
      // Transfer the buffer to the device.
      ret = trace_write (buf, (size_t) ret);
    }

  va_end(args);
  return ret;
}

int
trace_puts (const char *s)
{
  trace_write (s, strlen (s));
  return trace_write ("\n", 1);
}

int
trace_putchar (int c)
{
  trace_write ((const char*) &c, 1);
  return c;
}

void
trace_dump_args (int argc, char* argv[])
{
  trace_printf ("main(argc=%d, argv=[", argc);
  for (int i = 0; i < argc; ++i)
    {
      if (i != 0)
        {
          trace_printf (", ");
        }
      trace_printf ("\"%s\"", argv[i]);
    }
  trace_printf ("]);\n");
}

// ----------------------------------------------------------------------------

#endif // defined(TRACE)
