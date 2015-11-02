/*
 * fitgeotrans.h
 *
 * Code generation for function 'fitgeotrans'
 *
 */

#ifndef __FITGEOTRANS_H__
#define __FITGEOTRANS_H__

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
extern void b_fitgeotrans(const double movingPoints[8], const double
  fixedPoints[8], double tform_T[9]);
extern void fitgeotrans(const double movingPoints[16], double tform_T[9]);

#endif

/* End of code generation (fitgeotrans.h) */
