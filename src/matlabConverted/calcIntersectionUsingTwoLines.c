/*
 * calcIntersectionUsingTwoLines.c
 *
 * Code generation for function 'calcIntersectionUsingTwoLines'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "calcIntersectionUsingTwoLines.h"
#include "det.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void calcIntersectionUsingTwoLines(const double line1_point1[2], const double
  line1_point2[2], const double line2_point1[2], const double line2_point2[2],
  double p_hat[2])
{
  double b_line1_point1[4];
  double b_line2_point1[4];
  int i19;
  double det_p1;
  double det_p2;
  double delta_x1;
  double delta_y1;
  double delta_x2;
  double delta_y2;
  double b_delta_x1[4];
  double deno;

  /*  Derivations see my handwritten notes. All points are stored in column */
  /*  vector form. */
  /*  Chau-Wai Wong, Oct. 2014 */
  for (i19 = 0; i19 < 2; i19++) {
    b_line1_point1[i19] = line1_point1[i19];
    b_line1_point1[2 + i19] = line1_point2[i19];
    b_line2_point1[i19] = line2_point1[i19];
    b_line2_point1[2 + i19] = line2_point2[i19];
  }

  det_p1 = det(b_line1_point1);
  det_p2 = det(b_line2_point1);
  delta_x1 = line1_point1[0] - line1_point2[0];
  delta_y1 = line1_point1[1] - line1_point2[1];
  delta_x2 = line2_point1[0] - line2_point2[0];
  delta_y2 = line2_point1[1] - line2_point2[1];
  b_delta_x1[0] = delta_x1;
  b_delta_x1[2] = delta_x2;
  b_delta_x1[1] = delta_y1;
  b_delta_x1[3] = delta_y2;
  deno = -det(b_delta_x1);
  p_hat[0] = -(det_p1 * delta_x2 - det_p2 * delta_x1) / deno;
  p_hat[1] = -(det_p1 * delta_y2 - det_p2 * delta_y1) / deno;
}

/* End of code generation (calcIntersectionUsingTwoLines.c) */
