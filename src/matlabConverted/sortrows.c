/*
 * sortrows.c
 *
 * Code generation for function 'sortrows'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "sortrows.h"
#include "getPowderAndQr_emxutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void apply_row_permutation(emxArray_real_T *y, const emxArray_int32_T *idx)
{
  emxArray_real_T *ycol;
  int m;
  int unnamed_idx_0;
  int i;
  b_emxInit_real_T(&ycol, 1);
  m = y->size[0];
  unnamed_idx_0 = y->size[0];
  i = ycol->size[0];
  ycol->size[0] = unnamed_idx_0;
  emxEnsureCapacity((emxArray__common *)ycol, i, (int)sizeof(double));
  for (unnamed_idx_0 = 0; unnamed_idx_0 < 2; unnamed_idx_0++) {
    for (i = 0; i + 1 <= m; i++) {
      ycol->data[i] = y->data[(idx->data[i] + y->size[0] * unnamed_idx_0) - 1];
    }

    for (i = 0; i + 1 <= m; i++) {
      y->data[i + y->size[0] * unnamed_idx_0] = ycol->data[i];
    }
  }

  emxFree_real_T(&ycol);
}

/* End of code generation (sortrows.c) */
