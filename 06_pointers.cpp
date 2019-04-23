#include "stdio.h"
int main()
{
  int A[128];
  int B[128];
  int *p = A, *q=B;
  //  int *q = B;

  A[100] = 8;
  B[100] = 6;

  // only A is mapped, not B
#pragma omp target data map(A)
{
    // since p points to A, which is mapped, this would work, and print a value
#pragma omp target map(p[:0])
    printf( "Explicitly mapped p: %d, should be 8\n", p[100]);
    // since q points to B, which is unmapped, this should be NULL
#pragma omp target map(q[:0])
    printf( "Explicitly mapped q: %p, should be NULL if memory is not shared\n", q);
    // since p points to A, which is mapped, this would work, and print a value
    // unmapped pointers default to tofrom:p[:0]
#pragma omp target
    printf( "Implicitly mapped p: %d, should be 8\n", p[100]);
    // error! maps the pointer as a scalar, just copies the host address to the device
    // host address doesn't exist on the device, so this is an error
#pragma omp target map(p)
    printf( "Explicitly mapped pointer p: %d, should crash on accelerator\n", p[100]);

  }
      return 0;
}
