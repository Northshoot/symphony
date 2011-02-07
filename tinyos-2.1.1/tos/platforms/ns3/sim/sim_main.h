#ifndef SIM_MAIN_H
#define SIM_MAIN_H

#include "ns3/LibToTosProxy.h"

int a;
int id_this_lib;
void * proxy; //pointer to tthis proxy object
//extern int gateway(void *tthis,int call, int arg);

#ifdef __cplusplus
extern "C" {
#endif
int setUniqueID(int i) @C() @spontaneous(){
  printf("uniq: %i\n", i);
  id_this_lib=i;
  return id_this_lib;
}

int runNextEventExternal(uint32_t a);
int sim_main_start_mote(int id) ;


int setProxy(void * con) @C() @spontaneous() {
         proxy=con;

         if(proxy != NULL ){
            a=gateway(proxy,0,id_this_lib);
           printf("gateway(proxy,0,id_this_lib): %i\n", a);
//           printf("proxy in lib: %i\n", id_this_lib);
         } else {
             printf("ops! no proxy\n");
         }

         return id_this_lib;
     }
#ifdef __cplusplus
}
#endif
  
#endif // SIM_MAIN_H
