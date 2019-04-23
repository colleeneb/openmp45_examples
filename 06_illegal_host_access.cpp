#include <stdio.h>
#include <omp.h>
int main( int argv, char** argc ) {

  int errors = 0;
  int *hptr = (int *)malloc(100*sizeof(int));

#pragma omp target map(hptr) // correct: map(hptr[0:100])
  {
  for( int i=0; i< 100;i++)
    hptr[i] = i;
  }

  // error check
  for(int i=0; i<100; i++ )
    {
      if( hptr[i] != i ) errors++;
    }

  if( errors != 0 )
    printf("Failed!\n");
  else
    printf("Success!\n");


  return 0;
}
