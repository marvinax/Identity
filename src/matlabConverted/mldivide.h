/*
 * mldivide.h
 *
 * Code generation for function 'mldivide'
 *
 */

#ifndef __MLDIVIDE_H__
#define __MLDIVIDE_H__

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "getPowderAndQr_types.h"

/* Function Declarations */
extern void b_mldivide(const double A[9], const double B[9], double Y[9]);
extern void c_mldivide(const double A[9], const double B[3], double Y[3]);
extern void d_mldivide(const double A[36], double B[6]);
extern void e_mldivide(const double A[64], double B[8]);
extern double eml_xnrm2(int n, const double x[128], int ix0);
extern void mldivide(const double A[128], const double B[16], double Y[8]);

#endif

/* End of code generation (mldivide.h) */
