/*
 * Copyright (C) 2014 Samsung Electronics
 * Minkyu Kang <mk7.kang@samsung.com>
 * Robert Baldyga <r.baldyga@samsung.com>
 *
 * based on arch/arm/cpu/armv7/omap3/cache.S
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>

#ifndef CONFIG_SYS_DCACHE_OFF

void dcache_enable(void);
void dcache_disable(void);

void enable_caches(void)
{
	dcache_enable();
}

void disable_caches(void)
{
	dcache_disable();
}
#endif
