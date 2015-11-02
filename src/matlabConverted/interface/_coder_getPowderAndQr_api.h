/*
 * _coder_getPowderAndQr_api.h
 *
 * Code generation for function 'getPowderAndQr'
 *
 */

#ifndef ___CODER_GETPOWDERANDQR_API_H__
#define ___CODER_GETPOWDERANDQR_API_H__
/* Include files */
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T
{
    real_T *data;
    int32_T *size;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_real_T*/
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /*typedef_emxArray_real_T*/
#ifndef struct_emxArray_boolean_T
#define struct_emxArray_boolean_T
struct emxArray_boolean_T
{
    boolean_T *data;
    int32_T *size;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_boolean_T*/
#ifndef typedef_emxArray_boolean_T
#define typedef_emxArray_boolean_T
typedef struct emxArray_boolean_T emxArray_boolean_T;
#endif /*typedef_emxArray_boolean_T*/

/* Function Declarations */
extern void getPowderAndQr_initialize(emlrtContext *aContext);
extern void getPowderAndQr_terminate(void);
extern void getPowderAndQr_atexit(void);
extern void getPowderAndQr_api(const mxArray *prhs[4], const mxArray *plhs[3]);
extern void getPowderAndQr(emxArray_real_T *reducedSizeImg, emxArray_boolean_T *reducedSizeMask, real_T edgeLength, uint8_T debugMode, emxArray_real_T *imgPowder, emxArray_real_T *imgQr, boolean_T *successFlag);
extern void getPowderAndQr_xil_terminate(void);

#endif
/* End of code generation (_coder_getPowderAndQr_api.h) */
