/*
 * SystemCore.c
 *
 * Code generation for function 'SystemCore'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "SystemCore.h"
#include "Nondirect.h"
#include "getPowderAndQr_emxutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Declarations */
static int div_s32s64_floor(long long numerator, long long denominator);

/* Function Definitions */
static int div_s32s64_floor(long long numerator, long long denominator)
{
  int quotient;
  unsigned long long absNumerator;
  unsigned long long absDenominator;
  boolean_T quotientNeedsNegation;
  unsigned long long tempAbsQuotient;
  if (denominator == 0LL) {
    if (numerator >= 0LL) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    if (numerator >= 0LL) {
      absNumerator = (unsigned long long)numerator;
    } else {
      absNumerator = (unsigned long long)-numerator;
    }

    if (denominator >= 0LL) {
      absDenominator = (unsigned long long)denominator;
    } else {
      absDenominator = (unsigned long long)-denominator;
    }

    quotientNeedsNegation = ((numerator < 0LL) != (denominator < 0LL));
    tempAbsQuotient = absNumerator / absDenominator;
    if (quotientNeedsNegation) {
      absNumerator %= absDenominator;
      if (absNumerator > 0ULL) {
        tempAbsQuotient++;
      }
    }

    if (quotientNeedsNegation) {
      quotient = (int)-(long long)tempAbsQuotient;
    } else {
      quotient = (int)tempAbsQuotient;
    }
  }

  return quotient;
}

void SystemCore_step(visioncodegen_Autothresholder *obj, const emxArray_uint8_T *
                     varargin_1, emxArray_boolean_T *varargout_1, unsigned char *
                     varargout_2)
{
  visioncodegen_Autothresholder *b_obj;
  emxArray_uint8_T *U0;
  vision_Autothresholder_3 *c_obj;
  int normTh;
  int muA2P3;
  int numPix;
  int i;
  int muT;
  int idxMaxVal;
  int maxVal;
  unsigned int posTh;
  unsigned char threshold;
  if (!obj->isInitialized) {
    b_obj = obj;
    b_obj->isInitialized = true;
    b_obj->c_NoTuningBeforeLockingCodeGenE = true;
    b_obj->TunablePropsChanged = false;
  }

  b_obj = obj;
  if (b_obj->TunablePropsChanged) {
    b_obj->TunablePropsChanged = false;
  }

  emxInit_uint8_T(&U0, 2);
  b_obj = obj;
  c_obj = &b_obj->cSFunObject;
  normTh = varargin_1->size[0];
  muA2P3 = U0->size[0] * U0->size[1];
  U0->size[0] = normTh;
  emxEnsureCapacity((emxArray__common *)U0, muA2P3, (int)sizeof(unsigned char));
  muA2P3 = U0->size[0] * U0->size[1];
  U0->size[1] = 1;
  emxEnsureCapacity((emxArray__common *)U0, muA2P3, (int)sizeof(unsigned char));
  normTh = varargin_1->size[0];
  for (muA2P3 = 0; muA2P3 < normTh; muA2P3++) {
    U0->data[muA2P3] = varargin_1->data[muA2P3];
  }

  /* System object Outputs function: vision.Autothresholder */
  muA2P3 = varargout_1->size[0] * varargout_1->size[1];
  varargout_1->size[0] = U0->size[0];
  varargout_1->size[1] = U0->size[1];
  emxEnsureCapacity((emxArray__common *)varargout_1, muA2P3, (int)sizeof
                    (boolean_T));
  numPix = U0->size[0] * U0->size[1];
  emxFree_uint8_T(&U0);
  if (numPix > 0) {
    b_obj->cSFunObject.W3_NORMF_FIXPT_DW = div_s32s64_floor(2147483648LL, numPix);
    for (i = 0; i < 256; i++) {
      c_obj->W0_HIST_FIXPT_DW[i] = 0;
    }

    for (i = 0; i < numPix; i++) {
      c_obj->W0_HIST_FIXPT_DW[varargin_1->data[i]]++;
    }

    for (i = 0; i < 256; i++) {
      normTh = c_obj->W0_HIST_FIXPT_DW[i];
      c_obj->W1_P_FIXPT_DW[i] = (int)((long long)c_obj->W3_NORMF_FIXPT_DW *
        normTh >> 1);
    }

    b_obj->cSFunObject.W2_MU_FIXPT_DW[0] = b_obj->cSFunObject.W1_P_FIXPT_DW[0] >>
      8;
    for (i = 0; i < 255; i++) {
      c_obj->W2_MU_FIXPT_DW[i + 1] = (i + 2) << 22;
      c_obj->W2_MU_FIXPT_DW[i + 1] = (int)((long long)c_obj->W2_MU_FIXPT_DW[i +
        1] * c_obj->W1_P_FIXPT_DW[i + 1] >> 30);
      muT = c_obj->W2_MU_FIXPT_DW[i];
      c_obj->W2_MU_FIXPT_DW[i + 1] += muT;
    }

    muT = b_obj->cSFunObject.W2_MU_FIXPT_DW[255];
    for (i = 0; i < 254; i++) {
      normTh = c_obj->W1_P_FIXPT_DW[i];
      c_obj->W1_P_FIXPT_DW[i + 1] += normTh;
    }

    idxMaxVal = 0;
    maxVal = 0;
    for (i = 0; i < 255; i++) {
      muA2P3 = (int)((long long)c_obj->W1_P_FIXPT_DW[i] * muT >> 30);
      muA2P3 -= c_obj->W2_MU_FIXPT_DW[i];
      normTh = 1073741824 - c_obj->W1_P_FIXPT_DW[i];
      normTh = (int)((long long)c_obj->W1_P_FIXPT_DW[i] * normTh >> 30);
      if (normTh == 0) {
        normTh = 0;
      } else {
        normTh = div_s32s64_floor((long long)((int)((long long)muA2P3 * muA2P3 >>
          30) << 2) << 30, normTh);
      }

      if (normTh > maxVal) {
        maxVal = normTh;
        idxMaxVal = i;
      }
    }

    normTh = b_obj->cSFunObject.P1_SCALE_FIXPT_RTP * idxMaxVal;
    posTh = (unsigned int)b_obj->cSFunObject.P3_UMAX_FIXPT_RTP << 15;
    posTh = (unsigned int)((unsigned long long)posTh * (unsigned int)normTh >>
      30);
    muA2P3 = (int)posTh;
    threshold = (unsigned char)((muA2P3 >> 15) + ((muA2P3 & 16384) != 0));
    for (i = 0; i < numPix; i++) {
      varargout_1->data[i] = (varargin_1->data[i] > threshold);
    }
  }

  *varargout_2 = threshold;
}

