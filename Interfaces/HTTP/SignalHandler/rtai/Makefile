#############################################################
#
# Copyright 2011 EFDA | European Fusion Development Agreement
#
# Licensed under the EUPL, Version 1.1 or - as soon they 
# will be approved by the European Commission - subsequent  
# versions of the EUPL (the "Licence"); 
# You may not use this work except in compliance with the 
# Licence. 
# You may obtain a copy of the Licence at: 
#  
# http://ec.europa.eu/idabc/eupl
#
# Unless required by applicable law or agreed to in 
# writing, software distributed under the Licence is 
# distributed on an "AS IS" basis, 
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either 
# express or implied. 
# See the Licence for the specific language governing 
# permissions and limitations under the Licence. 
#
# $Id: Makefile 3 2012-01-15 16:26:07Z aneto $
#
#############################################################
TARGET1 = RTAISignalServer

EXTRA_CFLAGS = -DEXPORT_SYMTAB -I/usr/realtime/include 
CURRENT = $(shell uname -r)
KDIR = /lib/modules/$(CURRENT)/build
KPWD = $(shell pwd)
DEST = /lib/modules/$(CURRENT)/kernel/$(MDIR)

$(LDFLAGS_NOKVERSION) = -T $(PWD)/../../../../OSFiles/rtai/C++Sup/global_obj_link.ld

obj-m	:= $(TARGET1).o

$(TARGET1)-objs := ../../../../OSFiles/rtai/C++Sup/global_obj_support.o SignalServer.o

default:
	make -C $(KDIR) SUBDIRS=$(KPWD) modules
	rm -f ../../../../BaseLib2/Level0/RTAILoader.o
	
clean:
	-rm -f *.o *.a *.ko .*.cmd .*.flags *.mod.c *.s
