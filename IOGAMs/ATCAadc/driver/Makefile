DRIVER_NAME := pci_atca_adc
CFILES :=  pci-atca-adc.c pci-atca-adc-ioctl.c

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

$(DRIVER_NAME)-objs := $(CFILES:.c=.o)
obj-m := $(DRIVER_NAME).o

##obj-m	:= pci-atca-adc.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD       := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.mod modules.order *.symvers built-in.a

