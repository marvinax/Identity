/*
 * patchOrientationCorection.c
 *
 * Code generation for function 'patchOrientationCorection'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "patchOrientationCorection.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T_4x4
#define struct_emxArray_real_T_4x4

struct emxArray_real_T_4x4
{
  double data[16];
  int size[2];
};

#endif                                 /*struct_emxArray_real_T_4x4*/

#ifndef typedef_emxArray_real_T_4x4
#define typedef_emxArray_real_T_4x4

typedef struct emxArray_real_T_4x4 emxArray_real_T_4x4;

#endif                                 /*typedef_emxArray_real_T_4x4*/

#ifndef typedef_g_struct_T
#define typedef_g_struct_T

typedef struct {
  emxArray_real_T_4x4 data;
} g_struct_T;

#endif                                 /*typedef_g_struct_T*/

/* Function Definitions */
void patchOrientationCorection(const double circleSize[8], const double pArr[16],
  double pArr_ret[16])
{
  double sizeMatrix[8];
  g_struct_T sizeMatrix_cand[4];
  int itmp;
  double x[8];
  int i;
  double xtmp;
  int ixstart;
  double b_diff[4];
  double b_x[8];
  static const signed char iv8[8] = { 1, 1, 1, 1, 2, 1, 2, 1 };

  double y[8];
  boolean_T exitg1;
  static const signed char iv9[8] = { 4, 5, 6, 7, 0, 1, 2, 3 };

  static const signed char iv10[8] = { 3, 2, 1, 0, 7, 6, 5, 4 };

  /* % Put the patch into correct orientation */
  /*   The patch's current orientation and correct orientation are up to a  */
  /*   Dihedral group (D_2n, n = 4) transformation */
  /*   Chau-Wai Wong, Mar. 2015 */
  /*   Two larger corner circles are denoted with double parentheses */
  /*   */
  /*    (1)--((5)) */
  /*     |     | */
  /*    (2)---(6) */
  /*     |     | */
  /*    (3)--((7)) */
  /*     |     | */
  /*    (4)---(8) */
  /*   */
  memcpy(&sizeMatrix[0], &circleSize[0], sizeof(double) << 3);

  /*  4 possible orientations. a: rotation 90 deg, b: mirroring */
  /*  sizeMatrix_cand = cell(4,1); */
  /*  sizeMatrix_cand{1} = sizeMatrix;          % a = 0, b = 0 */
  /*  sizeMatrix_cand{2} = fliplr(sizeMatrix);  % a = 0, b = 1 */
  /*  sizeMatrix_cand{3} = flipud(sizeMatrix);  % a = 2, b = 1 */
  /*  sizeMatrix_cand{4} = rot90(sizeMatrix,2); % a = 2, b = 0 */
  /*  var size */
  sizeMatrix_cand[0].data.size[0] = 4;
  sizeMatrix_cand[0].data.size[1] = 2;
  for (itmp = 0; itmp < 8; itmp++) {
    sizeMatrix_cand[0].data.data[itmp] = sizeMatrix[itmp];
  }

  /*  a = 0, b = 0 */
  memcpy(&x[0], &sizeMatrix[0], sizeof(double) << 3);
  for (i = 0; i < 4; i++) {
    xtmp = x[i];
    x[i] = x[4 + i];
    x[4 + i] = xtmp;
  }

  sizeMatrix_cand[1].data.size[0] = 4;
  sizeMatrix_cand[1].data.size[1] = 2;
  for (itmp = 0; itmp < 8; itmp++) {
    sizeMatrix_cand[1].data.data[itmp] = x[itmp];
  }

  /*  a = 0, b = 1 */
  memcpy(&x[0], &sizeMatrix[0], sizeof(double) << 3);
  for (ixstart = 0; ixstart < 2; ixstart++) {
    for (i = 0; i < 2; i++) {
      xtmp = x[i + (ixstart << 2)];
      x[i + (ixstart << 2)] = x[((ixstart << 2) - i) + 3];
      x[((ixstart << 2) - i) + 3] = xtmp;
    }
  }

  sizeMatrix_cand[2].data.size[0] = 4;
  sizeMatrix_cand[2].data.size[1] = 2;
  for (itmp = 0; itmp < 8; itmp++) {
    sizeMatrix_cand[2].data.data[itmp] = x[itmp];
  }

  /*  a = 2, b = 1 */
  for (ixstart = 0; ixstart < 2; ixstart++) {
    for (i = 0; i < 4; i++) {
      x[i + (ixstart << 2)] = sizeMatrix[(((1 - ixstart) << 2) - i) + 3];
    }
  }

  sizeMatrix_cand[3].data.size[0] = 4;
  sizeMatrix_cand[3].data.size[1] = 2;
  for (itmp = 0; itmp < 8; itmp++) {
    sizeMatrix_cand[3].data.data[itmp] = x[itmp];
  }

  /*  a = 2, b = 0 */
  /*  weighted absolute error */
  for (i = 0; i < 4; i++) {
    for (itmp = 0; itmp < 8; itmp++) {
      b_x[itmp] = (double)iv8[itmp] - sizeMatrix_cand[i].data.data[itmp];
    }

    for (ixstart = 0; ixstart < 8; ixstart++) {
      y[ixstart] = fabs(b_x[ixstart]) * (double)iv8[ixstart];
    }

    xtmp = y[0];
    for (ixstart = 0; ixstart < 7; ixstart++) {
      xtmp += y[ixstart + 1];
    }

    b_diff[i] = xtmp;
  }

  ixstart = 1;
  xtmp = b_diff[0];
  itmp = 1;
  if (rtIsNaN(b_diff[0])) {
    i = 2;
    exitg1 = false;
    while ((!exitg1) && (i < 5)) {
      ixstart = i;
      if (!rtIsNaN(b_diff[i - 1])) {
        xtmp = b_diff[i - 1];
        itmp = i;
        exitg1 = true;
      } else {
        i++;
      }
    }
  }

  if (ixstart < 4) {
    while (ixstart + 1 < 5) {
      if (b_diff[ixstart] < xtmp) {
        xtmp = b_diff[ixstart];
        itmp = ixstart + 1;
      }

      ixstart++;
    }
  }

  /* if smallestDiff==0 */
  switch (itmp) {
   case 1:
    memcpy(&pArr_ret[0], &pArr[0], sizeof(double) << 4);
    break;

   case 2:
    for (itmp = 0; itmp < 8; itmp++) {
      for (ixstart = 0; ixstart < 2; ixstart++) {
        pArr_ret[ixstart + (itmp << 1)] = pArr[ixstart + (iv9[itmp] << 1)];
      }
    }
    break;

   case 3:
    for (itmp = 0; itmp < 8; itmp++) {
      for (ixstart = 0; ixstart < 2; ixstart++) {
        pArr_ret[ixstart + (itmp << 1)] = pArr[ixstart + (iv10[itmp] << 1)];
      }
    }
    break;

   case 4:
    for (itmp = 0; itmp < 8; itmp++) {
      for (ixstart = 0; ixstart < 2; ixstart++) {
        pArr_ret[ixstart + (itmp << 1)] = pArr[ixstart + ((7 - itmp) << 1)];
      }
    }
    break;

   default:
    /*  this case does not happen due to the logic of the algorithm, */
    /*  however, we provide this path for Matlab Coder compiler. */
    memcpy(&pArr_ret[0], &pArr[0], sizeof(double) << 4);
    break;
  }

  /*  else */
  /*      pArr_ret = pArr; */
  /*  end */
}

/* End of code generation (patchOrientationCorection.c) */
