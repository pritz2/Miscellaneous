/**
 * @file psort.cpp
 */

/**
 * Public wrapper for the parallel sort implementation.
 * @param array The structure to sort
 */

int THRESHOLD = 3500;
int RECTHRESH = 4;
int STACKTHRESH = 2800000;//2096800;

template <class T>
void ParallelSort::psort(vector<T>* array)
{
    // Serial sorting if below a certain threshold
    if(array->size() < THRESHOLD)
    {
        quickSortLinear(array, 0, array->size()-1);
    }
    else
    {
#       pragma omp parallel
        {
#           pragma omp single
            quickSortParallel(array, 0, array->size()-1, 0);
        }
    }
}

template <class T>
void ParallelSort::quickSortLinear(vector<T>* array, int lb, int ub)
{
    // Base Case
    if(ub <= lb)
        return;
   
    int pivotnum = getPivot(array,lb,ub);
    T pivot = (*array)[pivotnum];
    
    //int i = lb;
    //int j;
    T temp;
    
    // Swap pivot to bottom of list
    temp = (*array)[pivotnum];
    (*array)[pivotnum] = (*array)[lb];
    (*array)[lb] = temp;
    
    int left = lb;
    int right = ub;

    while(left < right)
    {
        while((*array)[left] <= pivot && (left < ub))
            left++;
        while(pivot < (*array)[right] && (right > lb))
            right--;
        if (left < right)
        {
            temp = (*array)[left];
            (*array)[left] = (*array)[right];
            (*array)[right] = temp;
        }
    }
    (*array)[lb] = (*array)[right];
    (*array)[right] = pivot;
    
    quickSortLinear(array,lb,right-1);
    quickSortLinear(array,right+1,ub);
}

template <class T>
void ParallelSort::quickSortParallel(vector<T>* array, int lb, int ub, int level)
{
    if(ub <= lb)
        return;
    
    int pivotnum = getPivot(array,lb,ub);
    T pivot = (*array)[pivotnum];
    
    //int i = lb;
    //int j;
    T temp;
    
    // Swap pivot to bottom of list
    temp = (*array)[pivotnum];
    (*array)[pivotnum] = (*array)[lb];
    (*array)[lb] = temp;
    
    int left = lb;
    int right = ub;
    
    while(left < right)
    {
        while((*array)[left] <= pivot)
            left++;
        while(pivot < (*array)[right])
            right--;
        if(left < right)
        {
            temp = (*array)[left];
            (*array)[left] = (*array)[right];
            (*array)[right] = temp;
        }
    }
    (*array)[lb] = (*array)[right];
    (*array)[right] = pivot;
    
    if(level < RECTHRESH)
    {
#       pragma omp task shared(array, right, level)
        quickSortParallel(array, lb, right-1, level+1);
        quickSortParallel(array, right+1, ub, level+1);
#       pragma omp taskwait
    }
    else
    {
        quickSortLinear(array, lb, right-1);
        quickSortLinear(array, right+1, ub);
    }
}

// Uses a "Median of 3" method to get a decent pivot, hopefully.
// For some reason though, this isn't helping with tests 2 and 3.
template <class T>
int ParallelSort::getPivot(vector<T>*array, int lb, int ub)
{
    T x = (*array)[lb];
    T y = (*array)[(ub+lb)/2];
    T z = (*array)[ub];
	T temp;
	int ret = (lb+ub)/2;
    if((y<x && x<z)||(z<x && x<y))
	{
		ret = lb;
		temp = (*array)[lb];
		(*array)[lb] = (*array)[(ub+lb)/2];
		(*array)[(ub+lb)/2] = temp;
	}
	else if((x<z && z<y)||(y<z && z<x))
	{
		ret = ub;
		temp = (*array)[ub];
		(*array)[ub] = (*array)[(ub+lb)/2];
		(*array)[(ub+lb)/2] = temp;
	}
    return ret;
}

/* I used to have a mergesort algorithm, and while more stable, */
/* it was poorer in practice so now I switched to quicksort to see if I */
/* have better luck */

