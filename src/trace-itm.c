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

// ----------------------------------------------------------------------------

void
trace_initialize (void)
{
  ; // For ITM no inits required, the debug registers are set the JTAG software.
}

// ----------------------------------------------------------------------------

#include "cmsis_device.h"

#if defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)

// ITM is the ARM standard mechanism, running over SWD/SWO on Cortex-M3/M4
// devices, and is the recommended setting, if available.
//
// The JLink probe and the GDB server fully support SWD/SWO
// and the JLink Debugging plug-in enables it by default.
// The current OpenOCD does not include support to parse the SWO stream,
// so this configuration will not work on OpenOCD (will not crash, but
// nothing will be displayed in the output console).

#if !defined(OS_INTEGER_TRACE_ITM_STIMULUS_PORT)
#define OS_INTEGER_TRACE_ITM_STIMULUS_PORT     (0)
#endif

ssize_t
trace_write (const char* buf, size_t nbyte)
  {
    for (size_t i = 0; i < nbyte; i++)
      {
        // Check if ITM or the stimulus port are not enabled
        if (((ITM->TCR & ITM_TCR_ITMENA_Msk) == 0)
            || ((ITM->TER & (1UL << OS_INTEGER_TRACE_ITM_STIMULUS_PORT)) == 0))
          {
            return (ssize_t)i; // return the number of sent characters (may be 0)
          }

        // Wait until STIMx is ready...
        while (ITM->PORT[OS_INTEGER_TRACE_ITM_STIMULUS_PORT].u32 == 0)
        ;
        // then send data, one byte at a time
        ITM->PORT[OS_INTEGER_TRACE_ITM_STIMULUS_PORT].u8 = (uint8_t) (*buf++);
      }

    return (ssize_t)nbyte; // all characters successfully sent
  }

#else

#error "ITM available only on ARCH 7M"

#endif // defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)

#endif // defined(TRACE)

// ----------------------------------------------------------------------------

