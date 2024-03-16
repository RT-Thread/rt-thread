/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Python Wrapper
 * Title:        cmsismodule.h
 * Description:  Automatically generated C code for the CMSIS-DSP Python wrapper
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
typedef struct {
    PyObject_HEAD
    arm_fir_instance_q7 *instance;
} ml_arm_fir_instance_q7Object;


static void
arm_fir_instance_q7_dealloc(ml_arm_fir_instance_q7Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_fir_instance_q7_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_fir_instance_q7Object *self;
    //printf("New called\n");

    self = (ml_arm_fir_instance_q7Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_fir_instance_q7));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_fir_instance_q7_init(ml_arm_fir_instance_q7Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
char *kwlist[] = {
"numTaps",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|h", kwlist,&self->instance->numTaps
))
    {


    }
    return 0;
}

GETFIELD(arm_fir_instance_q7,numTaps,"h");


static PyMethodDef arm_fir_instance_q7_methods[] = {

    {"numTaps", (PyCFunction) Method_arm_fir_instance_q7_numTaps,METH_NOARGS,"numTaps"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_fir_instance_q7,arm_fir_instance_q7_new,arm_fir_instance_q7_dealloc,arm_fir_instance_q7_init,arm_fir_instance_q7_methods);


typedef struct {
    PyObject_HEAD
    arm_fir_instance_q15 *instance;
} ml_arm_fir_instance_q15Object;


static void
arm_fir_instance_q15_dealloc(ml_arm_fir_instance_q15Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_fir_instance_q15_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_fir_instance_q15Object *self;
    //printf("New called\n");

    self = (ml_arm_fir_instance_q15Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_fir_instance_q15));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_fir_instance_q15_init(ml_arm_fir_instance_q15Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
char *kwlist[] = {
"numTaps",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|h", kwlist,&self->instance->numTaps
))
    {


    }
    return 0;
}

GETFIELD(arm_fir_instance_q15,numTaps,"h");


static PyMethodDef arm_fir_instance_q15_methods[] = {

    {"numTaps", (PyCFunction) Method_arm_fir_instance_q15_numTaps,METH_NOARGS,"numTaps"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_fir_instance_q15,arm_fir_instance_q15_new,arm_fir_instance_q15_dealloc,arm_fir_instance_q15_init,arm_fir_instance_q15_methods);


typedef struct {
    PyObject_HEAD
    arm_fir_instance_q31 *instance;
} ml_arm_fir_instance_q31Object;


static void
arm_fir_instance_q31_dealloc(ml_arm_fir_instance_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_fir_instance_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_fir_instance_q31Object *self;
    //printf("New called\n");

    self = (ml_arm_fir_instance_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_fir_instance_q31));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_fir_instance_q31_init(ml_arm_fir_instance_q31Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
char *kwlist[] = {
"numTaps",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|h", kwlist,&self->instance->numTaps
))
    {


    }
    return 0;
}

GETFIELD(arm_fir_instance_q31,numTaps,"h");


static PyMethodDef arm_fir_instance_q31_methods[] = {

    {"numTaps", (PyCFunction) Method_arm_fir_instance_q31_numTaps,METH_NOARGS,"numTaps"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_fir_instance_q31,arm_fir_instance_q31_new,arm_fir_instance_q31_dealloc,arm_fir_instance_q31_init,arm_fir_instance_q31_methods);


typedef struct {
    PyObject_HEAD
    arm_fir_instance_f32 *instance;
} ml_arm_fir_instance_f32Object;


static void
arm_fir_instance_f32_dealloc(ml_arm_fir_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_fir_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_fir_instance_f32Object *self;
    //printf("New called\n");

    self = (ml_arm_fir_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_fir_instance_f32));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_fir_instance_f32_init(ml_arm_fir_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
char *kwlist[] = {
"numTaps",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|h", kwlist,&self->instance->numTaps
))
    {


    }
    return 0;
}

GETFIELD(arm_fir_instance_f32,numTaps,"h");


static PyMethodDef arm_fir_instance_f32_methods[] = {

    {"numTaps", (PyCFunction) Method_arm_fir_instance_f32_numTaps,METH_NOARGS,"numTaps"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_fir_instance_f32,arm_fir_instance_f32_new,arm_fir_instance_f32_dealloc,arm_fir_instance_f32_init,arm_fir_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_biquad_casd_df1_inst_q15 *instance;
} ml_arm_biquad_casd_df1_inst_q15Object;


static void
arm_biquad_casd_df1_inst_q15_dealloc(ml_arm_biquad_casd_df1_inst_q15Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_biquad_casd_df1_inst_q15_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_biquad_casd_df1_inst_q15Object *self;
    //printf("New called\n");

    self = (ml_arm_biquad_casd_df1_inst_q15Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_biquad_casd_df1_inst_q15));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_biquad_casd_df1_inst_q15_init(ml_arm_biquad_casd_df1_inst_q15Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
char *kwlist[] = {
"numStages","postShift",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|ii", kwlist,&self->instance->numStages
,&self->instance->postShift
))
    {


    }
    return 0;
}

GETFIELD(arm_biquad_casd_df1_inst_q15,numStages,"i");
GETFIELD(arm_biquad_casd_df1_inst_q15,postShift,"i");


static PyMethodDef arm_biquad_casd_df1_inst_q15_methods[] = {

    {"numStages", (PyCFunction) Method_arm_biquad_casd_df1_inst_q15_numStages,METH_NOARGS,"numStages"},
    {"postShift", (PyCFunction) Method_arm_biquad_casd_df1_inst_q15_postShift,METH_NOARGS,"postShift"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_biquad_casd_df1_inst_q15,arm_biquad_casd_df1_inst_q15_new,arm_biquad_casd_df1_inst_q15_dealloc,arm_biquad_casd_df1_inst_q15_init,arm_biquad_casd_df1_inst_q15_methods);


typedef struct {
    PyObject_HEAD
    arm_biquad_casd_df1_inst_q31 *instance;
} ml_arm_biquad_casd_df1_inst_q31Object;


static void
arm_biquad_casd_df1_inst_q31_dealloc(ml_arm_biquad_casd_df1_inst_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_biquad_casd_df1_inst_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_biquad_casd_df1_inst_q31Object *self;
    //printf("New called\n");

    self = (ml_arm_biquad_casd_df1_inst_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_biquad_casd_df1_inst_q31));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_biquad_casd_df1_inst_q31_init(ml_arm_biquad_casd_df1_inst_q31Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
char *kwlist[] = {
"numStages","postShift",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|ii", kwlist,&self->instance->numStages
,&self->instance->postShift
))
    {


    }
    return 0;
}

GETFIELD(arm_biquad_casd_df1_inst_q31,numStages,"i");
GETFIELD(arm_biquad_casd_df1_inst_q31,postShift,"i");


static PyMethodDef arm_biquad_casd_df1_inst_q31_methods[] = {

    {"numStages", (PyCFunction) Method_arm_biquad_casd_df1_inst_q31_numStages,METH_NOARGS,"numStages"},
    {"postShift", (PyCFunction) Method_arm_biquad_casd_df1_inst_q31_postShift,METH_NOARGS,"postShift"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_biquad_casd_df1_inst_q31,arm_biquad_casd_df1_inst_q31_new,arm_biquad_casd_df1_inst_q31_dealloc,arm_biquad_casd_df1_inst_q31_init,arm_biquad_casd_df1_inst_q31_methods);


typedef struct {
    PyObject_HEAD
    arm_biquad_casd_df1_inst_f32 *instance;
} ml_arm_biquad_casd_df1_inst_f32Object;


static void
arm_biquad_casd_df1_inst_f32_dealloc(ml_arm_biquad_casd_df1_inst_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_biquad_casd_df1_inst_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_biquad_casd_df1_inst_f32Object *self;
    //printf("New called\n");

    self = (ml_arm_biquad_casd_df1_inst_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_biquad_casd_df1_inst_f32));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_biquad_casd_df1_inst_f32_init(ml_arm_biquad_casd_df1_inst_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
char *kwlist[] = {
"numStages",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|i", kwlist,&self->instance->numStages
))
    {


    }
    return 0;
}

GETFIELD(arm_biquad_casd_df1_inst_f32,numStages,"i");


static PyMethodDef arm_biquad_casd_df1_inst_f32_methods[] = {

    {"numStages", (PyCFunction) Method_arm_biquad_casd_df1_inst_f32_numStages,METH_NOARGS,"numStages"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_biquad_casd_df1_inst_f32,arm_biquad_casd_df1_inst_f32_new,arm_biquad_casd_df1_inst_f32_dealloc,arm_biquad_casd_df1_inst_f32_init,arm_biquad_casd_df1_inst_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_matrix_instance_f32 *instance;
} ml_arm_matrix_instance_f32Object;


static void
arm_matrix_instance_f32_dealloc(ml_arm_matrix_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pData)
       {
          PyMem_Free(self->instance->pData);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_matrix_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_matrix_instance_f32Object *self;
    //printf("New called\n");

    self = (ml_arm_matrix_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_matrix_instance_f32));

        self->instance->pData = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_matrix_instance_f32_init(ml_arm_matrix_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pData=NULL;
char *kwlist[] = {
"numRows","numCols","pData",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hhO", kwlist,&self->instance->numRows
,&self->instance->numCols
,&pData
))
    {

    INITARRAYFIELD(pData,NPY_DOUBLE,double,float32_t);

    }
    return 0;
}

GETFIELD(arm_matrix_instance_f32,numRows,"h");
GETFIELD(arm_matrix_instance_f32,numCols,"h");


static PyMethodDef arm_matrix_instance_f32_methods[] = {

    {"numRows", (PyCFunction) Method_arm_matrix_instance_f32_numRows,METH_NOARGS,"numRows"},
    {"numCols", (PyCFunction) Method_arm_matrix_instance_f32_numCols,METH_NOARGS,"numCols"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_matrix_instance_f32,arm_matrix_instance_f32_new,arm_matrix_instance_f32_dealloc,arm_matrix_instance_f32_init,arm_matrix_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_matrix_instance_f64 *instance;
} ml_arm_matrix_instance_f64Object;


static void
arm_matrix_instance_f64_dealloc(ml_arm_matrix_instance_f64Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pData)
       {
          PyMem_Free(self->instance->pData);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_matrix_instance_f64_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_matrix_instance_f64Object *self;
    //printf("New called\n");

    self = (ml_arm_matrix_instance_f64Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_matrix_instance_f64));

        self->instance->pData = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_matrix_instance_f64_init(ml_arm_matrix_instance_f64Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pData=NULL;
char *kwlist[] = {
"numRows","numCols","pData",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hhO", kwlist,&self->instance->numRows
,&self->instance->numCols
,&pData
))
    {

    INITARRAYFIELD(pData,NPY_FLOAT64,float64_t,float64_t);

    }
    return 0;
}

GETFIELD(arm_matrix_instance_f64,numRows,"h");
GETFIELD(arm_matrix_instance_f64,numCols,"h");


static PyMethodDef arm_matrix_instance_f64_methods[] = {

    {"numRows", (PyCFunction) Method_arm_matrix_instance_f64_numRows,METH_NOARGS,"numRows"},
    {"numCols", (PyCFunction) Method_arm_matrix_instance_f64_numCols,METH_NOARGS,"numCols"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_matrix_instance_f64,arm_matrix_instance_f64_new,arm_matrix_instance_f64_dealloc,arm_matrix_instance_f64_init,arm_matrix_instance_f64_methods);


typedef struct {
    PyObject_HEAD
    arm_matrix_instance_q15 *instance;
} ml_arm_matrix_instance_q15Object;


static void
arm_matrix_instance_q15_dealloc(ml_arm_matrix_instance_q15Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pData)
       {
          PyMem_Free(self->instance->pData);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_matrix_instance_q15_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_matrix_instance_q15Object *self;
    //printf("New called\n");

    self = (ml_arm_matrix_instance_q15Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_matrix_instance_q15));

        self->instance->pData = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_matrix_instance_q15_init(ml_arm_matrix_instance_q15Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pData=NULL;
char *kwlist[] = {
"numRows","numCols","pData",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hhO", kwlist,&self->instance->numRows
,&self->instance->numCols
,&pData
))
    {

    INITARRAYFIELD(pData,NPY_INT16,int16_t,int16_t);

    }
    return 0;
}

GETFIELD(arm_matrix_instance_q15,numRows,"h");
GETFIELD(arm_matrix_instance_q15,numCols,"h");


static PyMethodDef arm_matrix_instance_q15_methods[] = {

    {"numRows", (PyCFunction) Method_arm_matrix_instance_q15_numRows,METH_NOARGS,"numRows"},
    {"numCols", (PyCFunction) Method_arm_matrix_instance_q15_numCols,METH_NOARGS,"numCols"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_matrix_instance_q15,arm_matrix_instance_q15_new,arm_matrix_instance_q15_dealloc,arm_matrix_instance_q15_init,arm_matrix_instance_q15_methods);


typedef struct {
    PyObject_HEAD
    arm_matrix_instance_q31 *instance;
} ml_arm_matrix_instance_q31Object;


static void
arm_matrix_instance_q31_dealloc(ml_arm_matrix_instance_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pData)
       {
          PyMem_Free(self->instance->pData);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_matrix_instance_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_matrix_instance_q31Object *self;
    //printf("New called\n");

    self = (ml_arm_matrix_instance_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_matrix_instance_q31));

        self->instance->pData = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_matrix_instance_q31_init(ml_arm_matrix_instance_q31Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pData=NULL;
char *kwlist[] = {
"numRows","numCols","pData",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hhO", kwlist,&self->instance->numRows
,&self->instance->numCols
,&pData
))
    {

    INITARRAYFIELD(pData,NPY_INT32,int32_t,int32_t);

    }
    return 0;
}

GETFIELD(arm_matrix_instance_q31,numRows,"h");
GETFIELD(arm_matrix_instance_q31,numCols,"h");


static PyMethodDef arm_matrix_instance_q31_methods[] = {

    {"numRows", (PyCFunction) Method_arm_matrix_instance_q31_numRows,METH_NOARGS,"numRows"},
    {"numCols", (PyCFunction) Method_arm_matrix_instance_q31_numCols,METH_NOARGS,"numCols"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_matrix_instance_q31,arm_matrix_instance_q31_new,arm_matrix_instance_q31_dealloc,arm_matrix_instance_q31_init,arm_matrix_instance_q31_methods);


typedef struct {
    PyObject_HEAD
    arm_pid_instance_q15 *instance;
} ml_arm_pid_instance_q15Object;


static void
arm_pid_instance_q15_dealloc(ml_arm_pid_instance_q15Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_pid_instance_q15_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_pid_instance_q15Object *self;
    //printf("New called\n");

    self = (ml_arm_pid_instance_q15Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_pid_instance_q15));


    }
 
   
    return (PyObject *)self;
}

static int
arm_pid_instance_q15_init(ml_arm_pid_instance_q15Object *self, PyObject *args, PyObject *kwds)
{

char *kwlist[] = {
"A0","A1","A2","state","Kp","Ki","Kd",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hhhhhhh", kwlist,&self->instance->A0
,&self->instance->A1
,&self->instance->A2
,&self->instance->state
,&self->instance->Kp
,&self->instance->Ki
,&self->instance->Kd
))
    {


    }
    return 0;
}

GETFIELD(arm_pid_instance_q15,A0,"h");
GETFIELD(arm_pid_instance_q15,A1,"h");
GETFIELD(arm_pid_instance_q15,A2,"h");
GETFIELD(arm_pid_instance_q15,state,"h");
GETFIELD(arm_pid_instance_q15,Kp,"h");
GETFIELD(arm_pid_instance_q15,Ki,"h");
GETFIELD(arm_pid_instance_q15,Kd,"h");


static PyMethodDef arm_pid_instance_q15_methods[] = {

    {"A0", (PyCFunction) Method_arm_pid_instance_q15_A0,METH_NOARGS,"A0"},
    {"A1", (PyCFunction) Method_arm_pid_instance_q15_A1,METH_NOARGS,"A1"},
    {"A2", (PyCFunction) Method_arm_pid_instance_q15_A2,METH_NOARGS,"A2"},
    {"state", (PyCFunction) Method_arm_pid_instance_q15_state,METH_NOARGS,"state"},
    {"Kp", (PyCFunction) Method_arm_pid_instance_q15_Kp,METH_NOARGS,"Kp"},
    {"Ki", (PyCFunction) Method_arm_pid_instance_q15_Ki,METH_NOARGS,"Ki"},
    {"Kd", (PyCFunction) Method_arm_pid_instance_q15_Kd,METH_NOARGS,"Kd"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_pid_instance_q15,arm_pid_instance_q15_new,arm_pid_instance_q15_dealloc,arm_pid_instance_q15_init,arm_pid_instance_q15_methods);


typedef struct {
    PyObject_HEAD
    arm_pid_instance_q31 *instance;
} ml_arm_pid_instance_q31Object;


static void
arm_pid_instance_q31_dealloc(ml_arm_pid_instance_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_pid_instance_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_pid_instance_q31Object *self;
    //printf("New called\n");

    self = (ml_arm_pid_instance_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_pid_instance_q31));


    }
 
   
    return (PyObject *)self;
}

static int
arm_pid_instance_q31_init(ml_arm_pid_instance_q31Object *self, PyObject *args, PyObject *kwds)
{

char *kwlist[] = {
"A0","A1","A2","state","Kp","Ki","Kd",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|iiiiiii", kwlist,&self->instance->A0
,&self->instance->A1
,&self->instance->A2
,&self->instance->state
,&self->instance->Kp
,&self->instance->Ki
,&self->instance->Kd
))
    {


    }
    return 0;
}

GETFIELD(arm_pid_instance_q31,A0,"i");
GETFIELD(arm_pid_instance_q31,A1,"i");
GETFIELD(arm_pid_instance_q31,A2,"i");
GETFIELD(arm_pid_instance_q31,state,"i");
GETFIELD(arm_pid_instance_q31,Kp,"i");
GETFIELD(arm_pid_instance_q31,Ki,"i");
GETFIELD(arm_pid_instance_q31,Kd,"i");


static PyMethodDef arm_pid_instance_q31_methods[] = {

    {"A0", (PyCFunction) Method_arm_pid_instance_q31_A0,METH_NOARGS,"A0"},
    {"A1", (PyCFunction) Method_arm_pid_instance_q31_A1,METH_NOARGS,"A1"},
    {"A2", (PyCFunction) Method_arm_pid_instance_q31_A2,METH_NOARGS,"A2"},
    {"state", (PyCFunction) Method_arm_pid_instance_q31_state,METH_NOARGS,"state"},
    {"Kp", (PyCFunction) Method_arm_pid_instance_q31_Kp,METH_NOARGS,"Kp"},
    {"Ki", (PyCFunction) Method_arm_pid_instance_q31_Ki,METH_NOARGS,"Ki"},
    {"Kd", (PyCFunction) Method_arm_pid_instance_q31_Kd,METH_NOARGS,"Kd"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_pid_instance_q31,arm_pid_instance_q31_new,arm_pid_instance_q31_dealloc,arm_pid_instance_q31_init,arm_pid_instance_q31_methods);


typedef struct {
    PyObject_HEAD
    arm_pid_instance_f32 *instance;
} ml_arm_pid_instance_f32Object;


static void
arm_pid_instance_f32_dealloc(ml_arm_pid_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_pid_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_pid_instance_f32Object *self;
    //printf("New called\n");

    self = (ml_arm_pid_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_pid_instance_f32));


    }
 
   
    return (PyObject *)self;
}

static int
arm_pid_instance_f32_init(ml_arm_pid_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

char *kwlist[] = {
"A0","A1","A2","state","Kp","Ki","Kd",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|fffffff", kwlist,&self->instance->A0
,&self->instance->A1
,&self->instance->A2
,&self->instance->state
,&self->instance->Kp
,&self->instance->Ki
,&self->instance->Kd
))
    {


    }
    return 0;
}

GETFIELD(arm_pid_instance_f32,A0,"f");
GETFIELD(arm_pid_instance_f32,A1,"f");
GETFIELD(arm_pid_instance_f32,A2,"f");
GETFIELD(arm_pid_instance_f32,state,"f");
GETFIELD(arm_pid_instance_f32,Kp,"f");
GETFIELD(arm_pid_instance_f32,Ki,"f");
GETFIELD(arm_pid_instance_f32,Kd,"f");


static PyMethodDef arm_pid_instance_f32_methods[] = {

    {"A0", (PyCFunction) Method_arm_pid_instance_f32_A0,METH_NOARGS,"A0"},
    {"A1", (PyCFunction) Method_arm_pid_instance_f32_A1,METH_NOARGS,"A1"},
    {"A2", (PyCFunction) Method_arm_pid_instance_f32_A2,METH_NOARGS,"A2"},
    {"state", (PyCFunction) Method_arm_pid_instance_f32_state,METH_NOARGS,"state"},
    {"Kp", (PyCFunction) Method_arm_pid_instance_f32_Kp,METH_NOARGS,"Kp"},
    {"Ki", (PyCFunction) Method_arm_pid_instance_f32_Ki,METH_NOARGS,"Ki"},
    {"Kd", (PyCFunction) Method_arm_pid_instance_f32_Kd,METH_NOARGS,"Kd"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_pid_instance_f32,arm_pid_instance_f32_new,arm_pid_instance_f32_dealloc,arm_pid_instance_f32_init,arm_pid_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_linear_interp_instance_f32 *instance;
} ml_arm_linear_interp_instance_f32Object;


static void
arm_linear_interp_instance_f32_dealloc(ml_arm_linear_interp_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pYData)
       {
          PyMem_Free(self->instance->pYData);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_linear_interp_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_linear_interp_instance_f32Object *self;
    //printf("New called\n");

    self = (ml_arm_linear_interp_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_linear_interp_instance_f32));

        self->instance->pYData = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_linear_interp_instance_f32_init(ml_arm_linear_interp_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pYData=NULL;
char *kwlist[] = {
"nValues","x1","xSpacing","pYData",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|iffO", kwlist,&self->instance->nValues
,&self->instance->x1
,&self->instance->xSpacing
,&pYData
))
    {

    INITARRAYFIELD(pYData,NPY_DOUBLE,double,float32_t);

    }
    return 0;
}

GETFIELD(arm_linear_interp_instance_f32,nValues,"i");
GETFIELD(arm_linear_interp_instance_f32,x1,"f");
GETFIELD(arm_linear_interp_instance_f32,xSpacing,"f");


static PyMethodDef arm_linear_interp_instance_f32_methods[] = {

    {"nValues", (PyCFunction) Method_arm_linear_interp_instance_f32_nValues,METH_NOARGS,"nValues"},
    {"x1", (PyCFunction) Method_arm_linear_interp_instance_f32_x1,METH_NOARGS,"x1"},
    {"xSpacing", (PyCFunction) Method_arm_linear_interp_instance_f32_xSpacing,METH_NOARGS,"xSpacing"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_linear_interp_instance_f32,arm_linear_interp_instance_f32_new,arm_linear_interp_instance_f32_dealloc,arm_linear_interp_instance_f32_init,arm_linear_interp_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_bilinear_interp_instance_f32 *instance;
} ml_arm_bilinear_interp_instance_f32Object;


static void
arm_bilinear_interp_instance_f32_dealloc(ml_arm_bilinear_interp_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pData)
       {
          PyMem_Free(self->instance->pData);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_bilinear_interp_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_bilinear_interp_instance_f32Object *self;
    //printf("New called\n");

    self = (ml_arm_bilinear_interp_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_bilinear_interp_instance_f32));

        self->instance->pData = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_bilinear_interp_instance_f32_init(ml_arm_bilinear_interp_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pData=NULL;
char *kwlist[] = {
"numRows","numCols","pData",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hhO", kwlist,&self->instance->numRows
,&self->instance->numCols
,&pData
))
    {

    INITARRAYFIELD(pData,NPY_DOUBLE,double,float32_t);

    }
    return 0;
}

GETFIELD(arm_bilinear_interp_instance_f32,numRows,"h");
GETFIELD(arm_bilinear_interp_instance_f32,numCols,"h");


static PyMethodDef arm_bilinear_interp_instance_f32_methods[] = {

    {"numRows", (PyCFunction) Method_arm_bilinear_interp_instance_f32_numRows,METH_NOARGS,"numRows"},
    {"numCols", (PyCFunction) Method_arm_bilinear_interp_instance_f32_numCols,METH_NOARGS,"numCols"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_bilinear_interp_instance_f32,arm_bilinear_interp_instance_f32_new,arm_bilinear_interp_instance_f32_dealloc,arm_bilinear_interp_instance_f32_init,arm_bilinear_interp_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_bilinear_interp_instance_q31 *instance;
} ml_arm_bilinear_interp_instance_q31Object;


static void
arm_bilinear_interp_instance_q31_dealloc(ml_arm_bilinear_interp_instance_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pData)
       {
          PyMem_Free(self->instance->pData);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_bilinear_interp_instance_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_bilinear_interp_instance_q31Object *self;
    //printf("New called\n");

    self = (ml_arm_bilinear_interp_instance_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_bilinear_interp_instance_q31));

        self->instance->pData = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_bilinear_interp_instance_q31_init(ml_arm_bilinear_interp_instance_q31Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pData=NULL;
char *kwlist[] = {
"numRows","numCols","pData",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hhO", kwlist,&self->instance->numRows
,&self->instance->numCols
,&pData
))
    {

    INITARRAYFIELD(pData,NPY_INT32,int32_t,int32_t);

    }
    return 0;
}

GETFIELD(arm_bilinear_interp_instance_q31,numRows,"h");
GETFIELD(arm_bilinear_interp_instance_q31,numCols,"h");


static PyMethodDef arm_bilinear_interp_instance_q31_methods[] = {

    {"numRows", (PyCFunction) Method_arm_bilinear_interp_instance_q31_numRows,METH_NOARGS,"numRows"},
    {"numCols", (PyCFunction) Method_arm_bilinear_interp_instance_q31_numCols,METH_NOARGS,"numCols"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_bilinear_interp_instance_q31,arm_bilinear_interp_instance_q31_new,arm_bilinear_interp_instance_q31_dealloc,arm_bilinear_interp_instance_q31_init,arm_bilinear_interp_instance_q31_methods);


typedef struct {
    PyObject_HEAD
    arm_bilinear_interp_instance_q15 *instance;
} ml_arm_bilinear_interp_instance_q15Object;


static void
arm_bilinear_interp_instance_q15_dealloc(ml_arm_bilinear_interp_instance_q15Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pData)
       {
          PyMem_Free(self->instance->pData);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_bilinear_interp_instance_q15_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_bilinear_interp_instance_q15Object *self;
    //printf("New called\n");

    self = (ml_arm_bilinear_interp_instance_q15Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_bilinear_interp_instance_q15));

        self->instance->pData = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_bilinear_interp_instance_q15_init(ml_arm_bilinear_interp_instance_q15Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pData=NULL;
char *kwlist[] = {
"numRows","numCols","pData",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hhO", kwlist,&self->instance->numRows
,&self->instance->numCols
,&pData
))
    {

    INITARRAYFIELD(pData,NPY_INT16,int16_t,int16_t);

    }
    return 0;
}

GETFIELD(arm_bilinear_interp_instance_q15,numRows,"h");
GETFIELD(arm_bilinear_interp_instance_q15,numCols,"h");


static PyMethodDef arm_bilinear_interp_instance_q15_methods[] = {

    {"numRows", (PyCFunction) Method_arm_bilinear_interp_instance_q15_numRows,METH_NOARGS,"numRows"},
    {"numCols", (PyCFunction) Method_arm_bilinear_interp_instance_q15_numCols,METH_NOARGS,"numCols"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_bilinear_interp_instance_q15,arm_bilinear_interp_instance_q15_new,arm_bilinear_interp_instance_q15_dealloc,arm_bilinear_interp_instance_q15_init,arm_bilinear_interp_instance_q15_methods);


typedef struct {
    PyObject_HEAD
    arm_bilinear_interp_instance_q7 *instance;
} ml_arm_bilinear_interp_instance_q7Object;


static void
arm_bilinear_interp_instance_q7_dealloc(ml_arm_bilinear_interp_instance_q7Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pData)
       {
          PyMem_Free(self->instance->pData);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_bilinear_interp_instance_q7_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_bilinear_interp_instance_q7Object *self;
    //printf("New called\n");

    self = (ml_arm_bilinear_interp_instance_q7Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_bilinear_interp_instance_q7));

        self->instance->pData = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_bilinear_interp_instance_q7_init(ml_arm_bilinear_interp_instance_q7Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pData=NULL;
char *kwlist[] = {
"numRows","numCols","pData",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hhO", kwlist,&self->instance->numRows
,&self->instance->numCols
,&pData
))
    {

    INITARRAYFIELD(pData,NPY_BYTE,int8_t,q7_t);

    }
    return 0;
}

GETFIELD(arm_bilinear_interp_instance_q7,numRows,"h");
GETFIELD(arm_bilinear_interp_instance_q7,numCols,"h");


static PyMethodDef arm_bilinear_interp_instance_q7_methods[] = {

    {"numRows", (PyCFunction) Method_arm_bilinear_interp_instance_q7_numRows,METH_NOARGS,"numRows"},
    {"numCols", (PyCFunction) Method_arm_bilinear_interp_instance_q7_numCols,METH_NOARGS,"numCols"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_bilinear_interp_instance_q7,arm_bilinear_interp_instance_q7_new,arm_bilinear_interp_instance_q7_dealloc,arm_bilinear_interp_instance_q7_init,arm_bilinear_interp_instance_q7_methods);


typedef struct {
    PyObject_HEAD
    arm_cfft_radix2_instance_q15 *instance;
} ml_arm_cfft_radix2_instance_q15Object;


static void
arm_cfft_radix2_instance_q15_dealloc(ml_arm_cfft_radix2_instance_q15Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_cfft_radix2_instance_q15_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_cfft_radix2_instance_q15Object *self;
    //printf("New called\n");

    self = (ml_arm_cfft_radix2_instance_q15Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_cfft_radix2_instance_q15));

        self->instance->pTwiddle = NULL;
        self->instance->pBitRevTable = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_cfft_radix2_instance_q15_init(ml_arm_cfft_radix2_instance_q15Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddle=NULL;
    PyObject *pBitRevTable=NULL;
char *kwlist[] = {
"fftLen","ifftFlag","bitReverseFlag","twidCoefModifier","bitRevFactor",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hiihh", kwlist,&self->instance->fftLen
,&self->instance->ifftFlag
,&self->instance->bitReverseFlag
,&self->instance->twidCoefModifier
,&self->instance->bitRevFactor
))
    {


    }
    return 0;
}

GETFIELD(arm_cfft_radix2_instance_q15,fftLen,"h");
GETFIELD(arm_cfft_radix2_instance_q15,ifftFlag,"i");
GETFIELD(arm_cfft_radix2_instance_q15,bitReverseFlag,"i");
GETFIELD(arm_cfft_radix2_instance_q15,twidCoefModifier,"h");
GETFIELD(arm_cfft_radix2_instance_q15,bitRevFactor,"h");


static PyMethodDef arm_cfft_radix2_instance_q15_methods[] = {

    {"fftLen", (PyCFunction) Method_arm_cfft_radix2_instance_q15_fftLen,METH_NOARGS,"fftLen"},
    {"ifftFlag", (PyCFunction) Method_arm_cfft_radix2_instance_q15_ifftFlag,METH_NOARGS,"ifftFlag"},
    {"bitReverseFlag", (PyCFunction) Method_arm_cfft_radix2_instance_q15_bitReverseFlag,METH_NOARGS,"bitReverseFlag"},
    {"twidCoefModifier", (PyCFunction) Method_arm_cfft_radix2_instance_q15_twidCoefModifier,METH_NOARGS,"twidCoefModifier"},
    {"bitRevFactor", (PyCFunction) Method_arm_cfft_radix2_instance_q15_bitRevFactor,METH_NOARGS,"bitRevFactor"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_cfft_radix2_instance_q15,arm_cfft_radix2_instance_q15_new,arm_cfft_radix2_instance_q15_dealloc,arm_cfft_radix2_instance_q15_init,arm_cfft_radix2_instance_q15_methods);


typedef struct {
    PyObject_HEAD
    arm_cfft_radix4_instance_q15 *instance;
} ml_arm_cfft_radix4_instance_q15Object;


static void
arm_cfft_radix4_instance_q15_dealloc(ml_arm_cfft_radix4_instance_q15Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_cfft_radix4_instance_q15_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_cfft_radix4_instance_q15Object *self;
    //printf("New called\n");

    self = (ml_arm_cfft_radix4_instance_q15Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_cfft_radix4_instance_q15));

        self->instance->pTwiddle = NULL;
        self->instance->pBitRevTable = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_cfft_radix4_instance_q15_init(ml_arm_cfft_radix4_instance_q15Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddle=NULL;
    PyObject *pBitRevTable=NULL;
char *kwlist[] = {
"fftLen","ifftFlag","bitReverseFlag","twidCoefModifier","bitRevFactor",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hiihh", kwlist,&self->instance->fftLen
,&self->instance->ifftFlag
,&self->instance->bitReverseFlag
,&self->instance->twidCoefModifier
,&self->instance->bitRevFactor
))
    {


    }
    return 0;
}

GETFIELD(arm_cfft_radix4_instance_q15,fftLen,"h");
GETFIELD(arm_cfft_radix4_instance_q15,ifftFlag,"i");
GETFIELD(arm_cfft_radix4_instance_q15,bitReverseFlag,"i");
GETFIELD(arm_cfft_radix4_instance_q15,twidCoefModifier,"h");
GETFIELD(arm_cfft_radix4_instance_q15,bitRevFactor,"h");


static PyMethodDef arm_cfft_radix4_instance_q15_methods[] = {

    {"fftLen", (PyCFunction) Method_arm_cfft_radix4_instance_q15_fftLen,METH_NOARGS,"fftLen"},
    {"ifftFlag", (PyCFunction) Method_arm_cfft_radix4_instance_q15_ifftFlag,METH_NOARGS,"ifftFlag"},
    {"bitReverseFlag", (PyCFunction) Method_arm_cfft_radix4_instance_q15_bitReverseFlag,METH_NOARGS,"bitReverseFlag"},
    {"twidCoefModifier", (PyCFunction) Method_arm_cfft_radix4_instance_q15_twidCoefModifier,METH_NOARGS,"twidCoefModifier"},
    {"bitRevFactor", (PyCFunction) Method_arm_cfft_radix4_instance_q15_bitRevFactor,METH_NOARGS,"bitRevFactor"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_cfft_radix4_instance_q15,arm_cfft_radix4_instance_q15_new,arm_cfft_radix4_instance_q15_dealloc,arm_cfft_radix4_instance_q15_init,arm_cfft_radix4_instance_q15_methods);


typedef struct {
    PyObject_HEAD
    arm_cfft_radix2_instance_q31 *instance;
} ml_arm_cfft_radix2_instance_q31Object;


static void
arm_cfft_radix2_instance_q31_dealloc(ml_arm_cfft_radix2_instance_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_cfft_radix2_instance_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_cfft_radix2_instance_q31Object *self;
    //printf("New called\n");

    self = (ml_arm_cfft_radix2_instance_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_cfft_radix2_instance_q31));

        self->instance->pTwiddle = NULL;
        self->instance->pBitRevTable = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_cfft_radix2_instance_q31_init(ml_arm_cfft_radix2_instance_q31Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddle=NULL;
    PyObject *pBitRevTable=NULL;
char *kwlist[] = {
"fftLen","ifftFlag","bitReverseFlag","twidCoefModifier","bitRevFactor",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hiihh", kwlist,&self->instance->fftLen
,&self->instance->ifftFlag
,&self->instance->bitReverseFlag
,&self->instance->twidCoefModifier
,&self->instance->bitRevFactor
))
    {


    }
    return 0;
}

