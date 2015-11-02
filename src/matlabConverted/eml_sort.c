/*
 * eml_sort.c
 *
 * Code generation for function 'eml_sort'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "eml_sort.h"
#include "getPowderAndQr_emxutil.h"
#include "median.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void eml_sort(const double x_data[], const int x_size[2], double y_data[], int
              y_size[2], int idx_data[], int idx_size[2])
{
  int vlen;
  double vwork_data[30];
  int vwork_size[1];
  signed char iv2[2];
  int ix;
  int k;
  emxArray_int32_T *iidx;
  emxArray_int32_T *r18;
  emxArray_real_T b_vwork_data;
  vlen = x_size[1] - 1;
  vwork_size[0] = (signed char)x_size[1];
  for (ix = 0; ix < 2; ix++) {
    y_size[ix] = x_size[ix];
    iv2[ix] = (signed char)x_size[ix];
  }

  idx_size[0] = 1;
  idx_size[1] = iv2[1];
  ix = 0;
  for (k = 0; k <= vlen; k++) {
    vwork_data[k] = x_data[ix];
    ix++;
  }

  emxInit_int32_T(&iidx, 1);
  emxInit_int32_T(&r18, 1);
  b_vwork_data.data = (double *)&vwork_data;
  b_vwork_data.size = (int *)&vwork_size;
  b_vwork_data.allocatedSize = 30;
  b_vwork_data.numDimensions = 1;
  b_vwork_data.canFreeData = false;
  eml_sort_idx(&b_vwork_data, r18);
  ix = iidx->size[0];
  iidx->size[0] = r18->size[0];
  emxEnsureCapacity((emxArray__common *)iidx, ix, (int)sizeof(int));
  k = r18->size[0];
  for (ix = 0; ix < k; ix++) {
    iidx->data[ix] = r18->data[ix];
  }

  emxFree_int32_T(&r18);
  ix = 0;
  for (k = 0; k <= vlen; k++) {
    y_data[ix] = vwork_data[iidx->data[k] - 1];
    idx_data[ix] = iidx->data[k];
    ix++;
  }

  emxFree_int32_T(&iidx);
}

/* End of code generation (eml_sort.c) */
