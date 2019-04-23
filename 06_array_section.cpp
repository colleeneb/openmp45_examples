#include "stdio.h"

#define BIG 100
#define N (1024*1024)
int a[N*BIG];

int main()
{
  int errors = 0;
  int c = 1;

  for(int k=0; k< N*BIG; k+=N) {
#pragma omp target map(from: a[k:N]) firstprivate(c)
    for( int i=0; i<N;i++) {
      a[k+i] = k+i * c;
    }
  }
      // error check
      for( int k=0; k< N*BIG; k++ )
	{
	  if( a[k] != k ) errors++;
	}

      if( errors > 0)
	printf( "errors!\n" );
      else
	printf( "Success!\n" );

      return 0;
}
