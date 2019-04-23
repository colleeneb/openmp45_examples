#include <stdio.h>
#include <omp.h>
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

  // splits the "N" in two, gives half to each team
#pragma omp target teams map(from:y[:N]) map(to:x[:N]) num_teams(2)
#pragma omp distribute dist_schedule(static,N/2)
  for(int j=0; j<N; j+=N/2 )
    {
#pragma omp parallel num_threads(4)
#pragma omp for
      for(int i=j; i< j+N/2; i++)
	y[i] = x[i];
    }

  // error check
  for(int i=0; i<N; i++ )
    {
      if( y[i] != x[i] ) errors++;
    }

  if( errors != 0 )
    printf("Failed!\n");
  else
    printf("Success!\n");

  return 0;
}
