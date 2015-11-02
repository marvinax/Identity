/*
 * findPointOnTheLine.c
 *
 * Code generation for function 'findPointOnTheLine'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "findPointOnTheLine.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void findPointOnTheLine(const double p[2], double lineParam_alpha_hat, double
  lineParam_beta_hat, double lineParam_gamma_hat, double p_new[2])
{
  double x_hat;
  double y_hat;

  /*  The line is in the form of  alpha * E[x] + beta * E[y] + gamma = 0 */
  /*  */
  /*  Chau-Wai Wong, Oct. 2014 */
  /*  case 1: use y coordinate to estimate x value */
  x_hat = -(lineParam_beta_hat * p[1] + lineParam_gamma_hat) /
    lineParam_alpha_hat;

  /*  case 2: use x coordinate to estimate y value */
  y_hat = -(lineParam_alpha_hat * p[0] + lineParam_gamma_hat) /
    lineParam_beta_hat;

  /*  choose the point on the line so that there's smaller estimation error */
  if ((fabs(p[0] - x_hat) < fabs(p[1] - y_hat)) || (lineParam_beta_hat == 0.0))
  {
    p_new[0] = x_hat;
    p_new[1] = p[1];
  } else {
    p_new[0] = p[0];
    p_new[1] = y_hat;
  }
}

/* End of code generation (findPointOnTheLine.c) */
