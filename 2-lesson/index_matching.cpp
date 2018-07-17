/*
[3] You are given a sorted (from smallest to largest) array A of n distinct integers which can be positive, negative, or zero. You want to decide whether or not there is an index i such that A[i] = i. Design the fastest algorithm that you can for solving this problem.
*/

#include <array>
#include <iostream>

template<typename I>
I index_matching(I first, I last)
{
	if(first == last) return last;

	I f = first;
	I l = last;
	I m = first + std::distance(first, last)/2;
	
	while(m != first && m != last)
	{
		if(*m == std::distance(first,m)) return m;

		if(*m < std::distance(first,m) ){ 
			m = m + std::distance(m, l)/2;
			if(m == f) break;
			f = m;
		}
		else{
			m = first + std::distance(f,m)/2;
			if(m == l) break;
			l = m;
		}
	}
	return last;
};

int main()
{
	std::array<int64_t,8> arr = {-10,-8,-7,-6,-5,-4,0,7};
	std::cout << *index_matching(std::begin(arr),std::end(arr)) << '\n';
	return 0;
}

