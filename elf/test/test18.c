#define _GNU_SOURCE 1
#include "test.h"
#include <dlfcn.h>
#include <stdio.h>
LIB(test18)

typedef int (*Fn) (int);

int main (int argc, char *argv[])
{
  void * h1[100] ;
  Fn fp1[100];
  int i;
  for( i=0;i<100;i++){
    h1[i]= dlmopen (LM_ID_NEWLM, "libp.so", RTLD_LAZY);
  }
  for (i=0;i<100;i++) {
    fp1[i] = dlsym (h1[i], "libp_set_global");
    printf("L:%d -- fp1(-1)=%d\n", i, fp1[i](-1));
  }
//  void * h2 = dlmopen (LM_ID_NEWLM, "libp.so", RTLD_LAZY);
//  if (h1 != h2)
//    {
//      printf ("loaded libp.so twice\n");
//    }
//  Lmid_t lmid1;
//  Lmid_t lmid2;
//  int status = dlinfo (h1, RTLD_DI_LMID, &lmid1);
//  if (status == 0)
//    {
//      printf ("got lmid1\n");
//    }
//  status = dlinfo (h2, RTLD_DI_LMID, &lmid2);
//  if (status == 0)
//    {
//      printf ("got lmid2\n");
//    }
//  if (lmid1 != lmid2)
//    {
//      printf ("yes, contexts are different !\n");
//    }
//  Fn fp1 = dlsym (h1, "libp_set_global");
//  Fn fq1 = dlsym (h1, "libq_set_global");
//  Fn fp2 = dlsym (h2, "libp_set_global");
//  Fn fq2 = dlsym (h2, "libq_set_global");
//  if (fp1(-1) == 0 &&
//      fp1(2) == -1 &&
//      fq1(-2) == 0 &&
//      fq1(-1) == -2 &&
//      fp2(-1) == 0 &&
//      fp2(2) == -1 &&
//      fq2(-2) == 0 &&
//      fq2(-1) == -2)
//    {
//      printf ("both libraries have separate symbols and global variables\n");
//    }
//
//  dlclose (h2);
  for( i=0;i<100;i++){
    dlclose (h1[i]);
  }



  return 0;
}
