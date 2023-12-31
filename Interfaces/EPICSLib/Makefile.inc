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
# $Id: Makefile.inc 3 2012-01-15 16:26:07Z aneto $
#
#############################################################
EPICS_PATH=$(EPICS_BASE)
MAKEDEFAULTDIR=../../MakeDefaults

include $(MAKEDEFAULTDIR)/MakeStdLibDefs.$(TARGET)

OBJSX=
OBJS= $(TARGET)/exServer.o \
	$(TARGET)/exPV.o \
	$(TARGET)/exVectorPV.o \
	$(TARGET)/exScalarPV.o \
	$(TARGET)/exAsyncPV.o \
	$(TARGET)/exChannel.o 

CFLAGS+= -I.
CFLAGS+= -I../../BaseLib2/Level0
CFLAGS+= -I../../BaseLib2/Level1
CFLAGS+= -I../../BaseLib2/Level2
CFLAGS+= -I../../BaseLib2/Level3
CFLAGS+= -I../../BaseLib2/Level4
CFLAGS+= -I../../BaseLib2/Level5
CFLAGS+= -I../../BaseLib2/Level6

CFLAGS+= -I$(EPICS_PATH)/include
CFLAGS+= -I$(EPICS_PATH)/include/os/Linux

LIBRARIES += -L$(EPICS_PATH)/lib/$(EPICS_HOST_ARCH)
LIBRARIES += -lcas
LIBRARIES += -lca
LIBRARIES += -lCom
LIBRARIES += -lgdd 

all: $(OBJS)  \
	$(TARGET)/EPICSHandler$(DLLEXT)
	echo $(OBJS)

include depends.$(TARGET)

include $(MAKEDEFAULTDIR)/MakeStdLibRules.$(TARGET)
