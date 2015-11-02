/*
 * DigitalDevice.c
 *
 * Code generation for function 'DigitalDevice'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "DigitalDevice.h"
#include "median.h"
#include "getPowderAndQr_emxutil.h"
#include "rdivide.h"
#include "ransacFit_plane.h"
#include "meshgrid.h"
#include "round.h"
#include "sqrt.h"
#include "power.h"
#include "SystemCore.h"
#include "BlobAnalysis.h"
#include "sum.h"
#include "removeReflectivePoints.h"
#include "fliplr.h"
#include "flipud.h"
#include "getPowderAndQr_rtwutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Declarations */
static int b_compute_nones(const boolean_T x[1024]);
static void b_eml_li_find(const boolean_T x[1024], int y_data[], int y_size[1]);
static void c_eml_xgemm(int n, const double A[120000], const double B_data[],
  emxArray_real_T *C);
static void createQuarterCircleMask(boolean_T mask[1024]);
static float rt_roundf_snf(float u);

/* Function Definitions */
static int b_compute_nones(const boolean_T x[1024])
{
  int k;
  int i;
  k = 0;
  for (i = 0; i < 1024; i++) {
    if (x[i]) {
      k++;
    }
  }

  return k;
}

static void b_eml_li_find(const boolean_T x[1024], int y_data[], int y_size[1])
{
  int j;
  int i;
  y_size[0] = b_compute_nones(x);
  j = 0;
  for (i = 0; i < 1024; i++) {
    if (x[i]) {
      y_data[j] = i + 1;
      j++;
    }
  }
}

static void c_eml_xgemm(int n, const double A[120000], const double B_data[],
  emxArray_real_T *C)
{
  int ic;
  int ar;
  int ib;
  int ia;
  if (n == 0) {
  } else {
    for (ic = 1; ic < 40001; ic++) {
      C->data[ic - 1] = 0.0;
    }

    ar = -1;
    for (ib = 0; ib + 1 < 4; ib++) {
      if (B_data[ib] != 0.0) {
        ia = ar;
        for (ic = 0; ic + 1 < 40001; ic++) {
          ia++;
          C->data[ic] += B_data[ib] * A[ia];
        }
      }

      ar += 40000;
    }
  }
}

