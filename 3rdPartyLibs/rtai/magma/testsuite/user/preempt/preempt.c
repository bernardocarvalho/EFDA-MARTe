/*
COPYRIGHT (C) 2003  Paolo Mantegazza (mantegazza@aero.polimi.it)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
*/

#include <sys/mman.h>
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>

#include <rtai_fifos.h>
#include <rtai_sem.h>

#define FIFO 0

#define NAVRG 800

#define USE_FPU 0

#define FASTMUL  4

#define SLOWMUL  24

#if defined(CONFIG_UCLINUX) || defined(CONFIG_ARM)
#define TICK_TIME 1000000
#else
#define TICK_TIME 500000
#endif

static RT_TASK *Latency_Task;
static RT_TASK *Slow_Task;
static RT_TASK *Fast_Task;

static volatile int period, slowjit, fastjit;
static volatile RTIME expected;

static SEM *barrier;

static volatile int end;
static void endme (int dummy) { end = 1; }

static void *slow_fun(void *arg)
{
        int jit;
        RTIME svt, t;

        if (!(Slow_Task = rt_task_init_schmod(nam2num("SLWTSK"), 3, 0, 0, SCHED_FIFO, 1))) {
                printf("CANNOT INIT SLOW TASK\n");
                exit(1);
        }

	mlockall(MCL_CURRENT | MCL_FUTURE);
	rt_make_hard_real_time();
	rt_sem_wait_barrier(barrier);
        svt = rt_get_time() - SLOWMUL*period;
        while (!end) {  
                jit = (int) count2nano((t = rt_get_time()) - svt - SLOWMUL*period);
                svt = t;
                if (jit) { jit = - jit; }
                if (jit > slowjit) { slowjit = jit; }
                rt_busy_sleep(SLOWMUL/2*TICK_TIME);
                rt_task_wait_period();                                        
        }
	rt_sem_wait_barrier(barrier);
	rt_make_soft_real_time();
	rt_task_delete(Slow_Task);
	return 0;
}                                        

static void *fast_fun(void *arg) 
{                             
        int jit;
        RTIME svt, t;

        if (!(Fast_Task = rt_task_init_schmod(nam2num("FSTSK"), 2, 0, 0, SCHED_FIFO, 1))) {
                printf("CANNOT INIT FAST TASK\n");
                exit(1);
        }

	mlockall(MCL_CURRENT | MCL_FUTURE);
	rt_make_hard_real_time();
	rt_sem_wait_barrier(barrier);
        svt = rt_get_time() - SLOWMUL*period;
        while (!end) {  
                jit = (int) count2nano((t = rt_get_time()) - svt - FASTMUL*period);
                svt = t;
                if (jit) { jit = - jit; }
                if (jit > fastjit) { fastjit = jit; }
                rt_busy_sleep(FASTMUL/2*TICK_TIME);
                rt_task_wait_period();                                        
        }                      
	rt_sem_wait_barrier(barrier);
	rt_make_soft_real_time();
	rt_task_delete(Fast_Task);
	return 0;
}

static void *latency_fun(void *arg)
{
	struct sample { long min, max, avrg, jitters[2]; } samp;
	int diff;
	int skip;
	int average;
	int min_diff;
	int max_diff;

	min_diff = 1000000000;
	max_diff = -1000000000;
        if (!(Latency_Task = rt_task_init_schmod(nam2num("LTCTSK"), 1, 0, 0, SCHED_FIFO, 1))) {
                printf("CANNOT INIT LATENCY TASK\n");
                exit(1);
        }

	mlockall(MCL_CURRENT | MCL_FUTURE);
	rt_make_hard_real_time();
	rt_sem_wait_barrier(barrier);
        while (!end) {  
		average = 0;
		for (skip = 0; skip < NAVRG && !end; skip++) {
			expected += period;
			rt_task_wait_period();
			diff = (int)count2nano(rt_get_time() - expected);
			if (diff < min_diff) {
				min_diff = diff;
			}
			if (diff > max_diff) {
				max_diff = diff;
			}
		average += diff;
		}
		samp.min = min_diff;
		samp.max = max_diff;
		samp.avrg = average/NAVRG;
		samp.jitters[0] = fastjit;
		samp.jitters[1] = slowjit;
		rtf_ovrwr_put(FIFO, &samp, sizeof(samp));
	}
	rt_sem_wait_barrier(barrier);
	rt_make_soft_real_time();
	rt_task_delete(Latency_Task);
	return 0;
}

static pthread_t latency_thread, fast_thread, slow_thread;

int main(void)
{
	char nm[RTF_NAMELEN+1];
	RT_TASK *Main_Task;
	int fifo;

	signal(SIGHUP,  endme);
	signal(SIGINT,  endme);
	signal(SIGKILL, endme);
	signal(SIGTERM, endme);
	signal(SIGALRM, endme);

        if (!(Main_Task = rt_task_init_schmod(nam2num("MNTSK"), 0, 0, 0, SCHED_FIFO, 1))) {
                printf("CANNOT INIT MAIN TASK\n");
                exit(1);
        }

	rtf_create(FIFO, 1000);
        if ((fifo = open(rtf_getfifobyminor(0,nm,sizeof(nm)), O_RDWR)) < 0) {
                printf("ERROR OPENING FIFO %s\n",nm);
                exit(1);
        }
	barrier = rt_sem_init(nam2num("PREMSM"), 4);
	pthread_create(&latency_thread, NULL, latency_fun, NULL);
	pthread_create(&fast_thread, NULL, fast_fun, NULL);
	pthread_create(&slow_thread, NULL, slow_fun, NULL);
	rt_set_oneshot_mode();
	period = start_rt_timer(nano2count(TICK_TIME));
	rt_sem_wait_barrier(barrier);
	expected = rt_get_time() + 100*period;
	rt_task_make_periodic(Latency_Task, expected, period);
	rt_task_make_periodic(Fast_Task, expected, FASTMUL*period);
	rt_task_make_periodic(Slow_Task, expected, SLOWMUL*period);
	pause();
	end = 1;
	rt_sem_wait_barrier(barrier);
	rt_thread_join(latency_thread);
	rt_thread_join(fast_thread);
	rt_thread_join(slow_thread);
	stop_rt_timer();	
	rtf_destroy(FIFO);
	rt_sem_delete(barrier);
	rt_task_delete(Main_Task);
	return 0;
}
