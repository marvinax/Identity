/*
 * BlobAnalysis.c
 *
 * Code generation for function 'BlobAnalysis'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "BlobAnalysis.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
visioncodegen_BlobAnalysis *BlobAnalysis_BlobAnalysis(visioncodegen_BlobAnalysis
  *obj)
{
  visioncodegen_BlobAnalysis *b_obj;
  visioncodegen_BlobAnalysis *c_obj;
  vision_BlobAnalysis_7 *d_obj;
  int i;
  static const short iv17[8] = { -1, 201, 202, 203, 1, -201, -202, -203 };

  boolean_T flag;
  b_obj = obj;
  c_obj = b_obj;
  c_obj->matlabCodegenIsDeleted = false;
  c_obj->isInitialized = false;
  c_obj->isReleased = false;
  c_obj->matlabCodegenIsDeleted = false;
  c_obj = b_obj;
  c_obj->matlabCodegenIsDeleted = false;
  b_obj->c_NoTuningBeforeLockingCodeGenE = true;
  d_obj = &b_obj->cSFunObject;

  /* System object Constructor function: vision.BlobAnalysis */
  d_obj->S0_isInitialized = false;
  d_obj->S1_isReleased = false;
  for (i = 0; i < 8; i++) {
    d_obj->P0_WALKER_RTP[i] = iv17[i];
  }

  d_obj->P1_MINAREA_RTP = 1U;
  d_obj->P2_MAXAREA_RTP = 100U;
  c_obj = b_obj;
  if (c_obj->isInitialized && (!c_obj->isReleased)) {
    flag = true;
  } else {
    flag = false;
  }

  if (flag) {
    c_obj->TunablePropsChanged = true;
  }

  c_obj->cSFunObject.P1_MINAREA_RTP = 1U;
  if (c_obj->isInitialized && (!c_obj->isReleased)) {
    flag = true;
  } else {
    flag = false;
  }

  if (flag) {
    c_obj->TunablePropsChanged = true;
  }

  c_obj->cSFunObject.P2_MAXAREA_RTP = 100U;
  b_obj->c_NoTuningBeforeLockingCodeGenE = false;
  return b_obj;
}

/* End of code generation (BlobAnalysis.c) */
