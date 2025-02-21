/* memcpy for RISC-V Vector.
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


#include <sysdep.h>
#include <sys/asm.h>

ENTRY (__memcpy_vector) 
.option push
.option arch, +v
    mv	    a6, a0
L(loop):
    vsetvli a3,a2,e8,m8,ta,ma
    vle8.v  v8,(a1)
    vse8.v  v8,(a6)
    add     a1,a1,a3
    sub     a2,a2,a3 
    add     a6,a6,a3 
    bnez    a2,L(loop)  
    ret
.option pop
END (__memcpy_vector)
