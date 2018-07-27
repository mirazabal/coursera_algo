#include <algorithm>
#include <array>
#include <fstream>
#include <iterator>
#include <iostream>
#include <vector>

static int64_t number_comparations{0};



// ------------------------------------------  https://www.geeksforgeeks.org/quick-sort/---------------------------------
// ----------------------------------------------------------------------------------------------------------------------

#include<stdio.h>
 
// A utility function to swap two elements
void swap_geeks(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 
/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition_geeks (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
 
    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap_geeks(&arr[i], &arr[j]);
        }
				++number_comparations;
    }
    swap_geeks(&arr[i + 1], &arr[high]);
    return (i + 1);
}
 
/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort_geeks(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition_geeks(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSort_geeks(arr, low, pi - 1);
        quickSort_geeks(arr, pi + 1, high);
    }
}


// ----------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------




template<typename I, typename Predicate>
I partition_mikel(I first, I last, Predicate p)
{
//	if(last <= first ) return last;
//	if(std::next(first) == last ) return last;

	I pivot = p(first,last); // pivot_pos;
	std::swap(*pivot,*first);
	pivot = first;
	std::advance(first,1);	
	I partition_point = first;

	while(first != last ){
		if(*first < *pivot ){
			std::swap(*first,*partition_point);
			++partition_point;
		}
		++number_comparations;
		++first;
	}
	partition_point=std::prev(partition_point);
	std::swap(*partition_point,*pivot);
	return partition_point;
};

template<typename I, typename Predicate>
void quicksort(I first, I last, Predicate p)
{
	if(std::distance(first,last) < 2 ) return;

	I pivot = partition_mikel(first,last,p);
	quicksort(first, pivot,p);
	quicksort(std::next(pivot),last,p);
};

std::vector<int64_t> fill_vector(std::ifstream inputFile)
{
	std::vector<int64_t> vec;
	vec.reserve(10000);
	std::istream_iterator<int64_t> input(inputFile);
	std::copy(input, std::istream_iterator<int64_t>(), std::back_inserter(vec));
	return vec;
}

int main()
{
	std::vector<int64_t> vec = fill_vector( std::ifstream("QuickSort.txt") );
	
	std::vector<int64_t> vec_first(vec);
	std::vector<int64_t> vec_last(vec);
	std::vector<int64_t> vec_median(vec);

	auto f_first = [=]( auto first, auto second){return first; };
	auto f_last = [=](auto first, auto last){ return std::prev(last);};
	auto f_median = [=](auto first, auto last){ 
					auto med = first + std::distance(first,last)/2;
					if( *first > *std::prev(last) && *first < *med || *first < *std::prev(last) && *first > *med)
						return first;
					if( *med > *first && *med < *std::prev(last) || *med < *first && *med > *std::prev(last))
					return med;

					return std::prev(last);
/*
					return std::max_element(std::min_element(first,std::prev(last)), 
													std::min_element(std::max_element(first,med),std::prev(last)));
*/
					 };

	number_comparations =  0;
	quicksort(std::begin(vec_first),std::end(vec_first), f_first);
	std::cout << "number of comparations first = " << number_comparations << '\n';

	number_comparations =  0;
	quicksort(std::begin(vec_last),std::end(vec_last), f_last);
	std::cout << "number of comparations last = " << number_comparations << '\n';

	number_comparations =  0;
	quicksort(std::begin(vec_median),std::end(vec_median), f_median);
	std::cout << "number of comparations median = " << number_comparations << '\n';

//	int arr[10000];
//	std::copy_n(vec.begin(), 10000,  arr);
//	quickSort_geeks( arr , 0, 10000-1);

//	for(auto val : vec){
//		std::cout << val << '\n';
//	}

	return 0;
}

