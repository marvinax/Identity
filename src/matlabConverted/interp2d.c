/*
 * interp2d.c
 *
 * Code generation for function 'interp2d'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "interp2d.h"
#include "getPowderAndQr_emxutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void interp2d(const emxArray_real_T *inputImage, emxArray_real_T *X,
              emxArray_real_T *Y, emxArray_real_T *outputImage)
{
  emxArray_real_T *b_inputImage;
  unsigned int sizeB[2];
  int i25;
  int k;
  int b_sizeB[2];
  int i;
  int i26;
  emxArray_real_T *b_Y;
  emxArray_real_T *b_X;
  double fillValues;
  double c_inputImage[2];
  double b_outputImage[2];
  emxInit_real_T(&b_inputImage, 2);
  if ((inputImage->size[0] == 0) || (inputImage->size[1] == 0)) {
    for (i25 = 0; i25 < 2; i25++) {
      sizeB[i25] = inputImage->size[i25] + 6U;
    }

    i25 = b_inputImage->size[0] * b_inputImage->size[1];
    b_inputImage->size[0] = (int)sizeB[0];
    emxEnsureCapacity((emxArray__common *)b_inputImage, i25, (int)sizeof(double));
    i25 = b_inputImage->size[0] * b_inputImage->size[1];
    b_inputImage->size[1] = (int)sizeB[1];
    emxEnsureCapacity((emxArray__common *)b_inputImage, i25, (int)sizeof(double));
    k = (int)sizeB[0] * (int)sizeB[1];
    for (i25 = 0; i25 < k; i25++) {
      b_inputImage->data[i25] = 220.0;
    }
  } else {
    for (k = 0; k < 2; k++) {
      b_sizeB[k] = (int)((double)inputImage->size[k] + 6.0);
    }

    i25 = b_inputImage->size[0] * b_inputImage->size[1];
    b_inputImage->size[0] = b_sizeB[0];
    b_inputImage->size[1] = b_sizeB[1];
    emxEnsureCapacity((emxArray__common *)b_inputImage, i25, (int)sizeof(double));
    for (k = 0; k < 3; k++) {
      i25 = b_inputImage->size[0];
      for (i = 0; i < i25; i++) {
        b_inputImage->data[i + b_inputImage->size[0] * k] = 220.0;
      }
    }

    i25 = b_inputImage->size[1];
    for (k = inputImage->size[1] + 3; k + 1 <= i25; k++) {
      i26 = b_inputImage->size[0];
      for (i = 0; i < i26; i++) {
        b_inputImage->data[i + b_inputImage->size[0] * k] = 220.0;
      }
    }

    for (k = 0; k < inputImage->size[1]; k++) {
      for (i = 0; i < 3; i++) {
        b_inputImage->data[i + b_inputImage->size[0] * (k + 3)] = 220.0;
      }
    }

    for (k = 0; k < inputImage->size[1]; k++) {
      i25 = b_inputImage->size[0];
      for (i = inputImage->size[0] + 3; i + 1 <= i25; i++) {
        b_inputImage->data[i + b_inputImage->size[0] * (k + 3)] = 220.0;
      }
    }

    for (k = 0; k < inputImage->size[1]; k++) {
      for (i = 0; i < inputImage->size[0]; i++) {
        b_inputImage->data[(i + b_inputImage->size[0] * (k + 3)) + 3] =
          inputImage->data[i + inputImage->size[0] * k];
      }
    }
  }

  i25 = X->size[0] * X->size[1];
  emxEnsureCapacity((emxArray__common *)X, i25, (int)sizeof(double));
  k = X->size[0];
  i = X->size[1];
  k *= i;
  for (i25 = 0; i25 < k; i25++) {
    X->data[i25] = (X->data[i25] + 3.0) - 1.0;
  }

  i25 = Y->size[0] * Y->size[1];
  emxEnsureCapacity((emxArray__common *)Y, i25, (int)sizeof(double));
  k = Y->size[0];
  i = Y->size[1];
  k *= i;
  for (i25 = 0; i25 < k; i25++) {
    Y->data[i25] = (Y->data[i25] + 3.0) - 1.0;
  }

  emxInit_real_T(&b_Y, 2);
  i25 = outputImage->size[0] * outputImage->size[1];
  outputImage->size[0] = X->size[0];
  outputImage->size[1] = X->size[1];
  emxEnsureCapacity((emxArray__common *)outputImage, i25, (int)sizeof(double));
  i25 = b_Y->size[0] * b_Y->size[1];
  b_Y->size[0] = Y->size[0];
  b_Y->size[1] = Y->size[1];
  emxEnsureCapacity((emxArray__common *)b_Y, i25, (int)sizeof(double));
  k = Y->size[0] * Y->size[1];
  for (i25 = 0; i25 < k; i25++) {
    b_Y->data[i25] = Y->data[i25];
  }

  emxInit_real_T(&b_X, 2);
  i25 = b_X->size[0] * b_X->size[1];
  b_X->size[0] = X->size[0];
  b_X->size[1] = X->size[1];
  emxEnsureCapacity((emxArray__common *)b_X, i25, (int)sizeof(double));
  k = X->size[0] * X->size[1];
  for (i25 = 0; i25 < k; i25++) {
    b_X->data[i25] = X->data[i25];
  }

  fillValues = 220.0;
  for (i25 = 0; i25 < 2; i25++) {
    c_inputImage[i25] = b_inputImage->size[i25];
  }

  for (i25 = 0; i25 < 2; i25++) {
    b_outputImage[i25] = outputImage->size[i25];
  }

  remaptbb_real64(&b_inputImage->data[0], c_inputImage, 2.0, &b_Y->data[0],
                  &b_X->data[0], 3, &fillValues, &outputImage->data[0],
                  b_outputImage, (double)(outputImage->size[0] *
    outputImage->size[1]));
  emxFree_real_T(&b_X);
  emxFree_real_T(&b_Y);
  emxFree_real_T(&b_inputImage);
}

/* End of code generation (interp2d.c) */
