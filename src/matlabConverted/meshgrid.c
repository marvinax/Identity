/*
 * meshgrid.c
 *
 * Code generation for function 'meshgrid'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "meshgrid.h"
#include "getPowderAndQr_emxutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void b_meshgrid(const double x[13], const double y[13], double xx[169], double
                yy[169])
{
  int jcol;
  int ibtile;
  int itilerow;
  for (jcol = 0; jcol < 13; jcol++) {
    ibtile = jcol * 13;
    for (itilerow = 0; itilerow < 13; itilerow++) {
      xx[ibtile + itilerow] = x[jcol];
    }
  }

  for (jcol = 0; jcol < 13; jcol++) {
    ibtile = jcol * 13;
    memcpy(&yy[ibtile], &y[0], 13U * sizeof(double));
  }
}

void c_meshgrid(const double x[200], const double y[200], double xx[40000],
                double yy[40000])
{
  int jcol;
  int ibtile;
  int itilerow;
  for (jcol = 0; jcol < 200; jcol++) {
    ibtile = jcol * 200;
    for (itilerow = 0; itilerow < 200; itilerow++) {
      xx[ibtile + itilerow] = x[jcol];
    }
  }

  for (jcol = 0; jcol < 200; jcol++) {
    ibtile = jcol * 200;
    memcpy(&yy[ibtile], &y[0], 200U * sizeof(double));
  }
}

void meshgrid(const emxArray_real_T *x, const emxArray_real_T *y,
              emxArray_real_T *xx, emxArray_real_T *yy)
{
  emxArray_real_T *a;
  int ibtile;
  int x_idx_0;
  unsigned int varargin_1_idx_0;
  int k;
  int y_idx_0;
  emxInit_real_T(&a, 2);
  if ((x->size[1] == 0) || (y->size[1] == 0)) {
    ibtile = xx->size[0] * xx->size[1];
    xx->size[0] = 0;
    xx->size[1] = 0;
    emxEnsureCapacity((emxArray__common *)xx, ibtile, (int)sizeof(double));
    ibtile = yy->size[0] * yy->size[1];
    yy->size[0] = 0;
    yy->size[1] = 0;
    emxEnsureCapacity((emxArray__common *)yy, ibtile, (int)sizeof(double));
  } else {
    x_idx_0 = x->size[1];
    ibtile = a->size[0] * a->size[1];
    a->size[0] = 1;
    a->size[1] = x_idx_0;
    emxEnsureCapacity((emxArray__common *)a, ibtile, (int)sizeof(double));
    for (ibtile = 0; ibtile < x_idx_0; ibtile++) {
      a->data[a->size[0] * ibtile] = x->data[ibtile];
    }

    varargin_1_idx_0 = (unsigned int)y->size[1];
    ibtile = xx->size[0] * xx->size[1];
    xx->size[0] = (int)varargin_1_idx_0;
    xx->size[1] = a->size[1];
    emxEnsureCapacity((emxArray__common *)xx, ibtile, (int)sizeof(double));
    for (x_idx_0 = 0; x_idx_0 + 1 <= a->size[1]; x_idx_0++) {
      ibtile = x_idx_0 * (int)varargin_1_idx_0;
      for (k = 1; k <= (int)varargin_1_idx_0; k++) {
        xx->data[(ibtile + k) - 1] = a->data[x_idx_0];
      }
    }

    varargin_1_idx_0 = (unsigned int)x->size[1];
    y_idx_0 = y->size[1];
    ibtile = yy->size[0] * yy->size[1];
    yy->size[0] = y_idx_0;
    yy->size[1] = (int)varargin_1_idx_0;
    emxEnsureCapacity((emxArray__common *)yy, ibtile, (int)sizeof(double));
    y_idx_0 = y->size[1];
    for (x_idx_0 = 1; x_idx_0 <= (int)varargin_1_idx_0; x_idx_0++) {
      ibtile = (x_idx_0 - 1) * y_idx_0;
      for (k = 1; k <= y_idx_0; k++) {
        yy->data[(ibtile + k) - 1] = y->data[k - 1];
      }
    }
  }

  emxFree_real_T(&a);
}

/* End of code generation (meshgrid.c) */
