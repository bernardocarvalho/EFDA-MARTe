#DRIVER_NAME := pci_atca_adc
TARGET_MODULE := pci_atca_adc
#CFILES :=  pci-atca-adc.c pci-atca-adc-ioctl.c

# set the install path
INSTDIR := /lib/modules/$(KVER)/kernel/drivers/atca

# Comment/uncomment the following line to disable/enable debugging
DEBUG = y
# Add your debugging flag (or not) to CFLAGS
ifeq ($(DEBUG),y)
  DEBFLAGS = -O -g -DATCA_DEBUG # "-O" is needed to expand inlines
else
  DEBFLAGS = -O2
endif

#EXTRA_CFLAGS += -I$(LDDINC)
EXTRA_CFLAGS += $(DEBFLAGS)

#i$(DRIVER_NAME)-objs := $(CFILES:.c=.o)
#obj-m := $(DRIVER_NAME).o

ifneq ($(KERNELRELEASE),)
	$(TARGET_MODULE)-objs := pci-atca-adc.o pci-atca-adc-ioctl.o
	obj-m := $(TARGET_MODULE).o
else
	BUILDSYSTEM_DIR:=/lib/modules/$(shell uname -r)/build
	PWD:=$(shell pwd)

##obj-m	:= pci-atca-adc.o

#KERNELDIR ?= /lib/modules/$(shell uname -r)/build
#PWD       := $(shell pwd)

all:
#	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	$(MAKE) -C $(BUILDSYSTEM_DIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(BUILDSYSTEM_DIR) M=$(PWD) clean
	@/bin/rm -f *.ko modules.order *.mod.c *.o *.o.ur-safe .*.o.cmd
#	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.mod modules.order *.symvers built-in.a

install: all
	$(MAKE) -C $(BUILDSYSTEM_DIR) M=$(PWD) modules_install
	depmod -A

endif
