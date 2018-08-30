/*
The goal of this problem is to implement a variant of the 2-SUM algorithm covered in this week's lectures.

The file contains 1 million integers, both positive and negative (there might be some repetitions!).This is your array of integers, with the ithi^{th}ith row of the file specifying the ithi^{th}ith entry of the array.

Your task is to compute the number of target values t in the interval [-10000,10000] (inclusive) such that there are distinct numbers x,y, in the input file that satisfy x+y=t. (NOTE: ensuring distinctness requires a one-line addition to the algorithm from lecture.)

Write your numeric answer (an integer between 0 and 20001) in the space provided.

OPTIONAL CHALLENGE: If this problem is too easy for you, try implementing your own hash table for it. For example, you could compare performance under the chaining and open addressing approaches to resolving collisions.
*/
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <istream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace mirazabal
{

template<typename T>
std::map<T,std::size_t> fillHasTable(std::vector<T> const& v)
{
  std::map<T,std::size_t> hashTable;
  for(auto a : v){
    hashTable[a] = 1;
   // auto it = hashTable.find(a);
   // if(it == std::end(hashTable) ){
   //   hashTable.insert(std::make_pair(a,1));
   // } else {
   //   ++it->second;
   // } 
  }
  return hashTable;
};

template<typename T>
std::vector<T> readAndFillVectorFromFile(std::string const& filePath)
{
  std::vector<T> vec;
  vec.reserve(10000000);
  std::ifstream file(filePath);
  std::string str;
  while(std::getline(file,str)){
    std::istringstream iss(str);
    T src;
    iss >> src;
    vec.emplace_back(src);
  }
  return vec;
};

template<typename T>
std::size_t sum2Algo(int64_t from, int64_t to, std::map<T,size_t> const &  hashMap, std::vector<T> const&  vec )
{
  size_t numberMatches{0};
  for(auto target = from; target < to+1; ++target){
    //std::cout << "Number seen so far = " << target << '\n';
	for(auto val : vec){
                auto rest = target - val;
		auto it_map = hashMap.find(rest);
		if(it_map != std::end(hashMap) && val != it_map->first){
                        std::cout << "value par =  " << val << " " << it_map->first << " target = "<< target << '\n'; 
			numberMatches += 1;//it.second;
                        break;
		}
	}	

  }
  return numberMatches;
};

} // namespace mirazabal

int main()
{
  auto vec = mirazabal::readAndFillVectorFromFile<int64_t>("2sum.txt");
  std::sort(std::begin(vec), std::end(vec));
  auto last = std::unique(std::begin(vec),std::end(vec));
  vec.erase(last, std::end(vec));
  auto hashTable = mirazabal::fillHasTable<int64_t>(vec);
  std::cout << mirazabal::sum2Algo<int64_t>(-10000,10000, hashTable,vec) << '\n';
  return 0;
}

