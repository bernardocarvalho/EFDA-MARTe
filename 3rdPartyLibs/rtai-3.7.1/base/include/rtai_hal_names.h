/*
 * Copyright 2005 Paolo Mantegazza <mantegazza@aero.polimi.it>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


#ifndef _RTAI_HAL_NAMES_H
#define _RTAI_HAL_NAMES_H

#include <linux/version.h>

#define TSKEXT0  (HAL_ROOT_NPTDKEYS - 4)
#define TSKEXT1  (HAL_ROOT_NPTDKEYS - 3)
#define TSKEXT2  (HAL_ROOT_NPTDKEYS - 2)
#define TSKEXT3  (HAL_ROOT_NPTDKEYS - 1)

#if !defined(CONFIG_PPC) && (LINUX_VERSION_CODE < KERNEL_VERSION(2,4,32) || (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0) && LINUX_VERSION_CODE < KERNEL_VERSION(2,6,13)))

#define HAL_VERSION_STRING   ADEOS_VERSION_STRING

#define HAL_NR_CPUS          ADEOS_NR_CPUS
#define HAL_NR_FAULTS        ADEOS_NR_FAULTS
#define HAL_NR_EVENTS        ADEOS_NR_EVENTS
#define HAL_ROOT_NPTDKEYS    ADEOS_ROOT_NPTDKEYS

#define HAL_APIC_HIGH_VECTOR  ADEOS_SERVICE_VECTOR3
#define HAL_APIC_LOW_VECTOR   ADEOS_SERVICE_VECTOR2

#define HAL_SCHEDULE_HEAD     ADEOS_SCHEDULE_HEADa
#define HAL_SCHEDULE_TAIL     ADEOS_SCHEDULE_TAIL
#define HAL_SYSCALL_PROLOGUE  ADEOS_SYSCALL_PROLOGUE
#define HAL_SYSCALL_EPILOGUE  1000000 // invalid for sure, will be rejected, OK ADEOS_SYSCALL_EPILOGUE
#define HAL_EXIT_PROCESS      ADEOS_EXIT_PROCESS
#define HAL_KICK_PROCESS      ADEOS_KICK_PROCESS

extern struct list_head __adeos_pipeline;

#define hal_pipeline           __adeos_pipeline
#define hal_domain_struct      adomain 
#define hal_root_domain        adp_root 
#define hal_current_domain(x)  adp_cpu_current[x] 

#define hal_propagate_irq  adeos_propagate_irq
#define hal_schedule_irq   adeos_schedule_irq

#define hal_critical_enter  adeos_critical_enter
#define hal_critical_exit   adeos_critical_exit

#define hal_clear_irq   __adeos_clear_irq
#define hal_lock_irq    __adeos_lock_irq
#define hal_unlock_irq  __adeos_unlock_irq

#define hal_std_irq_dtype        __adeos_std_irq_dtype
#define hal_adeos_std_irq_dtype  __adeos_std_irq_dtype

#define hal_tick_regs  __adeos_tick_regs
#define hal_tick_irq   __adeos_tick_irq

#define hal_sync_stage  __adeos_sync_stage

#define hal_set_irq_affinity  adeos_set_irq_affinity

#define hal_set_irq_handler   adeos_set_irq_handler

#define hal_propagate_event  adeos_propagate_event

#define hal_get_sysinfo  adeos_get_sysinfo

#define INTERCEPT_WAKE_UP_TASK(data)  (((struct sig_wakeup_t *)data)->task)

#define FIRST_LINE_OF_RTAI_DOMAIN_ENTRY  static void rtai_domain_entry(int iflag) { if (iflag)
#define LAST_LINE_OF_RTAI_DOMAIN_ENTRY   }

#ifdef CONFIG_ADEOS_NOTHREADS
#define HAL_TYPE  "ADEOS-NOTHREADS"
#define hal_suspend_domain()  break
#else
#define HAL_TYPE  "ADEOS-THREADS"
#define hal_suspend_domain()  adeos_suspend_domain()
#endif

#define hal_alloc_irq       adeos_alloc_irq
#define hal_free_irq        adeos_free_irq
#define hal_virtualize_irq  adeos_virtualize_irq_from
#define hal_irq_hits_pp(irq, domain, cpuid) \
do { \
	domain->cpudata[cpuid].irq_hits[irq]++; \
} while (0)

#define hal_sysinfo_struct         adsysinfo
#define hal_attr_struct            adattr
#define hal_init_attr              adeos_init_attr
#define hal_register_domain        adeos_register_domain
#define hal_unregister_domain      adeos_unregister_domain
#define hal_catch_event            adeos_catch_event_from
#define hal_event_handler          adeos_event_handler
#define hal_event_handler_fun(e)   events[e].handler

#define hal_set_printk_sync   adeos_set_printk_sync
#define hal_set_printk_async  adeos_set_printk_async

#define hal_schedule_back_root(prev) \
do { \
	if ((prev)->rtai_tskext(HAL_ROOT_NPTDKEYS - 1)) { \
		__adeos_schedule_back_root((prev)->rtai_tskext(HAL_ROOT_NPTDKEYS - 1)); \
		(prev)->rtai_tskext(HAL_ROOT_NPTDKEYS - 1) = NULL; \
	} else { \
		__adeos_schedule_back_root(prev); \
	} \
} while (0)

#define hal_processor_id  adeos_processor_id

#define hal_hw_cli                adeos_hw_cli
#define hal_hw_sti                adeos_hw_sti
#define hal_hw_local_irq_save     adeos_hw_local_irq_save
#define hal_hw_local_irq_restore  adeos_hw_local_irq_restore
#define hal_hw_local_irq_flags    adeos_hw_local_irq_flags

#define hal_unstall_pipeline_from  adeos_unstall_pipeline_from

#define hal_ack_system_irq  __adeos_ack_system_irq

#define hal_irq_handler  adeos_extern_irq_handler

#define hal_tskext  ptd

#define hal_set_linux_task_priority  __adeos_setscheduler_root

#else

#define HAL_VERSION_STRING   IPIPE_VERSION_STRING

#define HAL_NR_CPUS          IPIPE_NR_CPUS
#define HAL_NR_FAULTS        IPIPE_NR_FAULTS
#define HAL_NR_EVENTS        IPIPE_NR_EVENTS
#define HAL_ROOT_NPTDKEYS    IPIPE_ROOT_NPTDKEYS

#define HAL_APIC_HIGH_VECTOR  IPIPE_SERVICE_VECTOR3
#define HAL_APIC_LOW_VECTOR   IPIPE_SERVICE_VECTOR2

#define HAL_SCHEDULE_HEAD     IPIPE_EVENT_SCHEDULE
#define HAL_SCHEDULE_TAIL     (IPIPE_FIRST_EVENT - 2)  // safely unused, cared
#define HAL_SYSCALL_PROLOGUE  IPIPE_EVENT_SYSCALL
#define HAL_SYSCALL_EPILOGUE  1000000 // invalid for sure, will be rejected, OK
#define HAL_EXIT_PROCESS      IPIPE_EVENT_EXIT
#define HAL_KICK_PROCESS      IPIPE_EVENT_SIGWAKE

#define hal_pipeline        __ipipe_pipeline
#define hal_domain_struct   ipipe_domain 
#define hal_root_domain     ipipe_root_domain 

// temporary fix for using PPC
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,17) || (defined(CONFIG_PPC) && LINUX_VERSION_CODE > KERNEL_VERSION(2,6,13))
#define hal_current_domain(cpuid)  per_cpu(ipipe_percpu_domain, cpuid) 
#else
#define hal_current_domain(cpuid)  (ipipe_percpu_domain[cpuid])
#endif

#define hal_propagate_irq   ipipe_propagate_irq
#define hal_schedule_irq    ipipe_schedule_irq

#define hal_critical_enter  ipipe_critical_enter
#define hal_critical_exit   ipipe_critical_exit

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,22)
#define hal_clear_irq   __ipipe_clear_irq
#else
#define hal_clear_irq(a, b)
#endif

#define hal_lock_irq    __ipipe_lock_irq
#define hal_unlock_irq  __ipipe_unlock_irq

#define hal_std_irq_dtype        __ipipe_std_irq_dtype
#define hal_ipipe_std_irq_dtype  __adeos_std_irq_dtype

#define hal_tick_regs  __ipipe_tick_regs
#define hal_tick_irq   __ipipe_tick_irq

#define hal_sync_stage  __ipipe_sync_stage

#define hal_set_irq_affinity  ipipe_set_irq_affinity

#define hal_propagate_event  ipipe_propagate_event

#define hal_get_sysinfo  ipipe_get_sysinfo

#define HAL_TYPE  "IPIPE-NOTHREADS"

#define INTERCEPT_WAKE_UP_TASK(data)  ((struct task_struct *)data)

#define FIRST_LINE_OF_RTAI_DOMAIN_ENTRY  static void rtai_domain_entry(void) { if (1)
#define LAST_LINE_OF_RTAI_DOMAIN_ENTRY   }

#define hal_suspend_domain()  break

#define hal_alloc_irq       ipipe_alloc_virq
#define hal_free_irq        ipipe_free_virq

#if !defined(CONFIG_PPC) && (LINUX_VERSION_CODE < KERNEL_VERSION(2,4,32) || (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0) && LINUX_VERSION_CODE < KERNEL_VERSION(2,6,14)))
#define hal_virtualize_irq  ipipe_virtualize_irq
#define hal_irq_hits_pp(irq, domain, cpuid) \
do { \
	domain->cpudata[cpuid].irq_hits[irq]++; \
} while (0)
#else
#define hal_virtualize_irq(d, n, h, a, m) \
	ipipe_virtualize_irq(d, n, (void *)h, NULL, a, m)
#define hal_irq_hits_pp(irq, domain, cpuid) \
do { \
/*	domain->cpudata[cpuid].irq_counters[irq].total_hits++; REMIND ME TOO */\
	domain->cpudata[cpuid].irq_counters[irq].pending_hits++; \
} while (0)
#endif

