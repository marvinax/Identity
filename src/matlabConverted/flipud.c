/*
 * flipud.c
 *
 * Code generation for function 'flipud'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "flipud.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void b_flipud(boolean_T x[1024])
{
  int j;
  int i;
  boolean_T xtmp;
  for (j = 0; j < 32; j++) {
    for (i = 0; i < 16; i++) {
      xtmp = x[i + (j << 5)];
      x[i + (j << 5)] = x[((j << 5) - i) + 31];
      x[((j << 5) - i) + 31] = xtmp;
    }
  }
}

void flipud(boolean_T x[441])
{
  int j;
  int i;
  boolean_T xtmp;
  for (j = 0; j < 21; j++) {
    for (i = 0; i < 10; i++) {
      xtmp = x[i + 21 * j];
      x[i + 21 * j] = x[(21 * j - i) + 20];
      x[(21 * j - i) + 20] = xtmp;
    }
  }
}

/* End of code generation (flipud.c) */
