
/*
For this problem, use the same data set as in the previous problem.

Your task now is to run the greedy algorithm that schedules jobs (optimally) in decreasing order of the ratio (weight/length). In this algorithm, it does not matter how you break ties. You should report the sum of weighted completion times of the resulting schedule --- a positive integer --- in the box below
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

namespace mirazabal {
template<typename T>
std::vector<std::pair<T,T>> readAndFillVectorFromFile(std::string const& filePath)
{
 std::ifstream file(filePath);
  std::string str;
  std::getline(file,str);
  uint64_t lenght;
  std::istringstream iss(str);
  iss >> lenght;
  std::vector<std::pair<T,T>> vec;
  vec.reserve(lenght);
  while(std::getline(file,str)){
    std::istringstream iss(str);
    T  weight, lenght;
    iss >> weight >> lenght;
    vec.emplace_back(std::make_pair(weight,lenght));
  }
  return vec;
};


} // end namepsane mirazabal


int main()
{
  auto vec = mirazabal::readAndFillVectorFromFile<double>("jobs.txt");
  std::sort(std::begin(vec),std::end(vec),[](auto const& p1, auto const& p2)
      { 
        auto ratio1 =  p1.first/p1.second;
        auto ratio2 = p2.first/p2.second;
        if(ratio1 > ratio2)
          return true;
        return false;
      });
  uint64_t totalLenght{0};
  uint64_t functionCost{0};
  for(auto const& p : vec){
    totalLenght += p.second;
    functionCost += totalLenght*p.first; 
  
  }
  std::cout << functionCost << '\n';
  return 0;
}

