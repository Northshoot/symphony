#include <stdio.h>

static __attribute__ ((constructor))
  void constructor (void)
  {               \
    printf ("libtos constructor\n");
  }               \
  static __attribute__ ((destructor))
  void destructor (void)
  {
    printf ("libtos destructor\n");
  }


   extern int test_func(int i)
      {
        printf ("test_func: %d\n",i );
        return i;
      }

