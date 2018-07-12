#include <algorithm>
#include <cassert>
#include <fstream>
#include <iterator>
#include <iostream>
#include <vector>

//////////////////////////////// https://www.cp.eng.chula.ac.th/~piak/teaching/algo/algo2008/count-inv.htm ///////////////////////////////////


template<typename T>
uint64_t numInversionsTrivial(std::vector<T> const & vec)
{
	uint64_t numInversions{0};
	for(auto it = std::begin(vec); it != std::end(vec) -1; ++it ){
		for(auto it2 = it + 1; it2 != std::end(vec); ++it2){
			if(*it2 < *it) ++numInversions;
		}
	}
	return numInversions;
};

std::vector<int64_t> fill_vector(std::ifstream inputFile)
{
	std::vector<int64_t> vec;
	vec.reserve(100000);
	std::istream_iterator<int64_t> input(inputFile);
	std::copy(input, std::istream_iterator<int64_t>(), std::back_inserter(vec));
	return vec;
}

template<typename T>
uint64_t merge_inv(std::vector<T>& vec, uint64_t l, uint64_t m, uint64_t r)
{
	std::vector<T> left(std::begin(vec) + l, std::begin(vec) + m + 1);
	std::vector<T> right(std::begin(vec) + m + 1, std::begin(vec) + r + 1);

	uint64_t l_index{0};
	uint64_t r_index{0};
	uint64_t v_index{l};
	uint64_t inversions{0};
	while(l_index < left.size() && r_index < right.size() ){
		if(left[l_index] <= right[r_index] ){
			vec[v_index] = left[l_index];
			++l_index;
		} else {
			vec[v_index] = right[r_index];
			inversions +=  left.size() - l_index;
			++r_index;	
		}		
		++v_index;
	}

	while(l_index < left.size() ){
		vec[v_index] = left[l_index];
		++l_index;
		++v_index;
	}
	while(r_index < right.size()){
		vec[v_index] = right[r_index];
		++r_index;
		++v_index;
	}
	return inversions;
};

template<typename T>
uint64_t merge_sort_count_inv(std::vector<T>& vec, uint64_t l, uint64_t r)
{
	if(l >= r) return 0;
	auto m = (l+r)/2;
	uint64_t a = merge_sort_count_inv(vec, l, m );	
	uint64_t b = merge_sort_count_inv(vec, m+1, r);	
	uint64_t c = merge_inv(vec,l,m,r);
	return a+b+c;
};

int main()
{
	std::vector<int64_t> vec = fill_vector( std::ifstream("IntegerArray.txt") );
	std::cout << "number of inversions = " << numInversionsTrivial(vec)  << '\n';
	std::cout << "number of inversions in merge = " << merge_sort_count_inv(vec, 0, vec.size() - 1)  << '\n';
//	assert(std::is_sorted(std::begin(vec), std::end(vec)) );
	return 0;
}
