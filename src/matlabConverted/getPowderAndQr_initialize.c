/*
 * getPowderAndQr_initialize.c
 *
 * Code generation for function 'getPowderAndQr_initialize'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "getPowderAndQr_initialize.h"
#include "eml_rand_mt19937ar_stateful.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void getPowderAndQr_initialize(void)
{
  rt_InitInfAndNaN(8U);
  c_eml_rand_mt19937ar_stateful_i();
}

/* End of code generation (getPowderAndQr_initialize.c) */
