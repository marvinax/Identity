/*
 * DigitalDevice.h
 *
 * Code generation for function 'DigitalDevice'
 *
 */

#ifndef __DIGITALDEVICE_H__
#define __DIGITALDEVICE_H__

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
extern void DigitalDevice_detrend(DigitalDevice *obj);
extern void DigitalDevice_glareRemoval(DigitalDevice *obj);
extern void c_DigitalDevice_processSquarePa(DigitalDevice *obj);
extern void d_DigitalDevice_processSquarePa(DigitalDevice *obj);

#endif

/* End of code generation (DigitalDevice.h) */
