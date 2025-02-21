ifeq ($(subdir),string)
sysdep_routines += \
  memcpy \
  memcpy-generic \
  memcpy_noalignment \
  # sysdep_routines

ifeq ($(have-gcc-riscv-rvv),yes)
sysdep_routines += \
  memcpy_vector \
  # rvv sysdep_routines
endif

CFLAGS-memcpy_noalignment.c += -mno-strict-align
endif
