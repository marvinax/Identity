/*
 * isplaid.c
 *
 * Code generation for function 'isplaid'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "isplaid.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
boolean_T isplaid(const emxArray_real_T *varargin_1, const emxArray_real_T
                  *varargin_2)
{
  boolean_T p;
  unsigned int sz[2];
  int element_offset;
  int nx;
  unsigned int b_varargin_1[2];
  boolean_T b_p;
  boolean_T c_p;
  boolean_T exitg6;
  boolean_T guard1 = false;
  boolean_T b_guard1 = false;
  int i;
  int32_T exitg4;
  int32_T exitg3;
  boolean_T exitg5;
  int32_T exitg2;
  int32_T exitg1;
  p = false;
  for (element_offset = 0; element_offset < 2; element_offset++) {
    sz[element_offset] = (unsigned int)varargin_1->size[element_offset];
  }

  nx = varargin_1->size[0] * varargin_1->size[1];
  for (element_offset = 0; element_offset < 2; element_offset++) {
    b_varargin_1[element_offset] = (unsigned int)varargin_1->size[element_offset];
  }

  b_p = false;
  c_p = true;
  element_offset = 0;
  exitg6 = false;
  while ((!exitg6) && (element_offset < 2)) {
    if (!(b_varargin_1[element_offset] == sz[element_offset])) {
      c_p = false;
      exitg6 = true;
    } else {
      element_offset++;
    }
  }

  if (!c_p) {
  } else {
    b_p = true;
  }

  if (!b_p) {
  } else {
    guard1 = false;
    b_guard1 = false;
    if (nx > 1) {
      i = 0;
      do {
        exitg4 = 0;
        if (i + 1 <= varargin_1->size[0]) {
          element_offset = 1;
          do {
            exitg3 = 0;
            if (element_offset <= varargin_1->size[1]) {
              if (!(varargin_1->data[i] == varargin_1->data[i + (element_offset
                    - 1) * varargin_1->size[0]])) {
                exitg3 = 1;
              } else {
                element_offset++;
              }
            } else {
              i++;
              exitg3 = 2;
            }
          } while (exitg3 == 0);

          if (exitg3 == 1) {
            exitg4 = 1;
          }
        } else {
          exitg4 = 2;
        }
      } while (exitg4 == 0);

      if (exitg4 == 1) {
      } else {
        b_guard1 = true;
      }
    } else {
      b_guard1 = true;
    }

    if (b_guard1) {
      for (element_offset = 0; element_offset < 2; element_offset++) {
        b_varargin_1[element_offset] = (unsigned int)varargin_2->
          size[element_offset];
      }

      b_p = false;
      c_p = true;
      element_offset = 0;
      exitg5 = false;
      while ((!exitg5) && (element_offset < 2)) {
        if (!(b_varargin_1[element_offset] == sz[element_offset])) {
          c_p = false;
          exitg5 = true;
        } else {
          element_offset++;
        }
      }

      if (!c_p) {
      } else {
        b_p = true;
      }

      if (!b_p) {
      } else if (nx > 1) {
        i = 1;
        do {
          exitg2 = 0;
          if (i <= varargin_1->size[1]) {
            element_offset = (i - 1) * varargin_1->size[0];
            nx = 1;
            do {
              exitg1 = 0;
              if (nx <= varargin_1->size[0]) {
                if (!(varargin_2->data[element_offset] == varargin_2->data
                      [(element_offset + nx) - 1])) {
                  exitg1 = 1;
                } else {
                  nx++;
                }
              } else {
                i++;
                exitg1 = 2;
              }
            } while (exitg1 == 0);

            if (exitg1 == 1) {
              exitg2 = 1;
            }
          } else {
            guard1 = true;
            exitg2 = 1;
          }
        } while (exitg2 == 0);
      } else {
        guard1 = true;
      }
    }

    if (guard1) {
      p = true;
    }
  }

  return p;
}

/* End of code generation (isplaid.c) */
