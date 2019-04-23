#include "stdio.h"

class myArray {
public:
  int length;
  double *ptr;
  void allocate(int l) {
    double *p = new double[l];
    ptr = p;
    length = l;
#pragma omp target enter data map(alloc:p[0:length])
  }

  void release() {
    double *p = ptr;
#pragma omp target exit data map(release:p[0:length])
    delete[] p;
    ptr = 0;
    length = 0;
  }

};

int main()
{
  myArray arr;
  arr.allocate(5);
  arr.release();
  return 0;
}
