#include "stdio.h"
int main()
{
  int A[128];
  int B[128];
  int *p = A;
  int *q = B;

  A[100] = 8;
  B[100] = 6;

  // only A is mapped, not B
#pragma omp target data map(A)
{
  // A is previously mapped. Since p was set to the original value of A,
  // it is mapped to the device address of A
#pragma omp target map(p[:0])
    printf( "Explicitly mapped p: %d, should be 8\n", p[100]);

    // B is not previously mapped. Since q was set to the original value
    // of B, it is set to NULL. Possibly common pitfall.
#pragma omp target map(q[:0])
    printf( "Explicitly mapped q: %p, should be NULL if memory is not shared\n", q);

    // Pointers that are not explicitly mapped are treated as
    // map(tofrom: p[0:0]), so this is the same as (1)
#pragma omp target
    printf( "Implicitly mapped p: %d, should be 8\n", p[100]);

    // Pointer p is explicitly mapped as an address, so this copies
    // the host address to the device, which is an error unless they share
    // the same address space
#pragma omp target map(p)
    printf( "Explicitly mapped pointer p: %d, should error on accelerator\n", p[100]);

  }
      return 0;
}
