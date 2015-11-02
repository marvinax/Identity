/*
 * mean.c
 *
 * Code generation for function 'mean'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "mean.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void b_mean(const double x_data[], const int x_size[2], double y[2])
{
  int ix;
  int iy;
  int i;
  int ixstart;
  double s;
  ix = 0;
  iy = -1;
  for (i = 0; i < 2; i++) {
    ixstart = ix;
    ix++;
    s = x_data[ixstart];
    for (ixstart = 2; ixstart <= x_size[0]; ixstart++) {
      ix++;
      s += x_data[ix - 1];
    }

    iy++;
    y[iy] = s;
  }

  for (ixstart = 0; ixstart < 2; ixstart++) {
    y[ixstart] /= (double)x_size[0];
  }
}

double c_mean(const double x[16])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 15; k++) {
    y += x[k + 1];
  }

  y /= 16.0;
  return y;
}

double d_mean(const double x[8])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 7; k++) {
    y += x[k + 1];
  }

  y /= 8.0;
  return y;
}

double e_mean(const double x[169])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 168; k++) {
    y += x[k + 1];
  }

  y /= 169.0;
  return y;
}

double mean(const emxArray_real_T *x)
{
  double y;
  int k;
  if (x->size[0] == 0) {
    y = 0.0;
  } else {
    y = x->data[0];
    for (k = 2; k <= x->size[0]; k++) {
      y += x->data[k - 1];
    }
  }

  y /= (double)x->size[0];
  return y;
}

/* End of code generation (mean.c) */
