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

CURRENT = $(shell uname -r)

all:
	gcc -c -Wall -mregparm=3 -I/usr/realtime/include global_obj_support.c cfunc_sup.c strtod.c
	g++ -frtti -fno-use-cxa-atexit -fno-exceptions -mregparm=3 -c new_op.cc new_handler.cc new_opv.cc del_op.cc del_opv.cc tinfo.cc
	ld -r cfunc_sup.o new_op.o new_handler.o new_opv.o del_op.o del_opv.o strtod.o global_obj_support.o tinfo.o -o RTAISupC++.a
	cd module && make && cd ..
clean:
	rm -f *.o *.a .*.cmd
	cd module && make clean