GETFIELD(arm_cfft_radix2_instance_q31,fftLen,"h");
GETFIELD(arm_cfft_radix2_instance_q31,ifftFlag,"i");
GETFIELD(arm_cfft_radix2_instance_q31,bitReverseFlag,"i");
GETFIELD(arm_cfft_radix2_instance_q31,twidCoefModifier,"h");
GETFIELD(arm_cfft_radix2_instance_q31,bitRevFactor,"h");


static PyMethodDef arm_cfft_radix2_instance_q31_methods[] = {

    {"fftLen", (PyCFunction) Method_arm_cfft_radix2_instance_q31_fftLen,METH_NOARGS,"fftLen"},
    {"ifftFlag", (PyCFunction) Method_arm_cfft_radix2_instance_q31_ifftFlag,METH_NOARGS,"ifftFlag"},
    {"bitReverseFlag", (PyCFunction) Method_arm_cfft_radix2_instance_q31_bitReverseFlag,METH_NOARGS,"bitReverseFlag"},
    {"twidCoefModifier", (PyCFunction) Method_arm_cfft_radix2_instance_q31_twidCoefModifier,METH_NOARGS,"twidCoefModifier"},
    {"bitRevFactor", (PyCFunction) Method_arm_cfft_radix2_instance_q31_bitRevFactor,METH_NOARGS,"bitRevFactor"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_cfft_radix2_instance_q31,arm_cfft_radix2_instance_q31_new,arm_cfft_radix2_instance_q31_dealloc,arm_cfft_radix2_instance_q31_init,arm_cfft_radix2_instance_q31_methods);


typedef struct {
    PyObject_HEAD
    arm_cfft_radix4_instance_q31 *instance;
} ml_arm_cfft_radix4_instance_q31Object;


static void
arm_cfft_radix4_instance_q31_dealloc(ml_arm_cfft_radix4_instance_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_cfft_radix4_instance_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_cfft_radix4_instance_q31Object *self;
    //printf("New called\n");

    self = (ml_arm_cfft_radix4_instance_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_cfft_radix4_instance_q31));

        self->instance->pTwiddle = NULL;
        self->instance->pBitRevTable = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_cfft_radix4_instance_q31_init(ml_arm_cfft_radix4_instance_q31Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddle=NULL;
    PyObject *pBitRevTable=NULL;
char *kwlist[] = {
"fftLen","ifftFlag","bitReverseFlag","twidCoefModifier","bitRevFactor",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hiihh", kwlist,&self->instance->fftLen
,&self->instance->ifftFlag
,&self->instance->bitReverseFlag
,&self->instance->twidCoefModifier
,&self->instance->bitRevFactor
))
    {


    }
    return 0;
}

GETFIELD(arm_cfft_radix4_instance_q31,fftLen,"h");
GETFIELD(arm_cfft_radix4_instance_q31,ifftFlag,"i");
GETFIELD(arm_cfft_radix4_instance_q31,bitReverseFlag,"i");
GETFIELD(arm_cfft_radix4_instance_q31,twidCoefModifier,"h");
GETFIELD(arm_cfft_radix4_instance_q31,bitRevFactor,"h");


static PyMethodDef arm_cfft_radix4_instance_q31_methods[] = {

    {"fftLen", (PyCFunction) Method_arm_cfft_radix4_instance_q31_fftLen,METH_NOARGS,"fftLen"},
    {"ifftFlag", (PyCFunction) Method_arm_cfft_radix4_instance_q31_ifftFlag,METH_NOARGS,"ifftFlag"},
    {"bitReverseFlag", (PyCFunction) Method_arm_cfft_radix4_instance_q31_bitReverseFlag,METH_NOARGS,"bitReverseFlag"},
    {"twidCoefModifier", (PyCFunction) Method_arm_cfft_radix4_instance_q31_twidCoefModifier,METH_NOARGS,"twidCoefModifier"},
    {"bitRevFactor", (PyCFunction) Method_arm_cfft_radix4_instance_q31_bitRevFactor,METH_NOARGS,"bitRevFactor"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_cfft_radix4_instance_q31,arm_cfft_radix4_instance_q31_new,arm_cfft_radix4_instance_q31_dealloc,arm_cfft_radix4_instance_q31_init,arm_cfft_radix4_instance_q31_methods);


typedef struct {
    PyObject_HEAD
    arm_cfft_radix2_instance_f32 *instance;
} ml_arm_cfft_radix2_instance_f32Object;


static void
arm_cfft_radix2_instance_f32_dealloc(ml_arm_cfft_radix2_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_cfft_radix2_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_cfft_radix2_instance_f32Object *self;
    //printf("New called\n");

    self = (ml_arm_cfft_radix2_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_cfft_radix2_instance_f32));

        self->instance->pTwiddle = NULL;
        self->instance->pBitRevTable = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_cfft_radix2_instance_f32_init(ml_arm_cfft_radix2_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddle=NULL;
    PyObject *pBitRevTable=NULL;
char *kwlist[] = {
"fftLen","ifftFlag","bitReverseFlag","twidCoefModifier","bitRevFactor","onebyfftLen",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hiihhf", kwlist,&self->instance->fftLen
,&self->instance->ifftFlag
,&self->instance->bitReverseFlag
,&self->instance->twidCoefModifier
,&self->instance->bitRevFactor
,&self->instance->onebyfftLen
))
    {


    }
    return 0;
}

GETFIELD(arm_cfft_radix2_instance_f32,fftLen,"h");
GETFIELD(arm_cfft_radix2_instance_f32,ifftFlag,"i");
GETFIELD(arm_cfft_radix2_instance_f32,bitReverseFlag,"i");
GETFIELD(arm_cfft_radix2_instance_f32,twidCoefModifier,"h");
GETFIELD(arm_cfft_radix2_instance_f32,bitRevFactor,"h");
GETFIELD(arm_cfft_radix2_instance_f32,onebyfftLen,"f");


static PyMethodDef arm_cfft_radix2_instance_f32_methods[] = {

    {"fftLen", (PyCFunction) Method_arm_cfft_radix2_instance_f32_fftLen,METH_NOARGS,"fftLen"},
    {"ifftFlag", (PyCFunction) Method_arm_cfft_radix2_instance_f32_ifftFlag,METH_NOARGS,"ifftFlag"},
    {"bitReverseFlag", (PyCFunction) Method_arm_cfft_radix2_instance_f32_bitReverseFlag,METH_NOARGS,"bitReverseFlag"},
    {"twidCoefModifier", (PyCFunction) Method_arm_cfft_radix2_instance_f32_twidCoefModifier,METH_NOARGS,"twidCoefModifier"},
    {"bitRevFactor", (PyCFunction) Method_arm_cfft_radix2_instance_f32_bitRevFactor,METH_NOARGS,"bitRevFactor"},
    {"onebyfftLen", (PyCFunction) Method_arm_cfft_radix2_instance_f32_onebyfftLen,METH_NOARGS,"onebyfftLen"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_cfft_radix2_instance_f32,arm_cfft_radix2_instance_f32_new,arm_cfft_radix2_instance_f32_dealloc,arm_cfft_radix2_instance_f32_init,arm_cfft_radix2_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_cfft_radix4_instance_f32 *instance;
} ml_arm_cfft_radix4_instance_f32Object;


static void
arm_cfft_radix4_instance_f32_dealloc(ml_arm_cfft_radix4_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_cfft_radix4_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_cfft_radix4_instance_f32Object *self;
    //printf("New called\n");

    self = (ml_arm_cfft_radix4_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_cfft_radix4_instance_f32));

        self->instance->pTwiddle = NULL;
        self->instance->pBitRevTable = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_cfft_radix4_instance_f32_init(ml_arm_cfft_radix4_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddle=NULL;
    PyObject *pBitRevTable=NULL;
char *kwlist[] = {
"fftLen","ifftFlag","bitReverseFlag","twidCoefModifier","bitRevFactor","onebyfftLen",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hiihhf", kwlist,&self->instance->fftLen
,&self->instance->ifftFlag
,&self->instance->bitReverseFlag
,&self->instance->twidCoefModifier
,&self->instance->bitRevFactor
,&self->instance->onebyfftLen
))
    {


    }
    return 0;
}

GETFIELD(arm_cfft_radix4_instance_f32,fftLen,"h");
GETFIELD(arm_cfft_radix4_instance_f32,ifftFlag,"i");
GETFIELD(arm_cfft_radix4_instance_f32,bitReverseFlag,"i");
GETFIELD(arm_cfft_radix4_instance_f32,twidCoefModifier,"h");
GETFIELD(arm_cfft_radix4_instance_f32,bitRevFactor,"h");
GETFIELD(arm_cfft_radix4_instance_f32,onebyfftLen,"f");


static PyMethodDef arm_cfft_radix4_instance_f32_methods[] = {

    {"fftLen", (PyCFunction) Method_arm_cfft_radix4_instance_f32_fftLen,METH_NOARGS,"fftLen"},
    {"ifftFlag", (PyCFunction) Method_arm_cfft_radix4_instance_f32_ifftFlag,METH_NOARGS,"ifftFlag"},
    {"bitReverseFlag", (PyCFunction) Method_arm_cfft_radix4_instance_f32_bitReverseFlag,METH_NOARGS,"bitReverseFlag"},
    {"twidCoefModifier", (PyCFunction) Method_arm_cfft_radix4_instance_f32_twidCoefModifier,METH_NOARGS,"twidCoefModifier"},
    {"bitRevFactor", (PyCFunction) Method_arm_cfft_radix4_instance_f32_bitRevFactor,METH_NOARGS,"bitRevFactor"},
    {"onebyfftLen", (PyCFunction) Method_arm_cfft_radix4_instance_f32_onebyfftLen,METH_NOARGS,"onebyfftLen"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_cfft_radix4_instance_f32,arm_cfft_radix4_instance_f32_new,arm_cfft_radix4_instance_f32_dealloc,arm_cfft_radix4_instance_f32_init,arm_cfft_radix4_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_cfft_instance_q15 *instance;
} ml_arm_cfft_instance_q15Object;


static void
arm_cfft_instance_q15_dealloc(ml_arm_cfft_instance_q15Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_cfft_instance_q15_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_cfft_instance_q15Object *self;
    //printf("New called\n");

    self = (ml_arm_cfft_instance_q15Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_cfft_instance_q15));

        self->instance->pTwiddle = NULL;
        self->instance->pBitRevTable = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_cfft_instance_q15_init(ml_arm_cfft_instance_q15Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddle=NULL;
    PyObject *pBitRevTable=NULL;
char *kwlist[] = {
"fftLen","bitRevLength",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hh", kwlist,&self->instance->fftLen
,&self->instance->bitRevLength
))
    {


    }
    return 0;
}

GETFIELD(arm_cfft_instance_q15,fftLen,"h");
GETFIELD(arm_cfft_instance_q15,bitRevLength,"h");


static PyMethodDef arm_cfft_instance_q15_methods[] = {

    {"fftLen", (PyCFunction) Method_arm_cfft_instance_q15_fftLen,METH_NOARGS,"fftLen"},
    {"bitRevLength", (PyCFunction) Method_arm_cfft_instance_q15_bitRevLength,METH_NOARGS,"bitRevLength"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_cfft_instance_q15,arm_cfft_instance_q15_new,arm_cfft_instance_q15_dealloc,arm_cfft_instance_q15_init,arm_cfft_instance_q15_methods);


typedef struct {
    PyObject_HEAD
    arm_cfft_instance_q31 *instance;
} ml_arm_cfft_instance_q31Object;


static void
arm_cfft_instance_q31_dealloc(ml_arm_cfft_instance_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_cfft_instance_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_cfft_instance_q31Object *self;
    //printf("New called\n");

    self = (ml_arm_cfft_instance_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_cfft_instance_q31));

        self->instance->pTwiddle = NULL;
        self->instance->pBitRevTable = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_cfft_instance_q31_init(ml_arm_cfft_instance_q31Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddle=NULL;
    PyObject *pBitRevTable=NULL;
char *kwlist[] = {
"fftLen","bitRevLength",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hh", kwlist,&self->instance->fftLen
,&self->instance->bitRevLength
))
    {


    }
    return 0;
}

GETFIELD(arm_cfft_instance_q31,fftLen,"h");
GETFIELD(arm_cfft_instance_q31,bitRevLength,"h");


static PyMethodDef arm_cfft_instance_q31_methods[] = {

    {"fftLen", (PyCFunction) Method_arm_cfft_instance_q31_fftLen,METH_NOARGS,"fftLen"},
    {"bitRevLength", (PyCFunction) Method_arm_cfft_instance_q31_bitRevLength,METH_NOARGS,"bitRevLength"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_cfft_instance_q31,arm_cfft_instance_q31_new,arm_cfft_instance_q31_dealloc,arm_cfft_instance_q31_init,arm_cfft_instance_q31_methods);


typedef struct {
    PyObject_HEAD
    arm_cfft_instance_f32 *instance;
} ml_arm_cfft_instance_f32Object;


static void
arm_cfft_instance_f32_dealloc(ml_arm_cfft_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_cfft_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_cfft_instance_f32Object *self;
    //printf("New called\n");

    self = (ml_arm_cfft_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_cfft_instance_f32));

        self->instance->pTwiddle = NULL;
        self->instance->pBitRevTable = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_cfft_instance_f32_init(ml_arm_cfft_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddle=NULL;
    PyObject *pBitRevTable=NULL;
char *kwlist[] = {
"fftLen","bitRevLength",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hh", kwlist,&self->instance->fftLen
,&self->instance->bitRevLength
))
    {


    }
    return 0;
}

GETFIELD(arm_cfft_instance_f32,fftLen,"h");
GETFIELD(arm_cfft_instance_f32,bitRevLength,"h");


static PyMethodDef arm_cfft_instance_f32_methods[] = {

    {"fftLen", (PyCFunction) Method_arm_cfft_instance_f32_fftLen,METH_NOARGS,"fftLen"},
    {"bitRevLength", (PyCFunction) Method_arm_cfft_instance_f32_bitRevLength,METH_NOARGS,"bitRevLength"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_cfft_instance_f32,arm_cfft_instance_f32_new,arm_cfft_instance_f32_dealloc,arm_cfft_instance_f32_init,arm_cfft_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_rfft_instance_q15 *instance;
} ml_arm_rfft_instance_q15Object;


static void
arm_rfft_instance_q15_dealloc(ml_arm_rfft_instance_q15Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_rfft_instance_q15_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_rfft_instance_q15Object *self;
    //printf("New called\n");

    self = (ml_arm_rfft_instance_q15Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_rfft_instance_q15));

        self->instance->pTwiddleAReal = NULL;
        self->instance->pTwiddleBReal = NULL;
        self->instance->pCfft = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_rfft_instance_q15_init(ml_arm_rfft_instance_q15Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddleAReal=NULL;
    PyObject *pTwiddleBReal=NULL;
    PyObject *pCfft=NULL;
char *kwlist[] = {
"fftLenReal","ifftFlagR","bitReverseFlagR","twidCoefRModifier",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|iiii", kwlist,&self->instance->fftLenReal
,&self->instance->ifftFlagR
,&self->instance->bitReverseFlagR
,&self->instance->twidCoefRModifier
))
    {


    }
    return 0;
}

GETFIELD(arm_rfft_instance_q15,fftLenReal,"i");
GETFIELD(arm_rfft_instance_q15,ifftFlagR,"i");
GETFIELD(arm_rfft_instance_q15,bitReverseFlagR,"i");
GETFIELD(arm_rfft_instance_q15,twidCoefRModifier,"i");


static PyMethodDef arm_rfft_instance_q15_methods[] = {

    {"fftLenReal", (PyCFunction) Method_arm_rfft_instance_q15_fftLenReal,METH_NOARGS,"fftLenReal"},
    {"ifftFlagR", (PyCFunction) Method_arm_rfft_instance_q15_ifftFlagR,METH_NOARGS,"ifftFlagR"},
    {"bitReverseFlagR", (PyCFunction) Method_arm_rfft_instance_q15_bitReverseFlagR,METH_NOARGS,"bitReverseFlagR"},
    {"twidCoefRModifier", (PyCFunction) Method_arm_rfft_instance_q15_twidCoefRModifier,METH_NOARGS,"twidCoefRModifier"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_rfft_instance_q15,arm_rfft_instance_q15_new,arm_rfft_instance_q15_dealloc,arm_rfft_instance_q15_init,arm_rfft_instance_q15_methods);


typedef struct {
    PyObject_HEAD
    arm_rfft_instance_q31 *instance;
} ml_arm_rfft_instance_q31Object;


static void
arm_rfft_instance_q31_dealloc(ml_arm_rfft_instance_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_rfft_instance_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_rfft_instance_q31Object *self;
    //printf("New called\n");

    self = (ml_arm_rfft_instance_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_rfft_instance_q31));

        self->instance->pTwiddleAReal = NULL;
        self->instance->pTwiddleBReal = NULL;
        self->instance->pCfft = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_rfft_instance_q31_init(ml_arm_rfft_instance_q31Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddleAReal=NULL;
    PyObject *pTwiddleBReal=NULL;
    PyObject *pCfft=NULL;
char *kwlist[] = {
"fftLenReal","ifftFlagR","bitReverseFlagR","twidCoefRModifier",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|iiii", kwlist,&self->instance->fftLenReal
,&self->instance->ifftFlagR
,&self->instance->bitReverseFlagR
,&self->instance->twidCoefRModifier
))
    {


    }
    return 0;
}

GETFIELD(arm_rfft_instance_q31,fftLenReal,"i");
GETFIELD(arm_rfft_instance_q31,ifftFlagR,"i");
GETFIELD(arm_rfft_instance_q31,bitReverseFlagR,"i");
GETFIELD(arm_rfft_instance_q31,twidCoefRModifier,"i");


static PyMethodDef arm_rfft_instance_q31_methods[] = {

    {"fftLenReal", (PyCFunction) Method_arm_rfft_instance_q31_fftLenReal,METH_NOARGS,"fftLenReal"},
    {"ifftFlagR", (PyCFunction) Method_arm_rfft_instance_q31_ifftFlagR,METH_NOARGS,"ifftFlagR"},
    {"bitReverseFlagR", (PyCFunction) Method_arm_rfft_instance_q31_bitReverseFlagR,METH_NOARGS,"bitReverseFlagR"},
    {"twidCoefRModifier", (PyCFunction) Method_arm_rfft_instance_q31_twidCoefRModifier,METH_NOARGS,"twidCoefRModifier"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_rfft_instance_q31,arm_rfft_instance_q31_new,arm_rfft_instance_q31_dealloc,arm_rfft_instance_q31_init,arm_rfft_instance_q31_methods);


typedef struct {
    PyObject_HEAD
    arm_rfft_instance_f32 *instance;
} ml_arm_rfft_instance_f32Object;


static void
arm_rfft_instance_f32_dealloc(ml_arm_rfft_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_rfft_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_rfft_instance_f32Object *self;
    //printf("New called\n");

    self = (ml_arm_rfft_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_rfft_instance_f32));

        self->instance->pTwiddleAReal = NULL;
        self->instance->pTwiddleBReal = NULL;
        self->instance->pCfft = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_rfft_instance_f32_init(ml_arm_rfft_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddleAReal=NULL;
    PyObject *pTwiddleBReal=NULL;
    PyObject *pCfft=NULL;
char *kwlist[] = {
"fftLenReal","fftLenBy2","ifftFlagR","bitReverseFlagR","twidCoefRModifier",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|ihiii", kwlist,&self->instance->fftLenReal
,&self->instance->fftLenBy2
,&self->instance->ifftFlagR
,&self->instance->bitReverseFlagR
,&self->instance->twidCoefRModifier
))
    {


    }
    return 0;
}

GETFIELD(arm_rfft_instance_f32,fftLenReal,"i");
GETFIELD(arm_rfft_instance_f32,fftLenBy2,"h");
GETFIELD(arm_rfft_instance_f32,ifftFlagR,"i");
GETFIELD(arm_rfft_instance_f32,bitReverseFlagR,"i");
GETFIELD(arm_rfft_instance_f32,twidCoefRModifier,"i");


static PyMethodDef arm_rfft_instance_f32_methods[] = {

    {"fftLenReal", (PyCFunction) Method_arm_rfft_instance_f32_fftLenReal,METH_NOARGS,"fftLenReal"},
    {"fftLenBy2", (PyCFunction) Method_arm_rfft_instance_f32_fftLenBy2,METH_NOARGS,"fftLenBy2"},
    {"ifftFlagR", (PyCFunction) Method_arm_rfft_instance_f32_ifftFlagR,METH_NOARGS,"ifftFlagR"},
    {"bitReverseFlagR", (PyCFunction) Method_arm_rfft_instance_f32_bitReverseFlagR,METH_NOARGS,"bitReverseFlagR"},
    {"twidCoefRModifier", (PyCFunction) Method_arm_rfft_instance_f32_twidCoefRModifier,METH_NOARGS,"twidCoefRModifier"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_rfft_instance_f32,arm_rfft_instance_f32_new,arm_rfft_instance_f32_dealloc,arm_rfft_instance_f32_init,arm_rfft_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_rfft_fast_instance_f32 *instance;
} ml_arm_rfft_fast_instance_f32Object;


static void
arm_rfft_fast_instance_f32_dealloc(ml_arm_rfft_fast_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_rfft_fast_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_rfft_fast_instance_f32Object *self;
    //printf("New called\n");

    self = (ml_arm_rfft_fast_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_rfft_fast_instance_f32));

        self->instance->pTwiddleRFFT = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_rfft_fast_instance_f32_init(ml_arm_rfft_fast_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddleRFFT=NULL;
char *kwlist[] = {
"Sint","fftLenRFFT",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|?h", kwlist,&self->instance->Sint
,&self->instance->fftLenRFFT
))
    {


    }
    return 0;
}

GETFIELD(arm_rfft_fast_instance_f32,Sint,"?");
GETFIELD(arm_rfft_fast_instance_f32,fftLenRFFT,"h");


static PyMethodDef arm_rfft_fast_instance_f32_methods[] = {

    {"Sint", (PyCFunction) Method_arm_rfft_fast_instance_f32_Sint,METH_NOARGS,"Sint"},
    {"fftLenRFFT", (PyCFunction) Method_arm_rfft_fast_instance_f32_fftLenRFFT,METH_NOARGS,"fftLenRFFT"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_rfft_fast_instance_f32,arm_rfft_fast_instance_f32_new,arm_rfft_fast_instance_f32_dealloc,arm_rfft_fast_instance_f32_init,arm_rfft_fast_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_dct4_instance_f32 *instance;
} ml_arm_dct4_instance_f32Object;


static void
arm_dct4_instance_f32_dealloc(ml_arm_dct4_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_dct4_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_dct4_instance_f32Object *self;
    //printf("New called\n");

    self = (ml_arm_dct4_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_dct4_instance_f32));

        self->instance->pTwiddle = NULL;
        self->instance->pCosFactor = NULL;
        self->instance->pRfft = NULL;
        self->instance->pCfft = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_dct4_instance_f32_init(ml_arm_dct4_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddle=NULL;
    PyObject *pCosFactor=NULL;
    PyObject *pRfft=NULL;
    PyObject *pCfft=NULL;
char *kwlist[] = {
"N","Nby2","normalize",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hhf", kwlist,&self->instance->N
,&self->instance->Nby2
,&self->instance->normalize
))
    {


    }
    return 0;
}

GETFIELD(arm_dct4_instance_f32,N,"h");
GETFIELD(arm_dct4_instance_f32,Nby2,"h");
GETFIELD(arm_dct4_instance_f32,normalize,"f");


static PyMethodDef arm_dct4_instance_f32_methods[] = {

    {"N", (PyCFunction) Method_arm_dct4_instance_f32_N,METH_NOARGS,"N"},
    {"Nby2", (PyCFunction) Method_arm_dct4_instance_f32_Nby2,METH_NOARGS,"Nby2"},
    {"normalize", (PyCFunction) Method_arm_dct4_instance_f32_normalize,METH_NOARGS,"normalize"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_dct4_instance_f32,arm_dct4_instance_f32_new,arm_dct4_instance_f32_dealloc,arm_dct4_instance_f32_init,arm_dct4_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_dct4_instance_q31 *instance;
} ml_arm_dct4_instance_q31Object;


static void
arm_dct4_instance_q31_dealloc(ml_arm_dct4_instance_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_dct4_instance_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_dct4_instance_q31Object *self;
    //printf("New called\n");

    self = (ml_arm_dct4_instance_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_dct4_instance_q31));

        self->instance->pTwiddle = NULL;
        self->instance->pCosFactor = NULL;
        self->instance->pRfft = NULL;
        self->instance->pCfft = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_dct4_instance_q31_init(ml_arm_dct4_instance_q31Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddle=NULL;
    PyObject *pCosFactor=NULL;
    PyObject *pRfft=NULL;
    PyObject *pCfft=NULL;
char *kwlist[] = {
"N","Nby2","normalize",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hhi", kwlist,&self->instance->N
,&self->instance->Nby2
,&self->instance->normalize
))
    {


    }
    return 0;
}

GETFIELD(arm_dct4_instance_q31,N,"h");
GETFIELD(arm_dct4_instance_q31,Nby2,"h");
GETFIELD(arm_dct4_instance_q31,normalize,"i");


static PyMethodDef arm_dct4_instance_q31_methods[] = {

    {"N", (PyCFunction) Method_arm_dct4_instance_q31_N,METH_NOARGS,"N"},
    {"Nby2", (PyCFunction) Method_arm_dct4_instance_q31_Nby2,METH_NOARGS,"Nby2"},
    {"normalize", (PyCFunction) Method_arm_dct4_instance_q31_normalize,METH_NOARGS,"normalize"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_dct4_instance_q31,arm_dct4_instance_q31_new,arm_dct4_instance_q31_dealloc,arm_dct4_instance_q31_init,arm_dct4_instance_q31_methods);


typedef struct {
    PyObject_HEAD
    arm_dct4_instance_q15 *instance;
} ml_arm_dct4_instance_q15Object;


static void
arm_dct4_instance_q15_dealloc(ml_arm_dct4_instance_q15Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_dct4_instance_q15_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_dct4_instance_q15Object *self;
    //printf("New called\n");

    self = (ml_arm_dct4_instance_q15Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_dct4_instance_q15));

        self->instance->pTwiddle = NULL;
        self->instance->pCosFactor = NULL;
        self->instance->pRfft = NULL;
        self->instance->pCfft = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_dct4_instance_q15_init(ml_arm_dct4_instance_q15Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddle=NULL;
    PyObject *pCosFactor=NULL;
    PyObject *pRfft=NULL;
    PyObject *pCfft=NULL;
char *kwlist[] = {
"N","Nby2","normalize",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hhh", kwlist,&self->instance->N
,&self->instance->Nby2
,&self->instance->normalize
))
    {


    }
    return 0;
}

GETFIELD(arm_dct4_instance_q15,N,"h");
GETFIELD(arm_dct4_instance_q15,Nby2,"h");
GETFIELD(arm_dct4_instance_q15,normalize,"h");


static PyMethodDef arm_dct4_instance_q15_methods[] = {

    {"N", (PyCFunction) Method_arm_dct4_instance_q15_N,METH_NOARGS,"N"},
    {"Nby2", (PyCFunction) Method_arm_dct4_instance_q15_Nby2,METH_NOARGS,"Nby2"},
    {"normalize", (PyCFunction) Method_arm_dct4_instance_q15_normalize,METH_NOARGS,"normalize"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_dct4_instance_q15,arm_dct4_instance_q15_new,arm_dct4_instance_q15_dealloc,arm_dct4_instance_q15_init,arm_dct4_instance_q15_methods);


typedef struct {
    PyObject_HEAD
    arm_fir_decimate_instance_q15 *instance;
} ml_arm_fir_decimate_instance_q15Object;


static void
arm_fir_decimate_instance_q15_dealloc(ml_arm_fir_decimate_instance_q15Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_fir_decimate_instance_q15_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_fir_decimate_instance_q15Object *self;
    //printf("New called\n");

    self = (ml_arm_fir_decimate_instance_q15Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_fir_decimate_instance_q15));

        self->instance->pCoeffs = NULL;
        self->instance->pState = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_fir_decimate_instance_q15_init(ml_arm_fir_decimate_instance_q15Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pCoeffs=NULL;
    PyObject *pState=NULL;
char *kwlist[] = {
"M","numTaps",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|ih", kwlist,&self->instance->M
,&self->instance->numTaps
))
    {


    }
    return 0;
}

GETFIELD(arm_fir_decimate_instance_q15,M,"i");
GETFIELD(arm_fir_decimate_instance_q15,numTaps,"h");


static PyMethodDef arm_fir_decimate_instance_q15_methods[] = {

    {"M", (PyCFunction) Method_arm_fir_decimate_instance_q15_M,METH_NOARGS,"M"},
    {"numTaps", (PyCFunction) Method_arm_fir_decimate_instance_q15_numTaps,METH_NOARGS,"numTaps"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_fir_decimate_instance_q15,arm_fir_decimate_instance_q15_new,arm_fir_decimate_instance_q15_dealloc,arm_fir_decimate_instance_q15_init,arm_fir_decimate_instance_q15_methods);


typedef struct {
    PyObject_HEAD
    arm_fir_decimate_instance_q31 *instance;
} ml_arm_fir_decimate_instance_q31Object;


static void
arm_fir_decimate_instance_q31_dealloc(ml_arm_fir_decimate_instance_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_fir_decimate_instance_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_fir_decimate_instance_q31Object *self;
    //printf("New called\n");

    self = (ml_arm_fir_decimate_instance_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_fir_decimate_instance_q31));

        self->instance->pCoeffs = NULL;
        self->instance->pState = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_fir_decimate_instance_q31_init(ml_arm_fir_decimate_instance_q31Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pCoeffs=NULL;
    PyObject *pState=NULL;
char *kwlist[] = {
"M","numTaps",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|ih", kwlist,&self->instance->M
,&self->instance->numTaps
))
    {


    }
    return 0;
}

GETFIELD(arm_fir_decimate_instance_q31,M,"i");
GETFIELD(arm_fir_decimate_instance_q31,numTaps,"h");


static PyMethodDef arm_fir_decimate_instance_q31_methods[] = {

    {"M", (PyCFunction) Method_arm_fir_decimate_instance_q31_M,METH_NOARGS,"M"},
    {"numTaps", (PyCFunction) Method_arm_fir_decimate_instance_q31_numTaps,METH_NOARGS,"numTaps"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_fir_decimate_instance_q31,arm_fir_decimate_instance_q31_new,arm_fir_decimate_instance_q31_dealloc,arm_fir_decimate_instance_q31_init,arm_fir_decimate_instance_q31_methods);


typedef struct {
    PyObject_HEAD
    arm_fir_decimate_instance_f32 *instance;
} ml_arm_fir_decimate_instance_f32Object;


static void
arm_fir_decimate_instance_f32_dealloc(ml_arm_fir_decimate_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_fir_decimate_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_fir_decimate_instance_f32Object *self;
    //printf("New called\n");

    self = (ml_arm_fir_decimate_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_fir_decimate_instance_f32));

        self->instance->pCoeffs = NULL;
        self->instance->pState = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_fir_decimate_instance_f32_init(ml_arm_fir_decimate_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pCoeffs=NULL;
    PyObject *pState=NULL;
char *kwlist[] = {
"M","numTaps",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|ih", kwlist,&self->instance->M
,&self->instance->numTaps
))
    {


    }
    return 0;
}

GETFIELD(arm_fir_decimate_instance_f32,M,"i");
GETFIELD(arm_fir_decimate_instance_f32,numTaps,"h");


static PyMethodDef arm_fir_decimate_instance_f32_methods[] = {

    {"M", (PyCFunction) Method_arm_fir_decimate_instance_f32_M,METH_NOARGS,"M"},
    {"numTaps", (PyCFunction) Method_arm_fir_decimate_instance_f32_numTaps,METH_NOARGS,"numTaps"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_fir_decimate_instance_f32,arm_fir_decimate_instance_f32_new,arm_fir_decimate_instance_f32_dealloc,arm_fir_decimate_instance_f32_init,arm_fir_decimate_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_fir_interpolate_instance_q15 *instance;
} ml_arm_fir_interpolate_instance_q15Object;


static void
arm_fir_interpolate_instance_q15_dealloc(ml_arm_fir_interpolate_instance_q15Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_fir_interpolate_instance_q15_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_fir_interpolate_instance_q15Object *self;
    //printf("New called\n");

    self = (ml_arm_fir_interpolate_instance_q15Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_fir_interpolate_instance_q15));

        self->instance->pCoeffs = NULL;
        self->instance->pState = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_fir_interpolate_instance_q15_init(ml_arm_fir_interpolate_instance_q15Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pCoeffs=NULL;
    PyObject *pState=NULL;
char *kwlist[] = {
"L","phaseLength",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|ih", kwlist,&self->instance->L
,&self->instance->phaseLength
))
    {


    }
    return 0;
}

GETFIELD(arm_fir_interpolate_instance_q15,L,"i");
GETFIELD(arm_fir_interpolate_instance_q15,phaseLength,"h");


static PyMethodDef arm_fir_interpolate_instance_q15_methods[] = {

    {"L", (PyCFunction) Method_arm_fir_interpolate_instance_q15_L,METH_NOARGS,"L"},
    {"phaseLength", (PyCFunction) Method_arm_fir_interpolate_instance_q15_phaseLength,METH_NOARGS,"phaseLength"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_fir_interpolate_instance_q15,arm_fir_interpolate_instance_q15_new,arm_fir_interpolate_instance_q15_dealloc,arm_fir_interpolate_instance_q15_init,arm_fir_interpolate_instance_q15_methods);


typedef struct {
    PyObject_HEAD
    arm_fir_interpolate_instance_q31 *instance;
} ml_arm_fir_interpolate_instance_q31Object;


static void
arm_fir_interpolate_instance_q31_dealloc(ml_arm_fir_interpolate_instance_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_fir_interpolate_instance_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_fir_interpolate_instance_q31Object *self;
    //printf("New called\n");

    self = (ml_arm_fir_interpolate_instance_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_fir_interpolate_instance_q31));

        self->instance->pCoeffs = NULL;
        self->instance->pState = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_fir_interpolate_instance_q31_init(ml_arm_fir_interpolate_instance_q31Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pCoeffs=NULL;
    PyObject *pState=NULL;
char *kwlist[] = {
"L","phaseLength",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|ih", kwlist,&self->instance->L
,&self->instance->phaseLength
))
    {


    }
    return 0;
}

GETFIELD(arm_fir_interpolate_instance_q31,L,"i");
GETFIELD(arm_fir_interpolate_instance_q31,phaseLength,"h");


static PyMethodDef arm_fir_interpolate_instance_q31_methods[] = {

    {"L", (PyCFunction) Method_arm_fir_interpolate_instance_q31_L,METH_NOARGS,"L"},
    {"phaseLength", (PyCFunction) Method_arm_fir_interpolate_instance_q31_phaseLength,METH_NOARGS,"phaseLength"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_fir_interpolate_instance_q31,arm_fir_interpolate_instance_q31_new,arm_fir_interpolate_instance_q31_dealloc,arm_fir_interpolate_instance_q31_init,arm_fir_interpolate_instance_q31_methods);


typedef struct {
    PyObject_HEAD
    arm_fir_interpolate_instance_f32 *instance;
} ml_arm_fir_interpolate_instance_f32Object;


static void
arm_fir_interpolate_instance_f32_dealloc(ml_arm_fir_interpolate_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_fir_interpolate_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_fir_interpolate_instance_f32Object *self;
    //printf("New called\n");

    self = (ml_arm_fir_interpolate_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_fir_interpolate_instance_f32));

        self->instance->pCoeffs = NULL;
        self->instance->pState = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_fir_interpolate_instance_f32_init(ml_arm_fir_interpolate_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pCoeffs=NULL;
    PyObject *pState=NULL;
char *kwlist[] = {
"L","phaseLength",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|ih", kwlist,&self->instance->L
,&self->instance->phaseLength
))
    {


    }
    return 0;
}

