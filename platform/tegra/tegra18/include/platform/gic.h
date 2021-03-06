/*
 * Copyright (c) 2015 Google Inc. All rights reserved
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef __PLATFORM_GIC_H
#define __PLATFORM_GIC_H

#define MAX_INT 1020
#if ARCH_ARM64
#define GIC_BASE_VIRT 0xffffffff03880000
#else
#define GIC_BASE_VIRT 0x03880000
#endif
#define GICBASE(b) (GIC_BASE_VIRT)

#define GICC_SIZE (0x2000)
#define GICD_SIZE (0x1000)
#define GICH_SIZE (0x2000)
#define GICV_SIZE (0x2000)

#define GICC_OFFSET (0x2000)
#define GICD_OFFSET (0x1000)
#define GICH_OFFSET (0x4000)
#define GICV_OFFSET (0x6000)

#define GICC_BASE_VIRT (GIC_BASE_VIRT + GICC_OFFSET)
#define GICD_BASE_VIRT (GIC_BASE_VIRT + GICD_OFFSET)
#define GICH_BASE_VIRT (GIC_BASE_VIRT + GICH_OFFSET)
#define GICV_BASE_VIRT (GIC_BASE_VIRT + GICV_OFFSET)

#endif
