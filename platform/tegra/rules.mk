#
# Copyright (c) 2019, Codefire Solutions. All rights reserved
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files
# (the "Software"), to deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge,
# publish, distribute, sublicense, and/or sell copies of the Software,
# and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

ARCH := arm64
ARM_CPU := armv8-a
WITH_SMP := 1

COMMON_DIR := $(LOCAL_DIR)/common
PLATFORM_SOC_DIR := $(LOCAL_DIR)/$(PLATFORM_SOC)

GLOBAL_INCLUDES += \
	$(COMMON_DIR)/include \
	$(PLATFORM_SOC_DIR)/include

MODULE_SRCS += \
	$(COMMON_DIR)/debug.c \
	$(COMMON_DIR)/platform.c \
	$(COMMON_DIR)/smc.c

include $(PLATFORM_SOC_DIR)/rules.mk

MODULE_DEPS += \
	dev/interrupt/arm_gic \
	dev/timer/arm_generic

GLOBAL_DEFINES += \
	MEMBASE=$(MEMBASE) \
	MEMSIZE=$(MEMSIZE) \
	KERNEL_LOAD_OFFSET=$(KERNEL_LOAD_OFFSET) \
	MMU_WITH_TRAMPOLINE=1

LINKER_SCRIPT += \
	$(BUILDDIR)/system-onesegment.ld

include make/module.mk
