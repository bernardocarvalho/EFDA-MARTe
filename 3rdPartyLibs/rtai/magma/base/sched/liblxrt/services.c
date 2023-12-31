/*
 * Copyright (C) Pierre Cloutier <pcloutier@PoseidonControls.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the version 2 of the GNU Lesser
 * General Public License as published by the Free Software
 * Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 */


/* dummy defines to avoid annoying warning about here unused stuff */
#define read_cr4()  0
#define write_cr4(x)
/* end of dummy defines to avoid annoying warning about here unused stuff */

#define CONFIG_RTAI_LXRT_INLINE 0
#include <malloc.h>
#include <rtai_lxrt.h>
#include <rtai_schedcore.h>
#include <rtai_posix.h>
#ifdef CONFIG_RTAI_DRIVERS_SERIAL
#include <rtai_serial.h>
#endif /* CONFIG_RTAI_DRIVERS_SERIAL */
