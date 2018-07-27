#include <cstdint>
#include <iterator>
#include <iostream>
#include <vector>

template<typename I>
I randomized_select(I first, I last, uint64_t pos)
{
	if(first == last ) return last;

	std::cout << pos << std:: endl;
	I pivot = std::prev(last);
	I index = first;
	I l_index = first;
	while(index != pivot ){
		if(*index < *pivot){
			std::swap(*index, *l_index);
			++l_index;
		}
		++index;
	}
	
	std::swap(*pivot, *l_index);

	auto d = std::distance(first,l_index) + 1 ;

	if(d == pos) return l_index;
	if(d < pos){
		return quick_select(std::next(l_index) , last, pos - d);
	} else{
		return quick_select(first ,l_index, pos);
	}

	if(std::distance(first,last) <= 1) return last;
	return first;
};

int main()
{
	std::vector<int64_t> v = {1, -2, 0, -4, 3, -1, 2, -3, 4};
	std::cout << *randomized_select(std::begin(v), std::end(v), 5) << '\n';	
	return 0;
}


