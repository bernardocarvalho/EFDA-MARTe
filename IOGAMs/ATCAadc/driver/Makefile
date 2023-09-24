DRIVER_NAME := pci_atca_adc
#CFILES :=  pci-atca-adc.c
CFILES :=  pci-atca-adc.c pci-atca-adc-ioctl.c

$(DRIVER_NAME)-objs := $(CFILES:.c=.o)
obj-m := $(DRIVER_NAME).o

##obj-m	:= pci-atca-adc.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD       := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.mod modules.order *.symvers built-in.a

