/*
 *   ARTI -- RTAI-compatible Adeos-based Real-Time Interface. Based on
 *   the original RTAI layer for x86. This file provides user-visible
 *   definitions for compatibility purpose with the legacy RTHAL. Must
 *   be included from rtai_hal.h only.
 *
 *   Original RTAI/x86 layer implementation:
 *   Copyright (C) 2000 Paolo Mantegazza,
 *   Copyright (C) 2000 Steve Papacharalambous,
 *   Copyright (C) 2000 Stuart Hughes,
 *   and others.
 *
 *   RTAI/x86 rewrite over Adeos:
 *   Copyright (C) 2002 Philippe Gerum.
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, Inc., 675 Mass Ave, Cambridge MA 02139,
 *   USA; either version 2 of the License, or (at your option) any later
 *   version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef _RTAI_ASM_X8664_OLDNAMES_H
#define _RTAI_ASM_X8664_OLDNAMES_H

#ifdef __KERNEL__

#define IFLAG                        RTAI_IFLAG
#define hard_cli()                   rtai_cli()
#define hard_sti()                   rtai_sti()
#define hard_save_flags_and_cli(x)   rtai_save_flags_and_cli(x)
#define hard_restore_flags(x)        rtai_restore_flags(x)
#define hard_save_flags(x)           rtai_save_flags(x)
#define hard_cpu_id                  hal_processor_id

#endif /* __KERNEL__ */

#ifndef __RTAI_HAL__

#define tuned           rtai_tunables
#define NR_RT_CPUS      RTAI_NR_CPUS
#define RT_TIME_END     RTAI_TIME_LIMIT

#define CPU_FREQ        RTAI_CPU_FREQ
#define TIMER_8254_IRQ  RTAI_TIMER_8254_IRQ
#define FREQ_8254       RTAI_FREQ_8254
#define LATENCY_8254    RTAI_LATENCY_8254
#define SETUP_TIME_8254	RTAI_SETUP_TIME_8254

#define FREQ_APIC       RTAI_FREQ_APIC
#define LATENCY_APIC    RTAI_LATENCY_APIC
#define SETUP_TIME_APIC RTAI_SETUP_TIME_APIC

#define CALIBRATED_APIC_FREQ  RTAI_CALIBRATED_APIC_FREQ
#define CALIBRATED_CPU_FREQ   RTAI_CALIBRATED_CPU_FREQ

#ifdef __KERNEL__

#undef  rdtsc
#define rdtsc()     rtai_rdtsc()
#define rd_CPU_ts() rtai_rdtsc()

#define rt_set_rtai_trap_handler  rt_set_trap_handler
#define rt_mount_rtai   rt_mount
#define rt_umount_rtai  rt_umount
#define calibrate_8254  rtai_calibrate_8254

#define ulldiv(a,b,c)   rtai_ulldiv(a,b,c)
#define imuldiv(a,b,c)  rtai_imuldiv(a,b,c)
#define llimd(a,b,c)    rtai_llimd(a,b,c)
#define u64div32(a,b,c) rtai_u64div32c(a,b,c)

#ifndef __cplusplus

#include <linux/irq.h>
#include <asm/desc.h>

extern struct gate_struct idt_table[];

static inline struct gate_struct rt_set_full_intr_vect (unsigned vector,
							int type,
							int dpl,
							void (*handler)(void)) {
	struct gate_struct e = idt_table[vector];
	idt_table[vector].offset_low = PTR_LOW(handler); 
	idt_table[vector].segment = __KERNEL_CS;
	idt_table[vector].ist = 0; 
	idt_table[vector].p = 1;
	idt_table[vector].dpl = dpl; 
	idt_table[vector].zero0 = 0;
	idt_table[vector].zero1 = 0; 
	idt_table[vector].type = type; 
	idt_table[vector].offset_middle = PTR_MIDDLE(handler); 
	idt_table[vector].offset_high = PTR_HIGH(handler); 
    return e;
}

static inline void rt_reset_full_intr_vect(unsigned vector,
					   struct gate_struct e) {
    idt_table[vector] = e;
}

static inline int rt_request_cpu_own_irq (unsigned irq, void (*handler)(void)) {

    return rt_request_irq(irq, (rt_irq_handler_t)handler, NULL, 0);
}

static inline int rt_free_cpu_own_irq (unsigned irq) {

    return rt_release_irq(irq);
}

static inline void *get_intr_handler (unsigned vector) {
    return (void *)((unsigned long)idt_table[vector].offset_low + (((unsigned long)idt_table[vector].offset_middle) << 16) + (((unsigned long)idt_table[vector].offset_high) << 32));
}

static inline void set_intr_vect (unsigned vector,
				  void (*handler)(void)) {
	idt_table[vector].offset_low = PTR_LOW(handler); 
	idt_table[vector].offset_middle = PTR_MIDDLE(handler); 
	idt_table[vector].offset_high = PTR_HIGH(handler); 
}

static inline void *rt_set_intr_handler (unsigned vector,
					 void (*handler)(void)) {

    void (*saved_handler)(void) = get_intr_handler(vector);
    set_intr_vect(vector, handler);
    return saved_handler;
}

static inline void rt_reset_intr_handler (unsigned vector,
					  void (*handler)(void)) {
    set_intr_vect(vector, handler);
}

static inline unsigned long get_cr2 (void) {
	unsigned long address;
	__asm__("movq %%cr2,%0":"=r" (address));
	return address;
}

#endif /* __KERNEL__ */

#endif /* !__cplusplus */

#endif /* !__RTAI_HAL__ */

#endif /* !_RTAI_ASM_X8664_OLDNAMES_H */