#define hal_sysinfo_struct         ipipe_sysinfo
#define hal_attr_struct            ipipe_domain_attr
#define hal_init_attr              ipipe_init_attr
#define hal_register_domain        ipipe_register_domain
#define hal_unregister_domain      ipipe_unregister_domain
#define hal_catch_event            ipipe_catch_event
#define hal_event_handler          ipipe_event_handler
#define hal_event_handler_fun(e)   evhand[e]

#define hal_set_printk_sync   ipipe_set_printk_sync
#define hal_set_printk_async  ipipe_set_printk_async

#define hal_schedule_back_root(prev) \
do { \
	if ((prev)->rtai_tskext(HAL_ROOT_NPTDKEYS - 1)) { \
		ipipe_reenter_root((prev)->rtai_tskext(HAL_ROOT_NPTDKEYS - 1), (prev)->policy, (prev)->rt_priority); \
		(prev)->rtai_tskext(HAL_ROOT_NPTDKEYS - 1) = NULL; \
	} else { \
		ipipe_reenter_root(prev, (prev)->policy, (prev)->rt_priority); \
	} \
} while (0)

#define hal_processor_id  ipipe_processor_id

#define hal_hw_cli                local_irq_disable_hw
#define hal_hw_sti                local_irq_enable_hw
#define hal_hw_local_irq_save     local_irq_save_hw
#define hal_hw_local_irq_restore  local_irq_restore_hw
#define hal_hw_local_irq_flags    local_save_flags_hw

#define hal_set_timer(ns)  ipipe_tune_timer(ns, 0)
#define hal_reset_timer()  ipipe_tune_timer(0, IPIPE_RESET_TIMER)

#define hal_unstall_pipeline_from  ipipe_unstall_pipeline_from

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,18)
#define hal_ack_system_irq  __ipipe_ack_system_irq
#else
#define hal_ack_system_irq  __ipipe_ack_apic
#endif

#define hal_irq_handler     ipipe_irq_handler

#define hal_tskext  ptd

#define hal_set_linux_task_priority  ipipe_setscheduler_root

#endif

#if defined(IPIPE_ROOT_NPTDKEYS) && TSKEXT0 < 0
#error *** TSKEXTs WILL CAUSE MEMORY LEAKS, CHECK BOUNDS IN HAL PATCHES ***
#endif

#endif