static void createQuarterCircleMask(boolean_T mask[1024])
{
  double dv13[1024];
  static const double dv14[1024] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0,
    2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0,
    2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 3.0, 3.0, 3.0, 3.0, 3.0,
    3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0,
    3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 4.0, 4.0, 4.0,
    4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0,
    4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 5.0,
    5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0,
    5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0,
    5.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0,
    6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0,
    6.0, 6.0, 6.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0,
    7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 7.0,
    7.0, 7.0, 7.0, 7.0, 7.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0,
    8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0,
    8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0,
    9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0,
    9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 10.0, 10.0, 10.0, 10.0, 10.0,
    10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0,
    10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0,
    10.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0,
    11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0,
    11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 11.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0,
    12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0,
    12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0,
    13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0,
    13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 13.0,
    13.0, 13.0, 13.0, 13.0, 13.0, 13.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0,
    14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0,
    14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 15.0,
    15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0,
    15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0,
    15.0, 15.0, 15.0, 15.0, 15.0, 16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 16.0,
    16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 16.0,
    16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 17.0, 17.0,
    17.0, 17.0, 17.0, 17.0, 17.0, 17.0, 17.0, 17.0, 17.0, 17.0, 17.0, 17.0, 17.0,
    17.0, 17.0, 17.0, 17.0, 17.0, 17.0, 17.0, 17.0, 17.0, 17.0, 17.0, 17.0, 17.0,
    17.0, 17.0, 17.0, 17.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0,
    18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0,
    18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 18.0, 19.0, 19.0, 19.0,
    19.0, 19.0, 19.0, 19.0, 19.0, 19.0, 19.0, 19.0, 19.0, 19.0, 19.0, 19.0, 19.0,
    19.0, 19.0, 19.0, 19.0, 19.0, 19.0, 19.0, 19.0, 19.0, 19.0, 19.0, 19.0, 19.0,
    19.0, 19.0, 19.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0,
    20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0,
    20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 21.0, 21.0, 21.0, 21.0,
    21.0, 21.0, 21.0, 21.0, 21.0, 21.0, 21.0, 21.0, 21.0, 21.0, 21.0, 21.0, 21.0,
    21.0, 21.0, 21.0, 21.0, 21.0, 21.0, 21.0, 21.0, 21.0, 21.0, 21.0, 21.0, 21.0,
    21.0, 21.0, 22.0, 22.0, 22.0, 22.0, 22.0, 22.0, 22.0, 22.0, 22.0, 22.0, 22.0,
    22.0, 22.0, 22.0, 22.0, 22.0, 22.0, 22.0, 22.0, 22.0, 22.0, 22.0, 22.0, 22.0,
    22.0, 22.0, 22.0, 22.0, 22.0, 22.0, 22.0, 22.0, 23.0, 23.0, 23.0, 23.0, 23.0,
    23.0, 23.0, 23.0, 23.0, 23.0, 23.0, 23.0, 23.0, 23.0, 23.0, 23.0, 23.0, 23.0,
    23.0, 23.0, 23.0, 23.0, 23.0, 23.0, 23.0, 23.0, 23.0, 23.0, 23.0, 23.0, 23.0,
    23.0, 24.0, 24.0, 24.0, 24.0, 24.0, 24.0, 24.0, 24.0, 24.0, 24.0, 24.0, 24.0,
    24.0, 24.0, 24.0, 24.0, 24.0, 24.0, 24.0, 24.0, 24.0, 24.0, 24.0, 24.0, 24.0,
    24.0, 24.0, 24.0, 24.0, 24.0, 24.0, 24.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0,
    25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0,
    25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0,
    26.0, 26.0, 26.0, 26.0, 26.0, 26.0, 26.0, 26.0, 26.0, 26.0, 26.0, 26.0, 26.0,
    26.0, 26.0, 26.0, 26.0, 26.0, 26.0, 26.0, 26.0, 26.0, 26.0, 26.0, 26.0, 26.0,
    26.0, 26.0, 26.0, 26.0, 26.0, 26.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0,
    27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0,
    27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, 28.0,
    28.0, 28.0, 28.0, 28.0, 28.0, 28.0, 28.0, 28.0, 28.0, 28.0, 28.0, 28.0, 28.0,
    28.0, 28.0, 28.0, 28.0, 28.0, 28.0, 28.0, 28.0, 28.0, 28.0, 28.0, 28.0, 28.0,
    28.0, 28.0, 28.0, 28.0, 28.0, 29.0, 29.0, 29.0, 29.0, 29.0, 29.0, 29.0, 29.0,
    29.0, 29.0, 29.0, 29.0, 29.0, 29.0, 29.0, 29.0, 29.0, 29.0, 29.0, 29.0, 29.0,
    29.0, 29.0, 29.0, 29.0, 29.0, 29.0, 29.0, 29.0, 29.0, 29.0, 29.0, 30.0, 30.0,
    30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0,
    30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0,
    30.0, 30.0, 30.0, 30.0, 31.0, 31.0, 31.0, 31.0, 31.0, 31.0, 31.0, 31.0, 31.0,
    31.0, 31.0, 31.0, 31.0, 31.0, 31.0, 31.0, 31.0, 31.0, 31.0, 31.0, 31.0, 31.0,
    31.0, 31.0, 31.0, 31.0, 31.0, 31.0, 31.0, 31.0, 31.0, 31.0, 32.0, 32.0, 32.0,
    32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0,
    32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0,
    32.0, 32.0, 32.0 };

  double dv15[1024];
  static const double dv16[1024] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0,
    10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0,
    23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 1.0, 2.0, 3.0,
    4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0,
    18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
    31.0, 32.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0,
    13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0,
    26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0,
    8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0,
    21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 1.0,
    2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0,
    16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0,
    29.0, 30.0, 31.0, 32.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0,
    11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0,
    24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 1.0, 2.0, 3.0, 4.0,
    5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0,
    18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
    31.0, 32.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0,
    13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0,
    26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0,
    8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0,
    21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 1.0,
    2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0,
    16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0,
    29.0, 30.0, 31.0, 32.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0,
    11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0,
    24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 1.0, 2.0, 3.0, 4.0,
    5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0,
    18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
    31.0, 32.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0,
    13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0,
    26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0,
    8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0,
    21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 1.0,
    2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0,
    16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0,
    29.0, 30.0, 31.0, 32.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0,
    11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0,
    24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 1.0, 2.0, 3.0, 4.0,
    5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0,
    18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
    31.0, 32.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0,
    13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0,
    26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0,
    8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0,
    21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 1.0,
    2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0,
    16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0,
    29.0, 30.0, 31.0, 32.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0,
    11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0,
    24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 1.0, 2.0, 3.0, 4.0,
    5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0,
    18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
    31.0, 32.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0,
    13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0,
    26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0,
    8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0,
    21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 1.0,
    2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0,
    16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0,
    29.0, 30.0, 31.0, 32.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0,
    11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0,
    24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 1.0, 2.0, 3.0, 4.0,
    5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0,
    18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
    31.0, 32.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0,
    13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0,
    26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0,
    8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0,
    21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 1.0,
    2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0,
    16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0,
    29.0, 30.0, 31.0, 32.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0,
    11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0,
    24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 1.0, 2.0, 3.0, 4.0,
    5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0,
    18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
    31.0, 32.0 };

  boolean_T bv0[1024];
  int i40;
  int tmp_size[1];
  int tmp_data[1024];
  int loop_ub;

  /* % */
  d_power(dv14, dv13);
  d_power(dv16, dv15);
  for (i40 = 0; i40 < 1024; i40++) {
    mask[i40] = false;
    bv0[i40] = (dv13[i40] + dv15[i40] > 1024.0);
  }

  b_eml_li_find(bv0, tmp_data, tmp_size);
  loop_ub = tmp_size[0];
  for (i40 = 0; i40 < loop_ub; i40++) {
    mask[tmp_data[i40] - 1] = true;
  }
}

static float rt_roundf_snf(float u)
{
  float y;
  if ((real32_T)fabs(u) < 8.388608E+6F) {
    if (u >= 0.5F) {
      y = (real32_T)floor(u + 0.5F);
    } else if (u > -0.5F) {
      y = u * 0.0F;
    } else {
      y = (real32_T)ceil(u - 0.5F);
    }
  } else {
    y = u;
  }

  return y;
}

