#include "stdio.h"

#define N 1024
int A[N], B[N];

int main()
{
  int errors = 0;
  int e, c = 4, d = 5;

  for( int i=0;i<N;i++ )
    B[i] = i;

#pragma omp target data map(B)
  {
#pragma omp target map(B) map(always,from:A) firstprivate(c,d)
    for(int i=0; i< N; i++)
      A[i] = B[i]*c+d;

    e = A[10];

#pragma omp target map(B) firstprivate(e)
    for(int i=0; i< N; i++)
      B[i] = B[i] * e;
  }

  // error check
  for(int i=0; i< N; i++)
    {
      if( B[i] != i*(10*c+d) )  {
	errors++;
      }
    }

  if( errors != 0 )
    printf( "Failed!\n" );
  else
    printf( "Success!\n" );

  return 0;
}
