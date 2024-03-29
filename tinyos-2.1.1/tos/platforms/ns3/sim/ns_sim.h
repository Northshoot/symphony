#ifndef NS_SIM_H
#define NS_SIM_H

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>

#ifndef __cplusplus
//typedef uint8_t bool;
#endif
//
///* 
// * TEMPORARY: include the Safe TinyOS macros so that annotations get
// * defined away for non-safe users -- this will no longer be necessary
// * after we require users to use the ncc that has Safe TinyOS
// * support 
// */
#include "../../lib/safe/include/annots_stage1.h"
//
//enum { FALSE = 0, TRUE = 1 };
//
//extern uint16_t TOS_NODE_ID;


struct sim_event;
typedef struct sim_event sim_event_t;

struct sim_event {

  unsigned long  mote;
  bool force; // Whether this event type should always be executed
            // even if a mote is "turned off"
  bool cancelled; // Whether this event has been cancelled

};


#endif //NS_SIM_H
