/*[1] You are given as input an unsorted array of n distinct numbers, where n is a power of 2. Give an algorithm that identifies the second-largest number in the array, and that uses at most n+logn−2 comparations.
*/

#include <array>
#include <iostream>
#include <iterator>


template<typename I>
constexpr I second_biggest(I first, I last)
{
	using T = typename std::iterator_traits<I>::value_type;
	
	if(first == last) return last;

	I f = first;
	std::advance(first,1);
	I s = first;
	if(first == last) return last;

	if(*f < *s) std::swap(f,s);
	while(first != last){
		if(*first > *f)
		{
			s = f;
			f = first;
		} else if(*first > *s) {
			s = first;
		}

		std::advance(first,1);
	}
	return s;
};

int main()
{

	std::array<uint64_t,16> arr = {1,3,2,4,6,9,7,3,10,43,267,90,32,16,87,90};	
	std::cout << *second_biggest(std::begin(arr), std::end(arr)) << '\n';
	return 0;
}
