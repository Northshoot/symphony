#include "test.h"
#include <dlfcn.h>
#define __USE_GNU 1

LIB(test22);
int main (int argc, char *argv[])
{
  void *h[100] ;
  int i;
  for(i=0;i<100;i++){
    h[i]= dlopen ("lb22.so", RTLD_LAZY);
  }

  for(i=0;i<100;i++){
    dlclose (h[i]);
  }
  return 0;
}
