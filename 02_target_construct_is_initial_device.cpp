#include <stdio.h>
#include <omp.h>
int main( int argv, char** argc ) {

  printf( "Number of devices: %d\n", omp_get_num_devices() );
  printf( "Default device: %d\n", omp_get_default_device()  );
  printf( "We %s running on the initial device.\n", omp_is_initial_device() ? "are": "are not" );

#pragma omp target map(tofrom: a)
  {
    a=omp_is_initial_device();
  }

  printf( "output of omp_is_initial_device in the target region: %d\n",
	  a );

  return 0;
}