GETFIELD(arm_fir_interpolate_instance_f32,L,"i");
GETFIELD(arm_fir_interpolate_instance_f32,phaseLength,"h");


static PyMethodDef arm_fir_interpolate_instance_f32_methods[] = {

    {"L", (PyCFunction) Method_arm_fir_interpolate_instance_f32_L,METH_NOARGS,"L"},
    {"phaseLength", (PyCFunction) Method_arm_fir_interpolate_instance_f32_phaseLength,METH_NOARGS,"phaseLength"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_fir_interpolate_instance_f32,arm_fir_interpolate_instance_f32_new,arm_fir_interpolate_instance_f32_dealloc,arm_fir_interpolate_instance_f32_init,arm_fir_interpolate_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_biquad_cas_df1_32x64_ins_q31 *instance;
} ml_arm_biquad_cas_df1_32x64_ins_q31Object;


static void
arm_biquad_cas_df1_32x64_ins_q31_dealloc(ml_arm_biquad_cas_df1_32x64_ins_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_biquad_cas_df1_32x64_ins_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_biquad_cas_df1_32x64_ins_q31Object *self;
    //printf("New called\n");

    self = (ml_arm_biquad_cas_df1_32x64_ins_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_biquad_cas_df1_32x64_ins_q31));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_biquad_cas_df1_32x64_ins_q31_init(ml_arm_biquad_cas_df1_32x64_ins_q31Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
char *kwlist[] = {
"numStages","postShift",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|ii", kwlist,&self->instance->numStages
,&self->instance->postShift
))
    {


    }
    return 0;
}

GETFIELD(arm_biquad_cas_df1_32x64_ins_q31,numStages,"i");
GETFIELD(arm_biquad_cas_df1_32x64_ins_q31,postShift,"i");


static PyMethodDef arm_biquad_cas_df1_32x64_ins_q31_methods[] = {

    {"numStages", (PyCFunction) Method_arm_biquad_cas_df1_32x64_ins_q31_numStages,METH_NOARGS,"numStages"},
    {"postShift", (PyCFunction) Method_arm_biquad_cas_df1_32x64_ins_q31_postShift,METH_NOARGS,"postShift"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_biquad_cas_df1_32x64_ins_q31,arm_biquad_cas_df1_32x64_ins_q31_new,arm_biquad_cas_df1_32x64_ins_q31_dealloc,arm_biquad_cas_df1_32x64_ins_q31_init,arm_biquad_cas_df1_32x64_ins_q31_methods);


typedef struct {
    PyObject_HEAD
    arm_biquad_cascade_df2T_instance_f32 *instance;
} ml_arm_biquad_cascade_df2T_instance_f32Object;


static void
arm_biquad_cascade_df2T_instance_f32_dealloc(ml_arm_biquad_cascade_df2T_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_biquad_cascade_df2T_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_biquad_cascade_df2T_instance_f32Object *self;
    //printf("New called\n");

    self = (ml_arm_biquad_cascade_df2T_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_biquad_cascade_df2T_instance_f32));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_biquad_cascade_df2T_instance_f32_init(ml_arm_biquad_cascade_df2T_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
char *kwlist[] = {
"numStages",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|i", kwlist,&self->instance->numStages
))
    {


    }
    return 0;
}

GETFIELD(arm_biquad_cascade_df2T_instance_f32,numStages,"i");


static PyMethodDef arm_biquad_cascade_df2T_instance_f32_methods[] = {

    {"numStages", (PyCFunction) Method_arm_biquad_cascade_df2T_instance_f32_numStages,METH_NOARGS,"numStages"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_biquad_cascade_df2T_instance_f32,arm_biquad_cascade_df2T_instance_f32_new,arm_biquad_cascade_df2T_instance_f32_dealloc,arm_biquad_cascade_df2T_instance_f32_init,arm_biquad_cascade_df2T_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_biquad_cascade_stereo_df2T_instance_f32 *instance;
} ml_arm_biquad_cascade_stereo_df2T_instance_f32Object;


static void
arm_biquad_cascade_stereo_df2T_instance_f32_dealloc(ml_arm_biquad_cascade_stereo_df2T_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_biquad_cascade_stereo_df2T_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_biquad_cascade_stereo_df2T_instance_f32Object *self;
    //printf("New called\n");

    self = (ml_arm_biquad_cascade_stereo_df2T_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_biquad_cascade_stereo_df2T_instance_f32));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_biquad_cascade_stereo_df2T_instance_f32_init(ml_arm_biquad_cascade_stereo_df2T_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
char *kwlist[] = {
"numStages",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|i", kwlist,&self->instance->numStages
))
    {


    }
    return 0;
}

GETFIELD(arm_biquad_cascade_stereo_df2T_instance_f32,numStages,"i");


static PyMethodDef arm_biquad_cascade_stereo_df2T_instance_f32_methods[] = {

    {"numStages", (PyCFunction) Method_arm_biquad_cascade_stereo_df2T_instance_f32_numStages,METH_NOARGS,"numStages"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_biquad_cascade_stereo_df2T_instance_f32,arm_biquad_cascade_stereo_df2T_instance_f32_new,arm_biquad_cascade_stereo_df2T_instance_f32_dealloc,arm_biquad_cascade_stereo_df2T_instance_f32_init,arm_biquad_cascade_stereo_df2T_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_biquad_cascade_df2T_instance_f64 *instance;
} ml_arm_biquad_cascade_df2T_instance_f64Object;


static void
arm_biquad_cascade_df2T_instance_f64_dealloc(ml_arm_biquad_cascade_df2T_instance_f64Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_biquad_cascade_df2T_instance_f64_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_biquad_cascade_df2T_instance_f64Object *self;
    //printf("New called\n");

    self = (ml_arm_biquad_cascade_df2T_instance_f64Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_biquad_cascade_df2T_instance_f64));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_biquad_cascade_df2T_instance_f64_init(ml_arm_biquad_cascade_df2T_instance_f64Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
char *kwlist[] = {
"numStages",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|i", kwlist,&self->instance->numStages
))
    {


    }
    return 0;
}

GETFIELD(arm_biquad_cascade_df2T_instance_f64,numStages,"i");


static PyMethodDef arm_biquad_cascade_df2T_instance_f64_methods[] = {

    {"numStages", (PyCFunction) Method_arm_biquad_cascade_df2T_instance_f64_numStages,METH_NOARGS,"numStages"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_biquad_cascade_df2T_instance_f64,arm_biquad_cascade_df2T_instance_f64_new,arm_biquad_cascade_df2T_instance_f64_dealloc,arm_biquad_cascade_df2T_instance_f64_init,arm_biquad_cascade_df2T_instance_f64_methods);


typedef struct {
    PyObject_HEAD
    arm_fir_lattice_instance_q15 *instance;
} ml_arm_fir_lattice_instance_q15Object;


static void
arm_fir_lattice_instance_q15_dealloc(ml_arm_fir_lattice_instance_q15Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_fir_lattice_instance_q15_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_fir_lattice_instance_q15Object *self;
    //printf("New called\n");

    self = (ml_arm_fir_lattice_instance_q15Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_fir_lattice_instance_q15));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_fir_lattice_instance_q15_init(ml_arm_fir_lattice_instance_q15Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
char *kwlist[] = {
"numStages",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|h", kwlist,&self->instance->numStages
))
    {


    }
    return 0;
}

GETFIELD(arm_fir_lattice_instance_q15,numStages,"h");


static PyMethodDef arm_fir_lattice_instance_q15_methods[] = {

    {"numStages", (PyCFunction) Method_arm_fir_lattice_instance_q15_numStages,METH_NOARGS,"numStages"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_fir_lattice_instance_q15,arm_fir_lattice_instance_q15_new,arm_fir_lattice_instance_q15_dealloc,arm_fir_lattice_instance_q15_init,arm_fir_lattice_instance_q15_methods);


typedef struct {
    PyObject_HEAD
    arm_fir_lattice_instance_q31 *instance;
} ml_arm_fir_lattice_instance_q31Object;


static void
arm_fir_lattice_instance_q31_dealloc(ml_arm_fir_lattice_instance_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_fir_lattice_instance_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_fir_lattice_instance_q31Object *self;
    //printf("New called\n");

    self = (ml_arm_fir_lattice_instance_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_fir_lattice_instance_q31));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_fir_lattice_instance_q31_init(ml_arm_fir_lattice_instance_q31Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
char *kwlist[] = {
"numStages",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|h", kwlist,&self->instance->numStages
))
    {


    }
    return 0;
}

GETFIELD(arm_fir_lattice_instance_q31,numStages,"h");


static PyMethodDef arm_fir_lattice_instance_q31_methods[] = {

    {"numStages", (PyCFunction) Method_arm_fir_lattice_instance_q31_numStages,METH_NOARGS,"numStages"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_fir_lattice_instance_q31,arm_fir_lattice_instance_q31_new,arm_fir_lattice_instance_q31_dealloc,arm_fir_lattice_instance_q31_init,arm_fir_lattice_instance_q31_methods);


typedef struct {
    PyObject_HEAD
    arm_fir_lattice_instance_f32 *instance;
} ml_arm_fir_lattice_instance_f32Object;


static void
arm_fir_lattice_instance_f32_dealloc(ml_arm_fir_lattice_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_fir_lattice_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_fir_lattice_instance_f32Object *self;
    //printf("New called\n");

    self = (ml_arm_fir_lattice_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_fir_lattice_instance_f32));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_fir_lattice_instance_f32_init(ml_arm_fir_lattice_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
char *kwlist[] = {
"numStages",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|h", kwlist,&self->instance->numStages
))
    {


    }
    return 0;
}

GETFIELD(arm_fir_lattice_instance_f32,numStages,"h");


static PyMethodDef arm_fir_lattice_instance_f32_methods[] = {

    {"numStages", (PyCFunction) Method_arm_fir_lattice_instance_f32_numStages,METH_NOARGS,"numStages"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_fir_lattice_instance_f32,arm_fir_lattice_instance_f32_new,arm_fir_lattice_instance_f32_dealloc,arm_fir_lattice_instance_f32_init,arm_fir_lattice_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_iir_lattice_instance_q15 *instance;
} ml_arm_iir_lattice_instance_q15Object;


static void
arm_iir_lattice_instance_q15_dealloc(ml_arm_iir_lattice_instance_q15Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pkCoeffs)
       {
          PyMem_Free(self->instance->pkCoeffs);
       }


       if (self->instance->pvCoeffs)
       {
          PyMem_Free(self->instance->pvCoeffs);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_iir_lattice_instance_q15_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_iir_lattice_instance_q15Object *self;
    //printf("New called\n");

    self = (ml_arm_iir_lattice_instance_q15Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_iir_lattice_instance_q15));

        self->instance->pState = NULL;
        self->instance->pkCoeffs = NULL;
        self->instance->pvCoeffs = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_iir_lattice_instance_q15_init(ml_arm_iir_lattice_instance_q15Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pkCoeffs=NULL;
    PyObject *pvCoeffs=NULL;
char *kwlist[] = {
"numStages","pkCoeffs","pvCoeffs",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hOO", kwlist,&self->instance->numStages
,&pkCoeffs
,&pvCoeffs
))
    {

    INITARRAYFIELD(pkCoeffs,NPY_INT16,int16_t,int16_t);
    INITARRAYFIELD(pvCoeffs,NPY_INT16,int16_t,int16_t);

    }
    return 0;
}

GETFIELD(arm_iir_lattice_instance_q15,numStages,"h");


static PyMethodDef arm_iir_lattice_instance_q15_methods[] = {

    {"numStages", (PyCFunction) Method_arm_iir_lattice_instance_q15_numStages,METH_NOARGS,"numStages"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_iir_lattice_instance_q15,arm_iir_lattice_instance_q15_new,arm_iir_lattice_instance_q15_dealloc,arm_iir_lattice_instance_q15_init,arm_iir_lattice_instance_q15_methods);


typedef struct {
    PyObject_HEAD
    arm_iir_lattice_instance_q31 *instance;
} ml_arm_iir_lattice_instance_q31Object;


static void
arm_iir_lattice_instance_q31_dealloc(ml_arm_iir_lattice_instance_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pkCoeffs)
       {
          PyMem_Free(self->instance->pkCoeffs);
       }


       if (self->instance->pvCoeffs)
       {
          PyMem_Free(self->instance->pvCoeffs);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_iir_lattice_instance_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_iir_lattice_instance_q31Object *self;
    //printf("New called\n");

    self = (ml_arm_iir_lattice_instance_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_iir_lattice_instance_q31));

        self->instance->pState = NULL;
        self->instance->pkCoeffs = NULL;
        self->instance->pvCoeffs = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_iir_lattice_instance_q31_init(ml_arm_iir_lattice_instance_q31Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pkCoeffs=NULL;
    PyObject *pvCoeffs=NULL;
char *kwlist[] = {
"numStages","pkCoeffs","pvCoeffs",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hOO", kwlist,&self->instance->numStages
,&pkCoeffs
,&pvCoeffs
))
    {

    INITARRAYFIELD(pkCoeffs,NPY_INT32,int32_t,int32_t);
    INITARRAYFIELD(pvCoeffs,NPY_INT32,int32_t,int32_t);

    }
    return 0;
}

GETFIELD(arm_iir_lattice_instance_q31,numStages,"h");


static PyMethodDef arm_iir_lattice_instance_q31_methods[] = {

    {"numStages", (PyCFunction) Method_arm_iir_lattice_instance_q31_numStages,METH_NOARGS,"numStages"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_iir_lattice_instance_q31,arm_iir_lattice_instance_q31_new,arm_iir_lattice_instance_q31_dealloc,arm_iir_lattice_instance_q31_init,arm_iir_lattice_instance_q31_methods);


typedef struct {
    PyObject_HEAD
    arm_iir_lattice_instance_f32 *instance;
} ml_arm_iir_lattice_instance_f32Object;


static void
arm_iir_lattice_instance_f32_dealloc(ml_arm_iir_lattice_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pkCoeffs)
       {
          PyMem_Free(self->instance->pkCoeffs);
       }


       if (self->instance->pvCoeffs)
       {
          PyMem_Free(self->instance->pvCoeffs);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_iir_lattice_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_iir_lattice_instance_f32Object *self;
    //printf("New called\n");

    self = (ml_arm_iir_lattice_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_iir_lattice_instance_f32));

        self->instance->pState = NULL;
        self->instance->pkCoeffs = NULL;
        self->instance->pvCoeffs = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_iir_lattice_instance_f32_init(ml_arm_iir_lattice_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pkCoeffs=NULL;
    PyObject *pvCoeffs=NULL;
char *kwlist[] = {
"numStages","pkCoeffs","pvCoeffs",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hOO", kwlist,&self->instance->numStages
,&pkCoeffs
,&pvCoeffs
))
    {

    INITARRAYFIELD(pkCoeffs,NPY_DOUBLE,double,float32_t);
    INITARRAYFIELD(pvCoeffs,NPY_DOUBLE,double,float32_t);

    }
    return 0;
}

GETFIELD(arm_iir_lattice_instance_f32,numStages,"h");


static PyMethodDef arm_iir_lattice_instance_f32_methods[] = {

    {"numStages", (PyCFunction) Method_arm_iir_lattice_instance_f32_numStages,METH_NOARGS,"numStages"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_iir_lattice_instance_f32,arm_iir_lattice_instance_f32_new,arm_iir_lattice_instance_f32_dealloc,arm_iir_lattice_instance_f32_init,arm_iir_lattice_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_lms_instance_f32 *instance;
} ml_arm_lms_instance_f32Object;


static void
arm_lms_instance_f32_dealloc(ml_arm_lms_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_lms_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_lms_instance_f32Object *self;
    //printf("New called\n");

    self = (ml_arm_lms_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_lms_instance_f32));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_lms_instance_f32_init(ml_arm_lms_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
char *kwlist[] = {
"numTaps","mu",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hf", kwlist,&self->instance->numTaps
,&self->instance->mu
))
    {


    }
    return 0;
}

GETFIELD(arm_lms_instance_f32,numTaps,"h");
GETFIELD(arm_lms_instance_f32,mu,"f");


static PyMethodDef arm_lms_instance_f32_methods[] = {

    {"numTaps", (PyCFunction) Method_arm_lms_instance_f32_numTaps,METH_NOARGS,"numTaps"},
    {"mu", (PyCFunction) Method_arm_lms_instance_f32_mu,METH_NOARGS,"mu"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_lms_instance_f32,arm_lms_instance_f32_new,arm_lms_instance_f32_dealloc,arm_lms_instance_f32_init,arm_lms_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_lms_instance_q15 *instance;
} ml_arm_lms_instance_q15Object;


static void
arm_lms_instance_q15_dealloc(ml_arm_lms_instance_q15Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_lms_instance_q15_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_lms_instance_q15Object *self;
    //printf("New called\n");

    self = (ml_arm_lms_instance_q15Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_lms_instance_q15));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_lms_instance_q15_init(ml_arm_lms_instance_q15Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
char *kwlist[] = {
"numTaps","mu","postShift",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hhi", kwlist,&self->instance->numTaps
,&self->instance->mu
,&self->instance->postShift
))
    {


    }
    return 0;
}

GETFIELD(arm_lms_instance_q15,numTaps,"h");
GETFIELD(arm_lms_instance_q15,mu,"h");
GETFIELD(arm_lms_instance_q15,postShift,"i");


static PyMethodDef arm_lms_instance_q15_methods[] = {

    {"numTaps", (PyCFunction) Method_arm_lms_instance_q15_numTaps,METH_NOARGS,"numTaps"},
    {"mu", (PyCFunction) Method_arm_lms_instance_q15_mu,METH_NOARGS,"mu"},
    {"postShift", (PyCFunction) Method_arm_lms_instance_q15_postShift,METH_NOARGS,"postShift"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_lms_instance_q15,arm_lms_instance_q15_new,arm_lms_instance_q15_dealloc,arm_lms_instance_q15_init,arm_lms_instance_q15_methods);


typedef struct {
    PyObject_HEAD
    arm_lms_instance_q31 *instance;
} ml_arm_lms_instance_q31Object;


static void
arm_lms_instance_q31_dealloc(ml_arm_lms_instance_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_lms_instance_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_lms_instance_q31Object *self;
    //printf("New called\n");

    self = (ml_arm_lms_instance_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_lms_instance_q31));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_lms_instance_q31_init(ml_arm_lms_instance_q31Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
char *kwlist[] = {
"numTaps","mu","postShift",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hii", kwlist,&self->instance->numTaps
,&self->instance->mu
,&self->instance->postShift
))
    {


    }
    return 0;
}

GETFIELD(arm_lms_instance_q31,numTaps,"h");
GETFIELD(arm_lms_instance_q31,mu,"i");
GETFIELD(arm_lms_instance_q31,postShift,"i");


static PyMethodDef arm_lms_instance_q31_methods[] = {

    {"numTaps", (PyCFunction) Method_arm_lms_instance_q31_numTaps,METH_NOARGS,"numTaps"},
    {"mu", (PyCFunction) Method_arm_lms_instance_q31_mu,METH_NOARGS,"mu"},
    {"postShift", (PyCFunction) Method_arm_lms_instance_q31_postShift,METH_NOARGS,"postShift"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_lms_instance_q31,arm_lms_instance_q31_new,arm_lms_instance_q31_dealloc,arm_lms_instance_q31_init,arm_lms_instance_q31_methods);


typedef struct {
    PyObject_HEAD
    arm_lms_norm_instance_f32 *instance;
} ml_arm_lms_norm_instance_f32Object;


static void
arm_lms_norm_instance_f32_dealloc(ml_arm_lms_norm_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_lms_norm_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_lms_norm_instance_f32Object *self;
    //printf("New called\n");

    self = (ml_arm_lms_norm_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_lms_norm_instance_f32));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_lms_norm_instance_f32_init(ml_arm_lms_norm_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
char *kwlist[] = {
"numTaps","mu","energy","x0",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hfff", kwlist,&self->instance->numTaps
,&self->instance->mu
,&self->instance->energy
,&self->instance->x0
))
    {


    }
    return 0;
}

GETFIELD(arm_lms_norm_instance_f32,numTaps,"h");
GETFIELD(arm_lms_norm_instance_f32,mu,"f");
GETFIELD(arm_lms_norm_instance_f32,energy,"f");
GETFIELD(arm_lms_norm_instance_f32,x0,"f");


static PyMethodDef arm_lms_norm_instance_f32_methods[] = {

    {"numTaps", (PyCFunction) Method_arm_lms_norm_instance_f32_numTaps,METH_NOARGS,"numTaps"},
    {"mu", (PyCFunction) Method_arm_lms_norm_instance_f32_mu,METH_NOARGS,"mu"},
    {"energy", (PyCFunction) Method_arm_lms_norm_instance_f32_energy,METH_NOARGS,"energy"},
    {"x0", (PyCFunction) Method_arm_lms_norm_instance_f32_x0,METH_NOARGS,"x0"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_lms_norm_instance_f32,arm_lms_norm_instance_f32_new,arm_lms_norm_instance_f32_dealloc,arm_lms_norm_instance_f32_init,arm_lms_norm_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_lms_norm_instance_q31 *instance;
} ml_arm_lms_norm_instance_q31Object;


static void
arm_lms_norm_instance_q31_dealloc(ml_arm_lms_norm_instance_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }



       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_lms_norm_instance_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_lms_norm_instance_q31Object *self;
    //printf("New called\n");

    self = (ml_arm_lms_norm_instance_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_lms_norm_instance_q31));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;
        self->instance->recipTable = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_lms_norm_instance_q31_init(ml_arm_lms_norm_instance_q31Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
    PyObject *recipTable=NULL;
char *kwlist[] = {
"numTaps","mu","postShift","energy","x0",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hiiii", kwlist,&self->instance->numTaps
,&self->instance->mu
,&self->instance->postShift
,&self->instance->energy
,&self->instance->x0
))
    {


    }
    return 0;
}

GETFIELD(arm_lms_norm_instance_q31,numTaps,"h");
GETFIELD(arm_lms_norm_instance_q31,mu,"i");
GETFIELD(arm_lms_norm_instance_q31,postShift,"i");
GETFIELD(arm_lms_norm_instance_q31,energy,"i");
GETFIELD(arm_lms_norm_instance_q31,x0,"i");


static PyMethodDef arm_lms_norm_instance_q31_methods[] = {

    {"numTaps", (PyCFunction) Method_arm_lms_norm_instance_q31_numTaps,METH_NOARGS,"numTaps"},
    {"mu", (PyCFunction) Method_arm_lms_norm_instance_q31_mu,METH_NOARGS,"mu"},
    {"postShift", (PyCFunction) Method_arm_lms_norm_instance_q31_postShift,METH_NOARGS,"postShift"},
    {"energy", (PyCFunction) Method_arm_lms_norm_instance_q31_energy,METH_NOARGS,"energy"},
    {"x0", (PyCFunction) Method_arm_lms_norm_instance_q31_x0,METH_NOARGS,"x0"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_lms_norm_instance_q31,arm_lms_norm_instance_q31_new,arm_lms_norm_instance_q31_dealloc,arm_lms_norm_instance_q31_init,arm_lms_norm_instance_q31_methods);


typedef struct {
    PyObject_HEAD
    arm_lms_norm_instance_q15 *instance;
} ml_arm_lms_norm_instance_q15Object;


static void
arm_lms_norm_instance_q15_dealloc(ml_arm_lms_norm_instance_q15Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_lms_norm_instance_q15_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_lms_norm_instance_q15Object *self;
    //printf("New called\n");

    self = (ml_arm_lms_norm_instance_q15Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_lms_norm_instance_q15));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;
        self->instance->recipTable = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_lms_norm_instance_q15_init(ml_arm_lms_norm_instance_q15Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
    PyObject *recipTable=NULL;
char *kwlist[] = {
"numTaps","mu","postShift","energy","x0",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hhihh", kwlist,&self->instance->numTaps
,&self->instance->mu
,&self->instance->postShift
,&self->instance->energy
,&self->instance->x0
))
    {


    }
    return 0;
}

GETFIELD(arm_lms_norm_instance_q15,numTaps,"h");
GETFIELD(arm_lms_norm_instance_q15,mu,"h");
GETFIELD(arm_lms_norm_instance_q15,postShift,"i");
GETFIELD(arm_lms_norm_instance_q15,energy,"h");
GETFIELD(arm_lms_norm_instance_q15,x0,"h");


