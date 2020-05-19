# SPDX-License-Identifier: GPL-2.0+
#
# (C) Copyright 2000-2006
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.

extra-y	= start.o

obj-y	+= cpu.o
obj-y	+= cache.o

obj-$(CONFIG_EP93XX) += ep93xx/
obj-$(CONFIG_IMX) += imx/
obj-$(CONFIG_S3C24X0) += s3c24x0/


# some files can only build in ARM mode

ifdef CONFIG_$(SPL_)SYS_THUMB_BUILD
CFLAGS_cpu.o := -marm
endif
