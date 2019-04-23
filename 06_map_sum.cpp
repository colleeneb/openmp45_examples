#include <stdio.h>
#include <omp.h>
#define N 1024
int main( int argv, char** argc ) {
  int x[N];
  int errors = 0;
  int sum = 0;
  // initialize
  for(int i=0; i<N; i++ ) {
      x[i] = i;
    }

#pragma omp target map(to:x[:N]) //map(tofrom:sum)
  for(int j=0; j<N; j++ )
    {
	sum+=x[j];
    }

  // error check
  if( sum != N*(N-1)/2 ) errors++;

  if( errors != 0 )
    printf("Failed! %d\n", sum);
  else
    printf("Success!\n");

  return 0;
}
