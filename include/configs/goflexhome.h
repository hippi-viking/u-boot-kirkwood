/*
 * Copyright (C) 2014-2017 bodhi <mibodhi@gmail.com>
 * Based on 
 *
 * Copyright (C) 2013 Suriyan Ramasami <suriyan.r@gmail.com>
 *
 * Based on dockstar.h originally written by
 * Copyright (C) 2010  Eric C. Cooper <ecc@cmu.edu>
 *
 * Based on sheevaplug.h originally written by
 * Prafulla Wadaskar <prafulla@marvell.com>
 * (C) Copyright 2009
 * Marvell Semiconductor <www.marvell.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _CONFIG_GOFLEXHOME_H
#define _CONFIG_GOFLEXHOME_H

/*
 * High Level Configuration Options (easy to change)
 */
#define CONFIG_FEROCEON_88FR131	1	/* CPU Core subversion */
#define CONFIG_KW88F6281	1	/* SOC Name */
#define CONFIG_MACH_GOFLEXHOME		/* Machine type */
#define CONFIG_SKIP_LOWLEVEL_INIT	/* disable board lowlevel_init */

/*
 * Default GPIO configuration and LED status
 */
#define GOFLEXHOME_OE_LOW               (~(0))
#define GOFLEXHOME_OE_HIGH              (~(0))
#define GOFLEXHOME_OE_VAL_LOW           (1 << 29)       /* USB_PWEN low */
#define GOFLEXHOME_OE_VAL_HIGH          (1 << 17)       /* LED pin high */

/* PHY related */
#define MV88E1116_LED_FCTRL_REG         10
#define MV88E1116_CPRSP_CR3_REG         21
#define MV88E1116_MAC_CTRL_REG          21
#define MV88E1116_PGADR_REG             22
#define MV88E1116_RGMII_TXTM_CTRL       (1 << 4)
#define MV88E1116_RGMII_RXTM_CTRL       (1 << 5)

/*
 * Commands configuration
 */
#define CONFIG_CMD_NAND
#define CONFIG_SYS_MVFS         /* Picks up Filesystem from mv-common.h */
#define CONFIG_SYS_LONGHELP
#define CONFIG_PREBOOT 
#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2 "> "

/*
 * mv-common.h should be defined after CMD configs since it used them
 * to enable certain macros
 */
#include "mv-common.h"

/*
 *  Environment variables configurations
 */
#ifdef CONFIG_CMD_NAND
#define CONFIG_ENV_IS_IN_NAND		1
#define CONFIG_ENV_SECT_SIZE		0x20000	/* 128K */
#else
#define CONFIG_ENV_IS_NOWHERE		1	/* if env in SDRAM */
#endif
/*
 * max 4k env size is enough, but in case of nand
 * it has to be rounded to sector size
 */
#define CONFIG_ENV_SIZE			0x20000	/* 128k */
#define CONFIG_ENV_ADDR			0xC0000
#define CONFIG_ENV_OFFSET		0xC0000	/* env starts here */

/*
 * Default environment variables
 */

#define CONFIG_BOOTCOMMAND \
	"run bootcmd_uenv; run bootcmd_usb; reset"

