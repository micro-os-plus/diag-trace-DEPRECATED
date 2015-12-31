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

#include "diag/trace.h"

#include <cstdio>
#include <cassert>
#include <cstring>

extern "C"
{
  unsigned char traceBuff[1000];
  std::size_t count;

  void
  test ();
}

namespace os
{
  namespace trace
  {
    void
    initialize (void)
    {
      count = 0;
      std::memset (traceBuff, 0, sizeof(traceBuff));
    }

    ssize_t
    write (const char* buf, std::size_t nbyte)
    {
      assert(count + nbyte < sizeof(traceBuff));
      std::memcpy (&traceBuff[count], buf, nbyte);
      count += nbyte;

      return nbyte;
    }
  } /* namespace trace */
} /* namespace os */

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

int
main (int argc, char* argv[])
{
    {
      // C++ API

      os::trace::initialize ();
      assert(count == 0);
      assert(traceBuff[0] == '\0');

      const char msg[] = "Message";
      os::trace::write (msg, 7);
      assert(count == 7);
      assert(traceBuff[0] == 'M');
      assert(traceBuff[6] == 'e');
      assert(traceBuff[7] == '\0');

      os::trace::initialize ();
      os::trace::printf ("format %d", 7);
      assert(count == 8);
      assert(traceBuff[0] == 'f');
      assert(traceBuff[7] == '7');
      assert(traceBuff[8] == '\0');

      os::trace::initialize ();
      os::trace::puts ("Message");
      assert(count == 8);
      assert(traceBuff[0] == 'M');
      assert(traceBuff[7] == '\n');
      assert(traceBuff[8] == '\0');

      os::trace::initialize ();
      os::trace::putchar ('c');
      assert(count == 1);

      assert(traceBuff[0] == 'c');
      assert(traceBuff[1] == '\0');
    }

    {
      // C API
      os::trace::initialize ();
      assert(count == 0);
      assert(traceBuff[0] == '\0');

      const char msg[] = "Message";
      trace_write (msg, 7);
      assert(count == 7);
      assert(traceBuff[0] == 'M');
      assert(traceBuff[6] == 'e');
      assert(traceBuff[7] == '\0');

      os::trace::initialize ();
      trace_printf ("format %d", 7);
      assert(count == 8);
      assert(traceBuff[0] == 'f');
      assert(traceBuff[7] == '7');
      assert(traceBuff[8] == '\0');

      os::trace::initialize ();
      trace_puts ("Message");
      assert(count == 8);
      assert(traceBuff[0] == 'M');
      assert(traceBuff[7] == '\n');
      assert(traceBuff[8] == '\0');

      os::trace::initialize ();
      trace_putchar ('c');
      assert(count == 1);

      assert(traceBuff[0] == 'c');
      assert(traceBuff[1] == '\0');

    }

  test ();

  return 0;
}

#pragma GCC diagnostic pop
