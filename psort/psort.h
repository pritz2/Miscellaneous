/**
 * @file psort.h
 */

#ifndef _PSORT_H_
#define _PSORT_H_

#include <iostream>
#include <vector>
#include <omp.h>

using std::vector;

namespace ParallelSort
{
    /**
     * Public wrapper for the parallel sort implementation.
     * @param array The structure to sort
     */
	
    template <class T>
    void psort(vector<T>* array);
    
    template <class T>
    void quickSortLinear(vector<T>* array, int lb, int ub);
    
    template <class T>
    void quickSortParallel(vector<T>* array, int lb, int ub, int level);
    
    template <class T>
    int getPivot(vector<T>*array, int lb, int ub);
     /*
     template <class T>
     void mergeSortParallel(vector<T>* array, int lb, int ub, int level);
     
     template <class T>
     void mergeSortSingular(vector<T>* array, int lb, int ub);
     
     template <class T>
     void mergestack(vector<T>* array, int lb, int mid, int ub, int level);
     
     template <class T>
     void mergeheap(vector<T>* array, int lb, int mid, int ub, int level);
     */
}

#include "psort.cpp"
#endif
