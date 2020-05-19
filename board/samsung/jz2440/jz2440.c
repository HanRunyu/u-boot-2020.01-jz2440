/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002, 2010
 * David Mueller, ELSOFT AG, <d.mueller@elsoft.ch>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <netdev.h>
#include <asm/io.h>
#include <asm/arch/s3c24x0_cpu.h>
#include <asm/mach-types.h>

DECLARE_GLOBAL_DATA_PTR;

#define M_LIMILT	3600
#define U_LIMILT	3600

#define DIVN_UPLL	0
#define HDIVN		2
#define PDIVN		1

#define FCLK_SPEED 1

#if (FCLK_SPEED == 0)		/* Fout = 203MHz, Fin = 12MHz for Audio */
#define M_MDIV	0xC3
#define M_PDIV	0x4
#define M_SDIV	0x1
#elif (FCLK_SPEED == 1)		/* Fout = 400MHz */
#define M_MDIV	0x5C
#define M_PDIV	0x1
#define M_SDIV	0x1
#endif

#define USB_CLOCK 1

#if (USB_CLOCK == 0)
#define U_M_MDIV	0xA1
#define U_M_PDIV	0x3
#define U_M_SDIV	0x1
#elif (USB_CLOCK == 1)		/* Fout = 48MHz*/
#define U_M_MDIV	0x38
#define U_M_PDIV	0x2
#define U_M_SDIV	0x2
#endif

static inline void pll_delay(unsigned long loops)
{
	__asm__ volatile ("1:\n"
	  "subs %0, %1, #1\n"
	  "bne 1b" : "=r" (loops) : "0" (loops));
}

/*
 * Miscellaneous platform dependent initialisations
 */

int board_early_init_f(void)
{
	struct s3c24x0_clock_power * const clk_power =
					s3c24x0_get_base_clock_power();
	struct s3c24x0_gpio * const gpio = s3c24x0_get_base_gpio();

	/* to reduce PLL lock time, adjust the LOCKTIME register */
	writel((U_LIMILT << 16) + M_LIMILT, 
		   &clk_power->locktime);
	/* writel(val,addr)展开相当于： 
	   { 
		   u32 __v=val;
		   asm volatile ("" : : : "memory");	// 内存屏障
		   *(volatile unsigned int *)(addr) = (val);
		   val;
	   }
	*/
	writel((DIVN_UPLL << 3) + (HDIVN << 1) + PDIVN,
		   &clk_power->clkdivn);

	asm volatile (
		"mrc p15,0,r0,c1,c0,0\n"
		"orr r0,r0,#0xc0000000\n"
		"mcr p15,0,r0,c1,c0,0\n"
	);

	/* configure MPLL */
	writel((M_MDIV << 12) + (M_PDIV << 4) + M_SDIV,
	       &clk_power->mpllcon);

	/* some delay between MPLL and UPLL */
	pll_delay(800);

	/* configure UPLL */
	writel((U_M_MDIV << 12) + (U_M_PDIV << 4) + U_M_SDIV,
	       &clk_power->upllcon);

	/* some delay between MPLL and UPLL */
	pll_delay(800);

	/* set up the I/O ports */
	writel(0x007FFFFF, &gpio->gpacon);
	writel(0x00169555, &gpio->gpbcon);
	writel(0x000007FF, &gpio->gpbup);
	writel(0xAAAAAAAA, &gpio->gpccon);
	writel(0x0000FFFF, &gpio->gpcup);
	writel(0xAAAAAAAA, &gpio->gpdcon);
	writel(0x0000FFFF, &gpio->gpdup);
	writel(0xAAAAAAAA, &gpio->gpecon);
	writel(0x0000FFFF, &gpio->gpeup);
	writel(0x00001566, &gpio->gpfcon);
	writel(0x000000FF, &gpio->gpfup);
	writel(0x0296FD95, &gpio->gpgcon);
	writel(0x0000FFFF, &gpio->gpgup);
	writel(0x0015AAA5, &gpio->gphcon);
	writel(0x000007FF, &gpio->gphup);

	return 0;
}

int board_init(void)
{
	// gd->bd->bi_arch_number = MACH_TYPE_JZ2440;

	gd->bd->bi_boot_params = (PHYS_SDRAM_1 + 0x100UL);

	return 0;
}

int dram_init(void)
{
	// gd->ram_size = PHYS_SDRAM_1_SIZE;
	// return 0;
	
	unsigned int i;
	unsigned long addr;

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
		addr = CONFIG_SYS_SDRAM_BASE + (i * SDRAM_BANK_SIZE);
		gd->ram_size += get_ram_size((long *)addr, SDRAM_BANK_SIZE);
	}
	return 0;
}

int dram_init_banksize(void)
{
	unsigned int i;
	unsigned long addr, size;

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
		addr = CONFIG_SYS_SDRAM_BASE + (i * SDRAM_BANK_SIZE);
		size = get_ram_size((long *)addr, SDRAM_BANK_SIZE);

		gd->bd->bi_dram[i].start = addr;
		gd->bd->bi_dram[i].size = size;
	}

	return 0;
}

#ifdef CONFIG_CMD_NET
int board_eth_init(bd_t *bis)
{
	int rc = 0;
#ifdef CONFIG_CS8900
	rc = cs8900_initialize(0, CONFIG_CS8900_BASE);
#elif defined(CONFIG_DRIVER_DM9000)
	rc = dm9000_initialize(bis);
#endif
	return rc;
}
#endif

/*
 * Hardcoded flash setup:
 * Flash 0 is a non-CFI AMD AM29LV800BB flash.
 */
ulong board_flash_get_legacy(ulong base, int banknum, flash_info_t *info)
{
	info->portwidth = FLASH_CFI_16BIT;
	info->chipwidth = FLASH_CFI_BY16;
	info->interface = FLASH_CFI_X16;
	return 1;
}
