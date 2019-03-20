/*
 * Copyright (c) 2008 Travis Geiselbrecht
 * Copyright (c) 2012, NVIDIA CORPORATION. All rights reserved
 * Copyright (c) 2015 Google Inc. All rights reserved
 * Copyright (c) 2019 Rashed Abdel-Tawab
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
#include <stdarg.h>
#include <reg.h>
#include <debug.h>
#include <printf.h>
#include <kernel/thread.h>
#include <platform/debug.h>
#include <platform/tegra_debug.h>
#include <arch/ops.h>
#include <platform/memmap.h>

#define TEGRA_UART_NONE	0x0

static unsigned long uart_base[] = {
	TEGRA_UART_NONE,
	TEGRA_UARTA_BASE,
	TEGRA_UARTB_BASE,
	TEGRA_UARTC_BASE,
	TEGRA_UARTD_BASE,
	TEGRA_UARTE_BASE,
	TEGRA_UARTF_BASE,
	TEGRA_UARTG_BASE
};

static unsigned int debug_port;

#define UART_RHR	0
#define UART_THR	0
#define UART_LSR	5

static inline void write_uart_reg(int port, uint reg, unsigned char data)
{
	*(volatile unsigned char *)(uart_base[port] + (reg << 2)) = data;
}

static inline unsigned char read_uart_reg(int port, uint reg)
{
	return *(volatile unsigned char *)(uart_base[port] + (reg << 2));
}

static int uart_putc(int port, char c )
{
	while (!(read_uart_reg(port, UART_LSR) & (1<<6)))
		;
	write_uart_reg(port, UART_THR, c);
	return 0;
}

int uart_getc(int port, bool wait)
{
	if (wait) {
		while (!(read_uart_reg(port, UART_LSR) & (1<<0)))
			;
	} else {
		if (!(read_uart_reg(port, UART_LSR) & (1<<0)))
			return -1;
	}
	return read_uart_reg(port, UART_RHR);
}

void platform_dputc(char c)
{
	if (debug_port == TEGRA_UART_NONE)
		return;

	if (c == '\n') {
		uart_putc(debug_port, '\r');
	} else if (c == '\0') {
		return;
	}
	uart_putc(debug_port, c);
}

int platform_dgetc(char *c, bool wait)
{
	int _c;

	if (debug_port == TEGRA_UART_NONE)
		return -1;

	if ((_c = uart_getc(debug_port, false)) < 0)
		return -1;

	*c = _c;
	return 0;
}

void platform_init_debug_port(unsigned int dbg_port)
{
	debug_port = dbg_port;
}