#define CONFIG_EXTRA_ENV_SETTINGS \
	"arcNumber=3338\0" \
	"bootcmd_exec=run load_uimage; if run load_initrd; then if run load_dtb; then bootm $load_uimage_addr $load_initrd_addr $load_dtb_addr; else bootm $load_uimage_addr $load_initrd_addr; fi; else if run load_dtb; then bootm $load_uimage_addr - $load_dtb_addr; else bootm$load_uimage_addr; fi; fi\0" \
	"bootcmd=run bootcmd_uenv; run scan_disk; run set_bootargs; run bootcmd_exec; reset\0" \
	"bootcmd_uenv=run uenv_load; if test $uenv_loaded -eq 1; then run uenv_import; fi\0" \
	"bootdelay=10\0" \
	"bootdev=usb\0" \
        "console=console=ttyS0,115200\0" \
	"device=0:1\0" \
	"devices=usb ide\0" \
	"disks=0 1 2 3\0" \
	"ethact=egiga0\0" \
	"ethaddr=52:3b:20:9c:11:51\0" \
	"if_netconsole=ping $serverip\0" \
	"ipaddr=192.168.0.231\0" \
	"led_error=orange blinking\0" \
	"led_exit=green off\0" \
	"led_init=green blinking\0" \
	"dtb_file=/boot/dts/kirkwood-goflexhome.dtb\0" \
	"load_dtb_addr=0x1c00000\0" \
	"load_initrd_addr=0x1100000\0" \
	"load_uimage_addr=0x800000\0" \
	"load_dtb=echo loading DTB $dtb_file ...; load $bootdev $device $load_dtb_addr $dtb_file\0" \
	"load_initrd=echo loading uInitrd ...; load $bootdev $device $load_initrd_addr /boot/uInitrd\0" \
	"load_uimage=echo loading uImage ...; load $bootdev $device $load_uimage_addr /boot/uImage\0" \
	"mainlineLinux=yes\0" \
	"mtdids=nand0=orion_nand\0" \
	"mtdparts=mtdparts=orion_nand:1M(u-boot),4M(uImage),32M(rootfs),-(data)\0" \
	"partition=nand0,2\0" \
	"preboot_nc=run if_netconsole start_netconsole\0" \
	"scan_disk=echo running scan_disk ...; scan_done=0; setenv scan_usb \"usb start\";  setenv scan_ide \"ide reset\";  setenv scan_mmc \"mmc rescan\"; for dev in $devices; do if test $scan_done -eq 0; then echo Scan device $dev; run scan_$dev; for disknum in $disks; do if test $scan_done -eq 0; then echo device $dev $disknum:1; if load $dev $disknum:1 $load_uimage_addr /boot/uImage 1; then scan_done=1; echo Found bootable drive on $dev $disknum; setenv device $disknum:1; setenv bootdev $dev; fi; fi; done; fi; done\0" \
	"serverip=192.168.0.220\0" \
	"set_bootargs=setenv bootargs console=ttyS0,115200 root=LABEL=rootfs rootdelay=10 $mtdparts $custom_params\0" \
	"start_netconsole=setenv ncip $serverip; setenv bootdelay 10; setenv stdin nc; setenv stdout nc; setenv stderr nc; version;\0" \
	"stderr=serial\0" \
	"stdin=serial\0" \
	"stdout=serial\0" \
	"uenv_addr=0x810000\0" \
	"uenv_import=echo importing envs ...; env import -t $uenv_addr $filesize\0" \
	"uenv_init_devices=setenv init_usb \"usb start\";  setenv init_ide \"ide reset\";  setenv init_mmc \"mmc rescan\"; for devtype in $devices; do run init_$devtype; done;\0" \
	"uenv_load=run uenv_init_devices; setenv uenv_loaded 0; for devtype in $devices;  do for disknum in 0; do run uenv_read_disk; done; done;\0" \
	"uenv_read_disk=if test $devtype -eq mmc; then if $devtype part; then run uenv_read;  fi; else if $devtype part $disknum; then run uenv_read; fi;  fi\0" \
	"uenv_read=echo loading envs from $devtype $disknum ...; if load $devtype $disknum:1 $uenv_addr /boot/uEnv.txt; then setenv uenv_loaded 1; fi\0" \
	"usb_ready_retry=15\0"

/*
 * File system
 */
#define CONFIG_JFFS2_NAND
#define CONFIG_JFFS2_LZO
#define CONFIG_CMD_UBIFS
#define CONFIG_RBTREE
#define CONFIG_MTD_DEVICE               /* needed for mtdparts commands */
#define CONFIG_MTD_PARTITIONS
#define CONFIG_CMD_MTDPARTS
#define CONFIG_LZO

/*
 * Ethernet Driver configuration
 */
#ifdef CONFIG_CMD_NET
#define CONFIG_MVGBE_PORTS	{1, 0}	/* enable port 0 only */
#define CONFIG_PHY_BASE_ADR	0
#endif /* CONFIG_CMD_NET */

/*
 *  * SATA Driver configuration
 *   */
#ifdef CONFIG_MVSATA_IDE
#define CONFIG_SYS_ATA_IDE0_OFFSET      MV_SATA_PORT0_OFFSET
#endif /*CONFIG_MVSATA_IDE*/

/*
 *  Date Time
 *   
*/
#ifdef CONFIG_CMD_DATE
#define CONFIG_RTC_MV
#define CONFIG_CMD_SNTP
#define CONFIG_CMD_DNS
#endif /* CONFIG_CMD_DATE */

#endif /* _CONFIG_GOFLEXHOME_H */