void DigitalDevice_detrend(DigitalDevice *obj)
{
  double vert;
  double imgF[169];
  emxArray_real_T *b_obj;
  emxArray_real_T *c_obj;
  int y;
  int b_y;
  int hori;
  int x;
  int i56;
  int ix;
  int i57;
  int i58;
  int i59;
  int ixstart;
  int loop_ub;
  int i60;
  double val;
  double dv22[13];
  double dv23[13];
  double gy[169];
  double gx[169];
  double dv24[200];
  double dv25[200];
  static double gy_full[40000];
  static double gx_full[40000];
  int best_beta_hat_size[2];
  double best_beta_hat_data[3];
  double lowResPlane[169];
  static double a[120000];
  emxArray_real_T *y_hat;
  boolean_T exitg1;

  /*  Detrend the input image */
  /*  Chau-Wai Wong, Nov. 2014 */
  /*  Const def */
  vert = 0.0;
  memset(&imgF[0], 0, 169U * sizeof(double));
  b_emxInit_real_T(&b_obj, 1);
  emxInit_real_T(&c_obj, 2);
  for (y = 0; y < 13; y++) {
    b_y = 1 + 15 * y;
    vert++;
    hori = -1;
    for (x = 0; x < 13; x++) {
      hori++;
      if (b_y > b_y + 14) {
        i56 = 0;
        ix = 0;
      } else {
        i56 = b_y - 1;
        ix = b_y + 14;
      }

      if (1 + 15 * x > 15 * x + 15) {
        i57 = 0;
        i58 = 0;
      } else {
        i57 = 15 * x;
        i58 = 15 * x + 15;
      }

      i59 = c_obj->size[0] * c_obj->size[1];
      c_obj->size[0] = ix - i56;
      c_obj->size[1] = i58 - i57;
      emxEnsureCapacity((emxArray__common *)c_obj, i59, (int)sizeof(double));
      ixstart = i58 - i57;
      for (i59 = 0; i59 < ixstart; i59++) {
        loop_ub = ix - i56;
        for (i60 = 0; i60 < loop_ub; i60++) {
          c_obj->data[i60 + c_obj->size[0] * i59] = obj->patchProcessed[(i56 +
            i60) + 200 * (i57 + i59)];
        }
      }

      ixstart = (ix - i56) * (i58 - i57);
      i56 = b_obj->size[0];
      b_obj->size[0] = ixstart;
      emxEnsureCapacity((emxArray__common *)b_obj, i56, (int)sizeof(double));
      for (i56 = 0; i56 < ixstart; i56++) {
        b_obj->data[i56] = c_obj->data[i56];
      }

      val = median(b_obj);
      imgF[((int)vert + 13 * hori) - 1] = val;
    }
  }

  emxFree_real_T(&c_obj);
  emxFree_real_T(&b_obj);
  for (i56 = 0; i56 < 13; i56++) {
    dv22[i56] = 8.0 + 15.0 * (double)i56;
    dv23[i56] = 8.0 + 15.0 * (double)i56;
  }

  b_meshgrid(dv22, dv23, gx, gy);
  for (i56 = 0; i56 < 200; i56++) {
    dv24[i56] = 1.0 + (double)i56;
    dv25[i56] = 1.0 + (double)i56;
  }

  c_meshgrid(dv24, dv25, gx_full, gy_full);
  ransacFit_plane(gx, gy, imgF, lowResPlane, best_beta_hat_data,
                  best_beta_hat_size, &vert);
  for (i56 = 0; i56 < 40000; i56++) {
    a[i56] = 1.0;
    a[40000 + i56] = gx_full[i56];
    a[80000 + i56] = gy_full[i56];
  }

  emxInit_real_T(&y_hat, 2);
  if (best_beta_hat_size[0] == 1) {
    i56 = y_hat->size[0] * y_hat->size[1];
    y_hat->size[0] = 40000;
    y_hat->size[1] = best_beta_hat_size[1];
    emxEnsureCapacity((emxArray__common *)y_hat, i56, (int)sizeof(double));
    for (i56 = 0; i56 < 40000; i56++) {
      ixstart = best_beta_hat_size[1];
      for (ix = 0; ix < ixstart; ix++) {
        y_hat->data[i56 + y_hat->size[0] * ix] = 0.0;
        for (i57 = 0; i57 < 3; i57++) {
          y_hat->data[i56 + y_hat->size[0] * ix] += a[i56 + 40000 * i57] *
            best_beta_hat_data[i57 + ix];
        }
      }
    }
  } else {
    i56 = y_hat->size[0] * y_hat->size[1];
    y_hat->size[0] = 40000;
    emxEnsureCapacity((emxArray__common *)y_hat, i56, (int)sizeof(double));
    i56 = y_hat->size[0] * y_hat->size[1];
    y_hat->size[1] = (unsigned short)best_beta_hat_size[1];
    emxEnsureCapacity((emxArray__common *)y_hat, i56, (int)sizeof(double));
    ixstart = 40000 * (unsigned short)best_beta_hat_size[1];
    for (i56 = 0; i56 < ixstart; i56++) {
      y_hat->data[i56] = 0.0;
    }

    c_eml_xgemm(best_beta_hat_size[1], a, best_beta_hat_data, y_hat);
  }

  for (ixstart = 0; ixstart < 40000; ixstart++) {
    gx_full[ixstart] = y_hat->data[ixstart];
  }

  emxFree_real_T(&y_hat);
  ixstart = 1;
  vert = gx_full[0];
  if (rtIsNaN(gx_full[0])) {
    ix = 2;
    exitg1 = false;
    while ((!exitg1) && (ix < 40001)) {
      ixstart = ix;
      if (!rtIsNaN(gx_full[ix - 1])) {
        vert = gx_full[ix - 1];
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 40000) {
    while (ixstart + 1 < 40001) {
      if (gx_full[ixstart] < vert) {
        vert = gx_full[ixstart];
      }

      ixstart++;
    }
  }

  c_rdivide(vert, gx_full, gy_full);
  for (ixstart = 0; ixstart < 40000; ixstart++) {
    /*  figure(689), surf(imgF); */
    /*  hold on; surf(lowResPlane); hold off */
    obj->patchProcessed[ixstart] *= gy_full[ixstart];
  }
}

void DigitalDevice_glareRemoval(DigitalDevice *obj)
{
  double apnd;
  double a;
  boolean_T patchMaskNew[40000];
  boolean_T glareMask[40000];
  int j;
  static visioncodegen_BlobAnalysis hblob;
  int centroids_size[2];
  float centroids_data[200];
  int area_size[2];
  int area_data[100];
  int ii;
  int b_area_data[100];
  int ixstop;
  unsigned char medBuffer_data[100];
  int i;
  emxArray_real32_T *vert_range;
  emxArray_real32_T *hori_range;
  emxArray_real_T *tmpPatch;
  emxArray_real32_T *b_vert_range;
  emxArray_real32_T *b_hori_range;
  float vert_center;
  float hori_center;
  float varargin_2;
  float maxval;
  int n;
  double cdiff;
  double b_maxval;
  int jj;
  double c_maxval;
  int idx;
  int c_vert_range[1];
  emxArray_real_T b_tmpPatch;
  unsigned char u3;
  emxArray_int32_T *b_ii;
  emxArray_int32_T *b_jj;
  boolean_T exitg2;
  boolean_T guard1 = false;
  emxArray_real_T *idx_vert;
  emxArray_real_T *idx_hori;
  emxArray_real_T *distMat;
  emxArray_real32_T *r36;
  emxArray_real32_T *r37;
  emxArray_real_T *r38;
  emxArray_real32_T *b_idx_hori;
  emxArray_real32_T *b_idx_vert;
  unsigned short outsz[2];
  int itmp;
  int cindx;
  int ix;
  boolean_T exitg1;
  emxArray_real_T *extremum;
  removeReflectivePoints(obj->patchProcessed, obj->patchMask, patchMaskNew, &a,
    &apnd);
  for (j = 0; j < 40000; j++) {
    glareMask[j] = ((patchMaskNew[j] ^ obj->patchMask[j]) != 0);
  }

  if (c_sum(glareMask) != 0.0) {
    BlobAnalysis_BlobAnalysis(&hblob);
    c_SystemCore_step(&hblob, glareMask, area_data, area_size, centroids_data,
                      centroids_size);
    ii = area_size[0] * area_size[1];
    for (j = 0; j < ii; j++) {
      b_area_data[j] = area_data[j];
    }

    if ((0 == area_size[0]) || (0 == area_size[1])) {
      ixstop = 0;
    } else {
      ii = area_size[0];
      ixstop = area_size[1];
      if (ii >= ixstop) {
        ixstop = ii;
      }
    }

    for (j = 0; j < ixstop; j++) {
      medBuffer_data[j] = 0;
    }

    if ((0 == area_size[0]) || (0 == area_size[1])) {
      ixstop = 0;
    } else {
      ii = area_size[0];
      ixstop = area_size[1];
      if (ii >= ixstop) {
        ixstop = ii;
      }
    }

    i = 0;
    emxInit_real32_T(&vert_range, 2);
    emxInit_real32_T(&hori_range, 2);
    emxInit_real_T(&tmpPatch, 2);
    b_emxInit_real32_T(&b_vert_range, 1);
    b_emxInit_real32_T(&b_hori_range, 1);
    while (i <= ixstop - 1) {
      a = ceil(sqrt(b_area_data[i]) / 2.0);
      if (a <= 2.0) {
      } else {
        a = 2.0;
      }

      vert_center = rt_roundf_snf(centroids_data[i + centroids_size[0]]);
      hori_center = rt_roundf_snf(centroids_data[i]);
      varargin_2 = vert_center - (float)a;
      if (1.0F < varargin_2) {
        maxval = varargin_2;
      } else {
        maxval = 1.0F;
      }

      varargin_2 = vert_center + (float)a;
      if (200.0F > varargin_2) {
        vert_center = varargin_2;
      } else {
        vert_center = 200.0F;
      }

      if (vert_center < maxval) {
        n = -1;
      } else {
        ii = (int)floor(((double)vert_center - maxval) + 0.5);
        apnd = maxval + (double)ii;
        cdiff = apnd - vert_center;
        if (maxval > vert_center) {
          b_maxval = maxval;
        } else {
          b_maxval = vert_center;
        }

        if (fabs(cdiff) < 2.38418579E-7F * (float)b_maxval) {
          ii++;
        } else if (cdiff > 0.0) {
          vert_center = (float)(maxval + ((double)ii - 1.0));
        } else {
          ii++;
          vert_center = (float)apnd;
        }

        if (ii >= 0) {
          n = ii - 1;
        } else {
          n = -1;
        }
      }

      j = vert_range->size[0] * vert_range->size[1];
      vert_range->size[0] = 1;
      vert_range->size[1] = n + 1;
      emxEnsureCapacity((emxArray__common *)vert_range, j, (int)sizeof(float));
      if (n + 1 > 0) {
        vert_range->data[0] = maxval;
        if (n + 1 > 1) {
          vert_range->data[n] = vert_center;
          ii = n / 2;
          for (jj = 1; jj < ii; jj++) {
            vert_range->data[jj] = maxval + (float)jj;
            vert_range->data[n - jj] = vert_center - (float)jj;
          }

          if (ii << 1 == n) {
            vert_range->data[ii] = (maxval + vert_center) / 2.0F;
          } else {
            vert_range->data[ii] = maxval + (float)ii;
            vert_range->data[ii + 1] = vert_center - (float)ii;
          }
        }
      }

      varargin_2 = hori_center - (float)a;
      if (1.0F < varargin_2) {
        maxval = varargin_2;
      } else {
        maxval = 1.0F;
      }

      varargin_2 = hori_center + (float)a;
      if (200.0F > varargin_2) {
        vert_center = varargin_2;
      } else {
        vert_center = 200.0F;
      }

      if (vert_center < maxval) {
        n = -1;
      } else {
        ii = (int)floor(((double)vert_center - maxval) + 0.5);
        apnd = maxval + (double)ii;
        cdiff = apnd - vert_center;
        if (maxval > vert_center) {
          c_maxval = maxval;
        } else {
          c_maxval = vert_center;
        }

        if (fabs(cdiff) < 2.38418579E-7F * (float)c_maxval) {
          ii++;
        } else if (cdiff > 0.0) {
          vert_center = (float)(maxval + ((double)ii - 1.0));
        } else {
          ii++;
          vert_center = (float)apnd;
        }

        if (ii >= 0) {
          n = ii - 1;
        } else {
          n = -1;
        }
      }

      j = hori_range->size[0] * hori_range->size[1];
      hori_range->size[0] = 1;
      hori_range->size[1] = n + 1;
      emxEnsureCapacity((emxArray__common *)hori_range, j, (int)sizeof(float));
      if (n + 1 > 0) {
        hori_range->data[0] = maxval;
        if (n + 1 > 1) {
          hori_range->data[n] = vert_center;
          ii = n / 2;
          for (jj = 1; jj < ii; jj++) {
            hori_range->data[jj] = maxval + (float)jj;
            hori_range->data[n - jj] = vert_center - (float)jj;
          }

          if (ii << 1 == n) {
            hori_range->data[ii] = (maxval + vert_center) / 2.0F;
          } else {
            hori_range->data[ii] = maxval + (float)ii;
            hori_range->data[ii + 1] = vert_center - (float)ii;
          }
        }
      }

      j = tmpPatch->size[0] * tmpPatch->size[1];
      tmpPatch->size[0] = vert_range->size[1];
      tmpPatch->size[1] = hori_range->size[1];
      emxEnsureCapacity((emxArray__common *)tmpPatch, j, (int)sizeof(double));
      ii = hori_range->size[1];
      for (j = 0; j < ii; j++) {
        jj = vert_range->size[1];
        for (idx = 0; idx < jj; idx++) {
          tmpPatch->data[idx + tmpPatch->size[0] * j] = obj->patchProcessed
            [((int)vert_range->data[vert_range->size[0] * idx] + 200 * ((int)
               hori_range->data[hori_range->size[0] * j] - 1)) - 1];
        }
      }

      j = b_vert_range->size[0];
      b_vert_range->size[0] = vert_range->size[1];
      emxEnsureCapacity((emxArray__common *)b_vert_range, j, (int)sizeof(float));
      ii = vert_range->size[1];
      for (j = 0; j < ii; j++) {
        b_vert_range->data[j] = vert_range->data[vert_range->size[0] * j];
      }

      j = b_hori_range->size[0];
      b_hori_range->size[0] = hori_range->size[1];
      emxEnsureCapacity((emxArray__common *)b_hori_range, j, (int)sizeof(float));
      ii = hori_range->size[1];
      for (j = 0; j < ii; j++) {
        b_hori_range->data[j] = hori_range->data[hori_range->size[0] * j];
      }

      c_vert_range[0] = b_vert_range->size[0] * b_hori_range->size[0];
      b_tmpPatch = *tmpPatch;
      b_tmpPatch.size = (int *)&c_vert_range;
      b_tmpPatch.numDimensions = 1;
      a = rt_roundd_snf(median(&b_tmpPatch));
      if (a < 256.0) {
        if (a >= 0.0) {
          u3 = (unsigned char)a;
        } else {
          u3 = 0;
        }
      } else if (a >= 256.0) {
        u3 = MAX_uint8_T;
      } else {
        u3 = 0;
      }

      medBuffer_data[i] = u3;
      i++;
    }

    emxFree_real32_T(&b_hori_range);
    emxFree_real32_T(&b_vert_range);
    emxFree_real_T(&tmpPatch);
    emxFree_real32_T(&hori_range);
    emxFree_real32_T(&vert_range);
    emxInit_int32_T(&b_ii, 1);
    emxInit_int32_T(&b_jj, 1);
    idx = 0;
    j = b_ii->size[0];
    b_ii->size[0] = 40000;
    emxEnsureCapacity((emxArray__common *)b_ii, j, (int)sizeof(int));
    j = b_jj->size[0];
    b_jj->size[0] = 40000;
    emxEnsureCapacity((emxArray__common *)b_jj, j, (int)sizeof(int));
    ii = 1;
    jj = 1;
    exitg2 = false;
    while ((!exitg2) && (jj <= 200)) {
      guard1 = false;
      if (glareMask[(ii + 200 * (jj - 1)) - 1]) {
        idx++;
        b_ii->data[idx - 1] = ii;
        b_jj->data[idx - 1] = jj;
        if (idx >= 40000) {
          exitg2 = true;
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }

      if (guard1) {
        ii++;
        if (ii > 200) {
          ii = 1;
          jj++;
        }
      }
    }

    j = b_ii->size[0];
    if (1 > idx) {
      b_ii->size[0] = 0;
    } else {
      b_ii->size[0] = idx;
    }

    emxEnsureCapacity((emxArray__common *)b_ii, j, (int)sizeof(int));
    b_emxInit_real_T(&idx_vert, 1);
    j = b_jj->size[0];
    if (1 > idx) {
      b_jj->size[0] = 0;
    } else {
      b_jj->size[0] = idx;
    }

    emxEnsureCapacity((emxArray__common *)b_jj, j, (int)sizeof(int));
    j = idx_vert->size[0];
    idx_vert->size[0] = b_ii->size[0];
    emxEnsureCapacity((emxArray__common *)idx_vert, j, (int)sizeof(double));
    ii = b_ii->size[0];
    for (j = 0; j < ii; j++) {
      idx_vert->data[j] = b_ii->data[j];
    }

    b_emxInit_real_T(&idx_hori, 1);
    j = idx_hori->size[0];
    idx_hori->size[0] = b_jj->size[0];
    emxEnsureCapacity((emxArray__common *)idx_hori, j, (int)sizeof(double));
    ii = b_jj->size[0];
    for (j = 0; j < ii; j++) {
      idx_hori->data[j] = b_jj->data[j];
    }

    emxFree_int32_T(&b_jj);
    emxInit_real_T(&distMat, 2);

    /* % Given a set of pixels and a few centroids, assign a nearest centroid to */
    /*   each pixel and return the assigned list of indices. */
    ii = idx_vert->size[0];
    j = distMat->size[0] * distMat->size[1];
    distMat->size[0] = ii;
    emxEnsureCapacity((emxArray__common *)distMat, j, (int)sizeof(double));
    j = distMat->size[0] * distMat->size[1];
    distMat->size[1] = centroids_size[0];
    emxEnsureCapacity((emxArray__common *)distMat, j, (int)sizeof(double));
    ii = idx_vert->size[0] * centroids_size[0];
    for (j = 0; j < ii; j++) {
      distMat->data[j] = 0.0;
    }

    i = 0;
    b_emxInit_real32_T(&r36, 1);
    b_emxInit_real32_T(&r37, 1);
    b_emxInit_real_T(&r38, 1);
    b_emxInit_real32_T(&b_idx_hori, 1);
    b_emxInit_real32_T(&b_idx_vert, 1);
    while (i <= centroids_size[0] - 1) {
      j = b_idx_vert->size[0];
      b_idx_vert->size[0] = idx_vert->size[0];
      emxEnsureCapacity((emxArray__common *)b_idx_vert, j, (int)sizeof(float));
      ii = idx_vert->size[0];
      for (j = 0; j < ii; j++) {
        b_idx_vert->data[j] = (float)idx_vert->data[j] - centroids_data[i +
          centroids_size[0]];
      }

      e_power(b_idx_vert, r36);
      j = b_idx_hori->size[0];
      b_idx_hori->size[0] = idx_hori->size[0];
      emxEnsureCapacity((emxArray__common *)b_idx_hori, j, (int)sizeof(float));
      ii = idx_hori->size[0];
      for (j = 0; j < ii; j++) {
        b_idx_hori->data[j] = (float)idx_hori->data[j] - centroids_data[i];
      }

      e_power(b_idx_hori, r37);
      j = r36->size[0];
      emxEnsureCapacity((emxArray__common *)r36, j, (int)sizeof(float));
      ii = r36->size[0];
      for (j = 0; j < ii; j++) {
        r36->data[j] += r37->data[j];
      }

      b_sqrt(r36);
      j = r38->size[0];
      r38->size[0] = r36->size[0];
      emxEnsureCapacity((emxArray__common *)r38, j, (int)sizeof(double));
      ii = r36->size[0];
      for (j = 0; j < ii; j++) {
        r38->data[j] = r36->data[j];
      }

      ii = r38->size[0];
      for (j = 0; j < ii; j++) {
        distMat->data[j + distMat->size[0] * i] = r38->data[j];
      }

      i++;
    }

    emxFree_real32_T(&b_idx_vert);
    emxFree_real32_T(&b_idx_hori);
    emxFree_real_T(&r38);
    emxFree_real32_T(&r37);
    emxFree_real32_T(&r36);
    for (j = 0; j < 2; j++) {
      outsz[j] = (unsigned short)distMat->size[j];
    }

    j = b_ii->size[0];
    b_ii->size[0] = outsz[0];
    emxEnsureCapacity((emxArray__common *)b_ii, j, (int)sizeof(int));
    ii = outsz[0];
    for (j = 0; j < ii; j++) {
      b_ii->data[j] = 1;
    }

    n = distMat->size[1];
    ii = distMat->size[0];
    jj = 0;
    idx = -1;
    for (j = 1; j <= ii; j++) {
      jj++;
      i = jj;
      ixstop = jj + (n - 1) * ii;
      a = distMat->data[jj - 1];
      itmp = 1;
      if (n > 1) {
        cindx = 1;
        if (rtIsNaN(distMat->data[jj - 1])) {
          ix = jj + ii;
          exitg1 = false;
          while ((!exitg1) && (ix <= ixstop)) {
            cindx++;
            i = ix;
            if (!rtIsNaN(distMat->data[ix - 1])) {
              a = distMat->data[ix - 1];
              itmp = cindx;
              exitg1 = true;
            } else {
              ix += ii;
            }
          }
        }

        if (i < ixstop) {
          for (ix = i + ii; ix <= ixstop; ix += ii) {
            cindx++;
            if (distMat->data[ix - 1] < a) {
              a = distMat->data[ix - 1];
              itmp = cindx;
            }
          }
        }
      }

      idx++;
      b_ii->data[idx] = itmp;
    }

    emxFree_real_T(&distMat);
    b_emxInit_real_T(&extremum, 1);
    j = extremum->size[0];
    extremum->size[0] = b_ii->size[0];
    emxEnsureCapacity((emxArray__common *)extremum, j, (int)sizeof(double));
    ii = b_ii->size[0];
    for (j = 0; j < ii; j++) {
      extremum->data[j] = b_ii->data[j];
    }

    emxFree_int32_T(&b_ii);
    for (i = 0; i < extremum->size[0]; i++) {
      obj->patchProcessed[((int)idx_vert->data[i] + 200 * ((int)idx_hori->data[i]
        - 1)) - 1] = medBuffer_data[(int)extremum->data[i] - 1];
    }

    emxFree_real_T(&extremum);
    emxFree_real_T(&idx_hori);
    emxFree_real_T(&idx_vert);
  }

  for (j = 0; j < 40000; j++) {
    obj->patchMask[j] = patchMaskNew[j];
  }

  if (!hblob.matlabCodegenIsDeleted) {
    hblob.matlabCodegenIsDeleted = true;
  }
}

void c_DigitalDevice_processSquarePa(DigitalDevice *obj)
{
  boolean_T mask_large[1024];
  int i54;
  int loop_ub;
  static const boolean_T mask_small[441] = { false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, true, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, true, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, true, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, true, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    true, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, true,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, true, true, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, true, true, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, true, true, true, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, true, true, true, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, true, true, true, true, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, true, true, true, true, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, true,
    true, true, true, true, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, true, true, true,
    true, true, true, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, true, true, true, true, true, true,
    true, false, false, false, false, false, false, false, false, false, false,
    false, false, false, true, true, true, true, true, true, true, true, false,
    false, false, false, false, false, false, false, false, false, false, false,
    true, true, true, true, true, true, true, true, true, false, false, false,
    false, false, false, false, false, false, false, true, true, true, true,
    true, true, true, true, true, true, true, false, false, false, false, false,
    false, false, false, true, true, true, true, true, true, true, true, true,
    true, true, true, true, false, false, false, false, false, false, true, true,
    true, true, true, true, true, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true };

  boolean_T bv1[441];
  static const boolean_T bv2[441] = { true, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, true, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, true, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, true, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, true, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    true, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, true,
    true, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, true, true,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, true, true, true,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, true, true, true, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, true, true, true, true, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, true, true, true, true, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, true, true, true, true, true, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, true, true, true, true, true, true, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, true, true, true, true, true, true, true, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, true,
    true, true, true, true, true, true, true, false, false, false, false, false,
    false, false, false, false, false, false, false, false, true, true, true,
    true, true, true, true, true, true, false, false, false, false, false, false,
    false, false, false, false, false, false, true, true, true, true, true, true,
    true, true, true, true, true, false, false, false, false, false, false,
    false, false, false, false, true, true, true, true, true, true, true, true,
    true, true, true, true, true, false, false, false, false, false, false,
    false, false, true, true, true, true, true, true, true, true, true, true,
    true, true, true, true, true, false, false, false, false, false, false, true,
    true, true, true, true, true, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true };

  boolean_T b_obj[40000];
  emxArray_int32_T *r34;
  emxArray_int32_T *r35;
  emxArray_real_T *c_obj;
  double d2;

  /*  store the patch with the boundary */
  /*  size of the patch with boundary */
  /*  store the boundary-removed patch */
  /*  store the patch mask for calculating correlation */
  /*  store the preprocessed patch */
  /*  size of the patch without boundary */
  /*  store the name of the current dataset */
  /*  unique index of the patch in the dataset */
  /*  indicating whether the object can be used for matching */
  /*  feature for the patch */
  /*  parameter assignment */
  /*  function obj = processSquarePatch(obj, varargin) */
  /*  currently implementation */
  /*  function obj = processRawPatch(obj) */
  /*  early implementation, not recommended to use. Retained for */
  /*  compatibility purpose */
  /*  remove the glare using median filter (size adaptive to the */
  /*  size of glare) */
  /* figure(1); imshow(obj.patch); */
  /* figure(2); imshow(obj.patchProcessed); */
  /* pause(0.1) */
  /*              % filter parameters */
  /*              sigma1 = 5; sigma2 = 12; tol = 0.01; */
  /*              w  = 6*sigma1; if (mod(w,2) == 0), w  = w+1; end */
  /*              [image_filtered, param] =  shiftableBF(image, sigma1, sigma2, w, tol); */
  /*             %% (NOT used in the square patch experiment) */
  /*   a simple method for adaptively removing the boundary of the raw patch */
  /*   based on difference image signal */
  /*  width of the strip used determine the boundary index */
  /*  additional pad to be excluded */
  /*             %% (USED in the square patch experiment) */
  /*  1. cut away the excessive boundary according to the square */
  /*  patch design parameters */
  /*  2. mask out four corners using median filter */
  /*                 %% newest mode (no long support the single patch case) */
  createQuarterCircleMask(mask_large);

  /*  9 */
  for (i54 = 0; i54 < 200; i54++) {
    for (loop_ub = 0; loop_ub < 200; loop_ub++) {
      obj->patch[loop_ub + 200 * i54] = obj->rawPatch->data[(loop_ub +
        obj->rawPatch->size[0] * (i54 + 60)) + 458];
    }
  }

  /*  create a mask for conrer pixels for cross-correlation calculation */
  for (i54 = 0; i54 < 40000; i54++) {
    obj->patchMask[i54] = true;
  }

  for (i54 = 0; i54 < 21; i54++) {
    for (loop_ub = 0; loop_ub < 21; loop_ub++) {
      obj->patchMask[loop_ub + 200 * i54] = mask_small[loop_ub + 21 * i54];
    }
  }

  b_fliplr(mask_large);
  for (i54 = 0; i54 < 32; i54++) {
    for (loop_ub = 0; loop_ub < 32; loop_ub++) {
      obj->patchMask[loop_ub + 200 * (168 + i54)] = mask_large[loop_ub + (i54 <<
        5)];
    }
  }

  memcpy(&bv1[0], &mask_small[0], 441U * sizeof(boolean_T));
  flipud(bv1);
  for (i54 = 0; i54 < 21; i54++) {
    for (loop_ub = 0; loop_ub < 21; loop_ub++) {
      obj->patchMask[(loop_ub + 200 * i54) + 179] = bv1[loop_ub + 21 * i54];
    }
  }

  memcpy(&bv1[0], &bv2[0], 441U * sizeof(boolean_T));
  c_fliplr(bv1);
  for (i54 = 0; i54 < 21; i54++) {
    for (loop_ub = 0; loop_ub < 21; loop_ub++) {
      obj->patchMask[(loop_ub + 200 * (179 + i54)) + 179] = bv1[loop_ub + 21 *
        i54];
    }
  }

  /*  cropping */
  for (i54 = 0; i54 < 200; i54++) {
    for (loop_ub = 0; loop_ub < 6; loop_ub++) {
      obj->patchMask[loop_ub + 200 * i54] = false;
    }

    for (loop_ub = 0; loop_ub < 6; loop_ub++) {
      obj->patchMask[(loop_ub + 200 * i54) + 194] = false;
    }
  }

  for (i54 = 0; i54 < 6; i54++) {
    for (loop_ub = 0; loop_ub < 200; loop_ub++) {
      obj->patchMask[loop_ub + 200 * i54] = false;
    }
  }

  for (i54 = 0; i54 < 6; i54++) {
    for (loop_ub = 0; loop_ub < 200; loop_ub++) {
      obj->patchMask[loop_ub + 200 * (194 + i54)] = false;
    }
  }

  /*  fill 4 masked corners with corresponding background pixels */
  for (i54 = 0; i54 < 40000; i54++) {
    obj->patchProcessed[i54] = obj->patch[i54];
    b_obj[i54] = !obj->patchMask[i54];
  }

  emxInit_int32_T(&r34, 1);
  c_eml_li_find(b_obj, r34);
  for (i54 = 0; i54 < 40000; i54++) {
    b_obj[i54] = !obj->patchMask[i54];
  }

  emxInit_int32_T(&r35, 1);
  b_emxInit_real_T(&c_obj, 1);
  c_eml_li_find(b_obj, r35);
  i54 = c_obj->size[0];
  c_obj->size[0] = r35->size[0];
  emxEnsureCapacity((emxArray__common *)c_obj, i54, (int)sizeof(double));
  loop_ub = r35->size[0];
  for (i54 = 0; i54 < loop_ub; i54++) {
    c_obj->data[i54] = obj->patchProcessed[r35->data[i54] - 1];
  }

  emxFree_int32_T(&r35);
  d2 = median(c_obj);
  loop_ub = r34->size[0];
  emxFree_real_T(&c_obj);
  for (i54 = 0; i54 < loop_ub; i54++) {
    obj->patchProcessed[r34->data[i54] - 1] = d2;
  }

  emxFree_int32_T(&r34);
}

void d_DigitalDevice_processSquarePa(DigitalDevice *obj)
{
  boolean_T mask_large[1024];
  int i63;
  int loop_ub;
  static const boolean_T mask_small[441] = { false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, true, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, true, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, true, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, true, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    true, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, true,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, true, true, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, true, true, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, true, true, true, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, true, true, true, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, true, true, true, true, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, true, true, true, true, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, true,
    true, true, true, true, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, true, true, true,
    true, true, true, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, true, true, true, true, true, true,
    true, false, false, false, false, false, false, false, false, false, false,
    false, false, false, true, true, true, true, true, true, true, true, false,
    false, false, false, false, false, false, false, false, false, false, false,
    true, true, true, true, true, true, true, true, true, false, false, false,
    false, false, false, false, false, false, false, true, true, true, true,
    true, true, true, true, true, true, true, false, false, false, false, false,
    false, false, false, true, true, true, true, true, true, true, true, true,
    true, true, true, true, false, false, false, false, false, false, true, true,
    true, true, true, true, true, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true };

  boolean_T bv3[441];
  boolean_T b_obj[40000];
  emxArray_int32_T *r39;
  emxArray_int32_T *r40;
  emxArray_real_T *c_obj;
  double d3;

  /*  store the patch with the boundary */
  /*  size of the patch with boundary */
  /*  store the boundary-removed patch */
  /*  store the patch mask for calculating correlation */
  /*  store the preprocessed patch */
  /*  size of the patch without boundary */
  /*  store the name of the current dataset */
  /*  unique index of the patch in the dataset */
  /*  indicating whether the object can be used for matching */
  /*  feature for the patch */
  /*  parameter assignment */
  /*  function obj = processSquarePatch(obj, varargin) */
  /*  currently implementation */
  /*  function obj = processRawPatch(obj) */
  /*  early implementation, not recommended to use. Retained for */
  /*  compatibility purpose */
  /*  remove the glare using median filter (size adaptive to the */
  /*  size of glare) */
  /* figure(1); imshow(obj.patch); */
  /* figure(2); imshow(obj.patchProcessed); */
  /* pause(0.1) */
  /*              % filter parameters */
  /*              sigma1 = 5; sigma2 = 12; tol = 0.01; */
  /*              w  = 6*sigma1; if (mod(w,2) == 0), w  = w+1; end */
  /*              [image_filtered, param] =  shiftableBF(image, sigma1, sigma2, w, tol); */
  /*             %% (NOT used in the square patch experiment) */
  /*   a simple method for adaptively removing the boundary of the raw patch */
  /*   based on difference image signal */
  /*  width of the strip used determine the boundary index */
  /*  additional pad to be excluded */
  /*             %% (USED in the square patch experiment) */
  /*  1. cut away the excessive boundary according to the square */
  /*  patch design parameters */
  /*  2. mask out four corners using median filter */
  /*                 %% newest mode (no long support the single patch case) */
  createQuarterCircleMask(mask_large);

  /*  9 */
  for (i63 = 0; i63 < 200; i63++) {
    for (loop_ub = 0; loop_ub < 200; loop_ub++) {
      obj->patch[loop_ub + 200 * i63] = obj->rawPatch->data[(loop_ub +
        obj->rawPatch->size[0] * (i63 + 60)) + 259];
    }
  }

  /*  create a mask for conrer pixels for cross-correlation calculation */
  for (i63 = 0; i63 < 40000; i63++) {
    obj->patchMask[i63] = true;
  }

  for (i63 = 0; i63 < 21; i63++) {
    for (loop_ub = 0; loop_ub < 21; loop_ub++) {
      obj->patchMask[loop_ub + 200 * i63] = mask_small[loop_ub + 21 * i63];
    }
  }

  memcpy(&bv3[0], &mask_small[0], 441U * sizeof(boolean_T));
  c_fliplr(bv3);
  for (i63 = 0; i63 < 21; i63++) {
    for (loop_ub = 0; loop_ub < 21; loop_ub++) {
      obj->patchMask[loop_ub + 200 * (179 + i63)] = bv3[loop_ub + 21 * i63];
    }
  }

  memcpy(&bv3[0], &mask_small[0], 441U * sizeof(boolean_T));
  flipud(bv3);
  for (i63 = 0; i63 < 21; i63++) {
    for (loop_ub = 0; loop_ub < 21; loop_ub++) {
      obj->patchMask[(loop_ub + 200 * i63) + 179] = bv3[loop_ub + 21 * i63];
    }
  }

  b_flipud(mask_large);
  b_fliplr(mask_large);
  for (i63 = 0; i63 < 32; i63++) {
    for (loop_ub = 0; loop_ub < 32; loop_ub++) {
      obj->patchMask[(loop_ub + 200 * (168 + i63)) + 168] = mask_large[loop_ub +
        (i63 << 5)];
    }
  }

  /*  cropping */
  for (i63 = 0; i63 < 200; i63++) {
    for (loop_ub = 0; loop_ub < 6; loop_ub++) {
      obj->patchMask[loop_ub + 200 * i63] = false;
    }

    for (loop_ub = 0; loop_ub < 6; loop_ub++) {
      obj->patchMask[(loop_ub + 200 * i63) + 194] = false;
    }
  }

  for (i63 = 0; i63 < 6; i63++) {
    for (loop_ub = 0; loop_ub < 200; loop_ub++) {
      obj->patchMask[loop_ub + 200 * i63] = false;
    }
  }

  for (i63 = 0; i63 < 6; i63++) {
    for (loop_ub = 0; loop_ub < 200; loop_ub++) {
      obj->patchMask[loop_ub + 200 * (194 + i63)] = false;
    }
  }

  /*  fill 4 masked corners with corresponding background pixels */
  for (i63 = 0; i63 < 40000; i63++) {
    obj->patchProcessed[i63] = obj->patch[i63];
    b_obj[i63] = !obj->patchMask[i63];
  }

  emxInit_int32_T(&r39, 1);
  c_eml_li_find(b_obj, r39);
  for (i63 = 0; i63 < 40000; i63++) {
    b_obj[i63] = !obj->patchMask[i63];
  }

  emxInit_int32_T(&r40, 1);
  b_emxInit_real_T(&c_obj, 1);
  c_eml_li_find(b_obj, r40);
  i63 = c_obj->size[0];
  c_obj->size[0] = r40->size[0];
  emxEnsureCapacity((emxArray__common *)c_obj, i63, (int)sizeof(double));
  loop_ub = r40->size[0];
  for (i63 = 0; i63 < loop_ub; i63++) {
    c_obj->data[i63] = obj->patchProcessed[r40->data[i63] - 1];
  }

  emxFree_int32_T(&r40);
  d3 = median(c_obj);
  loop_ub = r39->size[0];
  emxFree_real_T(&c_obj);
  for (i63 = 0; i63 < loop_ub; i63++) {
    obj->patchProcessed[r39->data[i63] - 1] = d3;
  }

  emxFree_int32_T(&r39);
}

/* End of code generation (DigitalDevice.c) */
