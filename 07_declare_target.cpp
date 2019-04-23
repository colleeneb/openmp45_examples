#include "stdio.h"

int pos = 10;
extern int dev_c[128];
#pragma omp declare target(pos, dev_c)

extern int flip_sign(int);
#pragma omp declare target to(flip_sign)

#pragma omp declare target
void compute( int a, int b) {
  dev_c[pos] = flip_sign(a+b*8);
}
#pragma omp end declare target

int main()
{
#pragma omp target
  compute(4,5);

  // error check
#pragma omp target
  {
    if( dev_c[10] !=-44 ) 
      printf("Failed! %d\n", dev_c[10]);
    else
      printf("Success! %d\n", dev_c[10]);
  }
  return 0;
}
