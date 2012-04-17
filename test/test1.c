//#define _GNU_SOURCE
//#include <dlfcn.h>
//#include "test.h"
//LIB(test1)
//
//static void * get_pc (void)
//{
//  void *caller = __builtin_return_address (0);
//  return caller;
//}
//int main (int argc, char *argv[])
//{
//  int i;
//
//  printf ("enter main\n");
//  void *handler[100];
//  for(i=0; i<100;i++){
//    handler[i] = dlmopen(LM_ID_NEWLM,"/home/lauril/dev/elfloader_lr/test/liba.so", RTLD_LAZY);
//    //handler[i] = dlopen("/home/lauril/dev/elfloader_lr/test/liba.so", RTLD_LAZY);
//    if(!handler[i]){
//      printf ("Cannot open library: %s\n",dlerror());
//    } else {
//      printf("open: %d\n",i);
//    }
//    }
//
//  printf ("dlopen completed\n");
//
//  Dl_info info;
//  int status = dladdr(get_pc (), &info);
//  if (status != 0)
//    {
//      printf ("dladdr ok file=%s, symbol=%s\n",
//	      info.dli_fname, info.dli_sname);
//    }
//  for(i=0; i<100;i++){
//    dlclose (handler[i]);
//  }
//
//
//  printf ("leave main\n");
//  return 0;
//}
#define _GNU_SOURCE
#include <dlfcn.h>
#include "test.h"
LIB(test1)

static void * get_pc (void)
{
  void *caller = __builtin_return_address (0);
  return caller;
}
int main (int argc, char *argv[])
{
  printf ("enter main\n");
  void *h = dlopen ("liba.so", RTLD_LAZY);
  printf ("dlopen completed\n");

  Dl_info info;
  int status = dladdr(get_pc (), &info);
  if (status != 0)
    {
      printf ("dladdr ok file=%s, symbol=%s\n", 
        info.dli_fname, info.dli_sname);
    }

  dlclose (h);
  printf ("leave main\n");
  return 0;
}
