#include <stdio.h>
#include <omp.h>
#include <math.h>
#define N 1024
int main( int argv, char** argc ) {
  int x[N];
  int y[N];
  int errors = 0;
  // initialize
  for(int i=0; i<N; i++ ) {
      y[i] = 0;
      x[i] = i;
    }

#pragma omp target map(y,x)
  {
    int i;
    for(i=0;i<N;i++)
      y[i] = i+N;

    for(i=0;i<N;i++)
      x[i] = y[i];
  }

  // error check
  for(int i=0; i<N; i++ )
    {
      if( x[i] != i+N ) errors++;
    }

  if( errors != 0 )
    printf("Failed!\n");
  else
    printf("Success!\n");

  return 0;
}
