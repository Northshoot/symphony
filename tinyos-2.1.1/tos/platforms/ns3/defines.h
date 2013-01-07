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
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define dbg(s, ...) os_log_debug( s, __VA_ARGS__)
void os_log_debug(char* string, const char* format, ...);

void os_log_debug(char* string, const char* format, ...) {
//  va_list args;
//    printf("%s (%i): ",string, TOS_NODE_ID);
//    fprintf( stdout,format, args); 
//    fflush(stdout);

}

#endif //__NS3_DEFINES__