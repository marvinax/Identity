/*
 * Nondirect.c
 *
 * Code generation for function 'Nondirect'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "Nondirect.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Declarations */
static int div_s32(int numerator, int denominator);

/* Function Definitions */
static int div_s32(int numerator, int denominator)
{
  int quotient;
  unsigned int absNumerator;
  unsigned int absDenominator;
  boolean_T quotientNeedsNegation;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    if (numerator >= 0) {
      absNumerator = (unsigned int)numerator;
    } else {
      absNumerator = (unsigned int)-numerator;
    }

    if (denominator >= 0) {
      absDenominator = (unsigned int)denominator;
    } else {
      absDenominator = (unsigned int)-denominator;
    }

    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    absNumerator /= absDenominator;
    if (quotientNeedsNegation) {
      quotient = -(int)absNumerator;
    } else {
      quotient = (int)absNumerator;
    }
  }

  return quotient;
}

void Nondirect_stepImpl(visioncodegen_LocalMaximaFinder *obj, const
  emxArray_real_T *varargin_1, unsigned int varargout_1_data[], int
  varargout_1_size[2])
{
  visioncodegen_LocalMaximaFinder *b_obj;
  vision_LocalMaximaFinder_6 *c_obj;
  int rowsIn;
  int colsIn;
  int inWidth;
  int countPeak;
  boolean_T done;
  int nhood_center_idx_0;
  int nhood_center_idx_1;
  int i;
  int max_idx;
  double maxValue;
  int p;
  int j;
  int p1;
  int p2;
  int q1;
  unsigned int fromIdx;
  unsigned int toIdx;
  b_obj = obj;
  c_obj = &b_obj->cSFunObject;

  /* System object Outputs function: vision.LocalMaximaFinder */
  rowsIn = varargin_1->size[0];
  colsIn = varargin_1->size[1];
  inWidth = rowsIn * colsIn;
  countPeak = 0;
  done = false;
  nhood_center_idx_0 = (int)((b_obj->cSFunObject.P0_NHOODSIZE_RTP[0] - 1U) >> 1);
  nhood_center_idx_1 = (int)((b_obj->cSFunObject.P0_NHOODSIZE_RTP[1] - 1U) >> 1);
  for (i = 0; i < inWidth; i++) {
    c_obj->W0_TEMP_IN_DWORKS[i] = varargin_1->data[i];
  }

  memset(&varargout_1_data[0], 0, 20U * sizeof(unsigned int));
  while (!done) {
    max_idx = 0;
    maxValue = c_obj->W0_TEMP_IN_DWORKS[0];
    for (i = 0; i < inWidth; i++) {
      if (c_obj->W0_TEMP_IN_DWORKS[i] > maxValue) {
        max_idx = i;
        maxValue = c_obj->W0_TEMP_IN_DWORKS[i];
      }
    }

    p = max_idx % rowsIn;
    i = div_s32(max_idx, rowsIn);
    if (c_obj->W0_TEMP_IN_DWORKS[max_idx] >= c_obj->P1_THRESHOLD_RTP) {
      varargout_1_data[countPeak] = (unsigned int)(1 + i);
      varargout_1_data[10U + countPeak] = (unsigned int)(1 + p);
      countPeak++;
      if (countPeak == 10) {
        done = true;
      }

      j = p - nhood_center_idx_0;
      if (j >= 0) {
        p1 = j;
      } else {
        p1 = 0;
      }

      j = p + nhood_center_idx_0;
      max_idx = rowsIn - 1;
      if (j <= max_idx) {
        p2 = j;
      } else {
        p2 = max_idx;
      }

      q1 = i - nhood_center_idx_1;
      p = i + nhood_center_idx_1;
      if (!((q1 < 0) || (p > colsIn - 1))) {
        while (q1 <= p) {
          max_idx = q1 * rowsIn;
          for (i = p1; i <= p2; i++) {
            c_obj->W0_TEMP_IN_DWORKS[i + max_idx] = 0.0;
          }

          q1++;
        }
      } else {
        if (q1 < 0) {
          for (j = q1; j <= p; j++) {
            if (j < 0) {
              max_idx = (j + colsIn) * rowsIn;
              for (i = p1; i <= p2; i++) {
                c_obj->W0_TEMP_IN_DWORKS[((rowsIn - i) + max_idx) - 1] = 0.0;
              }
            } else {
              max_idx = j * rowsIn;
              for (i = p1; i <= p2; i++) {
                c_obj->W0_TEMP_IN_DWORKS[i + max_idx] = 0.0;
              }
            }
          }
        }

        if (p > colsIn - 1) {
          for (j = q1; j <= p; j++) {
            if (j > colsIn - 1) {
              max_idx = (j - colsIn) * rowsIn;
              for (i = p1; i <= p2; i++) {
                c_obj->W0_TEMP_IN_DWORKS[((rowsIn - i) + max_idx) - 1] = 0.0;
              }
            } else {
              max_idx = j * rowsIn;
              for (i = p1; i <= p2; i++) {
                c_obj->W0_TEMP_IN_DWORKS[i + max_idx] = 0.0;
              }
            }
          }
        }
      }
    } else {
      done = true;
    }
  }

  b_obj->cSFunObject.W1_NUMPEAKS_DWORK = (unsigned int)countPeak;
  fromIdx = 10U;
  toIdx = (unsigned int)countPeak;
  for (i = 0; i < countPeak; i++) {
    varargout_1_data[toIdx] = varargout_1_data[fromIdx];
    fromIdx++;
    toIdx++;
  }

  varargout_1_size[0] = (int)b_obj->cSFunObject.W1_NUMPEAKS_DWORK;
  varargout_1_size[1] = 2;
}

/* End of code generation (Nondirect.c) */