void b_SystemCore_step(visioncodegen_LocalMaximaFinder *obj, const
  emxArray_real_T *varargin_1, unsigned int varargout_1_data[], int
  varargout_1_size[2])
{
  visioncodegen_LocalMaximaFinder *b_obj;
  if (!obj->isInitialized) {
    b_obj = obj;
    b_obj->isInitialized = true;
    b_obj->TunablePropsChanged = false;
  }

  b_obj = obj;
  if (b_obj->TunablePropsChanged) {
    b_obj->TunablePropsChanged = false;
  }

  Nondirect_stepImpl(obj, varargin_1, varargout_1_data, varargout_1_size);
}

void c_SystemCore_step(visioncodegen_BlobAnalysis *obj, const boolean_T
  varargin_1[40000], int varargout_1_data[], int varargout_1_size[2], float
  varargout_2_data[], int varargout_2_size[2])
{
  visioncodegen_BlobAnalysis *b_obj;
  vision_BlobAnalysis_7 *c_obj;
  boolean_T maxNumBlobsReached;
  int loop;
  unsigned char currentLabel;
  int i;
  int idx;
  int n;
  int ms;
  unsigned int pixIdx;
  int pixListNinc;
  unsigned int padIdx;
  unsigned int start_pixIdx;
  unsigned int centerIdx;
  unsigned int walkerIdx;
  int j;
  float centroid_idx_0;
  float centroid_idx_1;
  if (!obj->isInitialized) {
    b_obj = obj;
    b_obj->isInitialized = true;
    b_obj->c_NoTuningBeforeLockingCodeGenE = true;
    b_obj->TunablePropsChanged = false;
  }

  b_obj = obj;
  if (b_obj->TunablePropsChanged) {
    b_obj->TunablePropsChanged = false;
  }

  b_obj = obj;
  c_obj = &b_obj->cSFunObject;

  /* System object Outputs function: vision.BlobAnalysis */
  maxNumBlobsReached = false;
  for (loop = 0; loop < 203; loop++) {
    c_obj->W3_PAD_DW[loop] = 0;
  }

  currentLabel = 1;
  i = 0;
  idx = 203;
  for (n = 0; n < 200; n++) {
    for (ms = 0; ms < 200; ms++) {
      if (varargin_1[i]) {
        c_obj->W3_PAD_DW[idx] = MAX_uint8_T;
      } else {
        c_obj->W3_PAD_DW[idx] = 0;
      }

      i++;
      idx++;
    }

    c_obj->W3_PAD_DW[idx] = 0;
    c_obj->W3_PAD_DW[idx + 1] = 0;
    idx += 2;
  }

  for (loop = 0; loop < 201; loop++) {
    c_obj->W3_PAD_DW[loop + idx] = 0;
  }

  loop = 1;
  pixIdx = 0U;
  n = 0;
  while (n < 200) {
    idx = 1;
    pixListNinc = loop * 202;
    ms = 0;
    while (ms < 200) {
      padIdx = (unsigned int)(pixListNinc + idx);
      start_pixIdx = pixIdx;
      if (c_obj->W3_PAD_DW[padIdx] == 255) {
        c_obj->W3_PAD_DW[padIdx] = currentLabel;
        c_obj->W0_N_PIXLIST_DW[pixIdx] = (short)(loop - 1);
        c_obj->W1_M_PIXLIST_DW[pixIdx] = (short)(idx - 1);
        pixIdx++;
        c_obj->W2_NUM_PIX_DW[currentLabel - 1] = 1U;
        c_obj->W4_STACK_DW[0U] = padIdx;
        padIdx = 1U;
        while (padIdx != 0U) {
          padIdx--;
          centerIdx = c_obj->W4_STACK_DW[padIdx];
          for (i = 0; i < 8; i++) {
            walkerIdx = centerIdx + c_obj->P0_WALKER_RTP[i];
            if (c_obj->W3_PAD_DW[walkerIdx] == 255) {
              c_obj->W3_PAD_DW[walkerIdx] = currentLabel;
              c_obj->W0_N_PIXLIST_DW[pixIdx] = (short)((short)(walkerIdx / 202U)
                - 1);
              c_obj->W1_M_PIXLIST_DW[pixIdx] = (short)(walkerIdx % 202U - 1U);
              pixIdx++;
              c_obj->W2_NUM_PIX_DW[currentLabel - 1]++;
              c_obj->W4_STACK_DW[padIdx] = walkerIdx;
              padIdx++;
            }
          }
        }

        if ((c_obj->W2_NUM_PIX_DW[currentLabel - 1] < c_obj->P1_MINAREA_RTP) ||
            (c_obj->W2_NUM_PIX_DW[currentLabel - 1] > c_obj->P2_MAXAREA_RTP)) {
          currentLabel--;
          pixIdx = start_pixIdx;
        }

        if (currentLabel == 100) {
          maxNumBlobsReached = true;
          n = 200;
          ms = 200;
        }

        if (ms < 200) {
          currentLabel++;
        }
      }

      idx++;
      ms++;
    }

    loop++;
    n++;
  }

  if (maxNumBlobsReached) {
    loop = currentLabel;
  } else {
    loop = (unsigned char)(currentLabel - 1U);
  }

  idx = 0;
  pixListNinc = 0;
  for (i = 0; i < loop; i++) {
    varargout_1_data[i] = (int)c_obj->W2_NUM_PIX_DW[i];
    n = 0;
    ms = 0;
    for (j = 0; j < (int)c_obj->W2_NUM_PIX_DW[i]; j++) {
      n += c_obj->W0_N_PIXLIST_DW[j + pixListNinc];
      ms += c_obj->W1_M_PIXLIST_DW[j + idx];
    }

    centroid_idx_0 = (float)ms / (float)c_obj->W2_NUM_PIX_DW[i];
    centroid_idx_1 = (float)n / (float)c_obj->W2_NUM_PIX_DW[i];
    varargout_2_data[i] = centroid_idx_1 + 1.0F;
    varargout_2_data[(unsigned int)loop + i] = centroid_idx_0 + 1.0F;
    idx += (int)c_obj->W2_NUM_PIX_DW[i];
    pixListNinc += (int)c_obj->W2_NUM_PIX_DW[i];
  }

  varargout_1_size[0] = loop;
  varargout_1_size[1] = 1;
  varargout_2_size[0] = loop;
  varargout_2_size[1] = 2;
}

/* End of code generation (SystemCore.c) */
