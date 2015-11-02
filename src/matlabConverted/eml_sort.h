/*
 * eml_sort.h
 *
 * Code generation for function 'eml_sort'
 *
 */

#ifndef __EML_SORT_H__
#define __EML_SORT_H__

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
extern void eml_sort(const double x_data[], const int x_size[2], double y_data[],
                     int y_size[2], int idx_data[], int idx_size[2]);

#endif

/* End of code generation (eml_sort.h) */
