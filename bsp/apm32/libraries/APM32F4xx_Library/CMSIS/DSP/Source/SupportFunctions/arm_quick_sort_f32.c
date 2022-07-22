/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_quick_sort_f32.c
 * Description:  Floating point quick sort
 *
 * $Date:        23 April 2021
 * $Revision:    V1.9.0
 *
 * Target Processor: Cortex-M and Cortex-A cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2021 ARM Limited or its affiliates. All rights reserved.
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

#include "arm_sorting.h"

static uint32_t arm_quick_sort_partition_f32(float32_t *pSrc, int32_t first, int32_t last, uint8_t dir)
{
    /* This function will be called */
    int32_t i, j, pivot_index;
    float32_t pivot;
    float32_t temp;

    /* The first element is the pivot */
    pivot_index = first;
    pivot = pSrc[pivot_index];

    /* Initialize indices for do-while loops */
    i = first - 1;
    j = last + 1;

    while(i < j)
    {
        /* The loop will stop as soon as the indices i and j cross each other.
         *
         * This event will happen surely since the values of the indices are incremented and
         * decrement in the do-while loops that are executed at least once.
         * It is impossible to loop forever inside the do-while loops since the pivot is
         * always an element of the array and the conditions cannot be always true (at least
         * the i-th or the j-th element will be equal to the pivot-th element).
         * For example, in the extreme case of an ordered array the do-while loop related to i will stop
         * at the first iteration (because pSrc[i]=pSrc[pivot] already), and the loop related to j
         * will stop after (last-first) iterations (when j=pivot=i=first). j is returned and
         * j+1 is going to be used as pivot by other calls of the function, until j=pivot=last. */

        /* Move indices to the right and to the left */
        if(dir)
        {
            /* Compare left elements with pivot */
            do
            {
                i++;
            } while (pSrc[i] < pivot && i<last);

            /* Compare right elements with pivot */
            do
            {
                j--;
            } while (pSrc[j] > pivot);
        }
        else
        {
            /* Compare left elements with pivot */
            do
            {
                i++;
            } while (pSrc[i] > pivot && i<last);

            /* Compare right elements with pivot */
            do
            {
                j--;
            } while (pSrc[j] < pivot);
        }

        /* If the indices didn't cross each other */
        if (i < j)
        {
            /* i and j are in the wrong position -> Swap */
            temp=pSrc[i];
            pSrc[i]=pSrc[j];
            pSrc[j]=temp;
        }
    }

    return j;
}

static void arm_quick_sort_core_f32(float32_t *pSrc, int32_t first, int32_t last, uint8_t dir)
{
    /* If the array [first ... last] has more than one element */
    if(first<last)
    {
        int32_t pivot;

        /* Compute pivot */
        pivot = arm_quick_sort_partition_f32(pSrc, first, last, dir);

        /* Iterate algorithm with two sub-arrays [first ... pivot] and [pivot+1 ... last] */
        arm_quick_sort_core_f32(pSrc, first,   pivot, dir);
        arm_quick_sort_core_f32(pSrc, pivot+1, last,  dir);
    }
}

/**
  @ingroup groupSupport
 */

/**
  @addtogroup Sorting
  @{
 */

/**
   * @private
   * @param[in]      S          points to an instance of the sorting structure.
   * @param[in,out]  pSrc       points to the block of input data.
   * @param[out]     pDst       points to the block of output data.
   * @param[in]      blockSize  number of samples to process.
   *
   * @par        Algorithm
   *                The quick sort algorithm is a comparison algorithm that
   *                divides the input array into two smaller sub-arrays and
   *                recursively sort them. An element of the array (the pivot)
   *                is chosen, all the elements with values smaller than the
   *                pivot are moved before the pivot, while all elements with
   *                values greater than the pivot are moved after it (partition).
   *
   * @par
   *                In this implementation the Hoare partition scheme has been
   *                used [Hoare, C. A. R. (1 January 1962). "Quicksort". The Computer
   *                Journal. 5 (1): 10...16.] The first element has always been chosen
   *                as the pivot. The partition algorithm guarantees that the returned
   *                pivot is never placed outside the vector, since it is returned only
   *                when the pointers crossed each other. In this way it isn't
   *                possible to obtain empty partitions and infinite recursion is avoided.
   *
   * @par
   *                It's an in-place algorithm. In order to obtain an out-of-place
   *                function, a memcpy of the source vector is performed.
   */

void arm_quick_sort_f32(
  const arm_sort_instance_f32 * S,
        float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize)
{
    float32_t * pA;

    /* Out-of-place */
    if(pSrc != pDst)
    {
        memcpy(pDst, pSrc, blockSize*sizeof(float32_t) );
        pA = pDst;
    }
    else
        pA = pSrc;

    arm_quick_sort_core_f32(pA, 0, blockSize-1, S->dir);
    /* The previous function could be called recursively a maximum
     * of (blockSize-1) times, generating a stack consumption of 4*(blockSize-1) bytes. */
}

/**
  @} end of Sorting group
 */
