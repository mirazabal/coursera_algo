#include <cstddef>
#include <iostream>
#include <vector>

void subset(std::vector<uint64_t> const& data, uint64_t index, uint64_t cardinalityLeft, std::vector<uint64_t> & helper, std::vector<std::vector<uint64_t>> & retVec)
{
	if(cardinalityLeft == 0 )
	{
 		retVec.emplace_back(helper);
		return;
	}
	for(auto i  = index; i < data.size(); ++i){
		helper.push_back(data[i]);
		subset(data, i+1, cardinalityLeft-1, helper, retVec);
		helper.pop_back();
	}
}

int main()
{
	std::vector<uint64_t> v{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};
	std::vector<uint64_t> helper;
	std::vector<std::vector<uint64_t>> retVal;
	subset(v,0,3,helper,retVal);

	for(auto const& v : retVal){
		for(auto val : v){
			std::cout << val  << " ";
		}
		std::cout << '\n';
	}

	return 0;
}
