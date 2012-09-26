#ifndef __NS3_DEFINES__
#define __NS3_DEFINES__

#define ASSERT(COND) for(;0;)

#ifdef	TASKLET_IS_TASK

	#define tasklet_async
	#define tasklet_norace

#else

	#define tasklet_async	async	
	#define tasklet_norace	norace

#endif //TASKLET_IS_TASK

#endif //__NS3_DEFINES__