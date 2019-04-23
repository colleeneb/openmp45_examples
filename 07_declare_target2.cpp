
#pragma omp declare target

int dev_c[128];

int flip_sign( int a )
{
  return -a;
}

#pragma omp end declare target
