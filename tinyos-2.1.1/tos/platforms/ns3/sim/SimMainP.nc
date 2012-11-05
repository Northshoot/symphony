//static void __nesc_nido_initialise(int node);
#include <stdio.h>


module SimMainP {
  provides interface Boot;
  uses interface Scheduler;
  uses interface Init as PlatformInit;
  uses interface Init as SoftwareInit;
}
implementation {
	

       extern void sim_function_not_found()@C() @spontaneous(){
     printf("ERROR: Function does not exist!!!\n");
  }
  
   extern int sim_main_start_mote(int id) @C() @spontaneous() {
  	TOS_NODE_ID=id;
    //char timeBuf[128];
    //printf("FROM toslib: sim_main_start_mote\n");

    atomic {
      /* First, initialize the Scheduler so components can post
	 tasks. Initialize all of the very hardware specific stuff, such
	 as CPU settings, counters, etc. After the hardware is ready,
	 initialize the requisite software components and start
	 execution.*/
      
      call Scheduler.init(); 
      
      /* Initialize the platform. Then spin on the Scheduler, passing
       * FALSE so it will not put the system to sleep if there are no
       * more tasks; if no tasks remain, continue on to software
       * initialization */
      call PlatformInit.init();    
      //while (call Scheduler.runNextTask());
      
      /* Initialize software components.Then spin on the Scheduler,
       * passing FALSE so it will not put the system to sleep if there
       * are no more tasks; if no tasks remain, the system has booted
       * successfully.*/
      call SoftwareInit.init(); 
      //while (call Scheduler.runNextTask());
      TOS_NODE_ID=id;
      
    }
    
    /* Enable interrupts now that system is ready. */
  //  __nesc_enable_interrupt();

//    sim_print_now(timeBuf, 128);
//    dbg("SimMainP", "Mote %li signaling boot at time %s.\n", sim_node(), timeBuf);
    signal Boot.booted();
    //while (call Scheduler.runNextTask());
    //call Scheduler.taskLoop();
    /* Normally, at this point a mote enters a while(1) loop to
     * execute tasks. In TOSSIM, this call completes: posted tasks
     * are part of the global TOSSIM event loop. Look at
     * SimSchedulerBasicP for more details. */
     //printf("sim_main_start_mote: EXIT\n");
    return 0;
  }

  default command error_t PlatformInit.init() { return SUCCESS; }
  default command error_t SoftwareInit.init() { return SUCCESS; }
  default event void Boot.booted() { }
}

