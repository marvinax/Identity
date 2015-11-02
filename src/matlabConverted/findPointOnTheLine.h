/*
 * findPointOnTheLine.h
 *
 * Code generation for function 'findPointOnTheLine'
 *
 */

#ifndef __FINDPOINTONTHELINE_H__
#define __FINDPOINTONTHELINE_H__

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
extern void findPointOnTheLine(const double p[2], double lineParam_alpha_hat,
  double lineParam_beta_hat, double lineParam_gamma_hat, double p_new[2]);

#endif

/* End of code generation (findPointOnTheLine.h) */
