/*
 * svd.h
 *
 * Code generation for function 'svd'
 *
 */

#ifndef __SVD_H__
#define __SVD_H__

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
extern void b_svd(const double A[64], double U[8]);
extern void svd(const double A[128], double U[8]);

#endif

/* End of code generation (svd.h) */
