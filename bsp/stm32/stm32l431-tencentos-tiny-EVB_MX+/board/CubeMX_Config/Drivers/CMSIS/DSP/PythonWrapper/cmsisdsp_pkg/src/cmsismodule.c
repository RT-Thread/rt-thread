/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Python Wrapper
 * Title:        cmsismodule.c
 * Description:  C code for the CMSIS-DSP Python wrapper
 *
 * $Date:        25. March 2019
 * $Revision:    V0.0.1
 *
 * Target Processor: Cortex-M cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2019 ARM Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#define NPY_NO_DEPRECATED_API NPY_1_15_API_VERSION

#ifdef WIN
#pragma warning( disable : 4013 ) 
#pragma warning( disable : 4244 ) 
#endif

#include <Python.h>
#define MAX(A,B) (A) < (B) ? (B) : (A)

#define CAT1(A,B) A##B
#define CAT(A,B) CAT1(A,B)


#ifdef CMSISDSP
#include "arm_math.h"
#define MODNAME "cmsisdsp"
#define MODINITNAME cmsisdsp
#endif 

#include <numpy/arrayobject.h>
#include <numpy/ndarraytypes.h>

#if PY_MAJOR_VERSION >= 3
#define IS_PY3K
#endif

struct module_state {
    PyObject *error;
};

#if PY_MAJOR_VERSION >= 3
#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))
#else
#define GETSTATE(m) (&_state)
static struct module_state _state;
#endif

static PyObject *
error_out(PyObject *m) {
    struct module_state *st = GETSTATE(m);
    PyErr_SetString(st->error, "something bad happened");
    return NULL;
}

#define MLTYPE(name,thenewfunc,deallocfunc,initfunc,methods)\
static PyTypeObject ml_##name##Type = {          \
    PyVarObject_HEAD_INIT(NULL, 0)               \
    .tp_name=MODNAME".##name",                   \
    .tp_basicsize = sizeof(ml_##name##Object),   \
    .tp_itemsize = 0,                            \
    .tp_dealloc = (destructor)deallocfunc,       \
    .tp_flags =  Py_TPFLAGS_DEFAULT,           \
    .tp_doc = #name,                             \
    .tp_init = (initproc)initfunc,               \
    .tp_new = (newfunc)thenewfunc,                \
    .tp_methods = methods  \
   };


#define MEMCPY(DST,SRC,NB,FORMAT) \
for(memCpyIndex = 0; memCpyIndex < (NB) ; memCpyIndex++)\
{                                \
  (DST)[memCpyIndex] = (FORMAT)(SRC)[memCpyIndex];       \
}

#define GETFIELD(NAME,FIELD,FORMAT)                                           \
static PyObject *                                                             \
Method_##NAME##_##FIELD(ml_##NAME##Object *self, PyObject *ignored)\
{                                                                             \
    return(Py_BuildValue(FORMAT,self->instance->FIELD));                      \
}                                                                             
    
