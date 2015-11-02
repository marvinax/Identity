/*
 * power.c
 *
 * Code generation for function 'power'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "power.h"
#include "getPowderAndQr_emxutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Declarations */
static void eml_scalexp_alloc(const emxArray_real32_T *varargin_1,
  emxArray_real32_T *z);

/* Function Definitions */
static void eml_scalexp_alloc(const emxArray_real32_T *varargin_1,
  emxArray_real32_T *z)
{
  unsigned short unnamed_idx_0;
  int i42;
  unnamed_idx_0 = (unsigned short)varargin_1->size[0];
  i42 = z->size[0];
  z->size[0] = unnamed_idx_0;
  emxEnsureCapacity((emxArray__common *)z, i42, (int)sizeof(float));
}

void b_power(const double a[6], double y[6])
{
  int k;
  for (k = 0; k < 6; k++) {
    y[k] = a[k] * a[k];
  }
}

void c_power(const emxArray_real_T *a, emxArray_real_T *y)
{
  unsigned int uv3[2];
  int i14;
  int k;
  for (i14 = 0; i14 < 2; i14++) {
    uv3[i14] = (unsigned int)a->size[i14];
  }

  i14 = y->size[0] * y->size[1];
  y->size[0] = (int)uv3[0];
  y->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)y, i14, (int)sizeof(double));
  i14 = (int)uv3[0] << 1;
  for (k = 0; k < i14; k++) {
    y->data[k] = a->data[k] * a->data[k];
  }
}

void d_power(const double a[1024], double y[1024])
{
  int k;
  for (k = 0; k < 1024; k++) {
    y[k] = a[k] * a[k];
  }
}

void e_power(const emxArray_real32_T *a, emxArray_real32_T *y)
{
  int i41;
  int k;
  eml_scalexp_alloc(a, y);
  i41 = y->size[0];
  for (k = 0; k < i41; k++) {
    y->data[k] = a->data[k] * a->data[k];
  }
}

void power(const emxArray_real_T *a, emxArray_real_T *y)
{
  unsigned int unnamed_idx_0;
  int k;
  unnamed_idx_0 = (unsigned int)a->size[0];
  k = y->size[0];
  y->size[0] = (int)unnamed_idx_0;
  emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(double));
  for (k = 0; k < (int)unnamed_idx_0; k++) {
    y->data[k] = a->data[k] * a->data[k];
  }
}

/* End of code generation (power.c) */
