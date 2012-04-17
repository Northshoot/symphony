#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#define NUM 1000000

int main (int argc, char *argv[])
{


  void *g1[NUM];
  int i=0;
  printf ("enter main\n");
  for(;i<NUM;i++){
    g1[i] = dlmopen(LM_ID_NEWLM,"/home/lauril/dev/elfloader_lr/test/libtos.so", RTLD_LAZY);
    if(!g1[i]){
      printf ("Cannot open library %d: %s\n",i,dlerror());
    } else {
      //printf ("dlopen libtos.so completed %d\n",i+1);
    }
  }
  printf("sizeof(g1[1])=%lu\n", sizeof(g1[1]));



  for(i=0;i<NUM;i++){
  dlclose (g1[i]);

  }

  printf ("dlclose libtos.so completed\n");
  printf ("leave main\n");
  return 0;
}
