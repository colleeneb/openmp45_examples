#include "stdio.h"

#define N 10
#define L (N-5)

int B[N];
#pragma omp declare target(B)

void update( int* B1, int l, int n )
{
  for(int i=l; i< n; i++)
    B1[i] *= 2;
}

int main()
{
  int errors = 0;
  
  // initialize
  for(int i=0; i< N; i++)
    B[i] = i;

  // make host and device consistent
#pragma omp target update to( B )

#pragma omp target 
    for(int i=L; i< N; i++)
      B[i] = i+1;

    // gets the last L elements in B from the accelerator, makes
    // the host consistent
#pragma omp target update from( B[L:N-L] )  
    update( B, L, N );
    // gets the last L elements in B from the host, makes
    // the accelerator consistent
#pragma omp target update to( B[L:N-L])  

  // error check
  for(int i=0; i< L; i++)
     if( B[i] != i ) errors++;
  for(int i=L; i< N; i++)
      if( B[i] != (i+1)*2 ) errors++;

  if( errors != 0 )
    printf( "Failed!\n" );
  else
    printf( "Success!\n" );

  return 0;
}
