/*
 * myImresize.c
 *
 * Code generation for function 'myImresize'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "myImresize.h"
#include "imwarp.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void myImresize(const emxArray_uint8_T *img, emxArray_uint8_T *imgRet)
{
  int i37;
  double dim[2];
  double tform_T[9];
  static const double t[9] = { 3.0, 0.0, 0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 1.0 };

  double obj_ImageSize[2];

  /* % Use affine transform with to replace imresize(.) in order for the code */
  /*   to be converted to C using Matlab Coder. */
  /*   Chau-Wai Wong, 10/14/2015 */
  for (i37 = 0; i37 < 2; i37++) {
    dim[i37] = img->size[i37];
  }

  memcpy(&tform_T[0], &t[0], 9U * sizeof(double));
  for (i37 = 0; i37 < 2; i37++) {
    dim[i37] *= 3.0;
  }

  obj_ImageSize[0] = dim[0];
  obj_ImageSize[1] = dim[1];
  b_imwarp(img, tform_T, obj_ImageSize, imgRet);
}

/* End of code generation (myImresize.c) */
