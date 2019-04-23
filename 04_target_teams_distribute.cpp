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

#pragma omp target teams map(from:y[:N]) map(to:x[:N]) num_teams(4)
#pragma omp distribute
  for(int i=0; i<N; i++ )
    {
      y[i] = x[i];
      int team = omp_get_team_num();
      int nteams = omp_get_num_teams();
      int tid = omp_get_thread_num();
      int nthreads = omp_get_num_threads(); 

      printf( "i:%d for Team %d out of %d teams\nThread %d of out %d threads in the team.\n",
	      i,team, nteams, tid, nthreads );

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
