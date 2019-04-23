#include <stdio.h>
#define N 1024

int main( int argv, char** argc ) {

  int s[N];
  int v[N];
  int i=0, errors=0;
  
  for(i=0;i<N;i++)
    {
      v[i] = 0;
      s[i] = -1;
    }

  // execute on the device
#pragma omp target nowait map(v[0:N])
  for(int i=0;i<N;i++)
    v[i] = i;

  // execute on the host
  for(i=0;i<N;i++)
    s[i] = i;
#pragma omp taskwait

  // error check
  for(i=0; i<N; i++ )
    {
      if( s[i] != v[i] ) errors++;
    }

  if( errors != 0 )
    printf("Failed!\n");
  else
    printf("Success!\n");

  return 0;
}
