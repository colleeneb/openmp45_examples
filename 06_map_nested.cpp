#include <stdio.h>
#define N 1024
int main( int argv, char** argc ) {
  double a[N];
  double b[N];
  int t[N];
  int errors = 0;

  // initialize
  for(int i=0;i<N;i++) {
      a[i] = -1;
      b[i] = i;
  }

#pragma omp target data map(from:a) map(to:b) map(alloc:t) // map-enter
  {
#pragma omp target map(always,from:t) // map-enter
  for(int i=0;i<N;i++) {
      t[i] = i;
  } // map-exit

#pragma omp target map(a,b,t) // map-enter
  for(int i=0;i<N;i++) {
      a[i] = b[t[i]];
  } // map-exit

  } // map-exit

  // error check
  for(int i=0; i<N; i++ )
    {
      if( a[i] != b[i] ) errors++;
    }

  if( errors != 0 )
    printf("Failed!\n");
  else
    printf("Success!\n");

  return 0;
}
