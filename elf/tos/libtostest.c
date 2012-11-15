#include <stdio.h>

static __attribute__ ((constructor))
  void constructor (void)
  {
    printf ("libtos constructor\n");
  }
  static __attribute__ ((destructor))
  void destructor (void)
  {
    printf ("libtos destructor\n");
  }


   extern long int tickFired(int i)
      {
        printf ("tickFired: %d\n",i );
        return i;
      }

