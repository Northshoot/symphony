#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM 35000
typedef int (*Fn)(int);

int main (int argc, char *argv[])
{

  void *g1[NUM];
  void * tmp[NUM];
  long int i=0;
  long int open=0;
  int libs = atoi(argv[1]);
  printf ("enter main, starting to open %d libraries\n", libs);
  clock_t start = clock();
  for(;i<libs;i++){
    g1[i] = dlmopen(LM_ID_NEWLM,"libtostest.so", RTLD_LAZY);
    if(!g1[i]){
      printf ("Cannot open library %ld: %s\n",i,dlerror());
    } else {
      char *error=NULL;
      tmp[i]= dlsym(g1[i],"tickFired");
      if( (error = dlerror()) != NULL){
         printf("ERROR getting function: %s\n", dlerror());

       } else {
    	   if(tmp[i])
    		   printf("got tickFired: %lu %lu\n",i, (long int)tmp[i]);
    	   else
    		   printf("Wierd error, should not end here\n");
        open++;
       }
    }
  }

printf("Opened %ld libraries, time : %f\n", open, ( (double)clock() - start ) / CLOCKS_PER_SEC );

  start = clock();
  for(i=0;i<libs;i++){
         ((Fn)tmp[i])(i);
  }

printf("Time to execute one function in %ld libraries : %f\n",  open,( (double)clock() - start ) / CLOCKS_PER_SEC );

  //sleep(30);
start = clock();
  for(i=0;i<libs;i++){
  dlclose (g1[i]);

  }
printf("Time to close  %ld libraries : %f\n", open,  ( (double)clock() - start ) / CLOCKS_PER_SEC );

  printf ("dlclose libtos.so completed\n");
  printf ("leave main\n");
  return 0;
}
