/*
 * imref2d.c
 *
 * Code generation for function 'imref2d'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "imref2d.h"
#include "getPowderAndQr_emxutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void imref2d_imref2d(const double imageSizeIn[2], double obj_XWorldLimits[2],
                     double obj_YWorldLimits[2], double obj_ImageSize[2], double
                     *obj_PixelExtentInWorldX, double *obj_PixelExtentInWorldY)
{
  double dv8[2];
  double dv9[2];
  int i21;
  obj_ImageSize[0] = imageSizeIn[0];
  obj_ImageSize[1] = imageSizeIn[1];
  dv8[0] = 0.0;
  dv8[1] = imageSizeIn[1];
  dv9[0] = 0.0;
  dv9[1] = imageSizeIn[0];
  for (i21 = 0; i21 < 2; i21++) {
    obj_XWorldLimits[i21] = 0.5 + dv8[i21];
    obj_YWorldLimits[i21] = 0.5 + dv9[i21];
  }

  *obj_PixelExtentInWorldX = 1.0;
  *obj_PixelExtentInWorldY = 1.0;
}

void imref2d_worldToIntrinsic(const emxArray_real_T *xWorld, const
  emxArray_real_T *yWorld, emxArray_real_T *xi, emxArray_real_T *yi)
{
  int i24;
  int loop_ub;
  i24 = xi->size[0] * xi->size[1];
  xi->size[0] = xWorld->size[0];
  xi->size[1] = xWorld->size[1];
  emxEnsureCapacity((emxArray__common *)xi, i24, (int)sizeof(double));
  loop_ub = xWorld->size[0] * xWorld->size[1];
  for (i24 = 0; i24 < loop_ub; i24++) {
    xi->data[i24] = 0.5 + (xWorld->data[i24] - 0.5);
  }

  i24 = yi->size[0] * yi->size[1];
  yi->size[0] = yWorld->size[0];
  yi->size[1] = yWorld->size[1];
  emxEnsureCapacity((emxArray__common *)yi, i24, (int)sizeof(double));
  loop_ub = yWorld->size[0] * yWorld->size[1];
  for (i24 = 0; i24 < loop_ub; i24++) {
    yi->data[i24] = 0.5 + (yWorld->data[i24] - 0.5);
  }
}

/* End of code generation (imref2d.c) */
