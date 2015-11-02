/*
 * fliplr.c
 *
 * Code generation for function 'fliplr'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "fliplr.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void b_fliplr(boolean_T x[1024])
{
  int b_j1;
  int i;
  boolean_T xtmp;
  for (b_j1 = 0; b_j1 < 16; b_j1++) {
    for (i = 0; i < 32; i++) {
      xtmp = x[i + (b_j1 << 5)];
      x[i + (b_j1 << 5)] = x[i + ((31 - b_j1) << 5)];
      x[i + ((31 - b_j1) << 5)] = xtmp;
    }
  }
}

void c_fliplr(boolean_T x[441])
{
  int b_j1;
  int i;
  boolean_T xtmp;
  for (b_j1 = 0; b_j1 < 10; b_j1++) {
    for (i = 0; i < 21; i++) {
      xtmp = x[i + 21 * b_j1];
      x[i + 21 * b_j1] = x[i + 21 * (20 - b_j1)];
      x[i + 21 * (20 - b_j1)] = xtmp;
    }
  }
}

void fliplr(unsigned int x_data[], int x_size[2])
{
  int m;
  int n;
  int nd2;
  int b_j1;
  unsigned int xtmp;
  m = x_size[0];
  n = x_size[1] - 1;
  nd2 = x_size[1] >> 1;
  b_j1 = 1;
  while (b_j1 <= nd2) {
    for (b_j1 = 0; b_j1 + 1 <= m; b_j1++) {
      xtmp = x_data[b_j1];
      x_data[b_j1] = x_data[b_j1 + x_size[0] * n];
      x_data[b_j1 + x_size[0] * n] = xtmp;
    }

    b_j1 = 2;
  }
}

/* End of code generation (fliplr.c) */
