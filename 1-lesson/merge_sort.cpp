#include <array>
#include <iostream>
#include <vector>

//////////////////////////////////////////////////////  mirazabal version  //////////////////////////////////////////////////////////////////

template<typename T>
void merge(std::vector<T>& v, uint64_t l, uint64_t middle, uint64_t r)
{
	std::vector<T> left(std::begin(v) + l, std::begin(v) + middle + 1 ) ;
	std::vector<T> right(std::begin(v)+middle+1, std::begin(v)+r+1 ) ;

	uint64_t left_index {0};
	uint64_t right_index {0};
	auto v_index = l;
	while( left_index < left.size()  && right_index < right.size() ){
	
		if(left[left_index] <= right[right_index]){
			v[v_index] = left[left_index];
			++left_index;
		} else {
			v[v_index] = right[right_index];
			++right_index;
		}
		++v_index;
	}		
	
	while(left_index < left.size() ){
		v[v_index] = left[left_index];
		++left_index;
		++v_index;
	}

	while(right_index < right.size() ){
		v[v_index] = right[right_index];
		++right_index;
		++v_index;
	}
}

template<typename T>
void merge_sort(std::vector<T>& v, uint64_t l, uint64_t r)
{
	if( l >= r ) return;
	auto sum = (r + l);
	auto middle = sum/2;
	merge_sort(v, l, middle);
	merge_sort(v, middle+1,r);
	
	merge(v, l, middle, r);
}

//////////////////////////////////////////////////////  mirazabal version  //////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////  https://www.geeksforgeeks.org/merge-sort/   //////////////////////////////////////////////////////////////////


// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}
 
/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

//////////////////////////////////////////////////////  https://www.geeksforgeeks.org/merge-sort/   //////////////////////////////////////////////////////////////////

int main()
{
	std::vector<int64_t> vec = {-100, 10, 31, 12, 2, 6, -390, 300, 32, 31, 50, -40 };
	merge_sort(vec, 0, vec.size()-1 );

	for(auto val : vec )
		std::cout << val << '\n';

}