/*
template <class T>
void ParallelSort::psort(vector<T>* array)
{
	if(array->size() > THRESHOLD)
	{
#   	pragma omp parallel
    	{
#   	    pragma omp single
    	    mergeSortParallel(array, 0, array->size()-1, 0);
    	}
	}
	else
		mergeSortSingular(array, 0, array->size()-1);
}

template <class T>
void ParallelSort::mergeSortParallel(vector<T>* array, int lb, int ub, int level)
{
    // Base Case: a trivial array of only 1 or 2 elements
    if(ub-lb <=1)
    {
        if ((*array)[ub] < (*array)[lb])
        {
            T tmp = (*array)[ub];
            (*array)[ub] = (*array)[lb];
            (*array)[lb] = tmp;
        }
    }
    else
    {
        // Splitpoint of array:
        int mid = (lb + ub) /  2;
        // Sort recursively:
		if(level < RECTHRESH)
        {
#           pragma omp task
        	mergeSortParallel(array, lb, mid, level+1);
        	mergeSortParallel(array, mid + 1, ub, level+1);
#       	pragma omp taskwait
		}
		else
		{
			mergeSortParallel(array, lb, mid, level);
        	mergeSortParallel(array, mid + 1, ub, level);
		}
        // Merge arrays:
		if(ub-lb < STACKTHRESH)
        	mergestack(array, lb, mid, ub, level);
		else
			mergeheap(array, lb, mid, ub, level);
    }
}

template <class T>
void ParallelSort::mergeSortSingular(vector<T>* array, int lb, int ub)
{
    // Base Case: a trivial array of only 1 or 2 elements
    if(ub-lb <=1)
    {
        if ((*array)[ub] < (*array)[lb])
        {
            T tmp = (*array)[ub];
            (*array)[ub] = (*array)[lb];
            (*array)[lb] = tmp;
        }
    }
    else
    {
        // Splitpoint of array:
        int mid = (lb + ub) /  2;
        // Sort recursively:
        mergeSortSingular(array, lb, mid);
        mergeSortSingular(array, mid + 1, ub);
        // Merge arrays:
        mergestack(array, lb, mid, ub, 0);
    }
}

template <class T>
void ParallelSort::mergeheap(vector<T>* array, int lb, int mid, int ub, int level)
{
    // Set up split arrays:
    int size1 = mid - lb + 1;
    int size2 = ub - mid;
    
    // Temp array must be allocated on the heap, or else I run into stack overflow issues
	T* temp1 = new T[size1];
    T* temp2 = new T[size2];
  
    for(int i=0; i<size1; i++)
        temp1[i] = (*array)[lb + i];
    for(int j=0; j<size2; j++)
        temp2[j] = (*array)[mid + 1 + j];
    
    int i = 0;
    int j = i;
    
    // Merge sorted temp arrays:
    for(int k=lb; k<=ub; k++)
    {
        if (i == size1 || (j!=size2 && temp1[i] > temp2[j]))
        {
            (*array)[k] = temp2[j];
            j++;
        }
        else
        {
            (*array)[k] = temp1[i];
            i++;
        }
    }
    delete[] temp1;
    delete[] temp2;
}

template <class T>
void ParallelSort::mergestack(vector<T>* array, int lb, int mid, int ub, int level)
{
    // Set up split arrays:
    int size1 = mid - lb + 1;
    int size2 = ub - mid;
    
    // Temp arrays are small enough, they can be put on the stack without risk of overflow
	T temp1 [size1];
    T temp2 [size2];

    for(int i=0; i<size1; i++)
        temp1[i] = (*array)[lb + i];
    for(int j=0; j<size2; j++)
        temp2[j] = (*array)[mid + 1 + j];
    
    int i = 0;
    int j = i;
    
    // Merge sorted temp arrays:
    for(int k=lb; k<=ub; k++)
    {
        if (i == size1 || (j!=size2 && temp1[i] > temp2[j]))
        {
            (*array)[k] = temp2[j];
            j++;
        }
        else
        {
            (*array)[k] = temp1[i];
            i++;
        }
    }
}
*/
