/*
 * getPowderAndQr_emxutil.h
 *
 * Code generation for function 'getPowderAndQr_emxutil'
 *
 */

#ifndef __GETPOWDERANDQR_EMXUTIL_H__
#define __GETPOWDERANDQR_EMXUTIL_H__

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
extern void b_emxInitStruct_struct_T(c_struct_T *pStruct);
extern void b_emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int
  numDimensions);
extern void b_emxInit_real32_T(emxArray_real32_T **pEmxArray, int numDimensions);
extern void b_emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);
extern void b_emxInit_uint8_T(emxArray_uint8_T **pEmxArray, int numDimensions);
extern void c_emxFreeStruct_visioncodegen_H(visioncodegen_HoughTransform_6
  *pStruct);
extern void c_emxInitStruct_visioncodegen_H(visioncodegen_HoughTransform_6
  *pStruct);
extern void c_emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);
extern void emxCopyStruct_struct_T(c_struct_T *dst, const c_struct_T *src);
extern void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, int
  elementSize);
extern void emxFreeMatrix_struct_T(c_struct_T pMatrix[2]);
extern void emxFreeStruct_AlignWorker_v2(AlignWorker_v2 *pStruct);
extern void emxFreeStruct_DigitalDevice(DigitalDevice *pStruct);
extern void emxFreeStruct_struct_T(c_struct_T *pStruct);
extern void emxFree_boolean_T(emxArray_boolean_T **pEmxArray);
extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);
extern void emxFree_real32_T(emxArray_real32_T **pEmxArray);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxFree_uint8_T(emxArray_uint8_T **pEmxArray);
extern void emxInitMatrix_struct_T(c_struct_T pMatrix[2]);
extern void emxInitStruct_AlignWorker_v2(AlignWorker_v2 *pStruct);
extern void emxInitStruct_DigitalDevice(DigitalDevice *pStruct);
extern void emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int numDimensions);
extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions);
extern void emxInit_real32_T(emxArray_real32_T **pEmxArray, int numDimensions);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);
extern void emxInit_uint8_T(emxArray_uint8_T **pEmxArray, int numDimensions);

#endif

/* End of code generation (getPowderAndQr_emxutil.h) */
