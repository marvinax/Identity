/*
 * normalizeControlPoints.c
 *
 * Code generation for function 'normalizeControlPoints'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "normalizeControlPoints.h"
#include "getPowderAndQr_rtwutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void normalizeControlPoints(const double pts[8], double ptsNorm[8], double
  normMatrixInv[9])
{
  double cent[2];
  int ix;
  int iy;
  int i;
  int ak;
  double c_sumOfPointDistancesFromOrigin;
  int k;
  double cv[4];
  ix = 0;
  iy = -1;
  for (i = 0; i < 2; i++) {
    ak = ix;
    ix++;
    c_sumOfPointDistancesFromOrigin = pts[ak];
    for (k = 0; k < 3; k++) {
      ix++;
      c_sumOfPointDistancesFromOrigin += pts[ix - 1];
    }

    iy++;
    cent[iy] = c_sumOfPointDistancesFromOrigin;
  }

  for (ak = 0; ak < 2; ak++) {
    cent[ak] /= 4.0;
  }

  ak = 0;
  ix = 0;
  for (iy = 0; iy < 6; iy += 4) {
    for (k = 0; k < 4; k++) {
      cv[k] = pts[ak + k] - cent[ix];
    }

    for (k = 0; k < 4; k++) {
      ptsNorm[iy + k] = cv[k];
    }

    ak += 4;
    ix++;
  }

  for (k = 0; k < 4; k++) {
    c_sumOfPointDistancesFromOrigin = rt_hypotd_snf(ptsNorm[k], ptsNorm[4 + k]);
    cv[k] = c_sumOfPointDistancesFromOrigin * c_sumOfPointDistancesFromOrigin;
  }

  c_sumOfPointDistancesFromOrigin = cv[0];
  for (k = 0; k < 3; k++) {
    c_sumOfPointDistancesFromOrigin += cv[k + 1];
  }

  if (c_sumOfPointDistancesFromOrigin > 0.0) {
    c_sumOfPointDistancesFromOrigin = 2.8284271247461903 / sqrt
      (c_sumOfPointDistancesFromOrigin);
  } else {
    c_sumOfPointDistancesFromOrigin = 1.0;
  }

  for (ak = 0; ak < 8; ak++) {
    ptsNorm[ak] *= c_sumOfPointDistancesFromOrigin;
  }

  normMatrixInv[0] = 1.0 / c_sumOfPointDistancesFromOrigin;
  normMatrixInv[3] = 0.0;
  normMatrixInv[6] = 0.0;
  normMatrixInv[1] = 0.0;
  normMatrixInv[4] = 1.0 / c_sumOfPointDistancesFromOrigin;
  normMatrixInv[7] = 0.0;
  normMatrixInv[2] = cent[0];
  normMatrixInv[5] = cent[1];
  normMatrixInv[8] = 1.0;
}

/* End of code generation (normalizeControlPoints.c) */
