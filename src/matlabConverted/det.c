/*
 * det.c
 *
 * Code generation for function 'det'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "det.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
double det(const double x[4])
{
  double y;
  double b_x[4];
  int ix;
  signed char ipiv[2];
  int iy;
  int k;
  double temp;
  boolean_T isodd;
  for (ix = 0; ix < 4; ix++) {
    b_x[ix] = x[ix];
  }

  for (ix = 0; ix < 2; ix++) {
    ipiv[ix] = (signed char)(1 + ix);
  }

  ix = 0;
  if (fabs(x[1]) > fabs(x[0])) {
    ix = 1;
  }

  if (x[ix] != 0.0) {
    if (ix != 0) {
      ipiv[0] = 2;
      ix = 0;
      iy = 1;
      for (k = 0; k < 2; k++) {
        temp = b_x[ix];
        b_x[ix] = b_x[iy];
        b_x[iy] = temp;
        ix += 2;
        iy += 2;
      }
    }

    b_x[1] /= b_x[0];
  }

  if (b_x[2] != 0.0) {
    b_x[3] += b_x[1] * -b_x[2];
  }

  y = b_x[0] * b_x[3];
  isodd = false;
  if (ipiv[0] > 1) {
    isodd = true;
  }

  if (isodd) {
    y = -y;
  }

  return y;
}

/* End of code generation (det.c) */
