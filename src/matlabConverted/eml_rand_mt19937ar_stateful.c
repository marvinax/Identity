/*
 * eml_rand_mt19937ar_stateful.c
 *
 * Code generation for function 'eml_rand_mt19937ar_stateful'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "eml_rand_mt19937ar_stateful.h"
#include "getPowderAndQr_data.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void c_eml_rand_mt19937ar_stateful_i(void)
{
  unsigned int r;
  int mti;
  memset(&state[0], 0, 625U * sizeof(unsigned int));
  r = 5489U;
  state[0] = 5489U;
  for (mti = 0; mti < 623; mti++) {
    r = (r ^ r >> 30U) * 1812433253U + (1 + mti);
    state[mti + 1] = r;
  }

  state[624] = 624U;
}

/* End of code generation (eml_rand_mt19937ar_stateful.c) */
