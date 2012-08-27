/*
 * pointer_struct.h
 *
 *  Created on: May 11, 2010
 *      Author: laurynas
 */

#ifndef POINTER_STRUCT_H_
#define POINTER_STRUCT_H_

typedef int (*nsfunc)(int);

typedef struct LibToTosPointers{
  int confirmSet;
  int setTimerPeriodic;
}LibToTosPointers;

#endif /* POINTER_STRUCT_H_ */
