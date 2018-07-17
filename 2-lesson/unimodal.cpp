/*
[2] You are a given a unimodal array of n distinct elements, meaning that its entries are in increasing order up until its maximum element, after which its elements are in decreasing order. Give an algorithm to compute the maximum element that runs in O(log n) time.
*/

#include <array>
#include <iostream>

template<typename I>
I max_point_unimodal(I first, I last)
{
	if(first == last) return first;

	I middle =  first + std::distance(first,last)/2;	
	if(*middle <= *first){
		return max_point_unimodal(first,middle);
	}
	return max_point_unimodal(middle,last);
}

int main()
{
	std::array<uint64_t,16> arr = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,13,12};
	std::cout << *max_point_unimodal(std::begin(arr),std::end(arr)) << '\n';
	return 0;
}

