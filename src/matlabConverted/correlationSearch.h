/*
 * correlationSearch.h
 *
 * Code generation for function 'correlationSearch'
 *
 */

#ifndef __CORRELATIONSEARCH_H__
#define __CORRELATIONSEARCH_H__

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
extern void b_correlationSearch(const emxArray_uint8_T *wholeImg, const double
  coordinates[8], const unsigned char refCircle_small_data_data[], const int
  refCircle_small_data_size[2], double c_refCircle_small_halfCirclePat, const
  unsigned char refCircle_large_data_data[], const int
  refCircle_large_data_size[2], double c_refCircle_large_halfCirclePat, double
  coordinates_new[8], double circleSizeNum[4], double dVec_overall[2]);
extern void correlationSearch(const emxArray_uint8_T *wholeImg, const double
  coordinates[16], const unsigned char refCircle_small_data_data[], const int
  refCircle_small_data_size[2], double c_refCircle_small_halfCirclePat, const
  unsigned char refCircle_large_data_data[], const int
  refCircle_large_data_size[2], double c_refCircle_large_halfCirclePat, double
  coordinates_new[16], double circleSizeNum[8], double dVec_overall[2]);

#endif

/* End of code generation (correlationSearch.h) */
