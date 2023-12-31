/*
 * Project: rtai_cpp - RTAI C++ Framework 
 *
 * File: $Id: rtf_init.c,v 1.1 2004/12/09 09:19:54 rpm Exp $
 *
 * Copyright: (C) 2001,2002 Erwin Rol <erwin@muffin.org>
 *
 * Licence:
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 */

#include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <asm/unistd.h>

#include <rtai_malloc.h>
#include "rtai.h"

// RTAI-- MODULE INIT and CLEANUP functions

MODULE_LICENSE("GPL");
MODULE_AUTHOR("the RTAI-Team (contact person Erwin Rol)");
MODULE_DESCRIPTION("RTAI C++ RTF support");

int __init rtai_cpp_rtf_init(void){
	return 0;
}

void rtai_cpp_rtf_cleanup(void)
{
}

module_init(rtai_cpp_rtf_init)
module_exit(rtai_cpp_rtf_cleanup)
  
