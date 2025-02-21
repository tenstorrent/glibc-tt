/* Enumerate available IFUNC implementations of a function.  RISCV version.
   Copyright (C) 2024-2025 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <ifunc-impl-list.h>
#include <string.h>
#include <sys/hwprobe.h>
#include <ldsodefs.h>
#include <asm/hwcap.h>

size_t
__libc_ifunc_impl_list (const char *name, struct libc_ifunc_impl *array,
			size_t max)
{
  size_t i = max;

  bool fast_unaligned = false;
#if defined(HAVE_RISCV_ASM_VECTOR_SUPPORT) 
  bool rvv_ext = false;
#endif

  struct riscv_hwprobe pair = { .key = RISCV_HWPROBE_KEY_CPUPERF_0 };
  if (__riscv_hwprobe (&pair, 1, 0, NULL, 0) == 0
      && (pair.value & RISCV_HWPROBE_MISALIGNED_MASK)
          == RISCV_HWPROBE_MISALIGNED_FAST)
    fast_unaligned = true;

#if defined(HAVE_RISCV_ASM_VECTOR_SUPPORT) 
  if (GLRO(dl_hwcap) & COMPAT_HWCAP_ISA_V) 
    rvv_ext = true;
#endif

  IFUNC_IMPL (i, name, memcpy,
#if defined(HAVE_RISCV_ASM_VECTOR_SUPPORT) 
	      IFUNC_IMPL_ADD (array, i, memcpy, rvv_ext,
			      __memcpy_vector)
#endif
	      IFUNC_IMPL_ADD (array, i, memcpy, fast_unaligned,
			      __memcpy_noalignment)
	      IFUNC_IMPL_ADD (array, i, memcpy, 1, __memcpy_generic))

  return 0;
}
