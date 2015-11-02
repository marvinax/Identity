/*
 * TensorGriddedInterp.c
 *
 * Code generation for function 'TensorGriddedInterp'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "TensorGriddedInterp.h"
#include "ppval.h"
#include "getPowderAndQr_emxutil.h"
#include "spline.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void TensorGriddedInterp(const emxArray_real_T *varargin_1, const
  emxArray_real_T *varargin_2, const emxArray_real_T *varargin_3, const
  emxArray_real_T *varargin_4, const emxArray_real_T *varargin_5,
  emxArray_real_T *yi)
{
  emxArray_real_T *ppk_breaks;
  emxArray_real_T *ppk_coefs;
  emxArray_real_T *varargout_1;
  int nxxi;
  int varargin_5_idx_0;
  int i;
  emxArray_real_T *vkj;
  emxInit_real_T(&ppk_breaks, 2);
  c_emxInit_real_T(&ppk_coefs, 3);
  emxInit_real_T(&varargout_1, 2);
  nxxi = varargin_5->size[0];
  spline(varargin_2, varargin_3, ppk_breaks, ppk_coefs);
  varargin_5_idx_0 = varargin_5->size[0];
  i = varargout_1->size[0] * varargout_1->size[1];
  varargout_1->size[0] = varargin_5_idx_0;
  emxEnsureCapacity((emxArray__common *)varargout_1, i, (int)sizeof(double));
  varargin_5_idx_0 = varargin_3->size[0];
  i = varargout_1->size[0] * varargout_1->size[1];
  varargout_1->size[1] = varargin_5_idx_0;
  emxEnsureCapacity((emxArray__common *)varargout_1, i, (int)sizeof(double));
  varargin_5_idx_0 = varargin_5->size[0] * varargin_3->size[0];
  for (i = 0; i < varargin_5_idx_0; i++) {
    varargout_1->data[i] = 0.0;
  }

  varargin_5_idx_0 = 0;
  b_emxInit_real_T(&vkj, 1);
  while (varargin_5_idx_0 <= nxxi - 1) {
    ppval(ppk_breaks, ppk_coefs, varargin_5->data[varargin_5_idx_0], vkj);
    for (i = 0; i < vkj->size[0]; i++) {
      varargout_1->data[(int)((1.0 + (double)varargin_5_idx_0) + ((1.0 + (double)
        i) - 1.0) * (double)nxxi) - 1] = vkj->data[i];
    }

    varargin_5_idx_0++;
  }

  nxxi = varargin_4->size[0];
  spline(varargin_1, varargout_1, ppk_breaks, ppk_coefs);
  varargin_5_idx_0 = varargin_4->size[0];
  i = yi->size[0] * yi->size[1];
  yi->size[0] = varargin_5_idx_0;
  emxEnsureCapacity((emxArray__common *)yi, i, (int)sizeof(double));
  varargin_5_idx_0 = varargin_5->size[0];
  i = yi->size[0] * yi->size[1];
  yi->size[1] = varargin_5_idx_0;
  emxEnsureCapacity((emxArray__common *)yi, i, (int)sizeof(double));
  varargin_5_idx_0 = varargin_4->size[0] * varargin_5->size[0];
  emxFree_real_T(&varargout_1);
  for (i = 0; i < varargin_5_idx_0; i++) {
    yi->data[i] = 0.0;
  }

  for (varargin_5_idx_0 = 0; varargin_5_idx_0 < nxxi; varargin_5_idx_0++) {
    ppval(ppk_breaks, ppk_coefs, varargin_4->data[varargin_5_idx_0], vkj);
    for (i = 0; i < vkj->size[0]; i++) {
      yi->data[(int)((1.0 + (double)varargin_5_idx_0) + ((1.0 + (double)i) - 1.0)
                     * (double)nxxi) - 1] = vkj->data[i];
    }
  }

  emxFree_real_T(&vkj);
  emxFree_real_T(&ppk_coefs);
  emxFree_real_T(&ppk_breaks);
}

/* End of code generation (TensorGriddedInterp.c) */