static PyMethodDef arm_lms_norm_instance_q15_methods[] = {

    {"numTaps", (PyCFunction) Method_arm_lms_norm_instance_q15_numTaps,METH_NOARGS,"numTaps"},
    {"mu", (PyCFunction) Method_arm_lms_norm_instance_q15_mu,METH_NOARGS,"mu"},
    {"postShift", (PyCFunction) Method_arm_lms_norm_instance_q15_postShift,METH_NOARGS,"postShift"},
    {"energy", (PyCFunction) Method_arm_lms_norm_instance_q15_energy,METH_NOARGS,"energy"},
    {"x0", (PyCFunction) Method_arm_lms_norm_instance_q15_x0,METH_NOARGS,"x0"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_lms_norm_instance_q15,arm_lms_norm_instance_q15_new,arm_lms_norm_instance_q15_dealloc,arm_lms_norm_instance_q15_init,arm_lms_norm_instance_q15_methods);


typedef struct {
    PyObject_HEAD
    arm_fir_sparse_instance_f32 *instance;
} ml_arm_fir_sparse_instance_f32Object;


static void
arm_fir_sparse_instance_f32_dealloc(ml_arm_fir_sparse_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       if (self->instance->pTapDelay)
       {
          PyMem_Free(self->instance->pTapDelay);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_fir_sparse_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_fir_sparse_instance_f32Object *self;
    //printf("New called\n");

    self = (ml_arm_fir_sparse_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_fir_sparse_instance_f32));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;
        self->instance->pTapDelay = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_fir_sparse_instance_f32_init(ml_arm_fir_sparse_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
    PyObject *pTapDelay=NULL;
char *kwlist[] = {
"numTaps","stateIndex","maxDelay","pTapDelay",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hhhO", kwlist,&self->instance->numTaps
,&self->instance->stateIndex
,&self->instance->maxDelay
,&pTapDelay
))
    {

    INITARRAYFIELD(pTapDelay,NPY_INT32,int32_t,int32_t);

    }
    return 0;
}

GETFIELD(arm_fir_sparse_instance_f32,numTaps,"h");
GETFIELD(arm_fir_sparse_instance_f32,stateIndex,"h");
GETFIELD(arm_fir_sparse_instance_f32,maxDelay,"h");


static PyMethodDef arm_fir_sparse_instance_f32_methods[] = {

    {"numTaps", (PyCFunction) Method_arm_fir_sparse_instance_f32_numTaps,METH_NOARGS,"numTaps"},
    {"stateIndex", (PyCFunction) Method_arm_fir_sparse_instance_f32_stateIndex,METH_NOARGS,"stateIndex"},
    {"maxDelay", (PyCFunction) Method_arm_fir_sparse_instance_f32_maxDelay,METH_NOARGS,"maxDelay"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_fir_sparse_instance_f32,arm_fir_sparse_instance_f32_new,arm_fir_sparse_instance_f32_dealloc,arm_fir_sparse_instance_f32_init,arm_fir_sparse_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_fir_sparse_instance_q31 *instance;
} ml_arm_fir_sparse_instance_q31Object;


static void
arm_fir_sparse_instance_q31_dealloc(ml_arm_fir_sparse_instance_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       if (self->instance->pTapDelay)
       {
          PyMem_Free(self->instance->pTapDelay);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_fir_sparse_instance_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_fir_sparse_instance_q31Object *self;
    //printf("New called\n");

    self = (ml_arm_fir_sparse_instance_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_fir_sparse_instance_q31));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;
        self->instance->pTapDelay = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_fir_sparse_instance_q31_init(ml_arm_fir_sparse_instance_q31Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
    PyObject *pTapDelay=NULL;
char *kwlist[] = {
"numTaps","stateIndex","maxDelay","pTapDelay",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hhhO", kwlist,&self->instance->numTaps
,&self->instance->stateIndex
,&self->instance->maxDelay
,&pTapDelay
))
    {

    INITARRAYFIELD(pTapDelay,NPY_INT32,int32_t,int32_t);

    }
    return 0;
}

GETFIELD(arm_fir_sparse_instance_q31,numTaps,"h");
GETFIELD(arm_fir_sparse_instance_q31,stateIndex,"h");
GETFIELD(arm_fir_sparse_instance_q31,maxDelay,"h");


static PyMethodDef arm_fir_sparse_instance_q31_methods[] = {

    {"numTaps", (PyCFunction) Method_arm_fir_sparse_instance_q31_numTaps,METH_NOARGS,"numTaps"},
    {"stateIndex", (PyCFunction) Method_arm_fir_sparse_instance_q31_stateIndex,METH_NOARGS,"stateIndex"},
    {"maxDelay", (PyCFunction) Method_arm_fir_sparse_instance_q31_maxDelay,METH_NOARGS,"maxDelay"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_fir_sparse_instance_q31,arm_fir_sparse_instance_q31_new,arm_fir_sparse_instance_q31_dealloc,arm_fir_sparse_instance_q31_init,arm_fir_sparse_instance_q31_methods);


typedef struct {
    PyObject_HEAD
    arm_fir_sparse_instance_q15 *instance;
} ml_arm_fir_sparse_instance_q15Object;


static void
arm_fir_sparse_instance_q15_dealloc(ml_arm_fir_sparse_instance_q15Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       if (self->instance->pTapDelay)
       {
          PyMem_Free(self->instance->pTapDelay);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_fir_sparse_instance_q15_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_fir_sparse_instance_q15Object *self;
    //printf("New called\n");

    self = (ml_arm_fir_sparse_instance_q15Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_fir_sparse_instance_q15));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;
        self->instance->pTapDelay = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_fir_sparse_instance_q15_init(ml_arm_fir_sparse_instance_q15Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
    PyObject *pTapDelay=NULL;
char *kwlist[] = {
"numTaps","stateIndex","maxDelay","pTapDelay",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hhhO", kwlist,&self->instance->numTaps
,&self->instance->stateIndex
,&self->instance->maxDelay
,&pTapDelay
))
    {

    INITARRAYFIELD(pTapDelay,NPY_INT32,int32_t,int32_t);

    }
    return 0;
}

GETFIELD(arm_fir_sparse_instance_q15,numTaps,"h");
GETFIELD(arm_fir_sparse_instance_q15,stateIndex,"h");
GETFIELD(arm_fir_sparse_instance_q15,maxDelay,"h");


static PyMethodDef arm_fir_sparse_instance_q15_methods[] = {

    {"numTaps", (PyCFunction) Method_arm_fir_sparse_instance_q15_numTaps,METH_NOARGS,"numTaps"},
    {"stateIndex", (PyCFunction) Method_arm_fir_sparse_instance_q15_stateIndex,METH_NOARGS,"stateIndex"},
    {"maxDelay", (PyCFunction) Method_arm_fir_sparse_instance_q15_maxDelay,METH_NOARGS,"maxDelay"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_fir_sparse_instance_q15,arm_fir_sparse_instance_q15_new,arm_fir_sparse_instance_q15_dealloc,arm_fir_sparse_instance_q15_init,arm_fir_sparse_instance_q15_methods);


typedef struct {
    PyObject_HEAD
    arm_fir_sparse_instance_q7 *instance;
} ml_arm_fir_sparse_instance_q7Object;


static void
arm_fir_sparse_instance_q7_dealloc(ml_arm_fir_sparse_instance_q7Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       if (self->instance->pState)
       {
          PyMem_Free(self->instance->pState);
       }


       if (self->instance->pCoeffs)
       {
          PyMem_Free(self->instance->pCoeffs);
       }


       if (self->instance->pTapDelay)
       {
          PyMem_Free(self->instance->pTapDelay);
       }


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_fir_sparse_instance_q7_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ml_arm_fir_sparse_instance_q7Object *self;
    //printf("New called\n");

    self = (ml_arm_fir_sparse_instance_q7Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_fir_sparse_instance_q7));

        self->instance->pState = NULL;
        self->instance->pCoeffs = NULL;
        self->instance->pTapDelay = NULL;

    }
 
   
    return (PyObject *)self;
}

static int
arm_fir_sparse_instance_q7_init(ml_arm_fir_sparse_instance_q7Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pState=NULL;
    PyObject *pCoeffs=NULL;
    PyObject *pTapDelay=NULL;
char *kwlist[] = {
"numTaps","stateIndex","maxDelay","pTapDelay",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hhhO", kwlist,&self->instance->numTaps
,&self->instance->stateIndex
,&self->instance->maxDelay
,&pTapDelay
))
    {

    INITARRAYFIELD(pTapDelay,NPY_INT32,int32_t,int32_t);

    }
    return 0;
}

GETFIELD(arm_fir_sparse_instance_q7,numTaps,"h");
GETFIELD(arm_fir_sparse_instance_q7,stateIndex,"h");
GETFIELD(arm_fir_sparse_instance_q7,maxDelay,"h");


static PyMethodDef arm_fir_sparse_instance_q7_methods[] = {

    {"numTaps", (PyCFunction) Method_arm_fir_sparse_instance_q7_numTaps,METH_NOARGS,"numTaps"},
    {"stateIndex", (PyCFunction) Method_arm_fir_sparse_instance_q7_stateIndex,METH_NOARGS,"stateIndex"},
    {"maxDelay", (PyCFunction) Method_arm_fir_sparse_instance_q7_maxDelay,METH_NOARGS,"maxDelay"},

    {NULL}  /* Sentinel */
};


MLTYPE(arm_fir_sparse_instance_q7,arm_fir_sparse_instance_q7_new,arm_fir_sparse_instance_q7_dealloc,arm_fir_sparse_instance_q7_init,arm_fir_sparse_instance_q7_methods);


void typeRegistration(PyObject *module) {

  ADDTYPE(arm_fir_instance_q7);
  ADDTYPE(arm_fir_instance_q15);
  ADDTYPE(arm_fir_instance_q31);
  ADDTYPE(arm_fir_instance_f32);
  ADDTYPE(arm_biquad_casd_df1_inst_q15);
  ADDTYPE(arm_biquad_casd_df1_inst_q31);
  ADDTYPE(arm_biquad_casd_df1_inst_f32);
  ADDTYPE(arm_matrix_instance_f32);
  ADDTYPE(arm_matrix_instance_f64);
  ADDTYPE(arm_matrix_instance_q15);
  ADDTYPE(arm_matrix_instance_q31);
  ADDTYPE(arm_pid_instance_q15);
  ADDTYPE(arm_pid_instance_q31);
  ADDTYPE(arm_pid_instance_f32);
  ADDTYPE(arm_linear_interp_instance_f32);
  ADDTYPE(arm_bilinear_interp_instance_f32);
  ADDTYPE(arm_bilinear_interp_instance_q31);
  ADDTYPE(arm_bilinear_interp_instance_q15);
  ADDTYPE(arm_bilinear_interp_instance_q7);
  ADDTYPE(arm_cfft_radix2_instance_q15);
  ADDTYPE(arm_cfft_radix4_instance_q15);
  ADDTYPE(arm_cfft_radix2_instance_q31);
  ADDTYPE(arm_cfft_radix4_instance_q31);
  ADDTYPE(arm_cfft_radix2_instance_f32);
  ADDTYPE(arm_cfft_radix4_instance_f32);
  ADDTYPE(arm_cfft_instance_q15);
  ADDTYPE(arm_cfft_instance_q31);
  ADDTYPE(arm_cfft_instance_f32);
  ADDTYPE(arm_rfft_instance_q15);
  ADDTYPE(arm_rfft_instance_q31);
  ADDTYPE(arm_rfft_instance_f32);
  ADDTYPE(arm_rfft_fast_instance_f32);
  ADDTYPE(arm_dct4_instance_f32);
  ADDTYPE(arm_dct4_instance_q31);
  ADDTYPE(arm_dct4_instance_q15);
  ADDTYPE(arm_fir_decimate_instance_q15);
  ADDTYPE(arm_fir_decimate_instance_q31);
  ADDTYPE(arm_fir_decimate_instance_f32);
  ADDTYPE(arm_fir_interpolate_instance_q15);
  ADDTYPE(arm_fir_interpolate_instance_q31);
  ADDTYPE(arm_fir_interpolate_instance_f32);
  ADDTYPE(arm_biquad_cas_df1_32x64_ins_q31);
  ADDTYPE(arm_biquad_cascade_df2T_instance_f32);
  ADDTYPE(arm_biquad_cascade_stereo_df2T_instance_f32);
  ADDTYPE(arm_biquad_cascade_df2T_instance_f64);
  ADDTYPE(arm_fir_lattice_instance_q15);
  ADDTYPE(arm_fir_lattice_instance_q31);
  ADDTYPE(arm_fir_lattice_instance_f32);
  ADDTYPE(arm_iir_lattice_instance_q15);
  ADDTYPE(arm_iir_lattice_instance_q31);
  ADDTYPE(arm_iir_lattice_instance_f32);
  ADDTYPE(arm_lms_instance_f32);
  ADDTYPE(arm_lms_instance_q15);
  ADDTYPE(arm_lms_instance_q31);
  ADDTYPE(arm_lms_norm_instance_f32);
  ADDTYPE(arm_lms_norm_instance_q31);
  ADDTYPE(arm_lms_norm_instance_q15);
  ADDTYPE(arm_fir_sparse_instance_f32);
  ADDTYPE(arm_fir_sparse_instance_q31);
  ADDTYPE(arm_fir_sparse_instance_q15);
  ADDTYPE(arm_fir_sparse_instance_q7);

}


static PyObject *
cmsis_arm_recip_q31(PyObject *obj, PyObject *args)
{

  q31_t in; // input
  q31_t *dst=NULL; // output
  PyObject *pRecipTable=NULL; // input
  q31_t *pRecipTable_converted=NULL; // input

  if (PyArg_ParseTuple(args,"iO",&in,&pRecipTable))
  {

    GETARGUMENT(pRecipTable,NPY_INT32,int32_t,int32_t);
    
    dst=PyMem_Malloc(sizeof(q31_t)*1);


    uint32_t returnValue = arm_recip_q31(in,dst,pRecipTable_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* dstOBJ=Py_BuildValue("i",*dst);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,dstOBJ);

    Py_DECREF(theReturnOBJ);
    Py_DECREF(dstOBJ);
    FREEARGUMENT(pRecipTable_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_recip_q15(PyObject *obj, PyObject *args)
{

  q15_t in; // input
  q15_t *dst=NULL; // output
  PyObject *pRecipTable=NULL; // input
  q15_t *pRecipTable_converted=NULL; // input

  if (PyArg_ParseTuple(args,"hO",&in,&pRecipTable))
  {

    GETARGUMENT(pRecipTable,NPY_INT16,int16_t,int16_t);
    
    dst=PyMem_Malloc(sizeof(q15_t)*1);


    uint32_t returnValue = arm_recip_q15(in,dst,pRecipTable_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* dstOBJ=Py_BuildValue("h",*dst);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,dstOBJ);

    Py_DECREF(theReturnOBJ);
    Py_DECREF(dstOBJ);
    FREEARGUMENT(pRecipTable_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_q7(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q7_t *pSrc_converted=NULL; // input
  q7_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_fir_instance_q7Object *selfS = (ml_arm_fir_instance_q7Object *)S;
    GETARGUMENT(pSrc,NPY_BYTE,int8_t,q7_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q7_t)*blockSize);


    arm_fir_q7(selfS->instance,pSrc_converted,pDst,blockSize);
 INT8ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_init_q7(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numTaps; // input
  PyObject *pCoeffs=NULL; // input
  q7_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  q7_t *pState_converted=NULL; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OhOO",&S,&numTaps,&pCoeffs,&pState))
  {

    ml_arm_fir_instance_q7Object *selfS = (ml_arm_fir_instance_q7Object *)S;
    GETARGUMENT(pCoeffs,NPY_BYTE,int8_t,q7_t);
    GETARGUMENT(pState,NPY_BYTE,int8_t,q7_t);
    blockSize = arraySizepState - arraySizepCoeffs + 1;

    arm_fir_init_q7(selfS->instance,numTaps,pCoeffs_converted,pState_converted,blockSize);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_fir_instance_q15Object *selfS = (ml_arm_fir_instance_q15Object *)S;
    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_fir_q15(selfS->instance,pSrc_converted,pDst,blockSize);
 INT16ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_fast_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_fir_instance_q15Object *selfS = (ml_arm_fir_instance_q15Object *)S;
    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_fir_fast_q15(selfS->instance,pSrc_converted,pDst,blockSize);
 INT16ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_init_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numTaps; // input
  PyObject *pCoeffs=NULL; // input
  q15_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  q15_t *pState_converted=NULL; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OhOO",&S,&numTaps,&pCoeffs,&pState))
  {

    ml_arm_fir_instance_q15Object *selfS = (ml_arm_fir_instance_q15Object *)S;
    GETARGUMENT(pCoeffs,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pState,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepState - arraySizepCoeffs + 1;

    arm_status returnValue = arm_fir_init_q15(selfS->instance,numTaps,pCoeffs_converted,pState_converted,blockSize);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_fir_instance_q31Object *selfS = (ml_arm_fir_instance_q31Object *)S;
    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_fir_q31(selfS->instance,pSrc_converted,pDst,blockSize);
 INT32ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_fast_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_fir_instance_q31Object *selfS = (ml_arm_fir_instance_q31Object *)S;
    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_fir_fast_q31(selfS->instance,pSrc_converted,pDst,blockSize);
 INT32ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_init_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numTaps; // input
  PyObject *pCoeffs=NULL; // input
  q31_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  q31_t *pState_converted=NULL; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OhOO",&S,&numTaps,&pCoeffs,&pState))
  {

    ml_arm_fir_instance_q31Object *selfS = (ml_arm_fir_instance_q31Object *)S;
    GETARGUMENT(pCoeffs,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pState,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepState - arraySizepCoeffs + 1;

    arm_fir_init_q31(selfS->instance,numTaps,pCoeffs_converted,pState_converted,blockSize);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  float32_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_fir_instance_f32Object *selfS = (ml_arm_fir_instance_f32Object *)S;
    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*blockSize);


    arm_fir_f32(selfS->instance,pSrc_converted,pDst,blockSize);
 FLOATARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numTaps; // input
  PyObject *pCoeffs=NULL; // input
  float32_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  float32_t *pState_converted=NULL; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OhOO",&S,&numTaps,&pCoeffs,&pState))
  {

    ml_arm_fir_instance_f32Object *selfS = (ml_arm_fir_instance_f32Object *)S;
    GETARGUMENT(pCoeffs,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pState,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepState - arraySizepCoeffs + 1;

    arm_fir_init_f32(selfS->instance,numTaps,pCoeffs_converted,pState_converted,blockSize);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_biquad_cascade_df1_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_biquad_casd_df1_inst_q15Object *selfS = (ml_arm_biquad_casd_df1_inst_q15Object *)S;
    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_biquad_cascade_df1_q15(selfS->instance,pSrc_converted,pDst,blockSize);
 INT16ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_biquad_cascade_df1_init_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint32_t numStages; // input
  PyObject *pCoeffs=NULL; // input
  q15_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  q15_t *pState_converted=NULL; // input
  int32_t postShift; // input

  if (PyArg_ParseTuple(args,"OiOOi",&S,&numStages,&pCoeffs,&pState,&postShift))
  {

    ml_arm_biquad_casd_df1_inst_q15Object *selfS = (ml_arm_biquad_casd_df1_inst_q15Object *)S;
    GETARGUMENT(pCoeffs,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pState,NPY_INT16,int16_t,int16_t);

    arm_biquad_cascade_df1_init_q15(selfS->instance,(uint8_t)numStages,pCoeffs_converted,pState_converted,(int8_t)postShift);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_biquad_cascade_df1_fast_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_biquad_casd_df1_inst_q15Object *selfS = (ml_arm_biquad_casd_df1_inst_q15Object *)S;
    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_biquad_cascade_df1_fast_q15(selfS->instance,pSrc_converted,pDst,blockSize);
 INT16ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_biquad_cascade_df1_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_biquad_casd_df1_inst_q31Object *selfS = (ml_arm_biquad_casd_df1_inst_q31Object *)S;
    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_biquad_cascade_df1_q31(selfS->instance,pSrc_converted,pDst,blockSize);
 INT32ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_biquad_cascade_df1_fast_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_biquad_casd_df1_inst_q31Object *selfS = (ml_arm_biquad_casd_df1_inst_q31Object *)S;
    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_biquad_cascade_df1_fast_q31(selfS->instance,pSrc_converted,pDst,blockSize);
 INT32ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_biquad_cascade_df1_init_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint32_t numStages; // input
  PyObject *pCoeffs=NULL; // input
  q31_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  q31_t *pState_converted=NULL; // input
  int32_t postShift; // input

  if (PyArg_ParseTuple(args,"OiOOi",&S,&numStages,&pCoeffs,&pState,&postShift))
  {

    ml_arm_biquad_casd_df1_inst_q31Object *selfS = (ml_arm_biquad_casd_df1_inst_q31Object *)S;
    GETARGUMENT(pCoeffs,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pState,NPY_INT32,int32_t,int32_t);

    arm_biquad_cascade_df1_init_q31(selfS->instance,(uint8_t)numStages,pCoeffs_converted,pState_converted,(int8_t)postShift);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_biquad_cascade_df1_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  float32_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_biquad_casd_df1_inst_f32Object *selfS = (ml_arm_biquad_casd_df1_inst_f32Object *)S;
    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*blockSize);


    arm_biquad_cascade_df1_f32(selfS->instance,pSrc_converted,pDst,blockSize);
 FLOATARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_biquad_cascade_df1_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint32_t numStages; // input
  PyObject *pCoeffs=NULL; // input
  float32_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  float32_t *pState_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OiOO",&S,&numStages,&pCoeffs,&pState))
  {

    ml_arm_biquad_casd_df1_inst_f32Object *selfS = (ml_arm_biquad_casd_df1_inst_f32Object *)S;
    GETARGUMENT(pCoeffs,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pState,NPY_DOUBLE,double,float32_t);

    arm_biquad_cascade_df1_init_f32(selfS->instance,(uint8_t)numStages,pCoeffs_converted,pState_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mat_add_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  arm_matrix_instance_f32 *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  arm_matrix_instance_f32 *pSrcB_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    arm_matrix_instance_f32 *pSrcA_converted = f32MatrixFromNumpy(pSrcA);
    arm_matrix_instance_f32 *pSrcB_converted = f32MatrixFromNumpy(pSrcB);
    uint32_t row = pSrcA_converted->numRows ;
    uint32_t column = pSrcB_converted->numCols ;
    arm_matrix_instance_f32 *pDst_converted = createf32Matrix(row,column);

    arm_status returnValue = arm_mat_add_f32(pSrcA_converted,pSrcB_converted,pDst_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pDstOBJ=NumpyArrayFromf32Matrix(pDst_converted);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mat_add_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  arm_matrix_instance_q15 *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  arm_matrix_instance_q15 *pSrcB_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    arm_matrix_instance_q15 *pSrcA_converted = q15MatrixFromNumpy(pSrcA);
    arm_matrix_instance_q15 *pSrcB_converted = q15MatrixFromNumpy(pSrcB);
    uint32_t row = pSrcA_converted->numRows ;
    uint32_t column = pSrcB_converted->numCols ;
    arm_matrix_instance_q15 *pDst_converted = createq15Matrix(row,column);

    arm_status returnValue = arm_mat_add_q15(pSrcA_converted,pSrcB_converted,pDst_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pDstOBJ=NumpyArrayFromq15Matrix(pDst_converted);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mat_add_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  arm_matrix_instance_q31 *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  arm_matrix_instance_q31 *pSrcB_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    arm_matrix_instance_q31 *pSrcA_converted = q31MatrixFromNumpy(pSrcA);
    arm_matrix_instance_q31 *pSrcB_converted = q31MatrixFromNumpy(pSrcB);
    uint32_t row = pSrcA_converted->numRows ;
    uint32_t column = pSrcB_converted->numCols ;
    arm_matrix_instance_q31 *pDst_converted = createq31Matrix(row,column);

    arm_status returnValue = arm_mat_add_q31(pSrcA_converted,pSrcB_converted,pDst_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pDstOBJ=NumpyArrayFromq31Matrix(pDst_converted);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mat_cmplx_mult_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  arm_matrix_instance_f32 *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  arm_matrix_instance_f32 *pSrcB_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    arm_matrix_instance_f32 *pSrcA_converted = f32MatrixFromNumpy(pSrcA);
    arm_matrix_instance_f32 *pSrcB_converted = f32MatrixFromNumpy(pSrcB);
    pSrcA_converted->numCols = pSrcA_converted->numCols / 2;
    pSrcB_converted->numCols = pSrcB_converted->numCols / 2;
    uint32_t row = pSrcA_converted->numRows ;
    uint32_t column = pSrcB_converted->numCols * 2;
    arm_matrix_instance_f32 *pDst_converted = createf32Matrix(row,column);

    arm_status returnValue = arm_mat_cmplx_mult_f32(pSrcA_converted,pSrcB_converted,pDst_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pDstOBJ=NumpyArrayFromf32Matrix(pDst_converted);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mat_cmplx_mult_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  arm_matrix_instance_q15 *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  arm_matrix_instance_q15 *pSrcB_converted=NULL; // input
  PyObject *pScratch=NULL; // input
  q15_t *pScratch_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OOO",&pSrcA,&pSrcB,&pScratch))
  {

    arm_matrix_instance_q15 *pSrcA_converted = q15MatrixFromNumpy(pSrcA);
    arm_matrix_instance_q15 *pSrcB_converted = q15MatrixFromNumpy(pSrcB);
    GETARGUMENT(pScratch,NPY_INT16,int16_t,int16_t);
    pSrcA_converted->numCols = pSrcA_converted->numCols / 2;
    pSrcB_converted->numCols = pSrcB_converted->numCols / 2;
    uint32_t row = pSrcA_converted->numRows ;
    uint32_t column = pSrcB_converted->numCols * 2;
    arm_matrix_instance_q15 *pDst_converted = createq15Matrix(row,column);

    arm_status returnValue = arm_mat_cmplx_mult_q15(pSrcA_converted,pSrcB_converted,pDst_converted,pScratch_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pDstOBJ=NumpyArrayFromq15Matrix(pDst_converted);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    FREEARGUMENT(pScratch_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mat_cmplx_mult_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  arm_matrix_instance_q31 *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  arm_matrix_instance_q31 *pSrcB_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    arm_matrix_instance_q31 *pSrcA_converted = q31MatrixFromNumpy(pSrcA);
    arm_matrix_instance_q31 *pSrcB_converted = q31MatrixFromNumpy(pSrcB);
    pSrcA_converted->numCols = pSrcA_converted->numCols / 2;
    pSrcB_converted->numCols = pSrcB_converted->numCols / 2;
    uint32_t row = pSrcA_converted->numRows ;
    uint32_t column = pSrcB_converted->numCols * 2;
    arm_matrix_instance_q31 *pDst_converted = createq31Matrix(row,column);

    arm_status returnValue = arm_mat_cmplx_mult_q31(pSrcA_converted,pSrcB_converted,pDst_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pDstOBJ=NumpyArrayFromq31Matrix(pDst_converted);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mat_trans_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  arm_matrix_instance_f32 *pSrc_converted=NULL; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    arm_matrix_instance_f32 *pSrc_converted = f32MatrixFromNumpy(pSrc);
    uint32_t row = pSrc_converted->numCols ;
    uint32_t column = pSrc_converted->numRows ;
    arm_matrix_instance_f32 *pDst_converted = createf32Matrix(row,column);

    arm_status returnValue = arm_mat_trans_f32(pSrc_converted,pDst_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pDstOBJ=NumpyArrayFromf32Matrix(pDst_converted);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mat_trans_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  arm_matrix_instance_q15 *pSrc_converted=NULL; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    arm_matrix_instance_q15 *pSrc_converted = q15MatrixFromNumpy(pSrc);
    uint32_t row = pSrc_converted->numCols ;
    uint32_t column = pSrc_converted->numRows ;
    arm_matrix_instance_q15 *pDst_converted = createq15Matrix(row,column);

    arm_status returnValue = arm_mat_trans_q15(pSrc_converted,pDst_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pDstOBJ=NumpyArrayFromq15Matrix(pDst_converted);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mat_trans_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  arm_matrix_instance_q31 *pSrc_converted=NULL; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    arm_matrix_instance_q31 *pSrc_converted = q31MatrixFromNumpy(pSrc);
    uint32_t row = pSrc_converted->numCols ;
    uint32_t column = pSrc_converted->numRows ;
    arm_matrix_instance_q31 *pDst_converted = createq31Matrix(row,column);

    arm_status returnValue = arm_mat_trans_q31(pSrc_converted,pDst_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pDstOBJ=NumpyArrayFromq31Matrix(pDst_converted);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mat_mult_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  arm_matrix_instance_f32 *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  arm_matrix_instance_f32 *pSrcB_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    arm_matrix_instance_f32 *pSrcA_converted = f32MatrixFromNumpy(pSrcA);
    arm_matrix_instance_f32 *pSrcB_converted = f32MatrixFromNumpy(pSrcB);
    uint32_t row = pSrcA_converted->numRows ;
    uint32_t column = pSrcB_converted->numCols ;
    arm_matrix_instance_f32 *pDst_converted = createf32Matrix(row,column);

    arm_status returnValue = arm_mat_mult_f32(pSrcA_converted,pSrcB_converted,pDst_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pDstOBJ=NumpyArrayFromf32Matrix(pDst_converted);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mat_mult_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  arm_matrix_instance_q15 *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  arm_matrix_instance_q15 *pSrcB_converted=NULL; // input
  PyObject *pState=NULL; // input
  q15_t *pState_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OOO",&pSrcA,&pSrcB,&pState))
  {

    arm_matrix_instance_q15 *pSrcA_converted = q15MatrixFromNumpy(pSrcA);
    arm_matrix_instance_q15 *pSrcB_converted = q15MatrixFromNumpy(pSrcB);
    GETARGUMENT(pState,NPY_INT16,int16_t,int16_t);
    uint32_t row = pSrcA_converted->numRows ;
    uint32_t column = pSrcB_converted->numCols ;
    arm_matrix_instance_q15 *pDst_converted = createq15Matrix(row,column);

    arm_status returnValue = arm_mat_mult_q15(pSrcA_converted,pSrcB_converted,pDst_converted,pState_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pDstOBJ=NumpyArrayFromq15Matrix(pDst_converted);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    FREEARGUMENT(pState_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mat_mult_fast_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  arm_matrix_instance_q15 *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  arm_matrix_instance_q15 *pSrcB_converted=NULL; // input
  PyObject *pState=NULL; // input
  q15_t *pState_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OOO",&pSrcA,&pSrcB,&pState))
  {

    arm_matrix_instance_q15 *pSrcA_converted = q15MatrixFromNumpy(pSrcA);
    arm_matrix_instance_q15 *pSrcB_converted = q15MatrixFromNumpy(pSrcB);
    GETARGUMENT(pState,NPY_INT16,int16_t,int16_t);
    uint32_t row = pSrcA_converted->numRows ;
    uint32_t column = pSrcB_converted->numCols ;
    arm_matrix_instance_q15 *pDst_converted = createq15Matrix(row,column);

    arm_status returnValue = arm_mat_mult_fast_q15(pSrcA_converted,pSrcB_converted,pDst_converted,pState_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pDstOBJ=NumpyArrayFromq15Matrix(pDst_converted);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    FREEARGUMENT(pState_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mat_mult_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  arm_matrix_instance_q31 *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  arm_matrix_instance_q31 *pSrcB_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    arm_matrix_instance_q31 *pSrcA_converted = q31MatrixFromNumpy(pSrcA);
    arm_matrix_instance_q31 *pSrcB_converted = q31MatrixFromNumpy(pSrcB);
    uint32_t row = pSrcA_converted->numRows ;
    uint32_t column = pSrcB_converted->numCols ;
    arm_matrix_instance_q31 *pDst_converted = createq31Matrix(row,column);

    arm_status returnValue = arm_mat_mult_q31(pSrcA_converted,pSrcB_converted,pDst_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pDstOBJ=NumpyArrayFromq31Matrix(pDst_converted);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mat_mult_fast_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  arm_matrix_instance_q31 *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  arm_matrix_instance_q31 *pSrcB_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    arm_matrix_instance_q31 *pSrcA_converted = q31MatrixFromNumpy(pSrcA);
    arm_matrix_instance_q31 *pSrcB_converted = q31MatrixFromNumpy(pSrcB);
    uint32_t row = pSrcA_converted->numRows ;
    uint32_t column = pSrcB_converted->numCols ;
    arm_matrix_instance_q31 *pDst_converted = createq31Matrix(row,column);

    arm_status returnValue = arm_mat_mult_fast_q31(pSrcA_converted,pSrcB_converted,pDst_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pDstOBJ=NumpyArrayFromq31Matrix(pDst_converted);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mat_sub_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  arm_matrix_instance_f32 *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  arm_matrix_instance_f32 *pSrcB_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    arm_matrix_instance_f32 *pSrcA_converted = f32MatrixFromNumpy(pSrcA);
    arm_matrix_instance_f32 *pSrcB_converted = f32MatrixFromNumpy(pSrcB);
    uint32_t row = pSrcA_converted->numRows ;
    uint32_t column = pSrcB_converted->numCols ;
    arm_matrix_instance_f32 *pDst_converted = createf32Matrix(row,column);

    arm_status returnValue = arm_mat_sub_f32(pSrcA_converted,pSrcB_converted,pDst_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pDstOBJ=NumpyArrayFromf32Matrix(pDst_converted);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mat_sub_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  arm_matrix_instance_q15 *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  arm_matrix_instance_q15 *pSrcB_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    arm_matrix_instance_q15 *pSrcA_converted = q15MatrixFromNumpy(pSrcA);
    arm_matrix_instance_q15 *pSrcB_converted = q15MatrixFromNumpy(pSrcB);
    uint32_t row = pSrcA_converted->numRows ;
    uint32_t column = pSrcB_converted->numCols ;
    arm_matrix_instance_q15 *pDst_converted = createq15Matrix(row,column);

    arm_status returnValue = arm_mat_sub_q15(pSrcA_converted,pSrcB_converted,pDst_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pDstOBJ=NumpyArrayFromq15Matrix(pDst_converted);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mat_sub_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  arm_matrix_instance_q31 *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  arm_matrix_instance_q31 *pSrcB_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    arm_matrix_instance_q31 *pSrcA_converted = q31MatrixFromNumpy(pSrcA);
    arm_matrix_instance_q31 *pSrcB_converted = q31MatrixFromNumpy(pSrcB);
    uint32_t row = pSrcA_converted->numRows ;
    uint32_t column = pSrcB_converted->numCols ;
    arm_matrix_instance_q31 *pDst_converted = createq31Matrix(row,column);

    arm_status returnValue = arm_mat_sub_q31(pSrcA_converted,pSrcB_converted,pDst_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pDstOBJ=NumpyArrayFromq31Matrix(pDst_converted);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mat_scale_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  arm_matrix_instance_f32 *pSrc_converted=NULL; // input
  float32_t scale; // input

  if (PyArg_ParseTuple(args,"Of",&pSrc,&scale))
  {

    arm_matrix_instance_f32 *pSrc_converted = f32MatrixFromNumpy(pSrc);
    uint32_t row = pSrc_converted->numRows ;
    uint32_t column = pSrc_converted->numCols ;
    arm_matrix_instance_f32 *pDst_converted = createf32Matrix(row,column);

    arm_status returnValue = arm_mat_scale_f32(pSrc_converted,scale,pDst_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pDstOBJ=NumpyArrayFromf32Matrix(pDst_converted);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mat_scale_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  arm_matrix_instance_q15 *pSrc_converted=NULL; // input
  q15_t scaleFract; // input
  int32_t shift; // input

  if (PyArg_ParseTuple(args,"Ohi",&pSrc,&scaleFract,&shift))
  {

    arm_matrix_instance_q15 *pSrc_converted = q15MatrixFromNumpy(pSrc);
    uint32_t row = pSrc_converted->numRows ;
    uint32_t column = pSrc_converted->numCols ;
    arm_matrix_instance_q15 *pDst_converted = createq15Matrix(row,column);

    arm_status returnValue = arm_mat_scale_q15(pSrc_converted,scaleFract,shift,pDst_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pDstOBJ=NumpyArrayFromq15Matrix(pDst_converted);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mat_scale_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  arm_matrix_instance_q31 *pSrc_converted=NULL; // input
  q31_t scaleFract; // input
  int32_t shift; // input

  if (PyArg_ParseTuple(args,"Oii",&pSrc,&scaleFract,&shift))
  {

    arm_matrix_instance_q31 *pSrc_converted = q31MatrixFromNumpy(pSrc);
    uint32_t row = pSrc_converted->numRows ;
    uint32_t column = pSrc_converted->numCols ;
    arm_matrix_instance_q31 *pDst_converted = createq31Matrix(row,column);

    arm_status returnValue = arm_mat_scale_q31(pSrc_converted,scaleFract,shift,pDst_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pDstOBJ=NumpyArrayFromq31Matrix(pDst_converted);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_pid_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  int32_t resetStateFlag; // input

  if (PyArg_ParseTuple(args,"Oi",&S,&resetStateFlag))
  {

    ml_arm_pid_instance_f32Object *selfS = (ml_arm_pid_instance_f32Object *)S;

    arm_pid_init_f32(selfS->instance,resetStateFlag);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_pid_reset_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input

  if (PyArg_ParseTuple(args,"O",&S))
  {

    ml_arm_pid_instance_f32Object *selfS = (ml_arm_pid_instance_f32Object *)S;

    arm_pid_reset_f32(selfS->instance);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_pid_init_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  int32_t resetStateFlag; // input

  if (PyArg_ParseTuple(args,"Oi",&S,&resetStateFlag))
  {

    ml_arm_pid_instance_q31Object *selfS = (ml_arm_pid_instance_q31Object *)S;

    arm_pid_init_q31(selfS->instance,resetStateFlag);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_pid_reset_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input

  if (PyArg_ParseTuple(args,"O",&S))
  {

    ml_arm_pid_instance_q31Object *selfS = (ml_arm_pid_instance_q31Object *)S;

    arm_pid_reset_q31(selfS->instance);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_pid_init_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  int32_t resetStateFlag; // input

  if (PyArg_ParseTuple(args,"Oi",&S,&resetStateFlag))
  {

    ml_arm_pid_instance_q15Object *selfS = (ml_arm_pid_instance_q15Object *)S;

    arm_pid_init_q15(selfS->instance,resetStateFlag);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_pid_reset_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input

  if (PyArg_ParseTuple(args,"O",&S))
  {

    ml_arm_pid_instance_q15Object *selfS = (ml_arm_pid_instance_q15Object *)S;

    arm_pid_reset_q15(selfS->instance);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mult_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q7_t *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  q7_t *pSrcB_converted=NULL; // input
  q7_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    GETARGUMENT(pSrcA,NPY_BYTE,int8_t,q7_t);
    GETARGUMENT(pSrcB,NPY_BYTE,int8_t,q7_t);
    blockSize = arraySizepSrcA ;
    
    pDst=PyMem_Malloc(sizeof(q7_t)*blockSize);


    arm_mult_q7(pSrcA_converted,pSrcB_converted,pDst,blockSize);
 INT8ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mult_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q15_t *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  q15_t *pSrcB_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    GETARGUMENT(pSrcA,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pSrcB,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrcA ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_mult_q15(pSrcA_converted,pSrcB_converted,pDst,blockSize);
 INT16ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mult_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q31_t *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  q31_t *pSrcB_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    GETARGUMENT(pSrcA,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pSrcB,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrcA ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_mult_q31(pSrcA_converted,pSrcB_converted,pDst,blockSize);
 INT32ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mult_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  float32_t *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  float32_t *pSrcB_converted=NULL; // input
  float32_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    GETARGUMENT(pSrcA,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pSrcB,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrcA ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*blockSize);


    arm_mult_f32(pSrcA_converted,pSrcB_converted,pDst,blockSize);
 FLOATARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix2_init_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t fftLen; // input
  uint32_t ifftFlag; // input
  uint32_t bitReverseFlag; // input

  if (PyArg_ParseTuple(args,"Ohii",&S,&fftLen,&ifftFlag,&bitReverseFlag))
  {

    ml_arm_cfft_radix2_instance_q15Object *selfS = (ml_arm_cfft_radix2_instance_q15Object *)S;

    arm_status returnValue = arm_cfft_radix2_init_q15(selfS->instance,fftLen,(uint8_t)ifftFlag,(uint8_t)bitReverseFlag);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix2_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_cfft_radix2_instance_q15Object *selfS = (ml_arm_cfft_radix2_instance_q15Object *)S;
    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);

    arm_cfft_radix2_q15(selfS->instance,pSrc_converted);
    FREEARGUMENT(pSrc_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix4_init_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t fftLen; // input
  uint32_t ifftFlag; // input
  uint32_t bitReverseFlag; // input

  if (PyArg_ParseTuple(args,"Ohii",&S,&fftLen,&ifftFlag,&bitReverseFlag))
  {

    ml_arm_cfft_radix4_instance_q15Object *selfS = (ml_arm_cfft_radix4_instance_q15Object *)S;

    arm_status returnValue = arm_cfft_radix4_init_q15(selfS->instance,fftLen,(uint8_t)ifftFlag,(uint8_t)bitReverseFlag);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix4_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_cfft_radix4_instance_q15Object *selfS = (ml_arm_cfft_radix4_instance_q15Object *)S;
    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);

    arm_cfft_radix4_q15(selfS->instance,pSrc_converted);
    FREEARGUMENT(pSrc_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix2_init_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t fftLen; // input
  uint32_t ifftFlag; // input
  uint32_t bitReverseFlag; // input

  if (PyArg_ParseTuple(args,"Ohii",&S,&fftLen,&ifftFlag,&bitReverseFlag))
  {

    ml_arm_cfft_radix2_instance_q31Object *selfS = (ml_arm_cfft_radix2_instance_q31Object *)S;

    arm_status returnValue = arm_cfft_radix2_init_q31(selfS->instance,fftLen,(uint8_t)ifftFlag,(uint8_t)bitReverseFlag);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix2_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_cfft_radix2_instance_q31Object *selfS = (ml_arm_cfft_radix2_instance_q31Object *)S;
    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);

    arm_cfft_radix2_q31(selfS->instance,pSrc_converted);
    FREEARGUMENT(pSrc_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix4_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_cfft_radix4_instance_q31Object *selfS = (ml_arm_cfft_radix4_instance_q31Object *)S;
    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);

    arm_cfft_radix4_q31(selfS->instance,pSrc_converted);
    FREEARGUMENT(pSrc_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix4_init_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t fftLen; // input
  uint32_t ifftFlag; // input
  uint32_t bitReverseFlag; // input

  if (PyArg_ParseTuple(args,"Ohii",&S,&fftLen,&ifftFlag,&bitReverseFlag))
  {

    ml_arm_cfft_radix4_instance_q31Object *selfS = (ml_arm_cfft_radix4_instance_q31Object *)S;

    arm_status returnValue = arm_cfft_radix4_init_q31(selfS->instance,fftLen,(uint8_t)ifftFlag,(uint8_t)bitReverseFlag);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix2_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t fftLen; // input
  uint32_t ifftFlag; // input
  uint32_t bitReverseFlag; // input

  if (PyArg_ParseTuple(args,"Ohii",&S,&fftLen,&ifftFlag,&bitReverseFlag))
  {

    ml_arm_cfft_radix2_instance_f32Object *selfS = (ml_arm_cfft_radix2_instance_f32Object *)S;

    arm_status returnValue = arm_cfft_radix2_init_f32(selfS->instance,fftLen,(uint8_t)ifftFlag,(uint8_t)bitReverseFlag);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix2_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_cfft_radix2_instance_f32Object *selfS = (ml_arm_cfft_radix2_instance_f32Object *)S;
    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);

    arm_cfft_radix2_f32(selfS->instance,pSrc_converted);
    FREEARGUMENT(pSrc_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix4_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t fftLen; // input
  uint32_t ifftFlag; // input
  uint32_t bitReverseFlag; // input

  if (PyArg_ParseTuple(args,"Ohii",&S,&fftLen,&ifftFlag,&bitReverseFlag))
  {

    ml_arm_cfft_radix4_instance_f32Object *selfS = (ml_arm_cfft_radix4_instance_f32Object *)S;

    arm_status returnValue = arm_cfft_radix4_init_f32(selfS->instance,fftLen,(uint8_t)ifftFlag,(uint8_t)bitReverseFlag);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix4_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_cfft_radix4_instance_f32Object *selfS = (ml_arm_cfft_radix4_instance_f32Object *)S;
    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);

    arm_cfft_radix4_f32(selfS->instance,pSrc_converted);
    FREEARGUMENT(pSrc_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *p1=NULL; // input
  q15_t *p1_converted=NULL; // input
  uint32_t ifftFlag; // input
  uint32_t bitReverseFlag; // input

  if (PyArg_ParseTuple(args,"OOii",&S,&p1,&ifftFlag,&bitReverseFlag))
  {

    ml_arm_cfft_instance_q15Object *selfS = (ml_arm_cfft_instance_q15Object *)S;
    GETARGUMENT(p1,NPY_INT16,int16_t,int16_t);

    arm_cfft_q15(selfS->instance,p1_converted,(uint8_t)ifftFlag,(uint8_t)bitReverseFlag);
 INT16ARRAY1(p1OBJ,2*selfS->instance->fftLen,p1_converted);

    PyObject *pythonResult = Py_BuildValue("O",p1OBJ);

    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *p1=NULL; // input
  q31_t *p1_converted=NULL; // input
  uint32_t ifftFlag; // input
  uint32_t bitReverseFlag; // input

  if (PyArg_ParseTuple(args,"OOii",&S,&p1,&ifftFlag,&bitReverseFlag))
  {

    ml_arm_cfft_instance_q31Object *selfS = (ml_arm_cfft_instance_q31Object *)S;
    GETARGUMENT(p1,NPY_INT32,int32_t,int32_t);

    arm_cfft_q31(selfS->instance,p1_converted,(uint8_t)ifftFlag,(uint8_t)bitReverseFlag);
 INT32ARRAY1(p1OBJ,2*selfS->instance->fftLen,p1_converted);

    PyObject *pythonResult = Py_BuildValue("O",p1OBJ);

    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *p1=NULL; // input
  float32_t *p1_converted=NULL; // input
  uint32_t ifftFlag; // input
  uint32_t bitReverseFlag; // input

  if (PyArg_ParseTuple(args,"OOii",&S,&p1,&ifftFlag,&bitReverseFlag))
  {

    ml_arm_cfft_instance_f32Object *selfS = (ml_arm_cfft_instance_f32Object *)S;
    GETARGUMENT(p1,NPY_DOUBLE,double,float32_t);

    arm_cfft_f32(selfS->instance,p1_converted,(uint8_t)ifftFlag,(uint8_t)bitReverseFlag);
 FLOATARRAY1(p1OBJ,2*selfS->instance->fftLen,p1_converted);

    PyObject *pythonResult = Py_BuildValue("O",p1OBJ);

    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rfft_init_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint32_t fftLenReal; // input
  uint32_t ifftFlagR; // input
  uint32_t bitReverseFlag; // input

  if (PyArg_ParseTuple(args,"Oiii",&S,&fftLenReal,&ifftFlagR,&bitReverseFlag))
  {

    ml_arm_rfft_instance_q15Object *selfS = (ml_arm_rfft_instance_q15Object *)S;

    arm_status returnValue = arm_rfft_init_q15(selfS->instance,fftLenReal,ifftFlagR,bitReverseFlag);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rfft_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  q15_t *pDst=NULL; // output

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_rfft_instance_q15Object *selfS = (ml_arm_rfft_instance_q15Object *)S;
    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    
    pDst=PyMem_Malloc(sizeof(q15_t)*2*selfS->instance->fftLenReal);


    arm_rfft_q15(selfS->instance,pSrc_converted,pDst);
 INT16ARRAY1(pDstOBJ,2*selfS->instance->fftLenReal,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rfft_init_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint32_t fftLenReal; // input
  uint32_t ifftFlagR; // input
  uint32_t bitReverseFlag; // input

  if (PyArg_ParseTuple(args,"Oiii",&S,&fftLenReal,&ifftFlagR,&bitReverseFlag))
  {

    ml_arm_rfft_instance_q31Object *selfS = (ml_arm_rfft_instance_q31Object *)S;

    arm_status returnValue = arm_rfft_init_q31(selfS->instance,fftLenReal,ifftFlagR,bitReverseFlag);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rfft_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  q31_t *pDst=NULL; // output

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_rfft_instance_q31Object *selfS = (ml_arm_rfft_instance_q31Object *)S;
    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    
    pDst=PyMem_Malloc(sizeof(q31_t)*2*selfS->instance->fftLenReal);


    arm_rfft_q31(selfS->instance,pSrc_converted,pDst);
 INT32ARRAY1(pDstOBJ,2*selfS->instance->fftLenReal,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rfft_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *S_CFFT=NULL; // input
  uint32_t fftLenReal; // input
  uint32_t ifftFlagR; // input
  uint32_t bitReverseFlag; // input

  if (PyArg_ParseTuple(args,"OOiii",&S,&S_CFFT,&fftLenReal,&ifftFlagR,&bitReverseFlag))
  {

    ml_arm_rfft_instance_f32Object *selfS = (ml_arm_rfft_instance_f32Object *)S;
    ml_arm_cfft_radix4_instance_f32Object *selfS_CFFT = (ml_arm_cfft_radix4_instance_f32Object *)S_CFFT;

    arm_status returnValue = arm_rfft_init_f32(selfS->instance,selfS_CFFT->instance,fftLenReal,ifftFlagR,bitReverseFlag);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rfft_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  float32_t *pDst=NULL; // output

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_rfft_instance_f32Object *selfS = (ml_arm_rfft_instance_f32Object *)S;
    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    
    pDst=PyMem_Malloc(sizeof(float32_t)*2*selfS->instance->fftLenReal);


    arm_rfft_f32(selfS->instance,pSrc_converted,pDst);
 FLOATARRAY1(pDstOBJ,2*selfS->instance->fftLenReal,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rfft_fast_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t fftLen; // input

  if (PyArg_ParseTuple(args,"Oh",&S,&fftLen))
  {

    ml_arm_rfft_fast_instance_f32Object *selfS = (ml_arm_rfft_fast_instance_f32Object *)S;

    arm_status returnValue = arm_rfft_fast_init_f32(selfS->instance,fftLen);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rfft_32_fast_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input

  if (PyArg_ParseTuple(args,"O",&S))
  {

    ml_arm_rfft_fast_instance_f32Object *selfS = (ml_arm_rfft_fast_instance_f32Object *)S;

    arm_status returnValue = arm_rfft_32_fast_init_f32(selfS->instance);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rfft_64_fast_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input

  if (PyArg_ParseTuple(args,"O",&S))
  {

    ml_arm_rfft_fast_instance_f32Object *selfS = (ml_arm_rfft_fast_instance_f32Object *)S;

    arm_status returnValue = arm_rfft_64_fast_init_f32(selfS->instance);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rfft_128_fast_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input

  if (PyArg_ParseTuple(args,"O",&S))
  {

    ml_arm_rfft_fast_instance_f32Object *selfS = (ml_arm_rfft_fast_instance_f32Object *)S;

    arm_status returnValue = arm_rfft_128_fast_init_f32(selfS->instance);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rfft_256_fast_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input

  if (PyArg_ParseTuple(args,"O",&S))
  {

    ml_arm_rfft_fast_instance_f32Object *selfS = (ml_arm_rfft_fast_instance_f32Object *)S;

    arm_status returnValue = arm_rfft_256_fast_init_f32(selfS->instance);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rfft_512_fast_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input

  if (PyArg_ParseTuple(args,"O",&S))
  {

    ml_arm_rfft_fast_instance_f32Object *selfS = (ml_arm_rfft_fast_instance_f32Object *)S;

    arm_status returnValue = arm_rfft_512_fast_init_f32(selfS->instance);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rfft_1024_fast_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input

  if (PyArg_ParseTuple(args,"O",&S))
  {

    ml_arm_rfft_fast_instance_f32Object *selfS = (ml_arm_rfft_fast_instance_f32Object *)S;

    arm_status returnValue = arm_rfft_1024_fast_init_f32(selfS->instance);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rfft_2048_fast_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input

  if (PyArg_ParseTuple(args,"O",&S))
  {

    ml_arm_rfft_fast_instance_f32Object *selfS = (ml_arm_rfft_fast_instance_f32Object *)S;

    arm_status returnValue = arm_rfft_2048_fast_init_f32(selfS->instance);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rfft_4096_fast_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input

  if (PyArg_ParseTuple(args,"O",&S))
  {

    ml_arm_rfft_fast_instance_f32Object *selfS = (ml_arm_rfft_fast_instance_f32Object *)S;

    arm_status returnValue = arm_rfft_4096_fast_init_f32(selfS->instance);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rfft_fast_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *p=NULL; // input
  float32_t *p_converted=NULL; // input
  float32_t *pOut=NULL; // output
  uint32_t ifftFlag; // input

  if (PyArg_ParseTuple(args,"OOi",&S,&p,&ifftFlag))
  {

    ml_arm_rfft_fast_instance_f32Object *selfS = (ml_arm_rfft_fast_instance_f32Object *)S;
    GETARGUMENT(p,NPY_DOUBLE,double,float32_t);
    
    pOut=PyMem_Malloc(sizeof(float32_t)*2*selfS->instance->fftLenRFFT);


    arm_rfft_fast_f32(selfS->instance,p_converted,pOut,(uint8_t)ifftFlag);
 FLOATARRAY1(pOutOBJ,2*selfS->instance->fftLenRFFT,pOut);

    PyObject *pythonResult = Py_BuildValue("O",pOutOBJ);

    FREEARGUMENT(p_converted);
    Py_DECREF(pOutOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_dct4_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *S_RFFT=NULL; // input
  PyObject *S_CFFT=NULL; // input
  uint16_t N; // input
  uint16_t Nby2; // input
  float32_t normalize; // input

  if (PyArg_ParseTuple(args,"OOOhhf",&S,&S_RFFT,&S_CFFT,&N,&Nby2,&normalize))
  {

    ml_arm_dct4_instance_f32Object *selfS = (ml_arm_dct4_instance_f32Object *)S;
    ml_arm_rfft_instance_f32Object *selfS_RFFT = (ml_arm_rfft_instance_f32Object *)S_RFFT;
    ml_arm_cfft_radix4_instance_f32Object *selfS_CFFT = (ml_arm_cfft_radix4_instance_f32Object *)S_CFFT;
    uint32_t outputLength = selfS->instance->N ;

    arm_status returnValue = arm_dct4_init_f32(selfS->instance,selfS_RFFT->instance,selfS_CFFT->instance,N,Nby2,normalize);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_dct4_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pState=NULL; // input
  float32_t *pState_converted=NULL; // input
  PyObject *pInlineBuffer=NULL; // input
  float32_t *pInlineBuffer_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OOO",&S,&pState,&pInlineBuffer))
  {

    ml_arm_dct4_instance_f32Object *selfS = (ml_arm_dct4_instance_f32Object *)S;
    GETARGUMENT(pState,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pInlineBuffer,NPY_DOUBLE,double,float32_t);
    uint32_t outputLength = selfS->instance->N ;

    arm_dct4_f32(selfS->instance,pState_converted,pInlineBuffer_converted);
 FLOATARRAY1(pInlineBufferOBJ,outputLength,pInlineBuffer_converted);

    PyObject *pythonResult = Py_BuildValue("O",pInlineBufferOBJ);

    FREEARGUMENT(pState_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_dct4_init_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *S_RFFT=NULL; // input
  PyObject *S_CFFT=NULL; // input
  uint16_t N; // input
  uint16_t Nby2; // input
  q31_t normalize; // input

  if (PyArg_ParseTuple(args,"OOOhhi",&S,&S_RFFT,&S_CFFT,&N,&Nby2,&normalize))
  {

    ml_arm_dct4_instance_q31Object *selfS = (ml_arm_dct4_instance_q31Object *)S;
    ml_arm_rfft_instance_q31Object *selfS_RFFT = (ml_arm_rfft_instance_q31Object *)S_RFFT;
    ml_arm_cfft_radix4_instance_q31Object *selfS_CFFT = (ml_arm_cfft_radix4_instance_q31Object *)S_CFFT;
    uint32_t outputLength = selfS->instance->N ;

    arm_status returnValue = arm_dct4_init_q31(selfS->instance,selfS_RFFT->instance,selfS_CFFT->instance,N,Nby2,normalize);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_dct4_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pState=NULL; // input
  q31_t *pState_converted=NULL; // input
  PyObject *pInlineBuffer=NULL; // input
  q31_t *pInlineBuffer_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OOO",&S,&pState,&pInlineBuffer))
  {

    ml_arm_dct4_instance_q31Object *selfS = (ml_arm_dct4_instance_q31Object *)S;
    GETARGUMENT(pState,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pInlineBuffer,NPY_INT32,int32_t,int32_t);
    uint32_t outputLength = selfS->instance->N ;

    arm_dct4_q31(selfS->instance,pState_converted,pInlineBuffer_converted);
 INT32ARRAY1(pInlineBufferOBJ,outputLength,pInlineBuffer_converted);

    PyObject *pythonResult = Py_BuildValue("O",pInlineBufferOBJ);

    FREEARGUMENT(pState_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_dct4_init_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *S_RFFT=NULL; // input
  PyObject *S_CFFT=NULL; // input
  uint16_t N; // input
  uint16_t Nby2; // input
  q15_t normalize; // input

  if (PyArg_ParseTuple(args,"OOOhhh",&S,&S_RFFT,&S_CFFT,&N,&Nby2,&normalize))
  {

    ml_arm_dct4_instance_q15Object *selfS = (ml_arm_dct4_instance_q15Object *)S;
    ml_arm_rfft_instance_q15Object *selfS_RFFT = (ml_arm_rfft_instance_q15Object *)S_RFFT;
    ml_arm_cfft_radix4_instance_q15Object *selfS_CFFT = (ml_arm_cfft_radix4_instance_q15Object *)S_CFFT;
    uint32_t outputLength = selfS->instance->N ;

    arm_status returnValue = arm_dct4_init_q15(selfS->instance,selfS_RFFT->instance,selfS_CFFT->instance,N,Nby2,normalize);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_dct4_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pState=NULL; // input
  q15_t *pState_converted=NULL; // input
  PyObject *pInlineBuffer=NULL; // input
  q15_t *pInlineBuffer_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OOO",&S,&pState,&pInlineBuffer))
  {

    ml_arm_dct4_instance_q15Object *selfS = (ml_arm_dct4_instance_q15Object *)S;
    GETARGUMENT(pState,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pInlineBuffer,NPY_INT16,int16_t,int16_t);
    uint32_t outputLength = selfS->instance->N ;

    arm_dct4_q15(selfS->instance,pState_converted,pInlineBuffer_converted);
 INT16ARRAY1(pInlineBufferOBJ,outputLength,pInlineBuffer_converted);

    PyObject *pythonResult = Py_BuildValue("O",pInlineBufferOBJ);

    FREEARGUMENT(pState_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_add_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  float32_t *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  float32_t *pSrcB_converted=NULL; // input
  float32_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    GETARGUMENT(pSrcA,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pSrcB,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrcA ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*blockSize);


    arm_add_f32(pSrcA_converted,pSrcB_converted,pDst,blockSize);
 FLOATARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_add_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q7_t *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  q7_t *pSrcB_converted=NULL; // input
  q7_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    GETARGUMENT(pSrcA,NPY_BYTE,int8_t,q7_t);
    GETARGUMENT(pSrcB,NPY_BYTE,int8_t,q7_t);
    blockSize = arraySizepSrcA ;
    
    pDst=PyMem_Malloc(sizeof(q7_t)*blockSize);


    arm_add_q7(pSrcA_converted,pSrcB_converted,pDst,blockSize);
 INT8ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_add_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q15_t *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  q15_t *pSrcB_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    GETARGUMENT(pSrcA,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pSrcB,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrcA ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_add_q15(pSrcA_converted,pSrcB_converted,pDst,blockSize);
 INT16ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_add_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q31_t *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  q31_t *pSrcB_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    GETARGUMENT(pSrcA,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pSrcB,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrcA ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_add_q31(pSrcA_converted,pSrcB_converted,pDst,blockSize);
 INT32ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_sub_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  float32_t *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  float32_t *pSrcB_converted=NULL; // input
  float32_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    GETARGUMENT(pSrcA,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pSrcB,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrcA ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*blockSize);


    arm_sub_f32(pSrcA_converted,pSrcB_converted,pDst,blockSize);
 FLOATARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_sub_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q7_t *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  q7_t *pSrcB_converted=NULL; // input
  q7_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    GETARGUMENT(pSrcA,NPY_BYTE,int8_t,q7_t);
    GETARGUMENT(pSrcB,NPY_BYTE,int8_t,q7_t);
    blockSize = arraySizepSrcA ;
    
    pDst=PyMem_Malloc(sizeof(q7_t)*blockSize);


    arm_sub_q7(pSrcA_converted,pSrcB_converted,pDst,blockSize);
 INT8ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_sub_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q15_t *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  q15_t *pSrcB_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    GETARGUMENT(pSrcA,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pSrcB,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrcA ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_sub_q15(pSrcA_converted,pSrcB_converted,pDst,blockSize);
 INT16ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_sub_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q31_t *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  q31_t *pSrcB_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    GETARGUMENT(pSrcA,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pSrcB,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrcA ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_sub_q31(pSrcA_converted,pSrcB_converted,pDst,blockSize);
 INT32ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_scale_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  float32_t scale; // input
  float32_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"Of",&pSrc,&scale))
  {

    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*blockSize);


    arm_scale_f32(pSrc_converted,scale,pDst,blockSize);
 FLOATARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_scale_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q7_t *pSrc_converted=NULL; // input
  int32_t scaleFract; // input
  int32_t shift; // input
  q7_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"Oii",&pSrc,&scaleFract,&shift))
  {

    GETARGUMENT(pSrc,NPY_BYTE,int8_t,q7_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q7_t)*blockSize);


    arm_scale_q7(pSrc_converted,(q7_t)scaleFract,(int8_t)shift,pDst,blockSize);
 INT8ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_scale_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  q15_t scaleFract; // input
  int32_t shift; // input
  q15_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"Ohi",&pSrc,&scaleFract,&shift))
  {

    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_scale_q15(pSrc_converted,scaleFract,(int8_t)shift,pDst,blockSize);
 INT16ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_scale_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  q31_t scaleFract; // input
  int32_t shift; // input
  q31_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"Oii",&pSrc,&scaleFract,&shift))
  {

    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_scale_q31(pSrc_converted,scaleFract,(int8_t)shift,pDst,blockSize);
 INT32ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_abs_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q7_t *pSrc_converted=NULL; // input
  q7_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_BYTE,int8_t,q7_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q7_t)*blockSize);


    arm_abs_q7(pSrc_converted,pDst,blockSize);
 INT8ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_abs_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  float32_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*blockSize);


    arm_abs_f32(pSrc_converted,pDst,blockSize);
 FLOATARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_abs_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_abs_q15(pSrc_converted,pDst,blockSize);
 INT16ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_abs_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_abs_q31(pSrc_converted,pDst,blockSize);
 INT32ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_dot_prod_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  float32_t *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  float32_t *pSrcB_converted=NULL; // input
  uint32_t blockSize; // input
  float32_t *result=NULL; // output

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    GETARGUMENT(pSrcA,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pSrcB,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrcA ;
    
    result=PyMem_Malloc(sizeof(float32_t)*1);


    arm_dot_prod_f32(pSrcA_converted,pSrcB_converted,blockSize,result);
    PyObject* resultOBJ=Py_BuildValue("f",*result);

    PyObject *pythonResult = Py_BuildValue("O",resultOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(resultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_dot_prod_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q7_t *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  q7_t *pSrcB_converted=NULL; // input
  uint32_t blockSize; // input
  q31_t *result=NULL; // output

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    GETARGUMENT(pSrcA,NPY_BYTE,int8_t,q7_t);
    GETARGUMENT(pSrcB,NPY_BYTE,int8_t,q7_t);
    blockSize = arraySizepSrcA ;
    
    result=PyMem_Malloc(sizeof(q31_t)*1);


    arm_dot_prod_q7(pSrcA_converted,pSrcB_converted,blockSize,result);
    PyObject* resultOBJ=Py_BuildValue("i",*result);

    PyObject *pythonResult = Py_BuildValue("O",resultOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(resultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_dot_prod_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q15_t *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  q15_t *pSrcB_converted=NULL; // input
  uint32_t blockSize; // input
  q63_t *result=NULL; // output

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    GETARGUMENT(pSrcA,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pSrcB,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrcA ;
    
    result=PyMem_Malloc(sizeof(q63_t)*1);


    arm_dot_prod_q15(pSrcA_converted,pSrcB_converted,blockSize,result);
    PyObject* resultOBJ=Py_BuildValue("L",*result);

    PyObject *pythonResult = Py_BuildValue("O",resultOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(resultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_dot_prod_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q31_t *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  q31_t *pSrcB_converted=NULL; // input
  uint32_t blockSize; // input
  q63_t *result=NULL; // output

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    GETARGUMENT(pSrcA,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pSrcB,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrcA ;
    
    result=PyMem_Malloc(sizeof(q63_t)*1);


    arm_dot_prod_q31(pSrcA_converted,pSrcB_converted,blockSize,result);
    PyObject* resultOBJ=Py_BuildValue("L",*result);

    PyObject *pythonResult = Py_BuildValue("O",resultOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(resultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_shift_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q7_t *pSrc_converted=NULL; // input
  int32_t shiftBits; // input
  q7_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"Oi",&pSrc,&shiftBits))
  {

    GETARGUMENT(pSrc,NPY_BYTE,int8_t,q7_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q7_t)*blockSize);


    arm_shift_q7(pSrc_converted,(int8_t)shiftBits,pDst,blockSize);
 INT8ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_shift_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  int32_t shiftBits; // input
  q15_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"Oi",&pSrc,&shiftBits))
  {

    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_shift_q15(pSrc_converted,(int8_t)shiftBits,pDst,blockSize);
 INT16ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_shift_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  int32_t shiftBits; // input
  q31_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"Oi",&pSrc,&shiftBits))
  {

    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_shift_q31(pSrc_converted,(int8_t)shiftBits,pDst,blockSize);
 INT32ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_offset_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  float32_t offset; // input
  float32_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"Of",&pSrc,&offset))
  {

    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*blockSize);


    arm_offset_f32(pSrc_converted,offset,pDst,blockSize);
 FLOATARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_offset_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q7_t *pSrc_converted=NULL; // input
  int32_t offset; // input
  q7_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"Oi",&pSrc,&offset))
  {

    GETARGUMENT(pSrc,NPY_BYTE,int8_t,q7_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q7_t)*blockSize);


    arm_offset_q7(pSrc_converted,(q7_t)offset,pDst,blockSize);
 INT8ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_offset_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  q15_t offset; // input
  q15_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"Oh",&pSrc,&offset))
  {

    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_offset_q15(pSrc_converted,offset,pDst,blockSize);
 INT16ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_offset_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  q31_t offset; // input
  q31_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"Oi",&pSrc,&offset))
  {

    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_offset_q31(pSrc_converted,offset,pDst,blockSize);
 INT32ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_negate_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  float32_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*blockSize);


    arm_negate_f32(pSrc_converted,pDst,blockSize);
 FLOATARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_negate_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q7_t *pSrc_converted=NULL; // input
  q7_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_BYTE,int8_t,q7_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q7_t)*blockSize);


    arm_negate_q7(pSrc_converted,pDst,blockSize);
 INT8ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_negate_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_negate_q15(pSrc_converted,pDst,blockSize);
 INT16ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_negate_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_negate_q31(pSrc_converted,pDst,blockSize);
 INT32ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_copy_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  float32_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*blockSize);


    arm_copy_f32(pSrc_converted,pDst,blockSize);
 FLOATARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_copy_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q7_t *pSrc_converted=NULL; // input
  q7_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_BYTE,int8_t,q7_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q7_t)*blockSize);


    arm_copy_q7(pSrc_converted,pDst,blockSize);
 INT8ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_copy_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_copy_q15(pSrc_converted,pDst,blockSize);
 INT16ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_copy_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_copy_q31(pSrc_converted,pDst,blockSize);
 INT32ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_conv_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  float32_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  float32_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  float32_t *pDst=NULL; // output

  if (PyArg_ParseTuple(args,"OiOi",&pSrcA,&srcALen,&pSrcB,&srcBLen))
  {

    GETARGUMENT(pSrcA,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pSrcB,NPY_DOUBLE,double,float32_t);
    uint32_t outputLength = srcALen + srcBLen - 1 ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*outputLength);


    arm_conv_f32(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst);
 FLOATARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_conv_opt_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q15_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q15_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q15_t *pDst=NULL; // output
  PyObject *pScratch1=NULL; // input
  q15_t *pScratch1_converted=NULL; // input
  PyObject *pScratch2=NULL; // input
  q15_t *pScratch2_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OiOiOO",&pSrcA,&srcALen,&pSrcB,&srcBLen,&pScratch1,&pScratch2))
  {

    GETARGUMENT(pSrcA,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pSrcB,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pScratch1,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pScratch2,NPY_INT16,int16_t,int16_t);
    uint32_t outputLength = srcALen + srcBLen - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*outputLength);


    arm_conv_opt_q15(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst,pScratch1_converted,pScratch2_converted);
 INT16ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    FREEARGUMENT(pScratch1_converted);
    FREEARGUMENT(pScratch2_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_conv_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q15_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q15_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q15_t *pDst=NULL; // output

  if (PyArg_ParseTuple(args,"OiOi",&pSrcA,&srcALen,&pSrcB,&srcBLen))
  {

    GETARGUMENT(pSrcA,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pSrcB,NPY_INT16,int16_t,int16_t);
    uint32_t outputLength = srcALen + srcBLen - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*outputLength);


    arm_conv_q15(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst);
 INT16ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_conv_fast_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q15_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q15_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q15_t *pDst=NULL; // output

  if (PyArg_ParseTuple(args,"OiOi",&pSrcA,&srcALen,&pSrcB,&srcBLen))
  {

    GETARGUMENT(pSrcA,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pSrcB,NPY_INT16,int16_t,int16_t);
    uint32_t outputLength = srcALen + srcBLen - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*outputLength);


    arm_conv_fast_q15(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst);
 INT16ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_conv_fast_opt_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q15_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q15_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q15_t *pDst=NULL; // output
  PyObject *pScratch1=NULL; // input
  q15_t *pScratch1_converted=NULL; // input
  PyObject *pScratch2=NULL; // input
  q15_t *pScratch2_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OiOiOO",&pSrcA,&srcALen,&pSrcB,&srcBLen,&pScratch1,&pScratch2))
  {

    GETARGUMENT(pSrcA,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pSrcB,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pScratch1,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pScratch2,NPY_INT16,int16_t,int16_t);
    uint32_t outputLength = srcALen + srcBLen - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*outputLength);


    arm_conv_fast_opt_q15(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst,pScratch1_converted,pScratch2_converted);
 INT16ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    FREEARGUMENT(pScratch1_converted);
    FREEARGUMENT(pScratch2_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_conv_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q31_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q31_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q31_t *pDst=NULL; // output

  if (PyArg_ParseTuple(args,"OiOi",&pSrcA,&srcALen,&pSrcB,&srcBLen))
  {

    GETARGUMENT(pSrcA,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pSrcB,NPY_INT32,int32_t,int32_t);
    uint32_t outputLength = srcALen + srcBLen - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*outputLength);


    arm_conv_q31(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst);
 INT32ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_conv_fast_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q31_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q31_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q31_t *pDst=NULL; // output

  if (PyArg_ParseTuple(args,"OiOi",&pSrcA,&srcALen,&pSrcB,&srcBLen))
  {

    GETARGUMENT(pSrcA,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pSrcB,NPY_INT32,int32_t,int32_t);
    uint32_t outputLength = srcALen + srcBLen - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*outputLength);


    arm_conv_fast_q31(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst);
 INT32ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_conv_opt_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q7_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q7_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q7_t *pDst=NULL; // output
  PyObject *pScratch1=NULL; // input
  q15_t *pScratch1_converted=NULL; // input
  PyObject *pScratch2=NULL; // input
  q15_t *pScratch2_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OiOiOO",&pSrcA,&srcALen,&pSrcB,&srcBLen,&pScratch1,&pScratch2))
  {

    GETARGUMENT(pSrcA,NPY_BYTE,int8_t,q7_t);
    GETARGUMENT(pSrcB,NPY_BYTE,int8_t,q7_t);
    GETARGUMENT(pScratch1,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pScratch2,NPY_INT16,int16_t,int16_t);
    uint32_t outputLength = srcALen + srcBLen - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q7_t)*outputLength);


    arm_conv_opt_q7(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst,pScratch1_converted,pScratch2_converted);
 INT8ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    FREEARGUMENT(pScratch1_converted);
    FREEARGUMENT(pScratch2_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_conv_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q7_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q7_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q7_t *pDst=NULL; // output

  if (PyArg_ParseTuple(args,"OiOi",&pSrcA,&srcALen,&pSrcB,&srcBLen))
  {

    GETARGUMENT(pSrcA,NPY_BYTE,int8_t,q7_t);
    GETARGUMENT(pSrcB,NPY_BYTE,int8_t,q7_t);
    uint32_t outputLength = srcALen + srcBLen - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q7_t)*outputLength);


    arm_conv_q7(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst);
 INT8ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_conv_partial_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  float32_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  float32_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  float32_t *pDst=NULL; // output
  uint32_t firstIndex; // input
  uint32_t numPoints; // input

  if (PyArg_ParseTuple(args,"OiOiii",&pSrcA,&srcALen,&pSrcB,&srcBLen,&firstIndex,&numPoints))
  {

    GETARGUMENT(pSrcA,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pSrcB,NPY_DOUBLE,double,float32_t);
    uint32_t outputLength = srcALen + srcBLen - 1 ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*outputLength);


    arm_status returnValue = arm_conv_partial_f32(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst,firstIndex,numPoints);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
 FLOATARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_conv_partial_opt_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q15_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q15_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q15_t *pDst=NULL; // output
  uint32_t firstIndex; // input
  uint32_t numPoints; // input
  PyObject *pScratch1=NULL; // input
  q15_t *pScratch1_converted=NULL; // input
  PyObject *pScratch2=NULL; // input
  q15_t *pScratch2_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OiOiiiOO",&pSrcA,&srcALen,&pSrcB,&srcBLen,&firstIndex,&numPoints,&pScratch1,&pScratch2))
  {

    GETARGUMENT(pSrcA,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pSrcB,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pScratch1,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pScratch2,NPY_INT16,int16_t,int16_t);
    uint32_t outputLength = srcALen + srcBLen - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*outputLength);


    arm_status returnValue = arm_conv_partial_opt_q15(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst,firstIndex,numPoints,pScratch1_converted,pScratch2_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
 INT16ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    FREEARGUMENT(pScratch1_converted);
    FREEARGUMENT(pScratch2_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_conv_partial_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q15_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q15_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q15_t *pDst=NULL; // output
  uint32_t firstIndex; // input
  uint32_t numPoints; // input

  if (PyArg_ParseTuple(args,"OiOiii",&pSrcA,&srcALen,&pSrcB,&srcBLen,&firstIndex,&numPoints))
  {

    GETARGUMENT(pSrcA,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pSrcB,NPY_INT16,int16_t,int16_t);
    uint32_t outputLength = srcALen + srcBLen - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*outputLength);


    arm_status returnValue = arm_conv_partial_q15(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst,firstIndex,numPoints);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
 INT16ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_conv_partial_fast_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q15_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q15_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q15_t *pDst=NULL; // output
  uint32_t firstIndex; // input
  uint32_t numPoints; // input

  if (PyArg_ParseTuple(args,"OiOiii",&pSrcA,&srcALen,&pSrcB,&srcBLen,&firstIndex,&numPoints))
  {

    GETARGUMENT(pSrcA,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pSrcB,NPY_INT16,int16_t,int16_t);
    uint32_t outputLength = srcALen + srcBLen - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*outputLength);


    arm_status returnValue = arm_conv_partial_fast_q15(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst,firstIndex,numPoints);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
 INT16ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_conv_partial_fast_opt_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q15_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q15_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q15_t *pDst=NULL; // output
  uint32_t firstIndex; // input
  uint32_t numPoints; // input
  PyObject *pScratch1=NULL; // input
  q15_t *pScratch1_converted=NULL; // input
  PyObject *pScratch2=NULL; // input
  q15_t *pScratch2_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OiOiiiOO",&pSrcA,&srcALen,&pSrcB,&srcBLen,&firstIndex,&numPoints,&pScratch1,&pScratch2))
  {

    GETARGUMENT(pSrcA,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pSrcB,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pScratch1,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pScratch2,NPY_INT16,int16_t,int16_t);
    uint32_t outputLength = srcALen + srcBLen - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*outputLength);


    arm_status returnValue = arm_conv_partial_fast_opt_q15(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst,firstIndex,numPoints,pScratch1_converted,pScratch2_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
 INT16ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    FREEARGUMENT(pScratch1_converted);
    FREEARGUMENT(pScratch2_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_conv_partial_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q31_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q31_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q31_t *pDst=NULL; // output
  uint32_t firstIndex; // input
  uint32_t numPoints; // input

  if (PyArg_ParseTuple(args,"OiOiii",&pSrcA,&srcALen,&pSrcB,&srcBLen,&firstIndex,&numPoints))
  {

    GETARGUMENT(pSrcA,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pSrcB,NPY_INT32,int32_t,int32_t);
    uint32_t outputLength = srcALen + srcBLen - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*outputLength);


    arm_status returnValue = arm_conv_partial_q31(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst,firstIndex,numPoints);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
 INT32ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_conv_partial_fast_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q31_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q31_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q31_t *pDst=NULL; // output
  uint32_t firstIndex; // input
  uint32_t numPoints; // input

  if (PyArg_ParseTuple(args,"OiOiii",&pSrcA,&srcALen,&pSrcB,&srcBLen,&firstIndex,&numPoints))
  {

    GETARGUMENT(pSrcA,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pSrcB,NPY_INT32,int32_t,int32_t);
    uint32_t outputLength = srcALen + srcBLen - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*outputLength);


    arm_status returnValue = arm_conv_partial_fast_q31(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst,firstIndex,numPoints);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
 INT32ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_conv_partial_opt_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q7_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q7_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q7_t *pDst=NULL; // output
  uint32_t firstIndex; // input
  uint32_t numPoints; // input
  PyObject *pScratch1=NULL; // input
  q15_t *pScratch1_converted=NULL; // input
  PyObject *pScratch2=NULL; // input
  q15_t *pScratch2_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OiOiiiOO",&pSrcA,&srcALen,&pSrcB,&srcBLen,&firstIndex,&numPoints,&pScratch1,&pScratch2))
  {

    GETARGUMENT(pSrcA,NPY_BYTE,int8_t,q7_t);
    GETARGUMENT(pSrcB,NPY_BYTE,int8_t,q7_t);
    GETARGUMENT(pScratch1,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pScratch2,NPY_INT16,int16_t,int16_t);
    uint32_t outputLength = srcALen + srcBLen - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q7_t)*outputLength);


    arm_status returnValue = arm_conv_partial_opt_q7(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst,firstIndex,numPoints,pScratch1_converted,pScratch2_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
 INT8ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    FREEARGUMENT(pScratch1_converted);
    FREEARGUMENT(pScratch2_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_conv_partial_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q7_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q7_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q7_t *pDst=NULL; // output
  uint32_t firstIndex; // input
  uint32_t numPoints; // input

  if (PyArg_ParseTuple(args,"OiOiii",&pSrcA,&srcALen,&pSrcB,&srcBLen,&firstIndex,&numPoints))
  {

    GETARGUMENT(pSrcA,NPY_BYTE,int8_t,q7_t);
    GETARGUMENT(pSrcB,NPY_BYTE,int8_t,q7_t);
    uint32_t outputLength = srcALen + srcBLen - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q7_t)*outputLength);


    arm_status returnValue = arm_conv_partial_q7(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst,firstIndex,numPoints);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
 INT8ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_decimate_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  float32_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_fir_decimate_instance_f32Object *selfS = (ml_arm_fir_decimate_instance_f32Object *)S;
    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*blockSize);


    arm_fir_decimate_f32(selfS->instance,pSrc_converted,pDst,blockSize);
 FLOATARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_decimate_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numTaps; // input
  uint32_t M; // input
  PyObject *pCoeffs=NULL; // input
  float32_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  float32_t *pState_converted=NULL; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OhiOO",&S,&numTaps,&M,&pCoeffs,&pState))
  {

    ml_arm_fir_decimate_instance_f32Object *selfS = (ml_arm_fir_decimate_instance_f32Object *)S;
    GETARGUMENT(pCoeffs,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pState,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepState - arraySizepCoeffs + 1;

    arm_status returnValue = arm_fir_decimate_init_f32(selfS->instance,numTaps,(uint8_t)M,pCoeffs_converted,pState_converted,blockSize);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_decimate_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_fir_decimate_instance_q15Object *selfS = (ml_arm_fir_decimate_instance_q15Object *)S;
    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_fir_decimate_q15(selfS->instance,pSrc_converted,pDst,blockSize);
 INT16ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_decimate_fast_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_fir_decimate_instance_q15Object *selfS = (ml_arm_fir_decimate_instance_q15Object *)S;
    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_fir_decimate_fast_q15(selfS->instance,pSrc_converted,pDst,blockSize);
 INT16ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_decimate_init_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numTaps; // input
  uint32_t M; // input
  PyObject *pCoeffs=NULL; // input
  q15_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  q15_t *pState_converted=NULL; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OhiOO",&S,&numTaps,&M,&pCoeffs,&pState))
  {

    ml_arm_fir_decimate_instance_q15Object *selfS = (ml_arm_fir_decimate_instance_q15Object *)S;
    GETARGUMENT(pCoeffs,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pState,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepState - arraySizepCoeffs + 1;

    arm_status returnValue = arm_fir_decimate_init_q15(selfS->instance,numTaps,(uint8_t)M,pCoeffs_converted,pState_converted,blockSize);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_decimate_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_fir_decimate_instance_q31Object *selfS = (ml_arm_fir_decimate_instance_q31Object *)S;
    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_fir_decimate_q31(selfS->instance,pSrc_converted,pDst,blockSize);
 INT32ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_decimate_fast_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_fir_decimate_instance_q31Object *selfS = (ml_arm_fir_decimate_instance_q31Object *)S;
    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_fir_decimate_fast_q31(selfS->instance,pSrc_converted,pDst,blockSize);
 INT32ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_decimate_init_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numTaps; // input
  uint32_t M; // input
  PyObject *pCoeffs=NULL; // input
  q31_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  q31_t *pState_converted=NULL; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OhiOO",&S,&numTaps,&M,&pCoeffs,&pState))
  {

    ml_arm_fir_decimate_instance_q31Object *selfS = (ml_arm_fir_decimate_instance_q31Object *)S;
    GETARGUMENT(pCoeffs,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pState,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepState - arraySizepCoeffs + 1;

    arm_status returnValue = arm_fir_decimate_init_q31(selfS->instance,numTaps,(uint8_t)M,pCoeffs_converted,pState_converted,blockSize);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_interpolate_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_fir_interpolate_instance_q15Object *selfS = (ml_arm_fir_interpolate_instance_q15Object *)S;
    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_fir_interpolate_q15(selfS->instance,pSrc_converted,pDst,blockSize);
 INT16ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_interpolate_init_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint32_t L; // input
  uint16_t numTaps; // input
  PyObject *pCoeffs=NULL; // input
  q15_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  q15_t *pState_converted=NULL; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OihOO",&S,&L,&numTaps,&pCoeffs,&pState))
  {

    ml_arm_fir_interpolate_instance_q15Object *selfS = (ml_arm_fir_interpolate_instance_q15Object *)S;
    GETARGUMENT(pCoeffs,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pState,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepState - arraySizepCoeffs + 1;

    arm_status returnValue = arm_fir_interpolate_init_q15(selfS->instance,(uint8_t)L,numTaps,pCoeffs_converted,pState_converted,blockSize);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_interpolate_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_fir_interpolate_instance_q31Object *selfS = (ml_arm_fir_interpolate_instance_q31Object *)S;
    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_fir_interpolate_q31(selfS->instance,pSrc_converted,pDst,blockSize);
 INT32ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_interpolate_init_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint32_t L; // input
  uint16_t numTaps; // input
  PyObject *pCoeffs=NULL; // input
  q31_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  q31_t *pState_converted=NULL; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OihOO",&S,&L,&numTaps,&pCoeffs,&pState))
  {

    ml_arm_fir_interpolate_instance_q31Object *selfS = (ml_arm_fir_interpolate_instance_q31Object *)S;
    GETARGUMENT(pCoeffs,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pState,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepState - arraySizepCoeffs + 1;

    arm_status returnValue = arm_fir_interpolate_init_q31(selfS->instance,(uint8_t)L,numTaps,pCoeffs_converted,pState_converted,blockSize);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_interpolate_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  float32_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_fir_interpolate_instance_f32Object *selfS = (ml_arm_fir_interpolate_instance_f32Object *)S;
    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*blockSize);


    arm_fir_interpolate_f32(selfS->instance,pSrc_converted,pDst,blockSize);
 FLOATARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_interpolate_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint32_t L; // input
  uint16_t numTaps; // input
  PyObject *pCoeffs=NULL; // input
  float32_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  float32_t *pState_converted=NULL; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OihOO",&S,&L,&numTaps,&pCoeffs,&pState))
  {

    ml_arm_fir_interpolate_instance_f32Object *selfS = (ml_arm_fir_interpolate_instance_f32Object *)S;
    GETARGUMENT(pCoeffs,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pState,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepState - arraySizepCoeffs + 1;

    arm_status returnValue = arm_fir_interpolate_init_f32(selfS->instance,(uint8_t)L,numTaps,pCoeffs_converted,pState_converted,blockSize);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_biquad_cas_df1_32x64_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  arm_biquad_cas_df1_32x64_ins_q31 *S_converted=NULL; // input
  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_biquad_cas_df1_32x64_q31(S_converted,pSrc_converted,pDst,blockSize);
 INT32ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_biquad_cas_df1_32x64_init_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  arm_biquad_cas_df1_32x64_ins_q31 *S_converted=NULL; // input
  uint32_t numStages; // input
  PyObject *pCoeffs=NULL; // input
  q31_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  q63_t *pState_converted=NULL; // input
  uint32_t postShift; // input

  if (PyArg_ParseTuple(args,"OiOOi",&S,&numStages,&pCoeffs,&pState,&postShift))
  {

    GETARGUMENT(pCoeffs,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pState,NPY_INT64,q63_t,q63_t);

    arm_biquad_cas_df1_32x64_init_q31(S_converted,(uint8_t)numStages,pCoeffs_converted,pState_converted,(uint8_t)postShift);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_biquad_cascade_df2T_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  float32_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_biquad_cascade_df2T_instance_f32Object *selfS = (ml_arm_biquad_cascade_df2T_instance_f32Object *)S;
    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*blockSize);


    arm_biquad_cascade_df2T_f32(selfS->instance,pSrc_converted,pDst,blockSize);
 FLOATARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_biquad_cascade_stereo_df2T_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  float32_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_biquad_cascade_stereo_df2T_instance_f32Object *selfS = (ml_arm_biquad_cascade_stereo_df2T_instance_f32Object *)S;
    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*blockSize);


    arm_biquad_cascade_stereo_df2T_f32(selfS->instance,pSrc_converted,pDst,blockSize);
 FLOATARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_biquad_cascade_df2T_f64(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  float64_t *pSrc_converted=NULL; // input
  float64_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_biquad_cascade_df2T_instance_f64Object *selfS = (ml_arm_biquad_cascade_df2T_instance_f64Object *)S;
    GETARGUMENT(pSrc,NPY_FLOAT64,float64_t,float64_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(float64_t)*blockSize);


    arm_biquad_cascade_df2T_f64(selfS->instance,pSrc_converted,pDst,blockSize);
 FLOAT64ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_biquad_cascade_df2T_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint32_t numStages; // input
  PyObject *pCoeffs=NULL; // input
  float32_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  float32_t *pState_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OiOO",&S,&numStages,&pCoeffs,&pState))
  {

    ml_arm_biquad_cascade_df2T_instance_f32Object *selfS = (ml_arm_biquad_cascade_df2T_instance_f32Object *)S;
    GETARGUMENT(pCoeffs,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pState,NPY_DOUBLE,double,float32_t);

    arm_biquad_cascade_df2T_init_f32(selfS->instance,(uint8_t)numStages,pCoeffs_converted,pState_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_biquad_cascade_stereo_df2T_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint32_t numStages; // input
  PyObject *pCoeffs=NULL; // input
  float32_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  float32_t *pState_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OiOO",&S,&numStages,&pCoeffs,&pState))
  {

    ml_arm_biquad_cascade_stereo_df2T_instance_f32Object *selfS = (ml_arm_biquad_cascade_stereo_df2T_instance_f32Object *)S;
    GETARGUMENT(pCoeffs,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pState,NPY_DOUBLE,double,float32_t);

    arm_biquad_cascade_stereo_df2T_init_f32(selfS->instance,(uint8_t)numStages,pCoeffs_converted,pState_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_biquad_cascade_df2T_init_f64(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint32_t numStages; // input
  PyObject *pCoeffs=NULL; // input
  float64_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  float64_t *pState_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OiOO",&S,&numStages,&pCoeffs,&pState))
  {

    ml_arm_biquad_cascade_df2T_instance_f64Object *selfS = (ml_arm_biquad_cascade_df2T_instance_f64Object *)S;
    GETARGUMENT(pCoeffs,NPY_FLOAT64,float64_t,float64_t);
    GETARGUMENT(pState,NPY_FLOAT64,float64_t,float64_t);

    arm_biquad_cascade_df2T_init_f64(selfS->instance,(uint8_t)numStages,pCoeffs_converted,pState_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_lattice_init_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numStages; // input
  PyObject *pCoeffs=NULL; // input
  q15_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  q15_t *pState_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OhOO",&S,&numStages,&pCoeffs,&pState))
  {

    ml_arm_fir_lattice_instance_q15Object *selfS = (ml_arm_fir_lattice_instance_q15Object *)S;
    GETARGUMENT(pCoeffs,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pState,NPY_INT16,int16_t,int16_t);

    arm_fir_lattice_init_q15(selfS->instance,numStages,pCoeffs_converted,pState_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_lattice_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_fir_lattice_instance_q15Object *selfS = (ml_arm_fir_lattice_instance_q15Object *)S;
    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_fir_lattice_q15(selfS->instance,pSrc_converted,pDst,blockSize);
 INT16ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_lattice_init_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numStages; // input
  PyObject *pCoeffs=NULL; // input
  q31_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  q31_t *pState_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OhOO",&S,&numStages,&pCoeffs,&pState))
  {

    ml_arm_fir_lattice_instance_q31Object *selfS = (ml_arm_fir_lattice_instance_q31Object *)S;
    GETARGUMENT(pCoeffs,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pState,NPY_INT32,int32_t,int32_t);

    arm_fir_lattice_init_q31(selfS->instance,numStages,pCoeffs_converted,pState_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_lattice_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_fir_lattice_instance_q31Object *selfS = (ml_arm_fir_lattice_instance_q31Object *)S;
    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_fir_lattice_q31(selfS->instance,pSrc_converted,pDst,blockSize);
 INT32ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_lattice_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numStages; // input
  PyObject *pCoeffs=NULL; // input
  float32_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  float32_t *pState_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OhOO",&S,&numStages,&pCoeffs,&pState))
  {

    ml_arm_fir_lattice_instance_f32Object *selfS = (ml_arm_fir_lattice_instance_f32Object *)S;
    GETARGUMENT(pCoeffs,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pState,NPY_DOUBLE,double,float32_t);

    arm_fir_lattice_init_f32(selfS->instance,numStages,pCoeffs_converted,pState_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_lattice_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  float32_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_fir_lattice_instance_f32Object *selfS = (ml_arm_fir_lattice_instance_f32Object *)S;
    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*blockSize);


    arm_fir_lattice_f32(selfS->instance,pSrc_converted,pDst,blockSize);
 FLOATARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_iir_lattice_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  float32_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_iir_lattice_instance_f32Object *selfS = (ml_arm_iir_lattice_instance_f32Object *)S;
    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*blockSize);


    arm_iir_lattice_f32(selfS->instance,pSrc_converted,pDst,blockSize);
 FLOATARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_iir_lattice_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numStages; // input
  PyObject *pkCoeffs=NULL; // input
  float32_t *pkCoeffs_converted=NULL; // input
  PyObject *pvCoeffs=NULL; // input
  float32_t *pvCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  float32_t *pState_converted=NULL; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OhOOO",&S,&numStages,&pkCoeffs,&pvCoeffs,&pState))
  {

    ml_arm_iir_lattice_instance_f32Object *selfS = (ml_arm_iir_lattice_instance_f32Object *)S;
    GETARGUMENT(pkCoeffs,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pvCoeffs,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pState,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepkCoeffs ;

    arm_iir_lattice_init_f32(selfS->instance,numStages,pkCoeffs_converted,pvCoeffs_converted,pState_converted,blockSize);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_iir_lattice_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_iir_lattice_instance_q31Object *selfS = (ml_arm_iir_lattice_instance_q31Object *)S;
    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_iir_lattice_q31(selfS->instance,pSrc_converted,pDst,blockSize);
 INT32ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_iir_lattice_init_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numStages; // input
  PyObject *pkCoeffs=NULL; // input
  q31_t *pkCoeffs_converted=NULL; // input
  PyObject *pvCoeffs=NULL; // input
  q31_t *pvCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  q31_t *pState_converted=NULL; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OhOOO",&S,&numStages,&pkCoeffs,&pvCoeffs,&pState))
  {

    ml_arm_iir_lattice_instance_q31Object *selfS = (ml_arm_iir_lattice_instance_q31Object *)S;
    GETARGUMENT(pkCoeffs,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pvCoeffs,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pState,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepkCoeffs ;

    arm_iir_lattice_init_q31(selfS->instance,numStages,pkCoeffs_converted,pvCoeffs_converted,pState_converted,blockSize);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_iir_lattice_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    ml_arm_iir_lattice_instance_q15Object *selfS = (ml_arm_iir_lattice_instance_q15Object *)S;
    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_iir_lattice_q15(selfS->instance,pSrc_converted,pDst,blockSize);
 INT16ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_iir_lattice_init_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numStages; // input
  PyObject *pkCoeffs=NULL; // input
  q15_t *pkCoeffs_converted=NULL; // input
  PyObject *pvCoeffs=NULL; // input
  q15_t *pvCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  q15_t *pState_converted=NULL; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OhOOO",&S,&numStages,&pkCoeffs,&pvCoeffs,&pState))
  {

    ml_arm_iir_lattice_instance_q15Object *selfS = (ml_arm_iir_lattice_instance_q15Object *)S;
    GETARGUMENT(pkCoeffs,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pvCoeffs,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pState,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepkCoeffs ;

    arm_iir_lattice_init_q15(selfS->instance,numStages,pkCoeffs_converted,pvCoeffs_converted,pState_converted,blockSize);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t fftLen; // input

  if (PyArg_ParseTuple(args,"Oh",&S,&fftLen))
  {

    ml_arm_cfft_instance_f32Object *selfS = (ml_arm_cfft_instance_f32Object *)S;

    arm_status returnValue = arm_cfft_init_f32(selfS->instance,fftLen);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_init_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t fftLen; // input

  if (PyArg_ParseTuple(args,"Oh",&S,&fftLen))
  {

    ml_arm_cfft_instance_q31Object *selfS = (ml_arm_cfft_instance_q31Object *)S;

    arm_status returnValue = arm_cfft_init_q31(selfS->instance,fftLen);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_init_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t fftLen; // input

  if (PyArg_ParseTuple(args,"Oh",&S,&fftLen))
  {

    ml_arm_cfft_instance_q15Object *selfS = (ml_arm_cfft_instance_q15Object *)S;

    arm_status returnValue = arm_cfft_init_q15(selfS->instance,fftLen);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_lms_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  PyObject *pRef=NULL; // input
  float32_t *pRef_converted=NULL; // input
  float32_t *pOut=NULL; // output
  PyObject *pErr=NULL; // input
  float32_t *pErr_converted=NULL; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OOOO",&S,&pSrc,&pRef,&pErr))
  {

    ml_arm_lms_instance_f32Object *selfS = (ml_arm_lms_instance_f32Object *)S;
    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pRef,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pErr,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pOut=PyMem_Malloc(sizeof(float32_t)*blockSize);


    arm_lms_f32(selfS->instance,pSrc_converted,pRef_converted,pOut,pErr_converted,blockSize);
 FLOATARRAY1(pOutOBJ,blockSize,pOut);

    PyObject *pythonResult = Py_BuildValue("O",pOutOBJ);

    FREEARGUMENT(pSrc_converted);
    FREEARGUMENT(pRef_converted);
    Py_DECREF(pOutOBJ);
    FREEARGUMENT(pErr_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_lms_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numTaps; // input
  PyObject *pCoeffs=NULL; // input
  float32_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  float32_t *pState_converted=NULL; // input
  float32_t mu; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OhOOf",&S,&numTaps,&pCoeffs,&pState,&mu))
  {

    ml_arm_lms_instance_f32Object *selfS = (ml_arm_lms_instance_f32Object *)S;
    GETARGUMENT(pCoeffs,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pState,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepState - arraySizepCoeffs + 1 ;

    arm_lms_init_f32(selfS->instance,numTaps,pCoeffs_converted,pState_converted,mu,blockSize);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_lms_init_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numTaps; // input
  PyObject *pCoeffs=NULL; // input
  q15_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  q15_t *pState_converted=NULL; // input
  q15_t mu; // input
  uint32_t blockSize; // input
  uint32_t postShift; // input

  if (PyArg_ParseTuple(args,"OhOOhi",&S,&numTaps,&pCoeffs,&pState,&mu,&postShift))
  {

    ml_arm_lms_instance_q15Object *selfS = (ml_arm_lms_instance_q15Object *)S;
    GETARGUMENT(pCoeffs,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pState,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepState - arraySizepCoeffs + 1 ;

    arm_lms_init_q15(selfS->instance,numTaps,pCoeffs_converted,pState_converted,mu,blockSize,postShift);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_lms_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  PyObject *pRef=NULL; // input
  q15_t *pRef_converted=NULL; // input
  q15_t *pOut=NULL; // output
  PyObject *pErr=NULL; // input
  q15_t *pErr_converted=NULL; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OOOO",&S,&pSrc,&pRef,&pErr))
  {

    ml_arm_lms_instance_q15Object *selfS = (ml_arm_lms_instance_q15Object *)S;
    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pRef,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pErr,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pOut=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_lms_q15(selfS->instance,pSrc_converted,pRef_converted,pOut,pErr_converted,blockSize);
 INT16ARRAY1(pOutOBJ,blockSize,pOut);

    PyObject *pythonResult = Py_BuildValue("O",pOutOBJ);

    FREEARGUMENT(pSrc_converted);
    FREEARGUMENT(pRef_converted);
    Py_DECREF(pOutOBJ);
    FREEARGUMENT(pErr_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_lms_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  PyObject *pRef=NULL; // input
  q31_t *pRef_converted=NULL; // input
  q31_t *pOut=NULL; // output
  PyObject *pErr=NULL; // input
  q31_t *pErr_converted=NULL; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OOOO",&S,&pSrc,&pRef,&pErr))
  {

    ml_arm_lms_instance_q31Object *selfS = (ml_arm_lms_instance_q31Object *)S;
    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pRef,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pErr,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pOut=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_lms_q31(selfS->instance,pSrc_converted,pRef_converted,pOut,pErr_converted,blockSize);
 INT32ARRAY1(pOutOBJ,blockSize,pOut);

    PyObject *pythonResult = Py_BuildValue("O",pOutOBJ);

    FREEARGUMENT(pSrc_converted);
    FREEARGUMENT(pRef_converted);
    Py_DECREF(pOutOBJ);
    FREEARGUMENT(pErr_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_lms_init_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numTaps; // input
  PyObject *pCoeffs=NULL; // input
  q31_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  q31_t *pState_converted=NULL; // input
  q31_t mu; // input
  uint32_t blockSize; // input
  uint32_t postShift; // input

  if (PyArg_ParseTuple(args,"OhOOii",&S,&numTaps,&pCoeffs,&pState,&mu,&postShift))
  {

    ml_arm_lms_instance_q31Object *selfS = (ml_arm_lms_instance_q31Object *)S;
    GETARGUMENT(pCoeffs,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pState,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepState - arraySizepCoeffs + 1 ;

    arm_lms_init_q31(selfS->instance,numTaps,pCoeffs_converted,pState_converted,mu,blockSize,postShift);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_lms_norm_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  PyObject *pRef=NULL; // input
  float32_t *pRef_converted=NULL; // input
  float32_t *pOut=NULL; // output
  PyObject *pErr=NULL; // input
  float32_t *pErr_converted=NULL; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OOOO",&S,&pSrc,&pRef,&pErr))
  {

    ml_arm_lms_norm_instance_f32Object *selfS = (ml_arm_lms_norm_instance_f32Object *)S;
    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pRef,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pErr,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pOut=PyMem_Malloc(sizeof(float32_t)*blockSize);


    arm_lms_norm_f32(selfS->instance,pSrc_converted,pRef_converted,pOut,pErr_converted,blockSize);
 FLOATARRAY1(pOutOBJ,blockSize,pOut);

    PyObject *pythonResult = Py_BuildValue("O",pOutOBJ);

    FREEARGUMENT(pSrc_converted);
    FREEARGUMENT(pRef_converted);
    Py_DECREF(pOutOBJ);
    FREEARGUMENT(pErr_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_lms_norm_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numTaps; // input
  PyObject *pCoeffs=NULL; // input
  float32_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  float32_t *pState_converted=NULL; // input
  float32_t mu; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OhOOf",&S,&numTaps,&pCoeffs,&pState,&mu))
  {

    ml_arm_lms_norm_instance_f32Object *selfS = (ml_arm_lms_norm_instance_f32Object *)S;
    GETARGUMENT(pCoeffs,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pState,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepState - arraySizepCoeffs + 1 ;

    arm_lms_norm_init_f32(selfS->instance,numTaps,pCoeffs_converted,pState_converted,mu,blockSize);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_lms_norm_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  PyObject *pRef=NULL; // input
  q31_t *pRef_converted=NULL; // input
  q31_t *pOut=NULL; // output
  PyObject *pErr=NULL; // input
  q31_t *pErr_converted=NULL; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OOOO",&S,&pSrc,&pRef,&pErr))
  {

    ml_arm_lms_norm_instance_q31Object *selfS = (ml_arm_lms_norm_instance_q31Object *)S;
    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pRef,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pErr,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pOut=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_lms_norm_q31(selfS->instance,pSrc_converted,pRef_converted,pOut,pErr_converted,blockSize);
 INT32ARRAY1(pOutOBJ,blockSize,pOut);

    PyObject *pythonResult = Py_BuildValue("O",pOutOBJ);

    FREEARGUMENT(pSrc_converted);
    FREEARGUMENT(pRef_converted);
    Py_DECREF(pOutOBJ);
    FREEARGUMENT(pErr_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_lms_norm_init_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numTaps; // input
  PyObject *pCoeffs=NULL; // input
  q31_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  q31_t *pState_converted=NULL; // input
  q31_t mu; // input
  uint32_t blockSize; // input
  uint32_t postShift; // input

  if (PyArg_ParseTuple(args,"OhOOii",&S,&numTaps,&pCoeffs,&pState,&mu,&postShift))
  {

    ml_arm_lms_norm_instance_q31Object *selfS = (ml_arm_lms_norm_instance_q31Object *)S;
    GETARGUMENT(pCoeffs,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pState,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepState - arraySizepCoeffs + 1 ;

    arm_lms_norm_init_q31(selfS->instance,numTaps,pCoeffs_converted,pState_converted,mu,blockSize,(uint8_t)postShift);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_lms_norm_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  PyObject *pRef=NULL; // input
  q15_t *pRef_converted=NULL; // input
  q15_t *pOut=NULL; // output
  PyObject *pErr=NULL; // input
  q15_t *pErr_converted=NULL; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OOOO",&S,&pSrc,&pRef,&pErr))
  {

    ml_arm_lms_norm_instance_q15Object *selfS = (ml_arm_lms_norm_instance_q15Object *)S;
    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pRef,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pErr,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pOut=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_lms_norm_q15(selfS->instance,pSrc_converted,pRef_converted,pOut,pErr_converted,blockSize);
 INT16ARRAY1(pOutOBJ,blockSize,pOut);

    PyObject *pythonResult = Py_BuildValue("O",pOutOBJ);

    FREEARGUMENT(pSrc_converted);
    FREEARGUMENT(pRef_converted);
    Py_DECREF(pOutOBJ);
    FREEARGUMENT(pErr_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_lms_norm_init_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numTaps; // input
  PyObject *pCoeffs=NULL; // input
  q15_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  q15_t *pState_converted=NULL; // input
  q15_t mu; // input
  uint32_t blockSize; // input
  uint32_t postShift; // input

  if (PyArg_ParseTuple(args,"OhOOhi",&S,&numTaps,&pCoeffs,&pState,&mu,&postShift))
  {

    ml_arm_lms_norm_instance_q15Object *selfS = (ml_arm_lms_norm_instance_q15Object *)S;
    GETARGUMENT(pCoeffs,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pState,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepState - arraySizepCoeffs + 1 ;

    arm_lms_norm_init_q15(selfS->instance,numTaps,pCoeffs_converted,pState_converted,mu,blockSize,(uint8_t)postShift);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_correlate_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  float32_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  float32_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  float32_t *pDst=NULL; // output

  if (PyArg_ParseTuple(args,"OiOi",&pSrcA,&srcALen,&pSrcB,&srcBLen))
  {

    GETARGUMENT(pSrcA,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pSrcB,NPY_DOUBLE,double,float32_t);
    uint32_t outputLength = 2*MAX(srcALen,srcBLen) - 1 ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*outputLength);


    arm_correlate_f32(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst);
 FLOATARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_correlate_opt_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q15_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q15_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q15_t *pDst=NULL; // output
  PyObject *pScratch=NULL; // input
  q15_t *pScratch_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OiOiO",&pSrcA,&srcALen,&pSrcB,&srcBLen,&pScratch))
  {

    GETARGUMENT(pSrcA,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pSrcB,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pScratch,NPY_INT16,int16_t,int16_t);
    uint32_t outputLength = 2*MAX(srcALen,srcBLen) - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*outputLength);


    arm_correlate_opt_q15(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst,pScratch_converted);
 INT16ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    FREEARGUMENT(pScratch_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_correlate_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q15_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q15_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q15_t *pDst=NULL; // output

  if (PyArg_ParseTuple(args,"OiOi",&pSrcA,&srcALen,&pSrcB,&srcBLen))
  {

    GETARGUMENT(pSrcA,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pSrcB,NPY_INT16,int16_t,int16_t);
    uint32_t outputLength = 2*MAX(srcALen,srcBLen) - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*outputLength);


    arm_correlate_q15(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst);
 INT16ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_correlate_fast_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q15_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q15_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q15_t *pDst=NULL; // output

  if (PyArg_ParseTuple(args,"OiOi",&pSrcA,&srcALen,&pSrcB,&srcBLen))
  {

    GETARGUMENT(pSrcA,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pSrcB,NPY_INT16,int16_t,int16_t);
    uint32_t outputLength = 2*MAX(srcALen,srcBLen) - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*outputLength);


    arm_correlate_fast_q15(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst);
 INT16ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_correlate_fast_opt_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q15_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q15_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q15_t *pDst=NULL; // output
  PyObject *pScratch=NULL; // input
  q15_t *pScratch_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OiOiO",&pSrcA,&srcALen,&pSrcB,&srcBLen,&pScratch))
  {

    GETARGUMENT(pSrcA,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pSrcB,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pScratch,NPY_INT16,int16_t,int16_t);
    uint32_t outputLength = 2*MAX(srcALen,srcBLen) - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*outputLength);


    arm_correlate_fast_opt_q15(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst,pScratch_converted);
 INT16ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    FREEARGUMENT(pScratch_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_correlate_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q31_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q31_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q31_t *pDst=NULL; // output

  if (PyArg_ParseTuple(args,"OiOi",&pSrcA,&srcALen,&pSrcB,&srcBLen))
  {

    GETARGUMENT(pSrcA,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pSrcB,NPY_INT32,int32_t,int32_t);
    uint32_t outputLength = 2*MAX(srcALen,srcBLen) - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*outputLength);


    arm_correlate_q31(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst);
 INT32ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_correlate_fast_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q31_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q31_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q31_t *pDst=NULL; // output

  if (PyArg_ParseTuple(args,"OiOi",&pSrcA,&srcALen,&pSrcB,&srcBLen))
  {

    GETARGUMENT(pSrcA,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pSrcB,NPY_INT32,int32_t,int32_t);
    uint32_t outputLength = 2*MAX(srcALen,srcBLen) - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*outputLength);


    arm_correlate_fast_q31(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst);
 INT32ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_correlate_opt_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q7_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q7_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q7_t *pDst=NULL; // output
  PyObject *pScratch1=NULL; // input
  q15_t *pScratch1_converted=NULL; // input
  PyObject *pScratch2=NULL; // input
  q15_t *pScratch2_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OiOiOO",&pSrcA,&srcALen,&pSrcB,&srcBLen,&pScratch1,&pScratch2))
  {

    GETARGUMENT(pSrcA,NPY_BYTE,int8_t,q7_t);
    GETARGUMENT(pSrcB,NPY_BYTE,int8_t,q7_t);
    GETARGUMENT(pScratch1,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pScratch2,NPY_INT16,int16_t,int16_t);
    uint32_t outputLength = 2*MAX(srcALen,srcBLen) - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q7_t)*outputLength);


    arm_correlate_opt_q7(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst,pScratch1_converted,pScratch2_converted);
 INT8ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    FREEARGUMENT(pScratch1_converted);
    FREEARGUMENT(pScratch2_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_correlate_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q7_t *pSrcA_converted=NULL; // input
  uint32_t srcALen; // input
  PyObject *pSrcB=NULL; // input
  q7_t *pSrcB_converted=NULL; // input
  uint32_t srcBLen; // input
  q7_t *pDst=NULL; // output

  if (PyArg_ParseTuple(args,"OiOi",&pSrcA,&srcALen,&pSrcB,&srcBLen))
  {

    GETARGUMENT(pSrcA,NPY_BYTE,int8_t,q7_t);
    GETARGUMENT(pSrcB,NPY_BYTE,int8_t,q7_t);
    uint32_t outputLength = 2*MAX(srcALen,srcBLen) - 1 ;
    
    pDst=PyMem_Malloc(sizeof(q7_t)*outputLength);


    arm_correlate_q7(pSrcA_converted,srcALen,pSrcB_converted,srcBLen,pDst);
 INT8ARRAY1(pDstOBJ,outputLength,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_sparse_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  float32_t *pDst=NULL; // output
  PyObject *pScratchIn=NULL; // input
  float32_t *pScratchIn_converted=NULL; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OOO",&S,&pSrc,&pScratchIn))
  {

    ml_arm_fir_sparse_instance_f32Object *selfS = (ml_arm_fir_sparse_instance_f32Object *)S;
    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pScratchIn,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*blockSize);


    arm_fir_sparse_f32(selfS->instance,pSrc_converted,pDst,pScratchIn_converted,blockSize);
 FLOATARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    FREEARGUMENT(pScratchIn_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_sparse_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numTaps; // input
  PyObject *pCoeffs=NULL; // input
  float32_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  float32_t *pState_converted=NULL; // input
  PyObject *pTapDelay=NULL; // input
  int32_t *pTapDelay_converted=NULL; // input
  uint16_t maxDelay; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OhOOOh",&S,&numTaps,&pCoeffs,&pState,&pTapDelay,&maxDelay))
  {

    ml_arm_fir_sparse_instance_f32Object *selfS = (ml_arm_fir_sparse_instance_f32Object *)S;
    GETARGUMENT(pCoeffs,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pState,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pTapDelay,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepState - arraySizepCoeffs + 1;

    arm_fir_sparse_init_f32(selfS->instance,numTaps,pCoeffs_converted,pState_converted,pTapDelay_converted,maxDelay,blockSize);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_sparse_init_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numTaps; // input
  PyObject *pCoeffs=NULL; // input
  q31_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  q31_t *pState_converted=NULL; // input
  PyObject *pTapDelay=NULL; // input
  int32_t *pTapDelay_converted=NULL; // input
  uint16_t maxDelay; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OhOOOh",&S,&numTaps,&pCoeffs,&pState,&pTapDelay,&maxDelay))
  {

    ml_arm_fir_sparse_instance_q31Object *selfS = (ml_arm_fir_sparse_instance_q31Object *)S;
    GETARGUMENT(pCoeffs,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pState,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pTapDelay,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepState - arraySizepCoeffs + 1;

    arm_fir_sparse_init_q31(selfS->instance,numTaps,pCoeffs_converted,pState_converted,pTapDelay_converted,maxDelay,blockSize);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_sparse_init_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numTaps; // input
  PyObject *pCoeffs=NULL; // input
  q15_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  q15_t *pState_converted=NULL; // input
  PyObject *pTapDelay=NULL; // input
  int32_t *pTapDelay_converted=NULL; // input
  uint16_t maxDelay; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OhOOOh",&S,&numTaps,&pCoeffs,&pState,&pTapDelay,&maxDelay))
  {

    ml_arm_fir_sparse_instance_q15Object *selfS = (ml_arm_fir_sparse_instance_q15Object *)S;
    GETARGUMENT(pCoeffs,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pState,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pTapDelay,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepState - arraySizepCoeffs + 1;

    arm_fir_sparse_init_q15(selfS->instance,numTaps,pCoeffs_converted,pState_converted,pTapDelay_converted,maxDelay,blockSize);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_fir_sparse_init_q7(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t numTaps; // input
  PyObject *pCoeffs=NULL; // input
  q7_t *pCoeffs_converted=NULL; // input
  PyObject *pState=NULL; // input
  q7_t *pState_converted=NULL; // input
  PyObject *pTapDelay=NULL; // input
  int32_t *pTapDelay_converted=NULL; // input
  uint16_t maxDelay; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OhOOOh",&S,&numTaps,&pCoeffs,&pState,&pTapDelay,&maxDelay))
  {

    ml_arm_fir_sparse_instance_q7Object *selfS = (ml_arm_fir_sparse_instance_q7Object *)S;
    GETARGUMENT(pCoeffs,NPY_BYTE,int8_t,q7_t);
    GETARGUMENT(pState,NPY_BYTE,int8_t,q7_t);
    GETARGUMENT(pTapDelay,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepState - arraySizepCoeffs + 1;

    arm_fir_sparse_init_q7(selfS->instance,numTaps,pCoeffs_converted,pState_converted,pTapDelay_converted,maxDelay,blockSize);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_sin_cos_f32(PyObject *obj, PyObject *args)
{

  float32_t theta; // input
  PyObject *pSinVal=NULL; // input
  float32_t *pSinVal_converted=NULL; // input
  PyObject *pCosVal=NULL; // input
  float32_t *pCosVal_converted=NULL; // input

  if (PyArg_ParseTuple(args,"fOO",&theta,&pSinVal,&pCosVal))
  {

    GETARGUMENT(pSinVal,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pCosVal,NPY_DOUBLE,double,float32_t);

    arm_sin_cos_f32(theta,pSinVal_converted,pCosVal_converted);
    FREEARGUMENT(pSinVal_converted);
    FREEARGUMENT(pCosVal_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_sin_cos_q31(PyObject *obj, PyObject *args)
{

  q31_t theta; // input
  PyObject *pSinVal=NULL; // input
  q31_t *pSinVal_converted=NULL; // input
  PyObject *pCosVal=NULL; // input
  q31_t *pCosVal_converted=NULL; // input

  if (PyArg_ParseTuple(args,"iOO",&theta,&pSinVal,&pCosVal))
  {

    GETARGUMENT(pSinVal,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pCosVal,NPY_INT32,int32_t,int32_t);

    arm_sin_cos_q31(theta,pSinVal_converted,pCosVal_converted);
    FREEARGUMENT(pSinVal_converted);
    FREEARGUMENT(pCosVal_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cmplx_conj_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  float32_t *pDst=NULL; // output
  uint32_t numSamples; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    numSamples = arraySizepSrc ;
    numSamples = numSamples / 2;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*2*numSamples);


    arm_cmplx_conj_f32(pSrc_converted,pDst,numSamples);
 FLOATARRAY1(pDstOBJ,2*numSamples,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cmplx_conj_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t numSamples; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    numSamples = arraySizepSrc ;
    numSamples = numSamples / 2;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*2*numSamples);


    arm_cmplx_conj_q31(pSrc_converted,pDst,numSamples);
 INT32ARRAY1(pDstOBJ,2*numSamples,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cmplx_conj_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t numSamples; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    numSamples = arraySizepSrc ;
    numSamples = numSamples / 2;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*2*numSamples);


    arm_cmplx_conj_q15(pSrc_converted,pDst,numSamples);
 INT16ARRAY1(pDstOBJ,2*numSamples,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cmplx_mag_squared_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  float32_t *pDst=NULL; // output
  uint32_t numSamples; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    numSamples = arraySizepSrc ;
    numSamples = numSamples / 2;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*2*numSamples);


    arm_cmplx_mag_squared_f32(pSrc_converted,pDst,numSamples);
 FLOATARRAY1(pDstOBJ,2*numSamples,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cmplx_mag_squared_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t numSamples; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    numSamples = arraySizepSrc ;
    numSamples = numSamples / 2;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*2*numSamples);


    arm_cmplx_mag_squared_q31(pSrc_converted,pDst,numSamples);
 INT32ARRAY1(pDstOBJ,2*numSamples,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cmplx_mag_squared_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t numSamples; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    numSamples = arraySizepSrc ;
    numSamples = numSamples / 2;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*2*numSamples);


    arm_cmplx_mag_squared_q15(pSrc_converted,pDst,numSamples);
 INT16ARRAY1(pDstOBJ,2*numSamples,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_pid_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  float32_t in; // input

  if (PyArg_ParseTuple(args,"Of",&S,&in))
  {

    ml_arm_pid_instance_f32Object *selfS = (ml_arm_pid_instance_f32Object *)S;

    float32_t returnValue = arm_pid_f32(selfS->instance,in);
    PyObject* theReturnOBJ=Py_BuildValue("f",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_pid_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  q31_t in; // input

  if (PyArg_ParseTuple(args,"Oi",&S,&in))
  {

    ml_arm_pid_instance_q31Object *selfS = (ml_arm_pid_instance_q31Object *)S;

    q31_t returnValue = arm_pid_q31(selfS->instance,in);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_pid_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  q15_t in; // input

  if (PyArg_ParseTuple(args,"Oh",&S,&in))
  {

    ml_arm_pid_instance_q15Object *selfS = (ml_arm_pid_instance_q15Object *)S;

    q15_t returnValue = arm_pid_q15(selfS->instance,in);
    PyObject* theReturnOBJ=Py_BuildValue("h",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mat_inverse_f32(PyObject *obj, PyObject *args)
{

  PyObject *src=NULL; // input
  arm_matrix_instance_f32 *src_converted=NULL; // input

  if (PyArg_ParseTuple(args,"O",&src))
  {

    arm_matrix_instance_f32 *src_converted = f32MatrixFromNumpy(src);
    uint32_t row = src_converted->numCols ;
    uint32_t column = src_converted->numRows ;
    arm_matrix_instance_f32 *dst_converted = createf32Matrix(row,column);

    arm_status returnValue = arm_mat_inverse_f32(src_converted,dst_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* dstOBJ=NumpyArrayFromf32Matrix(dst_converted);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,dstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(src_converted);
    Py_DECREF(dstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mat_inverse_f64(PyObject *obj, PyObject *args)
{

  PyObject *src=NULL; // input
  arm_matrix_instance_f64 *src_converted=NULL; // input

  if (PyArg_ParseTuple(args,"O",&src))
  {

    arm_matrix_instance_f64 *src_converted = f64MatrixFromNumpy(src);
    uint32_t row = src_converted->numCols ;
    uint32_t column = src_converted->numRows ;
    arm_matrix_instance_f64 *dst_converted = createf64Matrix(row,column);

    arm_status returnValue = arm_mat_inverse_f64(src_converted,dst_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* dstOBJ=NumpyArrayFromf64Matrix(dst_converted);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,dstOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(src_converted);
    Py_DECREF(dstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_clarke_f32(PyObject *obj, PyObject *args)
{

  float32_t Ia; // input
  float32_t Ib; // input
  PyObject *pIalpha=NULL; // input
  float32_t *pIalpha_converted=NULL; // input
  PyObject *pIbeta=NULL; // input
  float32_t *pIbeta_converted=NULL; // input

  if (PyArg_ParseTuple(args,"ffOO",&Ia,&Ib,&pIalpha,&pIbeta))
  {

    GETARGUMENT(pIalpha,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pIbeta,NPY_DOUBLE,double,float32_t);

    arm_clarke_f32(Ia,Ib,pIalpha_converted,pIbeta_converted);
    FREEARGUMENT(pIalpha_converted);
    FREEARGUMENT(pIbeta_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_clarke_q31(PyObject *obj, PyObject *args)
{

  q31_t Ia; // input
  q31_t Ib; // input
  PyObject *pIalpha=NULL; // input
  q31_t *pIalpha_converted=NULL; // input
  PyObject *pIbeta=NULL; // input
  q31_t *pIbeta_converted=NULL; // input

  if (PyArg_ParseTuple(args,"iiOO",&Ia,&Ib,&pIalpha,&pIbeta))
  {

    GETARGUMENT(pIalpha,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pIbeta,NPY_INT32,int32_t,int32_t);

    arm_clarke_q31(Ia,Ib,pIalpha_converted,pIbeta_converted);
    FREEARGUMENT(pIalpha_converted);
    FREEARGUMENT(pIbeta_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_q7_to_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q7_t *pSrc_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_BYTE,int8_t,q7_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_q7_to_q31(pSrc_converted,pDst,blockSize);
 INT32ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_inv_clarke_f32(PyObject *obj, PyObject *args)
{

  float32_t Ialpha; // input
  float32_t Ibeta; // input
  PyObject *pIa=NULL; // input
  float32_t *pIa_converted=NULL; // input
  PyObject *pIb=NULL; // input
  float32_t *pIb_converted=NULL; // input

  if (PyArg_ParseTuple(args,"ffOO",&Ialpha,&Ibeta,&pIa,&pIb))
  {

    GETARGUMENT(pIa,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pIb,NPY_DOUBLE,double,float32_t);

    arm_inv_clarke_f32(Ialpha,Ibeta,pIa_converted,pIb_converted);
    FREEARGUMENT(pIa_converted);
    FREEARGUMENT(pIb_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_inv_clarke_q31(PyObject *obj, PyObject *args)
{

  q31_t Ialpha; // input
  q31_t Ibeta; // input
  PyObject *pIa=NULL; // input
  q31_t *pIa_converted=NULL; // input
  PyObject *pIb=NULL; // input
  q31_t *pIb_converted=NULL; // input

  if (PyArg_ParseTuple(args,"iiOO",&Ialpha,&Ibeta,&pIa,&pIb))
  {

    GETARGUMENT(pIa,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pIb,NPY_INT32,int32_t,int32_t);

    arm_inv_clarke_q31(Ialpha,Ibeta,pIa_converted,pIb_converted);
    FREEARGUMENT(pIa_converted);
    FREEARGUMENT(pIb_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_q7_to_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q7_t *pSrc_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_BYTE,int8_t,q7_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_q7_to_q15(pSrc_converted,pDst,blockSize);
 INT16ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_park_f32(PyObject *obj, PyObject *args)
{

  float32_t Ialpha; // input
  float32_t Ibeta; // input
  PyObject *pId=NULL; // input
  float32_t *pId_converted=NULL; // input
  PyObject *pIq=NULL; // input
  float32_t *pIq_converted=NULL; // input
  float32_t sinVal; // input
  float32_t cosVal; // input

  if (PyArg_ParseTuple(args,"ffOOff",&Ialpha,&Ibeta,&pId,&pIq,&sinVal,&cosVal))
  {

    GETARGUMENT(pId,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pIq,NPY_DOUBLE,double,float32_t);

    arm_park_f32(Ialpha,Ibeta,pId_converted,pIq_converted,sinVal,cosVal);
    FREEARGUMENT(pId_converted);
    FREEARGUMENT(pIq_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_park_q31(PyObject *obj, PyObject *args)
{

  q31_t Ialpha; // input
  q31_t Ibeta; // input
  PyObject *pId=NULL; // input
  q31_t *pId_converted=NULL; // input
  PyObject *pIq=NULL; // input
  q31_t *pIq_converted=NULL; // input
  q31_t sinVal; // input
  q31_t cosVal; // input

  if (PyArg_ParseTuple(args,"iiOOii",&Ialpha,&Ibeta,&pId,&pIq,&sinVal,&cosVal))
  {

    GETARGUMENT(pId,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pIq,NPY_INT32,int32_t,int32_t);

    arm_park_q31(Ialpha,Ibeta,pId_converted,pIq_converted,sinVal,cosVal);
    FREEARGUMENT(pId_converted);
    FREEARGUMENT(pIq_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_q7_to_float(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q7_t *pSrc_converted=NULL; // input
  float32_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_BYTE,int8_t,q7_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*blockSize);


    arm_q7_to_float(pSrc_converted,pDst,blockSize);
 FLOATARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_inv_park_f32(PyObject *obj, PyObject *args)
{

  float32_t Id; // input
  float32_t Iq; // input
  PyObject *pIalpha=NULL; // input
  float32_t *pIalpha_converted=NULL; // input
  PyObject *pIbeta=NULL; // input
  float32_t *pIbeta_converted=NULL; // input
  float32_t sinVal; // input
  float32_t cosVal; // input

  if (PyArg_ParseTuple(args,"ffOOff",&Id,&Iq,&pIalpha,&pIbeta,&sinVal,&cosVal))
  {

    GETARGUMENT(pIalpha,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pIbeta,NPY_DOUBLE,double,float32_t);

    arm_inv_park_f32(Id,Iq,pIalpha_converted,pIbeta_converted,sinVal,cosVal);
    FREEARGUMENT(pIalpha_converted);
    FREEARGUMENT(pIbeta_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_inv_park_q31(PyObject *obj, PyObject *args)
{

  q31_t Id; // input
  q31_t Iq; // input
  PyObject *pIalpha=NULL; // input
  q31_t *pIalpha_converted=NULL; // input
  PyObject *pIbeta=NULL; // input
  q31_t *pIbeta_converted=NULL; // input
  q31_t sinVal; // input
  q31_t cosVal; // input

  if (PyArg_ParseTuple(args,"iiOOii",&Id,&Iq,&pIalpha,&pIbeta,&sinVal,&cosVal))
  {

    GETARGUMENT(pIalpha,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pIbeta,NPY_INT32,int32_t,int32_t);

    arm_inv_park_q31(Id,Iq,pIalpha_converted,pIbeta_converted,sinVal,cosVal);
    FREEARGUMENT(pIalpha_converted);
    FREEARGUMENT(pIbeta_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_q31_to_float(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  float32_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*blockSize);


    arm_q31_to_float(pSrc_converted,pDst,blockSize);
 FLOATARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_linear_interp_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  float32_t x; // input

  if (PyArg_ParseTuple(args,"Of",&S,&x))
  {

    ml_arm_linear_interp_instance_f32Object *selfS = (ml_arm_linear_interp_instance_f32Object *)S;

    float32_t returnValue = arm_linear_interp_f32(selfS->instance,x);
    PyObject* theReturnOBJ=Py_BuildValue("f",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_linear_interp_q31(PyObject *obj, PyObject *args)
{

  PyObject *pYData=NULL; // input
  q31_t *pYData_converted=NULL; // input
  q31_t x; // input
  uint32_t nValues; // input

  if (PyArg_ParseTuple(args,"Oii",&pYData,&x,&nValues))
  {

    GETARGUMENT(pYData,NPY_INT32,int32_t,int32_t);

    q31_t returnValue = arm_linear_interp_q31(pYData_converted,x,nValues);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pYData_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_linear_interp_q15(PyObject *obj, PyObject *args)
{

  PyObject *pYData=NULL; // input
  q15_t *pYData_converted=NULL; // input
  q31_t x; // input
  uint32_t nValues; // input

  if (PyArg_ParseTuple(args,"Oii",&pYData,&x,&nValues))
  {

    GETARGUMENT(pYData,NPY_INT16,int16_t,int16_t);

    q15_t returnValue = arm_linear_interp_q15(pYData_converted,x,nValues);
    PyObject* theReturnOBJ=Py_BuildValue("h",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pYData_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_linear_interp_q7(PyObject *obj, PyObject *args)
{

  PyObject *pYData=NULL; // input
  q7_t *pYData_converted=NULL; // input
  q31_t x; // input
  uint32_t nValues; // input

  if (PyArg_ParseTuple(args,"Oii",&pYData,&x,&nValues))
  {

    GETARGUMENT(pYData,NPY_BYTE,int8_t,q7_t);

    q7_t returnValue = arm_linear_interp_q7(pYData_converted,x,nValues);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    FREEARGUMENT(pYData_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_sin_f32(PyObject *obj, PyObject *args)
{

  float32_t x; // input

  if (PyArg_ParseTuple(args,"f",&x))
  {


    float32_t returnValue = arm_sin_f32(x);
    PyObject* theReturnOBJ=Py_BuildValue("f",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_sin_q31(PyObject *obj, PyObject *args)
{

  q31_t x; // input

  if (PyArg_ParseTuple(args,"i",&x))
  {


    q31_t returnValue = arm_sin_q31(x);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_sin_q15(PyObject *obj, PyObject *args)
{

  q15_t x; // input

  if (PyArg_ParseTuple(args,"h",&x))
  {


    q15_t returnValue = arm_sin_q15(x);
    PyObject* theReturnOBJ=Py_BuildValue("h",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cos_f32(PyObject *obj, PyObject *args)
{

  float32_t x; // input

  if (PyArg_ParseTuple(args,"f",&x))
  {


    float32_t returnValue = arm_cos_f32(x);
    PyObject* theReturnOBJ=Py_BuildValue("f",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cos_q31(PyObject *obj, PyObject *args)
{

  q31_t x; // input

  if (PyArg_ParseTuple(args,"i",&x))
  {


    q31_t returnValue = arm_cos_q31(x);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cos_q15(PyObject *obj, PyObject *args)
{

  q15_t x; // input

  if (PyArg_ParseTuple(args,"h",&x))
  {


    q15_t returnValue = arm_cos_q15(x);
    PyObject* theReturnOBJ=Py_BuildValue("h",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_sqrt_f32(PyObject *obj, PyObject *args)
{

  float32_t in; // input
  float32_t *pOut=NULL; // output

  if (PyArg_ParseTuple(args,"f",&in))
  {

    
    pOut=PyMem_Malloc(sizeof(float32_t)*1);


    arm_status returnValue = arm_sqrt_f32(in,pOut);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pOutOBJ=Py_BuildValue("f",*pOut);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pOutOBJ);

    Py_DECREF(theReturnOBJ);
    Py_DECREF(pOutOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_sqrt_q31(PyObject *obj, PyObject *args)
{

  q31_t in; // input
  q31_t *pOut=NULL; // output

  if (PyArg_ParseTuple(args,"i",&in))
  {

    
    pOut=PyMem_Malloc(sizeof(q31_t)*1);


    arm_status returnValue = arm_sqrt_q31(in,pOut);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pOutOBJ=Py_BuildValue("i",*pOut);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pOutOBJ);

    Py_DECREF(theReturnOBJ);
    Py_DECREF(pOutOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_sqrt_q15(PyObject *obj, PyObject *args)
{

  q15_t in; // input
  q15_t *pOut=NULL; // output

  if (PyArg_ParseTuple(args,"h",&in))
  {

    
    pOut=PyMem_Malloc(sizeof(q15_t)*1);


    arm_status returnValue = arm_sqrt_q15(in,pOut);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);
    PyObject* pOutOBJ=Py_BuildValue("h",*pOut);

    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pOutOBJ);

    Py_DECREF(theReturnOBJ);
    Py_DECREF(pOutOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_circularWrite_f32(PyObject *obj, PyObject *args)
{

  PyObject *circBuffer=NULL; // input
  int32_t *circBuffer_converted=NULL; // input
  int32_t L; // input
  PyObject *writeOffset=NULL; // input
  uint16_t *writeOffset_converted=NULL; // input
  int32_t bufferInc; // input
  PyObject *src=NULL; // input
  int32_t *src_converted=NULL; // input
  int32_t srcInc; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OiOiOi",&circBuffer,&L,&writeOffset,&bufferInc,&src,&srcInc))
  {

    GETARGUMENT(circBuffer,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(writeOffset,NPY_UINT16,uint16_t,uint16_t);
    GETARGUMENT(src,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizecircBuffer ;

    arm_circularWrite_f32(circBuffer_converted,L,writeOffset_converted,bufferInc,src_converted,srcInc,blockSize);
    FREEARGUMENT(circBuffer_converted);
    FREEARGUMENT(writeOffset_converted);
    FREEARGUMENT(src_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_circularWrite_q15(PyObject *obj, PyObject *args)
{

  PyObject *circBuffer=NULL; // input
  q15_t *circBuffer_converted=NULL; // input
  int32_t L; // input
  PyObject *writeOffset=NULL; // input
  uint16_t *writeOffset_converted=NULL; // input
  int32_t bufferInc; // input
  PyObject *src=NULL; // input
  q15_t *src_converted=NULL; // input
  int32_t srcInc; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OiOiOi",&circBuffer,&L,&writeOffset,&bufferInc,&src,&srcInc))
  {

    GETARGUMENT(circBuffer,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(writeOffset,NPY_UINT16,uint16_t,uint16_t);
    GETARGUMENT(src,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizecircBuffer ;

    arm_circularWrite_q15(circBuffer_converted,L,writeOffset_converted,bufferInc,src_converted,srcInc,blockSize);
    FREEARGUMENT(circBuffer_converted);
    FREEARGUMENT(writeOffset_converted);
    FREEARGUMENT(src_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_circularWrite_q7(PyObject *obj, PyObject *args)
{

  PyObject *circBuffer=NULL; // input
  q7_t *circBuffer_converted=NULL; // input
  int32_t L; // input
  PyObject *writeOffset=NULL; // input
  uint16_t *writeOffset_converted=NULL; // input
  int32_t bufferInc; // input
  PyObject *src=NULL; // input
  q7_t *src_converted=NULL; // input
  int32_t srcInc; // input
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"OiOiOi",&circBuffer,&L,&writeOffset,&bufferInc,&src,&srcInc))
  {

    GETARGUMENT(circBuffer,NPY_BYTE,int8_t,q7_t);
    GETARGUMENT(writeOffset,NPY_UINT16,uint16_t,uint16_t);
    GETARGUMENT(src,NPY_BYTE,int8_t,q7_t);
    blockSize = arraySizecircBuffer ;

    arm_circularWrite_q7(circBuffer_converted,L,writeOffset_converted,bufferInc,src_converted,srcInc,blockSize);
    FREEARGUMENT(circBuffer_converted);
    FREEARGUMENT(writeOffset_converted);
    FREEARGUMENT(src_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_power_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  q63_t *pResult=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(q63_t)*1);


    arm_power_q31(pSrc_converted,blockSize,pResult);
    PyObject* pResultOBJ=Py_BuildValue("L",*pResult);

    PyObject *pythonResult = Py_BuildValue("O",pResultOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_power_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  float32_t *pResult=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(float32_t)*1);


    arm_power_f32(pSrc_converted,blockSize,pResult);
    PyObject* pResultOBJ=Py_BuildValue("f",*pResult);

    PyObject *pythonResult = Py_BuildValue("O",pResultOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_power_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  q63_t *pResult=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(q63_t)*1);


    arm_power_q15(pSrc_converted,blockSize,pResult);
    PyObject* pResultOBJ=Py_BuildValue("L",*pResult);

    PyObject *pythonResult = Py_BuildValue("O",pResultOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_power_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q7_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  q31_t *pResult=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_BYTE,int8_t,q7_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(q31_t)*1);


    arm_power_q7(pSrc_converted,blockSize,pResult);
    PyObject* pResultOBJ=Py_BuildValue("i",*pResult);

    PyObject *pythonResult = Py_BuildValue("O",pResultOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mean_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q7_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  q7_t *pResult=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_BYTE,int8_t,q7_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(q7_t)*1);


    arm_mean_q7(pSrc_converted,blockSize,pResult);
    PyObject* pResultOBJ=Py_BuildValue("i",*pResult);

    PyObject *pythonResult = Py_BuildValue("O",pResultOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mean_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  q15_t *pResult=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(q15_t)*1);


    arm_mean_q15(pSrc_converted,blockSize,pResult);
    PyObject* pResultOBJ=Py_BuildValue("h",*pResult);

    PyObject *pythonResult = Py_BuildValue("O",pResultOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mean_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  q31_t *pResult=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(q31_t)*1);


    arm_mean_q31(pSrc_converted,blockSize,pResult);
    PyObject* pResultOBJ=Py_BuildValue("i",*pResult);

    PyObject *pythonResult = Py_BuildValue("O",pResultOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_mean_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  float32_t *pResult=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(float32_t)*1);


    arm_mean_f32(pSrc_converted,blockSize,pResult);
    PyObject* pResultOBJ=Py_BuildValue("f",*pResult);

    PyObject *pythonResult = Py_BuildValue("O",pResultOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_var_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  float32_t *pResult=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(float32_t)*1);


    arm_var_f32(pSrc_converted,blockSize,pResult);
    PyObject* pResultOBJ=Py_BuildValue("f",*pResult);

    PyObject *pythonResult = Py_BuildValue("O",pResultOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_var_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  q31_t *pResult=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(q31_t)*1);


    arm_var_q31(pSrc_converted,blockSize,pResult);
    PyObject* pResultOBJ=Py_BuildValue("i",*pResult);

    PyObject *pythonResult = Py_BuildValue("O",pResultOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_var_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  q15_t *pResult=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(q15_t)*1);


    arm_var_q15(pSrc_converted,blockSize,pResult);
    PyObject* pResultOBJ=Py_BuildValue("h",*pResult);

    PyObject *pythonResult = Py_BuildValue("O",pResultOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rms_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  float32_t *pResult=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(float32_t)*1);


    arm_rms_f32(pSrc_converted,blockSize,pResult);
    PyObject* pResultOBJ=Py_BuildValue("f",*pResult);

    PyObject *pythonResult = Py_BuildValue("O",pResultOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rms_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  q31_t *pResult=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(q31_t)*1);


    arm_rms_q31(pSrc_converted,blockSize,pResult);
    PyObject* pResultOBJ=Py_BuildValue("i",*pResult);

    PyObject *pythonResult = Py_BuildValue("O",pResultOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rms_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  q15_t *pResult=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(q15_t)*1);


    arm_rms_q15(pSrc_converted,blockSize,pResult);
    PyObject* pResultOBJ=Py_BuildValue("h",*pResult);

    PyObject *pythonResult = Py_BuildValue("O",pResultOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_std_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  float32_t *pResult=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(float32_t)*1);


    arm_std_f32(pSrc_converted,blockSize,pResult);
    PyObject* pResultOBJ=Py_BuildValue("f",*pResult);

    PyObject *pythonResult = Py_BuildValue("O",pResultOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_std_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  q31_t *pResult=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(q31_t)*1);


    arm_std_q31(pSrc_converted,blockSize,pResult);
    PyObject* pResultOBJ=Py_BuildValue("i",*pResult);

    PyObject *pythonResult = Py_BuildValue("O",pResultOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_std_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  q15_t *pResult=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(q15_t)*1);


    arm_std_q15(pSrc_converted,blockSize,pResult);
    PyObject* pResultOBJ=Py_BuildValue("h",*pResult);

    PyObject *pythonResult = Py_BuildValue("O",pResultOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cmplx_mag_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  float32_t *pDst=NULL; // output
  uint32_t numSamples; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    numSamples = arraySizepSrc ;
    numSamples = numSamples / 2;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*2*numSamples);


    arm_cmplx_mag_f32(pSrc_converted,pDst,numSamples);
 FLOATARRAY1(pDstOBJ,2*numSamples,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cmplx_mag_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t numSamples; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    numSamples = arraySizepSrc ;
    numSamples = numSamples / 2;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*2*numSamples);


    arm_cmplx_mag_q31(pSrc_converted,pDst,numSamples);
 INT32ARRAY1(pDstOBJ,2*numSamples,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cmplx_mag_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t numSamples; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    numSamples = arraySizepSrc ;
    numSamples = numSamples / 2;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*2*numSamples);


    arm_cmplx_mag_q15(pSrc_converted,pDst,numSamples);
 INT16ARRAY1(pDstOBJ,2*numSamples,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cmplx_dot_prod_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q15_t *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  q15_t *pSrcB_converted=NULL; // input
  uint32_t numSamples; // input
  q31_t *realResult=NULL; // output
  q31_t *imagResult=NULL; // output

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    GETARGUMENT(pSrcA,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pSrcB,NPY_INT16,int16_t,int16_t);
    numSamples = arraySizepSrcA ;
    numSamples = numSamples / 2;
    
    realResult=PyMem_Malloc(sizeof(q31_t)*1);

    
    imagResult=PyMem_Malloc(sizeof(q31_t)*1);


    arm_cmplx_dot_prod_q15(pSrcA_converted,pSrcB_converted,numSamples,realResult,imagResult);
    PyObject* realResultOBJ=Py_BuildValue("i",*realResult);
    PyObject* imagResultOBJ=Py_BuildValue("i",*imagResult);

    PyObject *pythonResult = Py_BuildValue("OO",realResultOBJ,imagResultOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(realResultOBJ);
    Py_DECREF(imagResultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cmplx_dot_prod_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q31_t *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  q31_t *pSrcB_converted=NULL; // input
  uint32_t numSamples; // input
  q63_t *realResult=NULL; // output
  q63_t *imagResult=NULL; // output

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    GETARGUMENT(pSrcA,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pSrcB,NPY_INT32,int32_t,int32_t);
    numSamples = arraySizepSrcA ;
    numSamples = numSamples / 2;
    
    realResult=PyMem_Malloc(sizeof(q63_t)*1);

    
    imagResult=PyMem_Malloc(sizeof(q63_t)*1);


    arm_cmplx_dot_prod_q31(pSrcA_converted,pSrcB_converted,numSamples,realResult,imagResult);
    PyObject* realResultOBJ=Py_BuildValue("L",*realResult);
    PyObject* imagResultOBJ=Py_BuildValue("L",*imagResult);

    PyObject *pythonResult = Py_BuildValue("OO",realResultOBJ,imagResultOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(realResultOBJ);
    Py_DECREF(imagResultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cmplx_dot_prod_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  float32_t *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  float32_t *pSrcB_converted=NULL; // input
  uint32_t numSamples; // input
  float32_t *realResult=NULL; // output
  float32_t *imagResult=NULL; // output

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    GETARGUMENT(pSrcA,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pSrcB,NPY_DOUBLE,double,float32_t);
    numSamples = arraySizepSrcA ;
    numSamples = numSamples / 2;
    
    realResult=PyMem_Malloc(sizeof(float32_t)*1);

    
    imagResult=PyMem_Malloc(sizeof(float32_t)*1);


    arm_cmplx_dot_prod_f32(pSrcA_converted,pSrcB_converted,numSamples,realResult,imagResult);
    PyObject* realResultOBJ=Py_BuildValue("f",*realResult);
    PyObject* imagResultOBJ=Py_BuildValue("f",*imagResult);

    PyObject *pythonResult = Py_BuildValue("OO",realResultOBJ,imagResultOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(realResultOBJ);
    Py_DECREF(imagResultOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cmplx_mult_real_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcCmplx=NULL; // input
  q15_t *pSrcCmplx_converted=NULL; // input
  PyObject *pSrcReal=NULL; // input
  q15_t *pSrcReal_converted=NULL; // input
  q15_t *pCmplxDst=NULL; // output
  uint32_t numSamples; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcCmplx,&pSrcReal))
  {

    GETARGUMENT(pSrcCmplx,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pSrcReal,NPY_INT16,int16_t,int16_t);
    numSamples = arraySizepSrcCmplx ;
    numSamples = numSamples / 2;
    
    pCmplxDst=PyMem_Malloc(sizeof(q15_t)*2*numSamples);


    arm_cmplx_mult_real_q15(pSrcCmplx_converted,pSrcReal_converted,pCmplxDst,numSamples);
 INT16ARRAY1(pCmplxDstOBJ,2*numSamples,pCmplxDst);

    PyObject *pythonResult = Py_BuildValue("O",pCmplxDstOBJ);

    FREEARGUMENT(pSrcCmplx_converted);
    FREEARGUMENT(pSrcReal_converted);
    Py_DECREF(pCmplxDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cmplx_mult_real_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrcCmplx=NULL; // input
  q31_t *pSrcCmplx_converted=NULL; // input
  PyObject *pSrcReal=NULL; // input
  q31_t *pSrcReal_converted=NULL; // input
  q31_t *pCmplxDst=NULL; // output
  uint32_t numSamples; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcCmplx,&pSrcReal))
  {

    GETARGUMENT(pSrcCmplx,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pSrcReal,NPY_INT32,int32_t,int32_t);
    numSamples = arraySizepSrcCmplx ;
    numSamples = numSamples / 2;
    
    pCmplxDst=PyMem_Malloc(sizeof(q31_t)*2*numSamples);


    arm_cmplx_mult_real_q31(pSrcCmplx_converted,pSrcReal_converted,pCmplxDst,numSamples);
 INT32ARRAY1(pCmplxDstOBJ,2*numSamples,pCmplxDst);

    PyObject *pythonResult = Py_BuildValue("O",pCmplxDstOBJ);

    FREEARGUMENT(pSrcCmplx_converted);
    FREEARGUMENT(pSrcReal_converted);
    Py_DECREF(pCmplxDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cmplx_mult_real_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrcCmplx=NULL; // input
  float32_t *pSrcCmplx_converted=NULL; // input
  PyObject *pSrcReal=NULL; // input
  float32_t *pSrcReal_converted=NULL; // input
  float32_t *pCmplxDst=NULL; // output
  uint32_t numSamples; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcCmplx,&pSrcReal))
  {

    GETARGUMENT(pSrcCmplx,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pSrcReal,NPY_DOUBLE,double,float32_t);
    numSamples = arraySizepSrcCmplx ;
    numSamples = numSamples / 2;
    
    pCmplxDst=PyMem_Malloc(sizeof(float32_t)*2*numSamples);


    arm_cmplx_mult_real_f32(pSrcCmplx_converted,pSrcReal_converted,pCmplxDst,numSamples);
 FLOATARRAY1(pCmplxDstOBJ,2*numSamples,pCmplxDst);

    PyObject *pythonResult = Py_BuildValue("O",pCmplxDstOBJ);

    FREEARGUMENT(pSrcCmplx_converted);
    FREEARGUMENT(pSrcReal_converted);
    Py_DECREF(pCmplxDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_min_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q7_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  q7_t *result=NULL; // output
  PyObject *index=NULL; // input
  uint32_t *index_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&pSrc,&index))
  {

    GETARGUMENT(pSrc,NPY_BYTE,int8_t,q7_t);
    GETARGUMENT(index,NPY_UINT32,uint32_t,uint32_t);
    blockSize = arraySizepSrc ;
    
    result=PyMem_Malloc(sizeof(q7_t)*1);


    arm_min_q7(pSrc_converted,blockSize,result,index_converted);
    PyObject* resultOBJ=Py_BuildValue("i",*result);

    PyObject *pythonResult = Py_BuildValue("O",resultOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(resultOBJ);
    FREEARGUMENT(index_converted);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_min_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  q15_t *pResult=NULL; // output
  uint32_t *pIndex=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(q15_t)*1);

    
    pIndex=PyMem_Malloc(sizeof(uint32_t)*1);


    arm_min_q15(pSrc_converted,blockSize,pResult,pIndex);
    PyObject* pResultOBJ=Py_BuildValue("h",*pResult);
    PyObject* pIndexOBJ=Py_BuildValue("i",*pIndex);

    PyObject *pythonResult = Py_BuildValue("OO",pResultOBJ,pIndexOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    Py_DECREF(pIndexOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_min_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  q31_t *pResult=NULL; // output
  uint32_t *pIndex=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(q31_t)*1);

    
    pIndex=PyMem_Malloc(sizeof(uint32_t)*1);


    arm_min_q31(pSrc_converted,blockSize,pResult,pIndex);
    PyObject* pResultOBJ=Py_BuildValue("i",*pResult);
    PyObject* pIndexOBJ=Py_BuildValue("i",*pIndex);

    PyObject *pythonResult = Py_BuildValue("OO",pResultOBJ,pIndexOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    Py_DECREF(pIndexOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_min_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  float32_t *pResult=NULL; // output
  uint32_t *pIndex=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(float32_t)*1);

    
    pIndex=PyMem_Malloc(sizeof(uint32_t)*1);


    arm_min_f32(pSrc_converted,blockSize,pResult,pIndex);
    PyObject* pResultOBJ=Py_BuildValue("f",*pResult);
    PyObject* pIndexOBJ=Py_BuildValue("i",*pIndex);

    PyObject *pythonResult = Py_BuildValue("OO",pResultOBJ,pIndexOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    Py_DECREF(pIndexOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_max_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q7_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  q7_t *pResult=NULL; // output
  uint32_t *pIndex=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_BYTE,int8_t,q7_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(q7_t)*1);

    
    pIndex=PyMem_Malloc(sizeof(uint32_t)*1);


    arm_max_q7(pSrc_converted,blockSize,pResult,pIndex);
    PyObject* pResultOBJ=Py_BuildValue("i",*pResult);
    PyObject* pIndexOBJ=Py_BuildValue("i",*pIndex);

    PyObject *pythonResult = Py_BuildValue("OO",pResultOBJ,pIndexOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    Py_DECREF(pIndexOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_max_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  q15_t *pResult=NULL; // output
  uint32_t *pIndex=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(q15_t)*1);

    
    pIndex=PyMem_Malloc(sizeof(uint32_t)*1);


    arm_max_q15(pSrc_converted,blockSize,pResult,pIndex);
    PyObject* pResultOBJ=Py_BuildValue("h",*pResult);
    PyObject* pIndexOBJ=Py_BuildValue("i",*pIndex);

    PyObject *pythonResult = Py_BuildValue("OO",pResultOBJ,pIndexOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    Py_DECREF(pIndexOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_max_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  q31_t *pResult=NULL; // output
  uint32_t *pIndex=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(q31_t)*1);

    
    pIndex=PyMem_Malloc(sizeof(uint32_t)*1);


    arm_max_q31(pSrc_converted,blockSize,pResult,pIndex);
    PyObject* pResultOBJ=Py_BuildValue("i",*pResult);
    PyObject* pIndexOBJ=Py_BuildValue("i",*pIndex);

    PyObject *pythonResult = Py_BuildValue("OO",pResultOBJ,pIndexOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    Py_DECREF(pIndexOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_max_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  uint32_t blockSize; // input
  float32_t *pResult=NULL; // output
  uint32_t *pIndex=NULL; // output

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pResult=PyMem_Malloc(sizeof(float32_t)*1);

    
    pIndex=PyMem_Malloc(sizeof(uint32_t)*1);


    arm_max_f32(pSrc_converted,blockSize,pResult,pIndex);
    PyObject* pResultOBJ=Py_BuildValue("f",*pResult);
    PyObject* pIndexOBJ=Py_BuildValue("i",*pIndex);

    PyObject *pythonResult = Py_BuildValue("OO",pResultOBJ,pIndexOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pResultOBJ);
    Py_DECREF(pIndexOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cmplx_mult_cmplx_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q15_t *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  q15_t *pSrcB_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t numSamples; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    GETARGUMENT(pSrcA,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pSrcB,NPY_INT16,int16_t,int16_t);
    numSamples = arraySizepSrcA ;
    numSamples = numSamples / 2;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*2*numSamples);


    arm_cmplx_mult_cmplx_q15(pSrcA_converted,pSrcB_converted,pDst,numSamples);
 INT16ARRAY1(pDstOBJ,2*numSamples,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cmplx_mult_cmplx_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  q31_t *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  q31_t *pSrcB_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t numSamples; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    GETARGUMENT(pSrcA,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pSrcB,NPY_INT32,int32_t,int32_t);
    numSamples = arraySizepSrcA ;
    numSamples = numSamples / 2;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*2*numSamples);


    arm_cmplx_mult_cmplx_q31(pSrcA_converted,pSrcB_converted,pDst,numSamples);
 INT32ARRAY1(pDstOBJ,2*numSamples,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cmplx_mult_cmplx_f32(PyObject *obj, PyObject *args)
{

  PyObject *pSrcA=NULL; // input
  float32_t *pSrcA_converted=NULL; // input
  PyObject *pSrcB=NULL; // input
  float32_t *pSrcB_converted=NULL; // input
  float32_t *pDst=NULL; // output
  uint32_t numSamples; // input

  if (PyArg_ParseTuple(args,"OO",&pSrcA,&pSrcB))
  {

    GETARGUMENT(pSrcA,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pSrcB,NPY_DOUBLE,double,float32_t);
    numSamples = arraySizepSrcA ;
    numSamples = numSamples / 2;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*2*numSamples);


    arm_cmplx_mult_cmplx_f32(pSrcA_converted,pSrcB_converted,pDst,numSamples);
 FLOATARRAY1(pDstOBJ,2*numSamples,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrcA_converted);
    FREEARGUMENT(pSrcB_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_float_to_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_float_to_q31(pSrc_converted,pDst,blockSize);
 INT32ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_float_to_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_float_to_q15(pSrc_converted,pDst,blockSize);
 INT16ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_float_to_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input
  q7_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q7_t)*blockSize);


    arm_float_to_q7(pSrc_converted,pDst,blockSize);
 INT8ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_q31_to_q15(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q15_t)*blockSize);


    arm_q31_to_q15(pSrc_converted,pDst,blockSize);
 INT16ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_q31_to_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  q7_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q7_t)*blockSize);


    arm_q31_to_q7(pSrc_converted,pDst,blockSize);
 INT8ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_q15_to_float(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  float32_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(float32_t)*blockSize);


    arm_q15_to_float(pSrc_converted,pDst,blockSize);
 FLOATARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_q15_to_q31(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q31_t)*blockSize);


    arm_q15_to_q31(pSrc_converted,pDst,blockSize);
 INT32ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_q15_to_q7(PyObject *obj, PyObject *args)
{

  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  q7_t *pDst=NULL; // output
  uint32_t blockSize; // input

  if (PyArg_ParseTuple(args,"O",&pSrc))
  {

    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    blockSize = arraySizepSrc ;
    
    pDst=PyMem_Malloc(sizeof(q7_t)*blockSize);


    arm_q15_to_q7(pSrc_converted,pDst,blockSize);
 INT8ARRAY1(pDstOBJ,blockSize,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    FREEARGUMENT(pSrc_converted);
    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_bilinear_interp_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  float32_t X; // input
  float32_t Y; // input

  if (PyArg_ParseTuple(args,"Off",&S,&X,&Y))
  {

    ml_arm_bilinear_interp_instance_f32Object *selfS = (ml_arm_bilinear_interp_instance_f32Object *)S;

    float32_t returnValue = arm_bilinear_interp_f32(selfS->instance,X,Y);
    PyObject* theReturnOBJ=Py_BuildValue("f",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_bilinear_interp_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  q31_t X; // input
  q31_t Y; // input

  if (PyArg_ParseTuple(args,"Oii",&S,&X,&Y))
  {

    ml_arm_bilinear_interp_instance_q31Object *selfS = (ml_arm_bilinear_interp_instance_q31Object *)S;

    q31_t returnValue = arm_bilinear_interp_q31(selfS->instance,X,Y);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_bilinear_interp_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  q31_t X; // input
  q31_t Y; // input

  if (PyArg_ParseTuple(args,"Oii",&S,&X,&Y))
  {

    ml_arm_bilinear_interp_instance_q15Object *selfS = (ml_arm_bilinear_interp_instance_q15Object *)S;

    q15_t returnValue = arm_bilinear_interp_q15(selfS->instance,X,Y);
    PyObject* theReturnOBJ=Py_BuildValue("h",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_bilinear_interp_q7(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  q31_t X; // input
  q31_t Y; // input

  if (PyArg_ParseTuple(args,"Oii",&S,&X,&Y))
  {

    ml_arm_bilinear_interp_instance_q7Object *selfS = (ml_arm_bilinear_interp_instance_q7Object *)S;

    q7_t returnValue = arm_bilinear_interp_q7(selfS->instance,X,Y);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyMethodDef CMSISMLMethods[] = {

{"arm_recip_q31",  cmsis_arm_recip_q31, METH_VARARGS,""},
{"arm_recip_q15",  cmsis_arm_recip_q15, METH_VARARGS,""},
{"arm_fir_q7",  cmsis_arm_fir_q7, METH_VARARGS,""},
{"arm_fir_init_q7",  cmsis_arm_fir_init_q7, METH_VARARGS,""},
{"arm_fir_q15",  cmsis_arm_fir_q15, METH_VARARGS,""},
{"arm_fir_fast_q15",  cmsis_arm_fir_fast_q15, METH_VARARGS,""},
{"arm_fir_init_q15",  cmsis_arm_fir_init_q15, METH_VARARGS,""},
{"arm_fir_q31",  cmsis_arm_fir_q31, METH_VARARGS,""},
{"arm_fir_fast_q31",  cmsis_arm_fir_fast_q31, METH_VARARGS,""},
{"arm_fir_init_q31",  cmsis_arm_fir_init_q31, METH_VARARGS,""},
{"arm_fir_f32",  cmsis_arm_fir_f32, METH_VARARGS,""},
{"arm_fir_init_f32",  cmsis_arm_fir_init_f32, METH_VARARGS,""},
{"arm_biquad_cascade_df1_q15",  cmsis_arm_biquad_cascade_df1_q15, METH_VARARGS,""},
{"arm_biquad_cascade_df1_init_q15",  cmsis_arm_biquad_cascade_df1_init_q15, METH_VARARGS,""},
{"arm_biquad_cascade_df1_fast_q15",  cmsis_arm_biquad_cascade_df1_fast_q15, METH_VARARGS,""},
{"arm_biquad_cascade_df1_q31",  cmsis_arm_biquad_cascade_df1_q31, METH_VARARGS,""},
{"arm_biquad_cascade_df1_fast_q31",  cmsis_arm_biquad_cascade_df1_fast_q31, METH_VARARGS,""},
{"arm_biquad_cascade_df1_init_q31",  cmsis_arm_biquad_cascade_df1_init_q31, METH_VARARGS,""},
{"arm_biquad_cascade_df1_f32",  cmsis_arm_biquad_cascade_df1_f32, METH_VARARGS,""},
{"arm_biquad_cascade_df1_init_f32",  cmsis_arm_biquad_cascade_df1_init_f32, METH_VARARGS,""},
{"arm_mat_add_f32",  cmsis_arm_mat_add_f32, METH_VARARGS,""},
{"arm_mat_add_q15",  cmsis_arm_mat_add_q15, METH_VARARGS,""},
{"arm_mat_add_q31",  cmsis_arm_mat_add_q31, METH_VARARGS,""},
{"arm_mat_cmplx_mult_f32",  cmsis_arm_mat_cmplx_mult_f32, METH_VARARGS,""},
{"arm_mat_cmplx_mult_q15",  cmsis_arm_mat_cmplx_mult_q15, METH_VARARGS,""},
{"arm_mat_cmplx_mult_q31",  cmsis_arm_mat_cmplx_mult_q31, METH_VARARGS,""},
{"arm_mat_trans_f32",  cmsis_arm_mat_trans_f32, METH_VARARGS,""},
{"arm_mat_trans_q15",  cmsis_arm_mat_trans_q15, METH_VARARGS,""},
{"arm_mat_trans_q31",  cmsis_arm_mat_trans_q31, METH_VARARGS,""},
{"arm_mat_mult_f32",  cmsis_arm_mat_mult_f32, METH_VARARGS,""},
{"arm_mat_mult_q15",  cmsis_arm_mat_mult_q15, METH_VARARGS,""},
{"arm_mat_mult_fast_q15",  cmsis_arm_mat_mult_fast_q15, METH_VARARGS,""},
{"arm_mat_mult_q31",  cmsis_arm_mat_mult_q31, METH_VARARGS,""},
{"arm_mat_mult_fast_q31",  cmsis_arm_mat_mult_fast_q31, METH_VARARGS,""},
{"arm_mat_sub_f32",  cmsis_arm_mat_sub_f32, METH_VARARGS,""},
{"arm_mat_sub_q15",  cmsis_arm_mat_sub_q15, METH_VARARGS,""},
{"arm_mat_sub_q31",  cmsis_arm_mat_sub_q31, METH_VARARGS,""},
{"arm_mat_scale_f32",  cmsis_arm_mat_scale_f32, METH_VARARGS,""},
{"arm_mat_scale_q15",  cmsis_arm_mat_scale_q15, METH_VARARGS,""},
{"arm_mat_scale_q31",  cmsis_arm_mat_scale_q31, METH_VARARGS,""},
{"arm_pid_init_f32",  cmsis_arm_pid_init_f32, METH_VARARGS,""},
{"arm_pid_reset_f32",  cmsis_arm_pid_reset_f32, METH_VARARGS,""},
{"arm_pid_init_q31",  cmsis_arm_pid_init_q31, METH_VARARGS,""},
{"arm_pid_reset_q31",  cmsis_arm_pid_reset_q31, METH_VARARGS,""},
{"arm_pid_init_q15",  cmsis_arm_pid_init_q15, METH_VARARGS,""},
{"arm_pid_reset_q15",  cmsis_arm_pid_reset_q15, METH_VARARGS,""},
{"arm_mult_q7",  cmsis_arm_mult_q7, METH_VARARGS,""},
{"arm_mult_q15",  cmsis_arm_mult_q15, METH_VARARGS,""},
{"arm_mult_q31",  cmsis_arm_mult_q31, METH_VARARGS,""},
{"arm_mult_f32",  cmsis_arm_mult_f32, METH_VARARGS,""},
{"arm_cfft_radix2_init_q15",  cmsis_arm_cfft_radix2_init_q15, METH_VARARGS,""},
{"arm_cfft_radix2_q15",  cmsis_arm_cfft_radix2_q15, METH_VARARGS,""},
{"arm_cfft_radix4_init_q15",  cmsis_arm_cfft_radix4_init_q15, METH_VARARGS,""},
{"arm_cfft_radix4_q15",  cmsis_arm_cfft_radix4_q15, METH_VARARGS,""},
{"arm_cfft_radix2_init_q31",  cmsis_arm_cfft_radix2_init_q31, METH_VARARGS,""},
{"arm_cfft_radix2_q31",  cmsis_arm_cfft_radix2_q31, METH_VARARGS,""},
{"arm_cfft_radix4_q31",  cmsis_arm_cfft_radix4_q31, METH_VARARGS,""},
{"arm_cfft_radix4_init_q31",  cmsis_arm_cfft_radix4_init_q31, METH_VARARGS,""},
{"arm_cfft_radix2_init_f32",  cmsis_arm_cfft_radix2_init_f32, METH_VARARGS,""},
{"arm_cfft_radix2_f32",  cmsis_arm_cfft_radix2_f32, METH_VARARGS,""},
{"arm_cfft_radix4_init_f32",  cmsis_arm_cfft_radix4_init_f32, METH_VARARGS,""},
{"arm_cfft_radix4_f32",  cmsis_arm_cfft_radix4_f32, METH_VARARGS,""},
{"arm_cfft_q15",  cmsis_arm_cfft_q15, METH_VARARGS,""},
{"arm_cfft_q31",  cmsis_arm_cfft_q31, METH_VARARGS,""},
{"arm_cfft_f32",  cmsis_arm_cfft_f32, METH_VARARGS,""},
{"arm_rfft_init_q15",  cmsis_arm_rfft_init_q15, METH_VARARGS,""},
{"arm_rfft_q15",  cmsis_arm_rfft_q15, METH_VARARGS,""},
{"arm_rfft_init_q31",  cmsis_arm_rfft_init_q31, METH_VARARGS,""},
{"arm_rfft_q31",  cmsis_arm_rfft_q31, METH_VARARGS,""},
{"arm_rfft_init_f32",  cmsis_arm_rfft_init_f32, METH_VARARGS,""},
{"arm_rfft_f32",  cmsis_arm_rfft_f32, METH_VARARGS,""},
{"arm_rfft_fast_init_f32",  cmsis_arm_rfft_fast_init_f32, METH_VARARGS,""},
{"arm_rfft_32_fast_init_f32",  cmsis_arm_rfft_32_fast_init_f32, METH_VARARGS,""},
{"arm_rfft_64_fast_init_f32",  cmsis_arm_rfft_64_fast_init_f32, METH_VARARGS,""},
{"arm_rfft_128_fast_init_f32",  cmsis_arm_rfft_128_fast_init_f32, METH_VARARGS,""},
{"arm_rfft_256_fast_init_f32",  cmsis_arm_rfft_256_fast_init_f32, METH_VARARGS,""},
{"arm_rfft_512_fast_init_f32",  cmsis_arm_rfft_512_fast_init_f32, METH_VARARGS,""},
{"arm_rfft_1024_fast_init_f32",  cmsis_arm_rfft_1024_fast_init_f32, METH_VARARGS,""},
{"arm_rfft_2048_fast_init_f32",  cmsis_arm_rfft_2048_fast_init_f32, METH_VARARGS,""},
{"arm_rfft_4096_fast_init_f32",  cmsis_arm_rfft_4096_fast_init_f32, METH_VARARGS,""},
{"arm_rfft_fast_f32",  cmsis_arm_rfft_fast_f32, METH_VARARGS,""},
{"arm_dct4_init_f32",  cmsis_arm_dct4_init_f32, METH_VARARGS,""},
{"arm_dct4_f32",  cmsis_arm_dct4_f32, METH_VARARGS,""},
{"arm_dct4_init_q31",  cmsis_arm_dct4_init_q31, METH_VARARGS,""},
{"arm_dct4_q31",  cmsis_arm_dct4_q31, METH_VARARGS,""},
{"arm_dct4_init_q15",  cmsis_arm_dct4_init_q15, METH_VARARGS,""},
{"arm_dct4_q15",  cmsis_arm_dct4_q15, METH_VARARGS,""},
{"arm_add_f32",  cmsis_arm_add_f32, METH_VARARGS,""},
{"arm_add_q7",  cmsis_arm_add_q7, METH_VARARGS,""},
{"arm_add_q15",  cmsis_arm_add_q15, METH_VARARGS,""},
{"arm_add_q31",  cmsis_arm_add_q31, METH_VARARGS,""},
{"arm_sub_f32",  cmsis_arm_sub_f32, METH_VARARGS,""},
{"arm_sub_q7",  cmsis_arm_sub_q7, METH_VARARGS,""},
{"arm_sub_q15",  cmsis_arm_sub_q15, METH_VARARGS,""},
{"arm_sub_q31",  cmsis_arm_sub_q31, METH_VARARGS,""},
{"arm_scale_f32",  cmsis_arm_scale_f32, METH_VARARGS,""},
{"arm_scale_q7",  cmsis_arm_scale_q7, METH_VARARGS,""},
{"arm_scale_q15",  cmsis_arm_scale_q15, METH_VARARGS,""},
{"arm_scale_q31",  cmsis_arm_scale_q31, METH_VARARGS,""},
{"arm_abs_q7",  cmsis_arm_abs_q7, METH_VARARGS,""},
{"arm_abs_f32",  cmsis_arm_abs_f32, METH_VARARGS,""},
{"arm_abs_q15",  cmsis_arm_abs_q15, METH_VARARGS,""},
{"arm_abs_q31",  cmsis_arm_abs_q31, METH_VARARGS,""},
{"arm_dot_prod_f32",  cmsis_arm_dot_prod_f32, METH_VARARGS,""},
{"arm_dot_prod_q7",  cmsis_arm_dot_prod_q7, METH_VARARGS,""},
{"arm_dot_prod_q15",  cmsis_arm_dot_prod_q15, METH_VARARGS,""},
{"arm_dot_prod_q31",  cmsis_arm_dot_prod_q31, METH_VARARGS,""},
{"arm_shift_q7",  cmsis_arm_shift_q7, METH_VARARGS,""},
{"arm_shift_q15",  cmsis_arm_shift_q15, METH_VARARGS,""},
{"arm_shift_q31",  cmsis_arm_shift_q31, METH_VARARGS,""},
{"arm_offset_f32",  cmsis_arm_offset_f32, METH_VARARGS,""},
{"arm_offset_q7",  cmsis_arm_offset_q7, METH_VARARGS,""},
{"arm_offset_q15",  cmsis_arm_offset_q15, METH_VARARGS,""},
{"arm_offset_q31",  cmsis_arm_offset_q31, METH_VARARGS,""},
{"arm_negate_f32",  cmsis_arm_negate_f32, METH_VARARGS,""},
{"arm_negate_q7",  cmsis_arm_negate_q7, METH_VARARGS,""},
{"arm_negate_q15",  cmsis_arm_negate_q15, METH_VARARGS,""},
{"arm_negate_q31",  cmsis_arm_negate_q31, METH_VARARGS,""},
{"arm_copy_f32",  cmsis_arm_copy_f32, METH_VARARGS,""},
{"arm_copy_q7",  cmsis_arm_copy_q7, METH_VARARGS,""},
{"arm_copy_q15",  cmsis_arm_copy_q15, METH_VARARGS,""},
{"arm_copy_q31",  cmsis_arm_copy_q31, METH_VARARGS,""},
{"arm_conv_f32",  cmsis_arm_conv_f32, METH_VARARGS,""},
{"arm_conv_opt_q15",  cmsis_arm_conv_opt_q15, METH_VARARGS,""},
{"arm_conv_q15",  cmsis_arm_conv_q15, METH_VARARGS,""},
{"arm_conv_fast_q15",  cmsis_arm_conv_fast_q15, METH_VARARGS,""},
{"arm_conv_fast_opt_q15",  cmsis_arm_conv_fast_opt_q15, METH_VARARGS,""},
{"arm_conv_q31",  cmsis_arm_conv_q31, METH_VARARGS,""},
{"arm_conv_fast_q31",  cmsis_arm_conv_fast_q31, METH_VARARGS,""},
{"arm_conv_opt_q7",  cmsis_arm_conv_opt_q7, METH_VARARGS,""},
{"arm_conv_q7",  cmsis_arm_conv_q7, METH_VARARGS,""},
{"arm_conv_partial_f32",  cmsis_arm_conv_partial_f32, METH_VARARGS,""},
{"arm_conv_partial_opt_q15",  cmsis_arm_conv_partial_opt_q15, METH_VARARGS,""},
{"arm_conv_partial_q15",  cmsis_arm_conv_partial_q15, METH_VARARGS,""},
{"arm_conv_partial_fast_q15",  cmsis_arm_conv_partial_fast_q15, METH_VARARGS,""},
{"arm_conv_partial_fast_opt_q15",  cmsis_arm_conv_partial_fast_opt_q15, METH_VARARGS,""},
{"arm_conv_partial_q31",  cmsis_arm_conv_partial_q31, METH_VARARGS,""},
{"arm_conv_partial_fast_q31",  cmsis_arm_conv_partial_fast_q31, METH_VARARGS,""},
{"arm_conv_partial_opt_q7",  cmsis_arm_conv_partial_opt_q7, METH_VARARGS,""},
{"arm_conv_partial_q7",  cmsis_arm_conv_partial_q7, METH_VARARGS,""},
{"arm_fir_decimate_f32",  cmsis_arm_fir_decimate_f32, METH_VARARGS,""},
{"arm_fir_decimate_init_f32",  cmsis_arm_fir_decimate_init_f32, METH_VARARGS,""},
{"arm_fir_decimate_q15",  cmsis_arm_fir_decimate_q15, METH_VARARGS,""},
{"arm_fir_decimate_fast_q15",  cmsis_arm_fir_decimate_fast_q15, METH_VARARGS,""},
{"arm_fir_decimate_init_q15",  cmsis_arm_fir_decimate_init_q15, METH_VARARGS,""},
{"arm_fir_decimate_q31",  cmsis_arm_fir_decimate_q31, METH_VARARGS,""},
{"arm_fir_decimate_fast_q31",  cmsis_arm_fir_decimate_fast_q31, METH_VARARGS,""},
{"arm_fir_decimate_init_q31",  cmsis_arm_fir_decimate_init_q31, METH_VARARGS,""},
{"arm_fir_interpolate_q15",  cmsis_arm_fir_interpolate_q15, METH_VARARGS,""},
{"arm_fir_interpolate_init_q15",  cmsis_arm_fir_interpolate_init_q15, METH_VARARGS,""},
{"arm_fir_interpolate_q31",  cmsis_arm_fir_interpolate_q31, METH_VARARGS,""},
{"arm_fir_interpolate_init_q31",  cmsis_arm_fir_interpolate_init_q31, METH_VARARGS,""},
{"arm_fir_interpolate_f32",  cmsis_arm_fir_interpolate_f32, METH_VARARGS,""},
{"arm_fir_interpolate_init_f32",  cmsis_arm_fir_interpolate_init_f32, METH_VARARGS,""},
{"arm_biquad_cas_df1_32x64_q31",  cmsis_arm_biquad_cas_df1_32x64_q31, METH_VARARGS,""},
{"arm_biquad_cas_df1_32x64_init_q31",  cmsis_arm_biquad_cas_df1_32x64_init_q31, METH_VARARGS,""},
{"arm_biquad_cascade_df2T_f32",  cmsis_arm_biquad_cascade_df2T_f32, METH_VARARGS,""},
{"arm_biquad_cascade_stereo_df2T_f32",  cmsis_arm_biquad_cascade_stereo_df2T_f32, METH_VARARGS,""},
{"arm_biquad_cascade_df2T_f64",  cmsis_arm_biquad_cascade_df2T_f64, METH_VARARGS,""},
{"arm_biquad_cascade_df2T_init_f32",  cmsis_arm_biquad_cascade_df2T_init_f32, METH_VARARGS,""},
{"arm_biquad_cascade_stereo_df2T_init_f32",  cmsis_arm_biquad_cascade_stereo_df2T_init_f32, METH_VARARGS,""},
{"arm_biquad_cascade_df2T_init_f64",  cmsis_arm_biquad_cascade_df2T_init_f64, METH_VARARGS,""},
{"arm_fir_lattice_init_q15",  cmsis_arm_fir_lattice_init_q15, METH_VARARGS,""},
{"arm_fir_lattice_q15",  cmsis_arm_fir_lattice_q15, METH_VARARGS,""},
{"arm_fir_lattice_init_q31",  cmsis_arm_fir_lattice_init_q31, METH_VARARGS,""},
{"arm_fir_lattice_q31",  cmsis_arm_fir_lattice_q31, METH_VARARGS,""},
{"arm_fir_lattice_init_f32",  cmsis_arm_fir_lattice_init_f32, METH_VARARGS,""},
{"arm_fir_lattice_f32",  cmsis_arm_fir_lattice_f32, METH_VARARGS,""},
{"arm_iir_lattice_f32",  cmsis_arm_iir_lattice_f32, METH_VARARGS,""},
{"arm_iir_lattice_init_f32",  cmsis_arm_iir_lattice_init_f32, METH_VARARGS,""},
{"arm_iir_lattice_q31",  cmsis_arm_iir_lattice_q31, METH_VARARGS,""},
{"arm_iir_lattice_init_q31",  cmsis_arm_iir_lattice_init_q31, METH_VARARGS,""},
{"arm_iir_lattice_q15",  cmsis_arm_iir_lattice_q15, METH_VARARGS,""},
{"arm_iir_lattice_init_q15",  cmsis_arm_iir_lattice_init_q15, METH_VARARGS,""},
{"arm_cfft_init_f32",  cmsis_arm_cfft_init_f32, METH_VARARGS,""},
{"arm_cfft_init_q31",  cmsis_arm_cfft_init_q31, METH_VARARGS,""},
{"arm_cfft_init_q15",  cmsis_arm_cfft_init_q15, METH_VARARGS,""},
{"arm_lms_f32",  cmsis_arm_lms_f32, METH_VARARGS,""},
{"arm_lms_init_f32",  cmsis_arm_lms_init_f32, METH_VARARGS,""},
{"arm_lms_init_q15",  cmsis_arm_lms_init_q15, METH_VARARGS,""},
{"arm_lms_q15",  cmsis_arm_lms_q15, METH_VARARGS,""},
{"arm_lms_q31",  cmsis_arm_lms_q31, METH_VARARGS,""},
{"arm_lms_init_q31",  cmsis_arm_lms_init_q31, METH_VARARGS,""},
{"arm_lms_norm_f32",  cmsis_arm_lms_norm_f32, METH_VARARGS,""},
{"arm_lms_norm_init_f32",  cmsis_arm_lms_norm_init_f32, METH_VARARGS,""},
{"arm_lms_norm_q31",  cmsis_arm_lms_norm_q31, METH_VARARGS,""},
{"arm_lms_norm_init_q31",  cmsis_arm_lms_norm_init_q31, METH_VARARGS,""},
{"arm_lms_norm_q15",  cmsis_arm_lms_norm_q15, METH_VARARGS,""},
{"arm_lms_norm_init_q15",  cmsis_arm_lms_norm_init_q15, METH_VARARGS,""},
{"arm_correlate_f32",  cmsis_arm_correlate_f32, METH_VARARGS,""},
{"arm_correlate_opt_q15",  cmsis_arm_correlate_opt_q15, METH_VARARGS,""},
{"arm_correlate_q15",  cmsis_arm_correlate_q15, METH_VARARGS,""},
{"arm_correlate_fast_q15",  cmsis_arm_correlate_fast_q15, METH_VARARGS,""},
{"arm_correlate_fast_opt_q15",  cmsis_arm_correlate_fast_opt_q15, METH_VARARGS,""},
{"arm_correlate_q31",  cmsis_arm_correlate_q31, METH_VARARGS,""},
{"arm_correlate_fast_q31",  cmsis_arm_correlate_fast_q31, METH_VARARGS,""},
{"arm_correlate_opt_q7",  cmsis_arm_correlate_opt_q7, METH_VARARGS,""},
{"arm_correlate_q7",  cmsis_arm_correlate_q7, METH_VARARGS,""},
{"arm_fir_sparse_f32",  cmsis_arm_fir_sparse_f32, METH_VARARGS,""},
{"arm_fir_sparse_init_f32",  cmsis_arm_fir_sparse_init_f32, METH_VARARGS,""},
{"arm_fir_sparse_init_q31",  cmsis_arm_fir_sparse_init_q31, METH_VARARGS,""},
{"arm_fir_sparse_init_q15",  cmsis_arm_fir_sparse_init_q15, METH_VARARGS,""},
{"arm_fir_sparse_init_q7",  cmsis_arm_fir_sparse_init_q7, METH_VARARGS,""},
{"arm_sin_cos_f32",  cmsis_arm_sin_cos_f32, METH_VARARGS,""},
{"arm_sin_cos_q31",  cmsis_arm_sin_cos_q31, METH_VARARGS,""},
{"arm_cmplx_conj_f32",  cmsis_arm_cmplx_conj_f32, METH_VARARGS,""},
{"arm_cmplx_conj_q31",  cmsis_arm_cmplx_conj_q31, METH_VARARGS,""},
{"arm_cmplx_conj_q15",  cmsis_arm_cmplx_conj_q15, METH_VARARGS,""},
{"arm_cmplx_mag_squared_f32",  cmsis_arm_cmplx_mag_squared_f32, METH_VARARGS,""},
{"arm_cmplx_mag_squared_q31",  cmsis_arm_cmplx_mag_squared_q31, METH_VARARGS,""},
{"arm_cmplx_mag_squared_q15",  cmsis_arm_cmplx_mag_squared_q15, METH_VARARGS,""},
{"arm_pid_f32",  cmsis_arm_pid_f32, METH_VARARGS,""},
{"arm_pid_q31",  cmsis_arm_pid_q31, METH_VARARGS,""},
{"arm_pid_q15",  cmsis_arm_pid_q15, METH_VARARGS,""},
{"arm_mat_inverse_f32",  cmsis_arm_mat_inverse_f32, METH_VARARGS,""},
{"arm_mat_inverse_f64",  cmsis_arm_mat_inverse_f64, METH_VARARGS,""},
{"arm_clarke_f32",  cmsis_arm_clarke_f32, METH_VARARGS,""},
{"arm_clarke_q31",  cmsis_arm_clarke_q31, METH_VARARGS,""},
{"arm_q7_to_q31",  cmsis_arm_q7_to_q31, METH_VARARGS,""},
{"arm_inv_clarke_f32",  cmsis_arm_inv_clarke_f32, METH_VARARGS,""},
{"arm_inv_clarke_q31",  cmsis_arm_inv_clarke_q31, METH_VARARGS,""},
{"arm_q7_to_q15",  cmsis_arm_q7_to_q15, METH_VARARGS,""},
{"arm_park_f32",  cmsis_arm_park_f32, METH_VARARGS,""},
{"arm_park_q31",  cmsis_arm_park_q31, METH_VARARGS,""},
{"arm_q7_to_float",  cmsis_arm_q7_to_float, METH_VARARGS,""},
{"arm_inv_park_f32",  cmsis_arm_inv_park_f32, METH_VARARGS,""},
{"arm_inv_park_q31",  cmsis_arm_inv_park_q31, METH_VARARGS,""},
{"arm_q31_to_float",  cmsis_arm_q31_to_float, METH_VARARGS,""},
{"arm_linear_interp_f32",  cmsis_arm_linear_interp_f32, METH_VARARGS,""},
{"arm_linear_interp_q31",  cmsis_arm_linear_interp_q31, METH_VARARGS,""},
{"arm_linear_interp_q15",  cmsis_arm_linear_interp_q15, METH_VARARGS,""},
{"arm_linear_interp_q7",  cmsis_arm_linear_interp_q7, METH_VARARGS,""},
{"arm_sin_f32",  cmsis_arm_sin_f32, METH_VARARGS,""},
{"arm_sin_q31",  cmsis_arm_sin_q31, METH_VARARGS,""},
{"arm_sin_q15",  cmsis_arm_sin_q15, METH_VARARGS,""},
{"arm_cos_f32",  cmsis_arm_cos_f32, METH_VARARGS,""},
{"arm_cos_q31",  cmsis_arm_cos_q31, METH_VARARGS,""},
{"arm_cos_q15",  cmsis_arm_cos_q15, METH_VARARGS,""},
{"arm_sqrt_f32",  cmsis_arm_sqrt_f32, METH_VARARGS,""},
{"arm_sqrt_q31",  cmsis_arm_sqrt_q31, METH_VARARGS,""},
{"arm_sqrt_q15",  cmsis_arm_sqrt_q15, METH_VARARGS,""},
{"arm_circularWrite_f32",  cmsis_arm_circularWrite_f32, METH_VARARGS,""},
{"arm_circularWrite_q15",  cmsis_arm_circularWrite_q15, METH_VARARGS,""},
{"arm_circularWrite_q7",  cmsis_arm_circularWrite_q7, METH_VARARGS,""},
{"arm_power_q31",  cmsis_arm_power_q31, METH_VARARGS,""},
{"arm_power_f32",  cmsis_arm_power_f32, METH_VARARGS,""},
{"arm_power_q15",  cmsis_arm_power_q15, METH_VARARGS,""},
{"arm_power_q7",  cmsis_arm_power_q7, METH_VARARGS,""},
{"arm_mean_q7",  cmsis_arm_mean_q7, METH_VARARGS,""},
{"arm_mean_q15",  cmsis_arm_mean_q15, METH_VARARGS,""},
{"arm_mean_q31",  cmsis_arm_mean_q31, METH_VARARGS,""},
{"arm_mean_f32",  cmsis_arm_mean_f32, METH_VARARGS,""},
{"arm_var_f32",  cmsis_arm_var_f32, METH_VARARGS,""},
{"arm_var_q31",  cmsis_arm_var_q31, METH_VARARGS,""},
{"arm_var_q15",  cmsis_arm_var_q15, METH_VARARGS,""},
{"arm_rms_f32",  cmsis_arm_rms_f32, METH_VARARGS,""},
{"arm_rms_q31",  cmsis_arm_rms_q31, METH_VARARGS,""},
{"arm_rms_q15",  cmsis_arm_rms_q15, METH_VARARGS,""},
{"arm_std_f32",  cmsis_arm_std_f32, METH_VARARGS,""},
{"arm_std_q31",  cmsis_arm_std_q31, METH_VARARGS,""},
{"arm_std_q15",  cmsis_arm_std_q15, METH_VARARGS,""},
{"arm_cmplx_mag_f32",  cmsis_arm_cmplx_mag_f32, METH_VARARGS,""},
{"arm_cmplx_mag_q31",  cmsis_arm_cmplx_mag_q31, METH_VARARGS,""},
{"arm_cmplx_mag_q15",  cmsis_arm_cmplx_mag_q15, METH_VARARGS,""},
{"arm_cmplx_dot_prod_q15",  cmsis_arm_cmplx_dot_prod_q15, METH_VARARGS,""},
{"arm_cmplx_dot_prod_q31",  cmsis_arm_cmplx_dot_prod_q31, METH_VARARGS,""},
{"arm_cmplx_dot_prod_f32",  cmsis_arm_cmplx_dot_prod_f32, METH_VARARGS,""},
{"arm_cmplx_mult_real_q15",  cmsis_arm_cmplx_mult_real_q15, METH_VARARGS,""},
{"arm_cmplx_mult_real_q31",  cmsis_arm_cmplx_mult_real_q31, METH_VARARGS,""},
{"arm_cmplx_mult_real_f32",  cmsis_arm_cmplx_mult_real_f32, METH_VARARGS,""},
{"arm_min_q7",  cmsis_arm_min_q7, METH_VARARGS,""},
{"arm_min_q15",  cmsis_arm_min_q15, METH_VARARGS,""},
{"arm_min_q31",  cmsis_arm_min_q31, METH_VARARGS,""},
{"arm_min_f32",  cmsis_arm_min_f32, METH_VARARGS,""},
{"arm_max_q7",  cmsis_arm_max_q7, METH_VARARGS,""},
{"arm_max_q15",  cmsis_arm_max_q15, METH_VARARGS,""},
{"arm_max_q31",  cmsis_arm_max_q31, METH_VARARGS,""},
{"arm_max_f32",  cmsis_arm_max_f32, METH_VARARGS,""},
{"arm_cmplx_mult_cmplx_q15",  cmsis_arm_cmplx_mult_cmplx_q15, METH_VARARGS,""},
{"arm_cmplx_mult_cmplx_q31",  cmsis_arm_cmplx_mult_cmplx_q31, METH_VARARGS,""},
{"arm_cmplx_mult_cmplx_f32",  cmsis_arm_cmplx_mult_cmplx_f32, METH_VARARGS,""},
{"arm_float_to_q31",  cmsis_arm_float_to_q31, METH_VARARGS,""},
{"arm_float_to_q15",  cmsis_arm_float_to_q15, METH_VARARGS,""},
{"arm_float_to_q7",  cmsis_arm_float_to_q7, METH_VARARGS,""},
{"arm_q31_to_q15",  cmsis_arm_q31_to_q15, METH_VARARGS,""},
{"arm_q31_to_q7",  cmsis_arm_q31_to_q7, METH_VARARGS,""},
{"arm_q15_to_float",  cmsis_arm_q15_to_float, METH_VARARGS,""},
{"arm_q15_to_q31",  cmsis_arm_q15_to_q31, METH_VARARGS,""},
{"arm_q15_to_q7",  cmsis_arm_q15_to_q7, METH_VARARGS,""},
{"arm_bilinear_interp_f32",  cmsis_arm_bilinear_interp_f32, METH_VARARGS,""},
{"arm_bilinear_interp_q31",  cmsis_arm_bilinear_interp_q31, METH_VARARGS,""},
{"arm_bilinear_interp_q15",  cmsis_arm_bilinear_interp_q15, METH_VARARGS,""},
{"arm_bilinear_interp_q7",  cmsis_arm_bilinear_interp_q7, METH_VARARGS,""},

    {"error_out", (PyCFunction)error_out, METH_NOARGS, NULL},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

