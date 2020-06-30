/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 * Gary Jennejohn <garyj@denx.de>
 * David Mueller <d.mueller@elsoft.ch>
 *
 * Configuation settings for the SAMSUNG SMDK2410 board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * High Level Configuration Options
 * (easy to change)
 */
#define CONFIG_SYS_ARM_CACHE_WRITETHROUGH

// MACH_TYPE_S3C2440 = 362
#define CONFIG_MACH_TYPE	MACH_TYPE_S3C2440

/* input clock of PLL (the JZ2440 has 12MHz input clock) */
#define CONFIG_SYS_CLK_FREQ	12000000

#define CONFIG_CMDLINE_TAG	/* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG

/*
 * Hardware drivers
 */
#define CONFIG_DRIVER_DM9000	/* we have a CS8900 on-board */
#define CONFIG_DM9000_BASE	0x20000000
#define DM9000_IO			0x20000000
#define DM9000_DATA			0x20000004
#define CONFIG_CS8900_BUS16	/* the Linux driver does accesses as shorts */

/*
 * select serial console configuration
 */
// #define CONFIG_S3C24X0_SERIAL
// #define CONFIG_SERIAL1		1	/* we use SERIAL 1 on SMDK2410 */

/************************************************************
 * USB support (currently only works with D-cache off)
 ************************************************************/
// #define CONFIG_USB_OHCI
// #define CONFIG_USB_OHCI_S3C24XX		1
// #define CONFIG_DOS_PARTITION

/************************************************************
 * RTC
 ************************************************************/
// #define CONFIG_RTC_S3C24X0

// #define CONFIG_BAUDRATE		115200

/*
 * BOOTP options
 */
#define CONFIG_BOOTP_BOOTFILESIZE
// #define CONFIG_BOOTP_BOOTPATH
// #define CONFIG_BOOTP_GATEWAY
// #define CONFIG_BOOTP_HOSTNAME

/*
 * Command line configuration.
 */
// #define CONFIG_CMD_BSP
// #define CONFIG_CMD_DATE
// #define CONFIG_LIB_DATE
// #define CONFIG_CMD_NAND

// #define CONFIG_CMDLINE_EDITING

/* autoboot */
#define CONFIG_BOOT_RETRY_TIME	-1
#define CONFIG_RESET_TO_RETRY

#define CONFIG_NETMASK		255.255.0.0
#define CONFIG_IPADDR		169.254.35.45
#define CONFIG_SERVERIP		169.254.35.49

#if defined(CONFIG_CMD_KGDB)
#define CONFIG_KGDB_BAUDRATE	115200	/* speed to run kgdb serial port */
#endif

/*
 * Miscellaneous configurable options
 */
// #define CONFIG_SYS_LONGHELP		/* undef to save memory */
#define CONFIG_SYS_CBSIZE	256
/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE	(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT)+16)
#define CONFIG_SYS_MAXARGS	16
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE

#define CONFIG_SYS_MEMTEST_START	0x30000000	/* memtest works on */
#define CONFIG_SYS_MEMTEST_END		0x33F00000	/* 63 MB in DRAM */

#define CONFIG_SYS_LOAD_ADDR		0x30000000

/* support additional compression methods */
#define CONFIG_BZIP2
// #define CONFIG_LZO
//#define CONFIG_LZMA

/*-----------------------------------------------------------------------
 * Physical Memory Map
 */
#define CONFIG_SYS_SDRAM_BASE	0x30000000
#define SDRAM_BANK_SIZE			0x08000000
#define PHYS_SDRAM_1			CONFIG_SYS_SDRAM_BASE /* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE		0x04000000 /* 64 MB */

#define CONFIG_SYS_FLASH_BASE	0x00000000
#define PHYS_FLASH_1			CONFIG_SYS_FLASH_BASE /* Flash Bank #0 */

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */

#define CONFIG_SYS_FLASH_CFI
#define CONFIG_FLASH_CFI_DRIVER
#define CONFIG_FLASH_CFI_LEGACY
#define CONFIG_SYS_FLASH_LEGACY_512Kx16
#define CONFIG_FLASH_SHOW_PROGRESS	45

#define CONFIG_SYS_MAX_FLASH_BANKS	1
#define CONFIG_SYS_FLASH_BANKS_LIST     { CONFIG_SYS_FLASH_BASE }
#define CONFIG_SYS_MAX_FLASH_SECT	(128)

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

/*
 * Size of malloc() pool
 * BZIP2 / LZO / LZMA need a lot of RAM
 */
#define CONFIG_SYS_MALLOC_LEN	(4 * 1024 * 1024)
#define CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_FLASH_BASE
#define CONFIG_SYS_MONITOR_LEN	(600 * 1024)


/*
 * NAND configuration
 */
// #define CONFIG_SYS_S3C2440_NAND_HWECC
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE		0x4E000000

/*
 * File system
 */
// #define CONFIG_CMD_UBIFS
/* #define CONFIG_CMD_MTDPARTS		 "mtdparts=jz2440-0:512k(u-boot),"   \
                            	 "256k(params),"     \
                            	 "4m(kernel),"   \
                            	 "-(rootfs)"  
*/
// #define CONFIG_YAFFS2
// #define CONFIG_RBTREE

/* additions for new relocation code, must be added to all boards */
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_SDRAM_BASE + 0x1000)

// #define CONFIG_BOARD_EARLY_INIT_F

#endif /* __CONFIG_H */
