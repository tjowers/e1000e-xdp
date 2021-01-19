# SPDX-License-Identifier: GPL-2.0
# Copyright(c) 1999 - 2018 Intel Corporation.

#
# Makefile for the Intel(R) PRO/1000 ethernet driver
#
BASE:=$(shell pwd)

obj-m += e1000e.o

e1000e-objs := 82571.o ich8lan.o 80003es2lan.o \
	       mac.o manage.o nvm.o phy.o \
	       param.o ethtool.o xdp.o netdev.o ptp.o

default: modules

modules:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(BASE) modules
clean:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(BASE) clean

reload: modules
	sudo rmmod -f e1000e | true
	sudo insmod ./e1000e.ko
