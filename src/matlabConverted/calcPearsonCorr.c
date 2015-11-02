/*
 * calcPearsonCorr.c
 *
 * Code generation for function 'calcPearsonCorr'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "calcPearsonCorr.h"
#include "getPowderAndQr_emxutil.h"
#include "sum.h"
#include "power.h"
#include "mean.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
double calcPearsonCorr(const emxArray_real_T *a, const emxArray_real_T *b)
{
  emxArray_real_T *a1;
  double var_a;
  int i29;
  int loop_ub;
  emxArray_real_T *b1;
  emxArray_real_T *b_a;
  emxArray_real_T *r24;
  double var_b;
  double y;
  b_emxInit_real_T(&a1, 1);

  /*  When only correlation value is needed, this function is about 30% faster */
  /*  than the Matlab build-in function corr(x,y) */
  /*  Oct. 2014, Chau-Wai Wong */
  var_a = mean(a);
  i29 = a1->size[0];
  a1->size[0] = a->size[0];
  emxEnsureCapacity((emxArray__common *)a1, i29, (int)sizeof(double));
  loop_ub = a->size[0];
  for (i29 = 0; i29 < loop_ub; i29++) {
    a1->data[i29] = a->data[i29] - var_a;
  }

  b_emxInit_real_T(&b1, 1);
  var_a = mean(b);
  i29 = b1->size[0];
  b1->size[0] = b->size[0];
  emxEnsureCapacity((emxArray__common *)b1, i29, (int)sizeof(double));
  loop_ub = b->size[0];
  for (i29 = 0; i29 < loop_ub; i29++) {
    b1->data[i29] = b->data[i29] - var_a;
  }

  emxInit_real_T(&b_a, 2);
  b_emxInit_real_T(&r24, 1);
  power(a1, r24);
  var_a = b_sum(r24);
  power(b1, r24);
  var_b = b_sum(r24);
  i29 = b_a->size[0] * b_a->size[1];
  b_a->size[0] = 1;
  b_a->size[1] = a1->size[0];
  emxEnsureCapacity((emxArray__common *)b_a, i29, (int)sizeof(double));
  loop_ub = a1->size[0];
  emxFree_real_T(&r24);
  for (i29 = 0; i29 < loop_ub; i29++) {
    b_a->data[b_a->size[0] * i29] = a1->data[i29];
  }

  emxFree_real_T(&a1);
  if ((b_a->size[1] == 1) || (b1->size[0] == 1)) {
    y = 0.0;
    for (i29 = 0; i29 < b_a->size[1]; i29++) {
      y += b_a->data[b_a->size[0] * i29] * b1->data[i29];
    }
  } else {
    y = 0.0;
    for (i29 = 0; i29 < b_a->size[1]; i29++) {
      y += b_a->data[b_a->size[0] * i29] * b1->data[i29];
    }
  }

  emxFree_real_T(&b_a);
  emxFree_real_T(&b1);
  return y / sqrt(var_a * var_b);
}

/* End of code generation (calcPearsonCorr.c) */
