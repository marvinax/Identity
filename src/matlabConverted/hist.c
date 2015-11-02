/*
 * hist.c
 *
 * Code generation for function 'hist'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "hist.h"
#include "getPowderAndQr_emxutil.h"
#include "eps.h"
#include "histc.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void hist(const emxArray_real_T *Y, emxArray_real_T *no)
{
  int Y_idx_0;
  double edges[257];
  int b_Y[1];
  emxArray_real_T c_Y;
  double nn[257];
  double b_no[256];
  Y_idx_0 = Y->size[0];
  if (Y_idx_0 == 0) {
    Y_idx_0 = no->size[0] * no->size[1];
    no->size[0] = 256;
    no->size[1] = 1;
    emxEnsureCapacity((emxArray__common *)no, Y_idx_0, (int)sizeof(double));
    for (Y_idx_0 = 0; Y_idx_0 < 256; Y_idx_0++) {
      no->data[Y_idx_0] = 0.0;
    }
  } else {
    for (Y_idx_0 = 0; Y_idx_0 < 255; Y_idx_0++) {
      edges[1 + Y_idx_0] = (double)Y_idx_0 + 0.5;
    }

    edges[0] = rtMinusInf;
    edges[256] = rtInf;
    for (Y_idx_0 = 0; Y_idx_0 < 255; Y_idx_0++) {
      edges[Y_idx_0 + 1] += eps(edges[Y_idx_0 + 1]);
    }

    b_Y[0] = Y->size[0];
    c_Y = *Y;
    c_Y.size = (int *)&b_Y;
    c_Y.numDimensions = 1;
    histc(&c_Y, edges, nn);
    memcpy(&b_no[0], &nn[0], sizeof(double) << 8);
    b_no[255] = nn[255] + nn[256];
    Y_idx_0 = no->size[0] * no->size[1];
    no->size[0] = 1;
    no->size[1] = 256;
    emxEnsureCapacity((emxArray__common *)no, Y_idx_0, (int)sizeof(double));
    for (Y_idx_0 = 0; Y_idx_0 < 256; Y_idx_0++) {
      no->data[Y_idx_0] = b_no[Y_idx_0];
    }
  }
}

/* End of code generation (hist.c) */