#define GETFIELDARRAY(NAME,FIELD,FORMAT)                                           \
static PyObject *                                                             \
Method_##NAME##_##FIELD(ml_##NAME##Object *self, PyObject *ignored)\
{                                                                             \
    return(specific_##NAME##_##FIELD(self->instance));                      \
}  

#define INITARRAYFIELD(FIELD,FORMAT,SRCFORMAT,DSTFORMAT)                         \
    if (FIELD)                                                                \
    {                                                                         \
       PyArray_Descr *desct=PyArray_DescrFromType(FORMAT);                    \
       PyArrayObject *FIELD##c = (PyArrayObject *)PyArray_FromAny(FIELD,desct,\
        1,0,NPY_ARRAY_C_CONTIGUOUS | NPY_ARRAY_ALIGNED | NPY_ARRAY_FORCECAST, \
        NULL);                                                                \
       if (FIELD##c)                                                          \
       {                                                                      \
           uint32_t memCpyIndex; \
           SRCFORMAT *f=(SRCFORMAT*)PyArray_DATA(FIELD##c);                   \
           uint32_t n = PyArray_SIZE(FIELD##c);                               \
           self->instance->FIELD =PyMem_Malloc(sizeof(DSTFORMAT)*n);                \
           MEMCPY(self->instance->FIELD ,f,n,DSTFORMAT);                      \
           Py_DECREF(FIELD##c);                                               \
       }                                                                      \
    }
#define GETCARRAY(PYVAR,CVAR,FORMAT,SRCFORMAT,DSTFORMAT)                                \
    if (PYVAR)                                                                \
    {                                                                         \
       PyArray_Descr *desct=PyArray_DescrFromType(FORMAT);                    \
       PyArrayObject *PYVAR##c = (PyArrayObject *)PyArray_FromAny(PYVAR,desct,\
        1,0,NPY_ARRAY_C_CONTIGUOUS | NPY_ARRAY_ALIGNED | NPY_ARRAY_FORCECAST, \
        NULL);                                                                \
       if (PYVAR##c)                                                          \
       {                                                                      \
           uint32_t memCpyIndex; \
           SRCFORMAT *f=(SRCFORMAT*)PyArray_DATA(PYVAR##c);                         \
           uint32_t n = PyArray_SIZE(PYVAR##c);                               \
           CVAR =PyMem_Malloc(sizeof(DSTFORMAT)*n);                                 \
           MEMCPY(CVAR ,f,n,DSTFORMAT);                               \
           Py_DECREF(PYVAR##c);                                               \
       }                                                                      \
    }

#define GETARGUMENT(FIELD,FORMAT,SRCFORMAT,DSTFORMAT)                          \
    uint32_t arraySize##FIELD=0;                                               \
    if (FIELD)                                                                 \
    {                                                                          \
       PyArray_Descr *desct=PyArray_DescrFromType(FORMAT);                     \
       PyArrayObject *FIELD##c = (PyArrayObject *)PyArray_FromAny(FIELD,desct, \
        1,0,NPY_ARRAY_C_CONTIGUOUS | NPY_ARRAY_ALIGNED | NPY_ARRAY_FORCECAST,  \
        NULL);                                                                 \
       if (FIELD##c)                                                           \
       {                                                                       \
           uint32_t memCpyIndex; \
           SRCFORMAT *f=(SRCFORMAT*)PyArray_DATA(FIELD##c);                    \
           arraySize##FIELD = PyArray_SIZE(FIELD##c);                          \
           FIELD##_converted =PyMem_Malloc(sizeof(DSTFORMAT)*arraySize##FIELD);\
           MEMCPY(FIELD##_converted ,f,arraySize##FIELD,DSTFORMAT);            \
           Py_DECREF(FIELD##c);                                                \
       }                                                                       \
    }

#define FREEARGUMENT(FIELD) \
    PyMem_Free(FIELD)

#ifdef IS_PY3K
#define ADDTYPE(name)                                               \
    if (PyType_Ready(&ml_##name##Type) < 0)                         \
        return;                                              \
                                                                    \
    Py_INCREF(&ml_##name##Type);                                    \
    PyModule_AddObject(module, #name, (PyObject *)&ml_##name##Type);
#else
#define ADDTYPE(name)                                               \
    if (PyType_Ready(&ml_##name##Type) < 0)                         \
        return;                                                     \
                                                                    \
    Py_INCREF(&ml_##name##Type);                                    \
    PyModule_AddObject(module, #name, (PyObject *)&ml_##name##Type);
#endif

#define FLOATARRAY2(OBJ,NB1,NB2,DATA)                                      \
    npy_intp dims[2];                                                  \
    dims[0]=NB1;                                                       \
    dims[1]=NB2;                                                       \
    const int ND=2;                                                    \
    PyObject *OBJ=PyArray_SimpleNewFromData(ND, dims, NPY_FLOAT, DATA);

#define FLOATARRAY1(OBJ,NB1,DATA)                                          \
    npy_intp dims[1];                                                  \
    dims[0]=NB1;                                                       \
    const int ND=1;                                                    \
    PyObject *OBJ=PyArray_SimpleNewFromData(ND, dims, NPY_FLOAT, DATA);

#define FLOAT64ARRAY1(OBJ,NB1,DATA)                                          \
    npy_intp dims[1];                                                  \
    dims[0]=NB1;                                                       \
    const int ND=1;                                                    \
    PyObject *OBJ=PyArray_SimpleNewFromData(ND, dims, NPY_DOUBLE, DATA);

#define UINT32ARRAY1(OBJ,NB1,DATA)                                          \
    npy_intp dims[1];                                                   \
    dims[0]=NB1;                                                        \
    const int ND=1;                                                     \
    PyObject *OBJ=PyArray_SimpleNewFromData(ND, dims, NPY_UINT32, DATA);

#define INT32ARRAY1(OBJ,NB1,DATA)                                          \
    npy_intp dims[1];                                                   \
    dims[0]=NB1;                                                        \
    const int ND=1;                                                     \
    PyObject *OBJ=PyArray_SimpleNewFromData(ND, dims, NPY_INT32, DATA);

#define INT16ARRAY1(OBJ,NB1,DATA)                                          \
    npy_intp dims[1];                                                   \
    dims[0]=NB1;                                                        \
    const int ND=1;                                                     \
    PyObject *OBJ=PyArray_SimpleNewFromData(ND, dims, NPY_INT16, DATA);

#define INT8ARRAY1(OBJ,NB1,DATA)                                          \
    npy_intp dims[1];                                                   \
    dims[0]=NB1;                                                        \
    const int ND=1;                                                     \
    PyObject *OBJ=PyArray_SimpleNewFromData(ND, dims, NPY_BYTE, DATA);


#define MATRIXFROMNUMPY(EXT,TYP,SRCTYPE,NUMPYTYPE)                                   \
arm_matrix_instance_##EXT *EXT##MatrixFromNumpy(PyObject *o)                   \
{                                                                            \
    arm_matrix_instance_##EXT *s;                                              \
                                                                             \
    s=PyMem_Malloc(sizeof(arm_matrix_instance_##EXT));                               \
    s->pData=NULL;                                                           \
    s->numRows=0;                                                            \
    s->numCols=0;                                                            \
                                                                             \
    PyArray_Descr *desct=PyArray_DescrFromType(NUMPYTYPE);                    \
    PyArrayObject *cdata = (PyArrayObject *)PyArray_FromAny(o,desct,         \
        1,0,NPY_ARRAY_C_CONTIGUOUS | NPY_ARRAY_ALIGNED | NPY_ARRAY_FORCECAST, \
        NULL);                                                                \
    if (cdata)                                                               \
    {                                                                        \
           uint32_t memCpyIndex;                                             \
           SRCTYPE *f=(SRCTYPE*)PyArray_DATA(cdata);                           \
           s->numRows=PyArray_DIM(cdata,0);                                  \
           s->numCols=PyArray_DIM(cdata,1);                                  \
           uint32_t nb = PyArray_SIZE(cdata);                                \
           s->pData = PyMem_Malloc(sizeof(TYP)*nb);                                \
           MEMCPY(s->pData ,f,nb,TYP);                                       \
           Py_DECREF(cdata);                                                 \
    }                                                                        \
                                                                             \
                                                                             \
    return(s);                                                               \
                                                                             \
}

MATRIXFROMNUMPY(f32,float32_t,double,NPY_DOUBLE);
MATRIXFROMNUMPY(f64,float64_t,double,NPY_DOUBLE);
MATRIXFROMNUMPY(q31,q31_t,int32_t,NPY_INT32);
MATRIXFROMNUMPY(q15,q15_t,int16_t,NPY_INT16);

#define CREATEMATRIX(EXT,TYP)                                        \
arm_matrix_instance_##EXT *create##EXT##Matrix(uint32_t r,uint32_t c)\
{                                                                    \
    arm_matrix_instance_##EXT *s;                                      \
                                                                     \
    s=PyMem_Malloc(sizeof(arm_matrix_instance_##EXT));                     \
    s->pData=PyMem_Malloc(sizeof(TYP)*r*c);                                \
    s->numRows=r;                                                    \
    s->numCols=c;                                                    \
    return(s);                                                       \
}

CREATEMATRIX(f32,float32_t);
CREATEMATRIX(f64,float64_t);
CREATEMATRIX(q31,q31_t);
CREATEMATRIX(q15,q15_t);

#define NUMPYARRAYFROMMATRIX(EXT,NUMPYTYPE_FROMC)                                  \
PyObject *NumpyArrayFrom##EXT##Matrix(arm_matrix_instance_##EXT *mat)              \
{                                                                                  \
    npy_intp dims[2];                                                              \
    dims[0]=mat->numRows;                                                          \
    dims[1]=mat->numCols;                                                          \
    const int ND=2;                                                                \
    PyObject *OBJ=PyArray_SimpleNewFromData(ND, dims, NUMPYTYPE_FROMC, mat->pData);\
    return(OBJ);                                                                   \
}

NUMPYARRAYFROMMATRIX(f32,NPY_FLOAT);
NUMPYARRAYFROMMATRIX(f64,NPY_DOUBLE);
NUMPYARRAYFROMMATRIX(q31,NPY_INT32);
NUMPYARRAYFROMMATRIX(q15,NPY_INT16);

//#include "specific.h"
#include "cmsismodule.h"

#if 0
static PyObject *cmsisml_test(PyObject *obj, PyObject *args)
{
    ml_arm_svm_linear_instance_f32Object *self=NULL;
    PyObject *svm, *vector=NULL;

    if (!PyArg_ParseTuple(args, "OO", &svm,&vector))
        return NULL;

    self=(ml_arm_svm_linear_instance_f32Object*)svm;
    if (self)
    {
        if (self->instance)
        {
            int result;
            float32_t *input=NULL;
            GETCARRAY(vector,input,NPY_DOUBLE,double,float32_t);
            
            arm_svm_linear_predict_f32(self->instance,input,&result);
            /*
            printf("Dual\n");
            for(int i = 0 ; i < self->instance->nbOfSupportVectors ; i++)
            {
                printf("%f\n",self->instance->dualCoefficients[i]);
            }
            printf("Vectors\n");
            int k=0;
            for(int i = 0 ; i < self->instance->nbOfSupportVectors ; i++)
            {
                printf("Vector %d\n",i);
                for(int j = 0 ; j < self->instance->vectorDimension ; j++)
                {
                    printf("%f\n",self->instance->supportVectors[k]);
                    k++;
                }
            }
            printf("Classes\n");
            for(int i = 0 ; i < 2 ; i++)
            {
                printf("%d\n",self->instance->classes[i]);
            }
            printf("Intercept %f\n",self->instance->intercept);
*/
            PyMem_Free(input);
            return(Py_BuildValue("i",result));
        }
    }
    return(Py_BuildValue("i",-1));
}
#endif

#ifdef IS_PY3K
static int cmsisml_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int cmsisml_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}


static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        MODNAME,
        NULL,
        sizeof(struct module_state),
        CMSISMLMethods,
        NULL,
        cmsisml_traverse,
        cmsisml_clear,
        NULL
};

#define INITERROR return NULL

PyMODINIT_FUNC
CAT(PyInit_,MODINITNAME)(void)


#else
#define INITERROR return

void CAT(init,MODINITNAME)(void)
#endif
{
    import_array();

  #ifdef IS_PY3K
    PyObject *module = PyModule_Create(&moduledef);
  #else
    PyObject *module = Py_InitModule(MODNAME, CMSISMLMethods);
  #endif

  if (module == NULL)
      INITERROR;
  struct module_state *st = GETSTATE(module);
  
  st->error = PyErr_NewException(MODNAME".Error", NULL, NULL);
  if (st->error == NULL) {
      Py_DECREF(module);
      INITERROR;
  }


  typeRegistration(module);

  #ifdef IS_PY3K
    return module;
  #endif
}