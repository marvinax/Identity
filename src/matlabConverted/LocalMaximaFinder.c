/*
 * LocalMaximaFinder.c
 *
 * Code generation for function 'LocalMaximaFinder'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "LocalMaximaFinder.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
visioncodegen_LocalMaximaFinder *c_LocalMaximaFinder_LocalMaxima
  (visioncodegen_LocalMaximaFinder *obj)
{
  visioncodegen_LocalMaximaFinder *b_obj;
  visioncodegen_LocalMaximaFinder *c_obj;
  vision_LocalMaximaFinder_6 *d_obj;
  int i8;
  boolean_T flag;
  b_obj = obj;
  c_obj = b_obj;
  c_obj->matlabCodegenIsDeleted = false;
  c_obj->isInitialized = false;
  c_obj->isReleased = false;
  c_obj->matlabCodegenIsDeleted = false;
  c_obj = b_obj;
  c_obj->matlabCodegenIsDeleted = false;
  d_obj = &b_obj->cSFunObject;

  /* System object Constructor function: vision.LocalMaximaFinder */
  d_obj->S0_isInitialized = false;
  d_obj->S1_isReleased = false;
  for (i8 = 0; i8 < 2; i8++) {
    d_obj->P0_NHOODSIZE_RTP[i8] = 623U + -522 * i8;
  }

  d_obj->P1_THRESHOLD_RTP = 407.0;
  c_obj = b_obj;
  if (c_obj->isInitialized && (!c_obj->isReleased)) {
    flag = true;
  } else {
    flag = false;
  }

  if (flag) {
    c_obj->TunablePropsChanged = true;
  }

  c_obj->cSFunObject.P1_THRESHOLD_RTP = 407.0;
  return b_obj;
}

/* End of code generation (LocalMaximaFinder.c) */
